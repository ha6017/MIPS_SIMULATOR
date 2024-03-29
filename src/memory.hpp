#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <vector>
#include <stdint.h>
#include <string>



class memory{
private:
  //uint32_t ADDR_INSTR[0x1000000];
  //uint8_t ADDR_DATA[0x4000000];
  std::vector<uint32_t> ADDR_INSTR;
  std::vector<uint8_t> ADDR_DATA;
  int num_instructions;

public:
  memory(std::string binaryfile);
  //void setMemory(std::string name_bin);
  uint32_t readInstruction(uint32_t PC);

  int32_t load_from_memory(int index);
  int32_t load_byte_from_memory(int index);
  uint32_t load_unsigned_byte_from_memory(int index);
  int32_t load_half_word_from_memory(int index);
  uint32_t load_unsigned_half_word_from_memory(int index);
  int32_t load_word_right_from_memory(int index);
  int32_t load_word_left_from_memory(int index);
  int8_t load_byte_from_instruction(int index);
  int16_t load_half_word_from_instruction(int index);


  void store_to_memory(int index, int32_t value);
  void store_byte_to_memory(int index, int8_t value);
  void store_halfword_to_memory(int index, int16_t value);

  //uint32_t* data();
  //int32_t* registers();

};

#endif
