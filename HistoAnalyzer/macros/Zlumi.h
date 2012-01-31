//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan 30 10:41:09 2012 by ROOT version 5.27/06b
// from TTree treeVJ_/treeVJ_
// found on file: /gpfs/cms/data/2011/jet/jetValidation_DATA_2011A_v1_10.root
//////////////////////////////////////////////////////////

#ifndef Zlumi_h
#define Zlumi_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
const std::string datafile   = "/gpfs/cms/data/2011/jet/jetValidation_DATA_2011A_v1_10.root";
const std::string dirname = "validationJEC";


class Zlumi {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   vector<double>  *IsoTrkEB_PUR;
   vector<double>  *IsoEcalEB_PUR;
   vector<double>  *IsoHcalEB_PUR;
   vector<double>  *IsoTrkEE_PUR;
   vector<double>  *IsoEcalEE_PUR;
   vector<double>  *IsoHcalEE_PUR;
   vector<double>  *IsoTrkEB;
   vector<double>  *IsoEcalEB;
   vector<double>  *IsoHcalEB;
   vector<double>  *HEEB;
   vector<float>   *DeltaPhiTkCluEB;
   vector<float>   *DeltaEtaTkCluEB;
   vector<float>   *sigmaIeIeEB;
   vector<double>  *IsoTrkEE;
   vector<double>  *IsoEcalEE;
   vector<double>  *IsoHcalEE;
   vector<double>  *HEEE;
   vector<float>   *DeltaPhiTkCluEE;
   vector<float>   *DeltaEtaTkCluEE;
   vector<float>   *sigmaIeIeEE;
   vector<double>  *fbrem;
   vector<double>  *etaSC;
   vector<float>   *Dcot;
   vector<float>   *Dist;
   vector<int>     *NumberOfExpectedInnerHits;
   vector<double>  *Rho;
   Int_t           Run;
   Int_t           LS;
   Int_t           Event;
   Int_t           numberOfVertices;
   //Double_t        etaSC;
   Double_t        Weight;

   // List of branches
   TBranch        *b_IsoTrkEB_PUR;   //!
   TBranch        *b_IsoEcalEB_PUR;   //!
   TBranch        *b_IsoHcalEB_PUR;   //!
   TBranch        *b_IsoTrkEE_PUR;   //!
   TBranch        *b_IsoEcalEE_PUR;   //!
   TBranch        *b_IsoHcalEE_PUR;   //!
   TBranch        *b_IsoTrkEB;   //!
   TBranch        *b_IsoEcalEB;   //!
   TBranch        *b_IsoHcalEB;   //!
   TBranch        *b_HEEB;   //!
   TBranch        *b_DeltaPhiTkCluEB;   //!
   TBranch        *b_DeltaEtaTkCluEB;   //!
   TBranch        *b_sigmaIeIeEB;   //!
   TBranch        *b_IsoTrkEE;   //!
   TBranch        *b_IsoEcalEE;   //!
   TBranch        *b_IsoHcalEE;   //!
   TBranch        *b_HEEE;   //!
   TBranch        *b_DeltaPhiTkCluEE;   //!
   TBranch        *b_DeltaEtaTkCluEE;   //!
   TBranch        *b_sigmaIeIeEE;   //!
   TBranch        *b_fbrem;   //!
   TBranch        *b_etaSC;   //!
   TBranch        *b_Dcot;   //!
   TBranch        *b_Dist;   //!
   TBranch        *b_NumberOfExpectedInnerHits;   //!
   TBranch        *b_Rho;   //!
   TBranch        *b_Run;   //!
   TBranch        *b_LS;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_numberOfVertices;   //!
   //TBranch        *b_etaSC;   //!
   TBranch        *b_Weight;   //!

   Zlumi(TTree *tree=0);
   virtual ~Zlumi();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Zlumi_cxx
Zlumi::Zlumi(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

	   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(datafile.c_str());
	   if (!f) {
		   f = new TFile(datafile.c_str());
		   std::string fake = datafile;
		   fake = fake + ":/" + dirname;
		   f->cd(fake.c_str());
	   }
	   tree = (TTree*)gDirectory->Get("treeVJ_");

   }
   Init(tree);
}

Zlumi::~Zlumi()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Zlumi::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Zlumi::LoadTree(Long64_t entry)
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

void Zlumi::Init(TTree *tree)
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
   IsoTrkEE_PUR = 0;
   IsoEcalEE_PUR = 0;
   IsoHcalEE_PUR = 0;
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
   Rho = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("IsoTrkEB_PUR", &IsoTrkEB_PUR, &b_IsoTrkEB_PUR);
   fChain->SetBranchAddress("IsoEcalEB_PUR", &IsoEcalEB_PUR, &b_IsoEcalEB_PUR);
   fChain->SetBranchAddress("IsoHcalEB_PUR", &IsoHcalEB_PUR, &b_IsoHcalEB_PUR);
   fChain->SetBranchAddress("IsoTrkEE_PUR", &IsoTrkEE_PUR, &b_IsoTrkEE_PUR);
   fChain->SetBranchAddress("IsoEcalEE_PUR", &IsoEcalEE_PUR, &b_IsoEcalEE_PUR);
   fChain->SetBranchAddress("IsoHcalEE_PUR", &IsoHcalEE_PUR, &b_IsoHcalEE_PUR);
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
   fChain->SetBranchAddress("etaSC", &etaSC, &b_etaSC);
   fChain->SetBranchAddress("Dcot", &Dcot, &b_Dcot);
   fChain->SetBranchAddress("Dist", &Dist, &b_Dist);
   fChain->SetBranchAddress("NumberOfExpectedInnerHits", &NumberOfExpectedInnerHits, &b_NumberOfExpectedInnerHits);
   fChain->SetBranchAddress("Rho", &Rho, &b_Rho);
   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("LS", &LS, &b_LS);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("numberOfVertices", &numberOfVertices, &b_numberOfVertices);
   fChain->SetBranchAddress("etaSC", &etaSC, &b_etaSC);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   Notify();
}

Bool_t Zlumi::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Zlumi::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Zlumi::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Zlumi_cxx
