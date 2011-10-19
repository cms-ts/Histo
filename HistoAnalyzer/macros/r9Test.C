#include "MMutil.C"
#include "tdrstyle.C"
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"

void r9Test(){

  // Filling plots, opening files, stuff like that...

  TFile *_fileg93 = TFile::Open("file:/gpfs/cms/data/2011/r9test/g93_zfilt.root");
  _fileg93->cd("demo");
  TH1D *g93= new TH1D("g93","g93",28,0,0.07);
  treeVJ_->Draw("IsoEcalEB_PUR>>g93","","goff");
  //TFile *_fileg94 = TFile::Open("../test/G94testnozfilt/res/g94.root");
  //_fileg94->cd("demo");
  //TH1D *g94= new TH1D("g94","g94",28,0,0.07);
  //treeVJ_->Draw("IsoEcalEB_PUR>>g94","","goff");
  TFile *_filegp2 = TFile::Open("file:/gpfs/cms/data/2011/r9test/p2_zfilt.root");
  _filegp2->cd("demo");
  TH1D *p2= new TH1D("p2","p2",28,0,0.07);
  treeVJ_->Draw("IsoEcalEB_PUR>>p2","","goff");
  //g94->SetLineColor(kRed);
  //g94->SetMarkerColor(kRed);
  //g94->SetMarkerSize(.5);
  //g94->Draw("E1");

  TCanvas *c1 = new TCanvas("c1","ratio GEANT",600,700);
  setTDRStyle();
  g93->SetLineColor(kBlue);
  g93->SetMarkerColor(kBlue);
  g93->SetMarkerSize(.5);
  p2->SetLineColor(kBlack);
  p2->SetMarkerColor(kBlack);
  p2->SetMarkerSize(.5);
  p2->SetMarkerStyle(3);
  g93->SetMarkerStyle(3);
  TLegend* legend_d = new TLegend(0.626506,0.19494,0.916667,0.447917);
  legend_d->SetFillColor(0);
  legend_d->SetFillStyle(0);
  legend_d->SetBorderSize(0);
  legend_d->AddEntry(g93,"g93","LE");
  //legend_d->AddEntry(g94,"g94","LE");
  legend_d->AddEntry(p2,"patch2","LE");
  //Plot the first canvas and pad
  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
  pad1->SetBottomMargin(1);
  pad1->Draw();
  pad1->cd();
  g93->Draw("E1");
  p2->Draw("E1SAME");
  legend_d->Draw("same");

  c1->cd();
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
  TH1D *ratiog= new TH1D("ratiog","ratiog",28,0,0.07);
  ratiog->Sumw2();
  g93->Sumw2();
  p2->Sumw2();
  ratiog->SetMarkerSize(.5);
  ratiog->SetLineColor(kRed);
  ratiog->SetMarkerColor(kRed);
  ratiog->SetMarkerSize(.5);
  ratiog->SetMarkerStyle(3);
  ratiog->Divide(g93,p2,1.,1.);
  pad2->SetTopMargin(1);
  pad2->Draw();
  pad2->cd();
  ratiog->Draw("E1");
  TF1 *myfit = new TF1("myfit","1", 0, 0.07);
  myfit->SetLineColor(kBlack);
  myfit->Draw("SAMES");

  ///// Other canvas
  TCanvas *c2 = new TCanvas("c2","ratio GEANT",600,700);
  c2->cd();
  setTDRStyle();
  TFile *_fileg93 = TFile::Open("/gpfs/cms/data/2011/r9test/pythiaD6Ttunesroot/D6T_zfilt.root");
  _fileg93->cd("demo");
  TH1D *g93= new TH1D("g93","g93",28,0,0.07);
  treeVJ_->Draw("IsoEcalEB_PUR>>g93");
  TFile *_fileg94 = TFile::Open("/gpfs/cms/data/2011/r9test/pythiaZ2tunesroot/Z2_zfilt.root");
  _fileg94->cd("demo");
  TH1D *g94= new TH1D("g94","g94",28,0,0.07);
  treeVJ_->Draw("IsoEcalEB_PUR>>g94");
  g94->Sumw2();
  g93->Sumw2();
  g94->SetLineColor(kRed);
  g94->SetMarkerColor(kRed);
  g94->SetMarkerSize(.5);
  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
  pad1->SetBottomMargin(1);
  pad1->Draw();
  pad1->cd();
  g94->Draw("E1");
  g93->SetLineColor(kBlue);
  g93->SetMarkerColor(kBlue);
  g93->SetMarkerSize(.5);
  double ratio=(double)g94->GetEntries()/(double)g93->GetEntries();
  cout<<ratio;
  cout<<"IF YOU READ TIHS LINE THE MANUAL RATIO IS ON...."<<endl;
  ratio=112919./178795;
  g93->Scale(ratio);
  g93->Draw("E1SAMES");
  TLegend* legend_d = new TLegend(0.626506,0.19494,0.916667,0.447917);
  legend_d->SetFillColor(0);
  legend_d->SetFillStyle(0);
  legend_d->SetBorderSize(0);
  legend_d->AddEntry(g93,"PythiaD6T","LE");
  legend_d->AddEntry(g94,"PythiaZ2","LE");
  legend_d->Draw("same");
  c2->cd();
  
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
  TH1D *ratiot= new TH1D("ratiot","ratiot",28,0,0.07);
  ratiot->Sumw2();
  ratiot->SetMarkerSize(.5);
  ratiot->SetMarkerColor(kRed);
  ratiot->Divide(g93,g94,1,1);
  pad2->SetTopMargin(1);
  pad2->Draw();
  pad2->cd();
  ratiot->Draw("E1");
  ratiot->SetLineColor(kRed);
  TF1 *myfit = new TF1("myfit","1", 0, 0.07);
  myfit->SetLineColor(kBlack);
  myfit->Draw("SAMES");

  TFile f3("corrections.root","UPDATE");
  f3.cd();
  //TH1D *correctionFactors= new TH1D("correctionFactors","correctionFactors",28,0,0.07);
  //correctionFactors=MH1clone("correctionFactors", "correctionFactors", ratiog);  
  ratiog->Multiply(ratiot);
  ratiog->Write();
  return;

  
}
