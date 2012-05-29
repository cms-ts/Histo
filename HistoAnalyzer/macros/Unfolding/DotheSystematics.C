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
#include "tdrstyle.C"

std::vector<double> DotheSystematics(){
  std::vector<double> vec;
  //vec=DotheSystematicsJECMultiplicity();
  int whichjet=4;
  DotheSystematicsJECJetPt(whichjet);
  //DotheSystematicsUnfoldingPythia();
  return vec;
}

std::vector<double> DotheSystematicsJECMultiplicity(){
  
  //setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  TFile *f = TFile::Open("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_22.root");
  f->cd("validationJECScaleDown"); //wrong one!!! need to have the dir. w/o JEC
  
  TH1F *DownJEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
  
  f->cd("validationJEC/");
  TH1F *JEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
  TH1F *hnew = (TH1F*)JEC->Clone("hnew");
  
  f->cd("validationJECScaleUp");
  TH1F *UpJEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
  
  for(int i=1; i<=JEC->GetNbinsX(); i++){		
    double contentdown = DownJEC->GetBinContent(i);
    double content = JEC->GetBinContent(i);
    double contentup = UpJEC->GetBinContent(i);
    systerr = max(fabs(contentdown - content),fabs(contentup-content));
    cout<<"Difference in bin "<<i<<" for the JEC-No JEC is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleUp->"<<contentup<<" scaleDown->"<<contentdown<<" and central value "<<content<<endl;
    hnew->SetBinError(i, systerr);
    systs.push_back(fabs(systerr/content));
  }
  TCanvas *d = new TCanvas ("d", "d", 1000, 700);
  d->cd ();
  
  d->SetLogy();
  JEC->SetLineColor(kBlack);
  JEC->SetMarkerStyle(20);
  JEC->SetMarkerColor(kBlack);
  JEC->GetXaxis()->SetTitle("# of Jets");
  JEC->GetYaxis()->SetTitle("Number of Z+jet events");
  hnew->SetLineColor(kBlack);
  hnew->SetMarkerStyle(20);
  hnew->SetFillColor(5); 
  hnew->SetMarkerColor(kBlack);
  
  hnew->Draw("E2");
  JEC->Draw("e1same");
  
  
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "DATA Unfolded", "LP20");
  legend_1->AddEntry (hnew, "JEC systematic uncertanties", "F");
  legend_1->Draw ("same");

 
  TCanvas *JECp = new TCanvas ("JECp", "JECp", 1000, 700);
  JECp->cd ();
  JECp->SetLogy();

  JEC->SetLineColor(kBlack);
  JEC->SetMarkerStyle(20);
  JEC->SetMarkerColor(kBlack);  
  JEC->Draw("e2");

  UpJEC->SetLineColor(kBlue);
  UpJEC->SetMarkerStyle(20);
  UpJEC->SetMarkerColor(kBlue);
  UpJEC->Draw("e1same");
  
  DownJEC->SetLineColor(kRed);
  DownJEC->SetMarkerStyle(20);
  DownJEC->SetMarkerColor(kRed);
  DownJEC->Draw("e1same");
  
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "jet multiplicity", "L");
  legend_1->AddEntry (UpJEC, "jet multiplicity + error", "L");
  legend_1->AddEntry (DownJEC, "jet multiplicity - errror", "L");
  legend_1->Draw ("same");

  return systs;
}

void DotheSystematicsJECJetPt(int whichjet){
  
  setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  TFile *f = TFile::Open("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_22.root");
  f->cd("validationJECScaleDown"); //wrong one!!! need to have the dir. w/o JEC
  
  TH1F *DownJEC;

  if (whichjet==1) DownJEC= (TH1F*)gDirectory->Get("h_jetPtNjet1");
  if (whichjet==2) DownJEC= (TH1F*)gDirectory->Get("h_jetPtNjet2");
  if (whichjet==3) DownJEC= (TH1F*)gDirectory->Get("h_jetPtNjet3");
  if (whichjet==4) DownJEC= (TH1F*)gDirectory->Get("h_jetPtNjet4");
  
  f->cd("validationJEC/");

  TH1F *JEC;
  if (whichjet==1) JEC= (TH1F*)gDirectory->Get("h_jetPtNjet1");
  if (whichjet==2) JEC= (TH1F*)gDirectory->Get("h_jetPtNjet2");
  if (whichjet==3) JEC= (TH1F*)gDirectory->Get("h_jetPtNjet3");
  if (whichjet==4) JEC= (TH1F*)gDirectory->Get("h_jetPtNjet4");

  TH1F *hnew = (TH1F*)JEC->Clone("hnew");

  f->cd("validationJECScaleUp");

  TH1F *UpJEC;
  if (whichjet==1) UpJEC= (TH1F*)gDirectory->Get("h_jetPtNjet1");
  if (whichjet==2) UpJEC= (TH1F*)gDirectory->Get("h_jetPtNjet2");
  if (whichjet==3) UpJEC= (TH1F*)gDirectory->Get("h_jetPtNjet3");
  if (whichjet==4) UpJEC= (TH1F*)gDirectory->Get("h_jetPtNjet4");

  int rebin=50; //500 bin... Ma che cazzo! da 0 a 200 GeV... 190 Gev
  JEC->Rebin(rebin);
  DownJEC->Rebin(rebin);
  UpJEC->Rebin(rebin);
  hnew->Rebin(rebin);

  int numbbins=0;
  if (whichjet==1) numbbins=h_jetPtNjet1->GetNbinsX();
  if (whichjet==2) numbbins=h_jetPtNjet2->GetNbinsX();
  if (whichjet==3) numbbins=h_jetPtNjet3->GetNbinsX();
  if (whichjet==4) numbbins=h_jetPtNjet4->GetNbinsX();

  for(int i=1; i<=numbbins; i++){		
    double contentdown = DownJEC->GetBinContent(i);
    double content = JEC->GetBinContent(i);
    double contentup = UpJEC->GetBinContent(i);
    systerr = max(fabs(contentdown - content),fabs(contentup-content));
    if (content>0) cout<<"Difference in bin "<<i<<" for the JEC-No JEC is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleUp->"<<contentup<<" scaleDown->"<<contentdown<<" and central value "<<content<<endl;
    hnew->SetBinError(i, systerr);
    if (content>0) systs.push_back(fabs(systerr/content));
    else systs.push_back(fabs(0));
  }
  TCanvas *d = new TCanvas ("d", "d", 1000, 700);
  d->cd ();
  
  d->SetLogy();
  JEC->SetLineColor(kBlack);
  JEC->SetMarkerStyle(20);
  JEC->SetMarkerColor(kBlack);
  JEC->GetXaxis()->SetTitle("# of Jets");
  JEC->GetYaxis()->SetTitle("Number of Z+jet events");
  hnew->SetLineColor(kBlack);
  hnew->SetMarkerStyle(20);
  hnew->SetFillColor(5); 
  hnew->SetMarkerColor(kBlack);
  
  hnew->Draw("E2");
  JEC->Draw("e1same");
  
  
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "DATA Unfolded", "LP20");
  legend_1->AddEntry (hnew, "JEC systematic uncertanties", "F");
  legend_1->Draw ("same");

 
  TCanvas *JECp = new TCanvas ("JECp", "JECp", 1000, 700);
  JECp->cd ();
  JECp->SetLogy();

  JEC->SetLineColor(kBlack);
  JEC->SetMarkerStyle(20);
  JEC->SetMarkerColor(kBlack);  
  JEC->Draw("e2");

  UpJEC->SetLineColor(kBlue);
  UpJEC->SetMarkerStyle(20);
  UpJEC->SetMarkerColor(kBlue);
  UpJEC->Draw("e1same");
  
  DownJEC->SetLineColor(kRed);
  DownJEC->SetMarkerStyle(20);
  DownJEC->SetMarkerColor(kRed);
  DownJEC->Draw("e1same");
  
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "jet multiplicity", "L");
  legend_1->AddEntry (UpJEC, "jet multiplicity + error", "L");
  legend_1->AddEntry (DownJEC, "jet multiplicity - errror", "L");
  legend_1->Draw ("same");

  cout<<"Saving systematics in a file"<<endl;
  string filename="/gpfs/cms/data/2011/Uncertainties/systematics.txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }

  
    
  return systs;
}

void DotheSystematicsUnfoldingPythia(){
  
  setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  TFile *f = TFile::Open("/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_22.root");
  f->cd(); //wrong one!!! need to have the dir. w/o JEC
  TH1F *MD = (TH1F*)gDirectory->Get("jReco");
 
  TFile *f2 = TFile::Open("/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_22pythia.root");
  f2->cd(); //wrong one!!! need to have the dir. w/o JEC
  TH1F *P = (TH1F*)gDirectory->Get("jReco");  

  TCanvas *d = new TCanvas ("d", "d", 1000, 700);
  d->cd ();
   
  TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.01, 1, 1);
  pad1->Draw ();
  pad1->cd ();
  gPad->SetLogy (1); 
  d->SetLogy();
  MD->SetLineColor(kRed);
  MD->SetMarkerStyle(20);
  MD->SetMarkerColor(kRed);
  MD->GetXaxis()->SetTitle("Leading Jet Pt");
  MD->GetYaxis()->SetTitle("# Events");  

  MD->Draw("E1");
  P->Draw("E1SAMES");

  pad1->SetBottomMargin (0.3);

  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (MD, "Unfolding using MadGraph", "L");
  legend_1->AddEntry (P, "Unfolding using Pythia", "L");
  legend_1->Draw ("same");

  //pad1->SetBottomMargin (0.1);
  TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.2);
  pad2->SetTopMargin (0);
  pad2->Draw ();
  pad2->cd ();
  TH1F* Ratio = (TH1F*)  MD -> Clone("MD");
  Ratio->SetName("Ratio");
  Ratio->Divide(P);
  Ratio->SetLineStyle(2);
  Ratio->SetTitle("");
  Ratio->GetYaxis()->SetRangeUser(0.7,1.3); 
  Ratio->SetLineWidth(2); 
  Ratio->Draw("E1HIST");  

  TF1 *fu = new TF1("fu","1",0,410);
  fu->SetLineWidth(1);
  fu->SetLineColor(kBlack);
  fu->Draw("SAMES");
 
}
