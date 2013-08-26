
#ifndef __NUCLEUS_HH
#define __NUCLEUS_HH

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "Shell.hh"
#include "State.hh"
using namespace std;


class Nucleus : public State{

public:

  Nucleus();
  Nucleus(int a,int z);
  virtual ~Nucleus();

  void SetAZ(int a,int z){A=a;Z=z;this->State::SetAZ(a,z);Fill();}

  inline vector<Shell> GetProtonShells(){return theProtonShells;}
  inline vector<Shell> GetNeutronShells(){return theNeutronShells;}

  void Draw();
  
  inline int GetA(){return A;}
  inline int GetZ(){return Z;}

  int GetNextShellClosure(int theClosure);

  vector <Shell> GetModelSpaceZShells();
  vector <Shell> GetModelSpaceNShells();
  
  void PrintModelSpaces();
  Shell GetShell(int NumNucleons);
  int GetShellIndex(int NumNucleons);

  void DumpShellClosureMap();
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
public:
  ClassDef(Nucleus,1);
};

#endif
