/**********************************
* Observables for Z+jet analysis *
 *                                *
 * Vieri Candelise March 2012     *
 * Matteo Marone
 **********************************
 *********************************/


#if !defined(__CINT__) || defined(__MAKECINT__)

#define Observables_cxx


#include "Observables.h"
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
#include "TLorentzVector.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include "TLatex.h"
#include <vector>
#include <iostream>
#include <TMath.h>
#include <TProfile.h>
#include "tdrStyle.C"
#include <TROOT.h>
#include "TObject.h"
#include <iostream>
#include <sstream>
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "THStack.h"
#include <string.h>
#include "Unfolding/NewUnfolding/getEfficiencyCorrection.C"
#include "Unfolding/NewUnfolding/getMuscleFitCorrection.C"


using
std::cout;
using
std::endl;	



#endif

//Andrea: ele girati con 2_28 , mu girati con 2_33 MU
bool activateScaleFactors=true;  // Correct for the difference MC/Data in the background
bool isMu=true;
bool combineChannel=false;

//string efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011Mu_v2_30.root";
string efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011_v2_41_MCtemplate.root";

/* Interesting Z + jet distributions */


TLorentzVector E1, E2, Z;
TLorentzVector J1, J2, JJ;

//Important parameters
double jetThreshold=30.0;
bool evalDiffCS=false; // if false it does not divide for # of Zs

// Files to be saved
string dir="/gpfs/cms/data/2011/Observables/Approval/";
//string dir="/tmp/";

const double asymmetricRangeLeadingJetPt[18]={30,50,70,90,110,130,150,170,190,210,230,250,280,310,350,400,500,700};

TFile *w;
//List of observables to show
TH1F *NData             = new TH1F ("Jet_multi", "Jet_multi", 8, 0.5, 8.5);
TH1F *NDataIncl             = new TH1F ("Jet_multiIncl", "Jet_multiIncl", 8, 0.5, 8.5);
TH1F *Ht                = new TH1F ("HT", "HT", 47, 30, 500);
TH1F *Ht_1j                = new TH1F ("HT_1j", "HT_1j", 17, 30, 710);
TH1F *Ht_2j                = new TH1F ("HT_2j", "HT_2j", 13, 60, 710);
TH1F *Ht_3j                = new TH1F ("HT_3j", "HT_3j", 14, 90, 790);
TH1F *Ht_4j                = new TH1F ("HT_4j", "HT_4j", 10, 120, 720);
TH1F *Dphi_12           = new TH1F ("Dphi_12", "Dphi_12", 25, 0, TMath::Pi());
TH1F *Dphi_13           = new TH1F ("Dphi_13", "Dphi_13", 25, 0, TMath::Pi());
TH1F *Dphi_23           = new TH1F ("Dphi_23", "Dphi_23", 25, 0, TMath::Pi());
TH1F *Dphi_ZJ1          = new TH1F ("Dphi_ZJ1", "Dphi_ZJ2", 25, 0, TMath::Pi());
TH1F *Dphi_ZJ2          = new TH1F ("Dphi_ZJ2", "Dphi_ZJ2", 25, 0, TMath::Pi());
TH1F *Dphi_ZJ3          = new TH1F ("Dphi_ZJ3", "Dphi_ZJ3", 25, 0, TMath::Pi());
TH1F *Dphi_all_Zlead    = new TH1F ("Dphi_all_Zlead", "Dphi_all_Zlead", 6, 0, 6.3);
TH1F *Dphi_all_notZlead = new TH1F ("Dphi_all_notZlead", "Dphi_all_notZlead", 6, 0, 6.3);
TH1F *ele_pT	        = new TH1F ("ele_pT", "ele_pT", 50, 0, 250);
TH1F *ele_eta	        = new TH1F ("ele_eta", "ele_eta", 20, -3, 3);
TH1F *ele_phi	        = new TH1F ("ele_phi", "ele_phi", 20, 0, 6);
//TH1F *jet_pT	        = new TH1F ("jet_pT", "jet_pT", 18, 30, 390);
TH1F *jet_pT	        = new TH1F ("jet_pT", "jet_pT",17,asymmetricRangeLeadingJetPt);
TH1F *jet_pT2	        = new TH1F ("jet_pT2", "jet_pT2", 15, 30, 330);
TH1F *jet_pT3	        = new TH1F ("jet_pT3", "jet_pT3", 8, 30, 190);
TH1F *jet_pT4	        = new TH1F ("jet_pT4", "jet_pT4", 5, 30, 130);
TH1F *jet_eta	        = new TH1F ("jet_eta", "jet_eta", 24, -2.4, 2.4);
TH1F *jet_eta2	        = new TH1F ("jet_eta2", "jet_eta2", 20, -2.4, 2.4);
TH1F *jet_eta3	        = new TH1F ("jet_eta3", "jet_eta3", 16, -2.4, 2.4);
TH1F *jet_eta4	        = new TH1F ("jet_eta4", "jet_eta4", 12, -2.4, 2.4);
TH1F *Z_pT		= new TH1F ("Z_pT", "Z_pT", 50, 30, 500);
TH1F *dijet_mass	= new TH1F ("dijet_mass", "dijet_mass", 10, 400, 600);
TH1F *Zjj_mass	        = new TH1F ("Zjj_mass", "Zjj_mass", 10, 400, 600);
TH1F *Theta_JZ	        = new TH1F ("Theta_JZ", "Theta_JZ", 100, -1, 1);
TH1F *Phi_star	        = new TH1F ("Phi_star", "Phi_star", 25, 0, 6.5);
TH1F *Phi_star_xs	= new TH1F ("Phi_star_xs", "(1/ #sigma) d #sigma / d#phi^{*}", 25, 0, 6.5);
TH2F *HZ		= new TH2F ("HZ", "HZ", 100, 30, 1000, 500, 0, 1000);
TH2F *NZ		= new TH2F ("NZ", "NZ", 5, 0.5, 5.5, 500, 0, 1000);
TH2F *HN		= new TH2F ("HN", "HN", 5, 0.5, 5.5, 100, 30, 1000);
TH2F *NZy		= new TH2F ("NZy", "NZy", 5, 0.5, 5.5, 30, -3, 3);
//Storing weights
TH1F  *h_weights        = new TH1F ("h_weights","Event Weights",500,0.,5);
TH1F  *h_invMass        = new TH1F ("h_invMass","L-L Invariant Mass Distribution",40,71.,111.);

bool isJetTooCloseToLeptons(double jet_eta, double jet_phi, double lepton1_eta, double lepton1_phi, double lepton2_eta, double lepton2_phi, double maxDRAllowed) 
{
  //Check if the DR jet_i Vs lepton_1,2 is < 0.5. 
  
  double delta_phi_l1 = fabs( lepton1_phi - jet_phi);
  double delta_phi_l2 = fabs( lepton2_phi - jet_phi);
  double delta_eta_l1 = lepton1_eta - jet_eta;
  double delta_eta_l2 = lepton2_eta - jet_eta;
  
  if (delta_phi_l1 > acos(-1)) delta_phi_l1 = 2*acos(-1) - delta_phi_l1;
  if (delta_phi_l2 > acos(-1)) delta_phi_l2 = 2*acos(-1) - delta_phi_l2;
  
  double deltaR1 = sqrt( pow(delta_eta_l1,2) + pow(delta_phi_l1,2) );
  double deltaR2 = sqrt( pow(delta_eta_l2,2) + pow(delta_phi_l2,2) );

  if (deltaR1<maxDRAllowed || deltaR2 <maxDRAllowed) return false;
  return true;
}

void
Observables::Loop()
{
  double numbOfZ = 0;
  double numbOfZPlus1 = 0;
  double numbOfZPlus2 = 0;
  double numbOfZPlus3 = 0;
  double numbOfZPlus4 = 0;

  string version="_v2_58.root";
 string versionMu=version;
 if (isMu) {
   versionMu="Mu"+version;
 }
 version=versionMu;
 if (!isMu){
   //version="_v2_30.root"; 
   //efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011_v2_28.root";
   efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011_v2_41_MCtemplate.root";
 }
 cout<<"#########################"<<endl;
 cout<<"You're using"<<endl;
 cout<<version<<endl;
 cout<<efffile<<endl;
 cout<<"isMu->"<<isMu<<endl;
 cout<<"#########################"<<endl;

//Open MC and data files to retrieve effciencies
TFile *fAeff = new TFile (efffile.c_str());// WHY 2 FILES? DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
TFile *fBeff = new TFile (efffile.c_str()); 


string szj=dir+"MC_zjets"+versionMu;
string swj=dir+"MC_wjets"+versionMu;
string stt=dir+"MC_ttbar"+versionMu;
string sWW=dir+"MC_diW"+versionMu;
string sZZ=dir+"MC_siZ"+versionMu;
string sWZ=dir+"MC_diWZ"+versionMu;
string sda=dir+"DATA"+versionMu;
string szjtau=dir+"MC_zjetstau"+versionMu;

TFile* fzj = new TFile(szj.c_str(), "RECREATE");
TFile* fwj = new TFile(swj.c_str(), "RECREATE");
TFile* ftt = new TFile(stt.c_str(), "RECREATE");
TFile* fWW = new TFile(sWW.c_str(), "RECREATE");
TFile* fZZ = new TFile(sZZ.c_str(), "RECREATE");
TFile* fWZ = new TFile(sWZ.c_str(), "RECREATE");
TFile* fda = new TFile(sda.c_str(), "RECREATE");
TFile* fzjtau = new TFile(szjtau.c_str(), "RECREATE");

 string dirvalidation="validationJEC";
 if (isMu && !combineChannel) dirvalidation="validationJECmu";

 
 TDirectory *validationJECz=fzj->mkdir(dirvalidation.c_str());
 TDirectory *validationJECw=fwj->mkdir(dirvalidation.c_str());
TDirectory *validationJECtt=ftt->mkdir(dirvalidation.c_str());
 TDirectory *validationJECWW=fWW->mkdir(dirvalidation.c_str());
TDirectory *validationJECZZ=fZZ->mkdir(dirvalidation.c_str());
TDirectory *validationJECWZ=fWZ->mkdir(dirvalidation.c_str());
TDirectory *validationJECda=fda->mkdir(dirvalidation.c_str());
 TDirectory *validationJECztau=fzjtau->mkdir(dirvalidation.c_str());
//FIles do be opened

string diropen="/gpfs/cms/data/2011/jet/jetValidation_";
 string sozj=diropen+"zjets_magd_2011Mu_v2_58.root";
string sowj=diropen+"w_2011Mu"+"_v2_33.root";//+version;
string soda=diropen+"DATA_2011"+versionMu;

//Decomment once bkg are ready
string sott=diropen+"ttbar_2011Mu_v2_58.root";
string soWW=diropen+"ww_2011Mu_v2_58.root";
string soZZ=diropen+"zz_2011Mu_v2_58.root";
string soWZ=diropen+"wz_2011Mu_v2_58.root";

//string sott=diropen+"ttbar_2011Mu_v2_32.root";                                                                                                                         
//string soWW=diropen+"ww_2011Mu_v2_32.root";                                                                                                                            
//string soZZ=diropen+"zz_2011Mu_v2_32.root";                                                                                                                            
//string soWZ=diropen+"wz_2011Mu_v2_32.root";

 string sozjtau=diropen+"zjets_magd_2011Mu_v2_58.root";

 string sodzj=sozj+":/EPTmuoReco_MC";
 string sodwj=sowj+":/EPTmuoReco_MC";
 string sodtt=sott+":/EPTmuoReco_MC";
 string sodWW=soWW+":/EPTmuoReco_MC";
 string sodZZ=soZZ+":/EPTmuoReco_MC";
 //if (isMu) sodWW=soWW+":/EPTmuoReco_MC";
 
 string sodWZ=soWZ+":/EPTmuoReco_MC";
 string sodda=soda+":/validationJEC";
 string sodzjtau=sozjtau+":/EPTmuoReco_MC";

 if (isMu) sodda=soda+":/EPTmuoReco";

TFile *Fzj = new TFile (sozj.c_str());
TFile *Fwj = new TFile (sowj.c_str());
TFile *Ftt = new TFile (sott.c_str());
TFile *Fda = new TFile (soda.c_str());
TFile *FWW = new TFile (soWW.c_str());
TFile *FWZ = new TFile (soWZ.c_str());
TFile *FZZ = new TFile (soZZ.c_str());
TFile *Fzjtau = new TFile (sozjtau.c_str());
 
 cout<<"-----------Directories------------------"<<endl;
 cout<<sodda<<endl;
 cout<<sodzj<<endl;
 cout<<sodtt<<endl;
 cout<<sodWW<<endl;
 cout<<sodWZ<<endl;
 cout<<sodZZ<<endl;
 cout<<sodwj<<endl;
 cout<<sodzjtau<<endl;

  cout<<"If you see an unexpected crash, control in which gDyrectory the tree treeUN has been stored.."<<endl;
  //DATA
  for(int i=0; i<8; i++){
    if (i==0) fda->cd (sodda.c_str());
    if (i==1) fzj->cd (sodzj.c_str());
    if (i==2) ftt->cd (sodtt.c_str());
    if (i==3) fWW->cd (sodWW.c_str());
    if (i==4) fWZ->cd (sodWZ.c_str());
    if (i==5) fZZ->cd (sodZZ.c_str());
    if (i==6) fwj->cd (sodwj.c_str());
    if (i==7) fzjtau->cd (sodzjtau.c_str());

    cout<<"Act #"<<i<<endl;

    TTree *tree_fB;
    if (!isMu){
      if (i==0)tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");
      if (i==1)tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");      
      //if (i>1) tree_fB = (TTree *) gDirectory->Get ("treeUN_");
      if (i==2) tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");      
      if (i==3) tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");      
      if (i==4) tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");      
      if (i==5) tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");      
      //if (i==2) tree_fB = (TTree *) gDirectory->Get ("treeUN_");
      //if (i==3) tree_fB = (TTree *) gDirectory->Get ("treeUN_");
      //if (i==4) tree_fB = (TTree *) gDirectory->Get ("treeUN_");
      //if (i==5) tree_fB = (TTree *) gDirectory->Get ("treeUN_");
      if (i==6) tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");      
      if (i==7)tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");      
    }
    else{
      if (i==0)tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");     
      if (i==1)tree_fB = (TTree *) gDirectory->Get ("treeValidationJECMu_");

      //if (i>=1) tree_fB = (TTree *) gDirectory->Get ("treeUNmu_");
      if (i==2 && isMu)tree_fB = (TTree *) gDirectory->Get ("treeValidationJECMu_");
      if (i==3 && isMu)tree_fB = (TTree *) gDirectory->Get ("treeValidationJECMu_");
      if (i==4 && isMu)tree_fB = (TTree *) gDirectory->Get ("treeValidationJECMu_");
      if (i==5 && isMu)tree_fB = (TTree *) gDirectory->Get ("treeValidationJECMu_");
      if (i==6 && isMu)tree_fB = (TTree *) gDirectory->Get ("treeValidationJECMu_");
      if (i==7 && isMu)tree_fB = (TTree *) gDirectory->Get ("treeValidationJECMu_");
    }
    

    fChain = tree_fB;		/* Loop RunA */
    Init (fChain); 
    
    Long64_t nentries = fChain->GetEntriesFast ();

    Long64_t nbytes = 0, nb = 0;
    
    if (fChain == 0)  return;
    
    //List of observables to show
    NData             = new TH1F ("Jet_multi", "Jet_multi", 8, 0.5, 8.5);
    NDataIncl             = new TH1F ("Jet_multiIncl", "Jet_multiIncl", 8, 0.5, 8.5);
    Ht                = new TH1F ("HT", "HT", 47, 30, 500);
    Ht_1j                = new TH1F ("HT_1j", "HT_1j", 17, 30, 710);
    Ht_2j                = new TH1F ("HT_2j", "HT_2j", 13, 60, 710);
    Ht_3j                = new TH1F ("HT_3j", "HT_3j", 14, 90, 790);
    Ht_4j                = new TH1F ("HT_4j", "HT_4j", 10, 120, 720);

    Dphi_12           = new TH1F ("Dphi_12", "Dphi_12", 25, 0, TMath::Pi());
    Dphi_13           = new TH1F ("Dphi_13", "Dphi_13", 25, 0, TMath::Pi());
    Dphi_23           = new TH1F ("Dphi_23", "Dphi_23", 25, 0, TMath::Pi());
    Dphi_ZJ1          = new TH1F ("Dphi_ZJ1", "Dphi_ZJ2", 25, 0, TMath::Pi());
    Dphi_ZJ2          = new TH1F ("Dphi_ZJ2", "Dphi_ZJ2", 25, 0, TMath::Pi());
    Dphi_ZJ3          = new TH1F ("Dphi_ZJ3", "Dphi_ZJ3", 25, 0, TMath::Pi());
    Dphi_all_Zlead    = new TH1F ("Dphi_all_Zlead", "Dphi_all_Zlead", 6, 0, 6.3);
    Dphi_all_notZlead = new TH1F ("Dphi_all_notZlead", "Dphi_all_notZlead", 6, 0, 6.3);
    ele_pT	    = new TH1F ("ele_pT", "ele_pT", 50, 0, 250);
    ele_eta	    = new TH1F ("ele_eta", "ele_eta", 20, -3, 3);
    ele_phi	    = new TH1F ("ele_phi", "ele_phi", 20, 0, 6);
    //jet_pT	    = new TH1F ("jet_pT", "jet_pT", 18, 30, 390);
    jet_pT	    = new TH1F ("jet_pT", "jet_pT",17,asymmetricRangeLeadingJetPt);
    jet_pT2	    = new TH1F ("jet_pT2", "jet_pT2", 15, 30, 330);
    jet_pT3	    = new TH1F ("jet_pT3", "jet_pT3", 8, 30, 190);
    jet_pT4	    = new TH1F ("jet_pT4", "jet_pT4", 5, 30, 130);
    jet_eta	    = new TH1F ("jet_eta", "jet_eta", 24, -2.4, 2.4);
    jet_eta2	    = new TH1F ("jet_eta2", "jet_eta2", 20, -2.4, 2.4);
    jet_eta3	    = new TH1F ("jet_eta3", "jet_eta3", 16, -2.4, 2.4);
    jet_eta4	    = new TH1F ("jet_eta4", "jet_eta4", 12, -2.4, 2.4);
    Z_pT	    = new TH1F ("Z_pT", "Z_pT", 50, 30, 500);
    dijet_mass	    = new TH1F ("dijet_mass", "dijet_mass", 10, 400, 600);
    Zjj_mass	    = new TH1F ("Zjj_mass", "Zjj_mass", 10, 400, 600);
    Theta_JZ	    = new TH1F ("Theta_JZ", "Theta_JZ", 100, -1, 1);
    Phi_star	    = new TH1F ("Phi_star", "Phi_star", 25, 0, 6.5);
    Phi_star_xs	    = new TH1F ("(1/ #sigma) d #sigma / d#phi^{*}", "(1/ #sigma) d #sigma / d#phi^{*}", 25, 0, 6.5);
    HZ		    = new TH2F ("HZ", "HZ", 100, 30, 1000, 500, 0, 1000);
    NZ		    = new TH2F ("NZ", "NZ", 5, 0.5, 5.5, 500, 0, 1000);
    HN		    = new TH2F ("HN", "HN", 5, 0.5, 5.5, 100, 30, 1000);
    NZy		    = new TH2F ("NZy", "NZy", 5, 0.5, 5.5, 30, -3, 3);
    h_weights       = new TH1F ("h_weights","h_weights",500,0.,5);
    h_invMass       = new TH1F ("h_invMass","h_invMass",40,71.,111.);

    Ht_1j->SetStats(0);
    Ht_2j->SetStats(0);
    Ht_3j->SetStats(0);
    Ht_4j->SetStats(0);
    jet_pT->SetStats(0);
    jet_pT2->SetStats(0);
    jet_pT3->SetStats(0);
    jet_pT4->SetStats(0);
    jet_eta->SetStats(0);
    jet_eta2->SetStats(0);
    jet_eta3->SetStats(0);
    jet_eta4->SetStats(0);
    NData->SetStats(0);
    NDataIncl->SetStats(0);
    h_invMass->SetStats(0);

    //Making the plots
    for (Long64_t jentry = 0; jentry < nentries; jentry++)
      {
	Long64_t ientry = LoadTree (jentry);
	if (ientry < 0)
	  break;
	nb = fChain->GetEntry (jentry);
	nbytes += nb;
	
	// Cure angular phi ambiguities : Dphi > pi
	/*if(Jet_multiplicity > 10 || Jet_multiplicity <=0 || jet1_pt<=0 || jet1_pt > 1000 || jet2_pt > 1000 || Z_y >3 || Z_y <-3) continue;*/
	if (i==7 && !isTaugen) continue;
	E1.SetPtEtaPhiM(e1_pt, e1_eta, e1_phi, 0);
	E2.SetPtEtaPhiM(e2_pt, e2_eta, e2_phi, 0);
	Z = (E1+E2);
	J1.SetPtEtaPhiM(jet1_pt, jet1_eta, jet1_phi, jet1_mass);
	J2.SetPtEtaPhiM(jet2_pt, jet2_eta, jet2_phi, jet2_mass);
	JJ = (J1+J2);
	
	double ZJJ = (JJ+Z).M();
	double MJJ =  JJ.M();
	double Z_phi = Z.Phi();
	double Dphi12 = TMath::Abs(jet2_phi - jet1_phi);
	double Dphi13 = TMath::Abs(jet3_phi - jet1_phi);
	double Dphi23 = TMath::Abs(jet3_phi - jet2_phi);
	double DphiZJ1 = TMath::Abs(jet1_phi - Z_phi);
	double DphiZJ2 = TMath::Abs(jet2_phi - Z_phi);
	double DphiZJ3 = TMath::Abs(jet3_phi - Z_phi);
	double theta_J1  = -2 * TMath::ATan(-TMath::Exp((jet1_eta)));
	double theta_Z   = -2 * TMath::ATan(-TMath::Exp((Z_y)));
	double theta_JZ  = theta_J1 + theta_Z;
	double phi_A = TMath::Pi() - TMath::Abs(e1_phi - e2_phi);
	double theta_star_eta = TMath::ACos(TMath::ATanH(0.5*(e1_eta - e2_eta))); //scattering angle of the leptons with respect to 
	//the dilepton system
	
	double phi_star = TMath::Sin(theta_star_eta)*TMath::Tan(0.5*phi_A);
	
	if(Dphi12 > TMath::Pi())  Dphi12 = 2*TMath::Pi() - Dphi12;
	if(Dphi13 > TMath::Pi())  Dphi13 = 2*TMath::Pi() - Dphi13;
	if(Dphi23 > TMath::Pi())  Dphi23 = 2*TMath::Pi() - Dphi23;
	if(DphiZJ1 > TMath::Pi())  DphiZJ1 = 2*TMath::Pi() - DphiZJ1;
	if(DphiZJ2 > TMath::Pi())  DphiZJ2 = 2*TMath::Pi() - DphiZJ2;
	if(DphiZJ3 > TMath::Pi())  DphiZJ3 = 2*TMath::Pi() - DphiZJ3;
	
	double Dphi_event = Dphi12 + Dphi13 + Dphi23;

	////////////////      
	/* Fill histos */
	////////////////

	//Fill all the weights
	h_weights->Fill(evWeight);


	/* Old method
	//Evaluate how close are the jets to electrons!
	bool isGoodJet1=true;
	bool isGoodJet2=true;
	bool isGoodJet3=true;
	bool isGoodJet4=true;

	if (Jet_multiplicity>=1) isGoodJet1=isJetTooCloseToLeptons(jet1_eta, jet1_phi, e1_eta, e1_phi, e2_eta, e2_phi, 0.5); 
	if (Jet_multiplicity>=2) isGoodJet2=isJetTooCloseToLeptons(jet2_eta, jet2_phi, e1_eta, e1_phi, e2_eta, e2_phi, 0.5); 
	if (Jet_multiplicity>=3) isGoodJet3=isJetTooCloseToLeptons(jet3_eta, jet3_phi, e1_eta, e1_phi, e2_eta, e2_phi, 0.5); 
	if (Jet_multiplicity>=4) isGoodJet4=isJetTooCloseToLeptons(jet4_eta, jet4_phi, e1_eta, e1_phi, e2_eta, e2_phi, 0.5); 

	if (!isGoodJet1 || !isGoodJet2 || !isGoodJet3 || !isGoodJet4) continue;
	*/

	//if (isAnyJetTooCloseToLepton) continue;

	//Ci va qualcosa che prende tutti i jets e la jetMulti, li valuta uno per uno e li scargnassa via se e' il caso

	double multiweight=1.0*evWeight;
	if (i>0 && activateScaleFactors) {
	  if (isMu) {
	    bool is2011A=false;
	    //if (run<180000) is2011A=true;
	    //double effMC=getEfficiencyMuonPOG(is2011A , true, e1_pt ,e1_eta, e2_pt, e2_eta);
	    //double effData=getEfficiencyMuonPOG(is2011A , false, e1_pt ,e1_eta, e2_pt ,e2_eta);
	    multiweight=getSfMuonPOG(is2011A,e1_pt ,e1_eta, e2_pt, e2_eta);
	  }
	  if (!isMu) {
	    //double SF=getSfEGammaPOG(e1_pt ,e1_eta, e2_pt , e2_eta);
	    //double effData=getEfficiencyCorrectionPtUsingElectron(fAeff, e1_pt , e1_eta, e2_pt, e2_eta, "data");
	    //double effMC=getEfficiencyCorrectionPtUsingElectron(fAeff, e1_pt , e1_eta, e2_pt, e2_eta, "MC");
	    multiweight=getSfEGammaPOG(e1_pt ,e1_eta, e2_pt, e2_eta,false,false)*getScaleFactorPtUsingElectron(fAeff,e1_pt ,e1_eta, e2_pt, e2_eta);
	  }
	}

	NData->Fill(Jet_multiplicity,multiweight);
	for (int k=1;k<=Jet_multiplicity;k++){
	  if (Jet_multiplicity<9) NDataIncl->Fill(k,multiweight);
	}
	h_invMass->Fill(Z.M(),multiweight);

	///////////////////
	///  HT, inclusive pt,eta and phi
	/////////////////// 

	
	//NON APPLICO ANCORA I SCALE FACTORS
	ele_pT   ->Fill(e1_pt,multiweight);
	ele_eta  ->Fill(e1_eta,multiweight);
	ele_phi  ->Fill(e1_phi,multiweight);


	///////////////////
	///  jet pt/eta spectra, up to 4
	/////////////////// 

	//NB!!!!!!!!!!!!!!!!!!!!!! -> Non considero il weight perche' lo considero poi in DrawComparison!!!!!!!!!!!!!!!!!!!!!

	if(jet1_pt>jetThreshold && jet1_pt<7000 && jet1_eta>-3 && jet1_eta<3){	
	  jet_pT  -> Fill(jet1_pt,multiweight);
	  jet_eta -> Fill(jet1_eta,multiweight);
	}

	///////

	if (Jet_multiplicity > 1 && jet2_pt > jetThreshold && jet2_pt <350 && TMath::Abs(jet2_eta)<2.5){
	  jet_pT2 -> Fill(jet2_pt,multiweight);
	  jet_eta2 -> Fill(jet2_eta,multiweight);
	}

	///////
	
	if (Jet_multiplicity > 2 && jet3_pt > jetThreshold && jet3_pt <350 && TMath::Abs(jet3_eta)<2.5){
	  jet_pT3 -> Fill(jet3_pt,multiweight);
	  jet_eta3 -> Fill(jet3_eta,multiweight);
	}

	///////

	
	if (Jet_multiplicity > 3 && jet4_pt > jetThreshold && jet4_pt <350 && TMath::Abs(jet4_eta)<2.5){
	  jet_pT4 -> Fill(jet4_pt,multiweight);
	  jet_eta4 -> Fill(jet4_eta,multiweight);
	}
	

	double jetHtCalculated=0;
	
	if (Jet_multiplicity>0 && jet1_pt>30 && jet1_pt<7000) jetHtCalculated+=jet1_pt;
	if (Jet_multiplicity>1 && jet2_pt>30 && jet2_pt<7000) jetHtCalculated+=jet2_pt;
	if (Jet_multiplicity>2 && jet3_pt>30 && jet3_pt<7000) jetHtCalculated+=jet3_pt;
	if (Jet_multiplicity>3 && jet4_pt>30 && jet4_pt<7000) jetHtCalculated+=jet4_pt;
	if (Jet_multiplicity>4 && jet5_pt>30 && jet5_pt<7000) jetHtCalculated+=jet5_pt;
	if (Jet_multiplicity>5 && jet6_pt>30 && jet6_pt<7000) jetHtCalculated+=jet6_pt;

	

	if(Jet_multiplicity>0) {
	  Ht->Fill(jetHt,multiweight);
	  if (Jet_multiplicity>0) Ht_1j->Fill(jetHtCalculated,multiweight);
	  if (Jet_multiplicity>1) Ht_2j->Fill(jetHtCalculated,multiweight);
	  if (Jet_multiplicity>2) Ht_3j->Fill(jetHtCalculated,multiweight);
	  if (Jet_multiplicity>3) Ht_4j->Fill(jetHtCalculated,multiweight);
	}

	///////////////////
	///  Z Boson, Ht and angles and other
	/////////////////// 
	
	
	Z_pT     ->Fill(Z_pt,multiweight);
	HZ       ->Fill(Z_pt, jetHt,multiweight);
	HN       ->Fill(Jet_multiplicity, jetHt,multiweight);
	NZ       ->Fill(Jet_multiplicity, Z_pt,multiweight);
	NZy      ->Fill(Jet_multiplicity, Z_y,multiweight);
	if (Jet_multiplicity >  0) Dphi_12  ->Fill(Dphi12,multiweight);
	if (Jet_multiplicity >  2) Dphi_13  ->Fill(Dphi13,multiweight);
	if (Jet_multiplicity >  2) Dphi_23  ->Fill(Dphi23,multiweight);
	
	if (Jet_multiplicity >  0) Dphi_ZJ1 ->Fill(DphiZJ1,multiweight);
	if (Jet_multiplicity >  1) Dphi_ZJ2 ->Fill(DphiZJ2,multiweight);
	if (Jet_multiplicity >  2) Dphi_ZJ3 ->Fill(DphiZJ3,multiweight);
	
	if (Jet_multiplicity >  1) dijet_mass ->Fill(MJJ,multiweight); 
	if (Jet_multiplicity >  1) Zjj_mass ->Fill(ZJJ,multiweight); 
	
	if (Jet_multiplicity >  0) Phi_star->Fill(phi_star,multiweight);
	
	double sigma = Phi_star -> GetEntries();
	Phi_star_xs -> Fill(phi_star/sigma,multiweight);
	
	if (Jet_multiplicity >= 3){
	  if (Z_pt > jet1_pt && jet1_pt > jet2_pt) {
	    Dphi_all_Zlead -> Fill(Dphi_event,multiweight);	
	  }else if((jet1_pt > Z_pt && Z_pt > jet2_pt) || (jet1_pt > jet2_pt && jet2_pt > Z_pt)) { 
	    Dphi_all_notZlead -> Fill(Dphi_event,multiweight);
	  }
	}
	
	if(Z_pt != 0 && Jet_multiplicity > 0){
	  Theta_JZ->Fill(TMath::Cos(theta_JZ),multiweight);  
	}
	
      }
    
    //Get the number of Z bosons in data
    if (i<8)  {
      numbOfZ = NData->GetEntries();
      cout<<"Data contains # Z ->"<<numbOfZ<<endl;
      numbOfZPlus1 = NData->GetBinContent(2)+NData->GetBinContent(3)+NData->GetBinContent(4)+NData->GetBinContent(5)+NData->GetBinContent(6)+NData->GetBinContent(7)+NData->GetBinContent(8)+NData->GetBinContent(9);
      numbOfZPlus2 = NData->GetBinContent(3)+NData->GetBinContent(4)+NData->GetBinContent(5)+NData->GetBinContent(6)+NData->GetBinContent(7)+NData->GetBinContent(8)+NData->GetBinContent(9);
      numbOfZPlus3 = NData->GetBinContent(4)+NData->GetBinContent(5)+NData->GetBinContent(6)+NData->GetBinContent(7)+NData->GetBinContent(8)+NData->GetBinContent(9);
      numbOfZPlus4 = NData->GetBinContent(5)+NData->GetBinContent(6)+NData->GetBinContent(7)+NData->GetBinContent(8)+NData->GetBinContent(9);
      cout<<"Data contains # Z >= 1 Jets ->"<<numbOfZPlus1<<endl;
      cout<<"Data contains # Z >= 2 Jets ->"<<numbOfZPlus2<<endl;
      cout<<"Data contains # Z >= 3 Jets ->"<<numbOfZPlus3<<endl;
      cout<<"Data contains # Z >= 4 Jets ->"<<numbOfZPlus4<<endl;
    }
    
    jet_pT2    ->Sumw2();
    jet_pT     ->Sumw2();
    jet_pT3    ->Sumw2();
    jet_pT4    ->Sumw2();
    jet_eta    ->Sumw2();
    jet_eta2   ->Sumw2();
    jet_eta3   ->Sumw2();
    jet_eta4   ->Sumw2();
    Ht         ->Sumw2();
    Ht_1j         ->Sumw2();
    Ht_2j         ->Sumw2();
    Ht_3j         ->Sumw2();
    Ht_4j         ->Sumw2();
    Dphi_12    ->Sumw2();
    Dphi_ZJ1   ->Sumw2();
    Dphi_ZJ2   ->Sumw2();
    Phi_star   ->Sumw2();
    
    if (evalDiffCS){
      jet_eta    ->Scale(1./numbOfZPlus1);
      jet_eta2   ->Scale(1./numbOfZPlus2);
      jet_eta3   ->Scale(1./numbOfZPlus3);
      jet_eta4   ->Scale(1./numbOfZPlus4);
      jet_pT2    ->Scale(1./numbOfZPlus2);
      jet_pT     ->Scale(1./numbOfZPlus1);
      jet_pT3    ->Scale(1./numbOfZPlus3);
      jet_pT4    ->Scale(1./numbOfZPlus4);
      Ht         ->Scale(1./numbOfZ);
      Dphi_12    ->Scale(1./numbOfZ);
      Dphi_ZJ1   ->Scale(1./numbOfZ);
      Dphi_ZJ2   ->Scale(1./numbOfZ);
      Phi_star   ->Scale(1./numbOfZ);
    }
    
    dijet_mass -> GetXaxis() -> SetTitle("M_{jj} [GeV/c^{2}]");
    Zjj_mass   -> GetXaxis() -> SetTitle("M_{Zjj} [GeV/c^{2}]");
    NData    -> GetXaxis() -> SetTitle("Jet multiplicity");  
    NDataIncl    -> GetXaxis() -> SetTitle("Jet multiplicity");  
    Ht       -> GetXaxis() -> SetTitle("H_{T} [GeV]"); 
    Ht_1j       -> GetXaxis() -> SetTitle("H_{T} [GeV]"); 
    Ht_2j       -> GetXaxis() -> SetTitle("H_{T} [GeV]");
    Ht_3j       -> GetXaxis() -> SetTitle("H_{T} [GeV]");
    Ht_4j       -> GetXaxis() -> SetTitle("H_{T} [GeV]");
    ele_pT   -> GetXaxis() -> SetTitle("Leading electron p_{T} [GeV/c]");        
    ele_eta  -> GetXaxis() -> SetTitle("Leading electron #eta");
    ele_phi  -> GetXaxis() -> SetTitle("Leading electron #phi");
    jet_pT -> GetXaxis() -> SetTitle("Leading jet p_{T} [GeV]");
    jet_pT2   -> GetXaxis() -> SetTitle("2^{nd} jet p_{T} [GeV]");
    jet_pT3   -> GetXaxis() -> SetTitle("3^{rd} jet p_{T} [GeV]");
    jet_pT4   -> GetXaxis() -> SetTitle("4^{th} jet p_{T} [GeV]");
    jet_eta -> GetXaxis() -> SetTitle("Leading jet #eta ");
    jet_eta2   -> GetXaxis() -> SetTitle("2^{nd} jet #eta ");
    jet_eta3   -> GetXaxis() -> SetTitle("3^{rd} jet #eta ");
    jet_eta4   -> GetXaxis() -> SetTitle("4^{th} jet #eta ");
    Z_pT     -> GetXaxis() -> SetTitle("Z boson p_{T} [GeV/c]");
    HZ       -> GetXaxis() -> SetTitle("H_{T} [GeV/c]");
    HN       -> GetXaxis() -> SetTitle("H_{T} [GeV/c]");
    NZ       -> GetXaxis() -> SetTitle("Jet multiplicity");
    NZy      -> GetXaxis() -> SetTitle("Jet multiplicity");
    Dphi_12  -> GetXaxis() -> SetTitle("#Delta #phi (J_{1}, J_{2}) [rad]");
    Dphi_13  -> GetXaxis() -> SetTitle("#Delta #phi (J_{1}, J_{3}) [rad]");
    Dphi_23  -> GetXaxis() -> SetTitle("#Delta #phi (J_{2}, J_{3}) [rad]");
    Dphi_ZJ1  -> GetXaxis() -> SetTitle("#Delta #phi (Z, J_{1}) [rad]");
    Dphi_ZJ2  -> GetXaxis() -> SetTitle("#Delta #phi (Z, J_{2})");
    Dphi_ZJ3  -> GetXaxis() -> SetTitle("#Delta #phi (Z, J_{3})");
    Theta_JZ -> GetXaxis() -> SetTitle("cos(#theta_{J1,Z})");
    Phi_star_xs -> GetXaxis() -> SetTitle("#phi^{*}");
    
    NData    -> GetYaxis() -> SetTitle("Events");
    NDataIncl    -> GetYaxis() -> SetTitle("Events");
    Ht       -> GetYaxis() -> SetTitle("Events");
    Ht_1j       -> GetYaxis() -> SetTitle("Events");
    Ht_2j       -> GetYaxis() -> SetTitle("Events");
    Ht_3j       -> GetYaxis() -> SetTitle("Events");
    Ht_4j       -> GetYaxis() -> SetTitle("Events");
    ele_pT   -> GetYaxis() -> SetTitle("Events");        
    ele_eta  -> GetYaxis() -> SetTitle("Events");
    ele_phi  -> GetYaxis() -> SetTitle("Events");
    jet_pT   -> GetYaxis() -> SetTitle("Events");
    jet_pT2   -> GetYaxis() -> SetTitle("Events");
    jet_pT3   -> GetYaxis() -> SetTitle("Events");
    jet_pT4   -> GetYaxis() -> SetTitle("Events");
    jet_eta  -> GetYaxis() -> SetTitle("Events");
    jet_eta2   -> GetYaxis() -> SetTitle("Events");
    jet_eta3   -> GetYaxis() -> SetTitle("Events");
    jet_eta4   -> GetYaxis() -> SetTitle("Events");
    h_invMass   -> GetYaxis() -> SetTitle("# events");
    h_invMass   -> GetXaxis() -> SetTitle("e^{+}e^{-} invariant mass");


    if (isMu){
      h_invMass   -> GetXaxis() -> SetTitle("#mu^{+}#mu^{-} invariant mass");
      NData    -> GetYaxis() -> SetTitle("Events");
      NDataIncl    -> GetYaxis() -> SetTitle("Events");
      Ht       -> GetYaxis() -> SetTitle("Events");
    Ht_1j       -> GetYaxis() -> SetTitle("Events");
    Ht_2j       -> GetYaxis() -> SetTitle("Events");
    Ht_3j       -> GetYaxis() -> SetTitle("Events");
    Ht_4j       -> GetYaxis() -> SetTitle("Events");
    jet_pT   -> GetYaxis() -> SetTitle("Events");
    jet_pT2   -> GetYaxis() -> SetTitle("Events");
    jet_pT3   -> GetYaxis() -> SetTitle("Events");
    jet_pT4   -> GetYaxis() -> SetTitle("Events");
    jet_eta  -> GetYaxis() -> SetTitle("Events");
    jet_eta2   -> GetYaxis() -> SetTitle("Events");
    jet_eta3   -> GetYaxis() -> SetTitle("Events");
    jet_eta4   -> GetYaxis() -> SetTitle("Events");
    }
    Z_pT     -> GetYaxis() -> SetTitle("Events");
    HZ       -> GetYaxis() -> SetTitle("Z boson p_{T} [GeV/c]");
    HN       -> GetYaxis() -> SetTitle("Jet multiplicity");
    NZ       -> GetYaxis() -> SetTitle("Z boson p_{T} [GeV/c]");
    NZy      -> GetYaxis() -> SetTitle("Z boson rapidity");
    Dphi_12  -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d #Delta #phi ^{jj}");
    Dphi_13  -> GetYaxis() -> SetTitle("Events");
    Dphi_23  -> GetYaxis() -> SetTitle("Events");
    Dphi_ZJ1  -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d #Delta #phi ^{Zj}");
    Dphi_ZJ2  -> GetYaxis() -> SetTitle("Events");
    Dphi_ZJ3  -> GetYaxis() -> SetTitle("Events");
    Theta_JZ -> GetYaxis() -> SetTitle("Events");
    Phi_star -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d #phi^{*}");
    
    
    /* Save on a file */

    if(i==0){
      fda->cd();
      validationJECda->cd();
    }
    if(i==1){
      fzj->cd();
      validationJECz->cd();
    }
    if(i==2){
      ftt->cd();
      validationJECtt->cd();
    }
    if(i==3){
      fWW->cd();
      validationJECWW->cd();
    }
    if(i==4){
      fWZ->cd();
      validationJECWZ->cd();
    }
    if(i==5){
      fZZ->cd();
      validationJECZZ->cd();
    }
    if(i==6){
      fwj->cd();
      validationJECw->cd();
    } 
    if(i==7){
      fzjtau->cd();
      validationJECztau->cd();
    }

    
    Ht_1j->SetStats(0);
    Ht_2j->SetStats(0);
    Ht_3j->SetStats(0);
    Ht_4j->SetStats(0);
    jet_pT->SetStats(0);
    jet_pT2->SetStats(0);
    jet_pT3->SetStats(0);
    jet_pT4->SetStats(0);
    jet_eta->SetStats(0);
    jet_eta2->SetStats(0);
    jet_eta3->SetStats(0);
    jet_eta4->SetStats(0);
    NData->SetStats(0);
    NDataIncl->SetStats(0);

    h_weights->Write();    
    h_invMass->Write();

    dijet_mass->Write();
    Zjj_mass ->Write();       	
    Ht      ->Write("jetHt");
    Ht_1j      ->Write();
    Ht_2j      ->Write();
    Ht_3j      ->Write();
    Ht_4j      ->Write();
    ele_pT  ->Write("e1_pt");
    ele_eta ->Write("e1_eta");
    ele_phi ->Write("e1_phi");
    jet_pT  ->Write("jet1_pt");
    jet_pT2  ->Write("jet2_pt");
    jet_pT3  ->Write("jet3_pt");
    jet_pT4  ->Write("jet4_pt");
    jet_eta  ->Write("jet1_eta");
    jet_eta2  ->Write("jet2_eta");
    jet_eta3  ->Write("jet3_eta");
    jet_eta4  ->Write("jet4_eta");
    Z_pT    ->Write("Z_pt");
    Dphi_all_Zlead ->Write("Dphi_all_Zlead");
    Dphi_all_notZlead -> Write("Dphi_all_notZlead");
    HZ       ->Write("HZ");
    HN       ->Write("HN");
    NZ       ->Write("NZ");
    NZy      ->Write("NZy");
    Dphi_12->Write("Dphi12");
    Dphi_23->Write("Dphi23");
    Dphi_13->Write("Dphi13");
    Dphi_ZJ1->Write("DphiZJ1");
    Dphi_ZJ2->Write("DphiZJ2");
    Dphi_ZJ3->Write("DphiZJ3");
    Theta_JZ->Write("Theta_JZ");
    Phi_star->Write("phi_star");
    NData->Write();
    NDataIncl->Write();


    // Clearing plots
    dijet_mass->Delete();
    Zjj_mass  ->Delete();       	
    NData     ->Delete();
    NDataIncl     ->Delete();
    Ht        ->Delete();
    ele_pT    ->Delete();
    ele_eta   ->Delete();
    ele_phi   ->Delete();
    jet_pT    ->Delete();
    jet_pT2   ->Delete();
    jet_pT3   ->Delete();
    jet_pT4   ->Delete();
    Z_pT      ->Delete();
    Dphi_all_Zlead ->Delete();
    Dphi_all_notZlead ->Delete();
    HZ       ->Delete();
    HN       ->Delete();
    NZ       ->Delete();
    NZy      ->Delete();
    Dphi_12  ->Delete();
    Dphi_23  ->Delete();
    Dphi_13  ->Delete();
    Dphi_ZJ1 ->Delete();
    Dphi_ZJ2 ->Delete();
    Dphi_ZJ3 ->Delete();
    Theta_JZ ->Delete();
    Phi_star ->Delete();
    jet_eta  ->Delete();
    jet_eta2 ->Delete();
    jet_eta3 ->Delete();   
    jet_eta4 ->Delete();   
    h_weights->Delete();
    h_invMass->Delete();

  }
  fzj->Close();
  fwj->Close();
  ftt->Close();
  fWW->Close();
  fZZ->Close();
  fWZ->Close();
  fda->Close();
  fzjtau->Close();
}

#ifndef __CINT__

int main ()
	        { 
Observables ();
       return 0;
	        }                               // Main program when run stand-alone
#endif

