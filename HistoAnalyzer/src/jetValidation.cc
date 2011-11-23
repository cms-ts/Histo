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
      //int cluSize2 =0;
      double cluTotEnergy1=0.;
      //double cluTotEnergy2=0.;
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
      bool checkPf1=false;
      bool checkPf2=false;

      reco::GsfElectronCollection::const_iterator it=goodEPair->begin();
      TLorentzVector e1, e2, e_pair;
      TLorentzVector pfe1, pfe2, pfe_pair;
      e1.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());

      // ================================
      // FIll the Weights info
      // ================================
      double wei=myweight[0];
      h_weights->Fill(wei);

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
	    double ratioPt =  (it->pt()-itPf->pt())/it->pt();
	    h_ptGsfPfGsfVsptGsf->Fill(it->pt(),ratioPt,myweight[0]);
	    pfe1.SetPtEtaPhiM(itPf->pt(),itPf->eta(),itPf->phi(),itPf->mass());
	    checkPf1=true;
	    
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

		  h_PFenMCenVsEnENear->Fill(itPf->energy(),itPf->energy()/enGen, myweight[0]);
		  h_PFenMCenVsEtaENear->Fill(itPf->eta(),itPf->energy()/enGen, myweight[0]);
		  h_GSFenMCenVsEnENear->Fill(it->energy(),it->energy()/enGen, myweight[0]);  
		  h_GSFenMCenVsEtaENear->Fill(it->eta(),it->energy()/enGen, myweight[0]);

		  h_gsfMcPfMcEnVsGsfEnENear->Fill(it->energy(),(it->energy()/enGen)/(itPf->energy()/enGen), myweight[0]); 
		  h_gsfMcPfMcEnVsGsfEtaENear->Fill(it->eta(),(it->energy()/enGen)/(itPf->energy()/enGen), myweight[0]);
		  h_gsfMcPfMcEnVsGsfMcEnENear->Fill(it->energy()/enGen,(it->energy()/enGen)/(itPf->energy()/enGen), myweight[0]); 
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
	    double ratioPt =  (it->pt()-itPf->pt())/it->pt();
	    h_ptGsfPfGsfVsptGsf->Fill(it->pt(),ratioPt,myweight[0]);
	    pfe2.SetPtEtaPhiM(itPf->pt(),itPf->eta(),itPf->phi(),itPf->mass());
	    checkPf2=true;
	    
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
		  h_gsfMcPfMcEnVsGsfEnENear->Fill(it->energy(),(it->energy()/enGen)/(itPf->energy()/enGen), myweight[0]); 
		  h_gsfMcPfMcEnVsGsfEtaENear->Fill(it->eta(),(it->energy()/enGen)/(itPf->energy()/enGen), myweight[0]); 
		  h_gsfMcPfMcEnVsGsfMcEnENear->Fill(it->energy()/enGen,(it->energy()/enGen)/(itPf->energy()/enGen), myweight[0]); 
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

      //Filling the Unfolding rootuple!
      Jet_multiplicity=totJets;
      Z_y=e_pair.Rapidity();
      Z_pt=zPt;

      //DONE

      h_invMass->Fill(zInvMass,myweight[0]);
      h_massMinusPdgGsf->Fill(zInvMass-zMassPdg,myweight[0]);
      if (fabs(e1.Eta())<=edgeEB && fabs(e2.Eta())<=edgeEB) {h_massMinusPdgGsf_EB->Fill(zInvMass-zMassPdg,myweight[0]);}
      else if (fabs(e1.Eta())<=edgeEE && fabs(e2.Eta())<=edgeEE &&
	       fabs(e1.Eta())>edgeEB && fabs(e2.Eta())>edgeEB) { h_massMinusPdgGsf_EE->Fill(zInvMass-zMassPdg,myweight[0]);}
      else if (fabs(e1.Eta())<edgeEE && fabs(e2.Eta())<edgeEE) {h_massMinusPdgGsf_EBEE->Fill(zInvMass-zMassPdg,myweight[0]);}

      if (checkPf1 && checkPf2){
	 h_invMassPF->Fill(pfe_pair.M(),myweight[0]);
	 h_massMinusPdgPf->Fill(pfe_pair.M()-zMassPdg,myweight[0]);
	 if (fabs(pfe1.Eta())<=edgeEB && fabs(pfe2.Eta())<=edgeEB) {h_massMinusPdgPf_EB->Fill(zInvMass-zMassPdg,myweight[0]);}
	 else if (fabs(pfe1.Eta())<=edgeEE && fabs(pfe2.Eta())<=edgeEE &&
		  fabs(pfe1.Eta())>edgeEB && fabs(pfe2.Eta())>edgeEB) {h_massMinusPdgPf_EE->Fill(zInvMass-zMassPdg,myweight[0]);}
	 else if (fabs(pfe1.Eta())<edgeEE && fabs(pfe2.Eta())<edgeEE) {h_massMinusPdgPf_EBEE->Fill(zInvMass-zMassPdg,myweight[0]);}
      }

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
	 h_zMassMinusPdgGsfNjet1->Fill(zInvMass-zMassPdg,myweight[0]);
	 if (checkPf1 && checkPf2) h_zMassMinusPdgPfNjet1->Fill(pfe_pair.M()-zMassPdg,myweight[0]);
      } else if (totJets == 2){ 
	 h_zEtaNjet2->Fill(e_pair.Eta(),myweight[0]);
	 h_zMassNjet2->Fill(zInvMass,myweight[0]);
	 h_zMassMinusPdgGsfNjet2->Fill(zInvMass-zMassPdg,myweight[0]);
	 if (checkPf1 && checkPf2) h_zMassMinusPdgPfNjet2->Fill(pfe_pair.M()-zMassPdg,myweight[0]);
      } else if (totJets == 3){ 
	 h_zEtaNjet3->Fill(e_pair.Eta(),myweight[0]);
	 h_zMassNjet3->Fill(zInvMass,myweight[0]);
	 h_zMassMinusPdgGsfNjet3->Fill(zInvMass-zMassPdg,myweight[0]);
	 if (checkPf1 && checkPf2) h_zMassMinusPdgPfNjet3->Fill(pfe_pair.M()-zMassPdg,myweight[0]);
      } else if (totJets == 4){ 
	 h_zEtaNjet4->Fill(e_pair.Eta(),myweight[0]);
	 h_zMassNjet4->Fill(zInvMass,myweight[0]);
	 h_zMassMinusPdgGsfNjet4->Fill(zInvMass-zMassPdg,myweight[0]);
	 if (checkPf1 && checkPf2) h_zMassMinusPdgPfNjet4->Fill(pfe_pair.M()-zMassPdg,myweight[0]);
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

   treeUN_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
jetValidation::beginJob()
{
  //TFile and TTree initialization
  treeUN_= new TTree("treeUN_","treeUN_");
  
  //EB PileUp REMOVED
  treeUN_->Branch("Z_pt",&Z_pt);
  treeUN_->Branch("Z_y",&Z_y);
  treeUN_->Branch("Jet_multiplicity",&Jet_multiplicity);

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
  h_weights->GetXaxis()->SetTitle("Weight");
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
 h_jetPtFirstCk_EB->GetXaxis()->SetTitle("p_{T}^{first jet}");
 h_jetPtFirstCk_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtSecondCk_EB->GetXaxis()->SetTitle("p_{T}^{second jet}");
 h_jetPtSecondCk_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtThirdCk_EB->GetXaxis()->SetTitle("p_{T}^{third jet}");
 h_jetPtThirdCk_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtFourthCk_EB->GetXaxis()->SetTitle("p_{T}^{fourth jet}");
 h_jetPtFourthCk_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVsEta_EB->GetXaxis()->SetTitle("#eta_{jets}");
 h_jetPtVsEta_EB->GetYaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVsEta_EB->GetZaxis()->SetTitle("N_{jets}");
 h_jetPtNjet1_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet1_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtNjet2_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet2_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtNjet3_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet3_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtNjet4_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet4_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_gsfPfSCEtaVsEn_EB->GetXaxis()->SetTitle("energy_{SuperCluster}");
 h_gsfPfSCEtaVsEn_EB->GetYaxis()->SetTitle("#eta_{GSF} / #eta_{PF} ^{SuperCluster}");
 h_gsfPfSCEnVsEn_EB->GetXaxis()->SetTitle("energy_{SuperCluster}");
 h_gsfPfSCEnVsEn_EB->GetYaxis()->SetTitle("En_{GSF} / En_{PF} ^{SuperCluster}");
 h_gsfPfSCEta_EB->GetYaxis()->SetTitle("N_{SuperCluster}");
 h_gsfPfSCEta_EB->GetXaxis()->SetTitle("#eta_{GSF} / #eta_{PF} ^{SuperCluster}");
 h_gsfPfSCEn_EB->GetYaxis()->SetTitle("N_{SuperCluster}");
 h_gsfPfSCEn_EB->GetXaxis()->SetTitle("En_{GSF} / En_{PF} ^{SuperCluster}");
 h_massMinusPdgGsf_EB->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgGsf_EB->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_massMinusPdgPf_EB->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgPf_EB->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");

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
 h_jetPtFirstCk_EE->GetXaxis()->SetTitle("p_{T}^{first jet}");
 h_jetPtFirstCk_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtSecondCk_EE->GetXaxis()->SetTitle("p_{T}^{second jet}");
 h_jetPtSecondCk_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtThirdCk_EE->GetXaxis()->SetTitle("p_{T}^{third jet}");
 h_jetPtThirdCk_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtFourthCk_EE->GetXaxis()->SetTitle("p_{T}^{fourth jet}");
 h_jetPtFourthCk_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVsEta_EE->GetXaxis()->SetTitle("#eta_{jets}");
 h_jetPtVsEta_EE->GetYaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVsEta_EE->GetZaxis()->SetTitle("N_{jets}");
 h_jetPtNjet1_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet1_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtNjet2_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet2_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtNjet3_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet3_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtNjet4_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet4_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_gsfPfSCEtaVsEn_EE->GetXaxis()->SetTitle("energy_{SuperCluster}");
 h_gsfPfSCEtaVsEn_EE->GetYaxis()->SetTitle("#eta_{GSF} / #eta_{PF} ^{SuperCluster}");
 h_gsfPfSCEnVsEn_EE->GetXaxis()->SetTitle("energy_{SuperCluster}");
 h_gsfPfSCEnVsEn_EE->GetYaxis()->SetTitle("En_{GSF} / En_{PF} ^{SuperCluster}");
 h_gsfPfSCEta_EE->GetYaxis()->SetTitle("N_{SuperCluster}");
 h_gsfPfSCEta_EE->GetXaxis()->SetTitle("#eta_{GSF} / #eta_{PF} ^{SuperCluster}");
 h_gsfPfSCEn_EE->GetYaxis()->SetTitle("N_{SuperCluster}");
 h_gsfPfSCEn_EE->GetXaxis()->SetTitle("En_{GSF} / En_{PF} ^{SuperCluster}");
 h_massMinusPdgGsf_EE->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgGsf_EE->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_massMinusPdgPf_EE->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgPf_EE->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");

 h_massMinusPdgGsf_EBEE->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgGsf_EBEE->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_massMinusPdgPf_EBEE->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgPf_EBEE->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");

 h_gsfPfSCEtaVsEta->GetYaxis()->SetTitle("#eta_{GSF} / #eta_{PF} ^{SuperCluster}");
 h_gsfPfSCEtaVsEta->GetXaxis()->SetTitle("#eta_{SuperCluster}");
 h_gsfPfSCEnVsEtaPhi->GetXaxis()->SetTitle("#eta_{SuperCluster}");
 h_gsfPfSCEnVsEtaPhi->GetYaxis()->SetTitle("#phi_{SuperCluster}");
 h_ptPFptVsEta->GetYaxis()->SetTitle("En_{GSF} / En_{PF} ^{electrons}");
 h_ptPFptVsEta->GetXaxis()->SetTitle("#eta_{GSF}");
 h_ptPFptVsEn->GetYaxis()->SetTitle("En_{GSF} / En_{PF} ^{electrons}");
 h_ptPFptVsEn->GetXaxis()->SetTitle("energy_{GSF}");
 h_superClusterSize->GetYaxis()->SetTitle("N_{events}");
 h_superClusterSize->GetXaxis()->SetTitle("n of clusters in the superCluster");
 h_gsfPfSCEnClu1->GetYaxis()->SetTitle("En_{GSF} / En_{PF} ^{electrons}");
 h_gsfPfSCEnClu1->GetYaxis()->SetTitle("N_{SuperCluster}");
 h_ptGsfPfGsfVsptGsf->GetYaxis()->SetTitle("(p_{T}^{GSF} - p_{T}^{PF}) / p_{T}^{GSF}");
 h_ptGsfPfGsfVsptGsf->GetXaxis()->SetTitle("p_{T}^{GSF}");

 h_nVtx->GetYaxis()->SetTitle("N_{events}");
 h_nVtx->GetXaxis()->SetTitle("N_{vertex}");
 h_zYieldVsjets->GetYaxis()->SetTitle("N_{events}");
 h_zYieldVsjets->GetXaxis()->SetTitle("N_{jets}");
 h_zYieldVsjetsVtx1->GetYaxis()->SetTitle("N_{events}");
 h_zYieldVsjetsVtx1->GetXaxis()->SetTitle("N_{jets}");
 h_zYieldVsjetsVtx5->GetYaxis()->SetTitle("N_{events}");
 h_zYieldVsjetsVtx5->GetXaxis()->SetTitle("N_{jets}");
 h_jetPtNjet1->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet1->GetXaxis()->SetTitle("p{T}^{jets}");
 h_jetPtNjet2->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet2->GetXaxis()->SetTitle("p{T}^{jets}");
 h_jetPtNjet3->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet3->GetXaxis()->SetTitle("p{T}^{jets}");
 h_jetPtNjet4->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet4->GetXaxis()->SetTitle("p{T}^{jets}");
 h_jetPtNjet1Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet1Incl->GetXaxis()->SetTitle("p{T}^{jets}");
 h_jetPtNjet2Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet2Incl->GetXaxis()->SetTitle("p{T}^{jets}");
 h_jetPtNjet3Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet3Incl->GetXaxis()->SetTitle("p{T}^{jets}");
 h_jetPtNjet4Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet4Incl->GetXaxis()->SetTitle("p{T}^{jets}");
 h_zRapidity->GetYaxis()->SetTitle("N_{Z}");
 h_zRapidity->GetXaxis()->SetTitle("rapidity_{Z}");
 h_zEta->GetYaxis()->SetTitle("N_{Z}");
 h_zEta->GetXaxis()->SetTitle("#eta_{Z}");
 h_zEtaNjet0->GetYaxis()->SetTitle("N_{Z}");
 h_zEtaNjet0->GetXaxis()->SetTitle("#eta_{Z}");
 h_zEtaNjet1->GetYaxis()->SetTitle("N_{Z}");
 h_zEtaNjet1->GetXaxis()->SetTitle("#eta_{Z}");
 h_zEtaNjet2->GetYaxis()->SetTitle("N_{Z}");
 h_zEtaNjet2->GetXaxis()->SetTitle("#eta_{Z}");
 h_zEtaNjet3->GetYaxis()->SetTitle("N_{Z}");
 h_zEtaNjet3->GetXaxis()->SetTitle("#eta_{Z}");
 h_zEtaNjet4->GetYaxis()->SetTitle("N_{Z}");
 h_zEtaNjet4->GetXaxis()->SetTitle("#eta_{Z}");
 h_zEtaNjet1Incl->GetYaxis()->SetTitle("N_{Z}");
 h_zEtaNjet1Incl->GetXaxis()->SetTitle("#eta_{Z}");
 h_zEtaNjet2Incl->GetYaxis()->SetTitle("N_{Z}");
 h_zEtaNjet2Incl->GetXaxis()->SetTitle("#eta_{Z}");
 h_zEtaNjet3Incl->GetYaxis()->SetTitle("N_{Z}");
 h_zEtaNjet3Incl->GetXaxis()->SetTitle("#eta_{Z}");
 h_zEtaNjet4Incl->GetYaxis()->SetTitle("N_{Z}");
 h_zEtaNjet4Incl->GetXaxis()->SetTitle("#eta_{Z}");

 h_invMass->GetXaxis()->SetTitle("mass_{Z}");
 h_invMass->GetYaxis()->SetTitle("N_{Z}");
 h_invMassPF->GetXaxis()->SetTitle("mass_{Z}");
 h_invMassPF->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgGsf->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_massMinusPdgGsf->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgPf->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_massMinusPdgPf->GetYaxis()->SetTitle("N_{Z}");
 h_zMassNjet1->GetXaxis()->SetTitle("mass_{Z}");
 h_zMassNjet1->GetYaxis()->SetTitle("N_{Z}");
 h_zMassNjet2->GetXaxis()->SetTitle("mass_{Z}");
 h_zMassNjet2->GetYaxis()->SetTitle("N_{Z}");
 h_zMassNjet3->GetXaxis()->SetTitle("mass_{Z}");
 h_zMassNjet3->GetYaxis()->SetTitle("N_{Z}");
 h_zMassNjet4->GetXaxis()->SetTitle("mass_{Z}");
 h_zMassNjet4->GetYaxis()->SetTitle("N_{Z}");
 h_zMassMinusPdgGsfNjet1->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_zMassMinusPdgGsfNjet1->GetYaxis()->SetTitle("N_{Z}");
 h_zMassMinusPdgGsfNjet2->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_zMassMinusPdgGsfNjet2->GetYaxis()->SetTitle("N_{Z}");
 h_zMassMinusPdgGsfNjet3->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_zMassMinusPdgGsfNjet3->GetYaxis()->SetTitle("N_{Z}");
 h_zMassMinusPdgGsfNjet4->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_zMassMinusPdgGsfNjet4->GetYaxis()->SetTitle("N_{Z}");
 h_zMassMinusPdgPfNjet1->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_zMassMinusPdgPfNjet1->GetYaxis()->SetTitle("N_{Z}");
 h_zMassMinusPdgPfNjet2->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_zMassMinusPdgPfNjet2->GetYaxis()->SetTitle("N_{Z}");
 h_zMassMinusPdgPfNjet3->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_zMassMinusPdgPfNjet3->GetYaxis()->SetTitle("N_{Z}");
 h_zMassMinusPdgPfNjet4->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_zMassMinusPdgPfNjet4->GetYaxis()->SetTitle("N_{Z}");


 for (int i=0; i<11; i++){
    h_ptZ_jet[i]->GetXaxis()->SetTitle("p_{T}^{Z}");
    h_ptZ_jet[i]->GetYaxis()->SetTitle("N_{Z}");
    h_ptZ_jetIncl[i]->GetXaxis()->SetTitle("p_{T}^{Z}");
    h_ptZ_jetIncl[i]->GetYaxis()->SetTitle("N_{Z}");
    h_jetPtVtx_EB[i]->GetYaxis()->SetTitle("N_{jets}");
    h_jetPtVtx_EB[i]->GetXaxis()->SetTitle("p{T}^{jets}");
    h_jetPtVtx_EE[i]->GetYaxis()->SetTitle("N_{jets}");
    h_jetPtVtx_EE[i]->GetXaxis()->SetTitle("p{T}^{jets}");   
    h_nJetVtx_EB[i]->GetYaxis()->SetTitle("N_{events}");
    h_nJetVtx_EB[i]->GetXaxis()->SetTitle("N_{jets}");   
    h_nJetVtx_EE[i]->GetYaxis()->SetTitle("N_{events}");
    h_nJetVtx_EE[i]->GetXaxis()->SetTitle("N_{jets}");
 }

 if (usingMC){
    h_MCenPFenVsEn->GetYaxis()->SetTitle("En_{MC} / En_{PF} ^{electrons}");
    h_MCenPFenVsEn->GetXaxis()->SetTitle("energy_{PF}");
    h_MCenPFenVsEta->GetYaxis()->SetTitle("En_{MC} / En_{PF} ^{electrons}");
    h_MCenPFenVsEta->GetXaxis()->SetTitle("#eta_{PF}");
    h_MCenGSFenVsEn->GetYaxis()->SetTitle("En_{MC} / En_{GSF} ^{electrons}");
    h_MCenGSFenVsEn->GetXaxis()->SetTitle("energy_{GSF}");
    h_MCenGSFenVsEta->GetYaxis()->SetTitle("En_{MC} / En_{GSF} ^{electrons}");
    h_MCenGSFenVsEta->GetXaxis()->SetTitle("#eta_{GSF}");
    h_MCenPFenVsEnWoEnCut->GetYaxis()->SetTitle("En_{MC} / En_{PF} ^{electrons}");
    h_MCenPFenVsEnWoEnCut->GetXaxis()->SetTitle("energy_{PF}");
    h_MCenPFenVsEtaWoEnCut->GetYaxis()->SetTitle("En_{MC} / En_{PF} ^{electrons}");
    h_MCenPFenVsEtaWoEnCut->GetXaxis()->SetTitle("#eta_{PF}");
    h_MCenGSFenVsEnWoEnCut->GetYaxis()->SetTitle("En_{MC} / En_{GSF} ^{electrons}");
    h_MCenGSFenVsEnWoEnCut->GetXaxis()->SetTitle("energy_{GSF}");
    h_MCenGSFenVsEtaWoEnCut->GetYaxis()->SetTitle("En_{MC} / En_{GSF} ^{electrons}");
    h_MCenGSFenVsEtaWoEnCut->GetXaxis()->SetTitle("#eta_{GSF}");
    h_MCenPFenVsEnTruth->GetYaxis()->SetTitle("En_{MC} / En_{PF} ^{electrons}");
    h_MCenPFenVsEnTruth->GetXaxis()->SetTitle("energy_{PF}");
    h_MCenPFenVsEtaTruth->GetYaxis()->SetTitle("En_{MC} / En_{PF} ^{electrons}");
    h_MCenPFenVsEtaTruth->GetXaxis()->SetTitle("#eta_{PF}");
    h_MCenGSFenVsEnTruth->GetYaxis()->SetTitle("En_{MC} / En_{GSF} ^{electrons}");
    h_MCenGSFenVsEnTruth->GetXaxis()->SetTitle("energy_{GSF}");
    h_MCenGSFenVsEtaTruth->GetYaxis()->SetTitle("En_{MC} / En_{GSF} ^{electrons}");
    h_MCenGSFenVsEtaTruth->GetXaxis()->SetTitle("#eta_{GSF}");
    h_MCenPFenVsEnENear->GetYaxis()->SetTitle("En_{MC} / En_{PF} ^{electrons}");
    h_MCenPFenVsEnENear->GetXaxis()->SetTitle("energy_{PF}");
    h_MCenPFenVsEtaENear->GetYaxis()->SetTitle("En_{MC} / En_{PF} ^{electrons}");
    h_MCenPFenVsEtaENear->GetXaxis()->SetTitle("#eta_{PF}");
    h_MCenGSFenVsEnENear->GetYaxis()->SetTitle("En_{MC} / En_{GSF} ^{electrons}");
    h_MCenGSFenVsEnENear->GetXaxis()->SetTitle("energy_{GSF}");
    h_MCenGSFenVsEtaENear->GetYaxis()->SetTitle("En_{MC} / En_{GSF} ^{electrons}");
    h_MCenGSFenVsEtaENear->GetXaxis()->SetTitle("#eta_{GSF}");
    h_PFenMCenVsEnENear->GetYaxis()->SetTitle("En_{PF} / En_{MC} ^{electrons}");
    h_PFenMCenVsEnENear->GetXaxis()->SetTitle("energy_{PF}");
    h_PFenMCenVsEtaENear->GetYaxis()->SetTitle("En_{PF} / En_{MC} ^{electrons}");
    h_PFenMCenVsEtaENear->GetXaxis()->SetTitle("#eta_{PF}");
    h_GSFenMCenVsEnENear->GetYaxis()->SetTitle("En_{GSF} / En_{MC} ^{electrons}");
    h_GSFenMCenVsEnENear->GetXaxis()->SetTitle("energy_{GSF}");
    h_GSFenMCenVsEtaENear->GetYaxis()->SetTitle("En_{GSF} / En_{MC} ^{electrons}");
    h_GSFenMCenVsEtaENear->GetXaxis()->SetTitle("#eta_{GSF}");
    h_gsfMcPfMcEnVsGsfEnENear->GetYaxis()->SetTitle("( En_{GSF} / En_{MC} ) / ( En_{PF} / En_{MC} )");
       h_gsfMcPfMcEnVsGsfEnENear->GetXaxis()->SetTitle("energy_{GSF}");
       h_gsfMcPfMcEnVsGsfEtaENear->GetYaxis()->SetTitle("( En_{GSF} / En_{MC} ) / ( En_{PF} / En_{MC} )");
       h_gsfMcPfMcEnVsGsfEtaENear->GetXaxis()->SetTitle("#eta_{GSF}");
       h_gsfMcPfMcEnVsGsfMcEnENear->GetYaxis()->SetTitle("( En_{GSF} / En_{MC} ) / ( En_{PF} / En_{MC} )");
       h_gsfMcPfMcEnVsGsfMcEnENear->GetXaxis()->SetTitle("En_{GSF} / En_{MC}");
 }  

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
