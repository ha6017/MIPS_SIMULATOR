#Makefile

all: R_Instruction.o J_Instruction.o I_Instruction.o compiler.o memory.o
	g++ R_Instruction.o J_Instruction.o I_Instruction.o compiler.o memory.o -o bin/mips_simulator

R_Instruction.o: R_Instruction.hpp R_Instruction.cpp
	g++ -c R_Instruction.cpp

J_Instruction.o: J_Instruction.hpp J_Instruction.cpp
	g++ -c J_Instruction.cpp

I_Instruction.o: I_Instruction.hpp I_Instruction.cpp
	g++ -c I_Instruction.cpp

compiler.o: compiler.hpp compiler.cpp
	g++ -c compiler.cpp

memory.o: memory.hpp memory.cpp
	g++ -c memory.cpp

register_map.o: register_map.hpp register_map.cpp
	g++ -c register_map.cpp

run:
	./bin/mips_simulator

clean:
	rm *.o bin/mips_simulator
