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
#include "TProfile.h"
#include "THStack.h"

#include <string.h>

#include "lumi_scale_factors.h"

bool lumiweights 	= 1;	//se 0 scala sull'integrale dell'area, se 1 scala sulla luminosita' integrata
bool useLog             = 1;

string plotpath		="/afs/infn.it/ts/user/marone/html/ZJets/Observables/"; 
//string plotpath		="test/"; //put here the path where you want the plots
string datafile		="DATA.root";
string mcfile		="MC_zjets.root"; 
string back_ttbar	="MC_ttbar.root"; 
string back_w		="/afs/infn.it/ts/project/cms/users/montanin/SPERO/CMSSW_4_4_2/src/Histo/HistoAnalyzer/work/AngDist/angDistW2011A_v12fake.root";

string datafile2       	="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_15.root";
string mcfile2		="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_15.root"; 
string back_ttbar2	="/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011A_v2_14.root"; 
string back_w2		="/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011A_v2_14.root";

string qcd23bc		="/afs/infn.it/ts/project/cms/users/montanin/SPERO/CMSSW_4_4_2/src/Histo/HistoAnalyzer/work/AngDist/angDistW2011A_v12fake.root";
string qcd38bc		="/afs/infn.it/ts/project/cms/users/montanin/SPERO/CMSSW_4_4_2/src/Histo/HistoAnalyzer/work/AngDist/angDistW2011A_v12fake.root";
string qcd817bc		="/afs/infn.it/ts/project/cms/users/montanin/SPERO/CMSSW_4_4_2/src/Histo/HistoAnalyzer/work/AngDist/angDistW2011A_v12fake.root";
string qcd23em		="/afs/infn.it/ts/project/cms/users/montanin/SPERO/CMSSW_4_4_2/src/Histo/HistoAnalyzer/work/AngDist/angDistW2011A_v12fake.root";
string qcd38em		="/afs/infn.it/ts/project/cms/users/montanin/SPERO/CMSSW_4_4_2/src/Histo/HistoAnalyzer/work/AngDist/angDistW2011A_v12fake.root";
string qcd817em		="/afs/infn.it/ts/project/cms/users/montanin/SPERO/CMSSW_4_4_2/src/Histo/HistoAnalyzer/work/AngDist/angDistW2011A_v12fake.root";

double zwemean=-10.; //le inizializzo a valori molto sbagliati, cosÃ¬ se non vengono modificate me ne accorgo
double wwemean=-100.;
double ttwemean=-1000.;

double dataNumEvents=-999;
double zNumEvents=-999; //lo definisco globale anche se non Ã¨ la cosa piÃ¹ bella da fare
double ttNumEvents=-999; //questo lavoro andrebbe fatto anche per i qcd... 
double wNumEvents=-999; //al momento non l'ho fatto perchÃ© passano 0 eventi e e' gran smeno

using namespace std;

void comparisonAngMCData(string plot,int rebin);
double numEventsPerStep(string filename, string dir);



void DrawComparisonAngMCData(void){
	struct STestFunctor {
		bool operator()(TObject *aObj) {
			//cout<<"pippo"<<endl;
			//comparisonAngMCData(aObj->GetTitle,1);
			return true;
		}
	};


	gROOT->Reset();
	gROOT->ForceStyle();
	gROOT->LoadMacro("tdrStyle.C++");
	tdrStyle();

	// Recupero l'informazione sul numero di eventi processati per singolo MC
	dataNumEvents = numEventsPerStep(datafile2, "demo"); 
	zNumEvents = numEventsPerStep(mcfile2, "demo"); 
	ttNumEvents = numEventsPerStep(back_ttbar2, "demo"); 
	wNumEvents = numEventsPerStep(back_w2, "demo"); 
	// ---------------------------------------------------


	TFile *mcf = TFile::Open(mcfile.c_str()); //MC file
	//mcf->cd("validationJEC/");
	mcf->cd();
	TDirectory *dir=gDirectory;
	TList *mylist=(TList*)dir->GetListOfKeys();
	TIter iter(mylist);	
	// Use TIter::Next() to get each TObject mom owns.
	TObject* tobj = 0;
	string tmpname;

	int i=0; // solo di servizio quando debuggo...
	while ( tobj = iter.Next() ) {

	   gROOT->Reset();
	   gROOT->ForceStyle();
	   tdrStyle();
	   gStyle->SetPadRightMargin(0.15);
	   
	   string name=tobj->GetName();
	   TString temp = (TString)name;
	   
	   int num=tobj->GetUniqueID();
	   //cout<<"num is "<<num<<endl;
	   //if(temp.Contains("weight")){
	   if(i==0){
	      
		   TFile *mcf2 = TFile::Open(mcfile2.c_str()); 
		   TFile *ttbarf2 = TFile::Open(back_ttbar2.c_str()); 
		   TFile *wf2 = TFile::Open(back_w2.c_str());
		   
		   TCanvas * Canv = (TCanvas*)gDirectory->GetList()->FindObject("Canv");
		   if (Canv) delete Canv;
		   Canv = new TCanvas("Canv","Canv",0,0,800,600);
		   
		   gPad->SetLogy(1);
		   
		   //---- weights
		   mcf2->cd("validationJEC");
		   //mcf2->cd();
		   TH1F* mc;
		   gDirectory->GetObject("h_weights",mc);
		   if(mc){
		      mc->SetFillColor(kRed);
		      mc->GetXaxis()->SetRangeUser(0.,12.);
		      mc->SetMinimum(1.);
		      mc->Draw();
		      zwemean = mc->GetMean();
		      tmpname=plotpath+name+"-zjets.png";
		      Canv->Print(tmpname.c_str());
		   }
		   
		   //---- weights
		   ttbarf2->cd("validationJEC");
		   //ttbarf->cd();
		   TH1F* ttbar;
		   gDirectory->GetObject("h_weights",ttbar);
		   
		   if(ttbar){
		      ttbar->SetFillColor(kBlue);
		      ttbar->GetXaxis()->SetRangeUser(0.,2.);
		      ttbar->Draw();
		      ttwemean = ttbar->GetMean();
		      tmpname=plotpath+name+"-ttbar.png";
		      Canv->Print(tmpname.c_str());
		   }
		   
		   //---- weights
		   wf2->cd("validationJEC");
		   //wf->cd();
		   TH1F* w;
		   gDirectory->GetObject("h_weights",w);
		   if(w){
		      w->SetFillColor(kViolet+2);
		      w->GetXaxis()->SetRangeUser(0.,2.);
		      w->Draw();
		      wwemean = w->GetMean();
		      tmpname=plotpath+name+"-wjets.png";
		      Canv->Print(tmpname.c_str());
		   }
		   
		}
	   
		comparisonAngMCData(name,1);
	
		
	//i++;
	//if(i==7) return;
	}


	// AVVISI AI NAVIGANTI
	//if(dataNumEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DEI DATI, quindi ho normalizzato sugli eventi totali del campione\n";
	//else cout << "Il numero di eventi (dati) " << dataNumEvents << "\n";
	
	if(zNumEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DELLO Z+JETS, quindi ho normalizzato sugli eventi totali del campione\n";
	else cout << "Il numero di eventi di Z+jets " << zNumEvents << "\n";
	
	if(ttNumEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DEL TTBAR+JETS, quindi ho normalizzato sugli eventi totali del campione\n";
	else cout << "Il numero di eventi di ttbar+jets " << ttNumEvents << "\n";
	
	
	if(wNumEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DEL W+JETS, quindi ho normalizzato sugli eventi totali del campione\n";
	else cout << "Il numero di eventi di W+jets " << wNumEvents << "\n";
	
	return;
}


//==================================
//	      Funzioni
//==================================

void comparisonAngMCData(string plot,int rebin){


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
	//dataf->cd("validationJEC");
	dataf->cd();
	
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
		if (useLog) gPad->SetLogy(1);
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
		if (useLog) pad1->SetLogy(1);
		TString str=data->GetTitle();
		//if (str.Contains("jet") && !str.Contains("zMass") && !str.Contains("Num") && !str.Contains("Eta") && !str.Contains("Phi") && !str.Contains("eld") && !str.Contains("meanPtZVsNjet")) rebin=5;
/*		if (str.Contains("jetHt"))rebin=10;
		if ((str.Contains("InvMass") || str.Contains("jet12Pt") || str.Contains("jetHt")) && str.Contains("j2"))rebin=10;
		if ((str.Contains("InvMass") || str.Contains("jet12Pt") || str.Contains("jetHt")) && str.Contains("j3"))rebin=25;
		if ((str.Contains("InvMass") || str.Contains("jet12Pt") || str.Contains("jetHt")) && str.Contains("j4"))rebin=30;

		if (str.Contains("delta") && ( str.Contains("300-1500")|| str.Contains("j4") )) rebin=10;
		if (str.Contains("delta") && ( str.Contains("180-300")|| str.Contains("j3") )) rebin=5;
		if (str.Contains("delta") && ( str.Contains("100-180")|| str.Contains("j2") )) rebin=4;
		if (str.Contains("delta") && ( str.Contains("j1") )) rebin=2;

		if ( (str.Contains("1") || str.Contains("2")) &&  str.Contains("deltaY")) rebin=2;
		if (str.Contains("3") &&  str.Contains("deltaY")) rebin=5;
		if (str.Contains("deltaPhiJetTot")) rebin=5;
		if (str.Contains("phi") && str.Contains("Star")) rebin=2;
		if (str.Contains("Theta")) rebin=2;

		if ((str.Contains("atDividedQ") || str.Contains("phiEtaStar")) 
		    && (str.Contains("j1") || str.Contains("j2"))) rebin=2;
		if ((str.Contains("atDividedQ") || str.Contains("phiEtaStar")) && str.Contains("j3") ) rebin=5;
		if ((str.Contains("atDividedQ") || str.Contains("phiEtaStar")) && str.Contains("j4") ) rebin=10;
		if (str.Contains("phiStar")){
		   if (str.Contains("j1") ) rebin=2;
		   if (str.Contains("j2") ) rebin=5;
		   if (str.Contains("j3") ) rebin=10;
		   if (str.Contains("j4") ) rebin=20;}
*/

		//======================
		// DATA
		Double_t dataint = data->Integral();
		data->SetLineColor(kBlack);
		data->Rebin(rebin);
		//if(str.Contains("nJetVtx")) data->GetXaxis()->SetRangeUser(0,10);	
		//if(str.Contains("zMass")) data->GetXaxis()->SetRangeUser(60,120);	
		if(str.Contains("InvMass") || str.Contains("jet12Pt") || str.Contains("jetHt")) data->GetXaxis()->SetRangeUser(0,600);
		if ( str.Contains("atDividedQ")) data->GetXaxis()->SetRangeUser(0,2);
		//data->SetMinimum(0.1);
		data->SetMinimum(1);
		data->Sumw2();
		data->Draw("E1");

		TLegend* legend = new TLegend(0.825,0.57,0.95,0.72);
		legend->SetFillColor(0);
		legend->SetFillStyle(0);
		legend->SetBorderSize(0);
		legend->AddEntry(data,"data","p");

		// hack to calculate some yields in restricted regions...
		int num1=0, num2=0, num3=0, num4=0, num5=0;
		// if(str.Contains("invMass") && !str.Contains("PF")){
// 			for(int j=1;j<=data->GetNbinsX();j++){
// 			num1 += data->GetBinContent(j); 		//conto quante Z ci sono tra 60 e 120 GeV
// 			if(j>10&&j<=50) num2 += data->GetBinContent(j); // ... tra 70 e 110
// 			if(j>15&&j<=45) num3 += data->GetBinContent(j); // ... tra 75 e 105
// 			}
// 			cout << "\n";
// 			cout << data->GetNbinsX() <<" Number of bins of the invmass histo\n";
// 			printf("Number of Z in 60-120 %i --- 70-110 %i --- 75-105 %i \n",num1,num2,num3);
// 			cout << "\n";
// 		}
// 		if(str.Contains("zYieldVsjets") && !str.Contains("Vtx")){
// 			for(int j=1;j<=data->GetNbinsX();j++){
// 				num1 += data->GetBinContent(j); 		//conto quante Z
// 				if(j>1) num2 += data->GetBinContent(j); // ... +1,2,3,4... jets
// 				if(j>2) num3 += data->GetBinContent(j); // ... +2,3,4... jets
// 				if(j>3) num4 += data->GetBinContent(j); // ... +3,4... jets
// 				if(j>4) num5 += data->GetBinContent(j); // ... +4... jets
// 			}
// 			cout << "\n";
// 			cout << data->GetNbinsX() <<" Number of bins of the zYieldVsjets histo\n";
// 			printf("Number of Z+n jet %i --- >1 %i --- >2 %i --- >3 %i --- >4 %i \n",num1,num2,num3,num4,num5);
// 			cout << "\n";
// 		}
		//


		//======================
		// Z + jets signal
		//mcf->cd("validationJEC");
		mcf->cd();
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
		
		// Blocco da propagare negli altri MC
		if(zNumEvents>0.){
			if(lumiweights==1) mc->Scale( dataLumi2011 / (zNumEvents / zjetsXsect));
		} else {
			if(lumiweights==1) mc->Scale(zjetsScale);
		}
		cout<<"X="<<zjetsScale<<endl;
		// fin qui

		if(lumiweights==1) mc->Scale(zwemean);  // perche' i Weights non fanno 1...
		mc->Rebin(rebin);
		if(lumiweights==0) mc->Draw("HISTO SAMES");
		hsum->Rebin(rebin);
		hsum->Add(mc);
		legend->AddEntry(mc,"Z+jets","f");
		}

		//======================
		// ttbar
		//ttbarf->cd("validationJEC");
		ttbarf->cd();
		TH1F* ttbar;
		gDirectory->GetObject(plot.c_str(),ttbar);
	
		if(ttbar){
		ttbar->SetFillColor(kBlue);
		ttbar->Sumw2();
		
		if(ttNumEvents>0.){
			if(lumiweights==1) ttbar->Scale( dataLumi2011 / (ttNumEvents / ttbarXsect));
		} else {
			if(lumiweights==1) ttbar->Scale(ttbarScale);
		}
		
		ttbar->Scale(ttwemean);  // perche' i Weights non fanno 1...
		ttbar->Rebin(rebin);
		//ttbar->Draw("HISTO SAMES");
		hsum->Add(ttbar);
		if(lumiweights==1)legend->AddEntry(ttbar,"ttbar","f");
		}

		//======================
		// w+jets
		//wf->cd("validationJEC");
		wf->cd();
		TH1F* w;
		gDirectory->GetObject(plot.c_str(),w);
		if(w){

		w->SetFillColor(kViolet+2);
		w->Sumw2();
		
		if(wNumEvents>0.){
			if(lumiweights==1) w->Scale( dataLumi2011 / (wNumEvents / wjetsXsect));
		} else {
			if(lumiweights==1) w->Scale(wjetsScale);
		}
		
		w->Scale(wjetsScale); 
		if(wNumEvents>0.) w->Scale(wjetsNevts/wNumEvents); // perche' il mc non e' completo...
		w->Scale(wwemean);  // perche' i Weights non fanno 1...
		w->Rebin(rebin);
		//w->Draw("HISTO SAMES");
		//
		//  TOLTO FINCHE NON C'E' IL SAMPLE 
		//     ALTRIMENTI NON VA NIENTE
		//
		//hsum->Add(w);
		if(lumiweights==1)legend->AddEntry(w,"W+jets","f");
		}

		//======================
		// QCD EM enriched
		//qcd23emf->cd("validationJEC");
		qcd23emf->cd();
		TH1F* qcd23em;
		gDirectory->GetObject(plot.c_str(),qcd23em);

		if(qcd23em){
		TH1D * qcdTotEM =  (TH1D*) qcd23em->Clone(); 
		qcdTotEM->SetTitle("qcd em");
		qcdTotEM->SetName("qcd em");
		qcdTotEM->Reset();
		qcdTotEM->Rebin(rebin);

		//qcd38emf->cd("validationJEC");
		qcd38emf->cd();
		TH1F* qcd38em;
		gDirectory->GetObject(plot.c_str(),qcd38em);


		//qcd817emf->cd("validationJEC");
		qcd817emf->cd();
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

		//
		//  TOLTO FINCHE NON C'E' IL SAMPLE 
		//     ALTRIMENTI NON VA NIENTE
		//
		//hsum->Add(qcdTotEM);

		if(lumiweights==1)legend->AddEntry(qcdTotEM,"QCD em","f");
		}
		
		//======================
		// QCD bc
		//qcd23bcf->cd("validationJEC");
		qcd23bcf->cd();
		TH1F* qcd23bc;
		gDirectory->GetObject(plot.c_str(),qcd23bc);

		if(qcd23bc){
		TH1D * qcdTotBC =  (TH1D*) qcd23bc->Clone(); 
		qcdTotBC->SetTitle("qcd bc");
		qcdTotBC->SetName("qcd bc");
		qcdTotBC->Reset();
		qcdTotBC->Rebin(rebin);

		//qcd38bcf->cd("validationJEC");
		qcd38bcf->cd();
		TH1F* qcd38bc;
		gDirectory->GetObject(plot.c_str(),qcd38bc);

		//qcd817bcf->cd("validationJEC");
		qcd817bcf->cd();
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

		

		//
		//  TOLTO FINCHE NON C'E' IL SAMPLE 
		//     ALTRIMENTI NON VA NIENTE
		//
		//hsum->Add(qcdTotBC);

		if(lumiweights==1)legend->AddEntry(qcdTotBC,"QCD bc","f");
		}

		//======================
		// Add here other backgrounds


		//======================
		// Stacked Histogram
		//if(qcd23em) 	hs->Add(qcdTotEM);
		//if(qcd23bc) 	hs->Add(qcdTotBC);
		//if(w)  	hs->Add(w);
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
		TLegend* lumi = new TLegend(0.45,0.65,0.75,0.55);
		lumi->SetFillColor(0);
		lumi->SetFillStyle(0);
		lumi->SetBorderSize(0);
		lumi->AddEntry((TObject*)0,"#int L dt = 4.907 fb^{-1}","");
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
		cout<<tmp<<endl;

	}
	else if (flag==2){
		//Canv.Divide(2,1);
		//Canv.cd(1);

		// data
		//dataf->cd("validationJEC");
		dataf->cd();
		gDirectory->GetObject(plot.c_str(),data2);
		data2->Draw("COLZ");
		TProfile * data_py =  data2->ProfileX("data_py",1,1500);

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
		//mcf->cd("validationJEC");
		mcf->cd();
		gDirectory->GetObject(plot.c_str(),data2);

		data2->SetMinimum(1);
		data2->Draw("COLZ");
		TProfile * mc_py =  data2->ProfileX("mc_py",1,1500);

		gPad->Update(); // altrimenti non becchi la stat
		TPaveStats *r2 = (TPaveStats*)data2->FindObject("stats");
		r2->SetX1NDC(0.70);
		r2->SetX2NDC(0.85); 
		r2->Draw();
		Canv->Update();

		tmp=plotpath+plot+"mc.png";
		Canv->Print(tmp.c_str());
		cout<<tmp<<endl;
		
		Canv->cd();
		TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
		pad1->Draw();
		pad1->cd();
		TString str=data2->GetTitle();
		if(str.Contains("Zpt")) rebin=5;
		data_py->SetLineColor(kBlack);
		data_py->Rebin(rebin);	
		mc_py->Rebin(rebin);	
		if(str.Contains("Zpt")) mc_py->GetXaxis()->SetRangeUser(0,400);
		if(str.Contains("Zeta")) mc_py->GetXaxis()->SetRangeUser(-3,3);
		if(str.Contains("JetMult")) mc_py->GetYaxis()->SetRangeUser(0,700);
		if(str.Contains("jet_pT")) mc_py->GetYaxis()->SetRangeUser(0.0000001,0.1);


		//data_py->SetMinimum(1.);
		data_py->Sumw2();
		//mc_py->SetLineColor(kRed);		
		mc_py->SetFillColor(kRed);
		mc_py->Draw("histo");
		data_py->Draw("E1 sames");
		
		TH1D *p1 = data_py->ProjectionX();
		TH1D *p2 = mc_py->ProjectionX();
		Canv->cd();
		TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
		pad2->Draw();
		pad2->cd();
		TH1D * ratio =  (TH1D*) p2->Clone();
		if(str.Contains("Zpt")) ratio->GetXaxis()->SetRangeUser(0,400);
		if(str.Contains("Zeta")) ratio->GetXaxis()->SetRangeUser(-3,3);
		ratio->SetTitle("ratio");
		ratio->SetName("ratio");
		ratio->Reset();
		ratio->Sumw2();
		p1->Sumw2();
		p2->Sumw2(); // FIXME controlla che sia corretto questo... 
		ratio->SetMarkerSize(.5);
		ratio->SetLineColor(kBlack);
		ratio->SetMarkerColor(kBlack);
		gStyle->SetOptStat("m");
		ratio->Divide(p1,p2,1.,1.);
		ratio->GetYaxis()->SetRangeUser(0,2);	
		pad2->SetTopMargin(1);
		ratio->Draw("E1");
		
		TLine *OLine = new TLine(ratio->GetXaxis()->GetXmin(),1.,ratio->GetXaxis()->GetXmax(),1.);
		OLine->SetLineColor(kBlack);
		OLine->SetLineStyle(2);
		OLine->Draw();

		tmp=plotpath+plot+"_py.png";
		Canv->Print(tmp.c_str());
		cout<<tmp<<endl;
		
	}
//	else { cout << "You're getting an exception! Most likely there's no histogram here... \n"; }

	delete data;
	delete data2;
	delete hs;
	delete Canv;



	dataf->Close();
	mcf->Close();
	ttbarf->Close();
	wf->Close();
	qcd23emf->Close();
	qcd38emf->Close();
	qcd817emf->Close();
	qcd23bcf->Close();
	qcd38bcf->Close();
	qcd817bcf->Close();


	return;
}





double numEventsPerStep(string filename, string dir){

	double entries=-999;

	TFile *tmp = TFile::Open(filename.c_str()); //MC file
	tmp->cd(dir.c_str());

	TObject * obj;
	gDirectory->GetObject("numEventsPerStep",obj);

	if(obj) entries = ((TH1F*)obj)->GetBinContent(1);

	tmp->Close();

	return entries;

}

