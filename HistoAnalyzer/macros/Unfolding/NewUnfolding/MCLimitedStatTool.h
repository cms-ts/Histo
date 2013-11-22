#include "TRandom3.h"

TH2D* GetAdetCovMatrix( Int_t ntoys, Int_t seed, TH2D* fAdet, TH1D* fXini, int fNdim, int kValue,  RooUnfoldResponse response_j, TH1D *jData, TH1D *jTrue, TH1D* jMCreco, TH2D* jMatx, int numbOfJetsSelected, string whichtype){
  TH1D* unfres;
  TH2D* unfcov = (TH2D*)fAdet->Clone("unfcovmat");

  for(int i=1; i<=fNdim; i++)
    for(int j=1; j<=fNdim; j++)
      unfcov->SetBinContent(i,j,0.);
  
  //Now the toys for the detector response matrix
  TRandom3 random(seed);
          
  TH2D *fToymat = (TH2D*)fAdet->Clone("toymat");
  TH1D *toymean = (TH1D*)fXini->Clone("toymean");
  for (Int_t j=1; j<=fNdim; j++) toymean->SetBinContent(j,0.);
 
  for (int i=1; i<=ntoys; i++) {    
    for (Int_t k=1; k<=fNdim; k++) {
      for (Int_t m=1; m<=fNdim; m++) {
	if (fAdet->GetBinContent(k,m)) {
	  fToymat->SetBinContent(k, m, random.Poisson(fAdet->GetBinContent(k,m)));
	}
      }
    }
  
  

    //unfres = Unfold(kValue);
    unfres= performUnfolding("SVD", kValue, jData, jTrue, response_j, jMCreco, jMatx, numbOfJetsSelected, whichtype);

    for (Int_t j=1; j<=fNdim; j++) {
      toymean->SetBinContent(j, toymean->GetBinContent(j) + unfres->GetBinContent(j)/ntoys);
    }
  }

           
  // Reset the random seed
  random.SetSeed(seed);
  
  for (int i=1; i<=ntoys; i++) {
    for (Int_t k=1; k<=fNdim; k++) {
      for (Int_t m=1; m<=fNdim; m++) {
	if (fAdet->GetBinContent(k,m))
	  fToymat->SetBinContent(k, m, random.Poisson(fAdet->GetBinContent(k,m)));
      }
    }
    
    unfres= performUnfolding("SVD", kValue, jData, jTrue, response_j, jMCreco, jMatx, numbOfJetsSelected, whichtype);
    //    unfres= performUnfolding("SVD",kValue, jData, jTrue, response_j, jMCreco, jMatx);
    
    for (Int_t j=1; j<=fNdim; j++) {
      for (Int_t k=1; k<=fNdim; k++) {
	unfcov->SetBinContent(j,k,unfcov->GetBinContent(j,k) + ( (unfres->GetBinContent(j) - toymean->GetBinContent(j))*(unfres->GetBinContent(k) - toymean->GetBinContent(k))/(ntoys-1)) );
      }
    }
  }
   
  delete unfres;
  return unfcov;
}

