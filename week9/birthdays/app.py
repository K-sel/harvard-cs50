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

        input = request.form.get("birthday")
        name = request.form.get("name")
        _, month, day = input.split('-')

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?,?,?);", name, month, day)

        return redirect("/")

    else:

        results = db.execute("SELECT * FROM birthdays;")
        for result in results:
            result["day"] = f"{result['day']:02}"
            result["month"] = f"{result['month']:02}"

    return render_template("index.html", results=results)
