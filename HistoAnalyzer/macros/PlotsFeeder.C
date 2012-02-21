#define PlotsFeeder_cxx
#include "PlotsFeeder.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>
#include <TPaveStats.h>


TObjArray * PlotsFeeder::Loop(int NumOfVtx)
{
//   In a ROOT session, you can do:
//      Root > .L PlotsFeeder.C
//      Root > PlotsFeeder t
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



	TObjArray* histarray = new TObjArray();
	
	//==================//
	//EB Reweight
	TH1D * h_IsoTrk_EBR; 
	TH1D * h_IsoEcal_EBR;
	TH1D * h_IsoHcal_EBR;

	TH1D * h_HE_EB;
	TH1F * h_dPhi_EB;
	TH1F * h_dEta_EB;
	TH1F * h_sigma_EB;
	
	TH1D * h_fbrem;
	TH1D * h_etaSC;
	TH1F * h_Dcot;
	TH1F * h_Dist;


	//EB Reweight
	h_IsoTrk_EBR = new TH1D("h_IsoTrk_EBR","IsoTrk",tEB,tEBmin,tEBmax);
	h_IsoEcal_EBR = new TH1D("h_IsoEcal_EBR","IsoEcal",eEB,eEBmin,eEBmax);
	h_IsoHcal_EBR = new TH1D("h_IsoHcal_EBR","IsoHcal",hEB,hEBmin,hEBmax);
	
	h_HE_EB = new TH1D("h_HE_EB","H/E",iHEEB,HEEBmin,HEEBmax);
	h_dPhi_EB = new TH1F("h_dPhiTkClu_EB","DeltaPhiTkClu",dPhiEB,dPhiEBmin,dPhiEBmax);
	h_dEta_EB = new TH1F("h_dEtaTkClu_EB","DeltaEtaTkClu",dEtaEB,dEtaEBmin,dEtaEBmax);
	h_sigma_EB = new TH1F("h_sigmaIeIe_EB","SigmaIeIe",sigmaEB,sigmaEBmin,sigmaEBmax);

	h_fbrem = new TH1D("h_fbrem","Brem fraction",100,0.,1.);
	h_etaSC = new TH1D("h_etaSC","etaSC",56,-2.4,2.4);
	h_Dcot = new TH1F("h_Dcot","Dcot",40,-0.2,0.2);
	h_Dist = new TH1F("h_Dist","Dist",40,-0.2,0.2);


	//=====================
	//EE Reweight
	TH1D * h_IsoTrk_EER; 
	TH1D * h_IsoEcal_EER;
	TH1D * h_IsoHcal_EER;
	
	TH1D * h_HE_EE;
	TH1F * h_dPhi_EE;
	TH1F * h_dEta_EE;
	TH1F * h_sigma_EE;
	
	//EE Reweight
	h_IsoTrk_EER = new TH1D("h_IsoTrk_EER","IsoTrk",tEE,tEEmin,tEEmax);
	h_IsoEcal_EER = new TH1D("h_IsoEcal_EER","IsoEcal",eEE,eEEmin,eEEmax);
	h_IsoHcal_EER = new TH1D("h_IsoHcal_EER","IsoHcal",hEE,hEEmin,hEEmax);

	h_HE_EE = new TH1D("h_HE_EE","H/E",iHEEE,HEEEmin,HEEEmax);
	h_dPhi_EE = new TH1F("h_dPhiTkClu_EE","DeltaPhiTkClu",dPhiEE,dPhiEEmin,dPhiEEmax);
	h_dEta_EE = new TH1F("h_dEtaTkClu_EE","DeltaEtaTkClu",dEtaEE,dEtaEEmin,dEtaEEmax);
	h_sigma_EE = new TH1F("h_sigmaIeIe_EE","SigmaIeIe",sigmaEE,sigmaEEmin,sigmaEEmax);


	//==================//
	//EB Reweight PUR
	TH1D * h_IsoTrk_EBR_PUR; 
	TH1D * h_IsoEcal_EBR_PUR;
	TH1D * h_IsoHcal_EBR_PUR;
	
	//EB Reweight PUR
	h_IsoTrk_EBR_PUR = new TH1D("h_IsoTrk_EBR_PUR","IsoTrk",tEB,tEBmin,tEBmax);
	h_IsoEcal_EBR_PUR = new TH1D("h_IsoEcal_EBR_PUR","IsoEcal",eEB,eEBmin,eEBmax);
	h_IsoHcal_EBR_PUR = new TH1D("h_IsoHcal_EBR_PUR","IsoHcal",hEB,hEBmin,hEBmax);


	//EE Reweight PUR
	TH1D * h_IsoTrk_EER_PUR; 
	TH1D * h_IsoEcal_EER_PUR;
	TH1D * h_IsoHcal_EER_PUR;
	
	//EE Reweight PUR
	h_IsoTrk_EER_PUR = new TH1D("h_IsoTrk_EER_PUR","IsoTrk",tEE,tEEmin,tEEmax);
	h_IsoEcal_EER_PUR = new TH1D("h_IsoEcal_EER_PUR","IsoEcal",eEE,eEEmin,eEEmax);
	h_IsoHcal_EER_PUR = new TH1D("h_IsoHcal_EER_PUR","IsoHcal",hEE,hEEmin,hEEmax);


	//==================//



	if (fChain == 0){ cout << " something went wrong in PlotsFeeder "; return histarray;}

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		if(numberOfVertices==NumOfVtx){
			if (IsoTrkEB_PUR->size()>0) {
				for (unsigned int i=0; i<IsoTrkEB_PUR->size();i++){
					float var=IsoTrkEB_PUR->at(i);
					h_IsoTrk_EBR_PUR->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoTrk_EBR_PUR->Fill(var,Weight);
				}
			} 
			if (IsoEcalEB_PUR->size()>0) {
				for (unsigned int i=0; i<IsoEcalEB_PUR->size();i++){
					float var=IsoEcalEB_PUR->at(i);
					h_IsoEcal_EBR_PUR->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoEcal_EBR_PUR->Fill(var,Weight);
				}
			}
			if (IsoHcalEB_PUR->size()>0) {
				for (unsigned int i=0; i<IsoEcalEB_PUR->size();i++){
					float var=IsoHcalEB_PUR->at(i);
					h_IsoHcal_EBR_PUR->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoHcal_EBR_PUR->Fill(var,Weight);
				}
			}
			if (IsoTrkEB->size()>0) {
				for (unsigned int i=0; i<IsoTrkEB->size();i++){
					float var=IsoTrkEB->at(i);
					h_IsoTrk_EBR->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoTrk_EBR->Fill(var,Weight);
				}
			}
			if (IsoEcalEB->size()>0) {
				for (unsigned int i=0; i<IsoEcalEB->size();i++){
					float var=IsoEcalEB->at(i);
					h_IsoEcal_EBR->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoEcal_EBR->Fill(var,Weight);
				}
			}
			if (IsoHcalEB->size()>0) {
				for (unsigned int i=0; i<IsoEcalEB->size();i++){
					float var=IsoHcalEB->at(i);
					h_IsoHcal_EBR->SetLineColor(kBlack);
					h_IsoHcal_EBR->Fill(var,Weight);
				}
			}

			if (sigmaIeIeEB->size()>0) {
				for (unsigned int i=0; i<sigmaIeIeEB->size();i++){
					float var=sigmaIeIeEB->at(i);
					h_sigma_EB->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_sigma_EB->Fill(var,Weight);
				}
			}

			if (HEEB->size()>0) {
				for (unsigned int i=0; i<HEEB->size();i++){
					float var=HEEB->at(i);
					h_HE_EB->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_HE_EB->Fill(var,Weight);
				}
			}

			if (DeltaPhiTkCluEB->size()>0) {
				for (unsigned int i=0; i<DeltaPhiTkCluEB->size();i++){
					float var=DeltaPhiTkCluEB->at(i);
					h_dPhi_EB->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_dPhi_EB->Fill(var,Weight);
				}
			}

			if (DeltaEtaTkCluEB->size()>0) {
				for (unsigned int i=0; i<DeltaEtaTkCluEB->size();i++){
					float var=DeltaEtaTkCluEB->at(i);
					h_dEta_EB->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_dEta_EB->Fill(var,Weight);
				}
			}

			if (fbrem->size()>0) {
				for (unsigned int i=0; i<fbrem->size();i++){
					double var=fbrem->at(i);
					h_fbrem->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_fbrem->Fill(var,Weight);
				}
			}

/*			if (etaSC->size()>0) { // non funziona perche' c'e' un duplicato nel tree con lo stesso nome in Histoanalyzer #FIXME THERE!!!
				for (unsigned int i=0; i<etaSC->size();i++){
					double var=etaSC->at(i);
					h_etaSC->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_etaSC->Fill(var,Weight);
				}
			}
*/
			if (Dcot->size()>0) {
				for (unsigned int i=0; i<Dcot->size();i++){
					float var=Dcot->at(i);
					h_Dcot->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_Dcot->Fill(var,Weight);
				}
			}

			if (Dist->size()>0) {
				for (unsigned int i=0; i<Dist->size();i++){
					float var=Dist->at(i);
					h_Dist->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_Dist->Fill(var,Weight);
				}
			}

			//==== EE ====//
			if (IsoTrkEE_PUR->size()>0) {
				for (unsigned int i=0; i<IsoTrkEE_PUR->size();i++){
					float var=IsoTrkEE_PUR->at(i);
					h_IsoTrk_EER_PUR->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoTrk_EER_PUR->Fill(var,Weight);
				}
			}
			if (IsoEcalEE_PUR->size()>0) {
				for (unsigned int i=0; i<IsoEcalEE_PUR->size();i++){
					float var=IsoEcalEE_PUR->at(i);
					h_IsoEcal_EER_PUR->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoEcal_EER_PUR->Fill(var,Weight);
				}
			}
			if (IsoHcalEE_PUR->size()>0) {
				for (unsigned int i=0; i<IsoHcalEE_PUR->size();i++){
					float var=IsoHcalEE_PUR->at(i);
					h_IsoHcal_EER_PUR->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoHcal_EER_PUR->Fill(var,Weight);
				}
			}

			if (IsoTrkEE->size()>0) {
				for (unsigned int i=0; i<IsoTrkEE->size();i++){
					float var=IsoTrkEE->at(i);
					h_IsoTrk_EER->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoTrk_EER->Fill(var,Weight);
				}
			}
			if (IsoEcalEE->size()>0) {
				for (unsigned int i=0; i<IsoEcalEE->size();i++){
					float var=IsoEcalEE->at(i);
					h_IsoEcal_EER->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoEcal_EER->Fill(var,Weight);
				}
			}
			if (IsoHcalEE->size()>0) {
				for (unsigned int i=0; i<IsoHcalEE->size();i++){
					float var=IsoHcalEE->at(i);
					h_IsoHcal_EER->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_IsoHcal_EER->Fill(var,Weight);
				}
			}
			if (sigmaIeIeEE->size()>0) {
				for (unsigned int i=0; i<sigmaIeIeEE->size();i++){
					float var=sigmaIeIeEE->at(i);
					h_sigma_EE->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_sigma_EE->Fill(var,Weight);
				}
			}
			if (HEEE->size()>0) {
				for (unsigned int i=0; i<HEEE->size();i++){
					float var=HEEE->at(i);
					h_HE_EE->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_HE_EE->Fill(var,Weight);
				}
			}

			if (DeltaPhiTkCluEE->size()>0) {
				for (unsigned int i=0; i<DeltaPhiTkCluEE->size();i++){
					float var=DeltaPhiTkCluEE->at(i);
					h_dPhi_EE->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_dPhi_EE->Fill(var,Weight);
				}
			}

			if (DeltaEtaTkCluEE->size()>0) {
				for (unsigned int i=0; i<DeltaEtaTkCluEE->size();i++){
					float var=DeltaEtaTkCluEE->at(i);
					h_dEta_EE->SetLineColor(kBlack);
					if(!Weight) Weight=1;
					h_dEta_EE->Fill(var,Weight);
				}
			}



		}
	}

	


	histarray->Add(h_IsoTrk_EBR_PUR); 
	histarray->Add(h_IsoEcal_EBR_PUR);
	histarray->Add(h_IsoHcal_EBR_PUR);
	histarray->Add(h_IsoTrk_EBR); 
	histarray->Add(h_IsoEcal_EBR);
	histarray->Add(h_IsoHcal_EBR);
	
	histarray->Add(h_IsoTrk_EER_PUR); 
	histarray->Add(h_IsoEcal_EER_PUR);
	histarray->Add(h_IsoHcal_EER_PUR);
	histarray->Add(h_IsoTrk_EER); 
	histarray->Add(h_IsoEcal_EER);
	histarray->Add(h_IsoHcal_EER);
	
	histarray->Add(h_HE_EB);
	histarray->Add(h_dPhi_EB);
	histarray->Add(h_dEta_EB);
	histarray->Add(h_sigma_EB);

	histarray->Add(h_HE_EE);
	histarray->Add(h_dPhi_EE);
	histarray->Add(h_dEta_EE);
	histarray->Add(h_sigma_EE);
	
	histarray->Add(h_fbrem);
	histarray->Add(h_etaSC);
	histarray->Add(h_Dcot);
	histarray->Add(h_Dist);


return  histarray;




}
