# Makefile for Awale Game

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = awale
SRC = awale.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
