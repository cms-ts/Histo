/**********************************
 * Get the Muscle Fit corr for muons
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
#include "TLorentzVector.h"
#include "MuScleFitCorrector.h"

///////////
// correcting muons for Muscle fit
///////////

std::vector<double> returnPtAndEtaFromTLorentz(TLorentzVector lepton){
  std::vector<double> values;
  values.push_back(lepton.Pt());
  values.push_back(lepton.Eta());
  return values;
}

TLorentzVector getNewTLorentzVectorForMu(TLorentzVector MuBefore, int charge){
  TString fitParametersFile = "MuScleFit_2011_DATA_44X.txt";
  std::vector<double> value=returnPtAndEtaFromTLorentz(MuBefore);
  MuScleFitCorrector* corrector_ = new MuScleFitCorrector(fitParametersFile);
  corrector_->applyPtCorrection(MuBefore,charge);
  std::vector<double> value2=returnPtAndEtaFromTLorentz(MuBefore);
  return MuBefore;
}



