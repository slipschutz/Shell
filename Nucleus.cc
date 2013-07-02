
#include "Nucleus.hh"

Nucleus::Nucleus()
{;}

Nucleus::Nucleus(int a, int z) : A(a),Z(z){
  cout<<"Z is "<<Z<<endl;
  cout<<"A is "<<A<<endl;
  DefineShells();
  Fill();
}


Nucleus::~Nucleus()
{;}


void Nucleus::DefineShells(){
  
  theShellOrder.push_back(Shell(2,"1s1/2"));
  theShellOrder.push_back(Shell(4,"1p3/2"));
  theShellOrder.push_back(Shell(2,"1p1/2"));
  theShellOrder.push_back(Shell(6,"1d5/2"));
  theShellOrder.push_back(Shell(2,"2s1/2"));
  theShellOrder.push_back(Shell(4,"1d3/2"));
  theShellOrder.push_back(Shell(8,"1f7/2"));
  theShellOrder.push_back(Shell(4,"2p3/2"));
  theShellOrder.push_back(Shell(6,"1f5/2"));
  theShellOrder.push_back(Shell(2,"2p1/2"));
  theShellOrder.push_back(Shell(10,"1g9/2"));
  theShellOrder.push_back(Shell(8,"1g7/2"));
  theShellOrder.push_back(Shell(6,"2d5/2"));
  theShellOrder.push_back(Shell(4,"2d3/2"));
  theShellOrder.push_back(Shell(2,"3s1/2"));
  theShellOrder.push_back(Shell(12,"1h11/2"));
  theShellOrder.push_back(Shell(10,"1h9/2"));
  theShellOrder.push_back(Shell(8,"2f7/2"));
  theShellOrder.push_back(Shell(14,"1i13/2"));
  theShellOrder.push_back(Shell(4,"3p3/2"));
  theShellOrder.push_back(Shell(6,"2f5/2"));
  theShellOrder.push_back(Shell(2,"3p1/2"));

}

#define MAXNZ 126
void Nucleus::Fill(){
  if ( Z>MAXNZ || (A-Z)>MAXNZ){
    cout<<"Error: Outside of supported N/Z range"<<endl;
    return;
  }

  theProtonShells = theShellOrder;

  int ShellCount =0;
  for (int i=0;i<Z;i++){

    if (theProtonShells[ShellCount].IsFull() ){
      ShellCount++;
      i--;//Go back one to start with i on next shell
    } else {
      theProtonShells[ShellCount].PushNucleon();
    } 
  }
  theProtonShells.resize(ShellCount+1);

  
  theNeutronShells = theShellOrder;
    
  ShellCount =0;
  for (int i=0;i<A-Z;i++){

    if (theNeutronShells[ShellCount].IsFull() ){
      ShellCount++;
      i--;//Go back one to start with i on next shell
    } else {
      theNeutronShells[ShellCount].PushNucleon();
    } 
  }
  theNeutronShells.resize(ShellCount+1);




}

void Nucleus::Draw(){
  
  int MaxLineChar=14;
  
  for (int i=theProtonShells.size()-1;i>=0;i--){
    for (int j=0;j<theProtonShells[i].GetOccupancy();j++){
      cout<<"-P";
    }
    
    if ( theProtonShells[i].IsFull()){
      for (int q=0;q< (MaxLineChar-theProtonShells[i].GetOccupancy());q++){
	cout<<"--";
      }
    }else {
      for (int q=0;q<(theProtonShells[i].GetMaxOccupancy()-theProtonShells[i].GetOccupancy());q++){
	cout<<"-0";
      }
      for (int q=0;q< (MaxLineChar-theProtonShells[i].GetMaxOccupancy());q++){
	cout<<"--";
      }

    }
    cout<<"  "<<theProtonShells[i].GetName()<<endl;
  }

  cout<<"\n====================================\n";
  for (int i=theNeutronShells.size()-1;i>=0;i--){
    for (int j=0;j<theNeutronShells[i].GetOccupancy();j++){
      cout<<"-N";
    }
    
    if ( theNeutronShells[i].IsFull()){
      for (int q=0;q< (MaxLineChar-theNeutronShells[i].GetOccupancy());q++){
	cout<<"--";
      }
    }else {
      for (int q=0;q<(theNeutronShells[i].GetMaxOccupancy()-theNeutronShells[i].GetOccupancy());q++){
	cout<<"-0";
      }
      for (int q=0;q< (MaxLineChar-theNeutronShells[i].GetMaxOccupancy());q++){
	cout<<"--";
      }

    }
    cout<<"  "<<theNeutronShells[i].GetName()<<endl;
  }

}

