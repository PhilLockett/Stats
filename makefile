# Makefile for Logger unit tests.
objects  = test.o
objects += test2.o
objects += unittest.o

headers  = Stats_c.h
headers += unittest.h

options = -std=c++20

test:	$(objects)	$(headers)
	g++ $(options) -o test $(objects)

%.o:	%.cpp	$(headers)
	g++ $(options) -c -o $@ $<

clean:
	rm -f *.exe *.o
