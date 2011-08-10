#include "MMutil.C"
#include "tdrStyle.C"
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"



void comparisonMCdata(){

	
	gROOT->ForceStyle();
	setTDRStyle();
	TFile *dataf = TFile::Open("rfio:/castor/cern.ch/user/m/marone/ZJets/results/PreselectionMay10_v1_1.root"); //data file
	TFile *dataremoved = TFile::Open("rfio:/castor/cern.ch/user/m/marone/ZJets/results/PreselectionMay10PURemoved_v1_1.root");
	TFile *mcf = TFile::Open("rfio:/castor/cern.ch/user/m/marone/ZJets/results/PreselectionMC_v1_1.root"); //MC file

	//DATA	
	dataf->cd("demo");
	//Numero di entries
	Int_t entries = treeVJ_->GetEntries();
	printf("Useful data:\ndata entries= %d \n",entries);

	//Creazione degli istogrammi
	//FIXME da duplicare per il file di MC
	//EB data
	TH1D* h_itEB_data = (TH1D*)gDirectory->GetList()->FindObject("h_itEB_data");
	if (h_itEB_data) delete h_itEB_data;
	h_itEB_data = new TH1D("h_itEB_data","IsoTrk EB",40,0.,0.40);
	treeVJ_->Draw("IsoTrkEB>>h_itEB_data");

	TH1D* h_ieEB_data = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB_data");
	if (h_ieEB_data) delete h_ieEB_data;
	h_ieEB_data = new TH1D("h_ieEB_data","IsoEcal EB",40,0.,0.40);
	treeVJ_->Draw("IsoEcalEB>>h_ieEB_data");

	TH1D* h_ihEB_data = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB_data");
	if (h_ihEB_data) delete h_ihEB_data;
	h_ihEB_data = new TH1D("h_ihEB_data","IsoHcal EB",40,0.,0.40);
	treeVJ_->Draw("IsoHcalEB>>h_ihEB_data");

	//EE data
	TH1D* h_itEE_data = (TH1D*)gDirectory->GetList()->FindObject("h_itEE_data");
	if (h_itEE_data) delete h_itEE_data;
	h_itEE_data = new TH1D("h_itEE_data","IsoTrk EE",40,0.,0.40);
	treeVJ_->Draw("IsoTrkEE>>h_itEE_data");

	TH1D* h_ieEE_data = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE_data");
	if (h_ieEE_data) delete h_ieEE_data;
	h_ieEE_data = new TH1D("h_ieEE_data","IsoEcal EE",40,0.,0.40);
	treeVJ_->Draw("IsoEcalEE>>h_ieEE_data");

	TH1D* h_ihEE_data = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE_data");
	if (h_ihEE_data) delete h_ihEE_data;
	h_ihEE_data = new TH1D("h_ihEE_data","IsoHcal EE",40,0.,0.40);
	treeVJ_->Draw("IsoHcalEE>>h_ihEE_data");


	//DATA REMOVED PU
	dataremoved->cd("demo");
	//Numero di entries
	Int_t rementries = treeVJ_->GetEntries();
	printf("Useful data:\ndata removed entries= %d \n",rementries);

	//EB data
	TH1D* h_itEB_rem = (TH1D*)gDirectory->GetList()->FindObject("h_itEB_rem");
	if (h_itEB_rem) delete h_itEB_rem;
	h_itEB_rem = new TH1D("h_itEB_rem","IsoTrk EB",40,0.,0.40);
	treeVJ_->Draw("IsoTrkEB>>h_itEB_rem");

	TH1D* h_ieEB_rem = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB_rem");
	if (h_ieEB_rem) delete h_ieEB_rem;
	h_ieEB_rem = new TH1D("h_ieEB_rem","IsoEcal EB",40,0.,0.40);
	treeVJ_->Draw("IsoEcalEB>>h_ieEB_rem");

	TH1D* h_ihEB_rem = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB_rem");
	if (h_ihEB_rem) delete h_ihEB_rem;
	h_ihEB_rem = new TH1D("h_ihEB_rem","IsoHcal EB",40,0.,0.40);
	treeVJ_->Draw("IsoHcalEB>>h_ihEB_rem");

	//EE data
	TH1D* h_itEE_rem = (TH1D*)gDirectory->GetList()->FindObject("h_itEE_rem");
	if (h_itEE_rem) delete h_itEE_rem;
	h_itEE_rem = new TH1D("h_itEE_rem","IsoTrk EE",40,0.,0.40);
	treeVJ_->Draw("IsoTrkEE>>h_itEE_rem");

	TH1D* h_ieEE_rem = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE_rem");
	if (h_ieEE_rem) delete h_ieEE_rem;
	h_ieEE_rem = new TH1D("h_ieEE_rem","IsoEcal EE",40,0.,0.40);
	treeVJ_->Draw("IsoEcalEE>>h_ieEE_rem");

	TH1D* h_ihEE_rem = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE_rem");
	if (h_ihEE_rem) delete h_ihEE_rem;
	h_ihEE_rem = new TH1D("h_ihEE_rem","IsoHcal EE",40,0.,0.40);
	treeVJ_->Draw("IsoHcalEE>>h_ihEE_rem");


	//MC
	mcf->cd("demo");
	Int_t mcentries = treeVJ_->GetEntries();
	printf("Useful data:\nmc entries= %d \n",mcentries);

	float scale=((float)entries)/((float)mcentries);
	
	//EB mc
	TH1D* h_itEB_mc = (TH1D*)gDirectory->GetList()->FindObject("h_itEB_mc");
	if (h_itEB_mc) delete h_itEB_mc;
	h_itEB_mc = new TH1D("h_itEB_mc","IsoTrk EB",40,0.,0.40);
	treeVJ_->Draw("IsoTrkEB>>h_itEB_mc");

	TH1D* h_ieEB_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB_mc");
	if (h_ieEB_mc) delete h_ieEB_mc;
	h_ieEB_mc = new TH1D("h_ieEB_mc","IsoEcal EB",40,0.,0.40);
	treeVJ_->Draw("IsoEcalEB>>h_ieEB_mc");

	TH1D* h_ihEB_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB_mc");
	if (h_ihEB_mc) delete h_ihEB_mc;
	h_ihEB_mc = new TH1D("h_ihEB_mc","IsoHcal EB",40,0.,0.40);
	treeVJ_->Draw("IsoHcalEB>>h_ihEB_mc");

	//EE mc
	TH1D* h_itEE_mc = (TH1D*)gDirectory->GetList()->FindObject("h_itEE_mc");
	if (h_itEE_mc) delete h_itEE_mc;
	h_itEE_mc = new TH1D("h_itEE_mc","IsoTrk EE",40,0.,0.40);
	treeVJ_->Draw("IsoTrkEE>>h_itEE_mc");

	TH1D* h_ieEE_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE_mc");
	if (h_ieEE_mc) delete h_ieEE_mc;
	h_ieEE_mc = new TH1D("h_ieEE_mc","IsoEcal EE",40,0.,0.40);
	treeVJ_->Draw("IsoEcalEE>>h_ieEE_mc");

	TH1D* h_ihEE_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE_mc");
	if (h_ihEE_mc) delete h_ihEE_mc;
	h_ihEE_mc = new TH1D("h_ihEE_mc","IsoHcal EE",40,0.,0.40);
	treeVJ_->Draw("IsoHcalEE>>h_ihEE_mc");


	//Definizione canvas e riempimento
	//EB
	TCanvas* Comp_EB = (TCanvas*)gDirectory->GetList()->FindObject("Comp_EB");
	if (Comp_EB) delete Comp_EB;
	Comp_EB = new TCanvas("Comp_EB","Comp_EB",0,0,800,600);
	Comp_EB->Divide(2,2);
	
	Comp_EB->cd(1);
	gPad->SetLogy(1);
	h_itEB_data->SetTitle("IsoTrk EB Comparison; ;entries");
	h_itEB_data->SetMarkerColor(kBlack);
	h_itEB_data->Draw("E");
	h_itEB_mc->SetLineColor(kRed);
	h_itEB_mc->Scale(scale);
	h_itEB_mc->Draw("HIST SAMES");
	h_itEB_rem->SetMarkerColor(kBlue);
	h_itEB_rem->Draw("E SAMES");
	Comp_EB->Update();
	
	TPaveStats *p1 = (TPaveStats*)h_itEB_mc->FindObject("stats"); 
	p1->SetY2NDC(0.75);
	p1->SetTextColor(kRed);
	p1->Draw();
	TPaveStats *r1 = (TPaveStats*)h_itEB_rem->FindObject("stats"); 
	r1->SetY1NDC(0.75); 
	r1->SetY2NDC(0.622); 
	r1->SetTextColor(kBlue);
	r1->Draw();
	Comp_EB->Update();
	
	leg = new TLegend(0.4,0.75,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_itEB_data,"data","p");
	leg->AddEntry(h_itEB_mc,"mc","l");
	leg->AddEntry(h_itEB_rem,"data removed PU","p");
	leg->Draw();
	Comp_EB->Update();


	Comp_EB->cd(2);
	gPad->SetLogy(1);
	h_ieEB_data->SetTitle("IsoEcal EB Comparison; ;entries");
	h_ieEB_data->SetMarkerColor(kBlack);
	h_ieEB_data->Draw("E");
	h_ieEB_mc->SetLineColor(kRed);
	h_ieEB_mc->Scale(scale);
	h_ieEB_mc->Draw("HIST SAMES");
	h_ieEB_rem->SetMarkerColor(kBlue);
	h_ieEB_rem->Draw("E SAMES");
	Comp_EB->Update();

	TPaveStats *p2 = (TPaveStats*)h_ieEB_mc->FindObject("stats"); 
	p2->SetY2NDC(0.75);
	p2->SetTextColor(kRed);
	p2->Draw();
	TPaveStats *r2 = (TPaveStats*)h_ieEB_rem->FindObject("stats"); 
	r2->SetY1NDC(0.75); 
	r2->SetY2NDC(0.622); 
	r2->SetTextColor(kBlue);
	r2->Draw();
	Comp_EB->Update();
	
	leg = new TLegend(0.4,0.75,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_ieEB_data,"data","p");
	leg->AddEntry(h_ieEB_mc,"mc","l");
	leg->AddEntry(h_ieEB_rem,"data removed PU","p");
	leg->Draw();
	Comp_EB->Update();


	Comp_EB->cd(3);
	gPad->SetLogy(1);
	h_ihEB_data->SetTitle("IsoHcal EB Comparison; ;entries");
	h_ihEB_data->SetMarkerColor(kBlack);
	h_ihEB_data->Draw("E");
	h_ihEB_mc->SetLineColor(kRed);
	h_ihEB_mc->Scale(scale);
	h_ihEB_mc->Draw("HIST SAMES");
	h_ihEB_rem->SetMarkerColor(kBlue);
	h_ihEB_rem->Draw("E SAMES");
	Comp_EB->Update();

	TPaveStats *p3 = (TPaveStats*)h_ihEB_mc->FindObject("stats"); 
	p3->SetY2NDC(0.75);
	p3->SetTextColor(kRed);
	p3->Draw();
	TPaveStats *r3 = (TPaveStats*)h_ihEB_rem->FindObject("stats"); 
	r3->SetY1NDC(0.75); 
	r3->SetY2NDC(0.622); 
	r3->SetTextColor(kBlue);
	r3->Draw();
	Comp_EB->Update();
	
	leg = new TLegend(0.4,0.75,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_ihEB_data,"data","p");
	leg->AddEntry(h_ihEB_mc,"mc","l");
	leg->AddEntry(h_ihEB_rem,"data removed PU","p");
	leg->Draw();
	Comp_EB->Update();


	//EE
	TCanvas* Comp_EE = (TCanvas*)gDirectory->GetList()->FindObject("Comp_EE");
	if (Comp_EE) delete Comp_EE;
	Comp_EE = new TCanvas("Comp_EE","Comp_EE",0,0,800,600);
	Comp_EE->Divide(2,2);
	

	Comp_EE->cd(1);
	gPad->SetLogy(1);
	h_itEE_data->SetTitle("IsoTrk EE Comparison; ;entries");
	h_itEE_data->SetMarkerColor(kBlack);
	h_itEE_data->Draw("E");
	h_itEE_mc->SetLineColor(kRed);
	h_itEE_mc->Scale(scale);
	h_itEE_mc->Draw("HIST SAMES");
	h_itEE_rem->SetMarkerColor(kBlue);
	h_itEE_rem->Draw("E SAMES");
	Comp_EE->Update();
	
	TPaveStats *p4 = (TPaveStats*)h_itEE_mc->FindObject("stats"); 
	p4->SetY2NDC(0.75);
	p4->SetTextColor(kRed);
	p4->Draw();
	TPaveStats *r4 = (TPaveStats*)h_itEE_rem->FindObject("stats"); 
	r4->SetY1NDC(0.75); 
	r4->SetY2NDC(0.622); 
	r4->SetTextColor(kBlue);
	r4->Draw();
	Comp_EB->Update();
	
	leg = new TLegend(0.4,0.75,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_itEE_data,"data","p");
	leg->AddEntry(h_itEE_mc,"mc","l");
	leg->AddEntry(h_itEE_rem,"data removed PU","p");
	leg->Draw();
	Comp_EB->Update();


	Comp_EE->cd(2);
	gPad->SetLogy(1);
	h_ieEE_data->SetTitle("IsoEcal EE Comparison; ;entries");
	h_ieEE_data->SetMarkerColor(kBlack);
	h_ieEE_data->Draw("E");
	h_ieEE_mc->SetLineColor(kRed);
	h_ieEE_mc->Scale(scale);
	h_ieEE_mc->Draw("HIST SAMES");
	h_ieEE_rem->SetMarkerColor(kBlue);
	h_ieEE_rem->Draw("E SAMES");
	Comp_EE->Update();
	
	TPaveStats *p5 = (TPaveStats*)h_ieEE_mc->FindObject("stats"); 
	p5->SetY2NDC(0.75);
	p5->SetTextColor(kRed);
	p5->Draw();
	TPaveStats *r5 = (TPaveStats*)h_ieEE_rem->FindObject("stats"); 
	r5->SetY1NDC(0.75); 
	r5->SetY2NDC(0.622); 
	r5->SetTextColor(kBlue);
	r5->Draw();
	Comp_EB->Update();
	
	leg = new TLegend(0.4,0.75,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_ieEE_data,"data","p");
	leg->AddEntry(h_ieEE_mc,"mc","l");
	leg->AddEntry(h_ieEE_rem,"data removed PU","p");
	leg->Draw();
	Comp_EB->Update();


	Comp_EE->cd(3);
	gPad->SetLogy(1);
	h_ihEE_data->SetTitle("IsoHcal EE Comparison; ;entries");
	h_ihEE_data->SetMarkerColor(kBlack);
	h_ihEE_data->Draw("E");
	h_ihEE_mc->SetLineColor(kRed);
	h_ihEE_mc->Scale(scale);
	h_ihEE_mc->Draw("HIST SAMES");
	h_ihEE_rem->SetMarkerColor(kBlue);
	h_ihEE_rem->Draw("E SAMES");
	Comp_EE->Update();
	
	TPaveStats *p6 = (TPaveStats*)h_ihEE_mc->FindObject("stats"); 
	p6->SetY2NDC(0.75);
	p6->SetTextColor(kRed);
	p6->Draw();
	TPaveStats *r6 = (TPaveStats*)h_ihEE_rem->FindObject("stats"); 
	r6->SetY1NDC(0.75); 
	r6->SetY2NDC(0.622); 
	r6->SetTextColor(kBlue);
	r6->Draw();
	Comp_EB->Update();
	
	leg = new TLegend(0.4,0.75,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_ihEE_data,"data","p");
	leg->AddEntry(h_ihEE_mc,"mc","l");
	leg->AddEntry(h_ihEE_rem,"data removed PU","p");
	leg->Draw();
	Comp_EB->Update();


	return;

}
