CC = gcc
CFLAGS = -Wall -pthread -g -ggdb
NOMBRE = spider
TARGETS = spider

all: $(TARGETS)

spider: main.o thpool.o net.o
	$(CC) $(CFLAGS) $(STANDARD) -o $@ $^ $(LDLIBS)

clean:
	rm -fv $(TARGETS) *.o *~

