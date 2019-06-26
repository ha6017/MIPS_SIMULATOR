# MIPS_SIMULATOR
This project was created by Hardik Aggarwal and Carla Arus Gomez

To compile the project from source provided use the make file provided and run "make bin/mips_simulator"

The Project is a creation of a MIPS CPU Simulator, which accurately executes MIPS-1 big-endian binaries. The project also includes a testbench, which allows testing of the simulator.

The simulator works on Binaries provided by the user. The testbench takes a single command-line parameter, which is the path to the simulator and outputs a CSV file, containing :

TestId, Instruction, Status, [Message]

The memory map of the simulated process is as follows:

Offset | Length | Name | R | W | X | -----------|-------------|------------|---|---|---|-------------------------------------------------------------------- 0x00000000 | 0x4 | ADDR_NULL | | | Y | Jumping to this address means the Binary has finished execution. 0x00000004 | 0xFFFFFFC | .... | | | | 0x10000000 | 0x1000000 | ADDR_INSTR | Y | | Y | Executable memory. The Binary should be loaded here. 0x11000000 | 0xF000000 | .... | | | | 0x20000000 | 0x4000000 | ADDR_DATA | Y | Y | | Read-write data area. Should be zero-initialised. 0x24000000 | 0xC000000 | .... | | | | 0x30000000 | 0x4 | ADDR_GETC | Y | | | Location of memory mapped input. Read-only. 0x30000004 | 0x4 | ADDR_PUTC | | Y | | Location of memory mapped output. Write-only. 0x30000008 | 0xCFFFFFF8 | .... | | | | -----------|-------------|------------|---|---|---|--------------------------------------------------------------------

When a simulated program reads from address ADDR_GETC, the simulator should

Block until a character is available (e.g. if a key needs to be pressed) Return the 8-bit extended to 32-bits as the result of the memory read. If there are no more characters (EOF), the memory read should return -1.

When a simulated program writes to address ADDR_PUTC, the simulator should write the character to stdout. If the write fails, the appropriate Error should be signalled.
