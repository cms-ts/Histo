#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TGraphAsymmErrors.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string.h>

// INSTRUCTIONS:
// .L combineLeptonStatistics.C
// combineLeptonStatistics t
// t.letscombine()
// CONGRATULATIONS!

class combineLeptonRivet {
public:
  Int_t letscombine ();
  void mergewhateveruwant (bool isMadGraph, Int_t whichobservable, string wichelepath, string wichmuopath, string wheretocombine);
};

Int_t combineLeptonRivet::letscombine () {

  // electron datasets:
  string eleRivetPathSherpa       ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod2/out.root";
  string eleRivetPathSherpaUP     ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaleup2/out.root";
  string eleRivetPathSherpaDOWN   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaledown2/out.root";
  string eleRivetPathSherpaPDF1   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfmstw/out.root";
  string eleRivetPathSherpaPDF2   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfnn/out.root";
  //  string eleRivetPathSherpa2NLO           ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01_7TeV_sherpa/out.root";
  string eleRivetPathSherpa2NLO           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/central/out.root";
  string eleRivetPathSherpa2NLOFRdown     ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/FRdown/out.root";
  string eleRivetPathSherpa2NLOFRup       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/FRup/out.root";
  string eleRivetPathSherpa2NLOQcutdown   ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qcutdown_7TeV_sherpa/out.root";
  string eleRivetPathSherpa2NLOQcutup     ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qcutup_7TeV_sherpa/out.root";
  string eleRivetPathSherpa2NLOQdown      ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qdown_7TeV_sherpa/out.root";
  string eleRivetPathSherpa2NLOQup        ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qup_7TeV_sherpa/out.root";
  string eleRivetPathSherpa2NLOmstw       ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01MSTW2008_7TeV_sherpa/out.root";
  string eleRivetPathSherpa2NLOnnpdf      ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01NNPDF_7TeV_sherpa/out.root";
  string eleRivetPathMadGraph     ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
  string eleRivetPathMadGraphDOWN ="/gpfs/cms/users/candelis/Rivet/madgraph/scaledown/DYtotal.root";
  string eleRivetPathMadGraphUP   ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleup/DYtotal.root";
  string eleRivetPathMadGraphPDF1 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfmstw/DYtotal.root"; 
  string eleRivetPathMadGraphPDF2 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfnn/DYtotal.root";
  string eleRivetPathPowheg       ="/gpfs/cms/users/candelis/Rivet/powheg/test_ee/out.root";
  string eleRivetPathPowhegMINLO           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-10/out.root";
  string eleRivetPathPowhegMINLO_05_10     ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/05-10/out.root";
  string eleRivetPathPowhegMINLO_20_10     ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/20-10/out.root";
  string eleRivetPathPowhegMINLO_10_05     ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-05/out.root";
  string eleRivetPathPowhegMINLO_10_20     ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-20/out.root";
  string eleRivetPathPowhegMINLO_UP        ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/05-05/out.root";
  string eleRivetPathPowhegMINLO_DOWN      ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/20-20/out.root";

  // muon datasets:
  string muoRivetPathSherpa       ="/gpfs/cms/users/candelis/Rivet/sherpa/test_prod_mu/out.root";
  string muoRivetPathSherpaUP     ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaleup_mu/out.root";
  string muoRivetPathSherpaDOWN   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_scaledown_mu/out.root";
  string muoRivetPathSherpaPDF1   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfmstw_mu/out.root";
  string muoRivetPathSherpaPDF2   ="/gpfs/cms/users/candelis/Rivet/sherpa/test_pdfnn_mu/out.root";
  //  string muoRivetPathSherpa2NLO           ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01_7TeV_sherpa/out.root";
  string muoRivetPathSherpa2NLO           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/central/out.root";
  string muoRivetPathSherpa2NLOFRdown     ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/FRdown/out.root";
  string muoRivetPathSherpa2NLOFRup       ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/Sherpa2b2/FRup/out.root";
  string muoRivetPathSherpa2NLOQcutdown   ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qcutdown_7TeV_sherpa/out.root";
  string muoRivetPathSherpa2NLOQcutup     ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qcutup_7TeV_sherpa/out.root";
  string muoRivetPathSherpa2NLOQdown      ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qdown_7TeV_sherpa/out.root";
  string muoRivetPathSherpa2NLOQup        ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01Qup_7TeV_sherpa/out.root";
  string muoRivetPathSherpa2NLOmstw       ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01MSTW2008_7TeV_sherpa/out.root";
  string muoRivetPathSherpa2NLOnnpdf      ="/gpfs/cms/users/cossutti/Generators/zjets_studies/sherpa/DYToLL_M_50_mepsnlo01NNPDF_7TeV_sherpa/out.root";
  string muoRivetPathMadGraph     ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleorig/DYtotal.root";
  string muoRivetPathMadGraphDOWN ="/gpfs/cms/users/candelis/Rivet/madgraph/scaledown/DYtotal.root";
  string muoRivetPathMadGraphUP   ="/gpfs/cms/users/candelis/Rivet/madgraph/scaleup/DYtotal.root";
  string muoRivetPathMadGraphPDF1 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfmstw/DYtotal.root";
  string muoRivetPathMadGraphPDF2 ="/gpfs/cms/users/candelis/Rivet/madgraph/pdfnn/DYtotal.root";
  string muoRivetPathPowheg       ="/gpfs/cms/users/candelis/Rivet/powheg/test_mm/out.root";
  string muoRivetPathPowhegMINLO           ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-10/out.root";
  string muoRivetPathPowhegMINLO_05_10     ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/05-10/out.root";
  string muoRivetPathPowhegMINLO_20_10     ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/20-10/out.root";
  string muoRivetPathPowhegMINLO_10_05     ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-05/out.root";
  string muoRivetPathPowhegMINLO_10_20     ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/10-20/out.root";
  string muoRivetPathPowhegMINLO_UP        ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/05-05/out.root";
  string muoRivetPathPowhegMINLO_DOWN      ="/gpfs/cms/users/schizzi/rivet/CMSSW_5_3_11/work/20-20/out.root";

//  //MADGRAPH
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (true, i, eleRivetPathMadGraph, muoRivetPathMadGraph, "/gpfs/cms/users/schizzi/rivet/combination/MadGraph_central.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (true, i, eleRivetPathMadGraphDOWN, muoRivetPathMadGraphDOWN, "/gpfs/cms/users/schizzi/rivet/combination/MadGraph_scaleDOWN.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (true, i, muoRivetPathMadGraphUP, muoRivetPathMadGraphUP, "/gpfs/cms/users/schizzi/rivet/combination/MadGraph_scaleUP.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (true, i, eleRivetPathMadGraphPDF1, muoRivetPathMadGraphPDF1, "/gpfs/cms/users/schizzi/rivet/combination/MadGraph_PDF1.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (true, i, eleRivetPathMadGraphPDF2, muoRivetPathMadGraphPDF2, "/gpfs/cms/users/schizzi/rivet/combination/MadGraph_PDF2.root");
//  }
//  //SHERPA
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpa, muoRivetPathSherpa, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa_central.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpaDOWN, muoRivetPathSherpaDOWN, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa_scaleDOWN.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpaUP, muoRivetPathSherpaUP, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa_scaleUP.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpaPDF1, muoRivetPathSherpaPDF1, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa_PDF1.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpaPDF2, muoRivetPathSherpaPDF2, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa_PDF2.root");
//  }
//  //SHERPA2
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpa2NLO, muoRivetPathSherpa2NLO, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_central.root");
//  }
  for (Int_t i=1;i<15;i++) {
    mergewhateveruwant (false, i, eleRivetPathSherpa2NLOFRdown, muoRivetPathSherpa2NLOFRdown, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_FRdown.root");
  }
  for (Int_t i=1;i<15;i++) {
    mergewhateveruwant (false, i, eleRivetPathSherpa2NLOFRup, muoRivetPathSherpa2NLOFRup, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_FRup.root");
  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpa2NLOQcutdown, muoRivetPathSherpa2NLOQcutdown, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qcutdown.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpa2NLOQcutup, muoRivetPathSherpa2NLOQcutup, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qcutup.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpa2NLOQdown, muoRivetPathSherpa2NLOQdown, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qdown.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpa2NLOQup, muoRivetPathSherpa2NLOQup, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_Qup.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpa2NLOmstw, muoRivetPathSherpa2NLOmstw, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_mstw.root");
//  }
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathSherpa2NLOnnpdf, muoRivetPathSherpa2NLOnnpdf, "/gpfs/cms/users/schizzi/rivet/combination/Sherpa2NLO_nnpdf.root");
//  }
//  //POWHEG
//  for (Int_t i=1;i<15;i++) {
//    mergewhateveruwant (false, i, eleRivetPathPowheg, muoRivetPathPowheg, "/gpfs/cms/users/schizzi/rivet/combination/Powheg_central.root");
//  }
//    for (Int_t i=1;i<15;i++) {
//      mergewhateveruwant (false, i, eleRivetPathPowhegMINLO, muoRivetPathPowhegMINLO, "/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_central.root");
//    }
//    for (Int_t i=1;i<15;i++) {
//      mergewhateveruwant (false, i, eleRivetPathPowhegMINLO_05_10, muoRivetPathPowhegMINLO_05_10, "/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_05-10.root");
//    }
//    for (Int_t i=1;i<15;i++) {
//      mergewhateveruwant (false, i, eleRivetPathPowhegMINLO_20_10, muoRivetPathPowhegMINLO_20_10, "/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_20-10.root");
//    }
//    for (Int_t i=1;i<15;i++) {
//      mergewhateveruwant (false, i, eleRivetPathPowhegMINLO_10_05, muoRivetPathPowhegMINLO_10_05, "/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_10-05.root");
//    }
//    for (Int_t i=1;i<15;i++) {
//      mergewhateveruwant (false, i, eleRivetPathPowhegMINLO_10_20, muoRivetPathPowhegMINLO_10_20, "/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_10-20.root");
//    }
//    for (Int_t i=1;i<15;i++) {
//      mergewhateveruwant (false, i, eleRivetPathPowhegMINLO_UP, muoRivetPathPowhegMINLO_UP, "/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_UP.root");
//    }
//    for (Int_t i=1;i<15;i++) {
//      mergewhateveruwant (false, i, eleRivetPathPowhegMINLO_DOWN, muoRivetPathPowhegMINLO_DOWN, "/gpfs/cms/users/schizzi/rivet/combination/PowhegMINLO_DOWN.root");
//    }

  return 0;
}

void combineLeptonRivet::mergewhateveruwant (bool isMadGraph, Int_t whichobservable, string wichelepath, string wichmuopath, string wheretocombine) {

  bool isMG = isMadGraph;
  Int_t usecase = whichobservable;

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

  Double_t wmean=0.;

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
  if (usecase == 14) {oss1<<"27"; oss2<<"28";}
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
	gDirectory->GetObject (muoname.c_str (), muohisto); // Save ele histogram!
      } else {
	gDirectory->GetObject (muoname.c_str (), muotgraph); // Save muo histogram!
      }
    }
  }


  // BEGIN COMBINATION:

  cout << "Combining " << elename << " for electrons with " << muoname << " for muons..."  << endl;
	
  Int_t nbins_ele;
  Int_t nbins_muo;
  Double_t dummyXvar=0.;
  Double_t dummyYvarEle=0.;
  Double_t dummyYvarMuo=0.;
  Double_t wele=0.;
  Double_t wmuo=0.;

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

  if (isMG) { // Update: il seguente if e' utile come una merda sotto la suola della scarpa!
    wele = elehisto->GetIntegral();
    wmuo = muohisto->GetIntegral();
  } else {
    for (Int_t i=0; i<nbins_ele;i++) {
      eletgraph->GetPoint(i,dummyXvar,dummyYvarEle);
      muotgraph->GetPoint(i,dummyXvar,dummyYvarMuo);
      wele = wele + dummyYvarEle;
      wmuo = wmuo + dummyYvarMuo;
    }
  }

  // Compute weighted mean and sigma for every bin:
  if (isMG) {
    for (Int_t i=1; i<(nbins_ele+1);i++) {
      dummyYvarEle = elehisto->GetBinContent(i);
      dummyYvarMuo = muohisto->GetBinContent(i);
      wmean = dummyYvarEle + dummyYvarMuo;
      combinehisto->SetBinContent(i,wmean);
      combinehisto->SetBinError(i,sqrt(pow(elehisto->GetBinError(i),2)+pow(muohisto->GetBinError(i),2)));
    }
  } else {
    for (Int_t i=0; i<nbins_ele;i++) {
      eletgraph->GetPoint(i,dummyXvar,dummyYvarEle);
      muotgraph->GetPoint(i,dummyXvar,dummyYvarMuo);
      wmean = dummyYvarEle + dummyYvarMuo;
      combinetgraph->SetPoint(i,dummyXvar,wmean);
      combinetgraph->SetPointEYhigh(i,sqrt(pow(eletgraph->GetErrorYhigh(i),2)+pow(muotgraph->GetErrorYhigh(i),2)));
      combinetgraph->SetPointEYlow(i,sqrt(pow(eletgraph->GetErrorYlow(i),2)+pow(muotgraph->GetErrorYlow(i),2)));
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
