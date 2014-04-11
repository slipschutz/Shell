

#include <iostream>
#include "State.hh"
using namespace std;


State::State(int a, int z) : _A(a), _Z(z){
  _IsoSpinZ=((_A-_Z) -_Z)/2.0;

  _IsoSpin=0;

  _J=0;
  _Parity=1;
  
  //  cout<<"iso spin z "<<_IsoSpinZ<<endl;
  //  cout<<"iso spin "<<_IsoSpin<<endl;
}



State::~State(){

  _A=-1;
  _Z=-1;
  _IsoSpin=-1;
  _IsoSpinZ=-1;

}

double State::GetIsoSpin(int ExcitedLevel){

  return fabs(_IsoSpinZ +double(ExcitedLevel));
}

void State::SetJPi(string input){
  if (input.find('+') !=string::npos && input.find('+')==input.length()-1){
    //Found A +
    _Parity=1;
  } else if (input.find('-') !=string::npos && input.find('-')==input.length()-1){
    _Parity=-1;
  } else {
    throw "Bad Parse";
  }
  
  string temp = input.substr(0,input.length()-1);
  if (temp.find('/') == string::npos ){
    _J= atof(temp.c_str());
  } else {
    int ind = temp.find('/');
    string left = temp.substr(0,ind);

    string right = temp.substr(ind+1, temp.length()-ind);

    _J = atof(left.c_str())/atof(right.c_str());
  }
  

}

string State::GetStringP(){

  if ( _Parity == 1 ){
    return "+";
  } else {
    return "-";
  }

}

string State::GetStringIZ(){
  stringstream ss;
  
  if ( _IsoSpinZ < 0 ){
    ss<<"-"<<fabs(_IsoSpinZ);
  } else if (_IsoSpinZ >0 ){
    ss<<"+"<<fabs(_IsoSpinZ);
  } else {
    ss<<"0.0";
  }
  if (_IsoSpinZ !=0){
    if (round(_IsoSpinZ)==_IsoSpinZ)
      ss<<".";
  }
      
  return ss.str();
  
}
