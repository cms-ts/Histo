#ifndef HistoAnalyzer_h
#define HistoAnalyzer_h

// system include files  
#include <memory>
#include <string.h>
#include <stddef.h>

//vedi se puoi gestire le stringhe con questa sstream
#include <sstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTfilters/interface/HLTHighLevel.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include <TMath.h>
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"


// root includes

#include "TH1.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"

#include <FWCore/MessageLogger/interface/MessageLogger.h>
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "DataFormats/Common/interface/MergeableCounter.h"

using namespace edm;
using namespace reco;
using namespace std;

bool debugH11=false; //If true it will activate the cout verbosity

bool cold=true; //It is used to process few lines only once per job...
class TTree;

/////
// class declaration
/////

typedef std::vector< edm::Handle< edm::ValueMap<reco::IsoDeposit> > > IsoDepositMaps;
typedef std::vector< edm::Handle< edm::ValueMap<double> > > IsoDepositVals;

class HistoAnalyzer : public edm::EDProducer {
   public:
      explicit HistoAnalyzer(const edm::ParameterSet&);
      ~HistoAnalyzer();
      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void beginRun(edm::Run&, const edm::EventSetup&);
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endRun(edm::Run&, const edm::EventSetup&);
      virtual void endJob() ;
      virtual void beginLuminosityBlock (edm::LuminosityBlock &, const edm::EventSetup &);
      virtual void endLuminosityBlock (edm::LuminosityBlock &, const edm::EventSetup &);

      static bool isGoodConversion(const reco::Conversion &conv, const math::XYZPoint &beamspot, float lxyMin=2.0, float probMin=1e-6, unsigned int nHitsBeforeVtxMax=1);   
      static bool matchesConversion(const pat::Electron &ele, const reco::Conversion &conv, bool allowCkfMatch=true);
      static bool hasMatchedConversion(const pat::Electron &ele, const edm::Handle<reco::ConversionCollection> &convCol, const math::XYZPoint &beamspot, bool allowCkfMatch=true, float lxyMin=2.0, float probMin=1e-6, unsigned int nHitsBeforeVtxMax=0);
      // ----------member data ---------------------------

      //Retrieved from the .py
      edm::InputTag electronCollection_;
      edm::InputTag particleCollection_;
      edm::InputTag triggerCollection_;
      edm::InputTag VertexCollectionTag_;
      edm::InputTag conversionsInputTag_;
      edm::InputTag beamSpotInputTag_;
      edm::InputTag primaryVertexInputTag_;
      std::vector<edm::InputTag>  isoValInputTags_;
      std::vector<std::string>  numEventsNames_;
      std::string WhichRun_;
      std::string rootuplaname;
 
      bool useCombinedPrescales_; // switch between HLT only and L1*HLT prescales
      bool useAllTriggers_; // if no trigger names are provided, use all triggers to find event weight
      HLTConfigProvider hltConfig_;        // to get configuration for L1s/Pre
      std::vector<std::string> triggerNames_; // name of the algorithms selected by our analysis
      std::vector<unsigned int> triggerIndices_; // index of the algorithms selected by our analysis
      bool removePU_;
      bool usingMC_;
      bool doTheHLTAnalysis_;
      TimeValue_t  Timestamp;
      bool giveEventWeightEqualToOne_;
      bool applyMCWeightsSherpa_;

      //Event Counter
      int lumi;
      TH1F * nEventsPerStep_;

      //Various
      TTree* treeVJ_;
      TTree* treeHLT_;
      TH1F * histNum;
      unsigned int nEvents_;

      //MC
      double Weight;
      double WeightSherpa;

      int npv;
      //MC reweight
      edm::Lumi3DReWeighting LumiWeights_;
      edm::Lumi3DReWeighting LumiWeightsScaleUp_;
      edm::Lumi3DReWeighting LumiWeightsScaleDown_;

      float ScaleFactor; // you can change it to evaluate systematic effects

      //EB
      TH1D * h_IsoTrk_EB;
      TH1D * h_IsoEcal_EB;
      TH1D * h_IsoHcal_EB;
      TH1D * h_HE_EB;
      TH1F * h_DeltaPhiTkClu_EB;
      TH1F * h_DeltaEtaTkClu_EB;
      TH1F * h_sigmaIeIe_EB;
      //EE
      TH1D * h_IsoTrk_EE;
      TH1D * h_IsoEcal_EE;
      TH1D * h_IsoHcal_EE;
      TH1D * h_HE_EE;
      TH1F * h_DeltaPhiTkClu_EE;
      TH1F * h_DeltaEtaTkClu_EE;
      TH1F * h_sigmaIeIe_EE;
      //common
      TH1D * h_fbrem;
      TH1D * h_etaSC;
      TH1F * h_Dcot;
      TH1F * h_Dist;
      TH1I * h_NumberOfExpectedInnerHits;
      TH1I * h_HLTbits;

      //Strings
      std::vector<string> path;

      std::vector<double> vRho;
      //EB
      std::vector<double> vIsoTrkEB;
      std::vector<double> vIsoEcalEB;
      std::vector<double> vIsoHcalEB;
      std::vector<double> vHEEB;
      std::vector<float> vDeltaPhiTkCluEB;
      std::vector<float> vDeltaEtaTkCluEB;
      std::vector<float> vsigmaIeIeEB;
      std::vector<float> vooemoopEB;
      
      //EE
      std::vector<double> vIsoTrkEE;
      std::vector<double> vIsoEcalEE;
      std::vector<double> vIsoHcalEE;
      std::vector<double> vHEEE;
      std::vector<float> vDeltaPhiTkCluEE;
      std::vector<float> vDeltaEtaTkCluEE;
      std::vector<float> vsigmaIeIeEE;
      std::vector<float> vooemoopEE;
      //Common
      std::vector<double> vfbrem;
      std::vector<double> vetaSC;
      std::vector<float> vDcot;
      std::vector<float> vDist;
      std::vector<float> vd0vtx;
      std::vector<float> vdzvtx;
      std::vector<bool> vFitConversion;
      std::vector<int> vNumberOfExpectedInnerHits;
      double HE_bc;
      double HE_old;

      // particle based isolation
      // barrel
      std::vector<double> vNeutHadIsoEB;
      std::vector<double> vChgHadIsoEB;
      std::vector<double> vPhotIsoEB;
      std::vector<double> vPhotIsoUserEB;
      std::vector<double> vNeutHadIsoEB_ned;
      std::vector<double> vNeutHadIsoUserEB_ned;
      std::vector<double> vChgHadIsoEB_ned;
      std::vector<double> vChgHadIsoUserEB_ned;
      std::vector<double> vPhotIsoEB_ned;
      std::vector<double> vPhotIsoUserEB_ned;
      std::vector<double> vCombinedIsoEB;
      //edncaps
      std::vector<double> vNeutHadIsoEE;
      std::vector<double> vChgHadIsoEE;
      std::vector<double> vPhotIsoEE;
      std::vector<double> vPhotIsoUserEE;
      std::vector<double> vNeutHadIsoEE_ned;
      std::vector<double> vNeutHadIsoUserEE_ned;
      std::vector<double> vChgHadIsoEE_ned;
      std::vector<double> vChgHadIsoUserEE_ned;
      std::vector<double> vPhotIsoEE_ned;
      std::vector<double> vPhotIsoUserEE_ned;
      std::vector<double> vCombinedIsoEE;

      // PileUp REMOVED variables
      //EB
      std::vector<double> vIsoTrkEB_PUR;
      std::vector<double> vIsoEcalEB_PUR;
      std::vector<double> vIsoHcalEB_PUR;
      //EE
      std::vector<double> vIsoTrkEE_PUR;
      std::vector<double> vIsoEcalEE_PUR;
      std::vector<double> vIsoHcalEE_PUR;                                                                                
      std::vector<double> vNeutHadIsoEB_PUR;
      std::vector<double> vPhotIsoEB_PUR;                                                                               
      std::vector<double> vNeutHadIsoEE_PUR;
      std::vector<double> vPhotIsoEE_PUR;
      std::vector<double> vCombinedIsoEB_PUR;
      std::vector<double> vCombinedIsoEE_PUR;

      //Run Properties
      int Run;
      int LS;
      int Event;

      //vertices
      int numberOfVertices;

      //SC study
      double etaSCPF;

      //HLT and Prescale
      std::vector<std::string> HLTPaths;
      std::vector<int> HLTPrescales;
      std::vector<std::string> HLTNames;
      std::vector<double> HLTValue;
      std::vector<double> HLTRatio;
      std::vector<int> vRun;


      void clean_vectors(){
        Timestamp=0;
	Weight=0;
	numberOfVertices=0;
	vRho.clear();
	vIsoTrkEB.clear();
	vIsoEcalEB.clear();
	vIsoHcalEB.clear();
	vHEEB.clear();
	vDeltaPhiTkCluEB.clear();
	vDeltaEtaTkCluEB.clear();
	vsigmaIeIeEB.clear();
	vooemoopEB.clear();
	vIsoTrkEE.clear();
	vIsoEcalEE.clear();
	vIsoHcalEE.clear();
	vHEEE.clear();
	vDeltaPhiTkCluEE.clear();
	vDeltaEtaTkCluEE.clear();
	vsigmaIeIeEE.clear();
	vooemoopEE.clear();
	vfbrem.clear();
	vetaSC.clear();
	vDcot.clear();
	vDist.clear();
	vd0vtx.clear();
	vdzvtx.clear();
	vFitConversion.clear();
	vNumberOfExpectedInnerHits.clear();
	// particle-based isolation variables
	vNeutHadIsoEB.clear();
	vChgHadIsoEB.clear();
	vPhotIsoEB.clear();
	vPhotIsoUserEB.clear();
	vNeutHadIsoEE.clear();
	vChgHadIsoEE.clear();
	vPhotIsoEE.clear();
	vPhotIsoUserEE.clear();
	vNeutHadIsoEB_ned.clear();
	vNeutHadIsoUserEB_ned.clear();
	vChgHadIsoEB_ned.clear();
	vChgHadIsoUserEB_ned.clear();
	vPhotIsoEB_ned.clear();
	vPhotIsoUserEB_ned.clear();
	vNeutHadIsoEE_ned.clear();
	vNeutHadIsoUserEE_ned.clear();
	vChgHadIsoEE_ned.clear();
	vChgHadIsoUserEE_ned.clear();
	vPhotIsoEE_ned.clear();
	vPhotIsoUserEE_ned.clear();
	vCombinedIsoEB.clear();
	vCombinedIsoEE.clear();
	//statento che uccido ogni giro anche il vettore stringa!
	path.clear();
	vIsoTrkEB_PUR.clear();
	vIsoEcalEB_PUR.clear();
	vIsoHcalEB_PUR.clear();
	vIsoTrkEE_PUR.clear();
	vIsoEcalEE_PUR.clear();
	vIsoHcalEE_PUR.clear();
	// particle-based isolatCion variables
	vNeutHadIsoEB_PUR.clear();
	vPhotIsoEB_PUR.clear();
	vNeutHadIsoEE_PUR.clear();
	vPhotIsoEE_PUR.clear();
	vCombinedIsoEE_PUR.clear();
	vCombinedIsoEB_PUR.clear();
      }
      

};

HistoAnalyzer::HistoAnalyzer(const edm::ParameterSet& conf):hltConfig_()

{
  produces<std::vector<float> >("EventWeight");
  produces<std::vector<float> >("EventWeightScaleUp");
  produces<std::vector<float> >("EventWeightScaleDown");
  produces<std::vector<float> >("EventWeightSherpa");

  electronCollection_ = conf.getParameter<edm::InputTag>("electronCollection");
  particleCollection_ = conf.getParameter<edm::InputTag>("particleCollection");
  triggerCollection_  = conf.getParameter<edm::InputTag>("triggerCollection");
  useCombinedPrescales_ = conf.getParameter<bool>("UseCombinedPrescales");
  triggerNames_         = conf.getParameter< std::vector<std::string> > ("TriggerNames");
  useAllTriggers_       = (triggerNames_.size()==0);
  removePU_             = conf.getParameter<bool>("removePU");
  usingMC_              = conf.getParameter<bool>("usingMC");
  doTheHLTAnalysis_     = conf.getParameter<bool>("doTheHLTAnalysis");
  VertexCollectionTag_  = conf.getParameter<edm::InputTag>("VertexCollectionTag");
  conversionsInputTag_  = conf.getParameter<edm::InputTag>("conversionsInputTag");
  beamSpotInputTag_     = conf.getParameter<edm::InputTag>("beamSpotInputTag");
  primaryVertexInputTag_= conf.getParameter<edm::InputTag>("primaryVertexInputTag");
  isoValInputTags_      = conf.getParameter<std::vector<edm::InputTag> >("isoValInputTags");
  numEventsNames_       = conf.getParameter< std::vector<std::string> > ("TotalNEventTag");
  WhichRun_             = conf.getParameter< std::string > ("WhichRun");
  giveEventWeightEqualToOne_ = conf.getParameter<bool>("giveEventWeightEqualToOne");
  rootuplaname          = conf.getParameter< std::string > ("RootuplaName");
  applyMCWeightsSherpa_ = conf.getUntrackedParameter<bool>("applyMCWeightsSherpa",false);

  //now do what ever initialization is needed
  edm::Service<TFileService> fs; 
  histNum = fs->make<TH1F>("h_histNum","# of electrons",10, 0.,10.);

  //EB
  h_IsoTrk_EB = fs->make<TH1D>("h_IsoTrk_EB","IsoTrk",20,0.,0.20);
  h_IsoEcal_EB = fs->make<TH1D>("h_IsoEcal_EB","IsoEcal",20,0.,0.20);
  h_IsoHcal_EB = fs->make<TH1D>("h_IsoHcal_EB","IsoHcal",20,0.,0.20);
  h_HE_EB = fs->make<TH1D>("h_HE_EB","H/E",20,0.,0.20);
  h_DeltaPhiTkClu_EB = fs->make<TH1F>("h_DeltaPhiTkClu_EB","DeltaPhiTkClu",20,0.,0.2);
  h_DeltaEtaTkClu_EB = fs->make<TH1F>("h_DeltaEtaTkClu_EB","DeltaEtaTkClu",20,0.,.05);
  h_sigmaIeIe_EB = fs->make<TH1F>("h_sigmaIeIe_EB","sigmaIeIe",20,0.,0.1);
  //EE
  h_IsoTrk_EE = fs->make<TH1D>("h_IsoTrk_EE","IsoTrk",20,0.,0.20);
  h_IsoEcal_EE = fs->make<TH1D>("h_IsoEcal_EE","IsoEcal",20,0.,0.20);
  h_IsoHcal_EE = fs->make<TH1D>("h_IsoHcal_EE","IsoHcal",20,0.,0.20);
  h_HE_EE = fs->make<TH1D>("h_HE_EE","H/E",20,0.,0.20);
  h_DeltaPhiTkClu_EE = fs->make<TH1F>("h_DeltaPhiTkClu_EE","DeltaPhiTkClu",20,0.,0.2);
  h_DeltaEtaTkClu_EE = fs->make<TH1F>("h_DeltaEtaTkClu_EE","DeltaEtaTkClu",20,0.,.05);
  h_sigmaIeIe_EE = fs->make<TH1F>("h_sigmaIeIe_EE","sigmaIeIe",20,0.,0.1);


  h_fbrem = fs->make<TH1D>("h_fbrem","fbrem",100,0.,1.0);
  h_etaSC = fs->make<TH1D>("h_etaSC","etaSC",54,-2.7,2.7);
  h_Dcot = fs->make<TH1F>("h_Dcot","Dcot",40,-0.2,0.2);
  h_Dist = fs->make<TH1F>("h_Dist","Dist",40,-0.2,0.2);
  h_NumberOfExpectedInnerHits = fs->make<TH1I>("h_NumberOfExpectedInnerHits","make title :)",20,0.,0.1);
  h_HLTbits = fs->make<TH1I>("h_HLTbits","fired",20,0.,0.1);

  const unsigned int nNames = numEventsNames_.size();
  nEventsPerStep_ = fs->make<TH1F>("numEventsPerStep", "", nNames, 0, nNames);
}


HistoAnalyzer::~HistoAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

#endif

