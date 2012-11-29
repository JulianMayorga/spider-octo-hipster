CC = gcc
CFLAGS = -Wall -pthread -g -ggdb
NOMBRE = araña
TARGETS = araña

all: $(TARGETS)

araña: main.o thread.o
	$(CC) $(CFLAGS) $(STANDARD) -o $@ $^ $(LDLIBS)

clean:
	rm -fv $(TARGETS) *.o *~

