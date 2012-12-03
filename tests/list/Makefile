CC = gcc
CFLAGS = -Wall -pthread -g -ggdb
NOMBRE = queue
TARGETS = queue

all: $(TARGETS)

queue: main.o
	$(CC) $(CFLAGS) $(STANDARD) -o $@ $^ $(LDLIBS)

clean:
	rm -fv $(TARGETS) *.o *~

