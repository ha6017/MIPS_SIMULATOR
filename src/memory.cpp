#include "memory.hpp"



#include <iostream>

#include <fstream>



memory::memory(std::string name_bin)

{

  std::fill(ADDR_DATA, ADDR_DATA + 0x4000000, 0);

  std::fill(ADDR_INSTR, ADDR_INSTR + 0x1000000, 0);

  //std::fill(REG_VECTOR, REG_VECTOR + 32, 0);// WHY IS THIS HERE, WE INITIALISED IT IN CLASS REGISTER MAP?



  std::ifstream filename (name_bin, std::ios::out|std::ios::binary|std::ios::ate);



  if (filename.is_open())

  {



    //filename.seekg (0, ios::end); //put the cursor to end of file

    int size = filename.tellg(); //tells the size of file

    //cout<<size<<endl;

    char bin_array [size];

    //memblock = new unsigned char [size]; //size of array

    filename.seekg (0, std::ios::beg); //put the cursor back to 0

    filename.read (bin_array, size); //read the file

    std::cout<< sizeof(bin_array) << std::endl;

    std::cout << "the entire file content is in memory";



    int num_instructions = sizeof(bin_array)/4;



    int ar_i=0;



    for (int i=0;i<num_instructions;i++)

    {

      ar_i=i*4;

      ADDR_INSTR[i] = (bin_array[ar_i]>>24)|(bin_array[ar_i+1]>>16)|(bin_array[ar_i+2]>>8)|(bin_array[ar_i+3]);

    }

  }



  else std::exit(-21);

}



uint32_t memory::load_from_memory(int index)

{

  if((index%4 == 0) && (index>=0x20000000) && (index<0x24000000) )//this is only loading word so should only call from the start

  {

    uint32_t Index_actual = (index-0x20000000);

    return ((ADDR_DATA[Index_actual]>>24)|(ADDR_DATA[Index_actual+1]>>16)|(ADDR_DATA[Index_actual+2]>>8)|(ADDR_DATA[Index_actual+3]));

  }

  else

  {

    std::exit(-11); //memory exception

  }

}



int32_t memory::load_byte_from_memory(int index)

{

  if((index>=0x20000000) && (index<0x24000000))

  {

    uint32_t Index_actual = (index-0x20000000);

    int32_t Sign_ext_byte = ADDR_DATA[Index_actual];

    return Sign_ext_byte;

  }

  else

  {

    std::exit(-11);

  }

}



uint32_t memory::load_unsigned_byte_from_memory(int index)

{

  if((index>=0x20000000) && (index<0x24000000))

  {

    uint32_t Index_actual = (index-0x20000000);

    uint32_t zero_ext_byte = int32_t(ADDR_DATA[Index_actual])&0x000000FF;

    return zero_ext_byte;

  }

  else

  {

    std::exit(-11);

  }

}



int32_t memory::load_half_word_from_memory(int index)

{

  if((index>=0x20000000) && (index<0x24000000) && (index%2==0))

  {

    uint32_t Index_actual = (index-0x20000000);

    int32_t sign_ext_halfword = (ADDR_DATA[Index_actual]>>8)|(ADDR_DATA[Index_actual+1]);

    return sign_ext_halfword;

  }

  else

  {

    std::exit(-11);

  }

}



uint32_t memory::load_unsigned_half_word_from_memory(int index)

{

  if((index>=0x20000000) && (index<0x24000000) && (index%2==0))

  {

    uint32_t Index_actual = (index-0x20000000);

    //uint32_t sign_ext_halfword = (ADDR_DATA[Index_actual]>>8)|(ADDR_DATA[Index_actual+1]);

    return (uint32_t((ADDR_DATA[Index_actual]>>8)|(ADDR_DATA[Index_actual+1]))&0xFFFF);

  }

  else

  {

    std::exit(-11);

  }

}



void memory::store_to_memory(int index, uint32_t value)

{

  if ((index%4 == 0) && (index>=0x20000000) && (index<0x24000000))

  {

    uint32_t Index_actual = (index-0x20000000);

    ADDR_DATA[Index_actual] = (value&0xFF000000)<<24;

    ADDR_DATA[Index_actual+1] = (value&0xFF0000)<<16;

    ADDR_DATA[Index_actual+2] = (value&0xFF00)<<8;

    ADDR_DATA[Index_actual+3] = value&0xFF;

  }

  else

  {

    std::exit(-11); // memory exception

  }

}



void memory::store_byte_to_memory(int index, int8_t value)

{

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



uint32_t* memory::readInstruction(uint32_t PC)

{
  if((PC != 0x0) && ((PC <= 0x11000000) && (PC >= 0x10000000)))
  {
    uint32_t indexPC=(PC-0x10000000)/4;

    return &ADDR_INSTR[indexPC];
  }
  else
  {
    std::exit(-11);
  }
}
