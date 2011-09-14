//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 11 09:00:36 2011 by ROOT version 5.27/06b
// from TTree MCReweightEffect_/MCReweightEffect_
// found on file: /tmp/marone/MCSignal_DYToEE_M-20_TuneZ2_7TeV-pythia6_reweightedPU191pb/sum.root
//////////////////////////////////////////////////////////

#ifndef MCReweightEffect_h
#define MCReweightEffect_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "string.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

   const Int_t kMaxHLTAndPrescale = 1;

class MCReweightEffect {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   std::vector<double>  *IsoTrkEB_PUR;
   std::vector<double>  *IsoEcalEB_PUR;
   std::vector<double>  *IsoHcalEB_PUR;
   std::vector<double>  *IsoTrkEB;
   std::vector<double>  *IsoEcalEB;
   std::vector<double>  *IsoHcalEB;
   std::vector<double>  *HEEB;
   std::vector<float>   *DeltaPhiTkCluEB;
   std::vector<float>   *DeltaEtaTkCluEB;
   std::vector<float>   *sigmaIeIeEB;
   std::vector<double>  *IsoTrkEE_PUR;
   std::vector<double>  *IsoEcalEE_PUR;
   std::vector<double>  *IsoHcalEE_PUR;
   std::vector<double>  *IsoTrkEE;
   std::vector<double>  *IsoEcalEE;
   std::vector<double>  *IsoHcalEE;
   std::vector<double>  *HEEE;
   std::vector<float>   *DeltaPhiTkCluEE;
   std::vector<float>   *DeltaEtaTkCluEE;
   std::vector<float>   *sigmaIeIeEE;
   std::vector<double>  *fbrem;
   std::vector<double>  *etaSC;
   std::vector<float>   *Dcot;
   std::vector<float>   *Dist;
   std::vector<int>     *NumberOfExpectedInnerHits;
   Int_t           HLTAndPrescale_;
   Int_t           HLTAndPrescale_second[kMaxHLTAndPrescale];   //[HLTAndPrescale_]
   Int_t           Run;
   Int_t           LS;
   Int_t           Event;
   Int_t           numberOfVertices;
   Double_t        Weight;

   // List of branches
   TBranch        *b_IsoTrkEB_PUR;   //!
   TBranch        *b_IsoEcalEB_PUR;   //!
   TBranch        *b_IsoHcalEB_PUR;   //!
   TBranch        *b_IsoTrkEB;   //!
   TBranch        *b_IsoEcalEB;   //!
   TBranch        *b_IsoHcalEB;   //!
   TBranch        *b_HEEB;   //!
   TBranch        *b_DeltaPhiTkCluEB;   //!
   TBranch        *b_DeltaEtaTkCluEB;   //!
   TBranch        *b_sigmaIeIeEB;   //!
   TBranch        *b_IsoTrkEE_PUR;   //!
   TBranch        *b_IsoEcalEE_PUR;   //!
   TBranch        *b_IsoHcalEE_PUR;   //!
   TBranch        *b_IsoTrkEE;   //!
   TBranch        *b_IsoEcalEE;   //!
   TBranch        *b_IsoHcalEE;   //!
   TBranch        *b_HEEE;   //!
   TBranch        *b_DeltaPhiTkCluEE;   //!
   TBranch        *b_DeltaEtaTkCluEE;   //!
   TBranch        *b_sigmaIeIeEE;   //!
   TBranch        *b_fbrem;   //!
   TBranch        *b_Dcot;   //!
   TBranch        *b_Dist;   //!
   TBranch        *b_NumberOfExpectedInnerHits;   //!
   TBranch        *b_HLTAndPrescale_;   //!
   TBranch        *b_HLTAndPrescale_first;   //!
   TBranch        *b_HLTAndPrescale_second;   //!
   TBranch        *b_Run;   //!
   TBranch        *b_LS;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_numberOfVertices;   //!
   TBranch        *b_Weight;   //!

   MCReweightEffect(TTree *tree=0);
   virtual ~MCReweightEffect();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MCReweightEffect_cxx
MCReweightEffect::MCReweightEffect(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/gpfs/cms/users/dscaini/mc-v1-wPUR_3set.root");
      if (!f) {
         f = new TFile("/gpfs/cms/users/dscaini/mc-v1-wPUR_3set.root");
         f->cd("/gpfs/cms/users/dscaini/mc-v1-wPUR_3set.root:/demo");
      }
      tree = (TTree*)gDirectory->Get("treeVJ_");

   }
   Init(tree);
}

MCReweightEffect::~MCReweightEffect()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MCReweightEffect::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MCReweightEffect::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MCReweightEffect::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   IsoTrkEB = 0;
   IsoEcalEB = 0;
   IsoHcalEB = 0;
   HEEB = 0;
   DeltaPhiTkCluEB = 0;
   DeltaEtaTkCluEB = 0;
   sigmaIeIeEB = 0;
   IsoTrkEE = 0;
   IsoEcalEE = 0;
   IsoHcalEE = 0;
   HEEE = 0;
   DeltaPhiTkCluEE = 0;
   DeltaEtaTkCluEE = 0;
   sigmaIeIeEE = 0;
   fbrem = 0;
   etaSC = 0;
   Dcot = 0;
   Dist = 0;
   NumberOfExpectedInnerHits = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("IsoTrkEB", &IsoTrkEB, &b_IsoTrkEB);
   fChain->SetBranchAddress("IsoEcalEB", &IsoEcalEB, &b_IsoEcalEB);
   fChain->SetBranchAddress("IsoHcalEB", &IsoHcalEB, &b_IsoHcalEB);
   fChain->SetBranchAddress("HEEB", &HEEB, &b_HEEB);
   fChain->SetBranchAddress("DeltaPhiTkCluEB", &DeltaPhiTkCluEB, &b_DeltaPhiTkCluEB);
   fChain->SetBranchAddress("DeltaEtaTkCluEB", &DeltaEtaTkCluEB, &b_DeltaEtaTkCluEB);
   fChain->SetBranchAddress("sigmaIeIeEB", &sigmaIeIeEB, &b_sigmaIeIeEB);
   fChain->SetBranchAddress("IsoTrkEE", &IsoTrkEE, &b_IsoTrkEE);
   fChain->SetBranchAddress("IsoEcalEE", &IsoEcalEE, &b_IsoEcalEE);
   fChain->SetBranchAddress("IsoHcalEE", &IsoHcalEE, &b_IsoHcalEE);
   fChain->SetBranchAddress("HEEE", &HEEE, &b_HEEE);
   fChain->SetBranchAddress("DeltaPhiTkCluEE", &DeltaPhiTkCluEE, &b_DeltaPhiTkCluEE);
   fChain->SetBranchAddress("DeltaEtaTkCluEE", &DeltaEtaTkCluEE, &b_DeltaEtaTkCluEE);
   fChain->SetBranchAddress("sigmaIeIeEE", &sigmaIeIeEE, &b_sigmaIeIeEE);
   fChain->SetBranchAddress("fbrem", &fbrem, &b_fbrem);
   fChain->SetBranchAddress("Dcot", &Dcot, &b_Dcot);
   fChain->SetBranchAddress("Dist", &Dist, &b_Dist);
   fChain->SetBranchAddress("NumberOfExpectedInnerHits", &NumberOfExpectedInnerHits, &b_NumberOfExpectedInnerHits);
   fChain->SetBranchAddress("HLTAndPrescale", &HLTAndPrescale_, &b_HLTAndPrescale_);
   fChain->SetBranchAddress("HLTAndPrescale.second", &HLTAndPrescale_second, &b_HLTAndPrescale_second);
   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("LS", &LS, &b_LS);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("numberOfVertices", &numberOfVertices, &b_numberOfVertices);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   Notify();
}

Bool_t MCReweightEffect::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MCReweightEffect::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MCReweightEffect::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MCReweightEffect_cxx
