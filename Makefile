CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Werror

main.o: main.c
	$(CC) $(CFLAGS) -o main.o main.c
