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

void
Unfolding::Loop ()
{

  /* Number of jet associated to a Z distribution */
  TH1D *NTrue = new TH1D ("N true", "N Truth", 5, 0, 5);
  TH1D *NData = new TH1D ("N data", "N DATA Measured", 5, 0, 5);
  TH2D *NMatx = new TH2D ("N hMatx", "N hMatx", 5, 0, 5, 5, 0, 5);
  TH1D *NMCreco = new TH1D ("N mcreco", "N mcreco", 5, 0, 5);
  TH1D *NData2 = new TH1D ("N data2", "N DATA Measured2", 5, 0, 5);

  /* Z boson pT distribution */
  TH1D *PTrue = new TH1D ("pT true", "pT Truth", 10, 0, 100);
  TH1D *PData = new TH1D ("pT data", "pT DATA Measured", 10, 0, 100);
  TH2D *PMatx = new TH2D ("pT hMatx", "pT hMatx", 10, 0, 100, 10, 0, 100);
  TH1D *PMCreco = new TH1D ("pT mcreco", "pT mcreco", 10, 0, 100);
  TH1D *PData2 = new TH1D ("pT data2", "pT DATA Measured2", 10, 0, 100);

  /* Z boson rapidity distribution */
  TH1D *yTrue = new TH1D ("y true", "y Truth", 25, -2.5, 2.5);
  TH1D *yData = new TH1D ("y data", "y DATA Measured", 25, -2.5, 2.5);
  TH2D *yMatx = new TH2D ("y hMatx", "y hMatx", 25, -2.5, 2.5, 25, -2.5, 2.5);
  TH1D *yMCreco = new TH1D ("y mcreco", "y mcreco", 25, -2.5, 2.5);
  TH1D *yData2 = new TH1D ("y data2", "y DATA Measured2", 25, -2.5, 2.5);

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  //if (fChain == 0) return;

  TFile *fA = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root");
  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_9.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");

  TFile *fB = new TFile ("provaVieri_v1_9.root");

  fB->cd ("provaVieri_v1_9.root:/validationJEC");

  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");
  /*costruisco la matrice di unfolding */

  fChain = tree_fA;		/* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;

  RooUnfoldResponse response_N (5, 0, 5); 
  RooUnfoldResponse response_pT (10, 0, 100);
  RooUnfoldResponse response_y (25, -2.5, 2.5);

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {

      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;


      /*event by event response matrix filling for Njet, ZpT, Zy */

      if (Jet_multiplicity > 6 || Jet_multiplicity_gen > 6)
	continue;

      response_N.Fill (Jet_multiplicity, Jet_multiplicity_gen);

      NTrue->Fill (Jet_multiplicity_gen);
      NMCreco->Fill (Jet_multiplicity);
      NMatx->Fill (Jet_multiplicity, Jet_multiplicity_gen);


      if (Z_pt > 500 || Z_pt_gen > 500)
	continue;

      response_pT.Fill (Z_pt, Z_pt_gen);

      PTrue->Fill (Z_pt_gen);
      PMCreco->Fill (Z_pt);
      PMatx->Fill (Z_pt, Z_pt_gen);

      response_y.Fill (Z_y, Z_y_gen);

      yTrue->Fill (Z_y_gen);
      yMCreco->Fill (Z_y);
      yMatx->Fill (Z_y, Z_y_gen);

    }

  fChain = tree_fB;		/* Loop RunB */
  Init (fChain);	
  Long64_t nentries2 = fChain->GetEntriesFast ();
  Long64_t nbytes2 = 0, nb2 = 0;

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

      PData->Fill (Z_pt);
      PData2->Fill (Z_pt);

      yData->Fill (Z_y);
      yData2->Fill (Z_y);
    }

  /*choose your favourite unfolding method */
  TH1D *NReco;
  TH1D *PReco;
  TH1D *yReco;

  cout<<"#####################"<<endl;
  cout<<"    Enter few param "<<endl;
  cout<<"#####################"<<endl;
  cout<<endl;
  cout<<"Which method you wonna set to unfold???"<<endl;
  cout<<"Please choose among:"<<endl;
  cout<<"BbB-> Bin By Bin"<<endl;
  cout<<"Ba -> Bayesian"<<endl;
  cout<<"Svd-> Single Value"<<endl;
  string method="";
  getline(cin, method);
  cout<<endl;
  cout<<"Draw the matrixes as plots at the end? [y/N] "<<endl;
  string drawm="";
  getline(cin, drawm);
  
  ////////////
  //// Set Parameters
  ///////////

  int myNumber=3;

  if (method=="Ba") {
    RooUnfoldBayes unfold_N (&response_N, NData, myNumber);
    RooUnfoldBayes unfold_pT (&response_pT, PData, myNumber);
    RooUnfoldBayes unfold_y (&response_y, yData, myNumber);
    NReco = (TH1D *) unfold_N.Hreco ();
    PReco = (TH1D *) unfold_pT.Hreco ();
    yReco = (TH1D *) unfold_y.Hreco ();
  }
  if (method=="Svd"){
    RooUnfoldSvd unfold_N (&response_N, NData, 5);	// OR
    RooUnfoldSvd unfold_pT (&response_pT, PData, 10);
    RooUnfoldSvd unfold_y (&response_y, yData, 25);
    NReco = (TH1D *) unfold_N.Hreco ();
    PReco = (TH1D *) unfold_pT.Hreco ();
    yReco = (TH1D *) unfold_y.Hreco ();
  }
  if (method=="BbB"){
    //RooUnfoldBinByBin unfold_N (&response_N, NMeas);
    //RooUnfoldBinByBin unfold_pT (&response_pT, PMeas);
    //RooUnfoldBinByBin unfold_y (&response_pT, PMeas);
    cout<<"Bin By Bin method not already implemented..exit"<<endl;
    return;
  }
  if (method !="BbB" && method !="Svd" && method !="Ba"){
    cout<<"Not Valid Unfolding method chosen... exit"<<endl;
    cout<<"Please choose among:"<<endl;
    cout<<"BbB-> Bin By Bin"<<endl;
    cout<<"Ba -> Bayesian"<<endl;
    cout<<"Svd-> Single Value"<<endl;
    return;
  }

  //unfold.PrintTable (cout, NTrue); // print statistics of the unfolding i.e. chi2/dof

  TCanvas *c = new TCanvas ("c", "c", 1000, 700);
  c->cd ();

  NReco->SetTitle ("Number of jet + Z distribution");
  NReco->GetXaxis ()->SetTitle ("");
  NReco->GetYaxis ()->SetTitle ("Entries");
  NReco->SetMarkerStyle (20);
  double area = ((NReco->Integral ()) / NTrue->Integral ());
  NReco->Scale (1.00000 / area);
  NData2->Scale (1.00000 / area);
  NReco->Draw ();		//risultato dell'unfolding
  NReco->SetLineColor (kRed);
  NReco->SetLineWidth (2);
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
  NReco->Draw ("ep");
  TF1 *j = new TF1 ("j1", "1", 0, 100);
  j->SetLineColor (kBlue + 1);
  j->SetLineWidth (1);
  j->SetLineStyle (2);
  j->Draw ("same");

  c->cd ();
  c->Print("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/jetMultiplicity.png");

  TCanvas *d = new TCanvas ("d", "d", 1000, 700);
  d->cd ();

  PReco->SetTitle ("Z pT distribution");
  PReco->GetXaxis ()->SetTitle ("");
  PReco->GetYaxis ()->SetTitle ("Entries");
  PReco->SetMarkerStyle (20);
  double area2 = ((PReco->Integral ()) / PTrue->Integral ());
  PReco->Scale (1.00000 / area2);
  PData2->Scale (1.00000 / area2);
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
  //PData2->SetLineColor(kGreen+1);
  //PData2->SetMarkerStyle(20);
  //PData2->Draw("SAME");

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
  legend_d2->AddEntry (NReco, "Data Unfolded", "LP20");
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
  PReco->GetXaxis ()->SetRangeUser (0, 100);
  PReco->GetYaxis ()->SetTitle ("Data Unfolded/MC truth");
  PReco->SetMarkerStyle (20);
  PReco->SetLineWidth (1);
  PReco->SetTitle ("");
  PReco->Draw ("ep");
  TF1 *k = new TF1 ("k1", "1", 0, 100);
  k->SetLineColor (kBlue + 1);
  k->SetLineWidth (1);
  k->SetLineStyle (2);
  k->Draw ("same");

  d->cd ();
  d->Print("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/Zpt.png");

  TCanvas *e = new TCanvas ("e", "e", 1000, 700);
  e->cd ();

  yReco->SetTitle ("Z rapidity distribution");
  yReco->GetXaxis ()->SetTitle ("");
  yReco->GetYaxis ()->SetTitle ("Entries");
  yReco->SetMarkerStyle (20);
  double area3 = ((yReco->Integral ()) / yTrue->Integral ());
  yReco->Scale (1.00000 / area3);
  yData2->Scale (1.00000 / area3);
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
  legend_d3->AddEntry (NReco, "Data Unfolded", "LP20");
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
  yReco->GetYaxis ()->SetTitle ("Data Unfolded/MC truth");
  yReco->SetMarkerStyle (20);
  yReco->SetLineWidth (1);
  yReco->SetTitle ("");
  yReco->Draw ("ep");
  TF1 *l = new TF1 ("f1", "1", 0, 100);
  l->SetLineColor (kBlue + 1);
  l->SetLineWidth (1);
  l->SetLineStyle (2);
  l->Draw ("same");

  e->cd ();
  e->Print("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/Zy.png");

  if (drawm=="y" || drawm=="Y"){

	  /************ Unfolding Matrix *************************/

  TCanvas *N =
    new TCanvas ("N jet response matrix", "N jet response matrix", 1000, 700);
  N->cd ();

  gStyle->SetPalette (1);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  NMatx->SetMarkerColor (kBlack);
  double entries=1.000/(double)NMatx->GetEntries();
  NMatx->Scale(entries);
  NMatx->Draw ("COLZ,text");
  N->Print("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/jetMultiplicityMatrix.png");

  TCanvas *P = new TCanvas ("Pt response matrix", "Pt response", 1000, 700);
  P->cd ();

  gStyle->SetPalette (1.);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  entries=1.000/(double)PMatx->GetEntries();
  PMatx->Scale(entries);
  PMatx->SetMarkerColor (kBlack);
  PMatx->Draw ("COLZ,text");
  P->Print("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/ZptMatrix.png");

  TCanvas *Y =
    new TCanvas ("rapidity response matrix", "rapidity response", 1000, 700);
  Y->cd ();

  gStyle->SetPalette (1.);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  entries=1.000/(double)yMatx->GetEntries();
  yMatx->Scale(entries);
  yMatx->SetMarkerColor (kBlack);
  yMatx->Draw ("COLZ,text");
  Y->Print("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/ZyMatrix.png");

  }
}

#ifndef __CINT__

int
main ()
{
  Unfolding ();
  return 0;
}				// Main program when run stand-alone
#endif
