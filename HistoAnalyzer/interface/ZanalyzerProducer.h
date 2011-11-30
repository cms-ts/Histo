#ifndef ZAnalyzerProducer_h_
#define ZAnalyzerProducer_h_

#include <memory>
#include <string>
#include <cmath>
#include <iostream>

#include "FWCore/Framework/interface/EDProducer.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "TLorentzVector.h"
#include "TMath.h"


class ZanalyzerProducer : public edm::EDProducer {
	public:
		explicit ZanalyzerProducer(const edm::ParameterSet &);
		~ZanalyzerProducer();

		virtual void produce(edm::Event&, edm::EventSetup const&);
		virtual void beginJob();
		//virtual bool beginRun(edm::Run &, edm::EventSetup const&);

	private:
		virtual void endJob() ;

		// ----------member data ---------------------------

		edm::InputTag theElectronCollectionLabel;
		bool removePU_;
		bool debug; //Activate with true if you wonna have verbosity for debug
 
};



//
// constructors and destructor
//
ZanalyzerProducer::ZanalyzerProducer (const edm::ParameterSet & parameters)
{
   debug = false;
   theElectronCollectionLabel = parameters.getParameter <edm::InputTag> ("electronCollection");
   removePU_ = parameters.getParameter<bool>("removePU");
   produces<reco::GsfElectronCollection>();
   

}



ZanalyzerProducer::~ZanalyzerProducer ()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}

#endif

