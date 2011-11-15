#ifndef jetValidation_h
#define jetValidation_h

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

#include <FWCore/MessageLogger/interface/MessageLogger.h>
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

using namespace edm;
using namespace reco;
using namespace std;

bool debugJet=false; //If true it will activate the cout verbosity


/////
// class declaration
/////

class jetValidation : public edm::EDAnalyzer {
   public:
      explicit jetValidation(const edm::ParameterSet&);
      ~jetValidation();

   private:
      virtual void beginJob() ;
      virtual void beginRun(edm::Run const &, const edm::EventSetup&);
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;


      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);


      std::string tpMapName;
      // ----------member data ---------------------------

      //Retrieved from the .py
      edm::InputTag electronCollection_;
      edm::InputTag pflowEleCollection_;
      edm::InputTag genParticleCollection_;
      edm::InputTag VertexCollection_;
      edm::InputTag jetCollection_;
      edm::InputTag goodEPairTag;
      std::string weightCollection_;
      bool usingMC;

      // Weight
      TH1F * h_weights;

//EB ==============================
      // jets
      TH1F * h_jetPt_EB;
      TH1F * h_jetEta_EB;
      TH1F * h_jetNum_EB;
      TH1F * h_jetPtFirst_EB;
      TH1F * h_jetPtSecond_EB;
      TH1F * h_jetPtThird_EB;
      TH1F * h_jetPtFourth_EB;
      TH1F * h_jetPtFirstCk_EB;
      TH1F * h_jetPtSecondCk_EB;
      TH1F * h_jetPtThirdCk_EB;
      TH1F * h_jetPtFourthCk_EB;
      TH2F * h_jetPtVsEta_EB;
      TH1F * h_jetPtVtx_EB[11];
      TH1F * h_nJetVtx_EB[11];
      TH1F * h_jetPtNjet1_EB;
      TH1F * h_jetPtNjet2_EB;
      TH1F * h_jetPtNjet3_EB;
      TH1F * h_jetPtNjet4_EB;
      // electrons
      TH1F * h_gsfPfSCEta_EB;
      TH1F * h_gsfPfSCEn_EB;
      TH2F * h_gsfPfSCEnVsEn_EB;
      TH2F * h_gsfPfSCEtaVsEn_EB;
      TH1F * h_massMinusPdgGsf_EB;
      TH1F * h_massMinusPdgPf_EB;
//EE ==============================
      //jets
      TH1F * h_jetPt_EE;
      TH1F * h_jetEta_EE;
      TH1F * h_jetNum_EE;
      TH1F * h_jetPtFirst_EE;
      TH1F * h_jetPtSecond_EE;
      TH1F * h_jetPtThird_EE;
      TH1F * h_jetPtFourth_EE;
      TH1F * h_jetPtFirstCk_EE;
      TH1F * h_jetPtSecondCk_EE;
      TH1F * h_jetPtThirdCk_EE;
      TH1F * h_jetPtFourthCk_EE;
      TH2F * h_jetPtVsEta_EE;
      TH1F * h_jetPtVtx_EE[11];
      TH1F * h_nJetVtx_EE[11];
      TH1F * h_jetPtNjet1_EE;
      TH1F * h_jetPtNjet2_EE;
      TH1F * h_jetPtNjet3_EE;
      TH1F * h_jetPtNjet4_EE;
      // electrons
      TH1F * h_gsfPfSCEta_EE;
      TH1F * h_gsfPfSCEn_EE;
      TH2F * h_gsfPfSCEnVsEn_EE;
      TH2F * h_gsfPfSCEtaVsEn_EE;
      TH1F * h_massMinusPdgGsf_EE;
      TH1F * h_massMinusPdgPf_EE;
// EB - EE ================================
      // electrons
      TH1F * h_massMinusPdgGsf_EBEE;
      TH1F * h_massMinusPdgPf_EBEE;
//common ==================================
      // electrons
      TH2F * h_gsfPfSCEtaVsEta;
      TProfile2D * h_gsfPfSCEnVsEtaPhi;
      TH2F * h_ptPFptVsEta;
      TH2F * h_ptPFptVsEn;
      TH1F * h_superClusterSize;
      TH1F * h_gsfPfSCEnClu1;
      TH2F * h_ptGsfPfGsfVsptGsf;
      // with MonteCarlo
      TH2F * h_MCenPFenVsEn;
      TH2F * h_MCenPFenVsEta;
      TH2F * h_MCenGSFenVsEn;
      TH2F * h_MCenGSFenVsEta;
      TH2F * h_MCenPFenVsEnWoEnCut;
      TH2F * h_MCenPFenVsEtaWoEnCut;
      TH2F * h_MCenGSFenVsEnWoEnCut;
      TH2F * h_MCenGSFenVsEtaWoEnCut;
      TH1F * h_failReason;
      TH2F * h_MCenPFenVsEnTruth;
      TH2F * h_MCenPFenVsEtaTruth;
      TH2F * h_MCenGSFenVsEnTruth;
      TH2F * h_MCenGSFenVsEtaTruth;
      TH2F * h_MCenPFenVsEnENear;
      TH2F * h_MCenPFenVsEtaENear;
      TH2F * h_MCenGSFenVsEnENear;
      TH2F * h_MCenGSFenVsEtaENear;
      TH2F * h_PFenMCenVsEnENear;
      TH2F * h_PFenMCenVsEtaENear;
      TH2F * h_GSFenMCenVsEnENear;
      TH2F * h_GSFenMCenVsEtaENear;
      TH2F * h_gsfMcPfMcEnVsGsfEnENear;
      TH2F * h_gsfMcPfMcEnVsGsfEtaENear;
      TH2F * h_gsfMcPfMcEnVsGsfMcEnENear;

      TH1F * h_nVtx;
      TH1F * h_ptZ_jetIncl[11];
      TH1F * h_ptZ_jet[11];
      TH1F * h_zYieldVsjets;
      TH1F * h_zYieldVsjetsVtx1;
      TH1F * h_zYieldVsjetsVtx5;
      TH1F * h_jetPtNjet1;
      TH1F * h_jetPtNjet2;
      TH1F * h_jetPtNjet3;
      TH1F * h_jetPtNjet4;
      TH1F * h_jetPtNjet1Incl;
      TH1F * h_jetPtNjet2Incl;
      TH1F * h_jetPtNjet3Incl;
      TH1F * h_jetPtNjet4Incl;
      TH1F * h_zEta;
      TH1F * h_zRapidity;
      TH1F * h_zEtaNjet0;
      TH1F * h_zEtaNjet1;
      TH1F * h_zEtaNjet2;
      TH1F * h_zEtaNjet3;
      TH1F * h_zEtaNjet4;
      TH1F * h_zEtaNjet1Incl;
      TH1F * h_zEtaNjet2Incl;
      TH1F * h_zEtaNjet3Incl;
      TH1F * h_zEtaNjet4Incl;
      TH1F * h_invMass;
      TH1F * h_invMassPF;
      TH1F * h_massMinusPdgGsf;
      TH1F * h_massMinusPdgPf;
      TH1F * h_zMassNjet1;
      TH1F * h_zMassNjet2;
      TH1F * h_zMassNjet3;
      TH1F * h_zMassNjet4;
      TH1F * h_zMassMinusPdgGsfNjet1;
      TH1F * h_zMassMinusPdgGsfNjet2;
      TH1F * h_zMassMinusPdgGsfNjet3;
      TH1F * h_zMassMinusPdgGsfNjet4;
      TH1F * h_zMassMinusPdgPfNjet1;
      TH1F * h_zMassMinusPdgPfNjet2;
      TH1F * h_zMassMinusPdgPfNjet3;
      TH1F * h_zMassMinusPdgPfNjet4;
      
      TH1F * h_sizePf;
      

      double edgeEB;
      double edgeEE;
      double edgeTrk;
      //vertices
      int numberOfVertices;
      double deltaRCone;
      double pi_;
      double zMassPdg;
     
};

jetValidation::jetValidation(const edm::ParameterSet& conf)

{

  pi_ = acos(-1);
  zMassPdg = 91.1876;
  tpMapName = conf.getParameter<std::string>("tpMapName");
  //  weightCollection_ = conf.getParameter<std::string>("EventWeight");
  //  weightCollection_ = conf.getParameter<edm::InputTag>("weightCollection");
  electronCollection_ = conf.getParameter<edm::InputTag>("electronCollection");
  pflowEleCollection_ = conf.getUntrackedParameter<edm::InputTag>("pflowEleCollection",edm::InputTag("particleFlow:electrons"));
  genParticleCollection_ = conf.getUntrackedParameter<edm::InputTag>("genParticleCollection",edm::InputTag("genParticles"));
  jetCollection_      = conf.getParameter<edm::InputTag>("jetCollection");
  VertexCollection_   = conf.getParameter<edm::InputTag>("VertexCollection");
  goodEPairTag        = conf.getParameter<edm::InputTag>("goodEPair");
  usingMC             = conf.getUntrackedParameter<bool>("usingMC",false);

  //now do what ever initialization is needed
  edm::Service<TFileService> fs; 

  //Weights
  h_weights = fs->make<TH1F>("h_weights","Event Weights",500,0.,5);

  double maxEnJet=200;
//EB ========================================================================
  h_jetPt_EB = fs->make<TH1F>("h_jetPt_EB","jetPt_EB",500,0.,maxEnJet);
  h_jetEta_EB = fs->make<TH1F>("h_jetEta_EB","jetEta_EB",100,-2.5,2.5);
  h_jetNum_EB = fs->make<TH1F>("h_jetNum_EB","jetNum_EB",10,0.,10);
  h_jetPtFirst_EB = fs->make<TH1F>("h_jetPtFirst_EB","jetPtFirst in EB",500,0.,maxEnJet);
  h_jetPtSecond_EB = fs->make<TH1F>("h_jetPtSecond_EB","jetPtSecond in EB",500,0.,maxEnJet);
  h_jetPtThird_EB = fs->make<TH1F>("h_jetPtThird_EB","jetPtThird in EB",500,0.,maxEnJet);
  h_jetPtFourth_EB = fs->make<TH1F>("h_jetPtFourth_EB","jetPtFourth in EB",500,0.,maxEnJet);
  h_jetPtFirstCk_EB = fs->make<TH1F>("h_jetPtFirstCk_EB","jetPt of the absolute first jet - EB",500,0.,maxEnJet);
  h_jetPtSecondCk_EB = fs->make<TH1F>("h_jetPtSecondCk_EB","jetPt of the absolute second jet - EB",500,0.,maxEnJet);
  h_jetPtThirdCk_EB = fs->make<TH1F>("h_jetPtThirdCk_EB","jetPt of the absolute third jet - EB",500,0.,maxEnJet);
  h_jetPtFourthCk_EB = fs->make<TH1F>("h_jetPtFourthCk_EB","jetPt of the absolute fourth jet - EB",500,0.,maxEnJet);
  h_jetPtVsEta_EB = fs->make<TH2F>("h_jetPtVsEta_EB","jetPtVsEta_EB",100,-2.5,2.5,500,0.,maxEnJet);
  h_jetPtNjet1_EB = fs->make<TH1F>("h_jetPtNjet1_EB","jetPtNjet1_EB",500,0.,maxEnJet);
  h_jetPtNjet2_EB = fs->make<TH1F>("h_jetPtNjet2_EB","jetPtNjet2_EB",500,0.,maxEnJet);
  h_jetPtNjet3_EB = fs->make<TH1F>("h_jetPtNjet3_EB","jetPtNjet3_EB",500,0.,maxEnJet);
  h_jetPtNjet4_EB = fs->make<TH1F>("h_jetPtNjet4_EB","jetPtNjet4_EB",500,0.,maxEnJet);

  h_gsfPfSCEta_EB = fs->make<TH1F>("h_gsfPfSCEta_EB","gsfPfSCEta_EB",160,0.6,1.4);
  h_gsfPfSCEn_EB = fs->make<TH1F>("h_gsfPfSCEn_EB","gsfPfSCEn_EB",160,0.6,1.4);
  h_gsfPfSCEnVsEn_EB = fs->make<TH2F>("h_gsfPfSCEnVsEn_EB","gsfPfSCEnVsEn_EB",200,0,200,160,0.6,1.4);
  h_gsfPfSCEtaVsEn_EB = fs->make<TH2F>("h_gsfPfSCEtaVsEn_EB","gsfPfSCEtaVsEn_EB",200,0,200,160,0.6,1.4);
  h_massMinusPdgGsf_EB = fs->make<TH1F>("h_massMinusPdgGsf_EB","massMinusPdgGsf_EB",100,-50,50);
  h_massMinusPdgPf_EB  = fs->make<TH1F>("h_massMinusPdgPf_EB","massMinusPdgPf_EB",100,-50,50);
//EE ========================================================================
  h_jetPt_EE = fs->make<TH1F>("h_jetPt_EE","jetPt_EE",500,0.,maxEnJet);
  h_jetEta_EE = fs->make<TH1F>("h_jetEta_EE","jetEta_EE",100,-2.5,2.5);
  h_jetNum_EE = fs->make<TH1F>("h_jetNum_EE","jetNum_EE",10,0.,10);
  h_jetPtFirst_EE = fs->make<TH1F>("h_jetPtFirst_EE","jetPtFirst in EE",500,0.,maxEnJet);
  h_jetPtSecond_EE = fs->make<TH1F>("h_jetPtSecond_EE","jetPtSecond in EE",500,0.,maxEnJet);
  h_jetPtThird_EE = fs->make<TH1F>("h_jetPtThird_EE","jetPtThird in EE",500,0.,maxEnJet);
  h_jetPtFourth_EE = fs->make<TH1F>("h_jetPtFourth_EE","jetPtFourth in EE",500,0.,maxEnJet);
  h_jetPtFirstCk_EE = fs->make<TH1F>("h_jetPtFirstCk_EE","jetPt of the absolute first jet - EE",500,0.,maxEnJet);
  h_jetPtSecondCk_EE = fs->make<TH1F>("h_jetPtSecondCk_EE","jetPt of the absolute second jet - EE",500,0.,maxEnJet);
  h_jetPtThirdCk_EE = fs->make<TH1F>("h_jetPtThirdCk_EE","jetPt of the absolute third jet - EE",500,0.,maxEnJet);
  h_jetPtFourthCk_EE = fs->make<TH1F>("h_jetPtFourthCk_EE","jetPt of the absolute fourth jet - EE",500,0.,maxEnJet);
  h_jetPtVsEta_EE = fs->make<TH2F>("h_jetPtVsEta_EE","jetPtVsEta_EE",100,-2.5,2.5,500,0.,maxEnJet);
  h_jetPtNjet1_EE = fs->make<TH1F>("h_jetPtNjet1_EE","jetPtNjet1_EE",500,0.,maxEnJet);
  h_jetPtNjet2_EE = fs->make<TH1F>("h_jetPtNjet2_EE","jetPtNjet2_EE",500,0.,maxEnJet);
  h_jetPtNjet3_EE = fs->make<TH1F>("h_jetPtNjet3_EE","jetPtNjet3_EE",500,0.,maxEnJet);
  h_jetPtNjet4_EE = fs->make<TH1F>("h_jetPtNjet4_EE","jetPtNjet4_EE",500,0.,maxEnJet);

  h_gsfPfSCEta_EE = fs->make<TH1F>("h_gsfPfSCEta_EE","gsfPfSCEta_EE",40,0.9,1.1);
  h_gsfPfSCEn_EE = fs->make<TH1F>("h_gsfPfSCEn_EE","gsfPfSCEn_EE",160,0.6,1.4);
  h_gsfPfSCEnVsEn_EE = fs->make<TH2F>("h_gsfPfSCEnVsEn_EE","gsfPfSCEnVsEn_EE",200,0,200,160,0.6,1.4);
  h_gsfPfSCEtaVsEn_EE = fs->make<TH2F>("h_gsfPfSCEtaVsEn_EE","gsfPfSCEtaVsEn_EE",200,0,200,40,0.9,1.1);
  h_massMinusPdgGsf_EE = fs->make<TH1F>("h_massMinusPdgGsf_EE","massMinusPdgGsf_EE",100,-50,50);
  h_massMinusPdgPf_EE  = fs->make<TH1F>("h_massMinusPdgPf_EE","massMinusPdgPf_EE",100,-50,50);
// EB - EE ========================================================================
  h_massMinusPdgGsf_EBEE = fs->make<TH1F>("h_massMinusPdgGsf_EBEE","massMinusPdgGsf_EBEE",100,-50,50);
  h_massMinusPdgPf_EBEE  = fs->make<TH1F>("h_massMinusPdgPf_EBEE","massMinusPdgPf_EBEE",100,-50,50);
//common ========================================================================
  h_gsfPfSCEtaVsEta = fs->make<TH2F>("h_gsfPfSCEnVsEta","gsfPfSCEnVsEta",100,-2.5,2.5,160,0.6,1.4);
  h_gsfPfSCEnVsEtaPhi = fs->make<TProfile2D>("h_gsfPfSCEnVsEtaPhi","gsfPfSCEnVsEtaPhi",100,-2.5,2.5,100,-pi_,pi_);
  h_ptPFptVsEta  = fs->make<TH2F>("h_ptPFptVsEta","ptPFptVsEta",100,-2.5,2.5,160,0.6,1.4);
  h_ptPFptVsEn   = fs->make<TH2F>("h_ptPFptVsEn","ptPFptVsEn",200,0,200,160,0.6,1.4);
  h_superClusterSize = fs->make<TH1F>("h_superClusterSize","superClusterSize",10,0,10);
  h_gsfPfSCEnClu1 = fs->make<TH1F>("h_gsfPfSCEnClu1","gsfPfSCEnClu1",160,0.6,1.4);
  h_ptGsfPfGsfVsptGsf = fs->make<TH2F>("h_ptGsfPfGsfVsptGsf","(ptGsf - ptPf) / ptGsf Vs ptGsf",200,0,200,200,-1.,1.);
 
  h_nVtx = fs->make<TH1F>("h_nVtx","h_nVtx",10,0,10);
  h_zYieldVsjets  = fs->make<TH1F>("h_zYieldVsjets","zYieldVsjets",10,0,10);
  h_zYieldVsjetsVtx1  = fs->make<TH1F>("h_zYieldVsjetsVtx1","zYieldVsjetsVtx1",10,0,10);
  h_zYieldVsjetsVtx5  = fs->make<TH1F>("h_zYieldVsjetsVtx5","zYieldVsjetsVtx5",10,0,10);
  h_jetPtNjet1 = fs->make<TH1F>("h_jetPtNjet1","jetPtNjet1",500,0.,maxEnJet);
  h_jetPtNjet2 = fs->make<TH1F>("h_jetPtNjet2","jetPtNjet2",500,0.,maxEnJet);
  h_jetPtNjet3 = fs->make<TH1F>("h_jetPtNjet3","jetPtNjet3",500,0.,maxEnJet);
  h_jetPtNjet4 = fs->make<TH1F>("h_jetPtNjet4","jetPtNjet4",500,0.,maxEnJet);
  h_jetPtNjet1Incl = fs->make<TH1F>("h_jetPtNjet1Incl","jetPtNjet1Incl",500,0.,maxEnJet);
  h_jetPtNjet2Incl = fs->make<TH1F>("h_jetPtNjet2Incl","jetPtNjet2Incl",500,0.,maxEnJet);
  h_jetPtNjet3Incl = fs->make<TH1F>("h_jetPtNjet3Incl","jetPtNjet3Incl",500,0.,maxEnJet);
  h_jetPtNjet4Incl = fs->make<TH1F>("h_jetPtNjet4Incl","jetPtNjet4Incl",500,0.,maxEnJet);
  h_zEta      = fs->make<TH1F>("h_zEta","zEta",100,-2.5,2.5);
  h_zRapidity = fs->make<TH1F>("h_zRapidity","zRapidity",100,-2.5,2.5);
  h_zEtaNjet0 = fs->make<TH1F>("h_zEtaNjet0","zEtaNjet0",100,-2.5,2.5);
  h_zEtaNjet1 = fs->make<TH1F>("h_zEtaNjet1","zEtaNjet1",100,-2.5,2.5);
  h_zEtaNjet2 = fs->make<TH1F>("h_zEtaNjet2","zEtaNjet2",100,-2.5,2.5);
  h_zEtaNjet3 = fs->make<TH1F>("h_zEtaNjet3","zEtaNjet3",100,-2.5,2.5);
  h_zEtaNjet4 = fs->make<TH1F>("h_zEtaNjet4","zEtaNjet4",100,-2.5,2.5);
  h_zEtaNjet1Incl = fs->make<TH1F>("h_zEtaNjet1Incl","zEtaNjet1Incl",100,-2.5,2.5);
  h_zEtaNjet2Incl = fs->make<TH1F>("h_zEtaNjet2Incl","zEtaNjet2Incl",100,-2.5,2.5);
  h_zEtaNjet3Incl = fs->make<TH1F>("h_zEtaNjet3Incl","zEtaNjet3Incl",100,-2.5,2.5);
  h_zEtaNjet4Incl = fs->make<TH1F>("h_zEtaNjet4Incl","zEtaNjet4Incl",100,-2.5,2.5);
  h_invMass    = fs->make<TH1F>("h_invMass","invMass",60,60,120);
  h_invMassPF  = fs->make<TH1F>("h_invMassPF","invMassPF",60,60,120);
  h_massMinusPdgGsf   = fs->make<TH1F>("h_massMinusPdgGsf","massMinusPdgGsf",100,-50,50);
  h_massMinusPdgPf   = fs->make<TH1F>("h_massMinusPdgPf","massMinusPdgPf",100,-50,50);
  h_zMassNjet1 = fs->make<TH1F>("h_zMassNjet1","zMassNjet1",60,60,120);
  h_zMassNjet2 = fs->make<TH1F>("h_zMassNjet2","zMassNjet2",60,60,120);
  h_zMassNjet3 = fs->make<TH1F>("h_zMassNjet3","zMassNjet3",60,60,120);
  h_zMassNjet4 = fs->make<TH1F>("h_zMassNjet4","zMassNjet4",60,60,120);
  h_zMassMinusPdgGsfNjet1 = fs->make<TH1F>("h_zMassMinusPdgGsfNjet1","zMassMinusPdgGsfNjet1",100,-50,50);
  h_zMassMinusPdgGsfNjet2 = fs->make<TH1F>("h_zMassMinusPdgGsfNjet2","zMassMinusPdgGsfNjet2",100,-50,50);
  h_zMassMinusPdgGsfNjet3 = fs->make<TH1F>("h_zMassMinusPdgGsfNjet3","zMassMinusPdgGsfNjet3",100,-50,50);
  h_zMassMinusPdgGsfNjet4 = fs->make<TH1F>("h_zMassMinusPdgGsfNjet4","zMassMinusPdgGsfNjet4",100,-50,50);
  h_zMassMinusPdgPfNjet1 = fs->make<TH1F>("h_zMassMinusPdgPfNjet1","zMassMinusPdgPfNjet1",100,-50,50);
  h_zMassMinusPdgPfNjet2 = fs->make<TH1F>("h_zMassMinusPdgPfNjet2","zMassMinusPdgPfNjet2",100,-50,50);
  h_zMassMinusPdgPfNjet3 = fs->make<TH1F>("h_zMassMinusPdgPfNjet3","zMassMinusPdgPfNjet3",100,-50,50);
  h_zMassMinusPdgPfNjet4 = fs->make<TH1F>("h_zMassMinusPdgPfNjet4","zMassMinusPdgPfNjet4",100,-50,50);

  h_sizePf = fs->make<TH1F>("h_sizePf","sizePf",3,0,3);
  
  for (int i=0; i<=10; i++){
    stringstream buffer_Bin;
	         buffer_Bin << i;
    string name;
           name ="h_ptZ_jet_";
           name += buffer_Bin.str();
    string label;
           label = "ptZ_jet_";
           label += buffer_Bin.str();
    h_ptZ_jet[i] = fs->make<TH1F>(name.c_str(),label.c_str(),500,0,maxEnJet);
    name +="Incl";
    label +="Incl";
    h_ptZ_jetIncl[i] = fs->make<TH1F>(name.c_str(),label.c_str(),500,0,maxEnJet);

    buffer_Bin.clear();
    int j= i+1;
    buffer_Bin << j;
    name ="h_jetPtVtx";
    name += buffer_Bin.str();
    name +="_EB";
    label = "jetPtVtx";
    label += buffer_Bin.str();
    label +="_EB";
    h_jetPtVtx_EB[i] = fs->make<TH1F>(name.c_str(),label.c_str(),300,0,300);

    name ="h_jetPtVtx";
    name += buffer_Bin.str();
    name +="_EE";
    label = "jetPtVtx";
    label += buffer_Bin.str();
    label +="_EE";
    h_jetPtVtx_EE[i] = fs->make<TH1F>(name.c_str(),label.c_str(),300,0,300);
    
    name ="h_nJetVtx";
    name += buffer_Bin.str();
    name +="_EB";
    label = "nJetVtx";
    label += buffer_Bin.str();
    label +="_EB";
    h_nJetVtx_EB[i] = fs->make<TH1F>(name.c_str(),label.c_str(),10,0,10);
    
    name ="h_nJetVtx";
    name += buffer_Bin.str();
    name +="_EE";
    label = "nJetVtx";
    label += buffer_Bin.str();
    label +="_EE";
    h_nJetVtx_EE[i] = fs->make<TH1F>(name.c_str(),label.c_str(),10,0,10);
  
  name.clear();
  label.clear();
  }



  if (usingMC){
     h_MCenPFenVsEn  = fs->make<TH2F>("h_MCenPFenVsEn","MCenPFenVsEn",200,0,200,160,0.6,1.4);
     h_MCenPFenVsEta = fs->make<TH2F>("h_MCenPFenVsEta","MCenPFenVsEta",100,-2.5,2.5,160,0.6,1.4);
     h_MCenGSFenVsEn = fs->make<TH2F>("h_MCenGSFenVsEn","MCenGSFenVsEn",200,0,200,160,0.6,1.4);
     h_MCenGSFenVsEta= fs->make<TH2F>("h_MCenGSFenVsEta","MCenGSFenVsEta",100,-2.5,2.5,160,0.6,1.4);
     h_MCenPFenVsEnWoEnCut   = fs->make<TH2F>("h_MCenPFenVsEnWoEnCut","MCenPFenVsEnWoEnCut",200,0,200,160,0.6,1.4);
     h_MCenPFenVsEtaWoEnCut  = fs->make<TH2F>("h_MCenPFenVsEtaWoEnCut","MCenPFenVsEtaWoEnCut",100,-2.5,2.5,160,0.6,1.4);
     h_MCenGSFenVsEnWoEnCut  = fs->make<TH2F>("h_MCenGSFenVsEnWoEnCut","MCenGSFenVsEnWoEnCut",200,0,200,160,0.6,1.4);
     h_MCenGSFenVsEtaWoEnCut = fs->make<TH2F>("h_MCenGSFenVsEtaWoEnCut","MCenGSFenVsEtaWoEnCut",100,-2.5,2.5,160,0.6,1.4);
     h_failReason = fs->make<TH1F>("h_failReason","failReason",5,0,5);
     h_MCenPFenVsEnTruth  = fs->make<TH2F>("h_MCenPFenVsEnTruth","MCenPFenVsEnTruth",200,0,200,160,0.6,1.4);
     h_MCenPFenVsEtaTruth = fs->make<TH2F>("h_MCenPFenVsEtaTruth","MCenPFenVsEtaTruth",100,-2.5,2.5,160,0.6,1.4);
     h_MCenGSFenVsEnTruth = fs->make<TH2F>("h_MCenGSFenVsEnTruth","MCenGSFenVsEnTruth",200,0,200,160,0.6,1.4);
     h_MCenGSFenVsEtaTruth= fs->make<TH2F>("h_MCenGSFenVsEtaTruth","MCenGSFenVsEtaTruth",100,-2.5,2.5,160,0.6,1.4);
     h_MCenPFenVsEnENear  = fs->make<TH2F>("h_MCenPFenVsEnENear","MCenPFenVsEnENear",200,0,200,160,0.6,1.4);
     h_MCenPFenVsEtaENear = fs->make<TH2F>("h_MCenPFenVsEtaENear","MCenPFenVsEtaENear",100,-2.5,2.5,160,0.6,1.4);
     h_MCenGSFenVsEnENear = fs->make<TH2F>("h_MCenGSFenVsEnENear","MCenGSFenVsEnENear",200,0,200,160,0.6,1.4);
     h_MCenGSFenVsEtaENear= fs->make<TH2F>("h_MCenGSFenVsEtaENear","MCenGSFenVsEtaENear",100,-2.5,2.5,160,0.6,1.4);
     h_PFenMCenVsEnENear  = fs->make<TH2F>("h_PFenMCenVsEnENear","PFenMCenVsEnENear",200,0,200,160,0.6,1.4);
     h_PFenMCenVsEtaENear = fs->make<TH2F>("h_PFenMCenVsEtaENear","PFenMCenVsEtaENear",100,-2.5,2.5,160,0.6,1.4);
     h_GSFenMCenVsEnENear = fs->make<TH2F>("h_GSFenMCenVsEnENear","GSFenMCenVsEnENear",200,0,200,160,0.6,1.4);
     h_GSFenMCenVsEtaENear= fs->make<TH2F>("h_GSFenMCenVsEtaENear","GSFenMCenVsEtaENear",100,-2.5,2.5,160,0.6,1.4);
     h_gsfMcPfMcEnVsGsfEnENear= fs->make<TH2F>("h_gsfMcPfMcEnVsGsfEnENear","gsfMcPfMcEnVsGsfEnENear",200,0,200,160,0.6,1.4);
     h_gsfMcPfMcEnVsGsfEtaENear= fs->make<TH2F>("h_gsfMcPfMcEnVsGsfEtaENear","gsfMcPfMcEnVsGsfEtaENear",100,-2.5,2.5,160,0.6,1.4);
     h_gsfMcPfMcEnVsGsfMcEnENear=fs->make<TH2F>("h_gsfMcPfMcEnVsGsfMcEnENear","gsfMcPfMcEnVsGsfMcEnENear",160,0.6,1.4,160,0.6,1.4);
  }
}


jetValidation::~jetValidation()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

#endif
