#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "R_Instruction.hpp"
#include "I_Instruction.hpp"
#include "J_Instruction.hpp"
#include "compiler.hpp"

#include <vector>
#include <stdint.h>

class memory{
private:
  std::vector<uint32_t> ADDR_INSTR();
  std::vector<uint32_t> ADDR_DATA();
  std::vector<int32_t> REG_VECTOR();
  uint32_t PC;

public:
  memory();
  memory(std::string name_bin);
  friend class R_Instruction;
  friend class I_Instruction;
  friend class J_Instruction;
  friend class compiler;

};

#endif
