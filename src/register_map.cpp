#include "register_map.hpp"

register_map::register_map()
{
  for (int i=0;i<32;i++)
  {
    REG_VECTOR[i]=0;
  }
}

void register_map::write(int index, uint32_t data)
{
  if((index != 0) && (index > 0) && (index < 32))
  {
    REG_VECTOR[index] = data;
  }
  else
  {
    //say not valid
    std::exit(-11);
  }

}
/*void register_map::setRegisters()
{
  memset(REG_VECTOR, 0, 32);
}*/

uint32_t register_map::read(int index)
{
  if((index != 0) && (index > 0) && (index < 32))
  {
    return REG_VECTOR[index];
  }

}
