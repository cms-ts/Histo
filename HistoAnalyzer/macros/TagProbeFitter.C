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
#include <TStyle.h>
#include <TCanvas.h>
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

using namespace RooFit ;
using namespace std ;

class TagProbeFitter {
  double TAP_efficiency;
  double TAP_efficiency_uncertainty;
public:
  void eff_vs_nJets();
  void eff_vs_nJets_MC();
  void eff_vs_eta();
  void eff_vs_eta_MC();
  void eff_vs_leadjetpt();
  void eff_vs_leadjetpt_MC();
  void eff_vs_nVertex();
  void eff_vs_nVertex_MC();
  void validate_BWCB();
  int doFit_BWCB(string, string, string);
  void toy_BWCB();
  void doFit_DATA_cruijff(string, string, string);
  void doFit_MC_cruijff(string, string, string);
};

//////////////////////////////////////
// Main routine of the TAP analysis //
//////////////////////////////////////

void TagProbeFitter::eff_vs_nJets() {
  
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

  // WP80 2st LEG Efficiency (DATA):

  TH1F  DATA_WP80_Probe("DATA_WP80_Probe","DATA_WP80_Probe;# Jets;efficiency",6,0,6);
  DATA_WP80_Probe.Sumw2();

  TH1F  DATA_WP80_Tag("DATA_WP80_Tag","DATA_WP80_Tag;# Jets;efficiency",6,0,6);
  DATA_WP80_Tag.Sumw2();

  TH1F  DATA_HLTele8_Probe("DATA_HLTele8_Probe","DATA_HLTele8_Probe;# Jets;efficiency",6,0,6);
  DATA_HLTele8_Probe.Sumw2();

  TH1F  DATA_HLTele8_Tag("DATA_HLTele8_Tag","DATA_HLTele8_Tag;# Jets;efficiency",6,0,6);
  DATA_HLTele8_Tag.Sumw2();

  TH1F  DATA_HLTele17_Probe("DATA_HLTele17_Probe","DATA_HLTele17_Probe;# Jets;efficiency",6,0,6);
  DATA_HLTele17_Probe.Sumw2();

  TH1F  DATA_HLTele17_Tag("DATA_HLTele17_Tag","DATA_HLTele17_Tag;# Jets;efficiency",6,0,6);
  DATA_HLTele17_Tag.Sumw2();

  TH1F  DATA_RECO_Probe("DATA_RECO_Probe","DATA_RECO_Probe;# Jets;efficiency",6,0,6);
  DATA_RECO_Probe.Sumw2();

  char dummy[100];

  for (int nj=0;nj<6;nj++) {

    sprintf (dummy, "TAPwp80/probepass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/probefail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Probe_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_WP80_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_WP80_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPwp80/tagpass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/tagfail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Tag_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_WP80_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_WP80_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/probepass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/probefail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele8_Probe_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele8_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele8_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/tagpass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/tagfail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele8_Tag_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele8_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele8_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/probepass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/probefail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Probe_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele17_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele17_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/tagpass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/tagfail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Tag_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele17_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele17_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPreco/probepass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPreco/probefail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_RECO_Probe_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_RECO_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_RECO_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);
  }

  input_file_DATA.Close();

  // Write histos to file:

  TFile output_file(output_rootuple.c_str(),"RECREATE");
  output_file.mkdir("efficiency_vs_nJets");
  output_file.cd("efficiency_vs_nJets");

  DATA_WP80_Probe.Write();
  DATA_WP80_Tag.Write();
  DATA_HLTele8_Probe.Write();
  DATA_HLTele8_Tag.Write();
  DATA_HLTele17_Probe.Write();
  DATA_HLTele17_Tag.Write();
  DATA_RECO_Probe.Write();

  output_file.Close();

}


void TagProbeFitter::eff_vs_nJets_MC() {
  
  // Load file names from config.txt
  string stupid, DATA_filename, MC_filename, pass_data_, fail_data_, output_name_, output_rootuple;

  ifstream in;
  in.open("TAPfitter_config.txt");
  in >> stupid >> DATA_filename;
  in >> stupid >> MC_filename;
  in >> stupid >> output_rootuple;
  in.close();


  //MC efficiencies:

  TFile input_file_MC(MC_filename.c_str(),"READ");

  // WP80 2st LEG Efficiency (MC):

  TH1F  MC_WP80_Probe("MC_WP80_Probe","MC_WP80_Probe;# Jets;efficiency",6,0,6);
  MC_WP80_Probe.Sumw2();

  TH1F  MC_WP80_Tag("MC_WP80_Tag","MC_WP80_Tag;# Jets;efficiency",6,0,6);
  MC_WP80_Tag.Sumw2();

  TH1F  MC_HLTele8_Probe("MC_HLTele8_Probe","MC_HLTele8_Probe;# Jets;efficiency",6,0,6);
  MC_HLTele8_Probe.Sumw2();

  TH1F  MC_HLTele8_Tag("MC_HLTele8_Tag","MC_HLTele8_Tag;# Jets;efficiency",6,0,6);
  MC_HLTele8_Tag.Sumw2();

  TH1F  MC_HLTele17_Probe("MC_HLTele17_Probe","MC_HLTele17_Probe;# Jets;efficiency",6,0,6);
  MC_HLTele17_Probe.Sumw2();

  TH1F  MC_HLTele17_Tag("MC_HLTele17_Tag","MC_HLTele17_Tag;# Jets;efficiency",6,0,6);
  MC_HLTele17_Tag.Sumw2();

  TH1F  MC_RECO_Probe("MC_RECO_Probe","MC_RECO_Probe;# Jets;efficiency",6,0,6);
  MC_RECO_Probe.Sumw2();

  char dummy[100];

  for (int nj=0;nj<6;nj++) {

    sprintf (dummy, "TAPwp80/probepass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/probefail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_WP80_Probe_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_WP80_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_WP80_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPwp80/tagpass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/tagfail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_WP80_Tag_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_WP80_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_WP80_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/probepass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/probefail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele8_Probe_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele8_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele8_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/tagpass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/tagfail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele8_Tag_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele8_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele8_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/probepass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/probefail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele17_Probe_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele17_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele17_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/tagpass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/tagfail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele17_Tag_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele17_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele17_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPreco/probepass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPreco/probefail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_RECO_Probe_%dJet.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_RECO_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_RECO_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);
  }

  input_file_MC.Close();

  // Write histos to file:

  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.cd("efficiency_vs_nJets");

  MC_WP80_Probe.Write();
  MC_WP80_Tag.Write();
  MC_HLTele8_Probe.Write();
  MC_HLTele8_Tag.Write();
  MC_HLTele17_Probe.Write();
  MC_HLTele17_Tag.Write();
  MC_RECO_Probe.Write();

  output_file.Close();

}


// Efficiency as a function of leading Jet pT:

void TagProbeFitter::eff_vs_leadjetpt() {
  
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

  // WP80 2st LEG Efficiency (DATA):

  TH1F  DATA_WP80_Probe("DATA_WP80_Probe","DATA_WP80_Probe;leading Jet pt;efficiency",9,0,9);
  DATA_WP80_Probe.Sumw2();

  TH1F  DATA_WP80_Tag("DATA_WP80_Tag","DATA_WP80_Tag;leading Jet pt;efficiency",9,0,9);
  DATA_WP80_Tag.Sumw2();

  TH1F  DATA_HLTele8_Probe("DATA_HLTele8_Probe","DATA_HLTele8_Probe;leading Jet pt;efficiency",9,0,9);
  DATA_HLTele8_Probe.Sumw2();

  TH1F  DATA_HLTele8_Tag("DATA_HLTele8_Tag","DATA_HLTele8_Tag;leading Jet pt;efficiency",9,0,9);
  DATA_HLTele8_Tag.Sumw2();

  TH1F  DATA_HLTele17_Probe("DATA_HLTele17_Probe","DATA_HLTele17_Probe;leading Jet pt;efficiency",9,0,9);
  DATA_HLTele17_Probe.Sumw2();

  TH1F  DATA_HLTele17_Tag("DATA_HLTele17_Tag","DATA_HLTele17_Tag;leading Jet pt;efficiency",9,0,9);
  DATA_HLTele17_Tag.Sumw2();

  TH1F  DATA_RECO_Probe("DATA_RECO_Probe","DATA_RECO_Probe;leading Jet pt;efficiency",9,0,9);
  DATA_RECO_Probe.Sumw2();

  char dummy[100];

  for (int nj=0;nj<9;nj++) {

    sprintf (dummy, "TAPwp80/probepass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/probefail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Probe_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_WP80_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_WP80_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPwp80/tagpass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/tagfail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Tag_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_WP80_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_WP80_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/probepass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/probefail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele8_Probe_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele8_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele8_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/tagpass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/tagfail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele8_Tag_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele8_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele8_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/probepass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/probefail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Probe_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele17_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele17_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/tagpass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/tagfail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Tag_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele17_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele17_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPreco/probepass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPreco/probefail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_RECO_Probe_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_RECO_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_RECO_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);
  }

  input_file_DATA.Close();

  // Write histos to file:

  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.mkdir("efficiency_vs_leadjetpt");
  output_file.cd("efficiency_vs_leadjetpt");

  DATA_WP80_Probe.Write();
  DATA_WP80_Tag.Write();
  DATA_HLTele8_Probe.Write();
  DATA_HLTele8_Tag.Write();
  DATA_HLTele17_Probe.Write();
  DATA_HLTele17_Tag.Write();
  DATA_RECO_Probe.Write();

  output_file.Close();

}


// Efficiency as a function of leading Jet pT:

void TagProbeFitter::eff_vs_leadjetpt_MC() {
  
  // Load file names from config.txt
  string stupid, DATA_filename, MC_filename, pass_data_, fail_data_, output_name_, output_rootuple;

  ifstream in;
  in.open("TAPfitter_config.txt");
  in >> stupid >> DATA_filename;
  in >> stupid >> MC_filename;
  in >> stupid >> output_rootuple;
  in.close();


  //MC efficiencies:

  TFile input_file_MC(MC_filename.c_str(),"READ");

  // WP80 2st LEG Efficiency (MC):

  TH1F  MC_WP80_Probe("MC_WP80_Probe","MC_WP80_Probe;leading Jet pt;efficiency",9,0,9);
  MC_WP80_Probe.Sumw2();

  TH1F  MC_WP80_Tag("MC_WP80_Tag","MC_WP80_Tag;leading Jet pt;efficiency",9,0,9);
  MC_WP80_Tag.Sumw2();

  TH1F  MC_HLTele8_Probe("MC_HLTele8_Probe","MC_HLTele8_Probe;leading Jet pt;efficiency",9,0,9);
  MC_HLTele8_Probe.Sumw2();

  TH1F  MC_HLTele8_Tag("MC_HLTele8_Tag","MC_HLTele8_Tag;leading Jet pt;efficiency",9,0,9);
  MC_HLTele8_Tag.Sumw2();

  TH1F  MC_HLTele17_Probe("MC_HLTele17_Probe","MC_HLTele17_Probe;leading Jet pt;efficiency",9,0,9);
  MC_HLTele17_Probe.Sumw2();

  TH1F  MC_HLTele17_Tag("MC_HLTele17_Tag","MC_HLTele17_Tag;leading Jet pt;efficiency",9,0,9);
  MC_HLTele17_Tag.Sumw2();

  TH1F  MC_RECO_Probe("MC_RECO_Probe","MC_RECO_Probe;leading Jet pt;efficiency",9,0,9);
  MC_RECO_Probe.Sumw2();

  char dummy[100];

  for (int nj=0;nj<9;nj++) {

    sprintf (dummy, "TAPwp80/probepass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/probefail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_WP80_Probe_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_WP80_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_WP80_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPwp80/tagpass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/tagfail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_WP80_Tag_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_WP80_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_WP80_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/probepass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/probefail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele8_Probe_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele8_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele8_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/tagpass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/tagfail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele8_Tag_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele8_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele8_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/probepass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/probefail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele17_Probe_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele17_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele17_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/tagpass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/tagfail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele17_Tag_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele17_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele17_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPreco/probepass%dleadjetpt", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPreco/probefail%dleadjetpt", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_RECO_Probe_%dleadjetpt.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_RECO_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_RECO_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);
  }

  input_file_MC.Close();

  // Write histos to file:

  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.cd("efficiency_vs_leadjetpt");

  MC_WP80_Probe.Write();
  MC_WP80_Tag.Write();
  MC_HLTele8_Probe.Write();
  MC_HLTele8_Tag.Write();
  MC_HLTele17_Probe.Write();
  MC_HLTele17_Tag.Write();
  MC_RECO_Probe.Write();

  output_file.Close();

}


// Efficiency as a function of electron pseudorapidity (eta):

void TagProbeFitter::eff_vs_eta() {
  
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

  // WP80 2st LEG Efficiency (DATA):

  TH1F  DATA_WP80_Probe("DATA_WP80_Probe","DATA_WP80_Probe;eta;efficiency",5,0,5);
  DATA_WP80_Probe.Sumw2();

  TH1F  DATA_WP80_Tag("DATA_WP80_Tag","DATA_WP80_Tag;eta;efficiency",5,0,5);
  DATA_WP80_Tag.Sumw2();

  TH1F  DATA_HLTele8_Probe("DATA_HLTele8_Probe","DATA_HLTele8_Probe;eta;efficiency",5,0,5);
  DATA_HLTele8_Probe.Sumw2();

  TH1F  DATA_HLTele8_Tag("DATA_HLTele8_Tag","DATA_HLTele8_Tag;eta;efficiency",5,0,5);
  DATA_HLTele8_Tag.Sumw2();

  TH1F  DATA_HLTele17_Probe("DATA_HLTele17_Probe","DATA_HLTele17_Probe;eta;efficiency",5,0,5);
  DATA_HLTele17_Probe.Sumw2();

  TH1F  DATA_HLTele17_Tag("DATA_HLTele17_Tag","DATA_HLTele17_Tag;eta;efficiency",5,0,5);
  DATA_HLTele17_Tag.Sumw2();

  TH1F  DATA_RECO_Probe("DATA_RECO_Probe","DATA_RECO_Probe;eta;efficiency",5,0,5);
  DATA_RECO_Probe.Sumw2();

  char dummy[100];

  for (int nj=0;nj<5;nj++) {

    sprintf (dummy, "TAPwp80/probepass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/probefail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Probe_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_WP80_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_WP80_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPwp80/tagpass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/tagfail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Tag_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_WP80_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_WP80_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/probepass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/probefail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele8_Probe_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele8_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele8_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/tagpass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/tagfail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele8_Tag_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele8_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele8_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/probepass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/probefail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Probe_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele17_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele17_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/tagpass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/tagfail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Tag_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele17_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele17_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPreco/probepass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPreco/probefail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_RECO_Probe_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_RECO_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_RECO_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);
  }

  input_file_DATA.Close();

  // Write histos to file:

  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.mkdir("efficiency_vs_eta");
  output_file.cd("efficiency_vs_eta");

  DATA_WP80_Probe.Write();
  DATA_WP80_Tag.Write();
  DATA_HLTele8_Probe.Write();
  DATA_HLTele8_Tag.Write();
  DATA_HLTele17_Probe.Write();
  DATA_HLTele17_Tag.Write();
  DATA_RECO_Probe.Write();

  output_file.Close();

}


// Efficiency as a function of electron pseudorapidity (eta):

void TagProbeFitter::eff_vs_eta_MC() {
  
  // Load file names from config.txt
  string stupid, DATA_filename, MC_filename, pass_data_, fail_data_, output_name_, output_rootuple;

  ifstream in;
  in.open("TAPfitter_config.txt");
  in >> stupid >> DATA_filename;
  in >> stupid >> MC_filename;
  in >> stupid >> output_rootuple;
  in.close();


  //MC efficiencies:

  TFile input_file_MC(MC_filename.c_str(),"READ");

  // WP80 2st LEG Efficiency (MC):

  TH1F  MC_WP80_Probe("MC_WP80_Probe","MC_WP80_Probe;eta;efficiency",5,0,5);
  MC_WP80_Probe.Sumw2();

  TH1F  MC_WP80_Tag("MC_WP80_Tag","MC_WP80_Tag;eta;efficiency",5,0,5);
  MC_WP80_Tag.Sumw2();

  TH1F  MC_HLTele8_Probe("MC_HLTele8_Probe","MC_HLTele8_Probe;eta;efficiency",5,0,5);
  MC_HLTele8_Probe.Sumw2();

  TH1F  MC_HLTele8_Tag("MC_HLTele8_Tag","MC_HLTele8_Tag;eta;efficiency",5,0,5);
  MC_HLTele8_Tag.Sumw2();

  TH1F  MC_HLTele17_Probe("MC_HLTele17_Probe","MC_HLTele17_Probe;eta;efficiency",5,0,5);
  MC_HLTele17_Probe.Sumw2();

  TH1F  MC_HLTele17_Tag("MC_HLTele17_Tag","MC_HLTele17_Tag;eta;efficiency",5,0,5);
  MC_HLTele17_Tag.Sumw2();

  TH1F  MC_RECO_Probe("MC_RECO_Probe","MC_RECO_Probe;eta;efficiency",5,0,5);
  MC_RECO_Probe.Sumw2();

  char dummy[100];

  for (int nj=0;nj<5;nj++) {

    sprintf (dummy, "TAPwp80/probepass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/probefail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_WP80_Probe_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_WP80_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_WP80_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPwp80/tagpass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/tagfail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_WP80_Tag_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_WP80_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_WP80_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/probepass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/probefail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele8_Probe_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele8_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele8_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/tagpass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/tagfail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele8_Tag_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele8_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele8_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/probepass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/probefail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele17_Probe_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele17_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele17_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/tagpass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/tagfail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele17_Tag_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele17_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele17_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPreco/probepass%deta", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPreco/probefail%deta", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_RECO_Probe_%deta.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_RECO_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_RECO_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);
  }

  input_file_MC.Close();

  // Write histos to file:

  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.cd("efficiency_vs_eta");

  MC_WP80_Probe.Write();
  MC_WP80_Tag.Write();
  MC_HLTele8_Probe.Write();
  MC_HLTele8_Tag.Write();
  MC_HLTele17_Probe.Write();
  MC_HLTele17_Tag.Write();
  MC_RECO_Probe.Write();

  output_file.Close();

}


// Efficiency as a function of the number of vertices:

void TagProbeFitter::eff_vs_nVertex() {
  
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

  // WP80 2st LEG Efficiency (DATA):

  TH1F  DATA_WP80_Probe("DATA_WP80_Probe","DATA_WP80_Probe;Pile-UP;efficiency",5,0,5);
  DATA_WP80_Probe.Sumw2();

  TH1F  DATA_WP80_Tag("DATA_WP80_Tag","DATA_WP80_Tag;Pile-UP;efficiency",5,0,5);
  DATA_WP80_Tag.Sumw2();

  TH1F  DATA_HLTele8_Probe("DATA_HLTele8_Probe","DATA_HLTele8_Probe;Pile-UP;efficiency",5,0,5);
  DATA_HLTele8_Probe.Sumw2();

  TH1F  DATA_HLTele8_Tag("DATA_HLTele8_Tag","DATA_HLTele8_Tag;Pile-UP;efficiency",5,0,5);
  DATA_HLTele8_Tag.Sumw2();

  TH1F  DATA_HLTele17_Probe("DATA_HLTele17_Probe","DATA_HLTele17_Probe;Pile-UP;efficiency",5,0,5);
  DATA_HLTele17_Probe.Sumw2();

  TH1F  DATA_HLTele17_Tag("DATA_HLTele17_Tag","DATA_HLTele17_Tag;Pile-UP;efficiency",5,0,5);
  DATA_HLTele17_Tag.Sumw2();

  TH1F  DATA_RECO_Probe("DATA_RECO_Probe","DATA_RECO_Probe;Pile-UP;efficiency",5,0,5);
  DATA_RECO_Probe.Sumw2();

  char dummy[100];

  for (int nj=0;nj<5;nj++) {

    sprintf (dummy, "TAPwp80/probepass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/probefail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Probe_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_WP80_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_WP80_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPwp80/tagpass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/tagfail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Tag_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_WP80_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_WP80_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/probepass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/probefail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele8_Probe_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele8_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele8_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/tagpass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/tagfail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele8_Tag_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele8_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele8_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/probepass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/probefail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Probe_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele17_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele17_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/tagpass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/tagfail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_HLTele17_Tag_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_HLTele17_Tag.SetBinContent(nj+1,TAP_efficiency);
    DATA_HLTele17_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPreco/probepass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPreco/probefail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_RECO_Probe_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_RECO_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_RECO_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);
  }

  input_file_DATA.Close();

  // Write histos to file:

  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.mkdir("efficiency_vs_pu");
  output_file.cd("efficiency_vs_pu");

  DATA_WP80_Probe.Write();
  DATA_WP80_Tag.Write();
  DATA_HLTele8_Probe.Write();
  DATA_HLTele8_Tag.Write();
  DATA_HLTele17_Probe.Write();
  DATA_HLTele17_Tag.Write();
  DATA_RECO_Probe.Write();

  output_file.Close();

}


// Efficiency as a function of the number of vertices:

void TagProbeFitter::eff_vs_nVertex_MC() {
  
  // Load file names from config.txt
  string stupid, DATA_filename, MC_filename, pass_data_, fail_data_, output_name_, output_rootuple;

  ifstream in;
  in.open("TAPfitter_config.txt");
  in >> stupid >> DATA_filename;
  in >> stupid >> MC_filename;
  in >> stupid >> output_rootuple;
  in.close();


  //MC efficiencies:

  TFile input_file_MC(MC_filename.c_str(),"READ");

  // WP80 2st LEG Efficiency (MC):

  TH1F  MC_WP80_Probe("MC_WP80_Probe","MC_WP80_Probe;Pile-UP;efficiency",5,0,5);
  MC_WP80_Probe.Sumw2();

  TH1F  MC_WP80_Tag("MC_WP80_Tag","MC_WP80_Tag;Pile-UP;efficiency",5,0,5);
  MC_WP80_Tag.Sumw2();

  TH1F  MC_HLTele8_Probe("MC_HLTele8_Probe","MC_HLTele8_Probe;Pile-UP;efficiency",5,0,5);
  MC_HLTele8_Probe.Sumw2();

  TH1F  MC_HLTele8_Tag("MC_HLTele8_Tag","MC_HLTele8_Tag;Pile-UP;efficiency",5,0,5);
  MC_HLTele8_Tag.Sumw2();

  TH1F  MC_HLTele17_Probe("MC_HLTele17_Probe","MC_HLTele17_Probe;Pile-UP;efficiency",5,0,5);
  MC_HLTele17_Probe.Sumw2();

  TH1F  MC_HLTele17_Tag("MC_HLTele17_Tag","MC_HLTele17_Tag;Pile-UP;efficiency",5,0,5);
  MC_HLTele17_Tag.Sumw2();

  TH1F  MC_RECO_Probe("MC_RECO_Probe","MC_RECO_Probe;Pile-UP;efficiency",5,0,5);
  MC_RECO_Probe.Sumw2();

  char dummy[100];

  for (int nj=0;nj<5;nj++) {

    sprintf (dummy, "TAPwp80/probepass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/probefail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_WP80_Probe_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_WP80_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_WP80_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPwp80/tagpass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPwp80/tagfail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_WP80_Tag_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_WP80_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_WP80_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/probepass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/probefail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele8_Probe_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele8_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele8_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele8/tagpass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele8/tagfail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele8_Tag_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele8_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele8_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/probepass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/probefail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele17_Probe_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele17_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele17_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPhltele17/tagpass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPhltele17/tagfail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_HLTele17_Tag_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_HLTele17_Tag.SetBinContent(nj+1,TAP_efficiency);
    MC_HLTele17_Tag.SetBinError(nj+1,TAP_efficiency_uncertainty);

    sprintf (dummy, "TAPreco/probepass%dpu", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAPreco/probefail%dpu", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/MC_RECO_Probe_%dpu.png", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    MC_RECO_Probe.SetBinContent(nj+1,TAP_efficiency);
    MC_RECO_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);
  }

  input_file_MC.Close();

  // Write histos to file:

  TFile output_file(output_rootuple.c_str(),"UPDATE");
  output_file.cd("efficiency_vs_pu");

  MC_WP80_Probe.Write();
  MC_WP80_Tag.Write();
  MC_HLTele8_Probe.Write();
  MC_HLTele8_Tag.Write();
  MC_HLTele17_Probe.Write();
  MC_HLTele17_Tag.Write();
  MC_RECO_Probe.Write();

  output_file.Close();

}


//////////////////////////////////////
//    Validation ROUTINE: BW+CB     //
//////////////////////////////////////

void TagProbeFitter::validate_BWCB() {

  TH1F  pulls_distrib("pulls_distrib","pulls_distrib",80,-4,4);

  TFile output_file_validation("validation_BWCB_evts10k.root","RECREATE");

  for (int i=0; i<3000; i++) {
    toy_BWCB();
    pulls_distrib.Fill((TAP_efficiency-0.8)/TAP_efficiency_uncertainty);
  }

  pulls_distrib.Write();
  output_file_validation.Close();

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
  w.factory("RooBreitWigner::bwgauss(mass[71.0,111.0], pass_bwmean[91.1876], pass_bwsigma[2.4952])");
  w.factory("RooCBShape::pass_cball(mass, pass_cbmean[0.0,-2.0,2.0], pass_cbsigma[2.1,0.5,10.0], pass_alpha[1.4,0.1,4.0], pass_n[2.6,1.0,5.0])");
  w.factory("FCONV::signalPass(mass,bwgauss,pass_cball)");
  w.factory("RooExponential::backgroundPass(mass, cPass[-0.01,-0.08,0.0])");
  w.factory("SUM::passing_model(signalPassNorm[0.9,0.0,1.0]*signalPass,backgroundPass)");

  // Failing PDF:
  w.factory("RooCBShape::fail_cball(mass, fail_cbmean[0.0,-2.0,2.0], fail_cbsigma[2.0,0.5,10.0], fail_alpha[1.4,0.1,4.0], fail_n[2.6,1.0,5.0])");
  //w.var("fail_n")->setConstant(kTRUE);
  w.factory("FCONV::signalFail(mass,bwgauss,fail_cball)");
  w.factory("RooExponential::backgroundFail(mass, cFail[-0.01,-0.08,0.0])");
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


////////////////////////////////////////////////////
// DATA efficiency measurement (Good old Cruijff) //
////////////////////////////////////////////////////

void TagProbeFitter::doFit_DATA_cruijff(string pass_data, string fail_data, string output_name) {
  
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

void TagProbeFitter::doFit_MC_cruijff(string pass_data, string fail_data, string output_name) {

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
  w.factory("SUM::passing_model(signalPassNorm[0.99,0.0,1.0]*signalPass,backgroundPass)");

  // Failing PDF:
  w.factory("RooCBShape::fail_cball(mass, fail_cbmean[0.0,-2.0,2.0], fail_cbsigma[2.0,0.5,10.0], fail_alpha[1.4,0.1,4.0], fail_n[2.6,1.0,5.0])");
  w.factory("FCONV::signalFail(mass,bwgauss,fail_cball)");
  w.factory("RooExponential::backgroundFail(mass, cFail[-0.01,-0.08,0.0])");
  w.factory("SUM::failing_model(signalFailNorm[0.5,0.0,1.0]*signalFail,backgroundFail)");

  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist *binnedData_passing = w.pdf("passing_model")->generateBinned(obs,10000);
  RooDataHist *binnedData_failing = w.pdf("failing_model")->generateBinned(obs,4950);

  // Everything ready for the disjoint fits!
  w.pdf("passing_model")->fitTo(*binnedData_passing);
  w.pdf("failing_model")->fitTo(*binnedData_failing);

  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.8,0.0,1.0], fSigAll[0.827759197,0.0,1.0],numTot[14950.0,0.0,10000000000.0])");
  w.factory("expr::nSignalFail('(1.0-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1.0-fSigAll)*numTot', effBkg[0.038834951,0.0,1.0],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1.0-effBkg)*(1.0-fSigAll)*numTot', effBkg,fSigAll,numTot)");  

  w.factory("SUM::pdf_pass(nSignalPass*signalPass,nBkgPass*backgroundPass)");
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
}
