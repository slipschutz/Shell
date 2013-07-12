
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Shell.hh"
#include "State.hh"
using namespace std;


class Nucleus : public State{

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
  void DefineShellClosures();
  
  map <int,int> theShellClosures;

  void DrawShell(Shell&,string);

  vector <Shell> theShellOrder;
  vector <Shell> theProtonShells;
  vector <Shell> theNeutronShells;
  void Fill();
};
