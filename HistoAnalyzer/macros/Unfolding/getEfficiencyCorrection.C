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



double getEfficiencyCorrectionPtUsingElectron(TFile *fA, TFile *fB, double ele1_pt ,double ele1_eta, double ele2_pt, double ele2_eta, string dataOrMC)
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

  if (isElectron) {
    double eff_global = WP80_effPt->GetBinContent(eta1,pt1)*
      WP80_effPt->GetBinContent(eta2,pt2)*
      RECO_effPt->GetBinContent(eta1,pt1)*
      RECO_effPt->GetBinContent(eta2,pt2)*
      (ele17_effPt->GetBinContent(eta1,pt1)*ele17_effPt->GetBinContent(eta2,pt2) +
       ele17_effPt->GetBinContent(eta1,pt1)*ele8NOTele17_effPt->GetBinContent(eta2,pt2) +
       ele8NOTele17_effPt->GetBinContent(eta1,pt1)*ele17_effPt->GetBinContent(eta2,pt2));
  } else {
    double eff_global = WP80_effPt->GetBinContent(eta1,pt1)*
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

  cout<<"2nd Jet ---------- input: jetPt -> "<<jetPt<<" ; output effPtJet -> "<<values[0]<<" ( error = "<< values[1] <<" )"<<endl;
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
  TH1F* effJets;
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

  cout<<"2nd Jet scale factor Data/MC is "<<effPtJet<<endl;
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
  cout<<"scale factor Data/MC is "<<effPtJet<<endl;
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
