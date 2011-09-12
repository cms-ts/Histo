#define PlotsFeeder_cxx
#include "PlotsFeeder.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>
#include <TPaveStats.h>

#include "MMutil.C"


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

//DS! PER IL MOMENTO LI LASCIO TUTTI, SE POI DECIDIAMO EFFETTIVAMENTE DI TENERE SOLO LE 3 ISO, 
//QUESTA MACRO È MEGLIO INTEGRARLA CON LA PlotsFeeder.C 
//(e modificare di conseguenza anche la DataMCValidation.C per far sparire la DataMCValidationPUR.C

	//EB Reweight
	TH1D * h_IsoTrk_EBR_PUR; 
	TH1D * h_IsoEcal_EBR_PUR;
	TH1D * h_IsoHcal_EBR_PUR;
	TH1D * h_HE_EBR;
	TH1F * h_DeltaPhiTkClu_EBR;
	TH1F * h_DeltaEtaTkClu_EBR;
	TH1F * h_sigmaIeIe_EBR;
	//EB Reweight
	h_IsoTrk_EBR_PUR = new TH1D("h_IsoTrk_EBR_PUR","IsoTrk_PUR",36,0.,0.09);
	h_IsoEcal_EBR_PUR = new TH1D("h_IsoEcal_EBR_PUR","IsoEcal_PUR",28,0.,0.07);
	h_IsoHcal_EBR_PUR = new TH1D("h_IsoHcal_EBR_PUR","IsoHcal_PUR",40,0.,0.10);
	/*h_IsoTrk_EBR_PUR = new TH1D("h_IsoTrk_EBR_PUR","IsoTrk_PUR",20,0.,0.20);
	h_IsoEcal_EBR_PUR = new TH1D("h_IsoEcal_EBR_PUR","IsoEcal_PUR",20,0.,0.20);
	h_IsoHcal_EBR_PUR = new TH1D("h_IsoHcal_EBR_PUR","IsoHcal_PUR",20,0.,0.20);*/
	h_HE_EBR = new TH1D("h_HE_EBR","H/E",20,0.,0.20);
	h_DeltaPhiTkClu_EBR = new TH1F("h_DeltaPhiTkClu_EBR","DeltaPhiTkClu",20,0.,0.2);
	h_DeltaEtaTkClu_EBR = new TH1F("h_DeltaEtaTkClu_EBR","DeltaEtaTkClu",20,0.,.05);
	h_sigmaIeIe_EBR = new TH1F("h_sigmaIeIe_EBR","sigmaIeIe",20,0.,0.1);

	/*=========================*/

	//EE Reweight
	TH1D * h_IsoTrk_EER_PUR; 
	TH1D * h_IsoEcal_EER_PUR;
	TH1D * h_IsoHcal_EER_PUR;
	TH1D * h_HE_EER;
	TH1F * h_DeltaPhiTkClu_EER;
	TH1F * h_DeltaEtaTkClu_EER;
	TH1F * h_sigmaIeIe_EER;
	//EE Reweight
	h_IsoTrk_EER_PUR = new TH1D("h_IsoTrk_EER_PUR","IsoTrk",16,0.,0.04);
	h_IsoEcal_EER_PUR = new TH1D("h_IsoEcal_EER_PUR","IsoEcal",20,0.,0.05);
	h_IsoHcal_EER_PUR = new TH1D("h_IsoHcal_EER_PUR","IsoHcal",10,0.,0.025);
	/*h_IsoTrk_EER_PUR = new TH1D("h_IsoTrk_EER_PUR","IsoTrk",20,0.,0.20);
	h_IsoEcal_EER_PUR = new TH1D("h_IsoEcal_EER_PUR","IsoEcal",20,0.,0.20);
	h_IsoHcal_EER_PUR = new TH1D("h_IsoHcal_EER_PUR","IsoHcal",20,0.,0.20);*/
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

			if (IsoTrkEB_PUR->size()>0) {
				for (unsigned int i=0; i<IsoTrkEB_PUR->size();i++){
					float var=IsoTrkEB_PUR->at(i);
					h_IsoTrk_EBR_PUR->Fill(var,Weight);
				}
			} 
			if (IsoEcalEB_PUR->size()>0) {
				for (unsigned int i=0; i<IsoEcalEB_PUR->size();i++){
					float var=IsoEcalEB_PUR->at(i);
					h_IsoEcal_EBR_PUR->Fill(var,Weight);
				}
			}
			if (IsoHcalEB_PUR->size()>0) {
				for (unsigned int i=0; i<IsoEcalEB_PUR->size();i++){
					float var=IsoHcalEB_PUR->at(i);
					h_IsoHcal_EBR_PUR->Fill(var,Weight);
				}
			}
			if (HEEB->size()>0) {
				for (unsigned int i=0; i<HEEB->size();i++){
					float var=HEEB->at(i);
					h_HE_EBR->Fill(var,Weight);
				}
			}
			if (DeltaPhiTkCluEB->size()>0) {
				for (unsigned int i=0; i<DeltaPhiTkCluEB->size();i++){
					float var=DeltaPhiTkCluEB->at(i);
					h_DeltaPhiTkClu_EBR->Fill(var,Weight);
				}
			}
			if (DeltaEtaTkCluEB->size()>0) {
				for (unsigned int i=0; i<DeltaEtaTkCluEB->size();i++){
					float var=DeltaEtaTkCluEB->at(i);
					h_DeltaEtaTkClu_EBR->Fill(var,Weight);
				}
			}
			if (sigmaIeIeEB->size()>0) {
				for (unsigned int i=0; i<sigmaIeIeEB->size();i++){
					float var=sigmaIeIeEB->at(i);
					h_sigmaIeIe_EBR->Fill(var,Weight);
				}
			}

			//==== EE ====//

			if (IsoTrkEE_PUR->size()>0) {
				for (unsigned int i=0; i<IsoTrkEE_PUR->size();i++){
					float var=IsoTrkEE_PUR->at(i);
					h_IsoTrk_EER_PUR->Fill(var,Weight);
				}
			}
			if (IsoEcalEE_PUR->size()>0) {
				for (unsigned int i=0; i<IsoEcalEE_PUR->size();i++){
					float var=IsoEcalEE_PUR->at(i);
					h_IsoEcal_EER_PUR->Fill(var,Weight);
				}
			}
			if (IsoHcalEE_PUR->size()>0) {
				for (unsigned int i=0; i<IsoHcalEE_PUR->size();i++){
					float var=IsoHcalEE_PUR->at(i);
					h_IsoHcal_EER_PUR->Fill(var,Weight);
				}
			}
			if (HEEE->size()>0) {
				for (unsigned int i=0; i<HEEE->size();i++){
					float var=HEEE->at(i);
					h_HE_EER->Fill(var,Weight);
				}
			}
			if (DeltaPhiTkCluEE->size()>0) {
				for (unsigned int i=0; i<DeltaPhiTkCluEE->size();i++){
					float var=DeltaPhiTkCluEE->at(i);
					h_DeltaPhiTkClu_EER->Fill(var,Weight);
				}
			}
			if (DeltaEtaTkCluEE->size()>0) {
				for (unsigned int i=0; i<DeltaEtaTkCluEE->size();i++){
					float var=DeltaEtaTkCluEE->at(i);
					h_DeltaEtaTkClu_EER->Fill(var,Weight);
				}
			}
			if (sigmaIeIeEE->size()>0) {
				for (unsigned int i=0; i<sigmaIeIeEE->size();i++){
					float var=sigmaIeIeEE->at(i);
					h_sigmaIeIe_EER->Fill(var,Weight);
				}
			}
		}
	}

	vHistograms.push_back(h_IsoTrk_EBR_PUR); 
	vHistograms.push_back(h_IsoEcal_EBR_PUR);
	vHistograms.push_back(h_IsoHcal_EBR_PUR);
	vHistograms.push_back(h_HE_EBR);
	vHistograms.push_back(h_DeltaPhiTkClu_EBR);
	vHistograms.push_back(h_DeltaEtaTkClu_EBR);
	vHistograms.push_back(h_sigmaIeIe_EBR);
	
	vHistograms.push_back(h_IsoTrk_EER_PUR); 
	vHistograms.push_back(h_IsoEcal_EER_PUR);
	vHistograms.push_back(h_IsoHcal_EER_PUR);
	vHistograms.push_back(h_HE_EER);
	vHistograms.push_back(h_DeltaPhiTkClu_EER);
	vHistograms.push_back(h_DeltaEtaTkClu_EER);
	vHistograms.push_back(h_sigmaIeIe_EER);
	


//===================================//
//=========== DEBUG AREA ============//
//===================================//

	bool debug=0;
	if(debug==1){

		TCanvas * EB_plots;
		TCanvas * EE_plots;

		//EB - Create a Canvas and divide it in Pads
		EB_plots = new TCanvas("EB_plots","EB",400,20,1200,800);
		EB_plots->Divide(4,2);

		//First histogram
		EB_plots->cd(1);
		h_IsoTrk_EBR_PUR->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_IsoTrk_EBR_PUR->SetLineColor(1);
		h_IsoTrk_EBR_PUR->Draw();

		//WP Lines and Legend
		TLegend *leg = new TLegend(0.4,0.55,0.8,0.9);
		leg->SetBorderSize(0);
		leg->SetEntrySeparation(0.01);
		leg->SetFillColor(0);
		leg->AddEntry(h_IsoTrk_EBR_PUR,"MC Reweighted and PUR","l");
		TLine *Line80 = new TLine(0.09,0.,0.09,h_IsoTrk_EBR_PUR->GetMaximum());
		Line80->SetLineColor(kBlue);
		Line80->SetLineStyle(2);
		Line80->Draw();
		leg->AddEntry(Line80,"WP 80","l");
		TLine *Line90 = new TLine(0.12,0.,0.12,h_IsoTrk_EBR_PUR->GetMaximum());
		Line90->SetLineColor(kBlack);
		Line90->SetLineStyle(2);
		Line90->Draw();
		leg->AddEntry(Line90,"WP 90","l");
		leg->Draw();


		//Second histogram
		EB_plots->cd(2);
		h_IsoEcal_EBR_PUR->GetYaxis()->SetTitle("Number of Events");
		h_IsoEcal_EBR_PUR->Draw();
		BLine(0.07,0.,0.07,h_IsoEcal_EBR_PUR->GetMaximum());
		MLine(0.09,0.,0.09,h_IsoEcal_EBR_PUR->GetMaximum());

		EB_plots->cd(3);
		h_IsoHcal_EBR_PUR->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_IsoHcal_EBR_PUR->SetLineColor(1);
		h_IsoHcal_EBR_PUR->Draw();
		BLine(0.10,0.,0.10,h_IsoHcal_EBR_PUR->GetMaximum());
		MLine(0.10,0.,0.10,h_IsoHcal_EBR_PUR->GetMaximum());

		EB_plots->cd(4);
		h_HE_EBR->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_HE_EBR->SetLineColor(1);
		h_HE_EBR->Draw();
		BLine(0.04,0.,0.04,h_HE_EBR->GetMaximum());
		MLine(0.12,0.,0.12,h_HE_EBR->GetMaximum());

		EB_plots->cd(5);
		h_DeltaPhiTkClu_EBR->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_DeltaPhiTkClu_EBR->SetLineColor(1);
		h_DeltaPhiTkClu_EBR->Draw();
		BLine(0.06,0.,0.06,h_DeltaPhiTkClu_EBR->GetMaximum());
		MLine(0.8,0.,0.8,h_DeltaPhiTkClu_EBR->GetMaximum());

		EB_plots->cd(6);
		h_DeltaEtaTkClu_EBR->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_DeltaEtaTkClu_EBR->SetLineColor(1);
		h_DeltaEtaTkClu_EBR->Draw();
		BLine(0.004,0.,0.004,h_DeltaEtaTkClu_EBR->GetMaximum());
		MLine(0.007,0.,0.007,h_DeltaEtaTkClu_EBR->GetMaximum());

		EB_plots->cd(7);
		h_sigmaIeIe_EBR->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_sigmaIeIe_EBR->SetLineColor(1);
		h_sigmaIeIe_EBR->Draw();
		BLine(0.004,0.,0.004,h_sigmaIeIe_EBR->GetMaximum());
		MLine(0.007,0.,0.007,h_sigmaIeIe_EBR->GetMaximum());


		/*============================*/

		// qua dei draw copi diretto da all plots
		//EE - Create a Canvas and divide it in Pads
		EE_plots = new TCanvas("EE_plots","EE",400,20,1200,800);
		EE_plots->Divide(4,2);

		//First histogram
		EE_plots->cd(1);
		h_IsoTrk_EER_PUR->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_IsoTrk_EER_PUR->SetLineColor(1);
		h_IsoTrk_EER_PUR->Draw();

		//WP Lines and Legend
		TLegend *leg2 = new TLegend(0.4,0.55,0.8,0.9);
		leg2->SetBorderSize(0);
		leg2->SetEntrySeparation(0.01);
		leg2->SetFillColor(0);
		leg2->AddEntry(h_IsoTrk_EER_PUR,"MC Reweighted and PUR","l");
		Line80->SetLineColor(kBlue);
		Line80->SetLineStyle(2);
		Line80->Draw();
		leg2->AddEntry(Line80,"WP 80","l");
		Line90->SetLineColor(kBlack);
		Line90->SetLineStyle(2);
		Line90->Draw();
		leg2->AddEntry(Line90,"WP 90","l");
		leg2->Draw();


		//Second histogram
		EE_plots->cd(2);
		h_IsoEcal_EER_PUR->GetYaxis()->SetTitle("Number of Events");
		h_IsoEcal_EER_PUR->SetLineColor(1);
		h_IsoEcal_EER_PUR->Draw();
		BLine(0.07,0.,0.07,h_IsoEcal_EER_PUR->GetMaximum());
		MLine(0.09,0.,0.09,h_IsoEcal_EER_PUR->GetMaximum());

		EE_plots->cd(3);
		h_IsoHcal_EER_PUR->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_IsoHcal_EER_PUR->SetLineColor(1);
		h_IsoHcal_EER_PUR->Draw();
		BLine(0.10,0.,0.10,h_IsoHcal_EER_PUR->GetMaximum());
		MLine(0.10,0.,0.10,h_IsoHcal_EER_PUR->GetMaximum());

		EE_plots->cd(4);
		h_HE_EER->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_HE_EER->SetLineColor(1);
		h_HE_EER->Draw();
		BLine(0.04,0.,0.04,h_HE_EER->GetMaximum());
		MLine(0.12,0.,0.12,h_HE_EER->GetMaximum());

		EE_plots->cd(5);
		h_DeltaPhiTkClu_EER->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_DeltaPhiTkClu_EER->SetLineColor(1);
		h_DeltaPhiTkClu_EER->Draw();
		BLine(0.06,0.,0.06,h_DeltaPhiTkClu_EER->GetMaximum());
		MLine(0.8,0.,0.8,h_DeltaPhiTkClu_EER->GetMaximum());

		EE_plots->cd(6);
		h_DeltaEtaTkClu_EER->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_DeltaEtaTkClu_EER->SetLineColor(1);
		h_DeltaEtaTkClu_EER->Draw();
		BLine(0.004,0.,0.004,h_DeltaEtaTkClu_EER->GetMaximum());
		MLine(0.007,0.,0.007,h_DeltaEtaTkClu_EER->GetMaximum());

		EE_plots->cd(7);
		h_sigmaIeIe_EER->GetYaxis()->SetTitle("Number of Events");
		gPad->SetLogy(1);
		h_sigmaIeIe_EER->SetLineColor(1);
		h_sigmaIeIe_EER->Draw();
		BLine(0.004,0.,0.004,h_sigmaIeIe_EER->GetMaximum());
		MLine(0.007,0.,0.007,h_sigmaIeIe_EER->GetMaximum());

	}

return  vHistograms;

}
