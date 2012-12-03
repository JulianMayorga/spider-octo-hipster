CC = gcc
CFLAGS = -Wall -pthread -g -ggdb
NOMBRE = queue-threads
TARGETS = queue-threads

all: $(TARGETS)

queue-threads: main.o thread.o
	$(CC) $(CFLAGS) $(STANDARD) -o $@ $^ $(LDLIBS)

clean:
	rm -fv $(TARGETS) *.o *~

