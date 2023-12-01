CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -g
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	INCLUDE_DIRS = -I/usr/local/include/ 
	LDFLAGS = -L/usr/local/lib/
    LIBS = -lcheck -lm
else
	INCLUDE_DIRS = -I/usr/include
    LDFLAGS = -L/usr/lib/x86_64-linux-gnu/
    LIBS = -lcheck -lsubunit -lm
endif
TARGET = tests
SRC_DIR = ../src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,%.o,$(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDE_DIRS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f  $(TARGET) $(OBJ_FILES)

run: $(TARGET)
	./$(TARGET)

check-mem: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

.PHONY: all clean run
