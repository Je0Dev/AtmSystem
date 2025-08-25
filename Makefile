CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g
LDFLAGS=
SOURCES=main.c system.c ui.c customer.c account.c utils.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=atm

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c atm.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean