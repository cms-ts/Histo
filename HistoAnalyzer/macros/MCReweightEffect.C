#define MCReweightEffect_cxx
#include "MCReweightEffect.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>

void MCReweightEffect::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L MCReweightEffect.C
//      Root > MCReweightEffect t
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

  TH1D *vert=new TH1D("vert","Number of vertices, reweighted Distribution",25,0,25);
  TH1D *vert2=new TH1D("vert2","Number of vertices, reweighted Distribution",25,0,25);

  TH1D *sigmaIeEB=new TH1D("sigmaIeEB","sigmaIeEB, reweighted Distribution",100,0,.1);
  TH1D *sigmaIeEB2=new TH1D("sigmaIeEB2","sigmaIeEB, reweighted Distribution",100,0,.1);

  TH1D *IsoE=new TH1D("IsoE","sigmaIeEB, reweighted Distribution",100,0,.1);
  TH1D *IsoE2=new TH1D("IsoE2","sigmaIeEB, reweighted Distribution",100,0,.1);



   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      vert->Fill(numberOfVertices,Weight);
      vert2->Fill(numberOfVertices,1);
      if (sigmaIeIeEB->size()>0) {float sigma=sigmaIeIeEB->at(0);
      sigmaIeEB->Fill(sigma,Weight);
      sigmaIeEB2->Fill(sigma,1);
      }
      if (IsoEcalEB->size()>0) {float sigma=IsoEcalEB->at(0);
      IsoE->Fill(sigma,Weight);
      IsoE2->Fill(sigma,1);
      }

   }
   
   IsoE->Draw();
   IsoE2->Draw("SAMES");
   
   vert->Draw();
   vert2->Draw("SAMES");
   
   sigmaIeEB->Draw();
   sigmaIeEB2->Draw("SAMES");
}
