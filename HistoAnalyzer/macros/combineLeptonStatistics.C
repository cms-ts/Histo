#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
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

// INSTRUCTIONS:
// .L combineLeptonStatistics.C++
// combineLeptonStatistics()
// CONGRATULATIONS!

int combineLeptonStatistics () {

  //  setTDRStyle ();

  string elePathFile;
  string muoPathFile;

  elePathFile="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3PostApproval.root";
  muoPathFile="/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3PostApprovalMu.root";

  TFile output_file("/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3PostApprovalCombined.root","RECREATE");

  // BEGIN COMBINATION:

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

  double wmean=0.;
  double wsigma=0.;

  while ((tobj1 = iter1.Next ())) {
    elename = tobj1->GetName ();
    if (elename == "N hMatx" || elename == "jTrue" || elename == "jMatx" || elename == "jData" || elename == "jMCreco") continue;
    histofile1->cd ("");
    gDirectory->GetObject (elename.c_str (), elehisto); // Save ele histogram!
    
    iter2.Reset();
    while ((tobj2 = iter2.Next ())) {
      muoname = tobj2->GetName ();
      if (muoname == "N hMatx" || muoname == "jTrue" || muoname == "jMatx" || muoname == "jData" || muoname == "jMCreco") continue;
      if (muoname == elename) {
	histofile2->cd ("");
	gDirectory->GetObject (muoname.c_str (), muohisto); // Save muo histogram!
	
	cout << "Combining " << elename << " for electrons with " << muoname << " for muons..."  << endl;
	
	int nbins_ele;
	int nbins_muo;
	
	nbins_ele = elehisto->GetNbinsX();
	nbins_muo = muohisto->GetNbinsX();
	
	if (nbins_ele != nbins_muo) {cout << "ERROR: combining histos with different binning... exit." << endl; return 0;}

	//	combinehisto->Reset();
	//	TH1D *combinehisto;
	combinehisto = (TH1D *) elehisto->Clone ("elehisto");
	combinehisto->SetName(muoname.c_str ());
	combinehisto->SetTitle(muoname.c_str ());

	// Compute weighted mean and sigma for every bin:
	for (int i=1; i<(nbins_ele+1);i++) {
	  wmean =   (elehisto->GetBinContent(i)/(elehisto->GetBinError(i)*elehisto->GetBinError(i)) 
		   + muohisto->GetBinContent(i)/(muohisto->GetBinError(i)*muohisto->GetBinError(i))) 
	    / (1./(elehisto->GetBinError(i)*elehisto->GetBinError(i)) 
	       + 1./(muohisto->GetBinError(i)*muohisto->GetBinError(i)));
	  wsigma = 1./sqrt(1./(elehisto->GetBinError(i)*elehisto->GetBinError(i)) 
			   + 1./(muohisto->GetBinError(i)*muohisto->GetBinError(i)));
	  combinehisto->SetBinContent(i,wmean);
	  combinehisto->SetBinError(i,wsigma);
	}

	output_file.cd();
	combinehisto->Write();

      }
    }
  }

  histofile1->Close();
  histofile2->Close();
  output_file.Close();
  cout << "Congratulations, combination achieved!" << endl;
  return 0;
}
