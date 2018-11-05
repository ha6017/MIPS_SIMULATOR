#include <iostream>
#include <fstream>
#include <vector>
#include<cmath>

using namespace std;

void RIJ_INSTRUCTION(uint32_t &PC, vector<uint32_t> &vect, vector<int32_t> &register_vector);

void init_mem(vector<uint32_t> &vect)
{
  for(int i=0; i<sizeof(vect); i++)
  {
    vect[i]=0;
  }
}

void init_mem_2(vector<int32_t> &vect)
{
  for(int i=0; i<sizeof(vect); i++)
  {
    vect[i]=0;
  }
}


void R_Instr(uint32_t &PC, vector<uint32_t> &vect, vector<int32_t> &register_vector )
{
  uint32_t copy_PC=(PC-0x10000000)/4;
  uint32_t instruction = vect[copy_PC];
  uint32_t Fn_code = instruction&0x3F;
  //cout<<"Fucntion code is= "<<Fn_code<<endl;
  uint32_t shamt = instruction&0x7C0;
  //shamt=shamt<<6;
  //cout<<"Shamt is= "<<shamt<<endl;
  uint32_t rd= instruction&0xF800;
  //rd=rd<<11;
  //rd=convertBinaryToDecimal(rd);
  rd=rd/pow(2,11);
  //uint32_t *rd_pointer= &register_vector[rd];
  //cout<<"RD is= "<<rd<<endl;
  uint32_t rt= instruction&0x1F0000;
  rt=rt/pow(2,16);
  //rs=rs<<16;
  //rs=convertBinaryToDecimal(rs);
  //cout<<"rt is= "<<rt<<endl;
  //uint32_t *rt_pointer= &register_vector[rt];
  uint32_t rs= instruction&0x3E00000;
  rs=rs/pow(2,21);
  //rt=rt<<21;
  //rt=convertBinaryToDecimal(rt);
  //cout<<"rs is = "<<rs<<endl;
  //uint32_t *rs_pointer= &register_vector[rs];

  switch(Fn_code){
    case 32:
      //ADD
      break;
    case 33:
      //ADDU
      register_vector[rd]=register_vector[rs]+register_vector[rt];
      //cout<<"\nregister_vector[rd] = "<<register_vector[rd]<<endl;
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
      PC = PC + 4;
      RIJ_INSTRUCTION(PC, vect, register_vector);
      PC = register_vector[rs] - 4;
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

void I_Instr(uint32_t &PC, uint32_t instruction){
  int opcode = instruction&0xFC000000;
  switch(opcode){
    case 8:
      //ADDI
      break;
    case 9:
      //ADDIU
      break;
    case 12:
      //ANDI
      break;
    case 4:
      //BEQ
      break;
    case 20:
      //BEQL
      break;
    case 1:
      if((instruction&0x1F0000) == 1){
        //BGEZ
      }else if((instruction&0x1F0000) == 19){
        //BGEZALL
      }else if ((instruction&0x1F0000) == 3){
        //BGEZL
      }else if ((instruction&0x1F0000) == 0){
        //BLTZ
      }else if ((instruction&0x1F0000) == 32){
        //BLTZAL
      }else if ((instruction&0x1F0000) == 34){
        //BLTZALL
      }else if ((instruction&0x1F0000) == 2){
        //BLTZL
      }else if ((instruction&0x1F0000) == 12){
        //TEQI
      }else if ((instruction&0x1F0000) == 8){
        //TGEI
      }else if ((instruction&0x1F0000) == 9){
        //TGEIU
      }else if ((instruction&0x1F0000) == 10){
        //TLTI
      }else if ((instruction&0x1F0000) == 11){
        //TLTIU
      }else if ((instruction&0x1F0000) == 14){
        //TNEI
      }
      break;
    case 33:
      //BGEZAL
      break;
    case 7:
      //BGTZ
      break;
    case 23:
      //BGTZL
      break;
    case 6:
      //BLEZ
      break;
    case 22:
      //BLEZL
      break;
    case 5:
      //BNE
      break;
    case 21:
      //BNEL
      break;
    case 24:
      //DADDI
      break;
    case 25:
      //DADDIU
      break;
    case 32:
      //LB
      break;
    case 36:
      //LBU
      break;
    case 55:
      //LD
      break;
    case 26:
      //LDL
      break;
    case 27:
      //LDR
      break;
    case 37:
      //LHU
      break;
    case 48:
      //LL
      break;
    case 52:
      //LLD
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
    case 39:
      //LWU
      break;
    case 13:
      //ORI
      break;
    case 51:
      //PREF
      break;
    case 56:
      //SC
      break;
    case 60:
      //SCD
      break;
    case 63:
      //SD
      break;
    case 44:
      //SDL
      break;
    case 45:
      //SD
      break;
    case 41:
      //SH
      break;
    case 10:
      //SLTI
      break;
    case 11:
      //SLTIU
      break;
    case 43:
      //SW
      break;
    case 42:
      //SWL
      break;
    case 46:
      //SWR
      break;
    case 14:
      //XORI
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






void J_Instr(uint32_t &PC, uint32_t instruction )
{
  int opcode = instruction&0xFC000000;
  if(opcode == 2){
    //JR
  }else{
    //JAL
  }
}


void RIJ_INSTRUCTION(uint32_t &PC, vector<uint32_t> &vect, vector<int32_t> &register_vector)
{
  //cout<<"\nvalue of PC in RIJ ="<<*PC<<endl;
  //cout<<"\nPC ="<<PC<<endl;
  uint32_t copy_PC=(PC-0x10000000)/4;
  //cout<<"\nPC Copy ="<<copy_PC<<endl;
  //cout << "value from vect = " << vect[copy_PC] << endl;
  //cout<<"\nvalue of copy_PC intially ="<<copy_PC<<endl;
  int compare = vect[copy_PC]&0xFC000000;
  //int compare = vect[copy_PC]&0xFFFFFFFF;
  //cout << "compare ="<<compare << endl;
  //case compared to 000000 is true --> return R
  if(compare == 0x0){
    R_Instr(PC, vect, register_vector);
  }//case compared to 0001 is true --> return J
  else if(compare == 0x8000000){
    J_Instr(PC, vect[copy_PC]);
  }//else --> return I
  else{
    I_Instr(PC, vect[copy_PC]);
  }
  PC=PC+4;
  //cout<<"NEW value of PC intially ="<<*PC<<endl;
}

void run_simulator(uint32_t &PC, vector<uint32_t> &vect, vector<int32_t> &register_vector)
{
  while((PC != 0x0) || ((PC <= 0x11000000) && (PC >= 0x10000000))) // ADD no-op[ cases]
  {
    RIJ_INSTRUCTION(PC, vect, register_vector);
    // if PC has reached end of instruction memory or points to a null instruction
    //if()

  }
  /*int count=0;
  while(count<=10)
  {
    RIJ_INSTRUCTION(PC, vect, register_vector);
    count++;
  }*/
}


int main (int argc, char const *argv[]) {

  /*string name_bin = "check2.bin";

  if (argc==2) name_bin = argv[1];*/

  vector<uint32_t> ADDR_INSTR(0x1000000);
  vector<uint32_t> ADDR_DATA(0x4000000);
  vector<int32_t> REG(32);

  init_mem(ADDR_DATA);
  init_mem(ADDR_INSTR);
  init_mem_2(REG);

  /*REG[1] = 2;
  REG[3] = 5;
  REG[4] = 1;
  REG[5] = 9;
  REG[6] = 0x10000010;*/

  uint32_t PC=0x10000000;
  //cout<<"value of PC intially ="<<*PC<<endl;

  /*ADDR_INSTR[0]=(0x611021);// reg2=reg1+reg3
  ADDR_INSTR[1]=(0xC00008);// JR reg6
  ADDR_INSTR[2]=(0x830821);// reg1=reg3+reg4
  ADDR_INSTR[3]=(0xA10821);// reg5=reg1+reg1
  ADDR_INSTR[4]=(0xA52821);//reg3=reg3+rweg3
  ADDR_INSTR[5]=(0x8);// jr zero*/
  string name_bin = "check2.bin";

  if (argc==2) name_bin = argv[1];

  ifstream filename (name_bin, ios::out|ios::binary|ios::ate);
  if (filename.is_open())
  {

    //filename.seekg (0, ios::end); //put the cursor to end of file
    int size = filename.tellg(); //tells the size of file
    //cout<<size<<endl;
    char bin_array [size];
    //memblock = new unsigned char [size]; //size of array
    filename.seekg (0, ios::beg); //put the cursor back to 0
    filename.read (bin_array, size); //read the file
    cout<< sizeof(bin_array) <<endl;
    cout << "the entire file content is in memory";

    int num_instructions = sizeof(bin_array)/4;

    int ar_i=0;

    for (int i=0;i<num_instructions;i++)
    {
      ar_i=i*4;
      ADDR_INSTR[i] = (bin_array[ar_i]>>24)|(bin_array[ar_i+1]>>16)|(bin_array[ar_i+2]>>8)|(bin_array[ar_i+3]);
    }
  }
  else cout << "Unable to open file";

  run_simulator(PC,ADDR_INSTR, REG);

  filename.close();
  return 0;
}
