# BacktestEngine

BacktestEngine is a C++ project designed for backtesting trading strategies using historical data. It provides a modular framework for simulating trades, analyzing performance, and optimizing strategy parameters.

## Features

- **Strategy Simulation:** Supports multiple trading strategies with modularity to add new ones easily.
- **Data Handling:** Reads historical data from CSV files for backtesting. Historical data is being recieved by a Python script.
- **Reporting:** Generates detailed performance reports for best strategies and parameter sets (5 at most).
- **Parameter Optimization:** Tests various parameter combinations to find the best-performing strategy.

## Project Structure

- `main/` — Main application source files.
- `include/` — Header files for strategies, data handling, reporting, and utility classes.
- `data/` — Contains downloaded historical data file.
- `reports/` — Output directory for generated strategy performance reports.
- `scripts/` — Python script for data preprocessing.
- `Makefile` — Build instructions for the project.
- `LICENSE` — Project license information.

## Getting Started

## Makefile Parameters

The Makefile supports several parameters to customize data preprocessing and building:

- `TICKER` — Symbol for the asset to backtest (default: `BTC-USD`).
- `START_DATE` — Start date for historical data (default: `2012-01-01`).
- `END_DATE` — End date for historical data (default: `2025-01-01`).

These parameters are used by the Python preprocessing script to fetch and prepare the data before building and running the engine.

### Example Usage

To build the project with custom parameters:

```bash
make TICKER=ETH-USD START_DATE=2018-01-01 END_DATE=2024-01-01
```

This will run the Python script with the specified ticker and date range, then build the C++ project.

### Prerequisites
- Ubuntu 24.04.2
- GCC or/ compatible C++23 compiler
- Make
- Python 3.12
- yfinance 0.2.65

### Build

To build the project, run:

```bash
make
```
Or run:
```bash
make TICKER=[tickername] START_DATE=[yyyy-mm-dd] END_DATE=[yyyy-mm-dd]
```

### Run

After building, execute the main binary:

```bash
./main
```

## Usage

1. Choose the ticker, start date and end date.
2. Run the engine to generate reports in the `reports/` directory.


## License

This project is licensed under the terms of the LICENSE file provided in the repository.

## Future Plans

- Add discreteness for asset classes such as stocks
- Implement more advanced trading strategies and risk management modules
- Implement more metrics to measure performance and risk (CAGR, Alpha, Benchmark-relative Return, Standart Deviation, Maximum Drawdown, Sharpe Ratio)
- Add support for shorting equites (selling equity on loan)
- Add support for brokerage commissions
- Add Support for leveraged trades and interest rates
- Enhance reporting with more metrics and interactive formats
- Improve documentation and add usage examples
- Optimize repedately used classes
- Add new strategies
- Implement a better way to choose best parameter sets
