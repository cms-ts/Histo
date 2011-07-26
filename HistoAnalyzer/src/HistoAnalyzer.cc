// -*- C++ -*-
//
// Package:    HistoAnalyzer
// Class:      HistoAnalyzer
// 
/**\class HistoAnalyzer HistoAnalyzer.cc Histo/HistoAnalyzer/src/HistoAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Davide Scaini,27 1-013,+41227678527,
//         Created:  Tue Jul 12 14:54:43 CEST 2011
// $Id$
//
//

#include "Histo/HistoAnalyzer/interface/HistoAnalyzer.h"


//
// member functions
//

// ------------ method called for each event  ------------
void
HistoAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{


///  edm::LuminosityBlockNumber_t 	LS = iEvent.id().luminosityBlock();
///  edm::EventNumber_t 		Events = iEvent.id().event();
///  edm::RunNumber_t 		Run = iEvent.id().run();

 //IMPORTANTE
 clean_vectors();
 nEvents_++;

 //Define Isolation variables
 double IsoTrk;
 double IsoEcal;
 double IsoHcal;
 double HE;
 double fbrem;
 double etaSC;

 //Define ID variables
 float DeltaPhiTkClu;
 float DeltaEtaTkClu;
 float sigmaIeIe;

 //Define Conversion Rejection Variables
 float Dcot;
 float Dist;
 int NumberOfExpectedInnerHits;
 //EODefinitions


 //Match The HLT Trigger
 using edm::TriggerResults;
 Handle<TriggerResults> HLTResults;
 iEvent.getByLabel(triggerCollection_, HLTResults);
 const edm::TriggerNames & triggerNames = iEvent.triggerNames(*HLTResults);
 int trigger_size = HLTResults->size();
 bool boolpass=0;

//cout << "trigger size is " << trigger_size << "\n";
 if (HLTResults.isValid()) {
	 //	if (nEvents_==1) { //questo ti permette di fare il lavro solo al primo evento... sarÃ  utile se farme le cose in maniera diversa piÃ avanti
	 for (int i=0; i<trigger_size;i++){
		 path.push_back(triggerNames.triggerName(i));
		 int pos=(int)triggerNames.triggerIndex(triggerNames.triggerName(i));
		 if(pos<trigger_size){
			 //accept serve per sapere se quel particolare path di HLT Ã¨ presente o meno
			 boolpass=(bool) HLTResults->accept(pos);
			 if (boolpass) {
				 //std::cout<<"Matched "<<path[i]<< "\n";
				 h_HLTbits->Fill(path[i].c_str(),1);
				 if(path[i]=="HLT_Ele10_LW_L1R"){b_HLT_Ele10_LW_L1R=1;}
				 if(path[i]=="HLT_Ele15_SW_L1R"){b_HLT_Ele15_SW_L1R=1;}
				 if(path[i]=="HLT_Ele15_SW_CaloEleId_L1R"){b_HLT_Ele15_SW_CaloEleId_L1R=1;}
				 if(path[i]=="HLT_Ele17_SW_CaloEleId_L1R"){b_HLT_Ele17_SW_CaloEleId_L1R=1;}
				 if(path[i]=="HLT_Ele17_SW_TightEleId_L1R"){b_HLT_Ele17_SW_TightEleId_L1R=1;}
				 if(path[i]=="HLT_Ele17_SW_TightEleId_L1R_v2"){b_HLT_Ele17_SW_TightEleId_L1R_v2=1;}
				 if(path[i]=="HLT_Ele17_SW_TightEleId_L1R_v3"){b_HLT_Ele17_SW_TightEleId_L1R_v3=1;}
				 if(path[i]=="HLT_Photon10_L1R"){b_HLT_Photon10_L1R=1;}
				 if(path[i]=="HLT_Photon15_L1R"){b_HLT_Photon15_L1R=1;}
				 if(path[i]=="HLT_Photon15_Cleaned_L1R"){b_HLT_Photon15_Cleaned_L1R=1;}
				 if(path[i]=="HLT_Photon26_IsoVL_Photon18_IsoVL_v3"){b_HLT_Photon26_IsoVL_Photon18_IsoVL_v3=1;}
			 }
			 //else{std::cout<<"Not Matched \n";}
		 }
	 }
	 //	}  
 }



   //Getting the Electron Collection
   using reco::GsfElectronCollection;
   Handle<GsfElectronCollection> gsfElectrons;
   iEvent.getByLabel(electronCollection_,gsfElectrons);

   for(GsfElectronCollection::const_iterator itElect = gsfElectrons->begin();
		   itElect != gsfElectrons->end();                      
		   ++itElect) {


	   //Assign Isolation variables
	   IsoTrk	= (itElect->dr03TkSumPt() / itElect->et());
	   IsoEcal	= (itElect->dr03EcalRecHitSumEt() / itElect->et());
	   IsoHcal 	= (itElect->dr03HcalTowerSumEt() / itElect->et());
	   HE		= (itElect->hcalOverEcal());
	   fbrem	= itElect->fbrem();
	   etaSC	= itElect->superCluster()->eta();

	   //Assign ID variables
	   DeltaPhiTkClu = itElect->deltaPhiSuperClusterTrackAtVtx();
	   DeltaEtaTkClu = itElect->deltaEtaSuperClusterTrackAtVtx();
	   sigmaIeIe     = itElect->sigmaIetaIeta ();

	   //Assign Conversion Rejection Variables
	   Dcot		= itElect->convDcot();
	   Dist 	= itElect->convDist();
	   NumberOfExpectedInnerHits = itElect->gsfTrack()->trackerExpectedHitsInner().numberOfHits();

	   //Filling Histos
	   //EB
	   if (fabs (itElect->eta()) <= 1.4442) {
		   //histos
		   h_IsoTrk_EB->Fill(IsoTrk);
		   h_IsoEcal_EB->Fill(IsoEcal);
		   h_IsoHcal_EB->Fill(IsoHcal);
		   h_HE_EB->Fill(HE);

		   h_DeltaPhiTkClu_EB->Fill(DeltaPhiTkClu);
		   h_DeltaEtaTkClu_EB->Fill(DeltaEtaTkClu);
		   h_sigmaIeIe_EB->Fill(sigmaIeIe);

		   //vectors
		   vIsoTrkEB.push_back(IsoTrk);
		   vIsoEcalEB.push_back(IsoEcal);
		   vIsoHcalEB.push_back(IsoHcal);
		   vHEEB.push_back(HE);
		   vDeltaPhiTkCluEB.push_back(DeltaPhiTkClu);
		   vDeltaEtaTkCluEB.push_back(DeltaEtaTkClu);
		   vsigmaIeIeEB.push_back(sigmaIeIe);
	   }
	   //EE
	   if (fabs (itElect->eta()) >= 1.5660
			   && fabs (itElect->eta()) <= 2.5000) {
		   //histos
		   h_IsoTrk_EE->Fill(IsoTrk);
		   h_IsoEcal_EE->Fill(IsoEcal);
		   h_IsoHcal_EE->Fill(IsoHcal);
		   h_HE_EE->Fill(HE);

		   h_DeltaPhiTkClu_EE->Fill(DeltaPhiTkClu);
		   h_DeltaEtaTkClu_EE->Fill(DeltaEtaTkClu);
		   h_sigmaIeIe_EE->Fill(sigmaIeIe);

		   //vectors
		   vIsoTrkEE.push_back(IsoTrk);
		   vIsoEcalEE.push_back(IsoEcal);
		   vIsoHcalEE.push_back(IsoHcal);
		   vHEEE.push_back(HE);
		   vDeltaPhiTkCluEE.push_back(DeltaPhiTkClu);
		   vDeltaEtaTkCluEE.push_back(DeltaEtaTkClu);
		   vsigmaIeIeEE.push_back(sigmaIeIe);

	   }

	   //Common (histo)
	   h_fbrem->Fill(fbrem);
	   h_etaSC->Fill(etaSC);
	   h_Dcot->Fill(Dcot);
	   h_Dist->Fill(Dist);
	   h_NumberOfExpectedInnerHits->Fill(NumberOfExpectedInnerHits);

	   //Common (vector)
	   vfbrem.push_back(fbrem);
	   vetaSC.push_back(etaSC);
	   vDcot.push_back(Dcot);
	   vDist.push_back(Dcot);
	   vNumberOfExpectedInnerHits.push_back(NumberOfExpectedInnerHits);

   }//End for


   //FIXME get axis per tutti, metto solo la Y perchÃ© la  Ã¨ in unia' UFO <_O_>
   histNum-> GetXaxis()-> SetTitle("N_{ele}");
   histNum-> GetYaxis()-> SetTitle("Events");
   histNum->Fill((*gsfElectrons).size());

   h_IsoTrk_EB->GetYaxis()-> SetTitle("Events");
   h_IsoEcal_EB->GetYaxis()-> SetTitle("Events");
   h_IsoHcal_EB->GetYaxis()-> SetTitle("Events");
   h_HE_EB->GetYaxis()-> SetTitle("Events");
   h_IsoTrk_EE->GetYaxis()-> SetTitle("Events");
   h_IsoEcal_EE->GetYaxis()-> SetTitle("Events");
   h_IsoHcal_EE->GetYaxis()-> SetTitle("Events");
   h_HE_EE->GetYaxis()-> SetTitle("Events");
   h_fbrem->GetYaxis()-> SetTitle("Events");
   h_etaSC->GetYaxis()-> SetTitle("Events");

   h_DeltaPhiTkClu_EB->GetYaxis()-> SetTitle("Events");
   h_DeltaEtaTkClu_EB->GetYaxis()-> SetTitle("Events");
   h_sigmaIeIe_EB->GetYaxis()-> SetTitle("Events");
   h_DeltaPhiTkClu_EE->GetYaxis()-> SetTitle("Events");
   h_DeltaEtaTkClu_EE->GetYaxis()-> SetTitle("Events");
   h_sigmaIeIe_EE->GetYaxis()-> SetTitle("Events");


   h_Dcot->GetYaxis()-> SetTitle("Events");
   h_Dist->GetYaxis()-> SetTitle("Events");
   h_NumberOfExpectedInnerHits->GetYaxis()-> SetTitle("Events");

   //--------------------------------//
   //---------Fill del Tree----------//
   treeVJ_->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
HistoAnalyzer::beginJob()
{

nEvents_ = 0;

	//TFile and TTree initialization
	treeVJ_= new TTree("treeVJ_","treeVJ_");
	//EB
	treeVJ_->Branch("IsoTrkEB","IsoTrkEB",&vIsoTrkEB);
	treeVJ_->Branch("IsoEcalEB","IsoEcalEB",&vIsoEcalEB);
	treeVJ_->Branch("IsoHcalEB","IsoHcalEB",&vIsoHcalEB);
	treeVJ_->Branch("HEEB","HEEB",&vHEEB);
	treeVJ_->Branch("DeltaPhiTkCluEB","DeltaPhiTkCluEB",&vDeltaPhiTkCluEB);
	treeVJ_->Branch("DeltaEtaTkCluEB","DeltaEtaTkCluEB",&vDeltaEtaTkCluEB);
	treeVJ_->Branch("sigmaIeIeEB","sigmaIeIeEB",&vsigmaIeIeEB);
	
	//EB
	treeVJ_->Branch("IsoTrkEE","IsoTrkEE",&vIsoTrkEE);
	treeVJ_->Branch("IsoEcalEE","IsoEcalEE",&vIsoEcalEE);
	treeVJ_->Branch("IsoHcalEE","IsoHcalEE",&vIsoHcalEE);
	treeVJ_->Branch("HEEE","HEEE",&vHEEE);
	treeVJ_->Branch("DeltaPhiTkCluEE","DeltaPhiTkCluEE",&vDeltaPhiTkCluEE);
	treeVJ_->Branch("DeltaEtaTkCluEE","DeltaEtaTkCluEE",&vDeltaEtaTkCluEE);
	treeVJ_->Branch("sigmaIeIeEE","sigmaIeIeEE",&vsigmaIeIeEE);

	//Common
	treeVJ_->Branch("fbrem","fbrem",&vfbrem);
	treeVJ_->Branch("etaSC","etaSC",&vetaSC);
	treeVJ_->Branch("Dcot","Dcot",&vDcot);
	treeVJ_->Branch("Dist","Dist",&vDist);
	treeVJ_->Branch("NumberOfExpectedInnerHits","NumberOfExpectedInnerHits",&vNumberOfExpectedInnerHits);

	//Branches for HLT variables
	treeVJ_->Branch("HLT_Ele10_LW_L1R",&b_HLT_Ele10_LW_L1R,"HLT_Ele10_LW_L1R/S");
	treeVJ_->Branch("HLT_Ele15_LW_L1R",&b_HLT_Ele15_SW_L1R,"HLT_Ele15_LW_L1R/S");
	treeVJ_->Branch("HLT_Ele15_SW_CaloEleId_L1R",&b_HLT_Ele15_SW_CaloEleId_L1R,"HLT_Ele15_SW_CaloEleId_L1R/S");
	treeVJ_->Branch("HLT_Ele17_SW_CaloEleId_L1R",&b_HLT_Ele17_SW_CaloEleId_L1R,"HLT_Ele17_SW_CaloEleId_L1R/S");
	treeVJ_->Branch("HLT_Ele17_SW_TightEleId_L1R",&b_HLT_Ele17_SW_TightEleId_L1R,"HLT_Ele17_SW_TightEleId_L1R/S");
	treeVJ_->Branch("HLT_Ele17_SW_TightEleId_L1R_v2",&b_HLT_Ele17_SW_TightEleId_L1R_v2,"HLT_Ele17_SW_TightEleId_L1R_v2/S");
	treeVJ_->Branch("HLT_Ele17_SW_TightEleId_L1R_v3",&b_HLT_Ele17_SW_TightEleId_L1R_v3,"HLT_Ele17_SW_TightEleId_L1R_v3/S");
	treeVJ_->Branch("HLT_Photon10_L1R",&b_HLT_Photon10_L1R,"HLT_Photon10_L1R/S");
	treeVJ_->Branch("HLT_Photon15_L1R",&b_HLT_Photon15_L1R,"HLT_Photon15_L1R/S");
	treeVJ_->Branch("HLT_Photon15_Cleaned_L1R",&b_HLT_Photon15_Cleaned_L1R,"HLT_Photon15_Cleaned_L1R/S");
	treeVJ_->Branch("HLT_Photon26_IsoVL_Photon18_IsoVL_v3",&b_HLT_Photon26_IsoVL_Photon18_IsoVL_v3,"HLT_Photon26_IsoVL_Photon18_IsoVL_v3/S");

}

// ------------ method called once each job just after ending the event loop  ------------
void 
HistoAnalyzer::endJob() 
{


}

// ------------ method called when starting to processes a run  ------------
void 
HistoAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
HistoAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
HistoAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
HistoAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HistoAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

 //Specify that only 'tracks' is allowed
 //To use, remove the default given above and uncomment below
 //ParameterSetDescription desc;
 //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
 //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HistoAnalyzer);
