/**********************************
 * Observables for Z+jet analysis *
 *                                *
 * Vieri Candelise March 2012     *
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

using
std::cout;
using
std::endl;	



#endif


/* Interesting Z + jet distributions */


TLorentzVector E1, E2, Z;
TLorentzVector J1, J2, JJ;

TFile* p = new TFile("MC_zjets.root", "RECREATE");
TFile* u = new TFile("MC_wjets.root", "RECREATE");
TFile* q = new TFile("MC_ttbar.root", "RECREATE");
TFile* v = new TFile("MC_diW.root", "RECREATE");
TFile* s = new TFile("MC_diZ.root", "RECREATE");
TFile* t = new TFile("MC_diWZ.root", "RECREATE");
TFile* r = new TFile("DATA.root", "RECREATE");

//FIles...

TFile *fa = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_17.root");
TFile *fb = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011_v2_17.root");
TFile *fc = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_17.root");
TFile *fd = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_ww_2011_v2_17.root");
TFile *fe = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_wz_2011_v2_17.root");
TFile *ff = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_zz_2011_v2_17.root");
TFile *fg = new TFile ("/gpfs/cms/data/2011/jet/jetValidation_ww_2011_v2_17.root");

TFile *w;

void
Observables::Loop()
{
  
  //DATA
  for(int i=0; i<7; i++){
    if (i==0) fc->cd ("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_17.root:/validationJEC");
    if (i==1) fa->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_17.root:/validationJEC");
    if (i==2) fb->cd ("/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011_v2_17.root:/validationJEC");
    if (i==3) fd->cd ("/gpfs/cms/data/2011/jet/jetValidation_ww_2011_v2_17.root:/validationJEC");
    if (i==4) fe->cd ("/gpfs/cms/data/2011/jet/jetValidation_wz_2011_v2_17.root:/validationJEC");
    if (i==5) ff->cd ("/gpfs/cms/data/2011/jet/jetValidation_zz_2011_v2_17.root:/validationJEC");
    if (i==6) fg->cd ("/gpfs/cms/data/2011/jet/jetValidation_ww_2011_v2_17.root:/validationJEC");
  
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");

  fChain = tree_fB;		/* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;

TH1D *NData             = new TH1D ("Jet_multi", "Jet_multi", 5, 0.5, 5.5);
TH1F *Ht                = new TH1F ("HT", "HT", 47, 30, 500);
TH1F *Dphi_12           = new TH1F ("Dphi_12", "Dphi_12", 25, 0, TMath::Pi());
TH1F *Dphi_13           = new TH1F ("Dphi_12", "Dphi_13", 25, 0, TMath::Pi());
TH1F *Dphi_23           = new TH1F ("Dphi_12", "Dphi_23", 25, 0, TMath::Pi());
TH1F *Dphi_ZJ1          = new TH1F ("Dphi_ZJ1", "Dphi_ZJ2", 25, 0, TMath::Pi());
TH1F *Dphi_ZJ2          = new TH1F ("Dphi_ZJ2", "Dphi_ZJ2", 25, 0, TMath::Pi());
TH1F *Dphi_ZJ3          = new TH1F ("Dphi_ZJ3", "Dphi_ZJ3", 25, 0, TMath::Pi());
TH1F *Dphi_all_Zlead    = new TH1F ("Dphi_all_Zlead", "Dphi_all_Zlead", 6, 0, 6.3);
TH1F *Dphi_all_notZlead = new TH1F ("Dphi_all_notZlead", "Dphi_all_notZlead", 6, 0, 6.3);
TH1F *ele_pT		= new TH1F ("ele_pT", "ele_pT", 50, 0, 250);
TH1F *ele_eta		= new TH1F ("ele_eta", "ele_eta", 20, -3, 3);
TH1F *ele_phi		= new TH1F ("ele_phi", "ele_phi", 20, 0, 6);
TH1F *jet_pT		= new TH1F ("jet_pT", "jet_pT", 30, 30, 330);
TH1F *jet_pT2		= new TH1F ("jet_pT2", "jet_pT2", 30, 30, 330);
TH1F *jet_pT3		= new TH1F ("jet_pT3", "jet_pT3", 30, 30, 330);
TH1F *jet_eta		= new TH1F ("jet_eta", "jet_eta", 30, -2.5, 2.5);
TH1F *jet_eta2		= new TH1F ("jet_eta2", "jet_eta2", 30, -2.5, 2.5);
TH1F *jet_eta3		= new TH1F ("jet_eta3", "jet_eta3", 30, -2.5, 2.5);
TH1F *Z_pT		= new TH1F ("Z_pT", "Z_pT", 50, 30, 500);
TH1F *dijet_mass	= new TH1F ("dijet_mass", "dijet_mass", 10, 400, 600);
TH1F *Zjj_mass	        = new TH1F ("Zjj_mass", "Zjj_mass", 10, 400, 600);
TH1F *Theta_JZ	        = new TH1F ("Theta_JZ", "Theta_JZ", 100, -1, 1);
TH1F *Phi_star		= new TH1F ("Phi_star", "Phi_star", 25, 0, 6.5);
TH1F *Phi_star_xs	= new TH1F ("(1/ #sigma) d #sigma / d#phi^{*}", "(1/ #sigma) d #sigma / d#phi^{*}", 25, 0, 6.5);




TH2F *HZ		= new TH2F ("HZ", "HZ", 100, 30, 1000, 500, 0, 1000);
TH2F *NZ		= new TH2F ("NZ", "NZ", 5, 0.5, 5.5, 500, 0, 1000);
TH2F *HN		= new TH2F ("HN", "HN", 5, 0.5, 5.5, 100, 30, 1000);
TH2F *NZy		= new TH2F ("NZy", "NZy", 5, 0.5, 5.5, 30, -3, 3);




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
      
      /* Fill histos */

   //if(MJJ>400 && MJJ<600){

      if (Jet_multiplicity >= 3){
      if (Z_pt > jet1_pt && jet1_pt > jet2_pt) {
	      Dphi_all_Zlead -> Fill(Dphi_event);	
      }else if((jet1_pt > Z_pt && Z_pt > jet2_pt) || (jet1_pt > jet2_pt && jet2_pt > Z_pt)) { 
	      Dphi_all_notZlead -> Fill(Dphi_event);
      }
      }

      if(Z_pt != 0 && Jet_multiplicity > 0){
	      Theta_JZ->Fill(TMath::Cos(theta_JZ));  
      }
      
      NData->Fill(Jet_multiplicity);

      if(Jet_multiplicity>0) Ht->Fill(jetHt);
      ele_pT   ->Fill(e1_pt);
      ele_eta  ->Fill(e1_eta);
      ele_phi  ->Fill(e1_phi);
      
      if(jet1_pt>30 && jet1_pt<350 && jet1_eta>-3 && jet1_eta<3){	
      jet_pT  -> Fill(jet1_pt);
      jet_eta -> Fill(jet1_eta);
      }
 
      if (Jet_multiplicity > 1 && jet2_pt > 30 && jet2_pt <350 && TMath::Abs(jet2_eta)<2.5){
	      jet_pT2 -> Fill(jet2_pt);
	      jet_eta2 -> Fill(jet2_eta);

      }

      if (Jet_multiplicity > 3 && jet3_pt > 30 && jet3_pt <350 && TMath::Abs(jet3_eta)<2.5){
	      jet_pT3 -> Fill(jet3_pt);
	      jet_eta3 -> Fill(jet3_eta);

      }
      
      Z_pT     ->Fill(Z_pt);
      HZ       ->Fill(Z_pt, jetHt);
      HN       ->Fill(Jet_multiplicity, jetHt);
      NZ       ->Fill(Jet_multiplicity, Z_pt);
      NZy      ->Fill(Jet_multiplicity, Z_y);
      if (Jet_multiplicity >  0) Dphi_12  ->Fill(Dphi12);
      if (Jet_multiplicity >  2) Dphi_13  ->Fill(Dphi13);
      if (Jet_multiplicity >  2) Dphi_23  ->Fill(Dphi23);

      if (Jet_multiplicity >  0) Dphi_ZJ1 ->Fill(DphiZJ1);
      if (Jet_multiplicity >  1) Dphi_ZJ2 ->Fill(DphiZJ2);
      if (Jet_multiplicity >  2) Dphi_ZJ3 ->Fill(DphiZJ3);

      if (Jet_multiplicity >  1) dijet_mass ->Fill(MJJ); 
      if (Jet_multiplicity >  1) Zjj_mass ->Fill(ZJJ); 

      if (Jet_multiplicity >  0) Phi_star->Fill(phi_star);

      double sigma = Phi_star -> GetEntries();
      Phi_star_xs -> Fill(phi_star/sigma);

  // } 
   
    }
      double Z = NData->GetEntries();

      // dividing by the Number of Z = 531198 in 2011A giving the xsec w/o efficiency, lumi
      
      jet_pT2    ->Sumw2();
      jet_pT     ->Sumw2();
      jet_pT3    ->Sumw2();
      jet_eta    ->Sumw2();
      jet_eta2   ->Sumw2();
      jet_eta3   ->Sumw2();
      Ht         ->Sumw2();
      Dphi_12    ->Sumw2();
      Dphi_ZJ1   ->Sumw2();
      Dphi_ZJ2   ->Sumw2();
      Phi_star   ->Sumw2();
      
      jet_eta    ->Scale(1./1123667);
      jet_eta2   ->Scale(1./1123667);
      jet_eta3   ->Scale(1./1123667);
      jet_pT2    ->Scale(1./1123667);
      jet_pT     ->Scale(1./1123667);
      jet_pT3    ->Scale(1./1123667);
      Ht         ->Scale(1./1123667);
      Dphi_12    ->Scale(1./1123667);
      Dphi_ZJ1   ->Scale(1./1123667);
      Dphi_ZJ2   ->Scale(1./1123667);
      Phi_star   ->Scale(1./1123667);


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
      jet_eta -> GetXaxis() -> SetTitle("Leading jet #eta [GeV/c]");
      jet_eta2   -> GetXaxis() -> SetTitle("2^{nd} jet #eta [GeV/c]");
      jet_eta3   -> GetXaxis() -> SetTitle("3^{rd} jet #eta [GeV/c]");
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
      jet_eta  -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}})   dN/d #eta");
      jet_eta2   -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d #eta");
      jet_eta3   -> GetYaxis() -> SetTitle("(1/N_{Z #rightarrow e^{+}e^{-}}) dN/d #eta");
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
       
      
    
       if(i==1){
	       p->cd();
       }
       if(i==2){
	      q->cd();
       }
       if(i==0){
       	       r->cd();
       }
       if(i==3){
       u->cd();
       }
       if(i==4){
	      t->cd();
       }
       if(i==5){
       	       s->cd();
       }
       if(i==6){
       	       v->cd();
       } 


	cout<<dijet_mass->GetEntries()<<endl;
      
       dijet_mass->Write();
       Zjj_mass ->Write();       	
       Ht      ->Write("jetHt");
       ele_pT  ->Write("e1_pt");
       ele_eta ->Write("e1_eta");
       ele_phi ->Write("e1_phi");
       jet_pT  ->Write("jet1_pt");
       jet_pT2  ->Write("jet2_pt");
       jet_pT3  ->Write("jet3_pt");
       jet_eta  ->Write("jet1_eta");
       jet_eta2  ->Write("jet2_eta");
       jet_eta3  ->Write("jet3_eta");
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


}
}

#ifndef __CINT__

int main ()
	        { 
Observables ();
       return 0;
	        }                               // Main program when run stand-alone
#endif

