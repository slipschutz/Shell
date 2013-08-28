
#ifndef __SHELL_HH
#define __SHELL_HH

#include <iostream>
#include <string>
#include "TObject.h"
using namespace std;

class Shell : public TObject{

public:
  Shell();
  Shell(int maxOc,string name,double j,double l, double n);
  virtual ~Shell();
  
  bool IsFull();
  
  inline int GetMaxOccupancy(){return _MaxOccupancy;}
  inline int GetOccupancy(){return _Occupancy;}
  inline double GetFullness(){return _Fullness;}
  inline double GetEmptiness(){return _Emptiness;}
  inline string GetName(){return _ShellName;}
  inline double GetJ(){return _J;}
  inline double Getl(){return _l;}
  inline double Getn(){return _n;}  
  inline double GetN() {return 2*(_n-1)+_l;}
  void PushNucleon();
  void SetEmptiness(double o){_Emptiness=o;_Fullness=1-_Emptiness;}
  void SetFullness(double f){_Fullness=f;_Emptiness=1-_Fullness;}

private:
  int _MaxOccupancy;
  int _Occupancy;
  double _Fullness;
  double _Emptiness;
  string _ShellName; 

  double _J;
  double _l;
  double _n;

public:
  ClassDef(Shell,1);
};
#endif
