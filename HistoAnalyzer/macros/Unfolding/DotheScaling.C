/**********************************
 * Berends-Giele Scaling          *
 *                                *
 * Vieri Candelise January  2012  *
 **********************************
 *********************************/

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
#include "TGraph.h"

void DotheScaling(){

  //Save plots here
  string direc = "/afs/infn.it/ts/user/marone/html/ZJets/ScalingBG/";
  
  //be sure default is Minuit since we will use gMinuit 
  TVirtualFitter::SetDefaultFitter("Minuit");

  using
    std::cout;
  using
    std::endl;

  gROOT->SetStyle("Plain");
  //gROOT->ForceStyle();
  //gROOT->LoadMacro("tdrStyle.C++");
  //tdrStyle();
 
  const int maxNJets=7; 

  TH1D *h2 = new TH1D ("N", "N", maxNJets-2, 0.5, maxNJets-1.5);
  TH1D *h3 = new TH1D ("N", "N", maxNJets-2, 0.5, maxNJets-1.5);
  h2->Sumw2();

  TFile *eff = TFile::Open("/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_17pf.root");

  TH1F *h1 = (TH1F*)gDirectory->Get("JetMultiplicityUnfolded");

  int counter = 1;
  const int loop = maxNJets-1;
  double content[loop];
  double content2[loop];

  ///////////
  //Reset the histo
  ///////////

  for(int i=0; i<loop; i++){
    content[i]=0;
    content2[i]=0;
  }

  ///////////
  // Caclculate ratio and errors
  ///////////

  for(int i=1; i<=loop; i++){
    for (unsigned int j=counter;j<=loop;j++){
      if (j != counter) content[i-1]  += JetMultiplicityUnfolded->GetBinContent(j);
      content2[i-1] += JetMultiplicityUnfolded->GetBinContent(j);
      cout<<"bin "<<j<<" has entries "<<JetMultiplicityUnfolded->GetBinContent(j)<<"; numerator is "<<content[i-1]<<" while denominator is "<<content2[i-1]<<endl;
    }
    cout<<"ratio "<<i<<" is "<<content[i-1]/content2[i-1]<<endl;
    counter++;
    cout<<endl;
  }	

  //////////
  // Fill the histogram properly
  //////////

  for(int i=1; i<loop; i++){
    double err1 = sqrt (JetMultiplicityUnfolded->GetBinContent(i)); // to have the sqrt(N) error, since it has been scaled
    if (i>0) double err2 = sqrt(JetMultiplicityUnfolded->GetBinContent(i-1));
    double z = content[i-1]/content2[i-1];
    double err= sqrt(-(content[i]*content[i])*err2*err2*(1/(content2[i]*content2[i]*content2[i]*content2[i]))+ (1/(content2[i]*content2[i]))*err1*err1);
    cout<<"For bin "<<i<<" err1 is "<<err1<<" while err2 is "<<err2<<" -> propagated:"<<err<<endl;
    h2->SetBinContent(i, z);
    h2->SetBinError(i, err);
  }

  TCanvas * Canv = new TCanvas("Canv","Canv",0,0,800,600);
  Canv->cd();
  h2->GetYaxis()->SetRangeUser(0., 0.4);
  h2->SetMarkerStyle(20);
  h2->SetMarkerColor(kRed);
  h2->GetXaxis()->SetTitle("N_{Jets}");
  h2->GetYaxis()->SetTitle("#sigma(Z + #geq N_{Jets}) / #sigma(Z + #geq (N-1)_{Jets})");
  h2->GetYaxis()->SetTitleSize(0.03);
  h2->GetYaxis()->SetTitleOffset(1.53);

  h2->Draw("E1");

  TLegend* lumi = new TLegend(0.067,0.659,0.448,0.858);
  lumi->SetFillColor(0);
  lumi->SetFillStyle(0);
  lumi->SetBorderSize(0);
  lumi->SetTextAlign(12);
  lumi->SetTextSize(0.0244);
  lumi->SetTextFont(42);
  lumi->AddEntry((TObject*)0,"#int L dt = 4.907 fb^{-1}","");
  lumi->AddEntry((TObject*)1,"anti-k_{T} jets R=0.5","");
  lumi->AddEntry((TObject*)2,"p^{jet}_{T} #geq 30 GeV/c","");

  //Fit the plateau: only > 1 are considered for BG scaling 
  TF1 *fitBG=new TF1("fitBG","[0]+[1]*x",2.,5.);
  fitBG->SetRange(1.5,5.5);
  h2->Fit(fitBG,"R");
  h2->Draw();
  double a=fitBG->GetParameter(0);
  double beta=fitBG->GetParameter(1);
  lumi->Draw();
  string path=direc+"BGScaling.png";
  Canv->Print(path.c_str());

  /////////////
  // Get Contour
  //////////////

  TCanvas *c2 = new TCanvas("c2","contours",10,10,800,800);
  //Draw the central point
  gMinuit->SetErrorDef(9);   //Get contour for parameter 0 versus parameter 1 for ERRDEF=3 -> 3 sigma, I guess (n^2->9)  
  TGraph *gr3 = (TGraph*)gMinuit->Contour(30,0,1);
  gr3->SetTitle("Berends-Giele Scaling, Contour Plot");
  gr3->SetFillColor(34);
  gr3->GetXaxis()->SetTitle("a");
  gr3->GetYaxis()->SetTitle("#beta");
  gr3->Draw("alf");
  gMinuit->SetErrorDef(4); //note 4 and not 2!
  TGraph *gr2 = (TGraph*)gMinuit->Contour(30,0,1);
  gr2->SetFillColor(42);
  gr2->Draw("lf");
  gMinuit->SetErrorDef(1);
  TGraph *gr1 = (TGraph*)gMinuit->Contour(30,0,1);
  gr1->SetFillColor(38);
  gr1->Draw("lf");
  cout<<"Your central point in contour is->"<<a<<","<<beta<<endl;
  double x[1]={a};
  double y[1]={beta};
  TGraph *gr4 = new TGraph(1,x,y);
  //gr4->GetXaxis()->SetRangeUser(0.1,0.3);
  //gr4->GetYaxis()->SetRangeUser(0.1,-0.3);
  gr4->SetMarkerColor(kRed);
  gr4->SetMarkerStyle(25);
  gr4->Draw("p");
  TLegend* lab = new TLegend(0.616422,0.667314,0.996507,0.867012);
  lab->SetFillColor(0);
  lab->SetFillStyle(0);
  lab->SetBorderSize(0);
  lab->SetTextAlign(12);
  lab->SetTextSize(0.0244);
  lab->SetTextFont(42);
  lab->AddEntry(gr3,"3 sigma","pf");
  lab->AddEntry(gr2,"2 sigma","pf");
  lab->AddEntry(gr1,"1 sigma","pf");
  lab->AddEntry(gr4,"best fit","p");
  lab->Draw();
  path=direc+"BGContour.png";
  c2->Print(path.c_str());
}
