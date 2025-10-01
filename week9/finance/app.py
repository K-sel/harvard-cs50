import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

app = Flask(__name__)

app.jinja_env.filters["usd"] = usd

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    user = session["user_id"]

    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total > 0",
        user
    )

    cash_row = db.execute("SELECT cash FROM users WHERE id = ?", user)
    cash = cash_row[0]["cash"]

    total = cash

    for stock in stocks:
        q = lookup(stock["symbol"])
        stock["name"] = q["name"]
        stock["price"] = q["price"]
        stock["value"] = stock["price"] * stock["total"]
        total += stock["value"]

    return render_template("index.html", stocks=stocks, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        sym = request.form.get("symbol")
        shares = request.form.get("shares")

        if not sym:
            return apology("must provide symbol", 400)

        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must provide valid shares", 400)

        shares = int(shares)

        q = lookup(sym)

        if q is None:
            return apology("invalid symbol", 400)

        user = session["user_id"]
        cash_row = db.execute("SELECT cash FROM users WHERE id = ?", user)
        cash = cash_row[0]["cash"]

        price = q["price"]
        cost = price * shares

        if cash < cost:
            return apology("not enough cash", 400)

        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?",
            cost, user
        )

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user, sym.upper(), shares, price
        )

        flash("Bought!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    user = session["user_id"]

    trans = db.execute(
        "SELECT symbol, shares, price, timestamp FROM transactions WHERE user_id = ?",
        user
    )

    return render_template("history.html", transactions=trans)


@app.route("/login", methods=["GET", "POST"])
def login():
    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get(
                "username")
        )

        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "POST":
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("must provide symbol", 400)

        quote = lookup(symbol)
        print(quote)

        if quote is None:
            return apology("invalid symbol", 400)

        return render_template("quoted.html", quote=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirm-password")

        if not username:
            return apology("must provide username", 400)

        if not password:
            return apology("must provide password", 400)

        if not confirmation:
            return apology("must confirm password", 400)

        if password != confirmation:
            return apology("passwords must match", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) != 0:
            return apology("username already exists", 400)

        hash_pwd = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   username, hash_pwd)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user = session["user_id"]

    if request.method == "POST":
        sym = request.form.get("symbol")
        shares = request.form.get("shares")

        if not sym:
            return apology("must provide symbol", 400)

        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must provide valid shares", 400)

        shares = int(shares)

        owned = db.execute(
            "SELECT SUM(shares) as total FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
            user, sym
        )

        if len(owned) == 0 or owned[0]["total"] < shares:
            return apology("not enough shares", 400)

        q = lookup(sym)

        if q is None:
            return apology("invalid symbol", 400)

        price = q["price"]
        sale = price * shares

        db.execute(
            "UPDATE users SET cash = cash + ? WHERE id = ?",
            sale, user
        )

        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user, sym.upper(), -shares, price
        )

        flash("Sold!")
        return redirect("/")

    else:
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0",
            user
        )
        return render_template("sell.html", symbols=symbols)
