#include "tdrStyle.C"
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TH2F.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "TObject.h"
#include <TROOT.h>

TH1D* h_itEB_data44;
TH1D* h_itEB_data42;

//Name
// Just Select your version that you wonna compare!! And the path in which you'll store it!!!!
//

TFile *CMSSW44 = TFile::Open("rfio:/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_24TP.root");
TFile *CMSSW42 = TFile::Open("rfio:/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_24wp90.root"); 
std::string plotpath ="/afs/infn.it/ts/user/marone/html/ZJets/WP90_80/"; //put here the path where you want the plots
std::string whichdirectory="validationJEC";
string name1="v24, WP80"; // Name on the Plot's Label
string name2="v24, WP90"; // Name on the Plot's Label

bool normalizeToEntries=false; //if true it will normalize to entries!

using namespace std;

void EvaluateDifferenceBetweenVersions(string plot, string directory);


void DrawDifferences(void){
  struct STestFunctor {
    bool operator()(TObject *aObj) {
      return true;
    }
  };

  for (unsigned int j=0; j<5; j++){
    
    if (j==1) whichdirectory="demo";
    if (j==2) whichdirectory="Selection";
    if (j==3) whichdirectory="goodEPair";
    if (j==4) whichdirectory="TAPwp80";


    CMSSW44->cd(whichdirectory.c_str());
    TDirectory *dir=gDirectory;
    TList *mylist=(TList*)dir->GetListOfKeys();
    TIter iter(mylist);     
    // Use TIter::Next() to get each TObject mom owns.
    TObject* tobj = 0;
    
    int i=0;
    while ( tobj = iter.Next() ) {
      gStyle->SetPadRightMargin(0.15);
      
      string name=tobj->GetName();
      TString temp = (TString)name;
      //if(temp.Contains("gsfPfSCEnVsEn")){
      int num=tobj->GetUniqueID();
      cout<<"num is "<<num<<endl;
      EvaluateDifferenceBetweenVersions(name,whichdirectory.c_str());
      //}
      i++;
      //if(i==1)break;
    }
  }
  
  
  return;
}


void EvaluateDifferenceBetweenVersions(string plot, string directory){
  TCanvas a;
  //Settings

  gPad->SetLogy (1);
  TH1F* obj44;
  TH1F* probe; 
  TH1F* obj42;

  //44X File
  CMSSW44->cd(whichdirectory.c_str());
  TObject *o44;
  TObject *o42;
  gDirectory->GetObject(plot.c_str(),o44);

  //42X File
  CMSSW42->cd(whichdirectory.c_str());
  gDirectory->GetObject(plot.c_str(),o42);

  obj44=(TH1F*)o44;
  obj42=(TH1F*)o42;
  
  if (probe = dynamic_cast<TH1F *>(obj44) ){
    if ( !(obj42) || !(obj44) ){
      cout<<"One of the two histograms were not available:"<<plot<<endl;
      return;
    }

  TString str=obj44->GetTitle();
  string name=obj44->GetTitle();


  //Numero di entries
  Int_t entries44 = obj44->GetEntries();
  printf("Useful data44:\ndata entries= %d \n",entries44);
  Int_t entries42 = obj42->GetEntries();
  printf("Useful data42:\ndata entries= %d \n",entries42);  

  if (normalizeToEntries) obj42->Scale((double)entries44/(double)entries42);

  if (str.Contains("jet") && !str.Contains("Num") && !str.Contains("Eta") && !str.Contains("Phi") && !str.Contains("eld") && !str.Contains("h_meanPtZVsNjet")) {
    int rebin=5;
    if (!entries42==0) obj42->Rebin(rebin);
    if (!entries44==0) obj44->Rebin(rebin);
  }

  obj42->SetLineColor(kRed);
  obj44->SetMarkerSize(15);
  obj42->SetMarkerSize(15);
  obj42->SetMarkerColor(kRed);

  a.cd();
  TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
  pad1->Draw();
  pad1->cd();
  gStyle->SetOptStat("emruo");
  pad1->SetLogy(1);
  obj44->Draw("E1");
  if (entries42==0) return;
  //obj42->Scale((double)entries44/(double)entries42);
  obj42->SetLineColor(kRed);
  obj42->Draw("E1 SAMES");

  pad1->Update();
  TPaveStats *r2 = (TPaveStats*) obj42->FindObject("stats"); 
  r2->SetY1NDC(0.82); 
  r2->SetY2NDC(0.65); 
  r2->SetTextColor(kRed);
  r2->Draw();
  pad1->Update();

  TLegend *leg = new TLegend(0.55,0.75,0.65,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(.03);
  leg->SetFillColor(0);
  leg->AddEntry(obj44,name1.c_str(),"l");
  leg->AddEntry(obj42,name2.c_str(),"l");
  leg->Draw();

  a.cd();

    TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
    pad2->Draw();
    pad2->cd();
    gStyle->SetOptStat("n");
    TH1D *ratio = (TH1D*) obj44->Clone();
    ratio->SetTitle("ratio");
    ratio->SetName("ratio");
    ratio->Reset();
  
    ratio->Sumw2();
    obj44->Sumw2();
    obj42->Sumw2(); 
    ratio->SetMarkerSize(.5);
    ratio->SetLineColor(kBlack);
    ratio->SetMarkerColor(kBlack);
    ratio->SetMarkerStyle(3);
    ratio->Divide( obj44, obj42,1.,1.);
    ratio->GetYaxis()->SetRangeUser(0,2);   
    pad2->SetTopMargin(1);
    ratio->Draw("E1");
    
    TLine *OLine = new TLine(ratio->GetXaxis()->GetXmin(),1.,ratio->GetXaxis()->GetXmax(),1.);
    OLine->SetLineColor(kBlack);
    OLine->SetLineStyle(2);
    OLine->Draw();
    string tmp=plotpath+"/"+directory+"/"+name+".pdf";
    a.Print(tmp.c_str());
    cout<<"Printing ->"<<tmp<<endl;
  
  }
  return;  
}
