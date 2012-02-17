// -*- C++ -*-
//

#include "Histo/HistoAnalyzer/interface/jetValidation.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/Common/interface/RefVector.h"
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

  bool Debug=false;

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

   edm::Handle<reco::PFCandidateCollection> pfPart;
   iEvent.getByLabel (pflowCollection_,pfPart);
  

   if (goodEPair->size()==2)
   {   
      double gsfScEn;
      double gsfScEta;
      double gsfScPhi;
      double pfScEn;
      double pfScEta;
      double pfScPhi;
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
      double enGen=0, ptGen=0, etaGen=0, phiGen=0;

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

      //TLorentz vector of the two Z boson electrons, at GEN level
      TLorentzVector e1_gen,e2_gen;
      
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
	 gsfScPhi= it->superCluster()->phi();
	 pfScEn  = it->pflowSuperCluster()->energy();
	 pfScEta= it->pflowSuperCluster()->eta();
	 pfScPhi= it->pflowSuperCluster()->phi();

	 h_gsfPfSCEtaVsEta->Fill(it->eta(),gsfScEta-pfScEta,myweight[0]);
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
	    h_gsfPfSCEta_EB->Fill(gsfScEta-pfScEta,myweight[0]);
	    h_gsfPfSCEn_EB->Fill(gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEnVsEn_EB->Fill(it->energy(),gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEtaVsEn_EB->Fill(it->energy(),gsfScEta-pfScEta,myweight[0]);
	 } else if (fabs(gsfScEta)<edgeEE){
	    h_gsfPfSCEta_EE->Fill(gsfScEta-pfScEta,myweight[0]);
	    h_gsfPfSCEn_EE->Fill(gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEnVsEn_EE->Fill(it->energy(),gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEtaVsEn_EE->Fill(it->energy(),gsfScEta-pfScEta,myweight[0]);


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
      if (doEfficiencies){
	 h_totalGsfElectronsVsEn->Fill(it->energy(),myweight[0]);
	 h_totalGsfElectronsVsEta->Fill(it->eta(),myweight[0]);
      }

      for(reco::PFCandidateCollection::const_iterator itPf=pfElec->begin();itPf!=pfElec->end();itPf++){
	 if (itPf->gsfTrackRef()==it->gsfTrack()) {
	    pfSize++;

	    if (doEfficiencies){
	       h_PairedPfElectronsVsEn->Fill(it->energy(),myweight[0]);
	       h_PairedPfElectronsVsEta->Fill(it->eta(),myweight[0]);
	    }

	    h_ptPFptVsEta->Fill(it->eta(),it->energy()/itPf->energy(),myweight[0]);
	    h_ptPFptVsEn->Fill(it->energy(),it->energy()/itPf->energy(),myweight[0]);
	    double ratioPt =  (it->pt()-itPf->pt())/it->pt();
	    h_ptGsfPfGsfVsptGsf->Fill(it->pt(),ratioPt,myweight[0]);
	    pfe1.SetPtEtaPhiM(itPf->pt(),itPf->eta(),itPf->phi(),itPf->mass());
	    checkPf1=true;
	    
	    if (usingMC){
	       if (doEfficiencies){
		  h_totalGsfxMcElectronsVsEn->Fill(it->energy(),myweight[0]);
		  h_totalGsfxMcElectronsVsEta->Fill(it->eta(),myweight[0]);
		  h_totalPfxMcElectronsVsEn->Fill(itPf->energy(),myweight[0]);
		  h_totalPfxMcElectronsVsEta->Fill(itPf->eta(),myweight[0]);
	       }

	       for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
		 dist= sqrt( pow(itgen->eta()-it->eta(),2)+pow(itgen->phi()-it->phi(),2) );
		 distEta = fabs(itgen->eta() - it->eta());
		 ratioEn = itgen->energy()/it->energy();
		 ratioEn2 = itgen->energy()/itPf->energy();

		 if (doElectronsComparisonMC){
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
		 }// end doElectronsComparisonMC

		 if ( fabs(itgen->pdgId())==11 && dist < maxDist && dist < nearerDist){
		     nearerDist = dist;
		     enGen=itgen->energy();
		     etaGen=itgen->eta();
		     ptGen=itgen->pt();
		     phiGen=itgen->phi();
		     checkNear=true;
		  }

	       } // end genParticle cycle
	       
	       if (doElectronsComparisonMC){
		  if (!checkPairing){  // check what fail for the association to gen level
		     if (dist > maxDist) h_failReason->Fill(1);
		     if (distEta > maxEta) h_failReason->Fill(2);
		     if (ratioEn > maxEn || 1./ratioEn > maxEn) h_failReason->Fill(3);
		     if (ratioEn2 > maxEn || 1./ratioEn2 > maxEn) h_failReason->Fill(4);
		  }
	       } // end doElectronsComparisonMC

	       if (checkNear){

		  if (doEfficiencies){
		     h_PairedMcGsfElectronsVsEn->Fill(it->energy(),myweight[0]);
		     h_PairedMcPfElectronsVsEn->Fill(itPf->energy(),myweight[0]);
		     h_PairedMcGsfElectronsVsEta->Fill(it->eta(),myweight[0]);
		     h_PairedMcPfElectronsVsEta->Fill(itPf->eta(),myweight[0]);
		  }

		  if (doElectronsComparisonMC){

		     if (it->superCluster().isNonnull() && it->pflowSuperCluster().isNonnull()){
			
			h_gsfMcGsfPhiVsVtxSc->Fill(numberOfVertices,(gsfScPhi-phiGen),myweight[0]);
			h_gsfMcGsfEtaVsVtxSc->Fill(numberOfVertices,(gsfScEta-etaGen),myweight[0]);
			h_gsfMcGsfEnVsVtxSc->Fill(numberOfVertices,(gsfScEn-enGen)/gsfScEn,myweight[0]);
			h_pfMcPfPhiVsVtxSc->Fill(numberOfVertices,(pfScPhi-phiGen),myweight[0]);
			h_pfMcPfEtaVsVtxSc->Fill(numberOfVertices,(pfScEta-etaGen),myweight[0]);
			h_pfMcPfEnVsVtxSc->Fill(numberOfVertices,(pfScEn-enGen)/pfScEn,myweight[0]);
			
			if (fabs(gsfScEta)<edgeEB){			   
			   h_gsfMcGsfPhiVsVtxEBSc->Fill(numberOfVertices,(gsfScPhi-phiGen),myweight[0]);
			   h_gsfMcGsfEtaVsVtxEBSc->Fill(numberOfVertices,(gsfScEta-etaGen),myweight[0]);
			   h_gsfMcGsfEnVsVtxEBSc->Fill(numberOfVertices,(gsfScEn-enGen)/gsfScEn,myweight[0]);
			   h_pfMcPfPhiVsVtxEBSc->Fill(numberOfVertices,(pfScPhi-phiGen),myweight[0]);
			   h_pfMcPfEtaVsVtxEBSc->Fill(numberOfVertices,(pfScEta-etaGen),myweight[0]);
			   h_pfMcPfEnVsVtxEBSc->Fill(numberOfVertices,(pfScEn-enGen)/pfScEn,myweight[0]);
			}else if (fabs(gsfScEta)<edgeEE){
			   h_gsfMcGsfPhiVsVtxEESc->Fill(numberOfVertices,(gsfScPhi-phiGen),myweight[0]);
			   h_gsfMcGsfEtaVsVtxEESc->Fill(numberOfVertices,(gsfScEta-etaGen),myweight[0]);
			   h_gsfMcGsfEnVsVtxEESc->Fill(numberOfVertices,(gsfScEn-enGen)/gsfScEn,myweight[0]);
			   h_pfMcPfPhiVsVtxEESc->Fill(numberOfVertices,(pfScPhi-phiGen),myweight[0]);
			   h_pfMcPfEtaVsVtxEESc->Fill(numberOfVertices,(pfScEta-etaGen),myweight[0]);
			   h_pfMcPfEnVsVtxEESc->Fill(numberOfVertices,(pfScEn-enGen)/pfScEn,myweight[0]);
			}

			h_gsfMcGsfEtaVsEtaSc->Fill(gsfScEta,(gsfScEta-etaGen), myweight[0]);
			h_gsfMcGsfEtaVsPhiSc->Fill(gsfScPhi,(gsfScEta-etaGen), myweight[0]);
			h_gsfMcGsfEtaVsEnSc->Fill(gsfScEn,(gsfScEta-etaGen), myweight[0]);
			h_pfMcPfEtaVsEtaSc->Fill(pfScEta,(pfScEta-etaGen), myweight[0]);
			h_pfMcPfEtaVsPhiSc->Fill(pfScPhi,(pfScEta-etaGen), myweight[0]);
			h_pfMcPfEtaVsEnSc->Fill(pfScEn,(pfScEta-etaGen), myweight[0]);

			h_gsfMcGsfPhiVsPhiSc->Fill(gsfScPhi,(gsfScPhi-phiGen), myweight[0]);
			h_gsfMcGsfPhiVsEtaSc->Fill(gsfScEta,(gsfScPhi-phiGen), myweight[0]);
			h_gsfMcGsfPhiVsEnSc->Fill(gsfScEn,(gsfScPhi-phiGen), myweight[0]);
			h_pfMcPfPhiVsPhiSc->Fill(pfScPhi,(pfScPhi-phiGen), myweight[0]);
			h_pfMcPfPhiVsEtaSc->Fill(pfScEta,(pfScPhi-phiGen), myweight[0]);
			h_pfMcPfPhiVsEnSc->Fill(pfScEn,(pfScPhi-phiGen), myweight[0]);

			h_gsfMcGsfEnVsEnSc->Fill(gsfScEn,(gsfScEn-enGen)/gsfScEn, myweight[0]);
			h_gsfMcGsfEnVsEtaSc->Fill(gsfScEta,(gsfScEn-enGen)/gsfScEn, myweight[0]);
			h_gsfMcGsfEnVsPhiSc->Fill(gsfScPhi,(gsfScEn-enGen)/gsfScEn, myweight[0]);
			h_pfMcPfEnVsEnSc->Fill(pfScEn,(pfScEn-enGen)/pfScEn, myweight[0]);
			h_pfMcPfEnVsEtaSc->Fill(pfScEta,(pfScEn-enGen)/pfScEn, myweight[0]);
			h_pfMcPfEnVsPhiSc->Fill(pfScPhi,(pfScEn-enGen)/pfScEn, myweight[0]);
		     }

		     h_MCenPFenVsEnENear->Fill(itPf->energy(),(itPf->energy()-enGen)/itPf->energy(), myweight[0]);
		     h_MCenPFenVsEtaENear->Fill(itPf->eta(),(itPf->energy()-enGen)/itPf->energy(), myweight[0]);
		     h_MCenGSFenVsEnENear->Fill(it->energy(),(it->energy()-enGen)/it->energy(), myweight[0]);  
		     h_MCenGSFenVsEtaENear->Fill(it->eta(),(it->energy()-enGen)/it->energy(), myweight[0]);

		     h_PFenMCenVsEnENear->Fill(itPf->energy(),itPf->energy()/enGen, myweight[0]);
		     h_PFenMCenVsEtaENear->Fill(itPf->eta(),itPf->energy()/enGen, myweight[0]);
		     h_GSFenMCenVsEnENear->Fill(it->energy(),it->energy()/enGen, myweight[0]);  
		     h_GSFenMCenVsEtaENear->Fill(it->eta(),it->energy()/enGen, myweight[0]);

		     h_PFenMCenVsMcEnENear->Fill(enGen,itPf->energy()/enGen, myweight[0]);
		     h_PFenMCenVsMcEtaENear->Fill(etaGen,itPf->energy()/enGen, myweight[0]);
		     h_GSFenMCenVsMcEnENear->Fill(enGen,it->energy()/enGen, myweight[0]);  
		     h_GSFenMCenVsMcEtaENear->Fill(etaGen,it->energy()/enGen, myweight[0]); 

		     h_gsfMcGsfPtVsVtx->Fill(numberOfVertices,(it->pt()-ptGen)/it->pt(),myweight[0]);
		     h_gsfMcGsfPhiVsVtx->Fill(numberOfVertices,(it->phi()-phiGen),myweight[0]);
		     h_gsfMcGsfEtaVsVtx->Fill(numberOfVertices,(it->eta()-etaGen),myweight[0]);
		     h_gsfMcGsfEnVsVtx->Fill(numberOfVertices,(it->energy()-enGen)/it->energy(),myweight[0]);
		     h_pfMcPfPtVsVtx->Fill(numberOfVertices,(itPf->pt()-ptGen)/itPf->pt(),myweight[0]);
		     h_pfMcPfPhiVsVtx->Fill(numberOfVertices,(itPf->phi()-phiGen),myweight[0]);
		     h_pfMcPfEtaVsVtx->Fill(numberOfVertices,(itPf->eta()-etaGen),myweight[0]);
		     h_pfMcPfEnVsVtx->Fill(numberOfVertices,(itPf->energy()-enGen)/itPf->energy(),myweight[0]);

		     h_gsfMcGsfPt->Fill((it->pt()-ptGen)/it->pt(),myweight[0]);
		     //h_gsfMcGsfEta->Fill((it->eta()-etaGen)/it->eta(),myweight[0]);
		     //h_gsfMcGsfPhi->Fill((it->phi()-phiGen)/it->phi(),myweight[0]);
		     h_gsfMcGsfEta->Fill((it->eta()-etaGen),myweight[0]);
		     h_gsfMcGsfPhi->Fill((it->phi()-phiGen),myweight[0]);
		     h_pfMcPfPt->Fill((itPf->pt()-ptGen)/itPf->pt(),myweight[0]);
		     //h_pfMcPfEta->Fill((itPf->eta()-etaGen)/itPf->eta(),myweight[0]);
		     //h_pfMcPfPhi->Fill((itPf->phi()-phiGen)/itPf->phi(),myweight[0]);
		     h_pfMcPfEta->Fill((itPf->eta()-etaGen),myweight[0]);
		     h_pfMcPfPhi->Fill((itPf->phi()-phiGen),myweight[0]);

		     h_gsfMcGsfPtVsPt->Fill(it->pt(),(it->pt()-ptGen)/it->pt(),myweight[0]);
		     //h_gsfMcGsfEtaVsEta->Fill(it->eta(),(it->eta()-etaGen)/it->eta(),myweight[0]);
		     //h_gsfMcGsfPhiVsPhi->Fill(it->phi(),(it->phi()-phiGen)/it->phi(),myweight[0]);
		     h_gsfMcGsfEtaVsEta->Fill(it->eta(),(it->eta()-etaGen),myweight[0]);
		     h_gsfMcGsfPhiVsPhi->Fill(it->phi(),(it->phi()-phiGen),myweight[0]);
		     h_pfMcPfPtVsPt->Fill(itPf->pt(),(itPf->pt()-ptGen)/itPf->pt(),myweight[0]);
		     //h_pfMcPfEtaVsEta->Fill(itPf->eta(),(itPf->eta()-etaGen)/itPf->eta(),myweight[0]);
		     //h_pfMcPfPhiVsPhi->Fill(itPf->phi(),(itPf->phi()-phiGen)/itPf->phi(),myweight[0]);
		     h_pfMcPfEtaVsEta->Fill(itPf->eta(),(itPf->eta()-etaGen),myweight[0]);
		     h_pfMcPfPhiVsPhi->Fill(itPf->phi(),(itPf->phi()-phiGen),myweight[0]);

		     h_gsfMcGsfPtVsEta->Fill(it->eta(),(it->pt()-ptGen)/it->pt(),myweight[0]);
		     h_gsfMcGsfPtVsPhi->Fill(it->phi(),(it->pt()-ptGen)/it->pt(),myweight[0]);
		     //h_gsfMcGsfEtaVsPt->Fill(it->pt(),(it->eta()-etaGen)/it->eta(),myweight[0]);
		     //h_gsfMcGsfEtaVsPhi->Fill(it->phi(),(it->eta()-etaGen)/it->eta(),myweight[0]);
		     //h_gsfMcGsfPhiVsEta->Fill(it->eta(),(it->phi()-phiGen)/it->phi(),myweight[0]);
		     //h_gsfMcGsfPhiVsPt->Fill(it->pt(),(it->phi()-phiGen)/it->phi(),myweight[0]);
		     h_gsfMcGsfEtaVsPt->Fill(it->pt(),(it->eta()-etaGen),myweight[0]);
		     h_gsfMcGsfEtaVsPhi->Fill(it->phi(),(it->eta()-etaGen),myweight[0]);
		     h_gsfMcGsfPhiVsEta->Fill(it->eta(),(it->phi()-phiGen),myweight[0]);
		     h_gsfMcGsfPhiVsPt->Fill(it->pt(),(it->phi()-phiGen),myweight[0]);
		     h_pfMcPfPtVsEta->Fill(itPf->eta(),(itPf->pt()-ptGen)/itPf->pt(),myweight[0]);
		     h_pfMcPfPtVsPhi->Fill(itPf->phi(),(itPf->pt()-ptGen)/itPf->pt(),myweight[0]);
		     //h_pfMcPfEtaVsPt->Fill(itPf->pt(),(itPf->eta()-etaGen)/itPf->eta(),myweight[0]);
		     //h_pfMcPfEtaVsPhi->Fill(itPf->phi(),(itPf->eta()-etaGen)/itPf->eta(),myweight[0]);
		     //h_pfMcPfPhiVsEta->Fill(itPf->eta(),(itPf->phi()-phiGen)/itPf->phi(),myweight[0]);
		     //h_pfMcPfPhiVsPt->Fill(itPf->pt(),(itPf->phi()-phiGen)/itPf->phi(),myweight[0]);
		     h_pfMcPfEtaVsPt->Fill(itPf->pt(),(itPf->eta()-etaGen),myweight[0]);
		     h_pfMcPfEtaVsPhi->Fill(itPf->phi(),(itPf->eta()-etaGen),myweight[0]);
		     h_pfMcPfPhiVsEta->Fill(itPf->eta(),(itPf->phi()-phiGen),myweight[0]);
		     h_pfMcPfPhiVsPt->Fill(itPf->pt(),(itPf->phi()-phiGen),myweight[0]);
		  }// end doElectronsComparison		  
		  
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
	 gsfScPhi= it->superCluster()->phi();
	 pfScEn  = it->pflowSuperCluster()->energy();
	 pfScEta= it->pflowSuperCluster()->eta();
	 pfScPhi= it->pflowSuperCluster()->phi();

	 h_gsfPfSCEtaVsEta->Fill(it->eta(),gsfScEta-pfScEta,myweight[0]);
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
	    h_gsfPfSCEta_EB->Fill(gsfScEta-pfScEta,myweight[0]);
	    h_gsfPfSCEn_EB->Fill(gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEnVsEn_EB->Fill(it->energy(),gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEtaVsEn_EB->Fill(it->energy(),gsfScEta-pfScEta,myweight[0]);
	 } else if (fabs(gsfScEta)<edgeEE){
	    h_gsfPfSCEta_EE->Fill(gsfScEta-pfScEta,myweight[0]);
	    h_gsfPfSCEn_EE->Fill(gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEnVsEn_EE->Fill(it->energy(),gsfScEn/pfScEn,myweight[0]);
	    h_gsfPfSCEtaVsEn_EE->Fill(it->energy(),gsfScEta-pfScEta,myweight[0]);
	 }     
      }      

      if (doEfficiencies){
	 h_totalGsfElectronsVsEn->Fill(it->energy(),myweight[0]);
	 h_totalGsfElectronsVsEta->Fill(it->eta(),myweight[0]);
      }

      for(reco::PFCandidateCollection::const_iterator itPf=pfElec->begin();itPf!=pfElec->end();itPf++){
	 if (itPf->gsfTrackRef()==it->gsfTrack()) {
	    pfSize++;
	    if (doEfficiencies){
	       h_PairedPfElectronsVsEn->Fill(it->energy(),myweight[0]);
	       h_PairedPfElectronsVsEta->Fill(it->eta(),myweight[0]);
	    }

	    h_ptPFptVsEta->Fill(it->eta(),it->energy()/itPf->energy(),myweight[0]);
	    h_ptPFptVsEn->Fill(it->energy(),it->energy()/itPf->energy(),myweight[0]);
	    double ratioPt =  (it->pt()-itPf->pt())/it->pt();
	    h_ptGsfPfGsfVsptGsf->Fill(it->pt(),ratioPt,myweight[0]);
	    pfe2.SetPtEtaPhiM(itPf->pt(),itPf->eta(),itPf->phi(),itPf->mass());
	    checkPf2=true;
	    
	    if (usingMC){
	       if (doEfficiencies){
		  h_totalGsfxMcElectronsVsEn->Fill(it->energy(),myweight[0]);
		  h_totalGsfxMcElectronsVsEta->Fill(it->eta(),myweight[0]);
		  h_totalPfxMcElectronsVsEn->Fill(itPf->energy(),myweight[0]);
		  h_totalPfxMcElectronsVsEta->Fill(itPf->eta(),myweight[0]);
	       }

	       for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
		  dist= sqrt( pow(itgen->eta()-it->eta(),2)+pow(itgen->phi()-it->phi(),2) );
		  distEta = fabs(itgen->eta() - it->eta());
		  ratioEn = itgen->energy()/it->energy();
		  ratioEn2 = itgen->energy()/itPf->energy();

		  if (doElectronsComparisonMC){
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
		  } //end doElectronsComparison

		  if ( fabs(itgen->pdgId())==11 && dist < maxDist && dist < nearerDist){
		     nearerDist = dist;
		     enGen=itgen->energy();
		     etaGen=itgen->eta();
		     ptGen=itgen->pt();
		     phiGen=itgen->phi();
		     checkNear=true;
		  }

	       } // end genParticle cycle
	       
	       if (doElectronsComparisonMC){
		  if (!checkPairing){  // check what fail for the association to gen level
		     if (dist > maxDist) h_failReason->Fill(1);
		     if (distEta > maxEta) h_failReason->Fill(2);
		     if (ratioEn > maxEn || 1./ratioEn > maxEn) h_failReason->Fill(3);
		     if (ratioEn2 > maxEn || 1./ratioEn2 > maxEn) h_failReason->Fill(4);
		  }
	       } // end doElectronsComparison

	       if (checkNear){

		  if (doEfficiencies){
		     h_PairedMcGsfElectronsVsEn->Fill(it->energy(),myweight[0]);
		     h_PairedMcPfElectronsVsEn->Fill(itPf->energy(),myweight[0]);
		     h_PairedMcGsfElectronsVsEta->Fill(it->eta(),myweight[0]);
		     h_PairedMcPfElectronsVsEta->Fill(itPf->eta(),myweight[0]);
		  }

		  if (doElectronsComparisonMC){

		      if (it->superCluster().isNonnull() && it->pflowSuperCluster().isNonnull()){
			
			h_gsfMcGsfPhiVsVtxSc->Fill(numberOfVertices,(gsfScPhi-phiGen),myweight[0]);
			h_gsfMcGsfEtaVsVtxSc->Fill(numberOfVertices,(gsfScEta-etaGen),myweight[0]);
			h_gsfMcGsfEnVsVtxSc->Fill(numberOfVertices,(gsfScEn-enGen)/gsfScEn,myweight[0]);
			h_pfMcPfPhiVsVtxSc->Fill(numberOfVertices,(pfScPhi-phiGen),myweight[0]);
			h_pfMcPfEtaVsVtxSc->Fill(numberOfVertices,(pfScEta-etaGen),myweight[0]);
			h_pfMcPfEnVsVtxSc->Fill(numberOfVertices,(pfScEn-enGen)/pfScEn,myweight[0]);

			if (fabs(gsfScEta)<edgeEB){			   
			   h_gsfMcGsfPhiVsVtxEBSc->Fill(numberOfVertices,(gsfScPhi-phiGen),myweight[0]);
			   h_gsfMcGsfEtaVsVtxEBSc->Fill(numberOfVertices,(gsfScEta-etaGen),myweight[0]);
			   h_gsfMcGsfEnVsVtxEBSc->Fill(numberOfVertices,(gsfScEn-enGen)/gsfScEn,myweight[0]);
			   h_pfMcPfPhiVsVtxEBSc->Fill(numberOfVertices,(pfScPhi-phiGen),myweight[0]);
			   h_pfMcPfEtaVsVtxEBSc->Fill(numberOfVertices,(pfScEta-etaGen),myweight[0]);
			   h_pfMcPfEnVsVtxEBSc->Fill(numberOfVertices,(pfScEn-enGen)/pfScEn,myweight[0]);
			}else if (fabs(gsfScEta)<edgeEE){
			   h_gsfMcGsfPhiVsVtxEESc->Fill(numberOfVertices,(gsfScPhi-phiGen),myweight[0]);
			   h_gsfMcGsfEtaVsVtxEESc->Fill(numberOfVertices,(gsfScEta-etaGen),myweight[0]);
			   h_gsfMcGsfEnVsVtxEESc->Fill(numberOfVertices,(gsfScEn-enGen)/gsfScEn,myweight[0]);
			   h_pfMcPfPhiVsVtxEESc->Fill(numberOfVertices,(pfScPhi-phiGen),myweight[0]);
			   h_pfMcPfEtaVsVtxEESc->Fill(numberOfVertices,(pfScEta-etaGen),myweight[0]);
			   h_pfMcPfEnVsVtxEESc->Fill(numberOfVertices,(pfScEn-enGen)/pfScEn,myweight[0]);
			}

			h_gsfMcGsfEtaVsEtaSc->Fill(gsfScEta,(gsfScEta-etaGen), myweight[0]);
			h_gsfMcGsfEtaVsPhiSc->Fill(gsfScPhi,(gsfScEta-etaGen), myweight[0]);
			h_gsfMcGsfEtaVsEnSc->Fill(gsfScEn,(gsfScEta-etaGen), myweight[0]);
			h_pfMcPfEtaVsEtaSc->Fill(pfScEta,(pfScEta-etaGen), myweight[0]);
			h_pfMcPfEtaVsPhiSc->Fill(pfScPhi,(pfScEta-etaGen), myweight[0]);
			h_pfMcPfEtaVsEnSc->Fill(pfScEn,(pfScEta-etaGen), myweight[0]);

			h_gsfMcGsfPhiVsPhiSc->Fill(gsfScPhi,(gsfScPhi-phiGen), myweight[0]);
			h_gsfMcGsfPhiVsEtaSc->Fill(gsfScEta,(gsfScPhi-phiGen), myweight[0]);
			h_gsfMcGsfPhiVsEnSc->Fill(gsfScEn,(gsfScPhi-phiGen), myweight[0]);
			h_pfMcPfPhiVsPhiSc->Fill(pfScPhi,(pfScPhi-phiGen), myweight[0]);
			h_pfMcPfPhiVsEtaSc->Fill(pfScEta,(pfScPhi-phiGen), myweight[0]);
			h_pfMcPfPhiVsEnSc->Fill(pfScEn,(pfScPhi-phiGen), myweight[0]);

			h_gsfMcGsfEnVsEnSc->Fill(gsfScEn,(gsfScEn-enGen)/gsfScEn, myweight[0]);
			h_gsfMcGsfEnVsEtaSc->Fill(gsfScEta,(gsfScEn-enGen)/gsfScEn, myweight[0]);
			h_gsfMcGsfEnVsPhiSc->Fill(gsfScPhi,(gsfScEn-enGen)/gsfScEn, myweight[0]);
			h_pfMcPfEnVsEnSc->Fill(pfScEn,(pfScEn-enGen)/pfScEn, myweight[0]);
			h_pfMcPfEnVsEtaSc->Fill(pfScEta,(pfScEn-enGen)/pfScEn, myweight[0]);
			h_pfMcPfEnVsPhiSc->Fill(pfScPhi,(pfScEn-enGen)/pfScEn, myweight[0]);
		     }

		     h_MCenPFenVsEnENear->Fill(itPf->energy(),(itPf->energy()-enGen)/itPf->energy(), myweight[0]);
		     h_MCenPFenVsEtaENear->Fill(itPf->eta(),(itPf->energy()-enGen)/itPf->energy(), myweight[0]);
		     h_MCenGSFenVsEnENear->Fill(it->energy(),(it->energy()-enGen)/it->energy(), myweight[0]);  
		     h_MCenGSFenVsEtaENear->Fill(it->eta(),(it->energy()-enGen)/it->energy(), myweight[0]); 

		     h_PFenMCenVsEnENear->Fill(itPf->energy(),itPf->energy()/enGen, myweight[0]);
		     h_PFenMCenVsEtaENear->Fill(itPf->eta(),itPf->energy()/enGen, myweight[0]);
		     h_GSFenMCenVsEnENear->Fill(it->energy(),it->energy()/enGen, myweight[0]);  
		     h_GSFenMCenVsEtaENear->Fill(it->eta(),it->energy()/enGen, myweight[0]);

		     h_PFenMCenVsMcEnENear->Fill(enGen,itPf->energy()/enGen, myweight[0]);
		     h_PFenMCenVsMcEtaENear->Fill(etaGen,itPf->energy()/enGen, myweight[0]);
		     h_GSFenMCenVsMcEnENear->Fill(enGen,it->energy()/enGen, myweight[0]);  
		     h_GSFenMCenVsMcEtaENear->Fill(etaGen,it->energy()/enGen, myweight[0]);
		     
		     h_gsfMcGsfPtVsVtx->Fill(numberOfVertices,(it->pt()-ptGen)/it->pt(),myweight[0]);
		     h_gsfMcGsfPhiVsVtx->Fill(numberOfVertices,(it->phi()-phiGen),myweight[0]);
		     h_gsfMcGsfEtaVsVtx->Fill(numberOfVertices,(it->eta()-etaGen),myweight[0]);
		     h_gsfMcGsfEnVsVtx->Fill(numberOfVertices,(it->energy()-enGen)/it->energy(),myweight[0]);
		     h_pfMcPfPtVsVtx->Fill(numberOfVertices,(itPf->pt()-ptGen)/itPf->pt(),myweight[0]);
		     h_pfMcPfPhiVsVtx->Fill(numberOfVertices,(itPf->phi()-phiGen),myweight[0]);
		     h_pfMcPfEtaVsVtx->Fill(numberOfVertices,(itPf->eta()-etaGen),myweight[0]);
		     h_pfMcPfEnVsVtx->Fill(numberOfVertices,(itPf->energy()-enGen)/itPf->energy(),myweight[0]);

		     h_gsfMcGsfPt->Fill((it->pt()-ptGen)/it->pt(),myweight[0]);
		     //h_gsfMcGsfEta->Fill((it->eta()-etaGen)/it->eta(),myweight[0]);
		     //h_gsfMcGsfPhi->Fill((it->phi()-phiGen)/it->phi(),myweight[0]);
		     h_gsfMcGsfEta->Fill((it->eta()-etaGen),myweight[0]);
		     h_gsfMcGsfPhi->Fill((it->phi()-phiGen),myweight[0]);
		     h_pfMcPfPt->Fill((itPf->pt()-ptGen)/itPf->pt(),myweight[0]);
		     //h_pfMcPfEta->Fill((itPf->eta()-etaGen)/itPf->eta(),myweight[0]);
		     //h_pfMcPfPhi->Fill((itPf->phi()-phiGen)/itPf->phi(),myweight[0]);
		     h_pfMcPfEta->Fill((itPf->eta()-etaGen),myweight[0]);
		     h_pfMcPfPhi->Fill((itPf->phi()-phiGen),myweight[0]);

		     h_gsfMcGsfPtVsPt->Fill(it->pt(),(it->pt()-ptGen)/it->pt(),myweight[0]);
		     //h_gsfMcGsfEtaVsEta->Fill(it->eta(),(it->eta()-etaGen)/it->eta(),myweight[0]);
		     //h_gsfMcGsfPhiVsPhi->Fill(it->phi(),(it->phi()-phiGen)/it->phi(),myweight[0]);
		     h_gsfMcGsfEtaVsEta->Fill(it->eta(),(it->eta()-etaGen),myweight[0]);
		     h_gsfMcGsfPhiVsPhi->Fill(it->phi(),(it->phi()-phiGen),myweight[0]);
		     h_pfMcPfPtVsPt->Fill(itPf->pt(),(itPf->pt()-ptGen)/itPf->pt(),myweight[0]);
		     //h_pfMcPfEtaVsEta->Fill(itPf->eta(),(itPf->eta()-etaGen)/itPf->eta(),myweight[0]);
		     //h_pfMcPfPhiVsPhi->Fill(itPf->phi(),(itPf->phi()-phiGen)/itPf->phi(),myweight[0]);
		     h_pfMcPfEtaVsEta->Fill(itPf->eta(),(itPf->eta()-etaGen),myweight[0]);
		     h_pfMcPfPhiVsPhi->Fill(itPf->phi(),(itPf->phi()-phiGen),myweight[0]);

		     h_gsfMcGsfPtVsEta->Fill(it->eta(),(it->pt()-ptGen)/it->pt(),myweight[0]);
		     h_gsfMcGsfPtVsPhi->Fill(it->phi(),(it->pt()-ptGen)/it->pt(),myweight[0]);
		     //h_gsfMcGsfEtaVsPt->Fill(it->pt(),(it->eta()-etaGen)/it->eta(),myweight[0]);
		     //h_gsfMcGsfEtaVsPhi->Fill(it->phi(),(it->eta()-etaGen)/it->eta(),myweight[0]);
		     //h_gsfMcGsfPhiVsEta->Fill(it->eta(),(it->phi()-phiGen)/it->phi(),myweight[0]);
		     //h_gsfMcGsfPhiVsPt->Fill(it->pt(),(it->phi()-phiGen)/it->phi(),myweight[0]);
		     h_gsfMcGsfEtaVsPt->Fill(it->pt(),(it->eta()-etaGen),myweight[0]);
		     h_gsfMcGsfEtaVsPhi->Fill(it->phi(),(it->eta()-etaGen),myweight[0]);
		     h_gsfMcGsfPhiVsEta->Fill(it->eta(),(it->phi()-phiGen),myweight[0]);
		     h_gsfMcGsfPhiVsPt->Fill(it->pt(),(it->phi()-phiGen),myweight[0]);
		     h_pfMcPfPtVsEta->Fill(itPf->eta(),(itPf->pt()-ptGen)/itPf->pt(),myweight[0]);
		     h_pfMcPfPtVsPhi->Fill(itPf->phi(),(itPf->pt()-ptGen)/itPf->pt(),myweight[0]);
		     //h_pfMcPfEtaVsPt->Fill(itPf->pt(),(itPf->eta()-etaGen)/itPf->eta(),myweight[0]);
		     //h_pfMcPfEtaVsPhi->Fill(itPf->phi(),(itPf->eta()-etaGen)/itPf->eta(),myweight[0]);
		     //h_pfMcPfPhiVsEta->Fill(itPf->eta(),(itPf->phi()-phiGen)/itPf->phi(),myweight[0]);
		     //h_pfMcPfPhiVsPt->Fill(itPf->pt(),(itPf->phi()-phiGen)/itPf->phi(),myweight[0]);
		     h_pfMcPfEtaVsPt->Fill(itPf->pt(),(itPf->eta()-etaGen),myweight[0]);
		     h_pfMcPfEtaVsPhi->Fill(itPf->phi(),(itPf->eta()-etaGen),myweight[0]);
		     h_pfMcPfPhiVsEta->Fill(itPf->eta(),(itPf->phi()-phiGen),myweight[0]);
		     h_pfMcPfPhiVsPt->Fill(itPf->pt(),(itPf->phi()-phiGen),myweight[0]);
		  }// end doElectronsComparison
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
		&& fabs(jet->eta())<2.4
		&& jet->chargedEmEnergyFraction()<0.99
		&& jet->neutralHadronEnergyFraction()<0.99
		&& jet->neutralEmEnergyFraction()<0.99
		&& jet->chargedHadronEnergyFraction()>0
		&& jet->chargedMultiplicity()>0
	       ){ 
	       JetContainer.push_back(jet->p4()); 
	    }
	 }
         std::stable_sort(JetContainer.begin(),JetContainer.end(),GreaterPt()); 
      }
      else{cout<<"No valid Jets Collection"<<endl;}
 
//------------------------------------------------------------------------------------------------- 
// study in the cone around the electrons *********************************************************
//------------------------------------------------------------------------------------------------- 
      
      for (reco::PFCandidateCollection::const_iterator pfCand = pfPart->begin();
	   pfCand != pfPart->end(); pfCand++)
      {
	 double deltaR1= sqrt( pow(pfCand->eta()-e1.Eta(),2)+pow(pfCand->phi()-e1.Phi(),2) );
	 double deltaR2= sqrt( pow(pfCand->eta()-e2.Eta(),2)+pow(pfCand->phi()-e2.Phi(),2) );	   
	 
	 if (deltaR1 > deltaConeGen && deltaR2 > deltaConeGen ){
	    h_pfIdPdgAroundE->Fill(pfCand->particleId(),myweight[0]);
	 }
	 
      }
      
      if (usingMC){
	 
	 if (doElectronsComparisonMC){
	    for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();
		itgen!=genPart->end();itgen++)
	    {
	       double deltaR1= sqrt( pow(itgen->eta()-e1.Eta(),2)+pow(itgen->phi()-e1.Phi(),2) );
	       double deltaR2= sqrt( pow(itgen->eta()-e2.Eta(),2)+pow(itgen->phi()-e2.Phi(),2) );	   
	       
	       if (deltaR1 > deltaConeGen && deltaR2 > deltaConeGen ){
		  if (itgen->status() ==1) h_idPdgAroundE->Fill(fabs(itgen->pdgId()),myweight[0]);
	       }
	    }
	 }
      }

//------------------------------------------------------------------------------------------------- 
// study on  R E J E C T E D  jets ****************************************************************
//------------------------------------------------------------------------------------------------- 
      if (doPlotsJetComposition){
	 double jetEn,jetEta;
	 int sizeRJ=0;
	 bool ckElInJet = true;
	 for (reco::PFJetCollection::const_iterator jet = pfJets->begin(); 
	      jet != pfJets->end(); jet++) {
	 
	    double deltaR1= sqrt( pow(jet->eta()-e1.Eta(),2)+pow(jet->phi()-e1.Phi(),2) );
	    double deltaR2= sqrt( pow(jet->eta()-e2.Eta(),2)+pow(jet->phi()-e2.Phi(),2) );
	    double totEnergy=0.;
	    //double totPt=0.;
	    if (useCkElInJet ){
	       ckElInJet = false;
	       if (jet->electronMultiplicity()>=1){
		  if (!ckElInJet && 
		      ( fabs(jet->electronEnergy()-pfe1.Energy())<0.01 
			|| fabs(jet->electronEnergy() -pfe2.Energy())<0.01) ) {
		     ckElInJet = true;
		  }
		  std::vector<reco::PFCandidatePtr> particles = jet->getPFConstituents();
		  for ( UInt_t j=0;j<particles.size(); j++){		  
		     totEnergy = totEnergy + particles[j]->p4().energy();
		  }
	       }
	    }
	    if ((deltaR1 < deltaRCone || deltaR2 < deltaRCone)&& jet->pt()>30 && ckElInJet
	       ){	    
	       h_totEnergy->Fill(totEnergy/jet->energy(),myweight[0]);
	       //h_totPt->Fill(totPt/jet->pt(),myweight[0]);

	       sizeRJ++;
	       h_nConstituents->Fill(jet->nConstituents(),myweight[0]);
	       h_rJetPt->Fill(jet->pt(),myweight[0]);
	       h_rJetEta->Fill(jet->eta(),myweight[0]);
	    
	       double chHE = jet->chargedHadronEnergy();
	       double nHE  = jet->neutralHadronEnergy();
	       double phE  = jet->photonEnergy();
	       double elE  = jet->electronEnergy();
	       double muE  = jet->muonEnergy();
	       double hfHE = jet->HFHadronEnergy();
	       double hfEmE= jet->HFEMEnergy();
	       double totCkE= chHE + nHE + phE + elE + muE + hfHE + hfEmE;
	    
	       h_energyFraction->Fill(0.5, totCkE/jet->energy(),myweight[0]);
	       h_energyFraction->Fill(1.5, chHE/totCkE,myweight[0]);
	       h_energyFraction->Fill(2.5, nHE/totCkE,myweight[0]);
	       h_energyFraction->Fill(3.5, phE/totCkE,myweight[0]);
	       h_energyFraction->Fill(4.5, elE/totCkE,myweight[0]);
	       h_energyFraction->Fill(5.5, muE/totCkE,myweight[0]);
	       h_energyFraction->Fill(6.5, hfHE/totCkE,myweight[0]);
	       h_energyFraction->Fill(7.5, hfEmE/totCkE,myweight[0]);
	    
	       double chHM = jet->chargedHadronMultiplicity();
	       double nHM  = jet->neutralHadronMultiplicity();
	       double phM  = jet->photonMultiplicity();
	       double elM  = jet->electronMultiplicity();
	       double muM  = jet->muonMultiplicity();
	       double hfHM = jet->HFHadronMultiplicity();
	       double hfEmM= jet->HFEMMultiplicity();
	       h_jetConstMult->Fill(0.5, jet->nConstituents(),myweight[0]);
	       h_jetConstMult->Fill(1.5, chHM,myweight[0]);
	       h_jetConstMult->Fill(2.5, nHM,myweight[0]);
	       h_jetConstMult->Fill(3.5, phM,myweight[0]);
	       h_jetConstMult->Fill(4.5, elM,myweight[0]);
	       h_jetConstMult->Fill(5.5, muM,myweight[0]);
	       h_jetConstMult->Fill(6.5, hfHM,myweight[0]);
	       h_jetConstMult->Fill(7.5, hfEmM,myweight[0]);

	       double totCk= chHM + nHM + phM + elM + muM + hfHM + hfEmM;	
	       //cout << "chMul = "<< chHM <<" ; nMul = "<<nHM<<
	       //   " ; phMul = "<< phM<< " ; elMul = "<< elM<<
	       //   " ; muMul = "<< muM<<" ; HFHM = "<<hfHM<<" ; HFEmM = "<<hfEmM<< endl;
	       h_multFraction->Fill(0.5, totCk/jet->nConstituents(),myweight[0]);
	       h_multFraction->Fill(1.5, chHM/jet->nConstituents(),myweight[0]);
	       h_multFraction->Fill(2.5, nHM/jet->nConstituents(),myweight[0]);
	       h_multFraction->Fill(3.5, phM/jet->nConstituents(),myweight[0]);
	       h_multFraction->Fill(4.5, elM/jet->nConstituents(),myweight[0]);
	       h_multFraction->Fill(5.5, muM/jet->nConstituents(),myweight[0]);
	       h_multFraction->Fill(6.5, hfHM/jet->nConstituents(),myweight[0]);
	       h_multFraction->Fill(7.5, hfEmM/jet->nConstituents(),myweight[0]);

	       h_chMultiplicity->Fill(chHM, myweight[0]);
	       h_nMultiplicity->Fill(nHM, myweight[0]);
	       h_phMultiplicity->Fill(phM, myweight[0]);
	       h_elMultiplicity->Fill(elM, myweight[0]);
	       h_muMultiplicity->Fill(muM, myweight[0]);
	       h_hfHMultiplicity->Fill(hfHM, myweight[0]);
	       h_hfEmMultiplicity->Fill(hfEmM, myweight[0]);
	       h_chMultFraction->Fill(chHM/jet->nConstituents(), myweight[0]);
	       h_nMultFraction->Fill(nHM/jet->nConstituents(), myweight[0]);
	       h_phMultFraction->Fill(phM/jet->nConstituents(), myweight[0]);
	       h_elMultFraction->Fill(elM/jet->nConstituents(), myweight[0]);
	       h_muMultFraction->Fill(muM/jet->nConstituents(), myweight[0]);
	       h_hfHMultFraction->Fill(hfHM/jet->nConstituents(), myweight[0]);
	       h_hfEmMultFraction->Fill(hfEmM/jet->nConstituents(), myweight[0]);
	       h_chEnerFraction->Fill(chHE/totCkE, myweight[0]);
	       h_nEnerFraction->Fill(nHE/totCkE, myweight[0]);
	       h_phEnerFraction->Fill(phE/totCkE, myweight[0]);
	       h_elEnerFraction->Fill(elE/totCkE, myweight[0]);
	       h_muEnerFraction->Fill(muE/totCkE, myweight[0]);
	       h_hfHEnerFraction->Fill(hfHE/totCkE, myweight[0]);
	       h_hfEmEnerFraction->Fill(hfEmE/totCkE, myweight[0]);
	    
	       double etaStep = 0.05, ptStep = 2.0;
	    
	       for (int k=0; k< 100; k++){

		  if (jet->pt()> k*ptStep && jet->pt()<= (k+1)*ptStep){
		     double meanPt = (k+0.5)*ptStep;
		     h_chMultiplicityVsPt->Fill(meanPt,chHM, myweight[0]);
		     h_nMultiplicityVsPt->Fill(meanPt,nHM, myweight[0]);
		     h_phMultiplicityVsPt->Fill(meanPt,phM, myweight[0]);
		     h_elMultiplicityVsPt->Fill(meanPt,elM, myweight[0]);
		     h_muMultiplicityVsPt->Fill(meanPt,muM, myweight[0]);
		     h_hfHMultiplicityVsPt->Fill(meanPt,hfHM, myweight[0]);
		     h_hfEmMultiplicityVsPt->Fill(meanPt,hfEmM, myweight[0]);
		     h_chMultFractionVsPt->Fill(meanPt,chHM/jet->nConstituents(), myweight[0]);
		     h_nMultFractionVsPt->Fill(meanPt,nHM/jet->nConstituents(), myweight[0]);
		     h_phMultFractionVsPt->Fill(meanPt,phM/jet->nConstituents(), myweight[0]);
		     h_elMultFractionVsPt->Fill(meanPt,elM/jet->nConstituents(), myweight[0]);
		     h_muMultFractionVsPt->Fill(meanPt,muM/jet->nConstituents(), myweight[0]);
		     h_hfHMultFractionVsPt->Fill(meanPt,hfHM/jet->nConstituents(), myweight[0]);
		     h_hfEmMultFractionVsPt->Fill(meanPt,hfEmM/jet->nConstituents(), myweight[0]);
		     h_chEnerFractionVsPt->Fill(meanPt,chHE/totCkE, myweight[0]);
		     h_nEnerFractionVsPt->Fill(meanPt,nHE/totCkE, myweight[0]);
		     h_phEnerFractionVsPt->Fill(meanPt,phE/totCkE, myweight[0]);
		     h_elEnerFractionVsPt->Fill(meanPt,elE/totCkE, myweight[0]);
		     h_muEnerFractionVsPt->Fill(meanPt,muE/totCkE, myweight[0]);
		     h_hfHEnerFractionVsPt->Fill(meanPt,hfHE/totCkE, myweight[0]);
		     h_hfEmEnerFractionVsPt->Fill(meanPt,hfEmE/totCkE, myweight[0]);
		  }
		  if ((jet->eta()+2.5)> k*etaStep && (jet->eta()+2.5)<= (k+1)*etaStep){
		     double meanEta = (k+0.5)*etaStep -2.5;
		     h_chMultiplicityVsEta->Fill(meanEta,chHM, myweight[0]);
		     h_nMultiplicityVsEta->Fill(meanEta,nHM, myweight[0]);
		     h_phMultiplicityVsEta->Fill(meanEta,phM, myweight[0]);
		     h_elMultiplicityVsEta->Fill(meanEta,elM, myweight[0]);
		     h_muMultiplicityVsEta->Fill(meanEta,muM, myweight[0]);
		     h_hfHMultiplicityVsEta->Fill(meanEta,hfHM, myweight[0]);
		     h_hfEmMultiplicityVsEta->Fill(meanEta,hfEmM, myweight[0]);
		     h_chMultFractionVsEta->Fill(meanEta,chHM/jet->nConstituents(), myweight[0]);
		     h_nMultFractionVsEta->Fill(meanEta,nHM/jet->nConstituents(), myweight[0]);
		     h_phMultFractionVsEta->Fill(meanEta,phM/jet->nConstituents(), myweight[0]);
		     h_elMultFractionVsEta->Fill(meanEta,elM/jet->nConstituents(), myweight[0]);
		     h_muMultFractionVsEta->Fill(meanEta,muM/jet->nConstituents(), myweight[0]);
		     h_hfHMultFractionVsEta->Fill(meanEta,hfHM/jet->nConstituents(), myweight[0]);
		     h_hfEmMultFractionVsEta->Fill(meanEta,hfEmM/jet->nConstituents(), myweight[0]);
		     h_chEnerFractionVsEta->Fill(meanEta,chHE/totCkE, myweight[0]);
		     h_nEnerFractionVsEta->Fill(meanEta,nHE/totCkE, myweight[0]);
		     h_phEnerFractionVsEta->Fill(meanEta,phE/totCkE, myweight[0]);
		     h_elEnerFractionVsEta->Fill(meanEta,elE/totCkE, myweight[0]);
		     h_muEnerFractionVsEta->Fill(meanEta,muE/totCkE, myweight[0]);
		     h_hfHEnerFractionVsEta->Fill(meanEta,hfHE/totCkE, myweight[0]);
		     h_hfEmEnerFractionVsEta->Fill(meanEta,hfEmE/totCkE, myweight[0]);
		  }

	       }
	    
	       if (usingMC){
		  nearerDist= 999;
		  checkNear=false;
		  int pdgValue=0;
		  for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();
		      itgen!=genPart->end();itgen++)
		  {
		     dist= sqrt( pow(itgen->eta()-jet->eta(),2)+pow(itgen->phi()-jet->phi(),2) );
		     if (dist < maxDist && dist < nearerDist){
			nearerDist = dist;
			pdgValue= itgen->pdgId();
			jetEn=itgen->pt();
			jetEta=itgen->eta();
			checkNear=true;
		     }	       
		  } // end genParticle
		  if (checkNear)
		  {
		     h_idPdgJet->Fill(fabs(pdgValue),myweight[0]);
		  }
	       } // end UsingMC
	    } // end if rejected jets
	 }

      
	 h_sizeJetRejected->Fill(sizeRJ,myweight[0]);
      }
//------------------------------------------------------------------------------------------------- 
// study on  P A S S I N G  jets *************************************************************************
//-------------------------------------------------------------------------------------------------
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

      //////////////////
      //Filling the Unfolding rootuple!
      //////////////////
      Jet_multiplicity=totJets;
      Z_y=e_pair.Rapidity();
      Z_pt=zPt;

      Jet_multiplicity_gen=-9999;
      Z_y_gen=-9999;
      Z_pt_gen=-9999;

      //bUILDING THE Z GEN BOSON

      if (usingMC){
	TLorentzVector Z_gen,ele_gen;
	std::vector <TLorentzVector> ele_gen_vec ;
	for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
	  if (itgen->pdgId()==23 && itgen->status()==2){ // itgen->status()==1 &&   
	    if (Debug) cout<<"(GEN) Z boson"<<endl;
	    Z_gen.SetPxPyPzE(itgen->px(),itgen->py(),itgen->pz(),itgen->energy()); 
	  }
	  if (fabs(itgen->pdgId())==11 && itgen->mother()->pdgId()==23){ //itgen->status()==1 && 
	    ele_gen.SetPxPyPzE(itgen->px(),itgen->py(),itgen->pz(),itgen->energy()); 
	    ele_gen_vec.push_back(ele_gen);
	  }
	}
	if (Z_gen.Pt()<7000) Z_pt_gen=Z_gen.Pt();
	if (Z_gen.Rapidity()<7000) Z_y_gen=Z_gen.Rapidity();
	if (Debug) cout<<"Z pt (GEN) is "<<Z_pt_gen<<" and y is "<<Z_y_gen<<endl;
	
	int numbOfJets=0;      
	//Number of GenJet
	edm::Handle<reco::GenJetCollection> genJets;
	iEvent.getByLabel(genJetsCollection, genJets );
	
	for (reco::GenJetCollection::const_iterator iter=genJets->begin();iter!=genJets->end();++iter){
	  if (ele_gen_vec.size()==2){  // Only jets reaching the detector are allowed...
	    // check if the jet is equal to one of the isolated electrons
	    //spacchetto
	    std::vector<edm::Ptr<reco::Candidate> > particles = iter->getJetConstituents();
	    for (UInt_t j=0; j<particles.size(); j++){
	      if (Debug) cout<<"jet constituent status is ->"<<particles[j]->status()<<" and pt is->"<<particles[j]->pt()<<endl; }
	    double ptgen = (*iter).pt();
	    double etagen = (*iter).eta();
	    double phigen = (*iter).phi();
	    double deltaR1= sqrt( pow(etagen-ele_gen_vec[0].Eta(),2)+pow(phigen-ele_gen_vec[0].Phi(),2) );
	    double deltaR2= sqrt( pow(etagen-ele_gen_vec[1].Eta(),2)+pow(phigen-ele_gen_vec[1].Phi(),2) );
	    if (Debug) cout<<"ptgen "<<ptgen<<" etagen "<<etagen<<" deltaR1 "<<deltaR1<<" deltaR2 "<<deltaR2<<" phigen "<<phigen<<endl;
	    if (deltaR1 > deltaRCone && deltaR2 > deltaRCone && ptgen>30
		//aggiungi
		){ 
	      numbOfJets++;
	    }
	  }
	}
	if (Debug) cout<<"Jet Multiplicity (GEN) "<<numbOfJets<<endl;
	if (numbOfJets<100) Jet_multiplicity_gen=numbOfJets;
      }
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
	h_zEtaNjet0->Fill(e_pair.Eta(),myweight[0]);
	h_zMassNjet0->Fill(zInvMass,myweight[0]);
	h_zMassMinusPdgGsfNjet0->Fill(zInvMass-zMassPdg,myweight[0]);
	if (checkPf1 && checkPf2) h_zMassMinusPdgPfNjet0->Fill(pfe_pair.M()-zMassPdg,myweight[0]);
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
      

   } //else {std::cout << "WARNING: More than two electron selected"<< std::endl;}

   //Fill Unfolding rootuple!
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
  treeUN_->Branch("Z_pt_gen",&Z_pt_gen);
  treeUN_->Branch("Z_y_gen",&Z_y_gen);
  treeUN_->Branch("Jet_multiplicity_gen",&Jet_multiplicity_gen);


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
 h_totalGsfElectronsVsEn->GetXaxis()->SetTitle("GSFelectron energy");
 h_totalGsfElectronsVsEn->GetYaxis()->SetTitle("N_{electrons}");
 h_PairedPfElectronsVsEn->GetXaxis()->SetTitle("PFelectron energy");
 h_PairedPfElectronsVsEn->GetYaxis()->SetTitle("N_{electrons}");
 h_totalGsfElectronsVsEta->GetXaxis()->SetTitle("GSFelectron eta");
 h_totalGsfElectronsVsEta->GetYaxis()->SetTitle("N_{electrons}");
 h_PairedPfElectronsVsEta->GetXaxis()->SetTitle("PFelectron eta");
 h_PairedPfElectronsVsEta->GetYaxis()->SetTitle("N_{electrons}");

 if (doPlotsJetComposition){
    h_sizeJetRejected->GetXaxis()->SetTitle("N_{jets}"); 
    h_sizeJetRejected->GetYaxis()->SetTitle("N_{events}");
    h_nConstituents->GetXaxis()->SetTitle("N_{constituents}");
    h_nConstituents->GetYaxis()->SetTitle("N_{events}");
    h_rJetPt->GetXaxis()->SetTitle("p_T^{jets}");
    h_rJetPt->GetYaxis()->SetTitle("N_{jets}");
    h_rJetEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_rJetEta->GetYaxis()->SetTitle("N_{jets}");
    h_totEnergy->GetXaxis()->SetTitle("E_{constituents}/E_{jets}");
    h_totEnergy->GetYaxis()->SetTitle("N_{jets}");
    h_energyFraction->GetXaxis()->SetTitle("constituent type");
    h_energyFraction->GetYaxis()->SetTitle("Fraction");
    h_jetConstMult->GetXaxis()->SetTitle("constituent type");
    h_jetConstMult->GetYaxis()->SetTitle("N_{jets}");
    h_multFraction->GetXaxis()->SetTitle("constituent type");
    h_multFraction->GetYaxis()->SetTitle("Fraction");
    h_chMultiplicity->GetXaxis()->SetTitle("N_{constituents}");
    h_chMultiplicity->GetYaxis()->SetTitle("N_{jets}");
    h_nMultiplicity->GetXaxis()->SetTitle("N_{constituents}");
    h_nMultiplicity->GetYaxis()->SetTitle("N_{jets}");
    h_phMultiplicity->GetXaxis()->SetTitle("N_{constituents}");
    h_phMultiplicity->GetYaxis()->SetTitle("N_{jets}");
    h_elMultiplicity->GetXaxis()->SetTitle("N_{constituents}");
    h_elMultiplicity->GetYaxis()->SetTitle("N_{jets}");
    h_muMultiplicity->GetXaxis()->SetTitle("N_{constituents}");
    h_muMultiplicity->GetYaxis()->SetTitle("N_{jets}");
    h_hfHMultiplicity->GetXaxis()->SetTitle("N_{constituents}");
    h_hfHMultiplicity->GetYaxis()->SetTitle("N_{jets}");
    h_hfEmMultiplicity->GetXaxis()->SetTitle("N_{constituents}");
    h_hfEmMultiplicity->GetYaxis()->SetTitle("N_{jets}");
    h_chMultFraction->GetXaxis()->SetTitle("multiplicity Fraction");
    h_chMultFraction->GetYaxis()->SetTitle("N_{jets}");
    h_nMultFraction->GetXaxis()->SetTitle("multiplicity Fraction");
    h_nMultFraction->GetYaxis()->SetTitle("N_{jets}");
    h_phMultFraction->GetXaxis()->SetTitle("multiplicity Fraction");
    h_phMultFraction->GetYaxis()->SetTitle("N_{jets}");
    h_elMultFraction->GetXaxis()->SetTitle("multiplicity Fraction");
    h_elMultFraction->GetYaxis()->SetTitle("N_{jets}");
    h_muMultFraction->GetXaxis()->SetTitle("multiplicity Fraction");
    h_muMultFraction->GetYaxis()->SetTitle("N_{jets}");
    h_hfHMultFraction->GetXaxis()->SetTitle("multiplicity Fraction");
    h_hfHMultFraction->GetYaxis()->SetTitle("N_{jets}");
    h_hfEmMultFraction->GetXaxis()->SetTitle("multiplicity Fraction");
    h_hfEmMultFraction->GetYaxis()->SetTitle("N_{jets}");
    h_chEnerFraction->GetXaxis()->SetTitle("Energy Fraction");
    h_chEnerFraction->GetYaxis()->SetTitle("N_{jets}");
    h_nEnerFraction->GetXaxis()->SetTitle("Energy Fraction");
    h_nEnerFraction->GetYaxis()->SetTitle("N_{jets}");
    h_phEnerFraction->GetXaxis()->SetTitle("Energy Fraction");
    h_phEnerFraction->GetYaxis()->SetTitle("N_{jets}");
    h_elEnerFraction->GetXaxis()->SetTitle("Energy Fraction");
    h_elEnerFraction->GetYaxis()->SetTitle("N_{jets}");
    h_muEnerFraction->GetXaxis()->SetTitle("Energy Fraction");
    h_muEnerFraction->GetYaxis()->SetTitle("N_{jets}");
    h_hfHEnerFraction->GetXaxis()->SetTitle("Energy Fraction");
    h_hfHEnerFraction->GetYaxis()->SetTitle("N_{jets}");
    h_hfEmEnerFraction->GetXaxis()->SetTitle("Energy Fraction");
    h_hfEmEnerFraction->GetYaxis()->SetTitle("N_{jets}");

    h_chMultiplicityVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_chMultiplicityVsPt->GetYaxis()->SetTitle("N_{constituents}");
    h_nMultiplicityVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_nMultiplicityVsPt->GetYaxis()->SetTitle("N_{constituents}");
    h_phMultiplicityVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_phMultiplicityVsPt->GetYaxis()->SetTitle("N_{constituents}");
    h_elMultiplicityVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_elMultiplicityVsPt->GetYaxis()->SetTitle("N_{constituents}");
    h_muMultiplicityVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_muMultiplicityVsPt->GetYaxis()->SetTitle("N_{constituents}");
    h_hfHMultiplicityVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_hfHMultiplicityVsPt->GetYaxis()->SetTitle("N_{constituents}");
    h_hfEmMultiplicityVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_hfEmMultiplicityVsPt->GetYaxis()->SetTitle("N_{constituents}");
    h_chMultFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_chMultFractionVsPt->GetYaxis()->SetTitle("multiplicity Fraction");
    h_nMultFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_nMultFractionVsPt->GetYaxis()->SetTitle("multiplicity Fraction");
    h_phMultFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_phMultFractionVsPt->GetYaxis()->SetTitle("multiplicity Fraction");
    h_elMultFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_elMultFractionVsPt->GetYaxis()->SetTitle("multiplicity Fraction");
    h_muMultFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_muMultFractionVsPt->GetYaxis()->SetTitle("multiplicity Fraction");
    h_hfHMultFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_hfHMultFractionVsPt->GetYaxis()->SetTitle("multiplicity Fraction");
    h_hfEmMultFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_hfEmMultFractionVsPt->GetYaxis()->SetTitle("multiplicity Fraction");
    h_chEnerFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_chEnerFractionVsPt->GetYaxis()->SetTitle("Energy Fraction");
    h_nEnerFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_nEnerFractionVsPt->GetYaxis()->SetTitle("Energy Fraction");
    h_phEnerFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_phEnerFractionVsPt->GetYaxis()->SetTitle("Energy Fraction");
    h_elEnerFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_elEnerFractionVsPt->GetYaxis()->SetTitle("Energy Fraction");
    h_muEnerFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_muEnerFractionVsPt->GetYaxis()->SetTitle("Energy Fraction");
    h_hfHEnerFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_hfHEnerFractionVsPt->GetYaxis()->SetTitle("Energy Fraction");
    h_hfEmEnerFractionVsPt->GetXaxis()->SetTitle("p_{T}^{jets}");
    h_hfEmEnerFractionVsPt->GetYaxis()->SetTitle("Energy Fraction");

    h_chMultiplicityVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_chMultiplicityVsEta->GetYaxis()->SetTitle("N_{constituents}");
    h_nMultiplicityVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_nMultiplicityVsEta->GetYaxis()->SetTitle("N_{constituents}");
    h_phMultiplicityVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_phMultiplicityVsEta->GetYaxis()->SetTitle("N_{constituents}");
    h_elMultiplicityVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_elMultiplicityVsEta->GetYaxis()->SetTitle("N_{constituents}");
    h_muMultiplicityVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_muMultiplicityVsEta->GetYaxis()->SetTitle("N_{constituents}");
    h_hfHMultiplicityVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_hfHMultiplicityVsEta->GetYaxis()->SetTitle("N_{constituents}");
    h_hfEmMultiplicityVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_hfEmMultiplicityVsEta->GetYaxis()->SetTitle("N_{constituents}");
    h_chMultFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_chMultFractionVsEta->GetYaxis()->SetTitle("Fraction");
    h_nMultFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_nMultFractionVsEta->GetYaxis()->SetTitle("Fraction");
    h_phMultFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_phMultFractionVsEta->GetYaxis()->SetTitle("Fraction");
    h_elMultFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_elMultFractionVsEta->GetYaxis()->SetTitle("Fraction");
    h_muMultFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_muMultFractionVsEta->GetYaxis()->SetTitle("Fraction");
    h_hfHMultFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_hfHMultFractionVsEta->GetYaxis()->SetTitle("Fraction");
    h_hfEmMultFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_hfEmMultFractionVsEta->GetYaxis()->SetTitle("Fraction");
    h_chEnerFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_chEnerFractionVsEta->GetYaxis()->SetTitle("Energy Fraction");
    h_nEnerFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_nEnerFractionVsEta->GetYaxis()->SetTitle("Energy Fraction");
    h_phEnerFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_phEnerFractionVsEta->GetYaxis()->SetTitle("Energy Fraction");
    h_elEnerFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_elEnerFractionVsEta->GetYaxis()->SetTitle("Energy Fraction");
    h_muEnerFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_muEnerFractionVsEta->GetYaxis()->SetTitle("Energy Fraction");
    h_hfHEnerFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_hfHEnerFractionVsEta->GetYaxis()->SetTitle("Energy Fraction");
    h_hfEmEnerFractionVsEta->GetXaxis()->SetTitle("#eta_{jets}");
    h_hfEmEnerFractionVsEta->GetYaxis()->SetTitle("Energy Fraction");     
 }

 h_pfIdPdgAroundE->GetYaxis()->SetTitle("N_{particles}");
 h_pfIdPdgAroundE->GetXaxis()->SetTitle("particle type");

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

    if (doEfficiencies){
       h_totalGsfxMcElectronsVsEn->GetXaxis()->SetTitle("GSFelectron energy");
       h_totalGsfxMcElectronsVsEn->GetYaxis()->SetTitle("N_{electrons}");
       h_totalPfxMcElectronsVsEn->GetXaxis()->SetTitle("PFelectron energy");
       h_totalPfxMcElectronsVsEn->GetYaxis()->SetTitle("N_{electrons}");
       h_totalGsfxMcElectronsVsEta->GetXaxis()->SetTitle("GSFelectron eta");
       h_totalGsfxMcElectronsVsEta->GetYaxis()->SetTitle("N_{electrons}");
       h_totalPfxMcElectronsVsEta->GetXaxis()->SetTitle("PFelectron eta");
       h_totalPfxMcElectronsVsEta->GetYaxis()->SetTitle("N_{electrons}");
       h_PairedMcGsfElectronsVsEn->GetXaxis()->SetTitle("GSFelectron energy");
       h_PairedMcGsfElectronsVsEn->GetYaxis()->SetTitle("N_{electrons}");
       h_PairedMcPfElectronsVsEn->GetXaxis()->SetTitle("PFelectron energy");
       h_PairedMcPfElectronsVsEn->GetYaxis()->SetTitle("N_{electrons}");
       h_PairedMcGsfElectronsVsEta->GetXaxis()->SetTitle("GSFelectron eta");
       h_PairedMcGsfElectronsVsEta->GetYaxis()->SetTitle("N_{electrons}");
       h_PairedMcPfElectronsVsEta->GetXaxis()->SetTitle("PFelectron eta");
       h_PairedMcPfElectronsVsEta->GetYaxis()->SetTitle("N_{electrons}");
    }

    if (doElectronsComparisonMC){
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
       h_PFenMCenVsMcEnENear->GetYaxis()->SetTitle("En_{PF} / En_{MC} ^{electrons}");
       h_PFenMCenVsMcEnENear->GetXaxis()->SetTitle("energy_{MC}");
       h_PFenMCenVsMcEtaENear->GetYaxis()->SetTitle("En_{PF} / En_{MC} ^{electrons}");
       h_PFenMCenVsMcEtaENear->GetXaxis()->SetTitle("#eta_{MC}");
       h_GSFenMCenVsMcEnENear->GetYaxis()->SetTitle("En_{GSF} / En_{MC} ^{electrons}");
       h_GSFenMCenVsMcEnENear->GetXaxis()->SetTitle("energy_{MC}");
       h_GSFenMCenVsMcEtaENear->GetYaxis()->SetTitle("En_{GSF} / En_{MC} ^{electrons}");
       h_GSFenMCenVsMcEtaENear->GetXaxis()->SetTitle("#eta_{MC}");

       // h_gsfMcPt->GetXaxis()->SetTitle("GSF/MC p_{T}");
//        h_gsfMcPt->GetYaxis()->SetTitle("N_{electrons}");
//        h_gsfMcEta->GetXaxis()->SetTitle("GSF/MC #eta");
//        h_gsfMcEta->GetYaxis()->SetTitle("N_{electrons}");
//        h_gsfMcPhi->GetXaxis()->SetTitle("GSF/MC #phi");
//        h_gsfMcPhi->GetYaxis()->SetTitle("N_{electrons}");
//        h_pfMcPt->GetXaxis()->SetTitle("PF/MC p_{T}");
//        h_pfMcPt->GetYaxis()->SetTitle("N_{electrons}");
//        h_pfMcEta->GetXaxis()->SetTitle("PF/MC #eta");
//        h_pfMcEta->GetYaxis()->SetTitle("N_{electrons}");
//        h_pfMcPhi->GetXaxis()->SetTitle("PF/MC #phi");
//        h_pfMcPhi->GetYaxis()->SetTitle("N_{electrons}");

       h_gsfMcGsfPt->GetXaxis()->SetTitle("(GSF-MC)/GSF p_{T}");
       h_gsfMcGsfPt->GetYaxis()->SetTitle("N_{electrons}");
       h_gsfMcGsfEta->GetXaxis()->SetTitle("(GSF-MC)/GSF #eta");
       h_gsfMcGsfEta->GetYaxis()->SetTitle("N_{electrons}");
       h_gsfMcGsfPhi->GetXaxis()->SetTitle("(GSF-MC)/GSF #phi");
       h_gsfMcGsfPhi->GetYaxis()->SetTitle("N_{electrons}");
       h_pfMcPfPt->GetXaxis()->SetTitle("(PF-MC)/PF p_{T}");
       h_pfMcPfPt->GetYaxis()->SetTitle("N_{electrons}");
       h_pfMcPfEta->GetXaxis()->SetTitle("(PF-MC)/PF #eta");
       h_pfMcPfEta->GetYaxis()->SetTitle("N_{electrons}");
       h_pfMcPfPhi->GetXaxis()->SetTitle("(PF-MC)/PF #phi");
       h_pfMcPfPhi->GetYaxis()->SetTitle("N_{electrons}");

       // h_gsfMcPtVsPt->GetXaxis()->SetTitle("GSFelectron p_{T}");
//        h_gsfMcPtVsPt->GetYaxis()->SetTitle("GSF/MC p_{T}");
//        h_gsfMcEtaVsEta->GetXaxis()->SetTitle("GSFelectron #eta");
//        h_gsfMcEtaVsEta->GetYaxis()->SetTitle("GSF/MC #eta");
//        h_gsfMcPhiVsPhi->GetXaxis()->SetTitle("GSFelectron #phi");
//        h_gsfMcPhiVsPhi->GetYaxis()->SetTitle("GSF/MC #phi");
//        h_pfMcPtVsPt->GetXaxis()->SetTitle("PFelectron p_{T}");
//        h_pfMcPtVsPt->GetYaxis()->SetTitle("PF/MC p_{T}");
//        h_pfMcEtaVsEta->GetXaxis()->SetTitle("PFelectron #eta");
//        h_pfMcEtaVsEta->GetYaxis()->SetTitle("PF/MC #eta");
//        h_pfMcPhiVsPhi->GetXaxis()->SetTitle("PFelectron #phi");
//        h_pfMcPhiVsPhi->GetYaxis()->SetTitle("PF/MC #phi");

       h_gsfMcGsfPtVsPt->GetXaxis()->SetTitle("GSFelectron p_{T}");
       h_gsfMcGsfPtVsPt->GetYaxis()->SetTitle("(GSF-MC)/GSF p_{T}");
       h_gsfMcGsfEtaVsEta->GetXaxis()->SetTitle("GSFelectron #eta");
       h_gsfMcGsfEtaVsEta->GetYaxis()->SetTitle("(GSF-MC)/GSF #eta");
       h_gsfMcGsfPhiVsPhi->GetXaxis()->SetTitle("GSFelectron #phi");
       h_gsfMcGsfPhiVsPhi->GetYaxis()->SetTitle("(GSF-MC)/GSF #phi");
       h_pfMcPfPtVsPt->GetXaxis()->SetTitle("PFelectron p_{T}");
       h_pfMcPfPtVsPt->GetYaxis()->SetTitle("(PF-MC)/PF p_{T}");
       h_pfMcPfEtaVsEta->GetXaxis()->SetTitle("PFelectron #eta");
       h_pfMcPfEtaVsEta->GetYaxis()->SetTitle("(PF-MC)/PF #eta");
       h_pfMcPfPhiVsPhi->GetXaxis()->SetTitle("PFelectron #phi");
       h_pfMcPfPhiVsPhi->GetYaxis()->SetTitle("(PF-MC)/PF #phi");

       h_gsfMcGsfPtVsEta->GetXaxis()->SetTitle("GSFelectron #eta");
       h_gsfMcGsfPtVsEta->GetYaxis()->SetTitle("(GSF-MC)/GSF p_{T}");
       h_gsfMcGsfPtVsPhi->GetXaxis()->SetTitle("GSFelectron #phi");
       h_gsfMcGsfPtVsPhi->GetYaxis()->SetTitle("(GSF-MC)/GSF p_{T}");
       h_gsfMcGsfEtaVsPt->GetXaxis()->SetTitle("GSFelectron p_{T}");
       h_gsfMcGsfEtaVsPt->GetYaxis()->SetTitle("(GSF-MC)/GSF #eta");
       h_gsfMcGsfEtaVsPhi->GetXaxis()->SetTitle("GSFelectron #phi");
       h_gsfMcGsfEtaVsPhi->GetYaxis()->SetTitle("(GSF-MC)/GSF #eta");
       h_gsfMcGsfPhiVsEta->GetXaxis()->SetTitle("GSFelectron #eta");
       h_gsfMcGsfPhiVsEta->GetYaxis()->SetTitle("(GSF-MC)/GSF #phi");
       h_gsfMcGsfPhiVsPt->GetXaxis()->SetTitle("GSFelectron p_{T}");
       h_gsfMcGsfPhiVsPt->GetYaxis()->SetTitle("(GSF-MC)/GSF #phi");
       h_pfMcPfPtVsEta->GetXaxis()->SetTitle("PFelectron #eta");
       h_pfMcPfPtVsEta->GetYaxis()->SetTitle("(PF-MC)/PF p_{T}");
       h_pfMcPfPtVsPhi->GetXaxis()->SetTitle("PFelectron #phi");
       h_pfMcPfPtVsPhi->GetYaxis()->SetTitle("(PF-MC)/PF p_{T}");
       h_pfMcPfEtaVsPt->GetXaxis()->SetTitle("PFelectron p_{T}");
       h_pfMcPfEtaVsPt->GetYaxis()->SetTitle("(PF-MC)/PF #eta");
       h_pfMcPfEtaVsPhi->GetXaxis()->SetTitle("PFelectron #phi");
       h_pfMcPfEtaVsPhi->GetYaxis()->SetTitle("(PF-MC)/PF #eta");
       h_pfMcPfPhiVsEta->GetXaxis()->SetTitle("PFelectron #eta");
       h_pfMcPfPhiVsEta->GetYaxis()->SetTitle("(PF-MC)/PF #phi");
       h_pfMcPfPhiVsPt->GetXaxis()->SetTitle("PFelectron p_{T}");
       h_pfMcPfPhiVsPt->GetYaxis()->SetTitle("(PF-MC)/PF #phi");


       h_idPdgAroundE->GetXaxis()->SetTitle("particle type"); 
       h_idPdgAroundE->GetYaxis()->SetTitle("N_{particles}");
    }

    if (doPlotsJetComposition){h_idPdgJet->GetXaxis()->SetTitle("particle type");
       h_idPdgJet->GetYaxis()->SetTitle("N_{jets}");}
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
