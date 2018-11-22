#include "compiler.hpp"
#include<cmath>
#include<iostream>

//the constructor of class compiler initialises the object mem of class memory
// which is defined as a private date member. This calls the constructor of class memory and initialises the memory.
compiler::compiler(std::string binaryfile) : mem(binaryfile), regs()
{
  //regs.setRegisters();
}

void compiler::loop_avoider(){
  if((regs.PC != 0x0) && ((regs.PC <= 0x11000000) && (regs.PC >= 0x10000000)))
  {
    //std::cout<<"INSIDE LOOP AVOIDER\n";
    uint32_t currentInstruction = mem.readInstruction(regs.PC);
    opcode = ((currentInstruction&0xFC000000)>>26);
    //case compared to 000000 is true --> return R
    if(opcode == 0x0){
      runRtype(currentInstruction);
    //  R_Instruction rInst(currentInstruction, regs);
    //  rInst.runInstruction(regs);
    }//case compared to 0001 is true --> return J
    else if(opcode == 0x2){
      //J_Instruction();
      //runJtype(currentInstruction);
      J(currentInstruction);
    }
    else if(opcode == 0x3)
    {
      JAL(currentInstruction);
    }//else --> return I
    else{
      //I_Instruction iInst(currentInstruction);
      //iInst.run_I_Instruction(regs);
      runItype(currentInstruction);
    }
    regs.PC=regs.PC+4;
    //std::cout<<"OUTSIDE LOOP AVOIDER\n";
    // if PC has reached end of instruction memory or points to a null instruction
    //if()
  }
  else
  {
    std::exit(-11);
  }
}

void compiler::run(){
  //int count=0;
  while((regs.PC != 0x0) && ((regs.PC <= 0x11000000) && (regs.PC >= 0x10000000))) // ADD no-op[ cases]
  {
    compiler::loop_avoider();
      //std::cout<<"an instruction has been sent to loop\n";
      //count++;
      /*if(count<10)
      {
        std::cout<<"an instruction has been sent to loop\n";
      }*/
  }
  uint8_t exitCode = (regs.read(2)&0x000000FF);
  std::exit(exitCode);
  //regs.printRegisters();
}

void compiler::runRtype(uint32_t instruction){

  Fn_code = instruction&0x3F;
  //std::cout<<std::hex<<"Fn_code = "<<Fn_code<<std::endl;
  shamt = ((instruction&0x7C0)>>6);
  rd = ((instruction&0xF800)>>11);
  //rd=rd/pow(2,11);
  rt = ((instruction&0x1F0000)>>16);
  //rt=rt/pow(2,16);
  rs = ((instruction&0x3E00000)>>21);
  //rs=rs/pow(2,21);
  op1s = regs.read(rs);
  op2s = regs.read(rt);
  op1 = regs.read(rs);
  op2 = regs.read(rt);

  switch(Fn_code)
  {
    case 32: ADD(); break;
    case 33: ADDU();break;
    case 36: AND(); break;
    case 26: DIV(); break;
    case 27: DIVU();break;
    case 9: JALR(); break;
    case 8: JR();   break;
    case 16: MFHI();break;
    case 18: MFLO();break;
    case 17: MTHI();break;
    case 19: MTLO();break;
    case 24: MULT();break;
    case 25:MULTU();break;
    case 37: OR();  break;
    case 0:  SLL(); break; //no-op
    case 4: SLLV(); break;
    case 42: SLT(); break;
    case 43: SLTU();break;
    case 3: SRA();  break;
    case 7: SRAV(); break;
    case 2: SRL();  break;
    case 6: SRLV(); break;
    case 34: SUB(); break;
    case 35: SUBU();break;
    case 38: XOR(); break;
  }
}

/*void compiler::runJtype(uint32_t instruction){
  instr_index = instruction&0x03FFFFFF;
  if(opcode == 2)
  {
    J();
  }
  else
  {
    JAL();
  }
}*/

void compiler::J(uint32_t instruction) //changed
{
  instr_index = instruction&0x03FFFFFF;
  //new PC (PC +4) takes 4 msb
  regs.PC=regs.PC+4;
  //adds onto this the instruction index left shifted by 2
  uint32_t copyPC = (((regs.PC)&0xF0000000) | (instr_index<<2)); //concatenated instead of + and added +4 to pc value
  //runs next instruction
  compiler::loop_avoider();
  //PC = new value calculated before
  regs.PC = copyPC-4;
}

void compiler::JAL(uint32_t instruction) //changed wrong
{
  instr_index = instruction&0x03FFFFFF;
  uint32_t copyPC2 = regs.PC;
  //new PC (PC +4) takes 4 msb
  regs.PC=regs.PC+4;
  //same as J instruction from here --
  uint32_t copyPC = (((regs.PC)&0xF0000000) | (instr_index<<2));
  compiler::loop_avoider();
  //writes link into register 31
  regs.write(31, copyPC2 + 8);
  regs.PC = copyPC-4;
}

/*void compiler::J(){
  //new PC (PC +4) takes 4 msb
  //adds onto this the instruction index left shifted by 2
  uint32_t copyPC = ((regs.PC)&0xF0000000) + (instr_index<<2);
  //runs next instruction
  compiler::loop_avoider();
  //PC = new value calculated before
  regs.PC = copyPC-4;
}

void compiler::JAL(){
  //writes link into register 31
  regs.write(31, regs.PC + 8);
  //same as J instruction from here --
  uint32_t copyPC = ((regs.PC)&0xF0000000) + (instr_index<<2);
  compiler::loop_avoider();
  regs.PC = copyPC-4;
}*/

void compiler::runItype(uint32_t instruction){
  immediate = instruction&0xFFFF;
  //std::cout<<std::hex<<"Immediate value ="<<immediate<<std::endl;
  rt= ((instruction&0x1F0000)>>16);
  rs= ((instruction&0x3E00000)>>21);
  signExtImmediate = int32_t(immediate);
  //instr =instruction;
  op1s = regs.read(rs);
  op2s = regs.read(rt);
  op1 = regs.read(rs);
  op2 = regs.read(rt);

  uint32_t copy_pc;
  int16_t val16;
  int8_t val;

  switch(opcode)
  {
    case 8: ADDI(); break;
    case 9: ADDIU(); break;
    case 12: ANDI(); break;
    case 4: BEQ(); break;
    case 1: BRANCHES(); break;
      /*if ((rt == 0) && (op1s < 0)) BLTZ();
      else if((rt==16) && (op1s < 0)) BLTZAL();
      else if (rt == 1) BGEZ();
      else if((rt==17) && (op1s >= 0)) BGEZAL();
      break;*/
    case 7: BGTZ(); break;
    case 6: BLEZ(); break;
    case 5: BNE(); break;
    case 32: LB(); break;
    case 36: LBU(); break;
    case 33: LH(); break;
    case 37: LHU(); break;
    case 15: LUI(); break;
    case 35: LW(); break;
    case 34: LWL(); break;
    case 38: LWR(); break;
    case 13: ORI(); break;
    case 10: SLTI(); break;
    case 11: SLTIU(); break;
    case 40: SB(); break;
    case 41: SH(); break;
    case 43: SW(); break;
    case 14: XORI(); break;
    }
}

void compiler::ADDI()
{
  if(((op1s > 0) && (signExtImmediate > 0) && (op1s + signExtImmediate <= 0)) || ((op1s < 0) && (signExtImmediate < 0) && (op1s + signExtImmediate >= 0))){
    // If both operands are +ve and result is -ve
    // OR If both operands are -ve and result is +ve
    std::exit(-10);
  }
  regs.write(rt, op1s+signExtImmediate);
  //std::cout<<std::hex<<"regs.read("<< rt <<")="<<regs.read(rt)<<std::endl;
  //std::cout<<std::hex<<"PC at addi= "<<regs.PC<<std::endl;
}

void compiler::ADDIU()
{
  regs.write(rt, op1s+signExtImmediate);
}

void compiler::ANDI()
{
  regs.write(rt, op1&(uint32_t(immediate)&0xFFFF));
}

void compiler::ADD()
{
  if(((op1s > 0) && (op2s > 0) && (op1s + op2s <= 0)) || ((op1s < 0) && (op2s < 0) && (op1s + op2s >= 0)))
  {
     std::exit(-10);
  }
  regs.write(rd, op1s+op2s);
}

void compiler::ADDU()
{
  regs.write(rd, op1 + op2);
  //cout<<"\nregister_vector[rd] = "<<register_vector[rd]<<endl;
}

void compiler::BEQ()
{
  //std::cout<<"BEQ has been called\n";
  uint32_t copyPC = regs.PC;
  //std::cout<<std::hex<<"copypc="<<copyPC<<std::endl;
  int32_t signExtImmediate2 = signExtImmediate;
  //std::cout<<std::hex<<"signExtImmediate="<<signExtImmediate<<std::endl;
  if (op1 == op2)
  {
    regs.PC=regs.PC+4;
    //std::cout<<"op1 = op2 and doing the delayed branch\n";
    //std::cout<<std::hex<<"regs.pc="<<regs.PC<<std::endl;
    compiler::loop_avoider();
    //std::cout<<"came back from delayed branch\n";
    //std::cout<<std::hex<<"regs.pc="<<regs.PC<<std::endl;
    //std::cout<<std::hex<<"copypc="<<copyPC<<std::endl;
    //std::cout<<std::hex<<"signExtImmediate2="<<signExtImmediate2<<std::endl;
    //std::cout<<std::hex<<"signExtImmediate2 shifted by 2="<<(signExtImmediate2<<2)<<std::endl;
    regs.PC = copyPC + (signExtImmediate2 << 2) - 4;
    //std::cout<<std::hex<<"regs.pc="<<regs.PC<<std::endl;
  }
}

void compiler::BRANCHES()
{
  uint32_t copyPC = regs.PC;
  int32_t signExtImmediate2 = signExtImmediate;
  if ((rt == 0) && (op1s < 0)) //BLTZ()
  {
    regs.PC=regs.PC+4;
    compiler::loop_avoider();
    regs.PC = copyPC + (signExtImmediate2 << 2);
  }
  else if((rt==16) && (op1s < 0)) //BLTZAL()
  {
    regs.PC=regs.PC+4;
    compiler::loop_avoider();
    regs.PC = copyPC + (signExtImmediate2 << 2);
    regs.write(31,(copyPC+8));
  }
  else if ((rt == 1)&&(op1s >= 0)) //BGEZ
  {
    regs.PC=regs.PC+4;
    compiler::loop_avoider();
    regs.PC = copyPC + (signExtImmediate2 << 2);
  }
  else if((rt==17) && (op1s >= 0)) //BGEZAL
  {
    regs.PC=regs.PC+4;
    compiler::loop_avoider();
    regs.PC = copyPC + (signExtImmediate2 << 2);
    regs.write(31,(copyPC+8));
  }
}

/*void compiler::BLTZ()
{
  uint32_t copyPC = regs.PC;
  int32_t signExtImmediate2 = signExtImmediate;
  regs.PC=regs.PC+4;
  compiler::loop_avoider();
  regs.PC = copyPC + (signExtImmediate2 << 2);
}

void compiler::BLTZAL()
{
  uint32_t copyPC = regs.PC;
  int32_t signExtImmediate2 = signExtImmediate;
  regs.PC=regs.PC+4;
  compiler::loop_avoider();
  regs.PC = copyPC + (signExtImmediate2 << 2);
  regs.write(31,(copyPC+8));
}

void compiler::BGEZ()
{
  if(op1s >= 0)
  {
    uint32_t copyPC = regs.PC;
    int32_t signExtImmediate2 = signExtImmediate;
    regs.PC=regs.PC+4;
    compiler::loop_avoider();
    regs.PC = copyPC + (signExtImmediate2 << 2);
  }
}

void compiler::BGEZAL()
{
  uint32_t copyPC = regs.PC;
  int32_t signExtImmediate2 = signExtImmediate;
  regs.PC=regs.PC+4;
  compiler::loop_avoider();
  regs.PC = copyPC + (signExtImmediate2 << 2);
  regs.write(31,(copyPC+8));
}*/

void compiler::BGTZ()
{
  uint32_t copyPC = regs.PC;
  int32_t signExtImmediate2 = signExtImmediate;
  if ((op1s > 0) && (rt==0))
  {
    regs.PC=regs.PC+4;
    compiler::loop_avoider();
    regs.PC = copyPC + (signExtImmediate2 << 2);
  }
}

void compiler::BLEZ()
{
  uint32_t copyPC = regs.PC;
  int32_t signExtImmediate2 = signExtImmediate;
  if((op1s<=0) && (rt==0))
  {
    regs.PC=regs.PC+4;
    compiler::loop_avoider();
    regs.PC = copyPC + (signExtImmediate2 << 2);
  }
}

void compiler::BNE()
{
  uint32_t copyPC = regs.PC;
  int32_t signExtImmediate2 = signExtImmediate;
  if (op1 != op2)
  {
    regs.PC=regs.PC+4;
    compiler::loop_avoider();
    regs.PC = copyPC + (signExtImmediate2 << 2);
  }
}

void compiler::LB()
{
  regs.write(rt, mem.load_byte_from_memory(regs.read(rs)+signExtImmediate));
}

void compiler::LBU()
{
  regs.write(rt, mem.load_unsigned_byte_from_memory(regs.read(rs)+signExtImmediate));
}

void compiler::LH()
{
  regs.write(rt, mem.load_half_word_from_memory(regs.read(rs)+signExtImmediate));
}

void compiler::LHU()
{
  regs.write(rt, mem.load_unsigned_half_word_from_memory(regs.read(rs)+signExtImmediate));
}

void compiler::LUI()
{
  regs.write(rt,((uint32_t(immediate)<<16)&0xFFFF0000));
}

void compiler::LW()
{
  regs.write(rt, mem.load_from_memory(regs.read(rs)+signExtImmediate));
}

void compiler::LWL()
{
  int32_t lwl_word = mem.load_word_left_from_memory(regs.read(rs)+signExtImmediate);
  if((regs.read(rs)+signExtImmediate)%4==0)
  {
    regs.write(rt,lwl_word);
  }
  else if((regs.read(rs)+signExtImmediate)%4==1)
  {
     regs.write(rt, (regs.read(rt)&0x000000FF)|lwl_word);
  }
  else if((regs.read(rs)+signExtImmediate)%4==2)
  {
     regs.write(rt, (regs.read(rt)&0x0000FFFF)|lwl_word);
  }
  else if((regs.read(rs)+signExtImmediate)%4==3)
  {
    regs.write(rt, (regs.read(rt)&0x00FFFFFF)|lwl_word);
  }

}

void compiler::LWR()
{
  int32_t lwr_word = mem.load_word_right_from_memory(regs.read(rs)+signExtImmediate);
  if((regs.read(rs)+signExtImmediate)%4==0)
  {
      regs.write(rt,lwr_word);
  }
  else if((regs.read(rs)+signExtImmediate)%4==1)
  {
      regs.write(rt, (regs.read(rt)&0xFFFFFF00)|lwr_word);
  }
  else if((regs.read(rs)+signExtImmediate)%4==2)
  {
      regs.write(rt, (regs.read(rt)&0xFFFF0000)|lwr_word);
  }
  else if((regs.read(rs)+signExtImmediate)%4==3)
  {
      regs.write(rt, (regs.read(rt)&0xFF000000)|lwr_word);
  }

}

void compiler::ORI()
{
  regs.write(rt,(op1|(int32_t(immediate)&0xFFFF)));
}

void compiler::SLTI()
{
  if (op1s < signExtImmediate)
  {
    regs.write(rt,1);
  }
  else
  {
    regs.write(rt,0);
  }
}

void compiler::SLTIU()
{
  if (op1 < uint32_t(signExtImmediate))
  {
    regs.write(rt,1);
  }
  else
  {
    regs.write(rt,0);
  }
}

void compiler::SB()
{
  int8_t val = regs.read(rt)&0xFF;
  mem.store_byte_to_memory((regs.read(rs)+signExtImmediate),val);
}

void compiler::SH()
{
  int16_t val16 = regs.read(rt)&0xFFFF;
  mem.store_halfword_to_memory((regs.read(rs)+signExtImmediate), val16);
}

void compiler::SW()
{
  mem.store_to_memory((regs.read(rs)+signExtImmediate),regs.read(rt));
}

void compiler::XORI()
{
  regs.write(rt,(op1^(int32_t(immediate)&0xFFFF)));
}

void compiler::AND()
{
  regs.write(rd, op1 & op2);
}

void compiler::DIV()
{
  if (op2 != 0){
     // Operation is now undefined - don't modify hi and lo
     regs.lo = op1s / op2s;
     regs.hi = op1s % op2s;
  }

}

void compiler::DIVU()
{
  if (op2 != 0)
  {
     // Operation is now undefined - don't modify hi and lo
     regs.lo = op1 / op2;
     regs.hi = op1 % op2;
  }

}

void compiler::JALR()
{
  //save the PC and rs value before executing the branch delay
  uint32_t copyPC = regs.PC;
  int32_t copyrs = regs.read(rs);
  regs.PC = regs.PC + 4;
  compiler::loop_avoider();
  regs.write(rd, (copyPC + 8));
  regs.PC = regs.read(copyrs)-4;
}

void compiler::JR()
{
  regs.PC = regs.PC + 4;
  int32_t copyrs = regs.read(rs);
  //std::cout<<"JR has been called\n";
  compiler::loop_avoider();
  regs.PC = copyrs - 4;
  //std::cout<<"regs.PC="<<regs.PC<<std::endl;
}

void compiler::MFHI()
{
  regs.write(rd,regs.hi);
}

void compiler::MFLO()
{
  regs.write(rd,regs.lo);
}

void compiler::MTHI()
{
  regs.hi = regs.read(rs);
}

void compiler::MTLO()
{
  regs.lo = regs.read(rs);
}

void compiler::MULT()
{
  //regs.hi = (((int64_t(op1) << 32) >> 32) * ((int64_t(op2) << 32) >> 32)) >> 32;
  //regs.lo = ((int64_t(op1) << 32) >> 32) * ((int64_t(op2) << 32) >> 32);

  regs.hi = (int64_t(op1s*op2s)>>32);
  regs.lo = int64_t(op1s*op2s);
}

void compiler::MULTU()
{
  //regs.hi = (uint64_t(op1) * uint64_t(op2)) >> 32;
  //regs.lo = uint64_t(op1) * uint64_t(op2);

  regs.hi = (uint64_t(op1*op2)>>32);
  regs.lo = (uint64_t(op1*op2));
}

void compiler::OR()
{
  regs.write(rd, (op1|op2));
}

void compiler::SLL()
{
  regs.write(rd, (op2*std::pow(2,shamt)));
}

void compiler::SLLV()
{
  regs.write(rd, (op2*std::pow(2,(op1&0x1F))));
}

void compiler::SLT()
{
  if (op1s < op2s)
  {
     regs.write(rd, 0x1);
  }
  else
  {
     regs.write(rd, 0x0);
  }
}

void compiler::SLTU()
{
  if (op1 < op2)
  {
     regs.write(rd, 0x1);
  }
  else
  {
     regs.write(rd, 0x0);
  }
}

void compiler::SRA()
{
  regs.write(rd, (op2s>>shamt));
}

void compiler::SRAV()
{
  regs.write(rd, (op2s >> op1));
}

void compiler::SRL()
{
  regs.write(rd, (op2/std::pow(2,shamt)));
}

void compiler::SRLV()
{
  regs.write(rd, (op2/std::pow(2,op1)));
}

void compiler::SUB()
{
  if(((op1s < 0) && (op2s > 0) && (op1s - op2s >= 0)) || ((op1s > 0) && (op2s < 0) && (op1s - op2s <= 0))){
    // If op1 -ve, op2 +ve, result +ve
    // OR If op1 +ve, op2 -ve, result -ve
    std::exit(-10);
  }
  regs.write(rd, (op1s - op2s));
}

void compiler::SUBU()
{
  regs.write(rd, op1 - op2);
}

void compiler::XOR()
{
  regs.write(rd, op1^op2);
}
