# Makefile for Awale Game

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = server

all: $(TARGET)

$(TARGET): server.c awalee.c awale.h
	$(CC) $(CFLAGS) -o $(TARGET) server.c awalee.c

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
