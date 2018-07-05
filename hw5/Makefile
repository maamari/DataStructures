CXX = g++
CPPFLAGS = -std=c++11 -g -Wall

all: thanksgiving functor

thanksgiving: Thanksgiving.cpp LengthMismatch.cpp LengthMismatch.h qsort.h functor.o
	$(CXX) $(CPPFLAGS) Thanksgiving.cpp LengthMismatch.cpp LengthMismatch.h qsort.h functor.cpp -o thanksgiving

functor: qsort.h functor.o
	$(CXX) $(CPPFLAGS) qsort.h functor.cpp -o functor

functor.o: functor.cpp functor.h 
	$(CXX) $(CPPFLAGS) -c functor.cpp functor.h -o functor.o

.PHONY: clean
clean: 
	rm -rf thanksgiving functor.o LengthMismatch.o functor a.out functor.h.gch LengthMismatch.h.gch qsort.h.gch qsort.o sort.o sort
