#include "tdrStyle.C"
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

void DataMCValidation_R9_tune(){

	std::vector<TH1D*> IsoEcalplotsBarrelNotRemoved;
	std::vector<TH1*> IsoPlotsMC;

	gROOT->LoadMacro("PlotsFeeder.C++");
	PlotsFeeder p;

	int numbofvertices=15;

	gROOT->ForceStyle();
	tdrStyle();
	TFile *dataf = TFile::Open(datafile.c_str()); //data fil

	TDirectory *dir=(TDirectory*)dataf->Get("demo");
	TTree *treeVJ_ = (TTree*)dir->Get("treeVJ_");

	TFile *a = TFile::Open("/gpfs/cms/data/2011/tools/corrections.root");
	TH1F* ratiog = (TH1F*) a->Get("ratiog");

	//DEFINITIONS (please outside the loop!)
	stringstream oss;
	string name;
	string cut;

	//HISTOGRAMS FOR VTX CUT
	//MONTECARLO
	TH1D* h_MCone_eEB = (TH1D*)gDirectory->GetList()->FindObject("h_MCone_eEB");
	if (h_MCone_eEB) delete h_MCone_eEB;

	TH1D* h_MCone_hEB = (TH1D*)gDirectory->GetList()->FindObject("h_MCone_hEB");
	if (h_MCone_hEB) delete h_MCone_hEB;

	TH1D* h_MCone_tEB = (TH1D*)gDirectory->GetList()->FindObject("h_MCone_tEB");
	if (h_MCone_tEB) delete h_MCone_tEB;

	TH1D* h_MCone_eEE = (TH1D*)gDirectory->GetList()->FindObject("h_MCone_eEE");
	if (h_MCone_eEE) delete h_MCone_eEE;

	TH1D* h_MCone_hEE = (TH1D*)gDirectory->GetList()->FindObject("h_MCone_hEE");
	if (h_MCone_hEE) delete h_MCone_hEE;

	TH1D* h_MCone_tEE = (TH1D*)gDirectory->GetList()->FindObject("h_MCone_tEE");
	if (h_MCone_tEE) delete h_MCone_tEE;

	//DATA
	TH1D* h_DATAone_eEB = (TH1D*)gDirectory->GetList()->FindObject("h_DATAone_eEB");
	if (h_DATAone_eEB) delete h_DATAone_eEB;

	TH1D* h_DATAone_hEB = (TH1D*)gDirectory->GetList()->FindObject("h_DATAone_hEB");
	if (h_DATAone_hEB) delete h_DATAone_hEB;

	TH1D* h_DATAone_tEB = (TH1D*)gDirectory->GetList()->FindObject("h_DATAone_tEB");
	if (h_DATAone_tEB) delete h_DATAone_tEB;

	TH1D* h_DATAone_eEE = (TH1D*)gDirectory->GetList()->FindObject("h_DATAone_eEE");
	if (h_DATAone_eEE) delete h_DATAone_eEE;

	TH1D* h_DATAone_hEE = (TH1D*)gDirectory->GetList()->FindObject("h_DATAone_hEE");
	if (h_DATAone_hEE) delete h_DATAone_hEE;

	TH1D* h_DATAone_tEE = (TH1D*)gDirectory->GetList()->FindObject("h_DATAone_tEE");
	if (h_DATAone_tEE) delete h_DATAone_tEE;



	//--------------//
	//    TOTALE    //
	//--------------//
	//EB data
	TH1D* h_trkEB = (TH1D*)gDirectory->GetList()->FindObject("h_trkEB");
	if (h_trkEB) delete h_trkEB;
	h_trkEB = new TH1D("h_trkEB","IsoTracker EB",tEB,tEBmin,tEBmax);

	TH1D* h_ieEB = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB");
	if (h_ieEB) delete h_ieEB;
	h_ieEB = new TH1D("h_ieEB","IsoEcal EB",eEB,eEBmin,eEBmax);

	TH1D* h_ihEB = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB");
	if (h_ihEB) delete h_ihEB;
	h_ihEB = new TH1D("h_ihEB","IsoHcal EB",hEB,hEBmin,hEBmax);

	//EB mc
	TH1D* h_trkEB_mc = (TH1D*)gDirectory->GetList()->FindObject("h_trkEB_mc");
	if (h_trkEB_mc) delete h_trkEB_mc;
	h_trkEB_mc = new TH1D("h_trkEB_mc","IsoTracker EB_mc",tEB,tEBmin,tEBmax);

	TH1D* h_ieEB_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB_mc");
	if (h_ieEB_mc) delete h_ieEB_mc;
	h_ieEB_mc = new TH1D("h_ieEB_mc","IsoEcal EB_mc",eEB,eEBmin,eEBmax);

	TH1D* h_ihEB_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB_mc");
	if (h_ihEB_mc) delete h_ihEB_mc;
	h_ihEB_mc = new TH1D("h_ihEB_mc","IsoHcal EB_mc",hEB,hEBmin,hEBmax);

	//EE data
	TH1D* h_trkEE = (TH1D*)gDirectory->GetList()->FindObject("h_trkEE");
	if (h_trkEE) delete h_trkEE;
	h_trkEE = new TH1D("h_trkEE","IsoTracker EE",tEE,tEEmin,tEEmax);

	TH1D* h_ieEE = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE");
	if (h_ieEE) delete h_ieEE;
	h_ieEE = new TH1D("h_ieEE","IsoEcal EE",eEE,eEEmin,eEEmax);

	TH1D* h_ihEE = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE");
	if (h_ihEE) delete h_ihEE;
	h_ihEE = new TH1D("h_ihEE","IsoHcal EE",hEE,hEEmin,hEEmax);

	//EE mc
	TH1D* h_trkEE_mc = (TH1D*)gDirectory->GetList()->FindObject("h_trkEE_mc");
	if (h_trkEE_mc) delete h_trkEE_mc;
	h_trkEE_mc = new TH1D("h_trkEE_mc","IsoTracker EE_mc",tEE,tEEmin,tEEmax);

	TH1D* h_ieEE_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE_mc");
	if (h_ieEE_mc) delete h_ieEE_mc;
	h_ieEE_mc = new TH1D("h_ieEE_mc","IsoEcal EE_mc",eEE,eEEmin,eEEmax);

	TH1D* h_ihEE_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE_mc");
	if (h_ihEE_mc) delete h_ihEE_mc;
	h_ihEE_mc = new TH1D("h_ihEE_mc","IsoHcal EE_mc",hEE,hEEmin,hEEmax);


	//NEW STUFF
	TObjArray* histarray = new TObjArray();
	//


	//----------
	//  LOOP!
	for (int i=1;i<=numbofvertices;i++){

		histarray = p.Loop(i);

		// HISTOGRAMS FOR VTX CUT
		//EB data
		TH1D* h_trkEB_data = (TH1D*)gDirectory->GetList()->FindObject("h_trkEB_data");
		if (h_trkEB_data) delete h_trkEB_data;
		h_trkEB_data = new TH1D("h_trkEB_data","IsoTracker EB",tEB,tEBmin,tEBmax);

		TH1D* h_ieEB_data = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB_data");
		if (h_ieEB_data) delete h_ieEB_data;
		h_ieEB_data = new TH1D("h_ieEB_data","IsoEcal EB",eEB,eEBmin,eEBmax);

		TH1D* h_ihEB_data = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB_data");
		if (h_ihEB_data) delete h_ihEB_data;
		h_ihEB_data = new TH1D("h_ihEB_data","IsoHcal EB",hEB,hEBmin,hEBmax);

		//EE data
		TH1D* h_trkEE_data = (TH1D*)gDirectory->GetList()->FindObject("h_trkEE_data");
		if (h_trkEE_data) delete h_trkEE_data;
		h_trkEE_data = new TH1D("h_trkEE_data","IsoTracker EE",tEE,tEEmin,tEEmax);

		TH1D* h_ieEE_data = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE_data");
		if (h_ieEE_data) delete h_ieEE_data;
		h_ieEE_data = new TH1D("h_ieEE_data","IsoEcal EE",eEE,eEEmin,eEEmax);

		TH1D* h_ihEE_data = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE_data");
		if (h_ihEE_data) delete h_ihEE_data;
		h_ihEE_data = new TH1D("h_ihEE_data","IsoHcal EE",hEE,hEEmin,hEEmax);


		// HISTOGRAMS FOR VTX CUT
		// PUR version :)
		//EB data
		TH1D* h_trkEB_data_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_trkEB_data_PUR");
		if (h_trkEB_data_PUR) delete h_trkEB_data_PUR;
		h_trkEB_data_PUR = new TH1D("h_trkEB_data_PUR","IsoTracker EB",tEB,tEBmin,tEBmax);

		TH1D* h_ieEB_data_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB_data_PUR");
		if (h_ieEB_data_PUR) delete h_ieEB_data_PUR;
		h_ieEB_data_PUR = new TH1D("h_ieEB_data_PUR","IsoEcal EB",eEB,eEBmin,eEBmax);

		TH1D* h_ihEB_data_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB_data_PUR");
		if (h_ihEB_data_PUR) delete h_ihEB_data_PUR;
		h_ihEB_data_PUR = new TH1D("h_ihEB_data_PUR","IsoHcal EB",hEB,hEBmin,hEBmax);

		//EE data
		TH1D* h_trkEE_data_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_trkEE_data_PUR");
		if (h_trkEE_data_PUR) delete h_trkEE_data_PUR;
		h_trkEE_data_PUR = new TH1D("h_trkEE_data_PUR","IsoTracker EE",tEE,tEEmin,tEEmax);

		TH1D* h_ieEE_data_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE_data_PUR");
		if (h_ieEE_data_PUR) delete h_ieEE_data_PUR;
		h_ieEE_data_PUR = new TH1D("h_ieEE_data_PUR","IsoEcal EE",eEE,eEEmin,eEEmax);

		TH1D* h_ihEE_data_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE_data_PUR");
		if (h_ihEE_data_PUR) delete h_ihEE_data_PUR;
		h_ihEE_data_PUR = new TH1D("h_ihEE_data_PUR","IsoHcal EE",hEE,hEEmin,hEEmax);



		//MONTECARLO - EB EE notPUR
		//if (!histarray->FindObject("h_IsoTrk_EBR")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_trkEB_pf = (TH1D*)gDirectory->GetList()->FindObject("h_trkEB_pf");
		if (h_trkEB_pf) delete h_trkEB_pf;
		h_trkEB_pf = (TH1D *)histarray->FindObject("h_IsoTrk_EBR");


		//if (!histarray->FindObject("h_IsoEcal_EBR")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_ieEB_pf = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB_pf");
		if (h_ieEB_pf) delete h_ieEB_pf;
		h_ieEB_pf = (TH1D *)histarray->FindObject("h_IsoEcal_EBR");


		//if (!histarray->FindObject("h_IsoHcal_EBR")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_ihEB_pf = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB_pf");
		if (h_ihEB_pf) delete h_ihEB_pf;
		h_ihEB_pf = (TH1D *)histarray->FindObject("h_IsoHcal_EBR");



		//if (!histarray->FindObject("h_IsoTrk_EER")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_trkEE_pf = (TH1D*)gDirectory->GetList()->FindObject("h_trkEE_pf");
		if (h_trkEE_pf) delete h_trkEE_pf;
		h_trkEE_pf = (TH1D *)histarray->FindObject("h_IsoTrk_EER");


		//if (!histarray->FindObject("h_IsoEcal_EER")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_ieEE_pf = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE_pf");
		if (h_ieEE_pf) delete h_ieEE_pf;
		h_ieEE_pf = (TH1D *)histarray->FindObject("h_IsoEcal_EER");


		//if (!histarray->FindObject("h_IsoHcal_EER")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_ihEE_pf = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE_pf");
		if (h_ihEE_pf) delete h_ihEE_pf;
		h_ihEE_pf = (TH1D *)histarray->FindObject("h_IsoHcal_EER");

		//MONTECARLO PUR
		//if (!histarray->FindObject("h_IsoTrk_EBR_PUR")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_trkEB_pf_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_trkEB_pf_PUR");
		if (h_trkEB_pf_PUR) delete h_trkEB_pf_PUR;
		h_trkEB_pf_PUR = (TH1D *)histarray->FindObject("h_IsoTrk_EBR_PUR");

		//if (!histarray->FindObject("h_IsoEcal_EBR_PUR")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_ieEB_pf_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB_pf_PUR");
		if (h_ieEB_pf_PUR) delete h_ieEB_pf_PUR;
		h_ieEB_pf_PUR = (TH1D *)histarray->FindObject("h_IsoEcal_EBR_PUR");

		//if (!histarray->FindObject("h_IsoHcal_EBR_PUR")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_ihEB_pf_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB_pf_PUR");
		if (h_ihEB_pf_PUR) delete h_ihEB_pf_PUR;
		h_ihEB_pf_PUR = (TH1D *)histarray->FindObject("h_IsoHcal_EBR_PUR");


		//if (!histarray->FindObject("h_IsoTrk_EER_PUR")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_trkEE_pf_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_trkEE_pf_PUR");
		if (h_trkEE_pf_PUR) delete h_trkEE_pf_PUR;
		h_trkEE_pf_PUR = (TH1D *)histarray->FindObject("h_IsoTrk_EER_PUR");

		//if (!histarray->FindObject("h_IsoEcal_EER_PUR")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_ieEE_pf_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE_pf_PUR");
		if (h_ieEE_pf_PUR) delete h_ieEE_pf_PUR;
		h_ieEE_pf_PUR = (TH1D *)histarray->FindObject("h_IsoEcal_EER_PUR");

		//if (!histarray->FindObject("h_IsoHcal_EER_PUR")) { cout << " !!! non ho trovato un istogramma... \n "; }
		TH1D* h_ihEE_pf_PUR = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE_pf_PUR");
		if (h_ihEE_pf_PUR) delete h_ihEE_pf_PUR;
		h_ihEE_pf_PUR = (TH1D *)histarray->FindObject("h_IsoHcal_EER_PUR");


		if(i==1){ h_MCone_hEE = (TH1D *)h_ihEE_pf_PUR->Clone(); h_MCone_hEE->SetName("h_MCone_hEE"); } /*messo in tutte le var. fino a qui _PUR irocrda di toglierlo*/
		if(i==1){ h_MCone_eEE = (TH1D *)h_ieEE_pf_PUR->Clone(); h_MCone_eEE->SetName("h_MCone_eEE"); }
		if(i==1){ h_MCone_tEE = (TH1D *)h_trkEE_pf_PUR->Clone(); h_MCone_tEE->SetName("h_MCone_tEE"); }
		if(i==1){ h_MCone_hEB = (TH1D *)h_ihEB_pf_PUR->Clone(); h_MCone_hEB->SetName("h_MCone_hEB"); }
		if(i==1){ h_MCone_tEB = (TH1D *)h_trkEB_pf_PUR->Clone(); h_MCone_tEB->SetName("h_MCone_tEB"); }        
		if(i==1){ h_MCone_eEB = (TH1D *)h_ieEB_pf_PUR->Clone(); h_MCone_eEB->SetName("h_MCone_eEB"); }


		//===================================
		//set the string
		oss<<i;
		name=" Number of Vertices="+oss.str();
		cut="numberOfVertices=="+oss.str();
		string picname;
		string eps;
		
		//Definizione canvas e riempimento
		//EB
		TCanvas* Comp = (TCanvas*)gDirectory->GetList()->FindObject("Comp");
		if (Comp) delete Comp;
		Comp = new TCanvas("Comp","Comp",0,0,1200,800);
		Comp->Divide(2,3);
		Comp->cd(1);


		//DATA: scrive gli istogrammi tagliati al numero di verici
		//EB data
		treeVJ_->Draw("IsoTrkEB>>h_trkEB_data",cut.c_str());
		treeVJ_->Draw("IsoEcalEB>>h_ieEB_data",cut.c_str());
		treeVJ_->Draw("IsoHcalEB>>h_ihEB_data",cut.c_str());

		//EE data
		treeVJ_->Draw("IsoTrkEE>>h_trkEE_data",cut.c_str());
		treeVJ_->Draw("IsoEcalEE>>h_ieEE_data",cut.c_str());
		treeVJ_->Draw("IsoHcalEE>>h_ihEE_data",cut.c_str());

		//EB_PUR data PUR
		treeVJ_->Draw("IsoTrkEB_PUR>>h_trkEB_data_PUR",cut.c_str());
		treeVJ_->Draw("IsoEcalEB_PUR>>h_ieEB_data_PUR",cut.c_str());
		treeVJ_->Draw("IsoHcalEB_PUR>>h_ihEB_data_PUR",cut.c_str());

		//EE_PUR data PUR
		treeVJ_->Draw("IsoTrkEE_PUR>>h_trkEE_data_PUR",cut.c_str());
		treeVJ_->Draw("IsoEcalEE_PUR>>h_ieEE_data_PUR",cut.c_str());
		treeVJ_->Draw("IsoHcalEE_PUR>>h_ihEE_data_PUR",cut.c_str());
		
		if(i==1) { h_DATAone_eEB = (TH1D *) h_ieEB_data_PUR  ->Clone(); h_DATAone_eEB->SetName("h_DATAone_eEB"); }
		if(i==1) { h_DATAone_hEB = (TH1D *) h_ihEB_data_PUR  ->Clone(); h_DATAone_hEB->SetName("h_DATAone_hEB"); }
		if(i==1) { h_DATAone_tEB = (TH1D *) h_trkEB_data_PUR ->Clone(); h_DATAone_tEB->SetName("h_DATAone_tEB"); }
		if(i==1) { h_DATAone_eEE = (TH1D *) h_ieEE_data_PUR  ->Clone(); h_DATAone_eEE->SetName("h_DATAone_eEE"); }
		if(i==1) { h_DATAone_hEE = (TH1D *) h_ihEE_data_PUR  ->Clone(); h_DATAone_hEE->SetName("h_DATAone_hEE"); }
		if(i==1) { h_DATAone_tEE = (TH1D *) h_trkEE_data_PUR ->Clone(); h_DATAone_tEE->SetName("h_DATAone_tEE"); }	
		//===================================
		


/* //NON PUR
		
		Comp->cd(1);
		gPad->SetLogy(1);
		h_ieEB_data->SetTitle(name.c_str());
		h_ieEB_data->SetMarkerColor(kBlack);
		h_ieEB_data->GetXaxis()->SetTitle("IsoEcal Barrel");
		h_ieEB_data->GetYaxis()->SetTitle("Entries");
		h_ieEB_data->SetLineColor(kBlack);
		h_ieEB_data->SetMarkerColor(kBlack);
		h_ieEB_data->Draw("E1");
		h_ieEB_pf->SetMarkerColor(kRed);
		h_ieEB_pf->SetLineColor(kRed);
		h_ieEB_pf->Draw("HIST SAMES");
		Comp->Update();
		double plotentries = ((h_ieEB_data->Integral()) / h_ieEB_pf->Integral());
		h_ieEB_pf->Scale(plotentries);

		TPaveStats *r2 = (TPaveStats*)h_ieEB_pf->FindObject("stats"); 
		r2->SetY1NDC(0.875); 
		r2->SetY2NDC(0.75); 
		r2->SetTextColor(kRed);
		r2->Draw();
		Comp->Update();

		TLegend *leg = new TLegend(0.6,0.75,0.825,0.9);
		leg->SetBorderSize(0);
		leg->SetEntrySeparation(0.01);
		leg->SetFillColor(0);
		leg->AddEntry(h_ieEB_data,"data","p");
		leg->AddEntry( h_ieEB_pf,"MonteCarlo","l");
		leg->Draw();
		Comp->Update();


		//
		Comp->cd(2);
		gPad->SetLogy(1);
		h_ieEE_data->SetTitle(name.c_str());
		h_ieEE_data->SetMarkerColor(kBlack);
		h_ieEE_data->SetLineColor(kBlack);
		h_ieEE_data->GetXaxis()->SetTitle("IsoEcal Endcap");
		h_ieEE_data->GetYaxis()->SetTitle("Entries");
		h_ieEE_data->Draw("E1");
		h_ieEE_pf->SetMarkerColor(kRed);
		h_ieEE_pf->SetLineColor(kRed);
		h_ieEE_pf->Draw("HIST SAMES");
		Comp->Update();
		double plotentries3 = ( (h_ieEE_data->Integral())/ h_ieEE_pf->Integral());
		h_ieEE_pf->Scale(plotentries3);

		TPaveStats *r5 = (TPaveStats*) h_ieEE_pf->FindObject("stats"); 
		r5->SetY1NDC(0.878); 
		r5->SetY2NDC(0.75); 
		r5->SetTextColor(kRed);
		r5->Draw();
		Comp->Update();

		TLegend *leg3 = new TLegend(0.6,0.75,0.825,0.9);
		leg3->SetBorderSize(0);
		leg3->SetEntrySeparation(0.01);
		leg3->SetFillColor(0);
		leg3->AddEntry(h_ieEE_data,"data","p");
		leg3->AddEntry(h_ieEE_pf,"MonteCarlo","l");
		leg3->Draw();
		Comp->Update();

		//
		Comp->cd(3);
		gPad->SetLogy(1);
		h_ihEB_data->SetTitle(name.c_str());
		h_ihEB_data->SetMarkerColor(kBlack);
		h_ihEB_data->SetLineColor(kBlack);
		h_ihEB_data->GetXaxis()->SetTitle("IsoHcal Barrel");
		h_ihEB_data->GetYaxis()->SetTitle("Entries");
		h_ihEB_data->Draw("E1");
		h_ihEB_pf->SetMarkerColor(kRed);
		h_ihEB_pf->SetLineColor(kRed);
		h_ihEB_pf->Draw("HIST SAMES");
		Comp->Update();
		double plotentries2 = ( (h_ihEB_data->Integral()) / h_ihEB_pf->Integral());
		h_ihEB_pf->Scale(plotentries2);

		TPaveStats *r3 = (TPaveStats*) h_ihEB_pf->FindObject("stats"); 
		r3->SetY1NDC(0.878); 
		r3->SetY2NDC(0.75); 
		r3->SetTextColor(kRed);
		r3->Draw();
		Comp->Update();

		TLegend *leg2 = new TLegend(0.6,0.75,0.825,0.9);
		leg2->SetBorderSize(0);
		leg2->SetEntrySeparation(0.01);
		leg2->SetFillColor(0);
		leg2->AddEntry(h_ihEB_data,"data","p");
		leg2->AddEntry( h_ihEB_pf,"MonteCarlo","l");
		leg2->Draw();
		Comp->Update();

		//
		Comp->cd(4);
		gPad->SetLogy(1);
		h_ihEE_data->SetTitle(name.c_str());
		h_ihEE_data->SetMarkerColor(kBlack);
		h_ihEE_data->SetLineColor(kBlack);
		h_ihEE_data->GetXaxis()->SetTitle("IsoHcal Endcap");
		h_ihEE_data->GetYaxis()->SetTitle("Entries");
		h_ihEE_data->Draw("E1");
		h_ihEE_pf->SetMarkerColor(kRed);
		h_ihEE_pf->SetLineColor(kRed);
		h_ihEE_pf->Draw("HIST SAMES");
		Comp->Update();
		double plotentries4 = ( (h_ihEE_data->Integral())/ h_ihEE_pf->Integral());
		h_ihEE_pf->Scale(plotentries4);

		TPaveStats *r6 = (TPaveStats*)h_ihEE_pf->FindObject("stats"); 
		r6->SetY1NDC(0.878); 
		r6->SetY2NDC(0.75); 
		r6->SetTextColor(kRed);
		r6->Draw();
		Comp->Update();

		TLegend *leg4 = new TLegend(0.6,0.75,0.825,0.9);
		leg4->SetBorderSize(0);
		leg4->SetEntrySeparation(0.01);
		leg4->SetFillColor(0);
		leg4->AddEntry(h_ihEE_data,"data","p");
		leg4->AddEntry(h_ihEE_pf,"MonteCarlo","l");
		leg4->Draw();
		Comp->Update();

		Comp->cd(5);
		gPad->SetLogy(1);
		h_trkEB_data->SetTitle(name.c_str());
		h_trkEB_data->SetMarkerColor(kBlack);
		h_trkEB_data->GetXaxis()->SetTitle("IsoTrk Barrel");
		h_trkEB_data->GetYaxis()->SetTitle("Entries");
		h_trkEB_data->SetLineColor(kBlack);
		h_trkEB_data->SetMarkerColor(kBlack);
		h_trkEB_data->Draw("E1");
		h_trkEB_pf->SetMarkerColor(kRed);
		h_trkEB_pf->SetLineColor(kRed);
		h_trkEB_pf->Draw("HIST SAMES");
		Comp->Update();
		double plotentries7 = ( (h_trkEB_data->Integral())/ h_trkEB_pf->Integral());
		h_trkEB_pf->Scale(plotentries7);

		TPaveStats *r7 = (TPaveStats*)h_trkEB_pf->FindObject("stats"); 
		r7->SetY1NDC(0.875); 
		r7->SetY2NDC(0.75); 
		r7->SetTextColor(kRed);
		r7->Draw();
		Comp->Update();

		TLegend *leg7 = new TLegend(0.6,0.75,0.825,0.9);
		leg7->SetBorderSize(0);
		leg7->SetEntrySeparation(0.01);
		leg7->SetFillColor(0);
		leg7->AddEntry(h_trkEB_data,"data","p");
		leg7->AddEntry( h_trkEB_pf,"MonteCarlo","l");
		leg7->Draw();

		Comp->cd(6);
		gPad->SetLogy(1);
		h_trkEE_data->SetTitle(name.c_str());
		h_trkEE_data->GetXaxis()->SetTitle("IsoTrk Endcap");
		h_trkEE_data->GetYaxis()->SetTitle("Entries");
		h_trkEE_data->SetLineColor(kBlack);
		h_trkEE_data->SetMarkerColor(kBlack);
		h_trkEE_data->Draw("E1");
		h_trkEE_pf->SetMarkerColor(kRed);
		h_trkEE_pf->SetLineColor(kRed);
		h_trkEE_pf->Draw("HIST SAMES");
		Comp->Update();
		double plotentries8 = ( (h_trkEE_data->Integral())/ h_trkEE_pf->Integral());
		h_trkEE_pf->Scale(plotentries8);

		TPaveStats *r8 = (TPaveStats*)h_trkEE_pf->FindObject("stats"); 
		r8->SetY1NDC(0.875); 
		r8->SetY2NDC(0.75); 
		r8->SetTextColor(kRed);
		r8->Draw();
		Comp->Update();

		TLegend *leg8 = new TLegend(0.6,0.75,0.825,0.9);
		leg8->SetBorderSize(0);
		leg8->SetEntrySeparation(0.01);
		leg8->SetFillColor(0);
		leg8->AddEntry(h_trkEE_data,"data","p");
		leg8->AddEntry(h_trkEE_pf,"MonteCarlo","l");
		leg8->Draw();
		Comp->Update();

		picname="Trk-Ecal-Hcal-Isolation"+oss.str()+".png";
		eps="Trk-Ecal-Hcal-Isolation"+oss.str()+".eps";
		Comp->Print(picname.c_str());
		Comp->Print(eps.c_str());


	//TOTALE NON PUR
		h_ieEB->Add(h_ieEB_data);
		h_ieEB_mc->Add(h_ieEB_pf);

		h_ihEB->Add(h_ihEB_data);
		h_ihEB_mc->Add(h_ihEB_pf);

		h_trkEB->Add(h_trkEB_data);
		h_trkEB_mc->Add(h_trkEB_pf);

		h_ieEE->Add(h_ieEE_data);
		h_ieEE_mc->Add(h_ieEE_pf);

		h_ihEE->Add(h_ihEE_data);
		h_ihEE_mc->Add(h_ihEE_pf);

		h_trkEE->Add(h_trkEE_data);
		h_trkEE_mc->Add(h_trkEE_pf);

*/
//PUR
		//Definizione canvas e riempimento
		//EB
		TCanvas* CompPUR = (TCanvas*)gDirectory->GetList()->FindObject("CompPUR");
		if (CompPUR) delete CompPUR;
		CompPUR = new TCanvas("CompPUR","CompPUR",0,0,1200,800);
		CompPUR->Divide(2,3);
		CompPUR->cd(1);


		gPad->SetLogy(1);
		h_ieEB_data_PUR->SetTitle(name.c_str());
		h_ieEB_data_PUR->SetMarkerColor(kBlack);
		h_ieEB_data_PUR->GetXaxis()->SetTitle("IsoEcal Barrel");
		h_ieEB_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ieEB_data_PUR->SetLineColor(kBlack);
		h_ieEB_data_PUR->SetMarkerColor(kBlack);
		h_ieEB_data_PUR->Draw("E1");
		h_ieEB_pf_PUR->SetMarkerColor(kRed);
		h_ieEB_pf_PUR->SetMarkerSize(0.);
		h_ieEB_pf_PUR->SetLineColor(kRed);
		ratiog->Sumw2();
		h_ieEB_pf_PUR->Sumw2();
		h_ieEB_pf_PUR->Multiply(ratiog);
		h_ieEB_pf_PUR->Draw("HISTO E1 SAMES");
		CompPUR->Update();
		double norm = ((h_ieEB_data_PUR->Integral()) / h_ieEB_pf_PUR->Integral()) ;
		h_ieEB_pf_PUR->Scale(norm);

		TPaveStats *stat2 = (TPaveStats*)h_ieEB_pf_PUR->FindObject("stats"); 
		stat2->SetY1NDC(0.875); 
		stat2->SetY2NDC(0.75); 
		stat2->SetTextColor(kRed);
		stat2->Draw();
		CompPUR->Update();

		TLegend *purleg = new TLegend(0.6,0.75,0.825,0.9);
		purleg->SetBorderSize(0);
		purleg->SetEntrySeparation(0.01);
		purleg->SetFillColor(0);
		purleg->AddEntry(h_ieEB_data_PUR,"data PUR","p");
		purleg->AddEntry( h_ieEB_pf_PUR,"MonteCarlo PUR","l");
		purleg->Draw();
		CompPUR->Update();


		//
		CompPUR->cd(2);
		gPad->SetLogy(1);
		h_ieEE_data_PUR->SetTitle(name.c_str());
		h_ieEE_data_PUR->SetMarkerColor(kBlack);
		h_ieEE_data_PUR->SetLineColor(kBlack);
		h_ieEE_data_PUR->GetXaxis()->SetTitle("IsoEcal Endcap");
		h_ieEE_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ieEE_data_PUR->Draw("E1");
		h_ieEE_pf_PUR->SetMarkerColor(kRed);
		h_ieEE_pf_PUR->SetLineColor(kRed);
		h_ieEE_pf_PUR->Draw("HISTO SAMES");
		CompPUR->Update();
		double norm3 = ( (h_ieEE_data_PUR->Integral())/ h_ieEE_pf_PUR->Integral());
		h_ieEE_pf_PUR->Scale(norm3);

		TPaveStats *stat5 = (TPaveStats*) h_ieEE_pf_PUR->FindObject("stats"); 
		stat5->SetY1NDC(0.878); 
		stat5->SetY2NDC(0.75); 
		stat5->SetTextColor(kRed);
		stat5->Draw();
		CompPUR->Update();

		TLegend *purleg3 = new TLegend(0.6,0.75,0.825,0.9);
		purleg3->SetBorderSize(0);
		purleg3->SetEntrySeparation(0.01);
		purleg3->SetFillColor(0);
		purleg3->AddEntry(h_ieEE_data_PUR,"data PUR","p");
		purleg3->AddEntry(h_ieEE_pf_PUR,"MonteCarlo PUR","l");
		purleg3->Draw();
		CompPUR->Update();

		//
		CompPUR->cd(3);
		gPad->SetLogy(1);
		h_ihEB_data_PUR->SetTitle(name.c_str());
		h_ihEB_data_PUR->SetMarkerColor(kBlack);
		h_ihEB_data_PUR->SetLineColor(kBlack);
		h_ihEB_data_PUR->GetXaxis()->SetTitle("IsoHcal Barrel");
		h_ihEB_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ihEB_data_PUR->Draw("E1");
		h_ihEB_pf_PUR->SetMarkerColor(kRed);
		h_ihEB_pf_PUR->SetLineColor(kRed);
		h_ihEB_pf_PUR->Draw("HIST SAMES");
		CompPUR->Update();
		double norm2 = ( (h_ihEB_data_PUR->Integral()) / h_ihEB_pf_PUR->Integral());
		h_ihEB_pf_PUR->Scale(norm2);

		TPaveStats *stat3 = (TPaveStats*) h_ihEB_pf_PUR->FindObject("stats"); 
		stat3->SetY1NDC(0.878); 
		stat3->SetY2NDC(0.75); 
		stat3->SetTextColor(kRed);
		stat3->Draw();
		CompPUR->Update();

		TLegend *purleg2 = new TLegend(0.6,0.75,0.825,0.9);
		purleg2->SetBorderSize(0);
		purleg2->SetEntrySeparation(0.01);
		purleg2->SetFillColor(0);
		purleg2->AddEntry(h_ihEB_data_PUR,"data PUR","p");
		purleg2->AddEntry( h_ihEB_pf_PUR,"MonteCarlo PUR","l");
		purleg2->Draw();
		CompPUR->Update();

		//
		CompPUR->cd(4);
		gPad->SetLogy(1);
		h_ihEE_data_PUR->SetTitle(name.c_str());
		h_ihEE_data_PUR->SetMarkerColor(kBlack);
		h_ihEE_data_PUR->SetLineColor(kBlack);
		h_ihEE_data_PUR->GetXaxis()->SetTitle("IsoHcal Endcap");
		h_ihEE_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ihEE_data_PUR->Draw("E1");
		h_ihEE_pf_PUR->SetMarkerColor(kRed);
		h_ihEE_pf_PUR->SetLineColor(kRed);
		h_ihEE_pf_PUR->Draw("HIST SAMES");
		CompPUR->Update();
		double norm4 = ( (h_ihEE_data_PUR->Integral())/ h_ihEE_pf_PUR->Integral());
		h_ihEE_pf_PUR->Scale(norm4);

		TPaveStats *stat6 = (TPaveStats*)h_ihEE_pf_PUR->FindObject("stats"); 
		stat6->SetY1NDC(0.878); 
		stat6->SetY2NDC(0.75); 
		stat6->SetTextColor(kRed);
		stat6->Draw();
		CompPUR->Update();

		TLegend *purleg4 = new TLegend(0.6,0.75,0.825,0.9);
		purleg4->SetBorderSize(0);
		purleg4->SetEntrySeparation(0.01);
		purleg4->SetFillColor(0);
		purleg4->AddEntry(h_ihEE_data_PUR,"data PUR","p");
		purleg4->AddEntry(h_ihEE_pf_PUR,"MonteCarlo PUR","l");
		purleg4->Draw();
		CompPUR->Update();

		CompPUR->cd(5);
		gPad->SetLogy(1);
		h_trkEB_data_PUR->SetTitle(name.c_str());
		h_trkEB_data_PUR->SetMarkerColor(kBlack);
		h_trkEB_data_PUR->GetXaxis()->SetTitle("IsoTrk Barrel");
		h_trkEB_data_PUR->GetYaxis()->SetTitle("Entries");
		h_trkEB_data_PUR->SetLineColor(kBlack);
		h_trkEB_data_PUR->SetMarkerColor(kBlack);
		h_trkEB_data_PUR->Draw("E1");
		h_trkEB_pf_PUR->SetMarkerColor(kRed);
		h_trkEB_pf_PUR->SetLineColor(kRed);
		h_trkEB_pf_PUR->Draw("HIST SAMES");
		CompPUR->Update();
		double norm7 = ( (h_trkEB_data_PUR->Integral())/ h_trkEB_pf_PUR->Integral());
		h_trkEB_pf_PUR->Scale(norm7);

		TPaveStats *stat7 = (TPaveStats*)h_trkEB_pf_PUR->FindObject("stats"); 
		stat7->SetY1NDC(0.875); 
		stat7->SetY2NDC(0.75); 
		stat7->SetTextColor(kRed);
		stat7->Draw();
		CompPUR->Update();

		TLegend *purleg7 = new TLegend(0.6,0.75,0.825,0.9);
		purleg7->SetBorderSize(0);
		purleg7->SetEntrySeparation(0.01);
		purleg7->SetFillColor(0);
		purleg7->AddEntry(h_trkEB_data_PUR,"data PUR","p");
		purleg7->AddEntry( h_trkEB_pf_PUR,"MonteCarlo PUR","l");
		purleg7->Draw();

		CompPUR->cd(6);
		gPad->SetLogy(1);
		h_trkEE_data_PUR->SetTitle(name.c_str());
		h_trkEE_data_PUR->GetXaxis()->SetTitle("IsoTrk Endcap");
		h_trkEE_data_PUR->GetYaxis()->SetTitle("Entries");
		h_trkEE_data_PUR->SetLineColor(kBlack);
		h_trkEE_data_PUR->SetMarkerColor(kBlack);
		h_trkEE_data_PUR->Draw("E1");
		h_trkEE_pf_PUR->SetMarkerColor(kRed);
		h_trkEE_pf_PUR->SetLineColor(kRed);
		h_trkEE_pf_PUR->Draw("HIST SAMES");
		CompPUR->Update();
		double norm8 = ( (h_trkEE_data_PUR->Integral())/ h_trkEE_pf_PUR->Integral());
		h_trkEE_pf_PUR->Scale(norm8);

		TPaveStats *stat8 = (TPaveStats*)h_trkEE_pf_PUR->FindObject("stats"); 
		stat8->SetY1NDC(0.875); 
		stat8->SetY2NDC(0.75); 
		stat8->SetTextColor(kRed);
		stat8->Draw();
		CompPUR->Update();

		TLegend *purleg8 = new TLegend(0.6,0.75,0.825,0.9);
		purleg8->SetBorderSize(0);
		purleg8->SetEntrySeparation(0.01);
		purleg8->SetFillColor(0);
		purleg8->AddEntry(h_trkEE_data_PUR,"data PUR","p");
		purleg8->AddEntry(h_trkEE_pf_PUR,"MonteCarlo PUR","l");
		purleg8->Draw();
		CompPUR->Update();

		picname="Trk-Ecal-Hcal-Isolation-pur"+oss.str()+".png";
		eps="Trk-Ecal-Hcal-Isolation-pur"+oss.str()+".eps";
		CompPUR->Print(picname.c_str());
		CompPUR->Print(eps.c_str());


/*
//MC vtx==1  vs. data vtx==N
		//Definizione canvas e riempimento
		//EB
		TCanvas* CompMC1data = (TCanvas*)gDirectory->GetList()->FindObject("CompMC1data");
		if (CompMC1data) delete CompMC1data;
		CompMC1data = new TCanvas("CompMC1data","CompMC1data",0,0,1200,800);
		CompMC1data->Divide(2,3);
		CompMC1data->cd(1);


		gPad->SetLogy(1);
		h_ieEB_data_PUR->SetTitle(name.c_str());
		h_ieEB_data_PUR->SetMarkerColor(kBlack);
		h_ieEB_data_PUR->GetXaxis()->SetTitle("IsoEcal Barrel");
		h_ieEB_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ieEB_data_PUR->SetLineColor(kBlack);
		h_ieEB_data_PUR->SetMarkerColor(kBlack);
		h_ieEB_data_PUR->Draw("E1");
		h_MCone_eEB->SetMarkerColor(kRed);
		h_MCone_eEB->SetLineColor(kRed);
		h_MCone_eEB->Draw("HIST SAMES");
		h_DATAone_eEB->SetMarkerColor(kBlue);
		h_DATAone_eEB->SetLineColor(kBlue);
		h_DATAone_eEB->Draw("E1 SAMES");
		h_DATAone_eEB->SetMarkerStyle(22);
		CompMC1data->Update();
		double normda = ((h_ieEB_data_PUR->Integral()) / h_MCone_eEB->Integral()) ;
		h_MCone_eEB->Scale(normda);
		normda = ((h_ieEB_data_PUR->Integral()) / h_DATAone_eEB->Integral()) ;
		h_DATAone_eEB->Sumw2();
		h_DATAone_eEB->Scale(normda);
		
		TPaveStats *stada2 = (TPaveStats*)h_MCone_eEB->FindObject("stats"); 
		stada2->SetY1NDC(0.875); 
		stada2->SetY2NDC(0.75); 
		stada2->SetTextColor(kRed);
		stada2->Draw();
		CompMC1data->Update();

		TLegend *da1leg = new TLegend(0.6,0.75,0.825,0.9);
		da1leg->SetBorderSize(0);
		da1leg->SetEntrySeparation(0.01);
		da1leg->SetFillColor(0);
		da1leg->AddEntry(h_ieEB_data,"data","p");
		da1leg->AddEntry(h_MCone_eEB,"MonteCarlo vtx=1","l");
		da1leg->AddEntry(h_DATAone_eEB,"data vtx=1","p");
		da1leg->Draw();
		CompMC1data->Update();


		//
		CompMC1data->cd(2);
		gPad->SetLogy(1);
		h_ieEE_data_PUR->SetTitle(name.c_str());
		h_ieEE_data_PUR->SetMarkerColor(kBlack);
		h_ieEE_data_PUR->SetLineColor(kBlack);
		h_ieEE_data_PUR->GetXaxis()->SetTitle("IsoEcal Endcap");
		h_ieEE_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ieEE_data_PUR->Draw("E1");
		h_MCone_eEE->SetMarkerColor(kRed);
		h_MCone_eEE->SetLineColor(kRed);
		h_MCone_eEE->Draw("HIST SAMES");
		h_DATAone_eEE->SetMarkerColor(kBlue);
		h_DATAone_eEE->SetLineColor(kBlue);
		h_DATAone_eEE->Draw("E1 SAMES");
		h_DATAone_eEE->SetMarkerStyle(22);
		CompMC1data->Update();
		double normda3 = ( (h_ieEE_data_PUR->Integral())/ h_MCone_eEE->Integral());
		h_MCone_eEE->Scale(normda3);
		normda3 = ( (h_ieEE_data_PUR->Integral())/ h_DATAone_eEE->Integral());
		h_DATAone_eEE->Sumw2();
		h_DATAone_eEE->Scale(normda3);

		TPaveStats *stada5 = (TPaveStats*) h_MCone_eEE->FindObject("stats"); 
		stada5->SetY1NDC(0.878); 
		stada5->SetY2NDC(0.75); 
		stada5->SetTextColor(kRed);
		stada5->Draw();
		CompMC1data->Update();

		TLegend *da1leg3 = new TLegend(0.6,0.75,0.825,0.9);
		da1leg3->SetBorderSize(0);
		da1leg3->SetEntrySeparation(0.01);
		da1leg3->SetFillColor(0);
		da1leg3->AddEntry(h_ieEE_data,"data","p");
		da1leg3->AddEntry(h_MCone_eEE,"MonteCarlo vtx=1","l");
		da1leg3->AddEntry(h_DATAone_eEE,"data vtx=1","p");
		da1leg3->Draw();
		CompMC1data->Update();

		//
		CompMC1data->cd(3);
		gPad->SetLogy(1);
		h_ihEB_data_PUR->SetTitle(name.c_str());
		h_ihEB_data_PUR->SetMarkerColor(kBlack);
		h_ihEB_data_PUR->SetLineColor(kBlack);
		h_ihEB_data_PUR->GetXaxis()->SetTitle("IsoHcal Barrel");
		h_ihEB_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ihEB_data_PUR->Draw("E1");
		h_MCone_hEB->SetMarkerColor(kRed);
		h_MCone_hEB->SetLineColor(kRed);
		h_MCone_hEB->Draw("HIST SAMES");
		h_DATAone_hEB->SetMarkerColor(kBlue);
		h_DATAone_hEB->SetLineColor(kBlue);
		h_DATAone_hEB->Draw("E1 SAMES");
		h_DATAone_hEB->SetMarkerStyle(22);
		CompMC1data->Update();
		double normda2 = ( (h_ihEB_data_PUR->Integral()) / h_MCone_hEB->Integral());
		h_MCone_hEB->Scale(normda2);
		normda2 = ( (h_ihEB_data_PUR->Integral()) / h_DATAone_hEB->Integral());
		h_DATAone_hEB->Sumw2();
		h_DATAone_hEB->Scale(normda2);

		TPaveStats *stada3 = (TPaveStats*) h_MCone_hEB->FindObject("stats"); 
		stada3->SetY1NDC(0.878); 
		stada3->SetY2NDC(0.75); 
		stada3->SetTextColor(kRed);
		stada3->Draw();
		CompMC1data->Update();

		TLegend *da1leg2 = new TLegend(0.6,0.75,0.825,0.9);
		da1leg2->SetBorderSize(0);
		da1leg2->SetEntrySeparation(0.01);
		da1leg2->SetFillColor(0);
		da1leg2->AddEntry(h_ihEB_data,"data","p");
		da1leg2->AddEntry(h_MCone_hEB,"MonteCarlo vtx=1","l");
		da1leg2->AddEntry(h_DATAone_hEB,"data vtx=1","p");
		da1leg2->Draw();
		CompMC1data->Update();

		//
		CompMC1data->cd(4);
		gPad->SetLogy(1);
		h_ihEE_data_PUR->SetTitle(name.c_str());
		h_ihEE_data_PUR->SetMarkerColor(kBlack);
		h_ihEE_data_PUR->SetLineColor(kBlack);
		h_ihEE_data_PUR->GetXaxis()->SetTitle("IsoHcal Endcap");
		h_ihEE_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ihEE_data_PUR->Draw("E1");
		h_MCone_hEE->SetMarkerColor(kRed);
		h_MCone_hEE->SetLineColor(kRed);
		h_MCone_hEE->Draw("HIST SAMES");
		h_DATAone_hEE->SetMarkerColor(kBlue);
		h_DATAone_hEE->SetLineColor(kBlue);
		h_DATAone_hEE->Draw("E1 SAMES");
		h_DATAone_hEE->SetMarkerStyle(22);
		CompMC1data->Update();
		double normda4 = ( (h_ihEE_data_PUR->Integral())/ h_MCone_hEE->Integral());
		h_MCone_hEE->Scale(normda4);
		normda4 = ( (h_ihEE_data_PUR->Integral())/ h_DATAone_hEE->Integral());
		h_DATAone_hEE->Sumw2();
		h_DATAone_hEE->Scale(normda4);


		TPaveStats *stada6 = (TPaveStats*)h_MCone_hEE->FindObject("stats"); 
		stada6->SetY1NDC(0.878); 
		stada6->SetY2NDC(0.75); 
		stada6->SetTextColor(kRed);
		stada6->Draw();
		CompMC1data->Update();

		TLegend *da1leg4 = new TLegend(0.6,0.75,0.825,0.9);
		da1leg4->SetBorderSize(0);
		da1leg4->SetEntrySeparation(0.01);
		da1leg4->SetFillColor(0);
		da1leg4->AddEntry(h_ihEE_data,"data","p");
		da1leg4->AddEntry(h_MCone_hEE,"MonteCarlo vtx=1","l");
		da1leg4->AddEntry(h_DATAone_hEE,"data vtx=1","p");
		da1leg4->Draw();
		CompMC1data->Update();

		CompMC1data->cd(5);
		gPad->SetLogy(1);
		h_trkEB_data_PUR->SetTitle(name.c_str());
		h_trkEB_data_PUR->SetMarkerColor(kBlack);
		h_trkEB_data_PUR->GetXaxis()->SetTitle("IsoTrk Barrel");
		h_trkEB_data_PUR->GetYaxis()->SetTitle("Entries");
		h_trkEB_data_PUR->SetLineColor(kBlack);
		h_trkEB_data_PUR->SetMarkerColor(kBlack);
		h_trkEB_data_PUR->Draw("E1");
		h_MCone_tEB->SetMarkerColor(kRed);
		h_MCone_tEB->SetLineColor(kRed);
		h_DATAone_tEB->SetMarkerColor(kBlue);
		h_DATAone_tEB->SetLineColor(kBlue);
		h_DATAone_tEB->Draw("E1 SAMES");
		h_DATAone_tEB->SetMarkerStyle(22);
		h_MCone_tEB->Draw("HIST SAMES");
		CompMC1data->Update();
		double normda7 = ( (h_trkEB_data_PUR->Integral())/ h_MCone_tEB->Integral());
		h_MCone_tEB->Scale(normda7);
		normda7 = ( (h_trkEB_data_PUR->Integral())/ h_DATAone_tEB->Integral());
		h_DATAone_tEB->Sumw2();
		h_DATAone_tEB->Scale(normda7);

		TPaveStats *stada7 = (TPaveStats*)h_MCone_tEB->FindObject("stats"); 
		stada7->SetY1NDC(0.875); 
		stada7->SetY2NDC(0.75); 
		stada7->SetTextColor(kRed);
		stada7->Draw();
		CompMC1data->Update();

		TLegend *da1leg7 = new TLegend(0.6,0.75,0.825,0.9);
		da1leg7->SetBorderSize(0);
		da1leg7->SetEntrySeparation(0.01);
		da1leg7->SetFillColor(0);
		da1leg7->AddEntry(h_trkEB_data,"data","p");
		da1leg7->AddEntry(h_MCone_tEB,"MonteCarlo vtx=1","l");
		da1leg7->AddEntry(h_DATAone_tEB,"data vtx=1","p");
		da1leg7->Draw();

		CompMC1data->cd(6);
		gPad->SetLogy(1);
		h_trkEE_data_PUR->SetTitle(name.c_str());
		h_trkEE_data_PUR->GetXaxis()->SetTitle("IsoTrk Endcap");
		h_trkEE_data_PUR->GetYaxis()->SetTitle("Entries");
		h_trkEE_data_PUR->SetLineColor(kBlack);
		h_trkEE_data_PUR->SetMarkerColor(kBlack);
		h_trkEE_data_PUR->Draw("E1");
		h_MCone_tEE->SetMarkerColor(kRed);
		h_MCone_tEE->SetLineColor(kRed);
		h_MCone_tEE->Draw("HIST SAMES");
		h_DATAone_tEE->SetMarkerColor(kBlue);
		h_DATAone_tEE->SetLineColor(kBlue);
		h_DATAone_tEE->Draw("E1 SAMES");
		h_DATAone_tEE->SetMarkerStyle(22);
		CompMC1data->Update();
		double normda8 = ( (h_trkEE_data_PUR->Integral())/ h_MCone_tEE->Integral());
		h_MCone_tEE->Scale(normda8);
		normda8 = ( (h_trkEE_data_PUR->Integral())/ h_DATAone_tEE->Integral());
		h_DATAone_tEE->Sumw2();
		h_DATAone_tEE->Scale(normda8);

		TPaveStats *stada8 = (TPaveStats*)h_MCone_tEE->FindObject("stats"); 
		stada8->SetY1NDC(0.875); 
		stada8->SetY2NDC(0.75); 
		stada8->SetTextColor(kRed);
		stada8->Draw();
		CompMC1data->Update();

		TLegend *da1leg8 = new TLegend(0.6,0.75,0.825,0.9);
		da1leg8->SetBorderSize(0);
		da1leg8->SetEntrySeparation(0.01);
		da1leg8->SetFillColor(0);
		da1leg8->AddEntry(h_trkEE_data,"data","p");
		da1leg8->AddEntry(h_MCone_tEE,"MonteCarlo vtx=1","l");
		da1leg8->AddEntry(h_DATAone_tEE,"data vtx=1","p");
		da1leg8->Draw();
		CompMC1data->Update();

		picname="Trk-Ecal-Hcal-Isolation-mc1dataN"+oss.str()+".png";
		eps="Trk-Ecal-Hcal-Isolation-mc1dataN"+oss.str()+".eps";
		CompMC1data->Print(picname.c_str());
		CompMC1data->Print(eps.c_str());



//MC con VTX==1 vs. dataPUR con VTX==N

		//Definizione canvas e riempimento
		//EB
		TCanvas* CompMC1dataPUR = (TCanvas*)gDirectory->GetList()->FindObject("CompMC1dataPUR");
		if (CompMC1dataPUR) delete CompMC1dataPUR;
		CompMC1dataPUR = new TCanvas("CompMC1dataPUR","CompMC1dataPUR",0,0,1200,800);
		CompMC1dataPUR->Divide(2,3);
		CompMC1dataPUR->cd(1);


		gPad->SetLogy(1);
		h_ieEB_data_PUR->SetTitle(name.c_str());
		h_ieEB_data_PUR->SetMarkerColor(kBlack);
		h_ieEB_data_PUR->GetXaxis()->SetTitle("IsoEcal Barrel");
		h_ieEB_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ieEB_data_PUR->SetLineColor(kBlack);
		h_ieEB_data_PUR->SetMarkerColor(kBlack);
		h_ieEB_data_PUR->Draw("E1");
		h_MCone_eEB->SetMarkerColor(kRed);
		h_MCone_eEB->SetLineColor(kRed);
		h_MCone_eEB->Draw("HIST SAMES");
		CompMC1dataPUR->Update();
		double normmc = ((h_ieEB_data_PUR->Integral()) / h_MCone_eEB->Integral()) ;
		h_MCone_eEB->Scale(normmc);

		TPaveStats *stamc2 = (TPaveStats*)h_MCone_eEB->FindObject("stats"); 
		stamc2->SetY1NDC(0.875); 
		stamc2->SetY2NDC(0.75); 
		stamc2->SetTextColor(kRed);
		stamc2->Draw();
		CompMC1dataPUR->Update();

		TLegend *mc1leg = new TLegend(0.6,0.75,0.825,0.9);
		mc1leg->SetBorderSize(0);
		mc1leg->SetEntrySeparation(0.01);
		mc1leg->SetFillColor(0);
		mc1leg->AddEntry(h_ieEB_data_PUR,"data PUR","p");
		mc1leg->AddEntry(h_MCone_eEB,"MonteCarlo vtx=1","l");
		mc1leg->Draw();
		CompMC1dataPUR->Update();


		//
		CompMC1dataPUR->cd(2);
		gPad->SetLogy(1);
		h_ieEE_data_PUR->SetTitle(name.c_str());
		h_ieEE_data_PUR->SetMarkerColor(kBlack);
		h_ieEE_data_PUR->SetLineColor(kBlack);
		h_ieEE_data_PUR->GetXaxis()->SetTitle("IsoEcal Endcap");
		h_ieEE_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ieEE_data_PUR->Draw("E1");
		h_MCone_eEE->SetMarkerColor(kRed);
		h_MCone_eEE->SetLineColor(kRed);
		h_MCone_eEE->Draw("HIST SAMES");
		CompMC1dataPUR->Update();
		double normmc3 = ( (h_ieEE_data_PUR->Integral())/ h_MCone_eEE->Integral());
		h_MCone_eEE->Scale(normmc3);

		TPaveStats *stamc5 = (TPaveStats*) h_MCone_eEE->FindObject("stats"); 
		stamc5->SetY1NDC(0.878); 
		stamc5->SetY2NDC(0.75); 
		stamc5->SetTextColor(kRed);
		stamc5->Draw();
		CompMC1dataPUR->Update();

		TLegend *mc1leg3 = new TLegend(0.6,0.75,0.825,0.9);
		mc1leg3->SetBorderSize(0);
		mc1leg3->SetEntrySeparation(0.01);
		mc1leg3->SetFillColor(0);
		mc1leg3->AddEntry(h_ieEE_data_PUR,"data PUR","p");
		mc1leg3->AddEntry(h_MCone_eEE,"MonteCarlo vtx=1","l");
		mc1leg3->Draw();
		CompMC1dataPUR->Update();

		//
		CompMC1dataPUR->cd(3);
		gPad->SetLogy(1);
		h_ihEB_data_PUR->SetTitle(name.c_str());
		h_ihEB_data_PUR->SetMarkerColor(kBlack);
		h_ihEB_data_PUR->SetLineColor(kBlack);
		h_ihEB_data_PUR->GetXaxis()->SetTitle("IsoHcal Barrel");
		h_ihEB_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ihEB_data_PUR->Draw("E1");
		h_MCone_hEB->SetMarkerColor(kRed);
		h_MCone_hEB->SetLineColor(kRed);
		h_MCone_hEB->Draw("HIST SAMES");
		CompMC1dataPUR->Update();
		double normmc2 = ( (h_ihEB_data_PUR->Integral()) / h_MCone_hEB->Integral());
		h_MCone_hEB->Scale(normmc2);

		TPaveStats *stamc3 = (TPaveStats*) h_MCone_hEB->FindObject("stats"); 
		stamc3->SetY1NDC(0.878); 
		stamc3->SetY2NDC(0.75); 
		stamc3->SetTextColor(kRed);
		stamc3->Draw();
		CompMC1dataPUR->Update();

		TLegend *mc1leg2 = new TLegend(0.6,0.75,0.825,0.9);
		mc1leg2->SetBorderSize(0);
		mc1leg2->SetEntrySeparation(0.01);
		mc1leg2->SetFillColor(0);
		mc1leg2->AddEntry(h_ihEB_data_PUR,"data PUR","p");
		mc1leg2->AddEntry(h_MCone_hEB,"MonteCarlo vtx=1","l");
		mc1leg2->Draw();
		CompMC1dataPUR->Update();

		//
		CompMC1dataPUR->cd(4);
		gPad->SetLogy(1);
		h_ihEE_data_PUR->SetTitle(name.c_str());
		h_ihEE_data_PUR->SetMarkerColor(kBlack);
		h_ihEE_data_PUR->SetLineColor(kBlack);
		h_ihEE_data_PUR->GetXaxis()->SetTitle("IsoHcal Endcap");
		h_ihEE_data_PUR->GetYaxis()->SetTitle("Entries");
		h_ihEE_data_PUR->Draw("E1");
		h_MCone_hEE->SetMarkerColor(kRed);
		h_MCone_hEE->SetLineColor(kRed);
		h_MCone_hEE->Draw("HIST SAMES");
		CompMC1dataPUR->Update();
		double normmc4 = ( (h_ihEE_data_PUR->Integral())/ h_MCone_hEE->Integral());
		h_MCone_hEE->Scale(normmc4);

		TPaveStats *stamc6 = (TPaveStats*)h_MCone_hEE->FindObject("stats"); 
		stamc6->SetY1NDC(0.878); 
		stamc6->SetY2NDC(0.75); 
		stamc6->SetTextColor(kRed);
		stamc6->Draw();
		CompMC1dataPUR->Update();

		TLegend *mc1leg4 = new TLegend(0.6,0.75,0.825,0.9);
		mc1leg4->SetBorderSize(0);
		mc1leg4->SetEntrySeparation(0.01);
		mc1leg4->SetFillColor(0);
		mc1leg4->AddEntry(h_ihEE_data_PUR,"data PUR","p");
		mc1leg4->AddEntry(h_MCone_hEE,"MonteCarlo vtx=1","l");
		mc1leg4->Draw();
		CompMC1dataPUR->Update();

		CompMC1dataPUR->cd(5);
		gPad->SetLogy(1);
		h_trkEB_data_PUR->SetTitle(name.c_str());
		h_trkEB_data_PUR->SetMarkerColor(kBlack);
		h_trkEB_data_PUR->GetXaxis()->SetTitle("IsoTrk Barrel");
		h_trkEB_data_PUR->GetYaxis()->SetTitle("Entries");
		h_trkEB_data_PUR->SetLineColor(kBlack);
		h_trkEB_data_PUR->SetMarkerColor(kBlack);
		h_trkEB_data_PUR->Draw("E1");
		h_MCone_tEB->SetMarkerColor(kRed);
		h_MCone_tEB->SetLineColor(kRed);
		h_MCone_tEB->Draw("HIST SAMES");
		CompMC1dataPUR->Update();
		double normmc7 = ( (h_trkEB_data_PUR->Integral())/ h_MCone_tEB->Integral());
		h_MCone_tEB->Scale(normmc7);

		TPaveStats *stamc7 = (TPaveStats*)h_MCone_tEB->FindObject("stats"); 
		stamc7->SetY1NDC(0.875); 
		stamc7->SetY2NDC(0.75); 
		stamc7->SetTextColor(kRed);
		stamc7->Draw();
		CompMC1dataPUR->Update();

		TLegend *mc1leg7 = new TLegend(0.6,0.75,0.825,0.9);
		mc1leg7->SetBorderSize(0);
		mc1leg7->SetEntrySeparation(0.01);
		mc1leg7->SetFillColor(0);
		mc1leg7->AddEntry(h_trkEB_data_PUR,"data PUR","p");
		mc1leg7->AddEntry(h_MCone_tEB,"MonteCarlo vtx=1","l");
		mc1leg7->Draw();

		CompMC1dataPUR->cd(6);
		gPad->SetLogy(1);
		h_trkEE_data_PUR->SetTitle(name.c_str());
		h_trkEE_data_PUR->GetXaxis()->SetTitle("IsoTrk Endcap");
		h_trkEE_data_PUR->GetYaxis()->SetTitle("Entries");
		h_trkEE_data_PUR->SetLineColor(kBlack);
		h_trkEE_data_PUR->SetMarkerColor(kBlack);
		h_trkEE_data_PUR->Draw("E1");
		h_MCone_tEE->SetMarkerColor(kRed);
		h_MCone_tEE->SetLineColor(kRed);
		h_MCone_tEE->Draw("HIST SAMES");
		CompMC1dataPUR->Update();
		double normmc8 = ( (h_trkEE_data_PUR->Integral())/ h_MCone_tEE->Integral());
		h_MCone_tEE->Scale(normmc8);

		TPaveStats *stamc8 = (TPaveStats*)h_MCone_tEE->FindObject("stats"); 
		stamc8->SetY1NDC(0.875); 
		stamc8->SetY2NDC(0.75); 
		stamc8->SetTextColor(kRed);
		stamc8->Draw();
		CompMC1dataPUR->Update();

		TLegend *mc1leg8 = new TLegend(0.6,0.75,0.825,0.9);
		mc1leg8->SetBorderSize(0);
		mc1leg8->SetEntrySeparation(0.01);
		mc1leg8->SetFillColor(0);
		mc1leg8->AddEntry(h_trkEE_data_PUR,"data PUR","p");
		mc1leg8->AddEntry(h_MCone_tEE,"MonteCarlo vtx=1","l");
		mc1leg8->Draw();
		CompMC1dataPUR->Update();

		picname="Trk-Ecal-Hcal-Isolation-mc1dataN-pur"+oss.str()+".png";
		eps="Trk-Ecal-Hcal-Isolation-mc1dataN-pur"+oss.str()+".eps";
		CompMC1dataPUR->Print(picname.c_str());
		CompMC1dataPUR->Print(eps.c_str());



//DATA vtx==1 vs. MC vtx==N
		TCanvas* Data1McN = (TCanvas*)gDirectory->GetList()->FindObject("Data1McN");
		if (Data1McN) delete Data1McN;
		Data1McN = new TCanvas("Data1McN","Data1McN",0,0,1200,800);
		Data1McN->Divide(2,3);
		Data1McN->cd(1);


		Data1McN->cd(1);
		gPad->SetLogy(1);
		h_DATAone_eEB->SetTitle(name.c_str());
		h_DATAone_eEB->SetMarkerColor(kBlack);
		h_DATAone_eEB->GetXaxis()->SetTitle("IsoEcal Barrel");
		h_DATAone_eEB->GetYaxis()->SetTitle("Entries");
		h_DATAone_eEB->SetLineColor(kBlack);
		h_DATAone_eEB->SetMarkerColor(kBlack);
		h_DATAone_eEB->Draw("E1");
		h_ieEB_pf->SetMarkerColor(kRed);
		h_ieEB_pf->SetLineColor(kRed);
		h_ieEB_pf->Draw("HIST SAMES");
		Data1McN->Update();
		double Norm = ((h_DATAone_eEB->Integral()) / h_ieEB_pf->Integral()) ;
		h_ieEB_pf->Scale(Norm);

		TPaveStats *tps2 = (TPaveStats*)h_ieEB_pf->FindObject("stats"); 
		tps2->SetY1NDC(0.875); 
		tps2->SetY2NDC(0.75); 
		tps2->SetTextColor(kRed);
		tps2->Draw();
		Data1McN->Update();

		TLegend *Leg = new TLegend(0.6,0.75,0.825,0.9);
		Leg->SetBorderSize(0);
		Leg->SetEntrySeparation(0.01);
		Leg->SetFillColor(0);
		Leg->AddEntry(h_DATAone_eEB,"data vtx=1","p");
		Leg->AddEntry( h_ieEB_pf,"MonteCarlo","l");
		Leg->Draw();
		Data1McN->Update();


		//
		Data1McN->cd(2);
		gPad->SetLogy(1);
		h_DATAone_eEE->SetTitle(name.c_str());
		h_DATAone_eEE->SetMarkerColor(kBlack);
		h_DATAone_eEE->SetLineColor(kBlack);
		h_DATAone_eEE->GetXaxis()->SetTitle("IsoEcal Endcap");
		h_DATAone_eEE->GetYaxis()->SetTitle("Entries");
		h_DATAone_eEE->Draw("E1");
		h_ieEE_pf->SetMarkerColor(kRed);
		h_ieEE_pf->SetLineColor(kRed);
		h_ieEE_pf->Draw("HIST SAMES");
		Data1McN->Update();
		double Norm3 = ( (h_DATAone_eEE->Integral())/ h_ieEE_pf->Integral());
		h_ieEE_pf->Scale(Norm3);

		TPaveStats *tps5 = (TPaveStats*) h_ieEE_pf->FindObject("stats"); 
		tps5->SetY1NDC(0.878); 
		tps5->SetY2NDC(0.75); 
		tps5->SetTextColor(kRed);
		tps5->Draw();
		Data1McN->Update();

		TLegend *Leg3 = new TLegend(0.6,0.75,0.825,0.9);
		Leg3->SetBorderSize(0);
		Leg3->SetEntrySeparation(0.01);
		Leg3->SetFillColor(0);
		Leg3->AddEntry(h_DATAone_eEE,"data vtx=1","p");
		Leg3->AddEntry(h_ieEE_pf,"MonteCarlo","l");
		Leg3->Draw();
		Data1McN->Update();

		//
		Data1McN->cd(3);
		gPad->SetLogy(1);
		h_DATAone_hEB->SetTitle(name.c_str());
		h_DATAone_hEB->SetMarkerColor(kBlack);
		h_DATAone_hEB->SetLineColor(kBlack);
		h_DATAone_hEB->GetXaxis()->SetTitle("IsoHcal Barrel");
		h_DATAone_hEB->GetYaxis()->SetTitle("Entries");
		h_DATAone_hEB->Draw("E1");
		h_ihEB_pf->SetMarkerColor(kRed);
		h_ihEB_pf->SetLineColor(kRed);
		h_ihEB_pf->Draw("HIST SAMES");
		Data1McN->Update();
		double Norm2 = ( (h_DATAone_hEB->Integral()) / h_ihEB_pf->Integral());
		h_ihEB_pf->Scale(Norm2);

		TPaveStats *tps3 = (TPaveStats*) h_ihEB_pf->FindObject("stats"); 
		tps3->SetY1NDC(0.878); 
		tps3->SetY2NDC(0.75); 
		tps3->SetTextColor(kRed);
		tps3->Draw();
		Data1McN->Update();

		TLegend *Leg2 = new TLegend(0.6,0.75,0.825,0.9);
		Leg2->SetBorderSize(0);
		Leg2->SetEntrySeparation(0.01);
		Leg2->SetFillColor(0);
		Leg2->AddEntry(h_DATAone_hEB,"data vtx=1","p");
		Leg2->AddEntry( h_ihEB_pf,"MonteCarlo","l");
		Leg2->Draw();
		Data1McN->Update();

		//
		Data1McN->cd(4);
		gPad->SetLogy(1);
		h_DATAone_hEE->SetTitle(name.c_str());
		h_DATAone_hEE->SetMarkerColor(kBlack);
		h_DATAone_hEE->SetLineColor(kBlack);
		h_DATAone_hEE->GetXaxis()->SetTitle("IsoHcal Endcap");
		h_DATAone_hEE->GetYaxis()->SetTitle("Entries");
		h_DATAone_hEE->Draw("E1");
		h_ihEE_pf->SetMarkerColor(kRed);
		h_ihEE_pf->SetLineColor(kRed);
		h_ihEE_pf->Draw("HIST SAMES");
		Data1McN->Update();
		double Norm4 = ( (h_DATAone_hEE->Integral())/ h_ihEE_pf->Integral());
		h_ihEE_pf->Scale(Norm4);

		TPaveStats *tps6 = (TPaveStats*)h_ihEE_pf->FindObject("stats"); 
		tps6->SetY1NDC(0.878); 
		tps6->SetY2NDC(0.75); 
		tps6->SetTextColor(kRed);
		tps6->Draw();
		Data1McN->Update();

		TLegend *Leg4 = new TLegend(0.6,0.75,0.825,0.9);
		Leg4->SetBorderSize(0);
		Leg4->SetEntrySeparation(0.01);
		Leg4->SetFillColor(0);
		Leg4->AddEntry(h_DATAone_hEE,"data vtx=1","p");
		Leg4->AddEntry(h_ihEE_pf,"MonteCarlo","l");
		Leg4->Draw();
		Data1McN->Update();

		Data1McN->cd(5);
		gPad->SetLogy(1);
		h_DATAone_tEB->SetTitle(name.c_str());
		h_DATAone_tEB->SetMarkerColor(kBlack);
		h_DATAone_tEB->GetXaxis()->SetTitle("IsoTrk Barrel");
		h_DATAone_tEB->GetYaxis()->SetTitle("Entries");
		h_DATAone_tEB->SetLineColor(kBlack);
		h_DATAone_tEB->SetMarkerColor(kBlack);
		h_DATAone_tEB->Draw("E1");
		h_trkEB_pf->SetMarkerColor(kRed);
		h_trkEB_pf->SetLineColor(kRed);
		h_trkEB_pf->Draw("HIST SAMES");
		Data1McN->Update();
		double Norm7 = ( (h_DATAone_tEB->Integral())/ h_trkEB_pf->Integral());
		h_trkEB_pf->Scale(Norm7);

		TPaveStats *tps7 = (TPaveStats*)h_trkEB_pf->FindObject("stats"); 
		tps7->SetY1NDC(0.875); 
		tps7->SetY2NDC(0.75); 
		tps7->SetTextColor(kRed);
		tps7->Draw();
		Data1McN->Update();

		TLegend *Leg7 = new TLegend(0.6,0.75,0.825,0.9);
		Leg7->SetBorderSize(0);
		Leg7->SetEntrySeparation(0.01);
		Leg7->SetFillColor(0);
		Leg7->AddEntry(h_DATAone_tEB,"data vtx=1","p");
		Leg7->AddEntry( h_trkEB_pf,"MonteCarlo","l");
		Leg7->Draw();

		Data1McN->cd(6);
		gPad->SetLogy(1);
		h_DATAone_tEE->SetTitle(name.c_str());
		h_DATAone_tEE->GetXaxis()->SetTitle("IsoTrk Endcap");
		h_DATAone_tEE->GetYaxis()->SetTitle("Entries");
		h_DATAone_tEE->SetLineColor(kBlack);
		h_DATAone_tEE->SetMarkerColor(kBlack);
		h_DATAone_tEE->Draw("E1");
		h_trkEE_pf->SetMarkerColor(kRed);
		h_trkEE_pf->SetLineColor(kRed);
		h_trkEE_pf->Draw("HIST SAMES");
		Data1McN->Update();
		double Norm8 = ( (h_DATAone_tEE->Integral())/ h_trkEE_pf->Integral());
		h_trkEE_pf->Scale(Norm8);

		TPaveStats *tps8 = (TPaveStats*)h_trkEE_pf->FindObject("stats"); 
		tps8->SetY1NDC(0.875); 
		tps8->SetY2NDC(0.75); 
		tps8->SetTextColor(kRed);
		tps8->Draw();
		Data1McN->Update();

		TLegend *Leg8 = new TLegend(0.6,0.75,0.825,0.9);
		Leg8->SetBorderSize(0);
		Leg8->SetEntrySeparation(0.01);
		Leg8->SetFillColor(0);
		Leg8->AddEntry(h_DATAone_tEE,"data vtx=1","p");
		Leg8->AddEntry(h_trkEE_pf,"MonteCarlo","l");
		Leg8->Draw();
		Data1McN->Update();

		picname="Trk-Ecal-Hcal-Isolation-data1mcN"+oss.str()+".png";
		eps="Trk-Ecal-Hcal-Isolation-data1mcN"+oss.str()+".eps";
		Data1McN->Print(picname.c_str());
		Data1McN->Print(eps.c_str());
*/
		oss.clear();
		oss.str("");





	} //END OF LOOP on vtx

/*
	//=================//
	//      TOTALE     //
	//=================//
	TCanvas* Tot = (TCanvas*)gDirectory->GetList()->FindObject("Tot");
	if (Tot) delete Tot;
	Tot = new TCanvas("Totale","Totale",0,0,1200,800);
	Tot->Divide(2,3);

	Tot->cd(1);
	gPad->SetLogy(1);
	h_ieEB->GetXaxis()->SetTitle("IsoEcal Barrel");
	h_ieEB->GetYaxis()->SetTitle("Entries");
	h_ieEB->SetLineColor(kBlack);
	h_ieEB->SetMarkerColor(kBlack);
	h_ieEB->Draw("E1");
	h_ieEB_mc->SetMarkerColor(kRed);
	h_ieEB_mc->SetLineColor(kRed);
	h_ieEB_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t3 = (TPaveStats*)h_ieEB_mc->FindObject("stats"); 
	t3->SetY1NDC(0.875); 
	t3->SetY2NDC(0.75); 
	t3->SetTextColor(kRed);
	t3->Draw();
	Tot->Update();

	Tot->cd(2);
	gPad->SetLogy(1);
	h_ieEE->GetXaxis()->SetTitle("IsoEcal Endcap");
	h_ieEE->GetYaxis()->SetTitle("Entries");
	h_ieEE->SetLineColor(kBlack);
	h_ieEE->SetMarkerColor(kBlack);
	h_ieEE->Draw("E1");
	h_ieEE_mc->SetMarkerColor(kRed);
	h_ieEE_mc->SetLineColor(kRed);
	h_ieEE_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t4 = (TPaveStats*)h_ieEE_mc->FindObject("stats"); 
	t4->SetY1NDC(0.875); 
	t4->SetY2NDC(0.75); 
	t4->SetTextColor(kRed);
	t4->Draw();
	Tot->Update();

//////////////////

	Tot->cd(3);
	gPad->SetLogy(1);
	h_ihEB->GetXaxis()->SetTitle("IsoHcal Barrel");
	h_ihEB->GetYaxis()->SetTitle("Entries");
	h_ihEB->SetLineColor(kBlack);
	h_ihEB->SetMarkerColor(kBlack);
	h_ihEB->Draw("E1");
	h_ihEB_mc->SetMarkerColor(kRed);
	h_ihEB_mc->SetLineColor(kRed);
	h_ihEB_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t5 = (TPaveStats*)h_ihEB_mc->FindObject("stats"); 
	t5->SetY1NDC(0.875); 
	t5->SetY2NDC(0.75); 
	t5->SetTextColor(kRed);
	t5->Draw();
	Tot->Update();

	Tot->cd(4);
	gPad->SetLogy(1);
	h_ihEE->GetXaxis()->SetTitle("IsoHcal Endcap");
	h_ihEE->GetYaxis()->SetTitle("Entries");
	h_ihEE->SetLineColor(kBlack);
	h_ihEE->SetMarkerColor(kBlack);
	h_ihEE->Draw("E1");
	h_ihEE_mc->SetMarkerColor(kRed);
	h_ihEE_mc->SetLineColor(kRed);
	h_ihEE_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t6 = (TPaveStats*)h_ihEE_mc->FindObject("stats"); 
	t6->SetY1NDC(0.875); 
	t6->SetY2NDC(0.75); 
	t6->SetTextColor(kRed);
	t6->Draw();
	Tot->Update();

//////////////

	Tot->cd(5);
	gPad->SetLogy(1);
	h_trkEB->GetXaxis()->SetTitle("IsoTrk Barrel");
	h_trkEB->GetYaxis()->SetTitle("Entries");
	h_trkEB->SetLineColor(kBlack);
	h_trkEB->SetMarkerColor(kBlack);
	h_trkEB->Draw("E1");
	h_trkEB_mc->SetMarkerColor(kRed);
	h_trkEB_mc->SetLineColor(kRed);
	h_trkEB_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t1 = (TPaveStats*)h_trkEB_mc->FindObject("stats"); 
	t1->SetY1NDC(0.875); 
	t1->SetY2NDC(0.75); 
	t1->SetTextColor(kRed);
	t1->Draw();
	Tot->Update();

	Tot->cd(6);
	gPad->SetLogy(1);
	h_trkEE->GetXaxis()->SetTitle("IsoTrk Endcap");
	h_trkEE->GetYaxis()->SetTitle("Entries");
	h_trkEE->SetLineColor(kBlack);
	h_trkEE->SetMarkerColor(kBlack);
	h_trkEE->Draw("E1");
	h_trkEE_mc->SetMarkerColor(kRed);
	h_trkEE_mc->SetLineColor(kRed);
	h_trkEE_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t2 = (TPaveStats*)h_trkEE_mc->FindObject("stats"); 
	t2->SetY1NDC(0.875); 
	t2->SetY2NDC(0.75); 
	t2->SetTextColor(kRed);
	t2->Draw();
	Tot->Update();




	Tot->Print("totale.eps");
	Tot->Print("totale.png");
*/
return;
}



