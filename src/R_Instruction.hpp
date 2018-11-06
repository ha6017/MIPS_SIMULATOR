#ifndef R_INSTRUCTION_HPP
#define R_INSTRUCTION_HPP

#include <cmath>
#include <stdint.h>

class R_Instruction{
private:
  uint32_t Fn_code;
  uint32_t shamt;
  uint32_t rd;
  uint32_t rt;
  uint32_t rs;
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
