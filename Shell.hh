
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
  inline string GetName(){return _ShellName;}
  inline double GetJ(){return _J;}
  inline double Getl(){return _l;}
  inline double Getn(){return _n;}  

  void PushNucleon();
  

private:
  int _MaxOccupancy;
  int _Occupancy;
  double _NormOccupancy;
  string _ShellName; 

  double _J;
  double _l;
  double _n;
  double num;
public:
  ClassDef(Shell,1);
};
#endif
