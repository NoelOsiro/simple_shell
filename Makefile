CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=gnu89
LDFLAGS =

simple_shell: main.o shell.o
    $(CC) $(CFLAGS) -o simple_shell main.o shell.o $(LDFLAGS)

main.o: main.c shell.h
    $(CC) $(CFLAGS) -c main.c

shell.o: shell.c shell.h
    $(CC) $(CFLAGS) -c shell.c

test_shell.o: tests/test_shell.c shell.h
    $(CC) $(CFLAGS) -c tests/test_shell.c

test_shell: main.o test_shell.o
    $(CC) $(CFLAGS) -o test_shell main.o test_shell.o $(LDFLAGS)

clean:
    rm -f simple_shell main.o shell.o test_shell.o
