// system include files
#include <memory>
#include <string.h>
#include <stddef.h>
//#include <map>


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

// root includes
#include "TH1.h"
#include "TTree.h"
#include "TFile.h"

#include <FWCore/MessageLogger/interface/MessageLogger.h>
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

using namespace edm;
using namespace reco;
using namespace std;

bool debug=false; //If true it will activate the cout verbosity

class TTree;

/////
// class declaration
/////

class HistoAnalyzer : public edm::EDAnalyzer {
   public:
      explicit HistoAnalyzer(const edm::ParameterSet&);
      ~HistoAnalyzer();
      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void beginRun(edm::Run const &, const edm::EventSetup&);
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;


      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------

      //Retrieved from the .py
      edm::InputTag electronCollection_;
      edm::InputTag triggerCollection_;
      edm::InputTag VertexCollectionTag_;
 
      bool useCombinedPrescales_; // switch between HLT only and L1*HLT prescales
      bool useAllTriggers_; // if no trigger names are provided, use all triggers to find event weight
      HLTConfigProvider hltConfig_;        // to get configuration for L1s/Pre
      std::vector<std::string> triggerNames_; // name of the algorithms selected by our analysis
      std::vector<unsigned int> triggerIndices_; // index of the algorithms selected by our analysis
      bool removePU_;
      bool doTheHLTAnalysis_;

      //Various
      TTree* treeVJ_;
      TH1F * histNum;
      unsigned int nEvents_;

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
      //EB
      std::vector<double> vIsoTrkEB;
      std::vector<double> vIsoEcalEB;
      std::vector<double> vIsoHcalEB;
      std::vector<double> vHEEB;
      std::vector<float> vDeltaPhiTkCluEB;
      std::vector<float> vDeltaEtaTkCluEB;
      std::vector<float> vsigmaIeIeEB;
      //EE
      std::vector<double> vIsoTrkEE;
      std::vector<double> vIsoEcalEE;
      std::vector<double> vIsoHcalEE;
      std::vector<double> vHEEE;
      std::vector<float> vDeltaPhiTkCluEE;
      std::vector<float> vDeltaEtaTkCluEE;
      std::vector<float> vsigmaIeIeEE;
      //Common
      std::vector<double> vfbrem;
      std::vector<double> vetaSC;
      std::vector<float> vDcot;
      std::vector<float> vDist;
      std::vector<int> vNumberOfExpectedInnerHits;

      //Run Properties
      int Run;
      int LS;
      int Event;

      //vertices
      int numberOfVertices;

      //SC study
      double etaSCPF;

      void clean_vectors(){
	numberOfVertices=0;
	vIsoTrkEB.clear();
	vIsoEcalEB.clear();
	vIsoHcalEB.clear();
	vHEEB.clear();
	vDeltaPhiTkCluEB.clear();
	vDeltaEtaTkCluEB.clear();
	vsigmaIeIeEB.clear();
	vIsoTrkEE.clear();
	vIsoEcalEE.clear();
	vIsoHcalEE.clear();
	vHEEE.clear();
	vDeltaPhiTkCluEE.clear();
	vDeltaEtaTkCluEE.clear();
	vsigmaIeIeEE.clear();
	vfbrem.clear();
	vetaSC.clear();
	vDcot.clear();
	vDist.clear();
	vNumberOfExpectedInnerHits.clear();
	//statento che uccido ogni giro anche il vettore stringa!
	path.clear();
	
      }

      //HLT and Prescale
      std::vector<pair<std::string,int> > HLTAndPrescale;

};

HistoAnalyzer::HistoAnalyzer(const edm::ParameterSet& conf):hltConfig_()

{


  electronCollection_ = conf.getParameter<edm::InputTag>("electronCollection");
  triggerCollection_  = conf.getParameter<edm::InputTag>("triggerCollection");
  useCombinedPrescales_ = conf.getParameter<bool>("UseCombinedPrescales");
  triggerNames_         = conf.getParameter< std::vector<std::string> > ("TriggerNames");
  useAllTriggers_       = (triggerNames_.size()==0);
  removePU_             = conf.getParameter<bool>("removePU");
  doTheHLTAnalysis_     = conf.getParameter<bool>("doTheHLTAnalysis");
  VertexCollectionTag_      = conf.getParameter<edm::InputTag>("VertexCollectionTag");

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

}


HistoAnalyzer::~HistoAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

