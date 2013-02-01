#include <vector>
#include <iostream>
#include <algorithm>
#include "TSVDUnfold.h"
#include <iostream>
#include <fstream>

using namespace std;

/*Initialize Variables*/
double minObsPlot=30;
double maxObsPlot=330;
int divPlot=15;
int kmin=1;
int kmax=1;
bool spanKvalues=false;
bool Unfold=true;      
double jet_Obs_gen=0;
double jet_Obs=0;

TH1F *relativebkg = new TH1F("relativebkg", "relativebkg bin contribution",divPlot,0,divPlot);
TH1D *errors = new TH1D ("errors", "jet DATA Measured",divPlot,0,divPlot);
TH1D *errorstat = new TH1D ("errorstat", "errors",divPlot,0,divPlot);

TCanvas *c; TH1D* modD; 

int getNumberOfValidJets(int Jet_multiplicity, double thresh, double thresheta, double jet1_pt, double jet2_pt, double jet3_pt, double jet4_pt, double jet5_pt, double jet6_pt, double jet1_eta, double jet2_eta, double jet3_eta, double jet4_eta, double jet5_eta, double jet6_eta){
  int counter=0;
  for (int i=1;i<=Jet_multiplicity; i++){
    if (i==1){
      if (jet1_pt>thresh && fabs(jet1_eta)<thresheta ) counter++;
    }    
    if (i==2){
      if (jet2_pt>thresh && fabs(jet2_eta)<thresheta ) counter++;
    }
    if (i==3){
      if (jet3_pt>thresh && fabs(jet3_eta)<thresheta ) counter++;
    }
    if (i==4){
      if (jet4_pt>thresh && fabs(jet4_eta)<thresheta ) counter++;
    }
    if (i==5){
      if (jet5_pt>thresh && fabs(jet5_eta)<thresheta ) counter++;
    }
    if (i==6){
      if (jet6_pt>thresh && fabs(jet6_eta)<thresheta ) counter++;
    }

  }// for
  return counter;
}// end


void setPlotsDivisionsAndRanges(int numbOfJetsSelected, string whichtype, string whichalgo)
{
  bool bayesianTests=false;
  if (whichalgo=="Bayes") bayesianTests=true;

  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      kmin=9;
      kmax=10;
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
    }
    if (numbOfJetsSelected==2){
      minObsPlot=30;
      maxObsPlot=330;
      divPlot=10;
      kmin=4;
      kmax=5;
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
    }
    if (numbOfJetsSelected==3){
      minObsPlot=30;
      maxObsPlot=190;
      divPlot=8;
      kmin=4;
      kmax=5;
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
    }
    if (numbOfJetsSelected==4){
      minObsPlot=30;
      maxObsPlot=100;
      divPlot=7;
      kmin=3;
      kmax=4;
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
    }
  }

  if (whichtype == "Eta"){
    minObsPlot=-2.4;
    maxObsPlot=2.4;
    divPlot=48;
    kmin=4;
    kmax=5;

    if (numbOfJetsSelected==1) {
      kmin=9;
      kmax=10;
      divPlot=24;

    }
    
    if (numbOfJetsSelected==2){
      kmin=20;
      kmax=21;
      divPlot=20;
    }
    
    if (numbOfJetsSelected==3){
      kmin=8;
      kmax=9;
      divPlot=16;
    }
    
    if (numbOfJetsSelected==4){
      kmin=8;
      kmax=9;
      divPlot=12;
    } 
      if (bayesianTests) {
	kmin=3;
	kmax=4;
      }
  }
  
  if (whichtype=="Ht"){
    
    divPlot = 12;
    minObsPlot = 30;
    maxObsPlot = 630;
    kmin = 11;
    kmax = 12;

if (numbOfJetsSelected == 1){
      kmin = 5;
      kmax = 6;
    }
  if (numbOfJetsSelected == 2){
      minObsPlot = 60;
      maxObsPlot = 630;
      kmin = 7;
      kmax = 8;
    }
  if (numbOfJetsSelected == 3){
      kmin = 7;
      kmax = 8;
      divPlot = 7;
      minObsPlot = 90;
      maxObsPlot = 630;
    }
  if (numbOfJetsSelected == 4){                          
      kmin = 4;
      kmax = 5;
      divPlot = 5;
      minObsPlot = 120;
      maxObsPlot = 630;
    }
  if (bayesianTests) {
    kmin=3;
    kmax=4;
      }
  }

  if (whichtype=="Multiplicity"){
    divPlot=maxNJets-1;
    minObsPlot=1;
    maxObsPlot=maxNJets-1;

    kmin=3;
    kmax=4;
    
    if (bayesianTests) {
      kmin=3;
      kmax=4;
    }
  }
  
  // When you span
  if (spanKvalues){
    kmin=2;
    kmax=divPlot; 
  }
  return;
}


//After that, Observables are set...
void setObservablesMC(int numbOfJetsSelected, string whichtype, double jet1_pt_gen, double jet2_pt_gen, double jet3_pt_gen, double jet4_pt_gen,  double jet5_pt_gen,  double jet6_pt_gen, double jet1_eta_gen, double jet2_eta_gen, double jet3_eta_gen, double jet4_eta_gen, double jet5_eta_gen, double jet6_eta_gen, int Jet_multiplicity_gen, double jet1_pt, double jet2_pt, double jet3_pt, double jet4_pt,  double jet5_pt,  double jet6_pt, double jet1_eta, double jet2_eta, double jet3_eta, double jet4_eta, double jet5_eta, double jet6_eta,int Jet_multiplicity){

  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      jet_Obs_gen=jet1_pt_gen;
      jet_Obs=jet1_pt;
    }
    if (numbOfJetsSelected==2) {
      jet_Obs_gen=jet2_pt_gen;
      jet_Obs=jet2_pt;
    }
    if (numbOfJetsSelected==3) {
      jet_Obs_gen=jet3_pt_gen;
      jet_Obs=jet3_pt;
    }
    if (numbOfJetsSelected==4) {
      jet_Obs_gen=jet4_pt_gen;
      jet_Obs=jet4_pt;
    }
    return;
  }

  if (whichtype=="Eta"){
    if (numbOfJetsSelected==1) {
      jet_Obs_gen=jet1_eta_gen;
      jet_Obs=jet1_eta;
    }
    if (numbOfJetsSelected==2) {
      jet_Obs_gen=jet2_eta_gen;
      jet_Obs=jet2_eta;

    }
    if (numbOfJetsSelected==3) {
      jet_Obs_gen=jet3_eta_gen;
      jet_Obs=jet3_eta;
    }
    if (numbOfJetsSelected==4) {
      jet_Obs_gen=jet4_eta_gen;
      jet_Obs=jet4_eta;
    }
    return;
  }

  if (whichtype=="Ht"){
    if (Jet_multiplicity >= numbOfJetsSelected ){
      if (jet1_pt > 30 && jet1_pt < 7000 && fabs(jet1_eta)<2.4 ) jet_Obs += jet1_pt;
        if (jet2_pt > 30 && jet2_pt < 7000 && fabs(jet2_eta)<2.4) jet_Obs += jet2_pt;
        if (jet3_pt > 30 && jet3_pt < 7000 && fabs(jet3_eta)<2.4) jet_Obs += jet3_pt;
        if (jet4_pt > 30 && jet4_pt < 7000 && fabs(jet4_eta)<2.4) jet_Obs += jet4_pt;
        if (jet5_pt > 30 && jet5_pt < 7000 && fabs(jet5_eta)<2.4) jet_Obs += jet5_pt;
        if (jet6_pt > 30 && jet6_pt < 7000 && fabs(jet6_eta)<2.4) jet_Obs += jet6_pt;
      }

    if (Jet_multiplicity_gen >= numbOfJetsSelected ){
        if (jet1_pt_gen > 30 && jet1_pt_gen < 7000 && fabs(jet1_eta_gen)<2.4) jet_Obs_gen += jet1_pt_gen;
        if (jet2_pt_gen > 30 && jet2_pt_gen < 7000 && fabs(jet2_eta_gen)<2.4) jet_Obs_gen += jet2_pt_gen;
        if (jet3_pt_gen > 30 && jet3_pt_gen < 7000 && fabs(jet3_eta_gen)<2.4) jet_Obs_gen += jet3_pt_gen;
        if (jet4_pt_gen > 30 && jet4_pt_gen < 7000 && fabs(jet4_eta_gen)<2.4) jet_Obs_gen += jet4_pt_gen;
        if (jet5_pt_gen > 30 && jet5_pt_gen < 7000 && fabs(jet5_eta_gen)<2.4) jet_Obs_gen += jet5_pt_gen;
        if (jet6_pt_gen > 30 && jet6_pt_gen < 7000 && fabs(jet6_eta_gen)<2.4) jet_Obs_gen += jet6_pt_gen;
      }
    return;
  }

  if (whichtype=="Multiplicity"){
    jet_Obs=Jet_multiplicity;
    jet_Obs_gen=Jet_multiplicity_gen;
  }

  return;
}

void setObservablesData(int numbOfJetsSelected, string whichtype, double jet1_pt, double jet2_pt, double jet3_pt, double jet4_pt,  double jet5_pt,  double jet6_pt, double jet1_eta, double jet2_eta, double jet3_eta, double jet4_eta, double jet5_eta, double jet6_eta,int Jet_multiplicity){

  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      jet_Obs=jet1_pt;
    }
    if (numbOfJetsSelected==2) {
      jet_Obs=jet2_pt;
    }
    if (numbOfJetsSelected==3) {
      jet_Obs=jet3_pt;
    }
    if (numbOfJetsSelected==4) {
      jet_Obs=jet4_pt;
    }
    return;
  }

  if (whichtype=="Eta"){
    if (numbOfJetsSelected==1) {
      jet_Obs=jet1_eta;
    }
    if (numbOfJetsSelected==2) {
      jet_Obs=jet2_eta;

    }
    if (numbOfJetsSelected==3) {
      jet_Obs=jet3_eta;
    }
    if (numbOfJetsSelected==4) {
      jet_Obs=jet4_eta;
    }
    if (jet_Obs==0) jet_Obs=-99; //To avoid peak
    return;
  }

  if (whichtype=="Ht"){
    if (Jet_multiplicity >= numbOfJetsSelected ){
        if (jet1_pt > 30 && jet1_pt < 7000 && fabs(jet1_eta)<2.4) jet_Obs += jet1_pt;
        if (jet2_pt > 30 && jet2_pt < 7000 && fabs(jet2_eta)<2.4) jet_Obs += jet2_pt;
        if (jet3_pt > 30 && jet3_pt < 7000 && fabs(jet3_eta)<2.4) jet_Obs += jet3_pt;
        if (jet4_pt > 30 && jet4_pt < 7000 && fabs(jet4_eta)<2.4) jet_Obs += jet4_pt;
        if (jet5_pt > 30 && jet5_pt < 7000 && fabs(jet5_eta)<2.4) jet_Obs += jet5_pt;
        if (jet6_pt > 30 && jet6_pt < 7000 && fabs(jet6_eta)<2.4) jet_Obs += jet6_pt;
      }
    return;
  }

  if (whichtype=="Multiplicity"){
    jet_Obs=Jet_multiplicity;
  }

  return;
}



TH1D* performUnfolding(string whichalgo, int kvalue, TH1D *jData, TH1D *jTrue, RooUnfoldResponse response_j, TH1D* jMCreco, TH2D* jMatx) //Specify which algo
{
  TH1D *unf;
  RooUnfoldBayes unfold_b (&response_j, jData, kvalue);  //NEVER,NEVER,NEVER set the parameter "1000" for the testing if you want to perform identity tests
  RooUnfoldSvd unfold_s (&response_j, jData, kvalue);

  if (whichalgo=="Bayes") {
    unf = (TH1D *) unfold_b.Hreco ();
    unfold_b.PrintTable(cout,jTrue);
    cout<<"Bayes: Chi2 of this k parameter(k="<<kvalue<<")<< is "<<unfold_b.Chi2(jTrue,RooUnfold::kErrors)<<endl;
    TVectorD vstat= unfold_b.ErecoV();
    TVectorD vunfo= unfold_b.ErecoV(RooUnfold::kCovToy);
    TVectorD vunfomat= unfold_b.ErecoV(RooUnfold::kCovariance);
    TVectorD vunfodiag= unfold_b.ErecoV(RooUnfold::kErrors);
  }
  else{
    unf = (TH1D *) unfold_s.Hreco ();
    unfold_s.PrintTable(cout,jTrue);
    TVectorD vstat= unfold_s.ErecoV();
    TVectorD vunfo= unfold_s.ErecoV(RooUnfold::kCovToy);
    TVectorD vunfomat= unfold_s.ErecoV(RooUnfold::kCovariance);
    TVectorD vunfodiag= unfold_s.ErecoV(RooUnfold::kErrors);
    TSVDUnfold unfold_modD (jData,jTrue,jMCreco,jMatx); // per calcolare il modulo
    TH1D* unfresult = unfold_modD.Unfold( kvalue); modD = unfold_modD.GetD();
  }

  cout<<"Set the error!!!!!!!!!!!"<<endl;
  for (unsigned int p=0;p<unf->GetNbinsX();p++){
    errors->SetBinContent(p+1,unf->GetBinError(p+1)); errorstat->SetBinContent(p+1,sqrt(unf->GetBinContent(p+1)));
  }
  //Returns vector of unfolding errors computed according to the withError flag:
  //0: Errors are the square root of the bin content
  //1: Errors from the diagonals of the covariance matrix given by the unfolding
  //2: Errors from the covariance matrix given by the unfolding
  //3: Errors from the covariance matrix from the variation of the results in toy MC tests
  // enum ErrorTreatment {      kNoError          //kErrors     //kCovariance //kCovToy     
  return unf;
} 

//////////////////////
//Draw options
///////////////////////


TCanvas* drawPlots(TH1D *jReco,TH1D* jData, TH1D *jTrue, TH1D* jMCreco, int numbOfJetsSelected, string whichtype, string whichalgo, int k){
  TCanvas *c=new TCanvas("c", "c", 1000, 700);
  c->cd ();
  TPad *pad1 = new TPad ("pad1", "pad1",0.01,0.33,0.99,0.99);
  pad1->Draw ();
  pad1->cd ();
  gPad->SetLogy (1);
  pad1->SetTopMargin(0.1);
  pad1->SetBottomMargin(0.01);
  pad1->SetRightMargin(0.1);
  pad1->SetFillStyle(0);
  
  string whichjet="";
  if (numbOfJetsSelected==1) whichjet="Leading "; 
  if (numbOfJetsSelected==2) whichjet="Second leading "; 
  if (numbOfJetsSelected==3) whichjet="Third leading "; 
  if (numbOfJetsSelected==4) whichjet="Fourth leading "; 
  string title2=whichjet+"jet pT diff xsec distribution. "+whichtype;
  jReco->SetTitle (title2.c_str());
  jReco->GetXaxis ()->SetTitle ("");
  if (!isMu) jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d p_{T}");
  if (isMu) jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d p_{T}");
  jReco->SetMarkerStyle (20);
  jData->SetMarkerStyle (21);
  jData->SetLineColor(kGreen);
  
  if (differentialCrossSection){
    jReco->Scale(1./jReco->Integral());             
    jTrue->Scale(1./jTrue->Integral());
    jMCreco->Scale(1./jMCreco->Integral());
    jData->Scale(1./jData->Integral());
  }
  
  cout<<"area jReco:"<<jReco->Integral()<<" and MCreco "<<jMCreco->Integral()<<endl;
  
  jReco->SetMarkerStyle (20);
  jMCreco->SetStats(0);
  jData->SetStats(0);
  jTrue->SetStats(0);
  jReco->SetStats(0);
  jReco->GetXaxis()->SetTitle("jet pT [GeV/c]");
  jReco->SetLineColor (kBlack); 
  
  jReco->SetLabelSize(0.0);
  jReco->GetXaxis()->SetTitleSize(0.00);
  jReco->GetYaxis()->SetLabelSize(0.07);
  jReco->GetYaxis()->SetTitleSize(0.08);
  jReco->GetYaxis()->SetTitleOffset(0.76);
  jReco->SetTitle("");
  jReco->Draw("EP");        //risultato dell'unfolding
  
  jMCreco->SetLineColor (kBlue + 1);
  jMCreco->SetLineStyle (2);
  jMCreco->SetLineWidth (2); 
  if (!pythiaCheck) jMCreco->Draw("HISTSAMES");
  jTrue->SetLineColor (kRed);
  jTrue->SetLineWidth (2);
  jTrue->Draw ("HISTSAME");
  jData->SetLineColor(kGreen+1);
  pad1->SetLogy (1);
  jData->SetMarkerStyle (4);
  jData->SetMarkerColor(kGreen+1);
  jData->SetStats(0);
  jData->Draw("EPSAME");
  
  //pad1->SetBottomMargin (0.1);
  
  TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
  legend_d->SetFillColor (0);
  legend_d->SetFillStyle (0);
  legend_d->SetBorderSize (0);
  legend_d->AddEntry (jReco, "Data Unfolded", "P20");
  legend_d->AddEntry (jTrue, "MC truth", "L");
  if (!pythiaCheck) legend_d->AddEntry (jMCreco, "MC reco", "L");
  legend_d->AddEntry(jData,"Data Folded","P20");
  legend_d->Draw ("same");
  
  TLatex *latexLabel=CMSPrel(4.890,""); // make fancy label
  latexLabel->Draw("same");   
  pad1->Update();      
  c->cd ();
  
  TPad *pad2 = new TPad ("pad2", "pad2",0.01,0.01,0.99,0.32);
  pad2->SetTopMargin (0);
  pad2->Draw ();
  pad2->cd ();
  pad2->SetTopMargin(0.01);
  pad2->SetBottomMargin(0.3);
  pad2->SetRightMargin(0.1);
  pad2->SetFillStyle(0);
  
  TH1D *jRecoClone= (TH1D*) jReco->Clone("jReco");
  jRecoClone->SetName("jRecoClone");      
  jRecoClone->SetStats(0);
  jRecoClone->GetXaxis ()->SetLabelSize (0.1);
  jRecoClone->GetYaxis ()->SetLabelSize (0.08);
  jRecoClone->Divide(jTrue);
  jRecoClone->SetMarkerStyle (6);
  jRecoClone->GetXaxis ()->SetLabelSize (0.06);
  jRecoClone->GetYaxis ()->SetLabelSize (0.06);
  jRecoClone->GetXaxis ()->SetTitleSize (0);
  jRecoClone->GetYaxis ()->SetTitleSize (0.06);
  jRecoClone->GetYaxis ()->SetTitleOffset (0.5);
  
  jRecoClone->GetYaxis ()->SetRangeUser (0.5, 1.5);
  jRecoClone->GetXaxis ()->SetRangeUser (0, 5);
  jRecoClone->GetYaxis ()->SetTitle ("Ratios");
  jRecoClone->GetXaxis ()->SetTitle("jet pT [GeV/c]");
  jRecoClone->SetMarkerStyle (20);
  jRecoClone->SetLineWidth (0);
  jRecoClone->SetTitle ("");
  double max=jRecoClone->GetMaximum();
  double min=jRecoClone->GetMinimum();
  jRecoClone->GetYaxis()->SetRangeUser(min,max);
  jRecoClone->GetYaxis()->SetNdivisions(5);
  jRecoClone->GetXaxis()->SetTitleSize(0.14);
  jRecoClone->GetXaxis()->SetLabelSize(0.14);
  jRecoClone->GetYaxis()->SetLabelSize(0.11);
  jRecoClone->GetYaxis()->SetTitleSize(0.11);
  jRecoClone->GetYaxis()->SetTitleOffset(0.28);
  jRecoClone->GetYaxis()->SetTitle("ratio data/MC");
  jRecoClone->Draw();
  
  TH1D *jDataClone= (TH1D*) jReco->Clone("jReco");
  jDataClone->SetName("jDataClone"); 
  jDataClone->Divide(jData);
  jDataClone->SetLineStyle (2); 
  jDataClone->SetMarkerSize (0);       
  jDataClone->SetLineWidth (0.05);
  jDataClone->SetLineColor(kViolet);
  jDataClone->Draw ("E1HISTSAME");
  jDataClone->SetLineWidth (0.1);
  
  TF1 *f = new TF1("f","1",0,410);
  f->SetLineWidth(1);
  f->Draw("SAMES");
  
  TLegend *legend_w = new TLegend(0.197791, 0.736607, 0.394578, 0.9375);
  legend_w->SetFillColor (0);
  legend_w->SetFillStyle (0);
  legend_w->SetBorderSize (0);
  legend_w->AddEntry (jRecoClone, "Data Unfolded / MC truth", "P20");
  //legend_w->AddEntry (jMCRecoClone, "MC reco / MC truth", "L");
  legend_w->AddEntry (jDataClone, "Data Unfolded / Data Folded", "L");
  legend_w->Draw ("same");
  //pad2->Update();
  stringstream num;
  num<<k;
  string whichjetname="";
  if (numbOfJetsSelected==1) whichjetname="Leading"; 
  if (numbOfJetsSelected==2) whichjetname="Second leading "; 
  if (numbOfJetsSelected==3) whichjetname="Third leading "; 
  if (numbOfJetsSelected==4) whichjetname="Fourth leading ";
  string title3= s+"JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+".pdf";
  num.str("");
  c->cd ();
  c->Print(title3.c_str());
  
  if (whichalgo == "SVD"){
    TCanvas *moduloD= new TCanvas ("moduloD", "moduloD", 1000, 700);
    moduloD->cd ();
    gPad->SetLogy (1); modD->SetStats (111111);
    modD->GetXaxis()->SetTitle("K Parameters"); modD->GetYaxis()->SetTitle("Value");
    modD->SetLineColor(kRed);
    modD->Draw(); 
    string title= s+"JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+"_moduloD.pdf";
    moduloD->Print(title.c_str()); 
  }

  TCanvas *errCanv= new TCanvas ("errCanv", "errCanv", 1000, 700);
  errCanv->cd ();
  gPad->SetLogy (1); errors->SetStats (111111);
  errors->GetXaxis()->SetTitle("Bin"); errors->GetYaxis()->SetTitle("Error");
  errors->SetLineColor(kRed);
  errors->Draw(); 
  errorstat->Draw("SAMES");
  TLegend *legend_ = new TLegend(0.697791, 0.736607, 0.894578, 0.9375);
  legend_->SetFillColor (0); legend_w->SetFillStyle (0); legend_w->SetBorderSize (0);
  legend_->AddEntry (errors, "Unfolding error", "L");
  legend_->AddEntry (errorstat, "Stat Error", "L");
  legend_->Draw("");
  string titlerr= s+"JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+"_errors.pdf";
  errCanv->Print(titlerr.c_str()); 

  return c;
}

//////
// Save File
///////

void saveIntoFile(int numbOfJetsSelected, string whichtype, TH1D* jReco, TH1D* jTrue, TH2D* jMatx, TH1D* jMCreco, TH1D* jData){
  TFile* w = new TFile(filename.c_str(), "UPDATE");
  w->cd();
  
  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      TH1D *jReco_leading= (TH1D*) jReco->Clone("jReco");
      jReco_leading->SetName("jReco_leading");
      jReco_leading->Write();
      TH1D *jTrue_leading= (TH1D*) jTrue->Clone("jTrue");
      jTrue_leading->Write();
      TH2D *jMatx_leading= (TH2D*) jMatx->Clone("jMatx");
      jMatx_leading->Write();
      TH1D *jData_leading= (TH1D*) jData->Clone("jData");
      jData_leading->Write();
      TH1D *jMCreco_leading= (TH1D*) jMCreco->Clone("jMCreco");
      jMCreco_leading->Write();
    }
    if (numbOfJetsSelected==2) {
      TH1D *jReco_subleading= (TH1D*) jReco->Clone("jReco");
      jReco_subleading->SetName("jReco_subleading");
      jReco_subleading->Write();
      TH1D *jTrue_subleading= (TH1D*) jTrue->Clone("jTrue");
      jTrue_subleading->Write();
      
    }
    if (numbOfJetsSelected==3) {
      TH1D *jReco_subsubleading= (TH1D*) jReco->Clone("jReco");
      jReco_subsubleading->SetName("jReco_subsubleading");
      jReco_subsubleading->Write();
      TH1D *jTrue_subsubleading= (TH1D*) jTrue->Clone("jTrue");
      jTrue_subsubleading->Write();
      
    }
    if (numbOfJetsSelected==4) {
      TH1D *jReco_subsubsubleading= (TH1D*) jReco->Clone("jReco");
      jReco_subsubsubleading->SetName("jReco_subsubsubleading");
      jReco_subsubsubleading->Write();
      TH1D *jTrue_subsubsubleading= (TH1D*) jTrue->Clone("jTrue");
      jTrue_subsubsubleading->Write();
      
    }
  }

  if (whichtype=="Eta"){
    if (numbOfJetsSelected==1) {
      TH1D *jReco_leadingeta= (TH1D*) jReco->Clone("jReco");
      jReco_leadingeta->SetName("jReco_leadingeta");
      jReco_leadingeta->Write();
    }
    if (numbOfJetsSelected==2) {
      TH1D *jReco_subleadingeta= (TH1D*) jReco->Clone("jReco");
      jReco_subleadingeta->SetName("jReco_subleadingeta");
      jReco_subleadingeta->Write();
    }
    if (numbOfJetsSelected==3) {
      TH1D *jReco_subsubleadingeta= (TH1D*) jReco->Clone("jReco");
      jReco_subsubleadingeta->SetName("jReco_subsubleadingeta");
      jReco_subsubleadingeta->Write();
    }
    if (numbOfJetsSelected==4) {
      TH1D *jReco_subsubsubleadingeta= (TH1D*) jReco->Clone("jReco");
      jReco_subsubsubleadingeta->SetName("jReco_subsubsubleadingeta");
      jReco_subsubsubleadingeta->Write();
    }

  }

  if (whichtype=="Ht"){
    if (numbOfJetsSelected==1) {
     TH1D *HReco_leading= (TH1D*) jReco->Clone("jReco");
      HReco_leading->SetName("HReco_leading");
      HReco_leading->Write();
    }
    if (numbOfJetsSelected==2) {
      TH1D *HReco_subleading= (TH1D*) jReco->Clone("jReco");
      HReco_subleading->SetName("HReco_subleading");
      HReco_subleading->Write();
    }
    if (numbOfJetsSelected==3) {
      TH1D *HReco_subsubleading= (TH1D*) jReco->Clone("jReco");
      HReco_subsubleading->SetName("HReco_subsubleading");
      HReco_subsubleading->Write();
    }
    if (numbOfJetsSelected==4) {
      TH1D *HReco_subsubsubleading= (TH1D*) jReco->Clone("jReco");
      HReco_subsubsubleading->SetName("HReco_subsubsubleading");
      HReco_subsubsubleading->Write();
    }

  }

  if (whichtype=="Multiplicity"){
    TH1D* JetMultiplicityUnfolded=(TH1D*) jReco->Clone("jReco");
    JetMultiplicityUnfolded->SetName("JetMultiplicityUnfolded");
    JetMultiplicityUnfolded->Write();
    jTrue->Write();
    jMatx->Write();
    jData->Write();
    jMCreco->Write();
  }

  w->Close();
}

//Background

void correctForBackground(int numbOfJetsSelected, string whichtype, TH1D* jData, bool verbose){
  ofstream backSignificance;
  std::vector<double> bckcoeff;

  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_pT");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1Pt.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1PtMu.txt");
    }
    if (numbOfJetsSelected==2) {
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2Pt.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2PtMu.txt");
      bckcoeff=getBackgroundContributions(bkgstring,"jet_pT2");
    }
    if (numbOfJetsSelected==3) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_pT3");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3Pt.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3PtMu.txt");
    }
    if (numbOfJetsSelected==4) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_pT4");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4Pt.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4PtMu.txt");
    }
  }
  
  if (whichtype=="Eta"){
    if (numbOfJetsSelected==1) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1EtaMu.txt");
    }
    if (numbOfJetsSelected==2) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta2");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2EtaMu.txt");
    }
    if (numbOfJetsSelected==3) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta3");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3EtaMu.txt");
    }
    if (numbOfJetsSelected==4) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta4");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4EtaMu.txt");
    } 
  }

  if (whichtype=="Ht"){
    if (numbOfJetsSelected == 1){
      bckcoeff = getBackgroundContributions (bkgstring, "HT1");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1Ht.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1HtMu.txt");
    }      
    if (numbOfJetsSelected == 2){
      bckcoeff = getBackgroundContributions (bkgstring, "HT2");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2Ht.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2HtMu.txt");
    }
    if (numbOfJetsSelected == 3){
      bckcoeff = getBackgroundContributions (bkgstring, "HT3");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3Ht.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3HtMu.txt");
    }
    if (numbOfJetsSelected == 4){
      bckcoeff = getBackgroundContributions (bkgstring, "HT4");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4Ht.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4HtMu.txt");
    }
  }
  
  if (whichtype=="Multiplicity"){
    bckcoeff=getBackgroundContributions(bkgstring,"jet_Multiplicity");
    if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJetMulti.txt");
    if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJetMultiMu.txt");
  }

  for (unsigned int k=0; k<divPlot; k++){
    cout<<bckcoeff[k]<<endl;
      jData->SetBinContent(k+1, jData->GetBinContent(k+1) - bckcoeff[k]);
      jData->SetBinError(k+1, sqrt(pow(jData->GetBinError(k+1),2) + pow(sqrt(bckcoeff[k]),2)) );  //Set also the error
      
      double backvalue=bckcoeff[k];
      if (jData->GetBinContent(k+1)>0) {
        if (bckcoeff[k]<0.000000001) backvalue=0.0;
        relativebkg->SetBinContent(k+1,bckcoeff[k]/jData->GetBinContent(k+1));
        if (verbose) cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is "<<bckcoeff[k]/jData->GetBinContent(k+1)<<endl;     
      }
      else {
        if (bckcoeff[k]<0.000000001) backvalue=0.0;
        relativebkg->SetBinContent(k+1,0);
        if (verbose) cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is 0"<<endl;
      }
      if (MCstatError) backSignificance<<jData->GetBinContent(k+1)<<" "<<backvalue<<endl;
  }
}

void loopAndDumpEntries(TH1D *jData){
  for (unsigned int p=0;p<jData->GetNbinsX();p++){
    cout<<"Bin "<<p+1<<" has "<<jData->GetBinContent(p+1)<<" and error "<<jData->GetBinError(p+1)<<endl;;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////
//
//         Unfolding
//
///////////////////////////////


void UnfoldingVJets2011::LoopVJets (int numbOfJetsSelected,string whichtype, string whichalgo)
{

  cout<<"*********************************"<<endl;
  cout<<"Welcome in Unfolding of 2011 Distribution.."<<endl;
  cout<<"*********************************"<<endl;
  
  // Set the kmin, kmax, minObsPlot, maxObsPlot (those are global variables)
  setPlotsDivisionsAndRanges(numbOfJetsSelected,whichtype,whichalgo);
  cout<<"Automatic histograms allocation ("<<whichtype<<"-"<<numbOfJetsSelected<<" jets). divPlot->"<<divPlot<<" min->"<<minObsPlot<<" max->"<<maxObsPlot<<" kmin->"<<kmin<<" kmax->"<<kmax<<endl;

  double divPlot2=divPlot; double minObsPlot2=minObsPlot; double maxObsPlot2=maxObsPlot;

  if (whichtype=="Multiplicity")  {
    divPlot2=6.5; minObsPlot2=0.5;maxObsPlot2=6.5;
  }

  TH1D *jTrue = new TH1D ("jTrue", "jet Truth",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jData = new TH1D ("jData", "jet DATA Measured",divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jReco = new TH1D ("jReco", "jet Unfolded DATA",divPlot2,minObsPlot2,maxObsPlot2);
  TH2D *jMatx = new TH2D ("jMatx", "Unfolding Matrix jeet",divPlot2,minObsPlot2,maxObsPlot2,divPlot2,minObsPlot2,maxObsPlot2);
  TH1D *jMCreco = new TH1D ("jMCreco", "jet mcreco",divPlot2,minObsPlot2,maxObsPlot2);

  jData->Sumw2(); jTrue->Sumw2(); jReco->Sumw2(); jMatx->Sumw2(); jMCreco->Sumw2();

  //Instanciate trees and CO
  string sdatadir=sdata+":/validationJEC";
  if (isMu) sdatadir=sdata+":/EPTmuoReco";
  
  string smcdir=smc+":/EPTmuoReco_MC";  
  if (isMu) {
    smcdir=smc+":/EPTmuoReco_MC";
  }
  
  fA->cd (smcdir.c_str());
  gDirectory->ls("tree*");
  TTree *tree_fA= (TTree *) gDirectory->Get ("treeValidationJEC_");
  if (isMu) tree_fA= (TTree *) gDirectory->Get ("treeValidationJECMu_");
  
  fB->cd (sdatadir.c_str());
  gDirectory->ls("tree*");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");

  // Configure various closure tests, if you want to do it
  if (identityCheck || splitCheck || pythiaCheck){  
    correctForEff=false; correctForMCReweighting=false; correctForBkg=false;
    fB->cd (smcdir.c_str());
    tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");
    if (isMu) tree_fB= (TTree *) gDirectory->Get ("treeValidationJECMu_");

    if (pythiaCheck){
      fPythia = new TFile (smcpythia.c_str());
      smcpythia=smcpythia+":/EPTmuoReco_MC";
      cout<<"-------------------------------------- Pythia check! -------------------"<<endl;  cout<<smcpythia<<endl;
      fPythia->cd (smcpythia.c_str());
      gDirectory->ls("tree*");
      tree_fA= (TTree *) gDirectory->Get ("treeValidationJEC_");
    if (isMu) tree_fA= (TTree *) gDirectory->Get ("treeValidationJECMu_");
    }
  }

  //Some output to help debugging
  cout<<"#####################"<<endl;
  cout<<"You'are using"<<endl;
  cout<<sdatadir<<endl;
  cout<<smcdir<<endl;  
  cout<<"MC tree  is ->"<<tree_fA->GetName()<<endl;
  cout<<"Data tree is->"<<tree_fB->GetName()<<endl;  
  cout<<"#####################"<<endl;
  
  
  ///////////////////////////////////////
  /*costruisco la matrice di unfolding */
  ///////////////////////////////////////

  //New style for unfolding
  RooUnfoldResponse response_fillfake(jMCreco,jTrue);
  response_fillfake.UseOverflow();
  
  /* Loop Montecarlo */
  fChain = tree_fA;             
  Init (fChain);
  
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (splitCheck) {
    nentries=(int) 20.0*(nentries/100.);
    cout<<"Splitcheck is active, so Dataset A (MC) has now "<<nentries<<endl;
  }

  if (fChain == 0) return;

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      jet_Obs_gen=0;
      jet_Obs=0;
      
      if (Jet_multiplicity > 10 || Jet_multiplicity_gen > 10 ) continue;

      // Get Efficiency
      double effcorrmc=1.00;
      if (correctForMCReweighting) effcorrmc=effcorrmc*evWeight;      // Weights per il PU
      if (correctForEff) effcorrmc=effcorrmc/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);

      //Fake Fill method
      int ValidGenJets=getNumberOfValidJets(Jet_multiplicity_gen, 30.0, 2.4, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen, jet5_pt_gen, jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen);
      int ValidRecoJets=getNumberOfValidJets(Jet_multiplicity, 30.0, 2.4, jet1_pt, jet2_pt, jet3_pt, jet4_pt, jet5_pt, jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta);

      if (ValidGenJets <numbOfJetsSelected && ValidRecoJets <numbOfJetsSelected) continue;

      if (jet_Obs==0 && whichtype=="Eta") {
	jet_Obs=-99;
      } 

      if (jet_Obs_gen==0 && whichtype=="Eta") {
	jet_Obs_gen=-99;
      } 

      //If there are no Z generated, it is a fake!
      if (recoZInAcceptance && !genZInAcceptance){
	//if (ValidRecoJets >=numbOfJetsSelected) response_fillfake.Fake(jet_Obs); 
	continue;
      }
      // If there are no Z reco, it is a miss
      if (!recoZInAcceptance && genZInAcceptance){
	//if (ValidGenJets >=numbOfJetsSelected) response_fillfake.Miss(jet_Obs_gen); 
	continue;
      }

      if ( (l1_pt_gen<20 || l2_pt_gen<20) & (recoZInAcceptance) ){
	//if (ValidRecoJets >=numbOfJetsSelected) response_fillfake.Fake(jet_Obs); 
	continue;
      }

      if ( (fabs(l1_eta_gen)>2.4 || fabs(l2_eta_gen)>2.4) & (recoZInAcceptance) ){
	//if (ValidRecoJets >=numbOfJetsSelected) response_fillfake.Fake(jet_Obs); 
	continue;
      }
      
      if ( (invMass_gen>111 || invMass_gen<71) & (recoZInAcceptance) ){
	//if (ValidRecoJets >=numbOfJetsSelected) response_fillfake.Fake(jet_Obs); 
	continue;
      }
      
      //account for the gap!
      if ( (( fabs(l1_eta_gen)>1.442 & fabs(l1_eta_gen)<1.566) || ( fabs(l2_eta_gen)>1.442 & fabs(l2_eta_gen)<1.566)) && isElectron && !recoZInAcceptance){
	if (ValidGenJets >=numbOfJetsSelected) response_fillfake.Miss(jet_Obs_gen); 
        continue;
      }

      // Initialize the Observables
      setObservablesMC(numbOfJetsSelected, whichtype, jet1_pt_gen, jet2_pt_gen, jet3_pt_gen, jet4_pt_gen,  jet5_pt_gen,  jet6_pt_gen, jet1_eta_gen, jet2_eta_gen, jet3_eta_gen, jet4_eta_gen, jet5_eta_gen, jet6_eta_gen, ValidGenJets, jet1_pt, jet2_pt, jet3_pt, jet4_pt,  jet5_pt,  jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta,ValidRecoJets);  
	  
      if (ValidGenJets >=numbOfJetsSelected && ValidRecoJets >= numbOfJetsSelected) {
	response_fillfake.Fill(jet_Obs,jet_Obs_gen,effcorrmc); 
      }
      if (!(ValidGenJets >=numbOfJetsSelected) && ValidRecoJets >= numbOfJetsSelected) response_fillfake.Fake(jet_Obs); 
      if (ValidGenJets >=numbOfJetsSelected && !(ValidRecoJets >= numbOfJetsSelected)) response_fillfake.Miss(jet_Obs_gen); 

      /*      
      if (ValidGenJets >=numbOfJetsSelected && ValidRecoJets >= numbOfJetsSelected) {
	if (jet1_pt>30 && fabs(jet1_eta<2.4) && (jet1_pt_gen>30 && fabs(jet1_eta_gen)<2.4) ) response_fillfake.Fill(jet_Obs,jet_Obs_gen,effcorrmc); 
	if (!(jet1_pt>30 && fabs(jet1_eta<2.4)) && (jet1_pt_gen>30 && fabs(jet1_eta_gen)<2.4) ) response_fillfake.Miss(jet_Obs_gen); 
	if (jet1_pt>30 && fabs(jet1_eta<2.4) && !((jet1_pt_gen>30 && fabs(jet1_eta_gen)<2.4)) ) response_fillfake.Fake(jet_Obs); 
      }
      if (!(ValidGenJets >=numbOfJetsSelected) && ValidRecoJets >= numbOfJetsSelected && jet1_pt>30 && fabs(jet1_eta<2.4)) response_fillfake.Fake(jet_Obs); 
      if (ValidGenJets >=numbOfJetsSelected && !(ValidRecoJets >= numbOfJetsSelected) && jet1_pt_gen>30 && fabs(jet1_eta_gen<2.4)) response_fillfake.Miss(jet_Obs_gen); 
      */

      //Filling histograms, old way, before the cuts...
      jMatx->Fill (jet_Obs, jet_Obs_gen,effcorrmc);        
      jTrue->Fill (jet_Obs_gen);
      jMCreco->Fill (jet_Obs,effcorrmc);
    }
      
  //End Loop MC
  
  /* Loop Data */
  fChain = tree_fB;
  Init (fChain);        
  Long64_t nentries2 = fChain->GetEntriesFast ();

  if (fChain == 0) return;

  for (Long64_t jentry = 0; jentry < nentries2; jentry++){
    if (jentry < 0) break;
    double nb2 = fChain->GetEntry (jentry);
    nbytes += nb2;
    jet_Obs=0;

    if (Jet_multiplicity > 10) continue;

    setObservablesData(numbOfJetsSelected, whichtype, jet1_pt, jet2_pt, jet3_pt, jet4_pt, jet5_pt, jet6_pt, jet1_eta, jet2_eta, jet3_eta, jet4_eta, jet5_eta, jet6_eta, Jet_multiplicity);
    double effcorrdata=1.0;

    if (correctForEff && isEle) effcorrdata=effcorrdata/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
    if (Jet_multiplicity >= numbOfJetsSelected) jData->Fill (jet_Obs,effcorrdata);
  }//End loop Data

  /// Background Sub
  if (correctForBkg) correctForBackground(numbOfJetsSelected,whichtype,jData,true); //bool -> activate verbosity
  
  //////////////////////////////
  ///
  ///     Unfolding Core
  ///
  //////////////////////////////
  
  //Old stile to perform the unfolding
  RooUnfoldResponse response_j(jMCreco, jTrue, jMatx); 
  response_j.UseOverflow();
  stringstream num;

  if (Unfold){
    string method=whichalgo;
    cout<<"Running "<<method<<" method"<<endl;
    
    for (int k=kmin; k< kmax; k++){
      int myNumber=k; num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Jet pT diff xsec distribution. "+title;
      //if (whichalgo=="Bayes") jReco=performUnfolding(whichalgo, k, jData, jTrue, response_j,jMCreco, jMatx); //Specify which algo
      //if (whichalgo=="SVD") jReco=performUnfolding(whichalgo, k, jData, jTrue,response_fillfake, jMCreco,jMatx);
      jReco=performUnfolding(whichalgo, k, jData, jTrue,response_fillfake, jMCreco,jMatx);
      //jReco=performUnfolding(whichalgo, k, jData, jTrue, response_j,jMCreco, jMatx); //Specify which algo
      num.str("");
    } 
  }
  
  if (identityCheck || splitCheck || pythiaCheck){
    jReco->Scale(1./jReco->Integral());             
    jTrue->Scale(1./jTrue->Integral());
    jMCreco->Scale(1./jMCreco->Integral());
    jData->Scale(1./jData->Integral());
  }

  //Drawing Histograms
  c= drawPlots(jReco,jData,jTrue,jMCreco,numbOfJetsSelected,whichtype, whichalgo, kmin);
  c->Draw();

  //Normalization 
  double unfarea=jReco->Integral()/4890.0;
  cout<<"Your unfolding has an integral value of "<<unfarea<<endl;
  
  if (activateXSSuperseding){
    if (!isMu) {
      cout<<"Rescaled to "<<XSElectron[numbOfJetsSelected-1]<<endl;
      jReco->Scale(XSElectron[numbOfJetsSelected-1]/unfarea);
    }
    if (isMu) {
      cout<<"Rescaled to "<<XSMuon[numbOfJetsSelected-1]<<endl;
      jReco->Scale(XSMuon[numbOfJetsSelected-1]/unfarea);
    }
  }
  
  if (!Unfold) jReco=(TH1D*) jData->Clone();
  if (saveFile) saveIntoFile(numbOfJetsSelected, whichtype, jReco, jTrue, jMatx, jMCreco, jData);

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

}

