CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

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

TARGET = libautoflow.a

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $(TARGET) $(OBJ)

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
	rm -f $(OBJ) $(TARGET)