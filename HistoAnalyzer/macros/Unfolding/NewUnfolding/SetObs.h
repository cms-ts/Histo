//After that, Observables are set...

////////////////////
//  return number of valid jets
////////////////////


int getNumberOfValidJets(int Jet_multiplicity, double thresh, double thresheta, double jet1_pt, double jet2_pt, double jet3_pt, double jet4_pt, double jet5_pt, double jet6_pt, double jet1_eta, double jet2_eta, double jet3_eta, double jet4_eta, double jet5_eta, double jet6_eta){
  int counter=0;
  for (int i=1;i<=Jet_multiplicity; i++){
    if (i==1){
      if (jet1_pt>thresh && fabs(jet1_eta)<thresheta ) counter++;
    }    
    if (i==2){
      if (jet2_pt>thresh && fabs(jet2_eta)<thresheta ) counter++;
    }
    if (i==3){
      if (jet3_pt>thresh && fabs(jet3_eta)<thresheta ) counter++;
    }
    if (i==4){
      if (jet4_pt>thresh && fabs(jet4_eta)<thresheta ) counter++;
    }
    if (i==5){
      if (jet5_pt>thresh && fabs(jet5_eta)<thresheta ) counter++;
    }
    if (i==6){
      if (jet6_pt>thresh && fabs(jet6_eta)<thresheta ) counter++;
    }

  }// for
  return counter;
}// end


////////////////////////
//Set the observables MC
//////////////////////// 

void setObservablesMC(int numbOfJetsSelected, string whichtype, double jet1_pt_gen, double jet2_pt_gen, double jet3_pt_gen, double jet4_pt_gen,  double jet5_pt_gen,  double jet6_pt_gen, double jet1_eta_gen, double jet2_eta_gen, double jet3_eta_gen, double jet4_eta_gen, double jet5_eta_gen, double jet6_eta_gen, int Jet_multiplicity_gen, double jet1_pt, double jet2_pt, double jet3_pt, double jet4_pt,  double jet5_pt,  double jet6_pt, double jet1_eta, double jet2_eta, double jet3_eta, double jet4_eta, double jet5_eta, double jet6_eta,int Jet_multiplicity){

  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      jet_Obs_gen=jet1_pt_gen;
      jet_Obs=jet1_pt;
    }
    if (numbOfJetsSelected==2) {
      jet_Obs_gen=jet2_pt_gen;
      jet_Obs=jet2_pt;
    }
    if (numbOfJetsSelected==3) {
      jet_Obs_gen=jet3_pt_gen;
      jet_Obs=jet3_pt;
    }
    if (numbOfJetsSelected==4) {
      jet_Obs_gen=jet4_pt_gen;
      jet_Obs=jet4_pt;
    }
    if (jet_Obs_gen>7000 || jet_Obs_gen<-1) jet_Obs_gen=0;
    return;
  }

  if (whichtype=="Eta"){
    if (numbOfJetsSelected==1) {
      jet_Obs_gen=jet1_eta_gen;
      jet_Obs=jet1_eta;
    }
    if (numbOfJetsSelected==2) {
      jet_Obs_gen=jet2_eta_gen;
      jet_Obs=jet2_eta;

    }
    if (numbOfJetsSelected==3) {
      jet_Obs_gen=jet3_eta_gen;
      jet_Obs=jet3_eta;
    }
    if (numbOfJetsSelected==4) {
      jet_Obs_gen=jet4_eta_gen;
      jet_Obs=jet4_eta;
    }
    return;
  }

  if (whichtype=="Ht"){
    if (Jet_multiplicity >= numbOfJetsSelected ){
      if (jet1_pt > 30 && jet1_pt < 7000 && fabs(jet1_eta)<2.4 ) jet_Obs += jet1_pt;
        if (jet2_pt > 30 && jet2_pt < 7000 && fabs(jet2_eta)<2.4) jet_Obs += jet2_pt;
        if (jet3_pt > 30 && jet3_pt < 7000 && fabs(jet3_eta)<2.4) jet_Obs += jet3_pt;
        if (jet4_pt > 30 && jet4_pt < 7000 && fabs(jet4_eta)<2.4) jet_Obs += jet4_pt;
        if (jet5_pt > 30 && jet5_pt < 7000 && fabs(jet5_eta)<2.4) jet_Obs += jet5_pt;
        if (jet6_pt > 30 && jet6_pt < 7000 && fabs(jet6_eta)<2.4) jet_Obs += jet6_pt;
      }

    if (Jet_multiplicity_gen >= numbOfJetsSelected ){
        if (jet1_pt_gen > 30 && jet1_pt_gen < 7000 && fabs(jet1_eta_gen)<2.4) jet_Obs_gen += jet1_pt_gen;
        if (jet2_pt_gen > 30 && jet2_pt_gen < 7000 && fabs(jet2_eta_gen)<2.4) jet_Obs_gen += jet2_pt_gen;
        if (jet3_pt_gen > 30 && jet3_pt_gen < 7000 && fabs(jet3_eta_gen)<2.4) jet_Obs_gen += jet3_pt_gen;
        if (jet4_pt_gen > 30 && jet4_pt_gen < 7000 && fabs(jet4_eta_gen)<2.4) jet_Obs_gen += jet4_pt_gen;
        if (jet5_pt_gen > 30 && jet5_pt_gen < 7000 && fabs(jet5_eta_gen)<2.4) jet_Obs_gen += jet5_pt_gen;
        if (jet6_pt_gen > 30 && jet6_pt_gen < 7000 && fabs(jet6_eta_gen)<2.4) jet_Obs_gen += jet6_pt_gen;
      }
    return;
  }

  if (whichtype=="Multiplicity"){
    jet_Obs_gen=getNumberOfValidJets(Jet_multiplicity_gen, 30.0, 2.4, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);
    jet_Obs=getNumberOfValidJets(Jet_multiplicity, 30.0, 2.4, jet1_pt, jet2_pt, jet3_pt, jet4_pt, jet5_pt, jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta);
  }

  return;
}


////////////////////////
//Set the observables Data
////////////////////////

void setObservablesData(int numbOfJetsSelected, string whichtype, double jet1_pt, double jet2_pt, double jet3_pt, double jet4_pt,  double jet5_pt,  double jet6_pt, double jet1_eta, double jet2_eta, double jet3_eta, double jet4_eta, double jet5_eta, double jet6_eta,int Jet_multiplicity){

  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      jet_Obs=jet1_pt;
    }
    if (numbOfJetsSelected==2) {
      jet_Obs=jet2_pt;
    }
    if (numbOfJetsSelected==3) {
      jet_Obs=jet3_pt;
    }
    if (numbOfJetsSelected==4) {
      jet_Obs=jet4_pt;
    }
    return;
  }

  if (whichtype=="Eta"){
    if (numbOfJetsSelected==1) {
      jet_Obs=jet1_eta;
    }
    if (numbOfJetsSelected==2) {
      jet_Obs=jet2_eta;

    }
    if (numbOfJetsSelected==3) {
      jet_Obs=jet3_eta;
    }
    if (numbOfJetsSelected==4) {
      jet_Obs=jet4_eta;
    }
    if (jet_Obs==0) jet_Obs=-99; //To avoid peak
    return;
  }

  if (whichtype=="Ht"){
    if (Jet_multiplicity >= numbOfJetsSelected ){
        if (jet1_pt > 30 && jet1_pt < 7000 && fabs(jet1_eta)<2.4) jet_Obs += jet1_pt;
        if (jet2_pt > 30 && jet2_pt < 7000 && fabs(jet2_eta)<2.4) jet_Obs += jet2_pt;
        if (jet3_pt > 30 && jet3_pt < 7000 && fabs(jet3_eta)<2.4) jet_Obs += jet3_pt;
        if (jet4_pt > 30 && jet4_pt < 7000 && fabs(jet4_eta)<2.4) jet_Obs += jet4_pt;
        if (jet5_pt > 30 && jet5_pt < 7000 && fabs(jet5_eta)<2.4) jet_Obs += jet5_pt;
        if (jet6_pt > 30 && jet6_pt < 7000 && fabs(jet6_eta)<2.4) jet_Obs += jet6_pt;
      }
    return;
  }

  if (whichtype=="Multiplicity"){
    jet_Obs=Jet_multiplicity;
  }

  return;
}

////////////////////////
//Set the observables: Divisions
////////////////////////

void setPlotsDivisionsAndRanges(int numbOfJetsSelected, string whichtype, string whichalgo)
{
  bool bayesianTests=false;
  if (whichalgo=="Bayes") bayesianTests=true;

  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      kmin=9;
      kmax=10;
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
    }
    if (numbOfJetsSelected==2){
      minObsPlot=30;
      maxObsPlot=330;
      divPlot=10;
      kmin=4;
      kmax=5;
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
    }
    if (numbOfJetsSelected==3){
      minObsPlot=30;
      maxObsPlot=190;
      divPlot=8;
      kmin=4;
      kmax=5;
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
    }
    if (numbOfJetsSelected==4){
      minObsPlot=30;
      maxObsPlot=100;
      divPlot=7;
      kmin=3;
      kmax=4;
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
    }
  }

  if (whichtype == "Eta"){
    minObsPlot=-2.4;
    maxObsPlot=2.4;
    divPlot=48;
    kmin=4;
    kmax=5;

    if (numbOfJetsSelected==1) {
      kmin=9;
      kmax=10;
      divPlot=24;

    }
    
    if (numbOfJetsSelected==2){
      kmin=20;
      kmax=21;
      divPlot=20;
    }
    
    if (numbOfJetsSelected==3){
      kmin=8;
      kmax=9;
      divPlot=16;
    }
    
    if (numbOfJetsSelected==4){
      kmin=8;
      kmax=9;
      divPlot=12;
    } 
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
  }
  
  if (whichtype=="Ht"){
    
    divPlot = 12;
    minObsPlot = 30;
    maxObsPlot = 630;
    kmin = 11;
    kmax = 12;

if (numbOfJetsSelected == 1){
      kmin = 5;
      kmax = 6;
    }
  if (numbOfJetsSelected == 2){
      minObsPlot = 60;
      maxObsPlot = 630;
      kmin = 7;
      kmax = 8;
    }
  if (numbOfJetsSelected == 3){
      kmin = 7;
      kmax = 8;
      divPlot = 7;
      minObsPlot = 90;
      maxObsPlot = 630;
    }
  if (numbOfJetsSelected == 4){                          
      kmin = 4;
      kmax = 5;
      divPlot = 5;
      minObsPlot = 120;
      maxObsPlot = 630;
    }
  if (bayesianTests) {
    kmin=3;
    kmax=4;
      }
  }

  if (whichtype=="Multiplicity"){
    divPlot=maxNJets-1;
    minObsPlot=1;
    maxObsPlot=maxNJets-1;

    kmin=2;
    kmax=3;
    
    if (bayesianTests) {
      kmin=3;
      kmax=4;
    }
  }
  
  // When you span
  if (spanKvalues){
    kmin=2;
    kmax=divPlot; 
  }
  return;
}
