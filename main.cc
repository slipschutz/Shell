



#include <iostream>
#include "Nucleus.hh"
#include <cstdlib>
int main(int argc, char** argv){
  
  Nucleus aNuc(atof(argv[1]),atof(argv[2]));
  aNuc.Draw();




  return 0;
}