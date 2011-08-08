// -*- C++ -*-
//
// Package:    HistoAnalyzer
// Class:      HistoAnalyzer
// 
/**\class HistoAnalyzer HistoAnalyzer.cc Histo/HistoAnalyzer/src/HistoAnalyzer.cc

*/
//
// Original Author:  Davide Scaini,Matteo Marone 27 1-013,+41227678527,
//         Created:  Tue Jul 12 14:54:43 CEST 2011
// $Id$
//
//

#include "Histo/HistoAnalyzer/interface/HistoAnalyzer.h"
#include "CondFormats/DataRecord/interface/L1GtStableParametersRcd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "CondFormats/L1TObjects/interface/L1GtStableParameters.h"
#include "CondFormats/DataRecord/interface/L1GtStableParametersRcd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

//
// member functions
//

// ------------ method called for each event  ------------
void
HistoAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  //Get The Run Parameters
  edm::LuminosityBlockNumber_t 	ls = iEvent.id().luminosityBlock();
  edm::EventNumber_t 		events = iEvent.id().event();
  edm::RunNumber_t 		run = iEvent.id().run();
  Run=run;
  Event=events;
  LS=ls;

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
  std::vector<std::pair<string,int> > HLTPres; 

 if (HLTResults.isValid() && doTheHLTAnalysis_) {
   /// Storing the Prescale information: loop over the triggers and record prescale
   
   unsigned int minimalPrescale(10000);
   unsigned int prescale(0);
   bool bit(true);
   std::pair<int,int> prescalepair;
   std::vector<int>  triggerSubset;
   for(unsigned int itrig = 0; itrig < triggerNames_.size(); ++itrig) {
     if(triggerIndices_[itrig]!=2048) {
       path.push_back(triggerNames_[itrig]);
       // check trigger response
       bit = HLTResults->accept(triggerIndices_[itrig]);
       triggerSubset.push_back(bit);
       
       if(bit) {
	 //If path is accepted, then together with its prescale it is stored in a map.
	 h_HLTbits->Fill(path[itrig].c_str(),1);
	 int prescaleset = hltConfig_.prescaleSet(iEvent,iSetup);
	 if(prescaleset!=-1) {
	   prescalepair = hltConfig_.prescaleValues(iEvent,iSetup,triggerNames_[itrig]);
	   if (debug) cout<<"prescale.first "<<prescalepair.first<<" prescalepair.second "<<prescalepair.second<<endl;
	   if((useCombinedPrescales_ && prescalepair.first<0) || prescalepair.second<0) {
	     edm::LogWarning("MyAnalyzer") << " Unable to get prescale from event for trigger " << triggerNames.triggerName(itrig) << " :" 
					   << prescalepair.first << ", " << prescalepair.second;
	   }
	   prescale = useCombinedPrescales_ ? prescalepair.first*prescalepair.second : prescalepair.second;
	   minimalPrescale = minimalPrescale <  prescale ? minimalPrescale : prescale;
	   if (debug) cout<<"prescale "<<prescale<<" minimal Prescale "<<minimalPrescale<<" for trigger "<<triggerNames.triggerName(itrig)<<endl;
	   string stringa=triggerNames_[itrig];
	   pair<string, int> pr2(stringa, prescale);
	   HLTPres.push_back(pr2);
	 } 
       }else {
	 //edm::LogError("HistoAnalyzer") << " Unable to get prescale set from event. Check that L1 data products are present.";
	 }
     }
     else {
       // that trigger is presently not in the menu
       triggerSubset.push_back(false);
     }
   }
 }
 
 HLTAndPrescale=HLTPres;
  HLTPres.clear();

 ///////////////////
 /// Electrons Study
 ///////////////////

 //Getting the Electron Collection
 using reco::GsfElectronCollection;
 Handle<GsfElectronCollection> gsfElectrons;
 iEvent.getByLabel(electronCollection_,gsfElectrons);
 
 //Loop over the gsf collection to study the variables distributions

 for(GsfElectronCollection::const_iterator itElect = gsfElectrons->begin();itElect != gsfElectrons->end(); ++itElect) {
      
    if (removePU_){
      double lepIsoRho;
      
      /////// Pileup density "rho" for lepton isolation subtraction /////
      
      edm::Handle<double> rhoLepIso;
      const edm::InputTag eventrhoLepIso("kt6PFJetsForIsolation", "rho");
      iEvent.getByLabel(eventrhoLepIso, rhoLepIso);
      if( *rhoLepIso == *rhoLepIso)  lepIsoRho = *rhoLepIso;
      else  lepIsoRho =  -999999.9;

      if (fabs (itElect->eta()) <= 1.4442) {      
	IsoEcal = (itElect->dr03EcalRecHitSumEt () - lepIsoRho*0.096) / itElect->et ();
	IsoTrk = (itElect->dr03TkSumPt () - lepIsoRho*0) / itElect->et ();
	IsoHcal = (itElect->dr03HcalTowerSumEt ()  - lepIsoRho*0.020) / itElect->et ();
	HE = itElect->hadronicOverEm();
      }
      else{
	IsoEcal = (itElect->dr03EcalRecHitSumEt () - lepIsoRho*0.044) / itElect->et ();
	IsoTrk = (itElect->dr03TkSumPt () - lepIsoRho*0) / itElect->et ();
	IsoHcal = (itElect->dr03HcalTowerSumEt ()  - lepIsoRho*0.041) / itElect->et ();
	HE = itElect->hadronicOverEm();
      }
    }
    else{
      // Define Isolation variables
      IsoTrk = (itElect->dr03TkSumPt () / itElect->et ());
      IsoEcal = (itElect->dr03EcalRecHitSumEt () / itElect->et ());
      IsoHcal = (itElect->dr03HcalTowerSumEt () / itElect->et ());
      HE = itElect->hadronicOverEm();
    }

   //Assign Isolation variables
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

 ///////////////////////
 ///// Vertex Analysis
 ///////////////////////

 edm::Handle<reco::VertexCollection> Vertexes;
 iEvent.getByLabel(VertexCollectionTag_, Vertexes);
 numberOfVertices = Vertexes->size();

 
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

	//////////////////
	//// Z->EE SELECTION VARIABLES 
	////////////////// 
  
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
	
	//HLT and Prescale
	treeVJ_->Branch("HLTAndPrescale",&HLTAndPrescale);

	//Run Properties
	treeVJ_->Branch("Run",&Run);
	treeVJ_->Branch("LS",&LS);
	treeVJ_->Branch("Event",&Event);
	
	//Vertices
	treeVJ_->Branch("numberOfVertices",&numberOfVertices);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
HistoAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
HistoAnalyzer::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup)
{
//HLT names
   std::vector<std::string>  hlNames;
   bool changed (true);
   if (hltConfig_.init(iRun,iSetup,triggerCollection_.process(),changed)) {
     if (changed) {
       hlNames = hltConfig_.triggerNames();
     }
   } else {
     edm::LogError("MyAnalyzer") << " HLT config extraction failure with process name " << triggerCollection_.process();
   }
   if (debug) cout<<"useAllTriggers?"<<useAllTriggers_<<endl;
   if(useAllTriggers_) triggerNames_ = hlNames;
   //triggerNames_ = hlNames;
   //HLT indices
   triggerIndices_.clear();
   for(unsigned int itrig = 0; itrig < triggerNames_.size(); ++itrig) {
     if(find(hlNames.begin(),hlNames.end(),triggerNames_[itrig])!=hlNames.end())
       triggerIndices_.push_back(hltConfig_.triggerIndex(triggerNames_[itrig]));
     else
       triggerIndices_.push_back(2048);
   }

   if (debug){
     // text (debug) output
     int i=0;
     for(std::vector<std::string>::const_iterator it = triggerNames_.begin(); it<triggerNames_.end();++it) {
       std::cout << (i++) << " = " << (*it) << std::endl;
     } 
   }

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
}

//define this as a plug-in
DEFINE_FWK_MODULE(HistoAnalyzer);
