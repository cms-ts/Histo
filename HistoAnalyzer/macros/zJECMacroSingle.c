#include <iostream>
#include <iomanip>
#include <cmath>
#include "TF1.h"
#include "TCanvas.h"
#include <TFile.h>
#include <TH1.h>
#include <TStyle.h>

#include "functions.h"

using std::cout;
using std::endl;

double myfunc (double *x, double *par) {
	return ( x[0]*par[0] +par[1]);
}


void zJECMacroSingle() {

	gROOT->Reset();
	//gStyle->SetOptStat(10);
	//gStyle->SetOptFit(1111);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetFrameFillColor(10);
	gStyle->SetPadColor(10);
	gStyle->SetCanvasColor(10);
	gStyle->SetTitleColor(1);
	gStyle->SetStatColor(10);
	gStyle->SetFillColor(10);
	gStyle->SetAxisColor(1);
	gStyle->SetLabelColor(1);
   
	TH1F * h_jetPtVtxEB[11];
	TH1F * h_jetPtVtxEE[11];
	TH1F * h_jetPtVtxL1EB[11];
	TH1F * h_jetPtVtxL1EE[11];
	TH1F * h_jetPtVtxJECEB[11];
	TH1F * h_jetPtVtxJECEE[11];
//_______aprire un file root_________________________________
	
	//char namefile[50]="totcrab_jetValidation1003singleCorrections.root";
	char namefile[100]="/gpfs/cms/users/montanin/basta_CMSSW_4_2_4/tot_jetValidation1201SingleCorrections.root";
	TFile *fdata = TFile::Open(namefile);
	

	string name;

	for(int i=1;i<=11; i++)
	{
	   stringstream buffer_Bin;
	   buffer_Bin << i;
	   name="validation/h_jetPtVtx";
	   name += buffer_Bin.str();
	   name+="_EB";
	   int j=i-1;
	   h_jetPtVtxEB[j] = (TH1F*)fdata->Get(name.c_str()); 
	   
	   name="validation/h_jetPtVtx";
	   name += buffer_Bin.str();
	   name+="_EE";
	   h_jetPtVtxEE[j] = (TH1F*)fdata->Get(name.c_str());
	   
	   name="validationJEC/h_jetPtVtx";
	   name += buffer_Bin.str();
	   name+="_EB";
	   h_jetPtVtxJECEB[j] = (TH1F*)fdata->Get(name.c_str()); 
	   
	   name="validationJEC/h_jetPtVtx";
	   name += buffer_Bin.str();
	   name+="_EE";
	   h_jetPtVtxJECEE[j] = (TH1F*)fdata->Get(name.c_str()); 
	   
	   name="validationL1/h_jetPtVtx";
	   name += buffer_Bin.str();
	   name+="_EB";
	   h_jetPtVtxL1EB[j] = (TH1F*)fdata->Get(name.c_str()); 
	   
	   name="validationL1/h_jetPtVtx";
	   name += buffer_Bin.str();
	   name+="_EE";
	   h_jetPtVtxL1EE[j] = (TH1F*)fdata->Get(name.c_str()); 
	}

	//  jet distributions without corrections
	string dir;
	dir = "validation/";
	TH1F * h_jetNum_EB = (TH1F*)fdata->Get((dir+"h_jetNum_EB").c_str());
	TH1F * h_jetPt_EB = (TH1F*)fdata->Get((dir+"h_jetPt_EB").c_str());  
	TH1F * h_jetPtVtx1_EB = (TH1F*)fdata->Get((dir+"h_jetPtVtx1_EB").c_str());  
	TH1F * h_jetPtFirstCk_EB = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EB").c_str());  
	TH1F * h_jetPtSecondCk_EB = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EB").c_str()); 

	TH1F * h_jetNum_EE = (TH1F*)fdata->Get((dir+"h_jetNum_EE").c_str());
	TH1F * h_jetPt_EE = (TH1F*)fdata->Get((dir+"h_jetPt_EE").c_str()); 
	TH1F * h_jetPtFirstCk_EE = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EE").c_str());  
	TH1F * h_jetPtSecondCk_EE = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EE").c_str());  

	TH1F * h_jetEta = (TH1F*)fdata->Get((dir+"h_jetEta_EE").c_str()); 
	TH1F * h_zYieldVsJets = (TH1F*)fdata->Get((dir+"h_zYieldVsjets").c_str()); 
	TH1F * h_zYieldVsJetsVtx1 = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx1").c_str()); 
	TH1F * h_zYieldVsJetsVtx5 = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx5").c_str()); 
	TH1F * h_nVtx = (TH1F*)fdata->Get((dir+"h_nVtx").c_str());
	TH1F * h_invMass = (TH1F*)fdata->Get((dir+"h_invMass").c_str());

	//  jet distributions with corrections
	dir = "validationJEC/";
	TH1F * h_jetNumJEC_EB = (TH1F*)fdata->Get((dir+"h_jetNum_EB").c_str());
	TH1F * h_jetPtJEC_EB = (TH1F*)fdata->Get((dir+"h_jetPt_EB").c_str()); 
	TH1F * h_jetPtVtx1JEC_EB = (TH1F*)fdata->Get((dir+"h_jetPtVtx1_EB").c_str());  
	TH1F * h_jetPtFirstCkJEC_EB = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EB").c_str());  
	TH1F * h_jetPtSecondCkJEC_EB = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EB").c_str()); 

	TH1F * h_jetNumJEC_EE = (TH1F*)fdata->Get((dir+"h_jetNum_EE").c_str());
	TH1F * h_jetPtJEC_EE = (TH1F*)fdata->Get((dir+"h_jetPt_EE").c_str());  
	TH1F * h_jetPtFirstCkJEC_EE = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EE").c_str());  
	TH1F * h_jetPtSecondCkJEC_EE = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EE").c_str());

	TH1F * h_jetEtaJEC = (TH1F*)fdata->Get((dir+"h_jetEta_EE").c_str());
	TH1F * h_zYieldVsJetsJEC = (TH1F*)fdata->Get((dir+"h_zYieldVsjets").c_str()); 
	TH1F * h_zYieldVsJetsVtx1JEC = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx1").c_str()); 
	TH1F * h_zYieldVsJetsVtx5JEC = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx5").c_str()); 
	TH1F * h_nVtxJEC = (TH1F*)fdata->Get((dir+"h_nVtx").c_str()); 
	TH1F * h_invMassJEC = (TH1F*)fdata->Get((dir+"h_invMass").c_str()); 

	//  jet distributions with L1 corrections
	dir = "validationL1/";
	TH1F * h_jetNumL1_EB = (TH1F*)fdata->Get((dir+"h_jetNum_EB").c_str());
	TH1F * h_jetPtL1_EB = (TH1F*)fdata->Get((dir+"h_jetPt_EB").c_str()); 
	TH1F * h_jetPtVtx1L1_EB = (TH1F*)fdata->Get((dir+"h_jetPtVtx1_EB").c_str());  
	TH1F * h_jetPtFirstCkL1_EB = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EB").c_str());  
	TH1F * h_jetPtSecondCkL1_EB = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EB").c_str()); 

	TH1F * h_jetNumL1_EE = (TH1F*)fdata->Get((dir+"h_jetNum_EE").c_str());
	TH1F * h_jetPtL1_EE = (TH1F*)fdata->Get((dir+"h_jetPt_EE").c_str());  
	TH1F * h_jetPtFirstCkL1_EE = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EE").c_str());  
	TH1F * h_jetPtSecondCkL1_EE = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EE").c_str());

	TH1F * h_jetEtaL1 = (TH1F*)fdata->Get((dir+"h_jetEta_EE").c_str());
	TH1F * h_zYieldVsJetsL1 = (TH1F*)fdata->Get((dir+"h_zYieldVsjets").c_str()); 
	TH1F * h_zYieldVsJetsVtx1L1 = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx1").c_str()); 
	TH1F * h_zYieldVsJetsVtx5L1 = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx5").c_str()); 
	TH1F * h_nVtxL1 = (TH1F*)fdata->Get((dir+"h_nVtx").c_str()); 
	TH1F * h_invMassL1 = (TH1F*)fdata->Get((dir+"h_invMass").c_str()); 

	//  jet distributions with L2 corrections
	dir = "validationL2/";
	TH1F * h_jetNumL2_EB = (TH1F*)fdata->Get((dir+"h_jetNum_EB").c_str());
	TH1F * h_jetPtL2_EB = (TH1F*)fdata->Get((dir+"h_jetPt_EB").c_str()); 
	TH1F * h_jetPtVtx1L2_EB = (TH1F*)fdata->Get((dir+"h_jetPtVtx1_EB").c_str());  
	TH1F * h_jetPtFirstCkL2_EB = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EB").c_str());  
	TH1F * h_jetPtSecondCkL2_EB = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EB").c_str()); 

	TH1F * h_jetNumL2_EE = (TH1F*)fdata->Get((dir+"h_jetNum_EE").c_str());
	TH1F * h_jetPtL2_EE = (TH1F*)fdata->Get((dir+"h_jetPt_EE").c_str());  
	TH1F * h_jetPtFirstCkL2_EE = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EE").c_str());  
	TH1F * h_jetPtSecondCkL2_EE = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EE").c_str());

	TH1F * h_jetEtaL2 = (TH1F*)fdata->Get((dir+"h_jetEta_EE").c_str());
	TH1F * h_zYieldVsJetsL2 = (TH1F*)fdata->Get((dir+"h_zYieldVsjets").c_str()); 
	TH1F * h_zYieldVsJetsVtx1L2 = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx1").c_str()); 
	TH1F * h_zYieldVsJetsVtx5L2 = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx5").c_str()); 
	TH1F * h_nVtxL2 = (TH1F*)fdata->Get((dir+"h_nVtx").c_str()); 
	TH1F * h_invMassL2 = (TH1F*)fdata->Get((dir+"h_invMass").c_str()); 

	//  jet distributions with L2L3 corrections
	dir = "validationL2L3/";
	TH1F * h_jetNumL2L3_EB = (TH1F*)fdata->Get((dir+"h_jetNum_EB").c_str());
	TH1F * h_jetPtL2L3_EB = (TH1F*)fdata->Get((dir+"h_jetPt_EB").c_str()); 
	TH1F * h_jetPtVtx1L2L3_EB = (TH1F*)fdata->Get((dir+"h_jetPtVtx1_EB").c_str());  
	TH1F * h_jetPtFirstCkL2L3_EB = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EB").c_str());  
	TH1F * h_jetPtSecondCkL2L3_EB = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EB").c_str()); 

	TH1F * h_jetNumL2L3_EE = (TH1F*)fdata->Get((dir+"h_jetNum_EE").c_str());
	TH1F * h_jetPtL2L3_EE = (TH1F*)fdata->Get((dir+"h_jetPt_EE").c_str());  
	TH1F * h_jetPtFirstCkL2L3_EE = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EE").c_str());  
	TH1F * h_jetPtSecondCkL2L3_EE = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EE").c_str());

	TH1F * h_jetEtaL2L3 = (TH1F*)fdata->Get((dir+"h_jetEta_EE").c_str());
	TH1F * h_zYieldVsJetsL2L3 = (TH1F*)fdata->Get((dir+"h_zYieldVsjets").c_str()); 
	TH1F * h_zYieldVsJetsVtx1L2L3 = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx1").c_str()); 
	TH1F * h_zYieldVsJetsVtx5L2L3 = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx5").c_str()); 
	TH1F * h_nVtxL2L3 = (TH1F*)fdata->Get((dir+"h_nVtx").c_str()); 
	TH1F * h_invMassL2L3 = (TH1F*)fdata->Get((dir+"h_invMass").c_str());

	//  jet distributions with L2L3Residual corrections
	dir = "validationL2L3Residual/";
	TH1F * h_jetNumL2L3Residual_EB = (TH1F*)fdata->Get((dir+"h_jetNum_EB").c_str());
	TH1F * h_jetPtL2L3Residual_EB = (TH1F*)fdata->Get((dir+"h_jetPt_EB").c_str()); 
	TH1F * h_jetPtVtx1L2L3Residual_EB = (TH1F*)fdata->Get((dir+"h_jetPtVtx1_EB").c_str());  
	TH1F * h_jetPtFirstCkL2L3Residual_EB = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EB").c_str());  
	TH1F * h_jetPtSecondCkL2L3Residual_EB = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EB").c_str()); 

	TH1F * h_jetNumL2L3Residual_EE = (TH1F*)fdata->Get((dir+"h_jetNum_EE").c_str());
	TH1F * h_jetPtL2L3Residual_EE = (TH1F*)fdata->Get((dir+"h_jetPt_EE").c_str());  
	TH1F * h_jetPtFirstCkL2L3Residual_EE = (TH1F*)fdata->Get((dir+"h_jetPtFirstCk_EE").c_str());  
	TH1F * h_jetPtSecondCkL2L3Residual_EE = (TH1F*)fdata->Get((dir+"h_jetPtSecondCk_EE").c_str());

	TH1F * h_jetEtaL2L3Residual = (TH1F*)fdata->Get((dir+"h_jetEta_EE").c_str());
	TH1F * h_zYieldVsJetsL2L3Residual = (TH1F*)fdata->Get((dir+"h_zYieldVsjets").c_str()); 
	TH1F * h_zYieldVsJetsVtx1L2L3Residual = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx1").c_str()); 
	TH1F * h_zYieldVsJetsVtx5L2L3Residual = (TH1F*)fdata->Get((dir+"h_zYieldVsjetsVtx5").c_str()); 
	TH1F * h_nVtxL2L3Residual = (TH1F*)fdata->Get((dir+"h_nVtx").c_str()); 
	TH1F * h_invMassL2L3Residual = (TH1F*)fdata->Get((dir+"h_invMass").c_str());
	

// ======================================================================================================
	TH1F * h_jetPtVsVtx_EB = new TH1F("h_jetPtVsVtx_EB","jetPtVsVtx",12,0,12);
	TH1F * h_jetPtVsVtx_EE = new TH1F("h_jetPtVsVtx_EE","jetPtVsVtx",12,0,12);
	TH1F * h_jetPtVsVtxL1_EB = new TH1F("h_jetPtVsVtxL1_EB","jetPtVsVtxL1",12,0,12);
	TH1F * h_jetPtVsVtxL1_EE = new TH1F("h_jetPtVsVtxL1_EE","jetPtVsVtxL1",12,0,12);
	TH1F * h_jetPtVsVtxJEC_EB = new TH1F("h_jetPtVsVtxJEC_EB","jetPtVsVtxJEC",12,0,12);
	TH1F * h_jetPtVsVtxJEC_EE = new TH1F("h_jetPtVsVtxJEC_EE","jetPtVsVtxJEC",12,0,12);

	for(int i=0;i<10; i++){

	   h_jetPtVsVtx_EB->SetBinContent(i+1,h_jetPtVtxEB[i]->GetMean());
	   h_jetPtVsVtxL1_EB->SetBinContent(i+1,h_jetPtVtxL1EB[i]->GetMean());
	   h_jetPtVsVtxJEC_EB->SetBinContent(i+1,h_jetPtVtxJECEB[i]->GetMean());

	   h_jetPtVsVtx_EE->SetBinContent(i+1,h_jetPtVtxEE[i]->GetMean());
	   h_jetPtVsVtxL1_EE->SetBinContent(i+1,h_jetPtVtxL1EE[i]->GetMean());
	   h_jetPtVsVtxJEC_EE->SetBinContent(i+1,h_jetPtVtxJECEE[i]->GetMean());
	}

	TCanvas *c_jetPtVsVtx_EB = new TCanvas("c_jetPtVsVtx_EB","jetPtVsVtx_EB", 600, 600);
	c_jetPtVsVtx_EB->SetGrid();
	//h_jetPtVsVtx_EB->GetXaxis()->SetRangeUser(0,7);
	h_jetPtVsVtx_EB->SetXTitle("N_{vtx}");
	h_jetPtVsVtx_EB->SetYTitle("<p_{T}>");
	//h_jetPtVsVtx_EB->SetMinimum(0.1);
	//h_jetPtVsVtx_EB->SetMaximum(10000);
	h_jetPtVsVtx_EB->SetStats(0);
	setDraw(h_jetPtVsVtx_EB,h_jetPtVsVtxL1_EB,h_jetPtVsVtxJEC_EB);
	h_jetPtVsVtx_EB->Draw("E");
	h_jetPtVsVtxL1_EB->Draw("E same");
	h_jetPtVsVtxJEC_EB->Draw("E same");

	TLegend* legV = new TLegend(0.905,0.1,1.00,0.9);
	legV->SetTextSize(0.02);
	legV->SetFillColor(0);
	//legV->SetLineColor(0);
	legV->SetBorderSize(0.);
	legV->AddEntry(h_jetPtVsVtx_EB, "wo JEC","p");
	legV->AddEntry(h_jetPtVsVtxL1_EB, "L1","p");
	legV->AddEntry(h_jetPtVsVtxJEC_EB, "L1L2L3Residual","p");
	legV->Draw();

	TCanvas *c_jetPtVsVtx_EE = new TCanvas("c_jetPtVsVtx_EE","jetPtVsVtx_EE", 600, 600);
	c_jetPtVsVtx_EE->SetGrid();
	//h_jetPtVsVtx_EE->GetXaxis()->SetRangeUser(0,7);
	h_jetPtVsVtx_EE->SetXTitle("N_{vtx}");
	h_jetPtVsVtx_EE->SetYTitle("<p_{T}>");
	//h_jetPtVsVtx_EE->SetMinimum(0.1);
	//h_jetPtVsVtx_EE->SetMaximum(10000);
	h_jetPtVsVtx_EE->SetStats(0);
	setDraw(h_jetPtVsVtx_EE,h_jetPtVsVtxL1_EE,h_jetPtVsVtxJEC_EE);
	h_jetPtVsVtx_EE->Draw("E");
	h_jetPtVsVtxL1_EE->Draw("E same");
	h_jetPtVsVtxJEC_EE->Draw("E same");
	legV->Draw();


	TCanvas *c_jetNum_EB = new TCanvas("c_jetNum_EB","jetNum_EB", 600, 600);
	c_jetNum_EB->SetGrid();
	h_jetNum_EB->GetXaxis()->SetRangeUser(0,7);
	h_jetNum_EB->SetXTitle("N_{jets}");
	h_jetNum_EB->SetYTitle("N_{events}");
	h_jetNum_EB->SetMinimum(0.1);
	gPad->SetLogy();
	//h_jetNum_EB->SetMaximum(10000);
	h_jetNum_EB->SetStats(0);

	setDraw(h_jetNum_EB,h_jetNumL1_EB,h_jetNumL2_EB,h_jetNumL2L3_EB,h_jetNumL2L3Residual_EB,h_jetNumJEC_EB);

	h_jetNum_EB->Draw("E");
	h_jetNumL1_EB->Draw("E same");
	h_jetNumL2_EB->Draw("E same");
	h_jetNumL2L3_EB->Draw("E same");
	h_jetNumL2L3Residual_EB->Draw("E same");
	h_jetNumJEC_EB->Draw("E same");

	TLegend* leg = new TLegend(0.905,0.1,1.00,0.9);
	leg->SetTextSize(0.02);
	leg->SetFillColor(0);
	//leg->SetLineColor(0);
	leg->SetBorderSize(0.);
	leg->AddEntry(h_jetNum_EB, "wo JEC","p");
	leg->AddEntry(h_jetNumL1_EB, "L1","p");
	leg->AddEntry(h_jetNumL2_EB, "L2","p");
	leg->AddEntry(h_jetNumL2L3_EB, "L2L3","p");
	leg->AddEntry(h_jetNumL2L3Residual_EB, "L2L3Residual","p");
	leg->AddEntry(h_jetNumJEC_EB, "L1L2L3Residual","p");
	leg->Draw();

	double ent = h_invMass->GetEntries();
	double entJEC = h_invMassJEC->GetEntries();
	double entVtx1 = h_nVtx->GetBinContent(2);
	double entVtx1JEC = h_nVtxJEC->GetBinContent(2);

/* 	h_jetPt_EB->Sumw2(); */
/* 	h_jetPt_EB->Scale(1./ent); */
/* 	h_jetPtJEC_EB->Sumw2(); */
/* 	h_jetPtJEC_EB->Scale(1./entJEC); */
/* 	h_jetPtVtx1_EB->Sumw2(); */
/* 	h_jetPtVtx1_EB->Scale(1./entVtx1); */
/* 	h_jetPtVtx1JEC_EB->Sumw2(); */
/* 	h_jetPtVtx1JEC_EB->Scale(1./entVtx1JEC); */

	TCanvas *c_jetPt_EB = new TCanvas("c_jetPt_EB","jetPt_EB", 600, 600);
	c_jetPt_EB->SetGrid();
	h_jetPt_EB->GetXaxis()->SetRangeUser(0,150);
	h_jetPt_EB->SetXTitle("p_{T}^{jet}");
	h_jetPt_EB->SetYTitle("N_{jets}");
	h_jetPt_EB->SetMinimum(1);
	gPad->SetLogy();
	//h_jetPt_EB->SetMaximum(10000);
	h_jetPt_EB->SetStats(0);

	setDraw(h_jetPt_EB,h_jetPtL1_EB,h_jetPtL2_EB,h_jetPtL2L3_EB,h_jetPtL2L3Residual_EB,h_jetPtJEC_EB);

	h_jetPt_EB->Draw("E");
	h_jetPtL1_EB->Draw("E same");
	h_jetPtL2_EB->Draw("E same");
	h_jetPtL2L3_EB->Draw("E same");
	h_jetPtL2L3Residual_EB->Draw("E same");
	h_jetPtJEC_EB->Draw("E same");
	leg->Draw();

	TCanvas *c_jetPtFirstCk_EB = new TCanvas("c_jetPtFirstCk_EB","jetPtFirstCk_EB", 600, 600);
	c_jetPtFirstCk_EB->SetGrid();
	h_jetPtFirstCk_EB->GetXaxis()->SetRangeUser(0,150);
	h_jetPtFirstCk_EB->SetXTitle("N_{jets}");
	h_jetPtFirstCk_EB->SetYTitle("N_{events}");
	h_jetPtFirstCk_EB->SetMinimum(1);
	gPad->SetLogy();
	//h_jetPtFirstCk_EB->SetMaximum(10000);
	h_jetPtFirstCk_EB->SetStats(0);

	setDraw(h_jetPtFirstCk_EB,h_jetPtFirstCkL1_EB,h_jetPtFirstCkL2_EB,h_jetPtFirstCkL2L3_EB,h_jetPtFirstCkL2L3Residual_EB,h_jetPtFirstCkJEC_EB);

	h_jetPtFirstCk_EB->Draw("E");
	h_jetPtFirstCkL1_EB->Draw("E same");
	h_jetPtFirstCkL2_EB->Draw("E same");
	h_jetPtFirstCkL2L3_EB->Draw("E same");
	h_jetPtFirstCkL2L3Residual_EB->Draw("E same");
	h_jetPtFirstCkJEC_EB->Draw("E same");	
	leg->Draw();

	TCanvas *c_jetPtSecondCk_EB = new TCanvas("c_jetPtSecondCk_EB","jetPtSecondCk_EB", 600, 600);
	c_jetPtSecondCk_EB->SetGrid();
	h_jetPtSecondCk_EB->GetXaxis()->SetRangeUser(0,150);
	h_jetPtSecondCk_EB->SetXTitle("N_{jets}");
	h_jetPtSecondCk_EB->SetYTitle("N_{events}");
	h_jetPtSecondCk_EB->SetMinimum(1);
	gPad->SetLogy();
	//h_jetPtSecondCk_EB->SetMaximum(10000);
	h_jetPtSecondCk_EB->SetStats(0);

	setDraw(h_jetPtSecondCk_EB,h_jetPtSecondCkL1_EB,h_jetPtSecondCkL2_EB,h_jetPtSecondCkL2L3_EB,h_jetPtSecondCkL2L3Residual_EB,h_jetPtSecondCkJEC_EB);

	h_jetPtSecondCk_EB->Draw("E");
	h_jetPtSecondCkL1_EB->Draw("E same");
	h_jetPtSecondCkL2_EB->Draw("E same");
	h_jetPtSecondCkL2L3_EB->Draw("E same");
	h_jetPtSecondCkL2L3Residual_EB->Draw("E same");
	h_jetPtSecondCkJEC_EB->Draw("E same");	
	leg->Draw();



	TCanvas *c_jetNum_EE = new TCanvas("c_jetNum_EE","jetNum_EE", 600, 600);
	c_jetNum_EE->SetGrid();
	h_jetNum_EE->GetXaxis()->SetRangeUser(0,7);
	h_jetNum_EE->SetXTitle("N_{jets}");
	h_jetNum_EE->SetYTitle("N_{events}");
	h_jetNum_EE->SetMinimum(1);
	gPad->SetLogy();
	//h_jetNum_EE->SetMaximum(100000);
	h_jetNum_EE->SetStats(0);

	setDraw(h_jetNum_EE,h_jetNumL1_EE,h_jetNumL2_EE,h_jetNumL2L3_EE,h_jetNumL2L3Residual_EE,h_jetNumJEC_EE);

	h_jetNum_EE->Draw("E");
	h_jetNumL1_EE->Draw("E same");
	h_jetNumL2_EE->Draw("E same");
	h_jetNumL2L3_EE->Draw("E same");
	h_jetNumL2L3Residual_EE->Draw("E same");	
	h_jetNumJEC_EE->Draw("E same");	
	leg->Draw();

	TCanvas *c_jetPt_EE = new TCanvas("c_jetPt_EE","jetPt_EE", 600, 600);
	c_jetPt_EE->SetGrid();
	h_jetPt_EE->GetXaxis()->SetRangeUser(0,150);
	h_jetPt_EE->SetXTitle("N_{jets}");
	h_jetPt_EE->SetYTitle("N_{events}");
	h_jetPt_EE->SetMinimum(1);
	gPad->SetLogy();
	//h_jetPt_EE->SetMaximum(100000);
	h_jetPt_EE->SetStats(0);

	setDraw(h_jetPt_EE,h_jetPtL1_EE,h_jetPtL2_EE,h_jetPtL2L3_EE,h_jetPtL2L3Residual_EE,h_jetPtJEC_EE);

	h_jetPt_EE->Draw("E");
	h_jetPtL1_EE->Draw("E same");
	h_jetPtL2_EE->Draw("E same");
	h_jetPtL2L3_EE->Draw("E same");
	h_jetPtL2L3Residual_EE->Draw("E same");
	h_jetPtJEC_EE->Draw("E same");	
	leg->Draw();

	TCanvas *c_jetPtFirstCk_EE = new TCanvas("c_jetPtFirstCk_EE","jetPtFirstCk_EE", 600, 600);
	c_jetPtFirstCk_EE->SetGrid();
	h_jetPtFirstCk_EE->GetXaxis()->SetRangeUser(0,150);
	h_jetPtFirstCk_EE->SetXTitle("N_{jets}");
	h_jetPtFirstCk_EE->SetYTitle("N_{events}");
	h_jetPtFirstCk_EE->SetMinimum(1);
	gPad->SetLogy();
	//h_jetPtFirstCk_EE->SetMaximum(10000);
	h_jetPtFirstCk_EE->SetStats(0);

	setDraw(h_jetPtFirstCk_EE,h_jetPtFirstCkL1_EE,h_jetPtFirstCkL2_EE,h_jetPtFirstCkL2L3_EE,h_jetPtFirstCkL2L3Residual_EE,h_jetPtFirstCkJEC_EE);

	h_jetPtFirstCk_EE->Draw("E");
	h_jetPtFirstCkL1_EE->Draw("E same");
	h_jetPtFirstCkL2_EE->Draw("E same");
	h_jetPtFirstCkL2L3_EE->Draw("E same");
	h_jetPtFirstCkL2L3Residual_EE->Draw("E same");
	h_jetPtFirstCkJEC_EE->Draw("E same");	
	leg->Draw();

	TCanvas *c_jetPtSecondCk_EE = new TCanvas("c_jetPtSecondCk_EE","jetPtSecondCk_EE", 600, 600);
	c_jetPtSecondCk_EE->SetGrid();
	h_jetPtSecondCk_EE->GetXaxis()->SetRangeUser(0,150);
	h_jetPtSecondCk_EE->SetXTitle("N_{jets}");
	h_jetPtSecondCk_EE->SetYTitle("N_{events}");
	h_jetPtSecondCk_EE->SetMinimum(1);
	gPad->SetLogy();
	//h_jetPtSecondCk_EE->SetMaximum(10000);
	h_jetPtSecondCk_EE->SetStats(0);

	setDraw(h_jetPtSecondCk_EE,h_jetPtSecondCkL1_EE,h_jetPtSecondCkL2_EE,h_jetPtSecondCkL2L3_EE,h_jetPtSecondCkL2L3Residual_EE,h_jetPtSecondCkJEC_EE);

	h_jetPtSecondCk_EE->Draw("E");
	h_jetPtSecondCkL1_EE->Draw("E same");
	h_jetPtSecondCkL2_EE->Draw("E same");
	h_jetPtSecondCkL2L3_EE->Draw("E same");
	h_jetPtSecondCkL2L3Residual_EE->Draw("E same");
	h_jetPtSecondCkJEC_EE->Draw("E same");	
	leg->Draw();


	TCanvas *c_jetEta = new TCanvas("c_jetEta","jetEta", 600, 600);
	c_jetEta->SetGrid();
	//h_jetEta->GetXaxis()->SetRangeUser(0,150);
	h_jetEta->SetXTitle("N_{jets}");
	h_jetEta->SetYTitle("N_{events}");
	h_jetEta->SetMinimum(1);
	//h_jetEta->SetMaximum(10000);
	h_jetEta->SetStats(0);

	setDraw(h_jetEta,h_jetEtaL1,h_jetEtaL2,h_jetEtaL2L3,h_jetEtaL2L3Residual,h_jetEtaJEC);

	h_jetEta->Draw("E");
	h_jetEtaL1->Draw("E same");
	h_jetEtaL2->Draw("E same");
	h_jetEtaL2L3->Draw("E same");
	h_jetEtaL2L3Residual->Draw("E same");
	h_jetEtaJEC->Draw("E same");	
	leg->Draw();

	double entr = h_invMass->GetEntries();
	double entrJEC = h_invMassJEC->GetEntries();
	double entrVtx1 = h_nVtx->GetBinContent(2);
	double entrVtx1JEC = h_nVtxJEC->GetBinContent(2);
	double entrVtx5 = h_nVtx->GetBinContent(6);
	double entrVtx5JEC = h_nVtxJEC->GetBinContent(6);

	h_zYieldVsJets->Sumw2();
	h_zYieldVsJets->Scale(1./entr);
	h_zYieldVsJetsJEC->Sumw2();
	h_zYieldVsJetsJEC->Scale(1./entrJEC);
	h_zYieldVsJetsVtx1->Sumw2();
	h_zYieldVsJetsVtx1->Scale(1./entrVtx1);
	h_zYieldVsJetsVtx1JEC->Sumw2();
	h_zYieldVsJetsVtx1JEC->Scale(1./entrVtx1JEC);
	h_zYieldVsJetsVtx5->Sumw2();
	h_zYieldVsJetsVtx5->Scale(1./entrVtx5);
	h_zYieldVsJetsVtx5JEC->Sumw2();
	h_zYieldVsJetsVtx5JEC->Scale(1./entrVtx5JEC);

	TCanvas *c_zYieldVsJets = new TCanvas("c_zYieldVsJets","zYieldVsJets", 600, 600);
	c_zYieldVsJets->SetGrid();
	//h_zYieldVsJets->GetXaxis()->SetRangeUser(0,150);
	h_zYieldVsJets->SetXTitle("N_{jets}");
	h_zYieldVsJets->SetYTitle("N_{events}");
	//h_zYieldVsJets->SetMinimum(1);
	//c_zYieldVsJets->SetLogy();
	gPad->SetLogy();
	//h_zYieldVsJets->SetMaximum(10000);
	h_zYieldVsJets->SetStats(0);

	setDraw(h_zYieldVsJets, h_zYieldVsJetsVtx1, h_zYieldVsJetsVtx5, h_zYieldVsJetsJEC, h_zYieldVsJetsVtx1JEC, h_zYieldVsJetsVtx5JEC);

/* 	h_zYieldVsJets->SetLineColor(kRed); */
/* 	h_zYieldVsJetsVtx1->SetLineColor(kGreen+2); */
/* 	h_zYieldVsJetsVtx5->SetLineColor(kAzure+10); */
/* 	h_zYieldVsJetsJEC->SetLineColor(kBlue); */
/* 	h_zYieldVsJetsVtx1JEC->SetLineColor(kMagenta+2); */
/* 	h_zYieldVsJetsVtx5JEC->SetLineColor(kOrange+1); */
	h_zYieldVsJets->Draw();
	h_zYieldVsJetsVtx1->Draw("same");
	h_zYieldVsJetsVtx5->Draw("same");
	h_zYieldVsJetsJEC->Draw("same");
	h_zYieldVsJetsVtx1JEC->Draw("same");
	h_zYieldVsJetsVtx5JEC->Draw("same");

	TLegend* leg3 = new TLegend(0.90,0.1,1.00,0.9);
	leg3->SetTextSize(0.02);
	leg3->SetFillColor(0);
	//leg3->SetLineColor(0);
	leg3->SetBorderSize(0.);
	leg3->AddEntry(h_zYieldVsJets, "wo JEC","l");
	leg3->AddEntry(h_zYieldVsJetsVtx1, "wo JEC Vtx1","l");
	leg3->AddEntry(h_zYieldVsJetsVtx5, "wo JEC Vtx5","l");
	leg3->AddEntry(h_zYieldVsJetsJEC, "with JEC","l");
	leg3->AddEntry(h_zYieldVsJetsVtx1JEC, "with JEC Vtx1","l");
	leg3->AddEntry(h_zYieldVsJetsVtx5JEC, "with JEC Vtx5","l");	
	leg3->Draw();


	double entrL1 = h_invMassL1->GetEntries();
	double entrVtx1L1 = h_nVtxL1->GetBinContent(2);
	double entrVtx5L1 = h_nVtxL1->GetBinContent(6);

	h_zYieldVsJetsL1->Sumw2();
	h_zYieldVsJetsL1->Scale(1./entrL1);
	h_zYieldVsJetsVtx1L1->Sumw2();
	h_zYieldVsJetsVtx1L1->Scale(1./entrVtx1L1);
	h_zYieldVsJetsVtx5L1->Sumw2();
	h_zYieldVsJetsVtx5L1->Scale(1./entrVtx5L1);

	TCanvas *c_zYieldVsJets2 = new TCanvas("c_zYieldVsJets2","zYieldVsJets2", 600, 600);
	c_zYieldVsJets2->SetGrid();
	//h_zYieldVsJets->GetXaxis()->SetRangeUser(0,150);
	//h_zYieldVsJets->SetXTitle("N_{jets}");
	//h_zYieldVsJets->SetYTitle("N_{events}");
	//h_zYieldVsJets->SetMinimum(1);
	//c_zYieldVsJets->SetLogy();
	gPad->SetLogy();
	//h_zYieldVsJets->SetMaximum(10000);
	h_zYieldVsJets->SetStats(0);

	setDraw(h_zYieldVsJets, h_zYieldVsJetsVtx1, h_zYieldVsJetsVtx5, h_zYieldVsJetsL1, h_zYieldVsJetsVtx1L1, h_zYieldVsJetsVtx5L1);

	h_zYieldVsJets->Draw();
	h_zYieldVsJetsVtx1->Draw("same");
	h_zYieldVsJetsVtx5->Draw("same");
	h_zYieldVsJetsL1->Draw("same");
	h_zYieldVsJetsVtx1L1->Draw("same");
	h_zYieldVsJetsVtx5L1->Draw("same");

	TLegend* leg4 = new TLegend(0.90,0.1,1.00,0.9);
	leg4->SetTextSize(0.02);
	leg4->SetFillColor(0);
	//leg4->SetLineColor(0);
	leg4->SetBorderSize(0.);
	leg4->AddEntry(h_zYieldVsJets, "wo JEC","l");
	leg4->AddEntry(h_zYieldVsJetsVtx1, "wo JEC Vtx1","l");
	leg4->AddEntry(h_zYieldVsJetsVtx5, "wo JEC Vtx5","l");
	leg4->AddEntry(h_zYieldVsJetsJEC, "with L1","l");
	leg4->AddEntry(h_zYieldVsJetsVtx1JEC, "with L1 Vtx1","l");
	leg4->AddEntry(h_zYieldVsJetsVtx5JEC, "with L1 Vtx5","l");	
	leg4->Draw();


/* //_______fittare una funzione_________________________________ */

/* 	TH1F *h1 = new TH1F("h1","titolo",10,0,10); */

/* 	TF1 *f1 = new TF1("f1","myfunc",0,1,2);  // range e numero parametri se ci sono */

/* 	// setta i parametri */

/* 	h1->Fit("f1","R"); */

	return;
	
}

