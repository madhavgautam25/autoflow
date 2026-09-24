CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

SRC = src/process.c \
      src/scheduler.c

TARGET = autoflow

EXAMPLE = examples/basic.c

all:
	$(CC) $(CFLAGS) $(SRC) $(EXAMPLE) -o $(TARGET)

clean:
	rm -f $(TARGET)