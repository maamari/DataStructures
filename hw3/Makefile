# BIN_DIR = bin
CXX = g++
CPPFLAGS = -g -Wall
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: stringparser lliststr.o stackstr.o 

stringparser: stringparser.cpp lliststr.o stackstr.o
	$(CXX) $(CPPFLAGS) stringparser.cpp stackstr.cpp lliststr.cpp -o stringparser

lliststr.o: lliststr.cpp lliststr.h 
	$(CXX) $(CPPFLAGS) -c lliststr.cpp -o lliststr.o

stackstr.o: stackstr.cpp stackstr.h 
	$(CXX) $(CPPFLAGS) -c stackstr.cpp stackstr.h -o stackstr.o

.PHONY: clean
clean: 
	rm -rf stackstr.o lliststr.o stringparser