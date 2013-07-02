
#include <iostream>
#include <string>
using namespace std;

class Shell{

public:
  Shell();
  Shell(int maxOc,string name);
  virtual ~Shell();
  
  bool IsFull();
  
  inline int GetMaxOccupancy(){return _MaxOccupancy;}
  inline int GetOccupancy(){return _Occupancy;}
  inline string GetName(){return _ShellName;}
  void PushNucleon();
  

private:
  int _MaxOccupancy;
  int _Occupancy;
  string _ShellName; 

};
