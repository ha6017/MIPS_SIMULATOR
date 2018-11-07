#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>
#include <stdint.h>

class memory{
protected:
  uint32_t ADDR_INSTR[0x1000000];
  uint32_t ADDR_DATA[0x4000000];
  int32_t REG_VECTOR[32];

public:
  memory(std::string name_bin);
  uint32_t getInstruction(uint32_t PCindex);
  uint32_t getData(uint32_t PCindex);
  int32_t getRegister(uint32_t PCindex);

};

#endif
