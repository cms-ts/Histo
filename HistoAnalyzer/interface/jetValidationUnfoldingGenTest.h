#ifndef jetValidationUnfoldingGenTest_h
#define jetValidationUnfoldingGenTest_h

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
//JEC
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

//#include "Histo/HistoAnalyzer/macros/TemplateForHistogramsUnfolding.h" // skeleton to clone the histograms

using namespace edm;
using namespace reco;
using namespace std;

class TTree;

/////
// class declaration
/////

class jetValidationUnfoldingGenTest : public edm::EDAnalyzer {
   public:
      explicit jetValidationUnfoldingGenTest(const edm::ParameterSet&);
      ~jetValidationUnfoldingGenTest();

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual double evaluateJECUncertainties(double jetpt,double jeteta);
      virtual int isTauOrMu(edm::Handle<GenParticleCollection> genParticlesCollection);
      
      double distR(TLorentzVector ,math::XYZTLorentzVector);

      std::string WeightName;
      std::string WeightNameSherpa;

      std::string EleGammaGenPt_;
      std::string EleGammaGenEta;
      std::string MuGammaGenPt;
      std::string MuGammaGenEta;
 

      // ----------member data ---------------------------

      //Retrieved from the .py
      edm::InputTag electronCollection_;
      edm::InputTag pflowCollection_;
      edm::InputTag genParticleCollection_;
      edm::InputTag VertexCollection_;
      edm::InputTag jetCollection_;
      edm::InputTag goodEPairTag;
      std::string weightCollection_;
      edm::InputTag genJetsCollection;
      std::string rootuplaname;
      bool usingMC;
      bool usingPF;
      bool useCkElInJet;
      bool doPlotsJetComposition;
      bool isElectron;
      double param;
      bool isSherpa;
      bool isUnfolding_;

      int oneJet;
      int twoJets;
      int threeJets;
      int fourJets;
      int eventNumberCounter;

      //JEC
      JetCorrectorParameters *p;
      JetCorrectionUncertainty *t;
	
      //UnfoldingGenTest Rootple and members
      TTree* treeUN_;

      double evWeight;
      double evWeightSherpa;
      double Z_pt;
      double Z_y;
      int Jet_multiplicity;
      double Z_pt_gen;
      double Z_y_gen;
      int Jet_multiplicity_gen;
      double jet1_pt_gen;
      double jet2_pt_gen;
      double jet3_pt_gen;
      double jet4_pt_gen;
      double jet5_pt_gen;
      double jet6_pt_gen;
      double jet7_pt_gen;


      double jet1_eta_gen;
      double jet2_eta_gen;
      double jet3_eta_gen;
      double jet4_eta_gen;
      double jet5_eta_gen;
      double jet6_eta_gen;
      double jet7_eta_gen;

      double invMass_gen;
      double l1_pt_gen;
      double l1_eta_gen;
      double l2_pt_gen;
      double l2_eta_gen;

      //std::vector<double> jetPtVector;
      //std::vector<double> genJetPtVector;

      // member for angular distributions  
      double e1_pt;
      double e1_eta;
      double e1_phi;
      double e1_mass;
      double e2_pt;
      double e2_eta;
      double e2_phi;
      double e2_mass;
      double z_mass;
      
      double jet1_pt;
      double jet2_pt;
      double jet3_pt;
      double jet4_pt;
      double jet5_pt;
      double jet6_pt;
      double jet7_pt;

      double jet1_eta;
      double jet2_eta;
      double jet3_eta;
      double jet4_eta;
      double jet5_eta;
      double jet6_eta;
      double jet7_eta;

      double jet1_phi;
      double jet2_phi;
      double jet3_phi;
      double jet4_phi;
      double jet1_mass;
      double jet2_mass;
      double jet3_mass; 
      double jet4_mass;     
      double jetHt;


      //taueMuons
      bool isMugen;
      bool isTaugen;

      // Weight
      TH1F * h_weights;
      TH1F * h_weightsSherpa;

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
      TH1F * h_massMinusPdgGsf_EB;
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
      TH1F * h_massMinusPdgGsf_EE;
// EB - EE ================================
      // electrons
      TH1F * h_massMinusPdgGsf_EBEE;

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
      TH1F * h_jetEtaNjet1;
      TH1F * h_jetEtaNjet2;
      TH1F * h_jetEtaNjet3;
      TH1F * h_jetEtaNjet4;
      TH1F * h_jetEtaNjet1Incl;
      TH1F * h_jetEtaNjet2Incl;
      TH1F * h_jetEtaNjet3Incl;
      TH1F * h_jetEtaNjet4Incl;

      TH1F * h_jetHtNjet1;
      TH1F * h_jetHtNjet2;
      TH1F * h_jetHtNjet3;
      TH1F * h_jetHtNjet4;

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
      TH1F * h_massMinusPdgGsf;
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
      
      TH1F * h_sizePf;
     
// constant variable definition ========== 
      double edgeEB;
      double edgeEE;
      double edgeTrk;
      double deltaRCone;
      double deltaRConeJet;
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

      int leptonId;
      int genZInAcceptance;
      int recoZInAcceptance;
     
      //vertices
      int numberOfVertices;
};

jetValidationUnfoldingGenTest::jetValidationUnfoldingGenTest(const edm::ParameterSet& conf)

{
// variable definition =========================
   edgeEB     = 1.479;
   edgeEE     = 3.0;
   edgeTrk    = 2.4;
   edgeEE     = edgeTrk;
   //deltaRCone = 0.3;
   //deltaConeGen = 0.1;
   pi_ = acos(-1);
   zMassPdg = 91.1876;

   //WeightName = conf.getParameter<std::string>("WeightName");
   //WeightNameSherpa = conf.getParameter<std::string>("WeightNameSherpa");
  //  weightCollection_ = conf.getParameter<std::string>("EventWeight");
  //  weightCollection_ = conf.getParameter<edm::InputTag>("weightCollection");
  //electronCollection_ = conf.getParameter<edm::InputTag>("electronCollection");
  //pflowCollection_ = conf.getUntrackedParameter<edm::InputTag>("pflowCollection",edm::InputTag("particleFlow"));
  genParticleCollection_ = conf.getUntrackedParameter<edm::InputTag>("genParticleCollection",edm::InputTag("genParticles"));
  //jetCollection_      = conf.getParameter<edm::InputTag>("jetCollection");
  //VertexCollection_   = conf.getParameter<edm::InputTag>("VertexCollection");
  //goodEPairTag        = conf.getParameter<edm::InputTag>("goodEPair");
  usingPF             = conf.getUntrackedParameter<bool>("usingPF",false);
  usingMC             = conf.getUntrackedParameter<bool>("usingMC",false);
  useCkElInJet        = conf.getUntrackedParameter<bool>("useCkElInJet",false);
  genJetsCollection   = conf.getParameter<edm::InputTag>("genJets");
  //isElectron          = conf.getUntrackedParameter<bool>("isElectron",true);
  //isSherpa            = conf.getUntrackedParameter<bool>("isSherpa",false);
  //isUnfolding_          = conf.getUntrackedParameter<bool>("isUnfoldingGenTest",true);
  //genParticleCollection_= conf.getUntrackedParameter<edm::InputTag>("genParticleCollection",edm::InputTag("genParticles"));
  EleGammaGenPt_ = conf.getParameter<std::string>("EleGammaGenPt_");
  EleGammaGenEta = conf.getParameter<std::string>("EleGammaGenEta");
  MuGammaGenPt = conf.getParameter<std::string>("MuGammaGenPt");
  MuGammaGenEta = conf.getParameter<std::string>("MuGammaGenEta");
  
  // variable to enable the fill of the plots
  //doPlotsJetComposition  = conf.getUntrackedParameter<bool>("doPlotsJetComposition",true); 

  //now do what ever initialization is needed
  //edm::Service<TFileService> fs; 

  //Weights
  //h_weights = fs->make<TH1F>("h_weights","Event Weights",500,0.,5);
  //h_weightsSherpa= fs->make<TH1F>("h_weightsSherpa","Event Weights with Sherpa",500,0.,5);

  //Jets Properties
  deltaRCone           = conf.getParameter<double>("deltaRCone");
  deltaRConeJet          = conf.getParameter<double>("deltaRConeJet");
  deltaConeGen        = conf.getParameter<double>("deltaRConeGen");
  maxEtaJets           = conf.getParameter<double>("maxEtaJets");
  minPtJets            = conf.getParameter<double>("minPtJets");
  chargedEmEnergyFraction = conf.getParameter<double>("chargedEmEnergyFraction");
  neutralHadronEnergyFraction= conf.getParameter<double>("neutralHadronEnergyFraction");
  neutralEmEnergyFraction= conf.getParameter<double>("neutralEmEnergyFraction");
  chargedHadronEnergyFraction= conf.getParameter<double>("chargedHadronEnergyFraction");
  chargedMultiplicity= conf.getParameter<int>("chargedMultiplicity");
  //param                = conf.getParameter<double>("JECUncertainties");
  rootuplaname          = conf.getParameter< std::string > ("RootuplaName");

  double maxEnJet=200;

}


jetValidationUnfoldingGenTest::~jetValidationUnfoldingGenTest()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

#endif
