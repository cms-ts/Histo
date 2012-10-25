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

string version="_v2_30.root";
bool isMu=false;  
bool isEle=!isMu;
bool makeSecondaryPlots=true;

string smc="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011Mu"+version;
//smc="/tmp/matteo.root";
string sdata="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011"+version;
string smcpythia="/gpfs/cms/data/2011/jet/jetValidation_zjets_sherpa_2011_v2_32.root";

TFile *fA;
TFile *fB;
TFile *fPythia;

//Directory and files to start with
 string s = "/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/DATA/";

//Save histos to be used afterward
bool saveFile=true; //if True, it will save the rootfile. Switch it, when you are sure!
string direct="/gpfs/cms/data/2011/Unfolding/";
string filename=direct+"UlfoldedDistributions_v2_32ApprovalNoNormalizationEtaUnf.root";//+version;
//string filename="/tmp/pippo.root";

// Efficiency corrections
bool correctForEff=true; // If true, it will take the correction factor from outside
bool useElectronsToCorrect=true;

// Evaluate the diff cross section (by dividing the bins by # Z >= 1 or higher)
bool differentialCrossSection=false;

// Correct for backgrounds: 
bool correctForBkg=true;
// name of the root file containing background evaluation
string dir="/gpfs/cms/data/2011/BackgroundEvaluation/";

//string bkgstring=dir+"Backgrounds"+version;
string bkgstring=dir+"Backgrounds_v2_28.root";

//File with efficiency coefficients
string efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011_v2_28_approval.root";//+version;

TFile *eff;

//Open MC and data files to retrieve effciencies
TFile *fAeff; // WHY 2 FILES? DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
TFile *fBeff; 

/* Number of jet associated to a Z distribution */
//-------------------------
double jetPtthreshold=30.0;
int maxNJets=7;
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
  if (isMu) {
    s = "/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/DATA/Mu/";
    smc="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011Mu"+version;
    sdata="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011Mu"+version;
    efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011Mu_v2_30_approval.root";//+version;
    bkgstring=dir+"BackgroundsMu_v2_30.root";
  }

  //  smc="/tmp/matteo.root";

  fA = new TFile (smc.c_str());
  fB = new TFile (sdata.c_str()); 

  eff = TFile::Open(efffile.c_str()); 

//Open MC and data files to retrieve effciencies
  fAeff = new TFile (efffile.c_str());// WHY 2 FILES? DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  fBeff = new TFile (efffile.c_str());  

  cout<<"########################################"<<endl;
  cout<<"You're using:"<<endl;
  cout<<smc<<endl;
  cout<<sdata<<endl;
  cout<<efffile<<endl;
  cout<<bkgstring<<endl;
  cout<<"########################################"<<endl;

  setTDRStyle();

  int numbOfJetsForLoop=1;
  LoopJetPt(numbOfJetsForLoop);
  //LoopHt(numbOfJetsForLoop);
  //LoopJetEta(numbOfJetsForLoop);

  LoopJetMultiplicity();
  

}

void
Unfolding::LoopOneFour()
{
  if (isMu) {
    s = "/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/DATA/Mu/";
    smc="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011Mu"+version;
    sdata="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011Mu"+version;
    efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011Mu_v2_30_approval.root";//+version
    bkgstring=dir+"BackgroundsMu_v2_30.root";
  }

  fA = new TFile (smc.c_str());
  fB = new TFile (sdata.c_str()); 

  eff = TFile::Open(efffile.c_str()); 

//Open MC and data files to retrieve effciencies
  fAeff = new TFile (efffile.c_str());// WHY 2 FILES? DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  fBeff = new TFile (efffile.c_str());

  cout<<"########################################"<<endl;
  cout<<"You're using:"<<endl;
  cout<<smc<<endl;
  cout<<sdata<<endl;
  cout<<efffile<<endl;
  cout<<bkgstring<<endl;
  cout<<"########################################"<<endl;

  setTDRStyle();
  //LoopJetMultiplicity();

  for (int i=1; i<=4; i++){
    //LoopHt(i);
    //LoopZpt();
    //LoopZy();
    //LoopJetPt(i);
    LoopJetEta(i); // ------------------------> Correggere baco, fare metodo Miss,Fake e controllare "correctGenJetEta"
  }
}


//Include the functions.. Make order, please!
#include "UnfoldingJetMultiplicity.h"
#include "UnfoldingZPt.h"
#include "UnfoldingZy.h"
#include "UnfoldingJetPt.h"
#include "LoopEta.h"
#include "UnfoldingHt.h"

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

  TH1F *leadhistoeta;
  TH1F *leadhistoeta2;
  TH1F *leadhistoeta3;
  TH1F *leadhistoeta4;

  TH1F *multiphisto;
  TH1F *HT;
  TH1F *HT1;
  TH1F *HT2;
  TH1F *HT3;
  TH1F *HT4;

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
  
    if(temp=="leadhistoeta"){
      gDirectory->GetObject(name.c_str(),leadhistoeta);
    } 
    if(temp=="leadhistoeta2"){
      gDirectory->GetObject(name.c_str(),leadhistoeta2);
    } 
    if(temp=="leadhistoeta3"){
      gDirectory->GetObject(name.c_str(),leadhistoeta3);
    } 
    if(temp=="leadhistoeta4"){
      gDirectory->GetObject(name.c_str(),leadhistoeta4);
    } 

  //FIlling the histograms
    if(temp=="HT"){
      gDirectory->GetObject(name.c_str(),HT);
    }
    if(temp=="HT1"){
      gDirectory->GetObject(name.c_str(),HT1);
    } 
    if(temp=="HT2"){
      gDirectory->GetObject(name.c_str(),HT2);
    } 
    if(temp=="HT3"){
      gDirectory->GetObject(name.c_str(),HT3);
    } 
    if(temp=="HT4"){
      gDirectory->GetObject(name.c_str(),HT4);
    } 

}
  ///////////////////////////////////

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

  //////////////////////////////////

   if (str=="jet_eta"){
    for(int k=0; k<leadhistoeta->GetNbinsX(); k++){
      value.push_back(leadhistoeta->GetBinContent(k+1));
    }
  }

  if (str=="jet_eta2"){
    for(int k=0; k<leadhistoeta2->GetNbinsX(); k++){
      value.push_back(leadhistoeta2->GetBinContent(k+1));
    }
  }

  if (str=="jet_eta3"){
    for(int k=0; k<leadhistoeta3->GetNbinsX(); k++){
      value.push_back(leadhistoeta3->GetBinContent(k+1));
    }
  }

  if (str=="jet_eta4"){
    for(int k=0; k<leadhistoeta4->GetNbinsX(); k++){
      value.push_back(leadhistoeta4->GetBinContent(k+1));
    }
  }

  /////////////////////////////
 
  if (str=="jet_Multiplicity"){
    for(int k=0; k<multiphisto->GetNbinsX(); k++){
        value.push_back(multiphisto->GetBinContent(k+1));
    }
  }

  ////////////////////////////
  
  if (str=="HT"){
    for(int k=0; k<HT->GetNbinsX(); k++){
        value.push_back(HT->GetBinContent(k+1));
    }
  }
  if (str=="HT1"){
    for(int k=0; k<HT1->GetNbinsX(); k++){
        value.push_back(HT1->GetBinContent(k+1));
    }
  }
  if (str=="HT2"){
    for(int k=0; k<HT2->GetNbinsX(); k++){
        value.push_back(HT2->GetBinContent(k+1));
    }
  }
  if (str=="HT3"){
    for(int k=0; k<HT3->GetNbinsX(); k++){
        value.push_back(HT3->GetBinContent(k+1));
    }
  }
  if (str=="HT4"){
    for(int k=0; k<HT4->GetNbinsX(); k++){
        value.push_back(HT4->GetBinContent(k+1));
    }
  }
  return value;
}
