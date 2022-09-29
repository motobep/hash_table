SRC = ./src/
BIN = ./bin/
TESTS = ./tests/

TARGET = main
TARGET_TEST = test

CC = g++
FLAGS = -g -Wall


all: build

do: build run

run:
	$(BIN)$(TARGET)

build:
	$(CC) $(SRC)*.cpp $(FLAGS) -o $(BIN)$(TARGET)


test: test_build test_run

test_run:
	$(BIN)test

test_build:
	$(CC) $(TESTS)*.cpp $(SRC)Hash.cpp -lgtest $(FLAGS) -o $(BIN)$(TARGET_TEST)

