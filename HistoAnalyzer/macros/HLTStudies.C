#define HLTStudies_cxx
#include "HLTStudies.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "string.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "TMath.h"
#include "TLegend.h"
#include "tdrstyle.C"

TCanvas *a;
std::vector<TH1D*> vec;

void HLTStudies::Loop()
{
  setTDRStyle();
   if (fChain == 0) return;

   string paths[10000];
   double pres[10000];

   for (int k=0; k<10000; k++){
   paths[k]="";
   pres[k]=0.0;     
   }
   

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int numberofmatched=0;
   int run=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     nb = fChain->GetEntry(jentry);   //nbytes += nb;
     //cout<<nb<<endl;
     if (run!=Run){
     cout<<jentry<<" "<<nentries<<" Run="<<Run<<endl;
       run=Run;
       //cout<<"EVENT SIZE "<<HLTPaths->size()<<endl;     
       for (unsigned int i=0;i<HLTPaths->size();i++){
	 string Path=(string)HLTPaths->at(i);
	 TString stringa=Path;
	 if (stringa.Contains("Ele") || stringa.Contains("Photon")){
	 //cout<<"i "<<i<<endl;
	 //int prescale=(int)HLTPrescales->at(i);
	 bool present=false;
	 int indexmatched=0;
	 if (numberofmatched==0) {
	   //cout<<Path<<" Matched"<<endl;
	   
	 }
	 for (int j=0;j<numberofmatched;j++){
	   //cout<<Path<<" --- "<<paths[j]<<" j-->"<<j<<" # of matched "<<numberofmatched<<endl; 
	   if(Path==paths[j]) {
	     present=true;
	     indexmatched=j;
	     //cout<<"Matched:"<<Path<<" "<<indexmatched<<endl;
	   }
	 }
	 if (!present) {
	   paths[numberofmatched]=Path;
	   //pres[numberofmatched]=1;
	   numberofmatched++;
	 }
	 if (present) {
	   pres[indexmatched]= pres[indexmatched]+1;
	   //cout<<" --> "<<pres[indexmatched]<<endl;
	 } 
	 }
       }
     }  
   }
   
   cout<<"------------"<<endl;
   //Sorting the matrix
   Int_t *sorted = new Int_t[numberofmatched];
   Int_t *values = new Int_t[numberofmatched];

    for (Int_t i=0; i<numberofmatched; ++i ) {
        values[i] = pres[i];
    }

    // array sorted now has the indices of the highest ET electrons
    TMath::Sort(numberofmatched, values, sorted, true);

   for (int i=0;i<numberofmatched;i++){
     cout<<"Path "<<paths[i]<<" count "<<pres[i]<<endl;
   }

   cout<<"------------Top 15 HLT paths"<<endl;

   for (int i=0;i<9;i++){
     cout<<"Path "<<paths[sorted[i]]<<" count "<<pres[sorted[i]]<<endl;
   }

   TFile *dataf = TFile::Open("histo.root"); //data file
   
   TDirectory *dir=(TDirectory*)dataf->Get("demo");
   TTree *treeVJ_ = (TTree*)dir->Get("treeVJ_");  
 
   string cut="HLTPaths.c_str()==\""+paths[sorted[1]]+"\"";//+" && numberOfVertices==5";
   cout<<cut<<endl;

   //DATA: scrive gli istogrammi tagliati al numero di verici
   
   dataf->cd("demo");
   
   //EB data
   
   //   TH1D *h_ieEB_data = new TH1D("h_ieEB_data","IsoEcal EB",20,0.,0.2);
   //treeVJ_->Draw("IsoEcalEB>>h_ieEB_data",cut.c_str(),"goff");
   //h_ieEB_data->Draw();
   int maximum=0;

   TLegend *leg = new TLegend(0.5,0.6,0.8,0.89);
   TH1D *ref = new TH1D("ref","MC reference",20,0.,0.2);
   treeVJ_->Draw("IsoTrkEB>>ref");//"numberOfVertices==5");
   vec.push_back(ref);
   leg->AddEntry(ref,"Entire Distribution","l");

   for(int j=0;j<numberofmatched;j++){
     TH1D *h_ieEB_data = new TH1D("h_ieEB_data","IsoTrk EB",20,0.,0.2);
     treeVJ_->Draw("IsoTrkEB>>h_ieEB_data",cut.c_str(),"SAMES");
     cut="HLTPaths.data()==\""+paths[sorted[j]]+"\"";//+" && numberOfVertices==5";
     int dim=treeVJ_->Draw("IsoTrkEB",cut.c_str(),"goff"); 
     if (dim>0 && dim>0.001*pres[sorted[0]]){
       cout<<cut<<" has entries... "<<dim<<endl;
       treeVJ_->Draw("IsoTrkEB>>h_ieEB_data",cut.c_str(),"SAMES");
       int max=h_ieEB_data->GetMaximum();
       if (max>maximum) maximum=max;
       vec.push_back(h_ieEB_data);
       leg->AddEntry(h_ieEB_data,paths[sorted[j]].c_str(),"l");
     }
   }

   a=new TCanvas("a","a",10,10,600,600);

   for (int i=0;i<vec.size();i++){
     cout<<i<<endl;
     vec[i]->SetLineColor(i+1); 
    if (i==0) {
      //ref->Draw();
      vec[i]->GetYaxis()->SetRangeUser(1,vec[i]->GetMaximum());
      vec[i]->Draw();
     } 
     else vec[i]->Draw("SAMES");
   }
   leg->SetBorderSize(0);
   leg->SetFillColor(0);
   leg->Draw();

   //Save .root of this
   TFile f2("file2.root","RECREATE");
   f2.cd();
   for (int i=0; i<vec.size();i++){
     vec[i]->Write();
   }
   f2.Write();
}
