import yfinance as yf 
import argparse
import pandas as pd
import os
import sys

def fetch_bitcoin_data(start_date, end_date, ticker):
    print(f"Downloading data for {ticker} from {start_date} to {end_date}...")
    sys.stdout.flush()
    bitcoin_data = yf.download(ticker, start=start_date, end=end_date)
    print("Download finished.")
    sys.stdout.flush()
    return bitcoin_data

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Fetch historical data using yfinance")
    parser.add_argument("--ticker", type=str, required=True, help="Ticker symbol (e.g., BTC-USD)")
    parser.add_argument("--start", type=str, default="2012-01-01", help="Start date (YYYY-MM-DD)")
    parser.add_argument("--end", type=str, default="2025-01-01", help="End date (YYYY-MM-DD)")
    parser.add_argument("--output", type=str, required=True, help="Path to save CSV (e.g., data/data.csv)")

    args = parser.parse_args()

    print(f"Arguments parsed: {args}")
    sys.stdout.flush()

    data = fetch_bitcoin_data(args.start, args.end, args.ticker)
    data.index.name = None

    # Make sure the directory exists
    os.makedirs(os.path.dirname(args.output), exist_ok=True)

    data.to_csv(args.output)
    print(f"Data saved to {args.output}")
    sys.stdout.flush()
