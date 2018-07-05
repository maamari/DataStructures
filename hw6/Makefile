CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: search crawler

search: engine.cpp webpage.o    
	$(CXX) $(CPPFLAGS) $^ -o $@
	
crawler: crawler.cpp 
	$(CXX) $(CPPFLAGS) crawler.cpp -o crawler

webpage.o: webpage.cpp webpage.h
	$(CXX) $(CPPFLAGS) -c webpage.cpp -o $@

.PHONY: clean
clean:
	rm webpage.o crawler search
