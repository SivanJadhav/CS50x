from functools import wraps
from flask import Flask, render_template, session, redirect
from sys import exit

# Configuring Flask App
app = Flask(__name__)


# Apology Function
def apology(error_code, message):
    try:
        error_code = int(error_code)
    except ValueError:
        return exit(1)

    return render_template("sys/apology.html", error_code=error_code, message=message)


# Login_Required Function
def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/latest/patterns/viewdecorators/
    """

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function


# Function That Validates Password
def password_validator(user_password):
    # Checking If Input is Empty
    if not user_password:
        return False

    # Checking If It Is 12 Characters Long
    if len(user_password) < 12:
        return False

    # Define symbols
    symbols = ".!@#$%&"

    # Initialize conditions
    contains_upper = any(letter.isupper() for letter in user_password)
    contains_lower = any(letter.islower() for letter in user_password)
    contains_number = any(letter.isdigit() for letter in user_password)
    contains_symbol = any(letter in symbols for letter in user_password)

    # Check all conditions
    if contains_upper and contains_lower and contains_number and contains_symbol:
        return True

    return False


# Empty Input Validating Function
def errored_input(*args):
    for arg in args:
        if not arg:
            return False
        if arg is None:
            return False
