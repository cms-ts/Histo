// -*- C++ -*-
//

#include "Histo/HistoAnalyzer/interface/jetValidation.h"


//
// member functions
//

class GreaterPt{
public:
  bool operator()( const math::XYZTLorentzVector& a, const math::XYZTLorentzVector& b) {
    return a.Pt() > b.Pt();
  }
};

// ------------ method called for each event  ------------
void
jetValidation::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  ////////
  //  Get The Weights
  ///////

  edm::Handle< std::vector<float> > weight;
  iEvent.getByLabel("demo","EventWeight",weight);
  const std::vector<float> & myweight=*weight;

   //IMPORTANTE  
   numberOfVertices=0;
   
   //Define Variables 
   int nJetsEB=0;
   int nJetsEE=0;
   int totJets=0;
   int totJetsCk=0;
   //bool isEB;
   //bool isEE;

   ///////////////////////
   ///// Vertex Analysis
   ///////////////////////

   edm::Handle<reco::VertexCollection> Vertexes;
   iEvent.getByLabel(VertexCollection_, Vertexes);
   numberOfVertices = Vertexes->size();  
   h_nVtx->Fill(numberOfVertices,myweight[0]);
   ///////////////////////
   ///// Z Analysis
   ///////////////////////

   edm::Handle<reco::PFCandidateCollection> pfElec;
   iEvent.getByLabel (pflowEleCollection_, pfElec);
   int pfSize=0;

   edm::Handle<reco::GsfElectronCollection > goodEPair;
   iEvent.getByLabel (goodEPairTag, goodEPair);
   
   
   edm::Handle<reco::GenParticleCollection> genPart;
   if (usingMC){
      iEvent.getByLabel (genParticleCollection_,genPart);
   }

   if (goodEPair->size()==2)
   {   
      double gsfScEn;
      double gsfScEta;
      double pfScEn;
      double pfScEta;
      double deltaEta_ = 5.0/100.0;
      double deltaPhi_ = 2.0*pi_/100;
      int cluSize1 =0;
      int cluSize2 =0;
      double cluTotEnergy1=0.;
      double cluTotEnergy2=0.;
      double dist=0.;
      double distEta=0.;
      double ratioEn=0.;
      double ratioEn2=0.;
      double maxDist=0.05;
      double maxEta=0.2;
      double maxEn=1.2;
      double nearerDist=9999.;
      double enGen;

      bool checkCut=false;
      bool checkPairing=false;
      bool checkTruth=false;
      bool checkNear=false;

      reco::GsfElectronCollection::const_iterator it=goodEPair->begin();
      TLorentzVector e1, e2, e_pair;
      TLorentzVector pfe1, pfe2, pfe_pair;
      e1.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());

      // ================================
      //  GSFelectrons VS PFelectrons 1
      // ================================
      if (it->superCluster().isNonnull() && it->pflowSuperCluster().isNonnull()){
	 gsfScEn = it->superCluster()->energy();
	 gsfScEta= it->superCluster()->eta();
	 pfScEn  = it->pflowSuperCluster()->energy();
	 pfScEta= it->pflowSuperCluster()->eta();

	 h_gsfPfSCEtaVsEta->Fill(it->eta(),gsfScEta/pfScEta,myweight[0]);
	 for (int j=0; j< 100; j++){
	    if ( it->eta()> j*deltaEta_ && it->eta()<(j+1)*deltaEta_){
	       for (int k=0; k<100; k++){
		  if ( it->phi()> k*deltaPhi_ && it->phi()<(k+1)*deltaPhi_){
		     h_gsfPfSCEnVsEtaPhi->Fill((j+0.5)*deltaEta_,(k+0.5)*deltaPhi_,gsfScEn/pfScEn,myweight[0]);
		  }
	       }
	    }
	 }
	 if (fabs(gsfScEta)<edgeEB){
	    h_gsfPfSCEta_EB->Fill(gsfScEta/pfScEta,myweight[0]);
	    h_gsfPfSCEn_EB->Fill(gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEnVsEn_EB->Fill(it->energy(),gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEtaVsEn_EB->Fill(it->energy(),gsfScEta/pfScEta,myweight[0]);
	 } else if (fabs(gsfScEta)<edgeEE){
	    h_gsfPfSCEta_EE->Fill(gsfScEta/pfScEta,myweight[0]);
	    h_gsfPfSCEn_EE->Fill(gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEnVsEn_EE->Fill(it->energy(),gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEtaVsEn_EE->Fill(it->energy(),gsfScEta/pfScEta,myweight[0]);


	    reco::CaloCluster_iterator itClu = it->superCluster()->clustersBegin();
	    reco::CaloCluster_iterator itClu_end = it->superCluster()->clustersEnd();
	    for (;itClu!=itClu_end; itClu++){
	       cluSize1++;
	       cluTotEnergy1 += (*itClu)->energy();
	    }
	    h_superClusterSize->Fill(cluSize1,myweight[0]);
	    if (cluSize1==1){ h_gsfPfSCEnClu1->Fill(gsfScEn/pfScEn,myweight[0]);}
	 }     
      }   
      
      for(reco::PFCandidateCollection::const_iterator itPf=pfElec->begin();itPf!=pfElec->end();itPf++){
	 if (itPf->gsfTrackRef()==it->gsfTrack()) {
	    pfSize++;
	    h_ptPFptVsEta->Fill(it->eta(),it->energy()/itPf->energy(),myweight[0]);
	    h_ptPFptVsEn->Fill(it->energy(),it->energy()/itPf->energy(),myweight[0]);
	    pfe1.SetPtEtaPhiM(itPf->pt(),itPf->eta(),itPf->phi(),itPf->mass());
	    
	    if (usingMC){
	       for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
		  dist= sqrt( pow(itgen->eta()-it->eta(),2)+pow(itgen->phi()-it->phi(),2) );
		  distEta = fabs(itgen->eta() - it->eta());
		  ratioEn = itgen->energy()/it->energy();
		  ratioEn2 = itgen->energy()/itPf->energy();
		  if (dist < maxDist && distEta < maxEta ){	     
		     if (!checkCut){
			h_MCenPFenVsEnWoEnCut->Fill(itPf->energy(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenPFenVsEtaWoEnCut->Fill(itPf->eta(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenGSFenVsEnWoEnCut->Fill(it->energy(),itgen->energy()/it->energy(), myweight[0]);  
			h_MCenGSFenVsEtaWoEnCut->Fill(it->eta(),itgen->energy()/it->energy(), myweight[0]);
			checkCut = true;
		     }
		     if (!checkPairing && ratioEn < maxEn && 1./ratioEn < maxEn && 
			 ratioEn2 < maxEn && 1./ratioEn2 < maxEn ){
			h_MCenPFenVsEn->Fill(itPf->energy(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenPFenVsEta->Fill(itPf->eta(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenGSFenVsEn->Fill(it->energy(),itgen->energy()/it->energy(), myweight[0]);  
			h_MCenGSFenVsEta->Fill(it->eta(),itgen->energy()/it->energy(), myweight[0]); 
			checkPairing=true;
		     }
		  }
		  if (fabs(itgen->pdgId())==11 && itgen->mother()->pdgId()==23){ //itgen->status()==1 && 
		     if (dist < 0.1 && !checkTruth){		     
			h_MCenPFenVsEnTruth->Fill(itPf->energy(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenPFenVsEtaTruth->Fill(itPf->eta(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenGSFenVsEnTruth->Fill(it->energy(),itgen->energy()/it->energy(), myweight[0]);  
			h_MCenGSFenVsEtaTruth->Fill(it->eta(),itgen->energy()/it->energy(), myweight[0]);
			checkTruth=true;
		     }
		  }

		  if ( fabs(itgen->pdgId())==11 && dist < maxDist && dist < nearerDist){
		     nearerDist = dist;
		     enGen=itgen->energy();
		     checkNear=true;
		  }

	       } // end genParticle cycle
	       
	       if (!checkPairing){  // check what fail for the association to gen level
		  if (dist > maxDist) h_failReason->Fill(1);
		  if (distEta > maxEta) h_failReason->Fill(2);
		  if (ratioEn > maxEn || 1./ratioEn > maxEn) h_failReason->Fill(3);
		  if (ratioEn2 > maxEn || 1./ratioEn2 > maxEn) h_failReason->Fill(4);
	       }
	       
	       if (checkNear){
		  h_MCenPFenVsEnENear->Fill(itPf->energy(),enGen/itPf->energy(), myweight[0]);
		  h_MCenPFenVsEtaENear->Fill(itPf->eta(),enGen/itPf->energy(), myweight[0]);
		  h_MCenGSFenVsEnENear->Fill(it->energy(),enGen/it->energy(), myweight[0]);  
		  h_MCenGSFenVsEtaENear->Fill(it->eta(),enGen/it->energy(), myweight[0]);
	       }

	    } // end UsingMC	    
	 }  // end association gsf-pf
      } // end PFelectron cycle
      // ================================
      it++;
      e2.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());
      e_pair = e1 + e2;
      checkPairing=false;
      checkCut=false;
      checkTruth=false;
      checkNear=false;
      nearerDist=9999.;
      // ================================
      //  GSFelectrons VS PFelectrons 2
      // ================================
      if (it->superCluster().isNonnull() && it->pflowSuperCluster().isNonnull()){
	 gsfScEn = it->superCluster()->energy();
	 gsfScEta= it->superCluster()->eta();
	 pfScEn  = it->pflowSuperCluster()->energy();
	 pfScEta= it->pflowSuperCluster()->eta();

	 h_gsfPfSCEtaVsEta->Fill(it->eta(),gsfScEta/pfScEta,myweight[0]);
	 h_gsfPfSCEnVsEtaPhi->Fill(it->eta(),it->phi(),gsfScEn/pfScEn,myweight[0]);

	 for (int j=0; j< 100; j++){
	    if ( it->eta()> j*deltaEta_ && it->eta()<(j+1)*deltaEta_){
	       for (int k=0; k<100; k++){
		  if ( it->phi()> k*deltaPhi_ && it->phi()<(k+1)*deltaPhi_){
		     h_gsfPfSCEnVsEtaPhi->Fill((j+0.5)*deltaEta_,(k+0.5)*deltaPhi_,gsfScEn/pfScEn,myweight[0]);
		  }
	       }
	    }
	 }

	 if (fabs(gsfScEta)<edgeEB){
	    h_gsfPfSCEta_EB->Fill(gsfScEta/pfScEta,myweight[0]);
	    h_gsfPfSCEn_EB->Fill(gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEnVsEn_EB->Fill(it->energy(),gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEtaVsEn_EB->Fill(it->energy(),gsfScEta/pfScEta,myweight[0]);
	 } else if (fabs(gsfScEta)<edgeEE){
	    h_gsfPfSCEta_EE->Fill(gsfScEta/pfScEta,myweight[0]);
	    h_gsfPfSCEn_EE->Fill(gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEnVsEn_EE->Fill(it->energy(),gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEtaVsEn_EE->Fill(it->energy(),gsfScEta/pfScEta,myweight[0]);
	 }     
      }      

      for(reco::PFCandidateCollection::const_iterator itPf=pfElec->begin();itPf!=pfElec->end();itPf++){
	 if (itPf->gsfTrackRef()==it->gsfTrack()) {
	    pfSize++;
	    h_ptPFptVsEta->Fill(it->eta(),it->energy()/itPf->energy(),myweight[0]);
	    h_ptPFptVsEn->Fill(it->energy(),it->energy()/itPf->energy(),myweight[0]);
	    pfe2.SetPtEtaPhiM(itPf->pt(),itPf->eta(),itPf->phi(),itPf->mass());

	    if (usingMC){
	       for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
		  dist= sqrt( pow(itgen->eta()-it->eta(),2)+pow(itgen->phi()-it->phi(),2) );
		  distEta = fabs(itgen->eta() - it->eta());
		  ratioEn = itgen->energy()/it->energy();
		  ratioEn2 = itgen->energy()/itPf->energy();
		  if (dist < maxDist && distEta < maxEta ){	     
		     if (!checkCut){
			h_MCenPFenVsEnWoEnCut->Fill(itPf->energy(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenPFenVsEtaWoEnCut->Fill(itPf->eta(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenGSFenVsEnWoEnCut->Fill(it->energy(),itgen->energy()/it->energy(), myweight[0]);  
			h_MCenGSFenVsEtaWoEnCut->Fill(it->eta(),itgen->energy()/it->energy(), myweight[0]);
			checkCut = true;
		     }
		     if (!checkPairing && ratioEn < maxEn && 1./ratioEn < maxEn && 
			 ratioEn2 < maxEn && 1./ratioEn2 < maxEn){
			h_MCenPFenVsEn->Fill(itPf->energy(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenPFenVsEta->Fill(itPf->eta(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenGSFenVsEn->Fill(it->energy(),itgen->energy()/it->energy(), myweight[0]);  
			h_MCenGSFenVsEta->Fill(it->eta(),itgen->energy()/it->energy(), myweight[0]);
			checkPairing=true;
			
		     }
		  }

		  if (fabs(itgen->pdgId())==11 && itgen->mother()->pdgId()==23){ // itgen->status()==1 && 
		     if (dist < 0.1 && !checkTruth){		     
			h_MCenPFenVsEnTruth->Fill(itPf->energy(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenPFenVsEtaTruth->Fill(itPf->eta(),itgen->energy()/itPf->energy(), myweight[0]);
			h_MCenGSFenVsEnTruth->Fill(it->energy(),itgen->energy()/it->energy(), myweight[0]);  
			h_MCenGSFenVsEtaTruth->Fill(it->eta(),itgen->energy()/it->energy(), myweight[0]);
			checkTruth=true;
		     }
		  }
		  if ( fabs(itgen->pdgId())==11 && dist < maxDist && dist < nearerDist){
		     nearerDist = dist;
		     enGen=itgen->energy();
		     checkNear=true;
		  }

	       } // end genParticle cycle
	       
	       if (!checkPairing){  // check what fail for the association to gen level
		  if (dist > maxDist) h_failReason->Fill(1);
		  if (distEta > maxEta) h_failReason->Fill(2);
		  if (ratioEn > maxEn || 1./ratioEn > maxEn) h_failReason->Fill(3);
		  if (ratioEn2 > maxEn || 1./ratioEn2 > maxEn) h_failReason->Fill(4);
	       }

	       if (checkNear){
		  h_MCenPFenVsEnENear->Fill(itPf->energy(),enGen/itPf->energy(), myweight[0]);
		  h_MCenPFenVsEtaENear->Fill(itPf->eta(),enGen/itPf->energy(), myweight[0]);
		  h_MCenGSFenVsEnENear->Fill(it->energy(),enGen/it->energy(), myweight[0]);  
		  h_MCenGSFenVsEtaENear->Fill(it->eta(),enGen/it->energy(), myweight[0]);
	       }
	       
	    } // end UsingMC
	 } 
      } // end PFelectron cycle
      h_sizePf->Fill(pfSize,myweight[0]);
      pfe_pair=pfe1 + pfe2;
      // ================================
    
      ///////////////////
      /// Jet Validation
      ///////////////////
      
      std::vector<math::XYZTLorentzVector> JetContainer;  
      JetContainer.clear();
      Handle<PFJetCollection> pfJets;
      iEvent.getByLabel(jetCollection_, pfJets);
      if (pfJets.isValid()) {
	 //  
	 // ===== riordina in pt i jets
	 //
         for(reco::PFJetCollection::const_iterator jet = pfJets->begin(); 
	     jet!=pfJets->end (); jet++) {
	    
	    // check if the jet is equal to one of the isolated electrons
	    double deltaR1= sqrt( pow(jet->eta()-e1.Eta(),2)+pow(jet->phi()-e1.Phi(),2) );
	    double deltaR2= sqrt( pow(jet->eta()-e2.Eta(),2)+pow(jet->phi()-e2.Phi(),2) );
	    if (deltaR1 > deltaRCone && deltaR2 > deltaRCone 
		// cut on the jet pt 
		&& jet->pt()>30
	       ){ 

	       JetContainer.push_back(jet->p4()); }
	 }
         std::stable_sort(JetContainer.begin(),JetContainer.end(),GreaterPt()); 
      }
      else{cout<<"No valid Jets Collection"<<endl;}
            
      for (std::vector<math::XYZTLorentzVector>::const_iterator jet = JetContainer.begin (); 
	   jet != JetContainer.end (); jet++) {
	 
	 // jet in the BARREL
	 if (fabs(jet->Eta())<edgeEB){
	    totJetsCk++;
	    nJetsEB++;
	    h_jetPt_EB->Fill(jet->Pt(),myweight[0]);
	    h_jetEta_EB->Fill(jet->Eta(),myweight[0]);
	    if (nJetsEB==1) h_jetPtFirst_EB->Fill(jet->Pt(),myweight[0]);
	    else if (nJetsEB==2) h_jetPtSecond_EB->Fill(jet->Pt(),myweight[0]);
	    else if (nJetsEB==3) h_jetPtThird_EB->Fill(jet->Pt(),myweight[0]);
	    else if (nJetsEB==4) h_jetPtFourth_EB->Fill(jet->Pt(),myweight[0]);
	    if (totJetsCk==1) h_jetPtFirstCk_EB->Fill(jet->Pt(),myweight[0]);
	    else if (totJetsCk==2) h_jetPtSecondCk_EB->Fill(jet->Pt(),myweight[0]);
	    else if (totJetsCk==3) h_jetPtThirdCk_EB->Fill(jet->Pt(),myweight[0]);
	    else if (totJetsCk==4) h_jetPtFourthCk_EB->Fill(jet->Pt(),myweight[0]);

	    h_jetPtVsEta_EB->Fill(jet->Eta(),jet->Pt(),myweight[0]);
	    for (int v=0; v<11; v++){
	       if (numberOfVertices==(v+1)) h_jetPtVtx_EB[v]->Fill(jet->Pt(),myweight[0]);
	    }
	 }
	 // jet in the ENDCAP
	 if (fabs(jet->Eta())>edgeEB && fabs(jet->Eta())<edgeEE){
	    totJetsCk++;
	    nJetsEE++;
	    h_jetPt_EE->Fill(jet->Pt(),myweight[0]);
	    if (nJetsEE==1) h_jetPtFirst_EE->Fill(jet->Pt(),myweight[0]);
	    else if (nJetsEE==2) h_jetPtSecond_EE->Fill(jet->Pt(),myweight[0]);
	    else if (nJetsEE==3) h_jetPtThird_EE->Fill(jet->Pt(),myweight[0]);
	    else if (nJetsEE==4) h_jetPtFourth_EE->Fill(jet->Pt(),myweight[0]);
	    if (totJetsCk==1) h_jetPtFirstCk_EE->Fill(jet->Pt(),myweight[0]);
	    else if (totJetsCk==2) h_jetPtSecondCk_EE->Fill(jet->Pt(),myweight[0]);
	    else if (totJetsCk==3) h_jetPtThirdCk_EE->Fill(jet->Pt(),myweight[0]);
	    else if (totJetsCk==4) h_jetPtFourthCk_EE->Fill(jet->Pt(),myweight[0]);
	    
	    for (int v=0; v<11; v++){
	       if (numberOfVertices==(v+1)) h_jetPtVtx_EE[v]->Fill(jet->Pt(),myweight[0]);
	    }
	 }
	 // jet in ECAL
	 if (fabs(jet->Eta())<edgeEE){
	    h_jetEta_EE->Fill(jet->Eta(),myweight[0]);
	    h_jetPtVsEta_EE->Fill(jet->Eta(),jet->Pt(),myweight[0]);
	 } 
      }
      h_jetNum_EB->Fill(nJetsEB,myweight[0]);
      h_jetNum_EE->Fill(nJetsEE,myweight[0]);
      for (int v=0; v<11; v++){
	 if (numberOfVertices==(v+1)) h_nJetVtx_EB[v]->Fill(nJetsEB,myweight[0]);
	 if (numberOfVertices==(v+1)) h_nJetVtx_EE[v]->Fill(nJetsEE,myweight[0]);
      }
      
      totJets = nJetsEB + nJetsEE;
      double zPt = e_pair.Pt();
      double zInvMass = e_pair.M();
      h_invMass->Fill(zInvMass,myweight[0]);
      h_invMassPF->Fill(pfe_pair.M(),myweight[0]);
      h_zEta->Fill(e_pair.Eta(),myweight[0]);
      h_zRapidity->Fill(e_pair.Rapidity(),myweight[0]);
      h_zYieldVsjets->Fill(totJets,myweight[0]);
      if (numberOfVertices==1) h_zYieldVsjetsVtx1->Fill(totJets,myweight[0]);
      if (numberOfVertices==5) h_zYieldVsjetsVtx5->Fill(totJets,myweight[0]);
      
      if (totJets == 0){ 
	 h_zEtaNjet0->Fill(e_pair.Eta());
      }
      if (totJets == 1){ 
	 h_zEtaNjet1->Fill(e_pair.Eta(),myweight[0]);
	 h_zMassNjet1->Fill(zInvMass,myweight[0]);
      } else if (totJets == 2){ 
	 h_zEtaNjet2->Fill(e_pair.Eta(),myweight[0]);
	 h_zMassNjet2->Fill(zInvMass,myweight[0]);
      } else if (totJets == 3){ 
	 h_zEtaNjet3->Fill(e_pair.Eta(),myweight[0]);
	 h_zMassNjet3->Fill(zInvMass,myweight[0]);
      } else if (totJets == 4){ 
	 h_zEtaNjet4->Fill(e_pair.Eta(),myweight[0]);
	 h_zMassNjet4->Fill(zInvMass,myweight[0]);
      } 

      if (totJets >= 1) h_zEtaNjet1Incl->Fill(e_pair.Eta(),myweight[0]);
      if (totJets >= 2) h_zEtaNjet2Incl->Fill(e_pair.Eta(),myweight[0]);
      if (totJets >= 3) h_zEtaNjet3Incl->Fill(e_pair.Eta(),myweight[0]);
      if (totJets >= 4) h_zEtaNjet4Incl->Fill(e_pair.Eta(),myweight[0]);
      
      for (int i=0; i<11; i++)
      {
	 if (totJets == i) h_ptZ_jet[i]->Fill(zPt,myweight[0]);
	 if (totJets >= i) h_ptZ_jetIncl[i]->Fill(zPt,myweight[0]);
      }     
      
      for (std::vector<math::XYZTLorentzVector>::const_iterator jet = JetContainer.begin ();
	   jet != JetContainer.end (); jet++) {
	 // jet in the BARREL
	 if (fabs(jet->Eta())<edgeEB){
	    if (totJets == 1) h_jetPtNjet1_EB->Fill(jet->Pt(),myweight[0]);
	    if (totJets == 2) h_jetPtNjet2_EB->Fill(jet->Pt(),myweight[0]);
	    if (totJets == 3) h_jetPtNjet3_EB->Fill(jet->Pt(),myweight[0]);
	    if (totJets == 4) h_jetPtNjet4_EB->Fill(jet->Pt(),myweight[0]);
	 }
	 // jet in the ENDCAP
	 if (fabs(jet->Eta())>edgeEB && fabs(jet->Eta())<edgeEE){
	    if (totJets == 1) h_jetPtNjet1_EE->Fill(jet->Pt(),myweight[0]);
	    if (totJets == 2) h_jetPtNjet2_EE->Fill(jet->Pt(),myweight[0]);
	    if (totJets == 3) h_jetPtNjet3_EE->Fill(jet->Pt(),myweight[0]);
	    if (totJets == 4) h_jetPtNjet4_EE->Fill(jet->Pt(),myweight[0]);
	 }
	 // jet in ECAL
	 if (fabs(jet->Eta())<edgeEE){
	    if (totJets == 1) h_jetPtNjet1->Fill(jet->Pt(),myweight[0]);
	    if (totJets == 2) h_jetPtNjet2->Fill(jet->Pt(),myweight[0]);
	    if (totJets == 3) h_jetPtNjet3->Fill(jet->Pt(),myweight[0]);
	    if (totJets == 4) h_jetPtNjet4->Fill(jet->Pt(),myweight[0]);

	    if (totJets >= 1) h_jetPtNjet1Incl->Fill(jet->Pt(),myweight[0]);
	    if (totJets >= 2) h_jetPtNjet2Incl->Fill(jet->Pt(),myweight[0]);
	    if (totJets >= 3) h_jetPtNjet3Incl->Fill(jet->Pt(),myweight[0]);
	    if (totJets >= 4) h_jetPtNjet4Incl->Fill(jet->Pt(),myweight[0]);
	 }
      }
      

   } else {std::cout << "WARNING: More than two electron selected"<< std::endl;}  

}


// ------------ method called once each job just before starting event loop  ------------
void 
jetValidation::beginJob()
{
   edgeEB     = 1.479;
   edgeEE     = 3.0;
   edgeTrk    = 2.4;
   edgeEE     = edgeTrk;
   deltaRCone = 0.3;
}

// ------------ method called once each job just after ending the event loop  ------------
void 
jetValidation::endJob() 
{
    
 //Histograms
 h_jetPt_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPt_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetEta_EB->GetXaxis()->SetTitle("#eta_{jets}");
 h_jetEta_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetNum_EB->GetXaxis()->SetTitle("N_{jets}");
 h_jetNum_EB->GetYaxis()->SetTitle("Events");
 h_jetPtFirst_EB->GetXaxis()->SetTitle("p_{T}^{first jet}");
 h_jetPtFirst_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtSecond_EB->GetXaxis()->SetTitle("p_{T}^{second jet}");
 h_jetPtSecond_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtThird_EB->GetXaxis()->SetTitle("p_{T}^{third jet}");
 h_jetPtThird_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtFourth_EB->GetXaxis()->SetTitle("p_{T}^{fourth jet}");
 h_jetPtFourth_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVsEta_EB->GetXaxis()->SetTitle("#eta_{jets}");
 h_jetPtVsEta_EB->GetYaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVsEta_EB->GetZaxis()->SetTitle("N_{jets}");

 h_jetPt_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPt_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetEta_EE->GetXaxis()->SetTitle("#eta_{jets}");
 h_jetEta_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetNum_EE->GetXaxis()->SetTitle("N_{jets}");
 h_jetNum_EE->GetYaxis()->SetTitle("Events");
 h_jetPtFirst_EE->GetXaxis()->SetTitle("p_{T}^{first jet}");
 h_jetPtFirst_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtSecond_EE->GetXaxis()->SetTitle("p_{T}^{second jet}");
 h_jetPtSecond_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtThird_EE->GetXaxis()->SetTitle("p_{T}^{third jet}");
 h_jetPtThird_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtFourth_EE->GetXaxis()->SetTitle("p_{T}^{fourth jet}");
 h_jetPtFourth_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVsEta_EE->GetXaxis()->SetTitle("#eta_{jets}");
 h_jetPtVsEta_EE->GetYaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVsEta_EE->GetZaxis()->SetTitle("N_{jets}");

 h_invMass->GetXaxis()->SetTitle("Mass_{Z}");
 h_invMass->GetYaxis()->SetTitle("N_{Z}");
 for (int i=0; i<11; i++){
    h_ptZ_jet[i]->GetXaxis()->SetTitle("p_{T}^{Z}");
    h_ptZ_jet[i]->GetYaxis()->SetTitle("N_{Z}");
    h_meanPtZVsNjet->SetBinContent(i+1, h_ptZ_jet[i]->GetMean());
 }
 h_meanPtZVsNjet->GetXaxis()->SetTitle("N_{jets}");
 h_meanPtZVsNjet->GetYaxis()->SetTitle("< p_{T}^{Z} >");

    
}

// ------------ method called when starting to processes a run  ------------
void 
jetValidation::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
jetValidation::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
jetValidation::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
jetValidation::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(jetValidation);
