#define Zlumi_cxx
#include "Zlumi.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "TMath.h"
#include "tdrStyle.C"

using namespace std;

void Zlumi::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L Zlumi.C
//      Root > Zlumi t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
 
 gROOT->ForceStyle();
        tdrStyle();

  if (fChain == 0) return;

int minRun=0;
int maxRun=0;
int maxLS=0;
bool forminRun=true;


//TH2I * LumiSRun = new TH2I("LumiSRun", "LS vs Run", 3000, 0., 3000., 20000, 160000., 180000.);
//TH1I * test2 = new TH1I("test2","test2", 3000,0, 3000);


Long64_t nentries = fChain->GetEntriesFast();

Long64_t nbytes = 0, nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
	Long64_t ientry = LoadTree(jentry);
	if (ientry < 0) break;
	nb = fChain->GetEntry(jentry);   nbytes += nb;


	if(forminRun && (Run!=0)){minRun=Run; forminRun=false;}
	if((Run!=0) && (Run>maxRun)){maxRun=Run;}
	if((LS!=0) && (LS>maxLS)){maxLS=LS;}
	//printf("run %i ls %i \n",Run,LS);
}
cout << nentries << " nentries \n";

TH2I *LumiSRun = new TH2I("LumiSRun", "LS vs Run", maxLS, 0, maxLS, maxRun-minRun+2, minRun-1, maxRun+1);
TH1I *Runs = new TH1I("Runs","Run", maxRun-minRun+2, minRun-1, maxRun+1);

nbytes = 0; nb = 0;
for (Long64_t jentry=0; jentry<nentries;jentry++) {
	Long64_t ientry = LoadTree(jentry);
	if (ientry < 0) break;
	nb = fChain->GetEntry(jentry);   nbytes += nb;

	LumiSRun->Fill(LS,Run);
	//printf("run %i ls %i \n",Run,LS);
	Runs->Fill(Run);
	//test2->Fill(LS);
}
	printf("minRun %i maxRun %i \n",minRun,maxRun);
LumiSRun->Draw();
Runs->Draw();
//test->Draw();
//test2->Draw();


TH1F *FileRuns = new TH1F("FileRuns","Run from Lumicalc", maxRun-minRun+2, minRun-1, maxRun+1);
TH1D *XsecDistro = new TH1D("XsecDistro","X sec distribution", 60, 0., 0.6);
//-------------
   const Int_t mpt = maxRun-minRun;
   int fileRun[mpt];
   double Lumi[mpt];

   int npt = 0;
   // read data file
   ifstream file;
   //file.open("./2011-run-lumi.txt");
   file.open("./LumiAeB-dav.txt");
   while (1) {

	   file >> fileRun[npt] >> Lumi[npt];
	   if ( ! file.good() ) break;
	   //cout << "x = " << fileRun[npt] << " y = " << Lumi[npt] << endl;
	   
	   FileRuns->SetBinContent((fileRun[npt]-minRun+2),0.2);
	   npt++;
   }

   file.close();
   printf("found %d Runs in file \n", npt);


bool flaggg=1;
TH1D *LumiRuns = new TH1D("LumiRuns","Zyield vs Run", maxRun-minRun+2, minRun-1, maxRun+1);
for(int i=0; i<npt;i++){
	for(int j=0;j<maxRun;j++){
		if(fileRun[i]==(minRun+j)){
	//cout << fileRun[i]-minRun+1 <<" "<< ((float)Runs->GetBinContent(j+1))/Lumi[i] <<" "<< Lumi[i] << " matched run \n";
		if(Lumi[i]>0.&&Runs->GetBinContent(j+2)>0.){
			LumiRuns->SetBinContent(fileRun[i]-minRun+2,(((double)Runs->GetBinContent(j+2))/Lumi[i])*1000);
			LumiRuns->SetBinError(fileRun[i]-minRun+2,((TMath::Sqrt((double)Runs->GetBinContent(j+2)))/Lumi[i])*1000);
			XsecDistro->Fill((((double)Runs->GetBinContent(j+2))/Lumi[i])*1000);
		flaggg=false;
		}
		}
		else if(fileRun[i]==(minRun+j) && (Runs->GetBinContent(j+2+1)>0. || Runs->GetBinContent(j+2-1)>0.)) cout << "Son cazzi " << fileRun[i]<<"\n";
	}
	if(flaggg) {
	//cout << " ---------------- \n";
	cout << fileRun[i] << " Run not matched! \n";
	//cout << Runs->GetBinContent(i) <<" " << Runs->GetBinContent(i+1) <<" " << Runs->GetBinContent(i+2) <<" "<< Lumi[i] << " probably not empty \n";
	//if(Lumi[i]>1.e+06) cout << "ALERT THIS ONE IS GOOD \n";
	}
	flaggg=true;
}

TCanvas * Canv = (TCanvas*)gDirectory->GetList()->FindObject("Canv");
if (Canv) delete Canv;
Canv = new TCanvas("Canv","Canv",0,0,800,600);
Canv->cd();
LumiRuns->SetXTitle("Run");
LumiRuns->SetYTitle("#sigma (nb)");
LumiRuns->SetLineColor(kBlack);
LumiRuns->Draw("E1");
Runs->SetLineColor(kRed);
//Runs->Draw("SAMES");
FileRuns->SetLineColor(kBlue);
//FileRuns->Draw("SAMES");
//LumiRuns->Draw("E1 SAMES");
Canv->Print("ratio_zlumi.eps");

TCanvas * Another = (TCanvas*)gDirectory->GetList()->FindObject("Another");
if (Another) delete Another;
Another = new TCanvas("Another","Another",0,0,800,600);
Another->cd();
XsecDistro->SetXTitle("#sigma (nb)");
XsecDistro->SetLineColor(kBlack);
XsecDistro->Draw();
Another->Print("distrib_zsigma.eps");

/*
  //-------------
  // per il momento tengo le due sezioni separate... solo per debuggare meglio...
  //-------------
   const Int_t rpt = 120000;
   int lsRun[rpt];
   float LuSec[rpt];

   npt = 0;
   // read data file
   ifstream in;
   in.open("./2011-LS.txt");
   while (1) {

	   in >> lsRun[npt] >> LuSec[npt];
	   if ( ! in.good() ) break;
	   //cout << "x = " << fileRun[npt] << " y = " << Lumi[npt] << endl;
	   npt++;
   }

   in.close();
   printf("found %d LS\n", npt);
*/
}
