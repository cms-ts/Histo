#include "MMutil.C"
#include "tdrstyle.C"
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"

	TCanvas a;

void comparisonJetMCData(string plot,int rebin){

	
	gROOT->ForceStyle();
	setTDRStyle();

	TFile *dataf = TFile::Open("rfio:/gpfs/cms/data/2011/jet/jetanalysis-200pb-zfilt.root"); //data file
	//TFile *mcf = TFile::Open("rfio:/gpfs/cms/data/2011/jet/jetanalysis-DYtoLLmadgraph-zfilt-191pb.root"); //MC file
	TFile *mcf = TFile::Open("rfio:/gpfs/cms/data/2011/jet/sum.root"); //MC file
	dataf->cd("validationJEC");
	//gDirectory->ls();
	//cout<<"Above you see the fields you could draw...press any key to go..."<<endl;
	//string b;
	//cin>>b;
	//Numero di entries
	TH1F* obj;
	TH1F *probe; 
	TH2F *probe2; 
	TH2F *obje;
	obj=gDirectory->GetObject(plot.c_str(),obj);
	obje=gDirectory->GetObject(plot.c_str(),obje);

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
	  string path="/afs/infn.it/ts/user/marone/html/ZJets/Jets/"+plot+".png";
	  a.Print(path.c_str());
	}
	
	if (probe2 = dynamic_cast<TH2F *>(obje)){
	  //a.Divide(2,1);
	  //a.cd(1);
	  gStyle->SetPalette(1);
	  gStyle->SetNumberContours(999);
	  dataf->cd("validationJEC");
	  gDirectory->GetObject(plot.c_str(),obje);
	  obje->Draw("COLZ");
	  string path="/afs/infn.it/ts/user/marone/html/ZJets/Jets/"+plot+"data.png";
	  a.Print(path.c_str());
	  //a.cd(2);
	  gStyle->SetPalette(1);
	  gStyle->SetNumberContours(999);
	  mcf->cd("validationJEC");
	  gDirectory->GetObject(plot.c_str(),obje);
	  obje->Draw("COLZ");
	  string path="/afs/infn.it/ts/user/marone/html/ZJets/Jets/"+plot+"mc.png";
	  a.Print(path.c_str());
	}
	
	return;
}

