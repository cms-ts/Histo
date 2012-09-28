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
//string s = "/afs/infn.it/ts/user/marone/html/ZJets/articlePlots/";
string s = "/home/schizzi/CMSSW_4_4_2/src/Histo/HistoAnalyzer/macros/plotArticleEle120918" + version + "/";

void
makeArticlePlots ()
{

  setTDRStyle ();

  int whichjet = 1;
  string plotpath = "/gpfs/cms/data/2011/Uncertainties/";
  gStyle->SetOptStat (0);

  //DATA:
  string pathFile="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributions_v2_32ApprovalB.root";

  //RIVET:
  string rivetPathSherpa ="/gpfs/cms/users/candelis/CMSSW_5_2_6/src/GeneratorInterface/RivetInterface/test/test_prod/out.root";
  string rivetPathSherpaUP ="/gpfs/cms/users/candelis/CMSSW_5_2_6/src/GeneratorInterface/RivetInterface/test/test_scaleup/out.root";
  string rivetPathSherpaDOWN ="/gpfs/cms/users/candelis/CMSSW_5_2_6/src/GeneratorInterface/RivetInterface/test/test_scaledown/out.root";
  string rivetPathSherpaPDF1 ="/gpfs/cms/users/candelis/CMSSW_5_2_6/src/GeneratorInterface/RivetInterface/test/test_pdfmstw/out.root";
  string rivetPathSherpaPDF2 ="/gpfs/cms/users/candelis/CMSSW_5_2_6/src/GeneratorInterface/RivetInterface/test/test_pdfnn/out.root";
  string rivetPathMadGraph ="/gpfs/cms/users/dellaric/work/cms/pythiaZ2tune/scaleorig/DYtotal.root";
  string rivetPathMadGraphUP ="/gpfs/cms/users/dellaric/work/cms/pythiaZ2tune/scaleup/DYtotal.root";
  string rivetPathMadGraphDOWN ="/gpfs/cms/users/dellaric/work/cms/pythiaZ2tune/scaledown/DYtotal.root";

  //====================================================================================================
  TFile *histof = TFile::Open (pathFile.c_str ());
  plots = new TCanvas ("plots", "EB", 0, 0, 1200, 800);
  histof->cd ("");
  TDirectory *dir = gDirectory;
  TList *mylist = (TList *) dir->GetListOfKeys ();
  TIter iter (mylist);
  // Use TIter::Next() to get each TObject mom owns.
  TObject *tobj = 0;
  string tmpname;

  plots->cd ();
  int i = 0;			// solo di servizio quando debuggo...
  while ((tobj = iter.Next ()))
    {
      string name = tobj->GetName ();
      string stringmatch;
      string systPathFile;
      string rivet_data;
      string rivet_dataMG;
      string rivet_data_eta;
      string rivet_dataMG_eta;
      string rivet_data_ht;
      string rivet_dataMG_ht;
      string rivet_data_nj="d03_x01_y01";
      string rivet_dataMG_nj="d03-x01-y01";

      if (whichjet == 1)
	{
	  stringmatch = "jReco_leading";
	  systPathFile = plotpath + "jet1PtFinalSyst" + version + ".txt";
	  rivet_data = "d01_x01_y01";
	  rivet_dataMG = "d01-x01-y01";
	  rivet_data_eta   = "d15_x01_y01";
	  rivet_dataMG_eta = "d15-x01-y01";
	  rivet_data_ht    = "d19_x01_y01";
	  rivet_dataMG_ht  = "d19-x01-y01";
	}
      if (whichjet == 2)
	{
	  stringmatch = "jReco_subleading";
	  systPathFile = plotpath + "jet2PtFinalSyst" + version + ".txt";
	  rivet_data = "d02_x01_y01";
	  rivet_dataMG = "d02-x01-y01";
	  rivet_data_eta   = "d16_x01_y01";
	  rivet_dataMG_eta = "d16-x01-y01";
	  rivet_data_ht    = "d20_x01_y01";
	  rivet_dataMG_ht  = "d20-x01-y01";
	}
      if (whichjet == 3)
	{
	  stringmatch = "jReco_subsubleading";
	  systPathFile = plotpath + "jet3PtFinalSyst" + version + ".txt";
	  rivet_data = "d04_x01_y01";
	  rivet_dataMG = "d04-x01-y01";
	  rivet_data_eta   = "d17_x01_y01";
	  rivet_dataMG_eta = "d17-x01-y01";
	  rivet_data_ht    = "d21_x01_y01";
	  rivet_dataMG_ht  = "d21-x01-y01";
	}
      if (whichjet == 4)
	{
	  stringmatch = "jReco_subsubsubleading";
	  systPathFile = plotpath + "jet4PtFinalSyst" + version + ".txt";
	  rivet_data = "d05_x01_y01";
	  rivet_dataMG = "d05-x01-y01";
	  rivet_data_eta   = "d18_x01_y01";
	  rivet_dataMG_eta = "d18-x01-y01";
	  rivet_data_ht    = "d22_x01_y01";
	  rivet_dataMG_ht  = "d22-x01-y01";
	}
      /*
      //Leading Jet Pt
      if (name == stringmatch)
	{
	  cout << "processing histogram->" << name << endl;
	  gPad->SetLogy (1);
	  TH1D *leading;
	  gDirectory->GetObject (name.c_str (), leading);
	  TH1D *leadingSystematics;
	  leadingSystematics = (TH1D *) leading->Clone ("leading");

	  // read from file ---------------------------------------------
	  double dat;
	  ifstream in;
	  cout << "reading ...  " << systPathFile << endl;
	  in.open (systPathFile.c_str ());
	  //int l2 =0;
	  std::vector < double >systTmp;
	  while (1)
	    {
	      in >> dat;
	      if (!in.good ())
		break;
	      systTmp.push_back (dat);
	      //l2++;  
	    }
	  in.close ();
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
	      if (nameRivetMadGraph == rivet_dataMG)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraph << endl;
		  TH1D *leadingRivetMadGraph;
		  gDirectory->GetObject (nameRivetMadGraph.c_str (), leadingRivetMadGraph);
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
		  TH1D *leadingRivetMadGraphUP;
		  gDirectory->GetObject (nameRivetMadGraphUP.c_str (), leadingRivetMadGraphUP);
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
		  TH1D *leadingRivetMadGraphDOWN;
		  gDirectory->GetObject (nameRivetMadGraphDOWN.c_str (), leadingRivetMadGraphDOWN);
		}
	    }
	  //-------------------------------------------------------------

	  leadingSystematics->SetName ("leadingSystematics");
	  if (systTmp.size () != leadingSystematics->GetNbinsX ())
	    cout << "WRONG NUMBER OF BINS" << endl;
	  for (int i = 0; i <= leadingSystematics->GetNbinsX (); i++)
	    {
	      double err =
		sqrt (pow (leading->GetBinError (i + 1), 2) +
		      pow (systTmp[i] *
			   leadingSystematics->GetBinContent (i + 1), 2));
	      leadingSystematics->SetBinError (i + 1, err);
	    }

	  leadingSystematics->Scale(1./leadingSystematics->Integral());
	  leading->Scale(1./leading->Integral());

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
	  leadingSystematics->GetYaxis ()->
	    SetTitle
	    ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d p_{T}");
	  leadingSystematics->GetXaxis ()->SetTitle ("jet p_{T} [GeV/c]");
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
	    cout << dummyYvar/dummyNorm << endl;
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

	  TColor *t = new TColor(996,0.,0.0,1.0,"blu1",0.5);
	  TColor *t = new TColor(995,0.,0.5,1.0,"blu2",0.5);
	  TColor *t = new TColor(994,0.,1.0,1.0,"blu3",0.5);
	  TColor *t = new TColor(993,0.,1.0,0.5.,"blu4",0.5);
	  TColor *t = new TColor(992,0.,1.0,0.0,"blu5",0.5);

	  leadingRivetSherpaPDF1->SetLineColor(992);
	  leadingRivetSherpaPDF1->SetFillColor(992);
	  //	  leadingRivetSherpaPDF1->SetFillStyle(3004);
	  leadingRivetSherpaPDF1->Draw("3");

	  leadingRivetSherpaPDF2->SetLineColor(993);
	  leadingRivetSherpaPDF2->SetFillColor(993);
	  //	  leadingRivetSherpaPDF2->SetFillStyle(3005);
	  leadingRivetSherpaPDF2->Draw("3");

	  leadingRivetSherpaUP->SetLineColor(994);
	  leadingRivetSherpaUP->SetFillColor(994);
	  //	  leadingRivetSherpaUP->SetFillStyle(1001);
	  leadingRivetSherpaUP->Draw("3");

	  leadingRivetSherpaDOWN->SetLineColor(995);
	  leadingRivetSherpaDOWN->SetFillColor(995);
	  //	  leadingRivetSherpaDOWN->SetFillStyle(1001);
	  leadingRivetSherpaDOWN->Draw("3");

	  leadingRivetSherpa->SetLineColor(996);
	  leadingRivetSherpa->SetFillColor(996);
	  //	  leadingRivetSherpa->SetFillStyle(1001);
	  leadingRivetSherpa->Draw("3");

	  TColor *t = new TColor(999,1.,0.5,0.0,"arancio1",0.5);
	  TColor *t = new TColor(998,1.,1.0,0.0,"arancio2",0.5);
	  TColor *t = new TColor(997,1.,0.0,0.5,"arancio3",0.5);

	  leadingRivetMadGraph->Sumw2();
	  leadingRivetMadGraph->Scale(1.0/leadingRivetMadGraph->Integral());
	  leadingRivetMadGraph->SetLineColor(999);
	  leadingRivetMadGraph->SetLineWidth(0);
	  leadingRivetMadGraph->SetFillColor(999);
	  leadingRivetMadGraph->Draw("E3SAMES");

	  leadingRivetMadGraphUP->Sumw2();
	  leadingRivetMadGraphUP->Scale(1.0/leadingRivetMadGraphUP->Integral());
	  leadingRivetMadGraphUP->SetLineColor(997);
	  leadingRivetMadGraphUP->SetLineWidth(0);
	  leadingRivetMadGraphUP->SetFillColor(997);
	  leadingRivetMadGraphUP->Draw("E3SAMES");

	  leadingRivetMadGraphDOWN->Sumw2();
	  leadingRivetMadGraphDOWN->Scale(1.0/leadingRivetMadGraphDOWN->Integral());
	  leadingRivetMadGraphDOWN->SetLineColor(998);
	  leadingRivetMadGraphDOWN->SetLineWidth(0);
	  leadingRivetMadGraphDOWN->SetFillColor(998);
	  leadingRivetMadGraphDOWN->Draw("E3SAMES");

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
	  legend_d->AddEntry (leadingRivetMadGraphUP, "MadGraph (scale-up)", "F");
	  legend_d->AddEntry (leadingRivetMadGraphDOWN, "MadGraph (scale-down)", "F");
	  legend_d->Draw ("same");

	  string title1 = s + "DifferentialX" + stringmatch + ".png";
	  cout << title1 << endl;
	  plots->Print (title1.c_str ());
	}
      */

      // Jet Multiplicity
      if (name == "JetMultiplicityUnfolded")
	{
	  gPad->SetLogy (1);
	  TH1D *leading;
	  gDirectory->GetObject (name.c_str (), leading);
	  TH1D *leadingSystematics;
	  leadingSystematics = (TH1D *) leading->Clone ("leading");
	  systPathFile = plotpath + "jetMultFinalSyst" + version + ".txt";

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
	      if (nameRivetSherpa == rivet_data_nj)
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
	      if (nameRivetSherpaUP == rivet_data_nj)
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
	      if (nameRivetSherpaDOWN == rivet_data_nj)
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
	      if (nameRivetSherpaPDF1 == rivet_data_nj)
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
	      if (nameRivetSherpaPDF2 == rivet_data_nj)
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
	      if (nameRivetMadGraph == rivet_dataMG_nj)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraph << endl;
		  TH1D *leadingRivetMadGraph;
		  gDirectory->GetObject (nameRivetMadGraph.c_str (), leadingRivetMadGraph);
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
	      if (nameRivetMadGraphUP == rivet_dataMG_nj)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraphUP << endl;
		  TH1D *leadingRivetMadGraphUP;
		  gDirectory->GetObject (nameRivetMadGraphUP.c_str (), leadingRivetMadGraphUP);
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
	      if (nameRivetMadGraphDOWN == rivet_dataMG_nj)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraphDOWN << endl;
		  TH1D *leadingRivetMadGraphDOWN;
		  gDirectory->GetObject (nameRivetMadGraphDOWN.c_str (), leadingRivetMadGraphDOWN);
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
	  leadingSystematics->GetYaxis ()->
	    SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d N");
	  leadingSystematics->GetXaxis ()->SetTitle ("jet multiplicity");
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

	  TColor *t = new TColor(996,0.,0.0,1.0,"blu1",0.5);
	  TColor *t = new TColor(995,0.,0.5,1.0,"blu2",0.5);
	  TColor *t = new TColor(994,0.,1.0,1.0,"blu3",0.5);
	  TColor *t = new TColor(993,0.,1.0,0.5.,"blu4",0.5);
	  TColor *t = new TColor(992,0.,1.0,0.0,"blu5",0.5);

	  leadingRivetSherpaPDF1->SetLineColor(992);
	  leadingRivetSherpaPDF1->SetFillColor(992);
	  //	  leadingRivetSherpaPDF1->SetFillStyle(3004);
	  leadingRivetSherpaPDF1->Draw("3");

	  leadingRivetSherpaPDF2->SetLineColor(993);
	  leadingRivetSherpaPDF2->SetFillColor(993);
	  //	  leadingRivetSherpaPDF2->SetFillStyle(3005);
	  leadingRivetSherpaPDF2->Draw("3");

	  leadingRivetSherpaUP->SetLineColor(994);
	  leadingRivetSherpaUP->SetFillColor(994);
	  //	  leadingRivetSherpaUP->SetFillStyle(1001);
	  leadingRivetSherpaUP->Draw("3");

	  leadingRivetSherpaDOWN->SetLineColor(995);
	  leadingRivetSherpaDOWN->SetFillColor(995);
	  //	  leadingRivetSherpaDOWN->SetFillStyle(1001);
	  leadingRivetSherpaDOWN->Draw("3");

	  leadingRivetSherpa->SetLineColor(996);
	  leadingRivetSherpa->SetFillColor(996);
	  //	  leadingRivetSherpa->SetFillStyle(1001);
	  leadingRivetSherpa->Draw("3");

	  TColor *t = new TColor(999,1.,0.5,0.0,"arancio1",0.5);
	  TColor *t = new TColor(998,1.,1.0,0.0,"arancio2",0.5);
	  TColor *t = new TColor(997,1.,0.0,0.5,"arancio3",0.5);

	  leadingRivetMadGraph->Sumw2();
	  leadingRivetMadGraph->Scale(1.0/leadingRivetMadGraph->Integral());
	  leadingRivetMadGraph->SetLineColor(999);
	  leadingRivetMadGraph->SetLineWidth(0);
	  leadingRivetMadGraph->SetFillColor(999);
	  leadingRivetMadGraph->Draw("E3SAMES");

	  leadingRivetMadGraphUP->Sumw2();
	  leadingRivetMadGraphUP->Scale(1.0/leadingRivetMadGraphUP->Integral());
	  leadingRivetMadGraphUP->SetLineColor(997);
	  leadingRivetMadGraphUP->SetLineWidth(0);
	  leadingRivetMadGraphUP->SetFillColor(997);
	  leadingRivetMadGraphUP->Draw("E3SAMES");

	  leadingRivetMadGraphDOWN->Sumw2();
	  leadingRivetMadGraphDOWN->Scale(1.0/leadingRivetMadGraphDOWN->Integral());
	  leadingRivetMadGraphDOWN->SetLineColor(998);
	  leadingRivetMadGraphDOWN->SetLineWidth(0);
	  leadingRivetMadGraphDOWN->SetFillColor(998);
	  leadingRivetMadGraphDOWN->Draw("E3SAMES");

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
	  legend_d->AddEntry (leadingRivetMadGraphUP, "MadGraph (scale-up)", "F");
	  legend_d->AddEntry (leadingRivetMadGraphDOWN, "MadGraph (scale-down)", "F");
	  legend_d->Draw ("same");

	  string title1 = s + "DifferentialXSJetMultiplicity.png";
	  cout << title1 << endl;
	  plots->Print (title1.c_str ());
	}

      /*
      //////////////////////
      /// Eta
      ////////////////////

      if (whichjet == 1)
	{
	  stringmatch = "jReco_leadingeta";
	  systPathFile = plotpath + "jet1EtaFinalSyst" + version + ".txt";
	}
      if (whichjet == 2)
	{
	  stringmatch = "jReco_subleadingeta";
	  systPathFile = plotpath + "jet2EtaFinalSyst" + version + ".txt";
	}
      if (whichjet == 3)
	{
	  stringmatch = "jReco_subsubleadingeta";
	  systPathFile = plotpath + "jet3EtaFinalSyst" + version + ".txt";
	}
      if (whichjet == 4)
	{
	  stringmatch = "jReco_subsubsubleadingeta";
	  systPathFile = plotpath + "jet4EtaFinalSyst" + version + ".txt";
	}
      //stringmatch= "ciccio";
      if (name == stringmatch)
	{
	  cout << "processing histogram->" << name << endl;
	  gPad->SetLogy (1);
	  //gPad->SetLogy(0);   // remove log scale
	  TH1D *leading;
	  gDirectory->GetObject (name.c_str (), leading);
	  TH1D *leadingSystematics;
	  leadingSystematics = (TH1D *) leading->Clone ("leading");

//
//   COMMENTED ONLY FOR NOW  **********************************
//
	  //  // read from file --------------------------------------------
	  double dat;
	  ifstream in2;
	  cout << "reading ...  " << systPathFile << endl;
	  in2.open (systPathFile.c_str ());
	  //int l2 =0;
	  std::vector < double >systTmpEta;
	  while (1)
	    {
	      in2 >> dat;
	      if (!in2.good ())
		break;
	      systTmpEta.push_back (dat);
	      //l2++;  
	    }
	  in2.close ();
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
	      if (nameRivetSherpa == rivet_data_eta)
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
	      if (nameRivetSherpaUP == rivet_data_eta)
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
	      if (nameRivetSherpaDOWN == rivet_data_eta)
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
	      if (nameRivetSherpaPDF1 == rivet_data_eta)
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
	      if (nameRivetSherpaPDF2 == rivet_data_eta)
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
	      if (nameRivetMadGraph == rivet_dataMG_eta)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraph << endl;
		  TH1D *leadingRivetMadGraph;
		  gDirectory->GetObject (nameRivetMadGraph.c_str (), leadingRivetMadGraph);
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
	      if (nameRivetMadGraphUP == rivet_dataMG_eta)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraphUP << endl;
		  TH1D *leadingRivetMadGraphUP;
		  gDirectory->GetObject (nameRivetMadGraphUP.c_str (), leadingRivetMadGraphUP);
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
	      if (nameRivetMadGraphDOWN == rivet_dataMG_eta)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraphDOWN << endl;
		  TH1D *leadingRivetMadGraphDOWN;
		  gDirectory->GetObject (nameRivetMadGraphDOWN.c_str (), leadingRivetMadGraphDOWN);
		}
	    }
	  //-------------------------------------------------------------

	  leadingSystematics->SetName ("leadingSystematics");
	  if (systTmpEta.size () != leadingSystematics->GetNbinsX ())
	    cout << "WRONG NUMBER OF BINS" << endl;
	  for (int i = 0; i <= leadingSystematics->GetNbinsX (); i++)
	    {
	      double err =
		sqrt (pow (leading->GetBinError (i + 1), 2) +
		      pow (systTmpEta[i] *
			   leadingSystematics->GetBinContent (i + 1), 2));
	      leadingSystematics->SetBinError (i + 1, err);
	    }

	  leadingSystematics->Scale(1./leadingSystematics->Integral());
	  leading->Scale(1./leading->Integral());
	  
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
	  leadingSystematics->GetYaxis ()->
	    SetTitle
	    ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d #eta");
	  leadingSystematics->GetXaxis ()->SetTitle ("jet #eta");
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

	  TColor *t = new TColor(996,0.,0.0,1.0,"blu1",0.5);
	  TColor *t = new TColor(995,0.,0.5,1.0,"blu2",0.5);
	  TColor *t = new TColor(994,0.,1.0,1.0,"blu3",0.5);
	  TColor *t = new TColor(993,0.,1.0,0.5.,"blu4",0.5);
	  TColor *t = new TColor(992,0.,1.0,0.0,"blu5",0.5);

	  leadingRivetSherpaPDF1->SetLineColor(992);
	  leadingRivetSherpaPDF1->SetFillColor(992);
	  //	  leadingRivetSherpaPDF1->SetFillStyle(3004);
	  leadingRivetSherpaPDF1->Draw("3");

	  leadingRivetSherpaPDF2->SetLineColor(993);
	  leadingRivetSherpaPDF2->SetFillColor(993);
	  //	  leadingRivetSherpaPDF2->SetFillStyle(3005);
	  leadingRivetSherpaPDF2->Draw("3");

	  leadingRivetSherpaUP->SetLineColor(994);
	  leadingRivetSherpaUP->SetFillColor(994);
	  //	  leadingRivetSherpaUP->SetFillStyle(1001);
	  leadingRivetSherpaUP->Draw("3");

	  leadingRivetSherpaDOWN->SetLineColor(995);
	  leadingRivetSherpaDOWN->SetFillColor(995);
	  //	  leadingRivetSherpaDOWN->SetFillStyle(1001);
	  leadingRivetSherpaDOWN->Draw("3");

	  leadingRivetSherpa->SetLineColor(996);
	  leadingRivetSherpa->SetFillColor(996);
	  //	  leadingRivetSherpa->SetFillStyle(1001);
	  leadingRivetSherpa->Draw("3");

	  TColor *t = new TColor(999,1.,0.5,0.0,"arancio1",0.5);
	  TColor *t = new TColor(998,1.,1.0,0.0,"arancio2",0.5);
	  TColor *t = new TColor(997,1.,0.0,0.5,"arancio3",0.5);

	  leadingRivetMadGraph->Sumw2();
	  leadingRivetMadGraph->Scale(1.0/leadingRivetMadGraph->Integral());
	  leadingRivetMadGraph->SetLineColor(999);
	  leadingRivetMadGraph->SetLineWidth(0);
	  leadingRivetMadGraph->SetFillColor(999);
	  leadingRivetMadGraph->Draw("E3SAMES");

	  leadingRivetMadGraphUP->Sumw2();
	  leadingRivetMadGraphUP->Scale(1.0/leadingRivetMadGraphUP->Integral());
	  leadingRivetMadGraphUP->SetLineColor(997);
	  leadingRivetMadGraphUP->SetLineWidth(0);
	  leadingRivetMadGraphUP->SetFillColor(997);
	  leadingRivetMadGraphUP->Draw("E3SAMES");

	  leadingRivetMadGraphDOWN->Sumw2();
	  leadingRivetMadGraphDOWN->Scale(1.0/leadingRivetMadGraphDOWN->Integral());
	  leadingRivetMadGraphDOWN->SetLineColor(998);
	  leadingRivetMadGraphDOWN->SetLineWidth(0);
	  leadingRivetMadGraphDOWN->SetFillColor(998);
	  leadingRivetMadGraphDOWN->Draw("E3SAMES");

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
	  legend_d->AddEntry (leadingRivetMadGraphUP, "MadGraph (scale-up)", "F");
	  legend_d->AddEntry (leadingRivetMadGraphDOWN, "MadGraph (scale-down)", "F");
	  legend_d->Draw ("same");

	  string title1 = s + "DifferentialXSEta" + stringmatch + ".png";
	  cout << title1 << endl;
	  plots->Print (title1.c_str ());
	}
      */
      /*
      //////////////////////
      /// HT
      ////////////////////

      if (whichjet == 1)
	{
	  stringmatch = "HReco_leading";
	  systPathFile = plotpath + "jet1HtFinalSyst" + version + ".txt";
	}
      if (whichjet == 2)
	{
	  stringmatch = "HReco_subleading";
	  systPathFile = plotpath + "jet2HtFinalSyst" + version + ".txt";
	}
      if (whichjet == 3)
	{
	  stringmatch = "HReco_subsubleading";
	  systPathFile = plotpath + "jet3HtFinalSyst" + version + ".txt";
	}
      if (whichjet == 4)
	{
	  stringmatch = "HReco_subsubsubleading";
	  systPathFile = plotpath + "jet4HtFinalSyst" + version + ".txt";
	}
      //stringmatch= "ciccio";
      if (name == stringmatch)
	{
	  cout << "processing histogram->" << name << endl;
	  gPad->SetLogy (1);
	  TH1D *leading;
	  gDirectory->GetObject (name.c_str (), leading);
	  TH1D *leadingSystematics;
	  leadingSystematics = (TH1D *) leading->Clone ("leading");

//
//   COMMENTED ONLY FOR NOW  **********************************
//
	  //  // read from file --------------------------------------------
	  double dat;
	  ifstream in2;
	  cout << "reading ...  " << systPathFile << endl;
	  in2.open (systPathFile.c_str ());
	  //int l2 =0;
	  std::vector < double >systTmpHt;
	  while (1)
	    {
	      in2 >> dat;
	      if (!in2.good ())
		break;
	      systTmpHt.push_back (dat);
	      //l2++;  
	    }
	  in2.close ();


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
	      if (nameRivetSherpa == rivet_data_ht)
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
	      if (nameRivetSherpaUP == rivet_data_ht)
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
	      if (nameRivetSherpaDOWN == rivet_data_ht)
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
	      if (nameRivetSherpaPDF1 == rivet_data_ht)
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
	      if (nameRivetSherpaPDF2 == rivet_data_ht)
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
	      if (nameRivetMadGraph == rivet_dataMG_ht)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraph << endl;
		  TH1D *leadingRivetMadGraph;
		  gDirectory->GetObject (nameRivetMadGraph.c_str (), leadingRivetMadGraph);
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
	      if (nameRivetMadGraphUP == rivet_dataMG_ht)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraphUP << endl;
		  TH1D *leadingRivetMadGraphUP;
		  gDirectory->GetObject (nameRivetMadGraphUP.c_str (), leadingRivetMadGraphUP);
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
	      if (nameRivetMadGraphDOWN == rivet_dataMG_ht)
		{
		  cout << "Getting rivet data->" << nameRivetMadGraphDOWN << endl;
		  TH1D *leadingRivetMadGraphDOWN;
		  gDirectory->GetObject (nameRivetMadGraphDOWN.c_str (), leadingRivetMadGraphDOWN);
		}
	    }
	  //-------------------------------------------------------------

	  // ------------------------------------------------------------
	  leadingSystematics->SetName ("leadingSystematics");
	  if (systTmpHt.size () != leadingSystematics->GetNbinsX ())
	    cout << "WRONG NUMBER OF BINS" << endl;
	  for (int i = 0; i <= leadingSystematics->GetNbinsX (); i++)
	    {
	      double err =
		sqrt (pow (leading->GetBinError (i + 1), 2) +
		      pow (systTmpHt[i] *
			   leadingSystematics->GetBinContent (i + 1), 2));
	      leadingSystematics->SetBinError (i + 1, err);
	    }

	  leadingSystematics->Scale(1./leadingSystematics->Integral());
	  leading->Scale(1./leading->Integral());
	  
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
	  leadingSystematics->GetYaxis ()->
	    SetTitle
	    ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d H_{T}");
	  leadingSystematics->GetXaxis ()->SetTitle ("jet H_{T} [GeV/c]");
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
	    cout << "x = " << dummyXvar << "y = " << dummyYvar/dummyNorm << endl;
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

	  TColor *t = new TColor(996,0.,0.0,1.0,"blu1",0.5);
	  TColor *t = new TColor(995,0.,0.5,1.0,"blu2",0.5);
	  TColor *t = new TColor(994,0.,1.0,1.0,"blu3",0.5);
	  TColor *t = new TColor(993,0.,1.0,0.5.,"blu4",0.5);
	  TColor *t = new TColor(992,0.,1.0,0.0,"blu5",0.5);

	  leadingRivetSherpaPDF1->SetLineColor(992);
	  leadingRivetSherpaPDF1->SetFillColor(992);
	  //	  leadingRivetSherpaPDF1->SetFillStyle(3004);
	  leadingRivetSherpaPDF1->Draw("3");

	  leadingRivetSherpaPDF2->SetLineColor(993);
	  leadingRivetSherpaPDF2->SetFillColor(993);
	  //	  leadingRivetSherpaPDF2->SetFillStyle(3005);
	  leadingRivetSherpaPDF2->Draw("3");

	  leadingRivetSherpaUP->SetLineColor(994);
	  leadingRivetSherpaUP->SetFillColor(994);
	  //	  leadingRivetSherpaUP->SetFillStyle(1001);
	  leadingRivetSherpaUP->Draw("3");

	  leadingRivetSherpaDOWN->SetLineColor(995);
	  leadingRivetSherpaDOWN->SetFillColor(995);
	  //	  leadingRivetSherpaDOWN->SetFillStyle(1001);
	  leadingRivetSherpaDOWN->Draw("3");

	  leadingRivetSherpa->SetLineColor(996);
	  leadingRivetSherpa->SetFillColor(996);
	  //	  leadingRivetSherpa->SetFillStyle(1001);
	  leadingRivetSherpa->Draw("3");

	  TColor *t = new TColor(999,1.,0.5,0.0,"arancio1",0.5);
	  TColor *t = new TColor(998,1.,1.0,0.0,"arancio2",0.5);
	  TColor *t = new TColor(997,1.,0.0,0.5,"arancio3",0.5);

	  leadingRivetMadGraph->Sumw2();
	  leadingRivetMadGraph->Scale(1.0/leadingRivetMadGraph->Integral());
	  leadingRivetMadGraph->SetLineColor(999);
	  leadingRivetMadGraph->SetLineWidth(0);
	  leadingRivetMadGraph->SetFillColor(999);
	  leadingRivetMadGraph->Draw("E3SAMES");

	  leadingRivetMadGraphUP->Sumw2();
	  leadingRivetMadGraphUP->Scale(1.0/leadingRivetMadGraphUP->Integral());
	  leadingRivetMadGraphUP->SetLineColor(997);
	  leadingRivetMadGraphUP->SetLineWidth(0);
	  leadingRivetMadGraphUP->SetFillColor(997);
	  leadingRivetMadGraphUP->Draw("E3SAMES");

	  leadingRivetMadGraphDOWN->Sumw2();
	  leadingRivetMadGraphDOWN->Scale(1.0/leadingRivetMadGraphDOWN->Integral());
	  leadingRivetMadGraphDOWN->SetLineColor(998);
	  leadingRivetMadGraphDOWN->SetLineWidth(0);
	  leadingRivetMadGraphDOWN->SetFillColor(998);
	  leadingRivetMadGraphDOWN->Draw("E3SAMES");

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
	  legend_d->AddEntry (leadingRivetMadGraphUP, "MadGraph (scale-up)", "F");
	  legend_d->AddEntry (leadingRivetMadGraphDOWN, "MadGraph (scale-down)", "F");
	  legend_d->Draw ("same");

	  string title1 = s + "DifferentialXSHt" + stringmatch + ".png";
	  cout << title1 << endl;
	  plots->Print (title1.c_str ());
	}
      */
    }
}
