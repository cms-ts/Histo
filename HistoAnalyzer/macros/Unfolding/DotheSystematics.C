#include <TH2.h>
#include "TF1.h"
#include <TStyle.h>
#include <TCanvas.h>
#include "TRandom.h"
#include "TH1D.h"
#include "TFile.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include "TLatex.h"
#include <vector>
#include <iostream>
#include "tdrStyle.C"


void DotheSystematics(){
	
	using	std::cout;
	using	std::endl;
	
	Double_t systerr;


        //TFile *A = TFile::Open("Unfolding.root");
        //TH1F *h1 = (TH1F*)gDirectory->Get("NReco");

	TFile *f = TFile::Open("/gpfs/cms/data/2011/jet/jetValidation_dataOct03_v1_11.root");
        f->cd("validation/");
	
	TH1F *NoJEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
	
	f->cd("validationJEC/");

	TH1F *JEC = (TH1F*)gDirectory->Get("h_zYieldVsjets");
	TH1F *hnew = (TH1F*)JEC->Clone("hnew");

	for(int i=1; i<=7; i++){
		
		double content = NoJEC->GetBinContent(i);
                double content2 = JEC->GetBinContent(i);
		systerr = (content2 - content)*0.5;
		//cout<<content<<content2<<(systerr/content2)<<endl;
		//cout<<(JEC->GetBinError(i))/content2<<endl;
		hnew->SetBinError(i, systerr);
	        //hnew->SetError(systerr);
		//cout<<(JEC->GetBinError(i))/content2<<endl;
	}
	       TCanvas *d = new TCanvas ("d", "d", 1000, 700);
	       d->cd ();

	       d->SetLogy();
	       JEC->SetLineColor(kBlack);
	       JEC->SetMarkerStyle(20);
	       JEC->SetMarkerColor(kBlack);
               JEC->GetXaxis()->SetTitle("# of Jets");
               JEC->GetYaxis()->SetTitle("Number of Z+jet events");
	       hnew->SetLineColor(kBlack);
               hnew->SetMarkerStyle(20);
	       hnew->SetFillColor(5); 
     	       hnew->SetMarkerColor(kBlack);
		
	       hnew->Draw("e2");
	       JEC->Draw("e1same");
	

               TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
               legend_1->SetFillColor (0);
               legend_1->SetFillStyle (0);
               legend_1->SetBorderSize (0);
               legend_1->SetTextFont(62);
	       legend_1->AddEntry (JEC, "DATA Unfolded", "LP20");
               legend_1->AddEntry (hnew, "JEC systematic uncertanties", "F");
               legend_1->Draw ("same");
}

