#ifndef REGISTER_MAP_HPP
#define REGISTER_MAP_HPP

#include <cmath>

class register_map
{
private:

  int32_t REG_VECTOR[32];

public:
  register_map();
  //void setRegisters();

  uint32_t PC = 0x10000000;//can not start it from 0
  uint32_t hi = 0;
  uint32_t lo = 0;

  void write(int index, uint32_t data);
  uint32_t read(int index);

};

#endif
