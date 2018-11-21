# Example usage:
# If you have testbench/my_test.c, you can execute the following to create a MIPS binary
# make testbench/my_test.mips.bin

# For simulator
CC = g++
CPPFLAGS = -W -Wall

# For MIPS binaries. Turn on all warnings, enable all optimisations and link everything statically
MIPS_CC = mips-linux-gnu-gcc
MIPS_OBJCOPY = mips-linux-gnu-objcopy
MIPS_OBJDUMP = mips-linux-gnu-objdump
MIPS_CPPFLAGS = -W -Wall -O3 -fno-builtin -march=mips1 -mfp32
MIPS_LDFLAGS = -nostdlib -Wl,-melf32btsmip -march=mips1 -nostartfiles -mno-check-zero-division -Wl,--gpsize=0 -static -Wl,-Bstatic -Wl,--build-id=none

# Compile C file (.c) into MIPS object file (.o)
%.mips.o: %.c
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@

# Assemble MIPS assembly file (.s) into MIPS object file (.o)
%.mips.o: %.s
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@

# Link MIPS object file (.o), producing .elf, using memory locations specified in spec
%.mips.elf: %.mips.o
	$(MIPS_CC) $(MIPS_CPPFLAGS) $(MIPS_LDFLAGS) -T linker.ld $< -o $@

# Extract binary instructions only from linked object file (.elf)
%.mips.bin: %.mips.elf
	$(MIPS_OBJCOPY) -O binary --only-section=.text $< $@

# Disassemble linked object file (.elf), pulling out instructions as MIPS assembly file (.s)
%.mips.s : %.mips.elf
	$(MIPS_OBJDUMP) -j .text -D $< > $@

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
	$(CC) $(CPPFLAGS) compiler.o memory.o register_map.o main.o -o bin/mips_simulator

# Dummy for build simulator to conform to spec
simulator: bin/mips_simulator

# Dummy for build testbench to conform to spec. Could do nothing
testbench:
