#include <vector>
#include <iostream>
#include <algorithm>
#include "TSVDUnfold.h"
#include <iostream>
#include <fstream>

using namespace std;

/*Initialize Variables*/
double minObsPlot=30;
double maxObsPlot=330;
int divPlot=15;
int kmin=1;
int kmax=1;
bool spanKvalues=false;
double jet_Obs_gen=0;
double jet_Obs=0;

TH1F *relativebkg = new TH1F("relativebkg", "relativebkg bin contribution",divPlot,0,divPlot);
TH1D *errors = new TH1D ("errors", "jet DATA Measured",divPlot,0,divPlot);
TH1D *errorstat = new TH1D ("errorstat", "errors",divPlot,0,divPlot);
TH1F *efficiencycorrections = new TH1F ("efficiencycorrections", "efficiencycorrections",60,0,3);       
TH1F *efficiencycorrectionsmc = new TH1F ("efficiencycorrections", "efficiencycorrections",60,0,3);
TH1D* modD; 

#include "SetObs.h" //Contains SetObservablesMC, SetObservablesData, SetPlotDiviisons, getNumberOfValidJets
#include "DrawUnfolding.h" //Contains DrawPlots
#include "BackgroundRemoval.h" // COntains correctForBackgrounds
#include "SaveUnfolding.h" // COntains correctForBackgrounds

TCanvas *c; 


TH1D* performUnfolding(string whichalgo, int kvalue, TH1D *jData, TH1D *jTrue, RooUnfoldResponse response_j, TH1D* jMCreco, TH2D* jMatx) //Specify which algo
{
  TH1D *unf;
  RooUnfoldBayes unfold_b (&response_j, jData, kvalue);  //NEVER,NEVER,NEVER set the parameter "1000" for the testing if you want to perform identity tests
  RooUnfoldSvd unfold_s (&response_j, jData, kvalue);
  
  if (whichalgo=="Bayes") {
    unf = (TH1D *) unfold_b.Hreco ();
    unfold_b.PrintTable(cout,jTrue);
    cout<<"Bayes: Chi2 of this k parameter(k="<<kvalue<<")<< is "<<unfold_b.Chi2(jTrue,RooUnfold::kErrors)<<endl;
    TVectorD vstat= unfold_b.ErecoV();
    TVectorD vunfo= unfold_b.ErecoV(RooUnfold::kCovToy);
    TVectorD vunfomat= unfold_b.ErecoV(RooUnfold::kCovariance);
    TVectorD vunfodiag= unfold_b.ErecoV(RooUnfold::kErrors);
  }
  else{
    unf = (TH1D *) unfold_s.Hreco ();
    unfold_s.PrintTable(cout,jTrue);
    TVectorD vstat= unfold_s.ErecoV();
    TVectorD vunfo= unfold_s.ErecoV(RooUnfold::kCovToy);
    TVectorD vunfomat= unfold_s.ErecoV(RooUnfold::kCovariance);
    TVectorD vunfodiag= unfold_s.ErecoV(RooUnfold::kErrors);
    TSVDUnfold unfold_modD (jData,jTrue,jMCreco,jMatx); // per calcolare il modulo
    TH1D* unfresult = unfold_modD.Unfold( kvalue); modD = unfold_modD.GetD();
  }
  
  cout<<"Set the error!!!!!!!!!!!"<<endl;
  for (unsigned int p=0;p<unf->GetNbinsX();p++){
    errors->SetBinContent(p+1,unf->GetBinError(p+1)); errorstat->SetBinContent(p+1,sqrt(unf->GetBinContent(p+1)));
  }
  //Returns vector of unfolding errors computed according to the withError flag:
  //0: Errors are the square root of the bin content
  //1: Errors from the diagonals of the covariance matrix given by the unfolding
  //2: Errors from the covariance matrix given by the unfolding
  //3: Errors from the covariance matrix from the variation of the results in toy MC tests
  // enum ErrorTreatment {      kNoError          //kErrors     //kCovariance //kCovToy     
  return unf;
}

void loopAndDumpEntries(TH1D *jData){
  for (unsigned int p=0;p<jData->GetNbinsX();p++){
    cout<<"Bin "<<p+1<<" has "<<jData->GetBinContent(p+1)<<" and error "<<jData->GetBinError(p+1)<<endl;;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////
//
//         Unfolding
//
///////////////////////////////


void UnfoldingVJets2011::LoopVJets (int numbOfJetsSelected,string whichtype, string whichalgo)
{

  cout<<"*********************************"<<endl;
  cout<<"Welcome in Unfolding of 2011 Distribution.."<<endl;
  cout<<"*********************************"<<endl;
  
  /////////////////////////
  // Set the kmin, kmax, minObsPlot, maxObsPlot (those are global variables)
  //////////////////////////

  setPlotsDivisionsAndRanges(numbOfJetsSelected,whichtype,whichalgo);
  cout<<"Automatic histograms allocation ("<<whichtype<<"-"<<numbOfJetsSelected<<" jets). divPlot->"<<divPlot<<" min->"<<minObsPlot<<" max->"<<maxObsPlot<<" kmin->"<<kmin<<" kmax->"<<kmax<<endl;
  double divPlot2=divPlot; double minObsPlot2=minObsPlot; double maxObsPlot2=maxObsPlot;
  if (whichtype=="Multiplicity")  {
    divPlot2=6.5; minObsPlot2=0.5;maxObsPlot2=6.5;
  }

  TH1D *jTrue = new TH1D ("jTrue", "jet Truth",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jData = new TH1D ("jData", "jet DATA Measured",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jReco = new TH1D ("jReco", "jet Unfolded DATA",divPlot2,minObsPlot2,maxObsPlot2);
  TH2D *jMatx = new TH2D ("jMatx", "Unfolding Matrix jeet",divPlot2,minObsPlot2,maxObsPlot2,divPlot2,minObsPlot2,maxObsPlot2);
  TH2D *jMatxlong = new TH2D ("jMatxlong", "Unfolding Matrix jeet long",divPlot2+1,minObsPlot2-((maxObsPlot2-minObsPlot2)/divPlot2),maxObsPlot2,divPlot2+1,minObsPlot2-((maxObsPlot2-minObsPlot2)/divPlot2),maxObsPlot2);
  TH1D *jMCreco = new TH1D ("jMCreco", "jet mcreco",divPlot2,minObsPlot2,maxObsPlot2);

  jData->Sumw2(); jTrue->Sumw2(); jReco->Sumw2(); jMatx->Sumw2(); jMatxlong->Sumw2(); jMCreco->Sumw2();

  //////////////////////////
  //Instanciate trees and CO
  //////////////////////////

  string sdatadir=sdata+":/validationJEC";
  if (isMu) sdatadir=sdata+":/EPTmuoReco";
    string smcdir=smc+":/EPTmuoReco_MC";  
  if (isMu) {smcdir=smc+":/EPTmuoReco_MC";}
  
  fA->cd (smcdir.c_str());
  gDirectory->ls("tree*");
  TTree *tree_fA= (TTree *) gDirectory->Get ("treeValidationJEC_");
  if (isMu) tree_fA= (TTree *) gDirectory->Get ("treeValidationJECMu_");
  
  fB->cd (sdatadir.c_str());
  gDirectory->ls("tree*");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");

  // Configure various closure tests, if you want to do it
  if (identityCheck || splitCheck || pythiaCheck){  
    correctForEff=false; correctForMCReweighting=false; correctForBkg=false;
    fB->cd (smcdir.c_str());
    tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");
    if (isMu) tree_fB= (TTree *) gDirectory->Get ("treeValidationJECMu_");

    if (pythiaCheck){
      fPythia = new TFile (smcpythia.c_str());
      smcpythia=smcpythia+":/EPTmuoReco_MC";
      cout<<"-------------------------------------- Pythia check! -------------------"<<endl;  cout<<smcpythia<<endl;
      fPythia->cd (smcpythia.c_str());
      gDirectory->ls("tree*");
      tree_fA= (TTree *) gDirectory->Get ("treeValidationJEC_");
    if (isMu) tree_fA= (TTree *) gDirectory->Get ("treeValidationJECMu_");
    }
  }

  //Some output to help debugging
  cout<<"#####################"<<endl;
  cout<<"You'are using"<<endl;
  cout<<sdatadir<<endl;
  cout<<smcdir<<endl;  
  cout<<"MC tree  is ->"<<tree_fA->GetName()<<endl;
  cout<<"Data tree is->"<<tree_fB->GetName()<<endl;  
  cout<<"#####################"<<endl;
  
  
  ///////////////////////////////////////
  /*costruisco la matrice di unfolding */
  ///////////////////////////////////////

  //New style for unfolding
  RooUnfoldResponse response_fillfake(jMCreco,jTrue);
  response_fillfake.UseOverflow();
  
  /* Loop Montecarlo */
  fChain = tree_fA;             
  Init (fChain);
  
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;
  int inTheGap=0; int recoButPtLow=0; int recoButEtaHigh=0; int recoButInvMassOut=0; int recoButNotGenerated=0; int genButNotReco=0; int recostructedEvents=0; int genOutsideTheLimits=0; int notGenNotReco=0; int recoinTheGap=0; int genRecoAfterGenCorr=0; int noGenRecoAfterGenCorr=0; int genNoRecoAfterGenCorr=0;//Simpatici counter 

  if (splitCheck) {
    nentries=(int) 20.0*(nentries/100.);
    cout<<"Splitcheck is active, so Dataset A (MC) has now "<<nentries<<endl;
  }

  if (fChain == 0) return; if (!doUnfold) nentries=0;

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      jet_Obs_gen=0;
      jet_Obs=0;
      
      if (Jet_multiplicity > 10 || Jet_multiplicity_gen > 10 ) continue;

      // Get Efficiency
      double effcorrmc=1.00;
      if (correctForMCReweighting) effcorrmc=effcorrmc*evWeight;      // Weights per il PU
      if (correctForEff) effcorrmc=effcorrmc/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);
      efficiencycorrectionsmc->Fill(effcorrmc);
      if (effcorrmc<1){
	cout<<"Low <1 correction for Eta1=>"<<e1_eta<<" Pt1=>"<<e1_pt<<" Et22=>"<<e2_eta<<" Pt2=>"<<e2_pt<<endl;
   	return;
      }

      //Fake Fill method
      int ValidGenJets=getNumberOfValidJets(Jet_multiplicity_gen, threshPt, threshEta, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);
      int ValidRecoJets=Jet_multiplicity;
      
      if (ValidGenJets<numbOfJetsSelected && ValidRecoJets <numbOfJetsSelected) continue;
   
      // Initialize the Observables
      setObservablesMC(numbOfJetsSelected, whichtype, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen,  jet5_pt_gen,  jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen, 
		       ValidGenJets, jet1_pt, jet2_pt, jet3_pt, jet4_pt,  jet5_pt,  jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta,ValidRecoJets);  

      if (jet_Obs==0 && whichtype=="Eta") {
	jet_Obs=-99;
      } 

      if (jet_Obs_gen==0 && whichtype=="Eta") {
	jet_Obs_gen=-99;
      } 

      //////////////////////////////////
      // Statistics
      //////////////////////////////////

      // Generated outside the accpetance!
      if (genZInAcceptance  && (l1_pt_gen<20 || l2_pt_gen<20 || fabs(l1_eta_gen)>2.4 || fabs(l2_eta_gen)>2.4 || invMass_gen>111 || invMass_gen<71)) genOutsideTheLimits++;
      // Generated Outside acceptance and not reco. skipped
      if ( (genZInAcceptance  && (l1_pt_gen<20 || l2_pt_gen<20 || fabs(l1_eta_gen)>2.4 || fabs(l2_eta_gen)>2.4 || invMass_gen>111 || invMass_gen<71)) && !recoZInAcceptance) {notGenNotReco++; continue;}
      //Generated Outside and Reco
      if (recoZInAcceptance && genZInAcceptance  && !((l1_pt_gen>20 && l2_pt_gen>20) && (fabs(l1_eta_gen)<2.4 && fabs(l2_eta_gen)<2.4) & (invMass_gen<111 && invMass_gen>71)) ) recoButNotGenerated++; //accounted afterwards! low pt , invmass, etc
      if (recoZInAcceptance) recostructedEvents++; 
      
      //account for the gap!
      if ( (fabs(l1_eta_gen)>1.442 && fabs(l1_eta_gen)<1.566 && fabs(l2_eta_gen)<2.4) || ( fabs(l2_eta_gen)>1.442 && fabs(l2_eta_gen)<1.566 && fabs(l1_eta_gen)<2.4) && l1_pt_gen>20 && l2_pt_gen>20 && (invMass_gen<111 && invMass_gen>71) && isElectron && !recoZInAcceptance){
	if (ValidGenJets >=numbOfJetsSelected) {
	  response_fillfake.Miss(jet_Obs_gen); 
	  inTheGap++; 
	}
	continue;
      }

      // If there are no Z reco, it is a miss. 
      if (!recoZInAcceptance && genZInAcceptance && (l1_pt_gen>20 && l2_pt_gen>20) && (fabs(l1_eta_gen)<2.4 && fabs(l2_eta_gen)<2.4) & (invMass_gen<111 && invMass_gen>71)  ){
	//if (ValidGenJets >=numbOfJetsSelected) response_fillfake.Miss(jet_Obs_gen);
	genButNotReco++; //Questa se vuoi e' l'essenza delle efficienze... Se c'e' questa attivata non serve a nulla l'effificeinza, perche' te la ricalcoli tu!
	continue;
      }

      if ( (l1_pt_gen<20 || l2_pt_gen<20) && (recoZInAcceptance) ){
	if (ValidRecoJets >=numbOfJetsSelected) response_fillfake.Fake(jet_Obs,effcorrmc); 
	recoButPtLow++; continue;
      }

      if ( (fabs(l1_eta_gen)>2.4 || fabs(l2_eta_gen)>2.4) && (recoZInAcceptance) ){
	if (ValidRecoJets >=numbOfJetsSelected) response_fillfake.Fake(jet_Obs,effcorrmc); 
	recoButEtaHigh++; continue;
      }
      
      if ( (invMass_gen>111 || invMass_gen<71) && (recoZInAcceptance) ){
	if (ValidRecoJets >=numbOfJetsSelected) response_fillfake.Fake(jet_Obs,effcorrmc);  
	recoButInvMassOut++; continue;
      }
      
      if ( (( fabs(l1_eta_gen)>1.442 && fabs(l1_eta_gen)<1.566) || ( fabs(l2_eta_gen)>1.442 && fabs(l2_eta_gen)<1.566)) && isElectron && recoZInAcceptance){
	if (ValidGenJets >=numbOfJetsSelected) response_fillfake.Fake(jet_Obs,effcorrmc); 
      recoinTheGap++; continue;
      }
      
      if (whichtype=="Multiplicity"){
	if (ValidGenJets >=numbOfJetsSelected && ValidRecoJets >= numbOfJetsSelected) {
	  response_fillfake.Fill(jet_Obs,jet_Obs_gen,effcorrmc); genRecoAfterGenCorr++;
	}
	if (!(ValidGenJets >=numbOfJetsSelected) && ValidRecoJets >= numbOfJetsSelected) {response_fillfake.Fake(jet_Obs,effcorrmc); noGenRecoAfterGenCorr++;}
	if (ValidGenJets >=numbOfJetsSelected && !(ValidRecoJets >= numbOfJetsSelected)) {response_fillfake.Miss(jet_Obs_gen); genNoRecoAfterGenCorr++;}
      }
      else{
	if (ValidGenJets >=numbOfJetsSelected && ValidRecoJets >= numbOfJetsSelected) {
	  if (jet1_pt>30 && fabs(jet1_eta<2.4) && (jet1_pt_gen>30 && fabs(jet1_eta_gen)<2.4) ) response_fillfake.Fill(jet_Obs,jet_Obs_gen,effcorrmc); 
	  if (!(jet1_pt>30 && fabs(jet1_eta<2.4)) && (jet1_pt_gen>30 && fabs(jet1_eta_gen)<2.4) ) response_fillfake.Miss(jet_Obs_gen); 
	  if (jet1_pt>30 && fabs(jet1_eta<2.4) && !((jet1_pt_gen>30 && fabs(jet1_eta_gen)<2.4)) ) response_fillfake.Fake(jet_Obs); 
	}
	if (!(ValidGenJets >=numbOfJetsSelected) && ValidRecoJets >= numbOfJetsSelected && jet1_pt>30 && fabs(jet1_eta<2.4)) response_fillfake.Fake(jet_Obs); 
	if (ValidGenJets >=numbOfJetsSelected && !(ValidRecoJets >= numbOfJetsSelected) && jet1_pt_gen>30 && fabs(jet1_eta_gen<2.4)) response_fillfake.Miss(jet_Obs_gen); 
      }

      //Filling histograms, old way, before the cuts...
      jMatx->Fill (jet_Obs, jet_Obs_gen,effcorrmc);        
      jMatxlong->Fill (jet_Obs, jet_Obs_gen,effcorrmc);        
      jTrue->Fill (jet_Obs_gen);
      jMCreco->Fill (jet_Obs,effcorrmc);
    }

  cout<<"Total Number of events inside the rootupla==>"<<nentries<<endl;
  cout<<"Generated Outside the detector limits=>"<<genOutsideTheLimits<<", of which "<<recoButNotGenerated<<" reconstructed."<<"So,"<<notGenNotReco<<" not reco not gen. Filling gap for ele with "<<inTheGap<<endl;
  cout<<"<Reconstructed events==>"<<recostructedEvents<<". Reco but gen in the gap=>"<<recoinTheGap<<" gen low pt=>"<<recoButPtLow<<" gen high eta=>"<<recoButEtaHigh<<" gen outInvMass=>"<<recoButInvMassOut<<" recoNotGen=>"<<recoButNotGenerated<<" genNotReco=>"<<genButNotReco<<endl;
  cout<<"Gen & Reco after GEN Level Correction=>"<<genRecoAfterGenCorr<<"Gen & !Reco=>"<<genNoRecoAfterGenCorr<<"!Gen & Reco=>"<<noGenRecoAfterGenCorr<<endl;
  //End Loop MC 

  /* Loop Data */
  fChain = tree_fB;
  Init (fChain);        
  Long64_t nentries2 = fChain->GetEntriesFast ();

  if (fChain == 0) return;

  for (Long64_t jentry = 0; jentry < nentries2; jentry++){
    if (jentry < 0) break;
    double nb2 = fChain->GetEntry (jentry);
    nbytes += nb2;
    jet_Obs=0;

    if (Jet_multiplicity > 10) continue;
    //if (fabs(e1_eta)<1.566 || fabs(e2_eta)<1.566 ) continue;

    setObservablesData(numbOfJetsSelected, whichtype, jet1_pt, jet2_pt, jet3_pt, jet4_pt, jet5_pt, jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta, Jet_multiplicity);
    double effcorrdata=1.0;
    if (correctForEff) effcorrdata=effcorrdata/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
    efficiencycorrections->Fill(effcorrdata);
    if (Jet_multiplicity >= numbOfJetsSelected) jData->Fill (jet_Obs,effcorrdata);
  }//End loop Data

  /// Background Sub
  if (correctForBkg) correctForBackground(numbOfJetsSelected,whichtype,jData,true); //bool -> activate verbosity
  
  //////////////////////////////
  ///
  ///     Unfolding Core
  ///
  //////////////////////////////
  
  //Old stile to perform the unfolding
  RooUnfoldResponse response_j(jMCreco, jTrue, jMatx); 
  response_j.UseOverflow();
  stringstream num;

  string method=whichalgo;
  cout<<"Running "<<method<<" method"<<endl;
  
  for (int k=kmin; k< kmax; k++){
    int myNumber=k; num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Jet pT diff xsec distribution. "+title;
      //if (whichalgo=="Bayes") jReco=performUnfolding(whichalgo, k, jData, jTrue, response_j,jMCreco, jMatx); //Specify which algo
      //if (whichalgo=="SVD") jReco=performUnfolding(whichalgo, k, jData, jTrue,response_fillfake, jMCreco,jMatx);
      if (doUnfold) jReco=performUnfolding(whichalgo, k, jData, jTrue,response_fillfake, jMCreco,jMatx);
      else{
      jReco=(TH1D*) jData->Clone("jData");
      jReco->SetName("jReco");
      }
      num.str("");
  } 

  if (identityCheck || splitCheck || pythiaCheck){
    jReco->Scale(1./jReco->Integral());             
    jTrue->Scale(1./jTrue->Integral());
    jMCreco->Scale(1./jMCreco->Integral());
    jData->Scale(1./jData->Integral());
  }

  //Drawing Histograms
  if (doUnfold) { c= drawPlots(jReco,jData,jTrue,jMCreco,jMatxlong,numbOfJetsSelected,whichtype, whichalgo, kmin); c->Draw(); }

  //Normalization 

  double unfarea=jReco->Integral()/4890.0;
  cout<<"Your unfolding has an integral value of "<<unfarea<<endl;

  if (activateXSSuperseding && doUnfold){
    if (!isMu) {
      cout<<"Rescaled to "<<XSElectron[numbOfJetsSelected-1]<<endl;
      jReco->Scale(XSElectron[numbOfJetsSelected-1]/unfarea);
    }
    if (isMu) {
      cout<<"Rescaled to "<<XSMuon[numbOfJetsSelected-1]<<endl;
      jReco->Scale(XSMuon[numbOfJetsSelected-1]/unfarea);
    }
  }

  if (saveFile) saveIntoFile(numbOfJetsSelected, whichtype, jReco, jTrue, jMatx, jMCreco, jData);

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

}

