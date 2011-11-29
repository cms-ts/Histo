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
#include "TTree.h"

#include <FWCore/MessageLogger/interface/MessageLogger.h>
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

using namespace edm;
using namespace reco;
using namespace std;

bool debugJet=false; //If true it will activate the cout verbosity

class TTree;

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
      edm::InputTag pflowCollection_;
      edm::InputTag pflowEleCollection_;
      edm::InputTag genParticleCollection_;
      edm::InputTag VertexCollection_;
      edm::InputTag jetCollection_;
      edm::InputTag goodEPairTag;
      std::string weightCollection_;
      edm::InputTag genJetsCollection;
      bool usingMC;
      bool useCkElInJet;

      //Unfolding Rootple and members
      TTree* treeUN_;
      double Z_pt;
      double Z_y;
      int Jet_multiplicity;
      double Z_pt_gen;
      double Z_y_gen;
      int Jet_multiplicity_gen;


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
      TH1F * h_totalGsfElectronsVsEn;
      TH1F * h_PairedPfElectronsVsEn;
      TH1F * h_totalGsfElectronsVsEta;
      TH1F * h_PairedPfElectronsVsEta;  
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
      TH2F * h_PFenMCenVsMcEnENear;
      TH2F * h_PFenMCenVsMcEtaENear;
      TH2F * h_GSFenMCenVsMcEnENear;
      TH2F * h_GSFenMCenVsMcEtaENear;
      TH1F * h_totalGsfxMcElectronsVsEn;
      TH1F * h_totalGsfxMcElectronsVsEta;
      TH1F * h_totalPfxMcElectronsVsEn;
      TH1F * h_totalPfxMcElectronsVsEta;
      TH1F * h_PairedMcGsfElectronsVsEn;
      TH1F * h_PairedMcPfElectronsVsEn;
      TH1F * h_PairedMcGsfElectronsVsEta;
      TH1F * h_PairedMcPfElectronsVsEta;

      TH1F * h_gsfMcPt;
      TH1F * h_gsfMcEta;
      TH1F * h_gsfMcPhi;
      TH1F * h_pfMcPt;
      TH1F * h_pfMcEta;
      TH1F * h_pfMcPhi;

      TH1F * h_gsfMcGsfPt;
      TH1F * h_gsfMcGsfEta;
      TH1F * h_gsfMcGsfPhi;
      TH1F * h_pfMcPfPt;
      TH1F * h_pfMcPfEta;
      TH1F * h_pfMcPfPhi;

      TH2F * h_gsfMcPtVsPt;
      TH2F * h_gsfMcEtaVsEta;
      TH2F * h_gsfMcPhiVsPhi;
      TH2F * h_pfMcPtVsPt;
      TH2F * h_pfMcEtaVsEta;
      TH2F * h_pfMcPhiVsPhi;

      TH2F * h_gsfMcGsfPtVsPt;
      TH2F * h_gsfMcGsfEtaVsEta;
      TH2F * h_gsfMcGsfPhiVsPhi;
      TH2F * h_pfMcPfPtVsPt;
      TH2F * h_pfMcPfEtaVsEta;
      TH2F * h_pfMcPfPhiVsPhi;

      TH2F * h_gsfMcGsfPtVsEta;
      TH2F * h_gsfMcGsfPtVsPhi;
      TH2F * h_gsfMcGsfEtaVsPt;
      TH2F * h_gsfMcGsfEtaVsPhi;
      TH2F * h_gsfMcGsfPhiVsEta;
      TH2F * h_gsfMcGsfPhiVsPt;
      TH2F * h_pfMcPfPtVsEta;
      TH2F * h_pfMcPfPtVsPhi;
      TH2F * h_pfMcPfEtaVsPt;
      TH2F * h_pfMcPfEtaVsPhi;
      TH2F * h_pfMcPfPhiVsEta;
      TH2F * h_pfMcPfPhiVsPt;

//  distributions about rejected jets -------  
      TH1F * h_sizeJetRejected;     
      TH1F * h_idPdgJet;
      TH1F * h_nConstituents;
      TH1F * h_rJetPt;
      TH1F * h_rJetEta;
      TH1F * h_totEnergy;
      TH1F * h_totPt;
      TProfile * h_energyFraction;
      TProfile * h_jetConstMult;
      TProfile * h_multFraction;
      TH1F * h_chMultiplicity;
      TH1F * h_nMultiplicity;
      TH1F * h_phMultiplicity;
      TH1F * h_elMultiplicity;
      TH1F * h_muMultiplicity;
      TH1F * h_hfHMultiplicity;
      TH1F * h_hfEmMultiplicity;
      TH1F * h_chMultFraction;
      TH1F * h_nMultFraction;
      TH1F * h_phMultFraction;
      TH1F * h_elMultFraction;
      TH1F * h_muMultFraction;
      TH1F * h_hfHMultFraction;
      TH1F * h_hfEmMultFraction;
      TH1F * h_chEnerFraction;
      TH1F * h_nEnerFraction;
      TH1F * h_phEnerFraction;
      TH1F * h_elEnerFraction;
      TH1F * h_muEnerFraction;
      TH1F * h_hfHEnerFraction;
      TH1F * h_hfEmEnerFraction;
      TProfile * h_chMultiplicityVsPt;
      TProfile * h_nMultiplicityVsPt;
      TProfile * h_phMultiplicityVsPt;
      TProfile * h_elMultiplicityVsPt;
      TProfile * h_muMultiplicityVsPt;
      TProfile * h_hfHMultiplicityVsPt;
      TProfile * h_hfEmMultiplicityVsPt;
      TProfile * h_chMultFractionVsPt;
      TProfile * h_nMultFractionVsPt;
      TProfile * h_phMultFractionVsPt;
      TProfile * h_elMultFractionVsPt;
      TProfile * h_muMultFractionVsPt;
      TProfile * h_hfHMultFractionVsPt;
      TProfile * h_hfEmMultFractionVsPt;
      TProfile * h_chEnerFractionVsPt;
      TProfile * h_nEnerFractionVsPt;
      TProfile * h_phEnerFractionVsPt;
      TProfile * h_elEnerFractionVsPt;
      TProfile * h_muEnerFractionVsPt;
      TProfile * h_hfHEnerFractionVsPt;
      TProfile * h_hfEmEnerFractionVsPt;
      TProfile * h_chMultiplicityVsEta;
      TProfile * h_nMultiplicityVsEta;
      TProfile * h_phMultiplicityVsEta;
      TProfile * h_elMultiplicityVsEta;
      TProfile * h_muMultiplicityVsEta;
      TProfile * h_hfHMultiplicityVsEta;
      TProfile * h_hfEmMultiplicityVsEta;
      TProfile * h_chMultFractionVsEta;
      TProfile * h_nMultFractionVsEta;
      TProfile * h_phMultFractionVsEta;
      TProfile * h_elMultFractionVsEta;
      TProfile * h_muMultFractionVsEta;
      TProfile * h_hfHMultFractionVsEta;
      TProfile * h_hfEmMultFractionVsEta;
      TProfile * h_chEnerFractionVsEta;
      TProfile * h_nEnerFractionVsEta;
      TProfile * h_phEnerFractionVsEta;
      TProfile * h_elEnerFractionVsEta;
      TProfile * h_muEnerFractionVsEta;
      TProfile * h_hfHEnerFractionVsEta;
      TProfile * h_hfEmEnerFractionVsEta;
      

// distributions around the electrons -------   
      TH1F * h_idPdgAroundE;  
      TH1F * h_pfIdPdgAroundE;

// distributions about jets -----------------
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
      TH1F * h_zMassNjet0;
      TH1F * h_zMassNjet1;
      TH1F * h_zMassNjet2;
      TH1F * h_zMassNjet3;
      TH1F * h_zMassNjet4;
      TH1F * h_zMassMinusPdgGsfNjet0;
      TH1F * h_zMassMinusPdgGsfNjet1;
      TH1F * h_zMassMinusPdgGsfNjet2;
      TH1F * h_zMassMinusPdgGsfNjet3;
      TH1F * h_zMassMinusPdgGsfNjet4;
      TH1F * h_zMassMinusPdgPfNjet0;
      TH1F * h_zMassMinusPdgPfNjet1;
      TH1F * h_zMassMinusPdgPfNjet2;
      TH1F * h_zMassMinusPdgPfNjet3;
      TH1F * h_zMassMinusPdgPfNjet4;
      
      TH1F * h_sizePf;
     
// constant variable definition ========== 
      double edgeEB;
      double edgeEE;
      double edgeTrk;
      double deltaRCone;
      double pi_;
      double zMassPdg;
      double deltaConeGen;
     
      //vertices
      int numberOfVertices;
};

jetValidation::jetValidation(const edm::ParameterSet& conf)

{
// variable definition =========================
   edgeEB     = 1.479;
   edgeEE     = 3.0;
   edgeTrk    = 2.4;
   edgeEE     = edgeTrk;
   deltaRCone = 0.3;
   deltaConeGen = 0.1;
   pi_ = acos(-1);
   zMassPdg = 91.1876;

  tpMapName = conf.getParameter<std::string>("tpMapName");
  //  weightCollection_ = conf.getParameter<std::string>("EventWeight");
  //  weightCollection_ = conf.getParameter<edm::InputTag>("weightCollection");
  electronCollection_ = conf.getParameter<edm::InputTag>("electronCollection");
  pflowEleCollection_ = conf.getUntrackedParameter<edm::InputTag>("pflowEleCollection",edm::InputTag("particleFlow:electrons"));
  pflowCollection_ = conf.getUntrackedParameter<edm::InputTag>("pflowCollection",edm::InputTag("particleFlow"));
  genParticleCollection_ = conf.getUntrackedParameter<edm::InputTag>("genParticleCollection",edm::InputTag("genParticles"));
  jetCollection_      = conf.getParameter<edm::InputTag>("jetCollection");
  VertexCollection_   = conf.getParameter<edm::InputTag>("VertexCollection");
  goodEPairTag        = conf.getParameter<edm::InputTag>("goodEPair");
  usingMC             = conf.getUntrackedParameter<bool>("usingMC",false);
  useCkElInJet        = conf.getUntrackedParameter<bool>("useCkElInJet",false);
  genJetsCollection   = conf.getParameter<edm::InputTag>("genJets");

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
  h_totalGsfElectronsVsEn = fs->make<TH1F>("h_totalGsfElectronsVsEn","totalGsfElectronsVsEn",10,0,200);
  h_PairedPfElectronsVsEn = fs->make<TH1F>("h_PairedPfElectronsVsEn","PairedPfElectronsVsEn",10,0,200);
  h_totalGsfElectronsVsEta = fs->make<TH1F>("h_totalGsfElectronsVsEta","totalGsfElectronsVsEta",10,-2.5,2.5);
  h_PairedPfElectronsVsEta = fs->make<TH1F>("h_PairedPfElectronsVsEta","PairedPfElectronsVsEta",10,-2.5,2.5);
  
// histo about rejected jets-------------------------------------------------------
  h_sizeJetRejected = fs->make<TH1F>("h_sizeJetRejected","sizeJetRejected",10,0,10);
  h_nConstituents   = fs->make<TH1F>("h_nConstituents","nConstituents",20,0,20);
  h_rJetPt    = fs->make<TH1F>("h_rJetPt","rejected jet pt",500,0.,maxEnJet);
  h_rJetEta   = fs->make<TH1F>("h_rJetEta","rejected jet eta",100,-2.5,2.5);
  h_totEnergy = fs->make<TH1F>("h_totEnergy","totEnergy",100,0,1);
  h_totPt     = fs->make<TH1F>("h_totPt","totPt",100,0,1);
  h_energyFraction = fs->make<TProfile>("h_energyFraction","energyFraction",8,0,8);
  h_jetConstMult   = fs->make<TProfile>("h_jetConstMult","jetConstMult",8,0,8);
  h_multFraction   = fs->make<TProfile>("h_multFraction","multFraction",8,0,8);
  h_chMultiplicity   = fs->make<TH1F>("h_chMultiplicity","chMultiplicity",150,0,150);
  h_nMultiplicity    = fs->make<TH1F>("h_nMultiplicity","nMultiplicity",150,0,150);
  h_phMultiplicity   = fs->make<TH1F>("h_phMultiplicity","phMultiplicity",150,0,150);
  h_elMultiplicity   = fs->make<TH1F>("h_elMultiplicity","elMultiplicity",150,0,150);
  h_muMultiplicity   = fs->make<TH1F>("h_muMultiplicity","muMultiplicity",150,0,150);
  h_hfHMultiplicity  = fs->make<TH1F>("h_hfHMultiplicity","hfHMultiplicity",150,0,150);
  h_hfEmMultiplicity = fs->make<TH1F>("h_hfEmMultiplicity","hfEmMultiplicity",150,0,150);
  h_chMultFraction   = fs->make<TH1F>("h_chMultFraction","chMultFraction",100,0,1);
  h_nMultFraction    = fs->make<TH1F>("h_nMultFraction","nMultFraction",100,0,1);
  h_phMultFraction   = fs->make<TH1F>("h_phMultFraction","phMultFraction",100,0,1);
  h_elMultFraction   = fs->make<TH1F>("h_elMultFraction","elMultFraction",100,0,1);
  h_muMultFraction   = fs->make<TH1F>("h_muMultFraction","muMultFraction",100,0,1);
  h_hfHMultFraction  = fs->make<TH1F>("h_hfHMultFraction","hfHMultFraction",100,0,1);
  h_hfEmMultFraction = fs->make<TH1F>("h_hfEmMultFraction","hfEmMultFraction",100,0,1);
  h_chEnerFraction   = fs->make<TH1F>("h_chEnerFraction","chEnerFraction",100,0,1);
  h_nEnerFraction    = fs->make<TH1F>("h_nEnerFraction","nEnerFraction",100,0,1);
  h_phEnerFraction   = fs->make<TH1F>("h_phEnerFraction","phEnerFraction",100,0,1);
  h_elEnerFraction   = fs->make<TH1F>("h_elEnerFraction","elEnerFraction",100,0,1);
  h_muEnerFraction   = fs->make<TH1F>("h_muEnerFraction","muEnerFraction",100,0,1);
  h_hfHEnerFraction  = fs->make<TH1F>("h_hfHEnerFraction","hfHEnerFraction",100,0,1);
  h_hfEmEnerFraction = fs->make<TH1F>("h_hfEmEnerFraction","hfEmEnerFraction",100,0,1);

  h_chMultiplicityVsPt = fs->make<TProfile>("h_chMultiplicityVsPt","chMultiplicityVsPt",100,0,200);
  h_nMultiplicityVsPt = fs->make<TProfile>("h_nMultiplicityVsPt","nMultiplicityVsPt",100,0,200);
  h_phMultiplicityVsPt = fs->make<TProfile>("h_phMultiplicityVsPt","phMultiplicityVsPt",100,0,200);
  h_elMultiplicityVsPt = fs->make<TProfile>("h_elMultiplicityVsPt","elMultiplicityVsPt",100,0,200);
  h_muMultiplicityVsPt = fs->make<TProfile>("h_muMultiplicityVsPt","muMultiplicityVsPt",100,0,200);
  h_hfHMultiplicityVsPt = fs->make<TProfile>("h_hfHMultiplicityVsPt","hfHMultiplicityVsPt",100,0,200);
  h_hfEmMultiplicityVsPt = fs->make<TProfile>("h_hfEmMultiplicityVsPt","hfEmMultiplicityVsPt",100,0,200);
  h_chMultFractionVsPt = fs->make<TProfile>("h_chMultFractionVsPt","chMultFractionVsPt",100,0,200);
  h_nMultFractionVsPt = fs->make<TProfile>("h_nMultFractionVsPt","nMultFractionVsPt",100,0,200);
  h_phMultFractionVsPt = fs->make<TProfile>("h_phMultFractionVsPt","phMultFractionVsPt",100,0,200);
  h_elMultFractionVsPt = fs->make<TProfile>("h_elMultFractionVsPt","elMultFractionVsPt",100,0,200);
  h_muMultFractionVsPt = fs->make<TProfile>("h_muMultFractionVsPt","muMultFractionVsPt",100,0,200);
  h_hfHMultFractionVsPt = fs->make<TProfile>("h_hfHMultFractionVsPt","hfHMultFractionVsPt",100,0,200);
  h_hfEmMultFractionVsPt = fs->make<TProfile>("h_hfEmMultFractionVsPt","hfEmMultFractionVsPt",100,0,200);
  h_chEnerFractionVsPt = fs->make<TProfile>("h_chEnerFractionVsPt","chEnerFractionVsPt",100,0,200);
  h_nEnerFractionVsPt = fs->make<TProfile>("h_nEnerFractionVsPt","nEnerFractionVsPt",100,0,200);
  h_phEnerFractionVsPt = fs->make<TProfile>("h_phEnerFractionVsPt","phEnerFractionVsPt",100,0,200);
  h_elEnerFractionVsPt = fs->make<TProfile>("h_elEnerFractionVsPt","elEnerFractionVsPt",100,0,200);
  h_muEnerFractionVsPt = fs->make<TProfile>("h_muEnerFractionVsPt","muEnerFractionVsPt",100,0,200);
  h_hfHEnerFractionVsPt = fs->make<TProfile>("h_hfHEnerFractionVsPt","hfHEnerFractionVsPt",100,0,200);
  h_hfEmEnerFractionVsPt = fs->make<TProfile>("h_hfEmEnerFractionVsPt","hfEmEnerFractionVsPt",100,0,200);

  h_chMultiplicityVsEta = fs->make<TProfile>("h_chMultiplicityVsEta","chMultiplicityVsEta",100,-2.5,2.5);
  h_nMultiplicityVsEta = fs->make<TProfile>("h_nMultiplicityVsEta","nMultiplicityVsEta",100,-2.5,2.5);
  h_phMultiplicityVsEta = fs->make<TProfile>("h_phMultiplicityVsEta","phMultiplicityVsEta",100,-2.5,2.5);
  h_elMultiplicityVsEta = fs->make<TProfile>("h_elMultiplicityVsEta","elMultiplicityVsEta",100,-2.5,2.5);
  h_muMultiplicityVsEta = fs->make<TProfile>("h_muMultiplicityVsEta","muMultiplicityVsEta",100,-2.5,2.5);
  h_hfHMultiplicityVsEta = fs->make<TProfile>("h_hfHMultiplicityVsEta","hfHMultiplicityVsEta",100,-2.5,2.5);
  h_hfEmMultiplicityVsEta = fs->make<TProfile>("h_hfEmMultiplicityVsEta","hfEmMultiplicityVsEta",100,-2.5,2.5);
  h_chMultFractionVsEta = fs->make<TProfile>("h_chMultFractionVsEta","chMultFractionVsEta",100,-2.5,2.5);
  h_nMultFractionVsEta = fs->make<TProfile>("h_nMultFractionVsEta","nMultFractionVsEta",100,-2.5,2.5);
  h_phMultFractionVsEta = fs->make<TProfile>("h_phMultFractionVsEta","phMultFractionVsEta",100,-2.5,2.5);
  h_elMultFractionVsEta = fs->make<TProfile>("h_elMultFractionVsEta","elMultFractionVsEta",100,-2.5,2.5);
  h_muMultFractionVsEta = fs->make<TProfile>("h_muMultFractionVsEta","muMultFractionVsEta",100,-2.5,2.5);
  h_hfHMultFractionVsEta = fs->make<TProfile>("h_hfHMultFractionVsEta","hfHMultFractionVsEta",100,-2.5,2.5);
  h_hfEmMultFractionVsEta = fs->make<TProfile>("h_hfEmMultFractionVsEta","hfEmMultFractionVsEta",100,-2.5,2.5);
  h_chEnerFractionVsEta = fs->make<TProfile>("h_chEnerFractionVsEta","chEnerFractionVsEta",100,-2.5,2.5);
  h_nEnerFractionVsEta = fs->make<TProfile>("h_nEnerFractionVsEta","nEnerFractionVsEta",100,-2.5,2.5);
  h_phEnerFractionVsEta = fs->make<TProfile>("h_phEnerFractionVsEta","phEnerFractionVsEta",100,-2.5,2.5);
  h_elEnerFractionVsEta = fs->make<TProfile>("h_elEnerFractionVsEta","elEnerFractionVsEta",100,-2.5,2.5);
  h_muEnerFractionVsEta = fs->make<TProfile>("h_muEnerFractionVsEta","muEnerFractionVsEta",100,-2.5,2.5);
  h_hfHEnerFractionVsEta = fs->make<TProfile>("h_hfHEnerFractionVsEta","hfHEnerFractionVsEta",100,-2.5,2.5);
  h_hfEmEnerFractionVsEta = fs->make<TProfile>("h_hfEmEnerFractionVsEta","hfEmEnerFractionVsEta",100,-2.5,2.5);

// histo of what there is around the electrons -------------------------------------
  h_pfIdPdgAroundE = fs->make<TH1F>("h_pfIdPdgAroundE","pfIdPdgAroundE",10,0,10);

// histo about what there is around the electrons
 
  h_nVtx = fs->make<TH1F>("h_nVtx","h_nVtx",25,0,25);
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
  h_zMassNjet0 = fs->make<TH1F>("h_zMassNjet0","zMassNjet0",200,0,200);
  h_zMassNjet1 = fs->make<TH1F>("h_zMassNjet1","zMassNjet1",60,60,120);
  h_zMassNjet2 = fs->make<TH1F>("h_zMassNjet2","zMassNjet2",60,60,120);
  h_zMassNjet3 = fs->make<TH1F>("h_zMassNjet3","zMassNjet3",60,60,120);
  h_zMassNjet4 = fs->make<TH1F>("h_zMassNjet4","zMassNjet4",60,60,120);
  h_zMassMinusPdgGsfNjet0 = fs->make<TH1F>("h_zMassMinusPdgGsfNjet0","zMassMinusPdgGsfNjet0",100,-50,50);
  h_zMassMinusPdgGsfNjet1 = fs->make<TH1F>("h_zMassMinusPdgGsfNjet1","zMassMinusPdgGsfNjet1",100,-50,50);
  h_zMassMinusPdgGsfNjet2 = fs->make<TH1F>("h_zMassMinusPdgGsfNjet2","zMassMinusPdgGsfNjet2",100,-50,50);
  h_zMassMinusPdgGsfNjet3 = fs->make<TH1F>("h_zMassMinusPdgGsfNjet3","zMassMinusPdgGsfNjet3",100,-50,50);
  h_zMassMinusPdgGsfNjet4 = fs->make<TH1F>("h_zMassMinusPdgGsfNjet4","zMassMinusPdgGsfNjet4",100,-50,50);
  h_zMassMinusPdgPfNjet0 = fs->make<TH1F>("h_zMassMinusPdgPfNjet0","zMassMinusPdgPfNjet0",100,-50,50);
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
    
    stringstream buffer_Bin2;
    int j= i+1;
    buffer_Bin2 << j;
    name ="h_jetPtVtx";
    name += buffer_Bin2.str();
    name +="_EB";
    label = "jetPtVtx";
    label += buffer_Bin2.str();
    label +="_EB";
    h_jetPtVtx_EB[i] = fs->make<TH1F>(name.c_str(),label.c_str(),300,0,300);

    name ="h_jetPtVtx";
    name += buffer_Bin2.str();
    name +="_EE";
    label = "jetPtVtx";
    label += buffer_Bin2.str();
    label +="_EE";
    h_jetPtVtx_EE[i] = fs->make<TH1F>(name.c_str(),label.c_str(),300,0,300);
    
    name ="h_nJetVtx";
    name += buffer_Bin2.str();
    name +="_EB";
    label = "nJetVtx";
    label += buffer_Bin2.str();
    label +="_EB";
    h_nJetVtx_EB[i] = fs->make<TH1F>(name.c_str(),label.c_str(),10,0,10);
    
    name ="h_nJetVtx";
    name += buffer_Bin2.str();
    name +="_EE";
    label = "nJetVtx";
    label += buffer_Bin2.str();
    label +="_EE";
    h_nJetVtx_EE[i] = fs->make<TH1F>(name.c_str(),label.c_str(),10,0,10);
  
  name.clear();
  label.clear();
  }



  if (usingMC){
     h_idPdgJet = fs->make<TH1F>("h_idPdgJet","idPdgJet",100,0,100);
     h_idPdgAroundE = fs->make<TH1F>("h_idPdgAroundE","idPdgAroundE",600,0,600);

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
     h_PFenMCenVsMcEnENear  = fs->make<TH2F>("h_PFenMCenVsMcEnENear","PFenMCenVsMcEnENear",200,0,200,160,0.6,1.4);
     h_PFenMCenVsMcEtaENear = fs->make<TH2F>("h_PFenMCenVsMcEtaENear","PFenMCenVsMcEtaENear",100,-2.5,2.5,160,0.6,1.4);
     h_GSFenMCenVsMcEnENear = fs->make<TH2F>("h_GSFenMCenVsMcEnENear","GSFenMCenVsMcEnENear",200,0,200,160,0.6,1.4);
     h_GSFenMCenVsMcEtaENear= fs->make<TH2F>("h_GSFenMCenVsMcEtaENear","GSFenMCenVsMcEtaENear",100,-2.5,2.5,160,0.6,1.4);
     
     h_gsfMcPt=fs->make<TH1F>("h_gsfMcPt","gsfMcPt",160,0.6,1.4);
     h_gsfMcEta=fs->make<TH1F>("h_gsfMcEta","gsfMcEta",160,0.6,1.4);
     h_gsfMcPhi=fs->make<TH1F>("h_gsfMcPhi","gsfMcPhi",160,0.6,1.4);
     h_pfMcPt=fs->make<TH1F>("h_pfMcPt","pfMcPt",160,0.6,1.4);
     h_pfMcEta=fs->make<TH1F>("h_pfMcEta","pfMcEta",160,0.6,1.4);
     h_pfMcPhi=fs->make<TH1F>("h_pfMcPhi","pfMcPhi",160,0.6,1.4);

     h_gsfMcGsfPt=fs->make<TH1F>("h_gsfMcGsfPt","gsfMcGsfPt",160,-0.5,0.5);
     h_gsfMcGsfEta=fs->make<TH1F>("h_gsfMcGsfEta","gsfMcGsfEta",160,-0.5,0.5);
     h_gsfMcGsfPhi=fs->make<TH1F>("h_gsfMcGsfPhi","gsfMcGsfPhi",160,-0.5,0.5);
     h_pfMcPfPt=fs->make<TH1F>("h_pfMcPfPt","pfMcPfPt",160,-0.5,0.5);
     h_pfMcPfEta=fs->make<TH1F>("h_pfMcPfEta","pfMcPfEta",160,-0.5,0.5);
     h_pfMcPfPhi=fs->make<TH1F>("h_pfMcPfPhi","pfMcPfPhi",160,-0.5,0.5);
     
     h_gsfMcPtVsPt=fs->make<TH2F>("h_gsfMcPtVsPt","gsfMcPtVsPt",200,0,200,160,0.6,1.4);
     h_gsfMcEtaVsEta=fs->make<TH2F>("h_gsfMcEtaVsEta","gsfMcEtaVsEta",100,-2.5,2.5,160,0.6,1.4);
     h_gsfMcPhiVsPhi=fs->make<TH2F>("h_gsfMcPhiVsPhi","gsfMcPhiVsPhi",100,-pi_,pi_,160,0.6,1.4);
     h_pfMcPtVsPt=fs->make<TH2F>("h_pfMcPtVsPt","pfMcPtVsPt",200,0,200,160,0.6,1.4);
     h_pfMcEtaVsEta=fs->make<TH2F>("h_pfMcEtaVsEta","pfMcEtaVsEta",100,-2.5,2.5,160,0.6,1.4);
     h_pfMcPhiVsPhi=fs->make<TH2F>("h_pfMcPhiVsPhi","pfMcPhiVsPhi",100,-pi_,pi_,160,0.6,1.4);

     h_gsfMcGsfPtVsPt=fs->make<TH2F>("h_gsfMcGsfPtVsPt","gsfMcGsfPtVsPt",200,0,200,160,-0.5,0.5);
     h_gsfMcGsfEtaVsEta=fs->make<TH2F>("h_gsfMcGsfEtaVsEta","gsfMcGsfEtaVsEta",100,-2.5,2.5,160,-0.5,0.5);
     h_gsfMcGsfPhiVsPhi=fs->make<TH2F>("h_gsfMcGsfPhiVsPhi","gsfMcGsfPhiVsPhi",100,-pi_,pi_,160,-0.5,0.5);
     h_pfMcPfPtVsPt=fs->make<TH2F>("h_pfMcPfPtVsPt","pfMcPfPtVsPt",200,0,200,160,-0.5,0.5);
     h_pfMcPfEtaVsEta=fs->make<TH2F>("h_pfMcPfEtaVsEta","pfMcPfEtaVsEta",100,-2.5,2.5,160,-0.5,0.5);
     h_pfMcPfPhiVsPhi=fs->make<TH2F>("h_pfMcPfPhiVsPhi","pfMcPfPhiVsPhi",100,-pi_,pi_,160,-0.5,0.5);

     h_gsfMcGsfPtVsEta=fs->make<TH2F>("h_gsfMcGsfPtVsEta","gsfMcGsfPtVsEta",100,-2.5,2.5,160,-0.5,0.5);
     h_gsfMcGsfPtVsPhi=fs->make<TH2F>("h_gsfMcGsfPtVsPhi","gsfMcGsfPtVsPhi",100,-pi_,pi_,160,-0.5,0.5);
     h_gsfMcGsfEtaVsPt=fs->make<TH2F>("h_gsfMcGsfEtaVsPt","gsfMcGsfEtaVsPt",200,0,200,160,-0.5,0.5);
     h_gsfMcGsfEtaVsPhi=fs->make<TH2F>("h_gsfMcGsfEtaVsPhi","gsfMcGsfEtaVsPhi",100,-pi_,pi_,160,-0.5,0.5);
     h_gsfMcGsfPhiVsEta=fs->make<TH2F>("h_gsfMcGsfPhiVsEta","gsfMcGsfPhiVsEta",100,-2.5,2.5,160,-0.5,0.5);
     h_gsfMcGsfPhiVsPt=fs->make<TH2F>("h_gsfMcGsfPhiVsPt","gsfMcGsfPhiVsPt",200,0,200,160,-0.5,0.5);
     h_pfMcPfPtVsEta=fs->make<TH2F>("h_pfMcPfPtVsEta","pfMcPfPtVsEta",100,-2.5,2.5,160,-0.5,0.5);
     h_pfMcPfPtVsPhi=fs->make<TH2F>("h_pfMcPfPtVsPhi","pfMcPfPtVsPhi",100,-pi_,pi_,160,-0.5,0.5);
     h_pfMcPfEtaVsPt=fs->make<TH2F>("h_pfMcPfEtaVsPt","pfMcPfEtaVsPt",200,0,200,160,-0.5,0.5);
     h_pfMcPfEtaVsPhi=fs->make<TH2F>("h_pfMcPfEtaVsPhi","pfMcPfEtaVsPhi",100,-pi_,pi_,160,-0.5,0.5);
     h_pfMcPfPhiVsEta=fs->make<TH2F>("h_pfMcPfPhiVsEta","pfMcPfPhiVsEta",100,-2.5,2.5,160,-0.5,0.5);
     h_pfMcPfPhiVsPt=fs->make<TH2F>("h_pfMcPfPhiVsPt","pfMcPfPhiVsPt",200,0,200,160,-0.5,0.5);

// efficiencies -----------------------
     h_totalGsfxMcElectronsVsEta = fs->make<TH1F>("h_totalGsfxMcElectronsVsEta","totalGsfxMcElectronsVsEta",10,-2.5,2.5);
     h_totalGsfxMcElectronsVsEn = fs->make<TH1F>("h_totalGsfxMcElectronsVsEn","totalGsfxMcElectronsVsEn",10,0,200);
     h_totalPfxMcElectronsVsEta = fs->make<TH1F>("h_totalPfxMcElectronsVsEta","totalPfxMcElectronsVsEta",10,-2.5,2.5);
     h_totalPfxMcElectronsVsEn = fs->make<TH1F>("h_totalPfxMcElectronsVsEn","totalPfxMcElectronsVsEn",10,0,200);
     h_PairedMcPfElectronsVsEn = fs->make<TH1F>("h_PairedMcPfElectronsVsEn","PairedMcPfElectronsVsEn",10,0,200);
     h_PairedMcGsfElectronsVsEn = fs->make<TH1F>("h_PairedMcGsfElectronsVsEn","PairedMcGsfElectronsVsEn",10,0,200);
     h_PairedMcPfElectronsVsEta = fs->make<TH1F>("h_PairedMcPfElectronsVsEta","PairedMcPfElectronsVsEta",10,-2.5,2.5);
     h_PairedMcGsfElectronsVsEta = fs->make<TH1F>("h_PairedMcGsfElectronsVsEta","PairedMcGsfElectronsVsEta",10,-2.5,2.5);   
  }
}


jetValidation::~jetValidation()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

#endif
