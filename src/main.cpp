#include <string>
#include <sstream>

#include "compiler.hpp"

int main(int argc, char const *argv[]){

  std::string name_bin = "";
  if (argc==2) name_bin = argv[1];

  compiler comp(name_bin);
  comp.run();


  return 0;
}
