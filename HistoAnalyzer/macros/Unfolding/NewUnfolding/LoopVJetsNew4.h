#include <vector>
#include <iostream>
#include <algorithm>
#include "TSVDUnfold.h"
#include <iostream>
#include <fstream>
#include "JERCorrection.h"

using namespace std;

/*Initialize Variables*/
double minObsPlot=30;
double maxObsPlot=330;
int divPlot=15;
int kmin=1;
int kmax=1;
bool spanKvalues=false;
double jet_Obs_gen=0;double jet_Obs=0;
double jet_Obs_pt_gen=0;double jet_Obs_pt=0;
double jet_Obs_eta_gen=0;double jet_Obs_eta=0;

TH1F *relativebkg = new TH1F("relativebkg", "relativebkg bin contribution",divPlot,0,divPlot);
TH1D *errors = new TH1D ("errors", "jet DATA Measured",divPlot,0,divPlot);
TH1D *errorstat = new TH1D ("errorstat", "errors",divPlot,0,divPlot);
TH1F *efficiencycorrections = new TH1F ("efficiencycorrections", "efficiencycorrections",60,0,3);       
TH1F *efficiencycorrectionsmc = new TH1F ("efficiencycorrections", "efficiencycorrections",60,0,3);
TH1D* modD; TCanvas *cc; TCanvas *d; 
#include "SetObs.h" //Contains SetObservablesMC, SetObservablesData, SetPlotDiviisons, getNumberOfValidJets
#include "DrawUnfolding.h" //Contains DrawPlots
#include "BackgroundRemoval.h" // COntains correctForBackgrounds
#include "SaveUnfolding.h" // COntains correctForBackgrounds
string titleCov;
string titleCovToy;
string titleCovToySumUp;
string titleCovToySumUpRatio;
TH1D *jDataPreUnf;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double getContributionMCStatLimited(int position, TH1D *jDataPreUnf2, TH2D *jCov){
  double value=0.0;
  for (int i=1; i<jCov->GetNbinsX()+1; i++){
    cout<<"jDataPreUnf->GetBinContent(i) "<<jDataPreUnf2->GetBinContent(i)<<" jCov->GetBinContent(position-1,i) "<<jCov->GetBinContent(position,i)<<endl;
    value=value+fabs(jDataPreUnf2->GetBinContent(i)*jCov->GetBinContent(position,i));
    //value=value+pow(fabs(jDataPreUnf->GetBinContent(i)),0.5)*pow(fabs(jCov->GetBinContent(position,i)),0.5);
  }
  cout<<pow(value,0.25)<<endl;
  return pow(value,0.25);
}

void formatCovMaxtrixLatex(TMatrixD matrix, int divPlot2)
{
  matrix.Print();
  cout<<"=================================="<<endl;
  for(int h=1;h<=divPlot2; h++){
    for(int y=1; y<=divPlot2; y++){
      if (y<divPlot2) cout<<matrix[h][y]<<" & ";
      else cout<<matrix[h][y]<<" \\\\ ";
    }
    cout<<endl;
  }
  cout<<"=================================="<<endl;
  return ;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TH2D* formatTH2DFromCovMaxtrixLatex(TMatrixD matrix, int divPlot2, double minPlot, double maxPlot)
{
  TH2D* histo=new TH2D("histo","histo",divPlot2,minPlot,maxPlot,divPlot2,minPlot,maxPlot);
  cout<<"=================================="<<endl;
  for(int h=1;h<=divPlot2; h++){
    for(int y=1; y<=divPlot2; y++){
      
      histo->SetBinContent(h,y,matrix[h][y]);
    }
    cout<<endl;
  }
  cout<<"=================================="<<endl;
  return histo;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TMatrixD formatMatrixFromHisto(TH2D *histo, int divPlot2)
{
  TMatrixD mat(divPlot2+3,divPlot2+3);
  for(int h=0;h<divPlot2+3; h++){
    for(int y=0; y<divPlot2+3; y++){
      mat[h][y]=histo->GetBinContent(h,y);
    }
  }
  return mat;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DivideTwoMatrixes(TMatrixD matrix, TMatrixD matrix2, int divPlot2)
{
  cout<<"=================================="<<endl;
  for(int h=1;h<=divPlot2; h++){
    for(int y=1; y<=divPlot2; y++){
      if (y<divPlot2) cout<<matrix[h][y]/matrix2[h][y]<<" & ";
      else cout<<matrix[h][y]/matrix2[h][y]<<" \\\\ ";
    }
    cout<<endl;
  }
  cout<<"=================================="<<endl;
  return ;
}

TH1D* performUnfolding(string whichalgo, int kvalue, TH1D *jData, TH1D *jTrue, RooUnfoldResponse response_j, TH1D* jMCreco, TH2D* jMatx, int numbOfJetsSelected, string whichtype) //Specify which algo
{
  string whichjet="";
  if (numbOfJetsSelected==1) whichjet="Leading_";
  if (numbOfJetsSelected==2) whichjet="Secondleading_";
  if (numbOfJetsSelected==3) whichjet="Thirdleading_";
  if (numbOfJetsSelected==4) whichjet="Fourthleading_";
  titleCov= s+"/"+whichtype+"/JET"+whichtype+"_"+whichalgo+whichjet+"covMatrix.pdf";
  titleCovToy= s+"/"+whichtype+"/JET"+whichtype+"_"+whichalgo+whichjet+"covMatrixAndToy.pdf";
  titleCovToySumUp= s+"/"+whichtype+"/JET"+whichtype+"_"+whichalgo+whichjet+"covMatrixAndToySum.pdf";
  titleCovToySumUpRatio= s+"/"+whichtype+"/JET"+whichtype+"_"+whichalgo+whichjet+"covMatrixRatioMCStat.pdf";

  TH1D *unf;
  //response_j.SetOverflow(1);

  RooUnfoldBayes unfold_b (&response_j, jData, kvalue);  //NEVER,NEVER,NEVER set the parameter "1000" for the testing if you want to perform identity tests
  RooUnfoldSvd unfold_s (&response_j, jData, kvalue);
  std::vector<double> extraMCLimitedStatErrors;

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
    unf = (TH1D *) unfold_s.Hreco (RooUnfold::kErrors);
    unfold_s.PrintTable(cout,jTrue);
    TVectorD vstat= unfold_s.ErecoV();
    TVectorD vunfo= unfold_s.ErecoV(RooUnfold::kCovToy);
    TVectorD vunfomat= unfold_s.ErecoV(RooUnfold::kCovariance);
    TVectorD vunfodiag= unfold_s.ErecoV(RooUnfold::kErrors);
    TSVDUnfold unfold_modD (jData,(TH1D*)response_j.Htruth(),(TH1D*)response_j.Hmeasured(),(TH2D*)response_j.Hresponse()); // per calcolare il modulo
    TSVDUnfold unfold_modD2 (jData,jMCreco,jTrue,jMatx); // per calcolare il modulo
    //TSVDUnfold unfold_modDaaa(jData, jMatx, jMCreco, jTrue, jMatx);
    TH1D* unfresult;
    unfresult= unfold_modD.Unfold( kvalue); modD = unfold_modD.GetD(); 
    TMatrixD covmatrixdiagonal=unfold_s.Ereco(RooUnfold::kErrors);
    TMatrixD covmatrix=unfold_s.Ereco(RooUnfold::kCovariance);
    TMatrixD covmatrixtoy=unfold_s.Ereco(RooUnfold::kCovToy);
    formatCovMaxtrixLatex(covmatrix,divPlot);

    //Matrice di covarianza of experiment as a TH2D
    TH2D *covMatExp=formatTH2DFromCovMaxtrixLatex(covmatrix, divPlot, minObsPlot, maxObsPlot);
    //TH2D *covMatExp=unfold_modD.GetXtau();  //<<============ Using TSVDUnfold 

    //MC limited stat matrix
    TH2D *pippotoy=unfold_modD.GetAdetCovMatrix(1000); //<<====================== Questo crea instabilita'... Se vari il numero cambia unf!!!!!

    //Print the exp cov matr
    TCanvas *covMatExperim= new TCanvas ("covMatExperim", "covMatExperim", 1000, 700);
    covMatExperim->cd ();
    covMatExp->SetTitle(titleCov.c_str());
    covMatExp->SetStats(0);
    covMatExp->Draw("TEXT");
    covMatExperim->Print(titleCov.c_str());
    
    //Print the matrix from toy
    TCanvas *covMatExperimToy= new TCanvas ("covMatExperimToy", "covMatExperimToy", 1000, 700);
    covMatExperimToy->cd ();
    pippotoy->Draw("TEXT");
    covMatExperimToy->Print(titleCovToy.c_str());
    //====> other method TH2D* covMaToy=GetAdetCovMatrix( 10, 1, jMatx, jTrue, divPlot, k, response_j, jData, jTrue, jMCreco, jMatx, numbOfJetsSelected, whichtype);

    //Print the combined one!
    TCanvas *covMatExperimToySum= new TCanvas ("covMatExperimToySum", "covMatExperimToySum", 3500, 2500);
    covMatExperimToySum->cd ();
    TH2D *pippoToySum= (TH2D*)pippotoy->Clone("pippoToySum");
    pippoToySum->Add(covMatExp);
    pippoToySum->SetStats(0);
    pippoToySum->SetTitle("Covariance Matrix, including MC limited statistics effect");
    pippoToySum->Draw("TEXT");
    if (whichtype!="Multiplicity" && whichjet==1) pippoToySum->SetMarkerSize(0.55);
    pippoToySum->SetMarkerSize(0.8);
    if (whichtype=="Pt" && whichjet==2) pippoToySum->SetMarkerSize(0.70);
    covMatExperimToySum->Print(titleCovToySumUp.c_str());
    for (int i=1;i<=jData->GetNbinsX();i++) {extraMCLimitedStatErrors.push_back(pippoToySum->GetBinContent(i,i));}

    //Print The ratio MC stat/matrix
    TCanvas *covRatioMcStat= new TCanvas ("covRatioMcStat", "covRatioMcStat", 1000, 700);
    covRatioMcStat->cd ();
    gStyle->SetPalette (1);
    gStyle->SetPaintTextFormat ("5.3f");
    gStyle->SetNumberContours (999);
    TH2D *ratioMCStat= (TH2D*)covMatExp->Clone("ratioMCStat");
    ratioMCStat->Divide(pippotoy);
    ratioMCStat->Draw("COLZ,text");
    covRatioMcStat->Print(titleCovToySumUpRatio.c_str());

    //TSVDUnfold unfold_modD2 (jData,covMatExp,jTrue,jMCreco,jMatx); // per calcolare il modulo
    //TMatrixD matToy=formatMatrixFromHisto(pippotoy, divPlot);
    //formatCovMaxtrixLatex(matToy,divPlot); 
    //cout<<"BBBBBBBBBBBBBBBBBBBBBBBB"<<endl;
    //TMatrixD matToyProp=matToy*covmatrix;
    //formatCovMaxtrixLatex(matToyProp,divPlot); 
    //TSVDUnfold *unfold_modD2 =new TSVDUnfold(jData,pippotoy,jTrue,jMCreco,jMatx); // per calcolare il modulo
    //TH1D* unfresult2 = unfold_modD.Unfold( kvalue);
    //DivideTwoMatrixes(covmatrix, covmatrixtoy,divPlot);
    //TSVDUnfold unfold_modD2 (jData,covmatrix,jTrue,jMCreco,jMatx); // per calcolare il modulo
    //TH1D* unfresult2 = unfold_modD2.Unfold( kvalue); 
    //unf=unfresult;

    //Calculate EXTRA smearing for MC stat limitless
    //jDataPreUnf
      
  }
  for (int p=0;p<unf->GetNbinsX();p++){
    double unfoldingBinError=unf->GetBinError(p+1);
    if (MClimitedStatEffect) {
      unfoldingBinError=sqrt(extraMCLimitedStatErrors[p]);
      unf->SetBinError(p+1,unfoldingBinError);
    }
    errors->SetBinContent(p+1,unfoldingBinError); errorstat->SetBinContent(p+1,sqrt(unf->GetBinContent(p+1)));
    
    cout<<"Bin "<<p+1<<" has "<<unfoldingBinError<<" sta error is "<<sqrt(unf->GetBinContent(p+1));
    if (unfoldingBinError<sqrt(unf->GetBinContent(p+1))) unf->SetBinError(p+1,sqrt(unf->GetBinContent(p+1)));
    cout<<"Error set at "<<unfoldingBinError<<endl;
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
  for (int p=0;p<jData->GetNbinsX();p++){
    cout<<"Bin "<<p+1<<" has "<<jData->GetBinContent(p+1)<<" and error "<<jData->GetBinError(p+1)<<endl;;
  }
}

#include "MCLimitedStatTool.h"
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
  // Set the kmin, kmax, minOb1sPlot, maxObsPlot (those are global variables)
  //////////////////////////

  setPlotsDivisionsAndRanges(numbOfJetsSelected,whichtype,whichalgo);
  cout<<"Automatic histograms allocation ("<<whichtype<<"-"<<numbOfJetsSelected<<" jets). divPlot->"<<divPlot<<" min->"<<minObsPlot<<" max->"<<maxObsPlot<<" kmin->"<<kmin<<" kmax->"<<kmax<<endl;
  double divPlot2=divPlot; double minObsPlot2=minObsPlot; double maxObsPlot2=maxObsPlot;
  if (whichtype=="Multiplicity")  {
    divPlot2=6.5; minObsPlot2=0.5;maxObsPlot2=6.5;
  }

  TH1D *jTrue = new TH1D ("jTrue", "jet Truth",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jTruePythia = new TH1D ("jTruePythia", "jet Truth other MC generator",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jData = new TH1D ("jData", "jet DATA Measured",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jReco = new TH1D ("jReco", "jet Unfolded DATA",divPlot2,minObsPlot2,maxObsPlot2);
  TH2D *jMatx = new TH2D ("jMatx", "Unfolding Matrix jeet",divPlot2,minObsPlot2,maxObsPlot2,divPlot2,minObsPlot2,maxObsPlot2);
  TH2D *jMatxlong = new TH2D ("jMatxlong", "Unfolding Matrix jeet long",divPlot2+1,minObsPlot2-((maxObsPlot2-minObsPlot2)/divPlot2),maxObsPlot2,divPlot2+1,minObsPlot2-((maxObsPlot2-minObsPlot2)/divPlot2),maxObsPlot2);
  TH1D *jMCreco = new TH1D ("jMCreco", "jet mcreco",divPlot2,minObsPlot2,maxObsPlot2);

  jData->Sumw2(); jTrue->Sumw2(); jReco->Sumw2(); jMatx->Sumw2(); jMatxlong->Sumw2(); jMCreco->Sumw2(); jTruePythia->Sumw2();

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
    identityCheck=true;
    smearingJERSyst=-9999;
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
  
  int numberOfInversion=0;
  int numberOfInversionDenominator=0;
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;
  int inTheGap=0; int recoButPtLow=0; int recoButEtaHigh=0; int recoButInvMassOut=0; int recoButNotGenerated=0; int genButNotReco=0; int recostructedEvents=0; int genOutsideTheLimits=0; int notGenNotReco=0; int recoinTheGap=0; int genRecoAfterGenCorr=0; int noGenRecoAfterGenCorr=0; int genNoRecoAfterGenCorr=0;//Simpatici counter 

  if (splitCheck) {
    nentries=(int) 50.0*(nentries/100.);
    cout<<"Splitcheck is active, so Dataset A (MC) has now "<<nentries<<endl;
  }

  if (fChain == 0) return; if (!doUnfold) nentries=0;
  int aaa=0;

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      jet_Obs_gen=0;
      jet_Obs=0;

      if (Jet_multiplicity > 20 || Jet_multiplicity_gen > 20 ) continue;     
      //In this way, jets with more than 25 GeV are accounted!! --> getNumberOfValidJets to change it offline..
      //int ValidGenJets=Jet_multiplicity_gen;//getNumberOfValidJets(Jet_multiplicity_gen, 30.0, threshEta, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);

      int ValidGenJets=getNumberOfValidJets(Jet_multiplicity_gen, 30, 2.4, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);
      int ValidRecoJets=Jet_multiplicity;
      
      // Initialize the Observables
      setObservablesMC(numbOfJetsSelected, whichtype, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen,  jet5_pt_gen,  jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen, 
		       ValidGenJets, jet1_pt, jet2_pt, jet3_pt, jet4_pt,  jet5_pt,  jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta,ValidRecoJets);  

      //Eta Case...by default, events missed can be =0, removed by hands
      if (jet_Obs==0 && whichtype=="Eta") {
	jet_Obs=-9999;
      } 

      if (jet_Obs_gen==0 && whichtype=="Eta") {
	jet_Obs_gen=-9999;
      } 

      if (ValidGenJets<numbOfJetsSelected &&  ValidRecoJets<numbOfJetsSelected) continue; //-------------> Occhio all'IDENTITY CHECK con questo
      aaa++;
      
 
      // Get Efficiency
      double effcorrmc=1.00;
      if (correctForMCReweighting) effcorrmc=effcorrmc*evWeight;      // Weights per il PU
      if (correctForEff) {
	//if (fabs(e1_pt)==9999) continue; 
	
	//Normal eff
	//if (!isEle) effcorrmc=effcorrmc/getEfficiencyMuonPOG(true,true,e1_pt,e1_eta,e2_pt,e2_eta);
        //if (isEle ) effcorrmc=effcorrmc/(getEfficiencyEGammaPOG(e1_pt ,e1_eta, e2_pt, e2_eta, true, false, false) * getEfficiencyCorrectionPtUsingElectron(fAeff, e1_pt , e1_eta, e2_pt, e2_eta, "MC"));
	
	if (jet1_pt_gen>30 && jet2_pt_gen>30 && jet1_pt_gen<4000 && jet2_pt_gen<4000 && jet1_pt_gen>0 && jet2_pt_gen>0) numberOfInversionDenominator++;
	// Scale factors
	if (isMu) {
	  bool is2011A=false;
	  //if (run<180000) is2011A=true;
	  //double effMC=getEfficiencyMuonPOG(is2011A , true, e1_pt ,e1_eta, e2_pt, e2_eta,false,false);
	  //double effData=getEfficiencyMuonPOG(is2011A , false, e1_pt ,e1_eta, e2_pt ,e2_eta,false,false);
	  //effcorrmc=(effData/effMC);
	  if (recoZInAcceptance) effcorrmc=getSfMuonPOG(is2011A, e1_pt ,e1_eta, e2_pt ,e2_eta);
	}
	if (!isMu) {
	  double SF=getSfEGammaPOG(e1_pt ,e1_eta, e2_pt , e2_eta,false,false)*getScaleFactorPtUsingElectron(fAeff, e1_pt , e1_eta, e2_pt, e2_eta);
	  if (recoZInAcceptance) effcorrmc=(SF);
	}
      }

      efficiencycorrectionsmc->Fill(effcorrmc);
      if (jet_Obs_gen==9999) jet_Obs_gen=-9999; //-------------> to protect us against spykes...

      //////////////////////////////////
      // Gen Level Correction
      //////////////////////////////////

      //printObservables( jet1_pt_gen,  jet2_pt_gen,  jet3_pt_gen,  jet4_pt_gen,   jet5_pt_gen,   jet6_pt_gen,  jet1_eta_gen,  jet2_eta_gen,  jet3_eta_gen,  jet4_eta_gen,  jet5_eta_gen,  jet6_eta_gen,  Jet_multiplicity_gen,  jet1_pt,  jet2_pt,  jet3_pt,  jet4_pt,   jet5_pt,   jet6_pt,  jet1_eta,  jet2_eta,  jet3_eta,  jet4_eta,  jet5_eta,  jet6_eta, Jet_multiplicity,  jet_Obs, jet_Obs_gen);
      if (whichtype=="Multiplicity"){
	
	//Old Working version.-------------------------?
	//jTrue->Fill (jet_Obs_gen); jMatx->Fill (jet_Obs, jet_Obs_gen,effcorrmc); jMatxlong->Fill (jet_Obs, jet_Obs_gen,effcorrmc); jMCreco->Fill (jet_Obs,effcorrmc);
	//Old Working version.-------------------------?
	if (jet_Obs_gen==0 && jet_Obs==0) continue;
	if (genZInAcceptance && recoZInAcceptance) {
	  response_fillfake.Fill(jet_Obs,jet_Obs_gen,effcorrmc);
	  if (jet_Obs_gen>=1 && jet_Obs>=1) {
	    jMatx->Fill (jet_Obs, jet_Obs_gen,effcorrmc);
	    jMCreco->Fill (jet_Obs,effcorrmc);
	    jTrue->Fill (jet_Obs_gen); 
	  }
	  else{
	    if (jet_Obs_gen>0) jTrue->Fill (jet_Obs_gen);
 	    if (jet_Obs>0) jMCreco->Fill (jet_Obs,effcorrmc);
	  }
	  jMatxlong->Fill (jet_Obs, jet_Obs_gen,effcorrmc); 
	  continue;
	}
	if (genZInAcceptance && !recoZInAcceptance) {
	  response_fillfake.Miss(jet_Obs_gen);
	  jTrue->Fill (jet_Obs_gen); 
	  continue;
	}
	if (!genZInAcceptance && recoZInAcceptance) {
	  jMCreco->Fill (jet_Obs,effcorrmc);
	  response_fillfake.Fake(jet_Obs,effcorrmc);
	  continue;
	}
      }
      else{
	//printObservables( jet1_pt_gen,  jet2_pt_gen,  jet3_pt_gen,  jet4_pt_gen,   jet5_pt_gen,   jet6_pt_gen,  jet1_eta_gen,  jet2_eta_gen,  jet3_eta_gen,  jet4_eta_gen,  jet5_eta_gen,  jet6_eta_gen,  Jet_multiplicity_gen,  jet1_pt,  jet2_pt,  jet3_pt,  jet4_pt,   jet5_pt,   jet6_pt,  jet1_eta,  jet2_eta,  jet3_eta,  jet4_eta,  jet5_eta,  jet6_eta, Jet_multiplicity,  jet_Obs, jet_Obs_gen);
	//if (ValidGenJets==4 && jet1_pt_gen==jet2_pt_gen && jet1_pt_gen>0) continue;
	//if (ValidGenJets==4 && jet1_pt_gen==jet3_pt_gen && jet1_pt_gen>0) continue;
	//if (ValidGenJets==4 && jet1_pt_gen==jet4_pt_gen && jet1_pt_gen>0) continue;
	//if (ValidGenJets==4 && jet2_pt_gen==jet3_pt_gen && jet2_pt_gen>0) continue;
	//if (ValidGenJets==4 && jet2_pt_gen==jet4_pt_gen && jet2_pt_gen>0) continue;
	//if (ValidGenJets==4 && jet3_pt_gen==jet4_pt_gen && jet3_pt_gen>0) continue;
	//if (ValidGenJets==4 && jet4_pt_gen==jet5_pt_gen && jet4_pt_gen>0) continue;
	//if (ValidGenJets==4 && jet3_pt_gen==jet5_pt_gen && jet5_pt_gen>0) continue;
        //if (ValidGenJets==4 && jet2_pt_gen==jet5_pt_gen && jet5_pt_gen>0) continue;
	//if (ValidGenJets==4 && jet1_pt_gen==jet5_pt_gen && jet5_pt_gen>0) continue;
	//vector<double> *a=deltaRRecoGenJet;
	//double b=a->at(0);
	
	//if (jet3_pt_gen>0 && ValidGenJets<3 && numbOfJetsSelected==3) {
	//jet_Obs_gen=-9999;
	//jet_Obs_pt_gen=-9999;
	//jet_Obs_eta_gen=-9999;
	//}

	//if (ValidGenJets==4 && (jet3_pt_gen==-9999 || jet2_pt_gen==-9999 || jet1_pt_gen==-9999)) {
	//jet_Obs_gen=-9999;
	//jet_Obs_pt_gen=-9999;
	//printObservables( jet1_pt_gen,  jet2_pt_gen,  jet3_pt_gen,  jet4_pt_gen,   jet5_pt_gen,   jet6_pt_gen,  jet1_eta_gen,  jet2_eta_gen,  jet3_eta_gen,  jet4_eta_gen,  jet5_eta_gen,  jet6_eta_gen,  Jet_multiplicity_gen,  jet1_pt,  jet2_pt,  jet3_pt,  jet4_pt,   jet5_pt,   jet6_pt,  jet1_eta,  jet2_eta,  jet3_eta,  jet4_eta,  jet5_eta,  jet6_eta, Jet_multiplicity,  jet_Obs, jet_Obs_gen);
	//}

	//if (jet4_pt_gen<30 && (jet5_pt_gen>30 || jet6_pt_gen>30)) {
	//if (ValidGenJets>3){
	//  jet_Obs_gen=jet5_pt_gen;
	//  jet_Obs_pt_gen=jet5_pt_gen;//<<=============================occhio, prova a toglierlo...
	//}
	//}

	//if (!(ValidGenJets==4 && ValidRecoJets==4)) continue;
	
	//if (ValidGenJets<4 && ValidRecoJets>=4) {
	//jMCreco->Fill (jet_Obs,effcorrmc);
	//response_fillfake.Fake(jet_Obs,effcorrmc);
	//cout<<"AAAAAAAAAAAAAAAAAAA"<<endl;
	//continue;
	//}
	//if (ValidGenJets>=4 && ValidRecoJets<4) {
	//jTrue->Fill (jet_Obs_gen);
	//response_fillfake.Miss(jet_Obs_gen,effcorrmc);
	//cout<<"BBBBBBBBBBBBBBBBBBBBB"<<endl;
	//continue;
	//}

	//Old Working version.-------------------------?
	//if (jet_Obs_gen<30) jet_Obs_gen=0;
	//if (jet_Obs<30) jet_Obs=0.0;
	//jTrue->Fill (jet_Obs_gen); jMatx->Fill (jet_Obs, jet_Obs_gen,effcorrmc); jMatxlong->Fill (jet_Obs, jet_Obs_gen,effcorrmc); jMCreco->Fill (jet_Obs,effcorrmc);
	//Old Working version.-------------------------?
	//if (fabs(jet4_pt_gen-jet4_pt)>10 && jet4_pt_gen>0) continue;

	//Calculate DeltaR among jets
	//deltaPhi = fabs(jet4_eta_gen-jet4_eta);
	//if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	//double deltaR = sqrt( deltaPhi*deltaPhi  + pow(jet->eta()-e1.Eta(),2) );


	if (genZInAcceptance && recoZInAcceptance) {
	  jet_Obs_gen=jet1_pt_gen_abs;
	if(  (jet_Obs_pt>30 && fabs(jet_Obs_eta)<2.4) &&  (jet_Obs_pt_gen>30 && fabs(jet_Obs_eta)<2.4) ) {
	  response_fillfake.Fill(jet_Obs,jet_Obs_gen,effcorrmc);
	  jTrue->Fill (jet_Obs_gen); 
	  jMatx->Fill (jet_Obs, jet_Obs_gen,effcorrmc); 
	  jMatxlong->Fill (jet_Obs, jet_Obs_gen,effcorrmc); jMCreco->Fill (jet_Obs,effcorrmc);
	}
	if( !(jet_Obs_pt>30 && fabs(jet_Obs_eta)<2.4) &&  (jet_Obs_pt_gen>30 && fabs(jet_Obs_eta)<2.4) ) {
	  response_fillfake.Miss(jet_Obs_gen,effcorrmc);
	  jTrue->Fill (jet_Obs_gen); //jMatx->Fill (jet_Obs, jet_Obs_gen,effcorrmc); jMatxlong->Fill (jet_Obs, jet_Obs_gen,effcorrmc); jMCreco->Fill (jet_Obs,effcorrmc); 
	}
	if(  (jet_Obs_pt>30 && fabs(jet_Obs_eta)<2.4) && !(jet_Obs_pt_gen>30 && fabs(jet_Obs_eta)<2.4) ) {
	  response_fillfake.Fake(jet_Obs,effcorrmc);
	  jMCreco->Fill (jet_Obs,effcorrmc);//<<========================Pietra dello scandalo
	}
	continue;
	}
	if (genZInAcceptance && !recoZInAcceptance) {
	  response_fillfake.Miss(jet_Obs_gen); 
	  jTrue->Fill (jet_Obs_gen); //jMatx->Fill (jet_Obs, jet_Obs_gen); jMatxlong->Fill (jet_Obs, jet_Obs_gen); jMCreco->Fill (jet_Obs);	
	  continue;
	}
	if (!genZInAcceptance && recoZInAcceptance) {
	  response_fillfake.Fake(jet_Obs,effcorrmc);	  
	  jMCreco->Fill (jet_Obs,effcorrmc);	
	  continue;}
      }
 
    }  cout<<"aaa is "<<aaa<<endl;
  //Numbers for debug.. Output in our code
  cout<<"Total Number of events inside the rootupla==>"<<nentries<<endl;
  cout<<"Generated Outside the detector limits=>"<<genOutsideTheLimits<<", of which "<<recoButNotGenerated<<" reconstructed."<<"So,"<<notGenNotReco<<" not reco not gen. Filling gap for ele with "<<inTheGap<<endl;
  cout<<"<Reconstructed events==>"<<recostructedEvents<<". Reco but gen in the gap=>"<<recoinTheGap<<" gen low pt=>"<<recoButPtLow<<" gen high eta=>"<<recoButEtaHigh<<" gen outInvMass=>"<<recoButInvMassOut<<" recoNotGen=>"<<recoButNotGenerated<<" genNotReco=>"<<genButNotReco<<endl;
  cout<<"Gen & Reco after GEN Level Correction=>"<<genRecoAfterGenCorr<<"Gen & !Reco=>"<<genNoRecoAfterGenCorr<<"!Gen & Reco=>"<<noGenRecoAfterGenCorr<<endl;
  cout<<"Inversion ->"<<numberOfInversion<<" out of->"<<numberOfInversionDenominator<<endl;
  
  /* Loop Data */
  int numbOfEventsInData=0;
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

 //if ((fabs(e1_eta)>1.442 && fabs(e1_eta)<1.566) || (fabs(e2_eta)>1.442 && fabs(e2_eta)<1.566))  continue;
    //if ((fabs(e1_eta)>2.0) || (fabs(e2_eta)>2.0))  continue;

    //When you test pythia or identity, this dataset becomes a MC one... So it requires some more gym
    setObservablesData(numbOfJetsSelected, whichtype, jet1_pt, jet2_pt, jet3_pt, jet4_pt, jet5_pt, jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta, Jet_multiplicity);

    double effcorrdata=1.0;
    if (correctForEff) {
      //if (!isEle) effcorrdata=effcorrdata/getEfficiencyMuonPOG(true,false,e1_pt,e1_eta,e2_pt,e2_eta);
      //if (isEle) effcorrdata=effcorrdata/(getEfficiencyEGammaPOG(e1_pt ,e1_eta, e2_pt, e2_eta, false, false, false) * getEfficiencyCorrectionPtUsingElectron(fAeff, e1_pt , e1_eta, e2_pt, e2_eta, "Data"));
      //cout<<effcorrdata<<endl;
      //effcorrmc=effcorrmc/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);
    }

    efficiencycorrections->Fill(effcorrdata);
    //Normal Filling
    jData->Fill (jet_Obs,effcorrdata);
  }//End loop Data

  cout<<"Recorded "<<numbOfEventsInData<<" events as Data"<<endl;

  ////////////////////////
  /// Background Sub
  /////////////////////////

  if (correctForBkg) correctForBackground(numbOfJetsSelected,whichtype,jData,true); //bool -> activate verbosity

  //////////////////////////////
  ///
  ///     Unfolding Core
  ///
  //////////////////////////////
  
  
  cout<<"These are the values PRE unfolding "<<endl;
  loopAndDumpEntries(jData);
  jDataPreUnf=(TH1D*) jData->Clone("jData");
  jDataPreUnf->SetName("jDataPreUnf");
  cout<<"================================== "<<endl;

  //Old stile to perform the unfolding
  RooUnfoldResponse response_j(jMCreco, jTrue, jMatx); 
  response_j.UseOverflow();   ///////////===================> Senza questo, ottengo il TSVDUnfold!!!!!!!!!!!!!!!!!!!
  stringstream num;

  string method=whichalgo;
  cout<<"Running "<<method<<" method"<<endl;
  
  for (int k=kmin; k< kmax; k++){
    int myNumber=k; num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Jet pT diff xsec distribution. "+title;
      if (doUnfold) {
	if (identityCheck) jReco=performUnfolding(whichalgo, k, jData, jTrue,response_j, jMCreco,jMatx, numbOfJetsSelected, whichtype);
	if (!identityCheck) jReco=performUnfolding(whichalgo, k, jData, jTrue,response_j, jMCreco,jMatx, numbOfJetsSelected, whichtype);
	//TH2D* covMaToy=GetAdetCovMatrix( 20, 1, jMatx, jTrue, divPlot, k, response_j, jData, jTrue, jMCreco, jMatx, numbOfJetsSelected, whichtype);
	//TCanvas *covMatExperimToy= new TCanvas ("covMatExperimToy", "covMatExperimToy", 1000, 700);
	//covMatExperimToy->cd ();
        //covMaToy->Draw("TEXT");
	//covMatExperimToy->Print(titleCovToy.c_str());
      }
      else{
      jReco=(TH1D*) jData->Clone("jData");
      jReco->SetName("jReco");
      }
      num.str("");
  } 

  if (identityCheck || splitCheck || pythiaCheck ||differentialCrossSection){
    jReco->Scale(1./jReco->Integral());             
    jTrue->Scale(1./jTrue->Integral());
    jMCreco->Scale(1./jMCreco->Integral());
    jData->Scale(1./jData->Integral());
    if (pythiaCheck) jTruePythia->Scale(1./jTruePythia->Integral());
  }

  //Drawing Histograms
  //if (doUnfold && !pythiaCheck) { cc= drawPlots(jReco,jData,jTrue,jMCreco,jMatxlong,numbOfJetsSelected,whichtype, whichalgo, kmin); cc->Draw(); }
  //if (doUnfold && pythiaCheck) { d= drawPlots(jReco,jData,jTruePythia,jMCreco,jMatxlong,numbOfJetsSelected,whichtype, whichalgo, kmin); d->Draw(); }
  //  d->Print("/tmp/a.png");
  //Normalization 

  double unfarea=jReco->Integral()/4890.0;
  cout<<"Your unfolding has an integral value of "<<unfarea<<endl;
  cout<<(jReco->GetBinContent(1)+jReco->GetBinContent(2)+jReco->GetBinContent(3)+jReco->GetBinContent(4)+jReco->GetBinContent(5)+jReco->GetBinContent(6))/4890.0<<endl;
  cout<<(jReco->GetBinContent(2)+jReco->GetBinContent(3)+jReco->GetBinContent(4)+jReco->GetBinContent(5)+jReco->GetBinContent(6))/4890.<<endl;
cout<<(jReco->GetBinContent(3)+jReco->GetBinContent(4)+jReco->GetBinContent(5)+jReco->GetBinContent(6))/4890.0<<endl;
cout<<(jReco->GetBinContent(4)+jReco->GetBinContent(5)+jReco->GetBinContent(6))/4890.0<<endl;

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
  loopAndDumpEntries(jReco);
  //if (saveFile) saveIntoFile(numbOfJetsSelected, whichtype, jReco, jTrue, jMatx, jMCreco, jData);


  delete relativebkg;
  delete errors;
  delete errorstat;
  delete efficiencycorrections;
  delete efficiencycorrectionsmc;
  delete modD; 
  delete jTrue;
  delete jTruePythia;
  delete jData;
  delete jReco;
  delete jMatx;
  delete jMatxlong;
  delete jMCreco;
  delete jDataPreUnf;
  fA->Close();


#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

}

