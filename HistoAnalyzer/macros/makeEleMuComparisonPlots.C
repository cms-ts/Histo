#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
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

ofstream myfile;
TH1D *leadingRatio;


void correctTheErrorsForDataStatContribution(TH1D* absolutedistr,TH1D *ratio){

  for (unsigned int p=0;p<jData->GetNbinsX();p++){
    //////////////////////////////////////
    //Extra contributo per togliere l'effetto del "gonfiamento degli errori statistici nell'unfolding"
    // errore^2_stat= (a/b*sigma)^2*(1/a^2+1/b^4)
  
    double sigma=absolutedistr->GetBinError(p+1);
    double a=absolutedistr->GetBinContent(p+1);
    double a_over_b=ratio->GetBinContent(p+1);
    double b=pow(a_over_b,-1)*a;
    double errquadrostat=pow(a_over_b,2)*pow(sigma,2)*( pow(a,-2)+pow(b,-4) );
    double errstat=sqrt(errquadrostat);
    cout<<errstat<<endl;
    leadingRatio->SetBinError(p+1,leadingRatio->GetBinError(p+1)-errstat);
  }
  ////////////////////////////////////
  return ;
}


void correctTheErrorsForDataStatContribution2(TH1D* absolutesherpa,TH1D* absoluteMD, TH1D *ratio){

  for (unsigned int p=0;p<absolutesherpa->GetNbinsX();p++){
    //////////////////////////////////////
    //Extra contributo per togliere l'effetto del "gonfiamento degli errori statistici nell'unfolding"
    // errore^2_stat= sigma_a^2/b^2 + a^2/b^4 * sigma_b^2
  
    double sigmaSherpa=absolutesherpa->GetBinError(p+1);
    double sigmaMD=absoluteMD->GetBinError(p+1);

    //Subtract stat component
    sigmaSherpa=sigmaSherpa-sqrt(absolutesherpa->GetBinContent(p+1));
    sigmaMD=sigmaMD-sqrt(absoluteMD->GetBinContent(p+1));

    double a=absolutesherpa->GetBinContent(p+1);
    double b=absoluteMD->GetBinContent(p+1);    

    double errstatQuadro=( pow(sigmaSherpa,2)/pow(b,2))+( pow(a,2)*pow(b,-4)*pow(sigmaMD,2) ); 
    leadingRatio->SetBinError(p+1,leadingRatio->GetBinError(p+1)-sqrt(errstatQuadro));
    cout<<"errstatr "<<sqrt(errstatQuadro)<<" leadingRatio->GetBinError(p+1) "<<leadingRatio->GetBinError(p+1)<<" data/total "<<(sqrt(errstatQuadro))/(leadingRatio->GetBinError(p+1))<<endl;
  }
  ////////////////////////////////////
  return ;
}

void loopAndDumpEntries(TH1D *jData, TH1D *leading){

  for (unsigned int p=0;p<jData->GetNbinsX();p++){

    /*
    //////////////////////////////////////
    //Extra contributo per togliere l'effetto del "gonfiamento degli errori statistici nell'unfolding"
    // errore^2_stat= (a/b*sigma)^2*(1/a^2+1/b^4)
    
    double sigma=leading->GetBinError(p+1);
    double a=leading->GetBinContent(p+1);
    double a_over_b=jData->GetBinContent(p+1);
    double b=pow(a_over_b,-1)*a;
    double errquadrostat=pow(a_over_b,2)*pow(sigma,2)*( pow(a,-2)+pow(b,-4) );
    double errstat=sqrt(errquadrostat);
    cout<<errstat<<endl;

    ////////////////////////////////////
    */

    double differenceErrorRatioOne=jData->GetBinError(p+1)-fabs(1-jData->GetBinContent(p+1)/*+errstat*/);

    if (differenceErrorRatioOne>0) {
      myfile<<"0.0000"<<endl;
      cout<<"SVD-Bayes for Bin "<<p+1<<" is "<<fabs(1-jData->GetBinContent(p+1))<<" and error +/- "<<jData->GetBinError(p+1)<<endl;
    }
    else {
      cout<<"SVD-Bayes for Bin "<<p+1<<" is "<<fabs(1-jData->GetBinContent(p+1))<<" and error +/- "<<jData->GetBinError(p+1)<<"----> ";
      double calculateExtraResidual=fabs(1-jData->GetBinContent(p+1)/*+errstat*/)-(jData->GetBinError(p+1));
      cout<<"SVD-Bayes for Bin "<<p+1<<" is "<<calculateExtraResidual<<endl;
      myfile<<calculateExtraResidual<<endl;
    }
  }
}

void
makeEleMuComparisonPlots (int whichobservable, int whichjet, int whichlepton)
{
  //Open the file and form the name
  string fileSystematics; 
  string suffix="/gpfs/cms/data/2011/Systematics/postApproval/";
  //string suffix="/tmp/";

  if (whichlepton==1) suffix=suffix+"ele/";
  if (whichlepton==2) suffix=suffix+"muo/";

  //  setTDRStyle ();
  gStyle->SetErrorX(0);
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);

  bool absoluteNormalization = true;
  int lepton = 3; //1 -> electron,  2-> muon , 3 -> combined reults!
  bool addLumiUncertainties = true;
  double lumiError = 0.025;
  int use_case = whichobservable;
  int whichjet = whichjet;
  string version = "_v2_32";

  //string s         = "/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v41/SVDBayes/";
  string s="/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v57_3_postApproval/ele/";
  //  string s         = "/gpfs/cms/users/schizzi/EleMuComparisonPlots/PostUnfolding/";
  string  eleplotpath = "/gpfs/cms/users/schizzi/Systematics/ele/";
  string  muoplotpath = "/gpfs/cms/users/schizzi/Systematics/muo/";

  gStyle->SetOptStat (0);

  TCanvas *plots = new TCanvas ("plots", "EB", 200, 100, 600, 800);

  //DATA:
  //string elepathFile   ="/gpfs/cms/data/2011/Unfolding/testReferenceMu.root";
  //string muopathFile   ="/gpfs/cms/data/2011/Unfolding/testMu.root";
  string elepathFile   ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3Sherpa.root";
  string muopathFile   ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3.root";

  if (whichlepton==2){
  elepathFile   ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3SherpaMu.root";
  muopathFile   ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3Mu.root";
  s="/afs/infn.it/ts/user/marone/html/ZJets/FinalPlotsForAN/v57_3_postApproval/muo/";
  }
  //string elepathFile   ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3NoSQRT.root";
  //string muopathFile   ="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3NoMCToy.root";
    
  TFile *histof = TFile::Open (elepathFile.c_str ());
  histof->cd ("");
  TDirectory *dir = gDirectory;
  TList *mylist = (TList *) dir->GetListOfKeys ();
  TIter iter (mylist);
  TObject *tobj = 0;

  TFile *histofmuo = TFile::Open (muopathFile.c_str ());

  string stringmatch;
  string systPathFile;
  string systPathFileMuo;

  histof->cd ("");

  int i = 0;			// solo di servizio quando debuggo...
  while ((tobj = iter.Next ()))
    {
      string name = tobj->GetName ();

      if (use_case == 1) 
	{ // Jet Multiplicity
	  stringmatch = "JetMultiplicityUnfolded";
	  systPathFile = eleplotpath + "systematicsEff_jetMult" + version + ".txt";
	  systPathFileMuo = muoplotpath + "systematicsEff_jetMult" + version + ".txt";
	  fileSystematics = suffix+"systematicsUnfMCToy_jetMult" + version + ".txt"; 
	}

      if (use_case == 2) 
	{ // Jet Pt
	  if (whichjet == 1)
	    {
	      stringmatch = "jReco_leading";
	      systPathFile = eleplotpath + "systematicsEff_jet1Pt" + version + ".txt";
	      systPathFileMuo = muoplotpath + "systematicsEff_jet1Pt" + version + ".txt";
	      fileSystematics = suffix+"systematicsUnfMCToy_jet1Pt" + version + ".txt"; 
	    }
	  
	  if (whichjet == 2)
	    {
	      stringmatch = "jReco_subleading";
	      systPathFile = eleplotpath + "systematicsEff_jet2Pt" + version + ".txt";
	      systPathFileMuo = muoplotpath + "systematicsEff_jet2Pt" + version + ".txt";
	      fileSystematics = suffix+"systematicsUnfMCToy_jet2Pt" + version + ".txt"; 
	    }
	  
	  if (whichjet == 3)
	    {
	      stringmatch = "jReco_subsubleading";
	      systPathFile = eleplotpath + "systematicsEff_jet3Pt" + version + ".txt";
	      systPathFileMuo = muoplotpath + "systematicsEff_jet3Pt" + version + ".txt";
	      fileSystematics = suffix+"systematicsUnfMCToy_jet3Pt" + version + ".txt"; 
	    }
	  
	  if (whichjet == 4)
	    {
	      stringmatch = "jReco_subsubsubleading";
	      systPathFile = eleplotpath + "systematicsEff_jet4Pt" + version + ".txt";
	      systPathFileMuo = muoplotpath + "systematicsEff_jet4Pt" + version + ".txt";
	      fileSystematics = suffix+"systematicsUnfMCToy_jet4Pt" + version + ".txt"; 
	    }
	}
      
      if (use_case == 3) { // Jet Eta
	if (whichjet == 1)
	  {
	    stringmatch = "jReco_leadingeta";
	    systPathFile = eleplotpath + "systematicsEff_jet1Eta" + version + ".txt";
	    systPathFileMuo = muoplotpath + "systematicsEff_jet1Eta" + version + ".txt";
	    fileSystematics = suffix+"systematicsUnfMCToy_jet1Eta" + version + ".txt"; 
	  }
	
	if (whichjet == 2)
	  {
	    stringmatch = "jReco_subleadingeta";
	    systPathFile = eleplotpath + "systematicsEff_jet2Eta" + version + ".txt";
	    systPathFileMuo = muoplotpath + "systematicsEff_jet2Eta" + version + ".txt";
	    fileSystematics = suffix+"systematicsUnfMCToy_jet2Eta" + version + ".txt"; 
	  }

	if (whichjet == 3)
	  {
	    stringmatch = "jReco_subsubleadingeta";
	    systPathFile = eleplotpath + "systematicsEff_jet3Eta" + version + ".txt";
	    systPathFileMuo = muoplotpath + "systematicsEff_jet3Eta" + version + ".txt";
	    fileSystematics = suffix+"systematicsUnfMCToy_jet3Eta" + version + ".txt"; 
	  }
	
	if (whichjet == 4)
	  {
	    stringmatch = "jReco_subsubsubleadingeta";
	    systPathFile = eleplotpath + "systematicsEff_jet4Eta" + version + ".txt";
	    systPathFileMuo = muoplotpath + "systematicsEff_jet4Eta" + version + ".txt";
	    fileSystematics = suffix+"systematicsUnfMCToy_jet4Eta" + version + ".txt"; 
	  }
      }
      
      if (use_case == 4) { // Ht
	if (whichjet == 1)
	  {
	    stringmatch = "HReco_leading";
	    systPathFile = eleplotpath + "systematicsEff_jet1Ht" + version + ".txt";
	    systPathFileMuo = muoplotpath + "systematicsEff_jet1Ht" + version + ".txt";
	    fileSystematics = suffix+"systematicsUnfMCToy_jet1Ht" + version + ".txt"; 
	  }
	if (whichjet == 2)
	  {
	    stringmatch = "HReco_subleading";
	    systPathFile = eleplotpath + "systematicsEff_jet2Ht" + version + ".txt";
	    systPathFileMuo = muoplotpath + "systematicsEff_jet2Ht" + version + ".txt";
	    fileSystematics = suffix+"systematicsUnfMCToy_jet2Ht" + version + ".txt"; 
	  }
	
	if (whichjet == 3)
	  {
	    stringmatch = "HReco_subsubleading";
	    systPathFile = eleplotpath + "systematicsEff_jet3Ht" + version + ".txt";
	    systPathFileMuo = muoplotpath + "systematicsEff_jet3Ht" + version + ".txt";
	    fileSystematics = suffix+"systematicsUnfMCToy_jet3Ht" + version + ".txt"; 
	  }

	if (whichjet == 4)
	  {
	    stringmatch = "HReco_subsubsubleading";
	    fileSystematics = suffix+"systematicsUnfMCToy_jet4Ht" + version + ".txt"; 
	    systPathFile = eleplotpath + "systematicsEff_jet4Ht" + version + ".txt";
	    systPathFileMuo = muoplotpath + "systematicsEff_jet4Ht" + version + ".txt";
	  }
      }

      
      if (name == stringmatch) {

	cout << "CONFIGURATION:" << endl;
	cout << "stringmatch: " <<stringmatch<< endl;
	cout << "systPathFile: " <<systPathFile<< endl;

	TH1D *leading;
	gDirectory->GetObject (name.c_str (), leading);
	leading->SetMarkerSize(0.9);
	leading->Sumw2();

	histofmuo->cd ("");
	TH1D *leadingmuo;
	gDirectory->GetObject (name.c_str (), leadingmuo);
	leadingmuo->SetMarkerSize(0.9);
	leadingmuo->Sumw2();

	//	/// EFFICIENCY Systematics:
	//	for (int nnbins=1;nnbins<=leading->GetNbinsX ();nnbins++) {
	  //	  cout << fabs(leading->GetBinContent(nnbins)-leadingmuo->GetBinContent(nnbins))/(2*leading->GetBinContent(nnbins)) << endl;
	  //	  cout << leading->GetBinContent(nnbins)-leadingmuo->GetBinContent(nnbins) << endl;
	//	}

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
	    systTmpM.push_back (dat);
	  }
	inM.close ();
	// ------------------------------------------------------------
	// read from file ---------------------------------------------
	ifstream inM2;
	cout << "reading ...  " << systPathFileMuo << endl;
	inM2.open (systPathFileMuo.c_str ());
	std::vector < double >systTmpMmuo;
	while (1)
	  {
	    inM2 >> dat;
	    if (!inM2.good ())
	      break;
	    systTmpMmuo.push_back (dat);
	  }
	inM2.close ();
	// ------------------------------------------------------------

        TH1D *leadingRatioSystematics;
	leadingRatioSystematics = (TH1D *) leading->Clone ("leading");

	if (systTmpM.size () != leadingRatioSystematics->GetNbinsX ())
	  cout << "TE SON MONA! WRONG NUMBER OF BINS (# syst from file->" <<systTmpM.size()<<" - # bins->"<<leadingRatioSystematics->GetNbinsX()<<")"<<endl;
	for (int i = 0; i < leadingRatioSystematics->GetNbinsX (); i++)
	  {
	    //leadingRatioSystematics->SetBinContent(i + 1, 1.0);
	    //leadingRatioSystematics->SetBinError (i + 1,sqrt(systTmpM[i]*systTmpM[i] + systTmpMmuo[i]*systTmpMmuo[i]));
	    //	    leadingRatioSystematics->SetBinContent(i + 1, 1.0);
	    //	    leadingRatioSystematics->SetBinError (i + 1,max(systTmpM[i]/100.0,systTmpMmuo[i]/100.0));
	  }

	plots->cd ();
	TPad *pad1 = new TPad("pad1","pad1",0.01,0.3,0.99,0.99);

	pad1->Draw();
	pad1->cd();
	pad1->SetTopMargin(0.1);
	pad1->SetBottomMargin(0.0);
	pad1->SetLeftMargin(0.2);
	pad1->SetRightMargin(0.0);
	pad1->SetFillStyle(0);
	if (use_case !=3) pad1->SetLogy(1); 
	else pad1->SetLogy(0);

	if (use_case ==3){
	  leading->SetMinimum((0.5-0.05*(whichjet-1))*leading->GetMinimum());
	  leading->SetMaximum((1.25+0.35*(whichjet-1))*leading->GetMaximum());
	}
	leading->SetLineColor (kRed+1);
	leading->SetMarkerStyle (20);
	leading->SetFillColor (kRed+1);
	leading->SetMarkerColor (kRed+1);

	leading->GetXaxis ()->SetTitleOffset (1.1);
	leading->GetXaxis ()->SetTitleSize (0.05);
	leading->GetXaxis ()->SetLabelSize (0.0);
	leading->GetXaxis ()->SetLabelFont (42);
	leading->GetXaxis ()->SetTitleFont (42);

	leading->GetYaxis ()->SetTitleOffset (1.);
	leading->GetYaxis ()->SetTitleSize (0.07);
	leading->GetYaxis ()->SetLabelSize (0.06);
	leading->GetYaxis ()->SetLabelFont (42);
	leading->GetYaxis ()->SetTitleFont (42);

	leading->SetTitle ();
	leading->GetXaxis ()->SetTitle ();
	    

	if (use_case ==1) {
	  if (absoluteNormalization) leading->GetYaxis ()->SetTitle ("d#sigma/dN [pb]");
	  else {
	    if (lepton == 1) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/dN");
	    if (lepton == 2) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/dN");
	    if (lepton == 3) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow l^{+}l^{-}}) d#sigma/dN");
	  }
	}

	if (use_case ==2) {
	  if (absoluteNormalization) leading->GetYaxis ()->SetTitle ("d#sigma/dp_{T} [pb/GeV]");
	  else {
	    if (lepton == 1) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/dp_{T}");
	    if (lepton == 2) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/dp_{T}");
	    if (lepton == 3) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow l^{+}l^{-}}) d#sigma/dp_{T}");
	  }
	}

	if (use_case ==3) {
	  if (absoluteNormalization) leading->GetYaxis ()->SetTitle ("d#sigma/d#eta [pb]");
	  else {
	    if (lepton == 1) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/d#eta");
	    if (lepton == 2) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/d#eta");
	    if (lepton == 3) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow l^{+}l^{-}}) d#sigma/d#eta");
	  }
	}
	  
	if (use_case ==4) {
	  if (absoluteNormalization) leading->GetYaxis ()->SetTitle ("d#sigma/dH_{T} [pb/GeV]");
	  else {
	    if (lepton == 1) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d#sigma/dH_{T}");
	    if (lepton == 2) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d#sigma/dH_{T}");
	    if (lepton == 3) leading->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow l^{+}l^{-}}) d#sigma/dH_{T}");
	  }
	}
	  
	leading->SetFillColor (kBlack);
	leading->SetFillStyle (3001);
	leading->SetMarkerColor (kBlack);
	leading->SetLineColor (kBlack);
	leading->SetMarkerStyle (20);
	leading->Draw ("E1");

	leadingmuo->SetFillColor (kBlue);
	leadingmuo->SetFillStyle (3001);
	leadingmuo->SetMarkerColor (kBlue);
	leadingmuo->SetLineColor (kBlue);
	leadingmuo->SetMarkerStyle (21);
	leadingmuo->Draw ("E1SAME");

	//-------------------------------------------

	TLegend *legendsx_d;
	legendsx_d = new TLegend (0.74, 0.6, 0.98, 0.88);	   

	legendsx_d->SetFillColor (kWhite);
	legendsx_d->SetBorderSize (1);
	legendsx_d->SetNColumns(1);
	legendsx_d->SetTextSize(.040);
	legendsx_d->AddEntry (leading, "Sherpa", "PEL");
	legendsx_d->AddEntry (leadingmuo, "Madgraph", "PEL");
	legendsx_d->Draw ("same");

	// Draw the ratio plot: ----------------------

	leadingRatio = (TH1D *) leading->Clone ("leading");
	leadingRatio->Divide(leadingmuo);

	for (int mem=1; mem<=leadingRatio->GetNbinsX(); mem++) {
	  cout << "Syst for bin nr." << mem << ":\t" << fabs(leadingRatio->GetBinContent(mem)-1.0)/2 << endl;
	}

	plots->cd();
	TPad *pad3 = new TPad("pad3","pad3",0.01,0.01,0.99,0.30);
	pad3->Draw();
	pad3->cd();
	pad3->SetTopMargin(0.0);
	pad3->SetBottomMargin(0.3);
	pad3->SetLeftMargin(0.2);
	pad3->SetRightMargin(0);
	pad3->SetFillStyle(0);

	leadingRatio->GetXaxis()->SetLabelFont (42);
	leadingRatio->GetXaxis()->SetTitleFont (42);
	leadingRatio->GetXaxis()->SetTitleSize(0.11);
	leadingRatio->GetXaxis()->SetLabelSize(0.11);
	leadingRatio->GetXaxis()->SetTitleOffset (1.1);
	leadingRatio->GetYaxis()->SetTitleSize(0.11);
	leadingRatio->GetYaxis()->SetLabelSize(0.10);
	leadingRatio->GetYaxis()->SetTitleOffset(0.65);
	leadingRatio->GetYaxis()->SetTitle("Ratio");   
	leadingRatio->GetYaxis()->SetNdivisions(5);
	leadingRatio->GetYaxis()->SetRangeUser(0.4,1.6);


	if (use_case ==1) {
	  leadingRatio->GetXaxis ()->SetTitle ("Exclusive jet multiplicity");
	}
	if (use_case ==2) {
	  if (whichjet == 1) leadingRatio->GetXaxis ()->SetTitle ("Leading jet p_{T} [GeV]");
	  if (whichjet == 2) leadingRatio->GetXaxis ()->SetTitle ("Second jet p_{T} [GeV]");
	  if (whichjet == 3) leadingRatio->GetXaxis ()->SetTitle ("Third jet p_{T} [GeV]");
	  if (whichjet == 4) leadingRatio->GetXaxis ()->SetTitle ("Fourth jet p_{T} [GeV]");
	}
	if (use_case ==3) {
	  if (whichjet == 1) leadingRatio->GetXaxis ()->SetTitle ("Leading jet #eta");
	  if (whichjet == 2) leadingRatio->GetXaxis ()->SetTitle ("Second jet #eta");
	  if (whichjet == 3) leadingRatio->GetXaxis ()->SetTitle ("Third jet #eta");
	  if (whichjet == 4) leadingRatio->GetXaxis ()->SetTitle ("Fourth jet #eta");
	}
	if (use_case ==4) {
	  if (whichjet == 1) leadingRatio->GetXaxis ()->SetTitle ("H_{T}, N_{jet} >= 1 [GeV]");
	  if (whichjet == 2) leadingRatio->GetXaxis ()->SetTitle ("H_{T}, N_{jet} >= 2 [GeV]");
	  if (whichjet == 3) leadingRatio->GetXaxis ()->SetTitle ("H_{T}, N_{jet} >= 3 [GeV]");
	  if (whichjet == 4) leadingRatio->GetXaxis ()->SetTitle ("H_{T}, N_{jet} >= 4 [GeV]");
	}

	leadingRatio->SetFillColor (kRed+2);
	leadingRatio->SetMarkerColor (kRed+2);
	leadingRatio->SetLineColor (kRed+2);
	leadingRatio->Draw ("E0");

	leadingRatioSystematics->SetFillColor (kGreen+3);
	leadingRatioSystematics->SetFillStyle (3004);
	leadingRatioSystematics->SetMarkerColor (kGreen+3);
	leadingRatioSystematics->SetLineColor (kGreen+3);
	leadingRatioSystematics->SetMarkerStyle (1);
	//leadingRatioSystematics->Draw ("E3SAME");

	leadingRatio->Draw ("E1SAME");

	myfile.open (fileSystematics.c_str());
	cout<<"TXT file saved in "<<fileSystematics<<endl;
	loopAndDumpEntries(leadingRatio,leadingmuo);

	TLine *OLine2 = new TLine(leading->GetXaxis()->GetXmin(),1.,leading->GetXaxis()->GetXmax(),1.);
	OLine2->SetLineColor(kBlack);
	OLine2->SetLineStyle(2);
	OLine2->Draw();
	  
	//latexLabel->SetTextSize(0.09);
	//	latexLabel->DrawLatex(0.2,0.35,"Ratio");	  

	/////////////////////////////////////////////////////
	  
	string title1;
	title1 = s + "DifferentialX" + stringmatch + ".pdf";
	cout << title1 << endl;
	plots->Print (title1.c_str ());
	plots->Draw();
	return;
      }
    }
}

