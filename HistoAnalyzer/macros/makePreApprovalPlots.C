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
#include "TH1D.h"
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

  setTDRStyle ();
  gStyle->SetErrorX(0);

  bool absoluteNormalization = true;
  int lepton = whichlepton; //1 -> electron,  2-> muon , 3 -> combined reults!
  bool addLumiUncertainties = true;
  double lumiError = 0.025;
  int use_case = whichobservable;
  int whichjet = whichjet;
  string version = "_v2_32";

  //  string s                = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v35/FinalTheoryComparison/";
  //  if (lepton==2) string s = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v35/FinalTheoryComparison/Mu/";
  //  if (lepton==3) string s = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v35/FinalTheoryComparison/combination/";
  string s                = "/gpfs/cms/users/schizzi/PreApprovalPlots/ele/";
  if (lepton==2) string s = "/gpfs/cms/users/schizzi/PreApprovalPlots/muo/";
  if (lepton==3) string s = "/gpfs/cms/users/schizzi/PreApprovalPlots/combined/";

  string plotpath = "/gpfs/cms/data/2011/Uncertainties/";
  if (lepton == 2) plotpath = "/gpfs/cms/data/2011/Uncertainties/muons/";
  if (lepton == 3) plotpath = "/gpfs/cms/users/schizzi/Systematics/combination/";

  gStyle->SetOptStat (0);

  TCanvas *plots = new TCanvas ("plots", "EB", 200, 100, 600, 800);

  //DATA:
  string pathFile="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributions_v2_35.root";

  if (lepton == 2) pathFile ="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributionsMu_v2_35.root";
  if (lepton == 3) pathFile ="/gpfs/cms/data/2011/Unfolding/UlfoldedDistributionsCombined_v2_35.root";
  
  //RIVET:
  string rivetPathSherpa   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";
  string rivetPathMadGraph ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
  string rivetPathPoweg    ="/gpfs/cms/users/candelis/Rivet/powheg/test_ee/out.root";

  if (lepton == 2){
    rivetPathSherpa       ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod_mu/out.root";
    rivetPathMadGraph     ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
    rivetPathPoweg        ="/gpfs/cms/users/candelis/Rivet/powheg/test_mm/out.root";
  }

  if (lepton == 3){
    rivetPathSherpa       ="/gpfs/cms/users/schizzi/rivet/combination/Sherpa_central.root";
    rivetPathMadGraph     ="/gpfs/cms/users/schizzi/rivet/combination/MadGraph_central.root";
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
	    systPathFile = plotpath + "jet3HtFinalSyst" + version + ".txt";
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

	//-------------------------------------------------------------
	  
	leadingSystematics->SetName ("leadingSystematics");
	if (systTmpM.size () != leadingSystematics->GetNbinsX ())
	  cout << "WRONG NUMBER OF BINS (# syst from file->" <<systTmpM.size()<<" - # bins leadingsystematics->"<<leadingSystematics->GetNbinsX()<<")"<<endl;
	for (int i = 0; i <= leadingSystematics->GetNbinsX (); i++)
	  {
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
	cout<<"data integral is->"<<leading->Integral()<<" pb"<<endl;

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
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1)); 
	  }

	  leadingRivetSherpa->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	  leadingRivetSherpa->SetPointEYhigh(ovo,0.06*dummyYvar/dummyNorm);
	  leadingRivetSherpa->SetPointEYlow(ovo,0.06*dummyYvar/dummyNorm);

	  leadingRatioSherpa->SetPoint(ovo,dummyXvar,1.0);
	  leadingRatioSherpa->SetPointEYhigh(ovo,0.06);
	  leadingRatioSherpa->SetPointEYlow(ovo,0.06);
	    
	  leadingRatio->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	  leadingRatioSystematics->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatioSystematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

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
	    dummyNorm= 2.0 * 0.000000001*( (1680.67)/3048.0);
	    if (lepton ==3) dummyNorm = dummyNorm*2;
	    dummyNorm= dummyNorm / (leading->GetXaxis()->GetBinWidth(1));
	  }

	  leadingRivetMadGraph->GetPoint(ovo,dummyXvar,dummyYvar); 

	  leadingRivetMadGraph->SetPoint(ovo,dummyXvar,dummyYvar/dummyNorm);
	  leadingRivetMadGraph->SetPointEYhigh(ovo,0.06*dummyYvar/dummyNorm);
	  leadingRivetMadGraph->SetPointEYlow(ovo,0.06*dummyYvar/dummyNorm);

	  leadingRatioMadGraph->SetPoint(ovo,dummyXvar,1.0);
	  leadingRatioMadGraph->SetPointEYhigh(ovo,0.06);
	  leadingRatioMadGraph->SetPointEYlow(ovo,0.06);

	  leadingRatio2->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio2->SetBinError(ovo+1,leading->GetBinError(ovo+1)/(dummyYvar/dummyNorm));

	  leadingRatio2Systematics->SetBinContent(ovo+1,leadingSystematics->GetBinContent(ovo+1)/(dummyYvar/dummyNorm));
	  leadingRatio2Systematics->SetBinError(ovo+1,leadingSystematics->GetBinError(ovo+1)/(dummyYvar/dummyNorm));
	    
	}


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

	leadingRivetSherpa->SetFillColor(996);
	leadingRivetSherpa->SetLineColor(kBlue);
	leadingRivetSherpa->SetLineWidth(3);
	leadingRivetSherpa->Draw("l3");
	    
	leadingRivetMadGraph->SetFillColor(999);
	leadingRivetMadGraph->SetLineColor(kRed);
	leadingRivetMadGraph->SetLineWidth(3);
	leadingRivetMadGraph->Draw("l3");
	    
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
	legendsx_d = new TLegend (0.6, 0.75, 0.92, 0.88);	   

	if (use_case ==3){
	  legendsx_d->SetFillColor (0);
	  legendsx_d->SetFillStyle (0);
	  legendsx_d->SetBorderSize (0);
	  legendsx_d->SetNColumns(2);
	  legendsx_d->SetTextSize(.027);
	  legendsx_d->AddEntry (leading, "Data (stat)", "PLE");
	  legendsx_d->AddEntry (leadingSystematics, "Data (stat+syst)", "PEL");
	  legendsx_d->AddEntry (leadingRivetSherpa, "Sherpa ref.", "L");
	  legendsx_d->AddEntry (leadingRivetMadGraph, "MadGraph ref.", "L"); 
	  legendsx_d->Draw ("same");
	}
	else{
	  legendsx_d->SetFillColor (0);
	  legendsx_d->SetFillStyle (0);
	  legendsx_d->SetBorderSize (0);
	  legendsx_d->SetNColumns(1);
	  legendsx_d->SetTextSize(.030);
	  legendsx_d->AddEntry (leading, "Data (stat)", "PLE");
	  legendsx_d->AddEntry (leadingSystematics, "Data (stat+syst)", "PEL");
	  legendsx_d->AddEntry (leadingRivetSherpa, "Sherpa ref.", "L");
	  legendsx_d->AddEntry (leadingRivetMadGraph, "MadGraph ref.", "L");
	  legendsx_d->Draw ("same");
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
	leadingRatioSystematics->GetYaxis()->SetRangeUser(0.4,1.6);

	leadingRatioSystematics->SetTitle("");	  

	leadingRatioSystematics->Draw ("E1");
	leadingRatio->Draw ("E1SAME");

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

