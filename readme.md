# BacktestEngine

BacktestEngine is a C++ project designed for backtesting trading strategies using historical data. It provides a modular framework for simulating trades, analyzing performance, and optimizing strategy parameters.

## Features

- **Strategy Simulation:** Supports multiple trading strategies with modularity to add new ones easily.
- **Data Handling:** Reads historical data from CSV files for backtesting. Historical data is being recieved by a Python script.
- **Reporting:** Generates detailed performance reports for each strategy and parameter set.
- **Parameter Optimization:** Tests various parameter combinations to find the best-performing strategy.
- **Extensible Architecture:** Easily add new strategies or calculators via the `include/`directory.

## Project Structure

- `main/` — Main application source files.
- `include/` — Header files for strategies, data handling, reporting, and utility classes.
- `data/` — Contains historical data files.
- `reports/` — Output directory for generated strategy performance reports.
- `scripts/` — Python scripts for data preprocessing or analysis.
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

- GCC or compatible C++23 compiler
- Make

### Build

To build the project, run:

```bash
make
```

Or use the provided VS Code build tasks for different GCC versions.

### Run

After building, execute the main binary:

```bash
./main
```

## Usage

1. Place your historical data in the `data/` directory (e.g., `data.csv`).
2. Configure strategies and parameters in the source code or via command-line options (if supported).
3. Run the engine to generate reports in the `reports/` directory.

## Adding Strategies

To add a new strategy:

1. Create a new header and implementation file in `include/`.
2. Implement the required interfaces (see existing strategies for examples).
3. Register the strategy in the main application.

## License

This project is licensed under the terms of the LICENSE file provided in the repository.
