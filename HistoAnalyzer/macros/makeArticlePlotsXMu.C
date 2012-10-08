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
makeArticlePlotsXMu ()
{

  setTDRStyle ();
  gStyle->SetErrorX(0);

  int use_case = 1;
  int whichjet = 1;
  string version = "_v2_32";
  //string s = "/home/schizzi/CMSSW_4_4_2/src/Histo/HistoAnalyzer/macros/plotArticleMu" + version + "/";
  string s="/tmp/";

  string plotpath = "/gpfs/cms/data/2011/Uncertainties/";
  gStyle->SetOptStat (0);

  TCanvas *plots = new TCanvas ("plots", "EB", 200, 100, 800, 800);

  //DATA:
  string pathFile="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributions_v2_32ApprovalNoNormalization.root";

  //RIVET:
  string rivetPathSherpa       ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod_mu/out.root";
  string rivetPathSherpaUP     ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaleup_mu/out.root";
  string rivetPathSherpaDOWN   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaledown_mu/out.root";
  string rivetPathSherpaPDF1   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfmstw_mu/out.root";
  string rivetPathSherpaPDF2   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfnn_mu/out.root";
  string rivetPathMadGraph     ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
  string rivetPathMadGraphDOWN ="/gpfs/cms/users/candelis/Rivet/madgraph/scaledown/DYtotal.root";
  string rivetPathMadGraphUP   ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleup/DYtotal.root";

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

      if (use_case == 1) 
	{ // Jet Multiplicity
	  stringmatch = "JetMultiplicityUnfolded";
	  systPathFile = plotpath + "jetMultFinalSyst" + version + ".txt";
	  rivet_data="d08_x01_y01";
	  rivet_dataMG="d08-x01-y01";
	}
      if (use_case == 2) 
	{ // Jet Pt
	  if (whichjet == 1)
	    {
	      stringmatch = "jReco_leading";
	      systPathFile = plotpath + "jet1PtFinalSyst" + version + ".txt";
	      rivet_data = "d06_x01_y01";
	      rivet_dataMG = "d06-x01-y01";
	    }
	  if (whichjet == 2)
	    {
	      stringmatch = "jReco_subleading";
	      systPathFile = plotpath + "jet2PtFinalSyst" + version + ".txt";
	      rivet_data = "d07_x01_y01";
	      rivet_dataMG = "d07-x01-y01";
	    }
	  if (whichjet == 3)
	    {
	      stringmatch = "jReco_subsubleading";
	      systPathFile = plotpath + "jet3PtFinalSyst" + version + ".txt";
	      rivet_data = "d09_x01_y01";
	      rivet_dataMG = "d09-x01-y01";
	    }
	  if (whichjet == 4)
	    {
	      stringmatch = "jReco_subsubsubleading";
	      systPathFile = plotpath + "jet4PtFinalSyst" + version + ".txt";
	      rivet_data = "d10_x01_y01";
	      rivet_dataMG = "d10-x01-y01";
	    }
	}
      if (use_case == 3) { // Jet Eta
	if (whichjet == 1)
	  {
	    stringmatch = "jReco_leadingeta";
	    systPathFile = plotpath + "jet1EtaFinalSyst" + version + ".txt";
	    rivet_data   = "d11_x01_y01";
	    rivet_dataMG   = "d11-x01-y01";
	  }
	if (whichjet == 2)
	  {
	    stringmatch = "jReco_subleadingeta";
	    systPathFile = plotpath + "jet2EtaFinalSyst" + version + ".txt";
	    rivet_data   = "d12_x01_y01";
	    rivet_dataMG   = "d12-x01-y01";
	  }
	if (whichjet == 3)
	  {
	    stringmatch = "jReco_subsubleadingeta";
	    systPathFile = plotpath + "jet3EtaFinalSyst" + version + ".txt";
	    rivet_data   = "d13_x01_y01";
	    rivet_dataMG   = "d13-x01-y01";
	  }
	if (whichjet == 4)
	  {
	    stringmatch = "jReco_subsubsubleadingeta";
	    systPathFile = plotpath + "jet4EtaFinalSyst" + version + ".txt";
	    rivet_data   = "d14_x01_y01";
	    rivet_dataMG   = "d14-x01-y01";
	  }
      }
      if (use_case == 4) { // Ht
	if (whichjet == 1)
	  {
	    stringmatch = "HReco_leading";
	    systPathFile = plotpath + "jet1HtFinalSyst" + version + ".txt";
	    rivet_data    = "d23_x01_y01";
	    rivet_dataMG    = "d23-x01-y01";
	  }
	if (whichjet == 2)
	  {
	    stringmatch = "HReco_subleading";
	    systPathFile = plotpath + "jet2HtFinalSyst" + version + ".txt";
	    rivet_data    = "d24_x01_y01";
	    rivet_dataMG    = "d24-x01-y01";
	  }
	if (whichjet == 3)
	  {
	    stringmatch = "HReco_subsubleading";
	    systPathFile = plotpath + "jet3HtFinalSyst" + version + ".txt";
	    rivet_data    = "d25_x01_y01";
	    rivet_dataMG    = "d25-x01-y01";
	  }
	if (whichjet == 4)
	  {
	    stringmatch = "HReco_subsubsubleading";
	    systPathFile = plotpath + "jet3HtFinalSyst" + version + ".txt";
	    rivet_data    = "d26_x01_y01";
	    rivet_dataMG    = "d26-x01-y01";
	  }
      }

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
	  /*
	  TFile *histoRivetMadGraph = TFile::Open (rivetPathMadGraph.c_str ());
	  histoRivetMadGraph->cd ("");
	  TDirectory *dirRivetMadGraph = gDirectory;
	  TList *mylistRivetMadGraph = (TList *) dirRivetMadGraph->GetListOfKeys ();
	  TIter iterRivetMadGraph (mylistRivetMadGraph);
	  TObject *tobjRivetMadGraph = 0;
	  while ((tobjRivetMadGraph = iterRivetMadGraph.Next ()))
	    {
	      string nameRivetMadGraph = tobjRivetMadGraph->GetName ();
	      if (nameRivetMadGraph == rivet_data)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraph << endl;
		  TGraphAsymmErrors *leadingRivetMadGraph;
		  gDirectory->GetObject (nameRivetMadGraph.c_str (), leadingRivetMadGraph);
		  TGraphAsymmErrors *leadingRatioMadGraph;
		  leadingRatioMadGraph = (TGraphAsymmErrors *) leadingRivetMadGraph->Clone ("");
		}
	    }
	  */

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
	  /*
	  TFile *histoRivetMadGraphDOWN = TFile::Open (rivetPathMadGraphDOWN.c_str ());
	  histoRivetMadGraphDOWN->cd ("");
	  TDirectory *dirRivetMadGraphDOWN = gDirectory;
	  TList *mylistRivetMadGraphDOWN = (TList *) dirRivetMadGraphDOWN->GetListOfKeys ();
	  TIter iterRivetMadGraphDOWN (mylistRivetMadGraphDOWN);
	  TObject *tobjRivetMadGraphDOWN = 0;
	  while ((tobjRivetMadGraphDOWN = iterRivetMadGraphDOWN.Next ()))
	    {
	      string nameRivetMadGraphDOWN = tobjRivetMadGraphDOWN->GetName ();
	      if (nameRivetMadGraphDOWN == rivet_data)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraphDOWN << endl;
		  TGraphAsymmErrors *leadingRivetMadGraphDOWN;
		  gDirectory->GetObject (nameRivetMadGraphDOWN.c_str (), leadingRivetMadGraphDOWN);
		}
	    }
	  */

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
	  /*
	  TFile *histoRivetMadGraphUP = TFile::Open (rivetPathMadGraphUP.c_str ());
	  histoRivetMadGraphUP->cd ("");
	  TDirectory *dirRivetMadGraphUP = gDirectory;
	  TList *mylistRivetMadGraphUP = (TList *) dirRivetMadGraphUP->GetListOfKeys ();
	  TIter iterRivetMadGraphUP (mylistRivetMadGraphUP);
	  TObject *tobjRivetMadGraphUP = 0;
	  while ((tobjRivetMadGraphUP = iterRivetMadGraphUP.Next ()))
	    {
	      string nameRivetMadGraphUP = tobjRivetMadGraphUP->GetName ();
	      if (nameRivetMadGraphUP == rivet_data)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraphUP << endl;
		  TGraphAsymmErrors *leadingRivetMadGraphUP;
		  gDirectory->GetObject (nameRivetMadGraphUP.c_str (), leadingRivetMadGraphUP);
		}
	    }
	  */

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

	  //-------------------------------------------------------------

	  leadingSystematics->SetName ("leadingSystematics");
	  if (systTmpM.size () != leadingSystematics->GetNbinsX ())
	    cout << "WRONG NUMBER OF BINS" << endl;
	  for (int i = 0; i <= leadingSystematics->GetNbinsX (); i++)
	    {
	      //cout<<"jetMulti - syst = "<<leadingSystematics->GetBinError(i+1)<<endl;       
	      double err =
		sqrt (pow (leading->GetBinError (i + 1), 2) +
		      pow (systTmpM[i] *
			   leadingSystematics->GetBinContent (i + 1), 2));
	      leadingSystematics->SetBinError (i + 1, err);
	    }

	  if ( (use_case>1) && (leadingSystematics->Integral()>1.001 | leadingSystematics->Integral()<0.999)) {
	    cout << "Warning: DATA is NOT NORMALIZED CORRECTLY! I will fix it...";
	    leadingSystematics->Scale(1./leadingSystematics->Integral());
	    leading->Scale(1./leading->Integral());
	  }

	  //When use_case = Jet Multi, then the absolute cross section is required...
	  if (use_case==1){
	    //Normalizing data to the luminosity
	    leadingSystematics->Scale(1./4890.0); //Int Lumi 1/pb -> bimn in pb
	    leading->Scale(1./4890.0);
	  }

	  plots->cd ();
	  TPad *pad1 = new TPad("pad1","pad1",0.01,0.33,0.99,0.99);
	  pad1->Draw();
	  pad1->cd();
	  pad1->SetTopMargin(0.1);
	  pad1->SetBottomMargin(0.01);
	  pad1->SetRightMargin(0.1);
	  pad1->SetFillStyle(0);
	  pad1->SetLogy(1);

	  leadingSystematics->SetLineColor (kRed);
	  leadingSystematics->SetMarkerStyle (20);
	  leadingSystematics->SetFillColor (kRed);
	  leadingSystematics->SetMarkerColor (kRed);
	  leadingSystematics->GetYaxis ()->SetTitleOffset (1.);
	  leadingSystematics->GetXaxis ()->SetTitleOffset (1.1);
	  leadingSystematics->GetXaxis ()->SetTitleSize (0.05);
	  leadingSystematics->GetXaxis ()->SetLabelSize (0.0);
	  leadingSystematics->GetXaxis ()->SetLabelFont (42);
	  leadingSystematics->GetXaxis ()->SetTitleFont (42);
	  leadingSystematics->GetYaxis ()->SetTitleSize (0.07);
	  leadingSystematics->GetYaxis ()->SetLabelSize (0.06);
	  leadingSystematics->GetYaxis ()->SetLabelFont (42);
	  leadingSystematics->GetYaxis ()->SetTitleFont (42);
	  leadingSystematics->SetTitle ();
	  leadingSystematics->GetXaxis ()->SetTitle ();

	  if (use_case ==1) {
	    leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d N [pb]");
	    //	    leadingSystematics->GetXaxis ()->SetTitle ("jet multiplicity");
	  }
	  if (use_case ==2) {
	    leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d p_{T}");
	    //	    leadingSystematics->GetXaxis ()->SetTitle ("jet p_{T} [GeV/c]");
	  }
	  if (use_case ==3) {
	    leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d #eta");
	    //	    leadingSystematics->GetXaxis ()->SetTitle ("jet #eta");
	  }
	  if (use_case ==4) {
	    leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d H_{T}");
	    //	    leadingSystematics->GetXaxis ()->SetTitle ("jet H_{T} [GeV/c]");
	  }
	  leadingSystematics->Draw ("E1");

	  leading->SetFillColor (kBlack);
	  leading->SetFillStyle (3001);
	  leading->SetMarkerColor (kBlack);
	  leading->SetLineColor (kBlack);
	  leading->SetMarkerStyle (20);
	  leading->Draw ("E1SAMES");

	  TH1D *leadingRatio;
	  leadingRatio = (TH1D *) leading->Clone ("leading");
	  TH1D *leadingRatioSystematics;
	  leadingRatioSystematics = (TH1D *) leadingSystematics->Clone ("leading");


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
	    if (use_case == 1 ) {
	      dummyNorm= 1000.0*( (1000000.0/967.713)/4890.0)*(1/1.23);   //   100*1.5*1.23;//000 *(2475./3048)*(1./1.23)*0.666;
	      //dummyNorm=1000000*(3048.0/967.713);
	    }
	    leadingRivetSherpaUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaUP->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    //leadingRivetSherpaUP->SetPointEXhigh(ovo,10.);
	    //leadingRivetSherpaUP->SetPointEXlow(ovo,10.);
	    leadingRivetSherpaUP->SetPointEYhigh(ovo,leadingRivetSherpaUP->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaUP->SetPointEYlow(ovo,leadingRivetSherpaUP->GetErrorYlow(ovo)/dummyNorm);
	  }

	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (use_case == 1 ) {
	      dummyNorm= 1000.0*( (1000000.0/837.477)/4890.0)*(1/1.23);   //   100*1.5*1.23;//000 *(2475./3048)*(1./1.23)*0.666;
	      //dummyNorm=2000000*(3048.0/837.477);
	    }
	    leadingRivetSherpaDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaDOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    //leadingRivetSherpaDOWN->SetPointEXhigh(ovo,10.);
	    //leadingRivetSherpaDOWN->SetPointEXlow(ovo,10.);
	    leadingRivetSherpaDOWN->SetPointEYhigh(ovo,leadingRivetSherpaDOWN->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaDOWN->SetPointEYlow(ovo,leadingRivetSherpaDOWN->GetErrorYlow(ovo)/dummyNorm);
	  }
	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (use_case == 1 ) {
	      dummyNorm= 1000.0*( (500000.0/902.862)/4890.0)*(1/1.23);   //   100*1.5*1.23;//000 *(2475./3048)*(1./1.23)*0.666;
	    }
	    leadingRivetSherpaPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaPDF1->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    //leadingRivetSherpaPDF1->SetPointEXhigh(ovo,10.);
	    //leadingRivetSherpaPDF1->SetPointEXlow(ovo,10.);
	    leadingRivetSherpaPDF1->SetPointEYhigh(ovo,leadingRivetSherpaPDF1->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaPDF1->SetPointEYlow(ovo,leadingRivetSherpaPDF1->GetErrorYlow(ovo)/dummyNorm);
	  }
	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (use_case == 1 ) {
	      dummyNorm= 1000.0*( (450000.0/895.164)/4890.0)*(1/1.23);   //   100*1.5*1.23;//000 *(2475./3048)*(1./1.23)*0.666;
	    }
	    leadingRivetSherpaPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaPDF2->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpaPDF2->SetPointEXhigh(ovo,10.);
	    leadingRivetSherpaPDF2->SetPointEXlow(ovo,10.);
	    leadingRivetSherpaPDF2->SetPointEYhigh(ovo,leadingRivetSherpaPDF2->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaPDF2->SetPointEYlow(ovo,leadingRivetSherpaPDF2->GetErrorYlow(ovo)/dummyNorm);
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

	    if (use_case == 1 ) {
	      dummyNorm= 1000.0*( (1000000.0/911.328)/4890.0)*(1/1.23);   //   100*1.5*1.23;//000 *(2475./3048)*(1./1.23)*0.666;
	    }

	    leadingRivetSherpa->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpa->SetPointEXhigh(ovo,0.);
	    leadingRivetSherpa->SetPointEXlow(ovo,0.);

	    leadingRatioSherpa->SetPointEXhigh(ovo,0.0);
	    leadingRatioSherpa->SetPointEXlow(ovo,0.0);
	    leadingRatioSherpa->SetPoint(ovo,dummyXvar,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));

	    if ((y1temp-dummyYvar/dummyNorm)<0 && (y2temp-dummyYvar/dummyNorm)>0) {
	      leadingRivetSherpa->SetPointEYhigh(ovo,y2temp-dummyYvar/dummyNorm);
	      leadingRivetSherpa->SetPointEYlow(ovo,dummyYvar/dummyNorm-y1temp);
	      leadingRatioSherpa->SetPointEYlow(ovo,((y2temp-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm))*leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	      leadingRatioSherpa->SetPointEYhigh(ovo,(dummyYvar/dummyNorm-y1temp)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      
	    }
	    if ((y1temp-dummyYvar/dummyNorm)>0 && (y2temp-dummyYvar/dummyNorm)<0) {
	      leadingRivetSherpa->SetPointEYhigh(ovo,y1temp-dummyYvar/dummyNorm);
	      leadingRivetSherpa->SetPointEYlow(ovo,dummyYvar/dummyNorm-y2temp);
	      leadingRatioSherpa->SetPointEYlow(ovo,(y1temp-dummyYvar/dummyNorm)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      leadingRatioSherpa->SetPointEYhigh(ovo,(dummyYvar/dummyNorm-y2temp)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	    }
	    if ((y1temp-dummyYvar/dummyNorm)>0 && (y2temp-dummyYvar/dummyNorm)>0) {
	      if ((y1temp-dummyYvar/dummyNorm) > (y2temp-dummyYvar/dummyNorm)) {
		leadingRivetSherpa->SetPointEYhigh(ovo,y1temp-dummyYvar/dummyNorm);
		leadingRatioSherpa->SetPointEYlow(ovo,(y1temp-dummyYvar/dummyNorm)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      } else {
		leadingRivetSherpa->SetPointEYhigh(ovo,y2temp-dummyYvar/dummyNorm);
		leadingRatioSherpa->SetPointEYlow(ovo,(y2temp-dummyYvar/dummyNorm)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      }
	      leadingRivetSherpa->SetPointEYlow(ovo,0.0);
	      leadingRatioSherpa->SetPointEYhigh(ovo,0.0);
	    }
	    if ((y1temp-dummyYvar/dummyNorm)<0 && (y2temp-dummyYvar/dummyNorm)<0) {
	      if ((y1temp-dummyYvar/dummyNorm) < (y2temp-dummyYvar/dummyNorm)) {
		leadingRivetSherpa->SetPointEYlow(ovo,dummyYvar/dummyNorm-y1temp);
		leadingRatioSherpa->SetPointEYhigh(ovo,(dummyYvar/dummyNorm-y1temp)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      } else {
		leadingRivetSherpa->SetPointEYlow(ovo,dummyYvar/dummyNorm-y2temp);
		leadingRatioSherpa->SetPointEYhigh(ovo,(dummyYvar/dummyNorm-y2temp)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      }
	      leadingRivetSherpa->SetPointEYhigh(ovo,0.0);
	      leadingRatioSherpa->SetPointEYlow(ovo,0.0);
	    }
	  }

	  // PDF envelop for Sherpa:
	  TGraphAsymmErrors *leadingRivetSherpaPDF;
	  leadingRivetSherpaPDF = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ();
	  TGraphAsymmErrors *leadingRatioSherpaPDF;
	  leadingRatioSherpaPDF = (TGraphAsymmErrors *) leadingRatioSherpa->Clone ();
	  //	  Double_t dummyNorm = 0.;
	  Double_t y1temp = 0.;
	  Double_t y2temp = 0.;
	  Double_t x1temp = 0.;
	  Double_t x2temp = 0.;
	  //	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  //	    leadingRivetSherpaPDF->GetPoint(ovo,dummyXvar,dummyYvar); 
	  //	    dummyNorm = dummyNorm + dummyYvar;
	  //	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaPDF->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaPDF1->GetPoint(ovo,x1temp,y1temp); 
	    leadingRivetSherpaPDF2->GetPoint(ovo,x2temp,y2temp); 
	    //	    leadingRivetSherpaPDF->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpaPDF->SetPointEXhigh(ovo,0.);
	    leadingRivetSherpaPDF->SetPointEXlow(ovo,0.);

	    leadingRatioSherpaPDF->SetPointEXhigh(ovo,0.0);
	    leadingRatioSherpaPDF->SetPointEXlow(ovo,0.0);
	    //	    leadingRatioSherpaPDF->SetPoint(ovo,dummyXvar,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));

	    if ((y1temp-dummyYvar/dummyNorm)<0 && (y2temp-dummyYvar)>0) {
	      leadingRivetSherpaPDF->SetPointEYhigh(ovo,y2temp-dummyYvar + leadingRivetSherpa->GetErrorYhigh(ovo));
	      leadingRivetSherpaPDF->SetPointEYlow(ovo,dummyYvar-y1temp + leadingRivetSherpa->GetErrorYlow(ovo));
	      leadingRatioSherpaPDF->SetPointEYlow(ovo,(y2temp-dummyYvar)*leadingSystematics->GetBinContent(ovo+1)/(dummyYvar*dummyYvar) + leadingRatioSherpa->GetErrorYlow(ovo));
	      leadingRatioSherpaPDF->SetPointEYhigh(ovo,(dummyYvar-y1temp)*leadingSystematics->GetBinContent(ovo+1)/(dummyYvar*dummyYvar) + leadingRatioSherpa->GetErrorYhigh(ovo));
	      
	    }
	    if ((y1temp-dummyYvar)>0 && (y2temp-dummyYvar)<0) {
	      leadingRivetSherpaPDF->SetPointEYhigh(ovo,y1temp-dummyYvar + leadingRivetSherpa->GetErrorYhigh(ovo));
	      leadingRivetSherpaPDF->SetPointEYlow(ovo,dummyYvar-y2temp + leadingRivetSherpa->GetErrorYlow(ovo));
	      leadingRatioSherpaPDF->SetPointEYlow(ovo,(y1temp-dummyYvar)*leadingSystematics->GetBinContent(ovo+1)/(dummyYvar*dummyYvar) + leadingRatioSherpa->GetErrorYlow(ovo));
	      leadingRatioSherpaPDF->SetPointEYhigh(ovo,(dummyYvar-y2temp)*leadingSystematics->GetBinContent(ovo+1)/(dummyYvar*dummyYvar) + leadingRatioSherpa->GetErrorYhigh(ovo));
	    }
	    if ((y1temp-dummyYvar)>0 && (y2temp-dummyYvar)>0) {
	      if ((y1temp-dummyYvar) > (y2temp-dummyYvar)) {
		leadingRivetSherpaPDF->SetPointEYhigh(ovo,y1temp-dummyYvar + leadingRivetSherpa->GetErrorYhigh(ovo));
		leadingRatioSherpaPDF->SetPointEYlow(ovo,(y1temp-dummyYvar)*leadingSystematics->GetBinContent(ovo+1)/(dummyYvar*dummyYvar) + leadingRatioSherpa->GetErrorYlow(ovo));
	      } else {
		leadingRivetSherpaPDF->SetPointEYhigh(ovo,y2temp-dummyYvar + leadingRivetSherpa->GetErrorYhigh(ovo));
		leadingRatioSherpaPDF->SetPointEYlow(ovo,(y2temp-dummyYvar)*leadingSystematics->GetBinContent(ovo+1)/(dummyYvar*dummyYvar) + leadingRatioSherpa->GetErrorYlow(ovo));
	      }
	      leadingRivetSherpaPDF->SetPointEYlow(ovo,0.0 + leadingRivetSherpa->GetErrorYlow(ovo));
	      leadingRatioSherpaPDF->SetPointEYhigh(ovo,0.0 + leadingRatioSherpa->GetErrorYhigh(ovo));
	    }
	    if ((y1temp-dummyYvar)<0 && (y2temp-dummyYvar)<0) {
	      if ((y1temp-dummyYvar) < (y2temp-dummyYvar)) {
		leadingRivetSherpaPDF->SetPointEYlow(ovo,dummyYvar-y1temp + leadingRivetSherpa->GetErrorYlow(ovo));
		leadingRatioSherpaPDF->SetPointEYhigh(ovo,(dummyYvar-y1temp)*leadingSystematics->GetBinContent(ovo+1)/(dummyYvar*dummyYvar) + leadingRatioSherpa->GetErrorYhigh(ovo));
	      } else {
		leadingRivetSherpaPDF->SetPointEYlow(ovo,dummyYvar-y2temp + leadingRivetSherpa->GetErrorYlow(ovo));
		leadingRatioSherpaPDF->SetPointEYhigh(ovo,(dummyYvar-y2temp)*leadingSystematics->GetBinContent(ovo+1)/(dummyYvar*dummyYvar) + leadingRatioSherpa->GetErrorYhigh(ovo));
	      }
	      leadingRivetSherpaPDF->SetPointEYhigh(ovo,0.0 + leadingRivetSherpa->GetErrorYhigh(ovo));
	      leadingRatioSherpaPDF->SetPointEYlow(ovo,0.0 + leadingRatioSherpa->GetErrorYlow(ovo));
	    }
	  }

	  // Madgraph:

	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetMadGraphDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (use_case ==1 ) dummyNorm= 2.0 * 0.000000001*( (1681.85)/3048.0);// Coefficiente 10^9 che gira, piu' il fantomatico 3048/2475: il resto e' tutto consistente!
	    leadingRivetMadGraphDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetMadGraphDOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetMadGraphDOWN->SetPointEXhigh(ovo,10.);
	    leadingRivetMadGraphDOWN->SetPointEXlow(ovo,10.);
	    leadingRivetMadGraphDOWN->SetPointEYhigh(ovo,leadingRivetMadGraphDOWN->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetMadGraphDOWN->SetPointEYlow(ovo,leadingRivetMadGraphDOWN->GetErrorYlow(ovo)/dummyNorm);
	  }
	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetMadGraphUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    if (use_case ==1 ) dummyNorm= 2.0 * 0.000000001*( (1681.85)/3048.0);// Coefficiente 10^9 che gira, piu' il fantomatico 3048/2475: il resto e' tutto consistente!
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
	    if (use_case ==1 ) dummyNorm= 2.0 * 0.000000001*( (1681.85)/3048.0);// Coefficiente 10^9 che gira, piu' il fantomatico 3048/2475: il resto e' tutto consistente!
	    leadingRivetMadGraph->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetMadGraphDOWN->GetPoint(ovo,x1temp,y1temp); 
	    leadingRivetMadGraphUP->GetPoint(ovo,x2temp,y2temp); 
	    leadingRivetMadGraph->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetMadGraph->SetPointEXhigh(ovo,0.);
	    leadingRivetMadGraph->SetPointEXlow(ovo,0.);

	    leadingRatioMadGraph->SetPointEXhigh(ovo,0.0);
	    leadingRatioMadGraph->SetPointEXlow(ovo,0.0);
	    leadingRatioMadGraph->SetPoint(ovo,dummyXvar,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));

	    leadingRatio->SetBinContent(ovo+1,1.0);
	    leadingRatioSystematics->SetBinContent(ovo+1,1.0);
	    leadingRatio->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));
	    leadingRatioSystematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	    if ((y1temp-dummyYvar/dummyNorm)<0 && (y2temp-dummyYvar/dummyNorm)>0) {
	      leadingRivetMadGraph->SetPointEYhigh(ovo,y2temp-dummyYvar/dummyNorm);
	      leadingRivetMadGraph->SetPointEYlow(ovo,dummyYvar/dummyNorm-y1temp);
	      leadingRatioMadGraph->SetPointEYlow(ovo,((y2temp-dummyYvar/dummyNorm)/(dummyYvar/dummyNorm))*leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	      leadingRatioMadGraph->SetPointEYhigh(ovo,(dummyYvar/dummyNorm-y1temp)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      
	    }
	    if ((y1temp-dummyYvar/dummyNorm)>0 && (y2temp-dummyYvar/dummyNorm)<0) {
	      leadingRivetMadGraph->SetPointEYhigh(ovo,y1temp-dummyYvar/dummyNorm);
	      leadingRivetMadGraph->SetPointEYlow(ovo,dummyYvar/dummyNorm-y2temp);
	      leadingRatioMadGraph->SetPointEYlow(ovo,(y1temp-dummyYvar/dummyNorm)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      leadingRatioMadGraph->SetPointEYhigh(ovo,(dummyYvar/dummyNorm-y2temp)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	    }
	    if ((y1temp-dummyYvar/dummyNorm)>0 && (y2temp-dummyYvar/dummyNorm)>0) {
	      if ((y1temp-dummyYvar/dummyNorm) > (y2temp-dummyYvar/dummyNorm)) {
		leadingRivetMadGraph->SetPointEYhigh(ovo,y1temp-dummyYvar/dummyNorm);
		leadingRatioMadGraph->SetPointEYlow(ovo,(y1temp-dummyYvar/dummyNorm)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      } else {
		leadingRivetMadGraph->SetPointEYhigh(ovo,y2temp-dummyYvar/dummyNorm);
		leadingRatioMadGraph->SetPointEYlow(ovo,(y2temp-dummyYvar/dummyNorm)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      }
	      leadingRivetMadGraph->SetPointEYlow(ovo,0.0);
	      leadingRatioMadGraph->SetPointEYhigh(ovo,0.0);
	    }
	    if ((y1temp-dummyYvar/dummyNorm)<0 && (y2temp-dummyYvar/dummyNorm)<0) {
	      if ((y1temp-dummyYvar/dummyNorm) < (y2temp-dummyYvar/dummyNorm)) {
		leadingRivetMadGraph->SetPointEYlow(ovo,dummyYvar/dummyNorm-y1temp);
		leadingRatioMadGraph->SetPointEYhigh(ovo,(dummyYvar/dummyNorm-y1temp)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      } else {
		leadingRivetMadGraph->SetPointEYlow(ovo,dummyYvar/dummyNorm-y2temp);
		leadingRatioMadGraph->SetPointEYhigh(ovo,(dummyYvar/dummyNorm-y2temp)*leadingSystematics->GetBinContent(ovo+1)/((dummyYvar*dummyYvar)/(dummyNorm*dummyNorm)));
	      }
	      leadingRivetMadGraph->SetPointEYhigh(ovo,0.0);
	      leadingRatioMadGraph->SetPointEYlow(ovo,0.0);
	    }
	  }
	  //	  leadingRivetMadGraph->Scale(1.0/leadingRivetMadGraph->Integral());
	  //	  leadingRatioMadGraph->Scale(1.0/leadingRatioMadGraph->Integral());

	  TColor *t = new TColor(996,0.,0.0,1.0,"blu1",0.5);
	  TColor *t = new TColor(995,0.,0.5,1.0,"blu2",0.5);
	  TColor *t = new TColor(994,0.,1.0,1.0,"blu3",0.5);
	  TColor *t = new TColor(993,0.,1.0,0.5.,"blu4",0.5);
	  TColor *t = new TColor(992,0.,1.0,0.0,"blu5",0.5);
	  TColor *t = new TColor(999,1.,0.5,0.0,"arancio1",0.5);
	  TColor *t = new TColor(998,1.,0.0,0.0,"arancio2",0.5);
	  TColor *t = new TColor(997,1.,1.0,0.0,"arancio3",0.5);

	  leadingRivetSherpaPDF1->SetFillColor(992);
	  //leadingRivetSherpaPDF1->Draw("3");

	  leadingRivetSherpaPDF2->SetFillColor(993);
	  //leadingRivetSherpaPDF2->Draw("3");

	  leadingRivetSherpaUP->SetFillColor(994);
	  //leadingRivetSherpaUP->Draw("3");
	  
	  leadingRivetSherpaDOWN->SetFillColor(995);
	  //leadingRivetSherpaDOWN->Draw("3");

	  leadingRivetSherpaPDF->SetFillColor(994);
	  leadingRivetSherpaPDF->SetLineColor(kBlue);
	  leadingRivetSherpaPDF->SetLineWidth(2);
	  leadingRivetSherpaPDF->Draw("l3");

	  leadingRivetSherpa->SetFillColor(995);
	  leadingRivetSherpa->SetLineColor(kBlue);
	  leadingRivetSherpa->SetLineWidth(2);
	  leadingRivetSherpa->Draw("l3");

	  leadingRivetMadGraph->SetFillColor(999);
	  leadingRivetMadGraph->SetLineColor(kRed);
	  leadingRivetMadGraph->SetLineWidth(2);
	  leadingRivetMadGraph->Draw("l3");

	  leadingRivetMadGraphDOWN->SetFillColor(998);
	  //	  leadingRivetMadGraphDOWN->Draw("3");

 	  leadingRivetMadGraphUP->SetFillColor(997);
	  //	  leadingRivetMadGraphUP->Draw("3");

	  leadingSystematics->Draw ("E1SAMES");
	  leading->Draw ("E1SAMES");
	  //-------------------------------------------

	  // Draw the label and save plot:
	  TLatex *latexLabel = CMSPrel (4.890, "", 0.25, 0.4);	// make fancy label
	  latexLabel->Draw ("same");
	  TLegend *legend_d = new TLegend (0.65, 0.62, 0.90, 0.88);
	  legend_d->SetFillColor (0);
	  legend_d->SetFillStyle (0);
	  legend_d->SetBorderSize (0);
	  legend_d->AddEntry (leading, "Data w/Stat Uncertainty", "LP");
	  legend_d->AddEntry (leadingSystematics, "Total Uncertainty", "LP");
	  legend_d->AddEntry (leadingRivetSherpa, "Sherpa", "F");
	  legend_d->AddEntry (leadingRivetSherpaPDF, "Sherpa (PDF dep.)", "F");
	  //	  legend_d->AddEntry (leadingRivetSherpaUP, "Sherpa (scale-up)", "F");
	  //	  legend_d->AddEntry (leadingRivetSherpaDOWN, "Sherpa (scale-down)", "F");
	  //	  legend_d->AddEntry (leadingRivetSherpaPDF1, "Sherpa (pdf mstw)", "F");
	  //	  legend_d->AddEntry (leadingRivetSherpaPDF2, "Sherpa (pdf nn)", "F");
	  legend_d->AddEntry (leadingRivetMadGraph, "MadGraph", "F");
	  //	  legend_d->AddEntry (leadingRivetMadGraphUP, "MadGraph (scale-up)", "F");
	  //	  legend_d->AddEntry (leadingRivetMadGraphDOWN, "MadGraph (scale-down)", "F");
	  legend_d->Draw ("same");

	  // Draw the ratio plot: ----------------------
	  plots->cd ();

	  TPad *pad2 = new TPad("pad2","pad2",0.01,0.01,0.99,0.32);
	  pad2->Draw();
	  pad2->cd();
	  pad2->SetTopMargin(0.01);
	  pad2->SetBottomMargin(0.3);
	  pad2->SetRightMargin(0.1);
	  pad2->SetFillStyle(0);

	  leadingRatioSherpaPDF->GetXaxis()->SetRangeUser(leadingSystematics->GetXaxis()->GetXmin(),leadingSystematics->GetXaxis()->GetXmax());
	  leadingRatioSherpaPDF->GetYaxis()->SetRangeUser(0.,2.);
	  leadingRatioSherpaPDF->GetYaxis()->SetNdivisions(5);
	  leadingRatioSherpaPDF->GetXaxis()->SetTitleSize(0.14);
	  leadingRatioSherpaPDF->GetYaxis()->SetTitleSize(0.11);
	  leadingRatioSherpaPDF->GetXaxis()->SetLabelSize(0.14);
	  leadingRatioSherpaPDF->GetYaxis()->SetLabelSize(0.11);
	  leadingRatioSherpaPDF->GetYaxis()->SetTitleOffset(0.65);
	  leadingRatioSherpaPDF->GetYaxis()->SetTitle("Ratio data/MC");   

	  leadingRatioSherpaPDF->GetXaxis()->SetTitleOffset (1.1);
	  //	  leadingRatioSherpaPDF->GetYaxis()->SetTitleOffset (1.);
	  //	  leadingRatioSherpaPDF->GetXaxis()->SetTitleSize (0.05);
	  //	  leadingRatioSherpaPDF->GetXaxis()->SetLabelSize (0.06);
	  leadingRatioSherpaPDF->GetXaxis()->SetLabelFont (42);
	  leadingRatioSherpaPDF->GetXaxis()->SetTitleFont (42);
	  //	  leadingRatioSherpaPDF->GetYaxis()->SetTitleSize (0.07);
	  //	  leadingRatioSherpaPDF->GetYaxis()->SetLabelSize (0.06);

	  if (use_case ==1) {
	    leadingRatioSherpaPDF->GetXaxis ()->SetTitle ("jet multiplicity");
	  }
	  if (use_case ==2) {
	    leadingRatioSherpaPDF->GetXaxis ()->SetTitle ("jet p_{T} [GeV/c]");
	  }
	  if (use_case ==3) {
	    leadingRatioSherpaPDF->GetXaxis ()->SetTitle ("jet #eta");
	  }
	  if (use_case ==4) {
	    leadingRatioSherpaPDF->GetXaxis ()->SetTitle ("jet H_{T} [GeV/c]");
	  }

	  leadingRatioSherpaPDF->SetFillColor(994);
	  leadingRatioSherpaPDF->SetLineColor(kBlue);
	  leadingRatioSherpaPDF->SetLineWidth(2);
	  leadingRatioSherpaPDF->Draw("al3");

	  leadingRatioSherpa->SetFillColor(995);
	  leadingRatioSherpa->SetLineColor(kBlue);
	  leadingRatioSherpa->SetLineWidth(2);
	  leadingRatioSherpa->Draw("l3");

	  leadingRatioMadGraph->SetFillColor(999);
	  leadingRatioMadGraph->SetLineColor(kRed);
	  leadingRatioMadGraph->SetLineWidth(2);
	  leadingRatioMadGraph->Draw("l3");


	  //	  leadingRatioSystematics->SetFillColor (kBlack);
	  //	  leadingRatioSystematics->SetFillStyle (3001);
	  //	  leadingRatioSystematics->SetMarkerColor (kBlack);
	  //	  leadingRatioSystematics->SetLineColor (kBlack);
	  //	  leadingRatioSystematics->SetMarkerStyle (20);
	  leadingRatioSystematics->Draw ("E1 SAME");

	  //	  leading->SetFillColor (kBlack);
	  //	  leading->SetFillStyle (3001);
	  //	  leading->SetMarkerColor (kBlack);
	  //	  leading->SetLineColor (kBlack);
	  //	  leading->SetMarkerStyle (20);
	  leadingRatio->Draw ("E1 SAME");

	  TLine *OLine = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	  OLine->SetLineColor(kBlack);
	  OLine->SetLineStyle(2);
	  OLine->Draw();

	  // -------------------------------------------

	  string title1 = s + "DifferentialX" + stringmatch + ".png";
	  cout << title1 << endl;
	  plots->Print (title1.c_str ());
	}
    }
}
