#include "compiler.hpp"
#include<cmath>
#include<iostream>

//the constructor of class compiler initialises the object mem of class memory
// which is defined as a private date member. This calls the constructor of class memory and initialises the memory.
compiler::compiler(std::string binaryfile) : mem(binaryfile), regs()
{


}

void compiler::loop_avoider()
{
  if((regs.PC < 0x11000000) && (regs.PC >= 0x10000000))
  {
    uint32_t currentInstruction = mem.readInstruction(regs.PC);
    opcode = ((currentInstruction&0xFC000000)>>26);
    if(opcode == 0x0) runRtype(currentInstruction); //case compared to 000000 is true --> return R
    else if(opcode == 0x2)  J(currentInstruction); //case compared to 0001 is true --> return J
    else if(opcode == 0x3) JAL(currentInstruction);
    else runItype(currentInstruction);
    regs.PC=regs.PC+4;
  }
  else   std::exit(-11);
}

void compiler::run()
{
  while((regs.PC != 0) && ((regs.PC >= 0x10000000) && (regs.PC <= 0x11000000)))
  {
    compiler::loop_avoider();
  }
  if(regs.PC==0)
  {
    uint8_t exitCode = (regs.read(2)&0x000000FF);
    std::cerr<<"exitcode is = "<< static_cast<int16_t>(exitCode) <<std::endl;
    std::exit(exitCode);
  }
  else std::exit(-11);
}

void compiler::runRtype(uint32_t instruction)
{
  Fn_code = instruction&0x3F;
  shamt = ((instruction&0x7C0)>>6);
  rd = ((instruction&0xF800)>>11);
  rt = ((instruction&0x1F0000)>>16);
  rs = ((instruction&0x3E00000)>>21);
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


void compiler::J(uint32_t instruction) //changed
{
  instr_index = instruction&0x03FFFFFF;
  regs.PC=regs.PC+4;
  uint32_t copyPC = (((regs.PC)&0xF0000000) | (instr_index<<2)); //concatenated instead of + and added +4 to pc value
  compiler::loop_avoider(); //runs next instruction
  regs.PC = copyPC-4;
}

void compiler::JAL(uint32_t instruction) //changed wrong
{
  instr_index = instruction&0x03FFFFFF;
  regs.write(31, regs.PC + 8); //writes link into register 31
  regs.PC=regs.PC+4; //new PC (PC +4) takes 4 msb
  uint32_t copyPC = (((regs.PC)&0xF0000000) | (instr_index<<2)); //same as J instruction from here --
  compiler::loop_avoider();
  regs.PC = copyPC-4;
}


void compiler::runItype(uint32_t instruction)
{
  immediate = instruction&0xFFFF;
  rt= ((instruction&0x1F0000)>>16);
  rs= ((instruction&0x3E00000)>>21);
  signExtImmediate = int32_t(immediate);

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
    default: std::exit(-12);
  }
}

void compiler::ADDI()
{
  if(((op1s > 0) && (signExtImmediate > 0) && (op1s + signExtImmediate <= 0)) || ((op1s < 0) && (signExtImmediate < 0) && (op1s + signExtImmediate >= 0)))
  {
    std::exit(-10);
  }
  regs.write(rt, op1s+signExtImmediate);
}

void compiler::ADDIU() {regs.write(rt, op1s+signExtImmediate);}

void compiler::ANDI() {regs.write(rt, op1&(uint32_t(immediate)&0xFFFF));}

void compiler::ADD()
{
  if(((op1s > 0) && (op2s > 0) && (op1s + op2s <= 0)) || ((op1s < 0) && (op2s < 0) && (op1s + op2s >= 0)))
  {
     std::exit(-10);
  }
  regs.write(rd, op1s+op2s);
}

void compiler::ADDU() {regs.write(rd, op1 + op2);}

void compiler::BEQ()
{
  uint32_t copyPC = regs.PC;
  int32_t signExtImmediate2 = signExtImmediate;
  if (op1 == op2)
  {
    regs.PC=regs.PC+4;
    compiler::loop_avoider();
    regs.PC = copyPC + (signExtImmediate2 << 2);
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
  else if(rt==16){ //BLTZAL()
    regs.write(31,(copyPC+8));
    if(op1s < 0)
    {
      regs.PC=regs.PC+4;
      compiler::loop_avoider();
      regs.PC = copyPC + (signExtImmediate2 << 2);
    }
  }
  else if ((rt == 1)&&(op1s >= 0)) //BGEZ
  {
    regs.PC=regs.PC+4;
    compiler::loop_avoider();
    regs.PC = copyPC + (signExtImmediate2 << 2);
  }
  else if(rt==17){ //BGEZAL
    regs.write(31,(copyPC+8));
    if(op1s >= 0)
    {
      regs.PC=regs.PC+4;
      compiler::loop_avoider();
      regs.PC = copyPC + (signExtImmediate2 << 2);
    }
  }
}

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
  uint32_t check_address = (op1s+signExtImmediate);
  if((check_address < 0x11000000) && (check_address >= 0x10000000))
  {
    int8_t instr_byte = mem.load_byte_from_instruction(check_address);
    int value = (0x000000FF & instr_byte);
    int  mask = 0x00000080;
    if(mask & instr_byte)
    {
      value += 0xFFFFFF00;
    }
    regs.write(rt, value);
  }
  else regs.write(rt, mem.load_byte_from_memory(check_address));
}

void compiler::LBU()
{
  uint32_t check_address = (op1s+signExtImmediate);
  if((check_address < 0x11000000) && (check_address >= 0x10000000))
  {
    int8_t instr_byte = mem.load_byte_from_instruction(check_address);
    regs.write(rt,(uint32_t(instr_byte)&0x000000FF));
  }
  else
  {
    regs.write(rt, mem.load_unsigned_byte_from_memory(check_address));
  }
}

void compiler::LH()
{
  uint32_t check_address = (op1s+signExtImmediate);
  if((check_address < 0x11000000) && (check_address >= 0x10000000) && (check_address%2==0))
  {
    int16_t instr_half_word = mem.load_half_word_from_instruction(check_address);
    regs.write(rt, (int32_t)instr_half_word);
  }
  else regs.write(rt, mem.load_half_word_from_memory(check_address));
}

void compiler::LHU()
{
  uint32_t check_address = (op1s+signExtImmediate);
  if((check_address < 0x11000000) && (check_address >= 0x10000000))
  {
    int16_t instr_half_word = mem.load_half_word_from_instruction(check_address);
    regs.write(rt, int32_t(instr_half_word)&0x0000FFFF);
  }
  else regs.write(rt, mem.load_unsigned_half_word_from_memory(check_address));
}

void compiler::LUI()
{
  regs.write(rt,((uint32_t(immediate)<<16)&0xFFFF0000));
}

void compiler::LW()
{
  uint32_t check_address = (op1s+signExtImmediate);
  if((check_address < 0x11000000) && (check_address >= 0x10000000)) regs.write(rt, mem.readInstruction(check_address));
  else regs.write(rt, mem.load_from_memory(check_address));
}

void compiler::LWL()
{
  uint32_t check_address = (op1s+signExtImmediate);
  int offset = (check_address%4);
  if((check_address < 0x11000000) && (check_address >= 0x10000000))
  {
    int32_t instr_word = mem.readInstruction(check_address-offset);
    switch (offset) {
      case 0: regs.write(rt,instr_word); break;
      case 1: regs.write(rt, (op2s&0x000000FF)|((instr_word&0x00FFFFFF)<<8)); break;
      case 2: regs.write(rt, (op2s&0x0000FFFF)|((instr_word&0x0000FFFF)<<16)); break;
      case 3: regs.write(rt, (op2s&0x00FFFFFF)|((instr_word&0x000000FF)<<24)); break;
    }
  }
  else
  {
    int32_t lwl_word = mem.load_word_left_from_memory(check_address);
    switch (offset) {
      case 0: regs.write(rt,lwl_word); break;
      case 1: regs.write(rt, (op2s&0x000000FF)|lwl_word); break;
      case 2: regs.write(rt, (op2s&0x0000FFFF)|lwl_word); break;
      case 3: regs.write(rt, (op2s&0x00FFFFFF)|lwl_word); break;
    }
  }
}

void compiler::LWR()
{
  uint32_t check_address = (op1s+signExtImmediate);
  int offset = check_address%4;
  if((check_address < 0x11000000) && (check_address >= 0x10000000))
  {
    int32_t instr_word = mem.readInstruction(check_address-offset);
    switch (offset)
    {
      case 3: regs.write(rt,instr_word); break;
      case 0: regs.write(rt, (op2s&0xFFFFFF00)|((instr_word&0xFF000000)>>24)); break;
      case 1: regs.write(rt, (op2s&0xFFFF0000)|((instr_word&0xFFFF0000)>>16)); break;
      case 2: regs.write(rt, (op2s&0xFF000000)|((instr_word&0xFFFFFF00)>>8)); break;
    }
  }
  else
  {
    int32_t lwr_word = mem.load_word_right_from_memory(check_address);
    switch (offset)
    {
      case 3: regs.write(rt,lwr_word); break;
      case 0: regs.write(rt, (op2s&0xFFFFFF00)|lwr_word); break;
      case 1: regs.write(rt, (op2s&0xFFFF0000)|lwr_word); break;
      case 2: regs.write(rt, (op2s&0xFF000000)|lwr_word); break;
    }
  }
}

void compiler::ORI() {regs.write(rt,(op1|(int32_t(immediate)&0xFFFF)));}

void compiler::SLTI()
{
  if (op1s < signExtImmediate) regs.write(rt,1);
  else regs.write(rt,0);
}

void compiler::SLTIU()
{
  if (op1 < uint32_t(signExtImmediate)) regs.write(rt,1);
  else regs.write(rt,0);
}

void compiler::SB()
{
  int8_t val = op2s&0xFF;
  mem.store_byte_to_memory((op1s+signExtImmediate),val);
}

void compiler::SH()
{
  int16_t val16 = op2s&0xFFFF;
  mem.store_halfword_to_memory((op1s+signExtImmediate), val16);
}

void compiler::SW() {mem.store_to_memory((op1s+signExtImmediate),op2s);}

void compiler::XORI() {regs.write(rt,(op1^(int32_t(immediate)&0xFFFF)));}

void compiler::AND() {regs.write(rd, op1 & op2);}

void compiler::DIV()
{
  if (op2 != 0){
     regs.lo = op1s / op2s;
     regs.hi = op1s % op2s;
  }
}

void compiler::DIVU()
{
  if (op2 != 0)
  {
     regs.lo = op1 / op2;
     regs.hi = op1 % op2;
  }
}

void compiler::JALR()
{
  int32_t copyrs = op1s;
  regs.write(rd, (regs.PC + 8));
  regs.PC = regs.PC + 4;
  compiler::loop_avoider();
  regs.PC = copyrs-4;
}

void compiler::JR()
{
  regs.PC = regs.PC + 4;
  int32_t copyrs = op1s;
  compiler::loop_avoider();
  regs.PC = copyrs - 4;
}

void compiler::MFHI() {regs.write(rd,regs.hi);}

void compiler::MFLO()
{
  regs.write(rd,regs.lo);
}

void compiler::MTHI() {regs.hi = op1s;}

void compiler::MTLO() {regs.lo = op1s;}

void compiler::MULT()
{
  int64_t op1s_64 = op1s;
  int64_t op2s_64 = op2s;
  int64_t product = op1s_64*op2s_64;
  regs.hi = (product >> 32) & 0XFFFFFFFF ;
  regs.lo = product & 0xFFFFFFFF;
}

void compiler::MULTU()
{
  uint64_t op1_64 = op1;
  uint64_t op2_64 = op2;
  uint64_t product = op1_64*op2_64;
  regs.hi = (product >> 32) & 0XFFFFFFFF ;
  regs.lo = product & 0xFFFFFFFF;
}

void compiler::OR() {regs.write(rd, (op1|op2));}

void compiler::SLL() {regs.write(rd, (op2*std::pow(2,shamt)));}

void compiler::SLLV() {regs.write(rd, (op2*std::pow(2,(op1&0x1F))));}

void compiler::SLT()
{
  if (op1s < op2s) regs.write(rd, 0x1);
  else regs.write(rd, 0x0);
}

void compiler::SLTU()
{
  if (op1 < op2)  regs.write(rd, 0x1);
  else regs.write(rd, 0x0);
}

void compiler::SRA() {regs.write(rd, (op2s>>shamt));}

void compiler::SRAV() {regs.write(rd, (op2s >> op1));}

void compiler::SRL() {regs.write(rd, (op2/std::pow(2,shamt)));}

void compiler::SRLV() {regs.write(rd, (op2/std::pow(2,(op1&0x1F))));}

void compiler::SUB()
{
  if(((op1s <= 0) && (op2s > 0) && (op1s - op2s >= 0)) || ((op1s >= 0) && (op2s < 0) && (op1s - op2s <= 0)) )
  {
    std::exit(-10);
  }
  regs.write(rd, (op1s - op2s));
}

void compiler::SUBU() {regs.write(rd, op1 - op2);}


void compiler::XOR() {regs.write(rd, op1^op2);}
