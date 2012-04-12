/**********************************
 * Berends-Giele Scaling          *
 *                                *
 * Vieri Candelise January  2012  *
 **********************************
 *********************************/

#include "Unfolding.h"
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

void DotheScaling(){

using
std::cout;
using
std::endl;

gROOT->SetStyle("Plain");
//gROOT->ForceStyle();
//gROOT->LoadMacro("tdrStyle.C++");
//tdrStyle();

 const int maxNJets=7; 

TH1D *h2 = new TH1D ("N", "N", maxNJets, 0.5, maxNJets+0.5);
TH1D *h3 = new TH1D ("N", "N", maxNJets, 0.5, maxNJets+0.5);


TFile *eff = TFile::Open("/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_17pf.root");

TH1F *h1 = (TH1F*)gDirectory->Get("JetMultiplicityUnfolded");

int counter = 0;
const int loop = maxNJets-1;
double content[loop];
double content2[loop];
double content3[loop];

for(int u=1; u<loop; u++){
	content3[u] = JetMultiplicityUnfolded->GetBinContent(u);
}



for(int i=1; i<=loop; i++){
	for (unsigned int j=counter;j<=loop;j++){
	if (j != counter) content[i-1]  += JetMultiplicityUnfolded->GetBinContent(j);
	content2[i-1] += JetMultiplicityUnfolded->GetBinContent(j);
	}	
	counter++;
}	
for(int i=1; i<=loop; i++){
	
	double err1 = JetMultiplicityUnfolded->GetBinError(i);
	double err2 = JetMultiplicityUnfolded->GetBinError(i-1);
	double z = content[i-1]/content2[i-1];
	double err= sqrt(-(content[i]*content[i])*err2*err2*(1/(content2[i]*content2[i]*content2[i]*content2[i]))+ (1/(content2[i]*content2[i]))*err1*err1);
	h2->SetBinContent(i, z);
	h2->SetBinError(i, err);
}

	TCanvas * Canv = new TCanvas("Canv","Canv",0,0,800,600);
	Canv->cd();
	h2->GetYaxis()->SetRangeUser(0., 0.4);
	h2->SetMarkerStyle(20);
	h2->SetMarkerColor(kRed);
	h2->GetXaxis()->SetTitle("N_{Jets}");
	h2->GetYaxis()->SetTitle("#sigma(Z + #geq N_{Jets}) / #sigma(Z + #geq (N-1)_{Jets})");
	h2->GetYaxis()->SetTitleSize(0.03);
	h2->GetYaxis()->SetTitleOffset(1.53);

	h2->Draw("E1");

	TLegend* lumi = new TLegend(0.067,0.659,0.448,0.858);
	lumi->SetFillColor(0);
	lumi->SetFillStyle(0);
	lumi->SetBorderSize(0);
	lumi->SetTextAlign(12);
	lumi->SetTextSize(0.0244);
	lumi->SetTextFont(42);
	lumi->AddEntry((TObject*)0,"#int L dt = 4.907 fb^{-1}","");
	lumi->AddEntry((TObject*)1,"anti-k_{T} jets R=0.5","");
	lumi->AddEntry((TObject*)2,"p^{jet}_{T} #geq 30 GeV/c","");

        lumi->Draw();
	Canv->Update();



}
