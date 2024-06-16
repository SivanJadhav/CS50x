from calendar import month
import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database

        # Get Data from Form
        name = request.form.get("name")
        # Error Check
        if not name:
            return redirect("/")

        # Error Check
        month = request.form.get("birthday_month")
        if not month:
            return redirect("/")
        try:
            month = int(month)
        except ValueError:
            return redirect("/")
        if not month >= 1 and month <= 12:
            return redirect("/")

        # Error Check
        day = request.form.get("birthday_day")
        if not day:
            return redirect("/")
        try:
            day = int(day)
        except ValueError:
            return redirect("/")
        if not day >= 1 and month <= 31:
            return redirect("/")

        # Adding data to form
        db.execute(
            "INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day
        )

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        INFO = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", info=INFO)
