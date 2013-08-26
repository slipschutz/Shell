
#include "Shell.hh"

Shell::Shell(){
  //Set Defualts to be an s-shell
  _MaxOccupancy=2;
  _ShellName="1s1/2";
  _Occupancy=0;
  _NormOccupancy=0;
  _J=1/2.0;
  _l=0;
  _n=1;
}

Shell::Shell(int maxOc,string name,double j,double l, double n) :
  _MaxOccupancy(maxOc), _ShellName(name),_J(j/2.0),_l(l),_n(n){
  _Occupancy=0;
  _NormOccupancy=0;
}

Shell::~Shell(){
  _MaxOccupancy=-1;
  _Occupancy=-1;
  _NormOccupancy=-1;
  _ShellName="***";

}

bool Shell::IsFull(){
  if ( _Occupancy >= _MaxOccupancy )
    return true;
  else
    return false;

}
void Shell::PushNucleon(){
  if (_Occupancy < _MaxOccupancy){
    _Occupancy++;
    _NormOccupancy=_Occupancy;
  } else {
    cout<<"******Shell Full Cannot Add to it******"<<endl;
  }
  
}
