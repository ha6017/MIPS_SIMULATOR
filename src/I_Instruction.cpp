#include <cmath>
#include <stdint.h>
#include "memory.hpp"

I_Instruction::I_Instruction(uint32_t instruction, register_map& regs)
{
  immediate = instruction&0xFFFF;
  rt= ((instruction&0x1F0000)>>16);
  rs= ((instruction&0x3E00000)>>21);
  opcode = ((instruction&0xFC000000)>>26);
  signExtImmediate = int32_t(immediate << 16) >> 16;
  instr=instruction;

  op1s = regs.read(rs);
  op2s = regs.read(rt);
  op1 = regs.read(rs);
  op2 = regs.read(rt);
};

void I_Instruction(register_map& regs)
{
  switch(opcode)
  {
    case 8:
      //ADDI
      if(((op1s > 0) && (signExtImmediate > 0) && (op1s + signExtImmediate <= 0)) || ((op1s < 0) && (signExtImmediate < 0) && (op1s + signExtImmediate >= 0)))
      {
        // If both operands are +ve and result is -ve
        // OR If both operands are -ve and result is +ve
        exit(-10);
      }
      regs.write(rd, op1s+signExtImmediate);
      break;
    case 9:
      //ADDIU
      regs.write(rd, op1s+signExtImmediate);
      break;
    case 12:
      //ANDI
      regs.write(rd, op1&uint32_t(immediate));
      break;
    case 4:
      //BEQ
      if (op1 == op2){
        PC = PC + (signExtImmediate << 2);
      }
      break;
    case 1:
      uint32_t copy_pc = PC;
      if (rt == 0)
      {
        // bltz
        if (op1s < 0)//rs<<0
        {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);
          //compiler::loop_avoider();
        }
      }
      else if(rt==16)
      {
        //bltzal
        if(op1s < 0)
        {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);
          regs.write(31,(copy_pc+8));

        }
      }
      else if (rt == 1)
      {
        // bgez
        if (op1s >= 0)
        {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);
        }
      }
      else if(rt==17)
      {
        //bgezal
        if (op1s >= 0)
        {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);
          regs.write(31,(copy_pc+8));
        }
      }
      /*else
      {
        return mips_ExceptionInvalidAlignment;
      }
      if(rt == 16 || rt == 17){
        // bltzal or bgezal - set R31 unconditionally
        mips_cpu_set_register(state, 31, state->pc + 4);
      }*/
      break;
    case 7:
      //BGTZ
      uint32_t copy_pc = PC;
      if (op1s > 0)
      {
        regs.PC=regs.PC+4;
        compiler::loop_avoider();
        regs.PC = copy_pc + 4 + (signExtImmediate << 2);
      }
      break;
    case 6:
      //BLEZ
      uint32_t copy_pc = PC;
      if(op1s<=0)
      {
        regs.PC=regs.PC+4;
        compiler::loop_avoider();
        regs.PC = copy_pc + 4 + (signExtImmediate << 2);
      }
      break;
    case 5:
      //BNE
      uint32_t copy_pc = PC;
      if (op1 != op2)
      {
        regs.PC=regs.PC+4;
        compiler::loop_avoider();
        regs.PC = copy_pc + 4 + (signExtImmediate << 2);
      }
      break;
    case 32:
      //LB
      break;
    case 36:
      //LBU
      break;
    case 33:
      //LH
      break;
    case 37:
      //LHU
      break;
    case 15:
      //LUI
      break;
    case 35:
      //LW
      break;
    case 34:
      //LWL
      break;
    case 38:
      //LWR
      break;
    case 13:
      //ORI
      regs.write(rt,(op1|uint32_t(immediate)));
      break;
    case 10:
      //SLTI
      if (op1s < signExtImmediate)
      {
        regs.write(rt,1);
      }
      else
      {
        regs.write(rt,0);
      }
      break;
    case 11:
      //SLTIU
      if (op1 < uint32_t(signExtImmediate))
      {
        regs.write(rt,1);
      }
      else
      {
        regs.write(rt,0);
      }
      break;
    case 43:
      //SW
      break;
    case 14:
      //XORI
      regs.write(rt,(op1^uint32_t(immediate)));
      break;
  }
  if((instruction&0xF0000000) == 8){
    //COPz
  }else if((instruction&0xF0000000) == 13){
    //LDCz
  }else if((instruction&0xF0000000) == 12){
    //LWCz
  }else if((instruction&0xF0000000) == 15){
    //SDCz
  }else if((instruction&0xF0000000) == 14){
    //SWCz
  }
}

  }
}
