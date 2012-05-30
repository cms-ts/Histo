/**********************************
* Unfolding Z+jet distributions  *
 *                                *
 **********************************
 *********************************/

#if !defined(__CINT__) || defined(__MAKECINT__)

#define 	UnfoldingIdentityCheck_cxx

#include "UnfoldingIdentityCheck.h"
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


using
std::cout;
using
std::endl;
#endif

// Set Parameters

/* Number of jet associated to a Z distribution */
TH1D *NTrue = new TH1D ("N true", "N Truth", 5, 0, 5);
TH1D *NData = new TH1D ("N data", "N DATA Measured", 5, 0, 5);
TH2D *NMatx = new TH2D ("N hMatx", "N hMatx", 5, 0, 5, 5, 0, 5);
TH1D *NMCreco = new TH1D ("N mcreco", "N mcreco", 5, 0, 5);
TH1D *NPyGen = new TH1D ("NPyGen", "N DATA Measured2", 5, 0, 5);
TH1D *NPyRec = new TH1D ("NPyRec", "N DATA Measured2", 5, 0, 5);

/* Z boson pT distribution */
TH1D *PTrue = new TH1D ("pT true", "pT Truth", 20, 0, 200);
TH1D *PData = new TH1D ("pT data", "pT DATA Measured", 20, 0, 200);
TH2D *PMatx = new TH2D ("pT hMatx", "pT hMatx", 20, 0, 100, 20, 0, 200);
TH1D *PMCreco = new TH1D ("pT mcreco", "pT mcreco", 20, 0, 200);
TH1D *PData2 = new TH1D ("pT data2", "pT DATA Measured2", 20, 0, 200);
TH1D *PPyGen = new TH1D ("PPyGen", "N DATA Measured2", 20, 0, 200);
TH1D *PPyRec = new TH1D ("PPyRec", "N DATA Measured2", 20, 0, 200);

/* Z boson rapidity distribution */
TH1D *yTrue = new TH1D ("y true", "y Truth", 25, -2.5, 2.5);
TH1D *yData = new TH1D ("y data", "y DATA Measured", 25, -2.5, 2.5);
TH2D *yMatx = new TH2D ("y hMatx", "y hMatx", 25, -2.5, 2.5, 25, -2.5, 2.5);
TH1D *yMCreco = new TH1D ("y mcreco", "y mcreco", 25, -2.5, 2.5);
TH1D *yData2 = new TH1D ("y data2", "y DATA Measured2", 25, -2.5, 2.5);
TH1D *yPyGen = new TH1D ("yPyGen", "N DATA Measured2", 25, -2.5, 2.5);
TH1D *yPyRec = new TH1D ("yPyRec", "N DATA Measured2", 25, -2.5, 2.5);


TH1D *NReco;
TH1D *PReco;
TH1D *yReco;

//Set the Matrixes size!

RooUnfoldResponse response_N (5, 0, 5); 
RooUnfoldResponse response_pT (20, 0, 200);
RooUnfoldResponse response_y (25, -2.5, 2.5);

//FIles...

TFile *fA = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root");
TFile *fB = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_zjets_pythia6Z2_2011A_v1_9.root");
TFile *fC = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011A_v1_9.root");

void
UnfoldingIdentityCheck::Loop()
{
  LoopJetMultiplicity();
  //LoopZpt();
  //LoopZy();
  LoopJetMultiplicityWithOtherMC();
  //LoopZptWithOtherMC();
  //LoopZyWithOtherMC();
  LoopJetMultiplicityAandB();
  //to be kept out //LoopJetMultiplicityBackground();
}

void
UnfoldingIdentityCheck::LoopJetMultiplicityBackground()
{
  response_N.UseOverflow();

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  fC->cd ("/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011A_v1_9.root:/validationJEC");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");
  double Madgraph_ne = numEventsPerStep("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root", "demo");
  double TTbar_ne = numEventsPerStep("/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011A_v1_9.root", "demo");

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;             /* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  cout<<"The number of Z events is (Mgraph)->"<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;


  /////////////////////////
  ///
  ///   Parametrizing the histogram structure

  //Take the # of simulated events from file...
  double Madgraph_cs=3048;
  double Madgraph_iL= Madgraph_ne/Madgraph_cs;

  double TTbar_cs=157.5;
  double TTbar_iL= TTbar_ne/TTbar_cs;    

  cout<<"Z Magraph has an int lumi of->"<< Madgraph_iL<<" 1/fb while TT bar ->"<< TTbar_iL<<endl;


  ///Bisogna lavure con gli istogrammi


  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
        break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      if (Jet_multiplicity > 20 || Jet_multiplicity_gen > 20 )
        continue;
      NTrue->Fill (Jet_multiplicity_gen);
      NMCreco->Fill (Jet_multiplicity);     
      response_N.Fill (Jet_multiplicity, Jet_multiplicity_gen);
    }

  fChain = tree_fB;             /* Loop RunB */
  Init (fChain);        
  Long64_t nentries2 = fChain->GetEntriesFast ();
  cout<<"The number of Z events is (TTbar)->"<<nentries2<<endl;
  if (fChain == 0)
    return;
  
  for (Long64_t jentry = 0; jentry < nentries2; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
        break;
      int nb2=0;
      nb2 = fChain->GetEntry (jentry);
      nbytes += nb2;
      if (Jet_multiplicity > 20)
        continue;
      NTrue->Fill (Jet_multiplicity_gen);
      NMCreco->Fill (Jet_multiplicity);
    }

  //At this stage, NTrue represent the 

  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=2; k<6; k++){
      int myNumber=k;
      stringstream num;
      num<<myNumber;
      string title=method+" method with K="+num.str()+" (from MGraph) applied on MC Signal + Background (5 1/fb)";
      std::string title2="Jet multiplicity. "+title;

      cout<<title<<endl;
 
      if (method=="Bayesian") {
        RooUnfoldBayes unfold_N (&response_N, NMCreco, myNumber);
        NReco = (TH1D *) unfold_N.Hreco ();
      }
      if (method=="Svd"){
        RooUnfoldSvd unfold_N (&response_N, NMCreco, myNumber);   // OR
        NReco = (TH1D *) unfold_N.Hreco ();
	//double chisq=unfold_N.Chi2(NPyGen, 0);
      }
        
      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.3, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      title2="# jet + Z. "+title;
      NReco->SetTitle (title2.c_str());
      NReco->GetXaxis ()->SetTitle ("");
      NReco->GetYaxis ()->SetTitle ("Entries");
      NReco->SetMarkerStyle (20);
      NReco->SetMarkerStyle (20);
      NReco->SetLineColor (kRed);
      NReco->SetLineWidth (2);
      NReco->SetStats (0);
      NReco->Draw ("P");           //risultato dell'unfolding
      NTrue->SetLineColor(kGreen+1);
      NTrue->Draw("SAME");
      NMCreco->Draw("SAME");

      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (NReco, "MC Sig+Bkg Unf", "LP20");
      legend_d->AddEntry (NMCreco, "MC Sig+Bkg Rec", "L");
      legend_d->AddEntry(NTrue,"Gen Truth","L");
      legend_d->Draw ("same");

      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.3);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      TH1F *CloneH=(TH1F*) NReco->Clone();
      CloneH->SetTitle("CloneH");
      CloneH->SetStats(1);
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(111);
      CloneH->GetXaxis ()->SetLabelSize (0.1);
      CloneH->GetYaxis ()->SetLabelSize (0.08);
      CloneH->Divide (NTrue);
      CloneH->SetMarkerStyle (6);
      CloneH->GetXaxis ()->SetLabelSize (0.06);
      CloneH->GetYaxis ()->SetLabelSize (0.06);
      CloneH->GetXaxis ()->SetTitleSize (0);
      CloneH->GetYaxis ()->SetTitleSize (0.06);
      CloneH->GetYaxis ()->SetTitleOffset (0.5);
      CloneH->GetYaxis ()->SetRangeUser (0.5, 1.3);
      CloneH->GetXaxis ()->SetRangeUser (0, 5);
      CloneH->GetYaxis ()->SetRangeUser (0.5, 1.3);
      CloneH->GetXaxis ()->SetRangeUser (0, 5);
      CloneH->GetYaxis ()->SetTitle ("MC signal+bkg Unfolded/MC truth");
      CloneH->SetMarkerStyle (20);
      CloneH->SetLineWidth (1);
      CloneH->SetTitle ("");
      double max=CloneH->GetMaximum();
      double min=CloneH->GetMinimum();
      CloneH->GetYaxis()->SetRangeUser(min,max);
      CloneH->Draw ("ep");
      TF1 *jj = new TF1 ("jj", "1", 0, 5);
      TF1 *fj = new TF1 ("fj", "[0]", 0, 5);
      fj->SetLineWidth(.5);
      fj->SetLineColor(kWhite);
      CloneH->Fit(fj);
      jj->SetLineColor (kBlue + 1);
      jj->SetLineWidth (1);
      jj->SetLineStyle (2);
      jj->Draw ("same");
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/DataBkgMixing/jetMultiplicityWithOtherMC_"+method+"_"+num.str()+".pdf";
      c->cd ();
      c->Print(title3.c_str());
      num.str("");
    }
  }
}

void
UnfoldingIdentityCheck::LoopJetMultiplicityWithOtherMC()
{
  response_N.UseOverflow();

  cout<<"*********************************"<<endl;
  cout<<"This Macro will perform a test   "<<endl;
  cout<<"The unfolding matrix will be applied"<<endl;
  cout<<"On the MC reco instead of data"<<endl;
  cout<<"Must be exactly alike"<<endl;
  cout<<"*********************************"<<endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;             /* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;


  //COnsider the events outside range...
  response_pT.UseOverflow();

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
        break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      if (Jet_multiplicity > 20 || Jet_multiplicity_gen > 20 )
        continue;
      
      response_N.Fill (Jet_multiplicity, Jet_multiplicity_gen);
    }

  fB->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_pythia6Z2_2011A_v1_9.root:/validationJEC");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");
  fChain = tree_fB;             /* Loop RunB */
  Init (fChain);        
  Long64_t nentries2 = fChain->GetEntriesFast ();
  
  if (fChain == 0)
    return;
  
  for (Long64_t jentry = 0; jentry < nentries2; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
        break;
      int nb2=0;
      nb2 = fChain->GetEntry (jentry);
      nbytes += nb2;
      if (Jet_multiplicity > 20)
        continue;
      
      NPyGen->Fill (Jet_multiplicity_gen);
      NPyRec->Fill (Jet_multiplicity);
    }

  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=2; k<6; k++){
      int myNumber=k;
      stringstream num;
      num<<myNumber;
      string title=method+" method with K="+num.str()+" (from MGraph) applied on Pythia";
      std::string title2="Jet multiplicity. "+title;
      cout<<title<<endl;
 
      if (method=="Bayesian") {
        RooUnfoldBayes unfold_N (&response_N, NPyRec, myNumber);
        NReco = (TH1D *) unfold_N.Hreco ();
      }
      if (method=="Svd"){
        RooUnfoldSvd unfold_N (&response_N, NPyRec, myNumber);   // OR
        NReco = (TH1D *) unfold_N.Hreco ();
	//double chisq=unfold_N.Chi2(NPyGen, 0);
      }

      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.3, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      title2="# jet + Z. "+title;
      NReco->SetTitle (title2.c_str());
      NReco->GetXaxis ()->SetTitle ("");
      NReco->GetYaxis ()->SetTitle ("Entries");
      NReco->SetMarkerStyle (20);
      NReco->SetMarkerStyle (20);
      NReco->SetLineColor (kRed);
      NReco->SetLineWidth (2);
      NReco->SetStats (0);
      NReco->Draw ("P");           //risultato dell'unfolding
      NPyGen->SetLineColor(kGreen+1);
      NPyGen->Draw("SAME");
      NPyRec->Draw("SAME");

      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (NReco, "MC Pythia Unfolded", "LP20");
      legend_d->AddEntry (NPyRec, "MC Pythia Recorded", "L");
      legend_d->AddEntry(NPyGen,"MC Pythia Gen","L");
      legend_d->Draw ("same");

      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.3);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      TH1F *CloneH=(TH1F*) NReco->Clone();
      CloneH->SetTitle("CloneH");
      CloneH->SetStats(1);
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(111);
      CloneH->GetXaxis ()->SetLabelSize (0.1);
      CloneH->GetYaxis ()->SetLabelSize (0.08);
      CloneH->Divide (NPyGen);
      CloneH->SetMarkerStyle (6);
      CloneH->GetXaxis ()->SetLabelSize (0.06);
      CloneH->GetYaxis ()->SetLabelSize (0.06);
      CloneH->GetXaxis ()->SetTitleSize (0);
      CloneH->GetYaxis ()->SetTitleSize (0.06);
      CloneH->GetYaxis ()->SetTitleOffset (0.5);
      CloneH->GetYaxis ()->SetRangeUser (0.5, 1.3);
      CloneH->GetXaxis ()->SetRangeUser (0, 5);
      CloneH->GetYaxis ()->SetRangeUser (0.5, 1.3);
      CloneH->GetXaxis ()->SetRangeUser (0, 5);
      CloneH->GetYaxis ()->SetTitle ("Data Unfolded/MC truth (Pythia 6 Using MG)");
      CloneH->SetMarkerStyle (20);
      CloneH->SetLineWidth (1);
      CloneH->SetTitle ("");
      double max=CloneH->GetMaximum();
      double min=CloneH->GetMinimum();
      CloneH->GetYaxis()->SetRangeUser(min,max);
      CloneH->Draw ("ep");
      TF1 *jj = new TF1 ("jj", "1", -100, 100);
      TF1 *fj = new TF1 ("fj", "[0]", 0, 5);
      fj->SetLineWidth(.5);
      fj->SetLineColor(kWhite);
      CloneH->Fit(fj);
      jj->SetLineColor (kBlue + 1);
      jj->SetLineWidth (1);
      jj->SetLineStyle (2);
      jj->Draw ("same");
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/PythiaZ2Check/jetMultiplicityWithOtherMC_"+method+"_"+num.str()+".pdf";
      c->cd ();
      c->Print(title3.c_str());
      num.str("");
    }
  }
}

void
UnfoldingIdentityCheck::LoopJetMultiplicityAandB()
{
  response_N.UseOverflow();

  cout<<"*********************************"<<endl;
  cout<<"This Macro will perform a test   "<<endl;
  cout<<"The unfolding matrix will be applied"<<endl;
  cout<<"On the MC reco instead of data"<<endl;
  cout<<"Must be exactly alike"<<endl;
  cout<<"*********************************"<<endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;             /* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  cout<<"Number of entries "<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;


  //COnsider the events outside range...
  response_pT.UseOverflow();

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
        break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      if (Jet_multiplicity > 20 || Jet_multiplicity_gen > 20 )
        continue;
      
      if (jentry<(nentries/5.0)) response_N.Fill (Jet_multiplicity, Jet_multiplicity_gen);
      NPyGen->Fill (Jet_multiplicity_gen);
      NPyRec->Fill (Jet_multiplicity);
    }

  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=2; k<6; k++){
      int myNumber=k;
      stringstream num;
      num<<myNumber;
      string title=method+" method with K="+num.str()+" Matrix estimated (MGraph) from 5 1/fb and applied to 25 1/fb";
      std::string title2="Jet multiplicity. "+title;
      cout<<title<<endl;
 
      if (method=="Bayesian") {
        RooUnfoldBayes unfold_N (&response_N, NPyRec, myNumber);
        NReco = (TH1D *) unfold_N.Hreco ();
      }
      if (method=="Svd"){
        RooUnfoldSvd unfold_N (&response_N, NPyRec, myNumber);   // OR
        NReco = (TH1D *) unfold_N.Hreco ();
	//double chisq=unfold_N.Chi2(NPyGen, 0);
      }
        
      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.3, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      title2="# jet + Z. "+title;
      NReco->SetTitle (title2.c_str());
      NReco->GetXaxis ()->SetTitle ("");
      NReco->GetYaxis ()->SetTitle ("Entries");
      NReco->SetMarkerStyle (20);
      NReco->SetMarkerStyle (20);
      NReco->SetLineColor (kRed);
      NReco->SetLineWidth (2);
      NReco->SetStats (0);
      NReco->Draw ("P");           //risultato dell'unfolding
      NPyGen->SetLineColor(kGreen+1);
      NPyGen->Draw("SAME");
      NPyRec->Draw("SAME");

      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (NReco, "MC Pythia Unfolded", "LP20");
      legend_d->AddEntry (NPyRec, "MC Pythia Recorded", "L");
      legend_d->AddEntry(NPyGen,"MC Pythia Gen","L");
      legend_d->Draw ("same");

      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.3);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      TH1F *CloneH=(TH1F*) NReco->Clone();
      CloneH->SetTitle("CloneH");
      CloneH->SetStats(1);
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(111);
      CloneH->GetXaxis ()->SetLabelSize (0.1);
      CloneH->GetYaxis ()->SetLabelSize (0.08);
      CloneH->Divide (NPyGen);
      CloneH->SetMarkerStyle (6);
      CloneH->GetXaxis ()->SetLabelSize (0.06);
      CloneH->GetYaxis ()->SetLabelSize (0.06);
      CloneH->GetXaxis ()->SetTitleSize (0);
      CloneH->GetYaxis ()->SetTitleSize (0.06);
      CloneH->GetYaxis ()->SetTitleOffset (0.5);
      CloneH->GetYaxis ()->SetRangeUser (0.5, 1.3);
      CloneH->GetXaxis ()->SetRangeUser (0, 5);
      CloneH->GetYaxis ()->SetRangeUser (0.5, 1.3);
      CloneH->GetXaxis ()->SetRangeUser (0, 5);
      CloneH->GetYaxis ()->SetTitle ("Data Unfolded/MC truth (Pythia 6 Using MG)");
      CloneH->SetMarkerStyle (20);
      CloneH->SetLineWidth (1);
      CloneH->SetTitle ("");
      double max=CloneH->GetMaximum();
      double min=CloneH->GetMinimum();
      CloneH->GetYaxis()->SetRangeUser(min,max);
      CloneH->Draw ("ep");
      TF1 *jj = new TF1 ("jj", "1", -100, 100);
      TF1 *fj = new TF1 ("fj", "[0]", 0, 5);
      fj->SetLineWidth(.5);
      fj->SetLineColor(kWhite);
      CloneH->Fit(fj);
      jj->SetLineColor (kBlue + 1);
      jj->SetLineWidth (1);
      jj->SetLineStyle (2);
      jj->Draw ("same");
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/SplitCheck/jetMultiplicitysplit_"+method+"_"+num.str()+".pdf";
      c->cd ();
      c->Print(title3.c_str());
      num.str("");
    }
  }
}

void
UnfoldingIdentityCheck::LoopJetMultiplicity ()
{
  response_N.UseOverflow();

  cout<<"*********************************"<<endl;
  cout<<"This Macro will perform a test   "<<endl;
  cout<<"The unfolding matrix will be applied"<<endl;
  cout<<"On the MC reco instead of data"<<endl;
  cout<<"Must be exactly alike"<<endl;
  cout<<"*********************************"<<endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;		/* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;


  //COnsider the events outside range...
  response_pT.UseOverflow();

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      if (Jet_multiplicity > 20 || Jet_multiplicity_gen > 20 )
	continue;
      
      response_N.Fill (Jet_multiplicity, Jet_multiplicity_gen);

      NTrue->Fill (Jet_multiplicity_gen);
      NMCreco->Fill (Jet_multiplicity);
      NMatx->Fill (Jet_multiplicity, Jet_multiplicity_gen);
    }


  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=2; k<6; k++){
      int myNumber=k;
      stringstream num;
      num<<myNumber;
      string title="MC reco unfolding (Closure test), using "+method+" method with K="+num.str();
      std::string title2="Z + N Jets distribution. "+title;
      cout<<title<<endl;

      if (method=="Bayesian") {
	RooUnfoldBayes unfold_N (&response_N, NMCreco, myNumber);
	NReco = (TH1D *) unfold_N.Hreco ();
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_N (&response_N, NMCreco, myNumber);	// OR
	NReco = (TH1D *) unfold_N.Hreco ();
      }
	
      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      title2="Number of jet + Z distribution. "+title;
      NReco->SetTitle (title2.c_str());
      NReco->GetXaxis ()->SetTitle ("");
      NReco->GetYaxis ()->SetTitle ("Entries");
      NReco->SetMarkerStyle (20);
      double area = ((NReco->Integral ()) / NTrue->Integral ());
      NReco->Scale (1.00000 / area);
      NData->Scale (1.00000 / area);
      NReco->Draw ();		//risultato dell'unfolding
      NReco->SetLineColor (kRed);
      NReco->SetLineWidth (2);
      NReco->SetStats(0);
      NMCreco->Draw ("SAME");
      NMCreco->SetLineColor (kBlue + 1);
      NMCreco->SetLineStyle (2);
      NTrue->SetLineColor (kBlack);
      NMCreco->SetLineWidth (2);
      NTrue->SetLineWidth (2);

      NTrue->Draw ("SAME");
      //NData2->SetLineColor(kGreen+1);
      //NData2->Draw("SAME");

      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.3, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      NReco->DrawCopy ();
      pad1->SetLogy (1);
      NTrue->Draw ("same");
      NMCreco->Draw ("same");
      //NData2->Draw("same");

      pad1->SetBottomMargin (0);
      NReco->SetTitleSize (0);

      NTrue->SetTitleSize (0);


      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (NReco, "Data Unfolded", "LP20");
      legend_d->AddEntry (NTrue, "MC truth", "L");
      legend_d->AddEntry (NMCreco, "MC reco", "L");
      legend_d->Draw ("same");

      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.3);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
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

      NReco->GetYaxis ()->SetRangeUser (0.5, 1.3);
      NReco->GetXaxis ()->SetRangeUser (0, 5);
      NReco->GetYaxis ()->SetTitle ("Data Unfolded/MC truth");
      NReco->SetMarkerStyle (20);
      NReco->SetLineWidth (1);
      NReco->SetTitle ("");
      double max=NReco->GetMaximum();
      double min=NReco->GetMinimum();
      NReco->GetYaxis()->SetRangeUser(min,max);
      NReco->SetStats(0);
      NReco->Draw ("ep");
      TF1 *jj = new TF1 ("jj", "1", 0, 100);
      jj->SetLineColor (kBlue + 1);
      jj->SetLineWidth (1);
      jj->SetLineStyle (2);
      jj->Draw ("same");
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/IdentityCheck/jetMultiplicityIdentityCheck_"+method+"_"+num.str()+".pdf";
      c->cd ();
      c->Print(title3.c_str());
      num.str("");
    }
  }
}

void
UnfoldingIdentityCheck::LoopZptWithOtherMC()
{
  response_pT.UseOverflow();

  cout<<"*********************************"<<endl;
  cout<<"This Macro will perform a test   "<<endl;
  cout<<"The unfolding matrix will be applied"<<endl;
  cout<<"On the MC reco instead of data"<<endl;
  cout<<"Must be exactly alike"<<endl;
  cout<<"*********************************"<<endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;             /* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;


  //COnsider the events outside range...
  response_pT.UseOverflow();

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
        break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      if (Z_pt > 500 || Z_pt_gen > 500)
	continue;

      response_pT.Fill (Z_pt, Z_pt_gen);
      
      PTrue->Fill (Z_pt_gen);
      PMCreco->Fill (Z_pt);
      PMatx->Fill (Z_pt, Z_pt_gen);

    }

  fB->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_pythia6Z2_2011A_v1_9.root:/validationJEC");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");
  fChain = tree_fB;             /* Loop RunB */
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

      if (Z_pt > 500 || Z_pt_gen > 500)
	continue;
      
      response_pT.Fill (Z_pt, Z_pt_gen);

      PPyGen->Fill (Z_pt_gen);
      PPyRec->Fill (Z_pt);
    }

  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=2; k<6; k++){
      int myNumber=1+k*4;
      stringstream num;
      num<<myNumber;
      string title=method+" method with K="+num.str()+" (from MGraph) applied on Pythia";
      std::string title2="Z Pt distribution. "+title;
      cout<<title<<endl;
 
      if (method=="Bayesian") {
        RooUnfoldBayes unfold_pT (&response_pT, PPyRec, myNumber);
        PReco = (TH1D *) unfold_pT.Hreco ();
      }
      if (method=="Svd"){
        RooUnfoldSvd unfold_pT (&response_pT, PPyRec, myNumber);   // OR
        PReco = (TH1D *) unfold_pT.Hreco ();
      }
        
      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.3, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      title2="# jet + Z distribution. "+title;
      PReco->SetTitle (title2.c_str());
      PReco->GetXaxis ()->SetTitle ("");
      PReco->GetYaxis ()->SetTitle ("Entries");
      PReco->SetMarkerStyle (20);
      PReco->SetMarkerStyle (20);
      PReco->SetLineColor (kRed);
      PReco->SetLineWidth (2);
      PReco->SetStats(0);
      PReco->Draw ("P");           //risultato dell'unfolding
      PPyGen->SetLineColor(kGreen+1);
      PPyGen->Draw("SAME");
      PPyRec->Draw("SAME");

      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (PReco, "MC Pythia Unfolded", "LP20");
      legend_d->AddEntry (PPyRec, "MC Pythia Recorded", "L");
      legend_d->AddEntry(PPyGen,"MC Pythia Gen","L");
      legend_d->Draw ("same");

      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.3);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      TH1F *CloneH=(TH1F*) PReco->Clone();
      CloneH->SetTitle("CloneH");
      CloneH->GetXaxis ()->SetLabelSize (0.1);
      CloneH->GetYaxis ()->SetLabelSize (0.08);
      CloneH->SetStats (0);
      CloneH->Divide (PPyGen);
      CloneH->SetMarkerStyle (6);
      CloneH->GetXaxis ()->SetLabelSize (0.06);
      CloneH->GetYaxis ()->SetLabelSize (0.06);
      CloneH->GetXaxis ()->SetTitleSize (0);
      CloneH->GetYaxis ()->SetTitleSize (0.06);
      CloneH->GetYaxis ()->SetTitleOffset (0.5);
      CloneH->GetYaxis ()->SetRangeUser (0.5, 1.3);
      CloneH->GetXaxis ()->SetRangeUser (0, 200);
      CloneH->GetYaxis ()->SetTitle ("Data Unfolded/MC truth (Pythia 6 Using MG)");
      CloneH->SetMarkerStyle (20);
      CloneH->SetLineWidth (1);
      CloneH->SetTitle ("");
      double max=CloneH->GetMaximum();
      double min=CloneH->GetMinimum();
      CloneH->GetYaxis()->SetRangeUser(min,max);
      CloneH->Draw ("ep");
      TF1 *jj = new TF1 ("jj", "1", -100, 200);
      jj->SetLineColor (kBlue + 1);
      jj->SetLineWidth (1);
      jj->SetLineStyle (2);
      jj->Draw ("same");
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/PythiaZ2Check/ZptWithOtherMC_"+method+"_"+num.str()+".pdf";
      c->cd ();
      c->Print(title3.c_str());
      num.str("");
    }
  }
}

void
UnfoldingIdentityCheck::LoopZpt ()
{
  response_pT.UseOverflow();
  cout<<"*********************************"<<endl;
  cout<<"This Macro will perform a test   "<<endl;
  cout<<"The unfolding matrix will be applied"<<endl;
  cout<<"On the MC reco instead of data"<<endl;
  cout<<"Must be exactly alike"<<endl;
  cout<<"*********************************"<<endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;		/* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;


  //COnsider the events outside range...
  response_pT.UseOverflow();

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      
      if (Z_pt > 500 || Z_pt_gen > 500)
	continue;

      response_pT.Fill (Z_pt, Z_pt_gen);

      PTrue->Fill (Z_pt_gen);
      PMCreco->Fill (Z_pt);
      PMatx->Fill (Z_pt, Z_pt_gen);

    }


  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=0; k<5; k++){
      int myNumber=1+k*4;
      stringstream num;
      num<<myNumber;
      string title="MC reco unfolding (Closure test), using "+method+" method with K="+num.str();
      std::string title2="Z pt distribution. "+title;
      cout<<title<<endl;
	
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_pT (&response_pT, PMCreco, myNumber);
	PReco = (TH1D *) unfold_pT.Hreco ();
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_pT (&response_pT, PMCreco, myNumber);
	PReco = (TH1D *) unfold_pT.Hreco ();
      }
	
      TCanvas *d = new TCanvas ("d", "d", 1000, 700);
      d->cd ();
      title2="Z pT distribution. "+title;
      PReco->SetTitle (title2.c_str());
      PReco->GetXaxis ()->SetTitle ("");
      PReco->GetYaxis ()->SetTitle ("Entries");
      PReco->SetMarkerStyle (20);
      double area2 = ((PReco->Integral ()) / PTrue->Integral ());
      PReco->Scale (1.00000 / area2);
      PData2->Scale (1.00000 / area2);
      PReco->SetStats(0);
      PReco->Draw ();		//risultato dell'unfolding
      PReco->SetLineColor (kRed);
      PReco->SetLineWidth (2);
      PMCreco->SetLineWidth (2);
      PData2->SetLineWidth (2);
      PMCreco->SetLineStyle (2);
      PMCreco->Draw ("SAME");
      PMCreco->SetLineColor (kBlue + 1);
      PTrue->SetLineColor (kBlack);
      PReco->SetMarkerStyle (20);
      PTrue->Draw ("SAME");
      TPad *pad12 = new TPad ("pad12", "pad12", 0, 0.3, 1, 1);
      pad12->Draw ();
      pad12->cd ();
      PReco->DrawCopy ();
      pad12->SetLogy (1);
      PTrue->Draw ("same");
      PMCreco->Draw ("same");
      //PData2->Draw("same");
	
      pad12->SetBottomMargin (0);
      PReco->SetTitleSize (0);
	
      PTrue->SetTitleSize (0);
	
	
      TLegend *legend_d2 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d2->SetFillColor (0);
      legend_d2->SetFillStyle (0);
      legend_d2->SetBorderSize (0);
      legend_d2->AddEntry (NReco, "MC Unfolded", "LP20");
      legend_d2->AddEntry (NTrue, "MC truth", "L");
      legend_d2->AddEntry (NMCreco, "MC reco", "L");
      //legend_d2->AddEntry(NData2, "Data Folded", "LE");
      legend_d2->Draw ("same");
	
      d->cd ();
	
      TPad *pad22 = new TPad ("pad22", "pad22", 0, 0, 1, 0.3);
      pad22->SetTopMargin (0);
      pad22->Draw ();
      pad22->cd ();
      PReco->GetXaxis ()->SetLabelSize (0.1);
      PReco->GetYaxis ()->SetLabelSize (0.08);
      PReco->SetStats (0);
      PReco->Divide (PTrue);
      PReco->SetMarkerStyle (6);
      PReco->GetXaxis ()->SetLabelSize (0.06);
      PReco->GetYaxis ()->SetLabelSize (0.06);
      PReco->GetXaxis ()->SetTitleSize (0);
      PReco->GetYaxis ()->SetTitleSize (0.06);
      PReco->GetYaxis ()->SetTitleOffset (0.5);
	
      PReco->GetYaxis ()->SetRangeUser (0.9, 1.1);
      PReco->GetXaxis ()->SetRangeUser (0, 200);
      PReco->GetYaxis ()->SetTitle ("MC Unfolded/MC truth");
      PReco->SetMarkerStyle (20);
      PReco->SetLineWidth (1);
      PReco->SetTitle ("");
      double max=PReco->GetMaximum();
      double min=PReco->GetMinimum();
      PReco->GetYaxis()->SetRangeUser(min,max);
      PReco->SetStats(0);
      PReco->Draw ("ep");
      TF1 *kk = new TF1 ("kk", "1", 0, 200);
      kk->SetLineColor (kBlue + 1);
      kk->SetLineWidth (1);
      kk->SetLineStyle (2);
      kk->Draw ("same");

      d->cd ();
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding//IdentityCheck/ZptIdentityCheck_"+method+"_"+num.str()+".pdf";
      d->Print(title3.c_str());
      num.str("");
    }
  }
}
void
UnfoldingIdentityCheck::LoopZy ()
{
  response_y.UseOverflow();
  cout<<"*********************************"<<endl;
  cout<<"This Macro will perform a test   "<<endl;
  cout<<"The unfolding matrix will be applied"<<endl;
  cout<<"On the MC reco instead of data"<<endl;
  cout<<"Must be exactly alike"<<endl;
  cout<<"*********************************"<<endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;		/* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;


  //COnsider the events outside range...
  response_pT.UseOverflow();

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      response_y.Fill (Z_y, Z_y_gen);

      yTrue->Fill (Z_y_gen);
      yMCreco->Fill (Z_y);
      yMatx->Fill (Z_y, Z_y_gen);
     
    }


  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=0; k<5; k++){
      int myNumber=1+k*5;
      stringstream num;
      num<<myNumber;
      string title="MC reco unfolding (Closure test), using "+method+" method with K="+num.str();
      std::string title2="Z rapidity distribution. "+title;
      cout<<title<<endl;
	
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_y (&response_y, yMCreco, myNumber);
	yReco = (TH1D *) unfold_y.Hreco ();
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_y (&response_y, yMCreco, myNumber);
	yReco = (TH1D *) unfold_y.Hreco ();
      }
	
      TCanvas *e = new TCanvas ("e", "e", 1000, 700);
      e->cd ();
      title2="Z rapidity distribution. "+title;
      yReco->SetTitle (title2.c_str());
      yReco->GetXaxis ()->SetTitle ("");
      yReco->GetYaxis ()->SetTitle ("Entries");
      yReco->SetMarkerStyle (20);
      double area3 = ((yReco->Integral ()) / yTrue->Integral ());
      yReco->Scale (1.00000 / area3);
      yData2->Scale (1.00000 / area3);
      yReco->SetStats(0);
      yReco->Draw ();		//risultato dell'unfolding
      yReco->SetLineColor (kRed);
      yReco->SetLineWidth (2);
      yMCreco->SetLineWidth (2);
      yData2->SetLineWidth (2);
      yMCreco->SetLineStyle (2);
      yMCreco->Draw ("SAME");
      yMCreco->SetLineColor (kBlue + 1);
      yTrue->SetLineColor (kBlack);
      yReco->SetMarkerStyle (20);
      yTrue->Draw ("SAME");
      //yData2->SetLineColor(kGreen+1);
      //yData2->SetMarkerStyle(20);
      //yData2->Draw("SAME");

      TPad *pad13 = new TPad ("pad13", "pad13", 0, 0.3, 1, 1);
      pad13->Draw ();
      pad13->cd ();
      yReco->DrawCopy ();
      pad13->SetLogy (1);
      yTrue->Draw ("same");
      yMCreco->Draw ("same");
      //yData2->Draw("same");

      pad13->SetBottomMargin (0);
      yReco->SetTitleSize (0);

      yTrue->SetTitleSize (0);


      TLegend *legend_d3 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d3->SetFillColor (0);
      legend_d3->SetFillStyle (0);
      legend_d3->SetBorderSize (0);
      legend_d3->AddEntry (NReco, "MC Unfolded", "LP20");
      legend_d3->AddEntry (NTrue, "MC truth", "L");
      legend_d3->AddEntry (NMCreco, "MC reco", "L");
      //legend_d3->AddEntry(NData2, "Data Folded", "LE");
      legend_d3->Draw ("same");

      e->cd ();

      TPad *pad14 = new TPad ("pad14", "pad14", 0, 0, 1, 0.3);
      pad14->SetTopMargin (0);
      pad14->Draw ();
      pad14->cd ();
      yReco->GetXaxis ()->SetLabelSize (0.1);
      yReco->GetYaxis ()->SetLabelSize (0.08);
      yReco->SetStats (0);
      yReco->Divide (yTrue);
      yReco->SetMarkerStyle (6);
      yReco->GetXaxis ()->SetLabelSize (0.06);
      yReco->GetYaxis ()->SetLabelSize (0.06);
      yReco->GetXaxis ()->SetTitleSize (0);
      yReco->GetYaxis ()->SetTitleSize (0.06);
      yReco->GetYaxis ()->SetTitleOffset (0.5);

      yReco->GetYaxis ()->SetRangeUser (0.9, 1.1);
      yReco->GetXaxis ()->SetRangeUser (-2.5, 2.5);
      yReco->GetYaxis ()->SetTitle ("MC Unfolded/MC truth");
      yReco->SetMarkerStyle (20);
      yReco->SetLineWidth (1);
      yReco->SetTitle ("");
      double max=yReco->GetMaximum();
      double min=yReco->GetMinimum();
      yReco->GetYaxis()->SetRangeUser(min,max);
      yReco->SetStats(0);
      yReco->Draw ("ep");
      TF1 *l = new TF1 ("f1", "1", -100, 100);
      l->SetLineColor (kBlue + 1);
      l->SetLineWidth (1);
      l->SetLineStyle (2);
      l->Draw ("same");

      e->cd ();
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/IdentityCheck/ZyIdentityCheck_"+method+"_"+num.str()+".pdf";
      e->Print(title3.c_str());
      num.str("");
    }
  }
}

void
UnfoldingIdentityCheck::LoopZyWithOtherMC()
{
  response_y.UseOverflow();

  cout<<"*********************************"<<endl;
  cout<<"This Macro will perform a test   "<<endl;
  cout<<"The unfolding matrix will be applied"<<endl;
  cout<<"On the MC reco instead of data"<<endl;
  cout<<"Must be exactly alike"<<endl;
  cout<<"*********************************"<<endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;             /* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;


  //COnsider the events outside range...

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
        break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      response_y.Fill (Z_y, Z_y_gen);
      
      yTrue->Fill (Z_y_gen);
      yMCreco->Fill (Z_y);
      yMatx->Fill (Z_y, Z_y_gen);

    }

  fB->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_pythia6Z2_2011A_v1_9.root:/validationJEC");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");
  fChain = tree_fB;             /* Loop RunB */
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


      response_y.Fill (Z_y, Z_y_gen);
      
      yTrue->Fill (Z_y_gen);
      yMCreco->Fill (Z_y);
      yMatx->Fill (Z_y, Z_y_gen);
      
      response_y.Fill (Z_y, Z_y_gen);

      yPyGen->Fill (Z_y_gen);
      yPyRec->Fill (Z_y);
    }

  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=2; k<6; k++){
      int myNumber=1+k*5;
      stringstream num;
      num<<myNumber;
      string title=method+" method with K="+num.str()+" (from MGraph) applied on Pythia";
      std::string title2="Z Pt distribution. "+title;
      cout<<title<<endl;
 
      if (method=="Bayesian") {
        RooUnfoldBayes unfold_y (&response_y, yPyRec, myNumber);
        yReco = (TH1D *) unfold_y.Hreco ();
      }
      if (method=="Svd"){
        RooUnfoldSvd unfold_y (&response_y, yPyRec, myNumber);   // OR
        yReco = (TH1D *) unfold_y.Hreco ();
      }
        
      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.3, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      title2="# jet + Z distribution. "+title;
      yReco->SetTitle (title2.c_str());
      yReco->GetXaxis ()->SetTitle ("");
      yReco->GetYaxis ()->SetTitle ("Entries");
      yReco->SetMarkerStyle (20);
      yReco->SetMarkerStyle (20);
      yReco->SetLineColor (kRed);
      yReco->SetLineWidth (2);
      yReco->SetStats(0);
      yReco->Draw ("P");           //risultato dell'unfolding
      yPyGen->SetLineColor(kGreen+1);
      yPyGen->Draw("SAME");
      yPyRec->Draw("SAME");

      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (yReco, "MC Pythia Unfolded", "LP20");
      legend_d->AddEntry (yPyRec, "MC Pythia Recorded", "L");
      legend_d->AddEntry(yPyGen,"MC Pythia Gen","L");
      legend_d->Draw ("same");

      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.3);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      TH1F *CloneH=(TH1F*) yReco->Clone();
      CloneH->SetTitle("CloneH");
      CloneH->GetXaxis ()->SetLabelSize (0.1);
      CloneH->GetYaxis ()->SetLabelSize (0.08);
      CloneH->SetStats (0);
      CloneH->Divide (yPyGen);
      CloneH->SetMarkerStyle (6);
      CloneH->GetXaxis ()->SetLabelSize (0.06);
      CloneH->GetYaxis ()->SetLabelSize (0.06);
      CloneH->GetXaxis ()->SetTitleSize (0);
      CloneH->GetYaxis ()->SetTitleSize (0.06);
      CloneH->GetYaxis ()->SetTitleOffset (0.5);
      CloneH->GetYaxis ()->SetRangeUser (0.5, 1.3);
      CloneH->GetXaxis ()->SetRangeUser (-2.5, 2.5);
      CloneH->GetYaxis ()->SetTitle ("Data Unfolded/MC truth (Pythia 6 Using MG)");
      CloneH->SetMarkerStyle (20);
      CloneH->SetLineWidth (1);
      CloneH->SetTitle ("");
      double max=CloneH->GetMaximum();
      double min=CloneH->GetMinimum();
      CloneH->GetYaxis()->SetRangeUser(min,max);
      CloneH->Draw ("ep");
      TF1 *jj = new TF1 ("jj", "1", -100, 200);
      jj->SetLineColor (kBlue + 1);
      jj->SetLineWidth (1);
      jj->SetLineStyle (2);
      jj->Draw ("same");
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/PythiaZ2Check/ZyWithOtherMC_"+method+"_"+num.str()+".pdf";
      c->cd ();
      c->Print(title3.c_str());
      num.str("");
    }
  }
}

#ifndef __CINT__

int
main ()
{
  UnfoldingIdentityCheck ();
  return 0;
}				// Main program when run stand-alone

double UnfoldingIdentityCheck::numEventsPerStep(string filename, string dir){
  double entries=-999;
  TFile *tmp = TFile::Open(filename.c_str()); //MC file
  tmp->cd(dir.c_str());
  TObject * obj;
  gDirectory->GetObject("numEventsPerStep",obj);
  if(obj) entries = ((TH1F*)obj)->GetBinContent(1);
  tmp->Close();
  return entries;
}


#endif
