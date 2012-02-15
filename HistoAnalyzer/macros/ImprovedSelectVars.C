#include "PlotsFeeder.C"
#include "TFile.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include <vector>
#include "tdrStyle.C"

void ImprovedSelectVars(){

TFile *Analysis = new TFile("IsoPlots.root", "RECREATE", "IsoPlots");


	gROOT->LoadMacro("PlotsFeeder.C++");
	PlotsFeeder datajet("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011B_v2_11.root");
	PlotsFeeder zjet("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011B_v1_11.root");
	PlotsFeeder wjet("/gpfs/cms/data/2011/jet/jetValidation_w_2011A_v1_10.root");
	PlotsFeeder ttbar("/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011A_v1_10.root");

	int numbofvertices=15;

	gROOT->ForceStyle();
	tdrStyle();

	//NEW STUFF
	TObjArray* histarray = new TObjArray();
	//

	stringstream oss;
	std::string numb;
	
	//----------
	//  LOOP!
	for (int i=1;i<=numbofvertices;i++){
		oss<<i;
	
		
		//============
		numb="datajet";
		numb=numb+oss.str();
		TDirectory *dir=Analysis->mkdir(numb.c_str());

		histarray = datajet.Loop(i);
		dir->cd();
		histarray->Write();

		//============
		numb="zjet";
		numb=numb+oss.str();
		dir=Analysis->mkdir(numb.c_str());

		histarray = zjet.Loop(i);
		dir->cd();
		histarray->Write();

		//============
		numb="wjet";
		numb=numb+oss.str();
		dir=Analysis->mkdir(numb.c_str());

		histarray = wjet.Loop(i);
		dir->cd();
		histarray->Write();

		//============
		numb="ttbar";
		numb=numb+oss.str();
		dir=Analysis->mkdir(numb.c_str());

		histarray = ttbar.Loop(i);
		dir->cd();
		histarray->Write();
		oss.clear();
		oss.str("");
	}
Analysis->Close();
}
