all: debug/numerical-integration

debug/numerical-integration: debug/main.o
	clang++ -Wall -Werror --std=c++11 -pedantic -g debug/main.o -o debug/numerical-integration

debug/main.o: src/main.cpp
	clang++ -Wall -Werror --std=c++11 -pedantic -I include/ -c -g -o debug/main.o src/main.cpp

clean:
	rm -f debug/* release/*
