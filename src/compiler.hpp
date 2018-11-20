#ifndef COMPILER_HPP
#define COMPILER_HPP

#include "memory.hpp"
#include "register_map.hpp"

class compiler{
  private:
    //uint32_t PC;
    memory mem; //defined an object of class memory
    register_map regs;

    uint8_t Fn_code;
    uint8_t shamt;
    uint8_t rd;
    uint8_t rt;
    uint8_t rs;

    int32_t op1s;
    int32_t op2s;
    uint32_t op1;
    uint32_t op2;

    int16_t immediate;
    int32_t signExtImmediate;

    uint32_t instr_index;


  public:
    compiler(std::string binaryfile); //constructor
    void run();
    void loop_avoider ();

    void runRtype(uint32_t instruction);
    void runJtype(uint32_t instruction);
    void runItype(uint32_t instruction);



    //R type instructions
    void ADD();
    void ADDU();
    void AND();
    void DIV();
    void DIVU();
    void JALR();
    void JR();
    void MFHI();
    void MFLO();
    void MTHI();
    void MTLO();
    void MULT();
    void MULTU();
    void OR();
    void SLL();
    void SLLV();
    void SLT();
    void SLTU();
    void SRA();
    void SRAV();
    void SRL();
    void SRLV();
    void SUB();
    void SUBU();
    void XOR();
};

#endif
