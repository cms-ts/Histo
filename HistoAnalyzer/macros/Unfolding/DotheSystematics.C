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
#include "plotsHistsAndRatioH.C"

//========================================================
///////  ELECTRONS  OR MUONS
//========================================================
bool isMu = false;
//bool isMu = true;
//========================================================
//========================================================
bool useRebin = false;
string txtPath, stringsyst;
//========================================================
//////  VERSION
//========================================================
//string version="_v2_28";
//string versionMu="_v2_31";
string version="_v2_33";
string versionMu="_v2_33";
//========================================================
//////  PATH  SYST  PDF
//========================================================
//string stringsyst= "/afs/infn.it/ts/user/marone/html/ZJets/Systematics/";
string stringsystEle= "plotSystEle"+version+"/";
string stringsystMu= "plotSystMu"+version+"/";
//========================================================
/////// PATH  SYST  TXT 
//========================================================
//string txtPathEle="/gpfs/cms/data/2011/Uncertainties/";
string txtPathEle=stringsystEle;
//string txtPathMu="/gpfs/cms/data/2011/Uncertainties/muons/";
string txtPathMu=stringsystMu;

/////////////////////////////////
///////// Main Loop
/////////////////////////////////

std::vector<double> DotheSystematics(){
   gROOT->LoadMacro("plotsHistsAndRatioH.C");
   std::vector<double> vec;
   int whichjet=4;
   if (!isMu){txtPath = txtPathEle; stringsyst = stringsystEle;}
   else {txtPath= txtPathMu; stringsyst = stringsystMu;}
   
   //==============================================
   //====== Jet Multiplicity
   //vec=DotheSystematicsJECMultiplicity();
   //vec=DotheSystematicsPUMultiplicity();
   //DotheSystematicsUnfMethodMultiplicity();
   //DotheSystematicsUnfoldingPythiaMultiplicity();
   //DotheSystematicsEfficiencyMultiplicity();
   //==============================================
   //====== Jet Pt
   //DotheSystematicsJEC(whichjet, "Pt");
   //DotheSystematicsPU(whichjet, "Pt");
   DotheSystematicsUnfMethod(whichjet, "Pt");
   //DotheSystematicsUnfoldingPythiaPt(whichjet);
   //DotheSystematicsEfficiency(whichjet, "Pt");
   //==============================================
   //====== Jet Eta
   //DotheSystematicsJEC(whichjet, "Eta");
   //DotheSystematicsPU(whichjet, "Eta");
   //DotheSystematicsUnfMethod(whichjet, "Eta");
   //DotheSystematicsUnfoldingPythiaEta(whichjet);
   //DotheSystematicsEfficiency(whichjet, "Eta");
   //==============================================
   //====== Jet Ht
   //DotheSystematicsJEC(whichjet, "Ht");
   //DotheSystematicsPU(whichjet, "Ht");
   //DotheSystematicsUnfMethod(whichjet, "Ht");
   //DotheSystematicsUnfoldingPythiaHt(whichjet);
   //DotheSystematicsEfficiency(whichjet, "Ht");
   //==============================================
   return vec;
}

std::vector<double> DotheSystematicsLoop(){
   gROOT->LoadMacro("plotsHistsAndRatioH.C");
   std::vector<double> vec;
   vec=DotheSystematicsJECMultiplicity();
   vec=DotheSystematicsPUMultiplicity();
   DotheSystematicsUnfMethodMultiplicity();
   //DotheSystematicsUnfoldingPythiaMultiplicity();
   //DotheSystematicsEfficiencyMultiplicity();
   
   for (int i=1;i<=4;i++){
      int whichjet=i;
      //====== Jet Pt
      DotheSystematicsJEC(whichjet, "Pt");
      DotheSystematicsPU(whichjet, "Pt");
      DotheSystematicsUnfMethod(whichjet, "Pt");
      //DotheSystematicsUnfoldingPythiaPt(whichjet);
      //DotheSystematicsEfficiency(whichjet, "Pt");
      //==============================================
      //====== Jet Eta
      DotheSystematicsJEC(whichjet, "Eta");
      DotheSystematicsPU(whichjet, "Eta");
      //DotheSystematicsUnfMethod(whichjet, "Eta");
      //DotheSystematicsUnfoldingPythiaEta(whichjet);
      //DotheSystematicsEfficiency(whichjet, "Eta");
      //==============================================
      //====== Jet Ht
      //DotheSystematicsJEC(whichjet, "Ht");
      //DotheSystematicsPU(whichjet, "Ht");
      //DotheSystematicsUnfMethod(whichjet, "Ht");
      //DotheSystematicsUnfoldingPythiaHt(whichjet);
      //DotheSystematicsEfficiency(whichjet, "Ht");
   }
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
  string pathFile;
  if (!isMu) pathFile="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011"+version+".root";
  else pathFile="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011Mu"+versionMu+".root";
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
    //cout<<"Difference in bin "<<i<<" for the JEC-No JEC is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleUp->"<<contentup<<" scaleDown->"<<contentdown<<" and central value "<<content<<endl;
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
  string filename=txtPath+"systematicsJECJetMultiplicity"+version+".txt";
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
  
  stringsystPU=stringsyst+"/JECJetMultiplicity.pdf";
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

  string pathFile;
  if (!isMu) pathFile="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011Mu"+version+".root";
  else pathFile="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011Mu"+versionMu+".root";

  TFile *f = TFile::Open(pathFile.c_str());

  if (!isMu) f->cd("validationJECXSScaleDown"); //wrong one!!! need to have the dir. w/o JEC
  else f->cd("validationJECMuXSScaleDown");

  TH1F *DownJEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
  
  if (!isMu) f->cd("validationJEC/");
  else f->cd("validationJECmu/");
  TH1F *JEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
  TH1F *hnew = (TH1F*)JEC->Clone("hnew");
  
  if (!isMu) f->cd("validationJECXSScaleUp");
  else f->cd("validationJECMuXSScaleUp/");

  TH1F *UpJEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
  
  for(int i=1; i<=JEC->GetNbinsX(); i++){		
    double contentdown = DownJEC->GetBinContent(i);
    double content = JEC->GetBinContent(i);
    double contentup = UpJEC->GetBinContent(i);
    systerr = max(fabs(contentdown - content),fabs(contentup-content));
    //cout<<"Difference in bin "<<i<<" for the JEC-No JEC is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleUp->"<<contentup<<" scaleDown->"<<contentdown<<" and central value "<<content<<endl;
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
  string filename=txtPath+"systematicsPUJetMultiplicity"+version+".txt";
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
  
  stringsystPU=stringsyst+"/PUJetMultiplicity.pdf";
  c1->Print(stringsystPU.c_str()); 
  return systs;
}

//////////////////////////////////////
//
//   UNFOLDING METHOD For Jet Multiplicity   //
//
//////////////////////////////////////

void DotheSystematicsUnfMethodMultiplicity(){
  
  bool kparsystematics=false;

  setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  //string pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions"+version+".root";
  string pathFile;
  if (!isMu) pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_30SVD.root";
  else pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_30SVD.root";
   TFile *f = TFile::Open(pathFile.c_str());

  f->cd(); //wrong one!!! need to have the dir. w/o JEC
  TH1F *MD = (TH1F*)gDirectory->Get("JetMultiplicityUnfolded");

  string UnfMethod;
  TFile *f2;
  //if (!kparsystematics) UnfMethod="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsBayes"+version+".root";
  if (!kparsystematics) {
     if (!isMu) UnfMethod="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_30Bayes.root";
     else UnfMethod="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_30Bayes.root";}
  else UnfMethod="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions"+version+"Kmoved.root";
  cout<<UnfMethod<<endl;
  f2 = TFile::Open(UnfMethod.c_str());
    
  f2->cd(); //wrong one!!! need to have the dir. w/o JEC
  TH1F *P = (TH1F*)gDirectory->Get("JetMultiplicityUnfolded");   

  for(int i=1; i<=MD->GetNbinsX(); i++){	
     double content = MD->GetBinContent(i);
     double contentup = P->GetBinContent(i);
     systerr = fabs(contentup-content);
     systs.push_back(fabs(systerr/content));
  }

  cout<<"Saving Unfolding Method for Jet Multiplicity - systematics in a file"<<endl;
  string filename=txtPath+"systematicsUnfMethod_JetMultiplicity"+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }

  TCanvas *d = new TCanvas ("d", "d", 1000, 700);
  d->cd ();
 
  string title;
  if (!kparsystematics) title="Unfolding Method Systematics Jet Multiplicity";
  else title="Unfolding K Parameter Systematics Jet Multiplicity";

  plotHistsAndRatio(MD,P,title.c_str(),"Jet Multiplicity","# Events"); 
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (MD, "SVD Method", "L");
  legend_1->AddEntry (P, "Bayes Method", "L");
  legend_1->Draw ("same");

  if (!kparsystematics) stringsystPU=stringsyst+"/UnfoldingMethod_JetMultiplicity.pdf";
  else stringsystPU=stringsyst+"/UnfoldingKParam_JetMultiplicity.pdf";
  c1->Print(stringsystPU.c_str()); 
 
}
/////////////////////
///// Efficiency For Jet Multiplicity
////////////////////


std::vector<double> DotheSystematicsEfficiencyMultiplicity(){
  
  setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;
  string pathFile, pathFileUp, pathFileDown;
  if (!isMu) {
     pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyReference"+version+".root";
     pathFileUp="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyScaleUp"+version+".root";
     pathFileDown="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyScaleDown"+version+".root";
  } else {
     pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyReference_Mu"+versionMu+".root";
     pathFileUp="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyScaleUp_Mu"+versionMu+".root";
     pathFileDown="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyScaleDown_Mu"+versionMu+".root";
  }

  TFile *fD = TFile::Open(pathFileDown.c_str());
  fD->cd(); //wrong one!!! need to have the dir. w/o JEC 
  TH1F *DownJEC = (TH1F*)gDirectory->Get("JetMultiplicityUnfolded");
  
  TFile *f = TFile::Open(pathFile.c_str());
  f->cd();
  TH1F *JEC = (TH1F*)gDirectory->Get("JetMultiplicityUnfolded");
  TH1F *hnew = (TH1F*)JEC->Clone("hnew");
  
  TFile *fU = TFile::Open(pathFileUp.c_str());
  fU->cd();
  TH1F *UpJEC = (TH1F*)gDirectory->Get("JetMultiplicityUnfolded");
  
  for(int i=1; i<=JEC->GetNbinsX(); i++){		
    double contentdown = DownJEC->GetBinContent(i);
    double content = JEC->GetBinContent(i);
    double contentup = UpJEC->GetBinContent(i);
    systerr = max(fabs(contentdown - content),fabs(contentup-content));
    //cout<<"Difference in bin "<<i<<" for the JEC-No JEC is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleUp->"<<contentup<<" scaleDown->"<<contentdown<<" and central value "<<content<<endl;
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
  legend_1->AddEntry (hnew, "Efficiency systematic uncertanties", "F");
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

  cout<<"Saving Efficiency Jet Multiplicity systematics in a file"<<endl;
  string filename=txtPath+"systematicsEffJetMultiplicity"+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }

  TCanvas *ratio= new TCanvas ("ratio", "ratio", 1000, 700);
  ratio->cd();
  string title="Efficiency systematics Jet Multiplicity";
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
  
  stringsystPU=stringsyst+"/EffJetMultiplicity.pdf";
  c1->Print(stringsystPU.c_str()); 
  return systs;
}

//*****************************************************************************************
//*****************************************************************************************
//*****************************************************************************************
///////////////////////////
//   JEC For N JET 
//////////////////////////

void DotheSystematicsJEC(int whichjet, string var){
  
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

  string pathFile;
  if (!isMu) pathFile="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011"+version+".root";
  else pathFile="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011Mu"+versionMu+".root";

  TFile *f = TFile::Open(pathFile.c_str());
  f->cd("validationJECScaleDown"); //wrong one!!! need to have the dir. w/o JEC
  
  TH1F *DownJEC;

  string namePlot;
  namePlot="h_jet"+var+"Njet"+namejet2;

  DownJEC= (TH1F*)gDirectory->Get(namePlot.c_str());  
  f->cd("validationJEC/");

  TH1F *JEC;
  JEC= (TH1F*)gDirectory->Get(namePlot.c_str());

  TH1F *hnew = (TH1F*)JEC->Clone("hnew");

  f->cd("validationJECScaleUp");

  TH1F *UpJEC;
  UpJEC= (TH1F*)gDirectory->Get(namePlot.c_str());

  if (useRebin && var=="Eta"){
     int rebin=1;
     if (whichjet==1) rebin=2;
     if (whichjet==2) rebin=2;
     if (whichjet==3) rebin=3;
     if (whichjet==4) rebin=4;
     JEC->Rebin(rebin);
     DownJEC->Rebin(rebin);
     UpJEC->Rebin(rebin);
     hnew->Rebin(rebin);
  }

  int numbbins=0;
  numbbins=JEC->GetNbinsX();

  for(int i=1; i<=numbbins; i++){		
    double contentdown = DownJEC->GetBinContent(i);
    double content = JEC->GetBinContent(i);
    double contentup = UpJEC->GetBinContent(i);
    systerr = max(fabs(contentdown - content),fabs(contentup-content));
    //if (content>0) cout<<"Difference in bin "<<i<<" for the JEC-No JEC is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleUp->"<<contentup<<" scaleDown->"<<contentdown<<" and central value "<<content<<endl;
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
  string axisTitle = var+" of Jets";
  JEC->GetXaxis()->SetTitle(axisTitle.c_str());
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
  axisTitle= "jet "+var;
  legend_1->AddEntry (JEC, axisTitle.c_str(), "L");
  axisTitle= "jet "+var+" + error";
  legend_1->AddEntry (UpJEC,axisTitle.c_str() , "L");
  axisTitle= "jet "+var+" - error";
  legend_1->AddEntry (DownJEC,axisTitle.c_str() , "L");
  legend_1->Draw ("same");

  cout<<"Saving Jet "<<var<<" JEC systematics in a file"<<endl;
  string filename=txtPath+"systematicsJECJet"+namejet2+var+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }

  TCanvas *ratio= new TCanvas ("ratio", "ratio", 1000, 700);
  ratio->cd();
  string title="JEC systematics "+namejet+" Jet "+var;
  if (var=="Pt") axisTitle = "Jet Pt [GeV]";
  if (var=="Ht") axisTitle = "Jet Ht [GeV]";
  if (var=="Eta") axisTitle = "Jet Eta";
  plotHistsAndRatio(DownJEC,UpJEC,JEC,title.c_str(),axisTitle.c_str(),"# Events"); 
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "Original Distribution", "L");
  legend_1->AddEntry (UpJEC, "Scale Up", "L");
  legend_1->AddEntry (DownJEC, "Scale Down", "L");
  legend_1->Draw ("same");
  
  stringsystPU=stringsyst+"/JECJet"+var+"_"+namejet2+".pdf";
  c1->Print(stringsystPU.c_str()); 
    
  return systs;
}


////////////////////////
///
///   PU for N JETS
///
/////////////////////////

std::vector<double> DotheSystematicsPU(int whichjet, string var){
   
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
   
   string pathFile;
   if (!isMu) pathFile="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011Mu"+version+".root";
   else pathFile="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011Mu"+versionMu+".root";

   TFile *f = TFile::Open(pathFile.c_str());
   
   string namePlot;
   namePlot="h_jet"+var+"Njet"+namejet2;
   
   if (!isMu) f->cd("validationJECXSScaleDown"); //wrong one!!! need to have the dir. w/o JEC  
   else f->cd("validationJECMuXSScaleDown");
   TH1F *DownJEC;
   DownJEC= (TH1F*)gDirectory->Get(namePlot.c_str());
   
   if (!isMu) f->cd("validationJEC/");
   else f->cd("validationJECmu/");
   TH1F *JEC;
   JEC= (TH1F*)gDirectory->Get(namePlot.c_str());
   TH1F *hnew = (TH1F*)JEC->Clone("hnew");
   
   if (!isMu) f->cd("validationJECXSScaleUp");
   else f->cd("validationJECMuXSScaleUp");
   TH1F *UpJEC;
   UpJEC= (TH1F*)gDirectory->Get(namePlot.c_str());
   
   if (useRebin && var=="Eta"){
      int rebin=1; 
      if (whichjet==1) rebin=2;
      if (whichjet==2) rebin=2;
      if (whichjet==3) rebin=3;
      if (whichjet==4) rebin=4;
      JEC->Rebin(rebin);
      DownJEC->Rebin(rebin);
      UpJEC->Rebin(rebin);
      hnew->Rebin(rebin);
   }
   
   int numbbins=0;
   numbbins=JEC->GetNbinsX();
   
   for(int i=1; i<=numbbins; i++){		
      double contentdown = DownJEC->GetBinContent(i);
      double content = JEC->GetBinContent(i);
      double contentup = UpJEC->GetBinContent(i);
      systerr = max(fabs(contentdown - content),fabs(contentup-content));
      //if (content>0) cout<<"Difference in bin "<<i<<" for the PU is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleXSUp->"<<contentup<<" scaleXSDown->"<<contentdown<<" and central value "<<content<<endl;
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
   string axisTitle = var+" of Jets";
   JEC->GetXaxis()->SetTitle(axisTitle.c_str());
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
   axixTitle = "jet "+var;
   legend_1->AddEntry (JEC, axixTitle.c_str(), "L");
   axixTitle = "jet "+var+" + error";
   legend_1->AddEntry (UpJEC, axixTitle.c_str(), "L");
   axixTitle = "jet "+var+" - error";
   legend_1->AddEntry (DownJEC, axixTitle.c_str(), "L");
   legend_1->Draw ("same");
   
   cout<<"Saving "<<var<<" PU systematics in a file"<<endl;
   string filename=txtPath+"systematicsPUJet"+namejet2+var+version+".txt";
   ofstream syste;
   syste.open(filename.c_str());
   for (int i=0;i<systs.size();i++){
      syste<<systs[i]<<endl;
   }
   
   TCanvas *ratio= new TCanvas ("ratio", "ratio", 1000, 700);
   ratio->cd();
   string title="Pile-Up systematics "+namejet+" Jet "+var;
   if (var=="Pt") axixTitle = "Jet Pt [GeV]";
   if (var=="Ht") axixTitle = "Jet Ht [GeV]";
   if (var=="Eta") axixTitle = "Jet Eta";
   plotHistsAndRatio(DownJEC,UpJEC,JEC,title.c_str(),axixTitle.c_str(),"# Events"); 
   TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
   legend_1->SetFillColor (0);
   legend_1->SetFillStyle (0);
   legend_1->SetBorderSize (0);
   legend_1->SetTextFont(62);
   legend_1->AddEntry (JEC, "Original Distribution", "L");
   legend_1->AddEntry (UpJEC, "Scale Up", "L");
   legend_1->AddEntry (DownJEC, "Scale Down", "L");
   legend_1->Draw ("same");
   
   stringsystPU=stringsyst+"/PU_Jet"+namejet2+var+".pdf";
   c1->Print(stringsystPU.c_str()); 
   
   return systs;
}

///////////////////////
///
/// syst Unfolding Method
///
////////////////////////

void DotheSystematicsUnfMethod(int whichjet, string var){
  
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

  string namePlot;
  string var2="";
  if (var == "Eta") var2 ="eta";
  if (whichjet==1) namePlot = "jReco_leading"+var2;
  if (whichjet==2) namePlot = "jReco_subleading"+var2;
  if (whichjet==3) namePlot = "jReco_subsubleading"+var2;
  if (whichjet==4) namePlot = "jReco_subsubsubleading"+var2;
  if (var == "Ht"){
     if (whichjet==1) namePlot = "HReco_leading";
     if (whichjet==2) namePlot = "HReco_subleading";
     if (whichjet==3) namePlot = "HReco_subsubleading";
     if (whichjet==4) namePlot = "HReco_subsubsubleading";
  }

   //string pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions"+version+".root";
  string pathFile;
  //if (!isMu) pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_30SVD.root";
  if (!isMu) pathFile="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributions_v2_33SVDDamiana.root";
  else pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsHTMu_v2_30.root";
   TFile *f = TFile::Open(pathFile.c_str());

  f->cd(); //wrong one!!! need to have the dir. w/o JEC
  TH1F *MD;
  MD = (TH1F*)gDirectory->Get(namePlot.c_str());

  string UnfMethod;
  TFile *f2;
  //if (!kparsystematics) UnfMethod="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsBayes"+version+".root";
  if (!kparsystematics) {
     //if (!isMu) UnfMethod="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_30Bayes.root";
     if (!isMu) UnfMethod="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributions_v2_33BayesDamiana.root";
     else UnfMethod="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsHTMuBayes_v2_30.root";}
  else UnfMethod="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions"+version+"Kmoved.root";
  cout<<UnfMethod<<endl;
  f2 = TFile::Open(UnfMethod.c_str());
    
  f2->cd(); //wrong one!!! need to have the dir. w/o JEC
  TH1F *P;
  P = (TH1F*)gDirectory->Get(namePlot.c_str());   

  for(int i=1; i<=MD->GetNbinsX(); i++){	
     double content = MD->GetBinContent(i);
     double contentup = P->GetBinContent(i);
     systerr = fabs(contentup-content);
     systs.push_back(fabs(systerr/content));
  }

  cout<<"Saving Unfolding Method for Jet "<<var<<" - systematics in a file"<<endl;
  string filename=txtPath+"systematicsUnfMethod_Jet"+namejet2+var+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }

  TCanvas *d = new TCanvas ("d", "d", 1000, 700);
  d->cd ();
 
  string title;
  if (!kparsystematics) title="Unfolding Method Systematics "+namejet+" Jet "+var;
  else title="Unfolding K Parameter Systematics "+namejet+" Jet "+var;
  string axisTitle;
  if (var=="Pt") axisTitle = "Jet Pt [GeV]";
  if (var=="Ht") axisTitle = "Jet Ht [GeV]";
  if (var=="Eta") axisTitle = "Jet Eta";
  plotHistsAndRatio(MD,P,title.c_str(),axisTitle.c_str(),"# Events"); 
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (MD, "SVD Method", "L");
  legend_1->AddEntry (P, "Bayes Method", "L");
  legend_1->Draw ("same");

  if (!kparsystematics) stringsystPU=stringsyst+"/UnfoldingMethod_Jet"+namejet2+var+".pdf";
  else stringsystPU=stringsyst+"/UnfoldingKParam_Jet"+namejet2+var+".pdf";
  c1->Print(stringsystPU.c_str()); 
 
}

///////////////////////////
//   Efficinecy For N JET 
//////////////////////////

void DotheSystematicsEfficiency(int whichjet, string var){
  
  setTDRStyle();

 string namejet="";
 string namejet2="";
 if (whichjet==1) {namejet="Leading"; namejet2 = "1";}
 if (whichjet==2) {namejet="Second leading"; namejet2 = "2";}
 if (whichjet==3) {namejet="Third leading"; namejet2 = "3";}
 if (whichjet==4) {namejet="Fourth leading"; namejet2 = "4";}

  string namePlot;
  string var2="";
  if (var == "Eta") var2 ="eta";
  if (whichjet==1) namePlot = "jReco_leading"+var2;
  if (whichjet==2) namePlot = "jReco_subleading"+var2;
  if (whichjet==3) namePlot = "jReco_subsubleading"+var2;
  if (whichjet==4) namePlot = "jReco_subsubsubleading"+var2;
  if (var == "Ht"){
     if (whichjet==1) namePlot = "HReco_leading";
     if (whichjet==2) namePlot = "HReco_subleading";
     if (whichjet==3) namePlot = "HReco_subsubleading";
     if (whichjet==4) namePlot = "HReco_subsubsubleading";
  }
 
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

string pathFile, pathFileUp, pathFileDown;
  if (!isMu) {
     pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyReference"+version+".root";
     pathFileUp="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyScaleUp"+version+".root";
     pathFileDown="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyScaleDown"+version+".root";
  } else {
     pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyReference_Mu"+versionMu+".root";
     pathFileUp="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyScaleUp_Mu"+versionMu+".root";
     pathFileDown="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsEfficiencyScaleDown_Mu"+versionMu+".root";
  }

  TFile *fD = TFile::Open(pathFileDown.c_str());
  fD->cd(); //wrong one!!! need to have the dir. w/o JEC 
  TH1F *DownJEC = (TH1F*)gDirectory->Get(namePlot.c_str());
  
  TFile *f = TFile::Open(pathFile.c_str());
  f->cd();
  TH1F *JEC = (TH1F*)gDirectory->Get(namePlot.c_str());
  TH1F *hnew = (TH1F*)JEC->Clone("hnew");
  
  TFile *fU = TFile::Open(pathFileUp.c_str());
  fU->cd();
  TH1F *UpJEC = (TH1F*)gDirectory->Get(namePlot.c_str());

  if (useRebin && var=="Eta"){
     int rebin=1;
     if (whichjet==1) rebin=2;
     if (whichjet==2) rebin=2;
     if (whichjet==3) rebin=3;
     if (whichjet==4) rebin=4;
     JEC->Rebin(rebin);
     DownJEC->Rebin(rebin);
     UpJEC->Rebin(rebin);
     hnew->Rebin(rebin);
  }

  int numbbins=0;
  numbbins=JEC->GetNbinsX();

  for(int i=1; i<=numbbins; i++){		
    double contentdown = DownJEC->GetBinContent(i);
    double content = JEC->GetBinContent(i);
    double contentup = UpJEC->GetBinContent(i);
    systerr = max(fabs(contentdown - content),fabs(contentup-content));
    //if (content>0) cout<<"Difference in bin "<<i<<" for the JEC-No JEC is "<<systerr<<" ("<<100*systerr/content<<"%)"<<" scaleUp->"<<contentup<<" scaleDown->"<<contentdown<<" and central value "<<content<<endl;
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
  string axisTitle = var+" of Jets";
  JEC->GetXaxis()->SetTitle(axisTitle.c_str());
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
  legend_1->AddEntry (hnew, "Efficiency systematic uncertanties", "F");
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
  axisTitle= "jet "+var;
  legend_1->AddEntry (JEC, axisTitle.c_str(), "L");
  axisTitle= "jet "+var+" + error";
  legend_1->AddEntry (UpJEC,axisTitle.c_str() , "L");
  axisTitle= "jet "+var+" - error";
  legend_1->AddEntry (DownJEC,axisTitle.c_str() , "L");
  legend_1->Draw ("same");

  cout<<"Saving Jet "<<var<<" Efficiency systematics in a file"<<endl;
  string filename=txtPath+"systematicsEffJet"+namejet2+var+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }

  TCanvas *ratio= new TCanvas ("ratio", "ratio", 1000, 700);
  ratio->cd();
  string title="Efficiency systematics "+namejet+" Jet "+var;
  if (var=="Pt") axisTitle = "Jet Pt [GeV]";
  if (var=="Ht") axisTitle = "Jet Ht [GeV]";
  if (var=="Eta") axisTitle = "Jet Eta";
  plotHistsAndRatio(DownJEC,UpJEC,JEC,title.c_str(),axisTitle.c_str(),"# Events"); 
  TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
  legend_1->SetFillColor (0);
  legend_1->SetFillStyle (0);
  legend_1->SetBorderSize (0);
  legend_1->SetTextFont(62);
  legend_1->AddEntry (JEC, "Original Distribution", "L");
  legend_1->AddEntry (UpJEC, "Scale Up", "L");
  legend_1->AddEntry (DownJEC, "Scale Down", "L");
  legend_1->Draw ("same");
  
  stringsystPU=stringsyst+"/EffJet"+var+"_"+namejet2+".pdf";
  c1->Print(stringsystPU.c_str()); 
    
  return systs;
}


////////////////
///// Systematcs for MD-Pythia in Unfolding...
///////////////


void DotheSystematicsUnfoldingPythia(int whichjet, string var){

   string namejet="";
   string namejet2="";
   if (whichjet==1) {namejet="Leading Jet "; namejet2 = "1";}
   if (whichjet==2) {namejet="Second leading Jet "; namejet2 = "2";}
   if (whichjet==3) {namejet="Third leading Jet "; namejet2 = "3";}
   if (whichjet==4) {namejet="Fourth leading Jet "; namejet2 = "4";}
  
  setTDRStyle();
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  string axisTitle;
  string namePlot;
  string var2="";
  if (var == "Ht"){
     if (whichjet==1) namePlot = "HReco_leading";
     if (whichjet==2) namePlot = "HReco_subleading";
     if (whichjet==3) namePlot = "HReco_subsubleading";
     if (whichjet==4) namePlot = "HReco_subsubsubleading";
  }
  if (var == "Eta") var2 ="eta";
  if (whichjet==1) namePlot = "jReco_leading"+var2;
  if (whichjet==2) namePlot = "jReco_subleading"+var2;
  if (whichjet==3) namePlot = "jReco_subsubleading"+var2;
  if (whichjet==4) namePlot = "jReco_subsubsubleading"+var2;

  string path1="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions"+version+".root";
  TFile *f = TFile::Open(path1.c_str());
  f->cd(); //wrong one!!! need to have the dir. w/o JEC
 
  TH1F *MD;
  MD = (TH1F*)gDirectory->Get(namePlot.c_str());

  string path2="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributionsPythia"+version+".root";
  TFile *f2 = TFile::Open(path2.c_str());
  f2->cd(); //wrong one!!! need to have the dir. w/o JEC
  TH1F *P;  
  P = (TH1F*)gDirectory->Get(namePlot.c_str());    

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
  axisTitle = namejet+var;
  MD->GetXaxis()->SetTitle(axisTitle.c_str());
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

  cout<<"Saving "<<var<<" Pythia MD- systematics in a file"<<endl;
  string filename=txtPath+"systematicsPythiaMDJet"+namejet2+var+version+".txt";
  ofstream syste;
  syste.open(filename.c_str());
  for (int i=0;i<systs.size();i++){
    syste<<systs[i]<<endl;
  }
  

  stringsystPU=stringsyst+"/MDPythia_Jet"+namejet2+var+".pdf";
  d->Print(stringsystPU.c_str()); 
}
