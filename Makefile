CC = gcc
CFLAGS = -Wall -pthread -g -ggdb
NOMBRE = spider
TARGETS = spider test_file

all: $(TARGETS)

spider: main.o thpool.o net.o file.o
	$(CC) $(CFLAGS) $(STANDARD) -o $@ $^ $(LDLIBS)

test_file: test_file.o file.o
	$(CC) $(CFLAGS) $(STANDARD) -o $@ $^ $(LDLIBS)

clean:
	rm -fvrf $(TARGETS) *.o *~ sites/*

