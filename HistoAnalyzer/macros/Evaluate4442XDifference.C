#include "tdrStyle.C"
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TLegend.h"
#include "TPaveStats.h"

TCanvas a;
TH1D* h_itEB_data44;
TH1D* h_itEB_data42;

void Evaluate4442XDifference(){
  //Settings
  setTDRStyle();
  gPad->SetLogy (1);
  //44X File
  TFile *CMSSW44 = TFile::Open("rfio:/gpfs/cms/data/2011/jet/jetValidation_DATA_2011A_v2_10.root"); 
  TDirectory *dir=(TDirectory*)CMSSW44->Get("validationJEC");
  TTree *treeVJ44 = (TTree*)dir->Get("treeVJ_");

  //42X File
  TFile *CMSSW42 = TFile::Open("rfio:/gpfs/cms/data/2011/jet/jetValidation_DATA_2011A_v1_10.root"); 
  TDirectory *dir2=(TDirectory*)CMSSW42->Get("validationJEC");
  TTree *treeVJ42 = (TTree*)dir2->Get("treeVJ_");  

  //Numero di entries
  Int_t entries44 = treeVJ44->GetEntries();
  printf("Useful data44:\ndata entries= %d \n",entries44);
  Int_t entries42 = treeVJ42->GetEntries();
  printf("Useful data42:\ndata entries= %d \n",entries42);  

  h_itEB_data44 = new TH1D("h_itEB_data44","IsoTrk Barrel Distribution",40,0.,0.40);
  h_itEB_data42 = new TH1D("h_itEB_data42","IsoTrk Barrel Distribution",40,0.,0.40);
  h_itEB_data42->SetLineColor(kRed);
  h_itEB_data44->SetMarkerSize(.8);
  h_itEB_data42->SetMarkerSize(.8);
  h_itEB_data42->SetMarkerColor(kRed);

  treeVJ44->Draw("IsoTrkEB>>h_itEB_data44");
  treeVJ42->Draw("IsoTrkEB>>h_itEB_data42");

  a.cd();
  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
  pad1->Draw();
  pad1->cd();
  pad1->SetLogy(1);
  h_itEB_data44->Draw();
  h_itEB_data42->Scale((double)entries44/(double)entries42);
  h_itEB_data42->SetLineColor(kRed);
  h_itEB_data42->Draw("SAMES");

  pad1->Update();
  TPaveStats *r2 = (TPaveStats*) h_itEB_data42->FindObject("stats"); 
  r2->SetY1NDC(0.878); 
  r2->SetY2NDC(0.75); 
  r2->SetTextColor(kRed);
  r2->Draw();
  pad1->Update();

  TLegend *leg = new TLegend(0.4,0.75,0.8,0.9);
  leg->SetBorderSize(0);
  leg->SetEntrySeparation(0.01);
  leg->SetFillColor(0);
  leg->AddEntry(h_itEB_data44,"CMSSW_4_2_4","p");
  leg->AddEntry(h_itEB_data42,"CMSSW_4_4_2","p");
  leg->Draw();

  a.cd();
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
  pad2->Draw();
  pad2->cd();
  TH1D *ratio = (TH1D*) h_itEB_data44->Clone();
  ratio->SetTitle("ratio");
  ratio->SetName("ratio");
  ratio->Reset();
  
  ratio->Sumw2();
  h_itEB_data44->Sumw2();
  h_itEB_data42->Sumw2(); 
  ratio->SetMarkerSize(.5);
  ratio->SetLineColor(kBlack);
  ratio->SetMarkerColor(kBlack);
  ratio->SetMarkerSize(.5);
  ratio->SetMarkerStyle(3);
  ratio->Divide( h_itEB_data44, h_itEB_data42,1.,1.);
  ratio->GetYaxis()->SetRangeUser(0,2);   
  pad2->SetTopMargin(1);
  ratio->Draw("E1");
  
  TLine *OLine = new TLine(ratio->GetXaxis()->GetXmin(),1.,ratio->GetXaxis()->GetXmax(),1.);
  OLine->SetLineColor(kBlack);
  OLine->SetLineStyle(2);
  OLine->Draw();
  
  return;  
}
