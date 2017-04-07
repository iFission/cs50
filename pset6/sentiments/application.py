from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "").lstrip("@")
    if not screen_name:
        return redirect(url_for("index"))

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)

    # analyze tweets
    green, red, yellow = 0, 0, 0
    for i in range(len(tweets)):
        # print(i)
        score = analyzer.analyze(tweets[i]['text'].encode('utf-8').lower())
        if score > 0.0:
            # print(colored(":)", "green"))
            green = green + 1
        elif score < 0.0:
            # print(colored(":(", "red"))
            red = red + 1
        else:
            # print(colored(":|", "yellow"))
            yellow = yellow + 1

    # positive, negative, neutral = 0.0, 0.0, 100.0 # initialize as float
    positive, negative, neutral = float(green/len(tweets))*100, float(red/len(tweets))*100, float(yellow/len(tweets))*100 

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)
