// -*- C++ -*-
//
// Package:    HistoAnalyzer
// Class:      HistoAnalyzer
// 
/**\class HistoAnalyzer HistoAnalyzer.cc Histo/HistoAnalyzer/src/HistoAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Davide Scaini,27 1-013,+41227678527,
//         Created:  Tue Jul 12 14:54:43 CEST 2011
// $Id$
//
//


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
#include "TH1.h"

//DS for gsf
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"

using namespace edm;
using namespace reco;
//SD

//
// class declaration
//

class HistoAnalyzer : public edm::EDAnalyzer {
   public:
      explicit HistoAnalyzer(const edm::ParameterSet&);
      ~HistoAnalyzer();

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
      edm::InputTag electronCollection_;


      TH1F * histNum;

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
      TH1C * h_NumberOfExpectedInnerHits;

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
HistoAnalyzer::HistoAnalyzer(const edm::ParameterSet& conf)
{

  electronCollection_=conf.getParameter<edm::InputTag>("electronCollection");

//FIXME controlla nome degli istogrammi
  //now do what ever initialization is needed
  edm::Service<TFileService> fs; 
  //fs->cd(); //PAY ATTENTION entering the working dir
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
  h_NumberOfExpectedInnerHits = fs->make<TH1C>("h_NumberOfExpectedInnerHits","make title :)",20,0.,0.1);


}


HistoAnalyzer::~HistoAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
HistoAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{


 //Define Isolation variables
 double IsoTrk;
 double IsoEcal;
 double IsoHcal;
 double HE;
 double fbrem;
 double etaSC;

 //Define ID variables
 float DeltaPhiTkClu;
 float DeltaEtaTkClu;
 float sigmaIeIe;

 //Define Conversion Rejection Variables
 float Dcot;
 float Dist;
 int NumberOfExpectedInnerHits;

 //EODefinitions


   using reco::GsfElectronCollection;
   Handle<GsfElectronCollection> gsfElectrons;
   iEvent.getByLabel(electronCollection_,gsfElectrons);

   for(GsfElectronCollection::const_iterator itElect = gsfElectrons->begin();
		   itElect != gsfElectrons->end();                      
		   ++itElect) {


	   //Assign Isolation variables
	   IsoTrk	= (itElect->dr03TkSumPt () / itElect->et ());
	   IsoEcal	= (itElect->dr03EcalRecHitSumEt () / itElect->et ());
	   IsoHcal 	= (itElect->dr03HcalTowerSumEt () / itElect->et ());
	   HE		= (itElect->hcalOverEcal ());
	   fbrem	= itElect->fbrem();
	   etaSC	= itElect->superCluster()->eta();

	   //Assign ID variables
	   DeltaPhiTkClu = itElect->deltaPhiSuperClusterTrackAtVtx ();
	   DeltaEtaTkClu = itElect->deltaEtaSuperClusterTrackAtVtx ();
	   sigmaIeIe     = itElect->sigmaIetaIeta ();

	   //Assign Conversion Rejection Variables
	   Dcot		= itElect->convDcot ();
	   Dist 	= itElect->convDist ();
	   NumberOfExpectedInnerHits = itElect->gsfTrack ()->trackerExpectedHitsInner ().numberOfHits ();

	   //Filling Histos
	   //EB
	   if (fabs (itElect->eta ()) <= 1.4442) {
		   h_IsoTrk_EB->Fill(IsoTrk);
		   h_IsoEcal_EB->Fill(IsoEcal);
		   h_IsoHcal_EB->Fill(IsoHcal);
		   h_HE_EB->Fill(HE);

		   h_DeltaPhiTkClu_EB->Fill(DeltaPhiTkClu);
		   h_DeltaEtaTkClu_EB->Fill(DeltaEtaTkClu);
		   h_sigmaIeIe_EB->Fill(sigmaIeIe);
	   }
	   //EE
	   if (fabs (itElect->eta()) >= 1.5660
	       && fabs (itElect->eta()) <= 2.5000) {
		   h_IsoTrk_EE->Fill(IsoTrk);
		   h_IsoEcal_EE->Fill(IsoEcal);
		   h_IsoHcal_EE->Fill(IsoHcal);
		   h_HE_EE->Fill(HE);

		   h_DeltaPhiTkClu_EE->Fill(DeltaPhiTkClu);
		   h_DeltaEtaTkClu_EE->Fill(DeltaEtaTkClu);
		   h_sigmaIeIe_EE->Fill(sigmaIeIe);
	   }


	   h_fbrem->Fill(fbrem);
	   h_etaSC->Fill(etaSC);

	   h_Dcot->Fill(Dcot);
	   h_Dist->Fill(Dist);
	   h_NumberOfExpectedInnerHits->Fill(NumberOfExpectedInnerHits);

   }


   //FIXME get axis per tutti, metto solo la Y perché la X è in unità UFO <_O_>
   histNum-> GetXaxis()-> SetTitle("N_{ele}");
   histNum-> GetYaxis()-> SetTitle("Events");
   histNum->Fill((*gsfElectrons).size());

   h_IsoTrk_EB->GetYaxis()-> SetTitle("Events");
   h_IsoEcal_EB->GetYaxis()-> SetTitle("Events");
   h_IsoHcal_EB->GetYaxis()-> SetTitle("Events");
   h_HE_EB->GetYaxis()-> SetTitle("Events");
   h_IsoTrk_EE->GetYaxis()-> SetTitle("Events");
   h_IsoEcal_EE->GetYaxis()-> SetTitle("Events");
   h_IsoHcal_EE->GetYaxis()-> SetTitle("Events");
   h_HE_EE->GetYaxis()-> SetTitle("Events");
   h_fbrem->GetYaxis()-> SetTitle("Events");
   h_etaSC->GetYaxis()-> SetTitle("Events");

   h_DeltaPhiTkClu_EB->GetYaxis()-> SetTitle("Events");
   h_DeltaEtaTkClu_EB->GetYaxis()-> SetTitle("Events");
   h_sigmaIeIe_EB->GetYaxis()-> SetTitle("Events");
   h_DeltaPhiTkClu_EE->GetYaxis()-> SetTitle("Events");
   h_DeltaEtaTkClu_EE->GetYaxis()-> SetTitle("Events");
   h_sigmaIeIe_EE->GetYaxis()-> SetTitle("Events");


   h_Dcot->GetYaxis()-> SetTitle("Events");
   h_Dist->GetYaxis()-> SetTitle("Events");
   h_NumberOfExpectedInnerHits->GetYaxis()-> SetTitle("Events");


#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
HistoAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HistoAnalyzer::endJob() 
{

//NON NECESSARY WITH "fs" :)
/*  // rec event
  histNum->Write();
  h_IsoTrk_EB->Write();
  h_IsoEcal_EB->Write();
  h_IsoHcal_EB->Write();
  h_HE_EB->Write();
  h_IsoTrk_EE->Write();
  h_IsoEcal_EE->Write();
  h_IsoHcal_EE->Write();
  h_HE_EE->Write();
  h_fbrem->Write();
  h_etaSC->Write();

  h_DeltaPhiTkClu_EB->Write();
  h_DeltaEtaTkClu_EB->Write();
  h_sigmaIeIe_EB->Write();
  h_DeltaPhiTkClu_EE->Write();
  h_DeltaEtaTkClu_EE->Write();
  h_sigmaIeIe_EE->Write();
 
  h_Dcot->Write();
  h_Dist->Write();
  h_NumberOfExpectedInnerHits->Write();
 // fs->Write();//PAY ATTENTION
*/
}

// ------------ method called when starting to processes a run  ------------
void 
HistoAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
HistoAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
HistoAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
HistoAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HistoAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

 //Specify that only 'tracks' is allowed
 //To use, remove the default given above and uncomment below
 //ParameterSetDescription desc;
 //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
 //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HistoAnalyzer);
