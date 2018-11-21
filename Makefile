# Example usage:
# If you have testbench/my_test.c, you can execute the following to create a MIPS binary
# make testbench/my_test.mips.bin

# For simulator
CC = g++
CPPFLAGS = -W -Wall




compiler.o: src/compiler.cpp src/compiler.hpp
	$(CC) -std=c++11 -c src/compiler.cpp

memory.o: src/memory.cpp src/memory.hpp
	$(CC) -std=c++11 -c src/memory.cpp

register_map.o: src/register_map.cpp src/register_map.hpp
	$(CC) -std=c++11 -c src/register_map.cpp

main.o: src/main.cpp
	$(CC) -std=c++11 -c src/main.cpp

# Build simulator
bin/mips_simulator: compiler.o memory.o register_map.o main.o
	mkdir -p bin
	$(CC) $(CPPFLAGS) -std=c++11 compiler.o memory.o register_map.o main.o -o bin/mips_simulator

# Dummy for build simulator to conform to spec
simulator: bin/mips_simulator

clean:
	rm *.o bin/mips_simulator -f 
# Dummy for build testbench to conform to spec. Could do nothing
testbench:
