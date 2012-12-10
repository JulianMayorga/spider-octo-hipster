CC = gcc
CFLAGS = -Wall -pthread -g -ggdb
NOMBRE = spider
TARGETS = spider

all: $(TARGETS)

spider: main.o thpool.o net.o file.o url_frontier.o
	$(CC) $(CFLAGS) $(STANDARD) -o $@ $^ $(LDLIBS)

clean:
	rm -fvrf $(TARGETS) *.o *~ sites/*

