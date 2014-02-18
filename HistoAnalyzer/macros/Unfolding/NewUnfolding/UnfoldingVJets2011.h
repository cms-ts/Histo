//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 28 13:34:25 2011 by ROOT version 5.27/06b
// from TTree treeUN_/treeUN_
// found on file: prova.root
//////////////////////////////////////////////////////////

#ifndef UnfoldingVJets2011_h
#define UnfoldingVJets2011_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TLorentzVector.h"


#include "RooUnfoldResponse.h"
#include "RooUnfoldBayes.h"
#include "RooUnfoldSvd.h"
#include "RooUnfoldBinByBin.h"
#include "RooUnfoldInvert.h"


class UnfoldingVJets2011 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        evWeight;
   Double_t        evWeightSherpa;
   Double_t        Z_pt;
   Double_t        Z_y;
   Int_t           Jet_multiplicity;
   Double_t        Z_pt_gen;
   Double_t        Z_y_gen;
   Int_t           Jet_multiplicity_gen;
   Double_t        jet1_pt;
   Double_t        jet1_pt_gen;
   Double_t        jet2_pt;
   Double_t        jet2_pt_gen;
   Double_t        jet3_pt;
   Double_t        jet3_pt_gen;
   Double_t        jet4_pt;
   Double_t        jet4_pt_gen;
   Double_t        jet5_pt;
   Double_t        jet5_pt_gen;
   Double_t        jet6_pt;
   Double_t        jet6_pt_gen;
   Double_t        jet1_eta;
   Double_t        jet1_eta_gen;
   Double_t        jet2_eta;
   Double_t        jet2_eta_gen;
   Double_t        jet3_eta;
   Double_t        jet3_eta_gen;
   Double_t        jet4_eta;
   Double_t        jet4_eta_gen;
   Double_t        jet5_eta;
   Double_t        jet5_eta_gen;
   Double_t        jet6_eta;
   Double_t        jet6_eta_gen;
   Double_t        e1_eta;
   Double_t        e2_eta;
   Double_t        e1_pt;
   Double_t        e2_pt;
   Double_t        e1_phi;
   Double_t        e2_phi;
   Double_t        e1_mass;
   Double_t        e2_mass;
   Bool_t          isElectron;
   Double_t        invMass_gen;
   Double_t        l1_eta_gen;
   Double_t        l2_eta_gen;
   Double_t        l1_pt_gen;
   Double_t        l2_pt_gen;
   Bool_t           genZInAcceptance;
   Bool_t           recoZInAcceptance;
   int    e1_charge;
   TLorentzVector e1_tlv;
   int    e2_charge;
   TLorentzVector e2_tlv;
   int Run;
   vector<double> deltaRRecoGenJet;

   Double_t        jet1_pt_gen_abs;
   Double_t        jet2_pt_gen_abs;
   Double_t        jet3_pt_gen_abs;
   Double_t        jet4_pt_gen_abs;
   Double_t        jet5_pt_gen_abs;
   Double_t        jet6_pt_gen_abs;
   Double_t        jet7_pt_gen_abs;

   Double_t        jet1_eta_gen_abs;
   Double_t        jet2_eta_gen_abs;
   Double_t        jet3_eta_gen_abs;
   Double_t        jet4_eta_gen_abs;
   Double_t        jet5_eta_gen_abs;
   Double_t        jet6_eta_gen_abs;
   Double_t        jet7_eta_gen_abs;

   Double_t        jet1_phi;
   Double_t        jet2_phi;   
   Double_t        jet3_phi;
   Double_t        jet4_phi;
   Double_t        jet5_phi;
   Double_t        jet6_phi;
   int numberOfVertices;
   Bool_t isAnyJetTooCloseToLepton;

   // List of branches
   TBranch        *b_evWeight;   //!
   TBranch        *b_evWeightSherpa;   //!
   TBranch        *b_Z_pt;   //!
   TBranch        *b_Z_y;   //!
   TBranch        *b_Jet_multiplicity;   //!
   TBranch        *b_Z_pt_gen;   //!
   TBranch        *b_Z_y_gen;   //!
   TBranch        *b_Jet_multiplicity_gen;   //!
   TBranch        *b_jet1_pt;
   TBranch        *b_jet1_pt_gen;
   TBranch        *b_jet2_pt;
   TBranch        *b_jet2_pt_gen;
   TBranch        *b_jet3_pt;
   TBranch        *b_jet3_pt_gen;
   TBranch        *b_jet4_pt;
   TBranch        *b_jet4_pt_gen;
   TBranch        *b_jet5_pt;
   TBranch        *b_jet5_pt_gen;
   TBranch        *b_jet6_pt;
   TBranch        *b_jet6_pt_gen;
   TBranch        *b_jet1_eta;
   TBranch        *b_jet1_eta_gen;
   TBranch        *b_jet2_eta;
   TBranch        *b_jet2_eta_gen;
   TBranch        *b_jet3_eta;
   TBranch        *b_jet3_eta_gen;
   TBranch        *b_jet4_eta;
   TBranch        *b_jet4_eta_gen;
   TBranch        *b_jet5_eta;
   TBranch        *b_jet5_eta_gen;
   TBranch        *b_jet6_eta;
   TBranch        *b_jet6_eta_gen;
   TBranch        *b_e1_eta;
   TBranch        *b_e2_eta;
   TBranch        *b_e1_pt;
   TBranch        *b_e2_pt;
   TBranch        *b_e1_phi;
   TBranch        *b_e2_phi;
   TBranch        *b_e1_mass;
   TBranch        *b_e2_mass;
   TBranch        *b_isElectron;
   TBranch        *b_invMass_gen;   //!
   TBranch        *b_l1_eta_gen;   //!
   TBranch        *b_l2_eta_gen;   //!
   TBranch        *b_l1_pt_gen;   //!
   TBranch        *b_l2_pt_gen;   //!
   TBranch        *b_genZInAcceptance;   //!
   TBranch        *b_recoZInAcceptance;   //!
   TBranch        *b_e1_charge;
   TBranch        *b_e2_charge;
   TBranch        *b_e1_tlv;
   TBranch        *b_e2_tlv;
   TBranch        *b_Run;
   TBranch        *b_deltaRRecoGenJet;

   TBranch        *b_jet1_pt_gen_abs;
   TBranch        *b_jet2_pt_gen_abs;
   TBranch        *b_jet3_pt_gen_abs;
   TBranch        *b_jet4_pt_gen_abs;
   TBranch        *b_jet5_pt_gen_abs;
   TBranch        *b_jet6_pt_gen_abs;
   TBranch        *b_jet7_pt_gen_abs;

   TBranch        *b_jet1_eta_gen_abs;
   TBranch        *b_jet2_eta_gen_abs;
   TBranch        *b_jet3_eta_gen_abs;
   TBranch        *b_jet4_eta_gen_abs;
   TBranch        *b_jet5_eta_gen_abs;
   TBranch        *b_jet6_eta_gen_abs;
   TBranch        *b_jet7_eta_gen_abs;

   TBranch        *b_numberOfVertices;

   TBranch        *b_jet1_phi;
   TBranch        *b_jet2_phi;
   TBranch        *b_jet3_phi;
   TBranch        *b_jet4_phi;
   TBranch        *b_jet5_phi;
   TBranch        *b_jet6_phi;

   TBranch        *b_isAnyJetTooCloseToLepton;

   UnfoldingVJets2011(TTree *tree=0);
   virtual ~UnfoldingVJets2011();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     LoopText(string algo, string type, int numbJets,bool isMuon);
   virtual void     LoopOneFour(bool isMuon);
   virtual void     LoopVJets(int numbOfJets, string whichtype, string whichalgo);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef UnfoldingVJets2011_cxx
UnfoldingVJets2011::UnfoldingVJets2011(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  if (tree == 0) {
    //  TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("prova.root");
    //if (!f) {
    //   f = new TFile("prova.root");
    //   f->cd("prova.root:/validationJEC");
    //}
    //tree = (TTree*)gDirectory->Get("treeUN_");
    //
  }
  //Init(tree);
}

UnfoldingVJets2011::~UnfoldingVJets2011()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t UnfoldingVJets2011::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t UnfoldingVJets2011::LoadTree(Long64_t entry)
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

void UnfoldingVJets2011::Init(TTree *tree)
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

   fChain->SetBranchAddress("evWeight", &evWeight, &b_evWeight);
   fChain->SetBranchAddress("evWeightSherpa", &evWeightSherpa, &b_evWeightSherpa);
   fChain->SetBranchAddress("Z_pt", &Z_pt, &b_Z_pt);
   fChain->SetBranchAddress("Z_y", &Z_y, &b_Z_y);
   fChain->SetBranchAddress("Jet_multiplicity", &Jet_multiplicity, &b_Jet_multiplicity);
   fChain->SetBranchAddress("Z_pt_gen", &Z_pt_gen, &b_Z_pt_gen);
   fChain->SetBranchAddress("Z_y_gen", &Z_y_gen, &b_Z_y_gen);
   fChain->SetBranchAddress("Jet_multiplicity_gen", &Jet_multiplicity_gen, &b_Jet_multiplicity_gen);
   fChain->SetBranchAddress("jet1_pt", &jet1_pt, &b_jet1_pt);
   fChain->SetBranchAddress("jet1_pt_gen", &jet1_pt_gen, &b_jet1_pt_gen);
   fChain->SetBranchAddress("jet2_pt", &jet2_pt, &b_jet2_pt);
   fChain->SetBranchAddress("jet2_pt_gen", &jet2_pt_gen, &b_jet2_pt_gen);
   fChain->SetBranchAddress("jet3_pt", &jet3_pt, &b_jet3_pt);
   fChain->SetBranchAddress("jet3_pt_gen", &jet3_pt_gen, &b_jet3_pt_gen);
   fChain->SetBranchAddress("jet4_pt", &jet4_pt, &b_jet4_pt);
   fChain->SetBranchAddress("jet4_pt_gen", &jet4_pt_gen, &b_jet4_pt_gen);
   fChain->SetBranchAddress("jet5_pt", &jet5_pt, &b_jet5_pt);
   fChain->SetBranchAddress("jet5_pt_gen", &jet5_pt_gen, &b_jet5_pt_gen);
   fChain->SetBranchAddress("jet6_pt", &jet6_pt, &b_jet6_pt);
   fChain->SetBranchAddress("jet6_pt_gen", &jet6_pt_gen, &b_jet6_pt_gen);

   fChain->SetBranchAddress("jet1_eta", &jet1_eta, &b_jet1_eta);
   fChain->SetBranchAddress("jet1_eta_gen", &jet1_eta_gen, &b_jet1_eta_gen);
   fChain->SetBranchAddress("jet2_eta", &jet2_eta, &b_jet2_eta);
   fChain->SetBranchAddress("jet2_eta_gen", &jet2_eta_gen, &b_jet2_eta_gen);
   fChain->SetBranchAddress("jet3_eta", &jet3_eta, &b_jet3_eta);
   fChain->SetBranchAddress("jet3_eta_gen", &jet3_eta_gen, &b_jet3_eta_gen);
   fChain->SetBranchAddress("jet4_eta", &jet4_eta, &b_jet4_eta);
   fChain->SetBranchAddress("jet4_eta_gen", &jet4_eta_gen, &b_jet4_eta_gen);
   fChain->SetBranchAddress("jet5_eta", &jet5_eta, &b_jet5_eta);
   fChain->SetBranchAddress("jet5_eta_gen", &jet5_eta_gen, &b_jet5_eta_gen);
   fChain->SetBranchAddress("jet6_eta", &jet6_eta, &b_jet6_eta);
   fChain->SetBranchAddress("jet6_eta_gen", &jet6_eta_gen, &b_jet6_eta_gen);

   fChain->SetBranchAddress("e1_eta", &e1_eta, &b_e1_eta);
   fChain->SetBranchAddress("e2_eta", &e2_eta, &b_e2_eta);
   fChain->SetBranchAddress("e1_pt", &e1_pt, &b_e1_pt);
   fChain->SetBranchAddress("e2_pt", &e2_pt, &b_e2_pt);
   fChain->SetBranchAddress("e1_phi", &e1_phi, &b_e1_phi);
   fChain->SetBranchAddress("e2_phi", &e2_phi, &b_e2_phi);
   fChain->SetBranchAddress("e1_mass", &e1_mass, &b_e1_mass);
   fChain->SetBranchAddress("e2_mass", &e2_mass, &b_e2_mass);
   fChain->SetBranchAddress("e1_charge", &e1_charge, &b_e1_charge);
   fChain->SetBranchAddress("e2_charge", &e2_charge, &b_e2_charge);
   fChain->SetBranchAddress("e1_tlv", &e1_tlv);
   fChain->SetBranchAddress("e2_tlv", &e2_tlv);

   fChain->SetBranchAddress("isElectron", &isElectron, &b_isElectron);
   fChain->SetBranchAddress("invMass_gen", &invMass_gen, &b_invMass_gen);
   fChain->SetBranchAddress("l1_eta_gen", &l1_eta_gen, &b_l1_eta_gen);
   fChain->SetBranchAddress("l2_eta_gen", &l2_eta_gen, &b_l2_eta_gen);
   fChain->SetBranchAddress("l1_pt_gen", &l1_pt_gen, &b_l1_pt_gen);
   fChain->SetBranchAddress("l2_pt_gen", &l2_pt_gen, &b_l2_pt_gen);
   fChain->SetBranchAddress("genZInAcceptance", &genZInAcceptance, &b_genZInAcceptance);
   fChain->SetBranchAddress("recoZInAcceptance", &recoZInAcceptance, &b_recoZInAcceptance);
   fChain->SetBranchAddress("deltaRRecoGenJet",&deltaRRecoGenJet,&b_deltaRRecoGenJet);
   fChain->SetBranchAddress("Run", &Run);

   fChain->SetBranchAddress("numberOfVertices", &numberOfVertices);

   fChain->SetBranchAddress("jet1_pt_gen_abs", &jet1_pt_gen_abs, &b_jet1_pt_gen_abs);
   fChain->SetBranchAddress("jet2_pt_gen_abs", &jet2_pt_gen_abs, &b_jet2_pt_gen_abs);
   fChain->SetBranchAddress("jet3_pt_gen_abs", &jet3_pt_gen_abs, &b_jet3_pt_gen_abs);
   fChain->SetBranchAddress("jet4_pt_gen_abs", &jet4_pt_gen_abs, &b_jet4_pt_gen_abs);
   fChain->SetBranchAddress("jet5_pt_gen_abs", &jet5_pt_gen_abs, &b_jet5_pt_gen_abs);
   fChain->SetBranchAddress("jet6_pt_gen_abs", &jet6_pt_gen_abs, &b_jet6_pt_gen_abs);
   fChain->SetBranchAddress("jet7_pt_gen_abs", &jet7_pt_gen_abs, &b_jet7_pt_gen_abs);

   fChain->SetBranchAddress("jet1_eta_gen_abs", &jet1_eta_gen_abs, &b_jet1_eta_gen_abs);
   fChain->SetBranchAddress("jet2_eta_gen_abs", &jet2_eta_gen_abs, &b_jet2_eta_gen_abs);
   fChain->SetBranchAddress("jet3_eta_gen_abs", &jet3_eta_gen_abs, &b_jet3_eta_gen_abs);
   fChain->SetBranchAddress("jet4_eta_gen_abs", &jet4_eta_gen_abs, &b_jet4_eta_gen_abs);
   fChain->SetBranchAddress("jet5_eta_gen_abs", &jet5_eta_gen_abs, &b_jet5_eta_gen_abs);
   fChain->SetBranchAddress("jet6_eta_gen_abs", &jet6_eta_gen_abs, &b_jet6_eta_gen_abs);
   fChain->SetBranchAddress("jet7_eta_gen_abs", &jet7_eta_gen_abs, &b_jet7_eta_gen_abs);

   fChain->SetBranchAddress("jet1_phi", &jet1_phi, &b_jet1_phi);
   fChain->SetBranchAddress("jet2_phi", &jet2_phi, &b_jet2_phi);
   fChain->SetBranchAddress("jet3_phi", &jet3_phi, &b_jet3_phi);
   fChain->SetBranchAddress("jet4_phi", &jet4_phi, &b_jet4_phi);
   fChain->SetBranchAddress("jet5_phi", &jet5_phi, &b_jet5_phi);
   fChain->SetBranchAddress("jet6_phi", &jet6_phi, &b_jet6_phi);

   fChain->SetBranchAddress("isAnyJetTooCloseToLepton",&isAnyJetTooCloseToLepton,&b_isAnyJetTooCloseToLepton);
   Notify();
}

Bool_t UnfoldingVJets2011::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void UnfoldingVJets2011::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t UnfoldingVJets2011::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
 return entry;
}
#endif // #ifdef UnfoldingVJets_cxx

// Set the kmin, kmax, minPtPlot, maxPtPlot (those are global variables)



