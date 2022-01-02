CC = gcc
CFLAGS = -std=c99 -Wall -g
BIN = tetris
OBJECT_FILES = main.o tetromino.o game_control.o

all: compile clean

compile: $(OBJECT_FILES)
	$(CC) -o $(BIN) $(OBJECT_FILES) -l pthread

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o