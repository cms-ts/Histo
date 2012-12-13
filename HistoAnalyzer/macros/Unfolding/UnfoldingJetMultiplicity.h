#include "TSVDUnfold.h"

TH1D *NTrue = new TH1D ("NTrue", "N Truth", maxNJets-0.5, 0.5, maxNJets-0.5);
TH1D *NTruepythia = new TH1D ("NTruepythia", "N Truth using pythia", maxNJets-0.5, 0.5, maxNJets-0.5);
TH1D *NData = new TH1D ("NData", "N DATA Measured", maxNJets-0.5, 0.5, maxNJets-0.5);
TH2D *NMatx = new TH2D ("N hMatx", "Unfolding Matrix in # of jets + Z", maxNJets-0.5, 0.5, maxNJets-0.5, maxNJets-0.5, 0.5, maxNJets-0.5);
TH2D *NMatxpythia = new TH2D ("N hMatxpythia", "Unfolding Matrix in # of jets + Z using pythia",maxNJets-0.5, 0.5, maxNJets-0.5, maxNJets-0.5, 0.5, maxNJets-0.5);
TH2D *NMatxlong = new TH2D ("N hMatxlong", "Unfolding Matrix in # of jets + Z", maxNJets, 0, maxNJets, maxNJets, 0, maxNJets);
TH1D *NMCreco = new TH1D ("N mcreco", "N mcreco", maxNJets-0.5, 0.5, maxNJets-0.5);
TH1D *NMCrecoratio_ = new TH1D ("N mcrecoratio_", "N mcreco_", maxNJets-0.5, 0.5, maxNJets-0.5);
TH1D *NData2 = new TH1D ("N data2", "N DATA Measured2", maxNJets-0.5, 0.5, maxNJets-0.5);
TH1F *relativebkgN = new TH1F("relativebkgN", "relativebkg bin contribution",maxNJets-0.5,0.5,maxNJets-0.5);

//Module D histo
TH1D* modD;


TH1F *JetMultiplicityUnfolded;
int kminN=maxNJets-1;
int kmaxN=maxNJets;
bool spanKvaluesN=false;
bool UnfoldDistributions=true; //if true, it performs the unfolding...

int getNumberOfValidGenJets(double threshPt, double threshEta, double jet1_pt_gen, double jet2_pt_gen, double jet3_pt_gen, double jet4_pt_gen, double jet5_pt_gen, double jet6_pt_gen, double jet1_eta_gen, double jet2_eta_gen, double jet3_eta_gen, double jet4_eta_gen, double jet5_eta_gen, double jet6_eta_gen){
  int counter=0;

  for (int i=1;i<=6; i++){
    if (i==1){
      if (jet1_pt_gen>threshPt && fabs(jet1_eta_gen)<threshEta ) counter++;
    }
    
    if (i==2){
      if (jet2_pt_gen>threshPt && fabs(jet2_eta_gen)<threshEta ) counter++;
    }

    if (i==3){
      if (jet3_pt_gen>threshPt && fabs(jet3_eta_gen)<threshEta ) counter++;
    }

    if (i==4){
      if (jet4_pt_gen>threshPt && fabs(jet4_eta_gen)<threshEta ) counter++;
    }

    if (i==5){
      if (jet5_pt_gen>threshPt && fabs(jet5_eta_gen)<threshEta ) counter++;
    }

    if (i==6){
      if (jet6_pt_gen>threshPt && fabs(jet6_eta_gen)<threshEta ) counter++;
    }
    
  }// for
  return counter;
}// end

int getNumberOfFakeGenJets(int Jet_multiplicity_gen, double threshpt, double thresheta,double jet1_pt_gen, double jet2_pt_gen, double jet3_pt_gen, double jet4_pt_gen, double jet5_pt_gen, double jet6_pt_gen, double jet1_eta_gen, double jet2_eta_gen, double jet3_eta_gen, double jet4_eta_gen, double jet5_eta_gen, double jet6_eta_gen){
  int counter=0;
  for (int i=1;i<=Jet_multiplicity_gen; i++){
    if (i==1){
      if (jet1_pt_gen<threshpt || fabs(jet1_eta_gen)>thresheta ) counter++;
    }
    
    if (i==2){
      if (jet2_pt_gen<threshpt || fabs(jet2_eta_gen)>thresheta ) counter++;
    }

    if (i==3){
      if (jet3_pt_gen<threshpt || fabs(jet3_eta_gen)>thresheta ) counter++;
    }

    if (i==4){
      if (jet4_pt_gen<threshpt || fabs(jet4_eta_gen)>thresheta ) counter++;
    }

    if (i==5){
      if (jet5_pt_gen<threshpt || fabs(jet5_eta_gen)>thresheta ) counter++;
    }

    if (i==6){
      if (jet6_pt_gen<threshpt || fabs(jet6_eta_gen)>thresheta ) counter++;
    }
    
  }// for
  return counter;
}// end

void Unfolding::LoopJetMultiplicity ()
{
  cout<<endl;
  cout<<"*********************************"<<endl;
  cout<<"Unfolding number of Jets"<<endl;
  cout<<"*********************************"<<endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  //////////////////////// VARIOUS CLOSURE TESTS ///////////////////
  bool indentityCheck=false;    //to perform identity check
  bool splitCheck=false;
  bool pythiaCheck=false;
  bool bayesianTests=false;
  //////////////////////////////////////////////////////////////////
  
  //Settings for Jet Multiplicity
  kminN=6;
  kmaxN=7;
  
  if (bayesianTests) {
    kminN=3;
    kmaxN=4;
  }
  if (spanKvaluesN){
    kminN=2;
    kmaxN=maxNJets; 
  }

  if (splitCheck) indentityCheck=true;
  if (pythiaCheck) indentityCheck=true;
  
  if (indentityCheck) {
    correctForEff=false;
    correctForBkg=false;
  }

  string sdatadir=sdata+":/validationJEC";
  if (isMu) sdatadir=sdata+":/EPTmuoReco";

  //string smcdir=smc+":/validationJEC";
  string smcdir=smc+":/EPTmuoReco_MC";  
  if (isMu) {
    smcdir=smc+":/EPTmuoReco_MC";
  }
  if (indentityCheck) sdatadir=smcdir;

  //if (pythiaCheck) smcdir=smcpythia+":/EPTmuoReco_MC";  

  fA->cd (smcdir.c_str());
  gDirectory->ls("tree*");
  TTree *tree_fA= (TTree *) gDirectory->Get ("treeValidationJEC_");
  if (isMu) tree_fA= (TTree *) gDirectory->Get ("treeValidationJECMu_");

  fB->cd (sdatadir.c_str());
  gDirectory->ls("tree*");

  TTree *tree_fB;
  if (!indentityCheck) tree_fB= (TTree *) gDirectory->Get ("treeValidationJEC_");
  //FOR closure tests
  if (indentityCheck){  
    //if (pythiaCheck) {
    //TFile *_file0 = TFile::Open(smcpythia.c_str()); 
    //_file0->cd("EPTmuoReco_MC");
    //cout<<"Activate the pythia tests->"<<smcpythia<<endl;
    //if (!isMu)tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");
    //if (isMu) tree_fB= (TTree *) gDirectory->Get ("treeValidationJECMu_");
    //smcdir=smcpythia;
    //}
    //else{
    fB->cd (smcdir.c_str());
    if (!isMu)tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");
    if (isMu) tree_fB= (TTree *) gDirectory->Get ("treeValidationJECMu_");
    //}
  }

  cout<<"#####################"<<endl;
  cout<<"You'are using"<<endl;
  cout<<sdatadir<<endl;
  cout<<smcdir<<endl;  
  cout<<"MC tree  is ->"<<tree_fA->GetName()<<endl;
  cout<<"Data tree is->"<<tree_fB->GetName()<<endl;  
  cout<<"#####################"<<endl;

  //Setting the errors
  NTrue->Sumw2();
  NMCreco->Sumw2();
  NMCrecoratio_->Sumw2();
  NData->Sumw2();
  
  int count=0;
  int countGEN=0;  

  RooUnfoldResponse unfold_secondpythia(NMCreco,NTrue);
  RooUnfoldResponse unfold_second(NMCreco,NTrue);
  unfold_secondpythia.UseOverflow();
  unfold_second.UseOverflow();


  if (pythiaCheck){	
    //fill the matrix --->
    fPythia = new TFile (smcpythia.c_str());
    smcpythia=smcpythia+":/EPTmuoReco_MC";
    cout<<"-------------------------------------- Pythia check! -------------------"<<endl;
    cout<<smcpythia<<endl;
    fPythia->cd (smcpythia.c_str());
    gDirectory->ls("tree*");
    TTree *tree_fC= (TTree *) gDirectory->Get ("treeValidationJEC_");
    if (isMu) tree_fC= (TTree *) gDirectory->Get ("treeValidationJECMu_");

    //Filling the other response Matrix
    fChain = tree_fC;
    Init (fChain);
    Long64_t nentries = fChain->GetEntriesFast ();
    Long64_t nbytes = 0, nb = 0;
    if (fChain == 0) return;

    for (Long64_t jentry = 0; jentry < nentries; jentry++){
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      if (Jet_multiplicity > 30 || Jet_multiplicity_gen > 30 ) continue;
      
      if (isElectron!=isEle) {
	cout<<"is_Electron(rootupla) is ->"<<isElectron<<", while the isElectron(unfolding) is "<<isEle<<" You are using the wrong TTree, ele instead of muons or viceversa..exit"<<endl;
	return;
      }
      int offsetJetMultiplicity=0;
      offsetJetMultiplicity=getNumberOfFakeGenJets(Jet_multiplicity_gen,threshPt,threshEta,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet5_pt_gen,jet6_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen,jet5_eta_gen,jet6_eta_gen);

      if (Jet_multiplicity > 0 || Jet_multiplicity_gen-offsetJetMultiplicity > 0){
	NMatxpythia->Fill (Jet_multiplicity, Jet_multiplicity_gen-offsetJetMultiplicity,evWeightSherpa);
	if (Jet_multiplicity >= 1 &&  (Jet_multiplicity_gen-offsetJetMultiplicity) >= 1) unfold_secondpythia.Fill(Jet_multiplicity, Jet_multiplicity_gen-offsetJetMultiplicity,evWeightSherpa);
	if (Jet_multiplicity >= 1 && !( (Jet_multiplicity_gen-offsetJetMultiplicity) >= 1)) unfold_secondpythia.Fake(Jet_multiplicity,evWeightSherpa);
	if (!(Jet_multiplicity >= 1) &&  (Jet_multiplicity_gen-offsetJetMultiplicity) >= 1) unfold_secondpythia.Miss(Jet_multiplicity_gen-offsetJetMultiplicity,evWeightSherpa);
      }
    }
  }

  int categoryCounter=0;
  double fillCounter=0;
  double missCounter=0;
  double fakeCounter=0;

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;	
  Init (fChain);

  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  int counter3=0;

  if (splitCheck) {
    nentries=(int) 2.0*(nentries/3.);
    cout<<"Slitcheck is active, so Dataset A has now "<<nentries<<endl;
  }

  if (fChain == 0) return;

  for (Long64_t jentry = 0; jentry < nentries; jentry++){
    Long64_t ientry = LoadTree (jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry (jentry);
    nbytes += nb;
 
    if (Jet_multiplicity > 30 || Jet_multiplicity_gen > 30 ) continue;

    double realGenJetMultiplicity=getNumberOfValidGenJets(threshPt,threshEta,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet5_pt_gen,jet6_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen,jet5_eta_gen,jet6_eta_gen);
    if (correctForSecondaryMigrations==true && (realGenJetMultiplicity>0) ){
      
	if ( (l1_pt_gen<20 || l2_pt_gen<20) & (recoZInAcceptance==1) ){
	  //cout<<"lepton below threshold->"<<l1_pt_gen<<" - "<<l2_pt_gen<<endl;
	unfold_second.Fake(Jet_multiplicity);
	continue;
    }
      
      if ( (invMass_gen>111 || invMass_gen<71) & (recoZInAcceptance==1) ){
	//cout<<"inv mass->"<<invMass_gen<<endl;
	unfold_second.Fake(Jet_multiplicity);
	continue;
    }

      
      if ( (( fabs(l1_eta_gen)>1.442 & fabs(l1_eta_gen)<1.566) || (( fabs(l2_eta_gen)>1.442 & fabs(l2_eta_gen)<1.566))) && (genZInAcceptance==1)  && (recoZInAcceptance==0) && isElectron ){
      	//cout<<"this electorn was on the crack, not measured!"<<endl;
	unfold_second.Miss(realGenJetMultiplicity);
	continue;
      }

      if (recoZInAcceptance==1 && genZInAcceptance==0){
	//cout<<"This was not a generated event!"<<endl;
	unfold_second.Fake(Jet_multiplicity);
	continue;
      }
    }

    
    if (recoZInAcceptance==0) continue;    
    
    if (isElectron!=isEle) {
      cout<<"is_Electron(rootupla) is ->"<<isElectron<<", while the isElectron(unfolding) is "<<isEle<<" You are using the wrong TTree, ele instead of muons or viceversa..exit"<<endl;
      return;
    }
    
    //if (jentry>10) continue;

    categoryCounter++;

    if (Jet_multiplicity >= 1 ||  realGenJetMultiplicity >= 1){
      counter3++;
      // To control and exclude jets having energy below "thresh"
      int offsetJetMultiplicity=0;
      offsetJetMultiplicity=getNumberOfFakeGenJets(Jet_multiplicity_gen,threshPt,threshEta,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet5_pt_gen,jet6_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen,jet5_eta_gen,jet6_eta_gen);

      double effcorrmc=1.0*evWeight;
      if (indentityCheck) effcorrmc=1.0; //Quando fai il closure test non vuoi correggere per i weights...

      if (correctForEff){
	if (!useElectronsToCorrect){
	  std::vector<double> valuesmc=getEfficiencyCorrectionJetMultiplicity(fAeff,fBeff,Jet_multiplicity,"MC");
	  effcorrmc=effcorrmc*(1.00/valuesmc[0]);	
	  double efferrmc=valuesmc[1]/pow(valuesmc[0],2); 
	  NTrue->Fill (realGenJetMultiplicity);
	  NMCreco->Fill (Jet_multiplicity,effcorrmc);
	  NMCrecoratio_->Fill(Jet_multiplicity,effcorrmc);
	  NMatx->Fill (Jet_multiplicity, realGenJetMultiplicity,effcorrmc);
	  NMatxlong->Fill (Jet_multiplicity, realGenJetMultiplicity,effcorrmc);
	}
	else{
	  effcorrmc=effcorrmc*1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);
	  //effcorrmc=1.0;
	  NMCreco->Fill (Jet_multiplicity,effcorrmc);
	  NMCrecoratio_->Fill(Jet_multiplicity,effcorrmc);
	  NMatx->Fill (Jet_multiplicity, realGenJetMultiplicity,effcorrmc);
	  NMatxlong->Fill (Jet_multiplicity, realGenJetMultiplicity,effcorrmc);
	  if (Jet_multiplicity >= 1 &&  (realGenJetMultiplicity) >= 1) {
	    unfold_second.Fill(Jet_multiplicity, realGenJetMultiplicity,effcorrmc);
	    fillCounter+=effcorrmc;
	  NTrue->Fill (realGenJetMultiplicity);
	  }
	  if (Jet_multiplicity >= 1 && !( (realGenJetMultiplicity) >= 1)) {
	    unfold_second.Fake(Jet_multiplicity,effcorrmc);
	    fakeCounter+=1*effcorrmc;
	  NTrue->Fill (realGenJetMultiplicity);
	  }
	  if (!(Jet_multiplicity >= 1) &&  (realGenJetMultiplicity) >= 1) {
	    unfold_second.Miss(realGenJetMultiplicity);
	    missCounter+=1*effcorrmc;
	  NTrue->Fill (realGenJetMultiplicity);
	  }
	}
      }
      else{
	NTrue->Fill (realGenJetMultiplicity);
	NMCreco->Fill (Jet_multiplicity);
	NMCrecoratio_->Fill(Jet_multiplicity);
	if (jet1_pt_gen<30) countGEN++;
	if (jet1_pt<30) count++;	
	NMatx->Fill (Jet_multiplicity, realGenJetMultiplicity);
	NMatxlong->Fill(Jet_multiplicity, realGenJetMultiplicity);
	//cout<<"jet_multip_gen->"<<realGenJetMultiplicity<<"  jet_multip->"<<Jet_multiplicity<<" jet1_pt_gen->"<<jet1_pt_gen<<" jet1_pt->"<<jet1_pt<<" jet1_eta_gen->"<<jet1_eta_gen<<"jet1_eta->"<<jet1_eta<<" jet2_pt_gen->"<<jet2_pt_gen<<" jet2_pt->"<<jet2_pt<<" jet2_eta_gen->"<<jet2_eta_gen<<endl;
      }
    }
  }

  cout<<"GEN >0 but <30 ->"<<countGEN<<" while RECO =0 ->"<<count<<endl;
  cout<<"the loop on MC has selected ->"<<counter3<<endl;
  cout<<"********************"<<endl;
  cout<<"number of events in MC training "<<categoryCounter<<endl;
  cout<<"number of events in MC training that fall in Fill "<<fillCounter<<endl;
  cout<<"number of events in MC training that fall in Miss "<<missCounter<<endl;
  cout<<"number of events in MC training that fall in Fakw "<<fakeCounter<<endl;
  cout<<"********************"<<endl;

  int dataCounter=0;
  double sumOnData=0;
  
  /*Loop on data */
  fChain = tree_fB;	
  Init (fChain);	
  Long64_t nentries2 = fChain->GetEntriesFast ();
  Long64_t nb2 = 0;
  
  if (fChain == 0) return;
  
  for (Long64_t jentry = 0; jentry < nentries2; jentry++) {
    
    Long64_t ientry = LoadTree (jentry);
    if (ientry < 0)
      break;
    nb2 = fChain->GetEntry (jentry);
    nbytes += nb2;

    if (Jet_multiplicity > 30) continue;

    if (Jet_multiplicity >= 1){
      if (correctForEff){
	if (!useElectronsToCorrect){
	  std::vector<double> valuesdata=getEfficiencyCorrectionJetMultiplicity(fAeff,fBeff,Jet_multiplicity,"Data");
	  double effcorrdata=1.00/valuesdata[0];	
	  double efferrdata=valuesdata[1]/pow(valuesdata[0],2);
	  NData->Fill (Jet_multiplicity,effcorrdata);
	  NData2->Fill (Jet_multiplicity,effcorrdata);
	}
	else{
	  double effcorrdata=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
	  NData->Fill (Jet_multiplicity,effcorrdata);
	  NData2->Fill (Jet_multiplicity,effcorrdata);
	  sumOnData+=effcorrdata;
	}
      }
      else{
	NData->Fill (Jet_multiplicity);
	NData2->Fill (Jet_multiplicity);	
      }
    }
  }

  ///   NOTA BENE!!
  //PER QUALCHE RAGIONE NON BISOGNA NORMALIZZARE NULLA PRIMA DI FARE LA RESPONSE MATRIX!!
  //////////////
  // MC Normalization
  //////////////
  double ScaleMCData = ((double)NData->GetEntries()/(double)NMCreco->GetEntries());
  cout<<"Scale is->"<<ScaleMCData<<endl;
  cout<<"In data your integral-efficinecy is "<<sumOnData<<endl;

  /////////////////////////
  //  Correct for background
  /////////////////////////
  
  if (correctForBkg){
    std::vector<double> bckcoeff;
    bckcoeff=getBackgroundContributions(bkgstring,"jet_Multiplicity");
    for (unsigned int k=0; k< maxNJets; k++){
      NData->SetBinContent(k+1, NData->GetBinContent(k+1) - bckcoeff[k]);  //K+1 perche' c'e' il bkgr a 0 Jets...
      if (NData->GetBinContent(k+1)>0) {
	relativebkgN->SetBinContent(k+1,bckcoeff[k]/NData->GetBinContent(k+1));
	cout<<"Data:"<<NData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is "<<bckcoeff[k]/NData->GetBinContent(k+1)<<endl;	
      }
      else {
	relativebkgN->SetBinContent(k+1,0);
	cout<<"Data:"<<NData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is 0"<<endl;
      }
      cout<<"after "<<bckcoeff[k]/NData->GetBinContent(k+1)<<endl;
    }
  }
  
  // Fill the matrix response with the MC values, this time as histograms!
  if (pythiaCheck) NMatx=NMatxpythia;
    
  RooUnfoldResponse response_N(NMCreco, NTrue, NMatx);
  response_N.UseOverflow();

  cout<<"***********************"<<endl;
  cout<<"MC will be normalized to data, using entries"<<endl;
  cout<<"N entries in Data:"<<NData->GetEntries()<<" and MC:"<<NMCreco->GetEntries()<<" ratio->"<<ScaleMCData<<endl;
  cout<<endl;
  NMCreco->Scale (ScaleMCData);
  NTrue->Scale (ScaleMCData);
  NMCrecoratio_->Scale (ScaleMCData);
    
  int k0=1;
  int k1=2;
  if (bayesianTests){
  k0=0;
  k1=1;    
  }

  TH1D *NTrueSwap;

  if(!differentialCrossSection){
    response_N=unfold_second;
  }
  
  if (pythiaCheck) {
    NTrueSwap= (TH1D*) NTrue->Clone("NTrue");
    NTrueSwap->SetName("NTrueSwap"); 
    NTrue=NTruepythia;
    NMatx=NMatxpythia;
    response_N=unfold_secondpythia;
  }

  if (pythiaCheck) {
    NTrue=NTrueSwap; //Perche' fai questo? Per riprendere la MD MC truth e confrontare con il ratio
  }

  
  //Repeating each algorithm
  for (int j=k0; j<k1; j++){
    string method;
    if (UnfoldDistributions){
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";

    cout<<"Running "<<method<<" method"<<endl;
    
    //Optimizing the k value
    for (int k=kminN; k<kmaxN; k++){
      int myNumber=k;
      stringstream num;
      num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Z + N Jets distribution. "+title;
      cout<<title<<endl;
      
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_N (&response_N, NData, myNumber);
	NReco = (TH1D *) unfold_N.Hreco ();
	unfold_N.PrintTable(cout,NTrue);
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_N (&unfold_second, NData, myNumber,1000);	// OR
	NReco = (TH1D *) unfold_N.Hreco ();
	unfold_N.PrintTable(cout,NTrue);
	cout<<"Chi2 of this k parameter(k="<<myNumber<<")<< is "<<unfold_N.Chi2(NTrue,RooUnfold::kCovariance)<<endl;
      
	TSVDUnfold unfold_t (NData, NTrue,NMCreco,NMatx); // per IL TEST PYTHIA!!!!!!!!!!!!!!!!!!!!!!
	TH1D* unfresult = unfold_t.Unfold( myNumber );
	modD = unfold_t.GetD();
      }

      NReco->Sumw2();

      if (differentialCrossSection){
	NReco->Scale(1./NReco->Integral());		
	NTrue->Scale(1./NTrue->Integral());
	NMCreco->Scale(1./NMCreco->Integral());
	NData->Scale(1./NData->Integral());
      }

      JetMultiplicityUnfolded=(TH1F*) NReco->Clone("NReco");
      JetMultiplicityUnfolded->SetName("JetMultiplicityUnfolded");

      //Save info to evaluate the unfolding uncertainties... Da fare a mano ogni volta cambiando il MC e vedendo la differenza nei dati... poi prendi i dati, e li trascrivi nella macro!
      for (int c=0;c<6;c ++){
	cout<<NReco->GetBinContent(c+1)<<endl;
      }

      cmultip->cd ();

      if (UnfoldDistributions){
      TPad *pad1 = new TPad ("pad1", "pad1",0.01,0.33,0.99,0.99);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      pad1->SetTopMargin(0.1);
      pad1->SetBottomMargin(0.01);
      pad1->SetRightMargin(0.1);
      pad1->SetFillStyle(0);

      title2="Number of jet + Z distribution. "+title;
      NReco->SetTitle (title2.c_str());
      NReco->GetXaxis ()->SetTitle ("");
      if (!isMu) NReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/dN");
      if (isMu) NReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/dN");

      NReco->SetMarkerStyle (20);
      NData->SetMarkerStyle (21);
      NData->SetLineColor(kGreen);
      
      NReco->SetMarkerStyle (20);
      NReco->SetStats(0);
      NReco->GetXaxis()->SetTitle("# of Jets");
      NReco->GetXaxis()->SetTitleSize(0.00);
      NReco->GetYaxis()->SetLabelSize(0.07);
      NReco->GetXaxis()->SetLabelSize(0.00);
      NReco->GetYaxis()->SetTitleSize(0.08);
      NReco->GetYaxis()->SetTitleOffset(0.76);
      NReco->SetTitle("");
      NReco->Draw("EP");		//risultato dell'unfolding
      NReco->SetLineColor (kRed);
      NReco->SetLineWidth (2);
      NMCreco->Draw();
      NMCreco->SetLineColor (kBlue + 1);
      NMCreco->SetLineStyle (2);
      NTrue->SetLineColor (kBlack);
      NMCreco->SetLineWidth (2);
      NTrue->SetLineWidth (2);

      NTrue->Draw ("EPSAME");
      NData2->SetLineColor(kGreen+1);
      NData2->Draw("EPSAME");

      NReco->DrawCopy ();
      pad1->SetLogy (1);
      NTrue->Draw ("same");
      NMCreco->Draw ("same");
      NData->SetLineStyle(2);
      NData->Draw("same");

      //      pad1->SetBottomMargin (0);
      NReco->SetTitleSize (0);

      NTrue->SetTitleSize (0);

      for(int i=1; i<=maxNJets; i++){
	double x = NReco->GetBinContent(i);
	cout << x << endl;
      }  

      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (NReco, "Data Unfolded", "LP20");
      legend_d->AddEntry (NTrue, "MC truth", "L");
      legend_d->AddEntry (NMCreco, "MC reco", "L");
      legend_d->AddEntry(NData,"Data Folded","L");
      legend_d->Draw ("same");

      /* Save Jet Multiplicity */

      pad1->Update();
	
      cmultip->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2",0.01,0.01,0.99,0.32);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      pad2->SetTopMargin(0.01);
      pad2->SetBottomMargin(0.3);
      pad2->SetRightMargin(0.1);
      pad2->SetFillStyle(0);

      NReco->GetXaxis ()->SetLabelSize (0.1);
      NReco->GetYaxis ()->SetLabelSize (0.08);
      NReco->SetStats (0);
      NReco->Divide (NTrue);
      NReco->SetMarkerStyle (6);
      NReco->GetXaxis ()->SetLabelSize (0.06);
      NReco->GetYaxis ()->SetLabelSize (0.06);
      NReco->GetXaxis ()->SetTitleSize (0);
      NReco->GetYaxis ()->SetTitleSize (0.06);
      NReco->GetYaxis ()->SetTitleOffset (0.5);

      NReco->GetYaxis ()->SetRangeUser (0.3, 1.7);
      //NReco->GetXaxis ()->SetRangeUser (0, 7.5);
      NReco->SetMarkerStyle (20);
      NReco->SetLineWidth (0);
      NReco->SetTitle ("");
      NReco->SetStats(0);
      NReco->GetXaxis ()->SetLabelSize (0.1);
      NReco->GetXaxis ()->SetTitleSize (0);
      NReco->GetYaxis ()->SetTitleSize (0.06);
      NReco->GetYaxis ()->SetTitleOffset (0.5);

      //NReco->GetXaxis ()->SetRangeUser (0, 5);
      NReco->GetYaxis ()->SetTitle ("Ratios");
      NReco->GetXaxis ()->SetTitle("jet Multiplicity");
      NReco->SetMarkerStyle (20);
      NReco->SetLineWidth (0);
      NReco->SetTitle ("");
      NReco->SetLineWidth (0.1);
      NReco->GetYaxis()->SetNdivisions(7);
      NReco->GetXaxis()->SetTitleSize(0.14);
      NReco->GetXaxis()->SetLabelSize(0.14);
      NReco->GetYaxis()->SetLabelSize(0.11);
      NReco->GetYaxis()->SetTitleSize(0.11);
      NReco->GetYaxis()->SetTitleOffset(0.28);
      NReco->GetYaxis()->SetTitle("ratio data/MC");	    
    
      NReco->Draw ("ep");
      
      TH1F *NRecoClone= (TH1F*) NMCreco->Clone("NReco");
      NRecoClone->SetName("NRecoClone");
      NRecoClone->Sumw2();

      NRecoClone->Divide(NTrue);		
      NRecoClone->SetMarkerStyle (20);
      NRecoClone->SetMarkerSize(0.0);
      NRecoClone->SetTitle ("");
      NRecoClone->SetStats(1);
      NRecoClone->SetLineStyle(3);
      NRecoClone->SetLineColor(kMagenta+3);
      NRecoClone->SetStats(0);

      NRecoClone->Draw ("ep SAMES");
	    
      TF1 *f = new TF1("f","1",0,10);
      f->SetLineWidth(1);
      f->Draw("SAMES");

      TLegend *legend_w = new TLegend (0.197791, 0.736607, 0.394578, 0.9375);
      legend_w->SetFillColor (0);
      legend_w->SetFillStyle (0);
      legend_w->SetBorderSize (0);
      legend_w->AddEntry (NReco, "Data Unfolded / MC truth", "LP20");
      legend_w->AddEntry (NRecoClone, "MC reco / MC truth", "L");
      legend_w->Draw ("same");

      pad2->Update();

      string title3= s+"JETMULTI"+method+"_"+num.str();
      if (correctForEff) title3= s+"JETMULTI"+method+"_"+num.str()+"_effcorr.pdf";
      else title3= s+"JETMULTI"+method+"_"+num.str()+".pdf";
      if (isMu) s="Muons_"+s;
      cmultip->cd ();

      cmultip->Print(title3.c_str());
      num.str("");
      cout<<"PDF file saved (maybe) on "<<title3<<endl;
      }
    }
  }
  }

  double unfarea=JetMultiplicityUnfolded->Integral()/4890.0;
  cout<<"Your unfolding has an integral value of "<<unfarea<<endl;
  
  if (activateXSSuperseding){
    if (!isMu) {
      cout<<"Rescaled to "<<XSElectron[0]<<endl;
      JetMultiplicityUnfolded->Scale(XSElectron[0]/unfarea);
    }
    if (isMu) {
      cout<<"Rescaled to "<<XSMuon[0]<<endl;
      JetMultiplicityUnfolded->Scale(XSMuon[0]/unfarea);
    }
  }

  if (!UnfoldDistributions) JetMultiplicityUnfolded=(TH1F*) NData->Clone();
  JetMultiplicityUnfolded->SetName("JetMultiplicityUnfolded");

  TCanvas *moduloD= new TCanvas ("moduloD", "moduloD", 1000, 700);
  moduloD->cd ();
  gPad->SetLogy (1);
  modD->SetStats (111111);
  modD->GetXaxis()->SetTitle("K Parameters");
  modD->GetYaxis()->SetTitle("Value");
  modD->SetLineColor(kRed);
  modD->Draw();
  string title7=s+"moduloD_jetMulti.pdf";
  moduloD->Print(title7.c_str()); 

  if (saveFile){
    TFile* w = new TFile(filename.c_str(), "UPDATE");
    w->cd();
    JetMultiplicityUnfolded->Write();
    NTrue->Write();
    NMatx->Write();
    NData->Write();
    NMCreco->Write();
    w->Close();
  }  


  if (UnfoldDistributions){
  TCanvas *N =new TCanvas ("N jet response matrix", "N jet response matrix", 1000, 700);
  N->cd ();
  NMatxlong->SetStats (0);
  gPad->SetLogz (1);
  gPad->SetRightMargin(0.15);
  NMatxlong->SetTitle("");
  NMatxlong->GetXaxis()->SetTitle("Reconstructed # of Jets");
  NMatxlong->GetYaxis()->SetTitle("Generated # of Jets");
  gStyle->SetPalette (1);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  NMatxlong->SetMarkerColor (kBlack);
  //double entries=1.000/(double)NMatxlonglong->Integral();
  //NMatxlonglong->Scale(entries);
  NMatxlong->Draw ("COLZ,text");
  string title3= s+"MatrixjetMultiplicity.pdf";;
  N->Print(title3.c_str());
  }
}

