#include <cmath>

#include "R_Instruction.hpp"
#include "register_map.hpp"

R_Instruction::R_Instruction(uint32_t instruction){

  uint32_t Fn_code = instruction&0x3F;
  uint32_t shamt = instruction&0x7C0;
  uint32_t rd= instruction&0xF800;
  rd=rd/pow(2,11);
  uint32_t rt= instruction&0x1F0000;
  rt=rt/pow(2,16);
  uint32_t rs= instruction&0x3E00000;
  rs=rs/pow(2,21);

}

void R_Instruction::runInstruction(register_map &regs){
  switch(Fn_code){
    case 32:
      //ADD
      break;
    case 33:
      //ADDU
      ADDU(register_map &regs);
      break;
    case 36:
      //AND
      break;
    case 13:
      //BREAK
      break;
    case 44:
      //DADD
      break;
    case 45:
      //DADDU
      break;
    case 30:
      //DDIV
      break;
    case 31:
      //DDIVU
      break;
    case 26:
      //DIV
      break;
    case 27:
      //DIVU
      break;
    case 28:
      //DMULT
      break;
    case 29:
      //DMULTU
      break;
    case 56:
      //DSLL
      break;
    case 60:
      //DSLL32
      break;
    case 20:
      //DSLLV
      break;
    case 59:
      //DSRA
      break;
    case 63:
      //DSRA32
      break;
    case 23:
      //DSRAV
      break;
    case 58:
      //DSRL
      break;
    case 62:
      //DSRL32
      break;
    case 22:
      //DSRLV
      break;
    case 46:
      //DSUB
      break;
    case 47:
      //DSUBU
      break;
    case 9:
      //JALR
      break;
    case 8:
      //JR
      JR(register_map &regs);
      break;
    case 16:
      //MFHI
      break;
    case 18:
      //MFLO
      break;
    case 11:
      //MOVN
      break;
    case 10:
      //MOVZ
      break;
    case 17:
      //MTHI
      break;
    case 19:
      //MTLO
      break;
    case 24:
      //MULT
      break;
    case 25:
      //MULTU
      break;
    case 39:
      //NOR
      break;
    case 37:
      //OR
      break;
    case 0:
      //SLL
      break;
    case 4:
      //SLLV
      break;
    case 42:
      //SLT
      break;
    case 43:
      //SLTU
      break;
    case 3:
      //SRA
      break;
    case 7:
      //SRAV
      break;
    case 2:
      //SRL
      break;
    case 6:
      //SRLV
      break;
    case 34:
      //SUB
      break;
    case 35:
      //SUBU
      break;
    case 15:
      //SYNC
      break;
    case 12:
      //SYSCALL
      break;
    case 52:
      //TEQ
      break;
    case 48:
      //TGE
      break;
    case 49:
      //TGEU
      break;
    case 50:
      //TLT
      break;
    case 51:
      //TLTU
      break;
    case 54:
      //TNE
      break;
    case 38:
      //XOR
      break;
  }
}

void R_Instruction::ADDU(register_map &regs){
  regs = REG_VECTOR[rs] + REG_VECTOR[rt];
  //cout<<"\nregister_vector[rd] = "<<register_vector[rd]<<endl;
}

void R_Instruction::JR(register_map &regs){
  PC = PC + 4;
  //RIJ_INSTRUCTION(PC, vect, register_vector);
  PC = REG_VECTOR[rs] - 4;
}
