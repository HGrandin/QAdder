CC=g++
CFLAGS=-I.
CXXFLAGS  = $(CFLAGS) -std=c++11

all: full_adder.o complete_adder.o test_adder.o
	$(CC) -o adder test_adder.o full_adder.o complete_adder.o $(CXXFLAGS)


.PHONY: clean

clean: 
	-rm *.o