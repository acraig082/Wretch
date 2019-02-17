CC = gcc
CFLAGS = -lncurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c\
		  $(SRCDIR)utils/*.c

all: wretch

wretch: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./wretch

clean:
	rm wretch