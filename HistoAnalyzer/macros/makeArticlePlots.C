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
makeArticlePlots (int whichobservable, int whichjet, int whichlepton)
{

  setTDRStyle ();
  gStyle->SetErrorX(0);
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);

  bool absoluteNormalization=true;
  int lepton=whichlepton; //1 -> electron,  2-> muon , 3 -> combined reults!
  bool addLumiUncertainties=true; double lumiError=0.025;

  int use_case = whichobservable;
  int whichjet = whichjet;
  string version = "_v2_32";
  string s                = "/afs/infn.it/ts/user/schizzi/html/test_newGenerators/theory_bands/ele/";
  if (lepton==2) string s = "/afs/infn.it/ts/user/schizzi/html/test_newGenerators/theory_bands/muo/";
  if (lepton==3) string s = "/afs/infn.it/ts/user/schizzi/html/test_newGenerators/theory_bands/combined/";

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
  string rivetPathSherpaQUP        ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qup.root";
  string rivetPathSherpaQDOWN      ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qdown.root";
  string rivetPathSherpaQcutUP     ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qcutup.root";
  string rivetPathSherpaQcutDOWN   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qcutdown.root";
  string rivetPathSherpaMSTW       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_mstw.root";
  string rivetPathSherpaNNPDF      ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_nnpdf.root";
  string rivetPathMadGraph         ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
  string rivetPathPowheg           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/out.root";
  //  string rivetPathMadGraphDOWN ="/gpfs/cms/users/candelis/Rivet/madgraph/scaledown/DYtotal.root";
  //  string rivetPathMadGraphUP   ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleup/DYtotal.root";
  //  string rivetPathMadGraphPDF1 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfmstw/DYtotal.root"; 
  //  string rivetPathMadGraphPDF2 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfnn/DYtotal.root";

  if (lepton == 2){
    //    rivetPathSherpa       ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod_mu/out.root";
    //    rivetPathSherpaUP     ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaleup_mu/out.root";
    //    rivetPathSherpaDOWN   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaledown_mu/out.root";
    //    rivetPathSherpaPDF1   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfmstw_mu/out.root";
    //    rivetPathSherpaPDF2   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfnn_mu/out.root";
    rivetPathSherpa           ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01_7TeV_sherpa/out.root";
    rivetPathSherpaUP         ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01FRup_7TeV_sherpa/out.root";
    rivetPathSherpaDOWN       ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01FRdown_7TeV_sherpa/out.root";
    rivetPathSherpaPDF1       ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qup_7TeV_sherpa/out.root";
    rivetPathSherpaPDF2       ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qdown_7TeV_sherpa/out.root";
    rivetPathSherpaQcutUP     ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qcutup_7TeV_sherpa/out.root";
    rivetPathSherpaQcutDOWN   ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qcutdown_7TeV_sherpa/out.root";
    rivetPathMadGraph         ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
    rivetPathPowheg           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/out.root";
    //    rivetPathMadGraphDOWN ="/gpfs/cms/users/candelis/Rivet/madgraph/scaledown/DYtotal.root";
    //    rivetPathMadGraphUP   ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleup/DYtotal.root";
    //    rivetPathMadGraphPDF1 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfmstw/DYtotal.root";
    //    rivetPathMadGraphPDF2 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfnn/DYtotal.root";
  }

  if (lepton == 3){
    //    rivetPathSherpa       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_central.root";
    //    rivetPathSherpaUP     ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_scaleUP.root";
    //    rivetPathSherpaDOWN   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_scaleDOWN.root";
    //    rivetPathSherpaPDF1   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_PDF1.root";
    //    rivetPathSherpaPDF2   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_PDF2.root";
    rivetPathSherpa           ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_central.root";
    rivetPathSherpaUP         ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_FRup.root";
    rivetPathSherpaDOWN       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_FRdown.root";
    rivetPathSherpaPDF1       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qup.root";
    rivetPathSherpaPDF2       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qdown.root";
    rivetPathSherpaQcutUP     ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qcutup.root";
    rivetPathSherpaQcutDOWN   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qcutdown.root";
    rivetPathMadGraph         ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_central.root";
    rivetPathPowheg           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/out.root";
    //    rivetPathMadGraphDOWN ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_scaleDOWN.root";
    //    rivetPathMadGraphUP   ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_scaleUP.root";
    //    rivetPathMadGraphPDF1 ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_PDF1.root";
    //    rivetPathMadGraphPDF2 ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_PDF2.root";
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

      if (use_case == 1) 
	{ // Jet Multiplicity
	  stringmatch = "JetMultiplicityUnfolded";
	  systPathFile = plotpath + "jetMultFinalSyst" + version + ".txt";
	  if (lepton == 1  || lepton == 3) oss<<"03"; else oss<<"08";
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
	TH1D *leadingSystematics;
	leadingSystematics = (TH1D *) leading->Clone ("leading");

	leadingSystematics->SetMarkerSize(0.9);
	leading->SetMarkerSize(0.9);

	// read from file ---------------------------------------------
	double dat;
	ifstream inM;
	//	cout << "reading ...  " << systPathFile << endl;
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
		//		cout << "Getting rivet data->" << nameRivetSherpa << endl;
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
		//		cout << "Getting rivet data->" << nameRivetSherpaUP << endl;
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
		//		cout << "Getting rivet data->" << nameRivetSherpaDOWN << endl;
		TGraphAsymmErrors *leadingRivetSherpaDOWN;
		gDirectory->GetObject (nameRivetSherpaDOWN.c_str (), leadingRivetSherpaDOWN);
	      }
	  }

	TFile *histoRivetSherpaPDF1 = TFile::Open (rivetPathSherpaPDF1.c_str ());
	histoRivetSherpaPDF1->cd ("");
	TDirectory *dirRivetSherpaPDF1 = gDirectory;
	TList *mylistRivetSherpaPDF1 = (TList *) dirRivetSherpaPDF1->GetListOfKeys ();
	TIter iterRivetSherpaPDF1 (mylistRivetSherpaPDF1);
	TObject *tobjRivetSherpaPDF1 = 0;
	while ((tobjRivetSherpaPDF1 = iterRivetSherpaPDF1.Next ()))
	  {
	    string nameRivetSherpaPDF1 = tobjRivetSherpaPDF1->GetName ();
	    if (nameRivetSherpaPDF1 == rivet_data)
	      {
		//		cout << "Getting rivet data->" << nameRivetSherpaPDF1 << endl;
		TGraphAsymmErrors *leadingRivetSherpaPDF1;
		gDirectory->GetObject (nameRivetSherpaPDF1.c_str (), leadingRivetSherpaPDF1);
	      }
	  }

	TFile *histoRivetSherpaPDF2 = TFile::Open (rivetPathSherpaPDF2.c_str ());
	histoRivetSherpaPDF2->cd ("");
	TDirectory *dirRivetSherpaPDF2 = gDirectory;
	TList *mylistRivetSherpaPDF2 = (TList *) dirRivetSherpaPDF2->GetListOfKeys ();
	TIter iterRivetSherpaPDF2 (mylistRivetSherpaPDF2);
	TObject *tobjRivetSherpaPDF2 = 0;
	while ((tobjRivetSherpaPDF2 = iterRivetSherpaPDF2.Next ()))
	  {
	    string nameRivetSherpaPDF2 = tobjRivetSherpaPDF2->GetName ();
	    if (nameRivetSherpaPDF2 == rivet_data)
	      {
		//		cout << "Getting rivet data->" << nameRivetSherpaPDF2 << endl;
		TGraphAsymmErrors *leadingRivetSherpaPDF2;
		gDirectory->GetObject (nameRivetSherpaPDF2.c_str (), leadingRivetSherpaPDF2);
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
		//		cout << "Getting rivet data->" << nameRivetSherpaQcutUP << endl;
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
		//		cout << "Getting rivet data->" << nameRivetSherpaQcutDOWN << endl;
		TGraphAsymmErrors *leadingRivetSherpaQcutDOWN;
		gDirectory->GetObject (nameRivetSherpaQcutDOWN.c_str (), leadingRivetSherpaQcutDOWN);
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
		//		cout << "Getting rivet data->" << nameRivetPowheg << endl;
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
		//		cout << "Getting rivet data->" << nameRivetMadGraph << endl;
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

	//	TFile *histoRivetMadGraphDOWN = TFile::Open (rivetPathMadGraphDOWN.c_str ());
	//	histoRivetMadGraphDOWN->cd ("");
	//	TDirectory *dirRivetMadGraphDOWN = gDirectory;
	//	TList *mylistRivetMadGraphDOWN = (TList *) dirRivetMadGraphDOWN->GetListOfKeys ();
	//	TIter iterRivetMadGraphDOWN (mylistRivetMadGraphDOWN);
	//	TObject *tobjRivetMadGraphDOWN = 0;
	//	while ((tobjRivetMadGraphDOWN = iterRivetMadGraphDOWN.Next ()))
	//	  {
	//	    string nameRivetMadGraphDOWN = tobjRivetMadGraphDOWN->GetName ();
	//	    if (nameRivetMadGraphDOWN == rivet_dataMG)
	//	      {
	//		//		cout << "Getting rivet data->" << nameRivetMadGraphDOWN << endl;
	//		TH1D *leadingRivetMadGraphDOWN_TH1;
	//		gDirectory->GetObject (nameRivetMadGraphDOWN.c_str (), leadingRivetMadGraphDOWN_TH1);
	//		TGraphAsymmErrors *leadingRivetMadGraphDOWN;
	//		leadingRivetMadGraphDOWN = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
	//		for (int n=0;n<nthbins;n++) {
	//		  leadingRivetMadGraphDOWN->SetPoint(n,leadingRivetMadGraphDOWN_TH1->GetBinCenter(n+1),leadingRivetMadGraphDOWN_TH1->GetBinContent(n+1));
	//		  leadingRivetMadGraphDOWN->SetPointEYhigh(n,leadingRivetMadGraphDOWN_TH1->GetBinError(n+1));
	//		  leadingRivetMadGraphDOWN->SetPointEYlow(n,leadingRivetMadGraphDOWN_TH1->GetBinError(n+1));
	//		}
	//	      }
	//	  }
	//
	//	TFile *histoRivetMadGraphUP = TFile::Open (rivetPathMadGraphUP.c_str ());
	//	histoRivetMadGraphUP->cd ("");
	//	TDirectory *dirRivetMadGraphUP = gDirectory;
	//	TList *mylistRivetMadGraphUP = (TList *) dirRivetMadGraphUP->GetListOfKeys ();
	//	TIter iterRivetMadGraphUP (mylistRivetMadGraphUP);
	//	TObject *tobjRivetMadGraphUP = 0;
	//	while ((tobjRivetMadGraphUP = iterRivetMadGraphUP.Next ()))
	//	  {
	//	    string nameRivetMadGraphUP = tobjRivetMadGraphUP->GetName ();
	//	    if (nameRivetMadGraphUP == rivet_dataMG)
	//	      {
	//		//		cout << "Getting rivet data->" << nameRivetMadGraphUP << endl;
	//		TH1D *leadingRivetMadGraphUP_TH1;
	//		gDirectory->GetObject (nameRivetMadGraphUP.c_str (), leadingRivetMadGraphUP_TH1);
	//		TGraphAsymmErrors *leadingRivetMadGraphUP;
	//		leadingRivetMadGraphUP = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
	//		for (int n=0;n<nthbins;n++) {
	//		  leadingRivetMadGraphUP->SetPoint(n,leadingRivetMadGraphUP_TH1->GetBinCenter(n+1),leadingRivetMadGraphUP_TH1->GetBinContent(n+1));
	//		  leadingRivetMadGraphUP->SetPointEYhigh(n,leadingRivetMadGraphUP_TH1->GetBinError(n+1));
	//		  leadingRivetMadGraphUP->SetPointEYlow(n,leadingRivetMadGraphUP_TH1->GetBinError(n+1));
	//		}
	//	      }
	//	  }
	//
	//	TFile *histoRivetMadGraphPDF1 = TFile::Open (rivetPathMadGraphPDF1.c_str ());
	//	histoRivetMadGraphPDF1->cd ("");
	//	TDirectory *dirRivetMadGraphPDF1 = gDirectory;
	//	TList *mylistRivetMadGraphPDF1 = (TList *) dirRivetMadGraphPDF1->GetListOfKeys ();
	//	TIter iterRivetMadGraphPDF1 (mylistRivetMadGraphPDF1);
	//	TObject *tobjRivetMadGraphPDF1 = 0;
	//	while ((tobjRivetMadGraphPDF1 = iterRivetMadGraphPDF1.Next ()))
	//	  {
	//	    string nameRivetMadGraphPDF1 = tobjRivetMadGraphPDF1->GetName ();
	//	    if (nameRivetMadGraphPDF1 == rivet_dataMG)
	//	      {
	//		//		cout << "Getting MG PDF1 rivet data->" << nameRivetMadGraphPDF1 << endl;
	//		TH1D *leadingRivetMadGraphPDF1_TH1;
	//		gDirectory->GetObject (nameRivetMadGraphPDF1.c_str (), leadingRivetMadGraphPDF1_TH1);
	//		TGraphAsymmErrors *leadingRivetMadGraphPDF1;
	//		leadingRivetMadGraphPDF1 = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
	//		for (int n=0;n<nthbins;n++) {
	//		  leadingRivetMadGraphPDF1->SetPoint(n,leadingRivetMadGraphPDF1_TH1->GetBinCenter(n+1),leadingRivetMadGraphPDF1_TH1->GetBinContent(n+1));
	//		  leadingRivetMadGraphPDF1->SetPointEYhigh(n,leadingRivetMadGraphPDF1_TH1->GetBinError(n+1));
	//		  leadingRivetMadGraphPDF1->SetPointEYlow(n,leadingRivetMadGraphPDF1_TH1->GetBinError(n+1));
	//		}
	//	      }
	//	  }
	//
	//	TFile *histoRivetMadGraphPDF2 = TFile::Open (rivetPathMadGraphPDF2.c_str ());
	//	histoRivetMadGraphPDF2->cd ("");
	//	TDirectory *dirRivetMadGraphPDF2 = gDirectory;
	//	TList *mylistRivetMadGraphPDF2 = (TList *) dirRivetMadGraphPDF2->GetListOfKeys ();
	//	TIter iterRivetMadGraphPDF2 (mylistRivetMadGraphPDF2);
	//	TObject *tobjRivetMadGraphPDF2 = 0;
	//	while ((tobjRivetMadGraphPDF2 = iterRivetMadGraphPDF2.Next ()))
	//	  {
	//	    string nameRivetMadGraphPDF2 = tobjRivetMadGraphPDF2->GetName ();
	//	    if (nameRivetMadGraphPDF2 == rivet_dataMG)
	//	      {
	//		//		cout << "Getting MG PDF2 rivet data->" << nameRivetMadGraphPDF2 << endl;
	//		TH1D *leadingRivetMadGraphPDF2_TH1;
	//		gDirectory->GetObject (nameRivetMadGraphPDF2.c_str (), leadingRivetMadGraphPDF2_TH1);
	//		TGraphAsymmErrors *leadingRivetMadGraphPDF2;
	//		leadingRivetMadGraphPDF2 = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
	//		for (int n=0;n<nthbins;n++) {
	//		  leadingRivetMadGraphPDF2->SetPoint(n,leadingRivetMadGraphPDF2_TH1->GetBinCenter(n+1),leadingRivetMadGraphPDF2_TH1->GetBinContent(n+1));
	//		  leadingRivetMadGraphPDF2->SetPointEYhigh(n,leadingRivetMadGraphPDF2_TH1->GetBinError(n+1));
	//		  leadingRivetMadGraphPDF2->SetPointEYlow(n,leadingRivetMadGraphPDF2_TH1->GetBinError(n+1));
	//		}
	//	      }
	//	  }

	//-------------------------------------------------------------
	  
	leadingSystematics->SetName ("leadingSystematics");
	if (systTmpM.size () != leadingSystematics->GetNbinsX ())
	  cout << "WRONG NUMBER OF BINS (# syst from file->" <<systTmpM.size()<<" - # bins leadingsystematics->"<<leadingSystematics->GetNbinsX()<<")"<<endl;
	for (int i = 0; i <= leadingSystematics->GetNbinsX (); i++)
	  {
	    cout<<"Systematics for bin "<<i+1<<" is "<<systTmpM[i]<<endl;
	    double err = sqrt (pow (leading->GetBinError (i + 1), 2) + pow (systTmpM[i] * leadingSystematics->GetBinContent (i + 1), 2));
	    leadingSystematics->SetBinError (i + 1, err);
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
	leadingSystematics->SetLineColor (kRed);
	leadingSystematics->SetMarkerStyle (20);
	leadingSystematics->SetFillColor (kRed);
	leadingSystematics->SetMarkerColor (kRed);

	leadingSystematics->GetXaxis ()->SetTitleOffset (1.1);
	leadingSystematics->GetXaxis ()->SetTitleSize (0.05);
	leadingSystematics->GetXaxis ()->SetLabelSize (0.0);
	leadingSystematics->GetXaxis ()->SetLabelFont (42);
	leadingSystematics->GetXaxis ()->SetTitleFont (42);

	leadingSystematics->GetYaxis ()->SetTitleOffset (1.);
	leadingSystematics->GetYaxis ()->SetTitleSize (0.07);
	leadingSystematics->GetYaxis ()->SetLabelSize (0.06);
	leadingSystematics->GetYaxis ()->SetLabelFont (42);
	leadingSystematics->GetYaxis ()->SetTitleFont (42);

	leadingSystematics->SetTitle ();
	leadingSystematics->GetXaxis ()->SetTitle ();

	if (use_case ==1) {
	  if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dN [pb]");
	  else {
	    if (lepton == 1) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/dN");
	    if (lepton == 2) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/dN");
	    if (lepton == 3) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow l^{+}l^{-}}) d#sigma/dN");
	  }
	}

	if (use_case ==2) {
	  if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dp_{T} [pb/GeV]");
	  else {
	    if (lepton == 1) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/dp_{T}");
	    if (lepton == 2) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/dp_{T}");
	    if (lepton == 3) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow l^{+}l^{-}}) d#sigma/dp_{T}");
	  }
	}

	if (use_case ==3) {
	  if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/d#eta [pb]");
	  else {
	    if (lepton == 1) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/d#eta");
	    if (lepton == 2) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/d#eta");
	    if (lepton == 3) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow l^{+}l^{-}}) d#sigma/d#eta");
	  }
	}
	  
	if (use_case ==4) {
	  if (absoluteNormalization) leadingSystematics->GetYaxis ()->SetTitle ("d#sigma/dH_{T} [pb/GeV]");
	  else {
	    if (lepton == 1) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/dH_{T}");
	    if (lepton == 2) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/dH_{T}");
	    if (lepton == 3) leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow l^{+}l^{-}}) d#sigma/dH_{T}");
	  }
	}
	  
	leadingSystematics->Draw ("E1");
	leading->SetFillColor (kBlack);
	leading->SetFillStyle (3001);
	leading->SetMarkerColor (kBlack);
	leading->SetLineColor (kBlack);
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
	nRivetPoints = leadingRivetSherpa->GetN();
	if (nRivetPoints != leadingSystematics->GetNbinsX ()) {cout << "Different number of bins wrt RIVET... quitting" << endl; return 0;}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    //	    if (lepton ==1) dummyNorm= 0.200477 * (1000000.0/971.754)*(971.754*3/3048);   
	    //	    if (lepton ==2) dummyNorm= 0.200097 *(1000000.0/967.713)*(967.713*3/3048); 
	    //	    if (lepton ==3) dummyNorm= 0.200477 * (1000000.0/971.754)*(971.754*3/3048) + 0.200097 *(1000000.0/967.713)*(967.713*3/3048); 
	    dummyNorm= (385519./2088.12);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); //Divide by the bin width 
	  }
	  // get The data bin value bin value
	  //	  cout<<"Data content (pb) in bin "<<ovo+1<<" is ->"<<leading->GetBinContent(ovo+1)<<endl;
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
	    //	    if (lepton ==1) dummyNorm=  0.113294 * (1000000.0/838.990)*(838.990*3/3048); 
	    //	    if (lepton ==2) dummyNorm=  0.112873 * (1000000.0/837.477)*(837.477*3/3048);
	    //	    if (lepton ==3) dummyNorm=  0.113294 * (1000000.0/838.990)*(838.990*3/3048) + 0.112873 * (1000000.0/837.477)*(837.477*3/3048); 
	    dummyNorm= (298354./2223.89);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); //Divide by the bin width 
	  }
	  leadingRivetSherpaDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaDOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaDOWN->SetPointEYhigh(ovo,leadingRivetSherpaDOWN->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaDOWN->SetPointEYlow(ovo,leadingRivetSherpaDOWN->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    //	    if (lepton==1) dummyNorm=  0.113644 * (1000000.0/898.33)*(898.33*3/3048);   
	    //	    if (lepton==2) dummyNorm=  0.114067 * (1000000.0/899.787)*(899.787*3/3048);
	    //	    if (lepton ==3) dummyNorm=  0.113644 * (1000000.0/898.33)*(898.33*3/3048) + 0.114067 * (1000000.0/899.787)*(899.787*3/3048);
	    dummyNorm= (343130./2141.66);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }
	  leadingRivetSherpaPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaPDF1->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaPDF1->SetPointEYhigh(ovo,leadingRivetSherpaPDF1->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaPDF1->SetPointEYlow(ovo,leadingRivetSherpaPDF1->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    //	    if (lepton ==1 ) dummyNorm=  0.150566 * (995000.0/896.767)*(896.767*3/3048);    
	    //	    if (lepton ==2 ) dummyNorm=  0.150439 * (1000000.0/895.779)*(895.779*3/3048);  
	    //	    if (lepton ==3) dummyNorm=  0.150566 * (995000.0/896.767)*(896.767*3/3048) + 0.150439 * (1000000.0/895.779)*(895.779*3/3048); 
	    dummyNorm= (346296./2184.26);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpaPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaPDF2->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaPDF2->SetPointEYhigh(ovo,leadingRivetSherpaPDF2->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaPDF2->SetPointEYlow(ovo,leadingRivetSherpaPDF2->GetErrorYlow(ovo)/dummyNorm);
	}

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpaQcutUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    //	    if (lepton==1) dummyNorm=  0.113644 * (1000000.0/898.33)*(898.33*3/3048);   
	    //	    if (lepton==2) dummyNorm=  0.114067 * (1000000.0/899.787)*(899.787*3/3048);
	    //	    if (lepton ==3) dummyNorm=  0.113644 * (1000000.0/898.33)*(898.33*3/3048) + 0.114067 * (1000000.0/899.787)*(899.787*3/3048);
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
	    //	    if (lepton ==1 ) dummyNorm=  0.150566 * (995000.0/896.767)*(896.767*3/3048);    
	    //	    if (lepton ==2 ) dummyNorm=  0.150439 * (1000000.0/895.779)*(895.779*3/3048);  
	    //	    if (lepton ==3) dummyNorm=  0.150566 * (995000.0/896.767)*(896.767*3/3048) + 0.150439 * (1000000.0/895.779)*(895.779*3/3048); 
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
	  leadingRivetSherpaStat->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    //	    if (lepton ==1 ) dummyNorm=  0.150566 * (995000.0/896.767)*(896.767*3/3048);    
	    //	    if (lepton ==2 ) dummyNorm=  0.150439 * (1000000.0/895.779)*(895.779*3/3048);  
	    //	    if (lepton ==3) dummyNorm=  0.150566 * (995000.0/896.767)*(896.767*3/3048) + 0.150439 * (1000000.0/895.779)*(895.779*3/3048); 
	    dummyNorm= (343072./2145.);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpaStat->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaStat->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetSherpaStat->SetPointEYhigh(ovo,leadingRivetSherpaStat->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpaStat->SetPointEYlow(ovo,leadingRivetSherpaStat->GetErrorYlow(ovo)/dummyNorm);
	  leadingRatioSherpaStat->SetPoint(ovo,dummyXvar,1.0);
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

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpa->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetSherpaDOWN->GetPoint(ovo,x1temp,y1temp); 
	  leadingRivetSherpaUP->GetPoint(ovo,x2temp,y2temp); 


	  if (absoluteNormalization) {
	    //	    if (lepton ==1) dummyNorm= 0.155390 *(1000000.0/906.826)*(906.826*3/3048);   
	    //	    if (lepton ==2) dummyNorm= 0.155456 *(1000000.0/907.485)*(907.485*3/3048);
	    //	    if (lepton ==3) dummyNorm= 0.155390 *(1000000.0/906.826)*(906.826*3/3048) + 0.155456 *(1000000.0/907.485)*(907.485*3/3048); 
	    dummyNorm= (343072./2145.);
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpa->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	  //	  leadingRivetSherpa->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm);
	  //	  leadingRivetSherpa->SetPointEYlow(ovo,-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm);
	  leadingRivetSherpa->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm + leadingRivetSherpaStat->GetErrorYhigh(ovo));
	  leadingRivetSherpa->SetPointEYlow(ovo,-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm + leadingRivetSherpaStat->GetErrorYlow(ovo));
	  leadingRatioSherpa->SetPoint(ovo,dummyXvar,1.0);
	  //	  leadingRatioSherpa->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	  //	  leadingRatioSherpa->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	  leadingRatioSherpa->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm + leadingRivetSherpaStat->GetErrorYhigh(ovo))/(dummyYvar/dummyNorm));
	  leadingRatioSherpa->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm + leadingRivetSherpaStat->GetErrorYlow(ovo))/(dummyYvar/dummyNorm));
	    
	  leadingRatio->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	  leadingRatioSystematics->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatioSystematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));
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
	  leadingRivetSherpaPDF1->GetPoint(ovo,x1temp,y1temp); 
	  leadingRivetSherpaPDF2->GetPoint(ovo,x2temp,y2temp); 

	  leadingRivetSherpaPDF->SetPoint(ovo,dummyXvar,dummyYvar);
	  leadingRivetSherpaPDF->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar)-dummyYvar + leadingRivetSherpa->GetErrorYhigh(ovo));
	  leadingRivetSherpaPDF->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar) + leadingRivetSherpa->GetErrorYlow(ovo));

	  leadingRatioSherpaPDF->SetPoint(ovo,dummyXvar,1.0);
	  leadingRatioSherpaPDF->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar)-dummyYvar)/dummyYvar + leadingRatioSherpa->GetErrorYhigh(ovo));
	  leadingRatioSherpaPDF->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar)/dummyYvar + leadingRatioSherpa->GetErrorYlow(ovo));

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
	  leadingRivetSherpaQcut->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar)-dummyYvar + leadingRivetSherpaPDF->GetErrorYhigh(ovo));
	  leadingRivetSherpaQcut->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar) + leadingRivetSherpaPDF->GetErrorYlow(ovo));

	  leadingRatioSherpaQcut->SetPoint(ovo,dummyXvar,1.0);
	  leadingRatioSherpaQcut->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar)-dummyYvar)/dummyYvar + leadingRatioSherpaPDF->GetErrorYhigh(ovo));
	  leadingRatioSherpaQcut->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar)/dummyYvar + leadingRatioSherpaPDF->GetErrorYlow(ovo));

	}

	// Powheg:

	Double_t dummyNorm = 0.;
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowhegStat->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    //	    if (lepton ==1 ) dummyNorm=  0.150566 * (995000.0/896.767)*(896.767*3/3048);    
	    //	    if (lepton ==2 ) dummyNorm=  0.150439 * (1000000.0/895.779)*(895.779*3/3048);  
	    //	    if (lepton ==3) dummyNorm=  0.150566 * (995000.0/896.767)*(896.767*3/3048) + 0.150439 * (1000000.0/895.779)*(895.779*3/3048); 
	    dummyNorm= (3827167486.5/972.9)/2.;
	    if (lepton ==3) dummyNorm= dummyNorm*2.0;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetPowhegStat->GetPoint(ovo,dummyXvar,dummyYvar); 
	  leadingRivetPowhegStat->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	  leadingRivetPowhegStat->SetPointEYhigh(ovo,leadingRivetPowhegStat->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetPowhegStat->SetPointEYlow(ovo,leadingRivetPowhegStat->GetErrorYlow(ovo)/dummyNorm);
	  leadingRatioPowhegStat->SetPoint(ovo,dummyXvar,1.0);
	  leadingRatioPowhegStat->SetPointEYhigh(ovo,(leadingRivetPowhegStat->GetErrorYhigh(ovo))/(dummyYvar/dummyNorm));
	  leadingRatioPowhegStat->SetPointEYlow(ovo,(leadingRivetPowhegStat->GetErrorYlow(ovo))/(dummyYvar/dummyNorm));

	  leadingRatio3->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio3->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	  leadingRatio3Systematics->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio3Systematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));
	}


	// Madgraph:

	//	Double_t dummyNorm = 0.;
	//	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	//	  leadingRivetMadGraphDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	//	  dummyNorm = dummyNorm + dummyYvar;
	//	}
	//	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	//	  if (absoluteNormalization) {
	//	    dummyNorm= 3.0 * 0.000000001 * 1737.42 / (2.0 * 3048.0);
	//	    if (lepton ==3) dummyNorm = dummyNorm*2;
	//	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	//	  }
	//	  leadingRivetMadGraphDOWN->GetPoint(ovo,dummyXvar,dummyYvar);
	//	  leadingRivetMadGraphDOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	//	  leadingRivetMadGraphDOWN->SetPointEYhigh(ovo,leadingRivetMadGraphDOWN->GetErrorYhigh(ovo)/dummyNorm);
	//	  leadingRivetMadGraphDOWN->SetPointEYlow(ovo,leadingRivetMadGraphDOWN->GetErrorYlow(ovo)/dummyNorm);
	//	}
	//	Double_t dummyNorm = 0.;
	//	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	//	  leadingRivetMadGraphUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	//	  dummyNorm = dummyNorm + dummyYvar;
	//	}
	//	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	//	  if (absoluteNormalization) {
	//	    dummyNorm= 3.0 * 0.000000001 * 1737.15 / (2.0 * 3048.0);
	//	    if (lepton ==3) dummyNorm = dummyNorm*2;
	//	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	//	  }
	//	  leadingRivetMadGraphUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	//	  leadingRivetMadGraphUP->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	//	  leadingRivetMadGraphUP->SetPointEXhigh(ovo,10.);
	//	  leadingRivetMadGraphUP->SetPointEXlow(ovo,10.);
	//	  leadingRivetMadGraphUP->SetPointEYhigh(ovo,leadingRivetMadGraphUP->GetErrorYhigh(ovo)/dummyNorm);
	//	  leadingRivetMadGraphUP->SetPointEYlow(ovo,leadingRivetMadGraphUP->GetErrorYlow(ovo)/dummyNorm);
	//	}

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

	  leadingRatioMadGraph->SetPoint(ovo,dummyXvar,1.0);
	  //	  leadingRatioMadGraph->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	  //	  leadingRatioMadGraph->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	  leadingRatioMadGraph->SetPointEYhigh(ovo,leadingRivetMadGraph->GetErrorYhigh(ovo)*dummyNorm/dummyYvar);
	  leadingRatioMadGraph->SetPointEYlow(ovo,leadingRivetMadGraph->GetErrorYlow(ovo)*dummyNorm/dummyYvar);

	  leadingRatio2->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio2->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	  leadingRatio2Systematics->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio2Systematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));
	}

	//	Double_t dummyNorm = 0.;
	//	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	//	  leadingRivetMadGraphPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	//	  dummyNorm = dummyNorm + dummyYvar;
	//	}
	//	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	//	  if (absoluteNormalization) {
	//	    dummyNorm= 3.0 * 0.000000001 * 1680.67 / (2.0 * 3048.0);
	//	    if (lepton ==3) dummyNorm = dummyNorm*2;
	//	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	//	  }
	//	  leadingRivetMadGraphPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	//	  leadingRivetMadGraphPDF1->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	//	  leadingRivetMadGraphPDF1->SetPointEYhigh(ovo,leadingRivetMadGraphPDF1->GetErrorYhigh(ovo)/dummyNorm);
	//	  leadingRivetMadGraphPDF1->SetPointEYlow(ovo,leadingRivetMadGraphPDF1->GetErrorYlow(ovo)/dummyNorm);
	//	}
	//
	//	Double_t dummyNorm = 0.;
	//	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	//	  leadingRivetMadGraphPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	//	  dummyNorm = dummyNorm + dummyYvar;
	//	}
	//	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	//	  if (absoluteNormalization) {
	//	    dummyNorm= 3.0 * 0.000000001 * 1680.67 / (2.0 * 3048.0);
	//	    if (lepton ==3) dummyNorm = dummyNorm*2;
	//	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	//	  }
	//	  leadingRivetMadGraphPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	//	  leadingRivetMadGraphPDF2->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	//	  leadingRivetMadGraphPDF2->SetPointEYhigh(ovo,leadingRivetMadGraphPDF2->GetErrorYhigh(ovo)/dummyNorm);
	//	  leadingRivetMadGraphPDF2->SetPointEYlow(ovo,leadingRivetMadGraphPDF2->GetErrorYlow(ovo)/dummyNorm);
	//	}
	//
	//	///////////////////////////
	//	//PDF Envelop for Madgraph
	//	///////////////////////////
	//	    
	//	TGraphAsymmErrors *leadingRivetMadGraphPDF;
	//	leadingRivetMadGraphPDF = (TGraphAsymmErrors *) leadingRivetMadGraph->Clone ();
	//	TGraphAsymmErrors *leadingRatioMadGraphPDF;
	//	leadingRatioMadGraphPDF = (TGraphAsymmErrors *) leadingRatioMadGraph->Clone ();
	//
	//	Double_t y1temp = 0.;
	//	Double_t y2temp = 0.;
	//	Double_t x1temp = 0.;
	//	Double_t x2temp = 0.;
	//
	//	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	//	  leadingRivetMadGraphPDF->GetPoint(ovo,dummyXvar,dummyYvar); 
	//	  leadingRivetMadGraphPDF1->GetPoint(ovo,x1temp,y1temp); 
	//	  leadingRivetMadGraphPDF2->GetPoint(ovo,x2temp,y2temp); 
	//
	//	  leadingRivetMadGraphPDF->SetPoint(ovo,dummyXvar,dummyYvar);
	//	  leadingRivetMadGraphPDF->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar)-dummyYvar + leadingRivetMadGraph->GetErrorYhigh(ovo));
	//	  leadingRivetMadGraphPDF->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar) + leadingRivetMadGraph->GetErrorYlow(ovo));
	//
	//	  leadingRatioMadGraphPDF->SetPoint(ovo,dummyXvar,1.0);
	//	  leadingRatioMadGraphPDF->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar)-dummyYvar)/dummyYvar + leadingRatioMadGraph->GetErrorYhigh(ovo));
	//	  leadingRatioMadGraphPDF->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar)/dummyYvar + leadingRatioMadGraph->GetErrorYlow(ovo));
	//
	//	}

	leadingRivetSherpaQcut->SetFillColor(kAzure+6);
	leadingRivetSherpaQcut->SetFillStyle(3004);
	leadingRivetSherpaQcut->SetLineColor(kAzure+6);
	leadingRivetSherpaQcut->SetMarkerColor(kAzure+6);
	leadingRivetSherpaQcut->SetLineWidth(0.6);
	leadingRivetSherpaQcut->Draw("5");

	leadingRivetSherpaPDF->SetFillColor(kBlue-7);
	leadingRivetSherpaPDF->SetFillStyle(3004);
	leadingRivetSherpaPDF->SetLineColor(kBlue-7);
	leadingRivetSherpaPDF->SetMarkerColor(kBlue-7);
	leadingRivetSherpaPDF->SetLineWidth(0.6);
	leadingRivetSherpaPDF->Draw("5");

	leadingRivetSherpa->SetFillColor(kBlue-4);
	leadingRivetSherpa->SetFillStyle(3004);
	leadingRivetSherpa->SetLineColor(kBlue-4);
	leadingRivetSherpa->SetMarkerColor(kBlue-4);
	leadingRivetSherpa->SetLineWidth(0.6);
	leadingRivetSherpa->Draw("5");

	leadingRivetSherpaStat->SetFillColor(kBlue);
	leadingRivetSherpaStat->SetFillStyle(3002);
	leadingRivetSherpaStat->SetLineColor(kBlue);
	leadingRivetSherpaStat->SetMarkerColor(kBlue);
	leadingRivetSherpaStat->SetLineWidth(0.6);
	leadingRivetSherpaStat->Draw("5");

	leadingRivetPowhegStat->SetFillColor(kGreen+4);
	leadingRivetPowhegStat->SetFillStyle(3002);
	leadingRivetPowhegStat->SetLineColor(kGreen+4);
	leadingRivetPowhegStat->SetMarkerColor(kGreen+4);
	leadingRivetPowhegStat->SetLineWidth(0.6);
	leadingRivetPowhegStat->Draw("5");

	//	leadingRivetMadGraphPDF->SetFillColor(kOrange+2);
	//	leadingRivetMadGraphPDF->SetFillStyle(3005);
	//	leadingRivetMadGraphPDF->SetLineColor(kOrange+2);
	//	leadingRivetMadGraphPDF->SetLineWidth(0.6);
	//	leadingRivetMadGraphPDF->Draw("5");
      
	leadingRivetMadGraph->SetFillColor(kOrange+10);
	leadingRivetMadGraph->SetFillStyle(3002);
	leadingRivetMadGraph->SetLineColor(kOrange+10);
	leadingRivetMadGraph->SetLineWidth(0.6);
	leadingRivetMadGraph->Draw("5");

	leadingSystematics->Draw ("ESAME");
	leading->Draw ("ESAME");
	//-------------------------------------------

	// Draw the label and save plot: (in the proper position)

	TLatex *latexLabel;

	if (use_case ==3){
	  if (lepton ==1) latexLabel = CMSPrel (4.890, "Z#rightarrow ee channel", 0.425, 0.19);	// make fancy label
	  if (lepton ==2) latexLabel = CMSPrel (4.890, "Z#rightarrow #mu#mu channel", 0.425, 0.19);	// make fancy label
	  if (lepton ==3) latexLabel = CMSPrel (4.890, "Z#rightarrow ll channel", 0.425, 0.19);	// make fancy label
	}

	if (use_case ==2 || use_case ==1 || use_case == 4){
	  if (lepton ==1) latexLabel = CMSPrel (4.890, "Z#rightarrow ee channel", 0.20, 0.21);	// make fancy label
	  if (lepton ==2) latexLabel = CMSPrel (4.890, "Z#rightarrow #mu#mu channel", 0.20, 0.21);	// make fancy label
	  if (lepton ==3) latexLabel = CMSPrel (4.890, "Z#rightarrow ll channel", 0.20, 0.21);	// make fancy label
	}

	leadingSystematics->SetMarkerColor(kBlack);
	leadingSystematics->SetMarkerSize(0.8);
	leading->SetMarkerSize(0.8);

	latexLabel->Draw ("same");
	  
	TLegend *legendsx_d;
	TLegend *legenddx_d;

	if (use_case ==3){
	  legendsx_d = new TLegend (0.20, 0.79, 0.57, 0.88);
	  legenddx_d = new TLegend (0.6, 0.75, 0.92, 0.88);	   
	  legendsx_d->SetFillColor (0);
	  legendsx_d->SetFillStyle (0);
	  legendsx_d->SetBorderSize (0);
	  legendsx_d->SetNColumns(2);
	  legendsx_d->SetTextSize(.027);
	  legendsx_d->AddEntry (leading, "Data (stat)", "PLE");
	  legendsx_d->AddEntry (leadingSystematics, "Data (stat+syst)", "PEL");
	  //	  legendsx_d->AddEntry (leadingRivetSherpa, "Sherpa2 ref.", "L");
	  //	  legendsx_d->AddEntry (leadingRivetMadGraph, "MadGraph ref.", "L"); 
	  legenddx_d->SetFillColor (0);
	  legenddx_d->SetFillStyle (0);
	  legenddx_d->SetBorderSize (0);
	  legenddx_d->SetTextSize(.027);
	  legenddx_d->AddEntry (leadingRivetSherpa, "Sherpa2 F/R var.", "F");
	  legenddx_d->AddEntry (leadingRivetSherpaPDF, "Sherpa2 Q var.", "F");
	  legenddx_d->AddEntry (leadingRivetSherpaQcut, "Sherpa2 Qcut var.", "F");
	  legenddx_d->AddEntry (leadingRivetSherpaStat, "Sherpa2 (stat. only)", "F");
	  legenddx_d->AddEntry (leadingRivetPowhegStat, "Powheg(MiNLO) (stat.)", "F");
	  legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph (stat. only)", "F");
	  //	  legenddx_d->AddEntry (leadingRivetMadGraphPDF, "MadGraph PDF var.", "F");
	  legendsx_d->Draw ("same");
	  legenddx_d->Draw ("same");
	} else {
	  legenddx_d = new TLegend (0.6, 0.60, 0.92, 0.88);	   
	  legenddx_d->SetFillColor (0);
	  legenddx_d->SetFillStyle (0);
	  legenddx_d->SetBorderSize (0);
	  legenddx_d->SetNColumns(1);
	  legenddx_d->SetTextSize(.030);
	  legenddx_d->AddEntry (leading, "Data (stat)", "PLE");
	  legenddx_d->AddEntry (leadingSystematics, "Data (stat+syst)", "PEL");
	  //	  legenddx_d->AddEntry (leadingRivetSherpa, "Sherpa2 ref.", "L");
	  //	  legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph ref.", "L");
	  legenddx_d->AddEntry (leadingRivetSherpa, "Sherpa2 F/R var.", "F");
	  legenddx_d->AddEntry (leadingRivetSherpaPDF, "Sherpa2 Q var.", "F");
	  legenddx_d->AddEntry (leadingRivetSherpaQcut, "Sherpa2 Qcut var.", "F");
	  legenddx_d->AddEntry (leadingRivetSherpaStat, "Sherpa2 (stat. only)", "F");
	  legenddx_d->AddEntry (leadingRivetPowhegStat, "Powheg(MiNLO) (stat.)", "F");
	  legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph (stat. only)", "F");
	  //	  legenddx_d->AddEntry (leadingRivetMadGraphPDF, "MadGraph PDF var.", "F");
	  legenddx_d->Draw ("same");
	}


	// Sherpa ratio plot: ----------------------

	plots->cd ();
	TPad *pad2 = new TPad("pad2","pad2",0.01,0.40,0.99,0.55);
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
	leadingRatioSystematics->GetYaxis()->SetTitle("Data/MC");   
	leadingRatioSystematics->GetYaxis()->SetNdivisions(505);
	leadingRatioSystematics->GetYaxis()->SetRangeUser(-0.2,2.2);

	leadingRatioSystematics->SetTitle("");	  

	leadingRatioSystematics->Draw ("E1");
	leadingRatio->Draw ("E1SAME");

	leadingRatioSherpaQcut->SetFillColor(kAzure+6);
	leadingRatioSherpaQcut->SetFillStyle(3004);
	leadingRatioSherpaQcut->SetLineColor(kAzure+6);
	leadingRatioSherpaQcut->SetMarkerColor(kAzure+6);
	leadingRatioSherpaQcut->SetLineWidth(0.6);
	leadingRatioSherpaQcut->Draw("5");

	leadingRatioSherpaPDF->SetFillColor(kBlue-7);
	leadingRatioSherpaPDF->SetFillStyle(3004);
	leadingRatioSherpaPDF->SetLineColor(kBlue-7);
	leadingRatioSherpaPDF->SetMarkerColor(kBlue-7);
	leadingRatioSherpaPDF->SetLineWidth(0.6);
	leadingRatioSherpaPDF->Draw("5");

	leadingRatioSherpa->SetFillColor(kBlue-4);
	leadingRatioSherpa->SetFillStyle(3004);
	leadingRatioSherpa->SetLineColor(kBlue-4);
	leadingRatioSherpa->SetMarkerColor(kBlue-4);
	leadingRatioSherpa->SetLineWidth(0.6);
	leadingRatioSherpa->Draw("5");

	leadingRatioSherpaStat->SetFillColor(kBlue);
	leadingRatioSherpaStat->SetFillStyle(3002);
	leadingRatioSherpaStat->SetLineColor(kBlue);
	leadingRatioSherpaStat->SetMarkerColor(kBlue);
	leadingRatioSherpaStat->SetLineWidth(0.6);
	leadingRatioSherpaStat->Draw("5");

	leadingRatioSystematics->Draw ("E1SAME");
	leadingRatio->Draw ("E1SAME");

	TLine *OLine = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	OLine->SetLineColor(kBlack);
	OLine->SetLineStyle(2);
	OLine->Draw();

	TLatex *latexLabel = new TLatex();
	latexLabel->SetTextSize(0.1);
	latexLabel->SetTextFont(42);
	latexLabel->SetLineWidth(2);
	latexLabel->SetNDC();
	latexLabel->DrawLatex(0.2,0.09,"Sherpa2");	  

	// Powheg ratio plot: ----------------------------------
	plots->cd ();
	TPad *pad4 = new TPad("pad4","pad4",0.01,0.25,0.99,0.40);
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
	leadingRatio3Systematics->GetYaxis()->SetTitle("Data/MC");   
	leadingRatio3Systematics->GetYaxis()->SetNdivisions(505);
	leadingRatio3Systematics->GetYaxis()->SetRangeUser(-0.2,2.2);
	leadingRatio3Systematics->SetTitle("");	  
	leadingRatio3Systematics->Draw ("E1");
	leadingRatio3->Draw ("E1SAME");

	leadingRatioPowhegStat->SetFillColor(kGreen+3);
	leadingRatioPowhegStat->SetFillStyle(3002);
	leadingRatioPowhegStat->SetLineColor(kGreen+3);
	leadingRatioPowhegStat->SetMarkerColor(kGreen+3);
	leadingRatioPowhegStat->SetLineWidth(0.6);
	leadingRatioPowhegStat->Draw("5");

	leadingRatio3Systematics->Draw ("E1SAME");
	leadingRatio3->Draw ("E1SAME");

	TLine *OLine = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	OLine->SetLineColor(kBlack);
	OLine->SetLineStyle(2);
	OLine->Draw();

	TLatex *latexLabel = new TLatex();
	latexLabel->SetTextSize(0.1);
	latexLabel->SetTextFont(42);
	latexLabel->SetLineWidth(2);
	latexLabel->SetNDC();
	latexLabel->DrawLatex(0.2,0.09,"Powheg(MiNLO)");	  


	// Madgraph ratio plot: ---------------------
	plots->cd();
	TPad *pad3 = new TPad("pad3","pad3",0.01,0.01,0.99,0.25);
	pad3->Draw();
	pad3->cd();
	pad3->SetTopMargin(0.0);
	pad3->SetBottomMargin(0.3);
	pad3->SetRightMargin(0.1);
	pad3->SetFillStyle(0);

	leadingRatio2Systematics->GetXaxis()->SetLabelFont (42);
	leadingRatio2Systematics->GetXaxis()->SetTitleFont (42);
	leadingRatio2Systematics->GetXaxis()->SetTitleSize(0.11);
	leadingRatio2Systematics->GetXaxis()->SetTitleOffset (1.1);
	leadingRatio2Systematics->GetYaxis()->SetTitleSize(0.095);
	leadingRatio2Systematics->GetYaxis()->SetLabelSize(0.10);
	leadingRatio2Systematics->GetYaxis()->SetTitleOffset(0.65);
	leadingRatio2Systematics->GetYaxis()->SetTitle("Data/MC");   
	leadingRatio2Systematics->GetYaxis()->SetNdivisions(505);
	leadingRatio2Systematics->GetYaxis()->SetRangeUser(0.4,1.6);


	leadingRatioMadGraph->SetTitle("");	  

	if (use_case ==1) {
	  leadingRatio2Systematics->GetXaxis ()->SetTitle ("jet multiplicity");
	}
	if (use_case ==2) {
	  if (whichjet == 1) leadingRatio2Systematics->GetXaxis ()->SetTitle ("leading jet p_{T} [GeV/c]");
	  if (whichjet == 2) leadingRatio2Systematics->GetXaxis ()->SetTitle ("subleading jet p_{T} [GeV/c]");
	  if (whichjet == 3) leadingRatio2Systematics->GetXaxis ()->SetTitle ("subsubleading jet p_{T} [GeV/c]");
	  if (whichjet == 4) leadingRatio2Systematics->GetXaxis ()->SetTitle ("subsubsubleading jet p_{T} [GeV/c]");
	}
	if (use_case ==3) {
	  if (whichjet == 1) leadingRatio2Systematics->GetXaxis ()->SetTitle ("leading jet #eta");
	  if (whichjet == 2) leadingRatio2Systematics->GetXaxis ()->SetTitle ("subleading jet #eta");
	  if (whichjet == 3) leadingRatio2Systematics->GetXaxis ()->SetTitle ("subsubleading jet #eta");
	  if (whichjet == 4) leadingRatio2Systematics->GetXaxis ()->SetTitle ("subsubsubleading jet #eta");
	}
	if (use_case ==4) {
	  if (whichjet == 1) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} >= 1 [GeV/c]");
	  if (whichjet == 2) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} >= 2 [GeV/c]");
	  if (whichjet == 3) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} >= 3 [GeV/c]");
	  if (whichjet == 4) leadingRatio2Systematics->GetXaxis ()->SetTitle ("H_{T}, N_{jet} >= 4 [GeV/c]");
	}

	leadingRatio2Systematics->Draw ("E1");
	leadingRatio2->Draw ("E1SAME");

	//	leadingRatioMadGraphPDF->SetFillColor(kOrange+2);
	//	leadingRatioMadGraphPDF->SetFillStyle(3005);
	//	leadingRatioMadGraphPDF->SetLineColor(kOrange+2);
	//	leadingRatioMadGraphPDF->SetLineWidth(0.6);
	//	leadingRatioMadGraphPDF->Draw("5");
      
	leadingRatioMadGraph->SetFillColor(kOrange+10);
	leadingRatioMadGraph->SetFillStyle(3002);
	leadingRatioMadGraph->SetLineColor(kOrange+10);
	leadingRatioMadGraph->SetLineWidth(0.6);
	leadingRatioMadGraph->Draw("5");
	  
	leadingRatio2Systematics->Draw ("E1SAME");
	leadingRatio2->Draw ("E1SAME");
	  
	TLine *OLine2 = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	OLine2->SetLineColor(kBlack);
	OLine2->SetLineStyle(2);
	OLine2->Draw();
	  
	latexLabel->SetTextSize(0.065);

	latexLabel->DrawLatex(0.2,0.35,"MadGraph");	  
	  
	string title1;
	title1 = s + "DifferentialX" + stringmatch + ".pdf";
	  
	cout << title1 << endl;
	  
	plots->Print (title1.c_str ());
	return;
      }
    }
}

