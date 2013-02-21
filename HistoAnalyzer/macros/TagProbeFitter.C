/////////////////////////////////////////////////
//  Usage:                                     //
//     -$ root -l                              //
//     .L TagProbeFitter.C++                   //
//     TagProbeFitter t                        //
//     t.eff_vs_nJets()                        //
//                                             //
//  Choose input file in:                      //
//  'TAPfitter_config.txt'                     //
//                                             //
//  Output is written to:                      //
//  /gpfs/cms/data/2011/TaP/efficiencies.root  //
//                                             //
//  For questions,                             //
//  kindly request to:                         //
//  andrea.schizzi@ts.infn.it                  //
/////////////////////////////////////////////////


#include <stdlib.h>
#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>

#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooWorkspace.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooDataSet.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooDataHist.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooRealVar.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooFormulaVar.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooAddPdf.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooGlobalFunc.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooCategory.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooSimultaneous.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooPlot.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooFitResult.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooMinuit.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooNLLVar.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooGenericPdf.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooExtendPdf.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooMinimizer.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooAbsReal.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooHistPdf.h"
#include "/afs/infn.it/ts/project/cms/software/slc5_amd64_gcc434/lcg/roofit/5.28.00a-cms10/include/RooMath.h"

using namespace RooFit ;
using namespace std ;

class TagProbeFitter {
  double TAP_efficiency;
  double TAP_efficiency_uncertainty;
  double ratio_truth_bkg_pass;
  double ratio_truth_bkg_fail;
public:
  void eff_vs_PtEta_edmStyle();
  void eff_vs_PtEta_edmStyle_MC();
  void effMU_vs_PtEta_edmStyle();
  void effMU_vs_PtEta_edmStyle_MC();
  void signal_yields();
  void validate_BWCB();
  int doFit_BWCB(string, string, string);
  int doFit_BWCB_FixedFailSig(string, string, string);
  int doFit_BWCB_WP80(string, string, string);
  int doFit_BWCB_FixedPassSig(string, string, string);
  int doFit_BWCB_edm(TH1D*, TH1D*, TH1D*, TH1D*, string, bool, bool, bool);
  int doFit_BWCB_edm_MC(TH1D*, TH1D*, TH1D*, TH1D*, string);
  void toy_BWCB();
  void doFit_DATA_cruijff(string, string);
  void doFit_MC_cruijff(string, string);
};

//////////////////////////////////////
// Main routine of the TAP analysis //
//////////////////////////////////////


void TagProbeFitter::eff_vs_PtEta_edmStyle() {
  
  // Load file names from config.txt
  string stupid, DATA_filename, MC_filename, pass_data_, fail_data_, output_name_, output_rootuple;

  ifstream in;
  in.open("TAPfitter_config.txt");
  in >> stupid >> DATA_filename;
  in >> stupid >> MC_filename;
  in >> stupid >> output_rootuple;
  in.close();


  //DATA efficiencies:

  TFile input_file_DATA(DATA_filename.c_str(),"READ");
  TFile input_file_MC(MC_filename.c_str(),"READ");

  // WP80 2st LEG Efficiency (DATA):

  TH2F DATA_WP80_Probe("DATA_WP80_Probe","Electron efficieny;eta BINS;pt BINS",4,0,4,4,0,4);
  DATA_WP80_Probe.Sumw2();

  TH2F  DATA_HLTele8NOTele17_Probe("DATA_HLTele8NOTele17_Probe","Electron efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  DATA_HLTele8NOTele17_Probe.Sumw2();

  TH2F  DATA_HLTele17_Probe("DATA_HLTele17_Probe","Electron efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  DATA_HLTele17_Probe.Sumw2();

  TH2F  DATA_RECO_Probe("DATA_RECO_Probe","Reconstruction efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  DATA_RECO_Probe.Sumw2();

  char dummy[100];
  bool isLowPt;
  bool isRECO,isHLT;

  for (int nj=0;nj<4;nj++) {
    for (int mj=0;mj<4;mj++) {

      sprintf (dummy, "EPTwp80_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTwp80_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      input_file_MC.cd();
      TH1D* hist_passing_MC_WP80 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_WP80 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPTwp80/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTwp80/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      input_file_DATA.cd();
      TH1D* hist_passing_DATA_WP80 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_WP80 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isLowPt = false;
      isRECO = false;
      isHLT = false;

      doFit_BWCB_edm(hist_passing_MC_WP80, hist_failing_MC_WP80, hist_passing_DATA_WP80, hist_failing_DATA_WP80, output_name_, isLowPt, isRECO, isHLT);
      DATA_WP80_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      DATA_WP80_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);

      sprintf (dummy, "EPThltele8NOTele17_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltele8NOTele17_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      input_file_MC.cd();
      TH1D* hist_passing_MC_HLTele8NOTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_HLTele8NOTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPThltele8NOTele17/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltele8NOTele17/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele8NOTele17_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      input_file_DATA.cd();
      TH1D* hist_passing_DATA_HLTele8NOTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_HLTele8NOTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      doFit_BWCB_edm_MC(hist_passing_MC_HLTele8NOTele17, hist_failing_MC_HLTele8NOTele17, hist_passing_DATA_HLTele8NOTele17, hist_failing_DATA_HLTele8NOTele17, output_name_);
      DATA_HLTele8NOTele17_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      DATA_HLTele8NOTele17_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);

      sprintf (dummy, "EPThltele17_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltele17_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      input_file_MC.cd();
      TH1D* hist_passing_MC_HLTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_HLTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPThltele17/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltele17/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      input_file_DATA.cd();
      TH1D* hist_passing_DATA_HLTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_HLTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isRECO = false;
      isHLT = true;
      isLowPt = false;
      if (mj < 2) isLowPt = true;

      doFit_BWCB_edm(hist_passing_MC_HLTele17, hist_failing_MC_HLTele17, hist_passing_DATA_HLTele17, hist_failing_DATA_HLTele17, output_name_, isLowPt, isRECO, isHLT);
      DATA_HLTele17_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      DATA_HLTele17_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);

      sprintf (dummy, "EPTreco_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTreco_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      input_file_MC.cd();
      TH1D* hist_passing_MC_RECO = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_RECO = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPTreco/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTreco/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_RECO_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      input_file_DATA.cd();
      TH1D* hist_passing_DATA_RECO = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_RECO = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isRECO = true;
      isHLT = false;
      isLowPt = false;
      if (mj < 2) isLowPt = true;

      doFit_BWCB_edm(hist_passing_MC_RECO, hist_failing_MC_RECO, hist_passing_DATA_RECO, hist_failing_DATA_RECO, output_name_, isLowPt, isRECO, isHLT);
      DATA_RECO_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      DATA_RECO_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);
    }
  }

  input_file_MC.Close();
  input_file_DATA.Close();

  //Compute global efficiencies:

  TH2F DATA_triggerEfficiency("DATA_triggerEfficiency","Trigger efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  DATA_triggerEfficiency.Sumw2();
  DATA_triggerEfficiency.Add(&DATA_HLTele8NOTele17_Probe);
  DATA_triggerEfficiency.Add(&DATA_HLTele17_Probe);

  TH2F DATA_globalEfficiency("DATA_globalEfficiency","Global efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  DATA_globalEfficiency.Sumw2();
  DATA_globalEfficiency.Add(&DATA_triggerEfficiency);
  DATA_globalEfficiency.Multiply(&DATA_WP80_Probe);
  DATA_globalEfficiency.Multiply(&DATA_RECO_Probe);

  // Write histos to file:
  
  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.mkdir("efficiency_vs_PtEta");
  output_file.cd("efficiency_vs_PtEta");

  DATA_WP80_Probe.Write();
  DATA_HLTele8NOTele17_Probe.Write();
  DATA_HLTele17_Probe.Write();
  DATA_RECO_Probe.Write();

  DATA_triggerEfficiency.Write();
  DATA_globalEfficiency.Write();

  output_file.Close();

}



// E. Di Marco inspired efficiency measurement as a function of electron pseudorapidity (eta) and transverse momentum (pt) MC:

void TagProbeFitter::eff_vs_PtEta_edmStyle_MC() {
  
  // Load file names from config.txt
  string stupid, DATA_filename, MC_filename, pass_data_, fail_data_, output_name_, output_rootuple;

  ifstream in;
  in.open("TAPfitter_config.txt");
  in >> stupid >> DATA_filename;
  in >> stupid >> MC_filename;
  in >> stupid >> output_rootuple;
  in.close();


  //DATA efficiencies:

  TFile input_file_MC(MC_filename.c_str(),"READ");

  // WP80 2st LEG Efficiency (DATA):

  TH2F  MC_WP80_Probe("MC_WP80_Probe","Electron efficieny;eta BINS;pt BINS",4,0,4,4,0,4);
  MC_WP80_Probe.Sumw2();

  TH2F  MC_HLTele8NOTele17_Probe("MC_HLTele8NOTele17_Probe","Electron efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  MC_HLTele8NOTele17_Probe.Sumw2();

  TH2F  MC_HLTele17_Probe("MC_HLTele17_Probe","Electron efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  MC_HLTele17_Probe.Sumw2();

  TH2F  MC_RECO_Probe("MC_RECO_Probe","Reconstruction efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  MC_RECO_Probe.Sumw2();

  TH2F  MC_TruthRatio_bkg_pass("MC_TruthRatio_bkg_pass","Ratio MC-DY bkg over MCtruth bkg (pass probes);eta BINS;pt BINS",4,0,4,4,0,4);
  MC_TruthRatio_bkg_pass.Sumw2();

  TH2F  MC_TruthRatio_bkg_fail("MC_TruthRatio_bkg_fail","Ratio MC-DY bkg over MCtruth bkg (fail probes);eta BINS;pt BINS",4,0,4,4,0,4);
  MC_TruthRatio_bkg_fail.Sumw2();

  bool isLowPt;
  bool isRECO,isHLT;
  char dummy[100];

  for (int nj=0;nj<4;nj++) {
    for (int mj=0;mj<4;mj++) {

      sprintf (dummy, "EPTwp80_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTwp80_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      TH1D* hist_passing_MC_WP80 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_WP80 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPTwp80/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTwp80/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_WP80_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      TH1D* hist_passing_DATA_WP80 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_WP80 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isLowPt = false;
      isRECO = false;
      isHLT = false;

      doFit_BWCB_edm(hist_passing_MC_WP80, hist_failing_MC_WP80, hist_passing_DATA_WP80, hist_failing_DATA_WP80, output_name_,isLowPt, isRECO, isHLT);
      MC_WP80_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      MC_WP80_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);
      MC_TruthRatio_bkg_pass.SetBinContent(nj+1,mj+1,ratio_truth_bkg_pass);
      MC_TruthRatio_bkg_fail.SetBinContent(nj+1,mj+1,ratio_truth_bkg_fail);

      sprintf (dummy, "EPThltele8NOTele17_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltele8NOTele17_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      TH1D* hist_passing_MC_HLTele8NOTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_HLTele8NOTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPThltele8NOTele17/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltele8NOTele17/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele8NOTele17_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      TH1D* hist_passing_DATA_HLTele8NOTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_HLTele8NOTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      doFit_BWCB_edm_MC(hist_passing_MC_HLTele8NOTele17, hist_failing_MC_HLTele8NOTele17, hist_passing_DATA_HLTele8NOTele17, hist_failing_DATA_HLTele8NOTele17, output_name_);
      MC_HLTele8NOTele17_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      MC_HLTele8NOTele17_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);

      sprintf (dummy, "EPThltele17_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltele17_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      TH1D* hist_passing_MC_HLTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_HLTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPThltele17/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltele17/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele17_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      TH1D* hist_passing_DATA_HLTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_HLTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isHLT = true;
      isRECO = false;
      isLowPt = false;
      if (mj < 2) isLowPt = true;

      doFit_BWCB_edm(hist_passing_MC_HLTele17, hist_failing_MC_HLTele17, hist_passing_DATA_HLTele17, hist_failing_DATA_HLTele17, output_name_, isLowPt, isRECO, isHLT);
      MC_HLTele17_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      MC_HLTele17_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);

      sprintf (dummy, "EPTreco_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTreco_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      TH1D* hist_passing_MC_RECO = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_RECO = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPTreco/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTreco/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_RECO_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      TH1D* hist_passing_DATA_RECO = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_RECO = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isRECO = true;
      isHLT = false;
      isLowPt = false;
      if (mj < 2) isLowPt = true;

      doFit_BWCB_edm(hist_passing_MC_RECO, hist_failing_MC_RECO, hist_passing_DATA_RECO, hist_failing_DATA_RECO, output_name_, isLowPt, isRECO, isHLT);
      MC_RECO_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      MC_RECO_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);
    }
  }

  input_file_MC.Close();

  //Compute global efficiencies:

  TH2F MC_triggerEfficiency("MC_triggerEfficiency","Trigger efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  MC_triggerEfficiency.Sumw2();
  MC_triggerEfficiency.Add(&MC_HLTele8NOTele17_Probe);
  MC_triggerEfficiency.Add(&MC_HLTele17_Probe);

  TH2F MC_globalEfficiency("MC_globalEfficiency","Global efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  MC_globalEfficiency.Sumw2();
  MC_globalEfficiency.Add(&MC_triggerEfficiency);
  MC_globalEfficiency.Multiply(&MC_WP80_Probe);
  MC_globalEfficiency.Multiply(&MC_RECO_Probe);

  // Write histos to file:
  
  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.mkdir("efficiency_vs_PtEta");
  output_file.cd("efficiency_vs_PtEta");

  MC_WP80_Probe.Write();
  MC_HLTele8NOTele17_Probe.Write();
  MC_HLTele17_Probe.Write();
  MC_RECO_Probe.Write();

  MC_triggerEfficiency.Write();
  MC_globalEfficiency.Write();

  MC_TruthRatio_bkg_pass.Write();
  MC_TruthRatio_bkg_fail.Write();

  output_file.Close();

}


// E. Di Marco inspired efficiency measurement as a function of muon pseudorapidity (eta) and transverse momentum (pt):

void TagProbeFitter::effMU_vs_PtEta_edmStyle() {
  
  // Load file names from config.txt
  string stupid, DATA_filename, MC_filename, pass_data_, fail_data_, output_name_, output_rootuple;

  ifstream in;
  in.open("TAPfitter_configMU.txt");
  in >> stupid >> DATA_filename;
  in >> stupid >> MC_filename;
  in >> stupid >> output_rootuple;
  in.close();


  //DATA efficiencies:

  TFile input_file_DATA(DATA_filename.c_str(),"READ");
  TFile input_file_MC(MC_filename.c_str(),"READ");

  // WP80 2st LEG Efficiency (DATA):

  TH2F DATA_WP80_Probe("DATA_WP80_Probe","Muon efficieny;eta BINS;pt BINS",4,0,4,4,0,4);
  DATA_WP80_Probe.Sumw2();

  TH2F  DATA_HLTele17_Probe("DATA_HLTele17_Probe","Muon efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  DATA_HLTele17_Probe.Sumw2();

  TH2F  DATA_RECO_Probe("DATA_RECO_Probe","Reconstruction efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  DATA_RECO_Probe.Sumw2();

  bool isLowPt;
  bool isRECO,isHLT;
  char dummy[100];

  for (int nj=0;nj<4;nj++) {
    for (int mj=0;mj<4;mj++) {

      sprintf (dummy, "EPTmuoWp80_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTmuoWp80_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      input_file_MC.cd();
      TH1D* hist_passing_MC_WP80 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_WP80 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPTmuoWp80/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTmuoWp80/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      input_file_DATA.cd();
      TH1D* hist_passing_DATA_WP80 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_WP80 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isLowPt = false;
      isRECO = false;
      isHLT = false;

      doFit_BWCB_edm(hist_passing_MC_WP80, hist_failing_MC_WP80, hist_passing_DATA_WP80, hist_failing_DATA_WP80, output_name_,isLowPt, isRECO, isHLT);
      DATA_WP80_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      DATA_WP80_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);

      sprintf (dummy, "EPThltmuoTight_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltmuoTight_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      input_file_MC.cd();
      TH1D* hist_passing_MC_HLTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_HLTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPThltmuoTight/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltmuoTight/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      input_file_DATA.cd();
      TH1D* hist_passing_DATA_HLTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_HLTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isHLT = true;
      isRECO = false;
      isLowPt = false;
      if (mj < 2) isLowPt = true;

      doFit_BWCB_edm(hist_passing_MC_HLTele17, hist_failing_MC_HLTele17, hist_passing_DATA_HLTele17, hist_failing_DATA_HLTele17, output_name_,isLowPt, isRECO, isHLT);
      DATA_HLTele17_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      DATA_HLTele17_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);

      sprintf (dummy, "EPTmuoReco_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTmuoReco_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      input_file_MC.cd();
      TH1D* hist_passing_MC_RECO = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_RECO = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPTmuoReco/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTmuoReco/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_RECO_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      input_file_DATA.cd();
      TH1D* hist_passing_DATA_RECO = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_RECO = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isRECO = true;
      isHLT = false;
      isLowPt = false;
      if (mj < 2) isLowPt = true;

      doFit_BWCB_edm(hist_passing_MC_RECO, hist_failing_MC_RECO, hist_passing_DATA_RECO, hist_failing_DATA_RECO, output_name_,isLowPt, isRECO, isHLT);
      DATA_RECO_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      DATA_RECO_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);
    }
  }

  input_file_MC.Close();
  input_file_DATA.Close();

  //Compute global efficiencies:

  TH2F DATA_globalEfficiency("DATA_globalEfficiency","Global efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  DATA_globalEfficiency.Sumw2();
  DATA_globalEfficiency.Add(&DATA_HLTele17_Probe);
  DATA_globalEfficiency.Multiply(&DATA_WP80_Probe);
  DATA_globalEfficiency.Multiply(&DATA_RECO_Probe);

  // Write histos to file:
  
  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.mkdir("efficiency_vs_PtEta");
  output_file.cd("efficiency_vs_PtEta");

  DATA_WP80_Probe.Write();
  DATA_HLTele17_Probe.Write();
  DATA_RECO_Probe.Write();

  DATA_globalEfficiency.Write();

  output_file.Close();

}



// E. Di Marco inspired efficiency measurement as a function of muon pseudorapidity (eta) and transverse momentum (pt) MC:

void TagProbeFitter::effMU_vs_PtEta_edmStyle_MC() {
  
  // Load file names from config.txt
  string stupid, DATA_filename, MC_filename, pass_data_, fail_data_, output_name_, output_rootuple;

  ifstream in;
  in.open("TAPfitter_configMU.txt");
  in >> stupid >> DATA_filename;
  in >> stupid >> MC_filename;
  in >> stupid >> output_rootuple;
  in.close();


  //DATA efficiencies:

  TFile input_file_MC(MC_filename.c_str(),"READ");

  // WP80 2st LEG Efficiency (DATA):

  TH2F  MC_WP80_Probe("MC_WP80_Probe","Muon efficieny;eta BINS;pt BINS",4,0,4,4,0,4);
  MC_WP80_Probe.Sumw2();

  TH2F  MC_HLTele17_Probe("MC_HLTele17_Probe","Muon efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  MC_HLTele17_Probe.Sumw2();

  TH2F  MC_RECO_Probe("MC_RECO_Probe","Reconstruction efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  MC_RECO_Probe.Sumw2();

  TH2F  MC_TruthRatio_bkg_pass("MC_TruthRatio_bkg_pass","Ratio MC-DY bkg over MCtruth bkg (pass probes);eta BINS;pt BINS",4,0,4,4,0,4);
  MC_TruthRatio_bkg_pass.Sumw2();

  TH2F  MC_TruthRatio_bkg_fail("MC_TruthRatio_bkg_fail","Ratio MC-DY bkg over MCtruth bkg (fail probes);eta BINS;pt BINS",4,0,4,4,0,4);
  MC_TruthRatio_bkg_fail.Sumw2();

  bool isLowPt;
  bool isRECO,isHLT;
  char dummy[100];

  for (int nj=0;nj<4;nj++) {
    for (int mj=0;mj<4;mj++) {

      sprintf (dummy, "EPTmuoWp80_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTmuoWp80_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      TH1D* hist_passing_MC_WP80 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_WP80 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPTmuoWp80/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTmuoWp80/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_WP80_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      TH1D* hist_passing_DATA_WP80 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_WP80 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isLowPt = false;
      isRECO = false;
      isHLT = false;

      doFit_BWCB_edm(hist_passing_MC_WP80, hist_failing_MC_WP80, hist_passing_DATA_WP80, hist_failing_DATA_WP80, output_name_,isLowPt, isRECO, isHLT);
      MC_WP80_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      MC_WP80_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);
      MC_TruthRatio_bkg_pass.SetBinContent(nj+1,mj+1,ratio_truth_bkg_pass);
      MC_TruthRatio_bkg_fail.SetBinContent(nj+1,mj+1,ratio_truth_bkg_fail);

      sprintf (dummy, "EPThltmuoTight_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltmuoTight_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      TH1D* hist_passing_MC_HLTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_HLTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPThltmuoTight/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPThltmuoTight/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele17_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      TH1D* hist_passing_DATA_HLTele17 = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_HLTele17 = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isRECO = false;
      isHLT = true;
      isLowPt = false;
      if (mj < 2) isLowPt = true;

      doFit_BWCB_edm(hist_passing_MC_HLTele17, hist_failing_MC_HLTele17, hist_passing_DATA_HLTele17, hist_failing_DATA_HLTele17, output_name_,isLowPt, isRECO, isHLT);
      MC_HLTele17_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      MC_HLTele17_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);

      sprintf (dummy, "EPTmuoReco_MC/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTmuoReco_MC/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      TH1D* hist_passing_MC_RECO = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_MC_RECO = (TH1D*) gDirectory->Get(fail_data_.c_str());

      sprintf (dummy, "EPTmuoReco/probepass%deta%dpt", nj+1, mj+1);
      pass_data_ = dummy;
      sprintf (dummy, "EPTmuoReco/probefail%deta%dpt", nj+1, mj+1);
      fail_data_ = dummy;
      sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_RECO_Probe_%deta%dpt.png", nj+1, mj+1);
      output_name_ = dummy;
      TH1D* hist_passing_DATA_RECO = (TH1D*) gDirectory->Get(pass_data_.c_str());
      TH1D* hist_failing_DATA_RECO = (TH1D*) gDirectory->Get(fail_data_.c_str());

      isRECO = true;
      isHLT = false;
      isLowPt = false;
      if (mj < 2) isLowPt = true;

      doFit_BWCB_edm(hist_passing_MC_RECO, hist_failing_MC_RECO, hist_passing_DATA_RECO, hist_failing_DATA_RECO, output_name_,isLowPt, isRECO, isHLT);
      MC_RECO_Probe.SetBinContent(nj+1,mj+1,TAP_efficiency);
      MC_RECO_Probe.SetBinError(nj+1,mj+1,TAP_efficiency_uncertainty);
    }
  }

  input_file_MC.Close();

  //Compute global efficiencies:

  TH2F MC_globalEfficiency("MC_globalEfficiency","Global efficiency;eta BINS;pt BINS",4,0,4,4,0,4);
  MC_globalEfficiency.Sumw2();
  MC_globalEfficiency.Add(&MC_HLTele17_Probe);
  MC_globalEfficiency.Multiply(&MC_WP80_Probe);
  MC_globalEfficiency.Multiply(&MC_RECO_Probe);

  // Write histos to file:
  
  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.mkdir("efficiency_vs_PtEta");
  output_file.cd("efficiency_vs_PtEta");

  MC_WP80_Probe.Write();
  MC_HLTele17_Probe.Write();
  MC_RECO_Probe.Write();

  MC_globalEfficiency.Write();

  MC_TruthRatio_bkg_pass.Write();
  MC_TruthRatio_bkg_fail.Write();

  output_file.Close();

}


//////////////////////////////////////
//    Validation ROUTINE: BW+CB     //
//////////////////////////////////////

void TagProbeFitter::validate_BWCB() {

  TH1F  pulls_distrib("pulls_distrib","pulls_distrib",80,-4,4);

  TFile output_file_validation("validation_BWCB_evts10k.root","UPDATE");

  for (int i=0; i<3000; i++) {
    toy_BWCB();
    pulls_distrib.Fill((TAP_efficiency-0.8)/TAP_efficiency_uncertainty);
  }

  pulls_distrib.Write();
  output_file_validation.Close();

}



////////////////////////////////////
// Ztoee signal extraction        //
////////////////////////////////////

void TagProbeFitter::signal_yields() {
  
  // Load file names from config.txt
  string stupid, DATA_filename, MC_filename, pass_data_, pass_data_hs_, output_name_, output_rootuple;

  ifstream in;
  in.open("signalYield_config.txt");
  in >> stupid >> DATA_filename;
  in >> stupid >> MC_filename;
  in >> stupid >> output_rootuple;
  in.close();

  //DATA yields:

  TFile input_file_DATA(MC_filename.c_str(),"READ");

  // Histogram with results:

  TH1F  SigYields_vs_nJets("SigYields_vs_nJets","Signal yields vs # Jets;# Jets;signal events",6,0,6);
  SigYields_vs_nJets.Sumw2();
  SigYields_vs_nJets.SetLineColor(1);
  SigYields_vs_nJets.SetMarkerColor(1);
  SigYields_vs_nJets.SetFillColor(1);
  SigYields_vs_nJets.SetFillStyle(3001);

  TH1F  BkgYields_vs_nJets("BkgYields_vs_nJets","Background yields vs leading Jet pt;# Jets;bkg events",6,0,6);
  BkgYields_vs_nJets.Sumw2();
  BkgYields_vs_nJets.SetLineColor(1);
  BkgYields_vs_nJets.SetMarkerColor(1);
  BkgYields_vs_nJets.SetFillColor(1);
  BkgYields_vs_nJets.SetFillStyle(3001);

  TH1F  SigYields_vs_leadjetpt("SigYields_vs_leadjetpt","Signal yields vs leading Jet pt;Jet pt BINS;signal events",9,0,9);
  SigYields_vs_leadjetpt.Sumw2();
  SigYields_vs_leadjetpt.SetLineColor(1);
  SigYields_vs_leadjetpt.SetMarkerColor(1);
  SigYields_vs_leadjetpt.SetFillColor(1);
  SigYields_vs_leadjetpt.SetFillStyle(3001);

  TH1F  BkgYields_vs_leadjetpt("BkgYields_vs_leadjetpt","Background yields vs leading Jet pt;Jet pt BINS;bkg events",9,0,9);
  BkgYields_vs_leadjetpt.Sumw2();
  BkgYields_vs_leadjetpt.SetLineColor(1);
  BkgYields_vs_leadjetpt.SetMarkerColor(1);
  BkgYields_vs_leadjetpt.SetFillColor(1);
  BkgYields_vs_leadjetpt.SetFillStyle(3001);

  input_file_DATA.cd("TAPwp80");

  char dummy[100];

  double sigyield_value, sigyield_error;
  double bkgyield_value, bkgyield_error;

  // JET MULTIPLICITY:
  //  for (int nj=0;nj<6;nj++) {
  for (int nj=0;nj<1;nj++) {
    /*
    sprintf (dummy, "probepass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "probepass%dJet_hs", nj);
    pass_data_hs_ = dummy;
    sprintf (dummy, "/afs/infn.it/ts/user/schizzi/html/yields/MC/SignalYields_%dJet.png", nj);
    output_name_ = dummy;
    */
    sprintf (dummy, "probepass_mee");
    pass_data_ = dummy;
    sprintf (dummy, "probepass_mee_hs");
    pass_data_hs_ = dummy;
    sprintf (dummy, "/afs/infn.it/ts/user/schizzi/html/yields/MC/SignalYields_INCLUSIVE.png");
    output_name_ = dummy;

    TH1D *pass_data; 
    gDirectory->GetObject(pass_data_.c_str(),pass_data);
    THStack *pass_data_hs; 
    gDirectory->GetObject(pass_data_hs_.c_str(),pass_data_hs);

    RooWorkspace w("w",kTRUE);

    // Definition of disjoint pdf's:
    // Passing PDF:
    w.factory("RooBreitWigner::bwgauss(mass[71.0,111.0], bwmean[91.1876], bwsigma[2.4952])");
    w.factory("RooCBShape::cball(mass, cbmean[0.0,-2.0,2.0], cbsigma[2.1,0.5,10.0], alpha[1.4,0.1,4.0], cbn[2.6,1.0,5.0])");
    w.factory("FCONV::signal(mass,bwgauss,cball)");
    //    w.factory("RooExponential::background(mass, cExp[-0.01,-0.08,0.0])");
    w.factory("RooExponential::background(mass, cExp[0.0])");
    w.factory("SUM::model(signalNorm[10000.0,0.0,10000000.0]*signal,backgroundNorm[100.0,0.0,1000000.0]*background)");
    //    w.factory("SUM::model(signalNorm[10000.0,0.0,10000000.0]*signal,backgroundNorm[120.0]*background)");

    // Definition of datasets:
    RooArgSet obs(*w.fundArg("mass"),"obs");
    
    RooDataHist binnedData("binnedData","my data",obs,pass_data) ;

    w.pdf("model")->fitTo(binnedData);

    TCanvas* cx2 = (TCanvas*)gDirectory->GetList()->FindObject("cx2");
    if (cx2) delete cx2;
    cx2 = new TCanvas("cx2","cx2",0,0,800,600);

    cx2->cd();

    pass_data_hs->Draw("HISTO");

    RooPlot* passFrame = w.var("mass")->frame(Title("Signal Yields")) ;
    binnedData.plotOn(passFrame);
    w.pdf("model")->plotOn(passFrame,LineColor(kGreen)) ;
    w.pdf("model")->plotOn(passFrame,LineColor(kGreen),Components("background"),LineStyle(kDashed)) ; //,ProjWData(*dataPass)
    passFrame->Draw("SAME") ;

    cx2->Print(output_name_.c_str());
    //    sleep(2);

    sigyield_value = w.var("signalNorm")->getVal();
    sigyield_error = w.var("signalNorm")->getError();
    bkgyield_value = w.var("backgroundNorm")->getVal();
    bkgyield_error = w.var("backgroundNorm")->getError();

    SigYields_vs_nJets.SetBinContent(nj+1,sigyield_value);
    SigYields_vs_nJets.SetBinError(nj+1,sigyield_error);
    BkgYields_vs_nJets.SetBinContent(nj+1,bkgyield_value);
    BkgYields_vs_nJets.SetBinError(nj+1,bkgyield_error);

  }

  // LEADING JET PT:

  for (int nj=0;nj<9;nj++) {

    sprintf (dummy, "probepass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "probepass%dleadjetpt_hs", nj);
    pass_data_hs_ = dummy;
    sprintf (dummy, "/afs/infn.it/ts/user/schizzi/html/yields/MC/SignalYields_%dleadjetpt.png", nj);
    output_name_ = dummy;

    TH1D *pass_data; 
    gDirectory->GetObject(pass_data_.c_str(),pass_data);
    THStack *pass_data_hs; 
    gDirectory->GetObject(pass_data_hs_.c_str(),pass_data_hs);

    RooWorkspace w("w",kTRUE);

    // Definition of disjoint pdf's:
    // Passing PDF:
    w.factory("RooBreitWigner::bwgauss(mass[71.0,111.0], bwmean[91.1876], bwsigma[2.4952])");
    w.factory("RooCBShape::cball(mass, cbmean[0.0,-2.0,2.0], cbsigma[2.1,0.5,10.0], alpha[1.4,0.1,4.0], cbn[2.6,1.0,5.0])");
    w.factory("FCONV::signal(mass,bwgauss,cball)");
    //    w.factory("RooExponential::background(mass, cExp[-0.01,-0.08,0.0])");
    w.factory("RooExponential::background(mass, cExp[0.0])");
    //    w.factory("SUM::model(signalNorm[10000.0,0.0,10000000.0]*signal,backgroundNorm[100.0,0.0,1000000.0]*background)");
    w.factory("SUM::model(signalNorm[10000.0,0.0,10000000.0]*signal,backgroundNorm[120.0]*background)");

    // Definition of datasets:
    RooArgSet obs(*w.fundArg("mass"),"obs");
    
    RooDataHist binnedData("binnedData","my data",obs,pass_data) ;

    w.pdf("model")->fitTo(binnedData);

    TCanvas* cx2 = (TCanvas*)gDirectory->GetList()->FindObject("cx2");
    if (cx2) delete cx2;
    cx2 = new TCanvas("cx2","cx2",0,0,800,600);

    cx2->cd();

    pass_data_hs->Draw("HISTO");

    RooPlot* passFrame = w.var("mass")->frame(Title("Signal Yields")) ;
    binnedData.plotOn(passFrame);
    w.pdf("model")->plotOn(passFrame,LineColor(kGreen)) ;
    w.pdf("model")->plotOn(passFrame,LineColor(kGreen),Components("background"),LineStyle(kDashed)) ; //,ProjWData(*dataPass)
    passFrame->Draw("SAME") ;

    cx2->Print(output_name_.c_str());
    //    sleep(2);

    sigyield_value = w.var("signalNorm")->getVal();
    sigyield_error = w.var("signalNorm")->getError();
    bkgyield_value = w.var("backgroundNorm")->getVal();
    bkgyield_error = w.var("backgroundNorm")->getError();

    SigYields_vs_leadjetpt.SetBinContent(nj+1,sigyield_value);
    SigYields_vs_leadjetpt.SetBinError(nj+1,sigyield_error);
    BkgYields_vs_leadjetpt.SetBinContent(nj+1,bkgyield_value);
    BkgYields_vs_leadjetpt.SetBinError(nj+1,bkgyield_error);

    //    delete fit_data;
  }

  input_file_DATA.Close();

  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.cd("");

  SigYields_vs_leadjetpt.Write();
  BkgYields_vs_leadjetpt.Write();
  SigYields_vs_nJets.Write();
  BkgYields_vs_nJets.Write();

  output_file.Close();

}



////////////////////////////////////
// Efficiency measurement (BW+CB) //
////////////////////////////////////

int TagProbeFitter::doFit_BWCB(string pass_data, string fail_data, string output_name) {

  TH1F* hist_passing = (TH1F*) gDirectory->Get(pass_data.c_str());
  TH1F* hist_failing = (TH1F*) gDirectory->Get(fail_data.c_str());

  double ntot_events = hist_passing->Integral() + hist_failing->Integral();

  RooWorkspace w("w",kTRUE);

  // Definition of disjoint pdf's:
  // Passing PDF:
  w.factory("RooBreitWigner::bwgauss(mass[60.0,120.0], pass_bwmean[91.1876], pass_bwsigma[2.4952])");
  w.factory("RooCBShape::pass_cball(mass, pass_cbmean[0.0,-2.0,2.0], pass_cbsigma[2.1,0.5,10.0], pass_alpha[1.4,0.1,4.0], pass_n[2.6,1.0,5.0])");
  w.factory("FCONV::signalPass(mass,bwgauss,pass_cball)");
  //  w.factory("RooExponential::backgroundPass(mass, cPass[-0.01,-0.08,0.0])");
  w.factory("RooExponential::backgroundPass(mass, cPass[-0.01,-0.1,0.1])");
  w.factory("SUM::passing_model(signalPassNorm[0.9,0.0,1.0]*signalPass,backgroundPass)");

  // Failing PDF:
  w.factory("RooCBShape::fail_cball(mass, fail_cbmean[0.0,-2.0,2.0], fail_cbsigma[2.0,0.5,10.0], fail_alpha[1.4,0.1,4.0], fail_n[2.6,1.0,5.0])");
  //w.var("fail_n")->setConstant(kTRUE);
  w.factory("FCONV::signalFail(mass,bwgauss,fail_cball)");
  //  w.factory("RooExponential::backgroundFail(mass, cFail[-0.01,-0.08,0.0])");
  w.factory("RooExponential::backgroundFail(mass, cFail[-0.01,-0.1,0.1])");
  w.factory("SUM::failing_model(signalFailNorm[0.5,0.0,1.0]*signalFail,backgroundFail)");


  // Definition of datasets:
  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist binnedData_passing("binnedData_passing","my data",obs,hist_passing) ;
  RooDataHist binnedData_failing("binnedData_failing","my data",obs,hist_failing) ;

  // Everything ready for the disjoint fits!
  w.pdf("passing_model")->fitTo(binnedData_passing);
  w.pdf("failing_model")->fitTo(binnedData_failing);

  // Definition of the simultaneous pdf for global fit:
  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.9,0.0,1.0], fSigAll[0.9,0.0,1.0],numTot[10000,0.0,1000000000.0])");
  w.factory("expr::nSignalFail('(1.0-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1.0-fSigAll)*numTot', effBkg[0.1,0.0,1.0],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1.0-effBkg)*(1.0-fSigAll)*numTot', effBkg,fSigAll,numTot)");  

  w.var("numTot")->setVal(ntot_events);

  w.factory("SUM::pdf_pass(nSignalPass*signalPass,nBkgPass*backgroundPass)");
  //  w.factory("SUM::pdf_fail(nSignalFail*signalFail,nBkgFail*backgroundFail)");
  w.factory("SUM::pdf_fail(nSignalFail*signalFail,nBkgFail*backgroundFail)");

  RooCategory efficiencyCategory("efficiencyCategory","efficiencyCategory") ;

  efficiencyCategory.defineType("Passed") ;
  efficiencyCategory.defineType("Failed") ;

  w.factory("SIMUL::pdf_global(efficiencyCategory[Passed,Failed],Passed=pdf_pass,Failed=pdf_fail)");

  // Definition of global datasets:
  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,Weight(0.5),Index(efficiencyCategory),Import("Passed", *hist_passing),Import("Failed", *hist_failing)) ;


  // And... "Let the sunshine in"!
  w.pdf("pdf_global")->fitTo(binnedData_PassFailJoined,Extended(kTRUE));

  // Plot the results:
  RooAbsData* dataPass = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed")); 
  RooAbsData* dataFail = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Failed")); 
  RooAbsData* dataAll = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed || efficiencyCategory==efficiencyCategory::Failed")); 

  TCanvas* cx2 = (TCanvas*)gDirectory->GetList()->FindObject("cx2");
  if (cx2) delete cx2;
  cx2 = new TCanvas("cx2","cx2",0,0,800,600);
  cx2->Divide(2,2);

  cx2->cd(1);
  RooPlot* passFrame = w.var("mass")->frame(Title("Passing probes")) ;
  dataPass->plotOn(passFrame);
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen)) ;
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen),Components("backgroundPass"),LineStyle(kDashed)) ;
  passFrame->Draw() ;

  cx2->cd(2);
  RooPlot* failFrame = w.var("mass")->frame(Title("Failing probes")) ;
  dataFail->plotOn(failFrame);
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed)) ;
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed),Components("backgroundFail"),LineStyle(kDashed)) ;
  failFrame->Draw() ;

  cx2->cd(3);
  RooPlot* globalFrame = w.var("mass")->frame(Title("Passing + failing probes")) ;
  dataAll->plotOn(globalFrame);
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue)) ;
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue),Components("backgroundPass,backgroundFail"),LineStyle(kDashed)) ;
  globalFrame->Draw() ;

  cx2->cd(4);
  RooPlot* parFrame = w.var("mass")->frame(Title("Fit results")) ;
  w.pdf("pdf_global")->paramOn(parFrame, dataAll, "", 2, "NELU", 0.2, 0.9, 0.9);
  parFrame->findObject(Form("%s_paramBox","pdf_global"))->Draw() ;

  cx2->Print(output_name.c_str());

  TAP_efficiency = w.var("efficiency")->getVal();
  TAP_efficiency_uncertainty = w.var("efficiency")->getError();

  cout << "---><---" << endl;
  cout << output_name << endl;
  cout << "---><---" << endl;

  sleep(2);

  return 0;
}



////////////////////////////////////
// Efficiency measurement (BW+CB) // !!! Fixed Fail-Signal SHAPE VERSION !!!
////////////////////////////////////

int TagProbeFitter::doFit_BWCB_FixedFailSig(string pass_data, string fail_data, string output_name) {

  TH1F* hist_passing = (TH1F*) gDirectory->Get(pass_data.c_str());
  TH1F* hist_failing = (TH1F*) gDirectory->Get(fail_data.c_str());

  double ntot_events = hist_passing->Integral() + hist_failing->Integral();

  RooWorkspace w("w",kTRUE);

  // Definition of disjoint pdf's:

  // Physics PDF:
  w.factory("RooBreitWigner::bwgauss(mass[71.0,111.0], pass_bwmean[91.1876], pass_bwsigma[2.4952])");

  // Passing PDF:
  w.factory("RooCBShape::pass_cball(mass, pass_cbmean[0.0,-2.0,2.0], pass_cbsigma[2.1,0.5,10.0], pass_alpha[1.4,0.1,4.0], pass_n[2.6,1.0,5.0])");
  w.factory("FCONV::signalPass(mass,bwgauss,pass_cball)");
  w.factory("EXPR::backgroundPass('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,cPass[0.0,-0.08,0.08],alphaPass[70.0,50.0,80.0],betaPass[0.01,0.0,0.05])");
  w.factory("SUM::passing_model(signalPassNorm[0.9,0.0,1.0]*signalPass,backgroundPass)");

  // Failing PDF:
  w.factory("RooCBShape::fail_cball(mass, fail_cbmean[0.0,-1.0,1.0], fail_cbsigma[2.1,0.5,10.0], fail_alpha[1.4,0.1,4.0], fail_n[2.6,1.0,5.0])");
  w.factory("FCONV::signalFail(mass,bwgauss,fail_cball)");
  w.factory("EXPR::backgroundFail('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,cFail[0.0,-0.1,0.08],alphaFail[80.0,50.0,90.0],betaFail[0.01,0.0,0.2])");
  w.factory("SUM::failing_model(signalFailNorm[0.5,0.0,1.0]*signalFail,backgroundFail)");


  // Definition of datasets:
  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist binnedData_passing("binnedData_passing","my data",obs,hist_passing) ;
  RooDataHist binnedData_failing("binnedData_failing","my data",obs,hist_failing) ;

  // Everything ready for the disjoint fits!

  w.pdf("passing_model")->fitTo(binnedData_passing);

  // Take parameters of signal shape in passing dist and put into failing dist:
  w.var("fail_cbmean")->setVal(w.var("pass_cbmean")->getVal());
  w.var("fail_cbmean")->setConstant(kTRUE);
  w.var("fail_cbsigma")->setVal(w.var("pass_cbsigma")->getVal());
  w.var("fail_cbsigma")->setConstant(kTRUE);
  w.var("fail_alpha")->setVal(w.var("pass_alpha")->getVal());
  w.var("fail_alpha")->setConstant(kTRUE);
  w.var("fail_n")->setVal(w.var("pass_n")->getVal());
  w.var("fail_n")->setConstant(kTRUE);

  w.pdf("failing_model")->fitTo(binnedData_failing);

  // Definition of the simultaneous pdf for global fit:
  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.95,0.0,1.0], fSigAll[0.9,0.0,1.0],numTot[10000,0.0,10000000.0])");
  w.factory("expr::nSignalFail('(1.0-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1.0-fSigAll)*numTot', effBkg[0.1,0.0,1.0],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1.0-effBkg)*(1.0-fSigAll)*numTot', effBkg,fSigAll,numTot)");  

  w.var("numTot")->setVal(ntot_events);

  w.factory("SUM::pdf_pass(nSignalPass*signalPass,nBkgPass*backgroundPass)");
  w.factory("SUM::pdf_fail(nSignalFail*signalFail,nBkgFail*backgroundFail)");

  RooCategory efficiencyCategory("efficiencyCategory","efficiencyCategory") ;

  efficiencyCategory.defineType("Passed") ;
  efficiencyCategory.defineType("Failed") ;

  w.factory("SIMUL::pdf_global(efficiencyCategory[Passed,Failed],Passed=pdf_pass,Failed=pdf_fail)");

  // Definition of global datasets:
  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,Weight(0.5),Index(efficiencyCategory),Import("Passed", *hist_passing),Import("Failed", *hist_failing)) ;


  // And... "Let the sunshine in"!
  w.pdf("pdf_global")->fitTo(binnedData_PassFailJoined,Extended(kTRUE));

  // Plot the results:
  RooAbsData* dataPass = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed")); 
  RooAbsData* dataFail = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Failed")); 
  RooAbsData* dataAll = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed || efficiencyCategory==efficiencyCategory::Failed")); 

  TCanvas* cx2 = (TCanvas*)gDirectory->GetList()->FindObject("cx2");
  if (cx2) delete cx2;
  cx2 = new TCanvas("cx2","cx2",0,0,800,600);
  cx2->Divide(2,2);

  cx2->cd(1);
  RooPlot* passFrame = w.var("mass")->frame(Title("Passing probes")) ;
  dataPass->plotOn(passFrame);
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen)) ;
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen),Components("backgroundPass"),LineStyle(kDashed)) ;
  passFrame->Draw() ;

  cx2->cd(2);
  RooPlot* failFrame = w.var("mass")->frame(Title("Failing probes")) ;
  dataFail->plotOn(failFrame);
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed)) ;
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed),Components("backgroundFail"),LineStyle(kDashed)) ;
  failFrame->Draw() ;

  cx2->cd(3);
  RooPlot* globalFrame = w.var("mass")->frame(Title("Passing + failing probes")) ;
  dataAll->plotOn(globalFrame);
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue)) ;
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue),Components("backgroundPass,backgroundFail"),LineStyle(kDashed)) ;
  globalFrame->Draw() ;

  cx2->cd(4);
  RooPlot* parFrame = w.var("mass")->frame(Title("Fit results")) ;
  w.pdf("pdf_global")->paramOn(parFrame, dataAll, "", 2, "NELU", 0.2, 0.9, 0.9);
  parFrame->findObject(Form("%s_paramBox","pdf_global"))->Draw() ;

  cx2->Print(output_name.c_str());

  TAP_efficiency = w.var("efficiency")->getVal();
  TAP_efficiency_uncertainty = w.var("efficiency")->getError();

  cout << "---><---" << endl;
  cout << output_name << endl;
  cout << "---><---" << endl;

  sleep(2);

  return 0;
}


////////////////////////////////////
// Efficiency measurement (BW+CB) // !!! WP80 Optimized version !!!
////////////////////////////////////

int TagProbeFitter::doFit_BWCB_WP80(string pass_data, string fail_data, string output_name) {

  TH1F* hist_passing = (TH1F*) gDirectory->Get(pass_data.c_str());
  TH1F* hist_failing = (TH1F*) gDirectory->Get(fail_data.c_str());

  double ntot_events = hist_passing->Integral() + hist_failing->Integral();

  RooWorkspace w("w",kTRUE);

  // Definition of disjoint pdf's:

  // Physics PDF:
  w.factory("RooBreitWigner::bwgauss(mass[71.0,111.0], pass_bwmean[91.1876], pass_bwsigma[2.4952])");

  // Passing PDF:
  w.factory("RooCBShape::pass_cball(mass, pass_cbmean[0.0,-2.0,2.0], pass_cbsigma[2.1,0.5,10.0], pass_alpha[1.4,0.1,4.0], pass_n[2.6,1.0,5.0])");
  w.factory("FCONV::signalPass(mass,bwgauss,pass_cball)");
  w.factory("EXPR::backgroundPass('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,cPass[0.0,-0.08,0.08],alphaPass[70.0,50.0,80.0],betaPass[0.01,0.0,0.05])");
  w.factory("SUM::passing_model(signalPassNorm[0.9,0.0,1.0]*signalPass,backgroundPass)");

  // Failing PDF:
  w.factory("RooCBShape::fail_cball(mass, fail_cbmean[0.0,-2.0,2.0], fail_cbsigma[2.1,0.5,10.0], fail_alpha[1.4,0.1,4.0], fail_n[2.6,1.0,5.0])");
  w.factory("FCONV::signalFail(mass,bwgauss,fail_cball)");
  w.factory("EXPR::backgroundFail('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,cFail[0.0,-0.1,0.08],alphaFail[80.0,50.0,90.0],betaFail[0.01,0.0,0.2])");
  w.factory("SUM::failing_model(signalFailNorm[0.5,0.0,1.0]*signalFail,backgroundFail)");


  // Definition of datasets:
  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist binnedData_passing("binnedData_passing","my data",obs,hist_passing) ;
  RooDataHist binnedData_failing("binnedData_failing","my data",obs,hist_failing) ;

  // Everything ready for the disjoint fits!

  w.pdf("passing_model")->fitTo(binnedData_passing);

  // Take parameters of signal shape in passing dist and put into failing dist:
  w.var("fail_cbmean")->setVal(w.var("pass_cbmean")->getVal());
  //  w.var("fail_cbmean")->setConstant(kTRUE);
  w.var("fail_cbsigma")->setVal(w.var("pass_cbsigma")->getVal());
  //  w.var("fail_cbsigma")->setConstant(kTRUE);
  w.var("fail_alpha")->setVal(w.var("pass_alpha")->getVal());
  //  w.var("fail_alpha")->setConstant(kTRUE);
  w.var("fail_n")->setVal(w.var("pass_n")->getVal());
  //  w.var("fail_n")->setConstant(kTRUE);

  w.pdf("failing_model")->fitTo(binnedData_failing);

  // Definition of the simultaneous pdf for global fit:
  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.95,0.0,1.0], fSigAll[0.9,0.0,1.0],numTot[10000,0.0,10000000.0])");
  w.factory("expr::nSignalFail('(1.0-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1.0-fSigAll)*numTot', effBkg[0.1,0.0,1.0],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1.0-effBkg)*(1.0-fSigAll)*numTot', effBkg,fSigAll,numTot)");  

  w.var("numTot")->setVal(ntot_events);

  w.factory("SUM::pdf_pass(nSignalPass*signalPass,nBkgPass*backgroundPass)");
  w.factory("SUM::pdf_fail(nSignalFail*signalFail,nBkgFail*backgroundFail)");

  RooCategory efficiencyCategory("efficiencyCategory","efficiencyCategory") ;

  efficiencyCategory.defineType("Passed") ;
  efficiencyCategory.defineType("Failed") ;

  w.factory("SIMUL::pdf_global(efficiencyCategory[Passed,Failed],Passed=pdf_pass,Failed=pdf_fail)");

  // Definition of global datasets:
  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,Weight(0.5),Index(efficiencyCategory),Import("Passed", *hist_passing),Import("Failed", *hist_failing)) ;


  // And... "Let the sunshine in"!
  w.pdf("pdf_global")->fitTo(binnedData_PassFailJoined,Extended(kTRUE));

  // Plot the results:
  RooAbsData* dataPass = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed")); 
  RooAbsData* dataFail = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Failed")); 
  RooAbsData* dataAll = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed || efficiencyCategory==efficiencyCategory::Failed")); 

  TCanvas* cx2 = (TCanvas*)gDirectory->GetList()->FindObject("cx2");
  if (cx2) delete cx2;
  cx2 = new TCanvas("cx2","cx2",0,0,800,600);
  cx2->Divide(2,2);

  cx2->cd(1);
  RooPlot* passFrame = w.var("mass")->frame(Title("Passing probes")) ;
  dataPass->plotOn(passFrame);
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen)) ;
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen),Components("backgroundPass"),LineStyle(kDashed)) ;
  passFrame->Draw() ;

  cx2->cd(2);
  RooPlot* failFrame = w.var("mass")->frame(Title("Failing probes")) ;
  dataFail->plotOn(failFrame);
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed)) ;
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed),Components("backgroundFail"),LineStyle(kDashed)) ;
  failFrame->Draw() ;

  cx2->cd(3);
  RooPlot* globalFrame = w.var("mass")->frame(Title("Passing + failing probes")) ;
  dataAll->plotOn(globalFrame);
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue)) ;
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue),Components("backgroundPass,backgroundFail"),LineStyle(kDashed)) ;
  globalFrame->Draw() ;

  cx2->cd(4);
  RooPlot* parFrame = w.var("mass")->frame(Title("Fit results")) ;
  w.pdf("pdf_global")->paramOn(parFrame, dataAll, "", 2, "NELU", 0.2, 0.9, 0.9);
  parFrame->findObject(Form("%s_paramBox","pdf_global"))->Draw() ;

  cx2->Print(output_name.c_str());

  TAP_efficiency = w.var("efficiency")->getVal();
  TAP_efficiency_uncertainty = w.var("efficiency")->getError();

  cout << "---><---" << endl;
  cout << output_name << endl;
  cout << "---><---" << endl;

  sleep(2);

  return 0;
}



////////////////////////////////////
// Efficiency measurement (BW+CB) // !!! Fixed Fail-Signal SHAPE VERSION !!!
////////////////////////////////////

int TagProbeFitter::doFit_BWCB_FixedPassSig(string pass_data, string fail_data, string output_name) {

  TH1F* hist_passing = (TH1F*) gDirectory->Get(pass_data.c_str());
  TH1F* hist_failing = (TH1F*) gDirectory->Get(fail_data.c_str());

  double ntot_events = hist_passing->Integral() + hist_failing->Integral();

  RooWorkspace w("w",kTRUE);

  // Definition of disjoint pdf's:

  // Physics PDF:
  w.factory("RooBreitWigner::bwgauss(mass[60.0,120.0], pass_bwmean[91.1876], pass_bwsigma[2.4952])");

  // Passing PDF:
  w.factory("RooCBShape::pass_cball(mass, pass_cbmean[0.0,-2.0,2.0], pass_cbsigma[2.1,0.5,10.0], pass_alpha[1.4,0.1,4.0], pass_n[2.6,1.0,5.0])");
  w.factory("FCONV::signalPass(mass,bwgauss,pass_cball)");
  w.factory("EXPR::backgroundPass('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,cPass[0.0,-0.08,0.08],alphaPass[70.0,50.0,100.0],betaPass[0.01,0.0,0.2])");
  w.factory("SUM::passing_model(signalPassNorm[0.5,0.0,1.0]*signalPass,backgroundPass)");

  // Failing PDF:
  w.factory("RooCBShape::fail_cball(mass, fail_cbmean[0.0,-2.0,2.0], fail_cbsigma[2.1,0.5,10.0], fail_alpha[1.4,0.1,4.0], fail_n[2.6,1.0,5.0])");
  w.factory("FCONV::signalFail(mass,bwgauss,fail_cball)");
  w.factory("EXPR::backgroundFail('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,cFail[0.0,-0.08,0.04],alphaFail[70.0,50.0,90.0],betaFail[0.01,0.0,0.2])");
  w.factory("SUM::failing_model(signalFailNorm[0.9,0.0,1.0]*signalFail,backgroundFail)");


  // Definition of datasets:
  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist binnedData_passing("binnedData_passing","my data",obs,hist_passing) ;
  RooDataHist binnedData_failing("binnedData_failing","my data",obs,hist_failing) ;

  // Everything ready for the disjoint fits!

  w.pdf("failing_model")->fitTo(binnedData_failing);

  // Take parameters of signal shape in failing dist and put into passing dist:
  w.var("pass_cbmean")->setVal(w.var("fail_cbmean")->getVal());
  w.var("pass_cbmean")->setConstant(kTRUE);
  w.var("pass_cbsigma")->setVal(w.var("fail_cbsigma")->getVal());
  w.var("pass_cbsigma")->setConstant(kTRUE);
  w.var("pass_alpha")->setVal(w.var("fail_alpha")->getVal());
  w.var("pass_alpha")->setConstant(kTRUE);
  w.var("pass_n")->setVal(w.var("fail_n")->getVal());
  w.var("pass_n")->setConstant(kTRUE);

  w.pdf("passing_model")->fitTo(binnedData_passing);

  // Definition of the simultaneous pdf for global fit:
  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.1,0.0,1.0], fSigAll[0.5,0.0,1.0],numTot[10000,0.0,1000000000.0])");
  w.factory("expr::nSignalFail('(1.0-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1.0-fSigAll)*numTot', effBkg[0.1,0.0,1.0],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1.0-effBkg)*(1.0-fSigAll)*numTot', effBkg,fSigAll,numTot)");  

  w.var("numTot")->setVal(ntot_events);

  w.factory("SUM::pdf_pass(nSignalPass*signalPass,nBkgPass*backgroundPass)");
  w.factory("SUM::pdf_fail(nSignalFail*signalFail,nBkgFail*backgroundFail)");

  RooCategory efficiencyCategory("efficiencyCategory","efficiencyCategory") ;

  efficiencyCategory.defineType("Passed") ;
  efficiencyCategory.defineType("Failed") ;

  w.factory("SIMUL::pdf_global(efficiencyCategory[Passed,Failed],Passed=pdf_pass,Failed=pdf_fail)");

  // Definition of global datasets:
  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,Weight(0.5),Index(efficiencyCategory),Import("Passed", *hist_passing),Import("Failed", *hist_failing)) ;


  // And... "Let the sunshine in"!
  w.pdf("pdf_global")->fitTo(binnedData_PassFailJoined,Extended(kTRUE));

  // Plot the results:
  RooAbsData* dataPass = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed")); 
  RooAbsData* dataFail = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Failed")); 
  RooAbsData* dataAll = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed || efficiencyCategory==efficiencyCategory::Failed")); 

  TCanvas* cx2 = (TCanvas*)gDirectory->GetList()->FindObject("cx2");
  if (cx2) delete cx2;
  cx2 = new TCanvas("cx2","cx2",0,0,800,600);
  cx2->Divide(2,2);

  cx2->cd(1);
  RooPlot* passFrame = w.var("mass")->frame(Title("Passing probes")) ;
  dataPass->plotOn(passFrame);
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen)) ;
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen),Components("backgroundPass"),LineStyle(kDashed)) ;
  passFrame->Draw() ;

  cx2->cd(2);
  RooPlot* failFrame = w.var("mass")->frame(Title("Failing probes")) ;
  dataFail->plotOn(failFrame);
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed)) ;
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed),Components("backgroundFail"),LineStyle(kDashed)) ;
  failFrame->Draw() ;

  cx2->cd(3);
  RooPlot* globalFrame = w.var("mass")->frame(Title("Passing + failing probes")) ;
  dataAll->plotOn(globalFrame);
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue)) ;
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue),Components("backgroundPass,backgroundFail"),LineStyle(kDashed)) ;
  globalFrame->Draw() ;

  cx2->cd(4);
  RooPlot* parFrame = w.var("mass")->frame(Title("Fit results")) ;
  w.pdf("pdf_global")->paramOn(parFrame, dataAll, "", 2, "NELU", 0.2, 0.9, 0.9);
  parFrame->findObject(Form("%s_paramBox","pdf_global"))->Draw() ;

  cx2->Print(output_name.c_str());

  TAP_efficiency = w.var("efficiency")->getVal();
  TAP_efficiency_uncertainty = w.var("efficiency")->getError();

  cout << "---><---" << endl;
  cout << output_name << endl;
  cout << "---><---" << endl;

  sleep(2);

  return 0;
}



////////////////////////////////////
// Efficiency measurement (BW+CB) // !!! E. Di Marco style version !!!
////////////////////////////////////

int TagProbeFitter::doFit_BWCB_edm( TH1D* hist_passing_MC, TH1D* hist_failing_MC, TH1D* hist_passing_DATA, TH1D* hist_failing_DATA, string output_name, bool isLowPt, bool isRECO, bool isHLT) {

  hist_passing_MC->Sumw2();
  hist_failing_MC->Sumw2();
  hist_passing_DATA->Sumw2();
  hist_failing_DATA->Sumw2();

  RooWorkspace w("w",kTRUE);

  // Definition of datasets:

  cout << "Si parte..." << endl;

  w.factory("RooBreitWigner::bwgauss(mass[60.0,120.0], pass_bwmean[91.1876], pass_bwsigma[2.4952])");

  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist binnedData_passing_MC("binnedData_passing_MC","my data",obs,hist_passing_MC) ;
  RooDataHist binnedData_failing_MC("binnedData_failing_MC","my data",obs,hist_failing_MC) ;

  cout << "Creo le roohistpdf..." << endl;

  RooHistPdf  zPdf_pass("zPdf_pass","zPdf_pass",obs,binnedData_passing_MC,0);
  RooHistPdf  zPdf_fail("zPdf_fail","zPdf_fail",obs,binnedData_failing_MC,0);

  w.import(RooArgSet(zPdf_pass));
  w.import(RooArgSet(zPdf_fail));
  /*
  if (isHLT && !isLowPt) {
    w.factory("RooGaussian::res_pass(mass, mean_pass[0.0,-1.0,1.0], sigma_pass[0.01])");
    w.factory("RooGaussian::res_fail(mass, mean_fail[0.0,-1.0,1.0], sigma_fail[0.01])");
  } else if (isHLT && isLowPt) {
    w.factory("RooGaussian::res_pass(mass, mean_pass[0.0,-1.0,1.0], sigma_pass[0.01,0.001,1.0])");
    w.factory("RooGaussian::res_fail(mass, mean_fail[0.0,-1.0,1.0], sigma_fail[0.01,0.001,1.0])");
  } else {
    w.factory("RooGaussian::res_pass(mass, mean_pass[0.0,-1.0,1.0], sigma_pass[0.2,0.0,2.0])");
    w.factory("RooGaussian::res_fail(mass, mean_fail[0.0,-1.0,1.0], sigma_fail[0.2,0.0,2.0])");
  }
  */
  w.factory("RooGaussian::res_pass(mass, mean_pass[0.0,-1.0,1.0], sigma_pass[0.1,0.0,2.0])");
  w.factory("RooGaussian::res_fail(mass, mean_fail[0.0,-1.0,1.0], sigma_fail[0.1,0.0,2.0])");

  w.factory("FCONV::passing_model(mass,zPdf_pass,res_pass)");
  w.factory("FCONV::failing_model(mass,zPdf_fail,res_fail)");
  /*
    RooHistPdf  zPdf_pass("zPdf_pass","zPdf_pass",obs,binnedData_passing_MC,0);
    w.import(RooArgSet(zPdf_pass));
    w.factory("RooGaussian::res_pass(mass, mean_pass[0.0,-1.0,1.0], sigma_pass[0.2,0.0,2.0])");
    w.factory("FCONV::passing_model(mass,zPdf_pass,res_pass)");
    
    RooHistPdf  failing_model("failing_model","failing_model",obs,binnedData_failing_MC,0);
    w.import(RooArgSet(failing_model));
  */

  TCanvas* cx1 = (TCanvas*)gDirectory->GetList()->FindObject("cx1");
  if (cx1) delete cx1;
  cx1 = new TCanvas("cx1","cx1",0,0,1200,800);
  cx1->Divide(3,2);

  cx1->cd(1);
  RooPlot* passFrameMC = w.var("mass")->frame(Title("Passing probes - MC truth")) ;
  binnedData_passing_MC.plotOn(passFrameMC);
  w.pdf("passing_model")->plotOn(passFrameMC,LineColor(kYellow)) ;
  passFrameMC->Draw() ;

  cx1->cd(2);
  RooPlot* failFrameMC = w.var("mass")->frame(Title("Failing probes - MC truth")) ;
  binnedData_failing_MC.plotOn(failFrameMC);
  w.pdf("failing_model")->plotOn(failFrameMC,LineColor(kViolet)) ;
  failFrameMC->Draw() ;


  //GLOBAL FIT:

  double ntot_events = hist_passing_DATA->Integral() + hist_failing_DATA->Integral();

  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.99,0.0,1.0], fSigAll[0.8,0.0,1.0],numTot[10000,0.0,1000000.0])");
  w.factory("expr::nSignalFail('(1.0-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1.0-fSigAll)*numTot', effBkg[0.001,0.0,1.0],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1.0-effBkg)*(1.0-fSigAll)*numTot', effBkg,fSigAll,numTot)");  

  if (isLowPt && isRECO) {
    w.factory("EXPR::backgroundPass('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,g_cPass[-0.05,-0.3,0.0],g_alphaPass[70.0,50.0,80.0],g_betaPass[0.08,0.008,0.2])");
    w.factory("EXPR::backgroundFail('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,g_cFail[-0.05,-0.3,0.0],g_alphaFail[70.0,50.0,80.0],g_betaFail[0.1,0.008,0.2])");
  } 
  if (!isLowPt && isRECO) {
    w.factory("EXPR::backgroundPass('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,g_cPass[-0.002,-0.3,0.0],g_alphaPass[70.0,60.0,100.0],g_betaPass[0.08,0.008,0.2])");
    w.factory("EXPR::backgroundFail('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,g_cFail[-0.002,-0.3,0.0],g_alphaFail[70.0,60.0,100.0],g_betaFail[0.08,0.008,0.2])");
  } 

  if (isLowPt && isHLT) {
    w.factory("EXPR::backgroundPass('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,g_cPass[-0.06,-0.3,0.0],g_alphaPass[70.0,50.0,80.0],g_betaPass[0.08,0.008,0.2])");
    w.factory("EXPR::backgroundFail('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,g_cFail[-0.06,-0.3,0.0],g_alphaFail[60.0,50.0,80.0],g_betaFail[0.08,0.008,0.2])");
  } 
  if (!isLowPt && isHLT) {
    w.factory("RooExponential::backgroundPass(mass, g_cPass[0.01,-0.1,0.1])");
    w.factory("EXPR::backgroundFail('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,g_cFail[0.0,-0.3,0.0],g_alphaFail[70.0,60.0,100.0],g_betaFail[0.08,0.008,0.2])");
  } 

  if (!isRECO && !isHLT){
    w.factory("RooExponential::backgroundPass(mass, g_cPass[0.0,-0.1,0.1])");
    w.factory("RooExponential::backgroundFail(mass, g_cFail[0.0,-0.1,0.1])");
  }

  w.var("numTot")->setVal(2*ntot_events);

  if ( isHLT && output_name == "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Probe_1eta1pt.png") {
  w.var("g_cPass")->setVal(-0.08);
  w.var("g_cFail")->setVal(-0.08);
  }

  w.factory("SUM::pdf_pass(nSignalPass*passing_model,nBkgPass*backgroundPass)");
  w.factory("SUM::pdf_fail(nSignalFail*failing_model,nBkgFail*backgroundFail)");

  RooCategory efficiencyCategory("efficiencyCategory","efficiencyCategory") ;

  efficiencyCategory.defineType("Passed") ;
  efficiencyCategory.defineType("Failed") ;

  w.factory("SIMUL::pdf_global(efficiencyCategory[Passed,Failed],Passed=pdf_pass,Failed=pdf_fail)");

  // Definition of global datasets:
  //  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,Weight(0.5),Index(efficiencyCategory),Import("Passed", *hist_passing_DATA),Import("Failed", *hist_failing_DATA)) ;
  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,Index(efficiencyCategory),Import("Passed", *hist_passing_DATA),Import("Failed", *hist_failing_DATA)) ;


  // And... "Let the sunshine in"!
  w.pdf("pdf_global")->fitTo(binnedData_PassFailJoined,Extended(kTRUE),NumCPU(3),Verbose(kFALSE),PrintLevel(-1),Warnings(kFALSE),PrintEvalErrors(kFALSE));

  TAP_efficiency = w.var("efficiency")->getVal();
  //  TAP_efficiency = w.var("efficiency")->getVal() - w.var("efficiency")->getError();
  TAP_efficiency_uncertainty = w.var("efficiency")->getError();
  ratio_truth_bkg_pass =(hist_passing_MC->Integral() / (hist_passing_MC->Integral() + hist_failing_MC->Integral()))/
    (w.var("efficiency")->getVal());
  ratio_truth_bkg_fail = 0.;

  // Plot the results:
  RooAbsData* dataPass = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed")); 
  RooAbsData* dataFail = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Failed")); 
  RooAbsData* dataAll = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed || efficiencyCategory==efficiencyCategory::Failed")); 

  cx1->cd(4);
  RooPlot* passFrame = w.var("mass")->frame(Title("Passing probes - DATA")) ;
  dataPass->plotOn(passFrame);
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen)) ;
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen),Components("backgroundPass"),LineStyle(kDashed)) ;
  passFrame->Draw() ;

  cx1->cd(5);
  RooPlot* failFrame = w.var("mass")->frame(Title("Failing probes - DATA")) ;
  dataFail->plotOn(failFrame);
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed)) ;
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed),Components("backgroundFail"),LineStyle(kDashed)) ;
  failFrame->Draw() ;

  cx1->cd(3);
  RooPlot* globalFrame = w.var("mass")->frame(Title("Global fit - DATA")) ;
  dataAll->plotOn(globalFrame);
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue)) ;
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue),Components("backgroundPass,backgroundFail"),LineStyle(kDashed)) ;
  globalFrame->Draw() ;

  cx1->cd(6);
  RooPlot* parFrame = w.var("mass")->frame(Title("Fit results - DATA")) ;
  w.pdf("pdf_global")->paramOn(parFrame, dataAll, "", 2, "NELU", 0.2, 0.9, 0.9);
  parFrame->findObject(Form("%s_paramBox","pdf_global"))->Draw() ;

  cx1->Print(output_name.c_str());

  //  cout << "---><---" << endl;
  //  cout << output_name << endl;
  //  cout << "---><---" << endl;

  //  sleep(2);

  return 0;
}



////////////////////////////////////
// Efficiency measurement (BW+CB) // !!! E. Di Marco style version for MonteCarlo !!!
////////////////////////////////////

int TagProbeFitter::doFit_BWCB_edm_MC( TH1D* hist_passing_MC, TH1D* hist_failing_MC, TH1D* hist_passing_DATA, TH1D* hist_failing_DATA,  string output_name) {

  hist_passing_MC->Sumw2();
  hist_failing_MC->Sumw2();
  hist_passing_DATA->Sumw2();
  hist_failing_DATA->Sumw2();

  //  TH1D* hist_passing_diff;
  //  TH1D* hist_failing_diff;

  RooWorkspace w("w",kTRUE);

  // Definition of datasets:

  w.factory("RooBreitWigner::bwgauss(mass[60.0,120.0], pass_bwmean[91.1876], pass_bwsigma[2.4952])");

  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist binnedData_passing_MC("binnedData_passing_MC","my data",obs,hist_passing_MC) ;
  RooDataHist binnedData_failing_MC("binnedData_failing_MC","my data",obs,hist_failing_MC) ;


  RooHistPdf  zPdf_pass("zPdf_pass","zPdf_pass",obs,binnedData_passing_MC,0);
  //  RooHistPdf  zPdf_fail("zPdf_fail","zPdf_fail",obs,binnedData_failing_MC,0);

  w.import(RooArgSet(zPdf_pass));
  //  w.import(RooArgSet(zPdf_fail));

  w.factory("RooGaussian::res_pass(mass, mean_pass[0.0,-1.0,1.0], sigma_pass[0.0,0.0,2.0])");
  //  w.factory("RooGaussian::res_fail(mass, mean_fail[0.0,-1.0,1.0], sigma_fail[0.0,0.0,2.0])");

  w.factory("FCONV::passing_model(mass,zPdf_pass,res_pass)");
  //  w.factory("FCONV::failing_model(mass,zPdf_fail,res_fail)");

  //  RooHistPdf  passing_model("passing_model","passing_model",obs,binnedData_passing_MC,0);
  RooHistPdf  failing_model("failing_model","failing_model",obs,binnedData_failing_MC,0);

  //  w.import(RooArgSet(passing_model));
  w.import(RooArgSet(failing_model));
  
  TCanvas* cx1 = (TCanvas*)gDirectory->GetList()->FindObject("cx1");
  if (cx1) delete cx1;
  cx1 = new TCanvas("cx1","cx1",0,0,1200,800);
  cx1->Divide(3,2);

  cx1->cd(1);
  RooPlot* passFrameMC = w.var("mass")->frame(Title("Passing probes - MC truth")) ;
  binnedData_passing_MC.plotOn(passFrameMC);
  w.pdf("passing_model")->plotOn(passFrameMC,LineColor(kYellow)) ;
  passFrameMC->Draw() ;

  cx1->cd(2);
  RooPlot* failFrameMC = w.var("mass")->frame(Title("Failing probes - MC truth")) ;
  binnedData_failing_MC.plotOn(failFrameMC);
  w.pdf("failing_model")->plotOn(failFrameMC,LineColor(kViolet)) ;
  failFrameMC->Draw() ;


  //GLOBAL FIT:

  double ntot_events = hist_passing_DATA->Integral() + hist_failing_DATA->Integral();

  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.01,0.0,1.0], fSigAll[0.9,0.0,1.0],numTot[10000,0.0,10000000.0])");
  w.factory("expr::nSignalFail('(1.0-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1.0-fSigAll)*numTot', effBkg[0.01,0.0,1.0],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1.0-effBkg)*(1.0-fSigAll)*numTot', effBkg,fSigAll,numTot)");  
 
  w.factory("EXPR::backgroundPass('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,g_cPass[-0.02,-0.3,0.0],g_alphaPass[70.0,60.0,110.0],g_betaPass[0.08,0.008,0.2])");
  w.factory("EXPR::backgroundFail('exp(@0*@1)*RooMath::erfc((@2-@0)*@3)',mass,g_cFail[-0.02,-0.3,0.0],g_alphaFail[70.0,60.0,110.0],g_betaFail[0.08,0.008,0.2])");

  w.var("numTot")->setVal(ntot_events);

  w.factory("SUM::pdf_pass(nSignalPass*passing_model,nBkgPass*backgroundPass)");
  w.factory("SUM::pdf_fail(nSignalFail*failing_model,nBkgFail*backgroundFail)");

  RooCategory efficiencyCategory("efficiencyCategory","efficiencyCategory") ;

  efficiencyCategory.defineType("Passed") ;
  efficiencyCategory.defineType("Failed") ;

  w.factory("SIMUL::pdf_global(efficiencyCategory[Passed,Failed],Passed=pdf_pass,Failed=pdf_fail)");

  // Definition of global datasets:
  //  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,Weight(0.5),Index(efficiencyCategory),Import("Passed", *hist_passing_DATA),Import("Failed", *hist_failing_DATA)) ;
  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,Index(efficiencyCategory),Import("Passed", *hist_passing_DATA),Import("Failed", *hist_failing_DATA)) ;


  // And... "Let the sunshine in"!
  w.pdf("pdf_global")->fitTo(binnedData_PassFailJoined,Extended(kTRUE),NumCPU(3),Verbose(kFALSE),PrintLevel(-1),Warnings(kFALSE),PrintEvalErrors(kFALSE));

  TAP_efficiency = w.var("efficiency")->getVal();
  //  TAP_efficiency = w.var("efficiency")->getVal() - w.var("efficiency")->getError();
  TAP_efficiency_uncertainty = w.var("efficiency")->getError();
  ratio_truth_bkg_pass =(hist_passing_MC->Integral() / (hist_passing_MC->Integral() + hist_failing_MC->Integral()))/
    (w.var("efficiency")->getVal());
  ratio_truth_bkg_fail = 0.;

  // Plot the results:
  RooAbsData* dataPass = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed")); 
  RooAbsData* dataFail = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Failed")); 
  RooAbsData* dataAll = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed || efficiencyCategory==efficiencyCategory::Failed")); 
  /*
  hist_passing_diff = hist_passing_DATA;
  hist_failing_diff = hist_failing_DATA;
  hist_passing_diff->Add(hist_passing_MC,-1.0) ;
  hist_failing_diff->Add(hist_failing_MC,-1.0) ;
  hist_passing_diff->SetLineColor(kBlue) ;
  hist_failing_diff->SetLineColor(kBlue) ;
  hist_passing_diff->SetMarkerColor(kBlue) ;
  hist_failing_diff->SetMarkerColor(kBlue) ;
  hist_passing_diff->SetMarkerStyle(20) ;
  hist_failing_diff->SetMarkerStyle(20) ;
  hist_passing_diff->SetMarkerSize(0.5) ;
  hist_failing_diff->SetMarkerSize(0.5) ;
  */
  cx1->cd(4);
  RooPlot* passFrame = w.var("mass")->frame(Title("Passing probes")) ;
  dataPass->plotOn(passFrame);
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen)) ;
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen),Components("backgroundPass"),LineStyle(kDashed)) ;
  passFrame->Draw() ;
  //  hist_passing_diff->Draw("SAME E1");

  cx1->cd(5);
  RooPlot* failFrame = w.var("mass")->frame(Title("Failing probes")) ;
  dataFail->plotOn(failFrame);
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed)) ;
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed),Components("backgroundFail"),LineStyle(kDashed)) ;
  failFrame->Draw() ;
  //  hist_failing_diff->Draw("SAME E1");

  cx1->cd(3);
  RooPlot* globalFrame = w.var("mass")->frame(Title("Global fit")) ;
  dataAll->plotOn(globalFrame);
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue)) ;
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue),Components("backgroundPass,backgroundFail"),LineStyle(kDashed)) ;
  globalFrame->Draw() ;

  cx1->cd(6);
  RooPlot* parFrame = w.var("mass")->frame(Title("Fit results - DATA")) ;
  w.pdf("pdf_global")->paramOn(parFrame, dataAll, "", 2, "NELU", 0.2, 0.9, 0.9);
  parFrame->findObject(Form("%s_paramBox","pdf_global"))->Draw() ;

  cx1->Print(output_name.c_str());

  //  cout << "---><---" << endl;
  //  cout << output_name << endl;
  //  cout << "---><---" << endl;

  //  sleep(2);

  return 0;
}



////////////////////////////////////////////////////
// DATA efficiency measurement (Good old Cruijff) //
////////////////////////////////////////////////////

void TagProbeFitter::doFit_DATA_cruijff(string pass_data, string fail_data) {
  
  TH1F* hist_passing = (TH1F*) gDirectory->Get(pass_data.c_str());
  TH1F* hist_failing = (TH1F*) gDirectory->Get(fail_data.c_str());

  RooWorkspace w("w",kTRUE);

  // Definition of disjoint pdf's:
  // Passing PDF:
  w.factory("EXPR::signalPass('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',pass_mean[89.9, 80.0, 100.0],mass[60.0,120.0],pass_sigmaL[5.3, 0.5, 10.0],pass_alphaL[0.209],pass_sigmaR[3.29, 0.5, 10.0],pass_alphaR[0.19,0,3])");
  w.var("pass_alphaL")->setConstant(kTRUE);
  w.factory("RooExponential::backgroundPass(mass[60.0,120.0], cPass[-0.055,-3,0.1])");
  w.factory("SUM::passing_model(signalPassNorm[0.0,1000000000.0]*signalPass,bkgPassNorm[0.0,1000000000.0]*backgroundPass)");

  // Failing PDF:
  w.factory("EXPR::signalFail('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',fail_mean[89.9, 80.0, 100.0],mass[60.0,120.0],fail_sigmaL[5.3, 0.5, 10.0],fail_alphaL[0.209],fail_sigmaR[3.29, 0.5, 10.0],fail_alphaR[0.19,0,3])");
  w.var("fail_alphaL")->setConstant(kTRUE);
  w.factory("RooExponential::backgroundFail(mass[60.0,120.0], cFail[-0.055,-3,0.1])");
  w.factory("SUM::failing_model(signalFailNorm[0.0,1000000000.0]*signalFail,bkgFailNorm[0.0,1000000000.0]*backgroundFail)");

  // Definition of datasets:
  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist binnedData_passing("binnedData_passing","my data",obs,hist_passing) ;
  RooDataHist binnedData_failing("binnedData_failing","my data",obs,hist_failing) ;

  // Everything ready for the disjoint fits!
  w.pdf("passing_model")->fitTo(binnedData_passing,Extended(kTRUE));
  w.pdf("failing_model")->fitTo(binnedData_failing,Extended(kTRUE));

  // Definition Global (passing + failing) PDF:
  w.factory("EXPR::global_signalPass('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',g_pass_mean[89.9, 80.0, 100.0],mass[60.0,120.0],g_pass_sigmaL[5.3, 0.5, 10.0],g_pass_alphaL[0.209],g_pass_sigmaR[3.29, 0.5, 10.0],g_pass_alphaR[0.19,0,3])");

  w.var("g_pass_alphaL")->setConstant(kTRUE);
  w.var("g_pass_mean")->setVal(w.var("pass_mean")->getVal());
  w.var("g_pass_sigmaL")->setVal(w.var("pass_sigmaL")->getVal());
  w.var("g_pass_sigmaR")->setVal(w.var("pass_sigmaR")->getVal());
  w.var("g_pass_alphaR")->setVal(w.var("pass_alphaR")->getVal());

  w.factory("RooExponential::global_backgroundPass(mass[60.0,120.0], g_cPass[-0.055,-3,0.1])");

  w.var("g_cPass")->setVal(w.var("cPass")->getVal());

  w.factory("EXPR::global_signalFail('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',g_pass_mean,mass[60.0,120.0],g_fail_sigmaL[5.3, 0.5, 10.0], g_fail_alphaL[0.209],g_fail_sigmaR[3.29, 0.5, 10.0],g_pass_alphaR)");

  w.var("g_fail_alphaL")->setConstant(kTRUE);
  w.var("g_fail_sigmaL")->setVal(w.var("fail_sigmaL")->getVal());
  w.var("g_fail_sigmaR")->setVal(w.var("fail_sigmaR")->getVal());

  w.factory("RooExponential::global_backgroundFail(mass[60.0,120.0], g_cFail[-0.055,-3,0.1])");

  w.var("g_cFail")->setVal(w.var("cFail")->getVal());

  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.8,0,1], fSigAll[.9,0,1],numTot[1,0,1e10])");
  w.factory("expr::nSignalFail('(1-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1-fSigAll)*numTot', effBkg[.9,0,1],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1-effBkg)*(1-fSigAll)*numTot', effBkg,fSigAll,numTot)");  

  w.factory("SUM::pdf_pass(nSignalPass*global_signalPass,nBkgPass*global_backgroundPass)");
  w.factory("SUM::pdf_fail(nSignalFail*global_signalFail,nBkgFail*global_backgroundFail)");

  RooCategory efficiencyCategory("efficiencyCategory","efficiencyCategory") ;

  efficiencyCategory.defineType("Passed") ;
  efficiencyCategory.defineType("Failed") ;

  w.factory("SIMUL::pdf_global(efficiencyCategory[Passed,Failed],Passed=pdf_pass,Failed=pdf_fail)");

  // Definition of global datasets:
  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,Weight(0.5),Index(efficiencyCategory),Import("Passed", *hist_passing),Import("Failed", *hist_failing)) ;


  // And... "Let the sunshine in"!
  w.pdf("pdf_global")->fitTo(binnedData_PassFailJoined,Extended(kTRUE));

  /*
  // Plot the results:
  RooAbsData* dataPass = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed")); 
  RooAbsData* dataFail = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Failed")); 
  RooAbsData* dataAll = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed || efficiencyCategory==efficiencyCategory::Failed")); 

  TCanvas* cx2 = (TCanvas*)gDirectory->GetList()->FindObject("cx2");
  if (cx2) delete cx2;
  cx2 = new TCanvas("cx2","cx2",0,0,800,600);
  cx2->Divide(2,2);

  cx2->cd(1);
  RooPlot* passFrame = w.var("mass")->frame(Title("Passing probes")) ;
  dataPass->plotOn(passFrame);
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen)) ;
  passFrame->Draw() ;

  cx2->cd(2);
  RooPlot* failFrame = w.var("mass")->frame(Title("Failing probes")) ;
  dataFail->plotOn(failFrame);
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed)) ;
  failFrame->Draw() ;

  cx2->cd(3);
  RooPlot* globalFrame = w.var("mass")->frame(Title("Passing + failing probes")) ;
  dataAll->plotOn(globalFrame);
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue)) ;
  globalFrame->Draw() ;

  cx2->cd(4);
  RooPlot* parFrame = w.var("mass")->frame(Title("Fit results")) ;
  w.pdf("pdf_global")->paramOn(parFrame, dataAll, "", 2, "NELU", 0.2, 0.9, 0.9);
  parFrame->Draw() ;

  cx2->Print(output_name.c_str());
  */

  TAP_efficiency = w.var("efficiency")->getVal();
  TAP_efficiency_uncertainty = w.var("efficiency")->getError();
}



////////////////////////////////////////////////////
// MC efficiency measurement (Good old Cruijff) //
////////////////////////////////////////////////////

void TagProbeFitter::doFit_MC_cruijff(string pass_data, string fail_data) {

  TH1F* hist_passing = (TH1F*) gDirectory->Get(pass_data.c_str());
  TH1F* hist_failing = (TH1F*) gDirectory->Get(fail_data.c_str());

  RooWorkspace w("w",kTRUE);

   // Definition of disjoint pdf's:
  // Passing PDF:
  w.factory("EXPR::signalPass('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',pass_mean[89.9, 80.0, 100.0],mass[60.0,120.0],pass_sigmaL[5.3, 0.5, 10.0],pass_alphaL[0.209,0,3],pass_sigmaR[3.29, 0.5, 10.0],pass_alphaR[0.19,0,3])");
  w.factory("RooExponential::backgroundPass(mass[60.0,120.0], cPass[0.0])");
  w.factory("SUM::passing_model(signalPassNorm[0.0,1000000000.0]*signalPass,bkgPassNorm[0.0,1000000000.0]*backgroundPass)");

  // Failing PDF:
  w.factory("EXPR::signalFail('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',fail_mean[89.9, 80.0, 100.0],mass[60.0,120.0],fail_sigmaL[5.3, 0.5, 10.0],fail_alphaL[0.209,0,3],fail_sigmaR[3.29, 0.5, 10.0],fail_alphaR[0.19,0,3])");
  w.factory("RooExponential::backgroundFail(mass[60.0,120.0], cFail[0.0])");
  w.factory("SUM::failing_model(signalFailNorm[0.0,1000000000.0]*signalFail,bkgFailNorm[0.0,1000000000.0]*backgroundFail)");

  // Definition of datasets:
  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist binnedData_passing("binnedData_passing","my data",obs,hist_passing) ;
  RooDataHist binnedData_failing("binnedData_failing","my data",obs,hist_failing) ;

  // Everything ready for the disjoint fits!
  w.pdf("passing_model")->fitTo(binnedData_passing,Extended(kTRUE));
  w.pdf("failing_model")->fitTo(binnedData_failing,Extended(kTRUE));

  // Definition Global (passing + failing) PDF:
  w.factory("EXPR::global_signalPass('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',g_pass_mean[89.9, 80.0, 100.0],mass[60.0,120.0],g_pass_sigmaL[5.3, 0.5, 10.0],g_pass_alphaL[0.209,0,3],g_pass_sigmaR[3.29, 0.5, 10.0],g_pass_alphaR[0.19,0,3])");

  w.var("g_pass_mean")->setVal(w.var("pass_mean")->getVal());
  w.var("g_pass_sigmaL")->setVal(w.var("pass_sigmaL")->getVal());
  w.var("g_pass_sigmaR")->setVal(w.var("pass_sigmaR")->getVal());
  w.var("g_pass_alphaR")->setVal(w.var("pass_alphaR")->getVal());
  w.var("g_pass_alphaL")->setVal(w.var("pass_alphaL")->getVal());

  w.factory("RooExponential::global_backgroundPass(mass[60.0,120.0], g_cPass[0.0])");


  w.factory("EXPR::global_signalFail('(@1<@0)*exp(-(@0-@1)*(@0-@1)/(@2*@2 + @3*(@0-@1)*(@0-@1))) + (@1>=@0)*exp(-(@0-@1)*(@0-@1)/(@4*@4 + @5*(@0-@1)*(@0-@1)))',g_fail_mean[90.0,80.0,100.0],mass[60.0,120.0],g_fail_sigmaL[5.3, 0.5, 10.0], g_fail_alphaL[0.209,0,3],g_fail_sigmaR[3.29, 0.5, 10.0],g_fail_alphaR[0.19,0,3])");

  w.var("g_fail_mean")->setVal(w.var("fail_mean")->getVal());
  w.var("g_fail_sigmaL")->setVal(w.var("fail_sigmaL")->getVal());
  w.var("g_fail_sigmaR")->setVal(w.var("fail_sigmaR")->getVal());
  w.var("g_fail_alphaR")->setVal(w.var("fail_alphaR")->getVal());
  w.var("g_fail_alphaL")->setVal(w.var("fail_alphaL")->getVal());

  w.factory("RooExponential::global_backgroundFail(mass[60.0,120.0], g_cFail[0.0])");


  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.8,0,1], fSigAll[1],numTot[1,0,1e10])");
  w.factory("expr::nSignalFail('(1-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1-fSigAll)*numTot', effBkg[0],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1-effBkg)*(1-fSigAll)*numTot', effBkg,fSigAll,numTot)");  

  w.factory("SUM::pdf_pass(nSignalPass*global_signalPass,nBkgPass*global_backgroundPass)");
  w.factory("SUM::pdf_fail(nSignalFail*global_signalFail,nBkgFail*global_backgroundFail)");

  RooCategory efficiencyCategory("efficiencyCategory","efficiencyCategory") ;

  efficiencyCategory.defineType("Passed") ;
  efficiencyCategory.defineType("Failed") ;

  w.factory("SIMUL::pdf_global(efficiencyCategory[Passed,Failed],Passed=pdf_pass,Failed=pdf_fail)");

  // Definition of global datasets:
  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,Weight(0.5),Index(efficiencyCategory),Import("Passed", *hist_passing),Import("Failed", *hist_failing)) ;


  // And... "Let the sunshine in"!
  w.pdf("pdf_global")->fitTo(binnedData_PassFailJoined,Extended(kTRUE));

  /*
  // Plot the results:
  RooAbsData* dataPass = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed")); 
  RooAbsData* dataFail = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Failed")); 
  RooAbsData* dataAll = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed || efficiencyCategory==efficiencyCategory::Failed")); 

  TCanvas* cx2 = (TCanvas*)gDirectory->GetList()->FindObject("cx2");
  if (cx2) delete cx2;
  cx2 = new TCanvas("cx2","cx2",0,0,800,600);
  cx2->Divide(2,2);

  cx2->cd(1);
  RooPlot* passFrame = w.var("mass")->frame(Title("Passing probes")) ;
  dataPass->plotOn(passFrame);
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen)) ;
  passFrame->Draw() ;

  cx2->cd(2);
  RooPlot* failFrame = w.var("mass")->frame(Title("Failing probes")) ;
  dataFail->plotOn(failFrame);
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed)) ;
  failFrame->Draw() ;

  cx2->cd(3);
  RooPlot* globalFrame = w.var("mass")->frame(Title("Passing + failing probes")) ;
  dataAll->plotOn(globalFrame);
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue)) ;
  globalFrame->Draw() ;

  cx2->cd(4);
  RooPlot* parFrame = w.var("mass")->frame(Title("Fit results")) ;
  w.pdf("pdf_global")->paramOn(parFrame, dataAll, "", 2, "NELU", 0.2, 0.9, 0.9);
  parFrame->Draw() ;
  */

  TAP_efficiency = w.var("efficiency")->getVal();
  TAP_efficiency_uncertainty = w.var("efficiency")->getError();
}


////////////////////////////////////
// Toy MC for BW+CB fit function  //
////////////////////////////////////

void TagProbeFitter::toy_BWCB() {

  RooWorkspace w("w",kTRUE);

  // Definition of disjoint pdf's:
  // Passing PDF:
  w.factory("RooBreitWigner::bwgauss(mass[60.0,120.0], pass_bwmean[91.1876], pass_bwsigma[2.4952])");
  w.factory("RooCBShape::pass_cball(mass, pass_cbmean[0.0,-2.0,2.0], pass_cbsigma[2.1,0.5,10.0], pass_alpha[1.4,0.1,4.0], pass_n[2.6,1.0,5.0])");
  w.factory("FCONV::signalPass(mass,bwgauss,pass_cball)");
  w.factory("RooExponential::backgroundPass(mass, cPass[-0.01,-0.08,0.0])");
  w.factory("SUM::passing_model(signalPassNorm[0.92,0.0,1.0]*signalPass,backgroundPass)");

  // Failing PDF:
  w.factory("RooCBShape::fail_cball(mass, fail_cbmean[0.0,-2.0,2.0], fail_cbsigma[2.0,0.5,10.0], fail_alpha[1.4,0.1,4.0], fail_n[2.6,1.0,5.0])");
  //w.var("fail_n")->setConstant(kTRUE);
  w.factory("FCONV::signalFail(mass,bwgauss,fail_cball)");
  w.factory("RooExponential::backgroundFail(mass, cFail[-0.01,-0.08,0.0])");
  w.factory("SUM::failing_model(signalFailNorm[0.4,0.0,1.0]*signalFail,backgroundFail)");

  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist *binnedData_passing = w.pdf("passing_model")->generateBinned(obs,10000);
  RooDataHist *binnedData_failing = w.pdf("failing_model")->generateBinned(obs,5750);

  // Everything ready for the disjoint fits!
  w.pdf("passing_model")->fitTo(*binnedData_passing);
  w.pdf("failing_model")->fitTo(*binnedData_failing);

  // Definition of the simultaneous pdf for global fit:
  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.8,0.0,1.0], fSigAll[0.73,0.0,1.0],numTot[10000,0.0,1000000000.0])");
  w.factory("expr::nSignalFail('(1.0-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1.0-fSigAll)*numTot', effBkg[0.18824,0.0,1.0],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1.0-effBkg)*(1.0-fSigAll)*numTot', effBkg,fSigAll,numTot)");  

  w.var("numTot")->setVal(15750);

  w.factory("SUM::pdf_pass(nSignalPass*signalPass,nBkgPass*backgroundPass)");
  //  w.factory("SUM::pdf_fail(nSignalFail*signalFail,nBkgFail*backgroundFail)");
  w.factory("SUM::pdf_fail(nSignalFail*signalFail,nBkgFail*backgroundFail)");

  RooCategory efficiencyCategory("efficiencyCategory","efficiencyCategory") ;

  efficiencyCategory.defineType("Passed") ;
  efficiencyCategory.defineType("Failed") ;

  w.factory("SIMUL::pdf_global(efficiencyCategory[Passed,Failed],Passed=pdf_pass,Failed=pdf_fail)");

  // Definition of global datasets:
  map<string,RooDataHist*> hmap ;
  hmap.insert(std::pair<string, RooDataHist*>("Passed", binnedData_passing));
  hmap.insert(std::pair<string, RooDataHist*>("Failed", binnedData_failing));
  RooDataHist binnedData_PassFailJoined("binnedData_PassFailJoined","binnedData_PassFailJoined",obs,efficiencyCategory,hmap,0.5);


  // And... "Let the sunshine in"!
  w.pdf("pdf_global")->fitTo(binnedData_PassFailJoined,Extended(kTRUE));

  TAP_efficiency = w.var("efficiency")->getVal();
  TAP_efficiency_uncertainty = w.var("efficiency")->getError();

  /*
  // Plot the results:
  RooAbsData* dataPass = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed")); 
  RooAbsData* dataFail = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Failed")); 
  RooAbsData* dataAll = binnedData_PassFailJoined.reduce(Cut("efficiencyCategory==efficiencyCategory::Passed || efficiencyCategory==efficiencyCategory::Failed")); 

  TCanvas* cx2 = (TCanvas*)gDirectory->GetList()->FindObject("cx2");
  if (cx2) delete cx2;
  cx2 = new TCanvas("cx2","cx2",0,0,800,600);
  cx2->Divide(2,2);

  cx2->cd(1);
  RooPlot* passFrame = w.var("mass")->frame(Title("Passing probes")) ;
  dataPass->plotOn(passFrame);
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen)) ;
  w.pdf("pdf_global")->plotOn(passFrame,ProjWData(*dataPass),LineColor(kGreen),Components("backgroundPass"),LineStyle(kDashed)) ;
  passFrame->Draw() ;

  cx2->cd(2);
  RooPlot* failFrame = w.var("mass")->frame(Title("Failing probes")) ;
  dataFail->plotOn(failFrame);
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed)) ;
  w.pdf("pdf_global")->plotOn(failFrame,ProjWData(*dataFail),LineColor(kRed),Components("backgroundFail"),LineStyle(kDashed)) ;
  failFrame->Draw() ;

  cx2->cd(3);
  RooPlot* globalFrame = w.var("mass")->frame(Title("Passing + failing probes")) ;
  dataAll->plotOn(globalFrame);
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue)) ;
  w.pdf("pdf_global")->plotOn(globalFrame,ProjWData(*dataAll),LineColor(kBlue),Components("backgroundPass,backgroundFail"),LineStyle(kDashed)) ;
  globalFrame->Draw() ;

  cx2->cd(4);
  RooPlot* parFrame = w.var("mass")->frame(Title("Fit results")) ;
  w.pdf("pdf_global")->paramOn(parFrame, dataAll, "", 2, "NELU", 0.2, 0.9, 0.9);
  parFrame->findObject(Form("%s_paramBox","pdf_global"))->Draw() ;

  cx2->Print("cacca.png");

  sleep(2);
  */
}
