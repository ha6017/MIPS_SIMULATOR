#include <cmath>

#include "R_Instruction.hpp"


R_Instruction::R_Instruction(uint32_t instruction){

   Fn_code = instruction&0x3F;
   shamt = ((instruction&0x7C0)>>6);
   rd= ((instruction&0xF800)>>11);
  //rd=rd/pow(2,11);
   rt= ((instruction&0x1F0000)>>16);
  //rt=rt/pow(2,16);
   rs= ((instruction&0x3E00000)>>21);
  //rs=rs/pow(2,21);

  op1s = regs.read(rs);
  op2s = regs.read(rt);
  op1 = regs.read(rs);
  op2 = regs.read(rt);

  switch(Fn_code){
    case 32:
      ADD(regs);
      break;
    case 33:
      ADDU(regs);
      break;
    case 36:
      AND(regs);
      break;
    case 26:
      DIV(regs);
      break;
    case 27:
      DIVU(regs);
      break;
    case 9:
      JALR(regs);
      break;
    case 8:
      JR(regs);
      break;
    case 16:
      MFHI(regs);
      break;
    case 18:
      MFLO(regs);
      break;
    case 17:
      MTHI(regs);
      break;
    case 19:
      MTLO(regs);
      break;
    case 24:
      MULT(regs);
      break;
    case 25:
      MULTU(regs);
      break;
    case 37:
      OR(regs);
      break;
    case 0:
      SLL(regs);
      break;
    case 4:
      SLLV(regs);
      break;
    case 42:
      SLT(regs);
      break;
    case 43:
      SLTU(regs);
      break;
    case 3:
      SRA(regs);
      break;
    case 7:
      SRAV(regs);
      break;
    case 2:
      SRL(regs);
      break;
    case 6:
      SRLV(regs);
      break;
    case 34:
      SUB(regs);
      break;
    case 35:
      SUBU(regs);
      break;
    case 38:
      XOR(regs);
      break;
  }
}

void R_Instruction::ADD(register_map& regs){
  if(((op1s > 0) && (op2s > 0) && (op1s + op2s <= 0)) || ((op1s < 0) && (op2s < 0) && (op1s + op2s >= 0))){
    std::exit(-10);
  }
  regs.write(rd, op1s+op2s);
}

void R_Instruction::ADDU(register_map& regs){
  regs.write(rd, op1 + op2);
  //cout<<"\nregister_vector[rd] = "<<register_vector[rd]<<endl;
}

void R_Instruction::AND(register_map& regs){
  regs.write(rd, op1 & op2);
}

void R_Instruction::DIV(register_map& regs){
  if (op2 == 0){
    // Operation is now undefined - don't modify hi and lo
    std::exit(-10);
  }
  regs.lo = op1s / op2s;
  regs.hi = op1s % op2s;
}

void R_Instruction::DIVU(register_map& regs){
  if (op2 == 0){
    // Operation is now undefined - don't modify hi and lo
    std::exit(-10);
  }
  regs.lo = op1 / op2;
  regs.hi = op1 % op2;
}

void R_Instruction::JALR(register_map& regs){
  //save the PC and rs value before executing the branch delay
  uint32_t copyPC = regs.PC;
  uint32_t copyrs = regs.read(rs);
  regs.PC = regs.PC + 4;
  compiler::loop_avoider();
  regs.write(rd, copyPC + 8);
  regs.PC = regs.read(copyrs);
}

void R_Instruction::JR(register_map& regs){
  regs.PC = regs.PC + 4;
  compiler::loop_avoider();
  regs.PC = regs.read(rs) - 4;

}

void R_Instruction::MFHI(register_map& regs){

}

void R_Instruction::MFLO(register_map& regs){

}

void R_Instruction::MTHI(register_map& regs){

}

void R_Instruction::MTLO(register_map& regs){

}

void R_Instruction::MULT(register_map& regs){
  regs.hi = (((int64_t(op1) << 32) >> 32) * ((int64_t(op2) << 32) >> 32)) >> 32;

  regs.lo = ((int64_t(op1) << 32) >> 32) * ((int64_t(op2) << 32) >> 32);
}

void R_Instruction::MULTU(register_map& regs){
  regs.hi = (uint64_t(op1) * uint64_t(op2)) >> 32;

  regs.lo = uint64_t(op1) * uint64_t(op2);

}

void R_Instruction::OR(register_map& regs){
  regs.write(rd, (op1|op2));
}

void R_Instruction::SLL(register_map& regs){
  regs.write(rd, (op2<<shamt));
}

void R_Instruction::SLLV(register_map& regs){
  regs.write(rd, (op2<<op1));
}

void R_Instruction::SLT(register_map& regs){
  if (op1s < op2s){
    regs.write(rd, 1);
  } else {
    regs.write(rd, 0);
  }
}

void R_Instruction::SLTU(register_map& regs){
  if (op1 < op2){
    regs.write(rd, 1);
  } else {
    regs.write(rd, 0);
  }
}

void R_Instruction::SRA(register_map& regs){
  regs.write(rd, (op2s>>shamt));
}

void R_Instruction::SRAV(register_map& regs){
  regs.write(rd, (op2s >> op1));
}

void R_Instruction::SRL(register_map& regs){
  regs.write(rd, (op2>>shamt));
}

void R_Instruction::SRLV(register_map& regs){
  regs.write(rd, op2>>op1);
}

void R_Instruction::SUB(register_map& regs){
  if(((op1s < 0) && (op2s > 0) && (op1s - op2s >= 0)) || ((op1s > 0) && (op2s < 0) && (op1s - op2s <= 0))){
    // If op1 -ve, op2 +ve, result +ve
    // OR If op1 +ve, op2 -ve, result -ve
    std::exit(-10);
  }
  regs.write(rd, (op1s - op2s));
}

void R_Instruction::SUBU(register_map& regs){
  regs.write(rd, op1 - op2);
}

void R_Instruction::XOR(register_map& regs){
  regs.write(rd, op1^op2);
}
