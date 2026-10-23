CC      ?= cc
CFLAGS  ?= -std=gnu99 -Wall -Wextra -O2 -g
TARGET  := test_bitops

.PHONY: all test clean

all: $(TARGET)

$(TARGET): test_bitops.c bitops.c bitops.h
	$(CC) $(CFLAGS) -o $@ test_bitops.c bitops.c

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
