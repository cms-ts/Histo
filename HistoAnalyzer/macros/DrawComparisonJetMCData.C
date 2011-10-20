#include "tdrStyle.C"

#include <TROOT.h>
#include "TStyle.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TLine.h"
#include <iostream>


#include "TH1.h"
#include "TH2.h"

#include <string.h>

using namespace std;

void comparisonJetMCData(string plot,int rebin);


void DrawComparisonJetMCData(void){
	struct STestFunctor {
		bool operator()(TObject *aObj) {
			//cout<<"pippo"<<endl;
			//comparisonJetMCData(aObj->GetTitle,1);
			return true;
		}
	};


	gROOT->ForceStyle();
	gROOT->LoadMacro("tdrStyle.C++");
	tdrStyle();

	

	TFile *mcf = TFile::Open("rfio:/gpfs/cms/data/2011/jet/jetanalysis-DYtoLLmadgraph-zfilt-191pb.root"); //MC file
	mcf->cd("validationJEC/");
	TDirectory *dir=gDirectory;
	TList *mylist=(TList*)dir->GetListOfKeys();
	TIter iter(mylist);	
	// Use TIter::Next() to get each TObject mom owns.
	TObject* tobj = 0;

	int i=0;
	while ( tobj = iter.Next() ) {
		string name=tobj->GetName();
		int num=tobj->GetUniqueID();
		cout<<"num is "<<num<<endl;
		comparisonJetMCData(name,1);
		//if(i=14) break;
		i++;
	}

	return;
}




void comparisonJetMCData(string plot,int rebin){


	string plotpath="./"; //put here the path where you want the plots
	string datafile="rfio:/gpfs/cms/data/2011/jet/jetanalysis-200pb-zfilt.root";
	string mcfile="rfio:/gpfs/cms/data/2011/jet/sum.root";

	string tmp;


	TFile *dataf = TFile::Open(datafile.c_str()); //data file
	TFile *mcf = TFile::Open(mcfile.c_str()); //MC file
	dataf->cd("validationJEC");

	TCanvas * Canv = (TCanvas*)gDirectory->GetList()->FindObject("Canv");
	if (Canv) delete Canv;
	Canv = new TCanvas("Canv","Canv",0,0,800,600);

	TH1F * obj;
	gDirectory->GetObject(plot.c_str(),obj);
	
	TH2F * obje;
	gDirectory->GetObject(plot.c_str(),obje);

	TH1F *probe; 
	TH2F *probe2; 

	if (probe = dynamic_cast<TH1F *>(obj) ){
		TString str=obj->GetTitle();
		if (str.Contains("jet") && !str.Contains("Num") && !str.Contains("Eta") && !str.Contains("Phi") && !str.Contains("eld") && !str.Contains("h_meanPtZVsNjet")) rebin=5;
		gPad->SetLogy(1);
		Int_t entries = obj->Integral();
		//printf("Useful data:\ndata entries= %d \n",entries);
		obj->SetLineColor(kBlack);
		obj->GetXaxis()->SetRangeUser(0,250);
		obj->Rebin(rebin);
		obj->Draw("E1");
		mcf->cd("validationJEC");
		TH1F* obj;
		gDirectory->GetObject(plot.c_str(),obj);
		Int_t entriesmc = obj->Integral();
		//printf("Useful data:\ndata entries= %d \n",entries);
		obj->SetLineColor(kRed);
		obj->Scale((double) entries/(double)entriesmc);
		obj->Rebin(rebin);
		obj->Draw("SAMES");
		tmp=plotpath+plot+".png";
		Canv->Print(tmp.c_str());

	}

	if (probe2 = dynamic_cast<TH2F *>(obje)){
		//Canv.Divide(2,1);
		//Canv.cd(1);
		gStyle->SetPalette(1);
		gStyle->SetNumberContours(999);
		dataf->cd("validationJEC");
		gDirectory->GetObject(plot.c_str(),obje);
		obje->Draw("COLZ");
		tmp=plotpath+plot+"data.png";
		Canv->Print(tmp.c_str());
		//Canv.cd(2);
		gStyle->SetPalette(1);
		gStyle->SetNumberContours(999);
		mcf->cd("validationJEC");
		gDirectory->GetObject(plot.c_str(),obje);
		obje->Draw("COLZ");
		tmp=plotpath+plot+"mc.png";
		Canv->Print(tmp.c_str());
	}

	return;
}

