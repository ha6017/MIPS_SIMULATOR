#ifndef R_INSTRUCTION_HPP
#define R_INSTRUCTION_HPP

#include <cmath>
#include <stdint.h>
#include "memory.hpp"

class R_Instruction{
private:
  uint32_t Fn_code;
  uint32_t shamt;
  uint32_t rd;
  uint32_t rt;
  uint32_t rs;
  uint32_t hi;
  uint32_t lo;
public:
  R_Instruction();
  void runInstruction();
  void ADD();
  void ADDU();
  void AND();

  void JR();

  friend void RIJ_INSTRUCTION();
};

#endif
