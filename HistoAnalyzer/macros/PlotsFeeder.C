#define PlotsFeeder_cxx
#include "PlotsFeeder.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>
#include <TPaveStats.h>


TCanvas * EB_plots;
TCanvas * EE_plots;



vector<TH1*> PlotsFeeder::Loop(int NumOfVtx)
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


	vector<TH1 *> vHistograms;

	//EB Reweight
	TH1D * h_IsoTrk_EBR; 
	TH1D * h_IsoEcal_EBR;
	TH1D * h_IsoHcal_EBR;
	TH1D * h_HE_EBR;
	TH1F * h_DeltaPhiTkClu_EBR;
	TH1F * h_DeltaEtaTkClu_EBR;
	TH1F * h_sigmaIeIe_EBR;
	//EB Reweight
	h_IsoTrk_EBR = new TH1D("h_IsoTrk_EBR","IsoTrk",20,0.,0.20);
	h_IsoEcal_EBR = new TH1D("h_IsoEcal_EBR","IsoEcal",20,0.,0.20);
	h_IsoHcal_EBR = new TH1D("h_IsoHcal_EBR","IsoHcal",20,0.,0.20);
	h_HE_EBR = new TH1D("h_HE_EBR","H/E",20,0.,0.20);
	h_DeltaPhiTkClu_EBR = new TH1F("h_DeltaPhiTkClu_EBR","DeltaPhiTkClu",20,0.,0.2);
	h_DeltaEtaTkClu_EBR = new TH1F("h_DeltaEtaTkClu_EBR","DeltaEtaTkClu",20,0.,.05);
	h_sigmaIeIe_EBR = new TH1F("h_sigmaIeIe_EBR","sigmaIeIe",20,0.,0.1);

	/*=========================*/

	//EE Reweight
	TH1D * h_IsoTrk_EER; 
	TH1D * h_IsoEcal_EER;
	TH1D * h_IsoHcal_EER;
	TH1D * h_HE_EER;
	TH1F * h_DeltaPhiTkClu_EER;
	TH1F * h_DeltaEtaTkClu_EER;
	TH1F * h_sigmaIeIe_EER;
	//EE Reweight
	h_IsoTrk_EER = new TH1D("h_IsoTrk_EER","IsoTrk",20,0.,0.20);
	h_IsoEcal_EER = new TH1D("h_IsoEcal_EER","IsoEcal",20,0.,0.20);
	h_IsoHcal_EER = new TH1D("h_IsoHcal_EER","IsoHcal",20,0.,0.20);
	h_HE_EER = new TH1D("h_HE_EER","H/E",20,0.,0.20);
	h_DeltaPhiTkClu_EER = new TH1F("h_DeltaPhiTkClu_EER","DeltaPhiTkClu",20,0.,0.2);
	h_DeltaEtaTkClu_EER = new TH1F("h_DeltaEtaTkClu_EER","DeltaEtaTkClu",20,0.,.05);
	h_sigmaIeIe_EER = new TH1F("h_sigmaIeIe_EER","sigmaIeIe",20,0.,0.1);

	/*=========================*/


	if (fChain == 0){ cout << " something went wrong in PlotsFeeder "; return vHistograms;}

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		if(numberOfVertices==NumOfVtx){

			if (IsoTrkEB->size()>0) {float var=IsoTrkEB->at(0);
				h_IsoTrk_EBR->Fill(var,Weight);
			}
			if (IsoEcalEB->size()>0) {float var=IsoEcalEB->at(0);
				h_IsoEcal_EBR->Fill(var,Weight);
			}
			if (IsoHcalEB->size()>0) {float var=IsoHcalEB->at(0);
				h_IsoHcal_EBR->Fill(var,Weight);
			}
			if (HEEB->size()>0) {float var=HEEB->at(0);
				h_HE_EBR->Fill(var,Weight);
			}
			if (DeltaPhiTkCluEB->size()>0) {float var=DeltaPhiTkCluEB->at(0);
				h_DeltaPhiTkClu_EBR->Fill(var,Weight);
			}
			if (DeltaEtaTkCluEB->size()>0) {float var=DeltaEtaTkCluEB->at(0);
				h_DeltaEtaTkClu_EBR->Fill(var,Weight);
			}
			if (sigmaIeIeEB->size()>0) {float var=sigmaIeIeEB->at(0);
				h_sigmaIeIe_EBR->Fill(var,Weight);
			}

			if (IsoTrkEE->size()>0) {float var=IsoTrkEE->at(0);
				h_IsoTrk_EER->Fill(var,Weight);
			}
			if (IsoEcalEE->size()>0) {float var=IsoEcalEE->at(0);
				h_IsoEcal_EER->Fill(var,Weight);
			}
			if (IsoHcalEE->size()>0) {float var=IsoHcalEE->at(0);
				h_IsoHcal_EER->Fill(var,Weight);
			}
			if (HEEE->size()>0) {float var=HEEE->at(0);
				h_HE_EER->Fill(var,Weight);
			}
			if (DeltaPhiTkCluEE->size()>0) {float var=DeltaPhiTkCluEE->at(0);
				h_DeltaPhiTkClu_EER->Fill(var,Weight);
			}
			if (DeltaEtaTkCluEE->size()>0) {float var=DeltaEtaTkCluEE->at(0);
				h_DeltaEtaTkClu_EER->Fill(var,Weight);
			}
			if (sigmaIeIeEE->size()>0) {float var=sigmaIeIeEE->at(0);
				h_sigmaIeIe_EER->Fill(var,Weight);
			}
		}
	}

	vHistograms.push_back(h_IsoTrk_EBR); 
	vHistograms.push_back(h_IsoEcal_EBR);
	vHistograms.push_back(h_IsoHcal_EBR);
	vHistograms.push_back(h_HE_EBR);
	vHistograms.push_back(h_DeltaPhiTkClu_EBR);
	vHistograms.push_back(h_DeltaEtaTkClu_EBR);
	vHistograms.push_back(h_sigmaIeIe_EBR);
	
	vHistograms.push_back(h_IsoTrk_EER); 
	vHistograms.push_back(h_IsoEcal_EER);
	vHistograms.push_back(h_IsoHcal_EER);
	vHistograms.push_back(h_HE_EER);
	vHistograms.push_back(h_DeltaPhiTkClu_EER);
	vHistograms.push_back(h_DeltaEtaTkClu_EER);
	vHistograms.push_back(h_sigmaIeIe_EER);
	


return  vHistograms;

}
