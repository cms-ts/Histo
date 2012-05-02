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


std::vector<double> DotheSystematics(){
  
  using	std::cout;
  using	std::endl;
  Double_t systerr;
  std::vector<double> systs;

  TFile *f = TFile::Open("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_21pf.root");
  f->cd("validationJECScaleDown"); //wrong one!!! need to have the dir. w/o JEC
  
  TH1F *DownJEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
  
  f->cd("validationJEC/");
  TH1F *JEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
  TH1F *hnew = (TH1F*)JEC->Clone("hnew");

   f->cd("validationJECScaleUp");
   TH1F *UpJEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");

  for(int i=1; i<=7; i++){		
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
  
  hnew->Draw("e2");
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

