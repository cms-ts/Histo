#ifndef GENPAnalyzer_h_
#define GENPAnalyzer_h_


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


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
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;

  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

  // ----------member data ---------------------------

  edm::InputTag goodEPairTag;
  edm::InputTag genParticleCollection_;

  bool isMC;


  // --- histograms
  
  TH1F * h_Mee;

  TH1F * h_ID_iso;
  TH1F * h_ID_iso1;
  TH1F * h_ID_iso2;

  TH1F * h_pt_iso;
  TH1F * h_pt_iso1;
  TH1F * h_pt_iso2;
  TH1F * h_pt_iso_e;
  TH1F * h_pt_iso_mu;
  TH1F * h_pt_iso_ph;
  TH1F * h_pt_iso_pi;
  TH1F * h_pt_iso_K;
  TH1F * h_pt_iso_KL;
  TH1F * h_pt_iso_KS;
  TH1F * h_pt_iso_p;
  TH1F * h_pt_iso_n;  



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

  goodEPairTag           = iConfig.getParameter<edm::InputTag>("goodEPair");
  genParticleCollection_ = iConfig.getUntrackedParameter<edm::InputTag>("genParticleCollection",edm::InputTag("genParticles"));

  isMC = iConfig.getUntrackedParameter<bool>("usingMC",false);


  edm::Service<TFileService> fs; 

  // --- histograms
  
  h_Mee       = fs->make<TH1F>("h_Mee","M_{ee}",200,0.,200.);

  h_ID_iso    = fs->make<TH1F>("h_ID_iso",  "GENP particles in ele iso", 4800,-2400.,2400.);
  h_ID_iso1   = fs->make<TH1F>("h_ID_iso1", "GENP particles in ele1 iso",4800,-2400.,2400.);
  h_ID_iso2   = fs->make<TH1F>("h_ID_iso2", "GENP particles in ele2 iso",4800,-2400.,2400.);

  h_pt_iso    = fs->make<TH1F>("h_pt_iso",    "pt of GENP particles in ele iso",100,0.,10.);
  h_pt_iso1   = fs->make<TH1F>("h_pt_iso1",   "pt of GENP particles in ele1 iso",100,0.,10.);
  h_pt_iso2   = fs->make<TH1F>("h_pt_iso2",   "pt of GENP particles in ele2 iso",100,0.,10.);
  h_pt_iso_e  = fs->make<TH1F>("h_pt_iso_e",  "pt of GENP particles in ele iso (e)",100,0.,10.);    
  h_pt_iso_mu = fs->make<TH1F>("h_pt_iso_mu", "pt of GENP particles in ele iso (#mu)",100,0.,10.);
  h_pt_iso_ph = fs->make<TH1F>("h_pt_iso_ph", "pt of GENP particles in ele iso (#gamma)",100,0.,10.);
  h_pt_iso_pi = fs->make<TH1F>("h_pt_iso_pi", "pt of GENP particles in ele iso (#pi^{#pm})",100,0.,10.);
  h_pt_iso_K  = fs->make<TH1F>("h_pt_iso_K",  "pt of GENP particles in ele iso (K^{#pm})",100,0.,10.);
  h_pt_iso_KL = fs->make<TH1F>("h_pt_iso_KL", "pt of GENP particles in ele iso (K_{L})",100,0.,10.);
  h_pt_iso_KS = fs->make<TH1F>("h_pt_iso_KS", "pt of GENP particles in ele iso (K_{S})",100,0.,10.);
  h_pt_iso_p  = fs->make<TH1F>("h_pt_iso_p",  "pt of GENP particles in ele iso (p)",100,0.,10.);
  h_pt_iso_n  = fs->make<TH1F>("h_pt_iso_n",  "pt of GENP particles in ele iso (n)",100,0.,10.);

  
}


GENPAnalyzer::~GENPAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


#endif

