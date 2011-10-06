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
      edm::InputTag VertexCollection_;
      edm::InputTag jetCollection_;
      edm::InputTag goodEPairTag;
      std::string weightCollection_;
      bool usingMC;

      //EB
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
      TH1F * h_jetPtVtx1_EB;
      TH1F * h_jetPtVtx2_EB;
      TH1F * h_jetPtVtx3_EB;
      TH1F * h_jetPtVtx4_EB;
      TH1F * h_jetPtVtx5_EB;
      TH1F * h_gsfPfSCEta_EB;
      TH1F * h_gsfPfSCEn_EB;
      TH2F * h_gsfPfSCEnVsEn_EB;
      TH2F * h_gsfPfSCEtaVsEn_EB;
      TH1F * h_jetPtNjet1_EB;
      TH1F * h_jetPtNjet2_EB;
      TH1F * h_jetPtNjet3_EB;
      TH1F * h_jetPtNjet4_EB;
      //EE
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
      TH1F * h_jetPtVtx1_EE;
      TH1F * h_jetPtVtx2_EE;
      TH1F * h_jetPtVtx3_EE;
      TH1F * h_jetPtVtx4_EE;
      TH1F * h_jetPtVtx5_EE;
      TH1F * h_gsfPfSCEta_EE;
      TH1F * h_gsfPfSCEn_EE;
      TH2F * h_gsfPfSCEnVsEn_EE;
      TH2F * h_gsfPfSCEtaVsEn_EE;
      TH1F * h_jetPtNjet1_EE;
      TH1F * h_jetPtNjet2_EE;
      TH1F * h_jetPtNjet3_EE;
      TH1F * h_jetPtNjet4_EE;
      //common
      TH2F * h_gsfPfSCEtaVsEta;
      TProfile2D * h_gsfPfSCEnVsEtaPhi;
      TH1F * h_nVtx;
      TH1F * h_ptZ_jetIncl[11];
      TH1F * h_ptZ_jet[11];
      TH1F * h_meanPtZVsNjet;
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
      TH1F * h_zEtaNjet1;
      TH1F * h_zEtaNjet2;
      TH1F * h_zEtaNjet3;
      TH1F * h_zEtaNjet4;
      TH1F * h_zEtaNjet1Incl;
      TH1F * h_zEtaNjet2Incl;
      TH1F * h_zEtaNjet3Incl;
      TH1F * h_zEtaNjet4Incl;
      TH1F * h_invMass;
      TH1F * h_zMassNjet1;
      TH1F * h_zMassNjet2;
      TH1F * h_zMassNjet3;
      TH1F * h_zMassNjet4;
      


      double edgeEB;
      double edgeEE;
      double edgeTrk;
      //vertices
      int numberOfVertices;
      double deltaRCone;
      double pi_;
     
};

jetValidation::jetValidation(const edm::ParameterSet& conf)

{

  pi_ = acos(-1);
  tpMapName = conf.getParameter<std::string>("tpMapName");
  //  weightCollection_ = conf.getParameter<std::string>("EventWeight");
  //  weightCollection_ = conf.getParameter<edm::InputTag>("weightCollection");
  electronCollection_ = conf.getParameter<edm::InputTag>("electronCollection");
  jetCollection_      = conf.getParameter<edm::InputTag>("jetCollection");
  VertexCollection_   = conf.getParameter<edm::InputTag>("VertexCollection");
  goodEPairTag        = conf.getParameter<edm::InputTag>("goodEPair");
  usingMC             = conf.getUntrackedParameter<bool>("usingMC",false);

  //now do what ever initialization is needed
  edm::Service<TFileService> fs; 

  //EB
  h_jetPt_EB = fs->make<TH1F>("h_jetPt_EB","jetPt",500,0.,500);
  h_jetEta_EB = fs->make<TH1F>("h_jetEta_EB","jetEta",100,-2.5,2.5);
  h_jetNum_EB = fs->make<TH1F>("h_jetNum_EB","jetNum",100,0.,100);
  h_jetPtFirst_EB = fs->make<TH1F>("h_jetPtFirst_EB","jetPtFirst",500,0.,500);
  h_jetPtSecond_EB = fs->make<TH1F>("h_jetPtSecond_EB","jetPtSecond",500,0.,500);
  h_jetPtThird_EB = fs->make<TH1F>("h_jetPtThird_EB","jetPtThird",500,0.,500);
  h_jetPtFourth_EB = fs->make<TH1F>("h_jetPtFourth_EB","jetPtFourth",500,0.,500);
  h_jetPtFirstCk_EB = fs->make<TH1F>("h_jetPtFirstCk_EB","jetPtFirstCk",500,0.,500);
  h_jetPtSecondCk_EB = fs->make<TH1F>("h_jetPtSecondCk_EB","jetPtSecondCk",500,0.,500);
  h_jetPtThirdCk_EB = fs->make<TH1F>("h_jetPtThirdCk_EB","jetPtThirdCk",500,0.,500);
  h_jetPtFourthCk_EB = fs->make<TH1F>("h_jetPtFourthCk_EB","jetPtFourthCk",500,0.,500);
  h_jetPtVsEta_EB = fs->make<TH2F>("h_jetPtVsEta_EB","jetPtVsEta",100,-2.5,2.5,500,0.,500);
  h_jetPtVtx1_EB = fs->make<TH1F>("h_jetPtVtx1_EB","jetPtVtx1",500,0,500);
  h_jetPtVtx2_EB = fs->make<TH1F>("h_jetPtVtx2_EB","jetPtVtx2",500,0,500);
  h_jetPtVtx3_EB = fs->make<TH1F>("h_jetPtVtx3_EB","jetPtVtx3",500,0,500);
  h_jetPtVtx4_EB = fs->make<TH1F>("h_jetPtVtx4_EB","jetPtVtx4",500,0,500);
  h_jetPtVtx5_EB = fs->make<TH1F>("h_jetPtVtx5_EB","jetPtVtx5",500,0,500);
  h_gsfPfSCEta_EB = fs->make<TH1F>("h_gsfPfSCEta_EB","gsfPfSCEta",160,0.6,1.4);
  h_gsfPfSCEn_EB = fs->make<TH1F>("h_gsfPfSCEn_EB","gsfPfSCEn",160,0.6,1.4);
  h_gsfPfSCEnVsEn_EB = fs->make<TH2F>("h_gsfPfSCEnVsEn_EB","gsfPfSCEnVsEn",200,0,200,160,0.6,1.4);
  h_gsfPfSCEtaVsEn_EB = fs->make<TH2F>("h_gsfPfSCEtaVsEn_EB","gsfPfSCEtaVsEn",200,0,200,160,0.6,1.4);
  h_jetPtNjet1_EB = fs->make<TH1F>("h_jetPtNjet1_EB","jetPtNjet1",500,0.,500);
  h_jetPtNjet2_EB = fs->make<TH1F>("h_jetPtNjet2_EB","jetPtNjet2",500,0.,500);
  h_jetPtNjet3_EB = fs->make<TH1F>("h_jetPtNjet3_EB","jetPtNjet3",500,0.,500);
  h_jetPtNjet4_EB = fs->make<TH1F>("h_jetPtNjet4_EB","jetPtNjet4",500,0.,500);
  //EE
  h_jetPt_EE = fs->make<TH1F>("h_jetPt_EE","jetPt",500,0.,500);
  h_jetEta_EE = fs->make<TH1F>("h_jetEta_EE","jetEta",100,-2.5,2.5);
  h_jetNum_EE = fs->make<TH1F>("h_jetNum_EE","jetNum",100,0.,100);
  h_jetPtFirst_EE = fs->make<TH1F>("h_jetPtFirst_EE","jetPtFirst",500,0.,500);
  h_jetPtSecond_EE = fs->make<TH1F>("h_jetPtSecond_EE","jetPtSecond",500,0.,500);
  h_jetPtThird_EE = fs->make<TH1F>("h_jetPtThird_EE","jetPtThird",500,0.,500);
  h_jetPtFourth_EE = fs->make<TH1F>("h_jetPtFourth_EE","jetPtFourth",500,0.,500);
  h_jetPtFirstCk_EE = fs->make<TH1F>("h_jetPtFirstCk_EE","jetPtFirstCk",500,0.,500);
  h_jetPtSecondCk_EE = fs->make<TH1F>("h_jetPtSecondCk_EE","jetPtSecondCk",500,0.,500);
  h_jetPtThirdCk_EE = fs->make<TH1F>("h_jetPtThirdCk_EE","jetPtThirdCk",500,0.,500);
  h_jetPtFourthCk_EE = fs->make<TH1F>("h_jetPtFourthCk_EE","jetPtFourthCk",500,0.,500);
  h_jetPtVsEta_EE = fs->make<TH2F>("h_jetPtVsEta_EE","jetPtVsEta",100,-2.5,2.5,500,0.,500);
  h_jetPtVtx1_EE = fs->make<TH1F>("h_jetPtVtx1_EE","jetPtVtx1",500,0,500);
  h_jetPtVtx2_EE = fs->make<TH1F>("h_jetPtVtx2_EE","jetPtVtx2",500,0,500);
  h_jetPtVtx3_EE = fs->make<TH1F>("h_jetPtVtx3_EE","jetPtVtx3",500,0,500);
  h_jetPtVtx4_EE = fs->make<TH1F>("h_jetPtVtx4_EE","jetPtVtx4",500,0,500);
  h_jetPtVtx5_EE = fs->make<TH1F>("h_jetPtVtx5_EE","jetPtVtx5",500,0,500);
  h_gsfPfSCEta_EE = fs->make<TH1F>("h_gsfPfSCEta_EE","gsfPfSCEta",160,0.6,1.4);
  h_gsfPfSCEn_EE = fs->make<TH1F>("h_gsfPfSCEn_EE","gsfPfSCEn",160,0.6,1.4);
  h_gsfPfSCEnVsEn_EE = fs->make<TH2F>("h_gsfPfSCEnVsEn_EE","gsfPfSCEnVsEn",200,0,200,160,0.6,1.4);
  h_gsfPfSCEtaVsEn_EE = fs->make<TH2F>("h_gsfPfSCEtaVsEn_EE","gsfPfSCEtaVsEn",200,0,200,160,0.6,1.4);
  h_jetPtNjet1_EE = fs->make<TH1F>("h_jetPtNjet1_EE","jetPtNjet1",500,0.,500);
  h_jetPtNjet2_EE = fs->make<TH1F>("h_jetPtNjet2_EE","jetPtNjet2",500,0.,500);
  h_jetPtNjet3_EE = fs->make<TH1F>("h_jetPtNjet3_EE","jetPtNjet3",500,0.,500);
  h_jetPtNjet4_EE = fs->make<TH1F>("h_jetPtNjet4_EE","jetPtNjet4",500,0.,500);
  //common
  h_gsfPfSCEtaVsEta = fs->make<TH2F>("h_gsfPfSCEnVsEta","gsfPfSCEnVsEta",100,-2.5,2.5,160,0.6,1.4);
  h_gsfPfSCEnVsEtaPhi = fs->make<TProfile2D>("h_gsfPfSCEnVsEtaPhi","gsfPfSCEnVsEtaPhi",100,-2.5,2.5,100,-pi_,pi_);
  h_nVtx = fs->make<TH1F>("h_nVtx","h_nVtx",10,0,10);
  h_zYieldVsjets  = fs->make<TH1F>("h_zYieldVsjets","zYieldVsjets",10,0,10);
  h_zYieldVsjetsVtx1  = fs->make<TH1F>("h_zYieldVsjetsVtx1","zYieldVsjetsVtx1",10,0,10);
  h_zYieldVsjetsVtx5  = fs->make<TH1F>("h_zYieldVsjetsVtx5","zYieldVsjetsVtx5",10,0,10);
  h_jetPtNjet1 = fs->make<TH1F>("h_jetPtNjet1","jetPtNjet1",500,0.,500);
  h_jetPtNjet2 = fs->make<TH1F>("h_jetPtNjet2","jetPtNjet2",500,0.,500);
  h_jetPtNjet3 = fs->make<TH1F>("h_jetPtNjet3","jetPtNjet3",500,0.,500);
  h_jetPtNjet4 = fs->make<TH1F>("h_jetPtNjet4","jetPtNjet4",500,0.,500);
  h_jetPtNjet1Incl = fs->make<TH1F>("h_jetPtNjet1Incl","jetPtNjet1Incl",500,0.,500);
  h_jetPtNjet2Incl = fs->make<TH1F>("h_jetPtNjet2Incl","jetPtNjet2Incl",500,0.,500);
  h_jetPtNjet3Incl = fs->make<TH1F>("h_jetPtNjet3Incl","jetPtNjet3Incl",500,0.,500);
  h_jetPtNjet4Incl = fs->make<TH1F>("h_jetPtNjet4Incl","jetPtNjet4Incl",500,0.,500);
  h_zEta      = fs->make<TH1F>("h_zEta","zEta",100,-2.5,2.5);
  h_zRapidity = fs->make<TH1F>("h_zRapidity","zRapidity",100,-2.5,2.5);
  h_zEtaNjet1 = fs->make<TH1F>("h_zEtaNjet1","zEtaNjet1",100,-2.5,2.5);
  h_zEtaNjet2 = fs->make<TH1F>("h_zEtaNjet2","zEtaNjet2",100,-2.5,2.5);
  h_zEtaNjet3 = fs->make<TH1F>("h_zEtaNjet3","zEtaNjet3",100,-2.5,2.5);
  h_zEtaNjet4 = fs->make<TH1F>("h_zEtaNjet4","zEtaNjet4",100,-2.5,2.5);
  h_zEtaNjet1Incl = fs->make<TH1F>("h_zEtaNjet1Incl","zEtaNjet1Incl",100,-2.5,2.5);
  h_zEtaNjet2Incl = fs->make<TH1F>("h_zEtaNjet2Incl","zEtaNjet2Incl",100,-2.5,2.5);
  h_zEtaNjet3Incl = fs->make<TH1F>("h_zEtaNjet3Incl","zEtaNjet3Incl",100,-2.5,2.5);
  h_zEtaNjet4Incl = fs->make<TH1F>("h_zEtaNjet4Incl","zEtaNjet4Incl",100,-2.5,2.5);
  h_invMass    = fs->make<TH1F>("h_invMass","invMass",200,0,200);
  h_zMassNjet1 = fs->make<TH1F>("h_zMassNjet1","zMassNjet1",200,0,200);
  h_zMassNjet2 = fs->make<TH1F>("h_zMassNjet2","zMassNjet2",200,0,200);
  h_zMassNjet3 = fs->make<TH1F>("h_zMassNjet3","zMassNjet3",200,0,200);
  h_zMassNjet4 = fs->make<TH1F>("h_zMassNjet4","zMassNjet4",200,0,200);
  
  for (int i=0; i<11; i++){
    stringstream buffer_Bin;
	         buffer_Bin << i;
    string name;
           name ="h_ptZ_jet_";
           name += buffer_Bin.str();
    string label;
           label = "ptZ_jet_";
           label += buffer_Bin.str();
    h_ptZ_jet[i] = fs->make<TH1F>(name.c_str(),label.c_str(),500,0,500);
    name +="Incl";
    label +="Incl";
    h_ptZ_jetIncl[i] = fs->make<TH1F>(name.c_str(),label.c_str(),500,0,500);
  }
  h_meanPtZVsNjet = fs->make<TH1F>("h_meanPtZVsNjet","meanPtZVsNjet",11, 0, 11);
}


jetValidation::~jetValidation()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

#endif
