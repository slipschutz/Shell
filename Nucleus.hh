
#include <iostream>
#include <string>
#include <vector>
#include "Shell.hh"
using namespace std;


class Nucleus {

public:

  Nucleus();
  Nucleus(int a,int z);
  virtual ~Nucleus();

  inline void SetAZ(int a,int z){A=a;Z=z;}


  void Draw();

private:
  int A;//Mass number
  int Z;//Charge
  void DefineShells();
  vector <Shell> theShellOrder;
  vector <Shell> theProtonShells;
  vector <Shell> theNeutronShells;
  void Fill();
};
