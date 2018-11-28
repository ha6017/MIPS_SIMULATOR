#ifndef REGISTER_MAP_HPP
#define REGISTER_MAP_HPP

#include <cmath>
#include <stdint.h>

class register_map{
private:

  int32_t REG_VECTOR[32];

public:
  register_map();
  uint32_t PC = 0x10000000;
  uint32_t hi = 0;
  uint32_t lo = 0;

  void write(int index, uint32_t data);
  uint32_t read(int index);
  //void printRegisters();

};

#endif
