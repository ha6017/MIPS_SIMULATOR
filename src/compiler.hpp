#ifndef COMPILER_HPP
#define COMPILER_HPP

#include "memory.hpp"
#include "R_Instruction.hpp"
#include "I_Instruction.hpp"
#include "J_Instruction.hpp"

class compiler{
  private:
    uint32_t PC;

  public:
    compiler(std::string binaryfile);
    //void RIJ_INSTRUCTION();
    void run();
    memory mem;
    register_map regs;
    I_Instruction iInst;
    R_Instruction rInst;
    J_Instruction jInst;

};

#endif
