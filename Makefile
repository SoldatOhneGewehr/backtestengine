TICKER ?= BTC-USD
START_DATE ?= 2012-01-01
END_DATE ?= 2025-01-01

# Python
PYTHON = python3
PY_SCRIPT = scripts/data.py
CSVFILE = data/data.csv


# Compiler
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Iinclude

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = main

all: run_python $(TARGET)

run_python:
	@mkdir -p data
	@echo "Running Python preprocessing script..."
	$(PYTHON) $(PY_SCRIPT) --ticker $(TICKER) --start $(START_DATE) --end $(END_DATE) --output $(CSVFILE)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) $(CSVFILE)

run: $(TARGET)
	./$(TARGET) $(CSVFILE)

.PHONY: all run_python clean run
