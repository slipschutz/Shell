
#include "Nucleus.hh"
#include <iomanip>

Nucleus::Nucleus() : State(-1,-1){
  A=-1;
  Z=-1;
}

Nucleus::Nucleus(int a, int z) : State(a,z),A(a),Z(z){
  cout<<"Z is "<<Z<<endl;
  cout<<"A is "<<A<<endl;
  DefineShellClosures();
  DefineShells();
  Fill();
}


Nucleus::~Nucleus()
{;}

void Nucleus::DefineShellClosures(){
  
  int array[]={0,2,8,20,28,50,82,126,126};

  for (int i=0;i<8;i++){
    for (int j=0;j<array[i+1];j++){

      theShellClosures[j+array[i]]=array[i];

    }
  }
  
}

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

  int ShellCountP =0;
  int ShellCountN =0;
  for (int i=0;i<Z;i++){

    if (theProtonShells[ShellCountP].IsFull() ){
      ShellCountP++;
      i--;//Go back one to start with i on next shell
    } else {
      theProtonShells[ShellCountP].PushNucleon();
    } 
  }
  
  theNeutronShells = theShellOrder;
  
  for (int i=0;i<A-Z;i++){

    if (theNeutronShells[ShellCountN].IsFull() ){
      ShellCountN++;
      i--;//Go back one to start with i on next shell
    } else {
      theNeutronShells[ShellCountN].PushNucleon();
    } 
  }
  if (ShellCountN >= ShellCountP)
    ShellCountP=ShellCountN;
  else
    ShellCountN=ShellCountP;
      
  theNeutronShells.resize(ShellCountN+1);

  theProtonShells.resize(ShellCountP+1);


}

void Nucleus::DrawShell(Shell& theShell,string type){
  
  int MaxLineChar=14;

  if ( type == "p" || type == "n" || type=="P" ||type=="N"){
    string particleSymbol=type;
    for (int j=0;j<theShell.GetOccupancy();j++){
      if (type == "p" || type =="n")
	cout<<"-"<<particleSymbol;
      else
	cout<<particleSymbol<<particleSymbol;
    }
    
    if ( theShell.IsFull()){
      for (int q=0;q< (MaxLineChar-theShell.GetOccupancy());q++){
	cout<<"--";
      }
    }else {
      for (int q=0;q<(theShell.GetMaxOccupancy()-theShell.GetOccupancy());q++){
	cout<<"-0";
      }
      for (int q=0;q< (MaxLineChar-theShell.GetMaxOccupancy());q++){
	cout<<"--";
      }
      
    }
    cout<<"  "<<setw(8)<<theShell.GetName();
  }else { // print blank filler line
    for (int q=0;q<MaxLineChar;q++)
      cout<<"  ";
    cout<<"  "<<setw(8)<<theShell.GetName();
  }
}

void Nucleus::Draw(){
  
  int MaxLineChar=14;
  
  int countZ=0;
  int spotZ=theShellClosures[Z];

  int countN=0;
  int spotN=theShellClosures[A-Z];

  int size=0;
  bool neutronBigger;
  if (theProtonShells.size() >= theNeutronShells.size()){
    size=theProtonShells.size();
    neutronBigger=false;
  } else {
    size=theNeutronShells.size();
    neutronBigger=true;
  }

  for (int i=size-1;i>=0;i--){


    //    cout<<"count "<<count<<endl;
    //    cout<<"spot "<<spot<<endl;

    if ((Z-countZ) == spotZ )
      DrawShell(theProtonShells[i],"P");
    else
      DrawShell(theProtonShells[i],"p");
    cout<<" ";

    if (( A-Z-countN) == spotN )
      DrawShell(theNeutronShells[i],"N");
    else
      DrawShell(theNeutronShells[i],"n");
    cout<<endl;
    countZ = countZ + theProtonShells[i].GetOccupancy();
    countN = countN + theNeutronShells[i].GetOccupancy();

  }

}

