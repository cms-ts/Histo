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
#include "TObject.h"
#include <iostream>

#include "TH1.h"
#include "TH2.h"
#include "THStack.h"

#include <string.h>

#include "lumi_scale_factors.h"

bool lumiweights 	= 1;

string plotpath		="./"; //put here the path where you want the plots
string datafile		="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011A.root";
string mcfile		="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A.root";
string back_ttbar	="/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011A.root";
string back_w		="/gpfs/cms/data/2011/jet/jetValidation_w_2011A.root";

string qcd23bc		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-20to30_BCtoE.root";
string qcd38bc		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-30to80_BCtoE.root";
string qcd817bc		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-80to170_BCtoE.root";
string qcd23em		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-20to30_Enriched.root";
string qcd38em		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-30to80_Enriched.root";
string qcd817em		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-80to170_EMEnriched.root";






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


	gROOT->Reset();
	gROOT->ForceStyle();
	gROOT->LoadMacro("tdrStyle.C++");
	tdrStyle();



	TFile *mcf = TFile::Open(mcfile.c_str()); //MC file
	mcf->cd("validationJEC/");
	TDirectory *dir=gDirectory;
	TList *mylist=(TList*)dir->GetListOfKeys();
	TIter iter(mylist);	
	// Use TIter::Next() to get each TObject mom owns.
	TObject* tobj = 0;

int i=0;
	while ( tobj = iter.Next() ) {

	gROOT->Reset();
	gROOT->ForceStyle();
	tdrStyle();
		gStyle->SetPadRightMargin(0.15);

		string name=tobj->GetName();
		TString temp = (TString)name;
		//if(temp.Contains("gsfPfSCEnVsEn")){
		int num=tobj->GetUniqueID();
		cout<<"num is "<<num<<endl;
		comparisonJetMCData(name,1);
		//}
	i++;
	//if(i==1)break;
	}


	return;
}




void comparisonJetMCData(string plot,int rebin){


	string tmp;

	// List of files
	TFile *dataf = TFile::Open(datafile.c_str()); //data file
	TFile *mcf = TFile::Open(mcfile.c_str()); //MC file
	TFile *ttbarf = TFile::Open(back_ttbar.c_str()); //MC background file
	TFile *wf = TFile::Open(back_w.c_str());

	TFile *qcd23emf = TFile::Open(qcd23em.c_str());
	TFile *qcd38emf = TFile::Open(qcd38em.c_str());
	TFile *qcd817emf = TFile::Open(qcd817em.c_str());

	TFile *qcd23bcf = TFile::Open(qcd23bc.c_str());
	TFile *qcd38bcf = TFile::Open(qcd38bc.c_str());
	TFile *qcd817bcf = TFile::Open(qcd817bc.c_str());



	// Canvas
	TCanvas * Canv = (TCanvas*)gDirectory->GetList()->FindObject("Canv");
	if (Canv) delete Canv;
	Canv = new TCanvas("Canv","Canv",0,0,800,600);

	// Getting, defining ...
	dataf->cd("validationJEC");
	
	TObject * obj;
	gDirectory->GetObject(plot.c_str(),obj);


	TH1F *data; 
	TH2F *data2; 
	THStack *hs = new THStack("hs","Total MC");


	int flag=-1;
	if (data = dynamic_cast<TH1F *>(obj) ){
		flag=1;
		gROOT->Reset();
		gROOT->ForceStyle();
		gStyle->SetPadRightMargin(0.03);
		gPad->SetLogy(1);
		gPad->Modified();
		gPad->Update();
	}
	if (data2 = dynamic_cast<TH2F *>(obj)){
		flag=2;
		gStyle->SetPalette(1);
		gStyle->SetPadRightMargin(0.15);
		gPad->Modified();
	}


	//===================
	// Dirty jobs :)
	if (flag==1){
		Canv->cd();
		TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
		pad1->Draw();
		pad1->cd();
		pad1->SetLogy(1);
		TString str=data->GetTitle();
		if (str.Contains("jet") && !str.Contains("Num") && !str.Contains("Eta") && !str.Contains("Phi") && !str.Contains("eld") && !str.Contains("meanPtZVsNjet")) rebin=5;

		//======================
		// DATA
		Double_t dataint = data->Integral();
		data->SetLineColor(kBlack);
		data->Rebin(rebin);
		if(str.Contains("nJetVtx")) data->GetXaxis()->SetRangeUser(0,10);	
		if(str.Contains("zMass")) data->GetXaxis()->SetRangeUser(60,120);	
		data->Draw("E1");

		TLegend* legend = new TLegend(0.60,0.9,0.85,0.75);
		legend->SetFillColor(0);
		legend->SetFillStyle(0);
		legend->SetBorderSize(0);
		legend->AddEntry(data,"data","p");


		//======================
		// Z + jets signal
		mcf->cd("validationJEC");
		TH1F* mc;
		gDirectory->GetObject(plot.c_str(),mc);

		TH1D * hsum =  (TH1D*) mc->Clone();
		hsum->SetTitle("hsum");
		hsum->SetName("hsum");
		hsum->Reset();

		Double_t mcint = mc->Integral();
		mc->SetFillColor(kRed);
		if(lumiweights==0) mc->Scale(dataint/mcint);
		if(lumiweights==1) mc->Scale(zjetsScale);
		mc->Rebin(rebin);
		if(lumiweights==0) mc->Draw("HISTO SAMES");
		hsum->Rebin(rebin);
		hsum->Add(mc);
		legend->AddEntry(mc,"Z+jets","f");

		//======================
		// ttbar
		ttbarf->cd("validationJEC");
		TH1F* ttbar;
		gDirectory->GetObject(plot.c_str(),ttbar);

		ttbar->SetFillColor(kBlue);
		ttbar->Scale(ttbarScale);
		ttbar->Rebin(rebin);
		//ttbar->Draw("HISTO SAMES");
		hsum->Add(ttbar);
		legend->AddEntry(ttbar,"ttbar","f");

		//======================
		// w+jets
		wf->cd("validationJEC");
		TH1F* w;
		gDirectory->GetObject(plot.c_str(),w);

		w->SetFillColor(kViolet+2);
		w->Scale(wjetsScale); 
		w->Rebin(rebin);
		//w->Draw("HISTO SAMES");
		hsum->Add(w);
		legend->AddEntry(w,"W+jets","f");



		//======================
		// QCD EM enriched
		qcd23emf->cd("validationJEC");
		TH1F* qcd23em;
		gDirectory->GetObject(plot.c_str(),qcd23em);

TH1D * qcdTotEM =  (TH1D*) qcd23em->Clone(); //da spostare piÃ¹ in su appena funziona il 23
		qcdTotEM->SetTitle("qcd em");
		qcdTotEM->SetName("qcd em");
		qcdTotEM->Reset();
		qcdTotEM->Rebin(rebin);

		qcd38emf->cd("validationJEC");
		TH1F* qcd38em;
		gDirectory->GetObject(plot.c_str(),qcd38em);


		qcd817emf->cd("validationJEC");
		TH1F* qcd817em;
		gDirectory->GetObject(plot.c_str(),qcd817em);

		qcd23em->Rebin(rebin);
		qcd23em->Scale(qcd23emScale); 
		qcd38em->Rebin(rebin);
		qcd38em->Scale(qcd38emScale); 
		qcd817em->Rebin(rebin);
		qcd817em->Scale(qcd817emScale); 

		qcdTotEM->SetFillColor(kOrange+1);
//		qcdTotEM->Add(qcd23em);
		qcdTotEM->Add(qcd38em);
		qcdTotEM->Add(qcd817em);

		hsum->Add(qcdTotEM);

		legend->AddEntry(qcdTotEM,"QCD em","f");

		
		
		//======================
		// QCD bc
		qcd23bcf->cd("validationJEC");
		TH1F* qcd23bc;
		gDirectory->GetObject(plot.c_str(),qcd23bc);

		TH1D * qcdTotBC =  (TH1D*) qcd23bc->Clone(); //da spostare piÃ¹ in su appena funziona il 23
		qcdTotBC->SetTitle("qcd bc");
		qcdTotBC->SetName("qcd bc");
		qcdTotBC->Reset();
		qcdTotBC->Rebin(rebin);

		qcd38bcf->cd("validationJEC");
		TH1F* qcd38bc;
		gDirectory->GetObject(plot.c_str(),qcd38bc);

		qcd817bcf->cd("validationJEC");
		TH1F* qcd817bc;
		gDirectory->GetObject(plot.c_str(),qcd817bc);

		qcd23bc->Rebin(rebin);
		qcd23bc->Scale(qcd23bcScale); 
		qcd38bc->Rebin(rebin);
		qcd38bc->Scale(qcd38bcScale); 
		qcd817bc->Rebin(rebin);
		qcd817bc->Scale(qcd817bcScale); 

		qcdTotBC->SetFillColor(kGreen+2);
		qcdTotBC->Add(qcd23bc);
		qcdTotBC->Add(qcd38bc);
		qcdTotBC->Add(qcd817bc);

		hsum->Add(qcdTotBC);

		legend->AddEntry(qcdTotBC,"QCD bc","f");


		//======================
		// Add here other backgrounds


		//======================
		// Stacked Histogram
		hs->Add(qcdTotEM);
		hs->Add(qcdTotBC);
		hs->Add(w);
		hs->Add(ttbar);
		hs->Add(mc); //Z+Jets
		
		// per avere le statistiche
		if(lumiweights==1) hsum->Draw("HISTO SAMES");
		
		//======================
		// Setting the stats
		pad1->Update(); // altrimenti non becchi la stat
		TPaveStats *r2;
		if(lumiweights==0) r2 = (TPaveStats*)mc->FindObject("stats");
		if(lumiweights==1) r2 = (TPaveStats*)hsum->FindObject("stats");
		r2->SetY1NDC(0.875);
		r2->SetY2NDC(0.75); 
		r2->SetTextColor(kRed);
		r2->Draw();
		
		if(lumiweights==1) hs->Draw("SAME");
		data->Draw("E1 SAMES");
		legend->Draw();
		Canv->Update();

	


		//===============//
		// RATIO DATA MC //
		//===============//
		Canv->cd();
		TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
		pad2->Draw();
		pad2->cd();
		TH1D * ratio =  (TH1D*) data->Clone();
		ratio->SetTitle("ratio");
		ratio->SetName("ratio");
		ratio->Reset();

		ratio->Sumw2();
		data->Sumw2();
		hsum->Sumw2(); // FIXME controlla che sia corretto questo... 
		ratio->SetMarkerSize(.5);
		ratio->SetLineColor(kBlack);
		ratio->SetMarkerColor(kBlack);
		ratio->SetMarkerSize(.5);
		ratio->SetMarkerStyle(3);
		ratio->Divide(data,mc,1.,1.);
		ratio->GetYaxis()->SetRangeUser(0,2);	
		pad2->SetTopMargin(1);
		ratio->Draw("E1");
		
		TLine *OLine = new TLine(ratio->GetXaxis()->GetXmin(),1.,ratio->GetXaxis()->GetXmax(),1.);
		OLine->SetLineColor(kBlack);
		OLine->SetLineStyle(2);
		OLine->Draw();

		TPaveStats *r3 = (TPaveStats*)ratio->FindObject("stats");
		r3->SetX1NDC(0.01);
		r3->SetX2NDC(0.10); 
		r3->SetY1NDC(0.20);
		r3->SetY2NDC(0.50); 
		r3->SetTextColor(kWhite);
		r3->SetLineColor(kWhite);
		r3->Draw();
		Canv->Update();

		tmp=plotpath+plot+".png";
		Canv->Print(tmp.c_str());

	}
	else if (flag==2){
		//Canv.Divide(2,1);
		//Canv.cd(1);

		// data
		dataf->cd("validationJEC");
		gDirectory->GetObject(plot.c_str(),data2);
		data2->Draw("COLZ");

		gPad->Update(); // altrimenti non becchi la stat
		TPaveStats *r1 = (TPaveStats*)data2->FindObject("stats");
		r1->SetX1NDC(0.70);
		r1->SetX2NDC(0.85); 
		r1->Draw();
		Canv->Update();

		tmp=plotpath+plot+"data.png";
		Canv->Print(tmp.c_str());


		//Canv.cd(2);
		// montecarlo
		mcf->cd("validationJEC");
		gDirectory->GetObject(plot.c_str(),data2);

		data2->SetMinimum(1);
		data2->Draw("COLZ");

		gPad->Update(); // altrimenti non becchi la stat
		TPaveStats *r2 = (TPaveStats*)data2->FindObject("stats");
		r2->SetX1NDC(0.70);
		r2->SetX2NDC(0.85); 
		r2->Draw();
		Canv->Update();

		tmp=plotpath+plot+"mc.png";
		Canv->Print(tmp.c_str());
	}
	else { cout << "You're getting an exception! Most likely there's no histogram here... \n"; }

	delete data;
	delete data2;
	delete hs;
	delete Canv;



	dataf->Close();
	mcf->Close();
	ttbarf->Close();
	wf->Close();
	//qcd23emf->Close();
	qcd38emf->Close();
	qcd817emf->Close();
	qcd23bcf->Close();
	qcd38bcf->Close();
	qcd817bcf->Close();


	return;
}

