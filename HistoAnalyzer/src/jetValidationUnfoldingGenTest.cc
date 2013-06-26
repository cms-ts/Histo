// -*- C++ -*-
//

#include "Histo/HistoAnalyzer/interface/jetValidationUnfoldingGenTest.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


//
// member functions
//

class GreaterPt{
public:
  bool operator()( const math::XYZTLorentzVector& a, const math::XYZTLorentzVector& b) {
    return a.Pt() > b.Pt();
  }
};

double
jetValidationUnfoldingGenTest::distR(TLorentzVector a ,math::XYZTLorentzVector b){

   double deltaPhi = fabs(a.Phi()-b.Phi());
   if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
   double delta = sqrt( deltaPhi*deltaPhi  + ((a.Eta()-b.Eta())*(a.Eta()-b.Eta())));
   return delta;
}
// ------------ method called for each event  ------------
void
jetValidationUnfoldingGenTest::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  eventNumberCounter++;
  cout<<"This is the number "<<eventNumberCounter<<endl;
  bool Debug=false;
  
  double genJetPtThreshold=30.0;
  double genJetEtaThreshold=2.4;

  leptonId = 11;
  if (!isElectron) leptonId = 13;

   //IMPORTANTE  
   numberOfVertices=0;
   
   //Define Variables 
   int nJetsEB=0;
   int nJetsEE=0;
   int totJets=0;
   int totJetsCk=0;
   double deltaPhi=0;

   double inclHt=0.;
   //bool isEB;
   //bool isEE;
   
   e1_pt  =-9999;
   e1_eta =-9999;
   e1_phi =-9999;
   e1_mass=-9999;
   e2_pt  =-9999;
   e2_eta =-9999;
   e2_phi =-9999;
   e2_mass=-9999;
   z_mass=-9999;
   
   jet1_pt  =-9999;
   jet2_pt  =-9999;
   jet3_pt  =-9999;
   jet4_pt  =-9999;
   jet5_pt  =-9999;
   jet6_pt  =-9999;
   jet7_pt  =-9999;

   jet1_eta =-9999;
   jet2_eta =-9999;
   jet3_eta =-9999;
   jet4_eta =-9999;
   jet5_eta =-9999;
   jet6_eta =-9999;
   jet7_eta =-9999;

   jet1_phi =-9999;
   jet2_phi =-9999;
   jet3_phi =-9999;
   jet4_phi =-9999;
   jet1_mass=-9999;
   jet2_mass=-9999;
   jet3_mass=-9999; 
   jet4_mass=-9999;
   jetHt    =-9999;
  
   l1_eta_gen=-9999;
   l2_eta_gen=-9999;
   l1_pt_gen=-9999;
   l2_pt_gen=-9999;
   invMass_gen=-9999;


   ///////////////////////
   ///// GenInfo For UnfoldingGenTest
   ///////////////////////

   genZInAcceptance=false;
   recoZInAcceptance=false;

   edm::Handle<reco::GenParticleCollection> genPart;
   iEvent.getByLabel (genParticleCollection_,genPart);

  //Evaluate if the events would have been selected at the generator level...
  if (isUnfolding_){
    //Find the ele of the Z  

    TLorentzVector l1, l2, l_pair;
    std::vector<TLorentzVector> leptonContainer;
    double zInvMass = 0;  

    double genElePtFSR=0;
    double genEleEtaFSR=0;
    double genMuPtFSR=0;
    double genMuEtaFSR=0;

    //Retrieve the energy and pt of the objects, after FSR treatment..
    edm::Handle< std::vector<float> > EleGenPtFSR;
    if (! iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",EleGammaGenPt_,EleGenPtFSR)) {
      cout<<"Problems to open the EleGenPtFSR... check"<<endl;
    }
    else
      {
	iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",EleGammaGenPt_,EleGenPtFSR);
	const std::vector<float> & myEleGenPtFSR=*EleGenPtFSR;
	if (myEleGenPtFSR.size()!=0) {
	  genElePtFSR=myEleGenPtFSR.at(0);
	}
      }

    edm::Handle< std::vector<float> > EleGenEtaFSR;
    if (! iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",EleGammaGenEta,EleGenEtaFSR)) {
      cout<<"Problems to open the EleGenPtFSR... check"<<endl;
    }
    else
      {
	iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",EleGammaGenEta,EleGenEtaFSR);
	const std::vector<float> & myEleGenEtaFSR=*EleGenEtaFSR;
	if (myEleGenEtaFSR.size()!=0) {
	  genEleEtaFSR=myEleGenEtaFSR.at(0);
	}
      }
    ////////
    edm::Handle< std::vector<float> > MuGenPtFSR;
    if (! iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",MuGammaGenPt,MuGenPtFSR)) {
      cout<<"Problems to open the MuGenPtFSR... check"<<endl;
    }
    else
      {
	iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",MuGammaGenPt,MuGenPtFSR);
	const std::vector<float> & myMuGenPtFSR=*MuGenPtFSR;
	if (myMuGenPtFSR.size()!=0) {
	  genMuPtFSR=myMuGenPtFSR.at(0);
	}
      }

    edm::Handle< std::vector<float> > MuGenEtaFSR;
    if (! iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",MuGammaGenEta,MuGenEtaFSR)) {
      cout<<"Problems to open the MuGenPtFSR... check"<<endl;
    }
    else
      {
	iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",MuGammaGenEta,MuGenEtaFSR);
	const std::vector<float> & myMuGenEtaFSR=*MuGenEtaFSR;
	if (myMuGenEtaFSR.size()!=0) {
	  genMuEtaFSR=myMuGenEtaFSR.at(0);
	}
      }
    
    
    bool foundZBoson=false;
    //Check if there is a Z boson decaying properly
    for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
      if ( ((fabs(itgen->pdgId())==leptonId)) && itgen->mother()->pdgId()==23){ //itgen->status()==1 &&
	cout<<"Found the "<<leptonId <<" looking at the Z childerns...."<<endl;
	foundZBoson=true;
      } 
    }

    for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
      if (((fabs(itgen->pdgId())==leptonId)) || ((fabs(itgen->pdgId())==22))) cout<<"Ele/photon with iD "<<itgen->pdgId()<<" and pt "<<itgen->pt()<<" and eta "<<itgen->eta()<<" and status "<<itgen->status()<<"is found in the GenCollection from Damniana"<<endl;
      if ( ((fabs(itgen->pdgId())==leptonId)) && itgen->status()==1 && foundZBoson){
	l1.SetPtEtaPhiM(itgen->pt(),itgen->eta(),itgen->phi(),itgen->mass());
	leptonContainer.push_back(l1);
      } 
    }

    if (leptonContainer.size()>=2)
      {
	l_pair = leptonContainer[0] + leptonContainer[1];
	zInvMass = l_pair.M();
	invMass_gen=zInvMass;
	l1_eta_gen=leptonContainer[0].Eta();
	l2_eta_gen=leptonContainer[1].Eta();
	l1_pt_gen=leptonContainer[0].Pt();
	l2_pt_gen=leptonContainer[1].Pt();

	if (invMass_gen<111 && invMass_gen>71 && 
	    fabs(l1_eta_gen)<2.4 &&
	    fabs(l2_eta_gen)<2.4 &&
	    fabs(l1_pt_gen) >20  &&
	    fabs(l2_pt_gen) >20) {
	  genZInAcceptance=true;
	  cout<<"This is a good Z boson decayn in "<<leptonId<<endl;
	}
	cout<<"lepton 1 bare pt->"<<l1_pt_gen;
	cout<<"  lepton 2 bare pt->"<<l2_pt_gen;
	cout<<"  lepton 1 eta->"<<l1_eta_gen;
	cout<<"  lepton 2 eta->"<<l2_eta_gen;
	cout<<"  inv mass "<<invMass_gen<<endl;
	leptonContainer.clear();
	//
	//edm::Handle<std::vector<TLorentzVector> > dressedLepton;
	//if (isElectron) iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone","EleGammaGen", dressedLepton);
	//else iEvent.getByLabel("genParticlesForJetsMuNoNuNoGammaCone","MuGammaGen", dressedLepton);
	//if (dressedLepton.isValid()) {
	//cout<<"Valid collection"<<endl;
	  //for(i = dressedLepton->begin(); i!= dressedLepton->end(); ++i){
	  //cout<<"lepton dressed pt->"<<i[0].Pt()<<endl;
	  //cout<<"lepton 2 dressed pt->"<<i[0].Pt()<<endl;
	  //}
	//}
      }
    else{
      //cout<<"This is a mumu"<<endl;
    }
  }

      std::vector<math::XYZTLorentzVector> JetContainer;  
      JetContainer.clear();
      std::vector<math::XYZTLorentzVector> GenJetContainer;  
      GenJetContainer.clear();

 


      /////////////////////
      /// Create a JetGenContainer, as done for the RecoJets, to create the jetpt variable, afterwards
      ////////////////////

      ///////////////////////////////////////

      Jet_multiplicity=totJets;

      Jet_multiplicity_gen=-9999;
      Z_y_gen=-9999;
      Z_pt_gen=-9999;
      jet1_pt_gen=-9999;
      jet2_pt_gen=-9999;
      jet3_pt_gen=-9999;
      jet4_pt_gen=-9999;
      jet5_pt_gen=-9999;
      jet6_pt_gen=-9999;
      jet7_pt_gen=-9999;

      jet1_eta_gen=-9999;
      jet2_eta_gen=-9999;
      jet3_eta_gen=-9999;
      jet4_eta_gen=-9999;
      jet5_eta_gen=-9999;
      jet6_eta_gen=-9999;
      jet7_eta_gen=-9999;
      
      if (usingMC){
	edm::Handle<reco::GenJetCollection> genJets;
	iEvent.getByLabel(genJetsCollection, genJets );
	int numbOfJets=0;      
	
	for (reco::GenJetCollection::const_iterator jet=genJets->begin();jet!=genJets->end();++jet){

	  // check if the jet is equal to one of the isolated electrons 
	  deltaPhi = 0.0;
	   if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	   double deltaR1 = 0.0;

	   deltaPhi = 0.0;
	   if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	   double deltaR2= 0.0;

	   if (deltaR1 > deltaRCone && deltaR2 > deltaRCone 
	       // cut on the jet pt 
	       && jet->pt()> genJetPtThreshold //A minimux allowed energy for GEN-JET!!!!!
	       && fabs(jet->eta())<genJetEtaThreshold //A minimux allowed eeta for GEN-JET!!!!!
	       //&& jet->chargedEmEnergyFraction()<chargedEmEnergyFraction
	       //&& jet->neutralHadronEnergyFraction()<neutralHadronEnergyFraction
	       //&& jet->neutralEmEnergyFraction()<neutralEmEnergyFraction
	       //&& jet->chargedHadronEnergyFraction()>chargedHadronEnergyFraction
	       //&& jet->charge()>chargedMultiplicity
	       ){

	     //Check if it is a charged jet!
	     double isChargedJet=false;
	     std::vector<const GenParticle*> mcparticles = jet->getGenConstituents();
	     for(std::vector <const GenParticle*>::const_iterator thepart =mcparticles.begin();thepart != mcparticles.end(); ++ thepart ) {
	       //cout<<"Charge of constituents->"<<(abs((**thepart).charge()))<<endl;
	       if ( (**thepart).charge()!=0 ){
		 isChargedJet=true;
	       }
	     }
	     cout<<"final charge->"<<isChargedJet<<endl;
	     if (isChargedJet) GenJetContainer.push_back(jet->p4()); 
	     isChargedJet=false;
	     numbOfJets++;
	     cout<<"Jet has energy:"<<jet->pt()<<" and eta:"<<jet->eta()<<endl;
	   }
	}
	if (genZInAcceptance && numbOfJets>0) {
	  cout<<"Jet Multiplicity (GEN) "<<numbOfJets<<", events "<<eventNumberCounter<<endl;
	  if (numbOfJets==1) oneJet++;
	  if (numbOfJets==2) twoJets++;
	  if (numbOfJets==3) threeJets++;
	  if (numbOfJets==4) fourJets++;
	}
	if (numbOfJets<100) Jet_multiplicity_gen=numbOfJets;
	std::stable_sort(GenJetContainer.begin(),GenJetContainer.end(),GreaterPt()); 
      }

      cout<<"#######################"<<endl;
      ////// Checking also if the Z boson has decayed int taus or muons, and then misreconstructed!

      isMugen=false;
      isTaugen=false;

      if (usingMC){
	int response=isTauOrMu(genPart);
	if (response==1) isTaugen=true; // if response is 1 is a tau, see function isTauOrMu
	if (response==2) isMugen=true; // if 2 is a muon
      }
      
      if (isTaugen) return;
      //bUILDING THE Z GEN BOSON
	/*
      if (usingMC){
	TLorentzVector Z_gen,ele_gen;
	std::vector <TLorentzVector> ele_gen_vec ;
	for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
	  if (itgen->pdgId()==23 && itgen->status()==2){ // itgen->status()==1 &&   
	    if (Debug) cout<<"(GEN) Z boson"<<endl;
	    Z_gen.SetPxPyPzE(itgen->px(),itgen->py(),itgen->pz(),itgen->energy()); 
	  }
	  if (fabs(itgen->pdgId())==leptonId && itgen->mother()->pdgId()==23){ //itgen->status()==1 && 
	    ele_gen.SetPxPyPzE(itgen->px(),itgen->py(),itgen->pz(),itgen->energy()); 
	    ele_gen_vec.push_back(ele_gen);
	  }
	}
	if (Z_gen.Pt()<7000) Z_pt_gen=Z_gen.Pt();
	if (Z_gen.Rapidity()<7000) Z_y_gen=Z_gen.Rapidity();
	if (Debug) cout<<"Z pt (GEN) is "<<Z_pt_gen<<" and y is "<<Z_y_gen<<endl;
	

	//Number of GenJet
	edm::Handle<reco::GenJetCollection> genJets;
	iEvent.getByLabel(genJetsCollection, genJets );
	
	// if Sherpa, fake lepton are created in order to fill the Jet_multiplicity_gen
	// if we removed the leptons before (in photonRemoval) the check  
	// within the cone is useless


      ///////////////////
      ///// Matching Gen-RECO
      ///////////////////
      
      if (usingMC){
	// Loop sui RecoGen ordinati in pt
	std::vector <double> jetpt_gen; 
	std::vector <double> jeteta_gen;

	for (std::vector<math::XYZTLorentzVector>::const_iterator jet = JetContainer.begin (); jet != JetContainer.end (); jet++) {
	  // Calcolare il DeltaR verso tutti i GenJet
	  double deltaRGenReco=9999;
	  double matchedGJetpt=9999;
          double matchedGJeteta=9999;

	  if (Debug) cout<<"reco jet pt in the loop. Starting the match "<<endl;
	  //jetPtVector.push_back(jet->Pt());
	  for (std::vector<math::XYZTLorentzVector>::const_iterator gjet = GenJetContainer.begin (); gjet != GenJetContainer.end (); gjet++) {

	     deltaPhi = fabs(jet->phi()-gjet->phi());
	     if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	     double deltaRswap= sqrt( pow(jet->eta()-gjet->eta(),2)+pow(deltaPhi,2) );
	     if (deltaRswap < deltaRGenReco) {
		deltaRGenReco=deltaRswap;
		matchedGJetpt=gjet->Pt();
		matchedGJeteta=gjet->Eta();
	     }
	  }
	  jetpt_gen.push_back(matchedGJetpt);
          jeteta_gen.push_back(matchedGJeteta);
	  if (Debug) cout<<"Gen Jet Matched: pt->"<<matchedGJetpt<<" and eta->"<<matchedGJeteta<<endl;
	}
	
	// In the above loop, in jetpt_gen you have the collection of gen jets matched by the detector. Now evaluating the viceversa,
	// jets generated > 30 but not reconstructed
	
	if (jetpt_gen.size() < GenJetContainer.size()){    // check if some gen jets are somehow missing... 
	  if (Debug) cout<<"There are more genjets than jetReco. # matched jets->"<<jetpt_gen.size()<<" # jets gen->"<<GenJetContainer.size()<<" you will see the entire list of jets, for residual matching"<<endl;
	  for (std::vector<math::XYZTLorentzVector>::const_iterator gjet = GenJetContainer.begin (); gjet != GenJetContainer.end (); gjet++) {
	    if (Debug) cout<<"gen jet pt->"<<gjet->Pt()<<" and eta->"<<gjet->Eta()<<endl;
	    bool isAgoodJet=false;
	    if (gjet->Pt()>genJetPtThreshold && fabs(gjet->Eta())<genJetEtaThreshold ){ // it should be above thresholds.. ADD the CHARGE information!
	      isAgoodJet=true; // it has at least one charged track
	    }
	    if (isAgoodJet){
	      if (Debug) cout<<"this is a overthreshold gen jet!, chcking if already stored!"<<endl;
	      bool matchedalready=false;
	      for (unsigned int k=0; k < jetpt_gen.size(); k++){
		//Check if it has already been added
		if (jetpt_gen[k]==gjet->Pt()) matchedalready=true;
	      }
	      if (!matchedalready) {
		jetpt_gen.push_back(gjet->Pt());
                jeteta_gen.push_back(gjet->Eta());
		if (Debug) cout<<"adding JET not reconstructed! pt->"<<gjet->Pt()<<" eta->"<<gjet->Eta()<<endl;
	      }
	      else if (Debug) cout<<"gen jet already stored!"<<endl;
	    }
	  }
	}

	int gvectorsize=jetpt_gen.size();
	if (Debug) cout<<"Gen Jet found->"<<gvectorsize<<" size of JetContainer->"<<JetContainer.size()<<endl;

	//genJetPtVector=jetpt_gen; // If works, cancel th following lines

	if (gvectorsize>0) {
	  jet1_pt_gen=jetpt_gen[0];
	  jet1_eta_gen=jeteta_gen[0];
	}
	if (gvectorsize>1) {
	  jet2_pt_gen=jetpt_gen[1];
	  jet2_eta_gen=jeteta_gen[1];
	}
	if (gvectorsize>2) {
	  jet3_pt_gen=jetpt_gen[2];
	  jet3_eta_gen=jeteta_gen[2];
	}
	if (gvectorsize>3) {
	  jet4_pt_gen=jetpt_gen[3];
	  jet4_eta_gen=jeteta_gen[3];
	}
	if (gvectorsize>4) {
	  jet5_pt_gen=jetpt_gen[4];
	  jet5_eta_gen=jeteta_gen[4];
	}
	if (gvectorsize>5) {
	  jet6_pt_gen=jetpt_gen[5];
	  jet6_eta_gen=jeteta_gen[5];
	}
	if (gvectorsize>6) {
	  jet7_pt_gen=jetpt_gen[6];
	  jet7_eta_gen=jeteta_gen[6];
	}

	//cout<<"gen jet1 has pt "<<jet1_pt_gen<<" jet2 "<<jet2_pt_gen<<" jet3 "<<jet3_pt_gen<<" jet4_pt_gen "<<jet4_pt_gen<<endl;
      }
      GenJetContainer.clear();

   } else if (Debug){std::cout << "WARNING: More than two electron selected"<< std::endl;}  
  
   //Fill Unfolding rootuple!
   if (Jet_multiplicity>0 || Jet_multiplicity_gen>0) treeUN_->Fill();
  */
  return;
}


// ------------ method called once each job just before starting event loop  ------------
void 
jetValidationUnfoldingGenTest::beginJob()
{
  eventNumberCounter=0;
  oneJet=0;
  twoJets=0;
  threeJets=0;
  fourJets=0;
  //Initilize the JEDC
  p = new JetCorrectorParameters("JEC11_V12_AK5PF_UncertaintySources.txt", "Total");
  t = new JetCorrectionUncertainty(*p);  
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
jetValidationUnfoldingGenTest::endJob() 
{
  cout<<"You have "<<oneJet<<" Z whith 1 jets"<<endl;
  cout<<"You have "<<twoJets<<" Z whith 2 jets"<<endl;
  cout<<"You have "<<threeJets<<" Z whith 3 jets"<<endl;
  cout<<"You have "<<fourJets<<" Z whith 4 jets"<<endl;

  cout<<"End Job"<<endl;
}

// Evalaute the systematics on JEC
double jetValidationUnfoldingGenTest::evaluateJECUncertainties(double jetpt,double jeteta){
  
  t->setJetPt(jetpt);
  t->setJetEta(jeteta);
  double uncert = t->getUncertainty(true);

  //Increase the efficiencies by an extra factor, according to https://hypernews.cern.ch/HyperNews/CMS/get/jes/316.html
  if (fabs(jeteta)<1.3 ) uncert+=0.01;
  else uncert+=0.015;
  return uncert;
}

int jetValidationUnfoldingGenTest::isTauOrMu(edm::Handle<GenParticleCollection> genParticlesCollection)
{
   bool theFilter=false;
   int ntausFromZ(0);
   int ntaus(0);
   int nmuFromZ(0);
   int nmu(0);

   std::vector<std::pair<int,math::XYZTLorentzVectorD> > idAndPTaus;
   math::XYZTLorentzVectorD pTauPos, pTauNeg, pZTauTau;

   std::vector<std::pair<int,math::XYZTLorentzVectorD> > idAndPMu;
   math::XYZTLorentzVectorD pMuPos, pMuNeg, pZMuMu;
   pTauPos.SetXYZT(0,0,0,0);
   pTauNeg.SetXYZT(0,0,0,0);
   pZTauTau.SetXYZT(0,0,0,0);   
   // initialize the gen 4vectors
   pMuPos.SetXYZT(0,0,0,0);
   pMuNeg.SetXYZT(0,0,0,0);
   pZMuMu.SetXYZT(0,0,0,0);


   for(GenParticleCollection::const_iterator genp = genParticlesCollection->begin();genp != genParticlesCollection->end(); ++ genp ) {  // loop over GEN particles
     
     if(abs(genp->pdgId()==15)){
       ntaus++;
     }
     
     //------------------------------------------- Z boson -------------------------------------------
     if(genp->pdgId()==23){   
       for(UInt_t i=0; i<genp->numberOfDaughters(); i++){
	 // Loop for taus...
	 if(abs(genp->daughter(i)->pdgId())==15 && genp->daughter(i)->status()==3){
	   //std::cout<<"found a tau from Z"<<std::endl;
	   ntausFromZ++;
	   std::pair<int,math::XYZTLorentzVectorD> theTauInfo;
	   theTauInfo = make_pair(0,pTauPos);
	   theTauInfo.first = genp->pdgId();
	   theTauInfo.second = genp->p4();
	   idAndPTaus.push_back(theTauInfo);
	   if(theTauInfo.first > 0) pTauPos = theTauInfo.second;
	   else pTauNeg = theTauInfo.second; 
	 }
	 //Loop for muons
	 if(abs(genp->daughter(i)->pdgId())==13 && genp->daughter(i)->status()==3){
	   //std::cout<<"found a mu from Z"<<std::endl;
	   nmuFromZ++;
	   std::pair<int,math::XYZTLorentzVectorD> theMuInfo;
	   theMuInfo = make_pair(0,pMuPos);
	   theMuInfo.first = genp->pdgId();
	   theMuInfo.second = genp->p4();
	   idAndPMu.push_back(theMuInfo);
	   if(theMuInfo.first > 0) pMuPos = theMuInfo.second;
	   else pMuNeg = theMuInfo.second; 
	 }
       }
     }
   }//end loop over genParticles
   
   if(ntausFromZ==2){
     theFilter=true;
     pZTauTau=pTauNeg+pTauPos;
     return 1;
   }
   
   if(nmuFromZ==2){
     theFilter=true;
     pZMuMu=pMuNeg+pMuPos;
     return 2;
   }
   
   return 0;
   
}



//define this as a plug-in
DEFINE_FWK_MODULE(jetValidationUnfoldingGenTest);
