import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]
    rows = db.execute("SELECT * FROM portfolio WHERE user_id = ?", user_id)
    for row in rows:
        value = lookup(row["symbol"])
        row["name"] = value["name"]
        row["price"] = value["price"]
        row["total"] = row["shares"] * value["price"]

    rowUser = db.execute("SELECT * FROM users WHERE id = ?", user_id)
    rowSum = db.execute("SELECT SUM(price) FROM portfolio WHERE user_id = ?", user_id)
    print(rowSum, rowUser)
    totalValue = 0
    if rowSum[0]["SUM(price)"] is not None:
        totalValue = rowSum[0]["SUM(price)"]
    rowUser[0]["total"] = rowUser[0]["cash"] + totalValue
    return render_template("index.html", len=len(rows), value=rows, user=rowUser[0])


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
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        print("Username: ", username)
        print("Password: ", password)
        print("Confirmation: ", confirmation)

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password or not confirmation:
            return apology("must provide password", 400)

        # Ensure password matches confirmation
        elif password != confirmation:
            return apology("confirmation password did not match", 400)

        # Hash Password
        hash = generate_password_hash(password)
        print("Hash: ", hash)

        # Check if username already exisits
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) == 1:
            return apology("user already exisits", 400)

        # Query database for username
        rows = db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    return render_template("register.html")


@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    """Account Update"""

    user_id = session["user_id"]
    if request.method == "POST":
        cash = float(request.form.get("cash"))

        print("Cash: ", cash)
        if not cash or cash <= 0:
            return apology("Minimum Cash Deposit is 1$", 400)

        # Check cash in users account
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Ensure username exists and password is correct
        if len(rows) != 1:
            return apology("User Not Found", 400)

        # Deposit Cash
        cash = rows[0]["cash"] + cash
        rows = db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

    # GET Request
    # Check cash in users account
    rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

    # Ensure username exists and password is correct
    if len(rows) != 1:
        return apology("User Not Found", 400)

    return render_template("account.html", value=rows[0])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Check if value is integer
        try:
            shares = int(shares)
        except ValueError:
            return apology("Number must be integer", 400)

        print("Symbol: ", symbol)
        print("Shares: ", shares)

        value = lookup(symbol)
        print(value)

        # Check if input is not empty
        if not symbol or not shares:
            return apology("Missing Input", 400)

        # Check if shares is not negative
        if shares <= 0:
            return apology("Minimum 1 share is required", 400)

        # Check value is present
        if value == None:
            return apology(symbol + " stock symbol does not exisits", 400)

        # Check cash in users account
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Ensure username exists and password is correct
        if len(rows) != 1:
            return apology("User Not Found", 400)

        cash = rows[0]["cash"]
        cashReq = value["price"] * shares

        print("Cash: ", cash)
        print("Money: ", cashReq)

        if cash < cashReq:
            return apology("Insufficient Balance", 400)

        # Purchase the stocks
        cash -= cashReq     # Reduce cash from account
        rows = db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

        # Check if it already exisits
        rowSelect = db.execute(
            "SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", user_id, symbol)
        if len(rowSelect) == 1:
            newShares = rowSelect[0]["shares"] + shares
            newCashReq = rowSelect[0]["price"] + cashReq
            rows = db.execute("UPDATE portfolio SET shares = ?, price = ? WHERE user_id = ? AND symbol = ?",
                              newShares, newCashReq, user_id, symbol)
        else:
            rows = db.execute("INSERT INTO portfolio (symbol, shares, price, user_id) VALUES(?, ?, ?, ?)",
                              symbol, shares, cashReq, user_id)

        # Add data in history table
        rows = db.execute("INSERT INTO history (symbol, shares, price, user_id) VALUES(?, ?, ?, ?)",
                          symbol, shares, cashReq, user_id)

        return redirect("/")

    return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Check if value is integer
        try:
            shares = int(shares)
        except ValueError:
            return apology("Number must be integer", 400)

        print("Symbol: ", symbol)
        print("Shares: ", shares)

        # Check if input is not empty
        if not symbol or not shares or symbol == "-1":
            return apology("Missing Input", 400)

        # Check if shares is not negative
        if shares <= 0:
            return apology("Minimum 1 share is required", 400)

        value = lookup(symbol)
        print(value)

        # Check value is present
        if value == None:
            return apology(symbol + " stock symbol does not exisits", 400)

        # Check cash in users account
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Ensure username exists and password is correct
        if len(rows) != 1:
            return apology("User Not Found", 400)

        cash = rows[0]["cash"]
        cashReq = value["price"] * shares

        print("Cash: ", cash)
        print("Money: ", cashReq)

        # Check if it already exisits
        rowSelect = db.execute(
            "SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", user_id, symbol)

        if shares > rowSelect[0]["shares"]:
            return apology("Insufficient Shares", 400)

        # Sell the stocks
        cash += cashReq     # Increase cash from account
        rows = db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", cash, user_id)

        if len(rowSelect) == 1:
            newShares = rowSelect[0]["shares"] - shares
            newCashReq = rowSelect[0]["price"] - cashReq
            rows = db.execute("UPDATE portfolio SET shares = ?, price = ? WHERE user_id = ? AND symbol = ?",
                              newShares, newCashReq, user_id, symbol)
        else:
            rows = db.execute("INSERT INTO portfolio (symbol, shares, price, user_id) VALUES(?, ?, ?, ?)",
                              symbol, shares, cashReq, user_id)

        # Add data in history table
        rows = db.execute("INSERT INTO history (symbol, shares, price, user_id) VALUES(?, ?, ?, ?)",
                          symbol, 0-shares, cashReq, user_id)

        return redirect("/")

    # GET Request
    rows = db.execute("SELECT * FROM portfolio WHERE user_id = ?", user_id)
    return render_template("sell.html", len=len(rows), value=rows)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    rows = db.execute("SELECT * FROM history WHERE user_id = ?", user_id)
    return render_template("history.html", len=len(rows), value=rows)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        print("Symbol: ", symbol)
        value = lookup(symbol)
        if value == None:
            return apology(symbol + " stock symbol does not exisits", 400)
        return render_template("quoted.html", value=value)

    return render_template("quote.html")
