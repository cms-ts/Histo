#include "Unfolding/tdrstyle.C"
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
#include "TColor.h"
#include <string.h>

void
makeArticlePlots (int whichobservable, int whichjet, int whichlepton)
{

  setTDRStyle ();
  gStyle->SetErrorX(0);

  bool absoluteNormalization=true;
  int lepton=whichlepton; //1 -> electron,  2 -> muon, 3 -> combined reults!
  bool noErrorsOnPad1=false;
  bool addLumiUncertainties=true; double lumiError=0.025;

  int use_case = whichobservable;
  int whichjet = whichjet;
  string version = "_v2_32";
  //string s = "/home/schizzi/CMSSW_4_4_2/src/Histo/HistoAnalyzer/macros/plotArticleEle" + version + "/";
  string s = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v32/FinalTheoryComparison/";
  if (lepton==2) string s = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v32/FinalTheoryComparison/Mu/";
  if (lepton==3) string s = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v32/FinalTheoryComparison/combination/";
  //string s="/tmp/";
  string plotpath = "/gpfs/cms/data/2011/Uncertainties/";
  gStyle->SetOptStat (0);

  TCanvas *plots = new TCanvas ("plots", "EB", 200, 100, 600, 800);

  //DATA:
  string pathFile="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributions_v2_32ApprovalNoNormalization.root";
  if (lepton == 2) pathFile="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributions_v2_32ApprovalNoNormalizationMu.root";
  if (lepton == 3) pathFile="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributions_v2_32_NoNormalization_Combined.root";

  //RIVET:
  //old Vieri string rivetPathSherpa ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod/out.root";
  string rivetPathSherpa ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";
  string rivetPathSherpaUP="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaleup2/out.root";
   // old vieri string rivetPathSherpaUP ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaleup/out.root";
  //old veri string rivetPathSherpaDOWN ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaledown/out.root";
  string rivetPathSherpaDOWN="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaledown2/out.root";
  string rivetPathSherpaPDF1 ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfmstw/out.root";
  string rivetPathSherpaPDF2 ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfnn/out.root";
  //  string rivetPathMadGraph ="/gpfs/cms/users/dellaric/work/cms/pythiaZ2tune/madgraph_lhe/test_full2/merged.root"; // Chiara
  //  string rivetPathMadGraphDOWN ="/gpfs/cms/users/dellaric/work/cms/pythiaZ2tune/madgraph_lhe/test_full2_scaledown/merged.root";
  //  string rivetPathMadGraphUP ="/gpfs/cms/users/dellaric/work/cms/pythiaZ2tune/madgraph_lhe/test_full2_scaleup/merged.root";
 string rivetPathMadGraph ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root"; // Tomo
 string rivetPathMadGraphDOWN ="/gpfs/cms/users/candelis/Rivet/madgraph/scaledown/DYtotal.root";
 string rivetPathMadGraphUP ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleup/DYtotal.root";
 string rivetPathMadGraphPDF1 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfmstw/DYtotal.root"; 
 string rivetPathMadGraphPDF2 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfnn/DYtotal.root";

  if (lepton == 2){
  rivetPathSherpa       ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod_mu/out.root";
  rivetPathSherpaUP     ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaleup_mu/out.root";
  rivetPathSherpaDOWN   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaledown_mu/out.root";
  rivetPathSherpaPDF1   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfmstw_mu/out.root";
  rivetPathSherpaPDF2   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfnn_mu/out.root";
  rivetPathMadGraph     ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
  rivetPathMadGraphDOWN ="/gpfs/cms/users/candelis/Rivet/madgraph/scaledown/DYtotal.root";
  rivetPathMadGraphUP   ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleup/DYtotal.root";
  rivetPathMadGraphPDF1 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfmstw/DYtotal.root";
  rivetPathMadGraphPDF2 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfnn/DYtotal.root";
  }

  if (lepton == 3){
  rivetPathSherpa       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_central.root";
  rivetPathSherpaUP     ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_scaleUP.root";
  rivetPathSherpaDOWN   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_scaleDOWN.root";
  rivetPathSherpaPDF1   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_PDF1.root";
  rivetPathSherpaPDF2   ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_PDF2.root";
  rivetPathMadGraph     ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_central.root";
  rivetPathMadGraphDOWN ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_scaleDOWN.root";
  rivetPathMadGraphUP   ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_scaleUP.root";
  rivetPathMadGraphPDF1 ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_PDF1.root";
  rivetPathMadGraphPDF2 ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_PDF2.root";
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
	  if (lepton == 1 || lepton == 3) oss<<"03"; else oss<<"08";
	}

      if (use_case == 2) 
	{ // Jet Pt
	  if (whichjet == 1)
	    {
	      stringmatch = "jReco_leading";
	      systPathFile = plotpath + "jet1PtFinalSyst" + version + ".txt";
	      if (lepton == 1 || lepton == 3) oss<<"01"; else oss<<"06";
	    }
	  
	  if (whichjet == 2)
	    {
	      stringmatch = "jReco_subleading";
	      systPathFile = plotpath + "jet2PtFinalSyst" + version + ".txt";
	      if (lepton == 1 || lepton == 3) oss<<"02"; else oss<<"07";
	    }
	  
	  if (whichjet == 3)
	    {
	      stringmatch = "jReco_subsubleading";
	      systPathFile = plotpath + "jet3PtFinalSyst" + version + ".txt";
	      if (lepton == 1 || lepton == 3) oss<<"04"; else oss<<"09";
	    }
	  
	  if (whichjet == 4)
	    {
	      stringmatch = "jReco_subsubsubleading";
	      systPathFile = plotpath + "jet4PtFinalSyst" + version + ".txt";
	      if (lepton == 1 || lepton == 3) oss<<"05"; else oss<<"10";
	    }
	}
      
      if (use_case == 3) { // Jet Eta
	if (whichjet == 1)
	  {
	    stringmatch = "jReco_leadingeta";
	    systPathFile = plotpath + "jet1EtaFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton == 3) oss<<"15"; else oss<<"11";
	  }
	
	if (whichjet == 2)
	  {
	    stringmatch = "jReco_subleadingeta";
	    systPathFile = plotpath + "jet2EtaFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton == 3) oss<<"16"; else oss<<"12";
	  }

	if (whichjet == 3)
	  {
	    stringmatch = "jReco_subsubleadingeta";
	    systPathFile = plotpath + "jet3EtaFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton == 3) oss<<"17"; else oss<<"13";
	  }
	
	if (whichjet == 4)
	  {
	    stringmatch = "jReco_subsubsubleadingeta";
	    systPathFile = plotpath + "jet4EtaFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton == 3) oss<<"18"; else oss<<"14";
	  }
      }
      
      if (use_case == 4) { // Ht
	if (whichjet == 1)
	  {
	    stringmatch = "HReco_leading";
	    systPathFile = plotpath + "jet1HtFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton == 3) oss<<"19"; else oss<<"23";
	  }
	
	if (whichjet == 2)
	  {
	    stringmatch = "HReco_subleading";
	    systPathFile = plotpath + "jet2HtFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton == 3) oss<<"20"; else oss<<"24";
	  }
	
	if (whichjet == 3)
	  {
	    stringmatch = "HReco_subsubleading";
	    systPathFile = plotpath + "jet3HtFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton == 3) oss<<"21"; else oss<<"25";
	  }

	if (whichjet == 4)
	  {
	    stringmatch = "HReco_subsubsubleading";
	    systPathFile = plotpath + "jet3HtFinalSyst" + version + ".txt";
	    if (lepton == 1 || lepton == 3) oss<<"22"; else oss<<"26";
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
	  cout << "reading ...  " << systPathFile << endl;
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
		  cout << "Getting rivet data->" << nameRivetSherpa << endl;
		  TGraphAsymmErrors *leadingRivetSherpa;
		  gDirectory->GetObject (nameRivetSherpa.c_str (), leadingRivetSherpa);
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
		  cout << "Getting rivet data->" << nameRivetSherpaUP << endl;
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
		  cout << "Getting rivet data->" << nameRivetSherpaDOWN << endl;
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
		  cout << "Getting rivet data->" << nameRivetSherpaPDF1 << endl;
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
		  cout << "Getting rivet data->" << nameRivetSherpaPDF2 << endl;
		  TGraphAsymmErrors *leadingRivetSherpaPDF2;
		  gDirectory->GetObject (nameRivetSherpaPDF2.c_str (), leadingRivetSherpaPDF2);
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
		  cout << "Getting rivet data->" << nameRivetMadGraph << endl;
		  TH1D *leadingRivetMadGraph_TH1;
		  gDirectory->GetObject (nameRivetMadGraph.c_str (), leadingRivetMadGraph_TH1);
		  int nthbins = leadingRivetMadGraph_TH1->GetNbinsX();
		  TGraphAsymmErrors *leadingRivetMadGraph;
		  leadingRivetMadGraph = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
		  for (int n=0;n<nthbins;n++) {
		    leadingRivetMadGraph->SetPoint(n,leadingRivetMadGraph_TH1->GetBinCenter(n+1),leadingRivetMadGraph_TH1->GetBinContent(n+1));
		    leadingRivetMadGraph->SetPointEXhigh(n,0.0);
		    leadingRivetMadGraph->SetPointEXlow(n,0.0);
		    leadingRivetMadGraph->SetPointEYhigh(n,leadingRivetMadGraph_TH1->GetBinError(n));
		    leadingRivetMadGraph->SetPointEYlow(n,leadingRivetMadGraph_TH1->GetBinError(n));
		  }
		  TGraphAsymmErrors *leadingRatioMadGraph;
		  leadingRatioMadGraph = (TGraphAsymmErrors *) leadingRivetMadGraph->Clone ("");
		}
	    }

	  TFile *histoRivetMadGraphDOWN = TFile::Open (rivetPathMadGraphDOWN.c_str ());
	  histoRivetMadGraphDOWN->cd ("");
	  TDirectory *dirRivetMadGraphDOWN = gDirectory;
	  TList *mylistRivetMadGraphDOWN = (TList *) dirRivetMadGraphDOWN->GetListOfKeys ();
	  TIter iterRivetMadGraphDOWN (mylistRivetMadGraphDOWN);
	  TObject *tobjRivetMadGraphDOWN = 0;
	  while ((tobjRivetMadGraphDOWN = iterRivetMadGraphDOWN.Next ()))
	    {
	      string nameRivetMadGraphDOWN = tobjRivetMadGraphDOWN->GetName ();
	      if (nameRivetMadGraphDOWN == rivet_dataMG)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraphDOWN << endl;
		  TH1D *leadingRivetMadGraphDOWN_TH1;
		  gDirectory->GetObject (nameRivetMadGraphDOWN.c_str (), leadingRivetMadGraphDOWN_TH1);
		  TGraphAsymmErrors *leadingRivetMadGraphDOWN;
		  leadingRivetMadGraphDOWN = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
		  for (int n=0;n<nthbins;n++) {
		    leadingRivetMadGraphDOWN->SetPoint(n,leadingRivetMadGraphDOWN_TH1->GetBinCenter(n+1),leadingRivetMadGraphDOWN_TH1->GetBinContent(n+1));
		    leadingRivetMadGraphDOWN->SetPointEXhigh(n,0.0);
		    leadingRivetMadGraphDOWN->SetPointEXlow(n,0.0);
		    leadingRivetMadGraphDOWN->SetPointEYhigh(n,leadingRivetMadGraphDOWN_TH1->GetBinError(n));
		    leadingRivetMadGraphDOWN->SetPointEYlow(n,leadingRivetMadGraphDOWN_TH1->GetBinError(n));
		  }
		}
	    }

	  TFile *histoRivetMadGraphUP = TFile::Open (rivetPathMadGraphUP.c_str ());
	  histoRivetMadGraphUP->cd ("");
	  TDirectory *dirRivetMadGraphUP = gDirectory;
	  TList *mylistRivetMadGraphUP = (TList *) dirRivetMadGraphUP->GetListOfKeys ();
	  TIter iterRivetMadGraphUP (mylistRivetMadGraphUP);
	  TObject *tobjRivetMadGraphUP = 0;
	  while ((tobjRivetMadGraphUP = iterRivetMadGraphUP.Next ()))
	    {
	      string nameRivetMadGraphUP = tobjRivetMadGraphUP->GetName ();
	      if (nameRivetMadGraphUP == rivet_dataMG)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraphUP << endl;
		  TH1D *leadingRivetMadGraphUP_TH1;
		  gDirectory->GetObject (nameRivetMadGraphUP.c_str (), leadingRivetMadGraphUP_TH1);
		  TGraphAsymmErrors *leadingRivetMadGraphUP;
		  leadingRivetMadGraphUP = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
		  for (int n=0;n<nthbins;n++) {
		    leadingRivetMadGraphUP->SetPoint(n,leadingRivetMadGraphUP_TH1->GetBinCenter(n+1),leadingRivetMadGraphUP_TH1->GetBinContent(n+1));
		    leadingRivetMadGraphUP->SetPointEXhigh(n,0.0);
		    leadingRivetMadGraphUP->SetPointEXlow(n,0.0);
		    leadingRivetMadGraphUP->SetPointEYhigh(n,leadingRivetMadGraphUP_TH1->GetBinError(n));
		    leadingRivetMadGraphUP->SetPointEYlow(n,leadingRivetMadGraphUP_TH1->GetBinError(n));
		  }
		}
	    }

	  TFile *histoRivetMadGraphPDF1 = TFile::Open (rivetPathMadGraphPDF1.c_str ());
	  histoRivetMadGraphPDF1->cd ("");
	  TDirectory *dirRivetMadGraphPDF1 = gDirectory;
	  TList *mylistRivetMadGraphPDF1 = (TList *) dirRivetMadGraphPDF1->GetListOfKeys ();
	  TIter iterRivetMadGraphPDF1 (mylistRivetMadGraphPDF1);
	  TObject *tobjRivetMadGraphPDF1 = 0;
	  while ((tobjRivetMadGraphPDF1 = iterRivetMadGraphPDF1.Next ()))
	    {
	      string nameRivetMadGraphPDF1 = tobjRivetMadGraphPDF1->GetName ();
	      if (nameRivetMadGraphPDF1 == rivet_dataMG)
		{
		  cout << "Getting MG PDF1 rivet data->" << nameRivetMadGraphPDF1 << endl;
		  TH1D *leadingRivetMadGraphPDF1_TH1;
		  gDirectory->GetObject (nameRivetMadGraphPDF1.c_str (), leadingRivetMadGraphPDF1_TH1);
		  TGraphAsymmErrors *leadingRivetMadGraphPDF1;
		  leadingRivetMadGraphPDF1 = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
		  for (int n=0;n<nthbins;n++) {
		    leadingRivetMadGraphPDF1->SetPoint(n,leadingRivetMadGraphPDF1_TH1->GetBinCenter(n+1),leadingRivetMadGraphPDF1_TH1->GetBinContent(n+1));
		    leadingRivetMadGraphPDF1->SetPointEXhigh(n,0.0);
		    leadingRivetMadGraphPDF1->SetPointEXlow(n,0.0);
		    leadingRivetMadGraphPDF1->SetPointEYhigh(n,leadingRivetMadGraphPDF1_TH1->GetBinError(n));
		    leadingRivetMadGraphPDF1->SetPointEYlow(n,leadingRivetMadGraphPDF1_TH1->GetBinError(n));
		  }
		}
	    }

	  TFile *histoRivetMadGraphPDF2 = TFile::Open (rivetPathMadGraphPDF2.c_str ());
	  histoRivetMadGraphPDF2->cd ("");
	  TDirectory *dirRivetMadGraphPDF2 = gDirectory;
	  TList *mylistRivetMadGraphPDF2 = (TList *) dirRivetMadGraphPDF2->GetListOfKeys ();
	  TIter iterRivetMadGraphPDF2 (mylistRivetMadGraphPDF2);
	  TObject *tobjRivetMadGraphPDF2 = 0;
	  while ((tobjRivetMadGraphPDF2 = iterRivetMadGraphPDF2.Next ()))
	    {
	      string nameRivetMadGraphPDF2 = tobjRivetMadGraphPDF2->GetName ();
	      if (nameRivetMadGraphPDF2 == rivet_dataMG)
		{
		  cout << "Getting MG PDF2 rivet data->" << nameRivetMadGraphPDF2 << endl;
		  TH1D *leadingRivetMadGraphPDF2_TH1;
		  gDirectory->GetObject (nameRivetMadGraphPDF2.c_str (), leadingRivetMadGraphPDF2_TH1);
		  TGraphAsymmErrors *leadingRivetMadGraphPDF2;
		  leadingRivetMadGraphPDF2 = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
		  for (int n=0;n<nthbins;n++) {
		    leadingRivetMadGraphPDF2->SetPoint(n,leadingRivetMadGraphPDF2_TH1->GetBinCenter(n+1),leadingRivetMadGraphPDF2_TH1->GetBinContent(n+1));
		    leadingRivetMadGraphPDF2->SetPointEXhigh(n,0.0);
		    leadingRivetMadGraphPDF2->SetPointEXlow(n,0.0);
		    leadingRivetMadGraphPDF2->SetPointEYhigh(n,leadingRivetMadGraphPDF2_TH1->GetBinError(n));
		    leadingRivetMadGraphPDF2->SetPointEYlow(n,leadingRivetMadGraphPDF2_TH1->GetBinError(n));
		  }
		}
	    }

	  //-------------------------------------------------------------
	  
	  leadingSystematics->SetName ("leadingSystematics");
	  if (systTmpM.size () != leadingSystematics->GetNbinsX ())
	    cout << "WRONG NUMBER OF BINS (# syst from file->" <<systTmpM.size()<<" - # bins leadingsystematics->"<<leadingSystematics->GetNbinsX()<<")"<<endl;
	  for (int i = 0; i <= leadingSystematics->GetNbinsX (); i++)
	    {
	      cout<<"Systematics for bin "<<i+1<<" is "<<systTmpM[i]<<endl;
	      //cout<<"jetMulti - syst = "<<leadingSystematics->GetBinError(i+1)<<endl;       
	      double err =
		sqrt (pow (leading->GetBinError (i + 1), 2) +
		      pow (systTmpM[i] *
			   leadingSystematics->GetBinContent (i + 1), 2));
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
	    leadingSystematics->Scale(1./4890.0); //Int Lumi 1/pb -> bin in pb
	    leading->Scale(1./4890.0);
	  }

	  plots->cd ();
	  TPad *pad1 = new TPad("pad1","pad1",0.01,0.50,0.99,0.99);

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
	  leadingRatio = (TH1D *) leading->Clone ("leading");
	  leadingRatio2 = (TH1D *) leading->Clone ("leading");
	  TH1D *leadingRatioSystematics;
	  TH1D *leadingRatio2Systematics;
	  leadingRatioSystematics = (TH1D *) leadingSystematics->Clone ("leading");
	  leadingRatio2Systematics = (TH1D *) leadingSystematics->Clone ("leading");

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
	      // 	      if (lepton ==1) dummyNorm= 2992.95 * (1000000.0/969.565)*(969.565*3/3048);   
	      if (lepton ==1) dummyNorm= 0.200477 * (1000000.0/971.754)*(971.754*3/3048);   
	      if (lepton ==2) dummyNorm= 0.200097 *(1000000.0/967.713)*(967.713*3/3048); 
	      if (lepton ==3) dummyNorm= 1.0; 
	      dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); //Divide by the bin width 
	    }
	    leadingRivetSherpaUP->GetPoint(ovo,dummyXvar,dummyYvar);
	    leadingRivetSherpaUP->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpaUP->SetPointEYhigh(ovo,leadingRivetSherpaUP->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaUP->SetPointEYlow(ovo,leadingRivetSherpaUP->GetErrorYlow(ovo)/dummyNorm);
	  }

	    cout<<"SherpaUP, after the rescaling, has integral -> "<<leadingRivetSherpaUP->Integral()<<endl;

	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (absoluteNormalization) {
	      //old Vieri if (lepton ==1) dummyNorm=  3705.55 * (1000000.0/838.298)*(838.298*3/3048); 
	      if (lepton ==1) dummyNorm=  0.113294 * (1000000.0/838.990)*(838.990*3/3048); 
	      if (lepton ==2) dummyNorm=  0.112873 * (1000000.0/837.477)*(837.477*3/3048); //Sherpa fattore di enhancement 
	      if (lepton ==3) dummyNorm= 1.0; 
	      dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); //Divide by the bin width 
	    }
	    leadingRivetSherpaDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaDOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpaDOWN->SetPointEYhigh(ovo,leadingRivetSherpaDOWN->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaDOWN->SetPointEYlow(ovo,leadingRivetSherpaDOWN->GetErrorYlow(ovo)/dummyNorm);
	  }

	    cout<<"SherpaDOWN, after the rescaling, has integral -> "<<leadingRivetSherpaDOWN->Integral()<<endl;

	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (absoluteNormalization) {
	      if (lepton==1) dummyNorm=  0.113644 * (1000000.0/898.33)*(898.33*3/3048);   
	      if (lepton==2) dummyNorm=  0.114067 * (1000000.0/899.787)*(899.787*3/3048);
	      if (lepton ==3) dummyNorm= 1.0; 
	      dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	    }
	    leadingRivetSherpaPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaPDF1->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpaPDF1->SetPointEYhigh(ovo,leadingRivetSherpaPDF1->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaPDF1->SetPointEYlow(ovo,leadingRivetSherpaPDF1->GetErrorYlow(ovo)/dummyNorm);
	  }

	    cout<<"SherpaPDF1, after the rescaling, has integral -> "<<leadingRivetSherpaPDF1->Integral()<<endl;

	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (absoluteNormalization) {
	      if (lepton ==1 ) dummyNorm=  0.150566 * (995000.0/896.767)*(896.767*3/3048);    
	      if (lepton ==2 ) dummyNorm=  0.150439 * (1000000.0/895.779)*(895.779*3/3048);  
	      if (lepton ==3) dummyNorm= 1.0; 
	      dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	    }

	    leadingRivetSherpaPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaPDF2->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpaPDF2->SetPointEYhigh(ovo,leadingRivetSherpaPDF2->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaPDF2->SetPointEYlow(ovo,leadingRivetSherpaPDF2->GetErrorYlow(ovo)/dummyNorm);
	  }

	    cout<<"SherpaPDF2, after the rescaling, has integral -> "<<leadingRivetSherpaPDF2->Integral()<<endl;

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
	      if (lepton ==1) dummyNorm= 0.155390 *(1000000.0/906.826)*(906.826*3/3048);   
	      if (lepton ==2) dummyNorm= 0.155456 *(1000000.0/907.485)*(907.485*3/3048);  
	      if (lepton ==3) dummyNorm= 1.0; 
	      dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	    }

	    leadingRivetSherpa->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	    leadingRivetSherpa->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm);
	    leadingRivetSherpa->SetPointEYlow(ovo,-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm);
 	    leadingRatioSherpa->SetPoint(ovo,dummyXvar,1.0);
	    leadingRatioSherpa->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	    leadingRatioSherpa->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));

	    leadingRatio->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	    leadingRatio->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	    leadingRatioSystematics->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	    leadingRatioSystematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	    if (noErrorsOnPad1){
	      leadingRivetSherpa->SetPointEYhigh(ovo,0);
	      leadingRivetSherpa->SetPointEYlow(ovo,0);
	      leadingRivetSherpa->SetPointEXhigh(ovo,0.);
	      leadingRivetSherpa->SetPointEXlow(ovo,0.);
	      leadingRivetSherpaUP->SetPointEYhigh(ovo,0);
	      leadingRivetSherpaUP->SetPointEYlow(ovo,0);
	      leadingRivetSherpaUP->SetPointEXhigh(ovo,0.);
	      leadingRivetSherpaUP->SetPointEXlow(ovo,0.);
	      leadingRivetSherpaDOWN->SetPointEYhigh(ovo,0);
	      leadingRivetSherpaDOWN->SetPointEYlow(ovo,0);
	      leadingRivetSherpaDOWN->SetPointEXhigh(ovo,0.);
	      leadingRivetSherpaDOWN->SetPointEXlow(ovo,0.);
	      leadingRivetSherpaPDF1->SetPointEYhigh(ovo,0);
	      leadingRivetSherpaPDF1->SetPointEYlow(ovo,0);
	      leadingRivetSherpaPDF1->SetPointEXhigh(ovo,0.);
	      leadingRivetSherpaPDF1->SetPointEXlow(ovo,0.);
	      leadingRivetSherpaPDF2->SetPointEYhigh(ovo,0);
	      leadingRivetSherpaPDF2->SetPointEYlow(ovo,0);
	      leadingRivetSherpaPDF2->SetPointEXhigh(ovo,0.);
	      leadingRivetSherpaPDF2->SetPointEXlow(ovo,0.);
	    }
	  }

	  /////////////////////////
	  
	  cout<<"Sherpa, after the rescaling, has integral -> "<<leadingRivetSherpa->Integral()<<endl;
	  
	  ////////////////////////
	  
	  
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


	  // Madgraph:

	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetMadGraphDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (absoluteNormalization) {
	      dummyNorm= 2.0 * 0.000000001*( (1737.42)/3048.0); // ele = mu !
	      dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	    }
	    leadingRivetMadGraphDOWN->GetPoint(ovo,dummyXvar,dummyYvar);
	    leadingRivetMadGraphDOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    //leadingRivetMadGraphDOWN->SetPointEXhigh(ovo,10.);
	    //leadingRivetMadGraphDOWN->SetPointEXlow(ovo,10.);
	    leadingRivetMadGraphDOWN->SetPointEYhigh(ovo,leadingRivetMadGraphDOWN->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetMadGraphDOWN->SetPointEYlow(ovo,leadingRivetMadGraphDOWN->GetErrorYlow(ovo)/dummyNorm);
	  }
	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetMadGraphUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (absoluteNormalization) {
	      dummyNorm= 2.0 * 0.000000001*( (1737.15)/3048.0);
	      dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	    }
	    leadingRivetMadGraphUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetMadGraphUP->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetMadGraphUP->SetPointEXhigh(ovo,10.);
	    leadingRivetMadGraphUP->SetPointEXlow(ovo,10.);
	    leadingRivetMadGraphUP->SetPointEYhigh(ovo,leadingRivetMadGraphUP->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetMadGraphUP->SetPointEYlow(ovo,leadingRivetMadGraphUP->GetErrorYlow(ovo)/dummyNorm);
	  }

	  Double_t dummyNorm = 0.;
	  Double_t y1temp = 0.;
	  Double_t y2temp = 0.;
	  Double_t x1temp = 0.;
	  Double_t x2temp = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetMadGraph->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (absoluteNormalization) {
	      dummyNorm= 2.0 * 0.000000001*( (1680.67)/3048.0);// Coefficiente 10^9 che gira...
	      dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); //Divide by the bin width 
	    }
	    leadingRivetMadGraph->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetMadGraphDOWN->GetPoint(ovo,x1temp,y1temp); 
	    leadingRivetMadGraphUP->GetPoint(ovo,x2temp,y2temp); 
	    leadingRivetMadGraph->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	    leadingRivetMadGraph->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm);
	    leadingRivetMadGraph->SetPointEYlow(ovo,-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm);

 	    leadingRatioMadGraph->SetPoint(ovo,dummyXvar,1.0);
	    leadingRatioMadGraph->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar/dummyNorm)-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));
	    leadingRatioMadGraph->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar/dummyNorm)+dummyYvar/dummyNorm)/(dummyYvar/dummyNorm));

	    leadingRatio2->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	    leadingRatio2->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	    leadingRatio2Systematics->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	    leadingRatio2Systematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	    //leadingRivetMadGraph->SetPointEYhigh(ovo,0);
	    //leadingRivetMadGraph->SetPointEYlow(ovo,0);

	    if (noErrorsOnPad1){
	      leadingRivetMadGraphDOWN->SetPointEYhigh(ovo,0);
	      leadingRivetMadGraphDOWN->SetPointEYlow(ovo,0);
	      leadingRivetMadGraphUP->SetPointEYhigh(ovo,0);
	      leadingRivetMadGraphUP->SetPointEYlow(ovo,0);
	      leadingRivetMadGraphDOWN->SetPointEXhigh(ovo,0.);
	      leadingRivetMadGraphDOWN->SetPointEXlow(ovo,0.);
	      leadingRivetMadGraphUP->SetPointEXhigh(ovo,0.);
	      leadingRivetMadGraphUP->SetPointEXlow(ovo,0.);
	      leadingRivetMadGraphPDF1->SetPointEYhigh(ovo,0);
	      leadingRivetMadGraphPDF1->SetPointEYlow(ovo,0);
	      leadingRivetMadGraphPDF1->SetPointEXhigh(ovo,0.);
	      leadingRivetMadGraphPDF1->SetPointEXlow(ovo,0.);
	      leadingRivetMadGraphPDF2->SetPointEYhigh(ovo,0);
	      leadingRivetMadGraphPDF2->SetPointEYlow(ovo,0);
	      leadingRivetMadGraphPDF2->SetPointEXhigh(ovo,0.);
	      leadingRivetMadGraphPDF2->SetPointEXlow(ovo,0.);
	    }
	  }

	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetMadGraphPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (absoluteNormalization) {
	      dummyNorm= 2.0 * 0.000000001*( (1680.67)/3048.0); // ele = mu !
	      dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	    }
	    leadingRivetMadGraphPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetMadGraphPDF1->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetMadGraphPDF1->SetPointEYhigh(ovo,leadingRivetMadGraphPDF1->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetMadGraphPDF1->SetPointEYlow(ovo,leadingRivetMadGraphPDF1->GetErrorYlow(ovo)/dummyNorm);
	  }

	    cout<<"MadGraphPDF1, after the rescaling, has integral -> "<<leadingRivetMadGraphPDF1->Integral()<<endl;

	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetMadGraphPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (absoluteNormalization) {
	      dummyNorm= 2.0 * 0.000000001*( (1680.67)/3048.0);
	      dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	    }
	    leadingRivetMadGraphPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetMadGraphPDF2->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetMadGraphPDF2->SetPointEYhigh(ovo,leadingRivetMadGraphPDF2->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetMadGraphPDF2->SetPointEYlow(ovo,leadingRivetMadGraphPDF2->GetErrorYlow(ovo)/dummyNorm);
	  }

	    cout<<"MadGraphPDF2, after the rescaling, has integral -> "<<leadingRivetMadGraphPDF2->Integral()<<endl;


	  ///////////////////////////
	  //PDF Envelop for Madgraph
	  ///////////////////////////

	  TGraphAsymmErrors *leadingRivetMadGraphPDF;
	  leadingRivetMadGraphPDF = (TGraphAsymmErrors *) leadingRivetMadGraph->Clone ();
	  TGraphAsymmErrors *leadingRatioMadGraphPDF;
	  leadingRatioMadGraphPDF = (TGraphAsymmErrors *) leadingRatioMadGraph->Clone ();

	  Double_t y1temp = 0.;
	  Double_t y2temp = 0.;
	  Double_t x1temp = 0.;
	  Double_t x2temp = 0.;

	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetMadGraphPDF->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetMadGraphPDF1->GetPoint(ovo,x1temp,y1temp); 
	    leadingRivetMadGraphPDF2->GetPoint(ovo,x2temp,y2temp); 

	    leadingRivetMadGraphPDF->SetPoint(ovo,dummyXvar,dummyYvar);
	    leadingRivetMadGraphPDF->SetPointEYhigh(ovo,max(max(y1temp,y2temp),dummyYvar)-dummyYvar + leadingRivetMadGraph->GetErrorYhigh(ovo));
	    leadingRivetMadGraphPDF->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar) + leadingRivetMadGraph->GetErrorYlow(ovo));

 	    leadingRatioMadGraphPDF->SetPoint(ovo,dummyXvar,1.0);
	    leadingRatioMadGraphPDF->SetPointEYhigh(ovo,(max(max(y1temp,y2temp),dummyYvar)-dummyYvar)/dummyYvar + leadingRatioMadGraph->GetErrorYhigh(ovo));
	    leadingRatioMadGraphPDF->SetPointEYlow(ovo,(-min(min(y1temp,y2temp),dummyYvar)+dummyYvar)/dummyYvar + leadingRatioMadGraph->GetErrorYlow(ovo));

	  }


	    /////////////////////////

	    cout<<"Madgraph, after the rescaling, has integral -> "<<leadingRivetMadGraph->Integral()<<endl;
	    cout<<"MadgraphUP, after the rescaling, has integral -> "<<leadingRivetMadGraphUP->Integral()<<endl;
	    cout<<"MadgraphDOWN, after the rescaling, has integral -> "<<leadingRivetMadGraphDOWN->Integral()<<endl;

	    ////////////////////////

	  TColor *t = new TColor(996,0.,0.0,1.0,"blu1",0.5);
	  TColor *t = new TColor(995,0.,0.5,1.0,"blu2",0.5);
	  TColor *t = new TColor(994,0.,1.0,1.0,"blu3",0.5);
	  TColor *t = new TColor(993,0.,1.0,0.5.,"blu4",0.5);
	  TColor *t = new TColor(992,0.,1.0,0.0,"blu5",0.5);
	  TColor *t = new TColor(999,1.,0.40,0.0,"arancio1",0.5);
	  TColor *t = new TColor(998,1.,0.0,0.0,"arancio2",0.5);
	  TColor *t = new TColor(997,1.,1.0,0.0,"arancio3",0.5);
	  TColor *t = new TColor(991,1.,0.8,0.0,"arancio-rosso",0.5);
	  TColor *t = new TColor(000,0.,0.0,0.0,"bianco",0.0);

	  bool drawPad1Withlines=false;
	  
	  if (drawPad1Withlines){
	    leadingRivetSherpaPDF1->SetFillColor(992);
	    leadingRivetSherpaPDF1->SetLineStyle(0);
	    leadingRivetSherpaPDF1->SetLineColor(kBlue);
	    leadingRivetSherpaPDF1->Draw("l");
	    
	    leadingRivetSherpaPDF2->SetFillColor(993);
	    leadingRivetSherpaPDF2->SetLineStyle(0);
	    leadingRivetSherpaPDF2->SetLineColor(kBlue);
	    leadingRivetSherpaPDF2->Draw("l");
	    
	    leadingRivetSherpaUP->SetLineStyle(5);
	    leadingRivetSherpaUP->SetLineColor(994);
	    leadingRivetSherpaUP->Draw("l");
	    
	    leadingRivetSherpaDOWN->SetLineStyle(5);
	    leadingRivetSherpaDOWN->SetLineColor(994);
	    leadingRivetSherpaDOWN->Draw("l");
	    
	    leadingRivetSherpaPDF->SetFillColor(994);
	    leadingRivetSherpaPDF->SetLineColor(kBlue);
	    leadingRivetSherpaPDF->SetLineWidth(2);
	    //leadingRivetSherpaPDF->Draw("l3");
	    
	    leadingRivetSherpa->SetFillColor(996);
	    leadingRivetSherpa->SetLineColor(kBlue);
	    leadingRivetSherpa->SetLineWidth(3);
	    leadingRivetSherpa->Draw("l");
	    
	    leadingRivetMadGraph->SetFillColor(999);
	    leadingRivetMadGraph->SetLineColor(kRed);
	    leadingRivetMadGraph->SetLineWidth(3);
	    leadingRivetMadGraph->Draw("l");
	    
	    //Envelop PDF Madgraph
	    leadingRivetMadGraphPDF->SetFillColor(991);
	    leadingRivetMadGraphPDF->SetLineColor(kRed);
	    leadingRivetMadGraphPDF->SetLineWidth(2);
	    //leadingRivetMadGraphPDF->Draw("l3");
	    
	    leadingRivetMadGraphDOWN->SetLineColor(kRed);
	    leadingRivetMadGraphDOWN->SetFillColor(kRed);
	    leadingRivetMadGraphDOWN->SetLineStyle(5);
	    leadingRivetMadGraphDOWN->Draw("l");
	    
	    leadingRivetMadGraphUP->SetFillColor(997);
	    leadingRivetMadGraphUP->SetLineColor(kRed);
	    leadingRivetMadGraphUP->SetLineStyle(5);
	    leadingRivetMadGraphUP->Draw("l");
	    
	    leadingRivetMadGraphPDF1->SetFillColor(997);
	    leadingRivetMadGraphPDF1->SetLineStyle(0);
	    leadingRivetMadGraphPDF1->SetLineColor(kRed);
	    leadingRivetMadGraphPDF1->Draw("l");
	    
	    leadingRivetMadGraphPDF2->SetFillColor(991);
	    leadingRivetMadGraphPDF2->SetLineStyle(0);
	    leadingRivetMadGraphPDF2->SetLineColor(kRed);
	    leadingRivetMadGraphPDF2->Draw("l");
	  }
	  else{
	    
	    leadingRivetSherpaPDF->SetFillColor(994);
	    leadingRivetSherpaPDF->SetLineColor(kBlue);
	    leadingRivetSherpaPDF->SetLineWidth(2);
	    leadingRivetSherpaPDF->Draw("l3");
	    
	    leadingRivetSherpa->SetFillColor(996);
	    leadingRivetSherpa->SetLineColor(kBlue);
	    leadingRivetSherpa->SetLineWidth(3);
	    leadingRivetSherpa->Draw("l3");
	    
	    leadingRivetMadGraph->SetFillColor(999);
	    leadingRivetMadGraph->SetLineColor(kRed);
	    leadingRivetMadGraph->SetLineWidth(3);
	    leadingRivetMadGraph->Draw("l3");
	    
	    //Envelop PDF Madgraph
	    leadingRivetMadGraphPDF->SetFillColor(991);
	    leadingRivetMadGraphPDF->SetLineColor(kRed);
	    leadingRivetMadGraphPDF->SetLineWidth(2);
	    leadingRivetMadGraphPDF->Draw("l3");
	  }
	  
	  leadingSystematics->Draw ("ESAME");
	  leading->Draw ("ESAME");
	  //-------------------------------------------

	  // Draw the label and save plot: (in the proper position)

	  TLatex *latexLabel;

	  if (use_case ==3){
	    if (lepton ==1) latexLabel = CMSPrel (4.890, "Z#rightarrow ee channel", 0.425, 0.15);	// make fancy label
	    if (lepton ==2) latexLabel = CMSPrel (4.890, "Z#rightarrow #mu#mu channel", 0.425, 0.15);	// make fancy label
	    if (lepton ==3) latexLabel = CMSPrel (4.890, "Z#rightarrow ll channel", 0.425, 0.15);	// make fancy label
	  }

	  if (use_case ==2 || use_case ==1 || use_case == 4){
	    if (lepton ==1) latexLabel = CMSPrel (4.890, "Z#rightarrow ee channel", 0.25, 0.3);	// make fancy label
	    if (lepton ==2) latexLabel = CMSPrel (4.890, "Z#rightarrow #mu#mu channel", 0.25, 0.3);	// make fancy label
	    if (lepton ==3) latexLabel = CMSPrel (4.890, "Z#rightarrow ll channel", 0.25, 0.3);	// make fancy label
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
	    legendsx_d->AddEntry (leadingRivetSherpa, "Sherpa ref.", "L");
	    legendsx_d->AddEntry (leadingRivetMadGraph, "MadGraph ref.", "L"); 
	    legenddx_d->SetFillColor (0);
	    legenddx_d->SetFillStyle (0);
	    legenddx_d->SetBorderSize (0);
	    legenddx_d->SetTextSize(.027);
	    //legenddx_d->AddEntry (leadingRivetSherpaDOWN, "Sherpa scale down", "L");
	    //legenddx_d->AddEntry (leadingRivetSherpaUP, "Sherpa scale up", "L");
	    legenddx_d->AddEntry (leadingRivetSherpa, "Sherpa scale var.", "F");
	    legenddx_d->AddEntry (leadingRivetSherpaPDF, "Sherpa PDF var.", "F");
	    legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph scale var.", "F");
	    legenddx_d->AddEntry (leadingRivetMadGraphPDF, "MadGraph PDF var.", "F");
	    legendsx_d->Draw ("same");
	    legenddx_d->Draw ("same");
	  }
	  else{
	    legenddx_d = new TLegend (0.6, 0.60, 0.92, 0.88);	   
	    legenddx_d->SetFillColor (0);
	    legenddx_d->SetFillStyle (0);
	    legenddx_d->SetBorderSize (0);
	    legenddx_d->SetNColumns(1);
	    legenddx_d->SetTextSize(.030);
	    legenddx_d->AddEntry (leading, "Data (stat)", "PLE");
	    legenddx_d->AddEntry (leadingSystematics, "Data (stat+syst)", "PEL");
	    legenddx_d->AddEntry (leadingRivetSherpa, "Sherpa ref.", "L");
	    legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph ref.", "L");
	    //legenddx_d->AddEntry (leadingRivetSherpaDOWN, "Sherpa scale up/down", "L");
	    //legenddx_d->AddEntry (leadingRivetMadGraphDOWN, "MadGraph scale down/up", "L");
	    //legenddx_d->AddEntry (leadingRivetSherpaPDF1, "Sherpa PDF var.", "L");
	    //legenddx_d->AddEntry (leadingRivetMadGraphPDF1, "MadGraph PDF var.", "L");

	    //legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph ref.", "L"); 
	    legenddx_d->AddEntry (leadingRivetSherpa, "Sherpa scale var.", "F");
	    legenddx_d->AddEntry (leadingRivetSherpaPDF, "Sherpa PDF var.", "F");
	    legenddx_d->AddEntry (leadingRivetMadGraph, "MadGraph scale var.", "F");
	    legenddx_d->AddEntry (leadingRivetMadGraphPDF, "MadGraph PDF var.", "F");
	    legenddx_d->Draw ("same");
	  }

	  // Draw the ratio plot: ----------------------

	  plots->cd ();
	  TPad *pad2 = new TPad("pad2","pad2",0.01,0.30,0.99,0.50);
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

	  leadingRatioSystematics->GetYaxis()->SetTitleSize(0.16);
	  leadingRatioSystematics->GetYaxis()->SetLabelSize(0.14);
	  leadingRatioSystematics->GetYaxis()->SetTitleOffset(0.45);
	  leadingRatioSystematics->GetYaxis()->SetTitle("Data/MC");   
	  leadingRatioSystematics->GetYaxis()->SetNdivisions(5);
	  leadingRatioSystematics->GetYaxis()->SetRangeUser(-0.2,2.2);

	  leadingRatioSystematics->SetTitle("");	  

	  leadingRatioSystematics->Draw ("E1");
	  leadingRatio->Draw ("E1SAME");

	  leadingRatioSherpaPDF->SetFillColor(994);
	  leadingRatioSherpaPDF->SetLineColor(kBlue);
	  leadingRatioSherpaPDF->SetLineWidth(2);
	  leadingRatioSherpaPDF->Draw("l3");

	  leadingRatioSherpa->SetFillColor(995);
	  leadingRatioSherpa->SetLineColor(kBlue);
	  leadingRatioSherpa->SetLineWidth(2);
	  leadingRatioSherpa->Draw("l3");

	  leadingRatioSystematics->Draw ("E1SAME");
	  leadingRatio->Draw ("E1SAME");

	  TLine *OLine = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	  OLine->SetLineColor(kBlack);
	  OLine->SetLineStyle(2);
	  OLine->Draw();

	  // -------------------------------------------
	  TLatex *latexLabel = new TLatex();
	  latexLabel->SetTextSize(0.1);
	  latexLabel->SetTextFont(42);
	  latexLabel->SetLineWidth(2);
	  latexLabel->SetNDC();
	  latexLabel->DrawLatex(0.2,0.09,"Sherpa");	  
	  plots->cd();
	  TPad *pad3 = new TPad("pad3","pad3",0.01,0.01,0.99,0.30);
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

	  leadingRatio2Systematics->GetYaxis()->SetTitleSize(0.11);
	  leadingRatio2Systematics->GetYaxis()->SetLabelSize(0.10);
	  leadingRatio2Systematics->GetYaxis()->SetTitleOffset(0.65);
	  leadingRatio2Systematics->GetYaxis()->SetTitle("Data/MC");   
	  leadingRatio2Systematics->GetYaxis()->SetNdivisions(5);
	  leadingRatio2Systematics->GetYaxis()->SetRangeUser(-0.2,2.2);


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
	    if (whichjet == 1) leadingRatio2Systematics->GetXaxis ()->SetTitle ("leading jet H_{T} [GeV/c]");
	    if (whichjet == 2) leadingRatio2Systematics->GetXaxis ()->SetTitle ("subleading jet H_{T} [GeV/c]");
	    if (whichjet == 3) leadingRatio2Systematics->GetXaxis ()->SetTitle ("subsubleading jet H_{T} [GeV/c]");
	    if (whichjet == 4) leadingRatio2Systematics->GetXaxis ()->SetTitle ("subsubsubleading jet H_{T} [GeV/c]");
	  }

	  leadingRatio2Systematics->Draw ("E1");
	  leadingRatio2->Draw ("E1SAME");

	  leadingRatioMadGraphPDF->SetFillColor(991);
	  leadingRatioMadGraphPDF->SetLineColor(kRed);
	  leadingRatioMadGraphPDF->SetLineWidth(2);
	  leadingRatioMadGraphPDF->Draw("l3");
      
	  leadingRatioMadGraph->SetFillColor(999);
	  leadingRatioMadGraph->SetLineColor(kRed);
	  leadingRatioMadGraph->SetLineWidth(2);
	  leadingRatioMadGraph->Draw("l3");
	  
	  leadingRatio2Systematics->Draw ("E1SAME");
	  leadingRatio2->Draw ("E1SAME");
	  
	  TLine *OLine2 = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	  OLine2->SetLineColor(kBlack);
	  OLine2->SetLineStyle(2);
	  OLine2->Draw();
	  
	  latexLabel->SetTextSize(0.07);

	  latexLabel->DrawLatex(0.2,0.35,"MadGraph");	  
	  
	  string title1;
	  title1 = s + "DifferentialX" + stringmatch + ".png";
	  
	  cout << title1 << endl;
	  
	  plots->Print (title1.c_str ());
	  return;
      }
    }
}

