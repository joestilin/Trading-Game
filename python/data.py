#!/usr/bin/env python3

# python script to get financial data and store it in a .csv file

import yfinance as yf
import pandas as pd
import datetime
import sys

def get_financial_data(ticker, days_back, time_interval):
    today = datetime.datetime.today()
    start_date = today + datetime.timedelta(days = -1*days_back)
    data = yf.download(ticker, start=start_date, end=today, interval=time_interval)

    return data

symbol = sys.argv[1]
interval = sys.argv[2]
data = get_financial_data(symbol, 730, interval)
pd.DataFrame(data).to_csv("data.csv")