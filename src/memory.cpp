#include "memory.hpp"
#include <iostream>
#include <fstream>

memory::memory(std::string name_bin)
{
  //std::cout<< "Initialising memory\n";
  //std::cout<< "Initialising data\n";

  ADDR_DATA.resize(0x4000000);
  //std::cout<< "Initialising insts\n";

  ADDR_INSTR.resize(0x1000000);

  std::fill(ADDR_DATA.begin(), ADDR_DATA.end() , 0);
  //std::cout<< "data zeroed\n";
  std::fill(ADDR_INSTR.begin(), ADDR_INSTR.end() , 0);
  //std::cout<< "Insts zeroed\n";

  std::ifstream file_name(name_bin.c_str(), std::ifstream::binary);
  //std::cout<<"file is loaded\n";

  if(!file_name.is_open())
  {
    //std::cout<<"file can't be open\n";
    std::exit(-21);
  }

  //std::cout<<"file is open\n";
  file_name.seekg(0, std::ios::end);
  int size = file_name.tellg(); //tells the size of file
  char bin_array [size];
  file_name.seekg(0, std::ios::beg); //put the cursor back to 0
  file_name.read (bin_array, size); //read the file
  //std::cout<<"file is stored in array\n";
  //std::cout<< sizeof(bin_array) << std::endl;
  //std::cout << "the entire file content is in memory\n";
  file_name.close();
  int num_instructions = sizeof(bin_array)/4;
  for(int i = 0; i < size; i++){
    //std::cout << bin_array[i] << std::endl;
  }
  int ar_i=0;
  for (int i=0;i<num_instructions;i++)
  {
    ar_i=i*4;
    ADDR_INSTR[i] = ((bin_array[ar_i]<<24)&0xFF000000)|((bin_array[ar_i+1]<<16)&0x00FF0000)|((bin_array[ar_i+2]<<8)&0x0000FF00)|((bin_array[ar_i+3])&0x000000FF);
    std::cout << std::hex<< ADDR_INSTR[i] << std::endl;
  }

  /*for(int i = 0; i < ADDR_INSTR.size(); i ++)
  {
    //if(ADDR_INSTR[i]!=0)
    //{
      std::cout << ADDR_INSTR[i] << " ";
    }
  }*/

}

int32_t memory::load_from_memory(int index)
{
  //CHECKING FOR GETCHAR
  if((index>=0x30000000)&&(index<0x30000004))//getc
  {
    if(index==0x30000000)
    {
      int data_in = std::getchar();
      if(std::cin.eof())
      {
        return 0xFFFFFFFF;
      }
      if(!std::cin.good())
      {
        std::exit(-21);
      }
      return (data_in);//how to return char from the function
    }
    else
    {
      std::exit(-11);
    }
  }

  //RUNNNING THE NORMAL INSTRUCTION
  if((index%4 == 0) && (index>=0x20000000) && (index<0x24000000) )//this is only loading word so should only call from the start
  {
    uint32_t Index_actual = (index-0x20000000);
    return (((int32_t(ADDR_DATA[Index_actual]<<24))&0xFF000000)|((int32_t(ADDR_DATA[Index_actual+1]<<16))&0x00FF0000)|((int32_t(ADDR_DATA[Index_actual+2])<<8)&0x0000FF00)|(int32_t(ADDR_DATA[Index_actual+3])&0x000000FF));
  }
  else
  {
    std::exit(-11); //memory exception
  }
}

int32_t memory::load_byte_from_memory(int index)
{
  //CHECKING FOR GETCHAR
  if((index>=0x30000000)&&(index<0x30000004))//getc
  {
    char data_in = std::getchar();
    if(std::cin.eof())
    {
      return 0xFF;
    }
    if(!std::cin.good())
    {
      std::exit(-21);
    }
    if(index==0x30000003)
    {
      return int32_t(data_in);//how to return char from the function
    }
    return 0x00000000;
  }

  //RUNNINNG NORMAL INSTRUCTIONN
  if((index>=0x20000000) && (index<0x24000000))//check if we are only getting the least significant byte
  {
    uint32_t Index_actual = (index-0x20000000);
    //int32_t Sign_ext_byte = ADDR_DATA[Index_actual];
    return (int32_t)ADDR_DATA[Index_actual];
  }
  else
  {
    std::exit(-11);
  }
}

uint32_t memory::load_unsigned_byte_from_memory(int index)
{
  //CHECKING FOR GETCHAR
  if((index>=0x30000000)&&(index<0x30000004))//getc
  {
    char data_in = std::getchar();
    if(std::cin.eof())
    {
      return 0xFF;
    }
    if(!std::cin.good())
    {
      std::exit(-21);
    }
    if(index==0x30000003)
    {
      return (int32_t(data_in)&0x000000FF);//how to return char from the function
    }
    return 0x00000000;
  }

  //RUNNING NORMAL INSTRUCTION
  if((index>=0x20000000) && (index<0x24000000))
  {
    uint32_t Index_actual = (index-0x20000000);
    //uint32_t zero_ext_byte = int32_t(ADDR_DATA[Index_actual])&0x000000FF;
    return uint32_t(int32_t(ADDR_DATA[Index_actual])&0x000000FF);
  }
  else
  {
    std::exit(-11);
  }
}

int32_t memory::load_half_word_from_memory(int index)
{
  //CHECKING FOR GETCHAR
  if((index>=0x30000000)&&(index<0x30000004))//getc
  {
    if((index==0x30000000) && (index==0x30000002))
    {
      char data_in = std::getchar();
      if(std::cin.eof())
      {
        return 0xFFFF;
      }
      if(!std::cin.good())
      {
        std::exit(-21);
      }
      if(index==0x30000002)
      {
        return (int32_t)data_in;//how to return char from the function
      }
      return 0x00000000;
    }
    else
    {
      std::exit(-11);
    }
  }

  //RUNNING NORMAL INNSTRUCTION
  if((index>=0x20000000) && (index<0x24000000) && (index%2==0))
  {
    uint32_t Index_actual = (index-0x20000000);
    int16_t sign_ext_halfword = (((ADDR_DATA[Index_actual]<<8)&0xFF00)|(ADDR_DATA[Index_actual+1]&0xFF));
    return (int32_t)sign_ext_halfword;
  }
  else
  {
    std::exit(-11);
  }
}

uint32_t memory::load_unsigned_half_word_from_memory(int index)
{
  //CHECKING FOR GETCHAR
  if((index>=0x30000000)&&(index<0x30000004))//getc
  {
    if((index==0x30000000) && (index==0x30000002))
    {
      char data_in = std::getchar();
      if(std::cin.eof())
      {
        return 0xFFFF;
      }
      if(!std::cin.good())
      {
        std::exit(-21);
      }
      if(index==0x30000002)
      {
        return (int32_t(data_in)&0x000000FF);//how to return char from the function
      }
      return 0x00000000;
    }
    else
    {
      std::exit(-11);
    }
  }

  //RUNNING NORMAL INNSTRUCTION
  if((index>=0x20000000) && (index<0x24000000) && (index%2==0))
  {
    uint32_t Index_actual = (index-0x20000000);
    return (int32_t((int16_t(ADDR_DATA[Index_actual]<<8)&0xFF00)|(int16_t(ADDR_DATA[Index_actual+1])&0xFF))&0xFFFF);//CHECK*************************
  }
  else
  {
    std::exit(-11);
  }
}

int32_t memory::load_word_right_from_memory(int index)
{
  if((index>=0x20000000) && (index<0x24000000))
  {
    uint32_t Index_actual = (index-0x20000000);
    int rem = index%4;
    if(rem==0)
    {
      return (((ADDR_DATA[Index_actual]<<24)&0xFF000000)|((ADDR_DATA[Index_actual+1]<<16)&0x00FF0000)|((ADDR_DATA[Index_actual+2]<<8)&0x0000FF00)|(ADDR_DATA[Index_actual+3]&0x000000FF));
    }
    else if(rem==1)
    {
      return(int32_t(ADDR_DATA[Index_actual+3])&0x000000FF);
    }
    else if (rem==2)
    {
      return (int32_t(((ADDR_DATA[Index_actual+2]<<8)&0x0000FF00)|(ADDR_DATA[Index_actual+3]&0x000000FF))&0x0000FFFF);
    }
    else
    {
      return (int32_t(((ADDR_DATA[Index_actual+1]<<16)&0x00FF0000)|((ADDR_DATA[Index_actual+2]<<8)&0x0000FF00)|(ADDR_DATA[Index_actual+3]&0x000000FF))&0x00FFFFFF);
    }
  }
  else
  {
    std::exit(-11);
  }
}

int32_t memory::load_word_left_from_memory(int index)
{

  if((index>=0x20000000) && (index<0x24000000))
  {
    uint32_t Index_actual = (index-0x20000000);
    int rem = index%4;
    if(rem==0)
    {
      return (((ADDR_DATA[Index_actual]<<24)&0xFF000000)|((ADDR_DATA[Index_actual+1]<<16)&0x00FF0000)|((ADDR_DATA[Index_actual+2]<<8)&0x0000FF00)|(ADDR_DATA[Index_actual+3]&0x000000FF));
    }
    else if(rem==3)
    {
      return(int32_t(ADDR_DATA[Index_actual]<<24)&0xFF000000);
    }
    else if (rem==2)
    {
      return (int32_t(((ADDR_DATA[Index_actual]<<24)&0xFF000000)|((ADDR_DATA[Index_actual+1]<<16)&0x00FF0000))&0xFFFF0000);
    }
    else
    {
      return (int32_t(((ADDR_DATA[Index_actual]<<24)&0xFF000000)|((ADDR_DATA[Index_actual+1]<<16)&0x00FF0000)|((ADDR_DATA[Index_actual+2]<<8)&0x0000FF00))&0xFFFFFF00);
    }
  }
  else
  {
    std::exit(-11);
  }
}

void memory::store_to_memory(int index, int32_t value)
{
  //CHECKING FOR PUTCHAR
  if(index==0x30000004){
    char data_out= int8_t(value&0xFF);
    if(!std::cout.good())
      std::exit(-21);
    std::putchar(data_out);//how to return char from the function
    return;
  }

  //RUNNINNG NORMAL INSTRUCTION
  if ((index%4 == 0) && (index>=0x20000000) && (index<0x24000000))
  {
    uint32_t Index_actual = (index-0x20000000);
    ADDR_DATA[Index_actual] = int8_t((value&0xFF000000)>>24);
    ADDR_DATA[Index_actual+1] = int8_t((value&0xFF0000)>>16);
    ADDR_DATA[Index_actual+2] = int8_t((value&0xFF00)>>8);
    ADDR_DATA[Index_actual+3] = int8_t(value&0xFF);
  }
  else  std::exit(-11); // memory exception
}

void memory::store_byte_to_memory(int index, int8_t value)
{
  //CHECKING FOR PUTCHAR
  if((index>=0x30000004)&&(index<0x30000008))//putc
  {
      char data_out= value&0xFF;
      if(!std::cout.good())
      {
        std::exit(-21);
      }
      if(index==0x30000007)
      {
        std::putchar(data_out);//how to return char from the function
      }
      else
      {
        std::putchar(0);
      }
<<<<<<< HEAD
      return;
  }
=======
    }
>>>>>>> 1de5266c809bb06ce44f0ed3509b8d7d897061d8

  //RUNNNING NORMAL INSTRUCTION
  if ((index>=0x20000000) && (index<0x24000000))
  {
    uint32_t Index_actual = (index-0x20000000);
    ADDR_DATA[Index_actual] = value;
  }
  else
  {
    std::exit(-11); // memory exception
  }
}

void memory::store_halfword_to_memory(int index, int16_t value)
{
  //CHECKING FOR PUTCHAR
  if((index>=0x30000004)&&(index<0x30000008))//putc
  {
      if((index==0x30000004) || (index==0x30000006))
      {
        char data_out= int8_t(value&0xFFFF);
        if(!std::cout.good())
        {
          std::exit(-21);
        }
        if(index==0x3000006)
        {
          std::putchar(data_out);//how to return char from the function
        }
        else
        {
            std::putchar(0);
        }
        return;
      }
      else
      {
        std::exit(-11);
      }
  }


  //RUNNNING NORMAL INSTRUCTION
  if ((index>=0x20000000) && (index<0x24000000) && (index%2==0))
  {
    uint32_t Index_actual = (index-0x20000000);
    ADDR_DATA[Index_actual] = int8_t((value&0xFF00)>>8);
    ADDR_DATA[Index_actual+1] = int8_t((value&0xFF));
  }
  else
  {
    std::exit(-11); // memory exception
  }
}

uint32_t memory::readInstruction(uint32_t PC)
{
  if((PC != 0x0) && ((PC < 0x11000000) && (PC >= 0x10000000)))
  {
    uint32_t indexPC=(PC-0x10000000)/4;
    return ADDR_INSTR[indexPC];
  }
  else
  {
    std::exit(-11);
  }
}
