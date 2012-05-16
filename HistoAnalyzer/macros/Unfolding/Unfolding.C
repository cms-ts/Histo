/**********************************
 * Unfolding Z+jet distributions  *
 *                                *
 * Vieri Candelise November 2011  *
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
#include "tdrStyle.C"
#include <TROOT.h>
#include "TObject.h"
#include <iostream>
#include <sstream>
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "THStack.h"
#include "TLatex.h"
#include <string.h>
#include "getEfficiencyCorrection.C"
#include "tdrstyle.C"
#include "MakePlotLumiLabel.C"

using
std::cout;
using
std::endl;
#endif

//string smc="/gpfs/cms/data/2011/jet/jetValidation_dytoee_pythia_2011_v2_22.root";
string smc="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_22.root";
//string sdata="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_22.root";
string sdata="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_22.root";
TFile *fA = new TFile (smc.c_str());
TFile *fB = new TFile (sdata.c_str());

//Directory and files to start with
string s = "/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/DATA/";

//Save histos to be used afterward
bool saveFile=false; //if True, it will save the rootfile. Switch it, when you are sure!
string direct="/gpfs/cms/data/2011/Unfolding/";
string filename=direct+"UnfoldedDistributions_v2_22.root";

// Efficiency corrections
bool correctForEff=true; // If true, it will take the correction factor from outside

// Evaluate the diff cross section (by dividing the bins by # Z >= 1 or higher)
bool differentialCrossSection=true;

//File with efficiency coefficients
string efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011_v2_22.root";
TFile *eff = TFile::Open(efffile.c_str()); 

// Correct for backgrounds: leading jet Pt
bool correctForBkg=true;
TH1F *relativebkg = new TH1F ("relativebkg", "relativebkg bin contribution",30,0,30);

/* Number of jet associated to a Z distribution */
//-------------------------
double jetPtthreshold=30.0;
int maxNJets=6;
//------------------------

TH1D *NTrue = new TH1D ("N true", "N Truth", maxNJets-1, 1, maxNJets);
TH1D *NData = new TH1D ("N data", "N DATA Measured", maxNJets-1, 1, maxNJets);
TH2D *NMatx = new TH2D ("N hMatx", "Unfolding Matrix in # of jets + Z", maxNJets-1, 1, maxNJets, maxNJets-1, 1, maxNJets);
TH1D *NMCreco = new TH1D ("N mcreco", "N mcreco", maxNJets-1, 1, maxNJets);
TH1D *NMCrecoratio_ = new TH1D ("N mcrecoratio_", "N mcreco_", maxNJets-1, 1, maxNJets);
TH1D *NData2 = new TH1D ("N data2", "N DATA Measured2", maxNJets-1, 1, maxNJets);

/* Z boson pT distribution */
TH1D *PTrue = new TH1D ("pT true", "pT Truth", 20, 0, 200);
TH1D *PData = new TH1D ("pT data", "pT DATA Measured", 20, 0, 200);
TH2D *PMatx = new TH2D ("pT hMatx", "Unfolding Matrix Z pT ", 100, 0, 100, 20, 0, 200);
TH1D *PMCreco = new TH1D ("pT mcreco", "pT mcreco", 20, 0, 200);
TH1D *PData2 = new TH1D ("pT data2", "pT DATA Measured2", 20, 0, 200);
TH1D *PRatio_ = new TH1D ("PRatio_", "PRatio_", 20, 0, 200);

/* Z boson rapidity distribution */
TH1D *yTrue = new TH1D ("y true", "y Truth", 25, -2.5, 2.5);
TH1D *yData = new TH1D ("y data", "y DATA Measured", 25, -2.5, 2.5);
TH2D *yMatx = new TH2D ("y hMatx", "Unfolding Matrix y Rapidity ", 25, -2.5, 2.5, 25, -2.5, 2.5);
TH1D *yMCreco = new TH1D ("y mcreco", "y mcreco", 25, -2.5, 2.5);
TH1D *yData2 = new TH1D ("y data2", "y DATA Measured2", 25, -2.5, 2.5);
TH1D *yRatio_ = new TH1D ("yRatio", "yRatio", 25, -2.5, 2.5);

/*Leading jet pt*/
double minPtPlot=30;
double maxPtPlot=330;
int divPlot=10;
TH1D *jTrue = new TH1D ("jTrue", "jetpT Truth",divPlot,minPtPlot,maxPtPlot);
TH1D *jData = new TH1D ("jData", "jetpT DATA Measured",divPlot,minPtPlot,maxPtPlot);
TH1D *jReco = new TH1D ("jReco", "jetpT Unfolded DATA",divPlot,minPtPlot,maxPtPlot);
TH2D *jMatx = new TH2D ("jMatx", "Unfolding Matrix jetpT Rapidity ",divPlot,minPtPlot,maxPtPlot,divPlot,minPtPlot,maxPtPlot);
TH1D *jMCreco = new TH1D ("jMCreco", "jetpT mcreco",divPlot,minPtPlot,maxPtPlot);
TH1D *jData2 = new TH1D ("jData2", "jetpT DATA Measured2",divPlot,minPtPlot,maxPtPlot);
TH1D *jRatio_ = new TH1D ("jRatio_", "jetpTRatio",divPlot,minPtPlot,maxPtPlot);
TH1D *PRatio = new TH1D ("PRatio", "reco/gen ratio",divPlot,minPtPlot,maxPtPlot);
//To compute errors
TH1F *staterror = new TH1F ("staterror", "staterror",30,0,30);
TH1F *staterrorsqrt = new TH1F ("staterrorsqrt", "staterrorsqrt",30,0,30);
TH1F *unfoerror = new TH1F ("unfoerror", "unfoerror",30,0,30);
TH1F *unfoerrormat = new TH1F ("unfoerrormat", "unfoerrormat",30,0,30);
TH1F *unfoerrordiag = new TH1F ("unfoerrordiag", "unfoerrordiag",30,0,30);


TH1D *NReco;
TH1D *PReco;
TH1D *yReco;
bool cold=true;
std::vector<std::vector<double> > kcontainer;


// name of the root file containing background evaluation
string dir="/gpfs/cms/data/2011/BackgroundEvaluation/";
string version="_v2_22.root";
string bkgstring=dir+"Backgrounds"+version;

string supplabel="";

TCanvas* C = new TCanvas("C","C",0,0,800,600);
TCanvas *cmultip = new TCanvas ("cmultip", "cmultip", 1000, 700);


//Set the Matrixes size!

RooUnfoldResponse response_pT (20, 0, 200);
RooUnfoldResponse response_y  (25, -2.5, 2.5);
//RooUnfoldResponse response_j  (30, 30, 330); 

std::vector<double> getBackgroundContributions(string filebkg, string str); // return the value to be subtracted to get the signal. Evaluated in DrawCompariosnJet.C

void
Unfolding::Loop()
{
  setTDRStyle();
  //LoopJetMultiplicity();
  //LoopZpt();
  //LoopZy();
  int numbOfJets=1;
  LoopJetPt(numbOfJets);
}

//Include the functions.. Make order, please!
#include "UnfoldingJetMultiplicity.h"
#include "UnfoldingZPt.h"
#include "UnfoldingZy.h"


void
Unfolding::LoopJetPt (int numbOfJets)
{
  cout<<"*********************************"<<endl;
  cout<<"Unfolding Jet Pt"<<endl;
  cout<<"*********************************"<<endl;
  
#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  string sdatadir=sdata+":/validationJEC";
  string smcdir=smc+":/validationJEC";
  
  //Enter the files
  fA->cd (smcdir.c_str());
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  //DATA
  fB->cd (sdatadir.c_str());
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");

  //Setting the errors
  jTrue->Sumw2();
  jMCreco->Sumw2();
  jData->Sumw2();

  //Dummy way to have the total number of Z
  TH1F* obj;
  obj=(TH1F*)gDirectory->Get("h_invMass");
  int NZ=obj->GetEntries();

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;		/* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;

       //if (ientry>80000) continue;
      
      if (numbOfJets<=1){
	if((jet1_pt>=0 && jet1_pt<7000) || (jet1_pt_gen>=0 && jet1_pt_gen<7000) ){   // Old working if((jet1_pt>=0 && jet1_pt<7000) || (jet1_pt_gen>0 && jet1_pt_gen<7000) ){
	  std::vector<double> valuesmc=getEfficiencyCorrectionPt(efffile.c_str(),numbOfJets,jet1_pt,"MC");
	  double effcorrmc=1.00/valuesmc[0];	
	  double efferrmc=valuesmc[1]/pow(valuesmc[0],2);
	  jTrue->Fill (jet1_pt_gen);
	  jMCreco->Fill (jet1_pt);
	  jMatx->Fill (jet1_pt, jet1_pt_gen,effcorrmc);
	  supplabel="_jet1";
	}
      }
      if (numbOfJets==2){
	if((jet2_pt>=0 && jet2_pt<7000) || (jet2_pt_gen>=0 && jet2_pt_gen<7000) ){
	  jTrue->Fill (jet2_pt_gen);
	  jMCreco->Fill (jet2_pt);
	  jMatx->Fill (jet2_pt, jet2_pt_gen); 
	}
	supplabel="_jet2";
      }
      if (numbOfJets==3){
	if((jet3_pt>=0 && jet3_pt<7000) || (jet3_pt_gen>=0 && jet3_pt_gen<7000) ){
	  jTrue->Fill (jet3_pt_gen);
	  jMCreco->Fill (jet3_pt);
	  jMatx->Fill (jet3_pt, jet3_pt_gen); 
	}
	supplabel="_jet3";
      }
      if (numbOfJets==4){
	if((jet4_pt>=0 && jet4_pt<7000) || (jet4_pt_gen>=0 && jet4_pt_gen<7000) ){
	  jTrue->Fill (jet4_pt_gen);
	  jMCreco->Fill (jet4_pt);
	  jMatx->Fill (jet4_pt, jet4_pt_gen); 
	}
	supplabel="_jet4";
      }
    }
  jTrue->Sumw2();
  jMCreco->Sumw2();
  

  fChain = tree_fB;		/* Loop RunB */
  Init (fChain);	
  Long64_t nentries2 = fChain->GetEntriesFast ();
  Long64_t nb2 = 0;
  
  if (fChain == 0)
    return;
  
  for (Long64_t jentry = 0; jentry < nentries2; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb2 = fChain->GetEntry (jentry);
      nbytes += nb2;

      if (numbOfJets==1){      
	if( jet1_pt>jetPtthreshold && jet1_pt<7000 ){    // Old        if( jet1_pt>=0 && jet1_pt<7000 ){
	  jData->Fill (jet1_pt);
	  jData2->Fill (jet1_pt);
	}
      }
      if (numbOfJets==2){      
	if(jet2_pt>jetPtthreshold && jet2_pt<7000){
	  jData->Fill (jet2_pt);
	  jData2->Fill (jet2_pt);
	}
      }
      if (numbOfJets==3){      
	if(jet3_pt>jetPtthreshold && jet3_pt<7000){
	  jData->Fill (jet3_pt);
	  jData2->Fill (jet3_pt);
	}
      }
      if (numbOfJets==4){      
	if(jet4_pt>jetPtthreshold && jet4_pt<7000){
	  jData->Fill (jet4_pt);
	  jData2->Fill (jet4_pt);
	}
      }
    }

  
  // SAVE AREA TO EVALUATE DIFFERENTIAL CROSS SECTIONS
  double scaleFactor=jData->GetEntries();
  double Zarea=jData->Integral();
  double ZMCarea=jMCreco->Integral();
  cout<<"#Z->"<<scaleFactor<<" area->"<<Zarea<<endl;
  
  //////////////
  // MC Normalization
  //////////////
  double ScaleMCData = ((double)jData->Integral()/(double)jMCreco->Integral());
      
  /////////////////
  // Efficiency Correction
  /////////////////
      
  double areaRecoVsTruth=1.000;
  TH1F* DataCorr;
  TH1F* PTJetMultiplicityUnfolded;
  cout<<"jData area before "<<jData->Integral()<<endl;
  if (correctForEff){
    for (unsigned int k=0; k<=divPlot; k++){
      // Retrieve efficiency correction and its error for data
      std::vector<double> valuesdata=getEfficiencyCorrectionPt(efffile.c_str(),numbOfJets,(k*((maxPtPlot-minPtPlot)/divPlot)+minPtPlot),"Data");
      //NB: you did: y=1/a -> errors -> sigmay=sqrt(df/da^2 * sigmaa^2 ) -> sigmaa/a^2!

      double effcorrdata=1.00/valuesdata[0];
      double efferrdata=valuesdata[1]/pow(valuesdata[0],2);

      // Retrieve efficiency correction and its error for MC
      std::vector<double> valuesmc=getEfficiencyCorrectionPt(efffile.c_str(),numbOfJets,(k*((maxPtPlot-minPtPlot)/divPlot)+minPtPlot),"MC");
      double effcorrmc=1.00/valuesmc[0];	
      double efferrmc=valuesmc[1]/pow(valuesmc[0],2);	  
      cout<<"efficieiency correction that you're applying are-> MC:"<<effcorrmc<<" data:"<<effcorrdata<<" (errors are MC:"<<efferrmc<<" and data:"<<efferrdata<<"). Those are percentage, multiplied by the bin content you get an error of (data): "<<efferrdata*jData->GetBinContent(k+1);
      cout<<" -- convolution with data-> stat error:"<<jData->GetBinError(k+1);

      //Correct distributions for efficiency
      jMCreco->SetBinContent(k+1, jMCreco->GetBinContent(k+1)*(effcorrmc));
      jData->SetBinContent(k+1, jData->GetBinContent(k+1)*(effcorrdata));
      jData2->SetBinContent(k+1, jData2->GetBinContent(k+1)*(effcorrdata));	 

      //Now, consider the efficiency error and the normal one
      // a=efficiency, sigmaa=eff error, b=stat value, sigmab=stat err
      // f=a*b -> sigmaf=sqrt(b^2*sigmaa^2+a^2*sigmab^2)
      jData->SetBinError(k+1, sqrt( pow(jData->GetBinContent(k+1),2)*pow(efferrdata,2) + pow(effcorrdata,2)*pow(jData->GetBinError(k+1),2) ) );
      jData2->SetBinError(k+1, sqrt( pow(jData2->GetBinContent(k+1),2)*pow(efferrdata,2) + pow(effcorrdata,2)*pow(jData2->GetBinError(k+1),2) ) );
      jMCreco->SetBinError(k+1, sqrt( pow(jMCreco->GetBinContent(k+1),2)*pow(efferrdata,2) + pow(effcorrdata,2)*pow(jMCreco->GetBinError(k+1),2) ) );	  
      cout<<" -- convolution with eff-> final error:"<<jData->GetBinError(k+1)<<" (relative bin error %"<<100.0*jData->GetBinError(k+1)/jData->GetBinContent(k+1)<<")"<<endl;
    }
    jData->Scale(Zarea/jData->Integral());
    jData2->Scale(Zarea/jData2->Integral());
    jMCreco->Scale(ZMCarea/jMCreco->Integral());
    jTrue->Scale(ZMCarea/jTrue->Integral());
  }

  cout<<"jData area after "<<jData->Integral()<<endl;     
  if (correctForBkg){
    std::vector<double> bckcoeff;
    if (numbOfJets==1) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT");
    if (numbOfJets==2) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT2");
    if (numbOfJets==3) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT3");
    if (numbOfJets==4) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT4");

    for (unsigned int k=0; k<bckcoeff.size(); k++){
      cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]*Zarea<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is "<<bckcoeff[k]*Zarea/jData->GetBinContent(k+1)<<endl;
      jData->SetBinContent(k+1, jData->GetBinContent(k+1) - bckcoeff[k]*Zarea);
      jData2->SetBinContent(k+1, jData2->GetBinContent(k+1) - bckcoeff[k]*Zarea);	
      relativebkg->SetBinContent(k+1,bckcoeff[k]*Zarea/jData->GetBinContent(k+1));
    }
  }
  
  //TH2D *jMatxeff = new TH2D ("jMatxeff", "Unfolding Matrix jetpT Rapidity ",divPlot,minPtPlot,maxPtPlot,divPlot,minPtPlot,maxPtPlot);
  //for (int i=0;i<jMCreco->GetNbinsX();i++){
  //for (int k=0;k<jTrue->GetNbinsX();k++){
  //  jMatxeff->SetBinContent(i+1,k+1, jMatxeff->GetBinContent(i+1,k+1)*);
  //}
  //}


  RooUnfoldResponse response_j(jMCreco, jTrue, jMatx); 
  response_j.UseOverflow();
      
  cout<<"***********************"<<endl;
  cout<<"MC will be normalized to data, using entries"<<endl;
  cout<<"N entries in Data:"<<jData->Integral()<<" and MC:"<<jMCreco->Integral()<<" ratio->"<<ScaleMCData<<endl;
  cout<<endl;
  //jMCreco->Scale (ScaleMCData);
  //jTrue->Scale (ScaleMCData);
      
  for (int j=1; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=15; k<16; k++){
      int myNumber=k;
      stringstream num;
      num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Jet pT diff xsec distribution. "+title;
      cout<<"ongoing:"<<title<<endl;
      
      cout<<"dassssssssssssssssssssssssssssssssss "<<jData->GetBinContent(2)<<endl;
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_j(&response_j, jData, myNumber, 1000);
	jReco = (TH1D *) unfold_j.Hreco ();
      }
      if (method=="Svd"){
	jReco->Sumw2();
	RooUnfoldSvd unfold_j (&response_j, jData, myNumber, 1000);	// OR
	jReco = (TH1D *) unfold_j.Hreco ();

	// Extract covariance matrix TMatrixD m= unfold_j.Ereco();
	TVectorD vstat= unfold_j.ErecoV();
	TVectorD vunfo= unfold_j.ErecoV(RooUnfold::kCovToy);
	TVectorD vunfomat= unfold_j.ErecoV(RooUnfold::kCovariance);
	TVectorD vunfodiag= unfold_j.ErecoV(RooUnfold::kErrors);

	for (unsigned int p=0;p<jData->GetNbinsX();p++){
	  cout<<vstat[p]<<" "<<vunfo[p]<<endl;
	  staterrorsqrt->SetBinContent(p+1,sqrt(jData->GetBinContent(p+1))/jData->GetBinContent(p+1));
	  staterror->SetBinContent(p+1,vstat[p]/jData->GetBinContent(p+1));
	  unfoerrormat->SetBinContent(p+1,vunfomat[p]/jData->GetBinContent(p+1));
	  unfoerror->SetBinContent(p+1,vunfo[p]/jData->GetBinContent(p+1));
          unfoerrordiag->SetBinContent(p+1,vunfodiag[p]/jData->GetBinContent(p+1));

	  //Returns vector of unfolding errors computed according to the withError flag:
	  //0: Errors are the square root of the bin content
	  //1: Errors from the diagonals of the covariance matrix given by the unfolding
	  //2: Errors from the covariance matrix given by the unfolding
	  //3: Errors from the covariance matrix from the variation of the results in toy MC tests
	  // enum ErrorTreatment { 	kNoError	
	  //kErrors	
	  //kCovariance	
	  //kCovToy	
	}

	std::vector<double> err;
	for (unsigned int k=0; k<jData->GetNbinsX(); k++){
	  jReco->SetBinError(k+1,sqrt(pow(vstat[k],2) + sqrt(pow(vunfo[k],2)) )); // How we chose to treat the eerros.. quatradutre sum
	  err.push_back(sqrt(pow(vstat[k],2) + sqrt(pow(vunfo[k],2))));
	}
	kcontainer.push_back(err);
	
      }
      
      jReco->Sumw2();
      jReco->SetName("jReco"); // After unfolding, it changed the name...
      jData->Sumw2();
      jMCreco->Sumw2();
      jTrue->Sumw2();	
      
      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.2, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      string whichjet="";
      if (numbOfJets==1) whichjet="Leading "; 
      if (numbOfJets==2) whichjet="Second leading "; 
      if (numbOfJets==3) whichjet="Third leading "; 
      if (numbOfJets==4) whichjet="Fourth leading "; 
      title2=whichjet+"jet pT diff xsec distribution. "+title;
      jReco->SetTitle (title2.c_str());
      jReco->GetXaxis ()->SetTitle ("");
      jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d p_{T}");
      jReco->SetMarkerStyle (20);
      jData->SetMarkerStyle (21);
      jData->SetLineColor(kGreen);

      //Normalize the area, to fit data with MC!
      double area = (((double)jReco->Integral ()) / (double)jTrue->Integral ());
      cout<<"area "<<area<<endl;
      jMCreco->Scale(area);
      jTrue->Scale  (area);
      
      if (differentialCrossSection){
	jReco->Scale(1./Zarea);		
	jTrue->Scale(1./Zarea);
	jMCreco->Scale(1./Zarea);
	jData->Scale(1./Zarea);
      }
      
      jReco->SetMarkerStyle (20);
      jMCreco->SetStats(0);
      jData->SetStats(0);
      jTrue->SetStats(0);
      jReco->SetStats(0);
      jReco->GetXaxis()->SetTitle("jet pT [GeV/c]");
      jReco->SetLineColor (kBlack); 
      jReco->Draw("EP");	//risultato dell'unfolding

      jMCreco->SetLineColor (kBlue + 1);
      jMCreco->SetLineStyle (2);
      jMCreco->SetLineWidth (2); 
      jMCreco->Draw("HISTSAMES");
      jTrue->SetLineColor (kRed);
      jTrue->SetLineWidth (2);
      jTrue->Draw ("HISTSAME");
      jData->SetLineColor(kGreen+1);
      pad1->SetLogy (1);
      jData->SetMarkerStyle (4);
      jData->SetMarkerColor(kGreen+1);
      jData->SetStats(0);
      jData->Draw("EPSAME");
   
      pad1->SetBottomMargin (0.1);
      
      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (jReco, "Data Unfolded", "P20");
      legend_d->AddEntry (jTrue, "MC truth", "L");
      legend_d->AddEntry (jMCreco, "MC reco", "L");
      legend_d->AddEntry(jData,"Data Folded","P20");
      legend_d->Draw ("same");
 
      TLatex *latexLabel=CMSPrel(4.890,""); // make fancy label
      latexLabel->Draw("same");   
      pad1->Update();      
      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.2);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      TH1F *jRecoClone= (TH1F*) jReco->Clone("jReco");
      jRecoClone->SetName("jRecoClone");      
      jRecoClone->SetStats(0);
      jRecoClone->GetXaxis ()->SetLabelSize (0.1);
      jRecoClone->GetYaxis ()->SetLabelSize (0.08);
      jRecoClone->Divide(jTrue);
      jRecoClone->SetMarkerStyle (6);
      jRecoClone->GetXaxis ()->SetLabelSize (0.06);
      jRecoClone->GetYaxis ()->SetLabelSize (0.06);
      jRecoClone->GetXaxis ()->SetTitleSize (0);
      jRecoClone->GetYaxis ()->SetTitleSize (0.06);
      jRecoClone->GetYaxis ()->SetTitleOffset (0.5);

      jRecoClone->GetYaxis ()->SetRangeUser (0.5, 1.5);
      jRecoClone->GetXaxis ()->SetRangeUser (0, 5);
      jRecoClone->GetYaxis ()->SetTitle ("Ratios");
      jRecoClone->GetXaxis ()->SetTitle("jet pT [GeV/c]");
      jRecoClone->SetMarkerStyle (20);
      jRecoClone->SetLineWidth (0);
      jRecoClone->SetTitle ("");
      double max=jRecoClone->GetMaximum();
      double min=jRecoClone->GetMinimum();
      jRecoClone->GetYaxis()->SetRangeUser(min,max);
      jRecoClone->Draw("ep");
      
      TH1F *jMCRecoClone= (TH1F*) jMCreco->Clone("jMCreco");
      jMCRecoClone->SetName("jMCRecoClone"); 
      jMCRecoClone->Divide(jTrue);
      jMCRecoClone->SetLineWidth (0.1);
      jMCRecoClone->Draw ("HISTSAME");

      TF1 *f = new TF1("f","1",0,410);
      f->SetLineWidth(1);
      f->Draw("SAMES");

      TLegend *legend_w = new TLegend(0.197791, 0.736607, 0.394578, 0.9375);
      legend_w->SetFillColor (0);
      legend_w->SetFillStyle (0);
      legend_w->SetBorderSize (0);
      legend_w->AddEntry (jRecoClone, "Data unfolded / MC truth", "P20");
      legend_w->AddEntry (jMCRecoClone, "MC reco / MC truth", "L");
      legend_w->Draw ("same");
      //pad2->Update();
      string title3= s+"JETPTXSEC"+method+"_"+num.str()+supplabel+".png";
      //c->cd ();
      c->Print(title3.c_str());

      TCanvas *err = new TCanvas ("err", "err", 1000, 700);
      err->cd ();
      staterror->SetStats (0);
      staterror->GetXaxis()->SetTitle("Jet Pt bin");
      staterror->GetYaxis()->SetTitle("Relative error");
      staterror->GetYaxis()->SetRangeUser(0.,.25);
      staterror->Draw();
      staterrorsqrt->SetLineColor(kViolet);
      staterrorsqrt->Draw("SAME");
      unfoerror->SetLineColor(kRed);
      unfoerror->Draw("SAME");

      TLegend *legend_e = new TLegend (0.23494, 0.696429, 0.431727, 0.895833);
      legend_e->SetFillColor (0);
      legend_e->SetFillStyle (0);
      legend_e->SetBorderSize (0);
      legend_e->AddEntry (staterror, "Statistical Errors", "L");
      legend_e->AddEntry (unfoerror, "Unf. Errors with Toy", "L");
      legend_e->AddEntry (staterrorsqrt, "Statistical Errors, sqrt of data", "L");
      legend_e->Draw ("same");

      string title4= s+"JETPTerror"+method+"_"+num.str()+supplabel+".png";
      err->Print(title4.c_str());

      TCanvas *N =new TCanvas ("jet pT response matrix", "jet pT response matrix", 1000, 700);
      N->cd ();
      jMatx->SetStats (0);
      jMatx->GetZaxis()->SetRangeUser(0.002,1);
      jMatx->GetXaxis()->SetTitle("Reconstructed jet pT [GeV/c]");
      jMatx->GetYaxis()->SetTitle("Generated jet pT [GeV/c]");
      gStyle->SetPalette (1);
      gStyle->SetPaintTextFormat ("5.3f");
      gStyle->SetNumberContours (999);
      jMatx->SetMarkerColor (kBlack);
      double entries=1.000/(double)jMatx->GetEntries();
      jMatx->Scale(entries);
      jMatx->Draw ("COLZ,text");
      string title5= s+"JetPtUnfoMatrix"+method+"_"+num.str()+supplabel+".png";
      N->Print(title5.c_str());      

      for (unsigned int p=0;p<staterror->GetNbinsX();p++){
	staterror->SetBinContent(p+1,0);	  
	unfoerror->SetBinContent(p+1,0);
	staterrorsqrt->SetBinContent(p+1,0);
      }

      num.str("");
      //delete staterror;
      //delete unfoerror;
      //delete unfoerrormat;
 
      if (cold){
	cold=false;
      }

      //Bring the scale back again to unfold properly...

      if (differentialCrossSection){
	jReco->Scale(Zarea);		
	jTrue->Scale(Zarea);
	jMCreco->Scale(Zarea);
	jData->Scale(Zarea);
      }      
    }
  }
  
   TCanvas *rel =new TCanvas ("rel", "Background relative contribution, bin by bin", 1000, 700);
  rel->cd ();
  relativebkg->SetLineColor(kRed);
  relativebkg->GetXaxis()->SetTitle("Jet Pt Bin");
  relativebkg->Draw();
  string title4= s+"BakgroundContribution.png";
  rel->Print(title4.c_str());
  
  TCanvas *kparam =new TCanvas ("kparam", "errors as a function of the k param", 1000, 700);
  bool firstp=true;
  kparam->cd();     
  TLegend *legend_e = new TLegend (0.73494, 0.63, 0.931727, 0.83);
  legend_e->SetFillColor (0);
  legend_e->SetFillStyle (0);
  legend_e->SetBorderSize (0);
  
  for (int i=0; i<kcontainer.size(); i++){
    stringstream num;
    num<<i;
    std::vector<double> ki=kcontainer[i];
    TH1D *histo= new TH1D("histo","histo",30,0,30);
    for (int ii=0; ii<ki.size();ii++){
      histo->SetBinContent(ii+1,ki[ii]);
      histo->SetLineWidth(2);
    }
    histo->SetLineColor(i+2);
    if (firstp) {
      histo->GetYaxis()->SetRangeUser(0,3000);
      histo->Draw();
      firstp=false;
      string stringa="k="+num.str();
      legend_e->AddEntry (histo,stringa.c_str(), "L");
    }
    else {
      histo->Draw("SAME");
      string stringa="k="+num.str();
      legend_e->AddEntry (histo,stringa.c_str(), "L");
    }   
    num.str("");
  }
  legend_e->Draw("same");
  
  string title6= s+"Kparam.png";
  kparam->Print(title6.c_str()); 
      
  ///////////
  ///SAve unfolded distribution
  /////////// 
      
  if (saveFile){
    TFile* w = new TFile(filename.c_str(), "RECREATE");
    w->cd();
    jReco->Write();
    w->Close();
  }  
}

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
  
  return value;
}
