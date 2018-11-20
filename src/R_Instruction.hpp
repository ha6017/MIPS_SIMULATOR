#ifndef R_INSTRUCTION_HPP
#define R_INSTRUCTION_HPP

#include <cmath>
#include <stdint.h>

#include "compiler.hpp"
#include "register_map.hpp"

class R_Instruction{
private:
  uint8_t Fn_code;
  uint8_t shamt;
  uint8_t rd;
  uint8_t rt;
  uint8_t rs;

  int32_t op1s;
  int32_t op2s;
  uint32_t op1;
  uint32_t op2;


public:
  //friend void compiler::run();
  R_Instruction(uint32_t instruction, register_map& regs);
  void runInstruction(register_map& regs);
  void ADD(register_map& regs);
  void ADDU(register_map& regs);
  void AND(register_map& regs);
  void DIV(register_map& regs);
  void DIVU(register_map& regs);
  void JALR(register_map& regs);
  void JR(register_map& regs);
  void MFHI(register_map& regs);
  void MFLO(register_map& regs);
  void MTHI(register_map& regs);
  void MTLO(register_map& regs);
  void MULT(register_map& regs);
  void MULTU(register_map& regs);
  void OR(register_map& regs);
  void SLL(register_map& regs);
  void SLLV(register_map& regs);
  void SLT(register_map& regs);
  void SLTU(register_map& regs);
  void SRA(register_map& regs);
  void SRAV(register_map& regs);
  void SRL(register_map& regs);
  void SRLV(register_map& regs);
  void SUB(register_map& regs);
  void SUBU(register_map& regs);
  void XOR(register_map& regs);

  //friend void RIJ_INSTRUCTION();
  friend uint32_t* instructions();
  friend uint32_t* data();
  friend int32_t* registers();
};

#endif
