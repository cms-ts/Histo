#ifndef GENPAnalyzer_h_
#define GENPAnalyzer_h_


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/Common/interface/SortedCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/deltaPhi.h"

#include "SimDataFormats/CaloHit/interface/CaloHit.h"

#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgoRcd.h"

#include "TH1F.h"
#include "TLorentzVector.h"


//
// class declaration
//

class GENPAnalyzer : public edm::EDAnalyzer {
 public:
  explicit GENPAnalyzer(const edm::ParameterSet&);
  ~GENPAnalyzer();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


 private:
  virtual void beginJob();
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  reco::GenParticleRef GENPMatcher(reco::GsfElectron const&, reco::GenParticleCollection const&, 
				   double &, double&);
  reco::GenParticleRef GENPMatcher(reco::Track const&, reco::GenParticleCollection const&, 
				   double &, double&);
  std::pair<reco::GenParticleRef, reco::VertexRef> GENPMatcher(CaloHit const&, 
							       reco::GenParticleCollection const&, 
							       reco::VertexCollection const&, 
							       double&, double&);
  std::pair<reco::GenParticleRef, reco::VertexRef> GENPMatcher(CaloTower const&, 
							       reco::GenParticleCollection const&, 
							       reco::VertexCollection const&, 
							       double&, double&);

  // ----------member data ---------------------------

  edm::InputTag goodEPairTag_;
  edm::InputTag genParticleCollection_;
  edm::InputTag trackCollection_;
  edm::InputTag ecalBarrelHits_;
  edm::InputTag ecalEndCapHits_;
  edm::InputTag towerCollection_;
  edm::InputTag vertexCollection_;


  edm::ESHandle<CaloGeometry> caloGeom_;
  const CaloSubdetectorGeometry* subdet_[2]; 

  edm::ESHandle<EcalSeverityLevelAlgo> sevLevel_;
  const EcalSeverityLevelAlgo* sevLevel;

  bool isMC;


  // --- histograms
  
  TH1F * h_Mee;

  TH1F * h_isoTrk;
  TH1F * h_isoTrk_diff;
  TH1F * h_isoTrk_dR;
  TH1F * h_isoTrk_dPt;

  TH1F * h_isoEcal;
  TH1F * h_isoEcal_diff;
  TH1F * h_isoEcal_dR;
  TH1F * h_isoEcal_dPt;

  TH1F * h_isoHcal;
  TH1F * h_isoHcal_diff;
  TH1F * h_isoHcal_dR;
  TH1F * h_isoHcal_dPt;

//
//
//
//  TH1F * h_ID_iso;
//  TH1F * h_ID_iso1;
//  TH1F * h_ID_iso2;
//
//  TH1F * h_pt_iso;
//  TH1F * h_pt_iso1;
//  TH1F * h_pt_iso2;
//  TH1F * h_pt_iso_e;
//  TH1F * h_pt_iso_mu;
//  TH1F * h_pt_iso_ph;
//  TH1F * h_pt_iso_pi;
//  TH1F * h_pt_iso_K;
//  TH1F * h_pt_iso_KL;
//  TH1F * h_pt_iso_KS;
//  TH1F * h_pt_iso_p;
//  TH1F * h_pt_iso_n;  
//
//  TH1F * h_trkiso_diff;  
//  TH1F * h_trkiso_dRmin1; 
//  TH1F * h_trkiso_dRmin2; 
//  TH1F * h_trkiso_ID; 
//  TH1F * h_trkiso_ID1; 
//  TH1F * h_trkiso_ID2;
//  TH1F * h_trkiso_Pt; 
//  TH1F * h_trkiso_Pt1; 
//  TH1F * h_trkiso_Pt2;
//  TH1F * h_trkiso_Pt_e; 
//  TH1F * h_trkiso_Pt_mu; 
//  TH1F * h_trkiso_Pt_pi; 
//  TH1F * h_trkiso_Pt_K; 
//  TH1F * h_trkiso_Pt_p; 
  

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
GENPAnalyzer::GENPAnalyzer(const edm::ParameterSet& iConfig)
{
  //now do what ever initialization is needed

  goodEPairTag_          = iConfig.getParameter<edm::InputTag>("goodEPair");
  genParticleCollection_ = iConfig.getUntrackedParameter<edm::InputTag>("genParticleCollection",edm::InputTag("genParticles"));
  trackCollection_       = iConfig.getUntrackedParameter<edm::InputTag>("trackCollection",edm::InputTag("generalTracks"));
  ecalBarrelHits_        = iConfig.getUntrackedParameter<edm::InputTag>("ecalBarrelHits",edm::InputTag("reducedEcalRecHitsEB"));
  ecalEndCapHits_        = iConfig.getUntrackedParameter<edm::InputTag>("ecalEndCapHits",edm::InputTag("reducedEcalRecHitsEE"));
  towerCollection_       = iConfig.getUntrackedParameter<edm::InputTag>("towerCollection",edm::InputTag("towerMaker"));
  vertexCollection_      = iConfig.getUntrackedParameter<edm::InputTag>("vertexCollection",edm::InputTag("offlinePrimaryVertices"));


  isMC = iConfig.getUntrackedParameter<bool>("usingMC",false);

  edm::Service<TFileService> fs; 



  // --- histograms
  
  h_Mee          = fs->make<TH1F>("h_Mee","M_{ee};M_{ee} [Gev/c^{2}];Entries",
				  200,0.,200.);

  h_isoTrk       = fs->make<TH1F>("h_isoTrk", "Track isolation;TrkIso [GeV/c];Entries",
				  100,0.,10.);
  h_isoTrk_diff  = fs->make<TH1F>("h_isoTrk_diff", "TrkIso difference;TrkIso - myTrkIso [GeV/c];Entries",
				  100,-1.,1.);
  h_isoTrk_dR    = fs->make<TH1F>("h_isoTrk_dR", "Min #DeltaR in trk-GENP matching;#DeltaR;Entries",
				  100,-0.35,0.35);
  h_isoTrk_dPt   = fs->make<TH1F>("h_isoTrk_dPt", "Min relative #DeltaP_{T} in trk-GENP matching;Rel #DeltaP_{T};Entries",
				  100,-1.,1.);

  h_isoEcal      = fs->make<TH1F>("h_isoEcal", "Ecal isolation;EcalIso [GeV];Entries",
				  150,0.,15.);
  h_isoEcal_diff = fs->make<TH1F>("h_isoEcal_diff", "EcalIso difference;EcalIso - myEcalIso [GeV];Entries",
				  100,-1.,1.);

  h_isoHcal      = fs->make<TH1F>("h_isoHcal", "Hcal isolation;HcalIso [GeV];Entries",
				  100,0.,10.);
  h_isoHcal_diff = fs->make<TH1F>("h_isoHcal_diff", "HcalIso difference;HcalIso - myHcalIso [GeV];Entries",
				  100,-1.,1.);


//  h_ID_iso    = fs->make<TH1F>("h_ID_iso",  "GENP particles in ele iso;GENP ID;Entries",
//			       4800,-2400.,2400.);
//  h_ID_iso1   = fs->make<TH1F>("h_ID_iso1", "GENP particles in ele1 iso;GENP ID;Entries",
//			       4800,-2400.,2400.);
//  h_ID_iso2   = fs->make<TH1F>("h_ID_iso2", "GENP particles in ele2 iso;GENP ID;Entries",
//			       4800,-2400.,2400.);
//
//  h_pt_iso    = fs->make<TH1F>("h_pt_iso",    "pt of GENP particles in ele iso;P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//  h_pt_iso1   = fs->make<TH1F>("h_pt_iso1",   "pt of GENP particles in ele1 iso;P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//  h_pt_iso2   = fs->make<TH1F>("h_pt_iso2",   "pt of GENP particles in ele2 iso;P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//  h_pt_iso_e  = fs->make<TH1F>("h_pt_iso_e",  "pt of GENP particles in ele iso (e);P_{T} [GeV/c];Entries",
//			       100,0.,10.);    
//  h_pt_iso_mu = fs->make<TH1F>("h_pt_iso_mu", "pt of GENP particles in ele iso (#mu);P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//  h_pt_iso_ph = fs->make<TH1F>("h_pt_iso_ph", "pt of GENP particles in ele iso (#gamma);P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//  h_pt_iso_pi = fs->make<TH1F>("h_pt_iso_pi", "pt of GENP particles in ele iso (#pi^{#pm});P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//  h_pt_iso_K  = fs->make<TH1F>("h_pt_iso_K",  "pt of GENP particles in ele iso (K^{#pm});P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//  h_pt_iso_KL = fs->make<TH1F>("h_pt_iso_KL", "pt of GENP particles in ele iso (K_{L});P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//  h_pt_iso_KS = fs->make<TH1F>("h_pt_iso_KS", "pt of GENP particles in ele iso (K_{S});P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//  h_pt_iso_p  = fs->make<TH1F>("h_pt_iso_p",  "pt of GENP particles in ele iso (p);P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//  h_pt_iso_n  = fs->make<TH1F>("h_pt_iso_n",  "pt of GENP particles in ele iso (n);P_{T} [GeV/c];Entries",
//			       100,0.,10.);
//
//
//  h_trkiso_diff   = fs->make<TH1F>("h_trkiso_diff", "TrkIso - myTrkIso;P_{T} [GeV/c];Entries",
//				 100,-1.,1.);
//  h_trkiso_dRmin1 = fs->make<TH1F>("h_trkiso_dRmin1", "#DeltaR_{min} for GenP matching (ele 1);#DeltaR_{min}(ele 1);Entries",
//				   100,-0.,0.);
//  h_trkiso_dRmin2 = fs->make<TH1F>("h_trkiso_dRmin2", "#DeltaR_{min} for GenP matching (ele 2);#DeltaR_{min}(ele 2);Entries",
//				   100,-0.,0.);
//  h_trkiso_ID     = fs->make<TH1F>("h_trkiso_ID", "GENP particles in ele iso;GENP ID;Entries",
//				   4800,-2400.,2400.);
//  h_trkiso_ID1    = fs->make<TH1F>("h_trkiso_ID1", "GENP particles in ele1 iso;GENP ID;Entries",
//				   4800,-2400.,2400.);
//  h_trkiso_ID2    = fs->make<TH1F>("h_trkiso_ID2", "GENP particles in ele2 iso;GENP ID;Entries",
//				   4800,-2400.,2400.);
//  				   
//
//  h_trkiso_Pt    = fs->make<TH1F>("h_trkiso_Pt", "pt of tracks in ele iso;P_{T} [GeV/c];Entries",
//				  100,0.,10.);
//  h_trkiso_Pt1   = fs->make<TH1F>("h_trkiso_Pt1", "pt of tracks in ele1 iso;P_{T} [GeV/c];Entries",
//				  100,0.,10.);
//  h_trkiso_Pt2   = fs->make<TH1F>("h_trkiso_Pt2", "pt of tracks in ele2 iso;P_{T} [GeV/c];Entries",
//				  100,0.,10.);
//  h_trkiso_Pt_e  = fs->make<TH1F>("h_trkiso_Pt_e", "pt of tracks in ele iso (e);P_{T} [GeV/c];Entries",
//				  100,0.,10.);
//  h_trkiso_Pt_mu = fs->make<TH1F>("h_trkiso_Pt_mu", "pt of tracks in ele iso (#mu);P_{T} [GeV/c];Entries",
//				  100,0.,10.);
//  h_trkiso_Pt_pi = fs->make<TH1F>("h_trkiso_Pt_pi", "pt of tracks in ele iso (#pi);P_{T} [GeV/c];Entries",
//				  100,0.,10.);
//  h_trkiso_Pt_K  = fs->make<TH1F>("h_trkiso_Pt_K", "pt of tracks in ele iso (K);P_{T} [GeV/c];Entries",
//				  100,0.,10.);
//  h_trkiso_Pt_p  = fs->make<TH1F>("h_trkiso_Pt_p" , "pt of tracks in ele iso (p);P_{T} [GeV/c];Entries",
//				  100,0.,10.);

}


GENPAnalyzer::~GENPAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


#endif

