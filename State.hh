


class State{
  
public:
  State(int,int);
  virtual ~State();

  double GetIsoSpin(int ExcitedLevel=0);
  inline double GetIsoSpinZ() {return _IsoSpinZ;}
  

private:
  int _A, _Z;

  double _IsoSpin,_IsoSpinZ;

};
