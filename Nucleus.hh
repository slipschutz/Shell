
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

  Nucleus(); //Constructor defualts to A=-1 and Z=-1
  Nucleus(int a,int z);//Constructor for given A and Z
  Nucleus(int a,string s);
  virtual ~Nucleus(); //Deconstructor 

  void SetAZ(int a,int z){A=a;Z=z;this->State::SetAZ(a,z);Fill();}//Set A and Z 

  
  
  vector <Shell>* GetProtonShells(){return &theProtonShells;}//Returns the P Shells
  vector <Shell>* GetNeutronShells(){return &theNeutronShells;}//Returns the N Shells

  void Draw();

  inline int GetA(){return A;}
  inline int GetZ(){return Z;}

  int GetNextShellClosure(int theClosure);

  vector <Shell> GetModelSpaceZShells();
  vector <Shell> GetModelSpaceNShells();
  
  void PrintModelSpaces();
  Shell* GetZShell(int NumNucleons);//returns the shell in which the NumNucleons nucleon appears
  Shell* GetZShell(string name);
  Shell* GetNShell(int NumNucleons);//returns the shell in which the NumNucleons nucleon appears
  Shell* GetNShell(string name);
  int GetShellIndex(int NumNucleons);

  void DumpShellClosureMap();

#ifndef __CINT__
  inline map <pair<string,string>,double>* GetTheZCoefs(){return &theZCoefs;}
#endif

private:
  int A;//Mass number
  int Z;//Charge
  void DefineShells();
  void DefineShellClosures();
  
  void DefineAbrevMap();

  Shell *GetShell(int NumNucleons,vector<Shell>&);
  Shell *GetShell(string name,vector<Shell>&);

  map <int,int> theShellClosures;
  map <string,bool> _theDrawClosures;

  map <string,int> AbrevMap;

#ifndef __CINT__
  map <pair<string,string>,double> theZCoefs; 
#endif

  void DrawShell(Shell&,string);

  vector <Shell> theShellOrder;
  vector <Shell> theProtonShells;
  vector <Shell> theNeutronShells;
  void Fill();
public:
  ClassDef(Nucleus,1);
};

#endif
