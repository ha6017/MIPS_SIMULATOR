#include "register_map.hpp"

void register_map::write(int index, uint32_t data){
  if((index != 0) && (index>0) && (index < 32)){
    REG_VECTOR[index] = data;
  }else{
    //say not valid
  }

}
void register_map::setRegisters(){
  memset(REG_VECTOR, 0, 32);
}
uint32_t register_map::read(int index){
  return REG_VECTOR[index];
}
