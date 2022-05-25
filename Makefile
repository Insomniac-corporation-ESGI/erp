CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Werror
SRC = src
BUILD = build

all: $(BUILD)/list_pokemon.o $(BUILD)/main.o
	$(CC) $(CFLAGS) -o main $(BUILD)/main.o $(BUILD)/list_pokemon.o

$(BUILD)/list_pokemon.o: $(SRC)/list_pokemon.h $(SRC)/list_pokemon.c
	$(CC) $(CFLAGS) -o $(BUILD)/list_pokemon.o -c $(SRC)/list_pokemon.c

$(BUILD)/main.o: $(SRC)/main.c $(BUILD)/list_pokemon.o
	$(CC) $(CFLAGS) -o $(BUILD)/main.o -c $(SRC)/main.c

clean:
	rm $(BUILD)/* main