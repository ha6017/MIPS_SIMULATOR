#include "compiler.hpp"

int main(int argc, char const *argv[]){

  string name_bin = "check2.bin";
  if (argc==2) name_bin = argv[1];

  compiler comp(name_bin);
  comp.run();


  return 0;
}
