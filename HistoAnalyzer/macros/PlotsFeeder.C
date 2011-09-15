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
//del	vector<TH1 *> vHistograms;

	
	//==================//
	//EB Reweight
	TH1D * h_IsoTrk_EBR; 
	TH1D * h_IsoEcal_EBR;
	TH1D * h_IsoHcal_EBR;
	//EB Reweight
	h_IsoTrk_EBR = new TH1D("h_IsoTrk_EBR","IsoTrk",tEB,tEBmin,tEBmax);
	h_IsoEcal_EBR = new TH1D("h_IsoEcal_EBR","IsoEcal",eEB,eEBmin,eEBmax);
	h_IsoHcal_EBR = new TH1D("h_IsoHcal_EBR","IsoHcal",hEB,hEBmin,hEBmax);

	//EE Reweight
	TH1D * h_IsoTrk_EER; 
	TH1D * h_IsoEcal_EER;
	TH1D * h_IsoHcal_EER;
	//EE Reweight
	h_IsoTrk_EER = new TH1D("h_IsoTrk_EER","IsoTrk",tEB,tEBmin,tEBmax);
	h_IsoEcal_EER = new TH1D("h_IsoEcal_EER","IsoEcal",eEB,eEBmin,eEBmax);
	h_IsoHcal_EER = new TH1D("h_IsoHcal_EER","IsoHcal",hEB,hEBmin,hEBmax);

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
	h_IsoTrk_EER_PUR = new TH1D("h_IsoTrk_EER_PUR","IsoTrk",tEB,tEBmin,tEBmax);
	h_IsoEcal_EER_PUR = new TH1D("h_IsoEcal_EER_PUR","IsoEcal",eEB,eEBmin,eEBmax);
	h_IsoHcal_EER_PUR = new TH1D("h_IsoHcal_EER_PUR","IsoHcal",hEB,hEBmin,hEBmax);


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
			if (IsoTrkEB->size()>0) {
				for (unsigned int i=0; i<IsoTrkEB->size();i++){
					float var=IsoTrkEB->at(i);
					h_IsoTrk_EBR->Fill(var,Weight);
				}
			}
			if (IsoEcalEB->size()>0) {
				for (unsigned int i=0; i<IsoEcalEB->size();i++){
					float var=IsoEcalEB->at(i);
					h_IsoEcal_EBR->Fill(var,Weight);
				}
			}
			if (IsoHcalEB->size()>0) {
				for (unsigned int i=0; i<IsoEcalEB->size();i++){
					float var=IsoHcalEB->at(i);
					h_IsoHcal_EBR->Fill(var,Weight);
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

			if (IsoTrkEE->size()>0) {
				for (unsigned int i=0; i<IsoTrkEE->size();i++){
					float var=IsoTrkEE->at(i);
					h_IsoTrk_EER->Fill(var,Weight);
				}
			}
			if (IsoEcalEE->size()>0) {
				for (unsigned int i=0; i<IsoEcalEE->size();i++){
					float var=IsoEcalEE->at(i);
					h_IsoEcal_EER->Fill(var,Weight);
				}
			}
			if (IsoHcalEE->size()>0) {
				for (unsigned int i=0; i<IsoHcalEE->size();i++){
					float var=IsoHcalEE->at(i);
					h_IsoHcal_EER->Fill(var,Weight);
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
	


return  histarray;

}
