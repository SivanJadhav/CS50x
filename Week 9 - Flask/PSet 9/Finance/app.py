from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Selecting Data
    shares = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? AND action = 'BUY' AND shares > 0 GROUP BY symbol",
        (session["user_id"]),
    )
    cash = db.execute("SELECT cash FROM users WHERE id = ?", (session["user_id"]))[0][
        "cash"
    ]

    prices = {}
    total_price = {}
    grand_total = cash

    for share in shares:
        symbol = share["symbol"]
        shares_count = share["shares"]

        # Fetching stock info for each symbol
        stock_info = lookup(symbol)

        if stock_info is not None:
            prices[symbol] = stock_info["price"]
            total_price[symbol] = stock_info["price"] * shares_count
            grand_total += total_price[symbol]
        else:
            # Handle case where stock info is not available
            prices[symbol] = 0
            total_price[symbol] = 0

    # Render the index page with symbols, prices, and other data
    return render_template(
        "index.html",
        shares=shares,
        price=prices,
        total_price=total_price,
        cash=cash,
        grand_total=grand_total,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    if request.method == "POST":
        # Symbol Error Checking
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Empty Input Not Accepted", code=400)
        elif not lookup(symbol):
            return apology("Invalid Input Not Accepted", code=400)

        # No. Of Shares Error Checking
        shares = request.form.get("shares")
        try:
            shares = int(shares or 0)
        except ValueError:
            return apology("Cannot Convert To Integer", code=400)

        if shares <= 0:
            return apology("Cannot Buy Shares Less Than 0", code=400)

        ran_price = lookup(symbol)
        if ran_price is None:
            return apology("None", code=400)
        elif not ran_price:
            return apology("Symbol Not Found", code=400)
        else:
            price = ran_price["price"]
        user_id = session["user_id"]
        cash_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0][
            "cash"
        ]
        if (price * shares) > cash_balance:
            return apology("Insufficient Funds", code=400)

        # Adding data to SQL Database, in transactions table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, shares_b_s, price, action) VALUES(?, ?, ?, ?, ?, ?)",
            session["user_id"],
            symbol,
            shares,
            shares,
            (price * shares),
            "BUY",
        )

        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            cash_balance - (price * shares),
            session["user_id"],
        )

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Retrieve all transactions for the user
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY id ASC",
        session["user_id"],
    )

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")  # type: ignore
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # If Method If Get
    if request.method == "GET":
        return render_template("quote.html")

    else:
        symbol = request.form.get("symbol")
        stock_info = lookup(symbol)
        if not stock_info:
            return apology("Invalid Symbol", code=400)
        return render_template("quoted.html", symbol=symbol, quote=stock_info["price"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Error Checking For Username
        usrname = request.form.get("username")
        existing_usernames = [
            row["username"] for row in db.execute("SELECT username FROM users")
        ]

        if not usrname:
            return apology("Provide Username", code=400)
        elif usrname in existing_usernames:
            return apology("Please Login, Username is already registered", code=400)

        # Error Checking For Password
        password = request.form.get("password")
        confirmation_password = request.form.get("confirmation")

        if not password or not confirmation_password:
            return apology("Blank Input not Accepted", code=400)
        elif password != confirmation_password:
            return apology("Not Matching", code=400)

        # After passing all tests, submitting their data to Database
        hashed_password = generate_password_hash(password)

        db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?)", usrname, hashed_password
        )

        # After passing all tests, redirect them back to home
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]

    # Retrieve distinct symbols and sum of shares bought by the user
    shares = db.execute(
        "SELECT symbol, SUM(shares) as shares FROM transactions WHERE shares > 0 GROUP BY symbol AND user_id = ?",
        user_id,
    )

    if request.method == "POST":
        # Get symbol and shares submitted by the user
        submitted_symbol = request.form.get("symbol")
        submitted_shares = request.form.get("shares")

        # Validate the submitted symbol and shares
        if not submitted_symbol:
            return apology("Symbol not provided", code=400)

        if not submitted_shares:
            return apology("Shares not provided", code=400)

        try:
            submitted_shares = int(submitted_shares)
            if submitted_shares <= 0:
                return apology("Shares must be a positive integer", code=400)
        except ValueError:
            return apology("Invalid number of shares", code=400)

        # Check if the submitted symbol is valid
        valid_symbol = False
        owned_shares = 0

        for item in shares:
            if item["symbol"] == submitted_symbol:
                valid_symbol = True
                owned_shares = item["shares"]
                break

        if valid_symbol == False:
            return apology("Invalid Symbol", code=400)

        if submitted_shares > owned_shares:
            return apology("Insufficient Shares", code=400)

        # Look up the current price of the submitted symbol
        result = lookup(submitted_symbol)
        if result is None:
            return apology("Symbol not found", code=400)

        # Calculate total proceeds from selling shares
        sale_proceeds = submitted_shares * result["price"]

        # Insert the sell transaction into the database
        db.execute(
            "UPDATE transactions SET shares = ?", owned_shares - submitted_shares
        )

        db.execute(
            "INSERT INTO transactions (action, symbol, shares, shares_b_s, price, user_id) VALUES (?, ?, ?, ?, ?, ?)",
            "SELL",
            submitted_symbol,
            (owned_shares - submitted_shares),
            submitted_shares,
            result["price"],
            user_id,
        )

        # Update user's cash after selling
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0][
            "cash"
        ]

        new_cash = current_cash + sale_proceeds

        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        # Redirect to home page after successful selling
        return redirect("/")
    else:
        symbol_list = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ?", user_id
        )

        # Render the sell page with symbols available for selling
        return render_template("sell.html", symbols=symbol_list)


# Personal Touch
@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == "POST":
        crr_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        wanted_cash = int(request.form.get("cash"))  # type: ignore
        if wanted_cash is None:
            return apology("None", code=400)

        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            (crr_cash[0]["cash"] + wanted_cash),
            session["user_id"],
        )

        return redirect("/")

    return render_template("add_cash.html")
