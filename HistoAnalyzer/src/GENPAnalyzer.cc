#include "Histo/HistoAnalyzer/interface/GENPAnalyzer.h"

using namespace std;
using namespace edm;
using namespace reco;

//
// member functions
//

// ------------ method called for each event  ------------
void 
GENPAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // Parameters used in the track isolation calculation:
  const double ptMinTrk      = 0.7;
  const double extRadiusTrk  = 0.3;
  const double intRadiusTrk  = 0.015;
  const double stripTrk      = 0.015;
  const double maxVtxDistTrk = 0.2;


  // Parameters used in the Ecal isolation calculation:
  map< int, double > etMinEcal;
       etMinEcal[1] = 0.;   // Barrel
       etMinEcal[2] = 0.1;  // EndCap
  map< int, double > eMinEcal;
       eMinEcal[1]  = 0.08; // Barrel
       eMinEcal[2]  = 0.;   // EndCap
  const double extRadiusEcal    = 0.3;
  const double intRadiusEcal    = 3.;
  const double etaSliceEcal     = 1.5;
  const bool   useNumCrystals   = true;
  const int    severityLevelCut = 4;


  // Parameters used in the track isolation calculation:
  const double etMinHcal      = 0.;
  const double extRadiusHcal  = 0.3;
  const double intRadiusHcal  = 0.15;


  // --- Retrieve data from the event record

  // Damiana's electrons:
  edm::Handle<reco::GsfElectronCollection> goodEPair;
  iEvent.getByLabel (goodEPairTag_, goodEPair);

  // Tracks:
  edm::Handle<reco::TrackCollection> tracks;
  iEvent.getByLabel (trackCollection_,tracks);

  // Ecal hits:
  edm::Handle<EcalRecHitCollection> ecalBarrelHits;
  iEvent.getByLabel (ecalBarrelHits_,ecalBarrelHits);
  edm::Handle<EcalRecHitCollection> ecalEndCapHits;
  iEvent.getByLabel (ecalEndCapHits_,ecalEndCapHits);

  // Merge the Barrel and EndCap hit collections:
  EcalRecHitCollection * ecalHits = new EcalRecHitCollection();
  for (EcalRecHitCollection::const_iterator iHit=ecalBarrelHits->begin(); iHit!=ecalBarrelHits->end(); ++iHit)
    ecalHits->push_back(*iHit);
  for (EcalRecHitCollection::const_iterator iHit=ecalEndCapHits->begin(); iHit!=ecalEndCapHits->end(); ++iHit)
    ecalHits->push_back(*iHit);
  
  // Hcal towers:
  edm::Handle<CaloTowerCollection> towers;
  iEvent.getByLabel(towerCollection_, towers);

  // Primary vertices:
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel(vertexCollection_, vertices);

  // GENP particles: 
  edm::Handle<reco::GenParticleCollection> genPart;
  iEvent.getByLabel (genParticleCollection_,genPart);


  std::vector<TLorentzVector> p_ele;
  std::map<reco::GsfElectronRef, reco::TrackRefVector > trk_iso; 
  std::map<reco::GsfElectronRef, vector<CaloHit>      > ecal_iso; 
  std::map<reco::GsfElectronRef, CaloTowerRefs        > hcal_iso; 

  std::vector<TLorentzVector> p_ele_GENP;
  std::map<reco::GsfElectronRef, reco::GenParticleRefVector> trk_iso_GENP;
  std::map<reco::GsfElectronRef, std::vector<std::pair<reco::GenParticleRef, reco::VertexRef> > > ecal_iso_GENP;
  std::map<reco::GsfElectronRef, std::vector<std::pair<reco::GenParticleRef, reco::VertexRef> > > hcal_iso_GENP;


  // Loop over the electron collection:
  for (reco::GsfElectronCollection::const_iterator ele=goodEPair->begin(); ele!=goodEPair->end(); ++ele) {

    reco::GsfElectronRef eleRef = reco::GsfElectronRef(goodEPair,std::distance(goodEPair->begin(), ele));
    
    // Save the electron four-momentum:
    p_ele.push_back( TLorentzVector(ele->px(), ele->py(), ele->pz(), ele->energy()) );


    // ---------------------------------------------------------------------------------------------------
    //  
    //   Track isolation: from RecoEgamma/EgammaIsolationAlgos/src/ElectronTkIsolation.cc
    //
    

    // Electron track momentum:
    TVector3 p_trk_e( ele->gsfTrack()->momentum().X(),
		      ele->gsfTrack()->momentum().Y(),
		      ele->gsfTrack()->momentum().Z() );


    // Get tracks in the electron isolation cone:
    double isoTrk=0.;
    double dR_trk=999.;
    double ptRel_trk=999.;
    for (reco::TrackCollection::const_iterator track=tracks->begin(); track!=tracks->end(); ++track){

      TVector3 p_trk( track->momentum().X(),
		      track->momentum().Y(),
		      track->momentum().Z() );

      if ( p_trk.Pt()<ptMinTrk ) continue;

      if ( fabs(track->vz()-ele->gsfTrack()->vz()) < maxVtxDistTrk  ) {

	double dr   = p_trk.DeltaR(p_trk_e);
	double deta = p_trk.Eta()-p_trk_e.Eta();

	if ( fabs(dr)<extRadiusTrk && fabs(dr)>=intRadiusTrk  && fabs(deta)>=stripTrk ) {

	  trk_iso[eleRef].push_back(reco::TrackRef(tracks,std::distance(tracks->begin(), track)));
	  isoTrk += p_trk.Pt();

	  // Find the closest GENP particle
	  if ( genPart.isValid() ) {

	    GenParticleRef genp = GENPMatcher( *track, *genPart, dR_trk, ptRel_trk );

	    if ( genp.isNonnull() )
	      trk_iso_GENP[eleRef].push_back(genp);
	    else
	      edm::LogError("GENPAnalyzer") << "Track-GENP particle matching failed." << endl;

	  }

	}
	
      }
      
    } // loop over tracks                 

    h_isoTrk->Fill(isoTrk);
    h_isoTrk_diff->Fill(isoTrk-ele->dr03TkSumPt());


    // ---------------------------------------------------------------------------------------------------
    //  
    //   Ecal isolation: from RecoEgamma/EgammaIsolationAlgos/src/EgammaRecHitIsolation.cc
    //


    // Get the electron SuperCluser position:
    GlobalPoint pclu( ele->superCluster()->position().X(),
		      ele->superCluster()->position().Y(),
		      ele->superCluster()->position().Z() );

    double etaSC = pclu.eta();
    double phiSC = pclu.phi();
    double R2    = intRadiusEcal*intRadiusEcal;

    // Get the Ecal hits in the electron isolation cone:
    double isoEcal=0.;    
    double dR_ecal=999.;
    double etRel_ecal=999.;    
    for( int idet=0; idet<2; idet++ ){

      // Select the cells around the electron SuperCluster:
      CaloSubdetectorGeometry::DetIdSet chosen = subdet_[idet]->getCells(pclu,extRadiusEcal);

      // Loop over the selected cells:
      EcalRecHitCollection::const_iterator ihit=ecalHits->end();
      for (CaloSubdetectorGeometry::DetIdSet::const_iterator icell=chosen.begin(); icell!=chosen.end();++icell ){

	// Find the selected cell among rechits
	ihit=ecalHits->find(*icell); 
	if( ihit!=ecalHits->end()){
	  const  GlobalPoint & position = caloGeom_.product()->getPosition(*icell);
	  double eta    = position.eta();
	  double phi    = position.phi();
	  double deta   = eta - etaSC;
	  double dphi   = reco::deltaPhi(phi,phiSC);
	  double dR2    = deta*deta + dphi*dphi;
	  double energy = ihit->energy();
	    
	  if( useNumCrystals ) {

	    // Barrel num crystals, crystal width = 0.0174
	    if( fabs(etaSC) < 1.479 ) {  
	      if ( fabs(deta) < 0.0174*etaSliceEcal  ) continue;  
	      if ( sqrt(dR2)  < 0.0174*intRadiusEcal ) continue; 
	    } 
	    // Endcap num crystals, crystal width = 0.00864*fabs(sinh(eta))
	    else {                     
	      if ( fabs(deta) < 0.00864*fabs(sinh(eta))*etaSliceEcal  ) continue;  
	      if ( sqrt(dR2)  < 0.00864*fabs(sinh(eta))*intRadiusEcal ) continue; 
	    }
	  } else {
	    // Jurassic strip cut
	    if ( fabs(deta) < etaSliceEcal ) continue; 
	    // Jurassic exclusion cone cut
	    if ( dR2 < R2 ) continue; 

	  }
	    

	  // Severity level check
	  if ( severityLevelCut!=-1 && (ihit->detid()).subdetId()==1 &&
	       sevLevel->severityLevel(EBDetId(ihit->detid()), *ecalBarrelHits) >= severityLevelCut ) 
	    continue;


	  // Check the channel status
	  if ( ihit->checkFlag(EcalRecHit::kTowerRecovered)          ||
	       ( !ihit->checkFlag(EcalRecHit::kGood)                 &&           
		 !ihit->checkFlag(EcalRecHit::kPoorReco)             &&            
		 !ihit->checkFlag(EcalRecHit::kOutOfTime)            &&           
		 !ihit->checkFlag(EcalRecHit::kFaultyHardware)       &&      
		 !ihit->checkFlag(EcalRecHit::kNoisy)                &&               
		 !ihit->checkFlag(EcalRecHit::kPoorCalib)            &&           
		 !ihit->checkFlag(EcalRecHit::kSaturated)            &&           
		 !ihit->checkFlag(EcalRecHit::kLeadingEdgeRecovered) &&
		 !ihit->checkFlag(EcalRecHit::kNeighboursRecovered)  && 
		 !ihit->checkFlag(EcalRecHit::kTowerRecovered)       &&      
		 !ihit->checkFlag(EcalRecHit::kDead)                 &&                
		 !ihit->checkFlag(EcalRecHit::kKilled)               &&              
		 !ihit->checkFlag(EcalRecHit::kTPSaturated)          &&         
		 !ihit->checkFlag(EcalRecHit::kL1SpikeFlag)          &&         
		 !ihit->checkFlag(EcalRecHit::kWeird)                &&               
		 !ihit->checkFlag(EcalRecHit::kDiWeird)              &&             
		 !ihit->checkFlag(EcalRecHit::kUnknown) )            ) continue;


 	  double et = energy*position.perp()/position.mag();

	  if ( fabs(et)>etMinEcal[(ihit->detid()).subdetId()]    && 
	       fabs(energy)>eMinEcal[(ihit->detid()).subdetId()] ){
	    
	    CaloHit caloHit((ihit->detid()).subdetId(), 0, energy, eta, phi, ihit->time(), 0);

	    ecal_iso[eleRef].push_back(caloHit);
	    isoEcal += et;


	    // Find the closest GENP particle and the vertex it comes from
	    if ( genPart.isValid() ) {
	      std::pair<reco::GenParticleRef, reco::VertexRef> matching = GENPMatcher( caloHit, 
										       *genPart, 
										       *vertices,
										       dR_ecal, 
										       etRel_ecal );
	      if ( matching.first.isNonnull() ){
		ecal_iso_GENP[eleRef].push_back(matching);
	      }
	      else
		edm::LogError("GENPAnalyzer") << "Ecal hit-GENP particle matching failed." << endl;

	    }
	  }

 
	} // if( ihit!=ecalHits->end())

      } // Loop over rechits

    } // Loop over barrel/endcap


    h_isoEcal->Fill(isoEcal);
    h_isoEcal_diff->Fill(isoEcal-ele->dr03EcalRecHitSumEt());



    // ---------------------------------------------------------------------------------------------------
    //  
    //   Hcal isolation: from RecoEgamma/EgammaIsolationAlgos/src/EgammaTowerIsolation.cc
    //


    // Get the Hcal towers in the electron isolation cone:
    double isoHcal=0.;
    double dR_hcal=999.;
    double etRel_hcal=999.;    
    for(CaloTowerCollection::const_iterator tower=towers->begin(); tower!=towers->end(); ++tower){
     
      double et = tower->hadEt();

      if ( et<etMinHcal  ) continue ;  
     
      double towerEta = tower->eta();
      double towerPhi = tower->phi();
      double dphi     = reco::deltaPhi(towerPhi,phiSC);
      double deta     = towerEta - etaSC;
      double dR2      = deta*deta + dphi*dphi;

      if( dR2 < extRadiusHcal*extRadiusHcal && dR2 >= intRadiusHcal*intRadiusHcal ){

	hcal_iso[eleRef].push_back(CaloTowerRef(towers,std::distance(towers->begin(), tower)));
	isoHcal += et;
	
	// Find the closest GENP particle and the vertex it comes from
	if ( genPart.isValid() && tower->hadEnergy()>0. ) {
	  std::pair<reco::GenParticleRef, reco::VertexRef> matching = GENPMatcher( *tower, 
										   *genPart, 
										   *vertices,
										   dR_hcal, 
										   etRel_hcal );
	  
	  if ( matching.first.isNonnull() ){
	    hcal_iso_GENP[eleRef].push_back(matching);
	  }
	  else
	    edm::LogError("GENPAnalyzer") << "Hcal tower-GENP particle matching failed." << endl;

	}

     }
     
    } // loop over towers


    h_isoHcal->Fill(isoHcal);
    h_isoHcal_diff->Fill(isoHcal-ele->dr03HcalTowerSumEt());


  } // loop over electrons


  if ( goodEPair->size()==2 )
    h_Mee->Fill( (p_ele[0]+p_ele[1]).M() );



  // --- Clean-up the heap
  delete ecalHits; 

}


// ------------ method called once each job just before starting event loop  ------------
void 
GENPAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GENPAnalyzer::endJob() 
{

}  

// ------------ method called when starting to processes a run  ------------
void 
GENPAnalyzer::beginRun(edm::Run const&, edm::EventSetup const& iSetup)
{

  // Get the Ecal geometry:
  iSetup.get<CaloGeometryRecord>().get(caloGeom_);
  const CaloGeometry* caloGeom = caloGeom_.product();
  subdet_[0] = caloGeom->getSubdetectorGeometry(DetId::Ecal,EcalBarrel);
  subdet_[1] = caloGeom->getSubdetectorGeometry(DetId::Ecal,EcalEndcap);

  // Get the Ecal hit severity level:
  iSetup.get<EcalSeverityLevelAlgoRcd>().get(sevLevel_);
  sevLevel = sevLevel_.product();

}

// ------------ method called when ending the processing of a run  ------------
void 
GENPAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
GENPAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
GENPAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GENPAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// --------------------------------------------------------------------------------------------------
//  Electron matcher:
//
reco::GenParticleRef
GENPAnalyzer::GENPMatcher(reco::GsfElectron const& electron, reco::GenParticleCollection const & genpCollection,
			  double& deltaR, double& ptRel )
{

  reco::GenParticleRef matched_genp;

  TLorentzVector p_ele( electron.px(), electron.py(), electron.pz(), electron.energy() );

  deltaR = 999.;
  for( reco::GenParticleCollection::const_iterator genp=genpCollection.begin();
       genp!=genpCollection.end(); ++genp ){
    
    if ( fabs(genp->pdgId())!=11 || genp->status()!=1 || genp->charge()!=electron.charge() ) continue;

    TLorentzVector p_gen( genp->px(), genp->py(), genp->pz(), genp->energy() );

    double dR  = p_ele.DeltaR(p_gen);
    double dPt = fabs(p_ele.Pt()-p_gen.Pt())/p_ele.Pt();

    
    if ( dR<deltaR && dPt<0.5 ){
      deltaR       = dR;
      ptRel        = dPt;
      matched_genp = reco::GenParticleRef(&genpCollection, std::distance(genpCollection.begin(), genp));
    }

  } // loop over genp


  return matched_genp;
  
}

// --------------------------------------------------------------------------------------------------
//  Track matcher:
//
reco::GenParticleRef
GENPAnalyzer::GENPMatcher(reco::Track const& track, reco::GenParticleCollection const & genpCollection,
			  double& deltaR, double& ptRel )
{

  reco::GenParticleRef matched_genp;

  TVector3 p_trk( track.px(), track.py(), track.pz() );

  deltaR = 999.;
  for( reco::GenParticleCollection::const_iterator genp=genpCollection.begin();
       genp!=genpCollection.end(); ++genp ){
    
    if ( genp->status()!=1 || genp->charge()!=track.charge() ) continue;

    TVector3 p_gen( genp->px(), genp->py(), genp->pz() );

    double dR  = p_trk.DeltaR(p_gen);
    double dPt = fabs(p_trk.Pt()-p_gen.Pt())/p_trk.Pt();

    
    if ( dR<deltaR && dPt<0.5 ){
      deltaR       = dR;
      ptRel        = dPt;
      matched_genp = reco::GenParticleRef(&genpCollection, std::distance(genpCollection.begin(), genp));
    }

  } // loop over genp


  return matched_genp;
  
}

// --------------------------------------------------------------------------------------------------
//  Ecal hit matcher:
//
std::pair<reco::GenParticleRef, reco::VertexRef>
GENPAnalyzer::GENPMatcher(CaloHit const& hit, reco::GenParticleCollection const & genpCollection,
			  reco::VertexCollection const& vtxCollection, double& deltaR, double& etRel)
{

  std::pair<reco::GenParticleRef, reco::VertexRef> matched_genp;
  
  TVector3 hit_dir; 
  hit_dir.SetMagThetaPhi(1.,2.*atan(exp(-hit.eta())),hit.phi());

  deltaR = 999.;
  for (reco::VertexCollection::const_iterator ivtx=vtxCollection.begin(); 
       ivtx!=vtxCollection.end(); ++ivtx ) {
    
    // Build the hit four-momentum
    double vtxMag = sqrt( ivtx->x()*ivtx->x() + ivtx->y()*ivtx->y() + ivtx->z()*ivtx->z() );
    TVector3 vtx_pos(ivtx->x()/vtxMag, ivtx->y()/vtxMag, ivtx->z()/vtxMag);

    TLorentzVector p_hit( hit.e()*(hit_dir-vtx_pos).X(),
			  hit.e()*(hit_dir-vtx_pos).Y(),
			  hit.e()*(hit_dir-vtx_pos).Z(),
			  hit.e() );

//TMP    cout << " vtx = " <<  std::distance(vtxCollection.begin(), ivtx) << " ======================= " <<endl;
//TMP    cout << " Z = " << ivtx->z() << endl;
//TMP    cout << " pt_hit = " <<  p_hit.X() << " "
//TMP	 <<  p_hit.Y() << " "
//TMP	 <<  p_hit.Z() << " "
//TMP	 <<  p_hit.T() << endl;
    
    for( reco::GenParticleCollection::const_iterator genp=genpCollection.begin();
	 genp!=genpCollection.end(); ++genp ){
    
      if ( genp->status()!=1 ) continue;

      TLorentzVector p_gen( genp->px(), genp->py(), genp->pz(), genp->energy() );

      double dR  = p_hit.DeltaR(p_gen);
      double dEt = fabs(p_hit.Et()-p_gen.Et())/p_hit.Et();

      // crystal dimension 0.0174x0.0.174
      if ( dR<deltaR ){
	deltaR       = dR;
	etRel        = dEt;
	matched_genp = make_pair( reco::GenParticleRef(&genpCollection, std::distance(genpCollection.begin(), genp)),
				  reco::VertexRef(&vtxCollection, std::distance(vtxCollection.begin(), ivtx)) );
      }

    } // loop over genp


  } // loop over vertices


//TMP  cout << " Matched GENP -> " 
//TMP       << matched_genp.first->px() << " " <<  matched_genp.first->py() << " " 
//TMP       <<  matched_genp.first->pz() << " " <<  matched_genp.first->energy() << endl;
//TMP  cout << "                 " << matched_genp.second->z() << endl;
//TMP  cout << deltaR << " " << etRel << endl; 


  return matched_genp;
  
}

// --------------------------------------------------------------------------------------------------
//  Hcal tower matcher:
//
std::pair<reco::GenParticleRef, reco::VertexRef>
GENPAnalyzer::GENPMatcher(CaloTower const& tower, reco::GenParticleCollection const & genpCollection,
			  reco::VertexCollection const& vtxCollection, double& deltaR, double& etRel)
{

  std::pair<reco::GenParticleRef, reco::VertexRef> matched_genp;
  
  deltaR = 999.;
  for (reco::VertexCollection::const_iterator ivtx=vtxCollection.begin(); 
       ivtx!=vtxCollection.end(); ++ivtx ) {
    

    TLorentzVector p_tow( tower.p4(ivtx->position()).X(),
			  tower.p4(ivtx->position()).Y(),
			  tower.p4(ivtx->position()).Z(),
			  tower.p4(ivtx->position()).T() );

//TMP    cout << " vtx = " <<  std::distance(vtxCollection.begin(), ivtx) << " ======================= " <<endl;
//TMP    cout << " Z = " << ivtx->z() << endl;
//TMP    cout << " pt_tow = " <<  tower.p4(ivtx->position()).X() << " "
//TMP	 <<  tower.p4(ivtx->position()).Y() << " "
//TMP	 <<  tower.p4(ivtx->position()).Z() << " "
//TMP	 <<  tower.p4(ivtx->position()).T() << endl;

    for( reco::GenParticleCollection::const_iterator genp=genpCollection.begin();
	 genp!=genpCollection.end(); ++genp ){
    
      if ( genp->status()!=1 ) continue;

      TLorentzVector p_gen( genp->px(), genp->py(), genp->pz(), genp->energy() );

      double dR  = p_tow.DeltaR(p_gen);
      double dEt = fabs(p_tow.Et()-p_gen.Et())/p_tow.Et();

      // tower dimension 0.1745x0.1
      //if ( dR<deltaR && etRel<10. && dR<0.2 ){
      if ( dR<deltaR && etRel<10. && dR<0.2 ){
	deltaR       = dR;
	etRel        = dEt;
	matched_genp = make_pair( reco::GenParticleRef(&genpCollection, std::distance(genpCollection.begin(), genp)),
				  reco::VertexRef(&vtxCollection, std::distance(vtxCollection.begin(), ivtx)) );
      }

    } // loop over genp


  } // loop over vertices


//TMP  cout << " Matched GENP -> " 
//TMP       << matched_genp.first->px() << " " <<  matched_genp.first->py() << " " 
//TMP       <<  matched_genp.first->pz() << " " <<  matched_genp.first->energy() << endl;
//TMP  cout << "                 " << matched_genp.second->z() << endl;
//TMP  cout << deltaR << " " << etRel << endl; 


  return matched_genp;
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(GENPAnalyzer);
