# Makefile for Logger unit tests.
objects  = test.o
objects += test2.o
objects += unittest.o

headers  = Stats_c.h
headers += unittest.h

options = -std=c++20

CC = g++
EXE = test

$(EXE):	$(objects)	$(headers)
	$(CC) $(options) -o $(EXE) $(objects)

%.o:	%.cpp	$(headers)
	$(CC) $(options) -c -o $@ $<

format:
	tfc -s -u -r Stats_c.h
	tfc -s -u -r test.cpp
	tfc -s -u -r test2.cpp
	tfc -s -u -r unittest.cpp
	tfc -s -u -r unittest.h

clean:
	rm -f *.exe *.o
