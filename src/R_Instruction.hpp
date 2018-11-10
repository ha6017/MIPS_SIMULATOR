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

  uint32_t* ADDR_DATA;
  int32_t* REG_VECTOR;
public:
  R_Instruction(uint32_t instruction);
  void runInstruction(register_map &regs);
  void ADD(register_map &regs);
  void ADDU(register_map &regs);
  void AND(register_map &regs);
  void JR(register_map &regs);

  //friend void RIJ_INSTRUCTION();
  friend uint32_t* instructions();
  friend uint32_t* data();
  friend int32_t* registers();
};

#endif
