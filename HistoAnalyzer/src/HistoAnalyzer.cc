// -*- C++ -*-
//
// Package:    HistoProducer
// Class:      HistoProducer
// 
/**\class HistoProducer HistoProducer.cc Histo/HistoProducer/src/HistoProducer.cc

*/
//
// Original Author:  Davide Scaini,Matteo Marone 27 1-013,+41227678527,
//         Created:  Tue Jul 12 14:54:43 CEST 2011
// $Id: HistoAnalyzer.cc,v 1.30 2011/11/30 15:47:26 marone Exp $
//
//

#include "Histo/HistoAnalyzer/interface/HistoAnalyzer.h"
#include "CondFormats/DataRecord/interface/L1GtStableParametersRcd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "CondFormats/L1TObjects/interface/L1GtStableParameters.h"
#include "CondFormats/DataRecord/interface/L1GtStableParametersRcd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h" 


//PU reweight
#include "Histo/HistoAnalyzer/interface/Flat10.h"
#include "Histo/HistoAnalyzer/interface/ZSkim_v1.h"
#include "DataFormats/Common/interface/MergeableCounter.h"


bool hltispresent=1;

//
// member functions
//

// ------------ method called for each event  ------------
void
HistoProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // We need the output Muon association collection to fill 
  std::auto_ptr<std::vector<float> > EventWeight( new std::vector<float>);
  //IMPORTANTE
  clean_vectors();
  nEvents_++;
  
  
	//Get The Run Parameters
  Timestamp = iEvent.time().value(); //lo fa ogni vento, ma se vuoi farlo ogni run, basta che ci metti prima if(nEvents_==1)
  edm::LuminosityBlockNumber_t 	ls = iEvent.id().luminosityBlock();
  edm::EventNumber_t 		events = iEvent.id().event();
  edm::RunNumber_t 		run = iEvent.id().run();
  Run=run;
  Event=events;
  LS=ls;
  
  //Add event counters
  lumi  = iEvent.luminosityBlock();
  //Isolation Variables for Removed PU
  double IsoTrk_PUR;
  double IsoEcal_PUR;
  double IsoHcal_PUR;
  
  //Define Isolation Variables (Non-Removed PU)
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
  
  
  
  if (HLTResults.isValid() && doTheHLTAnalysis_) {
    /// Storing the Prescale information: loop over the triggers and record prescale
    
    // Matching the HLT information event per event if no hlt info is present in iRun
    if(hltispresent==false){
      std::vector<std::string>  hlNames;
      hlNames.clear();
      hlNames=triggerNames.triggerNames();
      triggerIndices_.clear();
      unsigned int myflag=0;
      
      for(unsigned int itrig = 0; itrig < triggerNames_.size(); ++itrig) {
	if(find(hlNames.begin(),hlNames.end(),triggerNames_[itrig])!=hlNames.end()){
	  triggerIndices_.push_back(hltConfig_.triggerIndex(triggerNames_[itrig]));
	}
	else{
	  triggerIndices_.push_back(2048);
	  myflag++;
	}
      }
      if(myflag==triggerNames_.size()) hltispresent=false;
      else hltispresent=true; //cosi' prendo una sola volta l'hlt path tanto nie miei studi mi serve l'hlt path per run...
    }
    
    
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
	  
	  //WORKING HERE
	  //Se il path non esiste gia' nella lista dei paths, lo aggiungo
	  TString tstringa=(TString)triggerNames_[itrig]; //ci serve per l'IF
	  std::string stringa=(string)triggerNames_[itrig];
	  
	  if ((tstringa.Contains("Ele") || tstringa.Contains("Photon") || tstringa.Contains("FinalPath") )){
	    //Se il path e' Ele* o Photon* allora riempiamo l'istogramma
	    h_HLTbits->Fill(stringa.c_str(),1); //questo fa il plottino... 
	    
	    
	    if( !(find(HLTPaths.begin(), HLTPaths.end(), stringa)!=HLTPaths.end()) ){  
	      //If path is accepted, then together with its prescale it is stored in a map.
	      int prescaleset = hltConfig_.prescaleSet(iEvent,iSetup);
	      if(prescaleset!=-1) {
		prescalepair = hltConfig_.prescaleValues(iEvent,iSetup,triggerNames_[itrig]);
		if (debug) cout<<"prescale.first "<<prescalepair.first<<" prescalepair.second "<<prescalepair.second<<endl;
		//getting prescale info
		prescale = useCombinedPrescales_ ? prescalepair.first*prescalepair.second : prescalepair.second;
		if((useCombinedPrescales_ && prescalepair.first<0) || prescalepair.second<0) {
		  edm::LogWarning("MyAnalyzer") << " Unable to get prescale from event for trigger " << triggerNames.triggerName(itrig) << " :" << prescalepair.first << ", " << prescalepair.second;
		  prescale = -999;
		}
		
		if(prescalepair.first<0 || prescalepair.second<0) { prescale = -999; }
	      }
	      
	      minimalPrescale = minimalPrescale <  prescale ? minimalPrescale : prescale;
	      if (debug) cout<<"prescale "<<prescale<<" minimal Prescale "<<minimalPrescale<<" for trigger "<<triggerNames.triggerName(itrig)<<endl;
	      
	      
	      HLTPaths.push_back(stringa);
	      HLTPrescales.push_back(prescale);
	      vRun.push_back(Run);
	    }//chiusura if find ...
	    
	    //Qui si riempie il vettore che mi servira'  per calcolare il ratio
	    if(HLTValue.size()==0){ HLTValue.push_back(1); HLTNames.push_back(stringa);
	    }
	    else{
	      bool already = 0;
	      for(unsigned int dd=0;dd<HLTValue.size();dd++){
		
		if(HLTNames[dd]==stringa){HLTValue[dd] = HLTValue[dd] + 1;
		  already=1;
		}
		
	      } //chiusura for per vedere se c'e' il path
	      if(!already){ HLTValue.push_back(1); HLTNames.push_back(stringa);
	      }
	    }
	  } // Chiusura filtro du HLTPaths
	} //Chiusura del if(bit)
	else {
	  //edm::LogError("HistoProducer") << " Unable to get prescale set from event. Check that L1 data products are present.";
	}
      }
      else {
	// that trigger is presently not in the menu
	triggerSubset.push_back(false);
      }
    } //chiusura for
 } //chiusura HLT studies
  
  
  //////////////////
  ////// Pile UP studies
  /////////////////
  
  if (usingMC_){
    edm::InputTag PileupSrc_ = (edm::InputTag) "addPileupInfo";
    Handle<std::vector< PileupSummaryInfo > >  PupInfo;
    iEvent.getByLabel(PileupSrc_, PupInfo);
    
    std::vector<PileupSummaryInfo>::const_iterator PVI;
    
    /*
///////////////////
//// New way
/////////

int npv = -1;
float sum_nvtx = 0;

for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
npv = PVI->getPU_NumInteractions();
sum_nvtx += float(npv);
}

std::vector<float> simulated;
std::vector<float> trueD;
edm::LumiReWeighting LumiWeights_;


//Calculate the distributions (our data and MC)
for( int i=0; i<25; ++i) {
trueD.push_back(Data2011A_real[i]); // Name of the vector calculated with estimatedPU.py!
simulated.push_back(MikeSmeared_v2[i]); // Name of the vector included in Flat10.h !
}

LumiWeights_ = edm::LumiReWeighting(simulated, trueD);
float ave_nvtx = sum_nvtx/3.;
double MyWeight = LumiWeights_.weight3BX( ave_nvtx );
//////End of new version
*/
    
    /////////
    // 3D reweighting

    if (cold){
      LumiWeights_ = edm::Lumi3DReWeighting("/gpfs/cms/data/2011/tools/Summer11_Generated_Flat10Tail.root", "/gpfs/cms/data/2011/tools/Data2011A_160404-173692.root", "pileup", "pileup");
      LumiWeights_.weight3D_init( ScaleFactor );
      cout<<"Initializing weight3D at Factor Scale ->"<<ScaleFactor<<endl;
      cold=false;
    }
    
    int nm1 = -1; int n0 = -1; int np1 = -1;
    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
      
      int BX = PVI->getBunchCrossing();
      
      if(BX == -1) { 
	nm1 = PVI->getPU_NumInteractions();
      }
      if(BX == 0) { 
	n0 = PVI->getPU_NumInteractions();
      }
      if(BX == 1) { 
	np1 = PVI->getPU_NumInteractions();
      }
    }
    double MyWeight3D = LumiWeights_.weight3D( nm1,n0,np1);
    // end 3D
    /////////
    
    //////// Storing info
    Weight=MyWeight3D;
    EventWeight->push_back(MyWeight3D);
    if (MyWeight3D<0.01) cout<<"You are over-correcting in the MC reweight, HistoAnalyzer.cc!!!"<<endl;
  }
  else { 
    EventWeight->push_back(1); 
  }
  
  
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
			if( *rhoLepIso == *rhoLepIso) { 
				lepIsoRho = *rhoLepIso;
				vRho.push_back(lepIsoRho);
			}
			else { 
				lepIsoRho =  999999.9;
				vRho.push_back(lepIsoRho);
			}

			//EB
			if (fabs (itElect->eta()) <= 1.4442) {      
				//
				IsoTrk_PUR = (itElect->dr03TkSumPt () - lepIsoRho*0) / itElect->et ();
				IsoEcal_PUR = (itElect->dr03EcalRecHitSumEt () - lepIsoRho*0.096) / itElect->et ();
				IsoHcal_PUR = (itElect->dr03HcalTowerSumEt ()  - lepIsoRho*0.020) / itElect->et ();
				if(IsoEcal_PUR<=0.) IsoEcal_PUR=0.;
				if(IsoHcal_PUR<=0.) IsoHcal_PUR=0.;
				//vectors
				vIsoTrkEB_PUR.push_back(IsoTrk_PUR);
				vIsoEcalEB_PUR.push_back(IsoEcal_PUR);
				vIsoHcalEB_PUR.push_back(IsoHcal_PUR);
			}
			//EE
			if (fabs (itElect->eta()) >= 1.5660
					&& fabs (itElect->eta()) <= 2.5000) {
				//
				IsoTrk_PUR = (itElect->dr03TkSumPt () - lepIsoRho*0) / itElect->et ();
				IsoEcal_PUR = (itElect->dr03EcalRecHitSumEt () - lepIsoRho*0.044) / itElect->et ();
				IsoHcal_PUR = (itElect->dr03HcalTowerSumEt ()  - lepIsoRho*0.041) / itElect->et ();
				if(IsoEcal_PUR<=0.) IsoEcal_PUR=0.;
				if(IsoHcal_PUR<=0.) IsoHcal_PUR=0.;
				//vectors
				vIsoTrkEE_PUR.push_back(IsoTrk_PUR);
				vIsoEcalEE_PUR.push_back(IsoEcal_PUR);
				vIsoHcalEE_PUR.push_back(IsoHcal_PUR);
			}
		}


		//Non-Removed-PU variables
		// Define Isolation variables
		IsoTrk = (itElect->dr03TkSumPt () / itElect->et ());
		IsoEcal = (itElect->dr03EcalRecHitSumEt () / itElect->et ());
		IsoHcal = (itElect->dr03HcalTowerSumEt () / itElect->et ());
		HE = itElect->hadronicOverEm();

		//Assign Isolation variables
		fbrem	= itElect->fbrem();
		etaSC	= itElect->superCluster()->eta();
		//etaSCPF      = itElect->pflowSuperCluster()->eta();

		//Assign ID variables
		DeltaPhiTkClu = itElect->deltaPhiSuperClusterTrackAtVtx();
		DeltaEtaTkClu = itElect->deltaEtaSuperClusterTrackAtVtx();
		sigmaIeIe     = itElect->sigmaIetaIeta ();

		//Assign Conversion Rejection Variables
		Dcot		= itElect->convDcot();
		Dist 	= itElect->convDist();
		NumberOfExpectedInnerHits = itElect->gsfTrack()->trackerExpectedHitsInner().numberOfHits();

		//Filling Histos and Vectors
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



	//Histograms
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
	nEventsPerStep_->GetYaxis()->SetTitle("Events");

	///////////////////////
	///// Vertex Analysis
	///////////////////////

	edm::Handle<reco::VertexCollection> Vertexes;
	iEvent.getByLabel(VertexCollectionTag_, Vertexes);
	numberOfVertices = Vertexes->size();


	//--------------------------------//
	//---------Fill del Tree----------//
	treeVJ_->Fill();
	iEvent.put( EventWeight,"EventWeight" );
}


// ------------ method called once each job just before starting event loop  ------------
	void 
HistoProducer::beginJob()
{
	nEvents_ = 0;

HLTPaths.clear();
HLTPrescales.clear();
HLTNames.clear();
HLTValue.clear();
HLTRatio.clear();
vRun.clear();

//Initialize reweighting..
 if (usingMC_) {
   ScaleFactor=1.0;
   //LumiWeights_.weight3D_init( ScaleFactor ); UNESSENTIAL AT FIRST SIGHT! CHECK IF REWEWIGHT IS SCREWED UP!!!
 }
	//TFile and TTree initialization
	treeVJ_= new TTree("treeVJ_","treeVJ_");
	treeHLT_= new TTree("treeHLT_","treeHLT_");

	//////////////////
	//// Z->EE SELECTION VARIABLES 
	////////////////// 

	//EB PileUp REMOVED
	treeVJ_->Branch("IsoTrkEB_PUR","IsoTrkEB_PUR",&vIsoTrkEB_PUR);
	treeVJ_->Branch("IsoEcalEB_PUR","IsoEcalEB_PUR",&vIsoEcalEB_PUR);
	treeVJ_->Branch("IsoHcalEB_PUR","IsoHcalEB_PUR",&vIsoHcalEB_PUR);

	//EE PileUp REMOVED
	treeVJ_->Branch("IsoTrkEE_PUR","IsoTrkEE_PUR",&vIsoTrkEE_PUR);
	treeVJ_->Branch("IsoEcalEE_PUR","IsoEcalEE_PUR",&vIsoEcalEE_PUR);
	treeVJ_->Branch("IsoHcalEE_PUR","IsoHcalEE_PUR",&vIsoHcalEE_PUR);

	//EB
	treeVJ_->Branch("IsoTrkEB","IsoTrkEB",&vIsoTrkEB);
	treeVJ_->Branch("IsoEcalEB","IsoEcalEB",&vIsoEcalEB);
	treeVJ_->Branch("IsoHcalEB","IsoHcalEB",&vIsoHcalEB);
	treeVJ_->Branch("HEEB","HEEB",&vHEEB);
	treeVJ_->Branch("DeltaPhiTkCluEB","DeltaPhiTkCluEB",&vDeltaPhiTkCluEB);
	treeVJ_->Branch("DeltaEtaTkCluEB","DeltaEtaTkCluEB",&vDeltaEtaTkCluEB);
	treeVJ_->Branch("sigmaIeIeEB","sigmaIeIeEB",&vsigmaIeIeEB);

	//EE
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
	treeVJ_->Branch("Rho","Rho",&vRho);

	//HLT and Prescale
	treeHLT_->Branch("HLTPaths",&HLTPaths);
	treeHLT_->Branch("HLTPrescales",&HLTPrescales);
	treeHLT_->Branch("HLTNames",&HLTNames);
	treeHLT_->Branch("HLTValue",&HLTValue);
	treeHLT_->Branch("Timestamp",&Timestamp);
	treeHLT_->Branch("vRun",&vRun);

	//Run Properties
	treeVJ_->Branch("Run",&Run);
	treeVJ_->Branch("LS",&LS);
	treeVJ_->Branch("Event",&Event);

	//Vertices
	treeVJ_->Branch("numberOfVertices",&numberOfVertices);

	//SC
	treeVJ_->Branch("etaSC",&etaSCPF);

	//MC
	treeVJ_->Branch("Weight",&Weight);
}

// ------------ method called once each job just after ending the event loop  ------------
	void 
HistoProducer::endJob() 
{
  //nEventsPerStep_->Write();
}

// ------------ method called when starting to processes a run  ------------
	void 
HistoProducer::beginRun(edm::Run& iRun, const edm::EventSetup& iSetup)
{

hltispresent=true;
	//HLT names
	std::vector<std::string>  hlNames;
	hlNames.clear();
	bool changed (true);
	if (hltConfig_.init(iRun,iSetup,triggerCollection_.process(),changed)) {
		if (changed) {
			hlNames = hltConfig_.triggerNames();
		}
	} else {
		edm::LogError("MyAnalyzer") << " HLT config extraction failure with process name " << triggerCollection_.process();
	}


//debug dav
	if(hlNames.size()==0) { 
		hltispresent=false;
	}

	if (debug) cout<<"useAllTriggers?"<<useAllTriggers_<<endl;
	if(useAllTriggers_) triggerNames_ = hlNames;
	
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
			if (debug) cout << (i++) << " = " << (*it) << std::endl;
		} 
	}
}

// ------------ method called when ending the processing of a run  ------------
	void 
HistoProducer::endRun(edm::Run&,const edm::EventSetup&)
{
	treeHLT_->Fill();
}

// ------------ method called when starting to processes a luminosity block  ------------
	void 
HistoProducer::beginLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & iEvent)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
	void 
	HistoProducer::endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & iEvent)
{
  for (size_t i = 0; i < numEventsNames_.size(); i++)
    {
      edm::Handle<edm::MergeableCounter> numEventsCounter;
      lumi.getByLabel(numEventsNames_.at(i), numEventsCounter);
      if (numEventsCounter.isValid()){
	nEventsPerStep_->AddBinContent(i + 1, numEventsCounter->value);
      }
    }
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HistoProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HistoProducer);
