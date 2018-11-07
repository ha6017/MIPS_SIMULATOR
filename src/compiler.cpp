#include <cmath>

#include "compiler.hpp"

void compiler::RIJ_INSTRUCTION(){
  uint32_t index_PC=(PC-0x10000000)/4;
  int compare = ADDR_INSTR[index_PC]&0xFC000000;
  //case compared to 000000 is true --> return R
  if(compare == 0x0){
    R_Instruction rInst;
    rInst.runInstruction();
  }//case compared to 0001 is true --> return J
  else if(compare == 0x8000000){
    J_Instruction();
  }//else --> return I
  else{
    I_Instruction();
  }
  PC=PC+4;
  //cout<<"NEW value of PC intially ="<<*PC<<endl;
}

void compiler::run(std::string binaryfile){
  PC=0x10000000;
  memory mem(binaryfile);

  while((PC != 0x0) && ((PC <= 0x11000000) && (PC >= 0x10000000))) // ADD no-op[ cases]
  {
    uint32_t currentInstruction = mem.
    RIJ_INSTRUCTION();
    // if PC has reached end of instruction memory or points to a null instruction
    //if()

  }
}
