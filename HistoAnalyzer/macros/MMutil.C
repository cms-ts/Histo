#include <iostream>
#include <iomanip>
#include <string.h>
#include <math.h>
#include <istream>
#include <TLatex.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TArrow.h>

using namespace std;

// TTree *tree_;

/*
MDelete: to delete object
factorial: it returns the factorial number, used by prob
prob: it returns the poissonian probability at LumInt of having nevt events
xi: returns the minimum xi
EHF: returns the minimum sumEHF
MCanvas: returns a canvas 
MLine: draws a line
MArrows: draws an arrow
MText: writes a text
MH1clone: it clones a THF1
MH2clone: it clones a THF2
MHtoV: put the Histo content into a Vector 
IsItaZ : returns the fraction of events of a Z line in a 2 GeV bins
HFCor:  Returns the correction function for HF or Gap =0 
MStatOn(TH1F *histo)
MStatOff(TH1F *histo)
MHSetMarker(TH1F *histo, Color,Style,Size)

 */

/* void MDelete(string name){
  gDirectory->Delete(name);
  return;
}

/***********************/

int factorial(int n){
  if (n<=1)
    return(1);
  else
    n=n*factorial(n-1); // notice we just keep calling this over until we get to 1!
  return(n);
}



/***********************/

Float_t meanEvt( Float_t LumInt){

  Float_t sigma_NSD =  0.060*pow(10,-24);
  Float_t Lum_bunch = (LumInt*pow(10,30)/11346)*sigma_NSD ;

  //  cout << "Average events = " << Lum_bunch << endl;

  return(Lum_bunch);
 
}

/***********************/

Float_t prob( Float_t LumInt, int nevt){

  Float_t sigma_NSD =  0.060*pow(10,-24);
  //  Float_t sigma_NSD =  0.035*pow(10,-24);
  Float_t Lum_bunch = (LumInt*pow(10,30)/11346)*sigma_NSD ;
  Float_t pois_prob = pow(Lum_bunch,nevt) * exp(-Lum_bunch)/factorial(nevt) ;

  // cout << "Average events = " << Lum_bunch << endl;

  return(pois_prob);
 
}


/***********************/

Float_t prob_ghost( Float_t LumInt, int nevt){

  Float_t sigma_ghost =  0.035*pow(10,-24);
  Float_t Lum_bunch = (LumInt*pow(10,30)/11346)*sigma_ghost ;
  Float_t pois_prob = pow(Lum_bunch,nevt) * exp(-Lum_bunch)/factorial(nevt) ;

  cout << "Average ghost events = " << Lum_bunch << endl;

  return(pois_prob);
 
}


//******************************** // 
// selects the minimum xi
// tree_->Draw("xi(xi_PF_plus,xi_PF_minus)")

Float_t xi(Float_t xi_PF_plus, Float_t xi_PF_minus){
  if (xi_PF_plus < xi_PF_minus) {
    return(xi_PF_plus);
      }			  
    return(xi_PF_minus);
} 

//******************************** // 
// selects the minimum HF
// tree_->Draw("EHF(sumEHF_plus,sumEHF_minus)")
Float_t EHF(Float_t sumEHF_plus, Float_t sumEHF_minus){
  if (sumEHF_plus < sumEHF_minus) {
    return(sumEHF_plus);
      }			  
    return(sumEHF_minus);
}  

/***********************/

TCanvas * MCanvas( int arg1, int arg2) 
{

  TCanvas *MyC = new TCanvas("MyC","Test canvas",1);
  MyC->Divide(arg1,arg2);
  return(MyC);
}

/***********************/

void MLine(Float_t x1, Float_t y1, Float_t x2, Float_t y2 ) {
  TLine *MLine = new TLine(x1,y1,x2,y2);
  MLine->SetLineStyle(2);
  MLine->Draw();
  return;
}

/***********************/

void BLine(Float_t x1, Float_t y1, Float_t x2, Float_t y2 ) {
  TLine *BLine = new TLine(x1,y1,x2,y2);
  BLine->SetLineColor(kBlue);
  BLine->SetLineStyle(2);
  BLine->Draw();
  return;
}

/***********************/

void RLine(Float_t x1, Float_t y1, Float_t x2, Float_t y2 ) {
  TLine *RLine = new TLine(x1,y1,x2,y2);
  RLine->SetLineColor(kRed);
  RLine->SetLineStyle(2);
  RLine->Draw();
  return;
}


/***********************/

void MArrow(Float_t x1, Float_t y1, Float_t x2, Float_t y2, Float_t size, Option_t *option ) {
  TArrow *MArrow = new TArrow(x1,y1,x2,y2,size,option);
  MArrow->Draw();
  return;
}

/***********************/

void MText(Float_t x1, Float_t y1, string text, Int_t col=1){
  TLatex l;
  l.SetTextSize(0.04);
  l.SetTextColor(col);
 l.DrawLatex(x1,y1,text.c_str())   ;
 return;
}

/**********************
void MMarker(Int_t style, Int_t size, Int_t color){
  tree_->SetMarkerStyle(style);
  tree_->SetMarkerSize(size);
  tree_->SetMarkerColor(color);
  return;
}

/*********************************/

void MStatOn(TH1F *histo){
  histo->SetStats(kTRUE);
  gStyle->SetOptStat(1111111);
}


/*********************************/
void MStatOff(TH1F *histo){
  histo->SetStats(0);
}


/*********************************/

void MHSetMarker(TH1F *histo, Color_t Color, Style_t Style, Size_t Size){
  histo->SetMarkerColor(Color);
  histo->SetMarkerStyle(Style);
  histo->SetLineColor(Color);
  histo->SetMarkerSize(Size);
  return;
}

void MLogAxis(Int_t x, Int_t y){
  gPad->SetLogx(x);
  gPad->SetLogy(y);
  return;
}


/***********************************/
// MH1clone("toy", "k", EEP_all) 
// The pointer is called "name_new")
// Usage:
// TH1F *pluto;
// pluto = MH1clone("name","title",histo_old);

//TH1F* MH1clone (TH1F* histo_new, TString name_new, TString title_new, TH1F* histo_old ){
TH1F* MH1clone (TString name_new, TString title_new, TH1F* histo_old ){

  //  gDirectory->Delete(name_new);
  TH1F* histo_new =  (TH1F*) histo_old->Clone(); 
  histo_new->SetTitle(title_new); 
  histo_new->SetName(name_new); 
  histo_new->Reset();
  return histo_new;
}



/********************/

// Hystogram to Vector
// Float_t *Pcpythia = new Float_t [nbin];
// Float_t *Pepythia = new Float_t [nbin];
// NHtoV(Hpythia, Pcpythia, Pepythia);

void  MHtoV(TH1F * file_in, Float_t* content, Float_t* econtent)

{

  Int_t nbin = file_in->GetNbinsX();
  for (int i=0;i< nbin;i++){
    *(content+i) = file_in->GetBinContent(i);
    *(econtent+i) = file_in->GetBinError(i);
    //  cout << content[i] << " " << i << endl;
    // cout << econtent[i] << " " << i << endl;
  };
  return;
}


// This function returns the fraction of Z->mm events in that 2 GeV bin

/**************************************/

Float_t IsItaZ(Float_t mass){

  Float_t mass_up,mass_low;
  Int_t i = 0.;
    
  Float_t zmmprob[30] = {0,0.00151172,0.00377929,0.000755858,0.00529101,0.00529101,0.00604686,0.00604686,0.0120937,0.00831444,0.0120937,0.0226757,0.0279667,0.0468632,0.0733182,0.179138,0.266062,0.187453,0.0702948,0.0279667,0.010582,0.00755858,0.00151172,0.00377929,0.00453515,0.00151172,0.000755858,0.00226757,0.000755858,0.00151172};

  cout << zmmprob[3] << endl;
  for (i=0; i<30; i++)
    {
      mass_low = 60+i*2;
      mass_up = 62+i*2;    
      if (mass>=mass_low && mass<mass_up){
	cout << "The number  of Z->mm events in the interval "<< mass_low << " << Mx << " << mass_up << " is = " << 100*zmmprob[i]<< " %" <<endl;
	return(zmmprob[i]);
      }
    }		      
  cout << "No fraction found for your mass value" << endl;
  return 0.;
}

//******************************** // 
// Returns the correction function for HF at any energy


Float_t HFCor(Float_t istlumiPerBX, Float_t EHF)
{

  Float_t x = istlumiPerBX*6.37;  
  Float_t xl; 
  Float_t xu;
  const int xbin = 15;
  Float_t xlow[xbin] = {0., 4.,10.,20.,40.,60.,90.,120.,
			150.,250.,400.,600.,800.,1000.,15000. };
  Float_t slope[xbin-1] = {3.08909,1.48380, 1.08810, 0.751990,
			   0.587490,0.456329,0.318799,0.208317,
			   0.0850781,-0.113282,-0.349362,-0.729234,
			   -1.53780,-2.74242};
  
  
  if(x > 0.05) {
    for (int i=0; i<15; i++) {
      
      xl = xlow[i];
      xu = xlow[i+1];
      if ( EHF >=xl && EHF < xu) return(pow(2.71, slope[i]*x));
    }
  }

  return(1.);

}

//******************************** // 
// Returns the correction function for Castor+ HF= 0 


Float_t CastorCor(Float_t istlumiPerBX){

  Float_t par[3]={0.001922, -0.01115, 0.01678};
  Float_t x = istlumiPerBX*6.37;
  if(x > 0.05) return(1.*par[0]/(1.*par[0]+1.*par[1]*x+1.*par[2]*x*x));
  return(0.);
} 



// scale file2 so that it has the same max of file1
void M2HSameMax(TH1F *file1, TH1F *file2){

  Int_t Max1 = file1->GetMaximumBin();
  Float_t Max1Cont = file1->GetBinContent(Max1); 
  Int_t Max2 = file2->GetMaximumBin();
  Float_t Max2Cont = file2->GetBinContent(Max2); 

  Float_t scale = Max1Cont/Max2Cont;
  file2->Scale(scale);
  return;
}

// scale file2 so that it has the same max of file1
void M2HSameArea(TH1F *file1, TH1F *file2){

  Float_t Max1 = file1->Integral(); 
  Float_t Max2 = file2->Integral(); 

  cout << "file 1 entries " << Max1 << " file 2 entries " << Max2 << endl;
  Float_t scale = Max1/Max2;
  file2->Scale(scale);
  return;
}
