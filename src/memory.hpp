#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>
#include <stdint.h>

class memory{
private:
  uint32_t ADDR_INSTR[0x1000000];
  uint32_t ADDR_DATA[0x4000000];

public:
  void setMemory(std::string name_bin);
  uint32_t* readInstruction(uint32_t PC);

  //uint32_t* data();
  //int32_t* registers();

};

#endif
