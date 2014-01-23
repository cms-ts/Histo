#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include "Unfolding/MakePlotLumiLabel.C"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TCut.h"
#include "TLatex.h"
#include "tdrStyle.C"
#include "TObject.h"
#include "TTree.h"
#include "TH2.h"
#include "THStack.h"
#include "TColor.h"
#include <TROOT.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string.h>

void
makePreApprovalPlots (int whichobservable, int whichjet, int whichlepton)
{

  //setTDRStyle ();
  gStyle->SetErrorX(0);
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);

  bool absoluteNormalization = true;
  int lepton = whichlepton; //1 -> electron,  2-> muon , 3 -> combined reults!
  bool addLumiUncertainties = true;
  double lumiError = 0.025;
  int use_case = whichobservable;
  int whichjet = whichjet;
  string version = "_v2_32";
  bool incMultiplicity = false;


  //string s                = "/afs/infn.it/ts/user/marone/html/ZJets/articlePlots/Ele/";
  //if (lepton==2) string s = "/afs/infn.it/ts/user/marone/html/ZJets/articlePlots/Mu/";

  string s                = "/tmp/";
  if (lepton==2) string s = "/tmp/";


  if (lepton==3) string s = "/tmp/";
  //  string s                = "/afs/infn.it/ts/user/schizzi/html/NewSherpa_test/ele/";
  //  if (lepton==2) string s = "/afs/infn.it/ts/user/schizzi/html/NewSherpa_test/muo/";
  //  if (lepton==3) string s = "/afs/infn.it/ts/user/schizzi/html/NewSherpa_test/combined/";
  //  string s                = "/afs/infn.it/ts/user/schizzi/html/approval/ele/";
  //  if (lepton==2) string s = "/afs/infn.it/ts/user/schizzi/html/approval/muo/";
  //  if (lepton==3) string s = "/afs/infn.it/ts/user/schizzi/html/approval/combined/";

  string           plotpath = "/gpfs/cms/users/schizzi/Systematics/ele/";
  if (lepton == 2) plotpath = "/gpfs/cms/users/schizzi/Systematics/muo/";
  if (lepton == 3) plotpath = "/gpfs/cms/users/schizzi/Systematics/combination/";

  gStyle->SetOptStat (0);

  TCanvas *plots = new TCanvas ("plots", "EB", 200, 100, 600, 800);

  //DATA:
  string           pathFile ="/gpfs/cms/data/2011/Unfolding/JERPatch2.root";
  if (lepton == 2) pathFile ="/gpfs/cms/data/2011/Unfolding/JERPatch2Up.root";
  if (lepton == 3) pathFile ="/gpfs/cms/data/2011/Unfolding/JERPatch2Down.root";
  
  //RIVET:
  string rivetPthSherpa   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";
  //  string rivetPathSherpa   ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01_7TeV_sherpa/out.root"; // new Sherpa by Fabio
  string rivetPathMadGraph ="/gpfs/cms/users/candelis/Rivet/madgraph_lhe/test_full2/merged.root";
  //string rivetPathMadGraph ="/gpfs/cms/data/2011/Rivet/madgraph_lhe/merged.root";
  //  string rivetPathMadGraph ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
  string rivetPathPowheg    ="/gpfs/cms/users/candelis/Rivet/powheg/test_ee/out.root";

  if (lepton == 2){
    rivetPathSherpa       ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod_mu/out.root";
    //    rivetPathSherpa       ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01_7TeV_sherpa/out.root"; // new Sherpa by Fabio
    rivetPathMadGraph     ="/gpfs/cms/users/candelis/Rivet/madgraph_lhe/test_full2/merged.root";
    //rivetPathMadGraph ="/gpfs/cms/data/2011/Rivet/madgraph_lhe/merged.root";
    //    rivetPathMadGraph     ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
    rivetPathPowheg        ="/gpfs/cms/users/candelis/Rivet/powheg/test_mm/out.root";
  }

  rivetPathPowheg=rivetPathMadGraph;
  rivetPathSherpa=rivetPathMadGraph;
  if (lepton == 3){
    rivetPathSherpa       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_central.root";
    //    rivetPathSherpa       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_Unweighted_central.root"; // new Sherpa by Fabio
    rivetPathMadGraph     ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_central.root";
    rivetPathPowheg     ="/gpfs/cms/users/schizzi/rivet/combination/Powheg_central.root";
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
	cout << "reading ...  " << systPathFile << endl;
	inM.open (systPathFile.c_str ());
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
	  }
	inM.close ();
	// ------------------------------------------------------------

	// Get RIVET data: --------------------------------------------

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
		cout << "Getting rivet data->" << nameRivetPowheg << endl;
		TGraphAsymmErrors *leadingRivetPowheg;
		gDirectory->GetObject (nameRivetPowheg.c_str (), leadingRivetPowheg);
		TGraphAsymmErrors *leadingRatioPowheg;
		leadingRatioPowheg = (TGraphAsymmErrors *) leadingRivetPowheg->Clone ("");
	      }
	  }

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

	//	// New Sherpa modification:
	//	TFile *histoRivetSherpa = TFile::Open (rivetPathSherpa.c_str ());
	//	histoRivetSherpa->cd ("");
	//	TDirectory *dirRivetSherpa = gDirectory;
	//	TList *mylistRivetSherpa = (TList *) dirRivetSherpa->GetListOfKeys ();
	//	TIter iterRivetSherpa (mylistRivetSherpa);
	//	TObject *tobjRivetSherpa = 0;
	//	while ((tobjRivetSherpa = iterRivetSherpa.Next ()))
	//	  {
	//	    string nameRivetSherpa = tobjRivetSherpa->GetName ();
	//	    if (nameRivetSherpa == rivet_dataMG)
	//	      {
	//		cout << "Getting rivet data->" << nameRivetSherpa << endl;
	//		TH1F *leadingRivetSherpa_TH1;
	//		gDirectory->GetObject (nameRivetSherpa.c_str (), leadingRivetSherpa_TH1);
	//		int nshbins = leadingRivetSherpa_TH1->GetNbinsX();
	//		TGraphAsymmErrors *leadingRivetSherpa;
	//		leadingRivetSherpa = (TGraphAsymmErrors *) leadingRivetPowheg->Clone ("");
	//		for (int n=0;n<nshbins;n++) {
	//		  leadingRivetSherpa->SetPoint(n,leadingRivetSherpa_TH1->GetBinCenter(n+1),leadingRivetSherpa_TH1->GetBinContent(n+1));
	//		  //leadingRivetSherpa->SetPointEXhigh(n,0.0);
	//		  //leadingRivetSherpa->SetPointEXlow(n,0.0);
	//		  leadingRivetSherpa->SetPointEYhigh(n,leadingRivetSherpa_TH1->GetBinError(n));
	//		  leadingRivetSherpa->SetPointEYlow(n,leadingRivetSherpa_TH1->GetBinError(n));
	//		}
	//		TGraphAsymmErrors *leadingRatioSherpa;
	//		leadingRatioSherpa = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
	//	      }
	//	  }

	//	TFile *histoRivetMadGraph = TFile::Open (rivetPathMadGraph.c_str ());
	//	histoRivetMadGraph->cd ("");
	//	TDirectory *dirRivetMadGraph = gDirectory;
	//	TList *mylistRivetMadGraph = (TList *) dirRivetMadGraph->GetListOfKeys ();
	//	TIter iterRivetMadGraph (mylistRivetMadGraph);
	//	TObject *tobjRivetMadGraph = 0;
	//	while ((tobjRivetMadGraph = iterRivetMadGraph.Next ()))
	//	  {
	//	    string nameRivetMadGraph = tobjRivetMadGraph->GetName ();
	//	    if (nameRivetMadGraph == rivet_dataMG)
	//	      {
	//		cout << "Getting rivet data->" << nameRivetMadGraph << endl;
	//		TH1D *leadingRivetMadGraph_TH1;
	//		gDirectory->GetObject (nameRivetMadGraph.c_str (), leadingRivetMadGraph_TH1);
	//		int nthbins = leadingRivetMadGraph_TH1->GetNbinsX();
	//		TGraphAsymmErrors *leadingRivetMadGraph;
	//		leadingRivetMadGraph = (TGraphAsymmErrors *) leadingRivetSherpa->Clone ("");
	//		for (int n=0;n<nthbins;n++) {
	//		  leadingRivetMadGraph->SetPoint(n,leadingRivetMadGraph_TH1->GetBinCenter(n+1),leadingRivetMadGraph_TH1->GetBinContent(n+1));
	//		  //leadingRivetMadGraph->SetPointEXhigh(n,0.0);
	//		  //leadingRivetMadGraph->SetPointEXlow(n,0.0);
	//		  leadingRivetMadGraph->SetPointEYhigh(n,leadingRivetMadGraph_TH1->GetBinError(n));
	//		  leadingRivetMadGraph->SetPointEYlow(n,leadingRivetMadGraph_TH1->GetBinError(n));
	//		}
	//		TGraphAsymmErrors *leadingRatioMadGraph;
	//		leadingRatioMadGraph = (TGraphAsymmErrors *) leadingRivetMadGraph->Clone ("");
	//	      }
	//	  }

	// Madgraph vecchio inclusivo con i cazzo di T alla sburra di cherubino addolcita col miele
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
	cout<<"data integral is->"<<leading->Integral()<<" pb"<<endl;

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
	leadingSystematics->SetLineColor (kRed+1);
	leadingSystematics->SetMarkerStyle (20);
	leadingSystematics->SetFillColor (kRed+1);
	leadingSystematics->SetMarkerColor (kRed+1);

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

	/////////////////////////

	// Sherpa:

	Double_t dummyXvar=0.;
	Double_t dummyYvar=0.;
	Int_t nRivetPoints = 0;
	Double_t dummyNorm = 0.;
	nRivetPoints = leadingRivetSherpa->GetN();
	if (nRivetPoints != leadingSystematics->GetNbinsX ()) {cout << "Different number of bins wrt RIVET... quitting" << endl; return 0;}

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpa->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetSherpa->GetPoint(ovo,dummyXvar,dummyYvar); 

	  if (absoluteNormalization) {
	    if (lepton ==1) dummyNorm= 0.155390 *(1000000.0/906.826)*(906.826*3/3048);   
	    if (lepton ==2) dummyNorm= 0.155456 *(1000000.0/907.485)*(907.485*3/3048);
	    if (lepton ==3) dummyNorm= 0.155390 *(1000000.0/906.826)*(906.826*3/3048) + 0.155456 *(1000000.0/907.485)*(907.485*3/3048); 
	    //	    dummyNorm= (473000/2165.19)/2; //New Sherpa by Fabio Unweighted
	    //	    if (lepton ==3) dummyNorm = dummyNorm*2; // New Sherpa by Fabio
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpa->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	  leadingRivetSherpa->SetPointEYhigh(ovo,leadingRivetSherpa->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetSherpa->SetPointEYlow(ovo,leadingRivetSherpa->GetErrorYlow(ovo)/dummyNorm);

	  leadingRatioSherpa->SetPoint(ovo,dummyXvar,1.0);
	  leadingRatioSherpa->SetPointEYhigh(ovo,leadingRivetSherpa->GetErrorYhigh(ovo)*dummyNorm/dummyYvar);
	  leadingRatioSherpa->SetPointEYlow(ovo,leadingRivetSherpa->GetErrorYlow(ovo)*dummyNorm/dummyYvar);
	    
	  leadingRatio->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	  leadingRatioSystematics->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatioSystematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	}

	/////////////////////////

	// Powheg:

	Double_t dummyXvar=0.;
	Double_t dummyYvar=0.;
	Int_t nRivetPoints = 0;
	Double_t dummyNorm = 0.;
	nRivetPoints = leadingRivetPowheg->GetN();
	if (nRivetPoints != leadingSystematics->GetNbinsX ()) {cout << "Different number of bins wrt RIVET... quitting" << endl; return 0;}

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowheg->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetPowheg->GetPoint(ovo,dummyXvar,dummyYvar); 

	  if (absoluteNormalization) {
	    if (lepton ==1) dummyNorm= (4602659.0/276.761);
	    if (lepton ==2) dummyNorm= (5719233.0/276.603);
	    if (lepton ==3) dummyNorm= (4602659.0/276.761) + (5719233.0/276.603);
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetPowheg->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	  leadingRivetPowheg->SetPointEYhigh(ovo,leadingRivetPowheg->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetPowheg->SetPointEYlow(ovo,leadingRivetPowheg->GetErrorYlow(ovo)/dummyNorm);

	  leadingRatioPowheg->SetPoint(ovo,dummyXvar,1.0);
	  leadingRatioPowheg->SetPointEYhigh(ovo,leadingRivetPowheg->GetErrorYhigh(ovo)*dummyNorm/dummyYvar);
	  leadingRatioPowheg->SetPointEYlow(ovo,leadingRivetPowheg->GetErrorYlow(ovo)*dummyNorm/dummyYvar);
	    
	  leadingRatio3->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio3->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	  leadingRatio3Systematics->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio3Systematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	}

	/////////////////////////

	// Madgraph:

	Double_t dummyNorm = 0.;

	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  leadingRivetMadGraph->GetPoint(ovo,dummyXvar,dummyYvar); 
	  dummyNorm = dummyNorm + dummyYvar;
	}
	for (Int_t ovo=0;ovo<nRivetPoints;ovo++) {
	  if (absoluteNormalization) {
	    //	    dummyNorm= 2.0 * 0.000000001*( (1680.67)/3048.0);
	    dummyNorm= (24492754/3048)*3./2.; // vecchio madgraph caccolino
	    if (lepton ==3) dummyNorm = dummyNorm*2;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1));
	  }

	  leadingRivetMadGraph->GetPoint(ovo,dummyXvar,dummyYvar); 

	  leadingRivetMadGraph->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	  if (use_case ==1) cout << "MERDA: " << dummyYvar/dummyNorm << endl;
	  leadingRivetMadGraph->SetPointEYhigh(ovo,leadingRivetMadGraph->GetErrorYhigh(ovo)/dummyNorm);
	  leadingRivetMadGraph->SetPointEYlow(ovo,leadingRivetMadGraph->GetErrorYlow(ovo)/dummyNorm);

	  leadingRatioMadGraph->SetPoint(ovo,dummyXvar,1.0);
	  leadingRatioMadGraph->SetPointEYhigh(ovo,leadingRivetMadGraph->GetErrorYhigh(ovo)*dummyNorm/dummyYvar);
	  leadingRatioMadGraph->SetPointEYlow(ovo,leadingRivetMadGraph->GetErrorYlow(ovo)*dummyNorm/dummyYvar);

	  leadingRatio2->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio2->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	  leadingRatio2Systematics->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio2Systematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));
	    
	}


	////////////////////////

	leadingRivetSherpa->SetFillColor(kBlue-4);
	leadingRivetSherpa->SetFillStyle(3004);
	leadingRivetSherpa->SetLineColor(kBlue-4);
	leadingRivetSherpa->SetMarkerColor(kBlue-4);
	leadingRivetSherpa->SetMarkerStyle(22);
	leadingRivetSherpa->SetLineWidth(1);
	leadingRivetSherpa->Draw("2");
	leadingRivetSherpa->Draw("pz");

	leadingRivetPowheg->SetFillColor(kGreen+3);
	leadingRivetPowheg->SetFillStyle(3001);
	leadingRivetPowheg->SetLineColor(kGreen+3);
	leadingRivetPowheg->SetMarkerColor(kGreen+3);
	leadingRivetPowheg->SetMarkerStyle(21);
	leadingRivetPowheg->SetMarkerSize(0.7);
	leadingRivetPowheg->SetLineWidth(1);
	leadingRivetPowheg->Draw("2");
	leadingRivetPowheg->Draw("pz");

	leadingRivetMadGraph->SetFillColor(kOrange+10);
	leadingRivetMadGraph->SetFillStyle(3005);
	leadingRivetMadGraph->SetLineColor(kOrange+10);
	leadingRivetMadGraph->SetMarkerColor(kOrange+10);
	leadingRivetMadGraph->SetMarkerStyle(25);
	leadingRivetMadGraph->SetMarkerSize(1.2);
	leadingRivetMadGraph->SetLineWidth(1);
	leadingRivetMadGraph->Draw("2");
	leadingRivetMadGraph->Draw("pz");
	    
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
	legendsx_d = new TLegend (0.74, 0.6, 0.98, 0.88);	   

	legendsx_d->SetFillColor (kWhite);
	//	legendsx_d->SetFillStyle (0);
	legendsx_d->SetBorderSize (1);
	legendsx_d->SetNColumns(1);
	legendsx_d->SetTextSize(.040);
	legendsx_d->AddEntry (leading, "Data (stat)", "PEL");
	legendsx_d->AddEntry (leadingSystematics, "Data (stat+syst)", "PEL");
	legendsx_d->AddEntry (leadingRivetSherpa, "Sherpa", "PELF");
	legendsx_d->AddEntry (leadingRivetMadGraph, "MadGraph", "PELF"); 
	legendsx_d->AddEntry (leadingRivetPowheg, "Powheg", "PELF"); 
	legendsx_d->Draw ("same");

	// Draw the ratio plot: ----------------------

	//////////////////////
	//      Sherpa:

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
	leadingRatioSystematics->GetYaxis()->SetTitleSize(0.16);
	leadingRatioSystematics->GetYaxis()->SetLabelSize(0.14);
	leadingRatioSystematics->GetYaxis()->SetTitleOffset(0.45);
	leadingRatioSystematics->GetYaxis()->SetTitle("Data/MC");   
	leadingRatioSystematics->GetYaxis()->SetNdivisions(505);
	leadingRatioSystematics->GetYaxis()->SetRangeUser(0.4,1.6);
	leadingRatioSystematics->SetTitle("");	  
	leadingRatioSystematics->Draw ("E0");
	leadingRatio->Draw ("E0SAME");

	leadingRatioSherpa->SetFillColor(kBlue-4);
	leadingRatioSherpa->SetFillStyle(3004);
	leadingRatioSherpa->SetLineColor(kBlue-4);
	leadingRatioSherpa->SetMarkerColor(kBlue-4);
	leadingRatioSherpa->SetLineWidth(1);
	leadingRatioSherpa->Draw("2");
	//	leadingRatioSherpa->Draw("pz");

	leadingRatioSystematics->Draw ("E0SAME");
	leadingRatio->Draw ("E0SAME");

	TLine *OLine = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	OLine->SetLineColor(kBlack);
	OLine->SetLineStyle(2);
	OLine->Draw();

	TLatex *latexLabel = new TLatex();
	latexLabel->SetTextSize(0.15);
	latexLabel->SetTextFont(42);
	latexLabel->SetLineWidth(2);
	latexLabel->SetNDC();
	latexLabel->DrawLatex(0.2,0.09,"Sherpa");	  

	//////////////////////
	//      Powheg:

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
	leadingRatio3Systematics->GetXaxis()->SetTitleSize(0.14);
	leadingRatio3Systematics->GetXaxis()->SetLabelSize(0.0);
	leadingRatio3Systematics->GetYaxis()->SetTitleSize(0.16);
	leadingRatio3Systematics->GetYaxis()->SetLabelSize(0.14);
	leadingRatio3Systematics->GetYaxis()->SetTitleOffset(0.45);
	leadingRatio3Systematics->GetYaxis()->SetTitle("Data/MC");   
	leadingRatio3Systematics->GetYaxis()->SetNdivisions(505);
	leadingRatio3Systematics->GetYaxis()->SetRangeUser(0.4,1.6);
	leadingRatio3Systematics->SetTitle("");	  
	leadingRatio3Systematics->Draw ("E0");
	leadingRatio3->Draw ("E0SAME");

	leadingRatioPowheg->SetFillColor(kGreen+3);
	leadingRatioPowheg->SetFillStyle(3001);
	leadingRatioPowheg->SetLineColor(kGreen+3);
	leadingRatioPowheg->SetMarkerColor(kGreen+3);
	leadingRatioPowheg->SetLineWidth(1);
	leadingRatioPowheg->Draw("2");
	//	leadingRatioPowheg->Draw("pz");

	leadingRatio3Systematics->Draw ("E0SAME");
	leadingRatio3->Draw ("E0SAME");

	TLine *OLine = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	OLine->SetLineColor(kBlack);
	OLine->SetLineStyle(2);
	OLine->Draw();

	TLatex *latexLabel = new TLatex();
	latexLabel->SetTextSize(0.15);
	latexLabel->SetTextFont(42);
	latexLabel->SetLineWidth(2);
	latexLabel->SetNDC();
	latexLabel->DrawLatex(0.2,0.09,"Powheg");	  

	//////////////////////
	//      MadGraph:

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
	leadingRatio2Systematics->GetXaxis()->SetLabelSize(0.11);
	leadingRatio2Systematics->GetXaxis()->SetTitleOffset (1.1);
	leadingRatio2Systematics->GetYaxis()->SetTitleSize(0.11);
	leadingRatio2Systematics->GetYaxis()->SetLabelSize(0.10);
	leadingRatio2Systematics->GetYaxis()->SetTitleOffset(0.65);
	leadingRatio2Systematics->GetYaxis()->SetTitle("Data/MC");   
	leadingRatio2Systematics->GetYaxis()->SetNdivisions(505);
	leadingRatio2Systematics->GetYaxis()->SetRangeUser(0.4,1.6);


	leadingRatioMadGraph->SetTitle("");	  

	if (use_case ==1) {
	  leadingRatio2Systematics->GetXaxis ()->SetTitle ("Exclusive jet multiplicity");
	  if (incMultiplicity) leadingRatio2Systematics->GetXaxis ()->SetTitle ("Inclusive jet multiplicity");
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

	leadingRatio2Systematics->Draw ("E0");
	leadingRatio2->Draw ("E0SAME");
	  
	leadingRatioMadGraph->SetFillColor(kOrange+10);
	leadingRatioMadGraph->SetFillStyle(3005);
	leadingRatioMadGraph->SetLineColor(kOrange+10);
	leadingRatioMadGraph->SetMarkerColor(kOrange+10);
	leadingRatioMadGraph->SetLineWidth(1);
	leadingRatioMadGraph->Draw("2");
	//	leadingRatioMadGraph->Draw("pz");
	  
	leadingRatio2Systematics->Draw ("E0SAME");
	leadingRatio2->Draw ("E0SAME");
	  
	TLine *OLine2 = new TLine(leadingSystematics->GetXaxis()->GetXmin(),1.,leadingSystematics->GetXaxis()->GetXmax(),1.);
	OLine2->SetLineColor(kBlack);
	OLine2->SetLineStyle(2);
	OLine2->Draw();
	  
	latexLabel->SetTextSize(0.09);
	latexLabel->DrawLatex(0.2,0.35,"MadGraph");	  

	/////////////////////////////////////////////////////
	  
	string title1;
	title1 = s + "DifferentialX" + stringmatch + ".pdf";
	if (incMultiplicity) title1 = s + "DifferentialXInc" + stringmatch + ".pdf";
	cout << title1 << endl;
	plots->Print (title1.c_str ());
	return;
      }
    }
}

