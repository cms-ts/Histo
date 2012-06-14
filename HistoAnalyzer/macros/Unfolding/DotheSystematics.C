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
#include "plotsHistsAndRatio.C"

string stringsyst= "/afs/infn.it/ts/user/marone/html/ZJets/Systematics/";
string version="_v2_28";
//string stringsyst= "plot"+version+"/";

/////////////////////////////////
///////// Main Loop
/////////////////////////////////

std::vector<double> DotheSystematics(){
  gROOT->LoadMacro("plotsHistsAndRatio.C");
  std::vector<double> vec;
  int whichjet=1;

  vec=DotheSystematicsJECMultiplicity();
  vec=DotheSystematicsPUMultiplicity();
  //DotheSystematicsUnfoldingPythia(whichjet);
  DotheSystematicsJECJetPt(whichjet);
  DotheSystematicsPUJetPt(whichjet);
  DotheSystematicsJECJetEta(whichjet);
  DotheSystematicsPUJetEta(whichjet);
  DotheSystematicsUnfMethodJetPt(whichjet);
  //To be added by Andrea
  //DotheSystematicsEfficiencyJetPt(whichjet);
  //DotheSystematicsEfficiencyJetMultiplicity(whichjet);
  return vec;
}

std::vector<double> DotheSystematicsLoop(){
  gROOT->LoadMacro("plotsHistsAndRatio.C");
  std::vector<double> vec;
  vec=DotheSystematicsJECMultiplicity();
  vec=DotheSystematicsPUMultiplicity();

  for (int i=1;i<=4;i++){
    int whichjet=i;
    //DotheSystematicsUnfoldingPythia(whichjet);
    DotheSystematicsJECJetPt(whichjet);
    DotheSystematicsPUJetPt(whichjet);
    DotheSystematicsJECJetEta(whichjet);
    DotheSystematicsPUJetEta(whichjet);
    DotheSystematicsUnfMethodJetPt(whichjet);
  }
  //To be added by Andrea
  //DotheSystematicsEfficiencyJetPt(whichjet);
  //DotheSystematicsEfficiencyJetMultiplicity(whichjet);
  return vec;
}


/////////////////////
///// JEC For Jet Multiplicity
////////////////////


std::vector<double> DotheSystematicsJECMultiplicity(){
  
  setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;
  string pathFile="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011"+version+".root";
  TFile *f = TFile::Open(pathFile.c_str());
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

  cout<<"Saving JEC Jet Multiplicity systematics in a file"<<endl;
  string filename="/gpfs/cms/data/2011/Uncertainties/systematicsJECJetMultiplicity"+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }

  TCanvas *ratio= new TCanvas ("ratio", "ratio", 1000, 700);
  ratio->cd();
  string title="JEC systematics Jet Multiplicity";
  plotHistsAndRatio(DownJEC,UpJEC,JEC,title.c_str(),"Jet Multiplicity","# Events"); 
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "Original Distribution", "L");
  legend_1->AddEntry (UpJEC, "Scale Up", "L");
  legend_1->AddEntry (DownJEC, "Scale Down", "L");
  legend_1->Draw ("same");
  
  stringsystPU=stringsyst+"/JECJetMultiplicity.png";
  c1->Print(stringsystPU.c_str()); 
  return systs;
}

/////////////////////
///// PU For Jet Multiplicity
////////////////////


std::vector<double> DotheSystematicsPUMultiplicity(){
  
  setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  string pathFile="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011"+version+".root";
  TFile *f = TFile::Open(pathFile.c_str());

  f->cd("validationJECXSScaleDown"); //wrong one!!! need to have the dir. w/o JEC
  
  TH1F *DownJEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
  
  f->cd("validationJEC/");
  TH1F *JEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
  TH1F *hnew = (TH1F*)JEC->Clone("hnew");
  
  f->cd("validationJECXSScaleUp");
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

  cout<<"Saving PU Jet Multiplicity systematics in a file"<<endl;
  string filename="/gpfs/cms/data/2011/Uncertainties/systematicsPUJetMultiplicity"+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }

  TCanvas *ratio= new TCanvas ("ratio", "ratio", 1000, 700);
  ratio->cd();
  string title="PU systematics Jet Multiplicity";
  plotHistsAndRatio(DownJEC,UpJEC,JEC,title.c_str(),"Jet Multiplicity","# Events"); 
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "Original Distribution", "L");
  legend_1->AddEntry (UpJEC, "Scale Up", "L");
  legend_1->AddEntry (DownJEC, "Scale Down", "L");
  legend_1->Draw ("same");
  
  stringsystPU=stringsyst+"/PUJetMultiplicity.png";
  c1->Print(stringsystPU.c_str()); 
  return systs;
}


///////////////////////////
//   JEC For JET pt
//////////////////////////

void DotheSystematicsJECJetPt(int whichjet){
  
  setTDRStyle();

 string namejet="";
 string namejet2="";
 if (whichjet==1) {namejet="Leading"; namejet2 = "1";}
 if (whichjet==2) {namejet="Second leading"; namejet2 = "2";}
 if (whichjet==3) {namejet="Third leading"; namejet2 = "3";}
 if (whichjet==4) {namejet="Fourth leading"; namejet2 = "4";}
 
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  string pathFile="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011"+version+".root";
  TFile *f = TFile::Open(pathFile.c_str());
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
    else systs.push_back(fabs(0.));
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

  cout<<"Saving Jet PT JEC systematics in a file"<<endl;
  string filename="/gpfs/cms/data/2011/Uncertainties/systematicsJECJet"+namejet2+"Pt"+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }

  TCanvas *ratio= new TCanvas ("ratio", "ratio", 1000, 700);
  ratio->cd();
  string title="JEC systematics "+namejet+" Jet Pt";
  plotHistsAndRatio(DownJEC,UpJEC,JEC,title.c_str(),"Jet Pt [GeV]","# Events"); 
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "Original Distribution", "L");
  legend_1->AddEntry (UpJEC, "Scale Up", "L");
  legend_1->AddEntry (DownJEC, "Scale Down", "L");
  legend_1->Draw ("same");
  
  stringsystPU=stringsyst+"/JECJetPt_"+namejet+".png";
  c1->Print(stringsystPU.c_str()); 
    
  return systs;
}

/////////////////////
/// JEC fot Jet Eta
/////////////////////

void DotheSystematicsJECJetEta(int whichjet){
  
   string namejet="";
   string namejet2="";
   if (whichjet==1) {namejet="Leading"; namejet2 = "1";}
   if (whichjet==2) {namejet="Second leading"; namejet2 = "2";}
   if (whichjet==3) {namejet="Third leading"; namejet2 = "3";}
   if (whichjet==4) {namejet="Fourth leading"; namejet2 = "4";}

  setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  string pathFile="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011"+version+".root";
  TFile *f = TFile::Open(pathFile.c_str());
  f->cd("validationJECScaleDown"); //wrong one!!! need to have the dir. w/o JEC
  
  TH1F *DownJEC;

  if (whichjet==1) DownJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet1");
  if (whichjet==2) DownJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet2");
  if (whichjet==3) DownJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet3");
  if (whichjet==4) DownJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet4");
  
  f->cd("validationJEC/");

  TH1F *JEC;
  if (whichjet==1) JEC= (TH1F*)gDirectory->Get("h_jetEtaNjet1");
  if (whichjet==2) JEC= (TH1F*)gDirectory->Get("h_jetEtaNjet2");
  if (whichjet==3) JEC= (TH1F*)gDirectory->Get("h_jetEtaNjet3");
  if (whichjet==4) JEC= (TH1F*)gDirectory->Get("h_jetEtaNjet4");

  TH1F *hnew = (TH1F*)JEC->Clone("hnew");

  f->cd("validationJECScaleUp");

  TH1F *UpJEC;
  if (whichjet==1) UpJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet1");
  if (whichjet==2) UpJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet2");
  if (whichjet==3) UpJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet3");
  if (whichjet==4) UpJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet4");

  int rebin=50; //500 bin... Ma che cazzo! da 0 a 200 GeV... 190 Gev
  JEC->Rebin(rebin);
  DownJEC->Rebin(rebin);
  UpJEC->Rebin(rebin);
  hnew->Rebin(rebin);

  int numbbins=0;
  if (whichjet==1) numbbins=h_jetEtaNjet1->GetNbinsX();
  if (whichjet==2) numbbins=h_jetEtaNjet2->GetNbinsX();
  if (whichjet==3) numbbins=h_jetEtaNjet3->GetNbinsX();
  if (whichjet==4) numbbins=h_jetEtaNjet4->GetNbinsX();

  for(int i=1; i<=numbbins; i++){		
    double contentdown = DownJEC->GetBinContent(i);
    double content = JEC->GetBinContent(i);
    double contentup = UpJEC->GetBinContent(i);
    systerr = max(fabs(contentdown - content),fabs(contentup-content));
    if (content>0) cout<<"Difference in bin "<<i<<" for the JEC-No JEC is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleUp->"<<contentup<<" scaleDown->"<<contentdown<<" and central value "<<content<<endl;
    hnew->SetBinError(i, systerr);
    if (content>0) systs.push_back(fabs(systerr/content));
    else systs.push_back(fabs(0.));
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
  string filename="/gpfs/cms/data/2011/Uncertainties/systematicsJECJet"+namejet2+"Eta"+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }

  return systs;
}

////////////////////////
///// PU for JE Pt
/////////////////////////

 std::vector<double> DotheSystematicsPUJetPt(int whichjet){
  
  setTDRStyle();

 string namejet="";
   string namejet2="";
   if (whichjet==1) {namejet="Leading"; namejet2 = "1";}
   if (whichjet==2) {namejet="Second leading"; namejet2 = "2";}
   if (whichjet==3) {namejet="Third leading"; namejet2 = "3";}
   if (whichjet==4) {namejet="Fourth leading"; namejet2 = "4";}

 using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  string pathFile="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011"+version+".root";
  TFile *f = TFile::Open(pathFile.c_str());

  f->cd("validationJECXSScaleDown"); //wrong one!!! need to have the dir. w/o JEC
  
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

  f->cd("validationJECXSScaleUp");

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
    if (content>0) cout<<"Difference in bin "<<i<<" for the PU is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleXSUp->"<<contentup<<" scaleXSDown->"<<contentdown<<" and central value "<<content<<endl;
    hnew->SetBinError(i, systerr);
    if (content>0) systs.push_back(fabs(systerr/content));
    else systs.push_back(fabs(0.));
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
  string filename="/gpfs/cms/data/2011/Uncertainties/systematicsPUJet"+namejet2+"Pt"+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }
  
  TCanvas *ratio= new TCanvas ("ratio", "ratio", 1000, 700);
  ratio->cd();
  string title="Pile-Up systematics "+namejet+" Jet Pt";
  plotHistsAndRatio(DownJEC,UpJEC,JEC,title.c_str(),"Jet Pt [GeV]","# Events"); 
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "Original Distribution", "L");
  legend_1->AddEntry (UpJEC, "Scale Up", "L");
  legend_1->AddEntry (DownJEC, "Scale Down", "L");
  legend_1->Draw ("same");
  
  stringsystPU=stringsyst+"/PU_Jet"+namejet2+"Pt.png";
  c1->Print(stringsystPU.c_str()); 

  return systs;
}



////////////////////////
///// PU for Jet Eta
/////////////////////////

 std::vector<double> DotheSystematicsPUJetEta(int whichjet){
  
  setTDRStyle();

 string namejet="";
   string namejet2="";
   if (whichjet==1) {namejet="Leading"; namejet2 = "1";}
   if (whichjet==2) {namejet="Second leading"; namejet2 = "2";}
   if (whichjet==3) {namejet="Third leading"; namejet2 = "3";}
   if (whichjet==4) {namejet="Fourth leading"; namejet2 = "4";}

 using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  string pathFile="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011"+version+".root";
  TFile *f = TFile::Open(pathFile.c_str());
  f->cd("validationJECXSScaleDown"); //wrong one!!! need to have the dir. w/o JEC
  
  TH1F *DownJEC;

  if (whichjet==1) DownJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet1");
  if (whichjet==2) DownJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet2");
  if (whichjet==3) DownJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet3");
  if (whichjet==4) DownJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet4");
  
  f->cd("validationJEC/");

  TH1F *JEC;
  if (whichjet==1) JEC= (TH1F*)gDirectory->Get("h_jetEtaNjet1");
  if (whichjet==2) JEC= (TH1F*)gDirectory->Get("h_jetEtaNjet2");
  if (whichjet==3) JEC= (TH1F*)gDirectory->Get("h_jetEtaNjet3");
  if (whichjet==4) JEC= (TH1F*)gDirectory->Get("h_jetEtaNjet4");

  TH1F *hnew = (TH1F*)JEC->Clone("hnew");

  f->cd("validationJECXSScaleUp");

  TH1F *UpJEC;
  if (whichjet==1) UpJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet1");
  if (whichjet==2) UpJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet2");
  if (whichjet==3) UpJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet3");
  if (whichjet==4) UpJEC= (TH1F*)gDirectory->Get("h_jetEtaNjet4");

  int rebin=50; //500 bin... Ma che cazzo! da 0 a 200 GeV... 190 Gev
  JEC->Rebin(rebin);
  DownJEC->Rebin(rebin);
  UpJEC->Rebin(rebin);
  hnew->Rebin(rebin);

  int numbbins=0;
  if (whichjet==1) numbbins=h_jetEtaNjet1->GetNbinsX();
  if (whichjet==2) numbbins=h_jetEtaNjet2->GetNbinsX();
  if (whichjet==3) numbbins=h_jetEtaNjet3->GetNbinsX();
  if (whichjet==4) numbbins=h_jetEtaNjet4->GetNbinsX();

  for(int i=1; i<=numbbins; i++){		
    double contentdown = DownJEC->GetBinContent(i);
    double content = JEC->GetBinContent(i);
    double contentup = UpJEC->GetBinContent(i);
    systerr = max(fabs(contentdown - content),fabs(contentup-content));
    if (content>0) cout<<"Difference in bin "<<i<<" for the PU is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleXSUp->"<<contentup<<" scaleXSDown->"<<contentdown<<" and central value "<<content<<endl;
    hnew->SetBinError(i, systerr);
    if (content>0) systs.push_back(fabs(systerr/content));
    else systs.push_back(fabs(0.));
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
  string filename="/gpfs/cms/data/2011/Uncertainties/systematicsPUJet"+namejet2+"Eta"+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }
  
  TCanvas *ratio= new TCanvas ("ratio", "ratio", 1000, 700);
  ratio->cd();
  string title="Pile-Up systematics "+namejet+" Jet Eta";
  plotHistsAndRatio(DownJEC,UpJEC,JEC,title.c_str(),"Jet Eta","# Events"); 
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "Original Distribution", "L");
  legend_1->AddEntry (UpJEC, "Scale Up", "L");
  legend_1->AddEntry (DownJEC, "Scale Down", "L");
  legend_1->Draw ("same");
  
  stringsystPU=stringsyst+"/PUJet_"+namejet2+"Eta.png";
  c1->Print(stringsystPU.c_str()); 

  return systs;
}

///////////////////
//// Unfolding Method For JetPt
//////////////////

DotheSystematicsUnfMethodJetPt(whichjet){
  
  bool kparsystematics=false;

  setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  string namejet="";
   string namejet2="";
   if (whichjet==1) {namejet="Leading"; namejet2 = "1";}
   if (whichjet==2) {namejet="Second leading"; namejet2 = "2";}
   if (whichjet==3) {namejet="Third leading"; namejet2 = "3";}
   if (whichjet==4) {namejet="Fourth leading"; namejet2 = "4";}

   string pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions"+version+".root";
   TFile *f = TFile::Open(pathFile.c_str());

  f->cd(); //wrong one!!! need to have the dir. w/o JEC
  TH1F *MD;
  if (whichjet==1) MD = (TH1F*)gDirectory->Get("jReco_leading");
  if (whichjet==2) MD = (TH1F*)gDirectory->Get("jReco_subleading");
  if (whichjet==3) MD = (TH1F*)gDirectory->Get("jReco_subsubleading");
  if (whichjet==4) MD = (TH1F*)gDirectory->Get("jReco_subsubsubleading");

  string UnfMethod;
  TFile *f2;
  if (!kparsystematics) UnfMethod="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsBayes"+version+".root";
  else UnfMethod="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions"+version+"Kmoved.root";
  cout<<UnfMethod<<endl;
  f2 = TFile::Open(UnfMethod.c_str());
    
  f2->cd(); //wrong one!!! need to have the dir. w/o JEC
  TH1F *P;

  if (whichjet==1) P = (TH1F*)gDirectory->Get("jReco_leading");  
  if (whichjet==2) P = (TH1F*)gDirectory->Get("jReco_subleading");  
  if (whichjet==3) P = (TH1F*)gDirectory->Get("jReco_subsubleading");  
  if (whichjet==4) P = (TH1F*)gDirectory->Get("jReco_subsubsubleading");  


  TCanvas *d = new TCanvas ("d", "d", 1000, 700);
  d->cd ();
 
  string title;
  if (!kparsystematics) title="Unfolding Method Systematics "+namejet+" Jet Pt";
  else title="Unfolding K Parameter Systematics "+namejet+" Jet Pt";

  plotHistsAndRatio(MD,P,title.c_str(),"Jet Pt [GeV]","# Events"); 
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (MD, "SVD Method", "L");
  legend_1->AddEntry (P, "Bayes Method", "L");
  legend_1->Draw ("same");

  if (!kparsystematics) stringsystPU=stringsyst+"/UnfoldingMethod_"+namejet+".png";
  else stringsystPU=stringsyst+"/UnfoldingKParam_"+namejet+".png";
  c1->Print(stringsystPU.c_str()); 
 
}


////////////////
///// Systematcs for MD-Pythia in Unfolding...
///////////////


void DotheSystematicsUnfoldingPythia(int whichjet){

   string namejet="";
   string namejet2="";
   if (whichjet==1) {namejet="Leading"; namejet2 = "1";}
   if (whichjet==2) {namejet="Second leading"; namejet2 = "2";}
   if (whichjet==3) {namejet="Third leading"; namejet2 = "3";}
   if (whichjet==4) {namejet="Fourth leading"; namejet2 = "4";}
  
  setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  string path1="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions"+version+".root";
  TFile *f = TFile::Open(path1.c_str());
  f->cd(); //wrong one!!! need to have the dir. w/o JEC
 
  TH1F *MD;
  if (whichjet==1) MD = (TH1F*)gDirectory->Get("jReco_leading");
  if (whichjet==2) MD = (TH1F*)gDirectory->Get("jReco_subleading");
  if (whichjet==3) MD = (TH1F*)gDirectory->Get("jReco_subsubleading");
  if (whichjet==4) MD = (TH1F*)gDirectory->Get("jReco_subsubsubleading"); 

  string path2="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsPythia"+version+".root";
  TFile *f2 = TFile::Open(path2.c_str());
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

  cout<<"Saving Pythia MD- systematics in a file"<<endl;
  string filename="/gpfs/cms/data/2011/Uncertainties/systematicsPythiaMD"+namejet2+"Eta"+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }
  

  stringsystPU=stringsyst+"/MDPythia_"+namejet+".png";
  d->Print(stringsystPU.c_str()); 


 
}
