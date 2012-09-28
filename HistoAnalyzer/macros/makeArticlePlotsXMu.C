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

TCanvas *plots;
string version = "_v2_32";
string s = "/home/schizzi/CMSSW_4_4_2/src/Histo/HistoAnalyzer/macros/plotArticleMu" + version + "/";

void
makeArticlePlotsXMu ()
{

  setTDRStyle ();

  int use_case = 4;
  int whichjet = 4;
  string plotpath = "/gpfs/cms/data/2011/Uncertainties/";
  gStyle->SetOptStat (0);

  //DATA:
  string pathFile="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributions_v2_32MuApprovalB.root";

  //RIVET:
  string rivetPathSherpa ="/gpfs/cms/users/candelis/CMSSW_5_2_6/src/GeneratorInterface/RivetInterface/test/test_prod/out.root";
  string rivetPathSherpaUP ="/gpfs/cms/users/candelis/CMSSW_5_2_6/src/GeneratorInterface/RivetInterface/test/test_scaleup/out.root";
  string rivetPathSherpaDOWN ="/gpfs/cms/users/candelis/CMSSW_5_2_6/src/GeneratorInterface/RivetInterface/test/test_scaledown/out.root";
  string rivetPathSherpaPDF1 ="/gpfs/cms/users/candelis/CMSSW_5_2_6/src/GeneratorInterface/RivetInterface/test/test_pdfmstw/out.root";
  string rivetPathSherpaPDF2 ="/gpfs/cms/users/candelis/CMSSW_5_2_6/src/GeneratorInterface/RivetInterface/test/test_pdfnn/out.root";
  string rivetPathMadGraph ="/gpfs/cms/users/candelis/CMSSW_5_2_5_patch1/src/GeneratorInterface/RivetInterface/test/test_full2/merged.root";

  TFile *histof = TFile::Open (pathFile.c_str ());
  plots = new TCanvas ("plots", "EB", 0, 0, 1200, 800);
  histof->cd ("");
  TDirectory *dir = gDirectory;
  TList *mylist = (TList *) dir->GetListOfKeys ();
  TIter iter (mylist);
  TObject *tobj = 0;
  string tmpname;
  string stringmatch;
  string systPathFile;
  string rivet_data;

  plots->cd ();
  int i = 0;			// solo di servizio quando debuggo...
  while ((tobj = iter.Next ()))
    {
      string name = tobj->GetName ();
      /*
      if (whichjet == 1)
	{
	  stringmatch = "jReco_leading";
	  systPathFile = plotpath + "jet1PtFinalSyst" + version + ".txt";
	  rivet_data = "d06_x01_y01";
	  rivet_dataMG = "d06-x01-y01";
	  rivet_data_eta   = "d11_x01_y01";
	  rivet_dataMG_eta = "d11-x01-y01";
	  rivet_data_ht    = "d23_x01_y01";
	  rivet_dataMG_ht  = "d23-x01-y01";
	}
      if (whichjet == 2)
	{
	  stringmatch = "jReco_subleading";
	  systPathFile = plotpath + "jet2PtFinalSyst" + version + ".txt";
	  rivet_data = "d07_x01_y01";
	  rivet_dataMG = "d07-x01-y01";
	  rivet_data_eta   = "d12_x01_y01";
	  rivet_dataMG_eta = "d12-x01-y01";
	  rivet_data_ht    = "d24_x01_y01";
	  rivet_dataMG_ht  = "d24-x01-y01";
	}
      if (whichjet == 3)
	{
	  stringmatch = "jReco_subsubleading";
	  systPathFile = plotpath + "jet3PtFinalSyst" + version + ".txt";
	  rivet_data = "d09_x01_y01";
	  rivet_dataMG = "d09-x01-y01";
	  rivet_data_eta   = "d13_x01_y01";
	  rivet_dataMG_eta = "d13-x01-y01";
	  rivet_data_ht    = "d25_x01_y01";
	  rivet_dataMG_ht  = "d25-x01-y01";
	}
      if (whichjet == 4)
	{
	  stringmatch = "jReco_subsubsubleading";
	  systPathFile = plotpath + "jet4PtFinalSyst" + version + ".txt";
	  rivet_data = "d10_x01_y01";
	  rivet_dataMG = "d10-x01-y01";
	  rivet_data_eta   = "d14_x01_y01";
	  rivet_dataMG_eta = "d14-x01-y01";
	  rivet_data_ht    = "d26_x01_y01";
	  rivet_dataMG_ht  = "d26-x01-y01";
	}
      */
      if (use_case == 1) 
	{ // Jet Multiplicity
	  stringmatch = "JetMultiplicityUnfolded";
	  systPathFile = plotpath + "jetMultFinalSyst" + version + ".txt";
	  rivet_data="d03_x01_y01";
	}
      if (use_case == 2) 
	{ // Jet Pt
	  if (whichjet == 1)
	    {
	      stringmatch = "jReco_leading";
	      systPathFile = plotpath + "jet1PtFinalSyst" + version + ".txt";
	      rivet_data = "d01_x01_y01";
	    }
	  if (whichjet == 2)
	    {
	      stringmatch = "jReco_subleading";
	      systPathFile = plotpath + "jet2PtFinalSyst" + version + ".txt";
	      rivet_data = "d02_x01_y01";
	    }
	  if (whichjet == 3)
	    {
	      stringmatch = "jReco_subsubleading";
	      systPathFile = plotpath + "jet3PtFinalSyst" + version + ".txt";
	      rivet_data = "d04_x01_y01";
	    }
	  if (whichjet == 4)
	    {
	      stringmatch = "jReco_subsubsubleading";
	      systPathFile = plotpath + "jet4PtFinalSyst" + version + ".txt";
	      rivet_data = "d05_x01_y01";
	    }
	}
      if (use_case == 3) { // Jet Eta
	if (whichjet == 1)
	  {
	    stringmatch = "jReco_leadingeta";
	    systPathFile = plotpath + "jet1EtaFinalSyst" + version + ".txt";
	    rivet_data   = "d15_x01_y01";
	  }
	if (whichjet == 2)
	  {
	    stringmatch = "jReco_subleadingeta";
	    systPathFile = plotpath + "jet2EtaFinalSyst" + version + ".txt";
	    rivet_data   = "d16_x01_y01";
	  }
	if (whichjet == 3)
	  {
	    stringmatch = "jReco_subsubleadingeta";
	    systPathFile = plotpath + "jet3EtaFinalSyst" + version + ".txt";
	    rivet_data   = "d17_x01_y01";
	  }
	if (whichjet == 4)
	  {
	    stringmatch = "jReco_subsubsubleadingeta";
	    systPathFile = plotpath + "jet4EtaFinalSyst" + version + ".txt";
	    rivet_data   = "d18_x01_y01";
	  }
      }
      if (use_case == 4) { // Ht
	if (whichjet == 1)
	  {
	    stringmatch = "HReco_leading";
	    systPathFile = plotpath + "jet1HtFinalSyst" + version + ".txt";
	    rivet_data    = "d19_x01_y01";
	  }
	if (whichjet == 2)
	  {
	    stringmatch = "HReco_subleading";
	    systPathFile = plotpath + "jet2HtFinalSyst" + version + ".txt";
	    rivet_data    = "d20_x01_y01";
	  }
	if (whichjet == 3)
	  {
	    stringmatch = "HReco_subsubleading";
	    systPathFile = plotpath + "jet3HtFinalSyst" + version + ".txt";
	    rivet_data    = "d21_x01_y01";
	  }
	if (whichjet == 4)
	  {
	    stringmatch = "HReco_subsubsubleading";
	    systPathFile = plotpath + "jet3HtFinalSyst" + version + ".txt";
	    rivet_data    = "d22_x01_y01";
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
	      if (nameRivetMadGraph == rivet_data)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraph << endl;
		  TGraphAsymmErrors *leadingRivetMadGraph;
		  gDirectory->GetObject (nameRivetMadGraph.c_str (), leadingRivetMadGraph);
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

	  if (leadingSystematics->Integral()>1.001 | leadingSystematics->Integral()<0.999) {
	    cout << "Warning: DATA is NOT NORMALIZED CORRECTLY! I will fix it...";
	    leadingSystematics->Scale(1./leadingSystematics->Integral());
	    leading->Scale(1./leading->Integral());
	  }

	  leadingSystematics->SetLineColor (kRed);
	  leadingSystematics->SetLineWidth (1.5);
	  leadingSystematics->SetMarkerStyle (20);
	  leadingSystematics->SetMarkerSize (1);
	  leadingSystematics->SetFillStyle (3001);
	  leadingSystematics->SetFillColor (kRed);
	  leadingSystematics->SetMarkerColor (kRed);
	  leadingSystematics->GetYaxis ()->SetTitleOffset (1.);
	  leadingSystematics->GetXaxis ()->SetTitleOffset (1.1);
	  leadingSystematics->GetXaxis ()->SetTitleSize (0.05);
	  leadingSystematics->GetXaxis ()->SetLabelSize (0.06);
	  leadingSystematics->GetXaxis ()->SetLabelFont (42);
	  leadingSystematics->GetXaxis ()->SetTitleFont (42);
	  leadingSystematics->GetYaxis ()->SetTitleSize (0.07);
	  leadingSystematics->GetYaxis ()->SetLabelSize (0.06);
	  leadingSystematics->GetYaxis ()->SetLabelFont (42);
	  leadingSystematics->GetYaxis ()->SetTitleFont (42);
	  leadingSystematics->SetTitle ();
	  if (use_case ==1) {
	    leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d N");
	    leadingSystematics->GetXaxis ()->SetTitle ("jet multiplicity");
	  }
	  if (use_case ==2) {
	    leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d p_{T}");
	    leadingSystematics->GetXaxis ()->SetTitle ("jet p_{T} [GeV/c]");
	  }
	  if (use_case ==3) {
	    leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d #eta");
	    leadingSystematics->GetXaxis ()->SetTitle ("jet #eta");
	  }
	  if (use_case ==4) {
	    leadingSystematics->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d H_{T}");
	    leadingSystematics->GetXaxis ()->SetTitle ("jet H_{T} [GeV/c]");
	  }
	  leadingSystematics->Draw ("E1");
	  leading->SetFillColor (kBlack);
	  leading->SetFillStyle (3001);
	  leading->SetMarkerColor (kBlack);
	  leading->SetLineColor (kBlack);
	  leading->SetLineWidth (1.5);
	  leading->SetMarkerStyle (20);
	  leading->SetMarkerSize (1);
	  leading->Draw ("E1SAMES");


	  // Superimpose RIVET: -----------------------
	  Double_t dummyXvar=0.;
	  Double_t dummyYvar=0.;
	  Int_t nRivetPoints = 0;
	  Double_t dummyNorm = 0.;
	  nRivetPoints = leadingRivetSherpa->GetN();
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpa->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpa->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpa->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpa->SetPointEXhigh(ovo,10.);
	    leadingRivetSherpa->SetPointEXlow(ovo,10.);
	    leadingRivetSherpa->SetPointEYhigh(ovo,leadingRivetSherpa->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpa->SetPointEYlow(ovo,leadingRivetSherpa->GetErrorYlow(ovo)/dummyNorm);
	  }
	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaUP->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaUP->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpaUP->SetPointEXhigh(ovo,10.);
	    leadingRivetSherpaUP->SetPointEXlow(ovo,10.);
	    leadingRivetSherpaUP->SetPointEYhigh(ovo,leadingRivetSherpaUP->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaUP->SetPointEYlow(ovo,leadingRivetSherpaUP->GetErrorYlow(ovo)/dummyNorm);
	  }
	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaDOWN->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaDOWN->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpaDOWN->SetPointEXhigh(ovo,10.);
	    leadingRivetSherpaDOWN->SetPointEXlow(ovo,10.);
	    leadingRivetSherpaDOWN->SetPointEYhigh(ovo,leadingRivetSherpaDOWN->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaDOWN->SetPointEYlow(ovo,leadingRivetSherpaDOWN->GetErrorYlow(ovo)/dummyNorm);
	  }
	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaPDF1->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaPDF1->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpaPDF1->SetPointEXhigh(ovo,10.);
	    leadingRivetSherpaPDF1->SetPointEXlow(ovo,10.);
	    leadingRivetSherpaPDF1->SetPointEYhigh(ovo,leadingRivetSherpaPDF1->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaPDF1->SetPointEYlow(ovo,leadingRivetSherpaPDF1->GetErrorYlow(ovo)/dummyNorm);
	  }
	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetSherpaPDF2->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetSherpaPDF2->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetSherpaPDF2->SetPointEXhigh(ovo,10.);
	    leadingRivetSherpaPDF2->SetPointEXlow(ovo,10.);
	    leadingRivetSherpaPDF2->SetPointEYhigh(ovo,leadingRivetSherpaPDF2->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetSherpaPDF2->SetPointEYlow(ovo,leadingRivetSherpaPDF2->GetErrorYlow(ovo)/dummyNorm);
	  }
	  Double_t dummyNorm = 0.;
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetMadGraph->GetPoint(ovo,dummyXvar,dummyYvar); 
	    dummyNorm = dummyNorm + dummyYvar;
	  }
	  for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	    leadingRivetMadGraph->GetPoint(ovo,dummyXvar,dummyYvar); 
	    leadingRivetMadGraph->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm); 
	    leadingRivetMadGraph->SetPointEXhigh(ovo,10.);
	    leadingRivetMadGraph->SetPointEXlow(ovo,10.);
	    leadingRivetMadGraph->SetPointEYhigh(ovo,leadingRivetMadGraph->GetErrorYhigh(ovo)/dummyNorm);
	    leadingRivetMadGraph->SetPointEYlow(ovo,leadingRivetMadGraph->GetErrorYlow(ovo)/dummyNorm);
	  }

	  TColor *t = new TColor(996,0.,0.0,1.0,"blu1",0.5);
	  TColor *t = new TColor(995,0.,0.5,1.0,"blu2",0.5);
	  TColor *t = new TColor(994,0.,1.0,1.0,"blu3",0.5);
	  TColor *t = new TColor(993,0.,1.0,0.5.,"blu4",0.5);
	  TColor *t = new TColor(992,0.,1.0,0.0,"blu5",0.5);
	  TColor *t = new TColor(999,1.,0.5,0.0,"arancio1",0.5);

	  //	  leadingRivetSherpaPDF1->SetLineColor(992);
	  leadingRivetSherpaPDF1->SetFillColor(992);
	  leadingRivetSherpaPDF1->Draw("3");

	  //	  leadingRivetSherpaPDF2->SetLineColor(993);
	  leadingRivetSherpaPDF2->SetFillColor(993);
	  leadingRivetSherpaPDF2->Draw("3");

	  //	  leadingRivetSherpaUP->SetLineColor(994);
	  leadingRivetSherpaUP->SetFillColor(994);
	  leadingRivetSherpaUP->Draw("3");

	  //	  leadingRivetSherpaDOWN->SetLineColor(995);
	  leadingRivetSherpaDOWN->SetFillColor(995);
	  leadingRivetSherpaDOWN->Draw("3");

	  //	  leadingRivetSherpa->SetLineColor(996);
	  leadingRivetSherpa->SetFillColor(996);
	  leadingRivetSherpa->Draw("3");

	  //	  leadingRivetMadGraph->SetFillColor(999);
	  leadingRivetMadGraph->SetFillColor(999);
	  leadingRivetMadGraph->Draw("3");

	  leadingSystematics->Draw ("E1SAMES");
	  leading->Draw ("E1SAMES");
	  //-------------------------------------------

	  // Draw the label and save plot:
	  TLatex *latexLabel = CMSPrel (4.890, "", 0.25, 0.4);	// make fancy label
	  latexLabel->Draw ("same");
	  TLegend *legend_d = new TLegend (0.70494, 0.71, 0.931727, 0.93);
	  legend_d->SetFillColor (0);
	  legend_d->SetFillStyle (0);
	  legend_d->SetBorderSize (0);
	  legend_d->AddEntry (leading, "Data w/Stat Uncertainty", "LP");
	  legend_d->AddEntry (leadingSystematics, "Total Uncertainty", "LP");
	  legend_d->AddEntry (leadingRivetSherpa, "Sherpa", "F");
	  legend_d->AddEntry (leadingRivetSherpaUP, "Sherpa (scale-up)", "F");
	  legend_d->AddEntry (leadingRivetSherpaDOWN, "Sherpa (scale-down)", "F");
	  legend_d->AddEntry (leadingRivetSherpaPDF1, "Sherpa (pdf mstw)", "F");
	  legend_d->AddEntry (leadingRivetSherpaPDF2, "Sherpa (pdf nn)", "F");
	  legend_d->AddEntry (leadingRivetMadGraph, "MadGraph", "F");
	  legend_d->Draw ("same");

	  string title1 = s + "DifferentialX" + stringmatch + ".png";
	  cout << title1 << endl;
	  plots->Print (title1.c_str ());
	}
    }
}
