CC = gcc
CFLAGS = -Wall -pthread -g -ggdb
NOMBRE = spider
TARGETS = spider test_file test_net

all: $(TARGETS)

spider: main.o thpool.o net.o file.o url_frontier.o monitor.o
	$(CC) $(CFLAGS) $(STANDARD) -o $@ $^ $(LDLIBS)

test_file: test_file.o file.o
	$(CC) $(CFLAGS) $(STANDARD) -o $@ $^ $(LDLIBS)

test_net: test_net.o net.o
	$(CC) $(CFLAGS) $(STANDARD) -o $@ $^ $(LDLIBS)

clean:
	rm -fvrf $(TARGETS) *.o *~ sites/*

