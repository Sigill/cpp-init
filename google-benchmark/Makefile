CXXFLAGS ?= -Wall -O2

clean:
	rm -f main main.cpp.o functions.cpp.o

all: main

.PHONY: all clean
.DEFAULT_GOAL := all

functions.cpp.o: functions.cpp functions.h
	g++ $(CXXFLAGS) -o $@ -c $<

main.cpp.o: main.cpp functions.h
	g++ $(CXXFLAGS) -o $@ -c $<

main: main.cpp.o functions.cpp.o
	g++ -o $@ -lbenchmark_main -lbenchmark -lpthread $^
