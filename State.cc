

#include <iostream>
#include "State.hh"
using namespace std;


State::State(int a, int z) : _A(a), _Z(z){
  _IsoSpinZ=((_A-_Z) -_Z)/2.0;
  
  _IsoSpin=0;

  cout<<"iso spin z "<<_IsoSpinZ<<endl;
  cout<<"iso spin "<<_IsoSpin<<endl;
}



State::~State(){

  _A=-1;
  _Z=-1;
  _IsoSpin=-1;
  _IsoSpinZ=-1;

}

double State::GetIsoSpin(int ExcitedLevel){

  return (ExcitedLevel)+_IsoSpinZ;
}
