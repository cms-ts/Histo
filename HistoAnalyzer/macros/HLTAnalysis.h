//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 12 11:12:18 2011 by ROOT version 5.27/06b
// from TTree treeHLT_/treeHLT_
// found on file: histo.root
//////////////////////////////////////////////////////////

#ifndef HLTAnalysis_h
#define HLTAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string.h>

const std::string rootfile="histo-03Oct.root";

class HLTAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   vector<string>  *HLTPaths;
   vector<int>     *HLTPrescales;
   vector<string>  *HLTNames;
   vector<double>  *HLTValue;
   ULong64_t       Timestamp;
   vector<int>     *vRun;

   // List of branches
   TBranch        *b_HLTPaths;   //!
   TBranch        *b_HLTPrescales;   //!
   TBranch        *b_HLTNames;   //!
   TBranch        *b_HLTValue;   //!
   TBranch        *b_Timestamp;   //!
   TBranch        *b_vRun;   //!

   HLTAnalysis(TTree *tree=0);
   virtual ~HLTAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HLTAnalysis_cxx
HLTAnalysis::HLTAnalysis(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(rootfile.c_str());
      if (!f) {
         f = new TFile(rootfile.c_str());
	 std::string service=rootfile+":/demo";
         f->cd(service.c_str());
      }
      tree = (TTree*)gDirectory->Get("treeHLT_");

   }
   Init(tree);
}

HLTAnalysis::~HLTAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HLTAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HLTAnalysis::LoadTree(Long64_t entry)
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

void HLTAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   HLTPaths = 0;
   HLTPrescales = 0;
   HLTNames = 0;
   HLTValue = 0;
   vRun = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("HLTPaths", &HLTPaths, &b_HLTPaths);
   fChain->SetBranchAddress("HLTPrescales", &HLTPrescales, &b_HLTPrescales);
   fChain->SetBranchAddress("HLTNames", &HLTNames, &b_HLTNames);
   fChain->SetBranchAddress("HLTValue", &HLTValue, &b_HLTValue);
   fChain->SetBranchAddress("Timestamp", &Timestamp, &b_Timestamp);
   fChain->SetBranchAddress("vRun", &vRun, &b_vRun);
   Notify();
}

Bool_t HLTAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HLTAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HLTAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HLTAnalysis_cxx
