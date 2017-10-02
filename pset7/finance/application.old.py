from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
# @login_required
def index():
    """Show user's stats"""

    user_id = 11
    # user_id = session["user_id"]
    rows = db.execute("SELECT * FROM share WHERE user_id = :user_id", user_id=user_id)
    print(rows)

    value_total = 0
    # query symbol's price
    for row in rows:
        row['price'] = lookup(row['symbol'])['price']
        print(row['price'])
        value_symbol = row['share'] * float(row['price'])
        # row['value'] = 200
        row['value'] = value_symbol
        value_total += value_symbol

    # add cash and total
    cash = {}
    cash['symbol'] = 'CASH'
    value_cash = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=user_id)[0]['cash']
    cash['value'] = value_cash
    rows.append(cash)
    value_total += value_cash

    total = {}
    total['symbol'] = 'TOTAL'
    total['value'] = value_total
    rows.append(total)
    print(rows)

    return render_template("index.html", share_rows = rows)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "POST":

        user_id = session["user_id"]
        symbol = str(request.form.get("symbol")).upper()
        share = int(request.form.get("share"))

        # ensure symbol was submitted
        if not symbol:
            return apology("must provide symbol")

        # ensure symbol is valid
        if lookup(symbol) == None:
            return apology("must provide valid symbol")

        # ensure share was submitted
        if not share:
            return apology("must provide share")

        # ensure share was positive
        if share < 1:
            return apology("must provide positive")

        # retrieve active session based on session user_id
        rows = db.execute("SELECT * FROM users WHERE id = :user_id", user_id=user_id)

        # calculate balance
        price = lookup(symbol)['price']
        print(price)
        # price = 20
        balance = rows[0]['cash'] - price * share
        # print(balance)

        # ensure user has enough cash
        if balance < 0:
            return apology('not enough cash')

        # update user's balance into TABLE users
        db.execute("UPDATE users SET 'cash' = :cash WHERE id = :user_id", cash = balance, user_id=user_id)

        # log transaction into TABLE history
        db.execute("INSERT INTO history ('user_id', 'symbol', 'share', 'price', 'time') VALUES (:user_id, :symbol, :share, :price, datetime('now'))", user_id=user_id, symbol=symbol, share=share, price=usd(price))

        # log share into TABLE share
        rows = db.execute("SELECT * FROM share WHERE user_id = :user_id", user_id = user_id)
        if rows: # if rows for user exist
            symbol_exist = False # record if symbol is present in rows
            for row in rows: # check if the symbol is present
                if row["symbol"] == symbol:
                    symbol_exist = True # update symbol_exist to True
                    share += row["share"]
                    db.execute("UPDATE share SET 'share' = :share WHERE user_id = :user_id and symbol = :symbol", user_id=user_id, symbol=symbol, share=share)
            if not symbol_exist: # executes when symbol_exist is False
                db.execute("INSERT INTO share ('user_id', 'symbol', 'share') VALUES (:user_id, :symbol, :share)", user_id=user_id, symbol=symbol, share=share)
        else: # if rows for user does not exist
            db.execute("INSERT INTO share ('user_id', 'symbol', 'share') VALUES (:user_id, :symbol, :share)", user_id=user_id, symbol=symbol, share=share)

        return render_template("buy.html")
    return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""

    user_id = session["user_id"]
    rows = db.execute("SELECT * FROM history WHERE user_id = :user_id", user_id=user_id)
    for row in rows:
        row['value'] = usd(row['share'] * float(row['price'][1:]))
    return render_template("history.html", history_rows = rows)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote(): # can be accessed via url_for(quote), returns the html inside function, quote.html must contain url_for(quote)

    # template for return of quote
    def symbol_parse(string):
        name = str(string['name'])
        price = str(string['price'])
        symbol = str(string['symbol'])
        return "A share of " + name + " " + "(" + symbol + ")" + " " + "costs" + " " + "$" + price + "."

    """Get stock quote."""
    if request.method == "POST":

        # ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol")

        # ensure symbol is valid
        if lookup(request.form.get("symbol")) == None:
            return apology("must provide valid symbol")

        # print(symbol_parse(lookup(request.form.get("symbol"))))
        return render_template("quoted.html", main=symbol_parse(lookup(request.form.get("symbol"))))
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure username was unique
        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                            username=request.form.get("username"))
        if len(rows) == 1:
            return apology("must provide different username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # ensure password was the same
        elif not (request.form.get("password") == request.form.get("password2")):
            return apology("must provide same password")

        # create account for user
        # username = request.form.get("username")
        # hash = pwd_context.encrypt(request.form.get("password"))
        # db.execute("INSERT INTO 'users' ('username', 'hash') VALUES (:username, :hash)",username = username, hash = hash)
        db.execute("INSERT INTO 'users' ('username', 'hash') VALUES (:username, :hash)",
                    username = request.form.get("username"),
                    hash = pwd_context.encrypt(request.form.get("password")))

        # redirect user to home page
        # return redirect(url_for("index"))

        # log in user directly
        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))


    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/unregister")
def unregister(): # can be accessed via url_for(unregister)
    db.execute("DELETE FROM users WHERE id = :user_id", user_id=session["user_id"])
    return redirect(url_for("login"))

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    return apology("TODO")
