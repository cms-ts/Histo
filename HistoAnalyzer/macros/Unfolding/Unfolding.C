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

string s = "/home/candelis/html/Unfolding/DATA";

// Set Parameters

TFile* w = new TFile("Unfolded.root", "RECREATE");

int maxNJets=5;

//Double_t xbins[10] = {10, 10, 20, 20, 30, 30, 40, 40, 50, 100};
Double_t xbins[10] = {30, 40, 50, 70, 90, 120, 150, 190, 230, 330};

/* Number of jet associated to a Z distribution */
TH1D *NTrue = new TH1D ("N true", "N Truth", maxNJets, 0.5, maxNJets+0.5);
TH1D *NData = new TH1D ("N data", "N DATA Measured", maxNJets, 0.5, maxNJets+0.5);
TH2D *NMatx = new TH2D ("N hMatx", "Unfolding Matrix in # of jets + Z", maxNJets, 0.5, maxNJets+0.5, maxNJets, 0.5, maxNJets+0.5);
TH1D *NMCreco = new TH1D ("N mcreco", "N mcreco", maxNJets, 0.5, maxNJets+0.5);
TH1D *NMCrecoratio_ = new TH1D ("N mcrecoratio_", "N mcreco_", maxNJets, 0.5, maxNJets+0.5);
TH1D *NData2 = new TH1D ("N data2", "N DATA Measured2", maxNJets, 0.5, maxNJets+0.5);

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

/* Jet pT Differential Xsec distribution */

/*TH1D *jTrue = new TH1D ("jetpT true", "jetpT Truth", xbins, 30, 330);
TH1D *jData = new TH1D ("jetpT data", "jetpT DATA Measured", xbins, 30, 330);
TH2D *jMatx = new TH2D ("jetpT hMatx", "Unfolding Matrix jetpT Rapidity ", xbins, 30, 330, xbins, 30, 330);
TH1D *jMCreco = new TH1D ("jetpT mcreco", "jetpT mcreco", xbins, 30, 330);
TH1D *jData2 = new TH1D ("jetpT data2", "jetpT DATA Measured2", xbins, 30, 330);
TH1D *jRatio_ = new TH1D ("jetpTRatio", "jetpTRatio", xbins, 30, 330);
*/

TH1D *jTrue = new TH1D ("jetpT true", "jetpT Truth", 9, xbins);
TH1D *jData = new TH1D ("jetpT data", "jetpT DATA Measured", 9,  xbins);
TH2D *jMatx = new TH2D ("jetpT hMatx", "Unfolding Matrix jetpT Rapidity ", 9, xbins, 9, xbins);
TH1D *jMCreco = new TH1D ("jetpT mcreco", "jetpT mcreco", 9, xbins);
TH1D *jData2 = new TH1D ("jetpT data2", "jetpT DATA Measured2", 9, xbins);
TH1D *jRatio_ = new TH1D ("jetpTRatio", "jetpTRatio", 9, xbins);





TH1D *PRatio = new TH1D ("reco/en ratio", "reco/gen ratio", 100, 0, 1000);


TH1D *NReco;
TH1D *PReco;
TH1D *yReco;
TH1D *jReco;

TCanvas* C = new TCanvas("C","C",0,0,800,600);

//Set the Matrixes size!


RooUnfoldResponse response_pT (20, 0, 200);
RooUnfoldResponse response_y  (25, -2.5, 2.5);
//RooUnfoldResponse response_j  (30, 30, 330); 

//FIles...

TFile *fA = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_17.root");
TFile *fB = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_17.root");


void
Unfolding::Loop()
{
  LoopJetMultiplicity();
  LoopZpt();
  LoopZy();
  LoopJetPt();
}

void
Unfolding::LoopJetMultiplicity ()
{


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
  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_17.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  //DATA
  fB->cd ("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_17.root:/validationJEC");
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
      

      NTrue->Fill (Jet_multiplicity_gen);
      NMCreco->Fill (Jet_multiplicity);
      NMCrecoratio_->Fill(Jet_multiplicity);
      NMatx->Fill (Jet_multiplicity, Jet_multiplicity_gen);
    }//qui xorreggo per le eff e poi fillo response
     
      NTrue->Sumw2();
      NMCreco->Sumw2();
      NMCrecoratio_->Sumw2();

		

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
      NData->Sumw2();

      bool consider_efficiency = false;
      if(consider_efficiency) {

      TFile *eff = TFile::Open("/gpfs/cms/data/2011/TaP/efficiencies_2011_v2_17.root");
      TDirectory *dir=(TDirectory*)eff->cd("efficiency_vs_nJets");
      
      TH1F *h1 = (TH1F*)gDirectory->Get("MC_WP80_Tag");
      TH1F *h2 = (TH1F*)gDirectory->Get("MC_WP80_Probe");
      //TH1F *h3 = (TH1F*)gDirectory->Get("MC_RECO_Tag");
      TH1F *h4 = (TH1F*)gDirectory->Get("MC_RECO_Probe");

      TH1F *k1 = (TH1F*)gDirectory->Get("DATA_WP80_Tag");
      TH1F *k2 = (TH1F*)gDirectory->Get("DATA_WP80_Probe");
      //TH1F *k3 = (TH1F*)gDirectory->Get("DATA_RECO_Tag");
      TH1F *k4 = (TH1F*)gDirectory->Get("DATA_RECO_Probe");

      bool isEff = false;
      if(isEff){

      /* tag & probe efficiency study */

     C->Divide(2,2);
      
      C->cd(1);
      k1->SetMarkerColor(kBlack);
      k1->GetXaxis()->SetTitle("WP80 tag eff");
      k1->GetYaxis()->SetRangeUser(0.7, 0.9);
      k1->SetLineColor(kBlack);
      k1->SetMarkerColor(kBlack);
      k1->Draw("E1");
      h1  ->SetMarkerColor(kRed);
      h1  ->SetLineColor(kRed);
      h1  ->Draw("HIST SAMES");
      TLegend *legend_1 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_1->SetFillColor (0);
      legend_1->SetFillStyle (0);
      legend_1->SetBorderSize (0);
      legend_1->AddEntry (k1, "data", "LP20");
      legend_1->AddEntry (h1, "MC", "L");
      legend_1->Draw ("same");

      C->Update();
	cout << "1" << endl ;	

      C->cd(2);
      k2->SetMarkerColor(kBlack);
      k2->GetXaxis()->SetTitle("WP80 probe eff");
      k2->GetYaxis()->SetRangeUser(0.5, 0.75);
      k2->SetLineColor(kBlack);
      k2->SetMarkerColor(kBlack);
      k2->Draw("E1");
      h2  ->SetMarkerColor(kRed);
      h2  ->SetLineColor(kRed);
      h2  ->Draw("HIST SAMES");
      TLegend *legend_2 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_2->SetFillColor (0);
      legend_2->SetFillStyle (0);
      legend_2->SetBorderSize (0);
      legend_2->AddEntry (k2, "data", "LP20");
      legend_2->AddEntry (h2, "MC", "L");
      legend_2->Draw ("same");

      C->Update();
	cout << "1.2" << endl ;	
	
/*      C->cd(3);
      k3->SetMarkerColor(kBlack);
      k3->GetXaxis()->SetTitle("WP80 tag eff");
      k3->GetYaxis()->SetRangeUser(0.88, 1);
      k3->SetLineColor(kBlack);
      k3->SetMarkerColor(kBlack);
      k3->Draw("E1");
      h3  ->SetMarkerColor(kRed);
      h3  ->SetLineColor(kRed);
      h3  ->Draw("HIST SAMES");
      TLegend *legend_3 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_3->SetFillColor (0);
      legend_3->SetFillStyle (0);
      legend_3->SetBorderSize (0);
      legend_3->AddEntry (k3, "data", "LP20");
      legend_3->AddEntry (h3, "MC", "L");
      legend_3->Draw ("same");

      C->Update();
	cout << "2" << endl ;	

      C->cd(4);
      k4->SetMarkerColor(kBlack);
      k4->GetXaxis()->SetTitle("WP80 tag eff");
      k4->GetYaxis()->SetRangeUser(0.8, 1);
      k4->SetLineColor(kBlack);
      k4->SetMarkerColor(kBlack);
      k4->Draw("E1");
      h4  ->SetMarkerColor(kRed);
      h4  ->SetLineColor(kRed);
      h4  ->Draw("HIST SAMES");
      TLegend *legend_4 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_4->SetFillColor (0);
      legend_4->SetFillStyle (0);
      legend_4->SetBorderSize (0);
      legend_4->AddEntry (k4, "data", "LP20");
      legend_4->AddEntry (h4, "MC", "L");
      legend_4->Draw ("same");

      C->Update();
*/
      /*********************************************************/

      h1->Multiply(h2);
      //h1->Multiply(h3);
      h1->Multiply(h4);      
      NMCreco->Divide(h1);

      k1->Multiply(k2);
      //k1->Multiply(k3);
      k1->Multiply(k4);      
  

      NData->Divide(k1);
      }
	cout << "4" << endl ;	
      }
      RooUnfoldResponse response_N(NMCreco, NTrue, NMatx); 
      response_N.UseOverflow();
	cout << "5" << endl ;	
        

  	
 
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
	NReco->Sumw2();
      
	TH1F* NMCrecoratio = (TH1F*) NMCrecoratio_ -> Clone("NMCrecoratio");

	



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

      pad1->SetBottomMargin (0);
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
	
      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.3);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      NReco->GetXaxis ()->SetLabelSize (0.1);
      NReco->GetYaxis ()->SetLabelSize (0.08);
      NReco->SetStats (0);
      NReco->Divide (NData);
      NReco->SetMarkerStyle (6);
      NReco->GetXaxis ()->SetLabelSize (0.06);
      NReco->GetYaxis ()->SetLabelSize (0.06);
      NReco->GetXaxis ()->SetTitleSize (0);
      NReco->GetYaxis ()->SetTitleSize (0.06);
      NReco->GetYaxis ()->SetTitleOffset (0.5);

      NReco->GetYaxis ()->SetRangeUser (0.5, 1.3);
      NReco->GetXaxis ()->SetRangeUser (0, 7.5);
      NReco->GetYaxis ()->SetTitle ("Ratios");
      NReco->GetXaxis()->SetTitle("# of Jets");
      NReco->SetMarkerStyle (20);
      NReco->SetLineWidth (0);
      NReco->SetTitle ("");
      double max=NReco->GetMaximum();
      double min=NReco->GetMinimum();
      NReco->GetYaxis()->SetRangeUser(min,max);
      NReco->SetStats(1);
    
      NReco->Draw ("ep");

      NMCrecoratio->Divide(NTrue);		
      NMCrecoratio->SetMarkerStyle (20);
      NMCrecoratio->SetMarkerSize(0.0);
      NMCrecoratio->SetTitle ("");
      NMCrecoratio->SetStats(1);
      NMCrecoratio->SetLineStyle(3);
      NMCrecoratio->SetLineColor(kMagenta+3);
      NMCrecoratio->Draw ("HIST SAME");
      
      TLegend *legend_w = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_w->SetFillColor (0);
      legend_w->SetFillStyle (0);
      legend_w->SetBorderSize (0);
      legend_w->AddEntry (NReco, "Data Unfolded / MC truth", "LP20");
      legend_w->AddEntry (NMCrecoratio, "MC reco / MC truth", "L");
      legend_w->Draw ("same");
     
      pad2->Update();

      /*l->SetLineColor (kBlue + 1);
      l->SetLineWidth (1);
      l->SetLineStyle (2);
      l->Draw ("same");
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(111);
      jj->SetParameter(0, 1);
      jj->SetLineWidth(.5);
      jj->SetLineColor(kWhite);
      NReco->Fit(jj);
      jj->Draw ("same");
      l->Draw ("same");*/
      string title3= s+"JETMULTI"+method+"_"+num.str()+".pdf";
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
  //N->Print(s+"/MatrixjetMultiplicity.pdf");
 
}





void
Unfolding::LoopZpt ()
{
  cout<<"*********************************"<<endl;
  cout<<"This Macro will perform a test   "<<endl;
  cout<<"The unfolding matrix will be applied"<<endl;
  cout<<"On the MC reco instead of data"<<endl;
  cout<<"Must be exactly alike"<<endl;
  cout<<"*********************************"<<endl;
  
#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif
  
  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_17.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  //DATA
  fB->cd ("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_17.root:/validationJEC");
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
      
      
      if (Z_pt > 500 || Z_pt_gen > 500 || Z_pt <=0 || Z_pt_gen <=0)
	continue;
      
      response_pT.Fill (Z_pt, Z_pt_gen);
     
      double R = Z_pt/Z_pt_gen;

      PRatio_->Fill(Z_pt);
       
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
    for (int k=2; k<=20; k++){
      int myNumber=k;
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
      
      TCanvas *q = new TCanvas ("q", "q", 1000, 700);
      q->cd ();

      PRatio->Draw();

      TH1F* PRatio = (TH1F*) PRatio_ -> Clone("PRatio");


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
      PReco->Divide (PData);
      PReco->SetMarkerStyle (6);
      PReco->GetXaxis ()->SetLabelSize (0.06);
      PReco->GetYaxis ()->SetLabelSize (0.06);
      PReco->GetXaxis ()->SetTitleSize (0);
      PReco->GetYaxis ()->SetTitleSize (0.06);
      PReco->GetYaxis ()->SetTitleOffset (0.5);
      
      //PReco->GetYaxis ()->SetRangeUser (0, 1.1);
      PReco->GetXaxis ()->SetRangeUser (0, 200);
      PReco->GetYaxis ()->SetTitle ("Ratios");
      PReco->SetMarkerStyle (20);
      PReco->SetLineWidth (1);
      PReco->SetTitle ("");
      double max=PReco->GetMaximum();
      double min=PReco->GetMinimum();
      PReco->GetYaxis()->SetRangeUser(min,max+0.1);
      PReco->SetStats(1);
      PReco->Draw ("ep");
      
      
      PRatio->Divide(PTrue);		
      PRatio->SetMarkerStyle (20);
      PRatio->SetMarkerSize(0.0);
      PRatio->SetTitle ("");
      PRatio->SetStats(1);
      PRatio->SetLineStyle(3);
      PRatio->SetLineColor(kMagenta+3);
      PRatio->Draw ("HIST SAME");
      
      TLegend *legend_w2 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_w2->SetFillColor (0);
      legend_w2->SetFillStyle (0);
      legend_w2->SetBorderSize (0);
      legend_w2->AddEntry (PReco, "Data Unfolded / MC truth", "LP20");
      legend_w2->AddEntry (PRatio, "MC reco / MC truth", "L");
      legend_w2->Draw ("same");

      pad22->Update();

      /*m->SetLineColor (kBlue + 1);
      m->SetLineWidth (1);
      m->SetLineStyle (2);
      m->Draw ("same");
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(111);
      jj2->SetParameter(0, 1);
      jj2->SetLineWidth(.5);
      jj2->SetLineColor(kWhite);
      PReco->Fit(jj2);
      jj2->Draw ("same");
      m->Draw ("same");*/
      
      d->cd ();
      string title3= s+"ZPt"+method+"_"+num.str()+".pdf";
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
  string title3= s+"/MatrixZpt.pdf";
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
  
  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_17.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  fB->cd ("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_17.root:/validationJEC");
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
      yRatio_->Fill(Z_y); 
    }
  
  fChain = tree_fB;		 /*Loop RunB */
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
    for (int k=1; k<25; k++){
      int myNumber=k;
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
  
      TH1F* yRatio = (TH1F*) yRatio_ -> Clone("yRatio");
      

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
      yReco->Divide (yData);
      yReco->SetMarkerStyle (6);
      yReco->GetXaxis ()->SetLabelSize (0.06);
      yReco->GetYaxis ()->SetLabelSize (0.06);
      yReco->GetXaxis ()->SetTitleSize (0);
      yReco->GetYaxis ()->SetTitleSize (0.06);
      yReco->GetYaxis ()->SetTitleOffset (0.5);
      
      yReco->GetYaxis ()->SetRangeUser (0.9, 1.1);
      yReco->GetXaxis ()->SetRangeUser (-2.5, 2.5);
      yReco->GetYaxis ()->SetTitle ("Ratios");
      yReco->SetMarkerStyle (20);
      yReco->SetLineWidth (1);
      yReco->SetTitle ("");
      double max=yReco->GetMaximum();
      double min=yReco->GetMinimum();
      yReco->GetYaxis()->SetRangeUser(min,max);
      yReco->SetStats(1);
      yReco->Draw ("ep");
      
      yRatio->Divide(yTrue);		
      yRatio->SetMarkerStyle (20);
      yRatio->SetMarkerSize(0.0);
      yRatio->SetTitle ("");
      yRatio->SetStats(1);
      yRatio->SetLineStyle(3);
      yRatio->SetLineColor(kMagenta+3);
      yRatio->Draw ("HIST SAME");
      
      TLegend *legend_w3 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_w3->SetFillColor (0);
      legend_w3->SetFillStyle (0);
      legend_w3->SetBorderSize (0);
      legend_w3->AddEntry (yReco, "Data Unfolded / MC truth", "LP20");
      legend_w3->AddEntry (yRatio, "MC reco / MC truth", "L");
      legend_w3->Draw ("same");
    
   pad14->Update(); 

      /*n->SetLineColor (kBlue + 1);
      n->SetLineWidth (1);
      n->SetLineStyle (2);
      n->Draw ("same");
      jj3->SetParameter(0, 1);
      jj3->SetLineWidth(.5);
      jj3->SetLineColor(kWhite);
      yReco->Fit(jj3);
      jj3->Draw ("same");
      n->Draw ("same");
      
      e->cd ();*/
      string title3= s+"Zy_"+method+"_"+num.str()+".pdf";
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
  string title3= s+"/MatrixZy.pdf";
  Y->Print(title3.c_str());
}


void
Unfolding::LoopJetPt ()
{


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
  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_17.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  //DATA
  fB->cd ("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_17.root:/validationJEC");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");

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
      

      if(jet1_pt>30 && jet1_pt<330 && jet1_pt_gen>30 && jet1_pt_gen<330){
      jTrue->Fill (jet1_pt_gen);
      jMCreco->Fill (jet1_pt);
      jMatx->Fill (jet1_pt, jet1_pt_gen); 
    }//qui correggo per le eff e poi fillo response
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
      
      if(jet1_pt>30 && jet1_pt<330){

      jData->Fill (jet1_pt);
      jData2->Fill (jet1_pt);
    }
    }
      jData->Sumw2();

      bool consider_efficiency = true;
      
      //if(consider_efficiency) {

      TFile *eff = TFile::Open("/gpfs/cms/data/2011/TaP/efficiencies_2011_v2_17.root");
      TDirectory *dir=(TDirectory*)eff->cd("efficiency_vs_leadjetpt");
      
      TH1F *h1 = (TH1F*)gDirectory->Get("MC_WP80_Tag");
      TH1F *h2 = (TH1F*)gDirectory->Get("MC_WP80_Probe");
      TH1F *h3 = (TH1F*)gDirectory->Get("MC_HLTele8_Tag");
      TH1F *h4 = (TH1F*)gDirectory->Get("MC_RECO_Probe");
      TH1F *h5 = (TH1F*)gDirectory->Get("MC_HLTele17_Tag");
      TH1F *h6 = (TH1F*)gDirectory->Get("MC_HLTele8_Probe");
      TH1F *h7 = (TH1F*)gDirectory->Get("MC_HLTele17_Probe");

      TH1F *k1 = (TH1F*)gDirectory->Get("DATA_WP80_Tag");
      TH1F *k2 = (TH1F*)gDirectory->Get("DATA_WP80_Probe");
      TH1F *k3 = (TH1F*)gDirectory->Get("DATA_HLTele8_Tag");
      TH1F *k4 = (TH1F*)gDirectory->Get("DATA_RECO_Probe");
      TH1F *k5 = (TH1F*)gDirectory->Get("DATA_HLTele17_Tag");
      TH1F *k6 = (TH1F*)gDirectory->Get("DATA_HLTele8_Probe");
      TH1F *k7 = (TH1F*)gDirectory->Get("DATA_HLTele17_Probe");



      /* tag & probe efficiency study */

	cout << "2" << endl ;	
     
      h1->Multiply(h2);
      h1->Multiply(h3);
      h1->Multiply(h4);      
      h1->Multiply(h5);      
      h1->Multiply(h6);      
      h1->Multiply(h7);      
      
      jMCreco->Divide(h1);

      k1->Multiply(k2);
      k1->Multiply(k3);
      k1->Multiply(k4);      
      k1->Multiply(k5);      
      k1->Multiply(k6);      
      k1->Multiply(k7);      
     
      jData->Divide(k1);

	cout << "4" << endl ;	
	    
     // }
      RooUnfoldResponse response_j(jMCreco, jTrue, jMatx); 
      response_j.UseOverflow();
	cout << "5" << endl ;	
        


  	
 
  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=2; k<11; k++){
      int myNumber=k;
      stringstream num;
      num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Jet pT diff xsec distribution. "+title;
      cout<<"ongoing:"<<title<<endl;
 
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_j(&response_j, jData, myNumber);
	jReco = (TH1D *) unfold_j.Hreco ();
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_j (&response_j, jData, myNumber);	// OR
	jReco = (TH1D *) unfold_j.Hreco ();
      }
	jReco->Sumw2();
	jData->Sumw2();
	jMCreco->Sumw2();
	jTrue->Sumw2();

	        
if(k==10){ //need to be generalized for every k ...

	jData   -> Scale(1./( double) NZ * 0.65284);
	jReco   -> Scale(1./ (double) NZ * 0.65284);
        jMCreco -> Scale(1./( double) NZ * 0.65284);
        jTrue   -> Scale(1./( double) NZ * 0.65284);
}	
      cout<<"6"<<endl;      

      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.3, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      title2="Jet pT diff xsec distribution. "+title;
      jReco->SetTitle (title2.c_str());
      jReco->GetXaxis ()->SetTitle ("");
      jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d p_{T}");
      jReco->SetMarkerStyle (20);
      jData->SetMarkerStyle (21);
      jData->SetLineColor(kGreen);
      //if (k==2){
      
	

      double area = (((double)jReco->Integral ()) / (double)jTrue->Integral ());
      cout<<"area "<<area<<endl;
      

      //jReco->Scale (1.00000 / (area));
      //jData->Scale (1.00000 / (area));
       
        jMCreco->Scale(area);
        jTrue->Scale  (area);

        w->cd();
        jReco->Write("jReco");

	cout<<NZ<<endl;	
     
      //}
      jReco->SetMarkerStyle (20);
      jReco->SetStats(0);
      jReco->GetXaxis()->SetTitle("jet pT [GeV/c]");
      jReco->Draw("EP");		//risultato dell'unfolding
      jReco->SetLineColor (kRed);
      jReco->SetLineWidth (2);
      jMCreco->Draw();
      jMCreco->SetLineColor (kBlue + 1);
      jMCreco->SetLineStyle (2);
      jTrue->SetLineColor (kBlack);
      jMCreco->SetLineWidth (2);
      jTrue->SetLineWidth (2);

      jTrue->Draw ("EPSAME");
      jData2->SetLineColor(kGreen+1);
      jData2->Draw("EPSAME");

      jReco->DrawCopy ();
      pad1->SetLogy (1);
      jTrue->Draw ("same");
      jMCreco->Draw ("same");
      jData->SetLineStyle(2);
      jData->Draw("same");

      pad1->SetBottomMargin (0);
      jReco->SetTitleSize (0);

      jTrue->SetTitleSize (0);

      for(int i=1; i<=5; i++){
	double x = jReco->GetBinContent(i);
	cout << x << endl;
	}


      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (jReco, "Data Unfolded", "LP20");
      legend_d->AddEntry (jTrue, "MC truth", "L");
      legend_d->AddEntry (jMCreco, "MC reco", "L");
      legend_d->AddEntry(jData,"Data Folded","L");
      legend_d->Draw ("same");
      //legend_d->AddEntry((TObject*)0,"#int L dt = 4.096 fb^{-1}","");
       
      /* Save */


       pad1->Update();
	
      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.3);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      jReco->GetXaxis ()->SetLabelSize (0.1);
      jReco->GetYaxis ()->SetLabelSize (0.08);
      jReco->SetStats (0);
      jReco->Divide(jData);
      jReco->SetMarkerStyle (6);
      jReco->GetXaxis ()->SetLabelSize (0.06);
      jReco->GetYaxis ()->SetLabelSize (0.06);
      jReco->GetXaxis ()->SetTitleSize (0);
      jReco->GetYaxis ()->SetTitleSize (0.06);
      jReco->GetYaxis ()->SetTitleOffset (0.5);

      jReco->GetYaxis ()->SetRangeUser (0.5, 1.3);
      jReco->GetXaxis ()->SetRangeUser (0, 5);
      jReco->GetYaxis ()->SetTitle ("Ratios");
      jReco->GetXaxis()->SetTitle("jet pT [GeV/c]");
      jReco->SetMarkerStyle (20);
      jReco->SetLineWidth (0);
      jReco->SetTitle ("");
      double max=jReco->GetMaximum();
      double min=jReco->GetMinimum();
      jReco->GetYaxis()->SetRangeUser(min,max);
      jReco->SetStats(1);

    
      jReco->Draw("ep");
      
      TLegend *legend_w = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_w->SetFillColor (0);
      legend_w->SetFillStyle (0);
      legend_w->SetBorderSize (0);
      legend_w->AddEntry (jReco, "Data unfolded / Data folded", "LP20");
      legend_w->Draw ("same");
     
      pad2->Update();

      /*l->SetLineColor (kBlue + 1);
      l->SetLineWidth (1);
      l->SetLineStyle (2);
      l->Draw ("same");
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(111);
      jj->SetParameter(0, 1);
      jj->SetLineWidth(.5);
      jj->SetLineColor(kWhite);
      NReco->Fit(jj);
      jj->Draw ("same");
      l->Draw ("same");*/
      string title3= s+"JETPTXSEC"+method+"_"+num.str()+".pdf";
      c->cd ();
      c->Print(title3.c_str());
      num.str("");
   }
  }
  TCanvas *N =new TCanvas ("jet pT response matrix", "jet pT response matrix", 1000, 700);
  N->cd ();
  jMatx->SetStats (0);
  jMatx->GetXaxis()->SetTitle("Reconstructed jet pT [GeV/c]");
  jMatx->GetYaxis()->SetTitle("Generated jet pT [GeV/c]");
  gStyle->SetPalette (1);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  jMatx->SetMarkerColor (kBlack);
  double entries=1.000/(double)jMatx->GetEntries();
  jMatx->Scale(entries);
  jMatx->Draw ("COLZ,text");
      
 
}


#ifndef __CINT__

	int
	  main ()
	{
	  Unfolding ();
	w->cd();
        NReco->Write("NReco");
        yReco->Write("yReco");
        PReco->Write("PReco");


	  return 0;
	}				// Main program when run stand-alone
#endif
