#include <vector>
#include <iostream>
#include <algorithm>
#include "TSVDUnfold.h"
#include <iostream>
#include <fstream>
#include "JERCorrection.h"
#include <fstream>

using namespace std;

/*Initialize Variables*/
double minObsPlot=30;
double maxObsPlot=330;
int divPlot=15;
int kmin=1;
int kmax=1;
bool spanKvalues=false;

double jet_Obs_gen=0;double jet_Obs=0;
double jet_Obs_gen_abs=0;

double jet_Obs_pt_gen=0;double jet_Obs_pt=0;
double jet_Obs_eta_gen=0;double jet_Obs_eta=0;
double jet_Obs_multi_gen=0;double jet_Obs_multi=0;

double jet_Obs_pt_gen_abs=0;
double jet_Obs_eta_gen_abs=0;
double jet_Obs_multi_gen_abs=0;

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
    if (extraTests) return unf;
    TVectorD vstat= unfold_s.ErecoV();
    TVectorD vunfo= unfold_s.ErecoV(RooUnfold::kCovToy);
    TVectorD vunfomat= unfold_s.ErecoV(RooUnfold::kCovariance);
    TVectorD vunfodiag= unfold_s.ErecoV(RooUnfold::kErrors);
    TSVDUnfold unfold_modD2 (jData,(TH1D*)response_j.Htruth(),(TH1D*)response_j.Hmeasured(),(TH2D*)response_j.Hresponse()); // per calcolare il modulo
    TSVDUnfold unfold_modD (jData,jTrue,jMCreco,jMatx); // per calcolare il modulo
    //TSVDUnfold unfold_modDaaa(jData, jMatx, jMCreco, jTrue, jMatx);
    TH1D* unfresult;
    unfresult= unfold_modD.Unfold( kvalue); modD = unfold_modD.GetD(); 
    TMatrixD covmatrixdiagonal=unfold_s.Ereco(RooUnfold::kErrors);
    TMatrixD covmatrix=unfold_s.Ereco(RooUnfold::kCovariance);
    TMatrixD covmatrixtoy=unfold_s.Ereco(RooUnfold::kCovToy);
    formatCovMaxtrixLatex(covmatrix,divPlot);

    //Matrice di covarianza of experiment as a TH2D
    TH2D *covMatExp=formatTH2DFromCovMaxtrixLatex(covmatrixtoy, divPlot, minObsPlot, maxObsPlot);
    //TH2D *covMatExp=unfold_modD.GetXtau();  //<<============ Using TSVDUnfold 

    //MC limited stat matrix
    TH2D *pippotoy=unfold_modD.GetAdetCovMatrix(10000); //<<====================== Questo crea instabilita'... Se vari il numero cambia unf!!!!!

    //Print the exp cov matr
    TCanvas *covMatExperim= new TCanvas ("covMatExperim", "covMatExperim", 1000, 700);
    covMatExperim->cd ();
    covMatExp->SetTitle(titleCov.c_str());
    covMatExp->SetStats(0);
    gStyle->SetPalette (1);
    //gPad->SetRightMargin(0.15);
    gStyle->SetPaintTextFormat ("5.1f");
    gStyle->SetNumberContours (999);
    //gPad->SetLogz (1);
    if (whichjet=="Leading_") covMatExp->SetMarkerSize(1);
    if (whichtype=="Eta" && whichjet=="Leading_") covMatExp->SetMarkerSize(0.55);
    if (whichtype=="Eta" && whichjet=="SecondLeading_") covMatExp->SetMarkerSize(0.60);
    if (whichtype=="Eta" && whichjet=="ThirdLeading_") covMatExp->SetMarkerSize(0.65);
    if (whichtype=="Eta" && whichjet=="FourthLeading_") covMatExp->SetMarkerSize(0.70);
    covMatExp->GetXaxis()->SetTitle("Observable");
    covMatExp->GetYaxis()->SetTitle("Observable");
    covMatExp->SetTitle("Covariance Matrix");
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
    gPad->SetLogz (1);
    gPad->SetRightMargin(0.15);
    gStyle->SetPalette (1);
    gStyle->SetPaintTextFormat ("5.1f");
    gStyle->SetNumberContours (999);
    pippoToySum->SetTitle("Covariance Matrix, including MC limited statistics effect");
    pippoToySum->Draw("text");
    pippoToySum->SetMarkerSize(0.8);

    if (whichjet=="Leading_") pippoToySum->SetMarkerSize(0.65);
    if (whichtype=="Eta" && whichjet=="Leading_") pippoToySum->SetMarkerSize(0.55);
    if (whichtype=="Eta" && whichjet=="SecondLeading_") pippoToySum->SetMarkerSize(0.60);
    if (whichtype=="Eta" && whichjet=="ThirdLeading_") pippoToySum->SetMarkerSize(0.65);
    if (whichtype=="Eta" && whichjet=="FourthLeading_") pippoToySum->SetMarkerSize(0.70);

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
  }

  ofstream myfile;
  myfile.open ("/tmp/systematics.txt");
  myfile<<whichtype+"_"+whichalgo+whichjet<<endl;

  for (int p=0;p<unf->GetNbinsX();p++){
    double preCorrectionUnf=unf->GetBinError(p+1); //Questo contiene l'errore dell'unfolding "puro", non confrontato con sqrt
    double preCorrectionSQRT=sqrt(unf->GetBinContent(p+1)); // Erorre statistico
    double unfoldingBinError=unf->GetBinError(p+1); 

    if (MClimitedStatEffect) {
      unfoldingBinError=sqrt(extraMCLimitedStatErrors[p]); ////Errore dell'unfolding pre correczioni + toy, quindi anche piu' piccolo di sqrt
      unf->SetBinError(p+1,unfoldingBinError); //Ora unf e' con il toy
      cout<<unfoldingBinError/unfoldingBinError<<endl;
    }
    errors->SetBinContent(p+1,unfoldingBinError); errorstat->SetBinContent(p+1,sqrt(unf->GetBinContent(p+1)));
    
    cout<<"Bin "<<p+1<<" has "<<unfoldingBinError<<" sta error is "<<sqrt(unf->GetBinContent(p+1))<<" and MC toy error "<<extraMCLimitedStatErrors[p]<<endl;

    //Vecchio stile
    //Error procection ===============================================>
    //if (unfoldingBinError<sqrt(unf->GetBinContent(p+1)*0.8)) unf->SetBinError(p+1,sqrt(unf->GetBinContent(p+1)*0.8)); //se unf+toy > sqrt ok, altrimenti set to sqrt
    //unf->SetBinError(p+1,sqrt(unf->GetBinContent(p+1))); //se unf+toy > sqrt ok, altrimenti set to sqrt
    //*******

    cout<<"Error set at "<<unfoldingBinError<<endl;

    myfile<<(extraMCLimitedStatErrors[p])/preCorrectionUnf;
 
    //Info for MC toy incidence!
    if (unfoldingBinError<sqrt(unf->GetBinContent(p+1))) {
      cout<<"(sigma_unf+sigma_toy)/sigma_unf) is "<<(sqrt(extraMCLimitedStatErrors[p]))/preCorrectionSQRT;
    }
    else {
      cout<<"(sigma_unf+sigma_toy)/sigma_unf) is "<<sqrt(extraMCLimitedStatErrors[p])/preCorrectionUnf;
    }
   //cout<<"(sigma_unf+sigma_toy)/sigma_toy) is "<<(sqrt(extraMCLimitedStatErrors[p])/unf->GetBinError(p+1);
  }
  myfile.close();

  if (MClimitedStatEffect) {
    for (int p=0;p<unf->GetNbinsX();p++){
      double preCorrectionUnf=unf->GetBinError(p+1); //Questo contiene l'errore dell'unfolding "puro", non confrontato con sqrt
      double preCorrectionSQRT=sqrt(unf->GetBinContent(p+1));
      double unfoldingBinError=unf->GetBinError(p+1);
      if (MClimitedStatEffect) {
	unfoldingBinError=sqrt(extraMCLimitedStatErrors[p]);
	unf->SetBinError(p+1,unfoldingBinError);
      }
      errors->SetBinContent(p+1,unfoldingBinError); errorstat->SetBinContent(p+1,sqrt(unf->GetBinContent(p+1)));
      
      cout<<"Bin "<<p+1<<" has "<<unfoldingBinError<<" sta error is "<<sqrt(unf->GetBinContent(p+1))<<" and MC toy error "<<extraMCLimitedStatErrors[p]<<endl;
      //if (unfoldingBinError<sqrt(unf->GetBinContent(p+1))) unf->SetBinError(p+1,sqrt(unf->GetBinContent(p+1)));

      cout<<"Error set at "<<unfoldingBinError<<endl;
      
      //Info for MC toy incidence!
      //if (unfoldingBinError<sqrt(unf->GetBinContent(p+1))) cout<<"(sigma_unf+sigma_toy)/sigma_unf) is "<<(unfoldinBinError)/preCorrectionSQRT;
      //else cout<<"(sigma_unf+sigma_toy)/sigma_unf) is "<<(unfoldinBinError)/preCorrectionUnf;
    }
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
  TH1D *jTrueMatched = new TH1D ("jTrueMatched", "jet Truth Matched",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jTruePythia = new TH1D ("jTruePythia", "jet Truth other MC generator",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jData = new TH1D ("jData", "jet DATA Measured",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jReco = new TH1D ("jReco", "jet Unfolded DATA",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jRecoMatched = new TH1D ("jRecoMatched", "jet Unfolded DATA Matched",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jRecoAnne = new TH1D ("jRecoAnne", "jet Unfolded DATA Matched Anne MArie",divPlot2,minObsPlot2,maxObsPlot2);
  TH2D *jMatx = new TH2D ("jMatx", "Unfolding Matrix jeet",divPlot2,minObsPlot2,maxObsPlot2,divPlot2,minObsPlot2,maxObsPlot2);
  TH2D *jMatxAnneMarie = new TH2D ("jMatxAnneMarie", "Unfolding Matrix jeet Anne Marie",divPlot2,minObsPlot2,maxObsPlot2,divPlot2,minObsPlot2,maxObsPlot2);
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
  
  double PUreweightArea=0;
  int PUreweightEvents=0;

  if (splitCheck) {
    cout<<"Entries before split check test "<<nentries<<endl;
    nentries=(int) 50.0*(nentries/100.);
    cout<<"Splitcheck is active, so Dataset A (MC) has now "<<nentries<<endl;
  }

  if (fChain == 0) return; if (!doUnfold) nentries=0;
  int aaa=0; int bbb=0; int numbRecoGen=0; int numbRecoNotGen=0; int numbNotRecoGen=0; int numbRecoGenMatched=0; int numbRecoGenNotMatchedMiss=0; int numbRecoGenNotMatchedFake=0;

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      jet_Obs_gen_abs=0;
      jet_Obs_gen=0;
      jet_Obs=0;

      if (Jet_multiplicity > 10 || Jet_multiplicity_gen > 10 ) continue;     
      //In this way, jets with more than 25 GeV are accounted!! --> getNumberOfValidJets to change it offline..
      //int ValidGenJets=Jet_multiplicity_gen;//getNumberOfValidJets(Jet_multiplicity_gen, 30.0, threshEta, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);

      int ValidGenJets=getNumberOfValidJets(Jet_multiplicity_gen, 30, 2.4, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);
      int ValidRecoJets=Jet_multiplicity;
      
      // Initialize the Observables
      setObservablesMC(numbOfJetsSelected, whichtype, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen,  jet5_pt_gen,  jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen, ValidGenJets, jet1_pt, jet2_pt, jet3_pt, jet4_pt,  jet5_pt,  jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta,ValidRecoJets,jet1_pt_gen_abs, jet2_pt_gen_abs, jet3_pt_gen_abs, jet4_pt_gen_abs,  jet5_pt_gen_abs,  jet6_pt_gen_abs, jet1_eta_gen_abs, jet2_eta_gen_abs, jet3_eta_gen_abs, jet4_eta_gen_abs, jet5_eta_gen_abs, jet6_eta_gen_abs);

      //Eta Case...by default, events missed can be =0, removed by hands
      if (jet_Obs==0 && whichtype=="Eta") {
	///et_Obs=-9999;
      } 

      if (jet_Obs_gen==0 && whichtype=="Eta") {
	//jet_Obs_gen=-9999;
      } 

      if (ValidGenJets<numbOfJetsSelected &&  ValidRecoJets<numbOfJetsSelected) continue; //-------------> Occhio all'IDENTITY CHECK con questo
      aaa++;
      
      //PU
      double PU=1.00;
      if (!extraTests && !pythiaCheck && !identityCheck) PU=evWeight;
      PUreweightArea+=PU;
      PUreweightEvents++;
      if (unfoldWithSherpa || pythiaCheck) PU=PU*evWeightSherpa;
      //cout<<evWeightSherpa<<endl;

      // Get Efficiency
      double effcorrmc=1.00;
      if (correctForEff) {
	if (isMu) {
	  //------------> bool is2011A=false;
	  if (recoZInAcceptance && numberOfVertices<numbOfVerticesForSeparation) effcorrmc=PU*getSfMuonPOG(false, e1_pt ,e1_eta, e2_pt ,e2_eta);
	  if (recoZInAcceptance && numberOfVertices>=numbOfVerticesForSeparation) effcorrmc=PU*getSfMuonPOG(true, e1_pt ,e1_eta, e2_pt ,e2_eta);
	}
	if (!isMu) {
	  double SF=getSfEGammaPOG(e1_pt ,e1_eta, e2_pt , e2_eta,false,false)*getScaleFactorPtUsingElectron(fAeff, e1_pt , e1_eta, e2_pt, e2_eta);
	  if (recoZInAcceptance) effcorrmc=PU*(SF);
	}
      }
      efficiencycorrectionsmc->Fill(effcorrmc);

      //////////////////////////////////
      // Gen Level Correction
      //////////////////////////////////

      if (jet_Obs_gen==0 && jet_Obs==0) {  continue;}
      
      if (genZInAcceptance && recoZInAcceptance) {
	//printObservables( jet1_pt_gen,  jet2_pt_gen,  jet3_pt_gen,  jet4_pt_gen,   jet5_pt_gen,   jet6_pt_gen,  jet1_eta_gen,  jet2_eta_gen,  jet3_eta_gen,  jet4_eta_gen,  jet5_eta_gen,  jet6_eta_gen,  Jet_multiplicity_gen,  jet1_pt,  jet2_pt,  jet3_pt,  jet4_pt,   jet5_pt,   jet6_pt,  jet1_eta,  jet2_eta,  jet3_eta,  jet4_eta,  jet5_eta,  jet6_eta, Jet_multiplicity,  jet_Obs, jet_Obs_gen);
	//cout<<"Reco and Gen. ";
	numbRecoGen++;
	//MCrco e JTrue rimepite sempre
 	if (verifyAcceptance(whichtype,jet_Obs_gen_abs,jet_Obs_pt_gen_abs,jet_Obs_multi_gen_abs, jet_Obs_eta_gen_abs,numbOfJetsSelected))jTrue->Fill (jet_Obs_gen_abs,PU);
	if (verifyAcceptance(whichtype,jet_Obs,jet_Obs_pt,jet_Obs_multi, jet_Obs_eta,numbOfJetsSelected)) jMCreco->Fill (jet_Obs,effcorrmc);
	    
	//Matching RECO-GEN (Our method)
	if ( verifyMatching(whichtype, jet_Obs_gen, jet_Obs, jet_Obs_pt_gen, jet_Obs_pt,jet_Obs_eta_gen, jet_Obs_multi, jet_Obs_multi_gen,numbOfJetsSelected) ){
	  //cout<<" matched ";
	  if ( verifyAcceptance(whichtype,jet_Obs_gen,jet_Obs_pt_gen,jet_Obs_multi_gen, jet_Obs_eta_gen,numbOfJetsSelected) && (verifyAcceptance(whichtype,jet_Obs,jet_Obs_pt,jet_Obs_multi, jet_Obs_eta_gen,numbOfJetsSelected))){
	    jMatxlong->Fill (jet_Obs, jet_Obs_gen,effcorrmc); 
	    jMatx->Fill (jet_Obs, jet_Obs_gen,effcorrmc);
	    jTrueMatched->Fill (jet_Obs_gen,effcorrmc); 
	    numbRecoGenMatched++;
	    //cout<<" whithin acceptances"<<endl;
	  }
	}
	
	//Matching RECO-GEN (Anne Marie Method)
	if (extraTests){
	  if ( verifyMatching(whichtype, jet_Obs_gen, jet_Obs, jet_Obs_pt_gen, jet_Obs_pt,jet_Obs_eta_gen, jet_Obs_multi, jet_Obs_multi_gen,numbOfJetsSelected) ){
	    
	    if ( verifyAcceptance(whichtype,jet_Obs_gen_abs,jet_Obs_pt_gen_abs,jet_Obs_multi_gen_abs, jet_Obs_eta_gen_abs,numbOfJetsSelected) &&  verifyAcceptance(whichtype,jet_Obs,jet_Obs_pt,jet_Obs_multi, jet_Obs_eta_gen,numbOfJetsSelected) ){
	      jMatxAnneMarie->Fill (jet_Obs, jet_Obs_gen_abs,effcorrmc);
	    }
	  }
	}
	
	continue;
      }
      if (genZInAcceptance && !recoZInAcceptance) {
	numbNotRecoGen++;
	if (verifyAcceptance(whichtype,jet_Obs_gen_abs,jet_Obs_pt_gen_abs,jet_Obs_multi_gen_abs, jet_Obs_eta_gen_abs,numbOfJetsSelected)) jTrue->Fill (jet_Obs_gen_abs,PU);
	continue;
      }
      if (!genZInAcceptance && recoZInAcceptance) {
	if (verifyAcceptance(whichtype,jet_Obs,jet_Obs_pt,jet_Obs_multi, jet_Obs_eta,numbOfJetsSelected)) jMCreco->Fill (jet_Obs,effcorrmc);
	continue;
      }
    } 

  //Rescaling for non unitariety of the PU reweighting...
  double PUscaleFactor=PUreweightArea/PUreweightEvents;
  cout<<"PUscaleFactor "<<PUscaleFactor<<endl;
  jMCreco->Scale(1./PUscaleFactor);
  jTrue->Scale(1./PUscaleFactor);
  jTrueMatched->Scale(1./PUscaleFactor);
  jMatx->Scale(1./PUscaleFactor);
  jMatxAnneMarie->Scale(1./PUscaleFactor);

  cout<<"aaa is "<<aaa<<" and bbb "<<bbb<<endl;
  //Numbers for debug.. Output in our code
  cout<<"Total Number of events inside the rootupla==>"<<nentries<<endl;
  cout<<"Generated Outside the detector limits=>"<<genOutsideTheLimits<<", of which "<<recoButNotGenerated<<" reconstructed."<<"So,"<<notGenNotReco<<" not reco not gen. Filling gap for ele with "<<inTheGap<<endl;
  cout<<"<Reconstructed events==>"<<recostructedEvents<<". Reco but gen in the gap=>"<<recoinTheGap<<" gen low pt=>"<<recoButPtLow<<" gen high eta=>"<<recoButEtaHigh<<" gen outInvMass=>"<<recoButInvMassOut<<" recoNotGen=>"<<recoButNotGenerated<<" genNotReco=>"<<genButNotReco<<endl;
  cout<<"Gen & Reco after GEN Level Correction=>"<<genRecoAfterGenCorr<<"Gen & !Reco=>"<<genNoRecoAfterGenCorr<<"!Gen & Reco=>"<<noGenRecoAfterGenCorr<<endl;
  cout<<"Inversion ->"<<numberOfInversion<<" out of->"<<numberOfInversionDenominator<<endl;
  cout<<"numbRecoGen "<<numbRecoGen<<" (matched "<<numbRecoGenMatched<<") numbRecoNotGen "<<numbRecoNotGen<<" numbNotRecoGen "<<numbNotRecoGen<<endl;
  cout<<"int numbRecoGenNotMatchedMiss "<<numbRecoGenNotMatchedMiss<<" int numbRecoGenNotMatchedFake "<<numbRecoGenNotMatchedFake<<endl;

  //////////////////////
  /* Loop Data */
  /////////////////////


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

    if (!pythiaCheck) jData->Fill (jet_Obs,effcorrdata);
    
    if (pythiaCheck){
      int ValidGenJets=getNumberOfValidJets(Jet_multiplicity_gen, 30, 2.4, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);
      int ValidRecoJets=Jet_multiplicity;
      jet_Obs_gen_abs=0;
      if (ValidGenJets<numbOfJetsSelected &&  ValidRecoJets<numbOfJetsSelected) continue; //-------------> Occhio all'IDENTITY CHECK con questo
      //if (jet_Obs_gen==0 && jet_Obs==0) {  continue;}
      setObservablesMC(numbOfJetsSelected, whichtype, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen,  jet5_pt_gen,  jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen, ValidGenJets, jet1_pt, jet2_pt, jet3_pt, jet4_pt,  jet5_pt,  jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta,ValidRecoJets,jet1_pt_gen_abs, jet2_pt_gen_abs, jet3_pt_gen_abs, jet4_pt_gen_abs,  jet5_pt_gen_abs,  jet6_pt_gen_abs, jet1_eta_gen_abs, jet2_eta_gen_abs, jet3_eta_gen_abs, jet4_eta_gen_abs, jet5_eta_gen_abs, jet6_eta_gen_abs);

      if (verifyAcceptance(whichtype,jet_Obs,jet_Obs_pt,jet_Obs_multi, jet_Obs_eta,numbOfJetsSelected)) jData->Fill(jet_Obs,evWeightSherpa);
      if (verifyAcceptance(whichtype,jet_Obs_gen_abs,jet_Obs_pt_gen_abs,jet_Obs_multi_gen_abs, jet_Obs_eta_gen_abs,numbOfJetsSelected)) jTruePythia->Fill (jet_Obs_gen_abs,evWeightSherpa);
     }
  }
  cout<<"Area PRE-Unfolding "<<jData->Integral()<<endl;
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
  RooUnfoldResponse response_jMethod3(jMCreco, jTrue, jMatxAnneMarie); 
  RooUnfoldResponse response_jMatched(jMCreco, jTrueMatched, jMatx); 
  response_j.UseOverflow();   ///////////===================> Senza questo, ottengo il TSVDUnfold!!!!!!!!!!!!!!!!!!!
  response_jMatched.UseOverflow();   ///////////===================> Senza questo, ottengo il TSVDUnfold!!!!!!!!!!!!!!!!!!!
  response_jMethod3.UseOverflow();   ///////////===================> Senza questo, ottengo il TSVDUnfold!!!!!!!!!!!!!!!!!!!
  stringstream num;

  string method=whichalgo;
  cout<<"Running "<<method<<" method"<<endl;
  
  for (int k=kmin; k< kmax; k++){
    int myNumber=k; num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Jet pT diff xsec distribution. "+title;
      if (doUnfold) {
	if (identityCheck) jReco=performUnfolding(whichalgo, k, jData, jTrue,response_j, jMCreco,jMatx, numbOfJetsSelected, whichtype);
	if (extraTests) jRecoMatched=performUnfolding(whichalgo, k, jData, jTrueMatched,response_jMatched, jMCreco,jMatx, numbOfJetsSelected, whichtype);
	if (extraTests) jRecoAnne=performUnfolding(whichalgo, k, jData, jTrue,response_jMethod3, jMCreco,jMatx, numbOfJetsSelected, whichtype);
	if (!identityCheck) jReco=performUnfolding(whichalgo, k, jData, jTrue,response_j, jMCreco,jMatx, numbOfJetsSelected, whichtype);
      }
      else{
      jReco=(TH1D*) jData->Clone("jData");
      jReco->SetName("jReco");
      }
      num.str("");
  } 

  //if (!extraTests) jReco->Scale(PUscaleFactor);
  /////////////////////////
  //  Cross Checks
  ////////////////////////

  if (extraTests){
    performCrossChecks(jReco,jData,jTrue,jTrueMatched, jMCreco,jMatx,numbOfJetsSelected,whichtype, whichalgo, kmin, jRecoMatched, jRecoAnne); 
    return;
  }

  if (identityCheck || splitCheck || pythiaCheck ||differentialCrossSection){
    jReco->Scale(1./jReco->Integral());             
    jTrue->Scale(1./jTrue->Integral());
    jMCreco->Scale(1./jMCreco->Integral());
    jData->Scale(1./jData->Integral());
    if (pythiaCheck) jTruePythia->Scale(1./jTruePythia->Integral());
  }

  //Drawing Histograms
  if (doUnfold && !pythiaCheck) { cc= drawPlots(jReco,jData,jTrue,jMCreco,jMatx,numbOfJetsSelected,whichtype, whichalgo, kmin); cc->Draw(); }
  if (doUnfold && pythiaCheck) { d= drawPlots(jReco,jData,jTruePythia,jMCreco,jMatx,numbOfJetsSelected,whichtype, whichalgo, kmin); d->Draw(); }
  //  d->Print("/tmp/a.png");
  //Normalization 
  
  double unfarea=jReco->Integral()/4890.0;
  cout<<"Your unfolding has an integral value of "<<unfarea<<endl;
  cout<<(jReco->GetBinContent(1)+jReco->GetBinContent(2)+jReco->GetBinContent(3)+jReco->GetBinContent(4)+jReco->GetBinContent(5)+jReco->GetBinContent(6))/4890.0<<endl;
  cout<<(jReco->GetBinContent(2)+jReco->GetBinContent(3)+jReco->GetBinContent(4)+jReco->GetBinContent(5)+jReco->GetBinContent(6))/4890.<<endl;
cout<<(jReco->GetBinContent(3)+jReco->GetBinContent(4)+jReco->GetBinContent(5)+jReco->GetBinContent(6))/4890.0<<endl;
cout<<(jReco->GetBinContent(4)+jReco->GetBinContent(5)+jReco->GetBinContent(6))/4890.0<<endl;

  cout<<"Manual area counting"<<endl;
  double areaFinale=0;
  for (int i=0; i<divPlot+2; i++){
    cout<<"Area in bin "<<i<<" is "<<jReco->GetBinContent(i)<<endl;
    areaFinale+=jReco->GetBinContent(i);
  }
  cout<<"Area finale "<<areaFinale/4890<<endl; 

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
  if (saveFile) saveIntoFile(numbOfJetsSelected, whichtype, jReco, jTrue, jMatx, jMCreco, jData);


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

