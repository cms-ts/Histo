/**********************************
 * Get the efficiencies to correct plots
 * Matteo Marone
 **********************************
 *********************************/

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

///////////
//////// Efficiency using pt electron...
///////////

int getPtRangeElectron(double ele_pt){
  int x=0;
  if (ele_pt>=20 && ele_pt<30){
    x=1;
  }
  if (ele_pt>=30 && ele_pt<40){
    x=2;
  }
  if (ele_pt>=40 && ele_pt<50){
    x=3;
  }
  if (ele_pt>=50){
    x=4;
  }
  return x;
}

int getEtaRangeElectron(double ele_eta){
  int x=-1;
  if (fabs(ele_eta)>=0 && fabs(ele_eta)<0.8 ){
    x=1;
  }
  if (fabs(ele_eta)>=0.8 && fabs(ele_eta)<1.4442 ){
    x=2;
  }
  if (fabs(ele_eta)>=1.5666 && fabs(ele_eta)<2.0 ){
    x=3;
  }
  if (fabs(ele_eta)>=2.0 && fabs(ele_eta)<2.5 ){
    x=4;
  }
  return x;
}

double getEfficiencyElectronLovedeepEle(double pt ,double eta){
  //double matrix[6][5]={0.349,0.369,0.288,0.153,0.114,
  //                   0.556,0.467,0.312,0.285,0.383,
  //                   0.664,0.632,0.343,0.465,0.524,
  //                   0.802,0.758,0.515,0.585,0.616,
  //                   0.851,0.832,0.673,0.693,0.691,
  //                   0.862,0.855,0.692,0.743,0.738};

  double matrix[6][5]={
    0.418,0.502,0.664,0.343,0.363,
    0.620,0.608,0.485,0.506,0.559,
    0.775,0.765,0.559,0.688,0.684,
    0.858,0.858,0.723,0.787,0.749,
    0.981,0.903,0.834,0.845,0.798,
    0.896,0.908,0.854,0.863,0.816,
  };
  

  int idy=-1; int isoy=-1;

  if (eta<=0.8) {
    idy  =0;
  } else if (TMath::Abs(eta)>0.8 && TMath::Abs(eta)<=1.442) {   
    idy  =1;
  } else if (TMath::Abs(eta)>1.442 && TMath::Abs(eta)<=1.566) {
    idy  =2;
  } else if (TMath::Abs(eta)>1.566 && TMath::Abs(eta)<=2.0) {
    idy  =3;
  } else if (TMath::Abs(eta)>2.0 && TMath::Abs(eta)<=2.5) {
    idy =4;
  }

  if (pt<=15){
    isoy=0;
  } else if (pt > 15 && pt <=20){
    isoy=1;
  }
  else if (pt > 20 && pt <=30){
    isoy=2;
  }
  else if (pt > 30 && pt <=40){
    isoy=3;
  }
  else if (pt > 40 && pt <=50){
    isoy=4;
  }
  else if (pt > 50){
    isoy=5;
  }

  return matrix[isoy][idy];

}

double getEfficiencyMuonPOG(bool is2011A ,double muopt1 ,double muoeta1, double muopt2,double muoeta2){

  double muoIDrunA[15]={0.9111, 0.9429, 0.9661, 0.9398, 0.9639, 0.9789, 0.8731, 0.9665, 0.8643, 0.9777, 0.9616, 0.9334, 0.9614, 0.9499, 0.9164};
  
  double muoISOrunA[2][7]={
    0.8358, 0.9282, 0.9721, 0.9909, 0.9930, 0.9959, 0.9950,
    0.8418, 0.9433, 0.9777, 0.9930, 0.9957, 0.9957, 0.9943
  };
  double muoIDrunB[15]={0.8915, 0.8982, 0.9255, 0.9235, 0.9626, 0.9788, 0.8701, 0.9640, 0.8601, 0.9772, 0.9578, 0.9154, 0.9252, 0.9097, 0.8926};
  
  double muoISOrunB[2][7]={
    0.7800, 0.9052, 0.9614, 0.9860, 0.9923, 0.9922, 0.9985,
    0.7881, 0.9179, 0.9777, 0.9881, 0.9951, 0.9954, 0.9960
  };

  cout << "PORCO DIO: "  << muoIDrunA[8]<< endl;
  cout << "PORCO DIO: "  << muoISOrunA[1][3]<< endl;

  int muoId1=-1; int muoIso1=-1;
  int muoId2=-1; int muoIso2=-1;
  int highEta1=0; int highEta2=0;
  double efficiencyMuonPOG;

  if (muoeta1>1.2) highEta1=1;
  if (muoeta2>1.2) highEta2=1;

  if (muoeta1>=-2.4 && muoeta1<-2.1) muoId1=0;
  if (muoeta1>=-2.1 && muoeta1<-1.6) muoId1=1;
  if (muoeta1>=-1.6 && muoeta1<-1.2) muoId1=2;
  if (muoeta1>=-1.2 && muoeta1<-0.9) muoId1=3;
  if (muoeta1>=-0.9 && muoeta1<-0.6) muoId1=4;
  if (muoeta1>=-0.6 && muoeta1<-0.3) muoId1=5;
  if (muoeta1>=-0.3 && muoeta1<-0.2) muoId1=6;
  if (muoeta1>=-0.2 &&  muoeta1<0.2) muoId1=7;
  if (muoeta1>=0.2  &&  muoeta1<0.3) muoId1=8;
  if (muoeta1>=0.3  &&  muoeta1<0.6) muoId1=9;
  if (muoeta1>=0.6  &&  muoeta1<0.9) muoId1=10;
  if (muoeta1>=0.9  &&  muoeta1<1.2) muoId1=11;
  if (muoeta1>=1.2  &&  muoeta1<1.6) muoId1=12;
  if (muoeta1>=1.6  &&  muoeta1<2.1) muoId1=13;
  if (muoeta1>=2.1  &&  muoeta1<2.4) muoId1=14;

  if (muopt1>=10 && muopt1<20) muoIso1=0;
  if (muopt1>=20 && muopt1<30) muoIso1=1;
  if (muopt1>=30 && muopt1<40) muoIso1=2;
  if (muopt1>=40 && muopt1<50) muoIso1=3;
  if (muopt1>=50 && muopt1<60) muoIso1=4;
  if (muopt1>=60 && muopt1<80) muoIso1=5;
  if (muopt1>=80             ) muoIso1=6;

  if (muoeta2>=-2.4 && muoeta2<-2.1) muoId2=0;
  if (muoeta2>=-2.1 && muoeta2<-1.6) muoId2=1;
  if (muoeta2>=-1.6 && muoeta2<-1.2) muoId2=2;
  if (muoeta2>=-1.2 && muoeta2<-0.9) muoId2=3;
  if (muoeta2>=-0.9 && muoeta2<-0.6) muoId2=4;
  if (muoeta2>=-0.6 && muoeta2<-0.3) muoId2=5;
  if (muoeta2>=-0.3 && muoeta2<-0.2) muoId2=6;
  if (muoeta2>=-0.2 &&  muoeta2<0.2) muoId2=7;
  if (muoeta2>=0.2  &&  muoeta2<0.3) muoId2=8;
  if (muoeta2>=0.3  &&  muoeta2<0.6) muoId2=9;
  if (muoeta2>=0.6  &&  muoeta2<0.9) muoId2=10;
  if (muoeta2>=0.9  &&  muoeta2<1.2) muoId2=11;
  if (muoeta2>=1.2  &&  muoeta2<1.6) muoId2=12;
  if (muoeta2>=1.6  &&  muoeta2<2.1) muoId2=13;
  if (muoeta2>=2.1  &&  muoeta2<2.4) muoId2=14;

  if (muopt2>=10 && muopt2<20) muoIso2=0;
  if (muopt2>=20 && muopt2<30) muoIso2=1;
  if (muopt2>=30 && muopt2<40) muoIso2=2;
  if (muopt2>=40 && muopt2<50) muoIso2=3;
  if (muopt2>=50 && muopt2<60) muoIso2=4;
  if (muopt2>=60 && muopt2<80) muoIso2=5;
  if (muopt2>=80             ) muoIso2=6;

  cout << "PORCO DIO LADRO: "  << muoId1<< endl;
  cout << "PORCO DIO LADRO: "  << muoIso1<< endl;
  cout << "PORCO DIO LADRO: "  << muoId2<< endl;
  cout << "PORCO DIO LADRO: "  << muoIso2<< endl;


  if (is2011A) {
    efficiencyMuonPOG = muoIDrunA[muoId1] * muoISOrunA[highEta1][muoIso1] * muoIDrunA[muoId2] * muoISOrunA[highEta2][muoIso2];
  } else {
    efficiencyMuonPOG = muoIDrunB[muoId1] * muoISOrunB[highEta1][muoIso1] * muoIDrunB[muoId2] * muoISOrunB[highEta2][muoIso2];
  }

  return efficiencyMuonPOG;

}



double getEfficiencyCorrectionPtUsingElectron(TFile *fA, TFile *fB, double ele1_pt ,double ele1_eta, double ele2_pt, double ele2_eta, string dataOrMC, bool isElectron)
{
  TH2F* RECO_effPt;
  TH2F* ele17_effPt;
  TH2F* ele8NOTele17_effPt;
  TH2F* WP80_effPt;

  TDirectory *dir2;

  fB->cd("efficiency_vs_PtEta");
  dir2=(TDirectory*)fB->Get("efficiency_vs_PtEta");

  TList *mylist2=(TList*)dir2->GetListOfKeys();
  TIter iter2(mylist2); 
  TObject* tobj2 = 0;
 
  //Check for the interesting plots, regardless the content..
  while ( (tobj2 = iter2.Next()) ) {
    string name=tobj2->GetName();
    TString temp = (TString)name;
    if (dataOrMC=="Data"){
      if(temp.Contains("DATA_WP80_Probe")){
	gDirectory->GetObject(name.c_str(),WP80_effPt);
      }    
      if(temp.Contains("DATA_HLTele17_Probe")){
	gDirectory->GetObject(name.c_str(),ele17_effPt);
      }    
      if(temp.Contains("DATA_HLTele8NOTele17_Probe")){
	gDirectory->GetObject(name.c_str(),ele8NOTele17_effPt);
      }    
      if(temp.Contains("DATA_RECO_Probe")){
	gDirectory->GetObject(name.c_str(),RECO_effPt);
      }    
    }
    else{
      if(temp.Contains("MC_WP80_Probe")){
	gDirectory->GetObject(name.c_str(),WP80_effPt);
      }    
      if(temp.Contains("MC_HLTele17_Probe")){
	gDirectory->GetObject(name.c_str(),ele17_effPt);
      }    
      if(temp.Contains("MC_HLTele8NOTele17_Probe")){
	gDirectory->GetObject(name.c_str(),ele8NOTele17_effPt);
      }    
      if(temp.Contains("MC_RECO_Probe")){
	gDirectory->GetObject(name.c_str(),RECO_effPt);
      }    
    }
  }

  // Get the right pt bins
  int pt1=getPtRangeElectron(ele1_pt);
  int pt2=getPtRangeElectron(ele2_pt);
  // Get the right eta bins
  int eta1=getEtaRangeElectron(ele1_eta);
  int eta2=getEtaRangeElectron(ele2_eta);

  double eff_global=0;

  if (isElectron) {
    eff_global = WP80_effPt->GetBinContent(eta1,pt1)*
      WP80_effPt->GetBinContent(eta2,pt2)*
      RECO_effPt->GetBinContent(eta1,pt1)*
      RECO_effPt->GetBinContent(eta2,pt2)*
      (ele17_effPt->GetBinContent(eta1,pt1)*ele17_effPt->GetBinContent(eta2,pt2) +
      ele17_effPt->GetBinContent(eta1,pt1)*ele8NOTele17_effPt->GetBinContent(eta2,pt2) +
      ele8NOTele17_effPt->GetBinContent(eta1,pt1)*ele17_effPt->GetBinContent(eta2,pt2)
      );
  } else {
    eff_global = WP80_effPt->GetBinContent(eta1,pt1)*
      WP80_effPt->GetBinContent(eta2,pt2)*
      RECO_effPt->GetBinContent(eta1,pt1)*
      RECO_effPt->GetBinContent(eta2,pt2)*
      ele17_effPt->GetBinContent(eta1,pt1)*
      ele17_effPt->GetBinContent(eta2,pt2);
  }
  if (eff_global>0) return eff_global;
  return 1;
}


///////////////////
// Leading Jet Pt 
///////////////////


std::vector<double> getEfficiencyLeadingJet(double jetPt,  TH1F* effPt){
  double effPtJet=1.0;
  double effPtJeterror=0.0;

  if (jetPt>=30 && jetPt<40){
    effPtJet=effPt->GetBinContent(1);
    effPtJeterror=effPt->GetBinError(1);
  }
  if (jetPt>=40 && jetPt<50) {
    effPtJet=effPt->GetBinContent(2);
    effPtJeterror=effPt->GetBinError(2);
  }
  if (jetPt>=50 && jetPt<70) {
    effPtJet=effPt->GetBinContent(3);
    effPtJeterror=effPt->GetBinError(3);
  }
  if (jetPt>=70 && jetPt<90) {
    effPtJet=effPt->GetBinContent(4);
    effPtJeterror=effPt->GetBinError(4);
  }
  if (jetPt>=90 && jetPt<120) {
    effPtJet=effPt->GetBinContent(5);
    effPtJeterror=effPt->GetBinError(5);
  }
  if (jetPt>=120 && jetPt<150) {
    effPtJet=effPt->GetBinContent(6);
    effPtJeterror=effPt->GetBinError(6);
  }
  if (jetPt>=150 && jetPt<190) {
    effPtJet=effPt->GetBinContent(7);
    effPtJeterror=effPt->GetBinError(7);
  }
  if (jetPt>=190 && jetPt<230) {
    effPtJet=effPt->GetBinContent(8);
    effPtJeterror=effPt->GetBinError(8);
  }
  if (jetPt>=230) {
    effPtJet=effPt->GetBinContent(9);
    effPtJeterror=effPt->GetBinError(9);
  }
  std::vector<double> values;
  values.push_back(effPtJet);
  values.push_back(effPtJeterror);

  return values;
}

//Sub leading Correction
std::vector<double> getEfficiencySubLeadingJet(double jetPt,  TH1F* effPt){

  double effPtJet=1.0;
  double effPtJeterror=0.0;

  if (jetPt>=30 && jetPt<40){
    effPtJet=effPt->GetBinContent(1);
    effPtJeterror=effPt->GetBinError(1);
  }

  if (jetPt>=40 && jetPt<50){
    effPtJet=effPt->GetBinContent(2);
    effPtJeterror=effPt->GetBinError(2);
  }
  
  if (jetPt>=50 && jetPt<90){
    effPtJet=effPt->GetBinContent(3);
    effPtJeterror=effPt->GetBinError(3);
  }

  if (jetPt>=90 && jetPt<150){
    effPtJet=effPt->GetBinContent(4);
    effPtJeterror=effPt->GetBinError(4);
  }

  if (jetPt>=150){
    effPtJet=effPt->GetBinContent(5);
    effPtJeterror=effPt->GetBinError(5);
  }

  std::vector<double> values;
  values.push_back(effPtJet);
  values.push_back(effPtJeterror);

  //cout<<"2nd Jet ---------- input: jetPt -> "<<jetPt<<" ; output effPtJet -> "<<values[0]<<" ( error = "<< values[1] <<" )"<<endl;
  return values;
}

//Sub leading Correction
std::vector<double> getEfficiencySubSubLeadingJet(double jetPt,  TH1F* effPt){
  double effPtJet=1.0;
  double effPtJeterror=0.0;

  if (jetPt>=30 && jetPt<50){
    effPtJet=effPt->GetBinContent(1);
    effPtJeterror=effPt->GetBinError(1);
  }

  if (jetPt>=50 && jetPt<150){
    effPtJet=effPt->GetBinContent(2);
    effPtJeterror=effPt->GetBinError(2);
  }
  
  if (jetPt>=150){
    effPtJet=effPt->GetBinContent(3);
    effPtJeterror=effPt->GetBinError(3);
  }

  std::vector<double> values;
  values.push_back(effPtJet);
  values.push_back(effPtJeterror);

  return values;
}

std::vector<double> getEfficiencyCorrectionPt(TFile *fA, TFile *fB, int jetMultiplicity,double jetPt, string dataOrMC)
{

  std::vector<double> values;
  TH1F* effPt;

  ///////////////////////////////////////////

  //////////////
  // jET pT
  //////////////

  TDirectory *dir2;

  if (jetMultiplicity==1) {
    fB->cd("efficiency_vs_leadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_leadjetpt");
  }
  if (jetMultiplicity==2) {
    fB->cd("efficiency_vs_subleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subleadjetpt");
  }
  if (jetMultiplicity==3) {
    fB->cd("efficiency_vs_subsubleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subsubleadjetpt");
  }
  if (jetMultiplicity==4) {
    fB->cd("efficiency_vs_subsubsubleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subsubsubleadjetpt");
  }

  TList *mylist2=(TList*)dir2->GetListOfKeys();
  TIter iter2(mylist2); 
  TObject* tobj2 = 0;
  
 
  //Check for the interesting plots, regardless the content..
  while ( (tobj2 = iter2.Next()) ) {
    string name=tobj2->GetName();
    TString temp = (TString)name;
    if (dataOrMC=="Data"){
      if(temp.Contains("DATA_globalEfficiency")){
	gDirectory->GetObject(name.c_str(),effPt);
      }    
    }
    else{
      if(temp.Contains("MC_globalEfficiency")){
	gDirectory->GetObject(name.c_str(),effPt);
      }    
    }
  }
    
  if (jetPt <1000)
    {
      // insert the matrixes
      if (jetMultiplicity==1) values=getEfficiencyLeadingJet(jetPt,effPt);
      if (jetMultiplicity==2) {
	values=getEfficiencySubLeadingJet(jetPt,effPt);
      }
      if (jetMultiplicity==3) values=getEfficiencySubSubLeadingJet(jetPt,effPt);
      //if (jetMultiplicity==4) values=getEfficiencySubSubSubLeadingJet(jetPt,effPt);
    }
  else {
    cout<<"WARNING: events with too high pt. Efficiency put to 1"<<endl;
    values.push_back(1.0);
    values.push_back(0.0);    
  }

  return values;
 }

std::vector<double> getEfficiencyCorrectionJetMultiplicity(TFile *fA, TFile *fB, int jetMultiplicity, string dataOrMC)
{

 
  std::vector<double> values;
  TH1F* effJets;

  //////////////
  // Efficinecy as a function of # jets
  //////////////

  fA->cd("efficiency_vs_nJets");
  TDirectory *dir=(TDirectory*)fA->Get("efficiency_vs_nJets");
  TList *mylist=(TList*)dir->GetListOfKeys();
  TIter iter(mylist); 
  TObject* tobj = 0;

  
  //Check for the interesting plots, regardless the content..
  while ( (tobj = iter.Next()) ) {
    string name=tobj->GetName();
    TString temp = (TString)name;
    if (dataOrMC=="Data"){
      if(temp.Contains("DATA_globalEfficiency")){
	gDirectory->GetObject(name.c_str(),effJets);
      }    
    }
    else{
      if(temp.Contains("MC_globalEfficiency")){
	gDirectory->GetObject(name.c_str(),effJets);
      }    
    }
  }
  
  double effNJet=1.0;
  double effNJeterror=0.0;

  if (jetMultiplicity<=5) {
    effNJet=effJets->GetBinContent(jetMultiplicity+1);
    effNJeterror=effJets->GetBinError(jetMultiplicity+1);
    values.push_back(effNJet);
    values.push_back(effNJeterror); 
  }
  else {
    cout<<"WARNING: events with too much jets. Efficiency put to 1"<<endl;
    effNJet=1.0;
    values.push_back(1.0);
    values.push_back(0.0); 
  }

  return values;
}



//////////////////////////////
///   Scale Factors
/////////////////////////////


double getScaleFactorPtUsingElectron(TFile *fA, TFile *fB, double ele1_pt ,double ele1_eta, double ele2_pt, double ele2_eta, bool isElectron)
{
  TH2F* RECO_effPt_DATA;
  TH2F* ele17_effPt_DATA;
  TH2F* ele8NOTele17_effPt_DATA;
  TH2F* WP80_effPt_DATA;

  TH2F* RECO_effPt_MC;
  TH2F* ele17_effPt_MC;
  TH2F* ele8NOTele17_effPt_MC;
  TH2F* WP80_effPt_MC;

  TDirectory *dir2;

  fB->cd("efficiency_vs_PtEta");
  dir2=(TDirectory*)fB->Get("efficiency_vs_PtEta");

  TList *mylist2=(TList*)dir2->GetListOfKeys();
  TIter iter2(mylist2); 
  TObject* tobj2 = 0;
 
  //Check for the interesting plots, regardless the content..
  while ( (tobj2 = iter2.Next()) ) {
    string name=tobj2->GetName();
    TString temp = (TString)name;
    if(temp.Contains("DATA_WP80_Probe")){
      gDirectory->GetObject(name.c_str(),WP80_effPt_DATA);
    }    
    if(temp.Contains("DATA_HLTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele17_effPt_DATA);
    }    
    if(temp.Contains("DATA_HLTele8NOTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele8NOTele17_effPt_DATA);
    }    
    if(temp.Contains("DATA_RECO_Probe")){
      gDirectory->GetObject(name.c_str(),RECO_effPt_DATA);
    }    
    if(temp.Contains("MC_WP80_Probe")){
      gDirectory->GetObject(name.c_str(),WP80_effPt_MC);
    }    
    if(temp.Contains("MC_HLTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele17_effPt_MC);
    }    
    if(temp.Contains("MC_HLTele8NOTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele8NOTele17_effPt_MC);
    }    
    if(temp.Contains("MC_RECO_Probe")){
      gDirectory->GetObject(name.c_str(),RECO_effPt_MC);
    }    
  }

  // Get the right pt bins
  int pt1=getPtRangeElectron(ele1_pt);
  int pt2=getPtRangeElectron(ele2_pt);
  // Get the right eta bins
  int eta1=getEtaRangeElectron(ele1_eta);
  int eta2=getEtaRangeElectron(ele2_eta);

  double eff_global_DATA=0;
  double eff_global_MC=0;

  if (isElectron) {
    eff_global_DATA = WP80_effPt_DATA->GetBinContent(eta1,pt1)*
      WP80_effPt_DATA->GetBinContent(eta2,pt2)*
      RECO_effPt_DATA->GetBinContent(eta1,pt1)*
      RECO_effPt_DATA->GetBinContent(eta2,pt2)*
      (ele17_effPt_DATA->GetBinContent(eta1,pt1)*ele17_effPt_DATA->GetBinContent(eta2,pt2) +
      ele17_effPt_DATA->GetBinContent(eta1,pt1)*ele8NOTele17_effPt_DATA->GetBinContent(eta2,pt2) +
      ele8NOTele17_effPt_DATA->GetBinContent(eta1,pt1)*ele17_effPt_DATA->GetBinContent(eta2,pt2));
    eff_global_MC = WP80_effPt_MC->GetBinContent(eta1,pt1)*
      WP80_effPt_MC->GetBinContent(eta2,pt2)*
      RECO_effPt_MC->GetBinContent(eta1,pt1)*
      RECO_effPt_MC->GetBinContent(eta2,pt2)*
      (ele17_effPt_MC->GetBinContent(eta1,pt1)*ele17_effPt_MC->GetBinContent(eta2,pt2) +
       ele17_effPt_MC->GetBinContent(eta1,pt1)*ele8NOTele17_effPt_MC->GetBinContent(eta2,pt2) +
       ele8NOTele17_effPt_MC->GetBinContent(eta1,pt1)*ele17_effPt_MC->GetBinContent(eta2,pt2));
  } else {
    eff_global_DATA = WP80_effPt_DATA->GetBinContent(eta1,pt1)*
      WP80_effPt_DATA->GetBinContent(eta2,pt2)*
      RECO_effPt_DATA->GetBinContent(eta1,pt1)*
      RECO_effPt_DATA->GetBinContent(eta2,pt2)*
      ele17_effPt_DATA->GetBinContent(eta1,pt1)*
      ele17_effPt_DATA->GetBinContent(eta2,pt2);
    eff_global_MC = WP80_effPt_MC->GetBinContent(eta1,pt1)*
      WP80_effPt_MC->GetBinContent(eta2,pt2)*
      RECO_effPt_MC->GetBinContent(eta1,pt1)*
      RECO_effPt_MC->GetBinContent(eta2,pt2)*
      ele17_effPt_MC->GetBinContent(eta1,pt1)*
      ele17_effPt_MC->GetBinContent(eta2,pt2);
  }

  if (eff_global_DATA>0 && eff_global_MC>0) return eff_global_DATA/eff_global_MC;
  return 1;
}

// Leading Jet Pt 
double getScaleFactorsLeadingJet(double jetPt_MC,  TH1F* effPtData,  TH1F* effPtMC){
  double effPtJet=1.0;

  if (jetPt_MC>=30 && jetPt_MC<40){
    effPtJet=effPtData->GetBinContent(1)/effPtMC->GetBinContent(1);
  }
  if (jetPt_MC>=40 && jetPt_MC<50) {
    effPtJet=effPtData->GetBinContent(2)/effPtMC->GetBinContent(2);
  }
  if (jetPt_MC>=50 && jetPt_MC<70) {
    effPtJet=effPtData->GetBinContent(3)/effPtMC->GetBinContent(3);
  }
  if (jetPt_MC>=70 && jetPt_MC<90) {
    effPtJet=effPtData->GetBinContent(4)/effPtMC->GetBinContent(4);
  }
  if (jetPt_MC>=90 && jetPt_MC<120) {
    effPtJet=effPtData->GetBinContent(5)/effPtMC->GetBinContent(5);
  }
  if (jetPt_MC>=120 && jetPt_MC<150) {
    effPtJet=effPtData->GetBinContent(6)/effPtMC->GetBinContent(6);
  }
  if (jetPt_MC>=150 && jetPt_MC<190) {
    effPtJet=effPtData->GetBinContent(7)/effPtMC->GetBinContent(7);
  }
  if (jetPt_MC>=190 && jetPt_MC<230) {
    effPtJet=effPtData->GetBinContent(8)/effPtMC->GetBinContent(8);
  }
  if (jetPt_MC>=230) {
    effPtJet=effPtData->GetBinContent(9)/effPtMC->GetBinContent(9);
  }
  cout<<"scale factor Data/MC is "<<effPtJet<<endl;
  return effPtJet;
}

// Leading Jet Pt 
double getScaleFactorsSubLeadingJet(double jetPt_MC,  TH1F* effPtData,  TH1F* effPtMC){
  double effPtJet=1.0;

  if (jetPt_MC>=30 && jetPt_MC<40){
    effPtJet=effPtData->GetBinContent(1)/effPtMC->GetBinContent(1);
  }
  if (jetPt_MC>=40 && jetPt_MC<50) {
    effPtJet=effPtData->GetBinContent(2)/effPtMC->GetBinContent(2);
  }
  if (jetPt_MC>=50 && jetPt_MC<90) {
    effPtJet=effPtData->GetBinContent(3)/effPtMC->GetBinContent(3);
  }
  if (jetPt_MC>=90 && jetPt_MC<150) {
    effPtJet=effPtData->GetBinContent(4)/effPtMC->GetBinContent(4);
  }
  if (jetPt_MC>=150) {
    effPtJet=effPtData->GetBinContent(5)/effPtMC->GetBinContent(5);
  }

  //cout<<"2nd Jet scale factor Data/MC is "<<effPtJet<<endl;
  return effPtJet;
}

// Leading Jet Pt 
double getScaleFactorsSubSubLeadingJet(double jetPt_MC,  TH1F* effPtData,  TH1F* effPtMC){
  double effPtJet=1.0;

  if (jetPt_MC>=30 && jetPt_MC<50){
    effPtJet=effPtData->GetBinContent(1)/effPtMC->GetBinContent(1);
  }
  if (jetPt_MC>=50 && jetPt_MC<150) {
    effPtJet=effPtData->GetBinContent(2)/effPtMC->GetBinContent(2);
  }
  if (jetPt_MC>=150) {
    effPtJet=effPtData->GetBinContent(3)/effPtMC->GetBinContent(3);
  }
  //cout<<"scale factor Data/MC is "<<effPtJet<<endl;
  return effPtJet;
}

double getScaleFactorJetPt(TFile *fA, TFile *fB, int jetMultiplicity_MC,double jetPt_MC)
{

  double values;
  TH1F* effJets;
  TH1F* effPtMC;
  TH1F* effPtData;

  ///////////////////////////////////////////

  //////////////
  // jET pT
  //////////////

  TDirectory *dir2;

  if (jetMultiplicity_MC==1) {
    fB->cd("efficiency_vs_leadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_leadjetpt");
  }
  if (jetMultiplicity_MC==2) {
    fB->cd("efficiency_vs_subleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subleadjetpt");
  }
  if (jetMultiplicity_MC==3) {
    fB->cd("efficiency_vs_subsubleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subsubleadjetpt");
  }
  if (jetMultiplicity_MC==4) {
    fB->cd("efficiency_vs_subsubsubleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subsubsubleadjetpt");
  }

  TList *mylist2=(TList*)dir2->GetListOfKeys();
  TIter iter2(mylist2); 
  TObject* tobj2 = 0;
  
 
  //Check for the interesting plots, regardless the content..
  while ( (tobj2 = iter2.Next()) ) {
    string name=tobj2->GetName();
    TString temp = (TString)name;
    if(temp.Contains("DATA_globalEfficiency")){
      gDirectory->GetObject(name.c_str(),effPtData);
    }    
    if(temp.Contains("MC_globalEfficiency")){
      gDirectory->GetObject(name.c_str(),effPtMC);
    }    
  }
    
  if (jetPt_MC <1000)
    {
      // insert the matrixes
      if (jetMultiplicity_MC==1) values=getScaleFactorsLeadingJet(jetPt_MC,effPtData, effPtMC);
      if (jetMultiplicity_MC==2) {
	values=getScaleFactorsSubLeadingJet(jetPt_MC,effPtData, effPtMC);
      }
      if (jetMultiplicity_MC==3) values=getScaleFactorsSubSubLeadingJet(jetPt_MC,effPtData, effPtMC);
      //if (jetMultiplicity==4) values=getScaleFactorsSubSubSubLeadingJet(jetPt_MC,effPtData, effPtMC);
    }
  else {
    cout<<"WARNING: events with too high pt. Efficiency put to 1"<<endl;
    values=1.0;
  }

  return values;
 }
