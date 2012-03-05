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
   
   e1_pt  =0;
   e1_eta =0;
   e1_phi =0;
   e1_mass=0;
   e2_pt  =0;
   e2_eta =0;
   e2_phi =0;
   e2_mass=0;
   
   jet1_pt  =0;
   jet2_pt  =0;
   jet3_pt  =0;
   jet4_pt  =0;
   jet1_eta =0;
   jet2_eta =0;
   jet3_eta =0;
   jet4_eta =0;
   jet1_phi =0;
   jet2_phi =0;
   jet3_phi =0;
   jet4_phi =0;
   jet1_mass=0;
   jet2_mass=0;
   jet3_mass=0; 
   jet4_mass=0;
   jetHt    =0;
   
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
   
   edm::Handle<reco::GsfElectronCollection > goodEPair;
   edm::Handle<reco::PFCandidateCollection> goodPfEPair;
   int checkGoodEPairSize=0;
   if (!usingPF){
      iEvent.getByLabel (goodEPairTag, goodEPair);
      checkGoodEPairSize=goodEPair->size();}
   else {
      iEvent.getByLabel (goodEPairTag, goodPfEPair);
      checkGoodEPairSize=goodPfEPair->size();}
   
   edm::Handle<reco::GenParticleCollection> genPart;
   if (usingMC){
      iEvent.getByLabel (genParticleCollection_,genPart);
   }

   edm::Handle<reco::PFCandidateCollection> pfPart;
   iEvent.getByLabel (pflowCollection_,pfPart);
  

   if (checkGoodEPairSize==2)
   {  
      double dist=0.,maxDist=0.05;
      // ================================
      // FIll the Weights info
      // ================================
      double wei=myweight[0];
      h_weights->Fill(wei);
      // ================================
           
      //TLorentz vector of the two Z boson electrons, at GEN level
      TLorentzVector e1_gen,e2_gen;

      //TLorentz vector of the two Z boson electrons, at RECO level
      TLorentzVector e1, e2, e_pair;
      
      if (!usingPF){     
	 reco::GsfElectronCollection::const_iterator it=goodEPair->begin();     
	 e1.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());
	 it++;
	 e2.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());
      }
      else {     
	 reco::PFCandidateCollection::const_iterator it=goodPfEPair->begin();     
	 e1.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());
	 it++;
	 e2.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());
      }     
      e_pair = e1 + e2;

      e1_pt  =e1.Pt();
      e1_eta =e1.Eta();
      e1_phi =e1.Phi();
      e1_mass=e1.M();
      e2_pt  =e2.Pt();
      e2_eta =e2.Eta();
      e2_phi =e2.Phi();
      e2_mass=e2.M();
   
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
		      ( fabs(jet->electronEnergy()-e1.Energy())<0.1 
			|| fabs(jet->electronEnergy()-e2.Energy())<0.1) ) {
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
		  double nearerDist= 999;
		  bool checkNear=false;
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

	 if (totJetsCk==1) {
	    jet1_pt  =jet->Pt();
	    jet1_eta =jet->Eta();
	    jet1_phi =jet->Phi();
	    jet1_mass=jet->M();
	 }
	 else if (totJetsCk==2){
	    jet2_pt  =jet->Pt();
	    jet2_eta =jet->Eta();
	    jet2_phi =jet->Phi();
	    jet2_mass=jet->M();
	 }
	 else if (totJetsCk==3) {
	    jet3_pt  =jet->Pt();
	    jet3_eta =jet->Eta();
	    jet3_phi =jet->Phi();
	    jet3_mass=jet->M();
	 }
	 else if (totJetsCk==4){
	    jet4_pt  =jet->Pt();
	    jet4_eta =jet->Eta();
	    jet4_phi =jet->Phi();
	    jet4_mass=jet->M();
	 }
	 jetHt=jetHt + jet->Pt();
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

      h_zEta->Fill(e_pair.Eta(),myweight[0]);
      h_zRapidity->Fill(e_pair.Rapidity(),myweight[0]);
      h_zYieldVsjets->Fill(totJets,myweight[0]);
      if (numberOfVertices==1) h_zYieldVsjetsVtx1->Fill(totJets,myweight[0]);
      if (numberOfVertices==5) h_zYieldVsjetsVtx5->Fill(totJets,myweight[0]);
      
      if (totJets == 0){ 
	h_zEtaNjet0->Fill(e_pair.Eta(),myweight[0]);
	h_zMassNjet0->Fill(zInvMass,myweight[0]);
	h_zMassMinusPdgGsfNjet0->Fill(zInvMass-zMassPdg,myweight[0]);
      }
      if (totJets == 1){ 
	h_zEtaNjet1->Fill(e_pair.Eta(),myweight[0]);
	h_zMassNjet1->Fill(zInvMass,myweight[0]);
	h_zMassMinusPdgGsfNjet1->Fill(zInvMass-zMassPdg,myweight[0]);
      } else if (totJets == 2){ 
	 h_zEtaNjet2->Fill(e_pair.Eta(),myweight[0]);
	 h_zMassNjet2->Fill(zInvMass,myweight[0]);
	 h_zMassMinusPdgGsfNjet2->Fill(zInvMass-zMassPdg,myweight[0]);
      } else if (totJets == 3){ 
	 h_zEtaNjet3->Fill(e_pair.Eta(),myweight[0]);
	 h_zMassNjet3->Fill(zInvMass,myweight[0]);
	 h_zMassMinusPdgGsfNjet3->Fill(zInvMass-zMassPdg,myweight[0]);
      } else if (totJets == 4){ 
	 h_zEtaNjet4->Fill(e_pair.Eta(),myweight[0]);
	 h_zMassNjet4->Fill(zInvMass,myweight[0]);
	 h_zMassMinusPdgGsfNjet4->Fill(zInvMass-zMassPdg,myweight[0]);
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

  treeUN_->Branch("e1_pt",&e1_pt);
  treeUN_->Branch("e1_eta",&e1_eta);
  treeUN_->Branch("e1_phi",&e1_phi);
  treeUN_->Branch("e1_mass",&e1_mass);
  treeUN_->Branch("e2_pt",&e2_pt);
  treeUN_->Branch("e2_eta",&e2_eta);
  treeUN_->Branch("e2_phi",&e2_phi);
  treeUN_->Branch("e2_mass",&e2_mass);
  treeUN_->Branch("jet1_pt",&jet1_pt);
  treeUN_->Branch("jet2_pt",&jet2_pt);
  treeUN_->Branch("jet3_pt",&jet3_pt);
  treeUN_->Branch("jet4_pt",&jet4_pt);
  treeUN_->Branch("jet1_eta",&jet1_eta);
  treeUN_->Branch("jet2_eta",&jet2_eta);
  treeUN_->Branch("jet3_eta",&jet3_eta);
  treeUN_->Branch("jet4_eta",&jet4_eta);
  treeUN_->Branch("jet1_phi",&jet1_phi);
  treeUN_->Branch("jet2_phi",&jet2_phi);
  treeUN_->Branch("jet3_phi",&jet3_phi);
  treeUN_->Branch("jet4_phi",&jet4_phi);
  treeUN_->Branch("jet1_mass",&jet1_mass);
  treeUN_->Branch("jet2_mass",&jet2_mass);
  treeUN_->Branch("jet3_mass",&jet3_mass);
  treeUN_->Branch("jet4_mass",&jet4_mass);
  treeUN_->Branch("jetHt",&jetHt);

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
 h_massMinusPdgGsf_EB->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgGsf_EB->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");

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
 h_massMinusPdgGsf_EE->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgGsf_EE->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");

 h_massMinusPdgGsf_EBEE->GetYaxis()->SetTitle("N_{Z}");
 h_massMinusPdgGsf_EBEE->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");

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
 h_massMinusPdgGsf->GetXaxis()->SetTitle("mass_{Z} - mass_{pdg}");
 h_massMinusPdgGsf->GetYaxis()->SetTitle("N_{Z}");
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
