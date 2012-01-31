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

using
std::cout;
using
std::endl;
#endif

// Set Parameters

/* Number of jet associated to a Z distribution */
TH1D *NTrue = new TH1D ("N true", "N Truth", 5, 0, 5);
TH1D *NData = new TH1D ("N data", "N DATA Measured", 5, 0, 5);
TH2D *NMatx = new TH2D ("N hMatx", "Unfolding Matrix in # of jets + Z", 5, 0, 5, 5, 0, 5);
TH1D *NMCreco = new TH1D ("N mcreco", "N mcreco", 5, 0, 5);
TH1D *NData2 = new TH1D ("N data2", "N DATA Measured2", 5, 0, 5);

/* Z boson pT distribution */
TH1D *PTrue = new TH1D ("pT true", "pT Truth", 20, 0, 200);
TH1D *PData = new TH1D ("pT data", "pT DATA Measured", 20, 0, 200);
TH2D *PMatx = new TH2D ("pT hMatx", "Unfolding Matrix Z pT ", 20, 0, 100, 20, 0, 200);
TH1D *PMCreco = new TH1D ("pT mcreco", "pT mcreco", 20, 0, 200);
TH1D *PData2 = new TH1D ("pT data2", "pT DATA Measured2", 20, 0, 200);

/* Z boson rapidity distribution */
TH1D *yTrue = new TH1D ("y true", "y Truth", 25, -2.5, 2.5);
TH1D *yData = new TH1D ("y data", "y DATA Measured", 25, -2.5, 2.5);
TH2D *yMatx = new TH2D ("y hMatx", "Unfolding Matrix y Rapidity ", 25, -2.5, 2.5, 25, -2.5, 2.5);
TH1D *yMCreco = new TH1D ("y mcreco", "y mcreco", 25, -2.5, 2.5);
TH1D *yData2 = new TH1D ("y data2", "y DATA Measured2", 25, -2.5, 2.5);

TH1D *NReco;
TH1D *PReco;
TH1D *yReco;

//Set the Matrixes size!

RooUnfoldResponse response_N (5, 0, 5); 
RooUnfoldResponse response_pT (20, 0, 200);
RooUnfoldResponse response_y (25, -2.5, 2.5);

//FIles...

TFile *fA = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root");
TFile *fB = new TFile ("provaVieri_v1_9.root");


void
Unfolding::Loop()
{
  LoopJetMultiplicity();
  LoopZpt();
  LoopZy();
}

void
Unfolding::LoopJetMultiplicity ()
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
  //MC
  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  //DATA
  fB->cd ("provaVieri_v1_9.root:/validationJEC");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");

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
      
      if (Jet_multiplicity > 20 || Jet_multiplicity_gen > 20 )
	continue;
      
      response_N.Fill (Jet_multiplicity, Jet_multiplicity_gen);

      NTrue->Fill (Jet_multiplicity_gen);
      NMCreco->Fill (Jet_multiplicity);
      NMatx->Fill (Jet_multiplicity, Jet_multiplicity_gen);
    }

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
      if (Jet_multiplicity > 20)
	continue;
      
      NData->Fill (Jet_multiplicity);
      NData2->Fill (Jet_multiplicity);
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
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Z + N Jets distribution. "+title;
      cout<<title<<endl;
 
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_N (&response_N, NData, myNumber);
	NReco = (TH1D *) unfold_N.Hreco ();
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_N (&response_N, NData, myNumber);	// OR
	NReco = (TH1D *) unfold_N.Hreco ();
      }
	
      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.3, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      title2="Number of jet + Z distribution. "+title;
      NReco->SetTitle (title2.c_str());
      NReco->GetXaxis ()->SetTitle ("");
      NReco->GetYaxis ()->SetTitle ("Entries");
      NReco->SetMarkerStyle (20);
      NData->SetMarkerStyle (21);
      NData->SetLineColor(kGreen);
      //if (k==2){
      double area = (((double)NReco->Integral ()) / (double)NTrue->Integral ());
      cout<<"area "<<area<<endl;
      NReco->Scale (1.00000 / area);
      NData->Scale (1.00000 / area);
      //}
      NReco->SetMarkerStyle (20);
      NReco->SetStats(0);
      NReco->GetXaxis()->SetTitle("# of Jets");
      NReco->Draw ();		//risultato dell'unfolding
      NReco->SetLineColor (kRed);
      NReco->SetLineWidth (2);
      NMCreco->Draw ();
      NMCreco->SetLineColor (kBlue + 1);
      NMCreco->SetLineStyle (2);
      NTrue->SetLineColor (kBlack);
      NMCreco->SetLineWidth (2);
      NTrue->SetLineWidth (2);

      NTrue->Draw ("SAME");
      NData2->SetLineColor(kGreen+1);
      NData2->Draw("SAME");

      NReco->DrawCopy ();
      pad1->SetLogy (1);
      NTrue->Draw ("same");
      NMCreco->Draw ("same");
      NData->SetLineStyle(2);
      NData->Draw("same");

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
      legend_d->AddEntry(NData,"Data Folded","L");
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
      NReco->GetXaxis()->SetTitle("# of Jets");
      NReco->SetMarkerStyle (20);
      NReco->SetLineWidth (1);
      NReco->SetTitle ("");
      double max=NReco->GetMaximum();
      double min=NReco->GetMinimum();
      NReco->GetYaxis()->SetRangeUser(min,max);
      NReco->SetStats(1);
      NReco->Draw ("ep");
      TF1 *l = new TF1 ("l", "1",  0, 10);
      l->SetLineColor (kBlue + 1);
      l->SetLineWidth (1);
      l->SetLineStyle (2);
      l->Draw ("same");
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(111);
      TF1 *jj = new TF1 ("jj", "[0]", 0, 5);
      jj->SetParameter(0, 1);
      jj->SetLineWidth(.5);
      jj->SetLineColor(kWhite);
      NReco->Fit(jj);
      jj->Draw ("same");
      l->Draw ("same");
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/Data/jetMultiplicity_"+method+"_"+num.str()+".pdf";
      c->cd ();
      c->Print(title3.c_str());
      num.str("");
    }
  }
  TCanvas *N =new TCanvas ("N jet response matrix", "N jet response matrix", 1000, 700);
  N->cd ();
  NMatx->SetStats (0);
  NMatx->GetXaxis()->SetTitle("Reconstructed # of Jets");
  NMatx->GetYaxis()->SetTitle("Generated # of Jets");
  gStyle->SetPalette (1);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  NMatx->SetMarkerColor (kBlack);
  double entries=1.000/(double)NMatx->GetEntries();
  NMatx->Scale(entries);
  NMatx->Draw ("COLZ,text");
  N->Print("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/Data/MatrixjetMultiplicity.pdf");
}

void
Unfolding::LoopZpt ()
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
  //DATA
  fB->cd ("provaVieri_v1_9.root:/validationJEC");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");
  
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
      PData->Fill (Z_pt);
      PData2->Fill (Z_pt);
      
    }
  
  
  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=0; k<5; k++){
      int myNumber=2+k*4;
      stringstream num;
      num<<myNumber;
      string title="Data Unfolding, using "+method+" method with K="+num.str();
      std::string title2="Z pt distribution. "+title;
      cout<<title<<endl;
      
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_pT (&response_pT, PData, myNumber);
	PReco = (TH1D *) unfold_pT.Hreco ();
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_pT (&response_pT, PData, myNumber);
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
      PData->Scale (1.00000 / area2);
      PReco->Draw ();		//risultato dell'unfolding
      PReco->SetLineColor (kRed);
      PReco->SetLineWidth (2);
      PMCreco->SetLineWidth (2);
      PData->SetLineWidth (1);
      PData->SetLineColor(kGreen);
      PData->SetLineStyle(2);
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
      PData->Draw("same");
      
      pad12->SetBottomMargin (0);
      PReco->SetTitleSize (0);
      
      PTrue->SetTitleSize (0);
      
      TLegend *legend_d2 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d2->SetFillColor (0);
      legend_d2->SetFillStyle (0);
      legend_d2->SetBorderSize (0);
      legend_d2->AddEntry (PReco, "Data Unfolded", "LP20");
      legend_d2->AddEntry (PTrue, "MC truth", "L");
      legend_d2->AddEntry (PMCreco, "MC reco", "L");
      legend_d2->AddEntry(PData, "Data Folded", "L");
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
      PReco->GetYaxis ()->SetTitle ("Data Unfolded/MC truth");
      PReco->SetMarkerStyle (20);
      PReco->SetLineWidth (1);
      PReco->SetTitle ("");
      double max=PReco->GetMaximum();
      double min=PReco->GetMinimum();
      PReco->GetYaxis()->SetRangeUser(min,max);
      PReco->SetStats(1);
      PReco->Draw ("ep");
      TF1 *l = new TF1 ("l", "1",  0, 200);
      l->SetLineColor (kBlue + 1);
      l->SetLineWidth (1);
      l->SetLineStyle (2);
      l->Draw ("same");
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(111);
      TF1 *jj = new TF1 ("jj", "[0]", 0, 200);
      jj->SetParameter(0, 1);
      jj->SetLineWidth(.5);
      jj->SetLineColor(kWhite);
      PReco->Fit(jj);
      jj->Draw ("same");
      l->Draw ("same");
      d->cd ();
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/Data/Zpt_"+method+"_"+num.str()+".pdf";
      d->Print(title3.c_str());
      num.str("");
    }
  }
  TCanvas *P = new TCanvas ("Pt response matrix", "Pt response", 1000, 700);
  P->cd ();
  
  gStyle->SetPalette (1.);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  double entries=1.000/(double)PMatx->GetEntries();
  PMatx->Scale(entries);
  PMatx->SetMarkerColor (kBlack);
  gPad->SetLogz(1);
  PMatx->Draw ("COLZ,text");
  string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/Data/MatrixZpt.pdf";
  P->Print(title3.c_str());
}

void
Unfolding::LoopZy ()
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
  fB->cd ("provaVieri_v1_9.root:/validationJEC");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");
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
      
      yData->Fill (Z_y);
      yData2->Fill (Z_y);
    }
  
  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=0; k<5; k++){
      int myNumber=2+k*5;
      stringstream num;
      num<<myNumber;
      string title="Data Unfolding, using "+method+" method with K="+num.str();
      std::string title2="Z rapidity distribution. "+title;
      cout<<title<<endl;
      
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_y (&response_y, yData, myNumber);
	yReco = (TH1D *) unfold_y.Hreco ();
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_y (&response_y, yData, myNumber);
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
      yData->Scale (1.00000 / area3);
      yReco->Draw ();		//risultato dell'unfolding
      yReco->SetLineColor (kRed);
      yReco->SetLineWidth (2);
      yMCreco->SetLineWidth (2);
      yData->SetLineWidth (2);
      yMCreco->SetLineStyle (2);
      yMCreco->Draw ("SAME");
      yMCreco->SetLineColor (kBlue + 1);
      yTrue->SetLineColor (kBlack);
      yReco->SetMarkerStyle (20);
      yTrue->Draw ("SAME");
      yData->SetLineColor(kGreen+1);
      yData->SetLineWidth(.5);
      yData->SetLineStyle(2);
      yData->SetMarkerStyle(20);
      yData->Draw("SAME");
      
      TPad *pad13 = new TPad ("pad13", "pad13", 0, 0.3, 1, 1);
      pad13->Draw ();
      pad13->cd ();
      yReco->DrawCopy ();
      pad13->SetLogy (1);
      yTrue->Draw ("same");
      yMCreco->Draw ("same");
      yData->Draw("same");
      
      pad13->SetBottomMargin (0);
      yReco->SetTitleSize (0);
      
      yTrue->SetTitleSize (0);
      
      
      TLegend *legend_d3 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d3->SetFillColor (0);
      legend_d3->SetFillStyle (0);
      legend_d3->SetBorderSize (0);
      legend_d3->AddEntry (yReco, "MC Unfolded", "LP20");
      legend_d3->AddEntry (yTrue, "MC truth", "L");
      legend_d3->AddEntry (yMCreco, "MC reco", "L");
      legend_d3->AddEntry(yData, "Data Folded", "L");
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
      yReco->SetStats(1);
      yReco->Draw ("ep");
      TF1 *l = new TF1 ("l", "1", -200, 200);
      l->SetLineColor (kBlue + 1);
      l->SetLineWidth (1);
      l->SetLineStyle (2);
      l->Draw ("same");
      TF1 *jj = new TF1 ("jj", "[0]", -200, 200);
      jj->SetParameter(0, 1);
      jj->SetLineWidth(.5);
      jj->SetLineColor(kWhite);
      yReco->Fit(jj);
      jj->Draw ("same");
      l->Draw ("same");
      
      e->cd ();
      string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/Data/Zy_"+method+"_"+num.str()+".pdf";
      e->Print(title3.c_str());
      num.str("");
    }
  }
  TCanvas *Y =    new TCanvas ("rapidity response matrix", "rapidity response", 1000, 700);
  Y->cd ();
  
  gStyle->SetPalette (1.);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  double entries=1.000/(double)yMatx->GetEntries();
  yMatx->Scale(entries);
  yMatx->SetMarkerColor (kBlack);
  gPad->SetLogz(1);
  yMatx->Draw ("COLZ,text");
  string title3="/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/Data/MatrixZy.pdf";
  Y->Print(title3.c_str());
}

#ifndef __CINT__

	int
	  main ()
	{
	  Unfolding ();
	  return 0;
	}				// Main program when run stand-alone
#endif
