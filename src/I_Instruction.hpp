#ifndef I_INSTRUCTION_HPP
#define I_INSTRUCTION_HPP

#include <stdint.h>
#include "memory.hpp"
class I_Instruction: public memory// this notation means that public of class memory
                                  //is also public of class I_Instruction. I_instryction
                                  // inherits all methods and member variables from class memory
{
  private:
    int16_t immediate;
    uint8_t rs;
    uint8_t rt;
    uint8_t opcode;
    int32_t signExtImmediate;
    uint32_t instr;

  public:
    I_Instruction(uint32_t instruction, register_map& regs);
    void run_I_Instruction(register_map& regs);

};

#endif
