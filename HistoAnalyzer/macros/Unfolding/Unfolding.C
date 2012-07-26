/**********************************
 * Unfolding Z+jt distributions  *
 *                                *
 * Matteo Marone 2012             *
 **********************************
 *********************************/


#if !defined(__CINT__) || defined(__MAKECINT__)

#define 	Unfolding_cxx

#include "Unfolding.h"
#include <TH2.h>
#include "TF1.h"
#include <TStyle.h>
#include <TCanvas.h>
#include "TRandom.h"
#include "TH1D.h"
#include "TFile.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include "TLatex.h"
#include <vector>
#include <iostream>
//#include "tdrStyle.C"
#include <TROOT.h>
#include "TObject.h"
#include <iostream>
#include <sstream>
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "THStack.h"
#include "TLatex.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include <string.h>
#include "getEfficiencyCorrection.C"
#include "tdrstyle.C"
#include "MakePlotLumiLabel.C"

using
std::cout;
using
std::endl;
#endif

//string version="_v2_28.root";
string version="_v2_28.root";
bool isMu=false;

//string smc="/gpfs/cms/data/2011/jet/jetValidation_dytoee_pythia_2011_v2_27.root";
string smc="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011"+version;

string sdata="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011"+version;

TFile *fA = new TFile (smc.c_str());
TFile *fB = new TFile (sdata.c_str()); 

//Directory and files to start with
string s = "/afs/infn.it/ts/user/candelis/html/Unfolding/";

//Save histos to be used afterward
bool saveFile=false; //if True, it will save the rootfile. Switch it, when you are sure!
string direct="/gpfs/cms/data/2011/Unfolding/";
string filename=direct+"UnfoldedDistributions"+version;

// Efficiency corrections
bool correctForEff=false; // If true, it will take the correction factor from outside
bool useElectronsToCorrect=true;

// Evaluate the diff cross section (by dividing the bins by # Z >= 1 or higher)
bool differentialCrossSection=false;

// Correct for backgrounds: 
bool correctForBkg=false;
// name of the root file containing background evaluation
string dir="/gpfs/cms/data/2011/BackgroundEvaluation/";

string bkgstring=dir+"Backgrounds"+version;


//File with efficiency coefficients
//string efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011"+version;
string efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011_v2_28.root";//+version;

TFile *eff = TFile::Open(efffile.c_str()); 

//Open MC and data files to retrieve effciencies
TFile *fAeff = new TFile (efffile.c_str());// WHY 2 FILES? DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
TFile *fBeff = new TFile (efffile.c_str());  

/* Number of jet associated to a Z distribution */
//-------------------------
double jetPtthreshold=30.0;
int maxNJets=6;
//------------------------

TH1D *NReco;
TH1D *PReco;
TH1D *yReco;
TH1D *HReco;

bool cold=true;
std::vector<std::vector<double> > kcontainer;
TH1D *PRatio;

string supplabel="";

TCanvas* C = new TCanvas("C","C",0,0,800,600);
TCanvas *cmultip = new TCanvas ("cmultip", "cmultip", 1000, 700);

	  double jetPt=0.0;

//Set the Matrixes size!

RooUnfoldResponse response_pT (20, 0, 200);
RooUnfoldResponse response_y  (25, -2.5, 2.5);
//RooUnfoldResponse response_j  (30, 30, 330); 

std::vector<double> getBackgroundContributions(string filebkg, string str); // return the value to be subtracted to get the signal. Evaluated in DrawCompariosnJet.C

void
Unfolding::Loop()
{
  if (isMu) s = "/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/DATA/Mu/";
  setTDRStyle();
  //LoopJetMultiplicity();
  //LoopZpt();
  //LoopZy();
  LoopHt();
  int numbOfJets=1;
  //LoopJetPt(numbOfJets);
  //LoopJetEta(numbOfJets);
}

void
Unfolding::LoopOneFour()
{
  if (isMu) s = "/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/DATA/Mu/";
  setTDRStyle();
  LoopJetMultiplicity();
  LoopHt();
  for (int i=1; i<=3; i++){
    //LoopZpt();
    //LoopZy();
    //LoopJetPt(i);
    //LoopJetEta(i);
  }
}


//Include the functions.. Make order, please!
#include "UnfoldingJetMultiplicity.h"
#include "UnfoldingZPt.h"
#include "UnfoldingZy.h"
#include "UnfoldingHt.h"
#include "UnfoldingJetPt.h"
#include "LoopEta.h"


#ifndef __CINT__

int
main ()
{
  return 0;
}				// Main program when run stand-alone
#endif

/////////////////////////////////
// Return the Background Contribution
///////////

std::vector<double> getBackgroundContributions(string filename, string str){
  std::vector<double> value;
  TFile *f =  TFile::Open(filename.c_str());
  f->cd();
  TDirectory *dir=gDirectory;
  TList *mylist=(TList*)dir->GetListOfKeys();
  TIter iter(mylist); 
  TObject* tobj = 0;

  TH1F *leadhisto;
  TH1F *leadhisto2;
  TH1F *leadhisto3;
  TH1F *leadhisto4;
  TH1F *multiphisto;
  TH1F *hthisto;

  //Check for the interesting plots, regardless the content..
  while ( (tobj = iter.Next()) ) {
    string name=tobj->GetName();
    TString temp = (TString)name;
    if(temp=="leadhisto"){
      gDirectory->GetObject(name.c_str(),leadhisto);
    } 
    if(temp=="leadhisto2"){
      gDirectory->GetObject(name.c_str(),leadhisto2);
    } 
    if(temp=="leadhisto3"){
      gDirectory->GetObject(name.c_str(),leadhisto3);
    } 
    if(temp=="leadhisto4"){
      gDirectory->GetObject(name.c_str(),leadhisto4);
    } 
    if(temp=="multiphisto"){
      gDirectory->GetObject(name.c_str(),multiphisto);
    } 
  
    if(temp=="hthisto"){
      gDirectory->GetObject(name.c_str(),multiphisto);
    } 
}
  if (str=="jet_pT"){
    for(int k=0; k<leadhisto->GetNbinsX(); k++){
      value.push_back(leadhisto->GetBinContent(k+1));
    }
  }

  if (str=="jet_pT2"){
    for(int k=0; k<leadhisto2->GetNbinsX(); k++){
      value.push_back(leadhisto2->GetBinContent(k+1));
    }
  }

  if (str=="jet_pT3"){
    for(int k=0; k<leadhisto3->GetNbinsX(); k++){
      value.push_back(leadhisto3->GetBinContent(k+1));
    }
  }

  if (str=="jet_pT4"){
    for(int k=0; k<leadhisto4->GetNbinsX(); k++){
      value.push_back(leadhisto4->GetBinContent(k+1));
    }
  }
  
  if (str=="jet_Multiplicity"){
    for(int k=0; k<multiphisto->GetNbinsX(); k++){
        value.push_back(multiphisto->GetBinContent(k+1));
    }
  }
  
  if (str=="HT"){
    for(int k=0; k<hthisto->GetNbinsX(); k++){
        value.push_back(hthisto->GetBinContent(k+1));
    }
  }
  
  return value;
}
