#ifndef __STATE_HH
#define __STATE_HH

#include <string>
#include <sstream>
#include <cmath>
#include <stdlib.h>
using namespace std;
#include "TObject.h"
class State : public TObject{
  
public:
  State(int,int);
  virtual ~State();

  double GetIsoSpin(int ExcitedLevel=0);
  inline double GetIsoSpinZ() {return _IsoSpinZ;}
  inline void SetAZ(int a,int z){_A=a;_Z=z;_IsoSpinZ=((_A-_Z) -_Z)/2.0;}
  inline double GetJ(){return _J;}
  inline double GetParity(){return _Parity;}
  inline double GetP(){return _Parity;}
  void SetJPi(string);
  string GetStringP();
  string GetStringIZ();

private:
  int _A, _Z;

  double _IsoSpin,_IsoSpinZ;
  double _J;
  double _Parity;
public:
  ClassDef(State,1);
};
#endif
