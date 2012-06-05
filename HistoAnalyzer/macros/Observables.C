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
#include "Unfolding/getEfficiencyCorrection.C"


using
std::cout;
using
std::endl;	



#endif

bool activateScaleFactors=true;  // Correct for the difference MC/Data in the background

string efffile="/gpfs/cms/data/2011/TaP/efficiencies_2011_v2_2523mixmex.root";

//Open MC and data files to retrieve effciencies
TFile *fAeff = new TFile (efffile.c_str());// WHY 2 FILES? DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
TFile *fBeff = new TFile (efffile.c_str()); 

/* Interesting Z + jet distributions */


TLorentzVector E1, E2, Z;
TLorentzVector J1, J2, JJ;

//Important parameters
double jetThreshold=30.0;
bool evalDiffCS=true; // if false it does not divide for # of Zs

// Files to be saved
string dir="/gpfs/cms/data/2011/Observables/";
string version="_v2_25.root";

string szj=dir+"MC_zjets"+version;
string swj=dir+"MC_wjets"+version;
string stt=dir+"MC_ttbar"+version;
string sWW=dir+"MC_diW"+version;
string sZZ=dir+"MC_siZ"+version;
string sWZ=dir+"MC_diWZ"+version;
string sda=dir+"DATA"+version;


TFile* fzj = new TFile(szj.c_str(), "RECREATE");
TFile* fwj = new TFile(swj.c_str(), "RECREATE");
TFile* ftt = new TFile(stt.c_str(), "RECREATE");
TFile* fWW = new TFile(sWW.c_str(), "RECREATE");
TFile* fZZ = new TFile(sZZ.c_str(), "RECREATE");
TFile* fWZ = new TFile(sWZ.c_str(), "RECREATE");
TFile* fda = new TFile(sda.c_str(), "RECREATE");

TDirectory *validationJECz=fzj->mkdir("validationJEC");
TDirectory *validationJECw=fwj->mkdir("validationJEC");
TDirectory *validationJECtt=ftt->mkdir("validationJEC");
TDirectory *validationJECWW=fWW->mkdir("validationJEC");
TDirectory *validationJECZZ=fZZ->mkdir("validationJEC");
TDirectory *validationJECWZ=fWZ->mkdir("validationJEC");
TDirectory *validationJECda=fda->mkdir("validationJEC");

//FIles do be opened

string diropen="/gpfs/cms/data/2011/jet/jetValidation_";
string sozj=diropen+"zjets_magd_2011"+version;
string sowj=diropen+"w_2011"+"_v2_22.root";//+version;
string sott=diropen+"ttbar_2011"+version;
string soWW=diropen+"ww_2011"+version;
string soZZ=diropen+"zz_2011"+version;
string soWZ=diropen+"wz_2011"+version;
string soda=diropen+"DATA_2011"+version;

string folderdir="validationJEC";
string sodzj=sozj+":/"+folderdir;
string sodwj=sowj+":/"+folderdir;
string sodtt=sott+":/"+folderdir;
string sodWW=soWW+":/"+folderdir;
string sodZZ=soZZ+":/"+folderdir;
string sodWZ=soWZ+":/"+folderdir;
string sodda=soda+":/"+folderdir;

TFile *Fzj = new TFile (sozj.c_str());
TFile *Fwj = new TFile (sowj.c_str());
TFile *Ftt = new TFile (sott.c_str());
TFile *Fda = new TFile (soda.c_str());
TFile *FWW = new TFile (soWW.c_str());
TFile *FWZ = new TFile (soWZ.c_str());
TFile *FZZ = new TFile (soZZ.c_str());

TFile *w;
//List of observables to show
TH1F *NData             = new TH1F ("Jet_multi", "Jet_multi", 6, 0, 6);
TH1F *Ht                = new TH1F ("HT", "HT", 47, 30, 500);
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
TH1F *jet_pT	        = new TH1F ("jet_pT", "jet_pT", 15, 30, 330);
TH1F *jet_pT2	        = new TH1F ("jet_pT2", "jet_pT2", 10, 30, 330);
TH1F *jet_pT3	        = new TH1F ("jet_pT3", "jet_pT3", 8, 30, 190);
TH1F *jet_pT4	        = new TH1F ("jet_pT4", "jet_pT4", 7, 30, 100);
TH1F *jet_eta	        = new TH1F ("jet_eta", "jet_eta", 30, -2.5, 2.5);
TH1F *jet_eta2	        = new TH1F ("jet_eta2", "jet_eta2", 30, -2.5, 2.5);
TH1F *jet_eta3	        = new TH1F ("jet_eta3", "jet_eta3", 30, -2.5, 2.5);
TH1F *jet_eta4	        = new TH1F ("jet_eta4", "jet_eta4", 30, -2.5, 2.5);
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

void
Observables::Loop()
{
  double numbOfZ = 0;
  double numbOfZPlus1 = 0;
  double numbOfZPlus2 = 0;
  double numbOfZPlus3 = 0;
  double numbOfZPlus4 = 0;

  //DATA
  for(int i=0; i<7; i++){
    if (i==0) Fda->cd (sodda.c_str());
    if (i==1) Fzj->cd (sodzj.c_str());
    if (i==2) Ftt->cd (sodtt.c_str());
    if (i==3) FWW->cd (sodWW.c_str());
    if (i==4) FWZ->cd (sodWZ.c_str());
    if (i==5) FZZ->cd (sodZZ.c_str());
    if (i==6) Fwj->cd (sodwj.c_str());
    
    TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");
    
    fChain = tree_fB;		/* Loop RunA */
    Init (fChain);
    Long64_t nentries = fChain->GetEntriesFast ();
    Long64_t nbytes = 0, nb = 0;
    
    if (fChain == 0)  return;
    
    //List of observables to show
    NData             = new TH1F ("Jet_multi", "Jet_multi", 6, 0, 6);
    Ht                = new TH1F ("HT", "HT", 47, 30, 500);
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
    jet_pT	    = new TH1F ("jet_pT", "jet_pT", 15, 30, 330);
    jet_pT2	    = new TH1F ("jet_pT2", "jet_pT2", 10, 30, 330);
    jet_pT3	    = new TH1F ("jet_pT3", "jet_pT3", 8, 30, 190);
    jet_pT4	    = new TH1F ("jet_pT4", "jet_pT4", 7, 30, 100);
    jet_eta	    = new TH1F ("jet_eta", "jet_eta", 30, -2.5, 2.5);
    jet_eta2	    = new TH1F ("jet_eta2", "jet_eta2", 30, -2.5, 2.5);
    jet_eta3	    = new TH1F ("jet_eta3", "jet_eta3", 30, -2.5, 2.5);
    jet_eta4	    = new TH1F ("jet_eta4", "jet_eta4", 30, -2.5, 2.5);
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


	if (Jet_multiplicity >= 3){
	  if (Z_pt > jet1_pt && jet1_pt > jet2_pt) {
	    Dphi_all_Zlead -> Fill(Dphi_event,evWeight);	
	  }else if((jet1_pt > Z_pt && Z_pt > jet2_pt) || (jet1_pt > jet2_pt && jet2_pt > Z_pt)) { 
	    Dphi_all_notZlead -> Fill(Dphi_event,evWeight);
	  }
	}
	
	if(Z_pt != 0 && Jet_multiplicity > 0){
	  Theta_JZ->Fill(TMath::Cos(theta_JZ),evWeight);  
	}
	
	NData->Fill(Jet_multiplicity,evWeight);
	

	///////////////////
	///  HT, inclusive pt,eta and phi
	/////////////////// 


	if(Jet_multiplicity>0) Ht->Fill(jetHt,evWeight);
	ele_pT   ->Fill(e1_pt,evWeight);
	ele_eta  ->Fill(e1_eta,evWeight);
	ele_phi  ->Fill(e1_phi,evWeight);


	///////////////////
	///  jet pt/eta spectra, up to 4
	/////////////////// 

	double evWeight_scalefactors=1.0;
	
	if(jet1_pt>jetThreshold && jet1_pt<350 && jet1_eta>-3 && jet1_eta<3){	
	  
	  if (activateScaleFactors && i!=0) {
	    if (Jet_multiplicity==1) evWeight_scalefactors=getScaleFactorJetPt(fAeff, fBeff, Jet_multiplicity,jet1_pt);
	  }
	  jet_pT  -> Fill(jet1_pt,evWeight*evWeight_scalefactors);
	  jet_eta -> Fill(jet1_eta,evWeight);
	}

	///////

	if (Jet_multiplicity > 1 && jet2_pt > jetThreshold && jet2_pt <350 && TMath::Abs(jet2_eta)<2.5){
	  
	  if (activateScaleFactors && i!=0) {
	    if (Jet_multiplicity==2) evWeight_scalefactors=getScaleFactorJetPt(fAeff, fBeff, Jet_multiplicity,jet2_pt);
	  }
	  jet_pT2 -> Fill(jet2_pt,evWeight*evWeight_scalefactors);
	  jet_eta2 -> Fill(jet2_eta,evWeight);
	}

	///////
	
	if (Jet_multiplicity > 2 && jet3_pt > jetThreshold && jet3_pt <350 && TMath::Abs(jet3_eta)<2.5){
	  
	  if (activateScaleFactors && i!=0) {
	    if (Jet_multiplicity==3) evWeight_scalefactors=getScaleFactorJetPt(fAeff, fBeff, Jet_multiplicity,jet3_pt);
	  }
	  jet_pT3 -> Fill(jet3_pt,evWeight*evWeight_scalefactors);
	  jet_eta3 -> Fill(jet3_eta,evWeight);
	}

	///////

	
	if (Jet_multiplicity > 3 && jet4_pt > jetThreshold && jet4_pt <350 && TMath::Abs(jet4_eta)<2.5){
	  
	  //if (activateScaleFactors && i!=0) {
	  //if (Jet_multiplicity==4) evWeight_scalefactors=getScaleFactorJetPt(fAeff, fBeff, Jet_multiplicity,jet4_pt);
	  //}
	  jet_pT4 -> Fill(jet4_pt,evWeight*evWeight_scalefactors);
	  jet_eta4 -> Fill(jet4_eta,evWeight);
	}

	///////////////////
	///  Z Boson, Ht and angles and other
	/////////////////// 
	
	
	Z_pT     ->Fill(Z_pt,evWeight);
	HZ       ->Fill(Z_pt, jetHt,evWeight);
	HN       ->Fill(Jet_multiplicity, jetHt,evWeight);
	NZ       ->Fill(Jet_multiplicity, Z_pt,evWeight);
	NZy      ->Fill(Jet_multiplicity, Z_y,evWeight);
	if (Jet_multiplicity >  0) Dphi_12  ->Fill(Dphi12,evWeight);
	if (Jet_multiplicity >  2) Dphi_13  ->Fill(Dphi13,evWeight);
	if (Jet_multiplicity >  2) Dphi_23  ->Fill(Dphi23,evWeight);
	
	if (Jet_multiplicity >  0) Dphi_ZJ1 ->Fill(DphiZJ1,evWeight);
	if (Jet_multiplicity >  1) Dphi_ZJ2 ->Fill(DphiZJ2,evWeight);
	if (Jet_multiplicity >  2) Dphi_ZJ3 ->Fill(DphiZJ3,evWeight);
	
	if (Jet_multiplicity >  1) dijet_mass ->Fill(MJJ,evWeight); 
	if (Jet_multiplicity >  1) Zjj_mass ->Fill(ZJJ,evWeight); 
	
	if (Jet_multiplicity >  0) Phi_star->Fill(phi_star,evWeight);
	
	double sigma = Phi_star -> GetEntries();
	Phi_star_xs -> Fill(phi_star/sigma,evWeight);
	
      }
    
    //Get the number of Z bosons in data
    if (i==0)  {
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
    Ht       -> GetXaxis() -> SetTitle("H_{T} [GeV/c]"); 
    ele_pT   -> GetXaxis() -> SetTitle("Leading electron p_{T} [GeV/c]");        
    ele_eta  -> GetXaxis() -> SetTitle("Leading electron #eta");
    ele_phi  -> GetXaxis() -> SetTitle("Leading electron #phi");
    jet_pT -> GetXaxis() -> SetTitle("Leading jet p_{T} [GeV/c]");
    jet_pT2   -> GetXaxis() -> SetTitle("2^{nd} jet p_{T} [GeV/c]");
    jet_pT3   -> GetXaxis() -> SetTitle("3^{rd} jet p_{T} [GeV/c]");
    jet_pT4   -> GetXaxis() -> SetTitle("4^{th} jet p_{T} [GeV/c]");
    jet_eta -> GetXaxis() -> SetTitle("Leading jet #eta [GeV/c]");
    jet_eta2   -> GetXaxis() -> SetTitle("2^{nd} jet #eta [GeV/c]");
    jet_eta3   -> GetXaxis() -> SetTitle("3^{rd} jet #eta [GeV/c]");
    jet_eta4   -> GetXaxis() -> SetTitle("4^{th} jet #eta [GeV/c]");
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
    
    NData    -> GetYaxis() -> SetTitle("(Z #rightarrow e^{+}e^{-} + N_{jet})");
    Ht       -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d H_{T}");
    ele_pT   -> GetYaxis() -> SetTitle("Events");        
    ele_eta  -> GetYaxis() -> SetTitle("Events");
    ele_phi  -> GetYaxis() -> SetTitle("Events");
    jet_pT   -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d p_{T}");
    jet_pT2   -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d p_{T}");
    jet_pT3   -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d p_{T}");
    jet_pT4   -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d p_{T}");
    jet_eta  -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}})   dN/d #eta");
    jet_eta2   -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d #eta");
    jet_eta3   -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d #eta");
    jet_eta4   -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d #eta");
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
    
    h_weights->Write();
    dijet_mass->Write();
    Zjj_mass ->Write();       	
    Ht      ->Write("jetHt");
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

    // Clearing plots
    dijet_mass->Delete();
    Zjj_mass  ->Delete();       	
    NData     ->Delete();
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

  }
  fzj->Close();
  fwj->Close();
  ftt->Close();
  fWW->Close();
  fZZ->Close();
  fWZ->Close();
  fda->Close();
}

#ifndef __CINT__

int main ()
	        { 
Observables ();
       return 0;
	        }                               // Main program when run stand-alone
#endif

