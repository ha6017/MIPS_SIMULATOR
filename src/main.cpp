//#include "compiler.hpp"
#include <string>
#include<sstream>

int main(int argc, char const *argv[])
{
  std::string name_bin = "check2.bin";
  if (argc==2) name_bin = argv[1];

  compiler comp(name_bin);// on making an object of class compiler. we first call the constructor of class compiler.
  comp.run();

  return 0;
}
