#include "compiler.hpp"
#include <string>
#include <sstream>
#include<iostream>



int main(int argc, char* argv[]){
  //std::cout << "Compiled1" << std::endl;

  std::string name_bin = "addi_test1.bin";
  if (argc!=0) name_bin = argv[1];

  compiler comp(name_bin);
  //std::cout<<"checkpoint1\n";
  comp.run();
  //std::cout << "Compiled" << std::endl;


  return 0;
}
