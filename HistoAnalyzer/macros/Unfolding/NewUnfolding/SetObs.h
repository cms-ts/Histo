//After that, Observables are set...

bool isJetCloseToLeptons(double jet_eta, double jet_phi, double lepton1_eta, double lepton1_phi, double lepton2_eta, double lepton2_phi, double maxDRAllowed) 
{
  //Check if the DR jet_i Vs lepton_1,2 is < 0.5. 
  
  double delta_phi_l1 = fabs( lepton1_phi - jet_phi);
  double delta_phi_l2 = fabs( lepton2_phi - jet_phi);
  double delta_eta_l1 = lepton1_eta - jet_eta;
  double delta_eta_l2 = lepton2_eta - jet_eta;
  
  if (delta_phi_l1 > acos(-1)) delta_phi_l1 = 2*acos(-1) - delta_phi_l1;
  if (delta_phi_l2 > acos(-1)) delta_phi_l2 = 2*acos(-1) - delta_phi_l2;
  
  double deltaR1 = sqrt( pow(delta_eta_l1,2) + pow(delta_phi_l1,2) );
  double deltaR2 = sqrt( pow(delta_eta_l2,2) + pow(delta_phi_l2,2) );

  if (deltaR1<maxDRAllowed || deltaR2 <maxDRAllowed) return false;
  return true;
}

bool setRecoVariablesFilteringDRLeptons(double lepton1_eta, double lepton2_eta, double lepton1_phi, double lepton2_phi, double jet1_pt, double jet2_pt, double jet3_pt, double jet4_pt,  double jet5_pt,  double jet6_pt, double jet1_eta, double jet2_eta, double jet3_eta, double jet4_eta, double jet5_eta, double jet6_eta,  double jet1_phi, double jet2_phi, double jet3_phi, double jet4_phi,  double jet5_phi,  double jet6_phi, int Jet_multiplicity){
  bool res=true;

  //Put all variables in a wonderful vector!
  std::vector<std::vector <double> > jetscontainer;

  for (int i=1;i<=Jet_multiplicity; i++){
    double jeteta=0; double jetphi=0; double jetpt=0;
    
    if (i==1){jeteta=jet1_eta; jetphi=jet1_phi; jetpt=jet1_pt;}
    if (i==2){jeteta=jet2_eta; jetphi=jet2_phi; jetpt=jet2_pt;}
    if (i==3){jeteta=jet3_eta; jetphi=jet3_phi; jetpt=jet3_pt;}
    if (i==4){jeteta=jet4_eta; jetphi=jet4_phi; jetpt=jet4_pt;}
    if (i==5){jeteta=jet5_eta; jetphi=jet5_phi; jetpt=jet5_pt;}
    if (i==6){jeteta=jet6_eta; jetphi=jet6_phi; jetpt=jet6_pt;}
    
    if (!isJetCloseToLeptons(jeteta, jetphi, lepton1_eta, lepton1_phi, lepton2_eta, lepton2_phi, 0.5) ) {res=false;}
    else {
      std::vector<double> j;
      j.push_back(jeteta); j.push_back(jetphi); j.push_back(jetpt); 
      jetscontainer.push_back(j);
    } 
  }
  
  if (res) return res;
  //Riassegna i valori
  
  for (int j=0; j<=jetscontainer.size();j++){
    std::vector<double> jet=jetscontainer[j];
    if (j==0) jet1_eta=jet[0]; jet1_phi=jet[1]; jet1_pt=jet[2];
    if (j==1) jet2_eta=jet[0]; jet2_phi=jet[1]; jet2_pt=jet[2];
    if (j==2) jet3_eta=jet[0]; jet3_phi=jet[1]; jet3_pt=jet[2];
    if (j==3) jet4_eta=jet[0]; jet4_phi=jet[1]; jet4_pt=jet[2];
    if (j==4) jet5_eta=jet[0]; jet5_phi=jet[1]; jet5_pt=jet[2];
    if (j==5) jet6_eta=jet[0]; jet6_phi=jet[1]; jet6_pt=jet[2];
  }
  return false;
}

void printObservables(double jet1_pt_gen, double jet2_pt_gen, double jet3_pt_gen, double jet4_pt_gen,  double jet5_pt_gen,  double jet6_pt_gen, double jet1_eta_gen, double jet2_eta_gen, double jet3_eta_gen, double jet4_eta_gen, double jet5_eta_gen, double jet6_eta_gen, int Jet_multiplicity_gen, double jet1_pt, double jet2_pt, double jet3_pt, double jet4_pt,  double jet5_pt,  double jet6_pt, double jet1_eta, double jet2_eta, double jet3_eta, double jet4_eta, double jet5_eta, double jet6_eta,int Jet_multiplicity, double Jet_Obs, double Jet_Obs_gen)
{
  cout<<endl;
  cout<<"++++++++Begin Event++++++++++"<<endl;
  cout<<"gen: jet1:"<< jet1_pt_gen<<" jet2:"<< jet2_pt_gen<<" jet3:"<< jet3_pt_gen<<" jet4:"<< jet4_pt_gen<<" jet5:"<<  jet5_pt_gen<<" jet6:"<<  jet6_pt_gen<<" eta1:"<< jet1_eta_gen<<" eta2:"<< jet2_eta_gen<<" eta3:"<< jet3_eta_gen<<" eta4:"<< jet4_eta_gen<<" eta5:"<< jet5_eta_gen<<" eta6:"<< jet6_eta_gen<<" jet multi gen:"<<  Jet_multiplicity_gen<<endl;
  cout<<"reco jet1:"<< jet1_pt<<" jet2:"<< jet2_pt<<" jet3:"<< jet3_pt<<" jet4:"<< jet4_pt<<" jet5:"<<  jet5_pt<<" jet6:"<<  jet6_pt<<" eta1:"<< jet1_eta<<" eta2:"<< jet2_eta<<" eta3:"<< jet3_eta<<" eta4:"<< jet4_eta<<" eta5:"<< jet5_eta<<" eta6:"<< jet6_eta<<" jet multi reco:"<< Jet_multiplicity<<" jetObs_gen "<<Jet_Obs_gen<<" jetObs "<<Jet_Obs<<endl;
  return;
}

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

void setObservablesMC(int numbOfJetsSelected, string whichtype, double jet1_pt_gen, double jet2_pt_gen, double jet3_pt_gen, double jet4_pt_gen,  double jet5_pt_gen,  double jet6_pt_gen, double jet1_eta_gen, double jet2_eta_gen, double jet3_eta_gen, double jet4_eta_gen, double jet5_eta_gen, double jet6_eta_gen, int Jet_multiplicity_gen, double jet1_pt, double jet2_pt, double jet3_pt, double jet4_pt,  double jet5_pt,  double jet6_pt, double jet1_eta, double jet2_eta, double jet3_eta, double jet4_eta, double jet5_eta, double jet6_eta,int Jet_multiplicity,double jet1_pt_gen_abs, double jet2_pt_gen_abs, double jet3_pt_gen_abs, double jet4_pt_gen_abs,  double jet5_pt_gen_abs,  double jet6_pt_gen_abs, double jet1_eta_gen_abs, double jet2_eta_gen_abs, double jet3_eta_gen_abs, double jet4_eta_gen_abs, double jet5_eta_gen_abs, double jet6_eta_gen_abs){

  //Formula to compute smearing
  jet1_pt=returnJERCorrectionSimplifiedFormula(jet1_eta, jet1_pt, jet1_pt_gen, smearingJERSyst);
  jet2_pt=returnJERCorrectionSimplifiedFormula(jet2_eta, jet2_pt, jet2_pt_gen, smearingJERSyst);
  jet3_pt=returnJERCorrectionSimplifiedFormula(jet3_eta, jet3_pt, jet3_pt_gen, smearingJERSyst);
  jet4_pt=returnJERCorrectionSimplifiedFormula(jet4_eta, jet4_pt, jet4_pt_gen, smearingJERSyst);
  jet5_pt=returnJERCorrectionSimplifiedFormula(jet5_eta, jet5_pt, jet5_pt_gen, smearingJERSyst);
  jet6_pt=returnJERCorrectionSimplifiedFormula(jet6_eta, jet6_pt, jet6_pt_gen, smearingJERSyst);


  if (numbOfJetsSelected==1){jet_Obs_pt_gen=jet1_pt_gen;jet_Obs_eta_gen=jet1_eta_gen;}
  if (numbOfJetsSelected==2){jet_Obs_pt_gen=jet2_pt_gen;jet_Obs_eta_gen=jet2_eta_gen;}
  if (numbOfJetsSelected==3){jet_Obs_pt_gen=jet3_pt_gen;jet_Obs_eta_gen=jet3_eta_gen;}
  if (numbOfJetsSelected==4){jet_Obs_pt_gen=jet4_pt_gen;jet_Obs_eta_gen=jet4_eta_gen;}

  if (numbOfJetsSelected==1){jet_Obs_pt=jet1_pt;jet_Obs_eta=jet1_eta;}
  if (numbOfJetsSelected==2){jet_Obs_pt=jet2_pt;jet_Obs_eta=jet2_eta;}
  if (numbOfJetsSelected==3){jet_Obs_pt=jet3_pt;jet_Obs_eta=jet3_eta;}
  if (numbOfJetsSelected==4){jet_Obs_pt=jet4_pt;jet_Obs_eta=jet4_eta;}

  if (numbOfJetsSelected==1){jet_Obs_pt_gen_abs=jet1_pt_gen_abs;jet_Obs_eta_gen_abs=jet1_eta_gen_abs;}
  if (numbOfJetsSelected==2){jet_Obs_pt_gen_abs=jet2_pt_gen_abs;jet_Obs_eta_gen_abs=jet2_eta_gen_abs;}
  if (numbOfJetsSelected==3){jet_Obs_pt_gen_abs=jet3_pt_gen_abs;jet_Obs_eta_gen_abs=jet3_eta_gen_abs;}
  if (numbOfJetsSelected==4){jet_Obs_pt_gen_abs=jet4_pt_gen_abs;jet_Obs_eta_gen_abs=jet4_eta_gen_abs;}
  
  jet_Obs_multi_gen_abs=getNumberOfValidJets(Jet_multiplicity_gen, threshPt, threshEta, jet1_pt_gen_abs, jet2_pt_gen_abs, jet3_pt_gen_abs, jet4_pt_gen_abs, jet5_pt_gen_abs, jet6_pt_gen_abs, jet1_eta_gen_abs, jet2_eta_gen_abs, jet3_eta_gen_abs, jet4_eta_gen_abs, jet5_eta_gen_abs, jet6_eta_gen_abs);
  
  jet_Obs_multi_gen=getNumberOfValidJets(Jet_multiplicity_gen, threshPt, threshEta, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);

  jet_Obs_multi=getNumberOfValidJets(Jet_multiplicity, threshPt, threshEta, jet1_pt, jet2_pt, jet3_pt, jet4_pt, jet5_pt, jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta);
    
  
  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      jet_Obs_gen=jet1_pt_gen;
      jet_Obs=jet1_pt;
      jet_Obs_gen_abs=jet1_pt_gen_abs;
    }
    if (numbOfJetsSelected==2) {
      jet_Obs_gen=jet2_pt_gen;
      jet_Obs=jet2_pt;
      jet_Obs_gen_abs=jet2_pt_gen_abs;
    }
    if (numbOfJetsSelected==3) {
      jet_Obs_gen=jet3_pt_gen;
      jet_Obs=jet3_pt;
      jet_Obs_gen_abs=jet3_pt_gen_abs;
    }
    if (numbOfJetsSelected==4) {
      jet_Obs_gen=jet4_pt_gen;
      jet_Obs=jet4_pt;
      jet_Obs_gen_abs=jet4_pt_gen_abs;
    }
    return;
  }

  if (whichtype=="Eta"){
    if (numbOfJetsSelected==1) {
      jet_Obs_gen=jet1_eta_gen;
      jet_Obs=jet1_eta;
      jet_Obs_gen_abs=jet1_eta_gen_abs;
    }
    if (numbOfJetsSelected==2) {
      jet_Obs_gen=jet2_eta_gen;
      jet_Obs=jet2_eta;
      jet_Obs_gen_abs=jet2_eta_gen_abs;

    }
    if (numbOfJetsSelected==3) {
      jet_Obs_gen=jet3_eta_gen;
      jet_Obs=jet3_eta;
      jet_Obs_gen_abs=jet3_eta_gen_abs;
    }
    if (numbOfJetsSelected==4) {
      jet_Obs_gen=jet4_eta_gen;
      jet_Obs=jet4_eta;
      jet_Obs_gen_abs=jet4_eta_gen_abs;
    }
    return;
  }

  if (whichtype=="Ht"){
    jet_Obs_gen=0;
    jet_Obs=0;
    if (jet_Obs_multi >= numbOfJetsSelected || numbOfJetsSelected==1){ //----------> Cambia molteplicita', tanto non cambia!!
      if (jet1_pt > 30 && jet1_pt < 7000 && fabs(jet1_eta)<2.4) jet_Obs += jet1_pt;
      if (jet2_pt > 30 && jet2_pt < 7000 && fabs(jet2_eta)<2.4) jet_Obs += jet2_pt;
      if (jet3_pt > 30 && jet3_pt < 7000 && fabs(jet3_eta)<2.4) jet_Obs += jet3_pt;
      if (jet4_pt > 30 && jet4_pt < 7000 && fabs(jet4_eta)<2.4) jet_Obs += jet4_pt;
      if (jet5_pt > 30 && jet5_pt < 7000 && fabs(jet5_eta)<2.4) jet_Obs += jet5_pt;
      if (jet6_pt > 30 && jet6_pt < 7000 && fabs(jet6_eta)<2.4) jet_Obs += jet6_pt;
      }
    
    if (jet_Obs_multi_gen >= numbOfJetsSelected || numbOfJetsSelected==1){

      if (jet1_pt_gen > 15 && jet1_pt_gen < 7000 && fabs(jet1_eta_gen)<2.5) jet_Obs_gen += jet1_pt_gen;
      if (jet2_pt_gen > 15 && jet2_pt_gen < 7000 && fabs(jet2_eta_gen)<2.5) jet_Obs_gen += jet2_pt_gen;
      if (jet3_pt_gen > 15 && jet3_pt_gen < 7000 && fabs(jet3_eta_gen)<2.5) jet_Obs_gen += jet3_pt_gen;
      if (jet4_pt_gen > 15 && jet4_pt_gen < 7000 && fabs(jet4_eta_gen)<2.5) jet_Obs_gen += jet4_pt_gen;
      if (jet5_pt_gen > 15 && jet5_pt_gen < 7000 && fabs(jet5_eta_gen)<2.5) jet_Obs_gen += jet5_pt_gen;
      if (jet6_pt_gen > 15 && jet6_pt_gen < 7000 && fabs(jet6_eta_gen)<2.5) jet_Obs_gen += jet6_pt_gen;
      
      if (jet1_pt_gen_abs > 30 && jet1_pt_gen_abs < 7000 && fabs(jet1_eta_gen_abs)<2.4) jet_Obs_gen_abs += jet1_pt_gen_abs;
      if (jet2_pt_gen_abs > 30 && jet2_pt_gen_abs < 7000 && fabs(jet2_eta_gen_abs)<2.4) jet_Obs_gen_abs += jet2_pt_gen_abs;
      if (jet3_pt_gen_abs > 30 && jet3_pt_gen_abs < 7000 && fabs(jet3_eta_gen_abs)<2.4) jet_Obs_gen_abs += jet3_pt_gen_abs;
      if (jet4_pt_gen_abs > 30 && jet4_pt_gen_abs < 7000 && fabs(jet4_eta_gen_abs)<2.4) jet_Obs_gen_abs += jet4_pt_gen_abs;
      if (jet5_pt_gen_abs > 30 && jet5_pt_gen_abs < 7000 && fabs(jet5_eta_gen_abs)<2.4) jet_Obs_gen_abs += jet5_pt_gen_abs;
      if (jet6_pt_gen_abs > 30 && jet6_pt_gen_abs < 7000 && fabs(jet6_eta_gen_abs)<2.4) jet_Obs_gen_abs += jet6_pt_gen_abs;
      }
      if (jet_Obs==0) jet_Obs=-9999;
      if (jet_Obs_gen==0) jet_Obs_gen=-9999;
      return;
  }

  if (whichtype=="Multiplicity"){
    //jet_Obs_gen=Jet_multiplicity_gen;//getNumberOfValidJets(Jet_multiplicity_gen, threshPt, threshEta, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);

    jet_Obs_gen=getNumberOfValidJets(Jet_multiplicity_gen, 15.0, 2.4, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);

    jet_Obs=getNumberOfValidJets(Jet_multiplicity, threshPt, threshEta, jet1_pt, jet2_pt, jet3_pt, jet4_pt, jet5_pt, jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta);

    jet_Obs_gen_abs=getNumberOfValidJets(Jet_multiplicity_gen, threshPt, threshEta, jet1_pt_gen_abs, jet2_pt_gen_abs, jet3_pt_gen_abs, jet4_pt_gen_abs, jet5_pt_gen_abs, jet6_pt_gen_abs, jet1_eta_gen_abs, jet2_eta_gen_abs, jet3_eta_gen_abs, jet4_eta_gen_abs, jet5_eta_gen_abs, jet6_eta_gen_abs);

  }

  return;
}

////////////////////////
//Set the observables Data
////////////////////////

void setObservablesData(int numbOfJetsSelected, string whichtype, double jet1_pt, double jet2_pt, double jet3_pt, double jet4_pt,  double jet5_pt,  double jet6_pt, double jet1_eta, double jet2_eta, double jet3_eta, double jet4_eta, double jet5_eta, double jet6_eta,int Jet_multiplicity){

  if (numbOfJetsSelected==1){jet_Obs_pt=jet1_pt;jet_Obs_eta=jet1_eta;}
  if (numbOfJetsSelected==2){jet_Obs_pt=jet2_pt;jet_Obs_eta=jet2_eta;}
  if (numbOfJetsSelected==3){jet_Obs_pt=jet3_pt;jet_Obs_eta=jet3_eta;}
  if (numbOfJetsSelected==4){jet_Obs_pt=jet4_pt;jet_Obs_eta=jet4_eta;}

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
    return;
  }

  if (whichtype=="Ht"){
    if (Jet_multiplicity >= numbOfJetsSelected || numbOfJetsSelected==1){
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
      minObsPlot=30;
      maxObsPlot=390;
      divPlot=18;

      if (isEle){
	kmin=7;
	kmax=8;
      }
      else{
	kmin=10;
	kmax=11;
    }
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }

    }
    if (numbOfJetsSelected==2){
      minObsPlot=30;
      maxObsPlot=330;
      divPlot=15;
    
      if (isEle){
	kmin=8;
	kmax=9;
      }
      else{
	kmin=9;
	kmax=10;
      }
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
    }
    if (numbOfJetsSelected==3){
      minObsPlot=30;
      maxObsPlot=190;
      divPlot=8;
      
      if (isEle){
	kmin=5;
	kmax=6;
      }
      else{
	kmin=5;
	kmax=6;
      }
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
    }
    if (numbOfJetsSelected==4){
      minObsPlot=30;
      maxObsPlot=130;
      divPlot=5;
     
      if (isEle){
	kmin=2;
	kmax=3;
      }
      else{
	kmin=4;
	kmax=5;
      }
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
    
    if (numbOfJetsSelected==1) {
    if (isEle){
      kmin=5;
      kmax=6;
    }
    else{
      kmin=7;
      kmax=8;
    }
      divPlot=24;
    }
    
    if (numbOfJetsSelected==2){
      if (isEle){
	kmin=3;
	kmax=4;
      }
      else{
	kmin=3;
	kmax=4;
    }
      divPlot=20;
    }
    
    if (numbOfJetsSelected==3){
      if (isEle){
	kmin=3;
	kmax=4;
      }
      else{
	kmin=4;
	kmax=5;
      }
      divPlot=16;
    }
    
    if (numbOfJetsSelected==4){
      if (isEle){
	kmin=4;
	kmax=5;
      }
      else{
	kmin=3;
	kmax=4;
      }
      divPlot=12;
    } 
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
  }
  
  if (whichtype=="Ht"){
    
    divPlot = 17; //da 40 Gev... 
    minObsPlot = 30;
    maxObsPlot = 710;
    kmin = 8;
    kmax = 9;

if (numbOfJetsSelected == 1){
      if (isEle){
	kmin=7;
	kmax=8;
      }
      else{
	kmin=9;
	kmax=10;
      }
    }
  if (numbOfJetsSelected == 2){
    minObsPlot = 60; //da 50 Gev
      maxObsPlot = 710;
      divPlot = 13;
      if (isEle){
	kmin=5;
	kmax=6;
      }

      else{
	kmin=7;
	kmax=8;
      }
    }
  if (numbOfJetsSelected == 3){
      divPlot = 14;
      minObsPlot = 90;
      maxObsPlot = 790;

      if (isEle){
	kmin=5;
	kmax=6;
      }
      else{
	kmin=7;
	kmax=8;
      }
      
    }
  if (numbOfJetsSelected == 4){                          
    if (isEle){
      kmin=6;
      kmax=7;
    }
    else{
      kmin=5;
      kmax=6;
    }
    divPlot = 10; //da 60 GeV
    minObsPlot = 120;
    maxObsPlot = 720;
  }
  if (bayesianTests) {
    kmin=3;
    kmax=4;
  }
  }
  
  if (whichtype=="Multiplicity"){
    //divPlot=maxNJets-1;
    //minObsPlot=1;
    //maxObsPlot=maxNJets-1;
    divPlot=6.5; minObsPlot=0.5;maxObsPlot=6.5;
    if (isEle){
      kmin=4;
      kmax=5;
    }
    else{
      kmin=4;
      kmax=5;
    }
    
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


/////////////////////////////////
// Function to verify the Matching GEN-RECO
//////////////////////////////////

bool verifyMatching(string whichtype, double Obs_gen, double Obs, double Obs_gen_pt, double Obs_pt, double Obs_gen_eta, int Jet_multiplicity, int Jet_multiplicity_gen, int numbOfJets){
  //Matching is done in 


  if (whichtype=="Multiplicity"){
    if (Obs_gen>=1 && Obs>=1) return true;
  }

  if (whichtype=="Ht"){
    if (Jet_multiplicity>=numbOfJets && Jet_multiplicity_gen>=1) return true;
  }

  if (whichtype=="Pt"){
    if (fabs(Obs_gen_pt>=15) && fabs(Obs_gen_eta)<2.5) return true;
  }

  if (whichtype=="Eta"){
    if (fabs(Obs_gen_pt>=15) && fabs(Obs_gen_eta)<2.5) return true;
  }
  
  return false;
}

bool verifyAcceptance(string whichtype, double Obs, double Obs_pt, int Jet_multiplicity, double Obs_eta, int numbOfJets){
  double limit=0;
  if (whichtype=="Multiplicity") limit=1;
  if (whichtype=="Eta") limit=2.4;
  if (whichtype=="Pt") limit=30;
  if (whichtype=="Ht") limit=30; 

  if (whichtype=="Multiplicity"){
    if (Jet_multiplicity>=limit) return true;
  }

  if (whichtype=="Ht"){
    if (Jet_multiplicity>=numbOfJets) return true;
  }

  if (whichtype=="Pt"){
    if (Obs_pt>=30 && fabs(Obs_eta)<=2.4 && fabs(Obs)>=limit) return true;
  }
  
  if (whichtype=="Eta"){
    if (Obs_pt>=30 && fabs(Obs_eta)<=2.4 && fabs(Obs)<=limit) return true;
  }
 return false;
}

////////////////////////////////////////
// Thus funciont is used to adapt asymmetric binning in the SVD unfolding
//
// Takes the energy of the jet and returns an interger indicating which is the new bin for this variable, provided a definition of the binning you wish to have

int returnBinInAsymmetricBinRange(std::vector<double> binRanges, double variableValue){
  int i=0;
  int vectorsize=binRanges.size();

  for (int j=0; j<vectorsize; j++){
    if (variableValue>binRanges[j] && variableValue <=binRanges[j+1]) i=j;
  }
  return i;
}
