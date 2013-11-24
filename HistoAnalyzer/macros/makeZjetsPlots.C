#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include "Unfolding/MakePlotLumiLabel.C"
#include <TH2.h>
#include "TF1.h"
#include <TStyle.h>
#include <TCanvas.h>
#include "TRandom.h"
#include "TH1D.h"
#include "TFile.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include "TLatex.h"
#include <vector>
#include <iostream>
#include "tdrStyle.C"
#include <TROOT.h>
#include "TObject.h"
#include <iostream>
#include <sstream>
#include "TTree.h"
#include "TH2.h"
#include "THStack.h"
#include "TLatex.h"
#include <string.h>

void
makeZjetsPlots (int whichobservable, int whichjet, int whichlepton, bool inclusiveMultiplicity)
{

  setTDRStyle ();
  gStyle->SetErrorX(0.5);
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);

  bool absoluteNormalization=true;
  int lepton=whichlepton; //1 -> electron,  2-> muon , 3 -> combined reults!
  bool addLumiUncertainties=true; double lumiError=0.025;
  bool incMultiplicity = inclusiveMultiplicity;

  int use_case = whichobservable;
  int whichjet = whichjet;
  string version = "_v2_32";
  string s                = "/afs/infn.it/ts/user/schizzi/html/approval/ele/";
  if (lepton==2) string s = "/afs/infn.it/ts/user/schizzi/html/approval/muo/";
  if (lepton==3) string s = "/afs/infn.it/ts/user/schizzi/html/approval/combined/";

  string plotpath           = "/gpfs/cms/users/schizzi/Systematics/ele/";
  if (lepton == 2) plotpath = "/gpfs/cms/users/schizzi/Systematics/muo/";
  if (lepton == 3) plotpath = "/gpfs/cms/users/schizzi/Systematics/combination/";

  gStyle->SetOptStat (0);

  TCanvas *plots = new TCanvas ("plots", "EB", 200, 100, 600, 800);

  //DATA:
  string           pathFile ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3.root";
  if (lepton == 2) pathFile ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3Mu.root";
  if (lepton == 3) pathFile ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3Combined.root";

  //RIVET:
  string rivetPathSherpa           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/central/out.root";
  string rivetPathSherpaUP         ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/FRup/out.root";
  string rivetPathSherpaDOWN       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/FRdown/out.root";
  //  string rivetPathSherpaQUP        ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qup_7TeV_sherpa/out.root";
  //  string rivetPathSherpaQDOWN      ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qdown_7TeV_sherpa/out.root";
  //  string rivetPathSherpaQcutUP     ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qcutup_7TeV_sherpa/out.root";
  //  string rivetPathSherpaQcutDOWN   ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qcutdown_7TeV_sherpa/out.root";
  //  string rivetPathSherpaMSTW       ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01MSTW2008_7TeV_sherpa/out.root";
  //  string rivetPathSherpaNNPDF      ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01NNPDF_7TeV_sherpa/out.root";
  string  rivetPathSherpaQUP        ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qup.root";
  string  rivetPathSherpaQDOWN      ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qdown.root";
  string  rivetPathSherpaQcutUP     ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qcutup.root";
  string  rivetPathSherpaQcutDOWN   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qcutdown.root";
  string  rivetPathSherpaMSTW       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_mstw.root";
  string  rivetPathSherpaNNPDF      ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_nnpdf.root";

  string rivetPathMadGraph         ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
  //  string rivetPathPowheg           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-10/out.root";
  string rivetPathPowheg           ="/gpfs/cms/users/candelis/Rivet/powheg/test_ee/out.root";
  //  string rivetPathPowheg0510       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/05-10/out.root";
  //  string rivetPathPowheg2010       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/20-10/out.root";
  //  string rivetPathPowheg1005       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-05/out.root";
  //  string rivetPathPowheg1020       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-20/out.root";
  string  rivetPathPowheg0510       ="/gpfs/cms/users/candelis/Rivet/powheg/test_ee/out.root";
  string  rivetPathPowheg2010       ="/gpfs/cms/users/candelis/Rivet/powheg/test_ee/out.root";
  string  rivetPathPowheg1005       ="/gpfs/cms/users/candelis/Rivet/powheg/test_ee/out.root";
  string  rivetPathPowheg1020       ="/gpfs/cms/users/candelis/Rivet/powheg/test_ee/out.root";

  if (lepton == 2){
    rivetPathSherpa           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/central/out.root";
    rivetPathSherpaUP         ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/FRup/out.root";
    rivetPathSherpaDOWN       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/FRdown/out.root";
    //    rivetPathSherpaQUP       ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qup_7TeV_sherpa/out.root";
    //    rivetPathSherpaQDOWN       ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qdown_7TeV_sherpa/out.root";
    //    rivetPathSherpaQcutUP     ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qcutup_7TeV_sherpa/out.root";
    //    rivetPathSherpaQcutDOWN   ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qcutdown_7TeV_sherpa/out.root";
    //    rivetPathSherpaMSTW       ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01MSTW2008_7TeV_sherpa/out.root";
    //    rivetPathSherpaNNPDF      ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01NNPDF_7TeV_sherpa/out.root";
    rivetPathSherpaQUP        ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";
    rivetPathSherpaQDOWN      ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";
    rivetPathSherpaQcutUP     ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";
    rivetPathSherpaQcutDOWN   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";
    rivetPathSherpaMSTW       ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";
    rivetPathSherpaNNPDF      ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";

    rivetPathMadGraph         ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
    //    rivetPathPowheg           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-10/out.root";
    rivetPathPowheg           ="/gpfs/cms/users/candelis/Rivet/powheg/test_mm/out.root";
    //    rivetPathPowheg0510       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/05-10/out.root";
    //    rivetPathPowheg2010       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/20-10/out.root";
    //    rivetPathPowheg1005       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-05/out.root";
    //    rivetPathPowheg1020       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-20/out.root";
    rivetPathPowheg0510       ="/gpfs/cms/users/candelis/Rivet/powheg/test_mm/out.root";
    rivetPathPowheg2010       ="/gpfs/cms/users/candelis/Rivet/powheg/test_mm/out.root";
    rivetPathPowheg1005       ="/gpfs/cms/users/candelis/Rivet/powheg/test_mm/out.root";
    rivetPathPowheg1020       ="/gpfs/cms/users/candelis/Rivet/powheg/test_mm/out.root";
  }

  if (lepton == 3){
    //    rivetPathSherpa       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_central.root";
    //    rivetPathSherpaUP     ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_scaleUP.root";
    //    rivetPathSherpaDOWN   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_scaleDOWN.root";
    //    rivetPathSherpaQUP    ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_PDF1.root";
    //    rivetPathSherpaQDOWN  ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_PDF2.root";
    rivetPathSherpa           ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_central.root";
    rivetPathSherpaUP         ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_FRup.root";
    rivetPathSherpaDOWN       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_FRdown.root";
    rivetPathSherpaQUP        ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qup.root";
    rivetPathSherpaQDOWN      ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qdown.root";
    rivetPathSherpaQcutUP     ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qcutup.root";
    rivetPathSherpaQcutDOWN   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qcutdown.root";
    rivetPathSherpaMSTW       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_mstw.root";
    rivetPathSherpaNNPDF      ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_nnpdf.root";
    rivetPathMadGraph         ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_central.root";
    rivetPathPowheg           ="/gpfs/cms/users/schizzi/rivet/combination/Powheg_central.root";
    //    rivetPathPowheg           ="/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_central.root";
    //    rivetPathPowheg0510       ="/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_05-10.root";
    //    rivetPathPowheg2010       ="/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_20-10.root";
    //    rivetPathPowheg1005       ="/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_10-05.root";
    //    rivetPathPowheg1020       ="/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_10-20.root";
    rivetPathPowheg0510       ="/gpfs/cms/users/schizzi/rivet/combination/Powheg_central.root";
    rivetPathPowheg2010       ="/gpfs/cms/users/schizzi/rivet/combination/Powheg_central.root";
    rivetPathPowheg1005       ="/gpfs/cms/users/schizzi/rivet/combination/Powheg_central.root";
    rivetPathPowheg1020       ="/gpfs/cms/users/schizzi/rivet/combination/Powheg_central.root";
  }

  TFile *histof = TFile::Open (pathFile.c_str ());
  histof->cd ("");
  TDirectory *dir = gDirectory;
  TList *mylist = (TList *) dir->GetListOfKeys ();
  TIter iter (mylist);
  TObject *tobj = 0;
  string tmpname;
  string stringmatch;
  string systPathFile;
  string rivet_data;
  string rivet_dataMG;

  int i = 0;			// solo di servizio quando debuggo...
  while ((tobj = iter.Next ()))
    {
      string name = tobj->GetName ();
      stringstream oss;
      stringstream ossInc;

      if (use_case == 1) 
	{ // Jet Multiplicity
	  stringmatch = "JetMultiplicityUnfolded";
	  systPathFile = plotpath + "jetMultFinalSyst" + version + ".txt";
	  if (lepton == 1  || lepton == 3) {
	    oss<<"03";
	    ossInc<<"27";
	  } else {
	    oss<<"08";
	    ossInc<<"28";
	  }
	}
      if (use_case == 2) 
	{ // Jet Pt
	  if (whichjet == 1)
	    {
	      stringmatch = "jReco_leading";
	      systPathFile = plotpath + "jet1PtFinalSyst" + version + ".txt";
	      if (lepton == 1 || lepton ==3) oss<<"01"; else oss<<"06";
	    }
	  if (whichjet == 2)
	    {
	      stringmatch = "jReco_subleading";
	      systPathFile = plotpath + "jet2PtFinalSyst" + version + ".txt";
	      if (lepton == 1 || lepton ==3) oss<<"02"; else oss<<"07";
	    }
	  if (whichjet == 3)
	    {
	      stringmatch = "jReco_subsubleading";
	      systPathFile = plotpath + "jet3PtFinalSyst" + version + ".txt";
	      if (lepton == 1 || lepton ==3) oss<<"04"; else oss<<"09";
	    }
	  if (whichjet == 4)
	    {
	      stringmatch = "jReco_subsubsubleading";
	      systPathFile = plotpath + "jet4PtFinalSyst" + version + ".txt";
	      if (lepton == 1 || lepton ==3) oss<<"05"; else oss<<"10";
	    }
	}
      if (use_case == 3) { // Jet Eta
	if (whichjet == 1)
	  {
	    stringmatch = "jReco_leadingeta";
	    systPathFile = plotpath + "jet1EtaFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton ==3) oss<<"15"; else oss<<"11";
	  }
	if (whichjet == 2)
	  {
	    stringmatch = "jReco_subleadingeta";
	    systPathFile = plotpath + "jet2EtaFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton ==3) oss<<"16"; else oss<<"12";
	  }
	if (whichjet == 3)
	  {
	    stringmatch = "jReco_subsubleadingeta";
	    systPathFile = plotpath + "jet3EtaFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton ==3) oss<<"17"; else oss<<"13";
	  }
	if (whichjet == 4)
	  {
	    stringmatch = "jReco_subsubsubleadingeta";
	    systPathFile = plotpath + "jet4EtaFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton ==3) oss<<"18"; else oss<<"14";
	  }
      }
      if (use_case == 4) { // Ht
	if (whichjet == 1)
	  {
	    stringmatch = "HReco_leading";
	    systPathFile = plotpath + "jet1HtFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton ==3) oss<<"19"; else oss<<"23";
	  }
	if (whichjet == 2)
	  {
	    stringmatch = "HReco_subleading";
	    systPathFile = plotpath + "jet2HtFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton ==3) oss<<"20"; else oss<<"24";
	  }
	if (whichjet == 3)
	  {
	    stringmatch = "HReco_subsubleading";
	    systPathFile = plotpath + "jet3HtFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton ==3) oss<<"21"; else oss<<"25";
	  }
	if (whichjet == 4)
	  {
	    stringmatch = "HReco_subsubsubleading";
	    systPathFile = plotpath + "jet4HtFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton ==3) oss<<"22"; else oss<<"26";
	  }
      }

      string rivetname="d"+oss.str()+"_x01_y01";
      string rivetnameMG="d"+oss.str()+"-x01-y01";
      if (incMultiplicity) {
	rivetname="d"+ossInc.str()+"_x01_y01";
	rivetnameMG="d"+ossInc.str()+"-x01-y01";
      }

      rivet_data    = rivetname;
      rivet_dataMG    = rivetnameMG;
      
      if (name == stringmatch) {

	cout << "CONFIGURATION:" << endl;
	cout << "stringmatch: " <<stringmatch<< endl;
	cout << "systPathFile: " <<systPathFile<< endl;
	cout << "rivet_data: " <<rivet_data<< endl;

	gPad->SetLogy (1);
	TH1D *leading;
	gDirectory->GetObject (name.c_str (), leading);
	if (incMultiplicity) {
	  for (int dd=1; dd<=leading->GetNbinsX(); dd++) {
	    double inclusiveYield=0.0;
	    double inclusiveYieldUnc=0.0;
	    for (int ff=dd; ff<=leading->GetNbinsX(); ff++) {
	      inclusiveYield=inclusiveYield + leading->GetBinContent(ff);
	      inclusiveYieldUnc=sqrt(inclusiveYieldUnc*inclusiveYieldUnc + leading->GetBinError(ff)*leading->GetBinError(ff));
	    }
	    leading->SetBinContent(dd,inclusiveYield);
	  }
	}
	TH1D *leadingSystematics;
	leadingSystematics = (TH1D *) leading->Clone ("leading");

	leadingSystematics->SetMarkerSize(0.9);
	leading->SetMarkerSize(0.9);

	// read from file ---------------------------------------------
	double dat;
	ifstream inM;
	inM.open (systPathFile.c_str ());
	//int l2 =0;
	std::vector < double >systTmpM;
	while (1)
	  {
	    inM >> dat;
	    if (!inM.good ())
	      break;
	    if (addLumiUncertainties) {
	      dat=pow(dat*dat+lumiError*lumiError,0.5);
	    }
	    systTmpM.push_back (dat);
	    //l2++;  
	  }
	inM.close ();
	// ------------------------------------------------------------

	// Get RIVET data: --------------------------------------------
	TFile *histoRivetSherpa = TFile::Open (rivetPathSherpa.c_str ());
	histoRivetSherpa->cd ("");
	TDirectory *dirRivetSherpa = gDirectory;
	TList *mylistRivetSherpa = (TList *) dirRivetSherpa->GetListOfKeys ();
	TIter iterRivetSherpa (mylistRivetSherpa);
	TObject *tobjRivetSherpa = 0;
	while ((tobjRivetSherpa = iterRivetSherpa.Next ()))
	  {
	    string nameRivetSherpa = tobjRivetSherpa->GetName ();
	    if (nameRivetSherpa == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetSherpa;
		gDirectory->GetObject (nameRivetSherpa.c_str (), leadingRivetSherpa);
		TGraphAsymmErrors *leadingRivetSherpaStat;
		leadingRivetSherpaStat = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
		TGraphAsymmErrors *leadingRatioSherpaStat;
		leadingRatioSherpaStat = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
		TGraphAsymmErrors *leadingRatioSherpa;
		leadingRatioSherpa = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
	      }
	  }

	TFile *histoRivetSherpaUP = TFile::Open (rivetPathSherpaUP.c_str ());
	histoRivetSherpaUP->cd ("");
	TDirectory *dirRivetSherpaUP = gDirectory;
	TList *mylistRivetSherpaUP = (TList *) dirRivetSherpaUP->GetListOfKeys ();
	TIter iterRivetSherpaUP (mylistRivetSherpaUP);
	TObject *tobjRivetSherpaUP = 0;
	while ((tobjRivetSherpaUP = iterRivetSherpaUP.Next ()))
	  {
	    string nameRivetSherpaUP = tobjRivetSherpaUP->GetName ();
	    if (nameRivetSherpaUP == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetSherpaUP;
		gDirectory->GetObject (nameRivetSherpaUP.c_str (), leadingRivetSherpaUP);
	      }
	  }

	TFile *histoRivetSherpaDOWN = TFile::Open (rivetPathSherpaDOWN.c_str ());
	histoRivetSherpaDOWN->cd ("");
	TDirectory *dirRivetSherpaDOWN = gDirectory;
	TList *mylistRivetSherpaDOWN = (TList *) dirRivetSherpaDOWN->GetListOfKeys ();
	TIter iterRivetSherpaDOWN (mylistRivetSherpaDOWN);
	TObject *tobjRivetSherpaDOWN = 0;
	while ((tobjRivetSherpaDOWN = iterRivetSherpaDOWN.Next ()))
	  {
	    string nameRivetSherpaDOWN = tobjRivetSherpaDOWN->GetName ();
	    if (nameRivetSherpaDOWN == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetSherpaDOWN;
		gDirectory->GetObject (nameRivetSherpaDOWN.c_str (), leadingRivetSherpaDOWN);
	      }
	  }

	TFile *histoRivetSherpaQUP = TFile::Open (rivetPathSherpaQUP.c_str ());
	histoRivetSherpaQUP->cd ("");
	TDirectory *dirRivetSherpaQUP = gDirectory;
	TList *mylistRivetSherpaQUP = (TList *) dirRivetSherpaQUP->GetListOfKeys ();
	TIter iterRivetSherpaQUP (mylistRivetSherpaQUP);
	TObject *tobjRivetSherpaQUP = 0;
	while ((tobjRivetSherpaQUP = iterRivetSherpaQUP.Next ()))
	  {
	    string nameRivetSherpaQUP = tobjRivetSherpaQUP->GetName ();
	    if (nameRivetSherpaQUP == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetSherpaQUP;
		gDirectory->GetObject (nameRivetSherpaQUP.c_str (), leadingRivetSherpaQUP);
	      }
	  }

	TFile *histoRivetSherpaQDOWN = TFile::Open (rivetPathSherpaQDOWN.c_str ());
	histoRivetSherpaQDOWN->cd ("");
	TDirectory *dirRivetSherpaQDOWN = gDirectory;
	TList *mylistRivetSherpaQDOWN = (TList *) dirRivetSherpaQDOWN->GetListOfKeys ();
	TIter iterRivetSherpaQDOWN (mylistRivetSherpaQDOWN);
	TObject *tobjRivetSherpaQDOWN = 0;
	while ((tobjRivetSherpaQDOWN = iterRivetSherpaQDOWN.Next ()))
	  {
	    string nameRivetSherpaQDOWN = tobjRivetSherpaQDOWN->GetName ();
	    if (nameRivetSherpaQDOWN == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetSherpaQDOWN;
		gDirectory->GetObject (nameRivetSherpaQDOWN.c_str (), leadingRivetSherpaQDOWN);
	      }
	  }


	TFile *histoRivetSherpaQcutUP = TFile::Open (rivetPathSherpaQcutUP.c_str ());
	histoRivetSherpaQcutUP->cd ("");
	TDirectory *dirRivetSherpaQcutUP = gDirectory;
	TList *mylistRivetSherpaQcutUP = (TList *) dirRivetSherpaQcutUP->GetListOfKeys ();
	TIter iterRivetSherpaQcutUP (mylistRivetSherpaQcutUP);
	TObject *tobjRivetSherpaQcutUP = 0;
	while ((tobjRivetSherpaQcutUP = iterRivetSherpaQcutUP.Next ()))
	  {
	    string nameRivetSherpaQcutUP = tobjRivetSherpaQcutUP->GetName ();
	    if (nameRivetSherpaQcutUP == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetSherpaQcutUP;
		gDirectory->GetObject (nameRivetSherpaQcutUP.c_str (), leadingRivetSherpaQcutUP);
	      }
	  }

	TFile *histoRivetSherpaQcutDOWN = TFile::Open (rivetPathSherpaQcutDOWN.c_str ());
	histoRivetSherpaQcutDOWN->cd ("");
	TDirectory *dirRivetSherpaQcutDOWN = gDirectory;
	TList *mylistRivetSherpaQcutDOWN = (TList *) dirRivetSherpaQcutDOWN->GetListOfKeys ();
	TIter iterRivetSherpaQcutDOWN (mylistRivetSherpaQcutDOWN);
	TObject *tobjRivetSherpaQcutDOWN = 0;
	while ((tobjRivetSherpaQcutDOWN = iterRivetSherpaQcutDOWN.Next ()))
	  {
	    string nameRivetSherpaQcutDOWN = tobjRivetSherpaQcutDOWN->GetName ();
	    if (nameRivetSherpaQcutDOWN == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetSherpaQcutDOWN;
		gDirectory->GetObject (nameRivetSherpaQcutDOWN.c_str (), leadingRivetSherpaQcutDOWN);
	      }
	  }

	TFile *histoRivetSherpaMSTW = TFile::Open (rivetPathSherpaMSTW.c_str ());
	histoRivetSherpaMSTW->cd ("");
	TDirectory *dirRivetSherpaMSTW = gDirectory;
	TList *mylistRivetSherpaMSTW = (TList *) dirRivetSherpaMSTW->GetListOfKeys ();
	TIter iterRivetSherpaMSTW (mylistRivetSherpaMSTW);
	TObject *tobjRivetSherpaMSTW = 0;
	while ((tobjRivetSherpaMSTW = iterRivetSherpaMSTW.Next ()))
	  {
	    string nameRivetSherpaMSTW = tobjRivetSherpaMSTW->GetName ();
	    if (nameRivetSherpaMSTW == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetSherpaMSTW;
		gDirectory->GetObject (nameRivetSherpaMSTW.c_str (), leadingRivetSherpaMSTW);
	      }
	  }

	TFile *histoRivetSherpaNNPDF = TFile::Open (rivetPathSherpaNNPDF.c_str ());
	histoRivetSherpaNNPDF->cd ("");
	TDirectory *dirRivetSherpaNNPDF = gDirectory;
	TList *mylistRivetSherpaNNPDF = (TList *) dirRivetSherpaNNPDF->GetListOfKeys ();
	TIter iterRivetSherpaNNPDF (mylistRivetSherpaNNPDF);
	TObject *tobjRivetSherpaNNPDF = 0;
	while ((tobjRivetSherpaNNPDF = iterRivetSherpaNNPDF.Next ()))
	  {
	    string nameRivetSherpaNNPDF = tobjRivetSherpaNNPDF->GetName ();
	    if (nameRivetSherpaNNPDF == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetSherpaNNPDF;
		gDirectory->GetObject (nameRivetSherpaNNPDF.c_str (), leadingRivetSherpaNNPDF);
	      }
	  }

	TFile *histoRivetPowheg = TFile::Open (rivetPathPowheg.c_str ());
	histoRivetPowheg->cd ("");
	TDirectory *dirRivetPowheg = gDirectory;
	TList *mylistRivetPowheg = (TList *) dirRivetPowheg->GetListOfKeys ();
	TIter iterRivetPowheg (mylistRivetPowheg);
	TObject *tobjRivetPowheg = 0;
	while ((tobjRivetPowheg = iterRivetPowheg.Next ()))
	  {
	    string nameRivetPowheg = tobjRivetPowheg->GetName ();
	    if (nameRivetPowheg == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetPowheg;
		gDirectory->GetObject (nameRivetPowheg.c_str (), leadingRivetPowheg);
		TGraphAsymmErrors *leadingRivetPowhegStat;
		leadingRivetPowhegStat = (TGraphAsymmErrors *) leadingRivetPowheg->Clone ("");
		TGraphAsymmErrors *leadingRatioPowhegStat;
		leadingRatioPowhegStat = (TGraphAsymmErrors *) leadingRivetPowheg->Clone ("");
		TGraphAsymmErrors *leadingRatioPowheg;
		leadingRatioPowheg = (TGraphAsymmErrors *) leadingRivetPowheg->Clone ("");
	      }
	  }

	TFile *histoRivetPowheg0510 = TFile::Open (rivetPathPowheg0510.c_str ());
	histoRivetPowheg0510->cd ("");
	TDirectory *dirRivetPowheg0510 = gDirectory;
	TList *mylistRivetPowheg0510 = (TList *) dirRivetPowheg0510->GetListOfKeys ();
	TIter iterRivetPowheg0510 (mylistRivetPowheg0510);
	TObject *tobjRivetPowheg0510 = 0;
	while ((tobjRivetPowheg0510 = iterRivetPowheg0510.Next ()))
	  {
	    string nameRivetPowheg0510 = tobjRivetPowheg0510->GetName ();
	    if (nameRivetPowheg0510 == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetPowheg0510;
		gDirectory->GetObject (nameRivetPowheg0510.c_str (), leadingRivetPowheg0510);
		TGraphAsymmErrors *leadingRatioPowheg0510;
		leadingRatioPowheg0510 = (TGraphAsymmErrors *) leadingRivetPowheg0510->Clone ("");
	      }
	  }

	TFile *histoRivetPowheg2010 = TFile::Open (rivetPathPowheg2010.c_str ());
	histoRivetPowheg2010->cd ("");
	TDirectory *dirRivetPowheg2010 = gDirectory;
	TList *mylistRivetPowheg2010 = (TList *) dirRivetPowheg2010->GetListOfKeys ();
	TIter iterRivetPowheg2010 (mylistRivetPowheg2010);
	TObject *tobjRivetPowheg2010 = 0;
	while ((tobjRivetPowheg2010 = iterRivetPowheg2010.Next ()))
	  {
	    string nameRivetPowheg2010 = tobjRivetPowheg2010->GetName ();
	    if (nameRivetPowheg2010 == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetPowheg2010;
		gDirectory->GetObject (nameRivetPowheg2010.c_str (), leadingRivetPowheg2010);
		TGraphAsymmErrors *leadingRatioPowheg2010;
		leadingRatioPowheg2010 = (TGraphAsymmErrors *) leadingRivetPowheg2010->Clone ("");
	      }
	  }

	TFile *histoRivetPowheg1005 = TFile::Open (rivetPathPowheg1005.c_str ());
	histoRivetPowheg1005->cd ("");
	TDirectory *dirRivetPowheg1005 = gDirectory;
	TList *mylistRivetPowheg1005 = (TList *) dirRivetPowheg1005->GetListOfKeys ();
	TIter iterRivetPowheg1005 (mylistRivetPowheg1005);
	TObject *tobjRivetPowheg1005 = 0;
	while ((tobjRivetPowheg1005 = iterRivetPowheg1005.Next ()))
	  {
	    string nameRivetPowheg1005 = tobjRivetPowheg1005->GetName ();
	    if (nameRivetPowheg1005 == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetPowheg1005;
		gDirectory->GetObject (nameRivetPowheg1005.c_str (), leadingRivetPowheg1005);
		TGraphAsymmErrors *leadingRatioPowheg1005;
		leadingRatioPowheg1005 = (TGraphAsymmErrors *) leadingRivetPowheg1005->Clone ("");
	      }
	  }

	TFile *histoRivetPowheg1020 = TFile::Open (rivetPathPowheg1020.c_str ());
	histoRivetPowheg1020->cd ("");
	TDirectory *dirRivetPowheg1020 = gDirectory;
	TList *mylistRivetPowheg1020 = (TList *) dirRivetPowheg1020->GetListOfKeys ();
	TIter iterRivetPowheg1020 (mylistRivetPowheg1020);
	TObject *tobjRivetPowheg1020 = 0;
	while ((tobjRivetPowheg1020 = iterRivetPowheg1020.Next ()))
	  {
	    string nameRivetPowheg1020 = tobjRivetPowheg1020->GetName ();
	    if (nameRivetPowheg1020 == rivet_data)
	      {
		TGraphAsymmErrors *leadingRivetPowheg1020;
		gDirectory->GetObject (nameRivetPowheg1020.c_str (), leadingRivetPowheg1020);
		TGraphAsymmErrors *leadingRatioPowheg1020;
		leadingRatioPowheg1020 = (TGraphAsymmErrors *) leadingRivetPowheg1020->Clone ("");
	      }
	  }

	TFile *histoRivetMadGraph = TFile::Open (rivetPathMadGraph.c_str ());
	histoRivetMadGraph->cd ("");
	TDirectory *dirRivetMadGraph = gDirectory;
	TList *mylistRivetMadGraph = (TList *) dirRivetMadGraph->GetListOfKeys ();
	TIter iterRivetMadGraph (mylistRivetMadGraph);
	TObject *tobjRivetMadGraph = 0;
	while ((tobjRivetMadGraph = iterRivetMadGraph.Next ()))
	  {
	    string nameRivetMadGraph = tobjRivetMadGraph->GetName ();
	    if (nameRivetMadGraph == rivet_dataMG)
	      {
		TH1D *leadingRivetMadGraph_TH1;
		gDirectory->GetObject (nameRivetMadGraph.c_str (), leadingRivetMadGraph_TH1);
		int nthbins = leadingRivetMadGraph_TH1->GetNbinsX();
		TGraphAsymmErrors *leadingRivetMadGraph;
		leadingRivetMadGraph = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
		for (int n=0;n<nthbins;n++) {
		  leadingRivetMadGraph->SetPoint(n,leadingRivetMadGraph_TH1->GetBinCenter(n+1),leadingRivetMadGraph_TH1->GetBinContent(n+1));
		  leadingRivetMadGraph->SetPointEYhigh(n,leadingRivetMadGraph_TH1->GetBinError(n+1));
		  leadingRivetMadGraph->SetPointEYlow(n,leadingRivetMadGraph_TH1->GetBinError(n+1));
		}
		TGraphAsymmErrors *leadingRatioMadGraph;
		leadingRatioMadGraph = (TGraphAsymmErrors *) leadingRivetMadGraph->Clone ("");
	      }
	  }

	//-------------------------------------------------------------
	  
	leadingSystematics->SetName ("leadingSystematics");
	if (systTmpM.size () != leadingSystematics->GetNbinsX ())
	  cout << "WRONG NUMBER OF BINS (# syst from file->" <<systTmpM.size()<<" - # bins leadingsystematics->"<<leadingSystematics->GetNbinsX()<<")"<<endl;

	if (!incMultiplicity){
	  for (int i = 0; i < leadingSystematics->GetNbinsX (); i++)
	    {
	      double err = sqrt (pow (leading->GetBinError (i + 1), 2) + pow (systTmpM[i] * leadingSystematics->GetBinContent (i + 1), 2));
	      leadingSystematics->SetBinError (i + 1, err);
	    }
	} else {
	  for (int i = 0; i < leadingSystematics->GetNbinsX (); i++)
	    {
	      double temperr = 0.0;
	      for (int cc = i; cc < leadingSystematics->GetNbinsX (); cc++) {
		temperr = sqrt(pow(temperr,2) + pow(systTmpM[cc]*leadingSystematics->GetBinContent(cc + 1),2));
	      }
	      double err = sqrt (pow (leading->GetBinError (i + 1), 2) + pow (temperr, 2));
	      leadingSystematics->SetBinError (i + 1, err);
	    }

	}

	if ( (!absoluteNormalization) && (leadingSystematics->Integral()>1.001 | leadingSystematics->Integral()<0.999)) {
	  cout << "Warning: DATA is NOT NORMALIZED CORRECTLY! I will fix it...";
	  leadingSystematics->Scale(1./leadingSystematics->Integral());
	  leading->Scale(1./leading->Integral());
	}

	//When use_case = Jet Multi, then the absolute cross section is required...
	if (absoluteNormalization){
	  //Normalizing data to the luminosity
	  leadingSystematics->Scale(1./(4890.0)); //Int Lumi 1/pb -> bin in pb
	  leading->Scale(1./(4890.0));
	}

	plots->cd ();
	TPad *pad1 = new TPad("pad1","pad1",0.01,0.55,0.99,0.99);

	pad1->Draw();
	pad1->cd();
	pad1->SetTopMargin(0.1);
	pad1->SetBottomMargin(0.0);
	pad1->SetRightMargin(0.1);
	pad1->SetFillStyle(0);
	if (use_case !=3) pad1->SetLogy(1); 
	else pad1->SetLogy(0);

	if (use_case ==3){
	  leadingSystematics->SetMinimum((0.5-0.05*(whichjet-1))*leadingSystematics->GetMinimum());
	  leadingSystematics->SetMaximum((1.25+0.35*(whichjet-1))*leadingSystematics->GetMaximum());
	}
	//	leadingSystematics->SetLineColor (kRed+2);
	leadingSystematics->SetLineColor (kBlack);
	leadingSystematics->SetLineWidth (0.);
	leadingSystematics->SetMarkerStyle (20);
	leadingSystematics->SetFillColor (12);
	leadingSystematics->SetFillStyle (3004);
	leadingSystematics->SetMarkerColor (kBlack);

	leadingSystematics->GetXaxis()->SetTitleOffset (1.1);
	leadingSystematics->GetXaxis()->SetTitleSize (0.05);
	leadingSystematics->GetXaxis()->SetLabelSize (0.0);
	leadingSystematics->GetXaxis()->SetLabelFont (42);
	leadingSystematics->GetXaxis()->SetTitleFont (42);

	leadingSystematics->GetYaxis()->SetTitleOffset (1.);
	leadingSystematics->GetYaxis()->SetTitleSize (0.07);
	leadingSystematics->GetYaxis()->SetLabelSize (0.06);
	leadingSystematics->GetYaxis()->SetLabelFont (42);
	leadingSystematics->GetYaxis()->SetTitleFont (42);

	leadingSystematics->SetTitle();
	leadingSystematics->GetXaxis()->SetTitle ();

	if (use_case ==1) {
	  if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dN [pb]");
	  else {
	    if (lepton == 1) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/dN");
	    if (lepton == 2) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/dN");
	    if (lepton == 3) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}/#mu^{+}#mu^{-}}) d#sigma/dN");
	  }
	}

	if (use_case ==2) {
	  if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dp_{T} [pb/GeV]");
	  else {
	    if (lepton == 1) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/dp_{T}");
	    if (lepton == 2) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/dp_{T}");
	    if (lepton == 3) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}/#mu^{+}#mu^{-}}) d#sigma/dp_{T}");
	  }
	}

	if (use_case ==3) {
	  if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/d#eta [pb]");
	  else {
	    if (lepton == 1) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/d#eta");
	    if (lepton == 2) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/d#eta");
	    if (lepton == 3) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}/#mu^{+}#mu^{-}}) d#sigma/d#eta");
	  }
	}
	  
	if (use_case ==4) {
	  if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dH_{T} [pb/GeV]");
	  else {
	    if (lepton == 1) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/dH_{T}");
	    if (lepton == 2) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/dH_{T}");
	    if (lepton == 3) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}/#mu^{+}#mu^{-}}) d#sigma/dH_{T}");
	  }
	}
	  
	leadingSystematics->Draw ("E2");
	if (use_case ==1) leadingSystematics->GetXaxis()->SetNdivisions(110);
	leading->SetFillColor (kBlack);
	leading->SetFillStyle (3001);
	leading->SetMarkerColor (kBlack);
	leading->SetLineColor (kBlack);
	leading->SetLineWidth (0.);
	leading->SetMarkerStyle (20);
	leading->Draw ("E1SAME");

	TH1D *leadingRatio;
	TH1D *leadingRatio2;
	TH1D *leadingRatio3;
	leadingRatio = (TH1D *) leading->Clone ("leading");
	leadingRatio2 = (TH1D *) leading->Clone ("leading");
	leadingRatio3 = (TH1D *) leading->Clone ("leading");
	TH1D *leadingRatioSystematics;
	TH1D *leadingRatio2Systematics;
	TH1D *leadingRatio3Systematics;
	leadingRatioSystematics = (TH1D *) leadingSystematics->Clone ("leading");
	leadingRatio2Systematics = (TH1D *) leadingSystematics->Clone ("leading");
	leadingRatio3Systematics = (TH1D *) leadingSystematics->Clone ("leading");

	// Superimpose RIVET: -----------------------
	Double_t dummyXvar=0.;
	Double_t dummyYvar=0.;
	Int_t nRivetPoints = 0;
	Double_t dummyNorm = 0.;

	// SHERPA:
	nRivetPoints = leadingRivetSherpa->GetN();
	if (nRivetPoints != leadingSystematics->GetNbinsX ()) {cout << "Different number of bins wrt RIVET... quitting" << endl; return 0;}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    dummyNorm= (1516290./2089.46);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); //Divide by the bin width 
	  }
	  leadingRivetSherpaUP->GetPoint(ovo,dummyXvar,dummyYvar);
	  leadingRivetSherpaUP->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaUP->SetPointEYhigh(ovo,leadingRivetSherpaUP->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaUP->SetPointEYlow(ovo,leadingRivetSherpaUP->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    dummyNorm= (1157910./2229.49);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1));
	  }
	  leadingRivetSherpaDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaDOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaDOWN->SetPointEYhigh(ovo,leadingRivetSherpaDOWN->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaDOWN->SetPointEYlow(ovo,leadingRivetSherpaDOWN->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaQUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    dummyNorm= (343130./2141.66);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }
	  leadingRivetSherpaQUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaQUP->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaQUP->SetPointEYhigh(ovo,leadingRivetSherpaQUP->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaQUP->SetPointEYlow(ovo,leadingRivetSherpaQUP->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaQDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    dummyNorm= (346296./2184.26);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpaQDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaQDOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaQDOWN->SetPointEYhigh(ovo,leadingRivetSherpaQDOWN->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaQDOWN->SetPointEYlow(ovo,leadingRivetSherpaQDOWN->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaQcutUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    dummyNorm= (486429./2125.62);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }
	  leadingRivetSherpaQcutUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaQcutUP->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaQcutUP->SetPointEYhigh(ovo,leadingRivetSherpaQcutUP->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaQcutUP->SetPointEYlow(ovo,leadingRivetSherpaQcutUP->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaQcutDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    dummyNorm= (188604./2176.58);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpaQcutDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaQcutDOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaQcutDOWN->SetPointEYhigh(ovo,leadingRivetSherpaQcutDOWN->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaQcutDOWN->SetPointEYlow(ovo,leadingRivetSherpaQcutDOWN->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaMSTW->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    dummyNorm= (233071./2141.35);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpaMSTW->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaMSTW->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaMSTW->SetPointEYhigh(ovo,leadingRivetSherpaMSTW->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaMSTW->SetPointEYlow(ovo,leadingRivetSherpaMSTW->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaNNPDF->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    dummyNorm= (325973./2120.42);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpaNNPDF->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaNNPDF->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaNNPDF->SetPointEYhigh(ovo,leadingRivetSherpaNNPDF->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaNNPDF->SetPointEYlow(ovo,leadingRivetSherpaNNPDF->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaStat->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    //	    dummyNorm= (343072./2145.);
	    dummyNorm= (1331230./2144.84);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpaStat->GetPoint(ovo,dummyXvar,dummyYvar); 
	  //	  cout << leadingRivetSherpaStat->GetErrorYhigh(ovo) << " " << dummyYvar  << " " << endl;
	  leadingRivetSherpaStat->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaStat->SetPointEYhigh(ovo,leadingRivetSherpaStat->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaStat->SetPointEYlow(ovo,leadingRivetSherpaStat->GetErrorYlow(ovo)/dummyNorm);
	  leadingRatioSherpaStat->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovo+1));
	  leadingRatioSherpaStat->SetPointEYhigh(ovo,(leadingRivetSherpaStat->GetErrorYhigh(ovo))/(dummyYvar/dummyNorm));
	  leadingRatioSherpaStat->SetPointEYlow(ovo,(leadingRivetSherpaStat->GetErrorYlow(ovo))/(dummyYvar/dummyNorm));
	}

	Double_t dummyNorm = 0.;
	Double_t y1temp = 0.;
	Double_t y2temp = 0.;
	Double_t x1temp = 0.;
	Double_t x2temp = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpa->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}

	//	TCanvas *cacca = new TCanvas("cc","cc",0,0,800,600);
	//	cacca->cd();
	//	TGraph *statTest = new TGraph(nRivetPoints); // stattest
	//	ststTest->SetTitle("Stat. Uncertainty on F/R scale variation envelop");
	//	statTest->Draw("ap");

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpa->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaDOWN->GetPoint(ovo,x1temp,y1temp); 
	  leadingRivetSherpaUP->GetPoint(ovo,x2temp,y2temp); 

//	  cout << "diff = " << fabs(y1temp-y2temp) 
//	       << "; uncertainty = " << sqrt(leadingRivetSherpaDOWN->GetErrorYhigh(ovo)*leadingRivetSherpaDOWN->GetErrorYhigh(ovo) + leadingRivetSherpaUP->GetErrorYhigh(ovo)*leadingRivetSherpaUP->GetErrorYhigh(ovo))
//	       << "; relative = " << sqrt(leadingRivetSherpaDOWN->GetErrorYhigh(ovo)*leadingRivetSherpaDOWN->GetErrorYhigh(ovo) + leadingRivetSherpaUP->GetErrorYhigh(ovo)*leadingRivetSherpaUP->GetErrorYhigh(ovo))/fabs(y1temp-y2temp) << endl;
//
//	  statTest->SetPoint(ovo,dummyXvar,sqrt(leadingRivetSherpaDOWN->GetErrorYhigh(ovo)*leadingRivetSherpaDOWN->GetErrorYhigh(ovo) + leadingRivetSherpaUP->GetErrorYhigh(ovo)*leadingRivetSherpaUP->GetErrorYhigh(ovo))/fabs(y1temp-y2temp));//stattest

	  if (absoluteNormalization) {
	    dummyNorm= (1331230./2144.84);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpa->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	  //	  leadingRivetSherpa->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm);
	  //	  leadingRivetSherpa->SetPointEYlow(ovo,-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm);
	  leadingRivetSherpa->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm + leadingRivetSherpaStat->GetErrorYhigh(ovo));
	  leadingRivetSherpa->SetPointEYlow(ovo,-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm + leadingRivetSherpaStat->GetErrorYlow(ovo));
	  leadingRatioSherpa->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovo+1));
	  //	  leadingRatioSherpa->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	  //	  leadingRatioSherpa->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	  leadingRatioSherpa->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm + leadingRivetSherpaStat->GetErrorYhigh(ovo))/(dummyYvar/dummyNorm));
	  leadingRatioSherpa->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm + leadingRivetSherpaStat->GetErrorYlow(ovo))/(dummyYvar/dummyNorm));
	    
	  leadingRatio->SetBinContent(ovo+1,1.0);
	  //	  leadingRatio->SetBinError(ovo+1,leading->GetBinError(ovo+1)*(dummyYvar/dummyNorm)/(leadingSystematics->GetBinContent(ovo+1)*leadingSystematics->GetBinContent(ovo+1)));
	  leadingRatio->SetBinError(ovo+1,leading->GetBinError(ovo+1)/leading->GetBinContent(ovo+1));

	  leadingRatioSystematics->SetBinContent(ovo+1,1.0);
	  leadingRatioSystematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/leadingSystematics->GetBinContent(ovo+1));
	}

	// Q envelop for Sherpa:
	TGraphAsymmErrors *leadingRivetSherpaQ;
	leadingRivetSherpaQ = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ();
	TGraphAsymmErrors *leadingRatioSherpaQ;
	leadingRatioSherpaQ = (TGraphAsymmErrors *) leadingRatioSherpa->Clone ();

	Double_t y1temp = 0.;
	Double_t y2temp = 0.;
	Double_t x1temp = 0.;
	Double_t x2temp = 0.;

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaQ->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaQUP->GetPoint(ovo,x1temp,y1temp); 
	  leadingRivetSherpaQDOWN->GetPoint(ovo,x2temp,y2temp); 

	  leadingRivetSherpaQ->SetPoint(ovo,dummyXvar,dummyYvar);
	  leadingRivetSherpaQ->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar)-dummyYvar + leadingRivetSherpa->GetErrorYhigh(ovo));
	  leadingRivetSherpaQ->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar) + leadingRivetSherpa->GetErrorYlow(ovo));

	  leadingRatioSherpaQ->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovo+1));
	  leadingRatioSherpaQ->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar)-dummyYvar)/dummyYvar + leadingRatioSherpa->GetErrorYhigh(ovo));
	  leadingRatioSherpaQ->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar)/dummyYvar + leadingRatioSherpa->GetErrorYlow(ovo));

	}

	// Qcut envelop for Sherpa:
	TGraphAsymmErrors *leadingRivetSherpaQcut;
	leadingRivetSherpaQcut = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ();
	TGraphAsymmErrors *leadingRatioSherpaQcut;
	leadingRatioSherpaQcut = (TGraphAsymmErrors *) leadingRatioSherpa->Clone ();

	Double_t y1temp = 0.;
	Double_t y2temp = 0.;
	Double_t x1temp = 0.;
	Double_t x2temp = 0.;

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaQcut->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaQcutUP->GetPoint(ovo,x1temp,y1temp); 
	  leadingRivetSherpaQcutDOWN->GetPoint(ovo,x2temp,y2temp); 

	  leadingRivetSherpaQcut->SetPoint(ovo,dummyXvar,dummyYvar);
	  leadingRivetSherpaQcut->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar)-dummyYvar + leadingRivetSherpaQ->GetErrorYhigh(ovo));
	  leadingRivetSherpaQcut->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar) + leadingRivetSherpaQ->GetErrorYlow(ovo));

	  leadingRatioSherpaQcut->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovo+1));
	  leadingRatioSherpaQcut->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar)-dummyYvar)/dummyYvar + leadingRatioSherpaQ->GetErrorYhigh(ovo));
	  leadingRatioSherpaQcut->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar)/dummyYvar + leadingRatioSherpaQ->GetErrorYlow(ovo));

	}

	// PDF envelop for Sherpa:
	TGraphAsymmErrors *leadingRivetSherpaPDF;
	leadingRivetSherpaPDF = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ();
	TGraphAsymmErrors *leadingRatioSherpaPDF;
	leadingRatioSherpaPDF = (TGraphAsymmErrors *) leadingRatioSherpa->Clone ();

	Double_t y1temp = 0.;
	Double_t y2temp = 0.;
	Double_t x1temp = 0.;
	Double_t x2temp = 0.;

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaPDF->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaMSTW->GetPoint(ovo,x1temp,y1temp); 
	  leadingRivetSherpaNNPDF->GetPoint(ovo,x2temp,y2temp); 

	  leadingRivetSherpaPDF->SetPoint(ovo,dummyXvar,dummyYvar);
	  leadingRivetSherpaPDF->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar)-dummyYvar + leadingRivetSherpaQcut->GetErrorYhigh(ovo));
	  leadingRivetSherpaPDF->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar) + leadingRivetSherpaQcut->GetErrorYlow(ovo));

	  leadingRatioSherpaPDF->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovo+1));
	  leadingRatioSherpaPDF->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar)-dummyYvar)/dummyYvar + leadingRatioSherpaQcut->GetErrorYhigh(ovo));
	  leadingRatioSherpaPDF->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar)/dummyYvar + leadingRatioSherpaQcut->GetErrorYlow(ovo));

	}


	// POWHEG:
	nRivetPoints = leadingRivetPowheg->GetN();
	if (nRivetPoints != leadingSystematics->GetNbinsX ()) {cout << "Different number of bins wrt RIVET... quitting" << endl; return 0;}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowheg2010->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    if (lepton ==1) dummyNorm= (4602659.0/276.761);
	    if (lepton ==2) dummyNorm= (5719233.0/276.603);
	    if (lepton ==3) dummyNorm= (4602659.0/276.761) + (5719233.0/276.603);
	    //	    dummyNorm= (3450019667.4/876.6)/2.;
	    //	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); //Divide by the bin width 
	  }
	  leadingRivetPowheg2010->GetPoint(ovo,dummyXvar,dummyYvar);
	  leadingRivetPowheg2010->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetPowheg2010->SetPointEYhigh(ovo,leadingRivetPowheg2010->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetPowheg2010->SetPointEYlow(ovo,leadingRivetPowheg2010->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowheg0510->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    dummyNorm= (4087041585.8/1040.)/2.;
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1));
	  }
	  leadingRivetPowheg0510->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetPowheg0510->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetPowheg0510->SetPointEYhigh(ovo,leadingRivetPowheg0510->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetPowheg0510->SetPointEYlow(ovo,leadingRivetPowheg0510->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowheg1020->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    if (lepton ==1) dummyNorm= (4602659.0/276.761);
	    if (lepton ==2) dummyNorm= (5719233.0/276.603);
	    if (lepton ==3) dummyNorm= (4602659.0/276.761) + (5719233.0/276.603);
	    //	    dummyNorm= (4002640330.7/1015.)/2.;
	    //	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }
	  leadingRivetPowheg1020->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetPowheg1020->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetPowheg1020->SetPointEYhigh(ovo,leadingRivetPowheg1020->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetPowheg1020->SetPointEYlow(ovo,leadingRivetPowheg1020->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowheg1005->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    if (lepton ==1) dummyNorm= (4602659.0/276.761);
	    if (lepton ==2) dummyNorm= (5719233.0/276.603);
	    if (lepton ==3) dummyNorm= (4602659.0/276.761) + (5719233.0/276.603);
	    //	    dummyNorm= (3619611428.4/921.8)/2.;
	    //	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetPowheg1005->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetPowheg1005->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetPowheg1005->SetPointEYhigh(ovo,leadingRivetPowheg1005->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetPowheg1005->SetPointEYlow(ovo,leadingRivetPowheg1005->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowhegStat->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    if (lepton ==1) dummyNorm= (4602659.0/276.761);
	    if (lepton ==2) dummyNorm= (5719233.0/276.603);
	    if (lepton ==3) dummyNorm= (4602659.0/276.761) + (5719233.0/276.603);
	    //	    dummyNorm= (3827167486.5/972.9)/2.;
	    //	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetPowhegStat->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetPowhegStat->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetPowhegStat->SetPointEYhigh(ovo,leadingRivetPowhegStat->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetPowhegStat->SetPointEYlow(ovo,leadingRivetPowhegStat->GetErrorYlow(ovo)/dummyNorm);
	  leadingRatioPowhegStat->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovo+1));
	  leadingRatioPowhegStat->SetPointEYhigh(ovo,(leadingRivetPowhegStat->GetErrorYhigh(ovo))/(dummyYvar/dummyNorm));
	  leadingRatioPowhegStat->SetPointEYlow(ovo,(leadingRivetPowhegStat->GetErrorYlow(ovo))/(dummyYvar/dummyNorm));
	}

	Double_t dummyNorm = 0.;
	Double_t y1temp = 0.;
	Double_t y2temp = 0.;
	Double_t x1temp = 0.;
	Double_t x2temp = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowheg->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowheg->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetPowheg0510->GetPoint(ovo,x1temp,y1temp); 
	  leadingRivetPowheg2010->GetPoint(ovo,x2temp,y2temp); 


	  if (absoluteNormalization) {
	    if (lepton ==1) dummyNorm= (4602659.0/276.761);
	    if (lepton ==2) dummyNorm= (5719233.0/276.603);
	    if (lepton ==3) dummyNorm= (4602659.0/276.761) + (5719233.0/276.603);
	    //	    dummyNorm= (3827167486.5/972.9)/2.;
	    //	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetPowheg->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	  //	  leadingRivetPowheg->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm);
	  //	  leadingRivetPowheg->SetPointEYlow(ovo,-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm);
	  leadingRivetPowheg->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm + leadingRivetPowhegStat->GetErrorYhigh(ovo));
	  leadingRivetPowheg->SetPointEYlow(ovo,-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm + leadingRivetPowhegStat->GetErrorYlow(ovo));
	  leadingRatioPowheg->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovo+1));
	  //	  leadingRatioPowheg->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	  //	  leadingRatioPowheg->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	  leadingRatioPowheg->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm + leadingRivetPowhegStat->GetErrorYhigh(ovo))/(dummyYvar/dummyNorm));
	  leadingRatioPowheg->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm + leadingRivetPowhegStat->GetErrorYlow(ovo))/(dummyYvar/dummyNorm));
	    
	  leadingRatio3->SetBinContent(ovo+1,1.0);
	  leadingRatio3->SetBinError(ovo+1,leading->GetBinError(ovo+1)/leading->GetBinContent(ovo+1));

	  leadingRatio3Systematics->SetBinContent(ovo+1,1.0);
	  leadingRatio3Systematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/leadingSystematics->GetBinContent(ovo+1));
	}
	  
	// 2nd envelop for Powheg:
	TGraphAsymmErrors *leadingRivetPowheg2ENV;
	leadingRivetPowheg2ENV = (TGraphAsymmErrors *) leadingRivetPowheg->Clone ();
	TGraphAsymmErrors *leadingRatioPowheg2ENV;
	leadingRatioPowheg2ENV = (TGraphAsymmErrors *) leadingRatioPowheg->Clone ();

	Double_t y1temp = 0.;
	Double_t y2temp = 0.;
	Double_t x1temp = 0.;
	Double_t x2temp = 0.;

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowheg2ENV->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetPowheg1020->GetPoint(ovo,x1temp,y1temp); 
	  leadingRivetPowheg1005->GetPoint(ovo,x2temp,y2temp); 

	  leadingRivetPowheg2ENV->SetPoint(ovo,dummyXvar,dummyYvar);
	  leadingRivetPowheg2ENV->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar)-dummyYvar + leadingRivetPowheg->GetErrorYhigh(ovo));
	  leadingRivetPowheg2ENV->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar) + leadingRivetPowheg->GetErrorYlow(ovo));

	  leadingRatioPowheg2ENV->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovo+1));
	  leadingRatioPowheg2ENV->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar)-dummyYvar)/dummyYvar + leadingRatioPowheg->GetErrorYhigh(ovo));
	  leadingRatioPowheg2ENV->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar)/dummyYvar + leadingRatioPowheg->GetErrorYlow(ovo));

	}


	// Madgraph:

	Double_t dummyNorm = 0.;
	//	Double_t y1temp = 0.;
	//	Double_t y2temp = 0.;
	//	Double_t x1temp = 0.;
	//	Double_t x2temp = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetMadGraph->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    dummyNorm= 3.0 * 0.000000001 * 1680.67 / (2.0 * 3048.0);
	    if (lepton ==3) dummyNorm = dummyNorm*2;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); //Divide by the bin width 
	  }
	  leadingRivetMadGraph->GetPoint(ovo,dummyXvar,dummyYvar); 
	  //	  leadingRivetMadGraphDOWN->GetPoint(ovo,x1temp,y1temp); 
	  //	  leadingRivetMadGraphUP->GetPoint(ovo,x2temp,y2temp); 
	  leadingRivetMadGraph->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	  //	  leadingRivetMadGraph->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm);
	  //	  leadingRivetMadGraph->SetPointEYlow(ovo,-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm);
	  leadingRivetMadGraph->SetPointEYhigh(ovo,leadingRivetMadGraph->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetMadGraph->SetPointEYlow(ovo,leadingRivetMadGraph->GetErrorYlow(ovo)/dummyNorm);

	  leadingRatioMadGraph->SetPoint(ovo,dummyXvar,(dummyYvar/dummyNorm)/leadingSystematics->GetBinContent(ovo+1));
	  //	  leadingRatioMadGraph->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	  //	  leadingRatioMadGraph->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	  leadingRatioMadGraph->SetPointEYhigh(ovo,leadingRivetMadGraph->GetErrorYhigh(ovo)*dummyNorm/dummyYvar);
	  leadingRatioMadGraph->SetPointEYlow(ovo,leadingRivetMadGraph->GetErrorYlow(ovo)*dummyNorm/dummyYvar);

	  leadingRatio2->SetBinContent(ovo+1,1.0);
	  leadingRatio2->SetBinError(ovo+1,leading->GetBinError(ovo+1)/leading->GetBinContent(ovo+1));

	  leadingRatio2Systematics->SetBinContent(ovo+1,1.0);
	  leadingRatio2Systematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/leadingSystematics->GetBinContent(ovo+1));
	}

	//	leadingRivetSherpaPDF->SetFillColor(kBlue-9);
	//	leadingRivetSherpaPDF->SetFillStyle(3004);
	//	leadingRivetSherpaPDF->SetLineColor(kBlue-9);
	//	leadingRivetSherpaPDF->SetMarkerColor(kBlue-9);
	//	leadingRivetSherpaPDF->SetLineWidth(0.6);
	//	leadingRivetSherpaPDF->Draw("5");
	//
	//	leadingRivetSherpaQcut->SetFillColor(kAzure+6);
	//	leadingRivetSherpaQcut->SetFillStyle(3004);
	//	leadingRivetSherpaQcut->SetLineColor(kAzure+6);
	//	leadingRivetSherpaQcut->SetMarkerColor(kAzure+6);
	//	leadingRivetSherpaQcut->SetLineWidth(0.6);
	//	leadingRivetSherpaQcut->Draw("5");
	//
	//	leadingRivetSherpaQ->SetFillColor(kBlue-7);
	//	leadingRivetSherpaQ->SetFillStyle(3004);
	//	leadingRivetSherpaQ->SetLineColor(kBlue-7);
	//	leadingRivetSherpaQ->SetMarkerColor(kBlue-7);
	//	leadingRivetSherpaQ->SetLineWidth(0.6);
	//	leadingRivetSherpaQ->Draw("5");
	//
	//	leadingRivetSherpa->SetFillColor(kBlue-4);
	//	leadingRivetSherpa->SetFillStyle(3004);
	//	leadingRivetSherpa->SetLineColor(kBlue-4);
	//	leadingRivetSherpa->SetMarkerColor(kBlue-4);
	//	leadingRivetSherpa->SetLineWidth(0.6);
	//	leadingRivetSherpa->Draw("5");

	leadingRivetSherpaStat->SetFillColor(kBlue-10);
	leadingRivetSherpaStat->SetFillStyle(1001);
	leadingRivetSherpaStat->SetLineColor(kBlue);
	leadingRivetSherpaStat->SetMarkerColor(kBlue);
	leadingRivetSherpaStat->SetMarkerStyle(24);
	//	leadingRivetSherpaStat->SetLineWidth(0.6);
	//	leadingRivetSherpaStat->Draw("2");
	leadingRivetSherpaStat->Draw("pz");

	//	leadingRivetPowheg2ENV->SetFillColor(kGreen-6);
	//	leadingRivetPowheg2ENV->SetFillStyle(3004);
	//	leadingRivetPowheg2ENV->SetLineColor(kGreen-6);
	//	leadingRivetPowheg2ENV->SetMarkerColor(kGreen-6);
	//	leadingRivetPowheg2ENV->SetLineWidth(0.6);
	//	leadingRivetPowheg2ENV->Draw("5");
	//
	//	leadingRivetPowheg->SetFillColor(kGreen+2);
	//	leadingRivetPowheg->SetFillStyle(3004);
	//	leadingRivetPowheg->SetLineColor(kGreen+2);
	//	leadingRivetPowheg->SetMarkerColor(kGreen+2);
	//	leadingRivetPowheg->SetLineWidth(0.6);
	//	leadingRivetPowheg->Draw("5");

	leadingRivetPowhegStat->SetFillColor(kGreen-8);
	leadingRivetPowhegStat->SetFillStyle(1001);
	leadingRivetPowhegStat->SetLineColor(kGreen+4);
	leadingRivetPowhegStat->SetMarkerColor(kGreen+4);
	leadingRivetPowhegStat->SetMarkerStyle(26);
	//	leadingRivetPowhegStat->SetLineWidth(0.6);
	//	leadingRivetPowhegStat->Draw("2");
	leadingRivetPowhegStat->Draw("pz");

	leadingRivetMadGraph->SetFillColor(kOrange-2);
	leadingRivetMadGraph->SetFillStyle(1001);
	leadingRivetMadGraph->SetLineColor(kOrange+10);
	leadingRivetMadGraph->SetMarkerColor(kOrange+10);
	leadingRivetMadGraph->SetMarkerStyle(25);
	//	leadingRivetMadGraph->SetLineWidth(0.6);
	//	leadingRivetMadGraph->Draw("2");
	leadingRivetMadGraph->Draw("pz");

	//	leadingSystematics->Draw ("E2SAME");
	leading->Draw ("ESAME");
	//-------------------------------------------

	// Draw the label and save plot: (in the proper position)

	TLatex *latexLabel;

	if (use_case ==3){
	  if (lepton ==1) latexLabel = CMSPrel (4.890, "Z/#gamma*#rightarrow ee channel", 0.20, 0.87);
	  if (lepton ==2) latexLabel = CMSPrel (4.890, "Z/#gamma*#rightarrow #mu#mu channel", 0.20, 0.87);
	  if (lepton ==3) latexLabel = CMSPrel (4.890, "Z/#gamma*#rightarrow ll channel", 0.20, 0.87);
	}

	if (use_case ==2 || use_case ==1 || use_case == 4){
	  if (lepton ==1) latexLabel = CMSPrel (4.890, "Z/#gamma*#rightarrow ee channel", 0.20, 0.21);
	  if (lepton ==2) latexLabel = CMSPrel (4.890, "Z/#gamma*#rightarrow #mu#mu channel", 0.20, 0.21);
	  if (lepton ==3) latexLabel = CMSPrel (4.890, "Z/#gamma*#rightarrow ll channel", 0.20, 0.21);
	}

	leadingSystematics->SetMarkerColor(kBlack);
	leadingSystematics->SetMarkerSize(0.8);
	leading->SetMarkerSize(0.8);

	latexLabel->Draw ("same");
	  
	TLegend *legenddx_d;

	if (use_case ==3){
	  legenddx_d = new TLegend (0.64, 0.64, 0.99, 0.89);	   
	  legenddx_d->SetFillColor (0);
	  legenddx_d->SetFillStyle (1001);
	  legenddx_d->SetBorderSize (1);
	  legenddx_d->SetTextSize(.05);
	  legenddx_d->AddEntry (leadingSystematics, "Data", "PLEF");
	  //	  legenddx_d->AddEntry (leading, "Data (Stat.)", "PLE");
	  //	  legenddx_d->AddEntry (leadingSystematics, "Data (stat+syst)", "PEL");
	  legenddx_d->AddEntry (leadingRivetSherpaStat, "Sherpa2 (NLO+PS)", "PLEF");
	  //	  legenddx_d->AddEntry (leadingRivetSherpa, "Sherpa2 F/R scale var.", "F");
	  //	  legenddx_d->AddEntry (leadingRivetSherpaQ, "Sherpa2 Resumm. scale var.", "F");
	  //	  legenddx_d->AddEntry (leadingRivetSherpaQcut, "Sherpa2 Match. scale var.", "F");
	  //	  legenddx_d->AddEntry (leadingRivetSherpaPDF, "Sherpa2 PDF var.", "F");
	  //	  legenddx_d->AddEntry (leadingRivetPowhegStat, "Powheg(MiNLO) (stat.)", "F");
	  legenddx_d->AddEntry (leadingRivetPowhegStat, "Powheg (Z+1j NLO)", "PLEF");
	  //	  legenddx_d->AddEntry (leadingRivetPowheg, "Powheg(MiNLO) var.1", "F");
	  //	  legenddx_d->AddEntry (leadingRivetPowheg2ENV, "Powheg(MiNLO) var.2", "F");
	  //	  legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph (stat. only)", "F");
	  legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph (LO+PS)", "PLEF");
	  legenddx_d->Draw ("same");
	} else {
	  legenddx_d = new TLegend (0.64, 0.64, 0.99, 0.89);	   
	  legenddx_d->SetFillColor (0);
	  legenddx_d->SetFillStyle (1001);
	  legenddx_d->SetBorderSize (1);
	  legenddx_d->SetNColumns(1);
	  legenddx_d->SetTextSize(.05);
	  //	  legenddx_d->AddEntry (leading, "Data (stat)", "PLE");
	  legenddx_d->AddEntry (leadingSystematics, "Data", "PLEF");
	  //	  legenddx_d->AddEntry (leadingSystematics, "Data (stat+syst)", "PEL");
	  //	  legenddx_d->AddEntry (leadingRivetSherpaStat, "Sherpa2 (stat. only)", "F");
	  legenddx_d->AddEntry (leadingRivetSherpaStat, "Sherpa2 (NLO+PS)", "PLEF");
	  //	  legenddx_d->AddEntry (leadingRivetSherpa, "Sherpa2 F/R var.", "F");
	  //	  legenddx_d->AddEntry (leadingRivetSherpaQ, "Sherpa2 Resumm. scale var.", "F");
	  //	  legenddx_d->AddEntry (leadingRivetSherpaQcut, "Sherpa2 Match scale var.", "F");
	  //	  legenddx_d->AddEntry (leadingRivetSherpaPDF, "Sherpa2 PDF var.", "F");
	  //	  legenddx_d->AddEntry (leadingRivetPowhegStat, "Powheg(MiNLO) (stat.)", "F");
	  legenddx_d->AddEntry (leadingRivetPowhegStat, "Powheg (Z+1j NLO)", "PLEF");
	  //	  legenddx_d->AddEntry (leadingRivetPowheg, "Powheg(MiNLO) var.1", "F");
	  //	  legenddx_d->AddEntry (leadingRivetPowheg2ENV, "Powheg(MiNLO) var.2", "F");
	  //	  legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph (stat. only)", "F");
	  legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph (LO+PS)", "PLEF");
	  legenddx_d->Draw ("same");
	}


	// Sherpa ratio plot: ----------------------

	plots->cd ();
	TPad *pad2 = new TPad("pad2","pad2",0.01,0.39,0.99,0.55);
	pad2->Draw();
	pad2->cd();
	pad2->SetTopMargin(0.0);
	pad2->SetBottomMargin(0.0);
	pad2->SetRightMargin(0.1);
	pad2->SetFillStyle(0);

	leadingRatioSystematics->GetXaxis()->SetLabelFont (42);
	leadingRatioSystematics->GetXaxis()->SetTitleFont (42);
	leadingRatioSystematics->GetXaxis()->SetTitleSize(0.14);
	leadingRatioSystematics->GetXaxis()->SetLabelSize(0.0);
	leadingRatioSystematics->GetYaxis()->SetTitleSize(0.14);
	leadingRatioSystematics->GetYaxis()->SetLabelSize(0.14);
	leadingRatioSystematics->GetYaxis()->SetTitleOffset(0.45);
	leadingRatioSystematics->GetYaxis()->SetTitle("Theory/Data   ");   
	leadingRatioSystematics->GetYaxis()->SetNdivisions(505);
	leadingRatioSystematics->GetYaxis()->SetRangeUser(0.1,1.9);
	leadingRatioSystematics->SetTitle("");	  
	leadingRatioSystematics->SetMarkerStyle(1);
	leadingRatio->SetMarkerStyle(1);
	leadingRatioSystematics->Draw ("E2");
	leadingRatio->Draw ("E1SAME");

	//	leadingRatioSherpaPDF->SetFillColor(kBlue-9);
	//	leadingRatioSherpaPDF->SetFillStyle(3004);
	//	leadingRatioSherpaPDF->SetLineColor(kBlue-9);
	//	leadingRatioSherpaPDF->SetMarkerColor(kBlue-9);
	//	leadingRatioSherpaPDF->SetLineWidth(0.6);
	//	leadingRatioSherpaPDF->Draw("5");
	//
	//	leadingRatioSherpaQcut->SetFillColor(kAzure+6);
	//	leadingRatioSherpaQcut->SetFillStyle(3004);
	//	leadingRatioSherpaQcut->SetLineColor(kAzure+6);
	//	leadingRatioSherpaQcut->SetMarkerColor(kAzure+6);
	//	leadingRatioSherpaQcut->SetLineWidth(0.6);
	//	leadingRatioSherpaQcut->Draw("5");
	//
	//	leadingRatioSherpaQ->SetFillColor(kBlue-7);
	//	leadingRatioSherpaQ->SetFillStyle(3004);
	//	leadingRatioSherpaQ->SetLineColor(kBlue-7);
	//	leadingRatioSherpaQ->SetMarkerColor(kBlue-7);
	//	leadingRatioSherpaQ->SetLineWidth(0.6);
	//	leadingRatioSherpaQ->Draw("5");

	//	leadingRatioSherpa->SetFillColor(kBlue-4);
	//	leadingRatioSherpa->SetFillStyle(3004);
	//	leadingRatioSherpa->SetLineColor(kBlue-4);
	//	leadingRatioSherpa->SetMarkerColor(kBlue-4);
	//	leadingRatioSherpa->SetLineWidth(0.6);
	//	leadingRatioSherpa->Draw("5");

	leadingRatioSherpaStat->SetFillColor(kBlue-10);
	leadingRatioSherpaStat->SetFillStyle(1001);
	leadingRatioSherpaStat->SetLineColor(kBlue);
	leadingRatioSherpaStat->SetMarkerColor(kBlue);
	leadingRatioSherpaStat->SetMarkerStyle(24);
	leadingRatioSherpaStat->SetLineWidth(1);
	leadingRatioSherpaStat->Draw("2");
	leadingRatioSherpaStat->Draw("pz");

	leadingRatioSystematics->Draw ("E2SAME");
	leadingRatio->Draw ("E1SAME");

	//	TLine *OLine = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	//	OLine->SetLineColor(kBlack);
	//	OLine->SetLineStyle(1);
	//	OLine->SetLineWidth(0.);
	//	OLine->Draw();

	TLatex *latexLabel = new TLatex();
	latexLabel->SetTextSize(0.14);
	latexLabel->SetTextFont(42);
	latexLabel->SetLineWidth(2);
	latexLabel->SetNDC();
	latexLabel->DrawLatex(0.2,0.09,"Sherpa2 (NLO+PS)");	  

	// Powheg ratio plot: ----------------------------------
	plots->cd ();
	TPad *pad4 = new TPad("pad4","pad4",0.01,0.23,0.99,0.39);
	pad4->Draw();
	pad4->cd();
	pad4->SetTopMargin(0.0);
	pad4->SetBottomMargin(0.0);
	pad4->SetRightMargin(0.1);
	pad4->SetFillStyle(0);

	leadingRatio3Systematics->GetXaxis()->SetLabelFont (42);
	leadingRatio3Systematics->GetXaxis()->SetTitleFont (42);
	leadingRatio3Systematics->GetXaxis()->SetLabelSize(0.0);
	leadingRatio3Systematics->GetYaxis()->SetTitleSize(0.14);
	leadingRatio3Systematics->GetYaxis()->SetLabelSize(0.14);
	leadingRatio3Systematics->GetYaxis()->SetTitleOffset(0.45);
	leadingRatio3Systematics->GetYaxis()->SetTitle("Theory/Data   ");   
	leadingRatio3Systematics->GetYaxis()->SetNdivisions(505);
	leadingRatio3Systematics->GetYaxis()->SetRangeUser(0.1,1.9);
	leadingRatio3Systematics->SetMarkerStyle(1);
	leadingRatio3->SetMarkerStyle(1);
	leadingRatio3Systematics->SetTitle("");	  
	leadingRatio3Systematics->Draw ("E2");
	leadingRatio3->Draw ("E1SAME");

	//	leadingRatioPowheg2ENV->SetFillColor(kGreen-6);
	//	leadingRatioPowheg2ENV->SetFillStyle(3004);
	//	leadingRatioPowheg2ENV->SetLineColor(kGreen-6);
	//	leadingRatioPowheg2ENV->SetMarkerColor(kGreen-6);
	//	leadingRatioPowheg2ENV->SetLineWidth(0.6);
	//	leadingRatioPowheg2ENV->Draw("5");
	//
	//	leadingRatioPowheg->SetFillColor(kGreen+2);
	//	leadingRatioPowheg->SetFillStyle(3004);
	//	leadingRatioPowheg->SetLineColor(kGreen+2);
	//	leadingRatioPowheg->SetMarkerColor(kGreen+2);
	//	leadingRatioPowheg->SetLineWidth(0.6);
	//	leadingRatioPowheg->Draw("5");

	leadingRatioPowhegStat->SetFillColor(kGreen+8);
	leadingRatioPowhegStat->SetFillStyle(1001);
	leadingRatioPowhegStat->SetLineColor(kGreen+4);
	leadingRatioPowhegStat->SetMarkerColor(kGreen+4);
	leadingRatioPowhegStat->SetMarkerStyle(26);
	leadingRatioPowhegStat->SetLineWidth(1);
	leadingRatioPowhegStat->Draw("2");
	leadingRatioPowhegStat->Draw("pz");

	leadingRatio3Systematics->Draw ("E2SAME");
	leadingRatio3->Draw ("E1SAME");

	//	TLine *OLine3 = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	//	OLine3->SetLineColor(kBlack);
	//	OLine3->SetLineWidth(1);
	//	OLine3->SetLineStyle(1);
	//	OLine3->Draw();

	TLatex *latexLabel = new TLatex();
	latexLabel->SetTextSize(0.14);
	latexLabel->SetTextFont(42);
	latexLabel->SetLineWidth(2);
	latexLabel->SetNDC();
	latexLabel->DrawLatex(0.2,0.09,"Powheg (Z+1j NLO)");	  


	// Madgraph ratio plot: ---------------------
	plots->cd();
	TPad *pad3 = new TPad("pad3","pad3",0.01,0.01,0.99,0.23);
	pad3->Draw();
	pad3->cd();
	pad3->SetTopMargin(0.0);
	pad3->SetBottomMargin(0.3);
	pad3->SetRightMargin(0.1);
	pad3->SetFillStyle(0);

	leadingRatio2Systematics->GetXaxis()->SetLabelFont (42);
	leadingRatio2Systematics->GetXaxis()->SetTitleFont (42);
	leadingRatio2Systematics->GetXaxis()->SetTitleSize(0.11);
	leadingRatio2Systematics->GetXaxis()->SetLabelSize(0.11);
	leadingRatio2Systematics->GetXaxis()->SetTitleOffset (1.1);
	leadingRatio2Systematics->GetYaxis()->SetTitleSize(0.1);
	leadingRatio2Systematics->GetYaxis()->SetLabelSize(0.10);
	leadingRatio2Systematics->GetYaxis()->SetTitleOffset(0.63);
	leadingRatio2Systematics->GetYaxis()->SetTitle("Theory/Data   ");   
	leadingRatio2Systematics->GetYaxis()->SetNdivisions(505);
	leadingRatio2Systematics->GetYaxis()->SetRangeUser(0.1,1.9);

	leadingRatioMadGraph->SetTitle("");	  

	if (use_case ==1) {
	  leadingRatio2Systematics->GetXaxis()->SetTitle ("Exclusive jet multiplicity");
	  if (incMultiplicity) {
	    leadingRatio2Systematics->GetXaxis()->SetLabelSize(0.15);
	    leadingRatio2Systematics->GetXaxis()->SetBinLabel(1,"#geq 1");
	    leadingRatio2Systematics->GetXaxis()->SetBinLabel(2,"#geq 2");
	    leadingRatio2Systematics->GetXaxis()->SetBinLabel(3,"#geq 3");
	    leadingRatio2Systematics->GetXaxis()->SetBinLabel(4,"#geq 4");
	    leadingRatio2Systematics->GetXaxis()->SetBinLabel(5,"#geq 5");
	    leadingRatio2Systematics->GetXaxis()->SetBinLabel(6,"#geq 6");
	    leadingRatio2Systematics->GetXaxis()->SetTitle ("Inclusive jet multiplicity");
	  }
	  leadingRatio2Systematics->GetXaxis()->SetNdivisions(110);
	  leadingRatio3Systematics->GetXaxis()->SetNdivisions(110);
	  leadingRatioSystematics->GetXaxis()->SetNdivisions(110);
	}
	if (use_case ==2) {
	  if (whichjet == 1) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Leading jet p_{T} [GeV]");
	  if (whichjet == 2) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Second jet p_{T} [GeV]");
	  if (whichjet == 3) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Third jet p_{T} [GeV]");
	  if (whichjet == 4) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Fourth jet p_{T} [GeV]");
	}
	if (use_case ==3) {
	  if (whichjet == 1) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Leading jet #eta");
	  if (whichjet == 2) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Second jet #eta");
	  if (whichjet == 3) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Third jet #eta");
	  if (whichjet == 4) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Fourth jet #eta");
	}
	if (use_case ==4) {
	  if (whichjet == 1) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} #geq 1 [GeV]");
	  if (whichjet == 2) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} #geq 2 [GeV]");
	  if (whichjet == 3) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} #geq 3 [GeV]");
	  if (whichjet == 4) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} #geq 4 [GeV]");
	}

	leadingRatio2Systematics->SetMarkerStyle(1);
	leadingRatio2->SetMarkerStyle(1);
	leadingRatio2Systematics->Draw ("E2");
	leadingRatio2->Draw ("E1SAME");

	//	leadingRatioMadGraphPDF->SetFillColor(kOrange+2);
	//	leadingRatioMadGraphPDF->SetFillStyle(3005);
	//	leadingRatioMadGraphPDF->SetLineColor(kOrange+2);
	//	leadingRatioMadGraphPDF->SetLineWidth(0.6);
	//	leadingRatioMadGraphPDF->Draw("5");
      
	leadingRatioMadGraph->SetFillColor(kOrange-2);
	leadingRatioMadGraph->SetFillStyle(1001);
	leadingRatioMadGraph->SetLineColor(kOrange+10);
	leadingRatioMadGraph->SetMarkerColor(kOrange+10);
	leadingRatioMadGraph->SetMarkerStyle(25);
	leadingRatioMadGraph->SetLineWidth(1);
	leadingRatioMadGraph->Draw("2");
	leadingRatioMadGraph->Draw("pz");
	  
	leadingRatio2Systematics->Draw ("E2SAME");
	leadingRatio2->Draw ("E1SAME");
	  
	//	TLine *OLine2 = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	//	OLine2->SetLineColor(kBlack);
	//	OLine2->SetLineStyle(1);
	//	OLine2->SetLineWidth(1);
	//	OLine2->Draw();
	  
	TLatex *latexLabel = new TLatex();
	latexLabel->SetTextSize(0.1);
	latexLabel->SetTextFont(42);
	latexLabel->SetLineWidth(2);
	latexLabel->SetNDC();
	latexLabel->DrawLatex(0.2,0.37,"MadGraph (LO+PS)");	  
	  
	string title1;
	title1 = s + "DifferentialX" + stringmatch + ".pdf";
	if (incMultiplicity) title1 = s + "DifferentialXInc" + stringmatch + ".pdf";
	  
	cout << title1 << endl;
	  
	plots->Print (title1.c_str ());
	return;
      }
    }
}

