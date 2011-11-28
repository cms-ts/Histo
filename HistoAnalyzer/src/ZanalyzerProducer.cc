#include "Histo/HistoAnalyzer/interface/ZanalyzerProducer.h"

using namespace std;
using namespace edm;
using namespace reco;


//
// member functions
//

// ------------ method called for each event  ------------
void
ZanalyzerProducer::produce(edm::Event & iEvent, edm::EventSetup const & iSetup)
{

   // get gfs Electron 
   auto_ptr< reco::GsfElectronCollection > 
      pOutput( new reco::GsfElectronCollection ); 

  if (debug) cout<<"------- NEW Event -----"<<endl;

  Handle < GsfElectronCollection > electronCollection;
  iEvent.getByLabel (theElectronCollectionLabel, electronCollection);
  
 
  bool isBarrelElectrons;
  bool isEndcapElectrons;
  bool isIsolatedBarrel;
  bool isIDBarrel;
  bool isConvertedBarrel;
  bool isIsolatedEndcap;
  bool isIDEndcap;
  bool isConvertedEndcap;
  int elIsAccepted=0;
  int elIsAcceptedEB=0;
  int elIsAcceptedEE=0;

  for (reco::GsfElectronCollection::const_iterator recoElectron = electronCollection->begin (); recoElectron != electronCollection->end (); recoElectron++) {

    if (recoElectron->et () <= 25)  continue;
 
    // Define Isolation variables
    double IsoTrk = (recoElectron->dr03TkSumPt () / recoElectron->et ());
    double IsoEcal = (recoElectron->dr03EcalRecHitSumEt () / recoElectron->et ());
    double IsoHcal = (recoElectron->dr03HcalTowerSumEt () / recoElectron->et ());
    double HE = recoElectron->hadronicOverEm();

    //Define ID variables

    float DeltaPhiTkClu = recoElectron->deltaPhiSuperClusterTrackAtVtx ();
    float DeltaEtaTkClu = recoElectron->deltaEtaSuperClusterTrackAtVtx ();
    float sigmaIeIe = recoElectron->sigmaIetaIeta ();

    //Define Conversion Rejection Variables

    float Dcot = recoElectron->convDcot ();
    float Dist = recoElectron->convDist ();
    int NumberOfExpectedInnerHits = recoElectron->gsfTrack ()->trackerExpectedHitsInner ().numberOfHits ();

    //quality flags

    isBarrelElectrons = false;
    isEndcapElectrons = false;
    isIsolatedBarrel = false;
    isIDBarrel = false;
    isConvertedBarrel = false;
    isIsolatedEndcap = false;
    isIDEndcap = false;
    isConvertedEndcap = false;
 
    /***** Barrel WP80 Cuts *****/

    if (fabs (recoElectron->eta ()) <= 1.4442) {

      /* Isolation */
      if (IsoTrk < 0.09 && IsoEcal < 0.07 && IsoHcal < 0.10) {
	isIsolatedBarrel = true;
      }

      /* Identification */
      if (fabs (DeltaEtaTkClu) < 0.004 && fabs (DeltaPhiTkClu) < 0.06
	  && sigmaIeIe < 0.01 && HE < 0.04) {
	isIDBarrel = true;
      }

      /* Conversion Rejection */
      if ((fabs (Dist) >= 0.02 || fabs (Dcot) >= 0.02)
	  && NumberOfExpectedInnerHits == 0) {
	isConvertedBarrel = true;
      }
    }

    if (isIsolatedBarrel && isIDBarrel && isConvertedBarrel) {
      elIsAccepted++;
      elIsAcceptedEB++;
      pOutput->push_back(*recoElectron);
    }

    /***** Endcap WP80 Cuts *****/

    if (fabs (recoElectron->eta ()) >= 1.5660
	&& fabs (recoElectron->eta ()) <= 2.5000) {

      /* Isolation */
      if (IsoTrk < 0.04 && IsoEcal < 0.05 && IsoHcal < 0.025) {
	isIsolatedEndcap = true;
      }

      /* Identification */
      if (fabs (DeltaEtaTkClu) < 0.007 && fabs (DeltaPhiTkClu) < 0.03
	  && sigmaIeIe < 0.03 && HE < 0.15) {
	isIDEndcap = true;
      }

      /* Conversion Rejection */
      if ((fabs (Dcot) > 0.02 || fabs (Dist) > 0.02)
	  && NumberOfExpectedInnerHits == 0) {
	isConvertedEndcap = true;
      }
    }

    if (isIsolatedEndcap && isIDEndcap && isConvertedEndcap) {
      elIsAccepted++;
      elIsAcceptedEE++;   
      pOutput->push_back(*recoElectron);
    }

  }
   
   iEvent.put( pOutput );
 
}


// ------------ method called once each job just before starting event loop  ------------
void
ZanalyzerProducer::beginJob (){

//beginJob

}


// ------------ method called once each job just after ending the event loop  ------------
void
ZanalyzerProducer::endJob ()
{

//endJob

}

DEFINE_FWK_MODULE (ZanalyzerProducer);
