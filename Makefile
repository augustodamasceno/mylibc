SHELL = /bin/sh

srcdir = .

.SUFFIXES:
.SUFFIXES: .c .o

CFLAGS = -g -Wall -pedantic

LIBS = -lm

objects = personal.o examples.o

all : $(objects)
	cc -o examples $(objects) $(LIBS)
examples.o: examples.c
	cc -c examples.c
personal.o: personal.c personal.h 
	cc -c personal.c $(CFLAGS)
clean :
	rm $(objects)
