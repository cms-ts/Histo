#include "MMutil.C"
#include "tdrStyle.C"
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"


TCanvas * EB_plots;
TCanvas * EE_plots;
TCanvas * Common;
TCanvas * Other;


void allplots(){

	setTDRStyle();
	TFile *histof = TFile::Open("../rootf/histo.root");
	TDirectory *dir=histof->Get("demo");


	//EB - Create a Canvas and divide it in Pads
	EB_plots = new TCanvas("EB_plots","EB",400,20,1200,800);
	EB_plots->Divide(4,2);

	//First histogram
	EB_plots->cd(1);
	TH1D *IsoTrk_EB;
	IsoTrk_EB=(TH1D*)dir->Get("h_IsoTrk_EB");
	IsoTrk_EB->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	IsoTrk_EB->SetLineColor(2);
	IsoTrk_EB->Draw();
	//WP Lines and Legend
	leg = new TLegend(0.4,0.55,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(IsoTrk_EB,"data","l");
	TLine *Line = new TLine(0.09,0.,0.09,IsoTrk_EB->GetMaximum());
	Line->SetLineColor(kBlue);
	Line->SetLineStyle(2);
	Line->Draw();
	leg->AddEntry(Line,"WP 80","l");
	TLine *Line = new TLine(0.12,0.,0.12,IsoTrk_EB->GetMaximum());
	Line->SetLineColor(kBlack);
	Line->SetLineStyle(2);
	Line->Draw();
	leg->AddEntry(Line,"WP 90","l");
	leg->Draw();

	//Second histogram
	EB_plots->cd(2);
	TH1D *IsoEcal_EB;
	IsoEcal_EB=(TH1D*)dir->Get("h_IsoEcal_EB");
	IsoEcal_EB->GetYaxis()->SetTitle("Number of Events");
	IsoEcal_EB->SetLineColor(2);
	IsoEcal_EB->Draw();
	BLine(0.07,0.,0.07,IsoEcal_EB->GetMaximum());
	MLine(0.09,0.,0.09,IsoEcal_EB->GetMaximum());
	

	EB_plots->cd(3);
	TH1D *IsoHcal_EB;
	IsoHcal_EB=(TH1D*)dir->Get("h_IsoHcal_EB");
	IsoHcal_EB->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	IsoHcal_EB->SetLineColor(2);
	IsoHcal_EB->Draw();
	BLine(0.10,0.,0.10,IsoHcal_EB->GetMaximum());
	MLine(0.10,0.,0.10,IsoHcal_EB->GetMaximum());
	
	EB_plots->cd(4);
	TH1D *HE_EB;
	HE_EB=(TH1D*)dir->Get("h_HE_EB");
	HE_EB->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	HE_EB->SetLineColor(2);
	HE_EB->Draw();
	BLine(0.04,0.,0.04,HE_EB->GetMaximum());
	MLine(0.12,0.,0.12,HE_EB->GetMaximum());
	
	EB_plots->cd(5);
	TH1F *DeltaPhiTkClu_EB;
	DeltaPhiTkClu_EB=(TH1F*)dir->Get("h_DeltaPhiTkClu_EB");
	DeltaPhiTkClu_EB->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	DeltaPhiTkClu_EB->SetLineColor(2);
	DeltaPhiTkClu_EB->Draw();
	BLine(0.06,0.,0.06,DeltaPhiTkClu_EB->GetMaximum());
	MLine(0.8,0.,0.8,DeltaPhiTkClu_EB->GetMaximum());

	EB_plots->cd(6);
	TH1F *DeltaEtaTkClu_EB;
	DeltaEtaTkClu_EB=(TH1F*)dir->Get("h_DeltaEtaTkClu_EB");
	DeltaEtaTkClu_EB->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	DeltaEtaTkClu_EB->SetLineColor(2);
	DeltaEtaTkClu_EB->Draw();
	BLine(0.004,0.,0.004,DeltaEtaTkClu_EB->GetMaximum());
	MLine(0.007,0.,0.007,DeltaEtaTkClu_EB->GetMaximum());
	
	EB_plots->cd(7);
	TH1F *sigmaIeIe_EB;
	sigmaIeIe_EB=(TH1F*)dir->Get("h_sigmaIeIe_EB");
	sigmaIeIe_EB->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	sigmaIeIe_EB->SetLineColor(2);
	sigmaIeIe_EB->Draw();
	BLine(0.004,0.,0.004,sigmaIeIe_EB->GetMaximum());
	MLine(0.007,0.,0.007,sigmaIeIe_EB->GetMaximum());
	

//	EB_plots->cd(8);
//	TH1F *HE_EB;
//	HE_EB=(TH1F*)dir->Get("h_HE_EB");
//	HE_EB->GetYaxis()->SetTitle("Number of Events");
//	gPad->SetLogy(1);
//	HE_EB->Draw();



	//EE
	EE_plots = new TCanvas("EE_plots","EE",400,20,1200,800);
	EE_plots->Divide(4,2);

	EE_plots->cd(1);
	TH1D *IsoTrk_EE;
	IsoTrk_EE=(TH1D*)dir->Get("h_IsoTrk_EE");
	IsoTrk_EE->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	IsoTrk_EE->SetLineColor(2);
	IsoTrk_EE->Draw();
	BLine(0.04,0.,0.04,IsoTrk_EE->GetMaximum());
	MLine(0.05,0.,0.05,IsoTrk_EE->GetMaximum());
	

	EE_plots->cd(2);
	TH1D *IsoEcal_EE;
	IsoEcal_EE=(TH1D*)dir->Get("h_IsoEcal_EE");
	IsoEcal_EE->GetYaxis()->SetTitle("Number of Events");
	IsoEcal_EE->SetLineColor(2);
	IsoEcal_EE->Draw();
	BLine(0.05,0.,0.05,IsoEcal_EE->GetMaximum());
	MLine(0.06,0.,0.06,IsoEcal_EE->GetMaximum());
	
	EE_plots->cd(3);
	TH1D *IsoHcal_EE;
	IsoHcal_EE=(TH1D*)dir->Get("h_IsoHcal_EE");
	IsoHcal_EE->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	IsoHcal_EE->SetLineColor(2);
	IsoHcal_EE->Draw();
	BLine(0.03,0.,0.03,IsoHcal_EE->GetMaximum());
	MLine(0.025,0.,0.025,IsoHcal_EE->GetMaximum());
	
	EE_plots->cd(4);
	TH1D *HE_EE;
	HE_EE=(TH1D*)dir->Get("h_HE_EE");
	HE_EE->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	HE_EE->SetLineColor(2);
	HE_EE->Draw();
	BLine(0.15,0.,0.15,IsoHcal_EB->GetMaximum());
	MLine(0.15,0.,0.15,IsoHcal_EB->GetMaximum());
	

	EE_plots->cd(5);
	TH1F *DeltaPhiTkClu_EE;
	DeltaPhiTkClu_EE=(TH1F*)dir->Get("h_DeltaPhiTkClu_EE");
	DeltaPhiTkClu_EE->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	DeltaPhiTkClu_EE->SetLineColor(2);
	DeltaPhiTkClu_EE->Draw();
	BLine(0.03,0.,0.03,DeltaPhiTkClu_EE->GetMaximum());
	MLine(0.7,0.,0.7,DeltaPhiTkClu_EE->GetMaximum());
	
	EE_plots->cd(6);
	TH1F *DeltaEtaTkClu_EE;
	DeltaEtaTkClu_EE=(TH1F*)dir->Get("h_DeltaEtaTkClu_EE");
	DeltaEtaTkClu_EE->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	DeltaEtaTkClu_EE->SetLineColor(2);
	DeltaEtaTkClu_EE->Draw();
	BLine(0.007,0.,0.007,DeltaEtaTkClu_EE->GetMaximum());
	MLine(0.009,0.,0.009,DeltaEtaTkClu_EE->GetMaximum());
	
	EE_plots->cd(7);
	TH1F *sigmaIeIe_EE;
	sigmaIeIe_EE=(TH1F*)dir->Get("h_sigmaIeIe_EE");
	sigmaIeIe_EE->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	sigmaIeIe_EE->SetLineColor(2);
	sigmaIeIe_EE->Draw();
	BLine(0.03,0.,0.03,sigmaIeIe_EE->GetMaximum());
	MLine(0.03,0.,0.03,sigmaIeIe_EE->GetMaximum());
	
//	EE_plots->cd(8);
//	TH1F *HE_EE;
//	HE_EE=(TH1F*)dir->Get("h_HE_EE");
//	HE_EE->GetYaxis()->SetTitle("Number of Events");
//	gPad->SetLogy(1);
//	HE_EE->Draw();


	//Common
	Common = new TCanvas("Common","Common",400,20,1200,800);
	Common->Divide(2,2);
	
	Common->cd(1);
	TH1D *fbrem;
	fbrem=(TH1D*)dir->Get("h_fbrem");
	fbrem->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	fbrem->SetLineColor(2);
	fbrem->Draw();
	MLine(0.15,0.,0.15,fbrem->GetMaximum());

	Common->cd(2);
	TH1D *etaSC;
	etaSC=(TH1D*)dir->Get("h_etaSC");
	etaSC->GetYaxis()->SetTitle("Number of Events");
	etaSC->SetLineColor(2);
	etaSC->Draw();
	MLine(1.,0.,1.,etaSC->GetMaximum());
	MLine(-1.,0.,-1.,etaSC->GetMaximum());

	Common->cd(3);
	TH1F *Dcot;
	Dcot=(TH1F*)dir->Get("h_Dcot");
	Dcot->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	Dcot->SetLineColor(2);
	Dcot->Draw();
	MLine(0.02,0.,0.02,Dcot->GetMaximum());
	MLine(-0.02,0.,-0.02,Dcot->GetMaximum());

	Common->cd(4);
	TH1F *Dist;
	Dist=(TH1F*)dir->Get("h_Dist");
	Dist->GetYaxis()->SetTitle("Number of Events");
	gPad->SetLogy(1);
	Dist->SetLineColor(2);
	Dist->Draw();
	MLine(0.02,0.,0.02,Dist->GetMaximum());
	MLine(-0.02,0.,-0.02,Dist->GetMaximum());


/*
	//Other
	Other = new TCanvas("Other","Other",400,20,1200,800);
	Other->Divide(1,2);

	Other->cd(1);
	TH1F *Num;
	Num=(TH1F*)dir->Get("h_histNum");
	Num->GetYaxis()->SetTitle("Number of Events");
	Num->GetXaxis()->SetTitle("Number of Electrons");
	Num->Draw();

	Other->cd(2);
	TH1C *NOEIH;
	NOEIH=(TH1C*)dir->Get("h_NumberOfExpectedInnerHits");
	NOEIH->GetYaxis()->SetTitle("Number of Events");
	NOEIH->SetLineColor(2);
	NOEIH->Draw();
*/

}
