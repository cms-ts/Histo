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
#include <sstream>

#include "TH1.h"
#include "TH2.h"
#include "THStack.h"

#include <string.h>

#include "lumi_scale_factors.h"

bool lumiweights 	= 1;	//se 0 scala sull'integrale dell'area, se 1 scala sulla luminosita' integrata

string plotpath		="./"; //put here the path where you want the plots
//string datafile		="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011A.root";
string datafile		="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011A_v1_4.root";
string mcfile		="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_4.root"; 
string back_ttbar	="/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011A_v1_4.root"; 
string back_w		="/gpfs/cms/data/2011/jet/jetValidation_w_2011A_v1_4.root";

string qcd23bc		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-20to30_BCtoE_v1_4.root";
string qcd38bc		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-30to80_BCtoE_v1_4.root";
string qcd817bc		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-80to170_BCtoE_v1_4.root";
string qcd23em		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-20to30_Enriched_v1_4.root";
string qcd38em		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-30to80_Enriched_v1_4.root";
string qcd817em		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-80to170_EMEnriched_v1_4.root";

double zwemean=12.; //le inizializzo a valori molto sbagliati, cosÃ¬ se non vengono modificate me ne accorgo
double wwemean=130.;
double ttwemean=140.;




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
	string tmpname;

int i=0;
	while ( tobj = iter.Next() ) {

	gROOT->Reset();
	gROOT->ForceStyle();
	tdrStyle();
		gStyle->SetPadRightMargin(0.15);

		string name=tobj->GetName();
		TString temp = (TString)name;
		
		int num=tobj->GetUniqueID();
		cout<<"num is "<<num<<endl;
		if(temp.Contains("weight")){
		
		TFile *mcf = TFile::Open(mcfile.c_str()); 
		TFile *ttbarf = TFile::Open(back_ttbar.c_str()); 
		TFile *wf = TFile::Open(back_w.c_str());

		TCanvas * Canv = (TCanvas*)gDirectory->GetList()->FindObject("Canv");
		if (Canv) delete Canv;
		Canv = new TCanvas("Canv","Canv",0,0,800,600);

		gPad->SetLogy(1);
		
		mcf->cd("validationJEC");
		TH1F* mc;
		gDirectory->GetObject(name.c_str(),mc);
		if(mc){
		mc->SetFillColor(kRed);
		mc->GetXaxis()->SetRangeUser(0.,2.);
		mc->Draw();
		zwemean = mc->GetMean();
		tmpname=plotpath+name+"-zjets.png";
		Canv->Print(tmpname.c_str());
		}

		ttbarf->cd("validationJEC");
		TH1F* ttbar;
		gDirectory->GetObject(name.c_str(),ttbar);
	
		if(ttbar){
		ttbar->SetFillColor(kBlue);
		ttbar->GetXaxis()->SetRangeUser(0.,2.);
		ttbar->Draw();
		ttwemean = ttbar->GetMean();
		tmpname=plotpath+name+"-ttbar.png";
		Canv->Print(tmpname.c_str());
		}

		wf->cd("validationJEC");
		TH1F* w;
		gDirectory->GetObject(name.c_str(),w);
		if(w){
		w->SetFillColor(kViolet+2);
		w->GetXaxis()->SetRangeUser(0.,2.);
		w->Draw();
		wwemean = w->GetMean();
		tmpname=plotpath+name+"-wjets.png";
		Canv->Print(tmpname.c_str());
		}
	

		}
		else comparisonJetMCData(name,1);
	
	
	i++;
	//if(i==2)break;
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
		if (str.Contains("jet") && !str.Contains("zMass") && !str.Contains("Num") && !str.Contains("Eta") && !str.Contains("Phi") && !str.Contains("eld") && !str.Contains("meanPtZVsNjet")) rebin=5;


		//======================
		// DATA
		Double_t dataint = data->Integral();
		data->SetLineColor(kBlack);
		data->Rebin(rebin);
		if(str.Contains("nJetVtx")) data->GetXaxis()->SetRangeUser(0,10);	
		if(str.Contains("zMass")) data->GetXaxis()->SetRangeUser(60,120);	
		data->SetMinimum(1.);
		data->Sumw2();
		data->Draw("E1");

		TLegend* legend = new TLegend(0.825,0.57,0.95,0.72);
		legend->SetFillColor(0);
		legend->SetFillStyle(0);
		legend->SetBorderSize(0);
		legend->AddEntry(data,"data","p");


		//======================
		// Z + jets signal
		mcf->cd("validationJEC");
		TH1F* mc;
		gDirectory->GetObject(plot.c_str(),mc);
		TH1D * hsum;
		
		if(mc){
		hsum =  (TH1D*) mc->Clone();
		hsum->SetTitle("hsum");
		hsum->SetName("hsum");
		hsum->Reset();

		Double_t mcint = mc->Integral();
		mc->SetFillColor(kRed);
		mc->Sumw2();
		if(lumiweights==0) mc->Scale(dataint/mcint);
		if(lumiweights==1) mc->Scale(zjetsScale);
		if(lumiweights==1) mc->Scale(915./904.); // perche' il mc non e' completo...
		if(lumiweights==1) mc->Scale(1.-zwemean+1.);  // perche' i Weights non fanno 1...
		mc->Rebin(rebin);
		if(lumiweights==0) mc->Draw("HISTO SAMES");
		hsum->Rebin(rebin);
		hsum->Add(mc);
		legend->AddEntry(mc,"Z+jets","f");
		}

		//======================
		// ttbar
		ttbarf->cd("validationJEC");
		TH1F* ttbar;
		gDirectory->GetObject(plot.c_str(),ttbar);
	
		if(ttbar){
		ttbar->SetFillColor(kBlue);
		ttbar->Sumw2();
		ttbar->Scale(ttbarScale);
		//ttbar->Scale(24./23.);  // il mc non Ã¨ completo...
		ttbar->Scale(1.-ttwemean+1.);  // perche' i Weights non fanno 1...
		ttbar->Rebin(rebin);
		//ttbar->Draw("HISTO SAMES");
		hsum->Add(ttbar);
		if(lumiweights==1)legend->AddEntry(ttbar,"ttbar","f");
		}

		//======================
		// w+jets
		wf->cd("validationJEC");
		TH1F* w;
		gDirectory->GetObject(plot.c_str(),w);
		if(w){

		w->SetFillColor(kViolet+2);
		w->Sumw2();
		w->Scale(wjetsScale); 
		w->Scale(1.-wwemean+1.);  // perche' i Weights non fanno 1...
		w->Scale(438./330.); // il mc non Ã¨ completo... 
		w->Rebin(rebin);
		//w->Draw("HISTO SAMES");
		hsum->Add(w);
		if(lumiweights==1)legend->AddEntry(w,"W+jets","f");
		}

		//======================
		// QCD EM enriched
		qcd23emf->cd("validationJEC");
		TH1F* qcd23em;
		gDirectory->GetObject(plot.c_str(),qcd23em);

		if(qcd23em){
		TH1D * qcdTotEM =  (TH1D*) qcd23em->Clone(); 
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
		qcd23em->Sumw2();
		qcd23em->Scale(qcd23emScale); 
		qcd38em->Rebin(rebin);
		qcd38em->Sumw2();
		qcd38em->Scale(qcd38emScale); 
		qcd817em->Rebin(rebin);
		qcd817em->Sumw2();
		qcd817em->Scale(qcd817emScale); 

		qcdTotEM->SetFillColor(kOrange+1);
		qcdTotEM->Add(qcd23em);
		qcdTotEM->Add(qcd38em);
		qcdTotEM->Add(qcd817em);

		hsum->Add(qcdTotEM);

		if(lumiweights==1)legend->AddEntry(qcdTotEM,"QCD em","f");
		}
		
		//======================
		// QCD bc
		qcd23bcf->cd("validationJEC");
		TH1F* qcd23bc;
		gDirectory->GetObject(plot.c_str(),qcd23bc);

		if(qcd23bc){
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
		qcd23bc->Sumw2();
		qcd23bc->Scale(qcd23bcScale); 
		qcd38bc->Rebin(rebin);
		qcd38bc->Sumw2();
		qcd38bc->Scale(qcd38bcScale); 
		qcd817bc->Rebin(rebin);
		qcd817bc->Sumw2();
		qcd817bc->Scale(qcd817bcScale); 

		qcdTotBC->SetFillColor(kGreen+2);
		qcdTotBC->Add(qcd23bc);
		qcdTotBC->Add(qcd38bc);
		qcdTotBC->Add(qcd817bc);

		hsum->Add(qcdTotBC);

		if(lumiweights==1)legend->AddEntry(qcdTotBC,"QCD bc","f");
		}

		//======================
		// Add here other backgrounds


		//======================
		// Stacked Histogram
		//if(qcd23em) 	hs->Add(qcdTotEM);
		//if(qcd23bc) 	hs->Add(qcdTotBC);
		if(w)  		hs->Add(w);
		if(ttbar)	hs->Add(ttbar);
		if(mc)		hs->Add(mc); //Z+Jets
		
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
		
		if(lumiweights==1) hs->Draw("HISTO SAME");
		gPad->RedrawAxis();
		data->Draw("E1 SAMES");
		r2->Draw();
		legend->Draw();
		TLegend* lumi = new TLegend(0.60,0.9,0.85,0.75);
		lumi->SetFillColor(0);
		lumi->SetFillStyle(0);
		lumi->SetBorderSize(0);
		lumi->AddEntry((TObject*)0,"L=2.050 1/fb",""); // mean on Y
		lumi->Draw();
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
		gStyle->SetOptStat("m");
		ratio->Divide(data,mc,1.,1.);
		ratio->GetYaxis()->SetRangeUser(0,2);	
		pad2->SetTopMargin(1);
		ratio->Draw("E1");
		
		TLine *OLine = new TLine(ratio->GetXaxis()->GetXmin(),1.,ratio->GetXaxis()->GetXmax(),1.);
		OLine->SetLineColor(kBlack);
		OLine->SetLineStyle(2);
		OLine->Draw();
 
		TLegend* label = new TLegend(0.60,0.9,0.85,0.75);
		label->SetFillColor(0);
		label->SetFillStyle(0);
		label->SetBorderSize(0);
		//horrible mess
		double binContent = 0;
		double binSum = 0;
		double weightSum = 0;
		double binError = 1;
		double totalbins = ratio->GetSize() -2;
		for(unsigned int bin=1;bin<=totalbins;bin++){
			binContent = ratio->GetBinContent(bin);
			binError = ratio->GetBinError(bin);
			if(binError!=0){
				binSum += binContent/binError;
				weightSum += 1./binError;
			}
		}
		double ymean = binSum / weightSum;
		//double ymean = ratio->GetMean(2);
		stringstream sYmean;
		sYmean << ymean;
		string labeltext=sYmean.str()+" mean Y";
		//label->AddEntry((TObject*)0,labeltext.c_str(),""); // mean on Y
		//label->Draw();
		
		TPaveStats *r3 = (TPaveStats*)ratio->FindObject("stats");
		r3->SetX1NDC(0.01);
		r3->SetX2NDC(0.10); 
		r3->SetY1NDC(0.20);
		r3->SetY2NDC(0.50); 
		gStyle->SetOptStat("mr");
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

