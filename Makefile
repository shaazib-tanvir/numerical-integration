OPTIMIZED=-O3
DEBUG_MODE=

all: debug/numerical-integration
release: release/numerical-integration

debug/numerical-integration: debug/main.o
	clang++ -Wall -Werror --std=c++11 -pedantic -g debug/main.o -o debug/numerical-integration

debug/main.o: src/main.cpp include/integrator.hpp
	clang++ -Wall -Werror --std=c++11 -pedantic -I include/ -c -g -o debug/main.o src/main.cpp

debug/integrator.o: src/integrator.cpp
	clang++ -Wall -Werror --std=c++11 -pedantic -I include/ -c -g -o debug/integrator.o src/integrator.cpp

release/numerical-integration: release/main.o
	clang++ -Wall -Werror --std=c++11 -pedantic $(OPTIMIZED) $(DEBUG_MODE) release/main.o -o release/numerical-integration

release/main.o: src/main.cpp include/integrator.hpp
	clang++ -Wall -Werror --std=c++11 -pedantic -I include/ -c $(OPTIMIZED) $(DEBUG_MODE) -o release/main.o src/main.cpp

release/integrator.o: src/integrator.cpp
	clang++ -Wall -Werror --std=c++11 -pedantic -I include/ -c $(OPTIMIZED) -o release/integrator.o src/integrator.cpp

clean:
	rm -f debug/* release/*
