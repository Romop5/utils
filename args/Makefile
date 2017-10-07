CXXFLAGS=-std=c++11
main: args.o
	g++ main.cpp args.o -o main -g
args.o: args.cpp args.h
	g++ $(CXXFLAGS) -o args.o -c args.cpp

