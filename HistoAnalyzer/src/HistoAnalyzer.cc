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
// $Id: HistoAnalyzer.cc,v 1.45 2012/09/22 07:54:56 marone Exp $
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

//Sherpa weights
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

bool hltispresentH11=1;

//
// member functions
//

// ------------ method called for each event  ------------
void
HistoAnalyzer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // We need the output Muon association collection to fill 
  std::auto_ptr<std::vector<float> > EventWeight( new std::vector<float>);
  std::auto_ptr<std::vector<float> > EventWeightScaleUp( new std::vector<float>);
  std::auto_ptr<std::vector<float> > EventWeightScaleDown( new std::vector<float>);
  std::auto_ptr<std::vector<float> > EventWeightSherpa( new std::vector<float>);


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
  double NeutHadIso_PUR;
  double PhotIso_PUR;
  double CombinedIso_PUR;
  
  //Define Isolation Variables (Non-Removed PU)
  double IsoTrk;
  double IsoEcal;
  double IsoHcal;
  double HE;
  double fbrem;
  double etaSC;

  double NeutHadIso;
  double ChgHadIso;
  double PhotIso;
  double PhotIsoUser;
  double NeutHadIso_ned;
  double NeutHadIsoUser_ned;
  double ChgHadIso_ned;
  double ChgHadIsoUser_ned;
  double PhotIso_ned;
  double PhotIsoUser_ned;
  double CombinedIso;
  
  //Define ID variables
  float DeltaPhiTkClu;
  float DeltaEtaTkClu;
  float sigmaIeIe;
  float ooemoop;
  
  //Define Conversion Rejection Variables
  float Dcot;
  float Dist;
  float d0vtx;
  float dzvtx;
  bool FitConversion;
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
    if(hltispresentH11==false){
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
      if(myflag==triggerNames_.size()) hltispresentH11=false;
      else hltispresentH11=true; //cosi' prendo una sola volta l'hlt path tanto nie miei studi mi serve l'hlt path per run...
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
		if (debugH11) cout<<"prescale.first "<<prescalepair.first<<" prescalepair.second "<<prescalepair.second<<endl;
		//getting prescale info
		prescale = useCombinedPrescales_ ? prescalepair.first*prescalepair.second : prescalepair.second;
		if((useCombinedPrescales_ && prescalepair.first<0) || prescalepair.second<0) {
		  edm::LogWarning("MyAnalyzer") << " Unable to get prescale from event for trigger " << triggerNames.triggerName(itrig) << " :" << prescalepair.first << ", " << prescalepair.second;
		  prescale = -999;
		}
		
		if(prescalepair.first<0 || prescalepair.second<0) { prescale = -999; }
	      }
	      
	      minimalPrescale = minimalPrescale <  prescale ? minimalPrescale : prescale;
	      if (debugH11) cout<<"prescale "<<prescale<<" minimal Prescale "<<minimalPrescale<<" for trigger "<<triggerNames.triggerName(itrig)<<endl;
	      
	      
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
	  //edm::LogError("HistoAnalyzer") << " Unable to get prescale set from event. Check that L1 data products are present.";
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
  
  if (usingMC_ && !giveEventWeightEqualToOne_){
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
      if (WhichRun_=="Run2011B") {
	LumiWeights_ = edm::Lumi3DReWeighting("Fall11_truedist.root", "Data2011B_175832-180252.root", "PU_intended", "pileup");
	LumiWeightsScaleUp_ = edm::Lumi3DReWeighting("Fall11_truedist.root", "Data2011B_175832-180252.root", "PU_intended", "pileup");
	LumiWeightsScaleDown_ = edm::Lumi3DReWeighting("Fall11_truedist.root", "Data2011B_175832-180252.root", "PU_intended", "pileup");
	cout<<"Reweighting using the DATA RUN2011B distribution"<<endl;
      }
      if (WhichRun_=="Run2011A") {
	LumiWeights_ = edm::Lumi3DReWeighting("Fall11_truedist.root", "Data2011A_160404-173692.root", "PU_intended", "pileup");
	LumiWeightsScaleUp_ = edm::Lumi3DReWeighting("Fall11_truedist.root", "Data2011A_160404-173692.root", "PU_intended", "pileup");
	LumiWeightsScaleDown_ = edm::Lumi3DReWeighting("Fall11_truedist.root", "Data2011A_160404-173692.root", "PU_intended", "pileup");
	cout<<"Reweighting using the DATA RUN2011A distribution"<<endl;
      }
      if (WhichRun_=="Run2011AB") {
	LumiWeights_ = edm::Lumi3DReWeighting("Fall11_truedist.root", "Data2011_160404-180252.root", "PU_intended", "pileup");
	LumiWeightsScaleUp_ = edm::Lumi3DReWeighting("Fall11_truedist.root", "Data2011_160404-180252.root", "PU_intended", "pileup");
	LumiWeightsScaleDown_ = edm::Lumi3DReWeighting("Fall11_truedist.root", "Data2011_160404-180252.root", "PU_intended", "pileup");
	cout<<"Reweighting using the DATA RUN2011A+Run2011B distribution"<<endl;
      }
      LumiWeights_.weight3D_init( ScaleFactor );
      LumiWeightsScaleUp_.weight3D_init( ScaleFactor - 0.08 );
      LumiWeightsScaleDown_.weight3D_init( ScaleFactor + 0.08 );
      cout<<"Initializing weight3D at Factor Scale ->"<<ScaleFactor<<endl;
      cout<<"Initializing weight3DScaleUp at Factor Scale ->"<<ScaleFactor + 0.08 <<endl;
      cout<<"Initializing weight3DScaleDown at Factor Scale ->"<<ScaleFactor - 0.08 <<endl;
      cold=false;
    }
    
    int nm1 = -1; int n0 = -1; int np1 = -1;
    for(PVI = PupInfo->begin(); PVI != PupInfo->end(); ++PVI) {
      
      int BX = PVI->getBunchCrossing();
      
      if(BX == -1) { 
	//nm1 = PVI->getPU_NumInteractions();
	  nm1 =PVI->getTrueNumInteractions();
      }
      if(BX == 0) { 
	//n0 = PVI->getPU_NumInteractions();
	  n0 = PVI->getTrueNumInteractions();
      }
      if(BX == 1) { 
	//np1 = PVI->getPU_NumInteractions();
          np1 = PVI->getTrueNumInteractions();
      }
    }
    double MyWeight3D = LumiWeights_.weight3D( nm1,n0,np1);
    double MyWeight3DScaleUp = LumiWeightsScaleUp_.weight3D( nm1,n0,np1);
    double MyWeight3DScaleDown = LumiWeightsScaleDown_.weight3D( nm1,n0,np1);

    // end 3D
    /////////
    
    //////// Storing info
    Weight=MyWeight3D;
    if (MyWeight3D>10) {
    cout<<"You are over-correcting in the MC reweight, HistoAnalyzer.cc!!! Event re corrected by factor 1.0"<<endl;
    MyWeight3D=1.0;
    }
    EventWeight->push_back(MyWeight3D); 
    EventWeightScaleUp->push_back(MyWeight3DScaleUp); 
    EventWeightScaleDown->push_back(MyWeight3DScaleDown); 
  }
  else { 
    EventWeight->push_back(1); 
    EventWeightScaleUp->push_back(1); 
    EventWeightScaleDown->push_back(1); 
  }
  
	///////////////////
	/// Electrons Study
	///////////////////

	//Getting the Electron Collection
	//using reco::GsfElectronCollection;
	//Handle<GsfElectronCollection> gsfElectrons;
  
        Handle < pat::ElectronCollection > gsfElectrons;
	iEvent.getByLabel(electronCollection_,gsfElectrons);

	Handle<reco::PFCandidateCollection> particleCollection;
	iEvent.getByLabel(particleCollection_,particleCollection);

	// conversions
	edm::Handle<reco::ConversionCollection> conversions_h;
	iEvent.getByLabel(conversionsInputTag_, conversions_h);
	
	// iso deposits
	IsoDepositVals IsoVals(isoValInputTags_.size());
	for (size_t j = 0; j < isoValInputTags_.size(); ++j) {
	   iEvent.getByLabel(isoValInputTags_[j], IsoVals[j]);
	}
	
	// beam spot
	edm::Handle<reco::BeamSpot> beamspot_h;
	iEvent.getByLabel(beamSpotInputTag_, beamspot_h);
	const reco::BeamSpot &beamSpot = *(beamspot_h.product());
	
	// vertices
	edm::Handle<reco::VertexCollection> vtx_h;
	iEvent.getByLabel(primaryVertexInputTag_, vtx_h);

	//Loop over the gsf collection to study the variables distributions
	for(pat::ElectronCollection::const_iterator itElect = gsfElectrons->begin();itElect != gsfElectrons->end(); ++itElect) {
	   double isoPhotonUser=0,isoChgHadUser=0,isoNeutHadUser=0;
	   for(reco::PFCandidateCollection::const_iterator itPart = particleCollection->begin(); itPart!= particleCollection->end(); ++itPart) {
	      if (itPart->pdgId()==22){
		 double deltaPhi = fabs (itElect->phi() - itPart->phi());
		 if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
		 double deltaR = sqrt ( pow(itElect->eta() - itPart->eta(),2) + deltaPhi*deltaPhi);
		 if (deltaR < 0.3 
		     //&& itPart->pt()>0.5 
		    ) isoPhotonUser += itPart->pt();
	      }
	      if (itPart->particleId()==1){
		 double deltaPhi = fabs (itElect->phi() - itPart->phi());
		 if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
		 double deltaR = sqrt ( pow(itElect->eta() - itPart->eta(),2) + deltaPhi*deltaPhi);
		 if (deltaR < 0.3 ) isoChgHadUser += itPart->pt();
	      }
	      if (itPart->particleId()==5){
		 double deltaPhi = fabs (itElect->phi() - itPart->phi());
		 if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
		 double deltaR = sqrt ( pow(itElect->eta() - itPart->eta(),2) + deltaPhi*deltaPhi);
		 if (deltaR < 0.3 
		     //&& itPart->pt()>0.5 
		    ) isoNeutHadUser += itPart->pt();
	      }
	      
	   }	   
			
	   double charged = (*IsoVals[0])[itElect->originalObjectRef()];//myElectronRef
	   double photon  = (*IsoVals[1])[itElect->originalObjectRef()]; //myElectronRef
	   double neutral = (*IsoVals[2])[itElect->originalObjectRef()];//myElectronRef 

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

			// Effective area for 2011 data (Delta_R=0.3) (taken from https://twiki.cern.ch/twiki/bin/view/Main/HVVElectronId2012 )
			double A_eff_PH, A_eff_NH;
			if(abs(itElect->eta())<=1.0){A_eff_PH=0.081; A_eff_NH=0.024;}
			else if(abs(itElect->eta())>1.0 && abs(itElect->eta())<=1.479){A_eff_PH=0.084 ; A_eff_NH=0.037;}
			else if(abs(itElect->eta())>1.479 && abs(itElect->eta())<=2.0){A_eff_PH=0.048 ; A_eff_NH=0.037;}
			else if(abs(itElect->eta())>2.0 && abs(itElect->eta())<=2.2){A_eff_PH=0.089 ; A_eff_NH=0.023;}
			else if(abs(itElect->eta())>2.2 && abs(itElect->eta())<=2.3){A_eff_PH=0.092 ; A_eff_NH=0.023;}
			else if(abs(itElect->eta())>2.3 && abs(itElect->eta())<=2.4){A_eff_PH=0.097 ; A_eff_NH=0.021;}   
			else {A_eff_PH=0.11 ; A_eff_NH=0.021;}
			
			NeutHadIso_PUR =max(neutral - lepIsoRho * A_eff_NH, 0.)/std::max(0.5, itElect->pt());
			PhotIso_PUR = max(photon - lepIsoRho*A_eff_PH  , 0.) /std::max(0.5, itElect->pt());
			CombinedIso_PUR = (charged + max(photon - lepIsoRho*A_eff_PH  , 0.) +  max(neutral - lepIsoRho * A_eff_NH, 0.))/std::max(0.5, itElect->pt());
			
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

				vNeutHadIsoEB_PUR.push_back(NeutHadIso_PUR);
				vPhotIsoEB_PUR.push_back(PhotIso_PUR);
				vCombinedIsoEB_PUR.push_back(CombinedIso_PUR);
					   
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

				vNeutHadIsoEE_PUR.push_back(NeutHadIso_PUR);
				vPhotIsoEE_PUR.push_back(PhotIso_PUR);
				vCombinedIsoEE_PUR.push_back(CombinedIso_PUR);
			}
		}


		//Non-Removed-PU variables
		// Define Isolation variables
		IsoTrk = (itElect->dr03TkSumPt () / itElect->et ());
		IsoEcal = (itElect->dr03EcalRecHitSumEt () / itElect->et ());
		IsoHcal = (itElect->dr03HcalTowerSumEt () / itElect->et ());
		HE = itElect->hadronicOverEm();
		HE_old = itElect->hadronicOverEm();
		HE_bc = itElect->hcalOverEcalBc();

		NeutHadIso_ned= neutral;
		NeutHadIsoUser_ned= isoNeutHadUser;
		ChgHadIso_ned= charged;
		ChgHadIsoUser_ned= isoChgHadUser;
		PhotIso_ned= photon;
		PhotIsoUser_ned=isoPhotonUser;

		NeutHadIso = neutral/std::max(0.5, itElect->pt());
		PhotIso = photon/std::max(0.5, itElect->pt());
		ChgHadIso = charged /std::max(0.5, itElect->pt());
		CombinedIso = NeutHadIso + PhotIso + ChgHadIso;
		PhotIsoUser=isoPhotonUser/ itElect->pt ();

		//Assign Isolation variables
		fbrem	= itElect->fbrem();
		etaSC	= itElect->superCluster()->eta();
		//etaSCPF      = itElect->pflowSuperCluster()->eta();

		//Assign ID variables
		DeltaPhiTkClu = itElect->deltaPhiSuperClusterTrackAtVtx();
		DeltaEtaTkClu = itElect->deltaEtaSuperClusterTrackAtVtx();
		sigmaIeIe     = itElect->sigmaIetaIeta ();
		ooemoop = (1.0/itElect->ecalEnergy() - itElect->eSuperClusterOverP()/itElect->ecalEnergy());

		//Assign Conversion Rejection Variables
		d0vtx = 0.0;
		dzvtx = 0.0;
		if (vtx_h->size() >0){
		   reco::VertexRef vtx(vtx_h,0);		       
		   d0vtx = itElect->gsfTrack()->dxy(vtx->position());
		   dzvtx = itElect->gsfTrack()->dz(vtx->position());
		} else {
		   d0vtx = itElect->gsfTrack()->dxy();
		   dzvtx = itElect->gsfTrack()->dz();
		}

		FitConversion = HistoAnalyzer::hasMatchedConversion(*itElect, conversions_h, beamSpot.position());
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
			vooemoopEB.push_back(ooemoop);			
			vNeutHadIsoEB.push_back(NeutHadIso);
			vChgHadIsoEB.push_back(ChgHadIso);
			vPhotIsoEB.push_back(PhotIso);
			vPhotIsoUserEB.push_back(PhotIsoUser);
			vNeutHadIsoUserEB_ned.push_back(NeutHadIsoUser_ned);
			vNeutHadIsoEB_ned.push_back(NeutHadIso_ned);
			vChgHadIsoUserEB_ned.push_back(ChgHadIsoUser_ned);
			vChgHadIsoEB_ned.push_back(ChgHadIso_ned);
			vPhotIsoEB_ned.push_back(PhotIso_ned);
			vPhotIsoUserEB_ned.push_back(PhotIsoUser_ned);
			vCombinedIsoEB.push_back(CombinedIso);
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
			vooemoopEE.push_back(ooemoop);

			vNeutHadIsoEE.push_back(NeutHadIso);
			vChgHadIsoEE.push_back(ChgHadIso);
			vPhotIsoEE.push_back(PhotIso);
			vPhotIsoUserEE.push_back(PhotIsoUser);
			vNeutHadIsoEE_ned.push_back(NeutHadIso_ned);
			vNeutHadIsoUserEE_ned.push_back(NeutHadIsoUser_ned);
			vChgHadIsoEE_ned.push_back(ChgHadIso_ned);
			vChgHadIsoUserEE_ned.push_back(ChgHadIsoUser_ned);
			vPhotIsoEE_ned.push_back(PhotIso_ned);
			vPhotIsoUserEE_ned.push_back(PhotIsoUser_ned);
			vCombinedIsoEE.push_back(CombinedIso);

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
		vd0vtx.push_back(d0vtx);
		vdzvtx.push_back(dzvtx);
		vDcot.push_back(Dcot);
		vDist.push_back(Dist);
		vFitConversion.push_back(FitConversion);
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

	////////////////////////
	////// Weights to accomodate SHERPA
	////////////////////////

	// applies the MC weight corrections
	// for Sherpa (recipe from https://hypernews.cern.ch/HyperNews/CMS/get/ewk-vplusjets/317) and aMC@NLO
	if (usingMC_ && applyMCWeightsSherpa_) {  
	  edm::Handle<GenEventInfoProduct> genEventInfoHandle;
	  iEvent.getByLabel("generator",genEventInfoHandle);
	  double wMCtmp = genEventInfoHandle->weight();
	  if (debugH11) std::cout << "Weight MC for SHERPA -> " << wMCtmp<< std::endl; 
	  EventWeightSherpa->push_back(wMCtmp);
	}
	else{
	  EventWeightSherpa->push_back(1);
	}
	//--------------------------------//
	//---------Fill del Tree----------//
	treeVJ_->Fill();
	iEvent.put( EventWeight,"EventWeight" );
	iEvent.put( EventWeightScaleUp,"EventWeightScaleUp" );
	iEvent.put( EventWeightScaleDown,"EventWeightScaleDown" );
	iEvent.put( EventWeightSherpa,"EventWeightSherpa" );
}


// ------------ method called once each job just before starting event loop  ------------
	void 
HistoAnalyzer::beginJob()
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
 //TFile and TTree initialization
 treeVJ_= new TTree(rootuplaname.c_str(),rootuplaname.c_str());
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

	treeVJ_->Branch("NeutHadIsoEB_PUR","NeutHadIsoEB_PUR",&vNeutHadIsoEB_PUR);
	treeVJ_->Branch("PhotIsoEB_PUR","PhotIsoEB_PUR",&vPhotIsoEB_PUR);
	treeVJ_->Branch("NeutHadIsoEE_PUR","NeutHadIsoEE_PUR",&vNeutHadIsoEE_PUR);
	treeVJ_->Branch("PhotIsoEE_PUR","PhotIsoEE_PUR",&vPhotIsoEE_PUR);
	treeVJ_->Branch("CombinedIsoEB_PUR","CombinedIsoEB_PUR",&vCombinedIsoEB_PUR);
	treeVJ_->Branch("CombinedIsoEE_PUR","CombinedIsoEE_PUR",&vCombinedIsoEE_PUR);

	//EB
	treeVJ_->Branch("IsoTrkEB","IsoTrkEB",&vIsoTrkEB);
	treeVJ_->Branch("IsoEcalEB","IsoEcalEB",&vIsoEcalEB);
	treeVJ_->Branch("IsoHcalEB","IsoHcalEB",&vIsoHcalEB);
	treeVJ_->Branch("HEEB","HEEB",&vHEEB);
	treeVJ_->Branch("DeltaPhiTkCluEB","DeltaPhiTkCluEB",&vDeltaPhiTkCluEB);
	treeVJ_->Branch("DeltaEtaTkCluEB","DeltaEtaTkCluEB",&vDeltaEtaTkCluEB);
	treeVJ_->Branch("sigmaIeIeEB","sigmaIeIeEB",&vsigmaIeIeEB);
	treeVJ_->Branch("ooemoopEB","ooemoopEB",&vooemoopEB);

	treeVJ_->Branch("NeutHadIsoEB","NeutHadIsoEB",&vNeutHadIsoEB);
	treeVJ_->Branch("ChgHadIsoEB","ChgHadIsoEB",&vChgHadIsoEB);
	treeVJ_->Branch("PhotIsoEB","PhotIsoEB",&vPhotIsoEB);
	treeVJ_->Branch("PhotIsoUserEB","PhotIsoUserEB",&vPhotIsoUserEB);
	treeVJ_->Branch("NeutHadIsoEB_ned","NeutHadIsoEB_ned",&vNeutHadIsoEB_ned);
	treeVJ_->Branch("NeutHadIsoUserEB_ned","NeutHadIsoUserEB_ned",&vNeutHadIsoUserEB_ned);
	treeVJ_->Branch("ChgHadIsoEB_ned","ChgHadIsoEB_ned",&vChgHadIsoEB_ned);
	treeVJ_->Branch("ChgHadIsoUserEB_ned","ChgHadIsoUserEB_ned",&vChgHadIsoUserEB_ned);
	treeVJ_->Branch("PhotIsoEB_ned","PhotIsoEB_ned",&vPhotIsoEB_ned);
	treeVJ_->Branch("PhotIsoUserEB_ned","PhotIsoUserEB_ned",&vPhotIsoUserEB_ned);
	treeVJ_->Branch("CombinedIsoEB","CombinedIsoEB",&vCombinedIsoEB);

	//EE
	treeVJ_->Branch("IsoTrkEE","IsoTrkEE",&vIsoTrkEE);
	treeVJ_->Branch("IsoEcalEE","IsoEcalEE",&vIsoEcalEE);
	treeVJ_->Branch("IsoHcalEE","IsoHcalEE",&vIsoHcalEE);
	treeVJ_->Branch("HEEE","HEEE",&vHEEE);
	treeVJ_->Branch("DeltaPhiTkCluEE","DeltaPhiTkCluEE",&vDeltaPhiTkCluEE);
	treeVJ_->Branch("DeltaEtaTkCluEE","DeltaEtaTkCluEE",&vDeltaEtaTkCluEE);
	treeVJ_->Branch("sigmaIeIeEE","sigmaIeIeEE",&vsigmaIeIeEE);
	treeVJ_->Branch("ooemoopEE","ooemoopEE",&vooemoopEE);

	treeVJ_->Branch("NeutHadIsoEE","NeutHadIsoEE",&vNeutHadIsoEE);
	treeVJ_->Branch("ChgHadIsoEE","ChgHadIsoEE",&vChgHadIsoEE);
	treeVJ_->Branch("PhotIsoEE","PhotIsoEE",&vPhotIsoEE);
	treeVJ_->Branch("PhotIsoUserEE","PhotIsoUserEE",&vPhotIsoUserEE);
	treeVJ_->Branch("NeutHadIsoEE_ned","NeutHadIsoEE_ned",&vNeutHadIsoEE_ned);
	treeVJ_->Branch("NeutHadIsoUserEE_ned","NeutHadIsoUserEE_ned",&vNeutHadIsoUserEE_ned);
	treeVJ_->Branch("ChgHadIsoEE_ned","ChgHadIsoEE_ned",&vChgHadIsoEE_ned);
	treeVJ_->Branch("ChgHadIsoUserEE_ned","ChgHadIsoUserEE_ned",&vChgHadIsoUserEE_ned);
	treeVJ_->Branch("PhotIsoEE_ned","PhotIsoEE_ned",&vPhotIsoEE_ned);
	treeVJ_->Branch("PhotIsoUserEE_ned","PhotIsoUserEE_ned",&vPhotIsoUserEE_ned);
	treeVJ_->Branch("CombinedIsoEE","CombinedIsoEE",&vCombinedIsoEE);

	//Common
	treeVJ_->Branch("fbrem","fbrem",&vfbrem);
	treeVJ_->Branch("etaSC","etaSC",&vetaSC);
	treeVJ_->Branch("Dcot","Dcot",&vDcot);
	treeVJ_->Branch("Dist","Dist",&vDist);
	treeVJ_->Branch("d0vtx","d0vtx",&vd0vtx);
	treeVJ_->Branch("dzvtx","dzvtx",&vdzvtx);
	treeVJ_->Branch("FitConversion","FitConversion",&vFitConversion);
	treeVJ_->Branch("NumberOfExpectedInnerHits","NumberOfExpectedInnerHits",&vNumberOfExpectedInnerHits);
	treeVJ_->Branch("Rho","Rho",&vRho);
	treeVJ_->Branch("HE_bc",&HE_bc,"HE_bc/D");
	treeVJ_->Branch("HE_old",&HE_old,"HE_old/D");

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
HistoAnalyzer::endJob() 
{
  //nEventsPerStep_->Write();
}

// ------------ method called when starting to processes a run  ------------
	void 
HistoAnalyzer::beginRun(edm::Run& iRun, const edm::EventSetup& iSetup)
{

  hltispresentH11=true;
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
		hltispresentH11=false;
	}

	if (debugH11) cout<<"useAllTriggers?"<<useAllTriggers_<<endl;
	if(useAllTriggers_) triggerNames_ = hlNames;
	
	//HLT indices
	triggerIndices_.clear();
	
	for(unsigned int itrig = 0; itrig < triggerNames_.size(); ++itrig) {
		if(find(hlNames.begin(),hlNames.end(),triggerNames_[itrig])!=hlNames.end())
			triggerIndices_.push_back(hltConfig_.triggerIndex(triggerNames_[itrig]));
		else
			triggerIndices_.push_back(2048);
	}

	if (debugH11){
		// text (debug) output
		int i=0;
		for(std::vector<std::string>::const_iterator it = triggerNames_.begin(); it<triggerNames_.end();++it) {
			if (debugH11) cout << (i++) << " = " << (*it) << std::endl;
		} 
	}
}

// ------------ method called when ending the processing of a run  ------------
	void 
HistoAnalyzer::endRun(edm::Run&,const edm::EventSetup&)
{
	treeHLT_->Fill();
}

// ------------ method called when starting to processes a luminosity block  ------------
	void 
HistoAnalyzer::beginLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & iEvent)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
	void 
	HistoAnalyzer::endLuminosityBlock(edm::LuminosityBlock & lumi, const edm::EventSetup & iEvent)
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
HistoAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
}


bool HistoAnalyzer::isGoodConversion(const reco::Conversion &conv, const math::XYZPoint &beamspot, float lxyMin, float probMin, unsigned int nHitsBeforeVtxMax)
{
  
  //Check if a given conversion candidate passes the conversion selection cuts
  
  const reco::Vertex &vtx = conv.conversionVertex();

  //vertex validity
  if (!vtx.isValid()) return false;

  //fit probability
  if (TMath::Prob( vtx.chi2(),  vtx.ndof() )<probMin) return false;

  //compute transverse decay length
  math::XYZVector mom(conv.refittedPairMomentum()); 
  double dbsx = vtx.x() - beamspot.x();
  double dbsy = vtx.y() - beamspot.y();
  double lxy = (mom.x()*dbsx + mom.y()*dbsy)/mom.rho();

  //transverse decay length  
  if ( lxy<lxyMin )
    return false;
    
  //loop through daughters to check nhitsbeforevtx
  for (std::vector<uint8_t>::const_iterator it = conv.nHitsBeforeVtx().begin(); it!=conv.nHitsBeforeVtx().end(); ++it) {
    if ( (*it)>nHitsBeforeVtxMax ) return false;
  }
  
  return true;
}

bool HistoAnalyzer::matchesConversion(const pat::Electron &ele, const reco::Conversion &conv, bool allowCkfMatch)
{

  //check if a given GsfElectron matches a given conversion (no quality cuts applied)
  //matching is always attempted through the gsf track ref, and optionally attempted through the
  //closest ctf track ref

  const std::vector<edm::RefToBase<reco::Track> > &convTracks = conv.tracks();
  for (std::vector<edm::RefToBase<reco::Track> >::const_iterator it=convTracks.begin(); it!=convTracks.end(); ++it) {
    if ( ele.gsfTrack().isNonnull() && ele.gsfTrack().id()==it->id() && ele.gsfTrack().key()==it->key()) return true;
    else if ( allowCkfMatch && ele.closestCtfTrackRef().isNonnull() && ele.closestCtfTrackRef().id()==it->id() && ele.closestCtfTrackRef().key()==it->key() ) return true;
  }

  return false;
}

bool HistoAnalyzer::hasMatchedConversion(const pat::Electron &ele,
					  const edm::Handle<reco::ConversionCollection> &convCol,
					  const math::XYZPoint &beamspot, bool allowCkfMatch, float lxyMin, float probMin, unsigned int nHitsBeforeVtxMax)
{
  //check if a given electron candidate matches to at least one conversion candidate in the
  //collection which also passes the selection cuts, optionally match with the closestckf track in
  //in addition to just the gsf track (enabled in default arguments)
  
  for (reco::ConversionCollection::const_iterator it = convCol->begin(); it!=convCol->end(); ++it) {
     if (!HistoAnalyzer::matchesConversion(ele, *it, allowCkfMatch)) continue;
     if (!HistoAnalyzer::isGoodConversion(*it,beamspot,lxyMin,probMin,nHitsBeforeVtxMax)) continue;
   
    return true;
  }
  
  return false;
  
}


//define this as a plug-in
DEFINE_FWK_MODULE(HistoAnalyzer);
