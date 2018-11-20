#include <cmath>
#include <string>

#include "compiler.hpp"

//the constructor of class compiler initialises the object mem of class memory
// which is defined as a private date member. This calls the constructor of class memory and initialises the memory.
compiler::compiler(std::string binaryfile) : mem(binaryfile), regs(){
  //regs.setRegisters();
}

void compiler::loop_avoider(){
  if((regs.PC != 0x0) && ((regs.PC <= 0x11000000) && (regs.PC >= 0x10000000))){
    uint32_t* currentInstruction = mem.readInstruction(regs.PC);
    opcode = ((*currentInstruction&0xFC000000)>>26);
    //case compared to 000000 is true --> return R
    if(opcode == 0x0){
      runRtype(*currentInstruction);
    //  R_Instruction rInst(currentInstruction, regs);
    //  rInst.runInstruction(regs);
    }//case compared to 0001 is true --> return J
    else if(opcode == 0x1){
      //J_Instruction();
      runJtype(*currentInstruction);
    }//else --> return I
    else{
      //I_Instruction iInst(currentInstruction);
      //iInst.run_I_Instruction(regs);
      runItype(*currentInstruction);
    }
    regs.PC=regs.PC+4;
    // if PC has reached end of instruction memory or points to a null instruction
    //if()
  }
}

void compiler::run(){
  while((regs.PC != 0x0) && ((regs.PC <= 0x11000000) && (regs.PC >= 0x10000000))) // ADD no-op[ cases]
  {
      compiler::loop_avoider();

  }
}

void compiler::runRtype(uint32_t instruction){
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
    case 0: SLL();  break;
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

void compiler::runJtype(uint32_t instruction){
  instr_index = instruction&0x03FFFFFF;
  if(opcode == 2){
    //J
    //new PC (PC +4) takes 4 msb
    //adds onto this the instruction index left shifted by 2
    uint32_t copyPC = ((regs.PC)&0xF0000000) + (instr_index<<2);
    //runs next instruction
    loop_avoider();
    //PC = new value calculated before
    regs.PC = copyPC;
  }else{
    //JAL
    //writes link into register 31
    regs.write(31, regs.PC + 8);
    //same as J instruction from here --
    uint32_t copyPC = ((regs.PC)&0xF0000000) + (instr_index<<2);
    loop_avoider();
    regs.PC = copyPC;
  }
}

void compiler::runItype(uint32_t instruction){
  immediate = instruction&0xFFFF;
  rt= ((instruction&0x1F0000)>>16);
  rs= ((instruction&0x3E00000)>>21);
  signExtImmediate = int32_t(immediate << 16) >> 16;
  //instr =instruction;
  op1s = regs.read(rs);
  op2s = regs.read(rt);
  op1 = regs.read(rs);
  op2 = regs.read(rt);

  uint32_t copy_pc;
  int16_t val16;
  int8_t val;

  switch(opcode){
    case 8:
      //ADDI
      if(((op1s > 0) && (signExtImmediate > 0) && (op1s + signExtImmediate <= 0)) || ((op1s < 0) && (signExtImmediate < 0) && (op1s + signExtImmediate >= 0))){
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
    case 12:// CHECK for 0 extend
      //ANDI
      regs.write(rd, op1&(uint32_t(immediate)&0xFFFF));
      break;
    case 4:
      //BEQ
      copy_pc = regs.PC;
      if (op1 == op2)
      {
        regs.PC=regs.PC+4;
        compiler::loop_avoider();
        regs.PC = copy_pc + (signExtImmediate << 2);
      }
      break;
    case 1:
      copy_pc = regs.PC;
      if ((rt == 0)&&(op1s < 0)) //bltz
      {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);

      }
      else if((rt==16) && (op1s < 0)) //bltzal
      {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);
          regs.write(31,(copy_pc+8));

      }
      else if ((rt == 1) && (op1s >= 0)) //bgez
      {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);

      }
      else if((rt==17) && (op1s >= 0)) //bgezal
      {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);
          regs.write(31,(copy_pc+8));
      }
        break;
      case 7:
        //BGTZ
        copy_pc = regs.PC;
        if ((op1s > 0) && (rt==0))
        {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);
        }
        break;
      case 6:
        //BLEZ
        copy_pc = regs.PC;
        if((op1s<=0) && (rt==0))
        {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);
        }
        break;
      case 5:
        //BNE
        copy_pc = regs.PC;
        if (op1 != op2)
        {
          regs.PC=regs.PC+4;
          compiler::loop_avoider();
          regs.PC = copy_pc + 4 + (signExtImmediate << 2);
        }
        break;
      case 32:
        //LB
        regs.write(rt, mem.load_byte_from_memory(regs.read(rs)+signExtImmediate));
        break;
      case 36:
        //LBU
        regs.write(rt, mem.load_unsigned_byte_from_memory(regs.read(rs)+signExtImmediate));
        break;
      case 33:
        //LH
        regs.write(rt, mem.load_half_word_from_memory(regs.read(rs)+signExtImmediate));
        break;
      case 37:
        //LHU
        regs.write(rt, mem.load_unsigned_half_word_from_memory(regs.read(rs)+signExtImmediate));
        break;
      case 15:
        //LUI
        regs.write(rt,((uint32_t(immediate)<<16)&0xFFFF0000));
        break;
      case 35:
        //LW
        regs.write(rt, mem.load_from_memory(regs.read(rs)+signExtImmediate));
        break;
      case 34:
        //LWL
        break;
      case 38:
        //LWR
        break;
      case 13:
        //ORI
        regs.write(rt,(op1|(int32_t(immediate)&0xFFFF)));
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
      case 40:
        //SB
        val = regs.read(rt)&0xFF;
        mem.store_byte_to_memory((regs.read(rs)+signExtImmediate),val);
        break;
      case 41:
        //SH
        val16 = regs.read(rt)&0xFFFF;
        mem.store_halfword_to_memory((regs.read(rs)+signExtImmediate), val16);
        break;
      case 43:
        //SW
        mem.store_to_memory((regs.read(rs)+signExtImmediate),regs.read(rt));
        break;
      case 14:
        //XORI
        regs.write(rt,(op1^(int32_t(immediate)&0xFFFF)));
        break;
    }
}

void compiler::ADD()
{
  if(((op1s > 0) && (op2s > 0) && (op1s + op2s <= 0)) || ((op1s < 0) && (op2s < 0) && (op1s + op2s >= 0)))
  {

     std::exit(-10);

  }

  regs.write(rd, op1s+op2s);

}



void compiler::ADDU(){

regs.write(rd, op1 + op2);

//cout<<"\nregister_vector[rd] = "<<register_vector[rd]<<endl;

}



void compiler::AND(){

regs.write(rd, op1 & op2);

}



void compiler::DIV(){

if (op2 == 0){

   // Operation is now undefined - don't modify hi and lo

   std::exit(-10);

}

regs.lo = op1s / op2s;

regs.hi = op1s % op2s;

}



void compiler::DIVU(){

if (op2 == 0){

   // Operation is now undefined - don't modify hi and lo

   std::exit(-10);

}

regs.lo = op1 / op2;

regs.hi = op1 % op2;

}



void compiler::JALR()
{

//save the PC and rs value before executing the branch delay

uint32_t copyPC = regs.PC;

int32_t copyrs = regs.read(rs);

regs.PC = regs.PC + 4;

compiler::loop_avoider();

regs.write(rd, copyPC + 8);

regs.PC = regs.read(copyrs);

}



void compiler::JR()
{

regs.PC = regs.PC + 4;
int32_t copyrs = regs.read(rs);

compiler::loop_avoider();

regs.PC = copyrs - 4;



}



void compiler::MFHI(){



}



void compiler::MFLO(){



}



void compiler::MTHI(){



}



void compiler::MTLO(){



}



void compiler::MULT()
{

regs.hi = (((int64_t(op1) << 32) >> 32) * ((int64_t(op2) << 32) >> 32)) >> 32;



regs.lo = ((int64_t(op1) << 32) >> 32) * ((int64_t(op2) << 32) >> 32);

}



void compiler::MULTU(){

regs.hi = (uint64_t(op1) * uint64_t(op2)) >> 32;



regs.lo = uint64_t(op1) * uint64_t(op2);



}



void compiler::OR(){

regs.write(rd, (op1|op2));

}



void compiler::SLL(){

regs.write(rd, (op2*std::pow(2,shamt)));

}



void compiler::SLLV(){

regs.write(rd, (op2*std::pow(2,op1)));

}



void compiler::SLT(){

if (op1s < op2s){

   regs.write(rd, 1);

} else {

   regs.write(rd, 0);

}

}



void compiler::SLTU(){

if (op1 < op2){

   regs.write(rd, 1);

} else {

   regs.write(rd, 0);

}

}



void compiler::SRA(){

regs.write(rd, (op2s>>shamt));

}



void compiler::SRAV(){

regs.write(rd, (op2s >> op1));

}



void compiler::SRL(){

regs.write(rd, (op2/std::pow(2,shamt)));

}



void compiler::SRLV(){

regs.write(rd, (op2/std::pow(2,op1)));

}



void compiler::SUB(){

if(((op1s < 0) && (op2s > 0) && (op1s - op2s >= 0)) || ((op1s > 0) && (op2s < 0) && (op1s - op2s <= 0))){

   // If op1 -ve, op2 +ve, result +ve

   // OR If op1 +ve, op2 -ve, result -ve

   std::exit(-10);

}

regs.write(rd, (op1s - op2s));

}



void compiler::SUBU(){

regs.write(rd, op1 - op2);

}



void compiler::XOR(){

regs.write(rd, op1^op2);

}
