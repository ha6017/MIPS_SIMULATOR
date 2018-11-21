#include "register_map.hpp"
#include<iostream>

register_map::register_map()
{
  for (int i=0;i<32;i++){
    REG_VECTOR[i]=0;
    //std::cout<<"reg_vect["<<i<<"]="<<REG_VECTOR[i]<<std::endl;
  }
  //std::cout<<"the reg vect loaded with 0\n";
}

void register_map::write(int index, uint32_t data){
  if((index > 0) && (index < 32)){
    REG_VECTOR[index] = data;
  }
  else if(index==0)
  {
    REG_VECTOR[index]=0;
  }
  else{
    //say not valid
    std::exit(-11);
  }
}
/*void register_map::setRegisters(){
  memset(REG_VECTOR, 0, 32);
}*/

uint32_t register_map::read(int index)
{
  if((index >= 0) && (index < 32))
  {
    return REG_VECTOR[index];
  }
  else
  {
    std::exit(-11);
  }

}
/*void register_map::printRegisters(){
  for (int i=0;i<32;i++){
    std::cout<<"reg_vect["<<i<<"]="<<REG_VECTOR[i]<<std::endl;
  }*/
//}
