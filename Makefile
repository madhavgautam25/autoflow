CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

LIB = libautoflow.a

SRC = \
	src/process.c \
	src/queue.c \
	src/metrics.c \
	src/workload.c \
	src/scheduler.c

OBJ = \
	process.o \
	queue.o \
	metrics.o \
	workload.o \
	scheduler.o

all: $(LIB)

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

process.o:
	$(CC) $(CFLAGS) -c src/process.c

queue.o:
	$(CC) $(CFLAGS) -c src/queue.c

metrics.o:
	$(CC) $(CFLAGS) -c src/metrics.c

workload.o:
	$(CC) $(CFLAGS) -c src/workload.c

scheduler.o:
	$(CC) $(CFLAGS) -c src/scheduler.c

clean:
	rm -f $(OBJ) $(LIB)

.PHONY: all clean