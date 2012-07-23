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
//JEC
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include "Histo/HistoAnalyzer/macros/TemplateForHistograms.h" // skeleton to clone the histograms

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
      virtual double evaluateJECUncertainties(double jetpt,double jeteta);
      virtual int isTauOrMu(edm::Handle<GenParticleCollection> genParticlesCollection);
      
      double distR(TLorentzVector ,math::XYZTLorentzVector);

      std::string WeightName;
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

      //JEC
      JetCorrectorParameters *p;
      JetCorrectionUncertainty *t;
	
      //Unfolding Rootple and members
      TTree* treeUN_;

      double evWeight;
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


      double jet1_eta_gen;
      double jet2_eta_gen;
      double jet3_eta_gen;
      double jet4_eta_gen;
      double jet5_eta_gen;
      double jet6_eta_gen;

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

      double jet1_eta;
      double jet2_eta;
      double jet3_eta;
      double jet4_eta;
      double jet5_eta;
      double jet6_eta;

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
   //deltaRCone = 0.3;
   //deltaConeGen = 0.1;
   pi_ = acos(-1);
   zMassPdg = 91.1876;

  WeightName = conf.getParameter<std::string>("WeightName");
  //  weightCollection_ = conf.getParameter<std::string>("EventWeight");
  //  weightCollection_ = conf.getParameter<edm::InputTag>("weightCollection");
  electronCollection_ = conf.getParameter<edm::InputTag>("electronCollection");
  pflowCollection_ = conf.getUntrackedParameter<edm::InputTag>("pflowCollection",edm::InputTag("particleFlow"));
  genParticleCollection_ = conf.getUntrackedParameter<edm::InputTag>("genParticleCollection",edm::InputTag("genParticles"));
  jetCollection_      = conf.getParameter<edm::InputTag>("jetCollection");
  VertexCollection_   = conf.getParameter<edm::InputTag>("VertexCollection");
  goodEPairTag        = conf.getParameter<edm::InputTag>("goodEPair");
  usingPF             = conf.getUntrackedParameter<bool>("usingPF",false);
  usingMC             = conf.getUntrackedParameter<bool>("usingMC",false);
  useCkElInJet        = conf.getUntrackedParameter<bool>("useCkElInJet",false);
  genJetsCollection   = conf.getParameter<edm::InputTag>("genJets");
  isElectron          = conf.getUntrackedParameter<bool>("isElectron",true);

  // variable to enable the fill of the plots
  doPlotsJetComposition  = conf.getUntrackedParameter<bool>("doPlotsJetComposition",true); 

  //now do what ever initialization is needed
  edm::Service<TFileService> fs; 

  //Weights
  h_weights = fs->make<TH1F>("h_weights","Event Weights",500,0.,5);

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
  param                = conf.getParameter<double>("JECUncertainties");
  rootuplaname          = conf.getParameter< std::string > ("RootuplaName");

  double maxEnJet=200;
//EB ========================================================================
  h_jetPt_EB = fs->make<TH1F>("h_jetPt_EB","jetPt_EB",divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetEta_EB = fs->make<TH1F>("h_jetEta_EB","jetEta_EB",100,-2.5,2.5);
  h_jetNum_EB = fs->make<TH1F>("h_jetNum_EB","jetNum_EB",10,minPtPlot_leading,10);
  h_jetPtFirst_EB = fs->make<TH1F>("h_jetPtFirst_EB","jetPtFirst in EB",divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetPtSecond_EB = fs->make<TH1F>("h_jetPtSecond_EB","jetPtSecond in EB",divPlot_subleading,minPtPlot_subleading,maxPtPlot_subleading);
  h_jetPtThird_EB = fs->make<TH1F>("h_jetPtThird_EB","jetPtThird in EB",divPlot_subsubleading,minPtPlot_subsubleading,maxPtPlot_subsubleading);
  h_jetPtFourth_EB = fs->make<TH1F>("h_jetPtFourth_EB","jetPtFourth in EB",divPlot_subsubsubleading,minPtPlot_subsubsubleading,maxPtPlot_subsubsubleading);
  h_jetPtFirstCk_EB = fs->make<TH1F>("h_jetPtFirstCk_EB","jetPt of the absolute first jet - EB",divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetPtSecondCk_EB = fs->make<TH1F>("h_jetPtSecondCk_EB","jetPt of the absolute second jet - EB",divPlot_subleading,minPtPlot_subleading,maxPtPlot_subleading);
  h_jetPtThirdCk_EB = fs->make<TH1F>("h_jetPtThirdCk_EB","jetPt of the absolute third jet - EB",divPlot_subsubleading,minPtPlot_subsubleading,maxPtPlot_subsubleading);
  h_jetPtFourthCk_EB = fs->make<TH1F>("h_jetPtFourthCk_EB","jetPt of the absolute fourth jet - EB",divPlot_subsubsubleading,minPtPlot_subsubsubleading,maxPtPlot_subsubsubleading);
  h_jetPtVsEta_EB = fs->make<TH2F>("h_jetPtVsEta_EB","jetPtVsEta_EB",100,-2.5,2.5,divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetPtNjet1_EB = fs->make<TH1F>("h_jetPtNjet1_EB","jetPtNjet1_EB",divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetPtNjet2_EB = fs->make<TH1F>("h_jetPtNjet2_EB","jetPtNjet2_EB",divPlot_subleading,minPtPlot_subleading,maxPtPlot_subleading);
  h_jetPtNjet3_EB = fs->make<TH1F>("h_jetPtNjet3_EB","jetPtNjet3_EB",divPlot_subsubleading,minPtPlot_subsubleading,maxPtPlot_subsubleading);
  h_jetPtNjet4_EB = fs->make<TH1F>("h_jetPtNjet4_EB","jetPtNjet4_EB",divPlot_subsubsubleading,minPtPlot_subsubsubleading,maxPtPlot_subsubsubleading);
  h_massMinusPdgGsf_EB = fs->make<TH1F>("h_massMinusPdgGsf_EB","massMinusPdgGsf_EB",100,-50,50);
//EE ========================================================================
  h_jetPt_EE = fs->make<TH1F>("h_jetPt_EE","jetPt_EE",divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetEta_EE = fs->make<TH1F>("h_jetEta_EE","jetEta_EE",100,-2.5,2.5);
  h_jetNum_EE = fs->make<TH1F>("h_jetNum_EE","jetNum_EE",10,0.,10);
  h_jetPtFirst_EE = fs->make<TH1F>("h_jetPtFirst_EE","jetPtFirst in EE",divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetPtSecond_EE = fs->make<TH1F>("h_jetPtSecond_EE","jetPtSecond in EE",divPlot_subleading,minPtPlot_subleading,maxPtPlot_subleading);
  h_jetPtThird_EE = fs->make<TH1F>("h_jetPtThird_EE","jetPtThird in EE",divPlot_subsubleading,minPtPlot_subsubleading,maxPtPlot_subsubleading);
  h_jetPtFourth_EE = fs->make<TH1F>("h_jetPtFourth_EE","jetPtFourth in EE",divPlot_subsubsubleading,minPtPlot_subsubsubleading,maxPtPlot_subsubsubleading);
  h_jetPtFirstCk_EE = fs->make<TH1F>("h_jetPtFirstCk_EE","jetPt of the absolute first jet - EE",divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetPtSecondCk_EE = fs->make<TH1F>("h_jetPtSecondCk_EE","jetPt of the absolute second jet - EE",divPlot_subleading,minPtPlot_subleading,maxPtPlot_subleading);
  h_jetPtThirdCk_EE = fs->make<TH1F>("h_jetPtThirdCk_EE","jetPt of the absolute third jet - EE",divPlot_subsubleading,minPtPlot_subsubleading,maxPtPlot_subsubleading);
  h_jetPtFourthCk_EE = fs->make<TH1F>("h_jetPtFourthCk_EE","jetPt of the absolute fourth jet - EE",divPlot_subsubsubleading,minPtPlot_subsubsubleading,maxPtPlot_subsubsubleading);
  h_jetPtVsEta_EE = fs->make<TH2F>("h_jetPtVsEta_EE","jetPtVsEta_EE",100,-2.5,2.5,divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetPtNjet1_EE = fs->make<TH1F>("h_jetPtNjet1_EE","jetPtNjet1_EE",divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetPtNjet2_EE = fs->make<TH1F>("h_jetPtNjet2_EE","jetPtNjet2_EE",divPlot_subleading,minPtPlot_subleading,maxPtPlot_subleading);
  h_jetPtNjet3_EE = fs->make<TH1F>("h_jetPtNjet3_EE","jetPtNjet3_EE",divPlot_subsubleading,minPtPlot_subsubleading,maxPtPlot_subsubleading);
  h_jetPtNjet4_EE = fs->make<TH1F>("h_jetPtNjet4_EE","jetPtNjet4_EE",divPlot_subsubsubleading,minPtPlot_subsubsubleading,maxPtPlot_subsubsubleading);
  h_massMinusPdgGsf_EE = fs->make<TH1F>("h_massMinusPdgGsf_EE","massMinusPdgGsf_EE",100,-50,50);
// EB - EE ========================================================================
  h_massMinusPdgGsf_EBEE = fs->make<TH1F>("h_massMinusPdgGsf_EBEE","massMinusPdgGsf_EBEE",100,-50,50);

// histo about rejected jets-------------------------------------------------------
  if (doPlotsJetComposition){
     h_sizeJetRejected = fs->make<TH1F>("h_sizeJetRejected","number of rejected jets",10,0,10);
     h_nConstituents   = fs->make<TH1F>("h_nConstituents","nConstituents of rejected jets",20,0,20);
     h_rJetPt    = fs->make<TH1F>("h_rJetPt","rejected jet pt",500,0.,maxEnJet);
     h_rJetEta   = fs->make<TH1F>("h_rJetEta","rejected jet eta",100,-2.5,2.5);
     h_totEnergy = fs->make<TH1F>("h_totEnergy","totEnergy",100,0,1);
     h_totPt     = fs->make<TH1F>("h_totPt","totPt",100,0,1);
     h_energyFraction = fs->make<TProfile>("h_energyFraction","energyFraction of rejected jets",8,0,8);
     h_jetConstMult   = fs->make<TProfile>("h_jetConstMult","jetConstMult of rejected jets",8,0,8);
     h_multFraction   = fs->make<TProfile>("h_multFraction","multiplicityFraction of rejected jets",8,0,8);
     h_chMultiplicity   = fs->make<TH1F>("h_chMultiplicity","charged Hadron Multiplicity of rejected jets",60,0,60);
     h_nMultiplicity    = fs->make<TH1F>("h_nMultiplicity","neutral Hadron Multiplicity of rejected jets",60,0,60);
     h_phMultiplicity   = fs->make<TH1F>("h_phMultiplicity","photon Multiplicity of rejected jets",60,0,60);
     h_elMultiplicity   = fs->make<TH1F>("h_elMultiplicity","electron Multiplicity of rejected jets",60,0,60);
     h_muMultiplicity   = fs->make<TH1F>("h_muMultiplicity","muon Multiplicity of rejected jets",60,0,60);
     h_hfHMultiplicity  = fs->make<TH1F>("h_hfHMultiplicity","hf Hadronic Multiplicity of rejected jets",60,0,60);
     h_hfEmMultiplicity = fs->make<TH1F>("h_hfEmMultiplicity","hf Electromagnetic Multiplicity of rejected jets",60,0,60);
     h_chMultFraction   = fs->make<TH1F>("h_chMultFraction","charged Hadron Multiplicity Fraction of rejected jets",100,0,1);
     h_nMultFraction    = fs->make<TH1F>("h_nMultFraction","neutral Hadron Multiplicity Fraction of rejected jets",100,0,1);
     h_phMultFraction   = fs->make<TH1F>("h_phMultFraction","photon Multiplicity Fraction of rejected jets",100,0,1);
     h_elMultFraction   = fs->make<TH1F>("h_elMultFraction","electron Multiplicity Fraction of rejected jets",100,0,1);
     h_muMultFraction   = fs->make<TH1F>("h_muMultFraction","muon Multiplicity Fraction of rejected jets",100,0,1);
     h_hfHMultFraction  = fs->make<TH1F>("h_hfHMultFraction","hf Hadronic Multiplicity Fraction of rejected jets",100,0,1);
     h_hfEmMultFraction = fs->make<TH1F>("h_hfEmMultFraction","hf Electromagnetic Multiplicity Fraction of rejected jets",100,0,1);
     h_chEnerFraction   = fs->make<TH1F>("h_chEnerFraction","charged Hadron Energy Fraction of rejected jets",100,0,1);
     h_nEnerFraction    = fs->make<TH1F>("h_nEnerFraction","neutral Hadron Enerergy Fraction of rejected jets",100,0,1);
     h_phEnerFraction   = fs->make<TH1F>("h_phEnerFraction","photon Enerergy Fraction of rejected jets",100,0,1);
     h_elEnerFraction   = fs->make<TH1F>("h_elEnerFraction","electron Energy Fraction of rejected jets",100,0,1);
     h_muEnerFraction   = fs->make<TH1F>("h_muEnerFraction","muon Energy Fraction of rejected jets",100,0,1);
     h_hfHEnerFraction  = fs->make<TH1F>("h_hfHEnerFraction","hf Hadronic Energy Fraction of rejected jets",100,0,1);
     h_hfEmEnerFraction = fs->make<TH1F>("h_hfEmEnerFraction","hf Electromagnetic Energy Fraction of rejected jets",100,0,1);

     h_chMultiplicityVsPt = fs->make<TProfile>("h_chMultiplicityVsPt","charged Hadron Multiplicity Vs Pt of rejected jets",100,0,200);
     h_nMultiplicityVsPt = fs->make<TProfile>("h_nMultiplicityVsPt","neutral Hadron Multiplicity Vs Pt of rejected jets",100,0,200);
     h_phMultiplicityVsPt = fs->make<TProfile>("h_phMultiplicityVsPt","photon Multiplicity Vs Pt of rejected jets",100,0,200);
     h_elMultiplicityVsPt = fs->make<TProfile>("h_elMultiplicityVsPt","electron Multiplicity Vs Pt of rejected jets",100,0,200);
     h_muMultiplicityVsPt = fs->make<TProfile>("h_muMultiplicityVsPt","muon Multiplicity Vs Pt of rejected jets",100,0,200);
     h_hfHMultiplicityVsPt = fs->make<TProfile>("h_hfHMultiplicityVsPt","hf Hadronic Multiplicity Vs Pt of rejected jets",100,0,200);
     h_hfEmMultiplicityVsPt = fs->make<TProfile>("h_hfEmMultiplicityVsPt","hf Electromagnetic Multiplicity Vs Pt of rejected jets",100,0,200);
     h_chMultFractionVsPt = fs->make<TProfile>("h_chMultFractionVsPt","charged Hadron Multiplicity Fraction Vs Pt of rejected jets",100,0,200);
     h_nMultFractionVsPt = fs->make<TProfile>("h_nMultFractionVsPt","neutral Hadron Multiplicity Fraction Vs Pt of rejected jets",100,0,200);
     h_phMultFractionVsPt = fs->make<TProfile>("h_phMultFractionVsPt","photon Multiplicity Fraction Vs Pt of rejected jets",100,0,200);
     h_elMultFractionVsPt = fs->make<TProfile>("h_elMultFractionVsPt","electron Multiplicity Fraction Vs Pt of rejected jets",100,0,200);
     h_muMultFractionVsPt = fs->make<TProfile>("h_muMultFractionVsPt","muon Multiplicity Fraction Vs Pt of rejected jets",100,0,200);
     h_hfHMultFractionVsPt = fs->make<TProfile>("h_hfHMultFractionVsPt","hf Hadronic Multiplicity Fraction Vs Pt of rejected jets",100,0,200);
     h_hfEmMultFractionVsPt = fs->make<TProfile>("h_hfEmMultFractionVsPt","hf Electromagnetic Multiplicity Fraction Vs Pt of rejected jets",100,0,200);
     h_chEnerFractionVsPt = fs->make<TProfile>("h_chEnerFractionVsPt","charged Hadron Energy Fraction Vs Pt of rejected jets",100,0,200);
     h_nEnerFractionVsPt = fs->make<TProfile>("h_nEnerFractionVsPt","neutral Hadron Energy Fraction Vs Pt of rejected jets",100,0,200);
     h_phEnerFractionVsPt = fs->make<TProfile>("h_phEnerFractionVsPt","photon Energy Fraction Vs Pt of rejected jets",100,0,200);
     h_elEnerFractionVsPt = fs->make<TProfile>("h_elEnerFractionVsPt","electron Energy Fraction Vs Pt of rejected jets",100,0,200);
     h_muEnerFractionVsPt = fs->make<TProfile>("h_muEnerFractionVsPt","muon Energy Fraction Vs Pt of rejected jets",100,0,200);
     h_hfHEnerFractionVsPt = fs->make<TProfile>("h_hfHEnerFractionVsPt","hf Hadronic Energy Fraction Vs Pt of rejected jets",100,0,200);
     h_hfEmEnerFractionVsPt = fs->make<TProfile>("h_hfEmEnerFractionVsPt","hf Electromagnetic Energy Fraction Vs Pt of rejected jets",100,0,200);

     h_chMultiplicityVsEta = fs->make<TProfile>("h_chMultiplicityVsEta","charged Hadron Multiplicity Vs Eta of rejected jets",100,-2.5,2.5);
     h_nMultiplicityVsEta = fs->make<TProfile>("h_nMultiplicityVsEta","neutral Hadron Multiplicity Vs Eta of rejected jets",100,-2.5,2.5);
     h_phMultiplicityVsEta = fs->make<TProfile>("h_phMultiplicityVsEta","photon Multiplicity Vs Eta of rejected jets",100,-2.5,2.5);
     h_elMultiplicityVsEta = fs->make<TProfile>("h_elMultiplicityVsEta","electron Multiplicity Vs Eta of rejected jets",100,-2.5,2.5);
     h_muMultiplicityVsEta = fs->make<TProfile>("h_muMultiplicityVsEta","muon Multiplicity Vs Eta of rejected jets",100,-2.5,2.5);
     h_hfHMultiplicityVsEta = fs->make<TProfile>("h_hfHMultiplicityVsEta","hf Hadronic Multiplicity Vs Eta of rejected jets",100,-2.5,2.5);
     h_hfEmMultiplicityVsEta = fs->make<TProfile>("h_hfEmMultiplicityVsEta","hf Electromagnetic Multiplicity Vs Eta of rejected jets",100,-2.5,2.5);
     h_chMultFractionVsEta = fs->make<TProfile>("h_chMultFractionVsEta","charged Hadron Multiplicity Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_nMultFractionVsEta = fs->make<TProfile>("h_nMultFractionVsEta","neutral Hadron Multiplicity Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_phMultFractionVsEta = fs->make<TProfile>("h_phMultFractionVsEta","photon Multiplicity Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_elMultFractionVsEta = fs->make<TProfile>("h_elMultFractionVsEta","electron Multiplicity Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_muMultFractionVsEta = fs->make<TProfile>("h_muMultFractionVsEta","muon Multiplicity Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_hfHMultFractionVsEta = fs->make<TProfile>("h_hfHMultFractionVsEta","hf Hadronic Multiplicity Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_hfEmMultFractionVsEta = fs->make<TProfile>("h_hfEmMultFractionVsEta","hf Electromagnetic Multiplicity Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_chEnerFractionVsEta = fs->make<TProfile>("h_chEnerFractionVsEta","charged Hadron Energy Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_nEnerFractionVsEta = fs->make<TProfile>("h_nEnerFractionVsEta","neutral Hadron Energy Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_phEnerFractionVsEta = fs->make<TProfile>("h_phEnerFractionVsEta","photon Energy Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_elEnerFractionVsEta = fs->make<TProfile>("h_elEnerFractionVsEta","electron Energy Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_muEnerFractionVsEta = fs->make<TProfile>("h_muEnerFractionVsEta","muon Energy Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_hfHEnerFractionVsEta = fs->make<TProfile>("h_hfHEnerFractionVsEta","hf Hadronic Energy Fraction Vs Eta of rejected jets",100,-2.5,2.5);
     h_hfEmEnerFractionVsEta = fs->make<TProfile>("h_hfEmEnerFractionVsEta","hf Electromagnetic Energy Fraction Vs Eta of rejected jets",100,-2.5,2.5);
  }

// histo of what there is around the electrons -------------------------------------
  h_pfIdPdgAroundE = fs->make<TH1F>("h_pfIdPdgAroundE","PF particles around the isolated electrons",10,0,10);

// histo about what there is around the electrons
 
  h_nVtx = fs->make<TH1F>("h_nVtx","h_nVtx",25,0,25);
  h_zYieldVsjets  = fs->make<TH1F>("h_zYieldVsjets","zYieldVsjets",10,0,10);
  h_zYieldVsjetsVtx1  = fs->make<TH1F>("h_zYieldVsjetsVtx1","zYieldVsjetsVtx1",10,0,10);
  h_zYieldVsjetsVtx5  = fs->make<TH1F>("h_zYieldVsjetsVtx5","zYieldVsjetsVtx5",10,0,10);
  h_jetPtNjet1 = fs->make<TH1F>("h_jetPtNjet1","jetPtNjet1",divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetPtNjet2 = fs->make<TH1F>("h_jetPtNjet2","jetPtNjet2",divPlot_subleading,minPtPlot_subleading,maxPtPlot_subleading);
  h_jetPtNjet3 = fs->make<TH1F>("h_jetPtNjet3","jetPtNjet3",divPlot_subsubleading,minPtPlot_subsubleading,maxPtPlot_subsubleading);
  h_jetPtNjet4 = fs->make<TH1F>("h_jetPtNjet4","jetPtNjet4",divPlot_subsubsubleading,minPtPlot_subsubsubleading,maxPtPlot_subsubsubleading);
  h_jetPtNjet1Incl = fs->make<TH1F>("h_jetPtNjet1Incl","jetPtNjet1Incl",divPlot_leading,minPtPlot_leading,maxPtPlot_leading);
  h_jetPtNjet2Incl = fs->make<TH1F>("h_jetPtNjet2Incl","jetPtNjet2Incl",divPlot_subleading,minPtPlot_subleading,maxPtPlot_subleading);
  h_jetPtNjet3Incl = fs->make<TH1F>("h_jetPtNjet3Incl","jetPtNjet3Incl",divPlot_subsubleading,minPtPlot_subsubleading,maxPtPlot_subsubleading);
  h_jetPtNjet4Incl = fs->make<TH1F>("h_jetPtNjet4Incl","jetPtNjet4Incl",divPlot_subsubsubleading,minPtPlot_subsubsubleading,maxPtPlot_subsubsubleading);

  h_jetEtaNjet1 = fs->make<TH1F>("h_jetEtaNjet1","jetEtaNjet1",divPlot_leadingeta,minEtaPlot_leading,maxEtaPlot_leading);
  h_jetEtaNjet2 = fs->make<TH1F>("h_jetEtaNjet2","jetEtaNjet2",divPlot_subleadingeta,minEtaPlot_subleading,maxEtaPlot_subleading);
  h_jetEtaNjet3 = fs->make<TH1F>("h_jetEtaNjet3","jetEtaNjet3",divPlot_subsubleadingeta,minEtaPlot_subsubleading,maxEtaPlot_subsubleading);
  h_jetEtaNjet4 = fs->make<TH1F>("h_jetEtaNjet4","jetEtaNjet4",divPlot_subsubsubleadingeta,minEtaPlot_subsubsubleading,maxEtaPlot_subsubsubleading);
  h_jetEtaNjet1Incl = fs->make<TH1F>("h_jetEtaNjet1Incl","jetEtaNjet1Incl",divPlot_leadingeta,minEtaPlot_leading,maxEtaPlot_leading);
  h_jetEtaNjet2Incl = fs->make<TH1F>("h_jetEtaNjet2Incl","jetEtaNjet2Incl",divPlot_subleadingeta,minEtaPlot_subleading,maxEtaPlot_subleading);
  h_jetEtaNjet3Incl = fs->make<TH1F>("h_jetEtaNjet3Incl","jetEtaNjet3Incl",divPlot_subsubleadingeta,minEtaPlot_subsubleading,maxEtaPlot_subsubleading);
  h_jetEtaNjet4Incl = fs->make<TH1F>("h_jetEtaNjet4Incl","jetEtaNjet4Incl",divPlot_subsubsubleadingeta,minEtaPlot_subsubsubleading,maxEtaPlot_subsubsubleading);

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
  h_massMinusPdgGsf   = fs->make<TH1F>("h_massMinusPdgGsf","massMinusPdgGsf",100,-50,50);
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
     if (doPlotsJetComposition){
	h_idPdgJet = fs->make<TH1F>("h_idPdgJet","idPdgJet",100,0,100);
	h_idPdgAroundE = fs->make<TH1F>("h_idPdgAroundE","type of particles (pdg) around the isolated electrons",600,0,600);
     }
  }
}


jetValidation::~jetValidation()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

#endif
