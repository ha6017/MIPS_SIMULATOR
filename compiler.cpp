#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <inttypes.h>

using namespace std;
char ijkInstruction(uint32_t instructions);

int main(){

  vector<uint32_t> instructions;
  instructions.push_back(1431655765);
  instructions.push_back(3444921685);
  instructions.push_back(21685);
  instructions.push_back(178956970);
  instructions.push_back(179284650);
  instructions.push_back(22369621);
  instructions.push_back(4283782485);

  for(int i = 0; i < instructions.size(); i ++){
    char opcode = ijkInstruction(instructions[i]);
    cout << "The opcode of " << instructions[i] << " is " << opcode << endl;
  }

  return 0;
}

char ijkInstruction(uint32_t instruction){
  int compared = instruction&0xFC000000;
  cout << compared << endl;
  //case compared to 000000 is true --> return R
  if((instruction&0xFC000000) == 0x0){
    return 'R';
  }//case compared to 00001 is true --> return J
  else if((instruction&0xFC000000) == 0x8000000){
    return 'J';
  }//else --> return I
  else{
    return 'I';
  }
}

void Rinstructions(uint32_t instruction){
  int function = instruction&0x3F
  switch(function){
    case 32:
      //ADD
      break;
    case 33:
      //ADDU
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

void Iinstruction(uint32_t instruction){
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
    case 5:
      //BNE
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
    case 33:
      //LH
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

void Jinstruction(uint32_t instruction){
  int opcode = instruction&0xFC000000;
  if(opcode == 2){
    //J
  }else{
    //JAL
  }
}
