# Title: WorKing Out 50

# Setting Up The Imports
from cs50 import SQL
from datetime import timedelta
from flask import Flask, redirect, render_template, request, session
from flask_session import Session
import pycountry
from helpers import *
import requests as req
from werkzeug.security import check_password_hash, generate_password_hash

# Configure application
app = Flask(__name__)
app.secret_key = "!SivanJadhav26.CS50-2024?"

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = True

app.config["SESSION_TYPE"] = "filesystem"

app.config["PERMANENT_SESSION_LIFETIME"] = timedelta(hours=12)

Session(app)

# Setting Up the Database
db = SQL("sqlite:///static/wo50.db")


# User Dashboard
@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """The Homepage/Dashboard For Users"""

    # Sample data for exercises
    exercises = [
        {
            "name": "Push-Up",
            "description": "A basic upper body exercise that targets the chest, shoulders, and triceps.",
            "difficulty": "Medium",
        },
        {
            "name": "Squat",
            "description": "A fundamental lower body exercise that targets the thighs, hips, and buttocks.",
            "difficulty": "Medium",
        },
        {
            "name": "Plank",
            "description": "An isometric core strength exercise that involves maintaining a position similar to a push-up for the maximum possible time.",
            "difficulty": "Hard",
        },
        {
            "name": "Burpee",
            "description": "A full body exercise used in strength training and as an aerobic exercise.",
            "difficulty": "Hard",
        },
        {
            "name": "Lunge",
            "description": "A lower body exercise that works the thighs, hips, and buttocks.",
            "difficulty": "Medium",
        },
    ]

    return render_template("index.html", title="Dashboard", exercises=exercises)


# Registering User
@app.route("/register", methods=["GET", "POST"])
def register():
    """Registers User"""

    # Initializing Static Country List
    country_list = [country.name for country in pycountry.countries]

    # If the user is reaching via method post, that means, the user filled form, so validate its data
    if request.method == "POST":

        # Initializing Variables with Important Data
        name = request.form.get("full-name")

        username = request.form.get("username")

        password = request.form.get("password")
        confirmation_password = request.form.get("confirmation_password")

        nation = request.form.get("country")

        age = request.form.get("age")
        try:
            age = int(age)
        except ValueError:
            return apology(error_code=400, message="Age Not A Number")

        height = request.form.get("height")
        try:
            height = int(height)
        except ValueError:
            return apology(error_code=400, message="Height Not A Number")

        weight = request.form.get("weight")
        try:
            weight = int(weight)
        except ValueError:
            return apology(error_code=400, message="Weight Not A Number")

        # Checking If Any Of The Inputs Is Empty
        if (
            name
            or username
            or password
            or confirmation_password
            or nation
            or age
            or height
            or weight
        ) == "":
            return apology(error_code=400, message="All Fields Are Not Filled")

        # Validating Passwords
        if password_validator(password) == False:
            return apology(error_code=400, message="Password Not Valid")

        if password != confirmation_password:
            return apology(error_code=400, message="Passwords Not Matching")

        # Checking if The Username Already Exists
        existing_usernames = [
            row["username"] for row in (db.execute("SELECT username FROM users"))
        ]

        if username in existing_usernames:
            return apology(error_code=400, message="Username Already Taken")

        # Checking if The Selected Country is not in Country's List
        if nation not in country_list:
            return apology(error_code=400, message="Invalid Country Selected")

        # Checking If Age Is In Range
        if age < 0:
            return apology(error_code=400, message="Invalid Age (Negative Number)")

        # Validating Hashes, and Adding To SQL Database
        crr_user_hash = generate_password_hash(password)

        # Inserting Data Into Database
        query = """
        INSERT INTO
        users (hash, name, username, nation, age, height, weight)
        VALUES (?, ?, ?, ?, ?, ?, ?)"""

        db.execute(query, crr_user_hash, name, username, nation, age, height, weight)

        # Redirecting To Homepage After Success
        return redirect("/")

    # If the user is reaching via Get, render the html page
    else:
        return render_template("register.html", title="Register", nations=country_list)


# Users May Want To Login At Times
@app.route("/login", methods=["GET", "POST"])
def login():
    """Logs User In"""

    # Forgetting Any Logins
    session.clear()

    # If the User Is Reaching Via Post, By Submitting Form, Validate The Info
    if request.method == "POST":
        # Validating The Inputs

        # Initializing Variables With Important Info
        username = request.form.get("username")
        password = request.form.get("password")

        info = db.execute(
            "SELECT id, username, hash FROM users WHERE username = ?", username
        )

        # Username Validation
        if not username:
            return apology(error_code=400, message="Empty Username")

        elif username != info[0]["username"]:
            return apology(
                error_code=400, message="Username Not Found (Database Error)"
            )

        # Validating The Data
        if len(info) != 1:
            return apology(error_code=400, message="Database Error")

        # Password Validation
        if not password:
            return apology(error_code=400, message="Empty Password")

        elif not check_password_hash(info[0]["hash"], password):
            return apology(error_code=400, message="Wrong Password")

        # Remembering Which User Logged In
        session["user_id"] = info[0]["id"]

        # Redirecting To Homepage After Successful Login
        return redirect("/")

    else:
        # If Reaching Via Get, Render The HTML Page
        return render_template("login.html", title="Log In")


@app.route("/logout", methods=["GET", "POST"])
@login_required
def logout():
    """Logs User Out"""

    # Clearing Session
    session.clear()

    # Redirecting Back To Homepage
    return redirect("/")


# Users May Want To Change or See their Account Details
@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    """Helps The User See And Tweak Account Details"""

    # If The User Is Reaching Via Post, Handle and Validate Data
    if request.method == "POST":

        if request.form.get("select") == "username":
            # Initializing Variables With Important Input
            crr_username = request.form.get("crr_data")
            new_username = request.form.get("new_data")

            # Checking If Any Of The Inputs Is Empty
            if (not crr_username) or (not new_username):
                return apology(error_code=400, message="Empty New or Old Username")

            # Checking If Current Username Is Correct
            if (
                crr_username
                != (
                    db.execute(
                        "SELECT username FROM users WHERE id = ?", session["user_id"]
                    )
                )[0]["username"]
            ):
                return apology(error_code=400, message="Wrong Current Username Entered")

            # Updating Data
            db.execute("UPDATE users SET username = ?", new_username)

            # Redirecting To Home
            return redirect("/")

        elif request.form.get("select") == "password":
            # Initializing Variables With Important Input
            crr_password = request.form.get("crr_data")
            new_password = request.form.get("new_data")

            # Checking If Any Of The Inputs Is Empty
            if (not crr_password) or (not new_password):
                return apology(error_code=400, message="Empty New or Old Password")

            # Checking If Password Is Correct
            if not check_password_hash(
                password=crr_password,
                pwhash=(
                    db.execute(
                        "SELECT hash FROM users WHERE id = ?", session["user_id"]
                    )
                )[0]["hash"],
            ):
                return apology(error_code=400, message="Wrong Current Password")

            # Updating Data
            db.execute(
                "UPDATE users SET hash = ?", (generate_password_hash(new_password))
            )

            # Logging Out
            return logout()

        else:
            return apology(error_code=400, message="Invalid Option Selected")

    else:
        return render_template(
            "account.html",
            title="Account",
            username=(
                db.execute(
                    "SELECT username FROM users WHERE id = ?", session["user_id"]
                )
            )[0]["username"],
        )


@app.route("/diet")
@login_required
def diet():
    # API URL
    api_url = "https://api.edamam.com/api/food-database/v2/parser"
    params = {
        "app_id": "56db4fc9",
        "app_key": "3d67bc063d84a97d3063735ff511e7f8",
        "calories": "10-1000",
        "nutrients[CA]": "200-1200",
        "nutrients[SUGAR]": "20-40",
    }

    # Making the API call
    response = req.get(api_url, params=params)

    # Parsing the response
    data = response.json()

    return render_template("diet.html", title="Diet", data=data)


# <-- EOF -->
