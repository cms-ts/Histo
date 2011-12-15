//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 28 13:34:25 2011 by ROOT version 5.27/06b
// from TTree treeUN_/treeUN_
// found on file: prova.root
//////////////////////////////////////////////////////////

#ifndef Unfolding_h
#define Unfolding_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldBinByBin.h"


class Unfolding {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        Z_pt;
   Double_t        Z_y;
   Int_t           Jet_multiplicity;
   Double_t        Z_pt_gen;
   Double_t        Z_y_gen;
   Int_t           Jet_multiplicity_gen;

   // List of branches
   TBranch        *b_Z_pt;   //!
   TBranch        *b_Z_y;   //!
   TBranch        *b_Jet_multiplicity;   //!
   TBranch        *b_Z_pt_gen;   //!
   TBranch        *b_Z_y_gen;   //!
   TBranch        *b_Jet_multiplicity_gen;   //!

   Unfolding(TTree *tree=0);
   virtual ~Unfolding();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     LoopJetMultiplicity();
   virtual void     LoopZpt();
   virtual void     LoopZy();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Unfolding_cxx
Unfolding::Unfolding(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  //if (tree == 0) {
  //  TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("prova.root");
  //if (!f) {
  //   f = new TFile("prova.root");
  //   f->cd("prova.root:/validationJEC");
  //}
  //tree = (TTree*)gDirectory->Get("treeUN_");
  //
  //}
  //Init(tree);
}

Unfolding::~Unfolding()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Unfolding::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Unfolding::LoadTree(Long64_t entry)
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

void Unfolding::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Z_pt", &Z_pt, &b_Z_pt);
   fChain->SetBranchAddress("Z_y", &Z_y, &b_Z_y);
   fChain->SetBranchAddress("Jet_multiplicity", &Jet_multiplicity, &b_Jet_multiplicity);
   fChain->SetBranchAddress("Z_pt_gen", &Z_pt_gen, &b_Z_pt_gen);
   fChain->SetBranchAddress("Z_y_gen", &Z_y_gen, &b_Z_y_gen);
   fChain->SetBranchAddress("Jet_multiplicity_gen", &Jet_multiplicity_gen, &b_Jet_multiplicity_gen);
   Notify();
}

Bool_t Unfolding::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Unfolding::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Unfolding::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
 return 1;
}
#endif // #ifdef Unfolding_cxx
