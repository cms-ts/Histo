//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Aug 11 09:00:36 2011 by ROOT version 5.27/06b
// from TTree PlotsFeeder_/PlotsFeeder_
// found on file: /tmp/marone/MCSignal_DYToEE_M-20_TuneZ2_7TeV-pythia6_reweightedPU191pb/sum.root
//////////////////////////////////////////////////////////

#ifndef PlotsFeeder_h
#define PlotsFeeder_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "string.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "TObjArray.h"

//TODO find a better way to have global parameters
//Plots Parameters
/*const int tEB = 20; const float tEBmin = 0.; const float tEBmax = 0.20;
  const int eEB = 20; const float eEBmin = 0.; const float eEBmax = 0.20;
  const int hEB = 20; const float hEBmin = 0.; const float hEBmax = 0.20;

  const int tEE = 20; const float tEEmin = 0.; const float tEEmax = 0.20;
  const int eEE = 20; const float eEEmin = 0.; const float eEEmax = 0.20;
  const int hEE = 20; const float hEEmin = 0.; const float hEEmax = 0.20;*/

const int tEB = 36; const float tEBmin = 0.; const float tEBmax = 0.09;
const int eEB = 28; const float eEBmin = 0.; const float eEBmax = 0.07;
const int hEB = 40; const float hEBmin = 0.; const float hEBmax = 0.10;

const int tEE = 16; const float tEEmin = 0.; const float tEEmax = 0.04;
const int eEE = 20; const float eEEmin = 0.; const float eEEmax = 0.05;
const int hEE = 10; const float hEEmin = 0.; const float hEEmax = 0.025;

const int iHEEB = 16; const float HEEBmin = 0.; const float HEEBmax = 0.04;
const int dPhiEB = 24; const float dPhiEBmin = 0.; const float dPhiEBmax = 0.06;
const int dEtaEB = 16; const float dEtaEBmin = 0.; const float dEtaEBmax = 0.004;
const int sigmaEB = 40; const float sigmaEBmin = 0.; const float sigmaEBmax = 0.01;

const int iHEEE = 30; const float HEEEmin = 0.; const float HEEEmax = 0.15;
const int dPhiEE = 18; const float dPhiEEmin = 0.; const float dPhiEEmax = 0.03;
const int dEtaEE = 28; const float dEtaEEmin = 0.; const float dEtaEEmax = 0.007;
const int sigmaEE = 36; const float sigmaEEmin = 0.; const float sigmaEEmax = 0.03;



//TODO find a better way to have global parameters
//FILE NAMES
const std::string mctmpfile   = "/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_11.root";
const std::string dirname = "validationJEC";





class PlotsFeeder {
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
   TBranch        *b_Run;   //!
   TBranch        *b_LS;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_numberOfVertices;   //!
   TBranch        *b_Weight;   //!


   const std::string mcfile;//   = "/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011A_v1_11.root";
   PlotsFeeder(std::string mcfile="dummy", TTree *tree=0);
   virtual ~PlotsFeeder();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual TObjArray * Loop(int NumOfVtx);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

};

#endif

#ifdef PlotsFeeder_cxx
PlotsFeeder::PlotsFeeder(std::string mcfile, TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if(mcfile=="dummy") mcfile = mctmpfile;

   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(mcfile.c_str());
      if (!f) {
         f = new TFile(mcfile.c_str());
	 std::string fake = mcfile;
	 fake = fake + ":/" + dirname;
         f->cd(fake.c_str());
      }
      tree = (TTree*)gDirectory->Get("treeVJ_");

   }
   Init(tree);
}

PlotsFeeder::~PlotsFeeder()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PlotsFeeder::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PlotsFeeder::LoadTree(Long64_t entry)
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

void PlotsFeeder::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).



   // Set object pointer
   IsoTrkEB_PUR = 0;
   IsoEcalEB_PUR = 0;
   IsoHcalEB_PUR = 0;
   IsoTrkEB = 0;
   IsoEcalEB = 0;
   IsoHcalEB = 0;
   HEEB = 0;
   DeltaPhiTkCluEB = 0;
   DeltaEtaTkCluEB = 0;
   sigmaIeIeEB = 0;
   IsoTrkEE_PUR = 0;
   IsoEcalEE_PUR = 0;
   IsoHcalEE_PUR = 0;
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

   fChain->SetBranchAddress("IsoTrkEB_PUR", &IsoTrkEB_PUR, &b_IsoTrkEB_PUR);
   fChain->SetBranchAddress("IsoEcalEB_PUR", &IsoEcalEB_PUR, &b_IsoEcalEB_PUR);
   fChain->SetBranchAddress("IsoHcalEB_PUR", &IsoHcalEB_PUR, &b_IsoHcalEB_PUR);
   fChain->SetBranchAddress("IsoTrkEB", &IsoTrkEB, &b_IsoTrkEB);
   fChain->SetBranchAddress("IsoEcalEB", &IsoEcalEB, &b_IsoEcalEB);
   fChain->SetBranchAddress("IsoHcalEB", &IsoHcalEB, &b_IsoHcalEB);
   fChain->SetBranchAddress("HEEB", &HEEB, &b_HEEB);
   fChain->SetBranchAddress("DeltaPhiTkCluEB", &DeltaPhiTkCluEB, &b_DeltaPhiTkCluEB);
   fChain->SetBranchAddress("DeltaEtaTkCluEB", &DeltaEtaTkCluEB, &b_DeltaEtaTkCluEB);
   fChain->SetBranchAddress("sigmaIeIeEB", &sigmaIeIeEB, &b_sigmaIeIeEB);
   fChain->SetBranchAddress("IsoTrkEE_PUR", &IsoTrkEE_PUR, &b_IsoTrkEE_PUR);
   fChain->SetBranchAddress("IsoEcalEE_PUR", &IsoEcalEE_PUR, &b_IsoEcalEE_PUR);
   fChain->SetBranchAddress("IsoHcalEE_PUR", &IsoHcalEE_PUR, &b_IsoHcalEE_PUR);
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
   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("LS", &LS, &b_LS);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("numberOfVertices", &numberOfVertices, &b_numberOfVertices);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   Notify();
}

Bool_t PlotsFeeder::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PlotsFeeder::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PlotsFeeder::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}



#endif // #ifdef PlotsFeeder_cxx
