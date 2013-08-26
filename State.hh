#ifndef __STATE_HH
#define __STATE_HH

#include "TObject.h"
class State : public TObject{
  
public:
  State(int,int);
  virtual ~State();

  double GetIsoSpin(int ExcitedLevel=0);
  inline double GetIsoSpinZ() {return _IsoSpinZ;}
  inline void SetAZ(int a,int z){_A=a;_Z=z;_IsoSpinZ=((_A-_Z) -_Z)/2.0;}

private:
  int _A, _Z;

  double _IsoSpin,_IsoSpinZ;

public:
  ClassDef(State,1);
};
#endif
