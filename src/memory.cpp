#include "memory.hpp"

#include <iostream>
#include <fstream>

memory::memory(std::string name_bin){
  ADDR_DATA = {};
  ADDR_INSTR = {};
  REG_VECTOR = {};

  std::ifstream filename (name_bin, std::ios::out|std::ios::binary|std::ios::ate);

  if (filename.is_open())
  {

    //filename.seekg (0, ios::end); //put the cursor to end of file
    int size = filename.tellg(); //tells the size of file
    //cout<<size<<endl;
    char bin_array [size];
    //memblock = new unsigned char [size]; //size of array
    filename.seekg (0, ios::beg); //put the cursor back to 0
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
  else std::cout << "Unable to open file";

}

uint32_t getInstruction(uint32_t PCindex){
  return ADDR_INSTR[PCindex];
}
uint32_t getData(uint32_t PC){
  return ADDR_DATA[PCindex];
}
int32_t getRegister(uint32_t PCindex){
  return REG_VECTOR[PCindex];
}
