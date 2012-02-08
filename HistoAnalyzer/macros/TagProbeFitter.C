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
  void doFit_BWCB(string, string, string);
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

  TH1F  DATA_WP80_Probe("DATA_WP80_Probe","DATA_WP80_Probe",5,0,5);
  DATA_WP80_Probe.Sumw2();

  char dummy[100];

  for (int nj=0;nj<5;nj++) {

    sprintf (dummy, "TAP/WP80_probepass%dJet", nj);
    pass_data_ = dummy;
    sprintf (dummy, "TAP/WP80_probefail%dJet", nj);
    fail_data_ = dummy;
    sprintf (dummy, "/gpfs/cms/data/2011/TaP/plots/DATA_WP80_Probe_%dJet.eps", nj);
    output_name_ = dummy;

    doFit_BWCB(pass_data_, fail_data_, output_name_);
    DATA_WP80_Probe.SetBinContent(nj+1,TAP_efficiency);
    DATA_WP80_Probe.SetBinError(nj+1,TAP_efficiency_uncertainty);
  }

  input_file_DATA.Close();

  /*
  // MC efficiencies:

  TFile input_file_MC(MC_filename.c_str(),"READ");


  input_file_MC.Close();
  */

  // Write histos to file:

  TFile output_file(output_rootuple.c_str(),"RECREATE");
  output_file.mkdir("efficiency_vs_nJets");
  output_file.cd("efficiency_vs_nJets");

  DATA_WP80_Probe.Write();
  /*  DATA_WP80_Tag.Write();
  DATA_HLT_Probe.Write();
  DATA_HLT_Tag.Write();

  MC_WP80_Probe.Write();
  MC_WP80_Tag.Write();
  MC_HLT_Probe.Write();
  MC_HLT_Tag.Write();
  */
  output_file.Close();
}

////////////////////////////////////
// Efficiency measurement (BW+CB) //
////////////////////////////////////

void TagProbeFitter::doFit_BWCB(string pass_data, string fail_data, string output_name) {

  TH1F* hist_passing = (TH1F*) gDirectory->Get(pass_data.c_str());
  TH1F* hist_failing = (TH1F*) gDirectory->Get(fail_data.c_str());

  RooWorkspace w("w",kTRUE);

  // Definition of disjoint pdf's:
  // Passing PDF:
  w.factory("RooBreitWigner::bwgauss(mass[60.0,120.0], pass_bwmean[91.1876], pass_bwsigma[2.4952])");
  w.factory("RooCBShape::pass_cball(mass, pass_cbmean[0.0,-2.0,2.0], pass_cbsigma[2.0,0.5,20.0], pass_alpha[1.35,0.1,3.0], pass_n[2.6])");
  w.factory("FCONV::signalPass(mass,bwgauss,pass_cball)");
  w.factory("RooExponential::backgroundPass(mass, cPass[-0.05,-0.08,-0.005])");
  w.factory("SUM::passing_model(signalPassNorm[1000.0,0.0,1000000000.0]*signalPass,bkgPassNorm[100.0,0.0,1000000000.0]*backgroundPass)");

  // Failing PDF:
  w.factory("RooCBShape::fail_cball(mass, pass_cbmean, fail_cbsigma[2.0,0.5,20.0], fail_alpha[1.35,0.1,3.0], fail_n[2.6])");
  w.factory("FCONV::signalFail(mass,bwgauss,fail_cball)");
  w.factory("RooExponential::backgroundFail(mass, cFail[-0.05,-0.08,-0.005])");
  w.factory("SUM::failing_model(signalFailNorm[0.0,1000000000.0]*signalFail,bkgFailNorm[100.0,0.0,1000000000.0]*backgroundFail)");


  // Definition of datasets:
  RooArgSet obs(*w.fundArg("mass"),"obs");

  RooDataHist binnedData_passing("binnedData_passing","my data",obs,hist_passing) ;
  RooDataHist binnedData_failing("binnedData_failing","my data",obs,hist_failing) ;

  // Everything ready for the disjoint fits!
  w.pdf("passing_model")->fitTo(binnedData_passing,Extended(kTRUE));
  w.pdf("failing_model")->fitTo(binnedData_failing,Extended(kTRUE));

  // Definition of the simultaneous pdf for global fit:
  w.factory("expr::nSignalPass('efficiency*fSigAll*numTot', efficiency[0.8,0,1], fSigAll[.9,0,1],numTot[1,0,1e10])");
  w.factory("expr::nSignalFail('(1-efficiency)*fSigAll*numTot', efficiency, fSigAll,numTot)");  
  w.factory("expr::nBkgPass('effBkg*(1-fSigAll)*numTot', effBkg[.9,0,1],fSigAll,numTot)");
  w.factory("expr::nBkgFail('(1-effBkg)*(1-fSigAll)*numTot', effBkg,fSigAll,numTot)");  

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

  TAP_efficiency = w.var("efficiency")->getVal();
  TAP_efficiency_uncertainty = w.var("efficiency")->getError();
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

