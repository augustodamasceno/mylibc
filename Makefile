SHELL = /bin/sh

srcdir = .

.SUFFIXES:
.SUFFIXES: .c .o

CFLAGS = -g -Wall -pedantic

LIBS = -lm

objects = personalgen.o personalprint.o personalmath.o \
examples.o

all : $(objects)
	cc -o examples $(objects) $(LIBS)
examples.o: examples.c personal.h
	cc -c examples.c
personalgen.o: personalgen.c personalgen.h 
	cc -c personalgen.c $(CFLAGS)
personalprint.o: personalprint.c personalprint.h 
	cc -c personalprint.c $(CFLAGS)
personalmath.o: personalmath.c personalmath.h 
	cc -c personalmath.c $(CFLAGS)
clean :
	rm $(objects)

