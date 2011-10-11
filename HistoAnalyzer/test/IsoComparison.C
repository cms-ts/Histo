#include "TFile.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include <vector>
#include <TString.h>
#include <TCanvas.h>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++  Macro che confronta l'isolamento ECAL e HCAL per tre diversi file: g93 / g94 / patch2
//+++++  I file vengono presi in input da harryplotter

//++++   Vieri
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void harryplotter(TString data_file_name1, TString data_file_name2, TString data_file_name3){

	TFile* input_file_data1 = new TFile(data_file_name1.Data());
	TFile* input_file_data2 = new TFile(data_file_name2.Data());
	TFile* input_file_data3 = new TFile(data_file_name3.Data());

			TH1D* h_IsoEcal_EB1 = (TH1D*)input_file_data1->Get("demo/h_IsoEcal_EB");
			TH1D* h_IsoEcal_EB2 = (TH1D*)input_file_data2->Get("demo/h_IsoEcal_EB");
			TH1D* h_IsoEcal_EB3 = (TH1D*)input_file_data3->Get("demo/h_IsoEcal_EB");

			TH1D* h_IsoHcal_EB1 = (TH1D*)input_file_data1->Get("demo/h_IsoHcal_EB");
			TH1D* h_IsoHcal_EB2 = (TH1D*)input_file_data2->Get("demo/h_IsoHcal_EB");
			TH1D* h_IsoHcal_EB3 = (TH1D*)input_file_data3->Get("demo/h_IsoHcal_EB");
			 
			TCanvas* canvas = new TCanvas("Isolation Comparison","Isolation Comparison",1000,700);
			canvas->Divide(1,2);
			
			canvas->cd(1);
			h_IsoEcal_EB1->SetLineColor(kBlack);
			h_IsoEcal_EB2->SetLineColor(kRed);
			h_IsoEcal_EB3->SetLineColor(kGreen);
			h_IsoEcal_EB1->GetXaxis()->SetTitle("IsoEcal Barrel");
			h_IsoEcal_EB1->GetYaxis()->SetTitle("Events");
			h_IsoEcal_EB1->GetYaxis()->SetTitle("Events");
			h_IsoEcal_EB1->SetAxisRange(0, 0.075);
			h_IsoEcal_EB2->SetAxisRange(0, 0.075);
			h_IsoEcal_EB3->SetAxisRange(0, 0.075);
			h_IsoEcal_EB1->SetBins(28, 0, 0.075);
			h_IsoEcal_EB2->SetBins(28, 0, 0.075);
			h_IsoEcal_EB3->SetBins(28, 0, 0.075);
			h_IsoEcal_EB1->Draw();
			h_IsoEcal_EB2->Draw("SAME");
			h_IsoEcal_EB3->Draw("SAME");

			TLegend* legend_d = new TLegend(0.626506,0.19494,0.916667,0.447917);
			legend_d->SetFillColor(0);
			legend_d->SetFillStyle(0);
			legend_d->SetBorderSize(0);
			legend_d->AddEntry(h_IsoEcal_EB1,"g93","LE");
			legend_d->AddEntry(h_IsoEcal_EB2,"g94","LE");
			legend_d->AddEntry(h_IsoEcal_EB3,"patch2","LE");
			legend_d->Draw("same");
			canvas->Update();

			canvas->cd(2);
			h_IsoHcal_EB1->SetLineColor(kBlack);
			h_IsoHcal_EB2->SetLineColor(kRed);
			h_IsoHcal_EB3->SetLineColor(kGreen);
			h_IsoHcal_EB1->GetXaxis()->SetTitle("IsoEcal Barrel");
			h_IsoHcal_EB1->GetYaxis()->SetTitle("Events");
			h_IsoHcal_EB1->GetYaxis()->SetTitle("Events");
			h_IsoHcal_EB1->SetAxisRange(0, 0.1);
			h_IsoHcal_EB2->SetAxisRange(0, 0.1);
			h_IsoHcal_EB3->SetAxisRange(0, 0.1);
			h_IsoHcal_EB1->SetBins(100, 0, 0.1);
			h_IsoHcal_EB2->SetBins(100, 0, 0.1);
			h_IsoHcal_EB3->SetBins(100, 0, 0.1);
			h_IsoHcal_EB1->Draw();
			h_IsoHcal_EB2->Draw("SAME");
			h_IsoHcal_EB3->Draw("SAME");

			TLegend* legend_s = new TLegend(0.626506,0.19494,0.916667,0.447917);
			legend_s->SetFillColor(0);
			legend_s->SetFillStyle(0);
			legend_s->SetBorderSize(0);
			legend_s->AddEntry(h_IsoEcal_EB1,"g93","LE");
			legend_s->AddEntry(h_IsoEcal_EB2,"g94","LE");
			legend_s->AddEntry(h_IsoEcal_EB3,"patch2","LE");
			legend_s->Draw("same");
			canvas->Update();

				
}
