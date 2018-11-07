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
    void RIJ_INSTRUCTION();
    void run(std::string binaryfile);
};

#endif
