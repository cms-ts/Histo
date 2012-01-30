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
   if (fChain == 0) return;

int minRun=0;
int maxRun=0;
bool forminRun=true;



   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(forminRun && (Run!=0)){minRun=Run; forminRun=false;}
      if((Run!=0) && (Run>maxRun)){maxRun=Run;}
   }


   TH1D * h_Run = new TH1D("h_Run","Z vs run",maxRun-minRun+2,minRun-1,maxRun+1);
   const Int_t mpt = maxRun-minRun;
   int fileRun[mpt];
   Float_t Lumi[mpt];

   int npt = 0;
   // read data file
   ifstream in;
   in.open("2011-run-lumi.txt");
   while (1) {

	   in >> fileRun[npt] >> Lumi[npt];
	   if ( ! in.good() ) break;
	   //cout << "x = " << fileRun[npt] << " y = " << Lumi[npt] << endl;
	   npt++;
   }

   in.close();
   printf(" found %d points\n", npt);


   int auxRun=0;
   int counter=0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	   // if (Cut(ientry) < 0) continue;
	   
	   if(auxRun!=(int)Run){
		   if(auxRun!=0){
			for(int i=0;i<=npt;i++){
			if(fileRun[i]==Run) h_Run->SetBinContent(Run-minRun+1,((double)counter/Lumi[i]));
			}
		   }

		   auxRun=(int)Run;
		   counter=0;
	   }
	   if(auxRun==(int)Run) counter++;
	   //cout << "auxRun Run counter "<<auxRun<<" "<< Run<<" "<< counter<< "\n";
   }

h_Run->Draw();

}
