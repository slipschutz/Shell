
#include "Nucleus.hh"
#include <iomanip>

Nucleus::Nucleus() : State(-1,-1){
  A=-1;
  Z=-1;
  DefineShellClosures();
  DefineShells();
}

Nucleus::Nucleus(int a, int z) : State(a,z),A(a),Z(z){
  //  cout<<"Z is "<<Z<<endl;
  //  cout<<"A is "<<A<<endl;

  DefineShellClosures();
  DefineShells();
  Fill();
}
Nucleus::Nucleus(int a,string s) : State(0,0){
  DefineAbrevMap();
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);

  DefineShellClosures();
  DefineShells();
  if (AbrevMap.count(s) != 0 )
    SetAZ(a,AbrevMap[s]);
  else{
    cout<<"Element Not Found"<<endl;
  }
    
}

Nucleus::~Nucleus()
{;}

void Nucleus::DefineShellClosures(){
  
  int array[]={0,2,8,20,28,50,82,126,126};

  for (int i=0;i<8;i++){
    for (int j=0;j<array[i+1];j++){

      theShellClosures[j+1+array[i]]=array[i];

    }
  }

  //  _theDrawClosures["2g9/2"]=true;
  _theDrawClosures["1h9/2"]=true;
  _theDrawClosures["1g7/2"]=true;
  _theDrawClosures["1f7/2"]=true;
  _theDrawClosures["1d5/2"]=true;
  _theDrawClosures["1p3/2"]=true;

}

void Nucleus::DefineShells(){
  
  theShellOrder.push_back(Shell(2,"1s1/2",1,0,1,1));
  theShellOrder.push_back(Shell(4,"1p3/2",3,1,1,2));
  theShellOrder.push_back(Shell(2,"1p1/2",1,1,1,2));
  theShellOrder.push_back(Shell(6,"1d5/2",5,2,1,3));
  theShellOrder.push_back(Shell(2,"2s1/2",1,0,2,3));
  theShellOrder.push_back(Shell(4,"1d3/2",3,2,1,3));
  theShellOrder.push_back(Shell(8,"1f7/2",7,3,1,4));
  theShellOrder.push_back(Shell(4,"2p3/2",3,1,2,4));
  theShellOrder.push_back(Shell(6,"1f5/2",5,3,1,4));
  theShellOrder.push_back(Shell(2,"2p1/2",1,1,2,4));
  theShellOrder.push_back(Shell(10,"1g9/2",9,4,1,4));
  theShellOrder.push_back(Shell(8,"1g7/2",7,4,1,5));
  theShellOrder.push_back(Shell(6,"2d5/2",5,2,2,5));
  theShellOrder.push_back(Shell(4,"2d3/2",3,2,2,5));
  theShellOrder.push_back(Shell(2,"3s1/2",1,0,3,5));
  theShellOrder.push_back(Shell(12,"1h11/2",11,5,1,5));
  theShellOrder.push_back(Shell(10,"1h9/2",9,5,1,6));
  theShellOrder.push_back(Shell(8,"2f7/2",7,3,2,6));
  theShellOrder.push_back(Shell(14,"1i13/2",13,6,1,6));
  theShellOrder.push_back(Shell(4,"3p3/2",3,1,3,6));
  theShellOrder.push_back(Shell(6,"2f5/2",5,3,2,6));
  theShellOrder.push_back(Shell(2,"3p1/2",1,1,3,6));

}

#define MAXNZ 126
void Nucleus::Fill(){
  if ( Z>MAXNZ || (A-Z)>MAXNZ){
    cout<<"Error: Outside of supported N/Z range"<<endl;
    return;
  }
  //Clear theProton/neutron SHells

  theProtonShells.clear();
  theNeutronShells.clear();
  
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
      
  //  theNeutronShells.resize(ShellCountN+1);

  //  theProtonShells.resize(ShellCountP+1);


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
    cout<<"  "<<setw(8)<<theShell.GetName();//<<" "<<theShell.GetJ()<<" "<<theShell.Getl()<<" "<<theShell.Getn();;
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
    

    DrawShell(theProtonShells[i],"p");
    cout<<" ";
    DrawShell(theNeutronShells[i],"n");
        
    cout<<endl;
    
    if ( _theDrawClosures.count(theProtonShells[i].GetName())!=0){
      cout<<"_________________"<<endl;
    }
    countZ = countZ + theProtonShells[i].GetOccupancy();
    countN = countN + theNeutronShells[i].GetOccupancy();

  }

}


vector <Shell> Nucleus::GetModelSpaceZShells(){
  cout<<"Z is "<<Z<<endl;
  int theZClosure = theShellClosures[Z];
  cout<<"The Z closure is "<<theZClosure<<endl;
  
  vector <Shell> result;
  int start = GetShellIndex(theZClosure);
  for (int i=start+1;i<theProtonShells.size();++i){
    result.push_back(theProtonShells[i]);
  }
  return result;
}



vector <Shell> Nucleus::GetModelSpaceNShells(){
  cout<<"N is "<<A-Z<<endl;
  int theNClosure = theShellClosures[A-Z];
  cout<<"The N closure is "<<theNClosure<<endl;
  
  vector <Shell> result;
  int start = GetShellIndex(theNClosure);
  for (int i=start+1;i<theNeutronShells.size();++i){
    result.push_back(theNeutronShells[i]);
  }
  return result;
}

void Nucleus::PrintModelSpaces(){
  cout<<"The Proton Model space is"<<endl;
  vector <Shell> temp = GetModelSpaceZShells();
  for (int i=0;i<temp.size();i++){
    cout<<temp[i].GetName()<<endl;
  }
  cout<<"The Neutron Model space is"<<endl;
  temp = GetModelSpaceNShells();
  for (int i=0;i<temp.size();i++){
    cout<<temp[i].GetName()<<endl;
  }

}


int Nucleus::GetNextShellClosure(int theClosure){
  vector<int> vec;
  vec.push_back(2);
  vec.push_back(8);
  vec.push_back(20);
  vec.push_back(28);
  vec.push_back(50);
  vec.push_back(82);
  vec.push_back(126);
  
  int spot=-1;
  for (int i=0;i<vec.size();i++){
    if (vec[i] == theClosure && i<vec.size()-1){
      spot=i+1;
      i=vec.size()+1;
    }
  }
  if (spot == -1 ){
    throw "crap";
  }
  return vec[spot];
  
  
}
Shell* Nucleus::GetZShell(int NumNucleons){
  return GetShell(NumNucleons,theProtonShells);
}
Shell *Nucleus::GetNShell(int NumNucleons){
  return GetShell(NumNucleons,theNeutronShells);
}

Shell* Nucleus::GetZShell(string name){
  return GetShell(name,theProtonShells);
}
Shell *Nucleus::GetNShell(string name){
  return GetShell(name ,theNeutronShells);
}


Shell *Nucleus::GetShell(int NumNucleons,vector<Shell>& Shells){

  int spot =-1;
  int total = 0;

  for (int i=0;i<Shells.size();i++){

    if ( NumNucleons > total && 
	 NumNucleons <=total+ Shells[i].GetMaxOccupancy()){
      spot =i;
    }
    total = total + Shells[i].GetMaxOccupancy();
  }

  if (spot== -1){
    throw "Crap";
  }

  return &Shells[spot];
}

Shell *Nucleus::GetShell(string name,vector<Shell>&Shells){
  int spot=-1;
  for (int i=0;i<Shells.size();i++){
    if (Shells[i].GetName()==name){
      spot=i;
      i=Shells.size()+1;
    }
  }
  if (spot==-1){
    throw "crap";
  }
  return &Shells[spot];
  
}

int Nucleus::GetShellIndex(int NumNucleons){
  // Finds the shell for that Number of nucleons
  // Then does linear search for the spot in the shell
  // order where that shell is


  Shell theShell = *GetZShell(NumNucleons);//N vs Z here does not matter
  int spot=-1;
  
  for (int i=0;i<theShellOrder.size();i++){
    if ( theShell.GetName()== theShellOrder[i].GetName()){
      spot=i;
      i=theShellOrder.size()+1;
    }
  }
  if (spot == -1 ){
    throw "crap";
  }
  return spot;
}


void Nucleus::DumpShellClosureMap(){
  cout<<"Dumping Shell Closure Map\n\n\n";
  for (map<int,int>::iterator ii=theShellClosures.begin();ii!=theShellClosures.end();ii++){

    cout<<ii->first<<"     "<<ii->second<<endl;

  }



}

void Nucleus::DefineAbrevMap(){
  AbrevMap["ac"]=89;
  AbrevMap["al"]=13;
  AbrevMap["am"]=95;
  AbrevMap["sb"]=51;
  AbrevMap["ar"]=18;
  AbrevMap["as"]=33;
  AbrevMap["at"]=85;
  AbrevMap["ba"]=56;
  AbrevMap["bk"]=97;
  AbrevMap["be"]=4;
  AbrevMap["bi"]=83;
  AbrevMap["bh"]=107;
  AbrevMap["b"]=5;
  AbrevMap["br"]=35;
  AbrevMap["cd"]=48;
  AbrevMap["ca"]=20;
  AbrevMap["cf"]=98;
  AbrevMap["c"]=6;
  AbrevMap["ce"]=58;
  AbrevMap["cs"]=55;
  AbrevMap["cl"]=17;
  AbrevMap["cr"]=24;
  AbrevMap["co"]=27;
  AbrevMap["cu"]=29;
  AbrevMap["cm"]=96;
  AbrevMap["ds"]=110;
  AbrevMap["db"]=105;
  AbrevMap["dy"]=66;
  AbrevMap["es"]=99;
  AbrevMap["er"]=68;
  AbrevMap["eu"]=63;
  AbrevMap["fm"]=100;
  AbrevMap["f"]=9;
  AbrevMap["fr"]=87;
  AbrevMap["gd"]=64;
  AbrevMap["ga"]=31;
  AbrevMap["ge"]=32;
  AbrevMap["au"]=79;
  AbrevMap["hf"]=72;
  AbrevMap["hs"]=108;
  AbrevMap["he"]=2;
  AbrevMap["ho"]=67;
  AbrevMap["h"]=1;
  AbrevMap["in"]=49;
  AbrevMap["i"]=53;
  AbrevMap["ir"]=77;
  AbrevMap["fe"]=26;
  AbrevMap["kr"]=36;
  AbrevMap["la"]=57;
  AbrevMap["lr"]=103;
  AbrevMap["pb"]=82;
  AbrevMap["li"]=3;
  AbrevMap["lu"]=71;
  AbrevMap["mg"]=12;
  AbrevMap["mn"]=25;
  AbrevMap["mt"]=109;
  AbrevMap["md"]=101;
  AbrevMap["hg"]=80;
  AbrevMap["mo"]=42;
  AbrevMap["nd"]=60;
  AbrevMap["ne"]=10;
  AbrevMap["np"]=93;
  AbrevMap["ni"]=28;
  AbrevMap["nb"]=41;
  AbrevMap["n"]=7;
  AbrevMap["no"]=102;
  AbrevMap["os"]=76;
  AbrevMap["o"]=8;
  AbrevMap["pd"]=46;
  AbrevMap["p"]=15;
  AbrevMap["pt"]=78;
  AbrevMap["pu"]=94;
  AbrevMap["po"]=84;
  AbrevMap["k"]=19;
  AbrevMap["pr"]=59;
  AbrevMap["pm"]=61;
  AbrevMap["pa"]=91;
  AbrevMap["ra"]=88;
  AbrevMap["rn"]=86;
  AbrevMap["re"]=75;
  AbrevMap["rh"]=45;
  AbrevMap["rb"]=37;
  AbrevMap["ru"]=44;
  AbrevMap["rf"]=104;
  AbrevMap["sm"]=62;
  AbrevMap["sc"]=21;
  AbrevMap["sg"]=106;
  AbrevMap["se"]=34;
  AbrevMap["si"]=14;
  AbrevMap["ag"]=47;
  AbrevMap["na"]=11;
  AbrevMap["sr"]=38;
  AbrevMap["s"]=16;
  AbrevMap["ta"]=73;
  AbrevMap["tc"]=43;
  AbrevMap["te"]=52;
  AbrevMap["tb"]=65;
  AbrevMap["tl"]=81;
  AbrevMap["th"]=90;
  AbrevMap["tm"]=69;
  AbrevMap["sn"]=50;
  AbrevMap["ti"]=22;
  AbrevMap["w"]=74;
  AbrevMap["uub"]=112;
  AbrevMap["uuh"]=116;
  AbrevMap["uuo"]=118;
  AbrevMap["uup"]=115;
  AbrevMap["uuq"]=114;
  AbrevMap["uus"]=117;
  AbrevMap["uut"]=113;
  AbrevMap["uuu"]=111;
  AbrevMap["u"]=92;
  AbrevMap["v"]=23;
  AbrevMap["xe"]=54;
  AbrevMap["yb"]=70;
  AbrevMap["y"]=39;
  AbrevMap["zn"]=30;
  AbrevMap["zr"]=40;
}
