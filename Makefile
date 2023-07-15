CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=gnu89
LDFLAGS =

simple_shell: main.o shell.o
    $(CC) $(CFLAGS) -o simple_shell main.o shell.o $(LDFLAGS)

main.o: main.c shell.h
    $(CC) $(CFLAGS) -c main.c

shell.o: shell.c shell.h
    $(CC) $(CFLAGS) -c shell.c

clean:
    rm -f simple_shell main.o shell.o
