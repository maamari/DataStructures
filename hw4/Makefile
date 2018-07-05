CXX = g++
CPPFLAGS = -g -Wall

all: webpage.o search

search: search.cpp webpage.o 
	$(CXX) $(CPPFLAGS) $^ -o $@

webpage.o: webpage.cpp webpage.h 
	$(CXX) $(CPPFLAGS) -c webpage.cpp -o $@