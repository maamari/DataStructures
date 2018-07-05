CPPFLAGS = -g -Wall -std=c++11 
VALGRIND = valgrind --tool=memcheck --leak-check=yes

all: hypercube 

valgrind: hypercube
	$(VALGRIND) ./hypercube 00100 hw7-check/cube/permitted1.txt
	$(VALGRIND) ./hypercube 00100 hw7-check/cube/permitted2.txt
	$(VALGRIND) ./hypercube 010 hw7-check/cube/permitted3.txt
	$(VALGRIND) ./hypercube 0001 hw7-check/cube/permitted4.txt

test: hypercube
	./hypercube 00100 hw7-check/cube/permitted1.txt
	./hypercube 00100 hw7-check/cube/permitted2.txt
	./hypercube 010 hw7-check/cube/permitted3.txt
	./hypercube 0001 hw7-check/cube/permitted4.txt

hypercube: hypercube.cpp
	g++ $(CPPFLAGS) $^ -o $@
