#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"
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
#include "TCut.h"
#include "TLatex.h"
#include <vector>
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

class combineLeptonRivet {
public:
  int letscombine ();
  void mergewhateveruwant (bool isMadGraph, int whichobservable, string wichelepath, string wichmuopath, string wheretocombine);
};

int combineLeptonRivet::letscombine () {

  // electron datasets:
  string eleRivetPathSherpa       ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";
  string eleRivetPathSherpaUP     ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaleup2/out.root";
  string eleRivetPathSherpaDOWN   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaledown2/out.root";
  string eleRivetPathSherpaPDF1   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfmstw/out.root";
  string eleRivetPathSherpaPDF2   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfnn/out.root";
  string eleRivetPathMadGraph     ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
  string eleRivetPathMadGraphDOWN ="/gpfs/cms/users/candelis/Rivet/madgraph/scaledown/DYtotal.root";
  string eleRivetPathMadGraphUP   ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleup/DYtotal.root";
  string eleRivetPathMadGraphPDF1 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfmstw/DYtotal.root"; 
  string eleRivetPathMadGraphPDF2 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfnn/DYtotal.root";

  // muon datasets:
  string muoRivetPathSherpa       ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod_mu/out.root";
  string muoRivetPathSherpaUP     ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaleup_mu/out.root";
  string muoRivetPathSherpaDOWN   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaledown_mu/out.root";
  string muoRivetPathSherpaPDF1   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfmstw_mu/out.root";
  string muoRivetPathSherpaPDF2   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfnn_mu/out.root";
  string muoRivetPathMadGraph     ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
  string muoRivetPathMadGraphDOWN ="/gpfs/cms/users/candelis/Rivet/madgraph/scaledown/DYtotal.root";
  string muoRivetPathMadGraphUP   ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleup/DYtotal.root";
  string muoRivetPathMadGraphPDF1 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfmstw/DYtotal.root";
  string muoRivetPathMadGraphPDF2 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfnn/DYtotal.root";

  for (int i=1;i<14;i++) {
    mergewhateveruwant (true, i, eleRivetPathMadGraph, muoRivetPathMadGraph, "MadGraph_central.root");
  }
  for (int i=1;i<14;i++) {
    mergewhateveruwant (true, i, eleRivetPathMadGraphDOWN, muoRivetPathMadGraphDOWN, "MadGraph_scaleDOWN.root");
  }
  for (int i=1;i<14;i++) {
    mergewhateveruwant (true, i, muoRivetPathMadGraphUP, muoRivetPathMadGraphUP, "MadGraph_scaleUP.root");
  }
  for (int i=1;i<14;i++) {
    mergewhateveruwant (true, i, eleRivetPathMadGraphPDF1, muoRivetPathMadGraphPDF1, "MadGraph_PDF1.root");
  }
  for (int i=1;i<14;i++) {
    mergewhateveruwant (true, i, eleRivetPathMadGraphPDF2, muoRivetPathMadGraphPDF2, "MadGraph_PDF2.root");
  }
  for (int i=1;i<14;i++) {
    mergewhateveruwant (false, i, eleRivetPathSherpa, muoRivetPathSherpa, "Sherpa_central.root");
  }
  for (int i=1;i<14;i++) {
    mergewhateveruwant (false, i, eleRivetPathSherpaDOWN, muoRivetPathSherpaDOWN, "Sherpa_scaleDOWN.root");
  }
  for (int i=1;i<14;i++) {
    mergewhateveruwant (false, i, eleRivetPathSherpaUP, muoRivetPathSherpaUP, "Sherpa_scaleUP.root");
  }
  for (int i=1;i<14;i++) {
    mergewhateveruwant (false, i, eleRivetPathSherpaPDF1, muoRivetPathSherpaPDF1, "Sherpa_PDF1.root");
  }
  for (int i=1;i<14;i++) {
    mergewhateveruwant (false, i, eleRivetPathSherpaPDF2, muoRivetPathSherpaPDF2, "Sherpa_PDF2.root");
  }

  return 0;
}

void combineLeptonRivet::mergewhateveruwant (bool isMadGraph, int whichobservable, string wichelepath, string wichmuopath, string wheretocombine) {

  bool isMG = isMadGraph;
  int usecase = whichobservable;

  //  setTDRStyle ();

  string elePathFile = wichelepath;
  string muoPathFile = wichmuopath;
  string outfile = wheretocombine;

  TFile output_file(outfile.c_str (),"UPDATE");

  TFile *histofile1 = TFile::Open (elePathFile.c_str ());
  histofile1->cd ("");
  TDirectory *dir1 = gDirectory;
  TList *mylist1 = (TList *) dir1->GetListOfKeys ();
  TIter iter1 (mylist1);
  TObject *tobj1 = 0;

  TFile *histofile2 = TFile::Open (muoPathFile.c_str ());
  histofile2->cd ("");
  TDirectory *dir2 = gDirectory;
  TList *mylist2 = (TList *) dir2->GetListOfKeys ();
  TIter iter2 (mylist2);
  TObject *tobj2 = 0;

  string elename;
  string muoname;
  TH1D *elehisto;
  TH1D *muohisto;
  TH1D *combinehisto;
  TGraphAsymmErrors *eletgraph;
  TGraphAsymmErrors *muotgraph;
  TGraphAsymmErrors *combinetgraph;

  double wmean=0.;

  // Build the string with the histo/tgraph name:
  stringstream oss1, oss2;
  if (usecase == 1)  {oss1<<"03"; oss2<<"08";}
  if (usecase == 2)  {oss1<<"01"; oss2<<"06";}
  if (usecase == 3)  {oss1<<"02"; oss2<<"07";}
  if (usecase == 4)  {oss1<<"04"; oss2<<"09";}
  if (usecase == 5)  {oss1<<"05"; oss2<<"10";}
  if (usecase == 6)  {oss1<<"15"; oss2<<"11";}
  if (usecase == 7)  {oss1<<"16"; oss2<<"12";}
  if (usecase == 8)  {oss1<<"17"; oss2<<"13";}
  if (usecase == 9)  {oss1<<"18"; oss2<<"14";}
  if (usecase == 10) {oss1<<"19"; oss2<<"23";}
  if (usecase == 11) {oss1<<"20"; oss2<<"24";}
  if (usecase == 12) {oss1<<"21"; oss2<<"25";}
  if (usecase == 13) {oss1<<"22"; oss2<<"26";}
  if (isMG) {
    elename="d"+oss1.str()+"-x01-y01";
    muoname="d"+oss2.str()+"-x01-y01";
  } else {
    elename="d"+oss1.str()+"_x01_y01";
    muoname="d"+oss2.str()+"_x01_y01";
  }


  // GET THE TH1's or TGraph's:
  string temp_elename;
  string temp_muoname;
  while ((tobj1 = iter1.Next ())) {
    temp_elename = tobj1->GetName ();
    if (temp_elename == elename) {
      histofile1->cd ("");
      if (isMG) {
	gDirectory->GetObject (elename.c_str (), elehisto); // Save ele histogram!
      } else {
	gDirectory->GetObject (elename.c_str (), eletgraph); // Save ele histogram!
      }
    }
  }
  iter2.Reset();
  while ((tobj2 = iter2.Next ())) {
    temp_muoname = tobj2->GetName ();
    if (temp_muoname == muoname) {
      histofile2->cd ("");
      if (isMG) {
	gDirectory->GetObject (elename.c_str (), muohisto); // Save ele histogram!
      } else {
	gDirectory->GetObject (muoname.c_str (), muotgraph); // Save muo histogram!
      }
    }
  }


  // BEGIN COMBINATION:

  cout << "Combining " << elename << " for electrons with " << muoname << " for muons..."  << endl;
	
  int nbins_ele;
  int nbins_muo;
  double dummyXvar=0.;
  double dummyYvar=0.;

  if (isMG) {
    nbins_ele = elehisto->GetNbinsX();
    nbins_muo = muohisto->GetNbinsX();
  } else {
    nbins_ele = eletgraph->GetN();
    nbins_muo = muotgraph->GetN();
  }

  if (nbins_ele != nbins_muo) {cout << "ERROR: combining histos with different binning... exit." << endl;}

  if (isMG) {
  combinehisto = (TH1D *) elehisto->Clone ("elehisto");
  combinehisto->SetName(elename.c_str ());
  combinehisto->SetTitle(elename.c_str ());
  } else {
  combinetgraph = (TGraphAsymmErrors *) eletgraph->Clone ("eletgraph");
  combinetgraph->SetName(elename.c_str ());
  combinetgraph->SetTitle(elename.c_str ());
  }

  // Compute weighted mean and sigma for every bin:
  if (isMG) {
    for (int i=1; i<(nbins_ele+1);i++) {
      wmean = 1.;
      combinehisto->SetBinContent(i,wmean);
      combinehisto->SetBinError(i,0.);
    }
  } else {
    for (int i=1; i<(nbins_ele+1);i++) {
      eletgraph->GetPoint(i,dummyXvar,dummyYvar);
      wmean = 1.;
      combinetgraph->SetPoint(i,dummyXvar,wmean);
      combinetgraph->SetPointEYhigh(i,0.);
      combinetgraph->SetPointEYlow(i,0.);
    }
  }

  output_file.cd();

  if (isMG) {
  combinehisto->Write();
  } else {
  combinetgraph->Write();
  }


  histofile1->Close();
  histofile2->Close();
  output_file.Close();
  cout << "Congratulations, combination achieved!" << endl;
}
