#ifndef reclusVal_h
#define reclusVal_h

// system files
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <stddef.h>
//#include <map>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "HLTrigger/HLTfilters/interface/HLTHighLevel.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// root includes
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile2D.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TTree.h"

#include <FWCore/MessageLogger/interface/MessageLogger.h>
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

using namespace edm;
using namespace reco;
using namespace std;

/////
// class declaration
/////

class reclusVal : public edm::EDAnalyzer {
   public:
      explicit reclusVal(const edm::ParameterSet&);
      ~reclusVal();

   private:
      virtual void beginJob() ;
      virtual void beginRun(edm::Run const &, const edm::EventSetup&);
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;


      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      double distR(TLorentzVector ,math::XYZTLorentzVector);

      std::string tpMapName;
      // ----------member data ---------------------------

      //Retrieved from the .py
      edm::InputTag electronCollection_;
      edm::InputTag pflowCollection_;
      edm::InputTag VertexCollection_;
      edm::InputTag jetCollection_;
      edm::InputTag jetCollectionPU_;
      edm::InputTag jetCollectionRC_;
      edm::InputTag goodEPairTag;
      std::string weightCollection_;
      bool usingMC;
      bool usingPF;
      bool testMC;

      // Weight
      TH1F * h_weights;

//EB ==============================
      // 
      TH1F * h_deltaEtaBV_EB;
      TH1F * h_deltaEtaBVe_EB;
      TH1F * h_deltaEtaBVjet_EB;
      TH1F * h_cracksEtaBVe_EB;
      TH1F * h_cracksEtaBVjet_EB;
      TH2F * h_cracksEtaBV_EB;
      TH2F * h_totEtaBV_EB;
      TH2F * h_totEtaBVe_EB;
      TH2F * h_totEtaBVjet_EB;
      TH1F * h_cracks2EtaBVe_EB;
      TH1F * h_cracks2EtaBVjet_EB;
      TH2F * h_cracks2EtaBV_EB;
      TH1F * h_deltaEtaAV_EB;
      TH2F * h_totEtaAV_EB;
      TH1F * h_deltaEtaRC_EB;
      TH2F * h_totEtaRC_EB;
      TH1F * h_deltaPhiBV_EB;
      TH1F * h_deltaPhiAV_EB;
      TH1F * h_deltaPhiRC_EB;
      TH1F * h_deltaRBV_EB;
      TH1F * h_deltaRAV_EB;
      TH1F * h_deltaRRC_EB;

      TH2F * h_deltaEtaPhiBV_EB;
      TH2F * h_deltaEtaPhiAV_EB;
      TH2F * h_deltaEtaPhiRC_EB;
//EE ==============================
      //
      TH1F * h_deltaEtaBV_EE;
      TH1F * h_deltaEtaBVe_EE;
      TH1F * h_deltaEtaBVjet_EE;
      TH2F * h_totEtaBV_EE;
      TH2F * h_totEtaBVe_EE;
      TH2F * h_totEtaBVjet_EE;
      TH1F * h_deltaEtaAV_EE;
      TH2F * h_totEtaAV_EE;
      TH1F * h_deltaEtaRC_EE;
      TH2F * h_totEtaRC_EE;
      TH1F * h_deltaPhiBV_EE;
      TH1F * h_deltaPhiAV_EE;
      TH1F * h_deltaPhiRC_EE;
      TH1F * h_deltaRBV_EE;
      TH1F * h_deltaRAV_EE;
      TH1F * h_deltaRRC_EE;
     
      TH2F * h_deltaEtaPhiBV_EE;
      TH2F * h_deltaEtaPhiAV_EE;
      TH2F * h_deltaEtaPhiRC_EE;
      
// common
      TH1F * h_zPt_1jetPU;
      TH1F * h_zPt_1jetInclPU;
      TH1F * h_zPt_1jetRC;
      TH1F * h_zPt_1jetInclRC;

// constant variable definition ========== 
      double edgeEB;
      double edgeEE;
      double edgeTrk;
      double deltaRCone;
      double pi_;
      double zMassPdg;
      double deltaConeGen;
      double maxEtaJets;
      double minPtJets;
      double chargedEmEnergyFraction;
      double neutralHadronEnergyFraction;
      double neutralEmEnergyFraction;
      double chargedHadronEnergyFraction;
      int chargedMultiplicity;
     
      //vertices
      int numberOfVertices;
};

reclusVal::reclusVal(const edm::ParameterSet& conf)

{
// variable definition =========================
   edgeEB     = 1.479;
   edgeEE     = 3.0;
   edgeTrk    = 2.4;
   edgeEE     = edgeTrk;
   pi_ = acos(-1);
   zMassPdg = 91.1876;

  tpMapName = conf.getParameter<std::string>("tpMapName");
  electronCollection_ = conf.getParameter<edm::InputTag>("electronCollection");
  pflowCollection_ = conf.getUntrackedParameter<edm::InputTag>("pflowCollection",edm::InputTag("particleFlow"));
  jetCollection_      = conf.getParameter<edm::InputTag>("jetCollection");
  jetCollectionPU_      = conf.getParameter<edm::InputTag>("jetCollectionPU");
  jetCollectionRC_      = conf.getParameter<edm::InputTag>("jetCollectionRC");
  VertexCollection_   = conf.getParameter<edm::InputTag>("VertexCollection");
  goodEPairTag        = conf.getParameter<edm::InputTag>("goodEPair");
  usingPF             = conf.getUntrackedParameter<bool>("usingPF",false);
  usingMC             = conf.getUntrackedParameter<bool>("usingMC",false);
  testMC             = conf.getUntrackedParameter<bool>("testMC",false);
 

  //now do what ever initialization is needed
  edm::Service<TFileService> fs; 

  //Weights
  h_weights = fs->make<TH1F>("h_weights","Event Weights",500,0.,5);

  //Jets Properties
  deltaRCone           = conf.getParameter<double>("deltaRCone");
  deltaConeGen        = conf.getParameter<double>("deltaRConeGen");
  maxEtaJets           = conf.getParameter<double>("maxEtaJets");
  minPtJets            = conf.getParameter<double>("minPtJets");
  chargedEmEnergyFraction = conf.getParameter<double>("chargedEmEnergyFraction");
  neutralHadronEnergyFraction= conf.getParameter<double>("neutralHadronEnergyFraction");
  neutralEmEnergyFraction= conf.getParameter<double>("neutralEmEnergyFraction");
  chargedHadronEnergyFraction= conf.getParameter<double>("chargedHadronEnergyFraction");
  chargedMultiplicity= conf.getParameter<int>("chargedMultiplicity");

//EB ========================================================================
  h_deltaEtaBV_EB = fs->make<TH1F>("h_deltaEtaBV_EB","deltaEtaBV_EB",500,0,5);
  h_deltaEtaBVe_EB = fs->make<TH1F>("h_deltaEtaBVe_EB","deltaEtaBVe_EB",500,0,5);
  h_deltaEtaBVjet_EB = fs->make<TH1F>("h_deltaEtaBVjet_EB","deltaEtaBVjet_EB",500,0,5);
  h_cracksEtaBVe_EB = fs->make<TH1F>("h_cracksEtaBVe_EB","cracksEtaBVe_EB",500,-2.5,2.5);
  h_cracksEtaBVjet_EB = fs->make<TH1F>("h_cracksEtaBVjet_EB","cracksEtaBVjet_EB",500,-2.5,2.5);
  h_cracksEtaBV_EB = fs->make<TH2F>("h_cracksEtaBV_EB","cracksEtaBV_EB",500,-2.5,2.5,500,-2.5,2.5);
  h_totEtaBV_EB = fs->make<TH2F>("h_totEtaBV_EB","totEtaBV_EB",500,-2.5,2.5,500,-2.5,2.5);
  h_totEtaBVe_EB = fs->make<TH2F>("h_totEtaBVe_EB","totEtaBVe_EB",500,-2.5,2.5,500,-2.5,2.5);
  h_totEtaBVjet_EB = fs->make<TH2F>("h_totEtaBVjet_EB","totEtaBVjet_EB",500,-2.5,2.5,500,-2.5,2.5);
  h_cracks2EtaBVe_EB = fs->make<TH1F>("h_cracks2EtaBVe_EB","cracks2EtaBVe_EB",500,-2.5,2.5);
  h_cracks2EtaBVjet_EB = fs->make<TH1F>("h_cracks2EtaBVjet_EB","cracks2EtaBVjet_EB",500,-2.5,2.5);
  h_cracks2EtaBV_EB = fs->make<TH2F>("h_cracks2EtaBV_EB","cracks2EtaBV_EB",500,-2.5,2.5,500,-2.5,2.5);
  h_deltaEtaAV_EB = fs->make<TH1F>("h_deltaEtaAV_EB","deltaEtaAV_EB",500,0,5);
  h_totEtaAV_EB = fs->make<TH2F>("h_totEtaAV_EB","totEtaAV_EB",500,-2.5,2.5,500,-2.5,2.5);
  h_deltaEtaRC_EB = fs->make<TH1F>("h_deltaEtaRC_EB","deltaEtaRC_EB",500,0,5);
  h_totEtaRC_EB = fs->make<TH2F>("h_totEtaRC_EB","totEtaRC_EB",500,-2.5,2.5,500,-2.5,2.5);

  h_deltaPhiBV_EB = fs->make<TH1F>("h_deltaPhiBV_EB","deltaPhiBV_EB",500,0,6.5);
  h_deltaPhiAV_EB = fs->make<TH1F>("h_deltaPhiAV_EB","deltaPhiAV_EB",500,0,6.5);
  h_deltaPhiRC_EB = fs->make<TH1F>("h_deltaPhiRC_EB","deltaPhiRC_EB",500,0,6.5); 

  h_deltaRBV_EB = fs->make<TH1F>("h_deltaRBV_EB","deltaRBV_EB",500,0,10);
  h_deltaRAV_EB = fs->make<TH1F>("h_deltaRAV_EB","deltaRAV_EB",500,0,10);
  h_deltaRRC_EB = fs->make<TH1F>("h_deltaRRC_EB","deltaRRC_EB",500,0,10);
  
  h_deltaEtaPhiBV_EB = fs->make<TH2F>("h_deltaEtaPhiBV_EB","deltaEtaPhiBV_EB",500,0,5,500,0,6.5);
  h_deltaEtaPhiAV_EB = fs->make<TH2F>("h_deltaEtaPhiAV_EB","deltaEtaPhiAV_EB",500,0,5,500,0,6.5);
  h_deltaEtaPhiRC_EB = fs->make<TH2F>("h_deltaEtaPhiRC_EB","deltaEtaPhiRC_EB",500,0,5,500,0,6.5);
//EE ========================================================================
  h_deltaEtaBV_EE = fs->make<TH1F>("h_deltaEtaBV_EE","deltaEtaBV_EE",500,0,5);
  h_deltaEtaBVe_EE = fs->make<TH1F>("h_deltaEtaBVe_EE","deltaEtaBVe_EE",500,0,5);
  h_deltaEtaBVjet_EE = fs->make<TH1F>("h_deltaEtaBVjet_EE","deltaEtaBVjet_EE",500,0,5);
  h_totEtaBV_EE = fs->make<TH2F>("h_totEtaBV_EE","totEtaBV_EE",500,-2.5,2.5,500,-2.5,2.5);
  h_totEtaAV_EE = fs->make<TH2F>("h_totEtaAV_EE","totEtaAV_EE",500,-2.5,2.5,500,-2.5,2.5);
  h_totEtaRC_EE = fs->make<TH2F>("h_totEtaRC_EE","totEtaRC_EE",500,-2.5,2.5,500,-2.5,2.5);
  h_totEtaBVe_EE = fs->make<TH2F>("h_totEtaBVe_EE","totEtaBVe_EE",500,-2.5,2.5,500,-2.5,2.5);
  h_totEtaBVjet_EE = fs->make<TH2F>("h_totEtaBVjet_EE","totEtaBVjet_EE",500,-2.5,2.5,500,-2.5,2.5);
  h_deltaEtaAV_EE = fs->make<TH1F>("h_deltaEtaAV_EE","deltaEtaAV_EE",500,0,5);
  h_deltaEtaRC_EE = fs->make<TH1F>("h_deltaEtaRC_EE","deltaEtaRC_EE",500,0,5);

  h_deltaPhiBV_EE = fs->make<TH1F>("h_deltaPhiBV_EE","deltaPhiBV_EE",500,0,6.5);
  h_deltaPhiAV_EE = fs->make<TH1F>("h_deltaPhiAV_EE","deltaPhiAV_EE",500,0,6.5);
  h_deltaPhiRC_EE = fs->make<TH1F>("h_deltaPhiRC_EE","deltaPhiRC_EE",500,0,6.5); 

  h_deltaRBV_EE = fs->make<TH1F>("h_deltaRBV_EE","deltaRBV_EE",500,0,10);
  h_deltaRAV_EE = fs->make<TH1F>("h_deltaRAV_EE","deltaRAV_EE",500,0,10);
  h_deltaRRC_EE = fs->make<TH1F>("h_deltaRRC_EE","deltaRRC_EE",500,0,10);
  
  h_deltaEtaPhiBV_EE = fs->make<TH2F>("h_deltaEtaPhiBV_EE","deltaEtaPhiBV_EE",500,0,5,500,0,6.5);
  h_deltaEtaPhiAV_EE = fs->make<TH2F>("h_deltaEtaPhiAV_EE","deltaEtaPhiAV_EE",500,0,5,500,0,6.5);
  h_deltaEtaPhiRC_EE = fs->make<TH2F>("h_deltaEtaPhiRC_EE","deltaEtaPhiRC_EE",500,0,5,500,0,6.5);

  // common
  h_zPt_1jetPU = fs->make<TH1F>("h_zPt_1jetPU","zPt_1jetPU",200,0,200);
  h_zPt_1jetRC = fs->make<TH1F>("h_zPt_1jetRC","zPt_1jetRC",200,0,200);
  h_zPt_1jetInclPU = fs->make<TH1F>("h_zPt_1jetInclPU","zPt_1jetInclPU",200,0,200);
  h_zPt_1jetInclRC = fs->make<TH1F>("h_zPt_1jetInclRC","zPt_1jetInclRC",200,0,200);

}


reclusVal::~reclusVal()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

#endif
