CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Werror -std=c99 -g -O0
SRC = src
BUILD = build

all: $(BUILD)/list_pokemon.o $(BUILD)/sqlite_functions.o  $(BUILD)/main.o $(BUILD)/menu.o
	$(CC) $(CFLAGS) -o main $(BUILD)/main.o $(BUILD)/sqlite_functions.o $(BUILD)/menu.o $(BUILD)/list_pokemon.o -lsqlite3

$(BUILD)/list_pokemon.o: $(SRC)/list_pokemon.h $(SRC)/list_pokemon.c
	$(CC) $(CFLAGS) -o $(BUILD)/list_pokemon.o -c $(SRC)/list_pokemon.c

$(BUILD)/main.o: $(SRC)/main.c $(BUILD)/list_pokemon.o
	$(CC) $(CFLAGS) -o $(BUILD)/main.o -c $(SRC)/main.c

$(BUILD)/sqlite_functions.o: $(SRC)/sqlite_functions.h $(SRC)/sqlite_functions.c $(BUILD)/list_pokemon.o
	$(CC) $(CFLAGS) -o $(BUILD)/sqlite_functions.o -c $(SRC)/sqlite_functions.c
	
$(BUILD)/menu.o: $(SRC)/menu.h $(SRC)/menu.c 
	$(CC) $(CFLAGS) -o $(BUILD)/menu.o -c $(SRC)/menu.c

clean:
	rm $(BUILD)/* main

run: all
	./main
