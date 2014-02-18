// -*- C++ -*-
//

#include "Histo/HistoAnalyzer/interface/jetValidationUnfolding.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/Common/interface/RefVector.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
// To account for JER
#include "Histo/HistoAnalyzer/interface/JERCorrection.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"

#include "PhysicsTools/PatAlgos/plugins/PATJetProducer.h"
//
// member functions
//

class GreaterPt{
public:
  bool operator()( const math::XYZTLorentzVector& a, const math::XYZTLorentzVector& b) {
    return a.Pt() > b.Pt();
  }
};

static bool greaterPtJet( const reco::PFCandidate& a, const reco::PFCandidate& b ) {
  return (a.pt()>b.pt());
}

double
jetValidationUnfolding::distR(TLorentzVector a ,math::XYZTLorentzVector b){

   double deltaPhi = fabs(a.Phi()-b.Phi());
   if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
   double delta = sqrt( deltaPhi*deltaPhi  + ((a.Eta()-b.Eta())*(a.Eta()-b.Eta())));
   return delta;
}
// ------------ method called for each event  ------------
void
jetValidationUnfolding::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  eventNumberCounter++;
  bool Debug=false;
  if (Debug) cout<<"This is the number "<<eventNumberCounter<<endl;

  double genJetPtThreshold=15.0;
  double genJetEtaThreshold=2.5;

  ////////
  //  Get The Weights
  ///////
  
  //Sherpa weights
  
  edm::Handle< std::vector<float> > weightSherpa;
  if (! iEvent.getByLabel("demo",WeightNameSherpa,weightSherpa)) {
    cout<<"Problems to open the Sherpa Weight... check"<<endl;
  }
  else
    {
      iEvent.getByLabel("demo",WeightNameSherpa,weightSherpa);
      const std::vector<float> & myweightSherpa=*weightSherpa;
      evWeightSherpa = myweightSherpa[0];
    }
  // Normal Weights

  edm::Handle< std::vector<float> > weight;
  iEvent.getByLabel("demo",WeightName,weight);
  const std::vector<float> & myweight=*weight;
  evWeight = myweight[0];

  leptonId = 11;
  if (!isElectron) leptonId = 13;

   //IMPORTANTE  
   numberOfVertices=0;
   
   //Define Variables 
   //int nJetsEB=0;
   //int nJetsEE=0;
   //int totJets=0;
   //int totJetsCk=0;
   double deltaPhi=0;

   //double inclHt=0.;
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

   Jet_multiplicity=-9999;
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

   jet1_pt_gen_abs=-9999;
   jet2_pt_gen_abs=-9999;
   jet3_pt_gen_abs=-9999;
   jet4_pt_gen_abs=-9999;
   jet5_pt_gen_abs=-9999;
   jet6_pt_gen_abs=-9999;
   jet7_pt_gen_abs=-9999;

   jet1_eta_gen_abs=-9999;
   jet2_eta_gen_abs=-9999;
   jet3_eta_gen_abs=-9999;
   jet4_eta_gen_abs=-9999;
   jet5_eta_gen_abs=-9999;
   jet6_eta_gen_abs=-9999;
   jet7_eta_gen_abs=-9999;
   
   jet1_eta_gen=-9999;
   jet2_eta_gen=-9999;
   jet3_eta_gen=-9999;
   jet4_eta_gen=-9999;
   jet5_eta_gen=-9999;
   jet6_eta_gen=-9999;
   jet7_eta_gen=-9999;

   jet1_phi_gen=-9999;
   jet2_phi_gen=-9999;
   jet3_phi_gen=-9999;
   jet4_phi_gen=-9999;
   jet5_phi_gen=-9999;
   jet6_phi_gen=-9999;
   jet7_phi_gen=-9999;
   

   ///////////////////////
   ///// GenInfo For Unfolding
   ///////////////////////

   genZInAcceptance=false;
   recoZInAcceptance=false;

   std::vector<math::XYZTLorentzVector> JetContainer;  
   JetContainer.clear();

   std::vector<math::XYZTLorentzVector> JetContainerFullEvent;
   JetContainerFullEvent.clear();

   std::vector<math::XYZTLorentzVector> GenJetContainerFullEvent;
   JetContainerFullEvent.clear();

   std::vector<math::XYZTLorentzVector> GenJetContainerForAbsolutePtValue;
   GenJetContainerForAbsolutePtValue.clear();
   std::vector<TLorentzVector> GenJetContainer;  
   GenJetContainer.clear();
   std::vector<TLorentzVector> GenJetContainer2;  
   GenJetContainer.clear();

   //TLorentz vector of the two Z boson electrons, at GEN level
   TLorentzVector e1_gen,e2_gen;
   
   //TLorentz vector of the two Z boson electrons, at RECO level
   TLorentzVector e1, e2, e_pair;
   
   if (Debug) cout<<"before: recoZInAcceptance->"<<recoZInAcceptance<<" genZInAcceptance->"<<genZInAcceptance<<endl;

  //Evaluate if the events would have been selected at the generator level...
   edm::Handle<reco::GenParticleCollection> genPart;
   iEvent.getByLabel (genParticleCollection_,genPart);
   //Find the ele of the Z  
   
   TLorentzVector l1, l2, l_pair;
   std::vector<TLorentzVector> leptonContainer;
   std::vector<TLorentzVector> leptonsGen; //Copy to pass gen ele to dr gen evaluation
   double zInvMass = 0;  
   
   //New set of variables to retrieve FSR
   double genElePtFSRp=0;
   double genEleEtaFSRp=0;
   double genMuPtFSRp=0;
   double genMuEtaFSRp=0;
   
   double genElePtFSRm=0;
   double genEleEtaFSRm=0;
   double genMuPtFSRm=0;
   double genMuEtaFSRm=0;
   
   //Retrieve the energy and pt of the objects, after FSR treatment..
   edm::Handle< std::vector<float> > EleGenPtFSR;
   if (! iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",EleGammaGenPt_,EleGenPtFSR)) {
     if (Debug) cout<<"Problems to open the EleGenPtFSR... check"<<endl;
   }
   else
     {
       iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",EleGammaGenPt_,EleGenPtFSR);
       const std::vector<float> & myEleGenPtFSR=*EleGenPtFSR;
       if (myEleGenPtFSR.size()!=0) {
	 genElePtFSRp=myEleGenPtFSR.at(0);
	 genElePtFSRm=myEleGenPtFSR.at(1);
       }
     }
   
   edm::Handle< std::vector<float> > EleGenEtaFSR;
   if (! iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",EleGammaGenEta,EleGenEtaFSR)) {
     if (Debug) cout<<"Problems to open the EleGenPtFSR... check"<<endl;
   }
   else
     {
       iEvent.getByLabel("genParticlesForJetsENoNuNoGammaCone",EleGammaGenEta,EleGenEtaFSR);
       const std::vector<float> & myEleGenEtaFSR=*EleGenEtaFSR;
       if (myEleGenEtaFSR.size()!=0) {
	 genEleEtaFSRp=myEleGenEtaFSR.at(0);
	 genEleEtaFSRm=myEleGenEtaFSR.at(1);
       }
     }
   ////////
   edm::Handle< std::vector<float> > MuGenPtFSR;
   if (! iEvent.getByLabel("genParticlesForJetsMuNoNuNoGammaCone",MuGammaGenPt,MuGenPtFSR)) {
     if (Debug) cout<<"Problems to open the MuGenPtFSR... check"<<endl;
   }
   else
     {
       iEvent.getByLabel("genParticlesForJetsMuNoNuNoGammaCone",MuGammaGenPt,MuGenPtFSR);
       const std::vector<float> & myMuGenPtFSR=*MuGenPtFSR;
       if (myMuGenPtFSR.size()!=0) {
	 genMuPtFSRp=myMuGenPtFSR.at(0);
	 genMuPtFSRm=myMuGenPtFSR.at(1);
       }
     }
   
   edm::Handle< std::vector<float> > MuGenEtaFSR;
   if (! iEvent.getByLabel("genParticlesForJetsMuNoNuNoGammaCone",MuGammaGenEta,MuGenEtaFSR)) {
     if (Debug) cout<<"Problems to open the MuGenPtFSR... check"<<endl;
   }
   else
     {
       iEvent.getByLabel("genParticlesForJetsMuNoNuNoGammaCone",MuGammaGenEta,MuGenEtaFSR);
       const std::vector<float> & myMuGenEtaFSR=*MuGenEtaFSR;
       if (myMuGenEtaFSR.size()!=0) {
	 genMuEtaFSRp=myMuGenEtaFSR.at(0);
	 genMuEtaFSRm=myMuGenEtaFSR.at(1);
       }
     }
   
   
   //Check using the mc truth (status 3) whether it was a ee or mm event
   bool foundZBoson=false;
   int  childCounter=0;
   //Check if there is a Z boson decaying properly
   for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
     if ( ((fabs(itgen->pdgId())==leptonId)) && itgen->mother()->pdgId()==23){ //itgen->status()==1 &&
       if (Debug) cout<<"Found the "<<leptonId <<" looking at the Z childerns...."<<endl;
       childCounter++;
       if (childCounter==2) foundZBoson=true;
     } 
   }

   //if sherpa, previous loop is empty! I repeat it
   if (isSherpa){
     for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
       if ( ((fabs(itgen->pdgId())==leptonId)) && itgen->pt()>20 && (fabs(itgen->eta())<2.4)){ //itgen->status()==1 &&                                                                            
	 if (Debug) cout<<"Found the "<<leptonId <<" looking at the Z childerns in sherpa...."<<endl;
	 childCounter++;
	 if (childCounter==2) foundZBoson=true;
       }
     }
   }
   
   for(reco::GenParticleCollection::const_iterator itgen=genPart->begin();itgen!=genPart->end();itgen++){
     if ( ((fabs(itgen->pdgId())==leptonId)) && itgen->status()==1 && foundZBoson){
       if (Debug) cout<<genElePtFSRp<<genEleEtaFSRp<<endl;
       if (Debug) cout<<genElePtFSRm<<genEleEtaFSRm<<endl;
       if (Debug) cout<<genMuPtFSRp<<genMuEtaFSRp<<endl;
       if (Debug) cout<<genMuPtFSRm<<genMuEtaFSRm<<endl;
       
       if (genElePtFSRp==0 && genElePtFSRm==0 && fabs(itgen->pdgId())==11) continue;
       if (genMuPtFSRp==0 && genMuPtFSRm==0 && fabs(itgen->pdgId())==13) continue;
       
       if (itgen->pdgId()>0 && fabs(itgen->pdgId())==11 ) l1.SetPtEtaPhiM(genElePtFSRp,genEleEtaFSRp,itgen->phi(),itgen->mass());
       if (itgen->pdgId()<0 && fabs(itgen->pdgId())==11 ) l1.SetPtEtaPhiM(genElePtFSRm,genEleEtaFSRm,itgen->phi(),itgen->mass());
       if (itgen->pdgId()>0 && fabs(itgen->pdgId())==13 ) l1.SetPtEtaPhiM(genMuPtFSRp,genMuEtaFSRp,itgen->phi(),itgen->mass());
       if (itgen->pdgId()<0 && fabs(itgen->pdgId())==13 ) l1.SetPtEtaPhiM(genMuPtFSRm,genMuEtaFSRm,itgen->phi(),itgen->mass());
       leptonContainer.push_back(l1);
       leptonsGen.push_back(l1);
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
	 if (Debug) cout<<"This is a good gen Z boson decayn in "<<leptonId<<endl;
       }
       if (Debug)cout<<"lepton 1 bare pt->"<<l1_pt_gen;
       if (Debug)cout<<"  lepton 2 bare pt->"<<l2_pt_gen;
       if (Debug)cout<<"  lepton 1 eta->"<<l1_eta_gen;
       if (Debug)cout<<"  lepton 2 eta->"<<l2_eta_gen;
       if (Debug)cout<<"  inv mass "<<invMass_gen<<endl;
       leptonContainer.clear();
     }
   else{
     //cout<<"This is a mumu"<<endl;
   }
   
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
   
   edm::Handle<reco::PFCandidateCollection> goodPfEPair;
   edm::Handle<reco::GsfElectronCollection > goodEPair;
   
   if (! iEvent.getByLabel (goodEPairTag, goodPfEPair)) {
     //cout<<"Add a filter to avoid Z->mumu non selected"<<endl;
     return;
   }
   int checkGoodEPairSize=0;
   if (!usingPF){
     iEvent.getByLabel (goodEPairTag, goodEPair);
     checkGoodEPairSize=goodEPair->size();}
   else {
     iEvent.getByLabel (goodEPairTag, goodPfEPair);
     checkGoodEPairSize=goodPfEPair->size();}
   
   edm::Handle<reco::PFCandidateCollection> pfPart;
   iEvent.getByLabel (pflowCollection_,pfPart);
   
   if (checkGoodEPairSize>=2){   
     recoZInAcceptance=true;
     if (Debug) cout<<"This is a good reco Z Boson"<<endl;
     // ================================
     // FIll the Weights info
     // ================================
     double wei=myweight[0];
     h_weights->Fill(wei);
     // ================================
     
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
     
     if (e1.Pt()>e2.Pt()){
       e1_pt  =e1.Pt();
       e1_eta =e1.Eta();
       e1_phi =e1.Phi();
       e1_mass=e1.M();
       e2_pt  =e2.Pt();
       e2_eta =e2.Eta();
       e2_phi =e2.Phi();
       e2_mass=e2.M();
     }
     else {
       e1_pt  =e2.Pt();
       e1_eta =e2.Eta();
       e1_phi =e2.Phi();
       e1_mass=e2.M();
       e2_pt  =e1.Pt();
       e2_eta =e1.Eta();
       e2_phi =e1.Phi();
       e2_mass=e1.M();
     }
     
     if (Debug) cout<<"e1_pt "<<e1_pt<<" e2_pt "<<e2_pt<<endl;
     // ================================
     
     ///////////////////
     /// Jet Validation
     ///////////////////
     
     Handle<PFJetCollection> pfJets;
     iEvent.getByLabel(jetCollection_, pfJets);

     isAnyJetTooCloseToLepton=false;

     if (pfJets.isValid()) {
       //  
       // ===== riordina in pt i jets
       //

       for(reco::PFJetCollection::const_iterator jet = pfJets->begin(); 
	   jet!=pfJets->end (); jet++) {
	 double uncert=evaluateJECUncertainties(jet->pt(), jet->eta()); //pt of the jet changed, if JEC unc are "active".
	 double corr=(1.0+uncert*param);                                // "param" is defined in the cfi: ±1 -> sistematics, 0 normal
	 math::XYZTLorentzVector myjet(jet->px()*corr, jet->py()*corr, jet->pz()*corr, jet->p()*corr);
	 // check if the jet is equal to one of the isolated electrons

	 // check if the jet is equal to one of the isolated electrons
	 //cout<<uncert<<endl;
	 deltaPhi = fabs(jet->phi()-e1.Phi());
	 if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	 double deltaR1 = sqrt( deltaPhi*deltaPhi  + pow(jet->eta()-e1.Eta(),2) );
	 
	 deltaPhi = fabs(jet->phi()-e2.Phi());
	 if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	 double deltaR2= sqrt( deltaPhi*deltaPhi  + pow(jet->eta()-e2.Eta(),2) );

	 if (
	     // cut on the jet pt 
	     myjet.Pt()> minPtJets  
	     && fabs(jet->eta())<maxEtaJets
	     && jet->chargedEmEnergyFraction()<chargedEmEnergyFraction
	     && jet->neutralHadronEnergyFraction()<neutralHadronEnergyFraction
	     && jet->neutralEmEnergyFraction()<neutralEmEnergyFraction
	     && jet->chargedHadronEnergyFraction()>chargedHadronEnergyFraction
	     && jet->chargedMultiplicity()>chargedMultiplicity
	     ){ 
	   JetContainerFullEvent.push_back(myjet);
	   if (deltaR1 < deltaRConeJet || deltaR2 < deltaRConeJet){ isAnyJetTooCloseToLepton=true; cout<<"Jet Too Close (reco level), discarge the jet"<<endl;}
	   if (deltaR1 > deltaRConeJet && deltaR2 > deltaRConeJet) JetContainer.push_back(myjet);
	   /////////////////////
	   //Filling constituents of the reco jet   ; Debugging reco not gen events, 6% of total cases
	   /////////////////////
	 
	 
	   pat::PFCandidateFwdPtrCollection iparticlesRef;
	   std::vector< reco::PFCandidatePtr > iparticles = jet->getPFConstituents();
	   int i=0; double totalJetEnergy=0;
	   
	   fractionOfPFID0=0; fractionOfPFID1=0; fractionOfPFID2=0; fractionOfPFID3=0; fractionOfPFID4=0; fractionOfPFID5=0; fractionOfPFID6=0; fractionOfPFID7=0;
	   
	   for ( std::vector<reco::PFCandidatePtr>::const_iterator partBegin = iparticles.begin(), partEnd = iparticles.end(), ipart = partBegin;ipart != partEnd; ++ipart ) {
	     const reco::PFCandidate & cand = (*ipart);
	     double candEnergy=cand.pt();
	     double candEta=cand.eta();
	     double candPhi=cand.phi();
	     int candId=cand.particleId();
	     i++;
	     if (Debug) cout<<"component number "<<i<<" has energy "<<candEnergy<<" particle iD "<<candId<<" candEta "<<candEta<<" candPhi "<<candPhi<<endl;
	     if (candId==0) fractionOfPFID0+=candEnergy;
	     if (candId==1) fractionOfPFID1+=candEnergy;
	     if (candId==2) fractionOfPFID2+=candEnergy;
	     if (candId==3) fractionOfPFID3+=candEnergy;
	     if (candId==4) fractionOfPFID4+=candEnergy;
	     if (candId==5) fractionOfPFID5+=candEnergy;
	     if (candId==6) fractionOfPFID6+=candEnergy;
	     if (candId==7) fractionOfPFID7+=candEnergy;
	     totalJetEnergy+=candEnergy;
	   }
	   
	   if (totalJetEnergy>0){
	     fractionOfPFID0RecoJet.push_back(fractionOfPFID0/totalJetEnergy);
	     fractionOfPFID1RecoJet.push_back(fractionOfPFID1/totalJetEnergy);
	     fractionOfPFID2RecoJet.push_back(fractionOfPFID2/totalJetEnergy);
	     fractionOfPFID3RecoJet.push_back(fractionOfPFID3/totalJetEnergy);
	     fractionOfPFID4RecoJet.push_back(fractionOfPFID4/totalJetEnergy);
	     fractionOfPFID5RecoJet.push_back(fractionOfPFID5/totalJetEnergy);
	     fractionOfPFID6RecoJet.push_back(fractionOfPFID6/totalJetEnergy);
	     fractionOfPFID7RecoJet.push_back(fractionOfPFID7/totalJetEnergy);
	     
	     if (Debug) cout<<" Fractions: 0:"<<fractionOfPFID0/totalJetEnergy;
	     if (Debug) cout<<" 1:"<<fractionOfPFID1/totalJetEnergy; 
	     if (Debug) cout<<" 2:"<<fractionOfPFID2/totalJetEnergy; 
	     if (Debug) cout<<" 3:"<<fractionOfPFID3/totalJetEnergy; 
	     if (Debug) cout<<" 4:"<<fractionOfPFID4/totalJetEnergy; 
	     if (Debug) cout<<" 5:"<<fractionOfPFID5/totalJetEnergy; 
	     if (Debug) cout<<" 6:"<<fractionOfPFID6/totalJetEnergy; 
	     if (Debug) cout<<" 7:"<<fractionOfPFID7/totalJetEnergy;
	     if (Debug) cout<<" total energy:"<<totalJetEnergy<<endl;
	     
	   }
	 }
       }
       std::stable_sort(JetContainer.begin(),JetContainer.end(),GreaterPt()); 
       Jet_multiplicity=JetContainer.size();
       for (int k=0; k<Jet_multiplicity;k++){
	   if (k==0) {
	     jet1_pt=JetContainer[k].Pt();
	     jet1_eta=JetContainer[k].Eta();
	     jet1_phi=JetContainer[k].Phi();
	 }
	 if (k==1) {
	   jet2_pt=JetContainer[k].Pt();
	   jet2_eta=JetContainer[k].Eta();
	   jet2_phi=JetContainer[k].Phi();
	 }
	 if (k==2) {
	   jet3_pt=JetContainer[k].Pt();
	   jet3_eta=JetContainer[k].Eta();
	   jet3_phi=JetContainer[k].Phi();
	 }
	 if (k==3) {
	   jet4_pt=JetContainer[k].Pt();
	   jet4_eta=JetContainer[k].Eta();
	   jet4_phi=JetContainer[k].Phi();
	 }
	 if (k==4) {
	   jet5_pt=JetContainer[k].Pt();
	   jet5_eta=JetContainer[k].Eta();
	   jet5_phi=JetContainer[k].Phi();
	 }
	 if (k==5) {
	   jet6_pt=JetContainer[k].Pt();
	   jet6_eta=JetContainer[k].Eta();
	   jet6_phi=JetContainer[k].Phi();
	 }
	 if (k==6) {
	   jet7_pt=JetContainer[k].Pt();
	   jet7_eta=JetContainer[k].Eta();
	   jet7_phi=JetContainer[k].Phi();
	 }
       }
     }
     else{cout<<"No valid Jets Collection"<<endl;}
   }
   
   JetContainerFull=JetContainerFullEvent;

   /////////////////////
   /// Create a JetGenContainer, as done for the RecoJets, to create the jetpt variable, afterwards
   ////////////////////
   
   ///////////////////////////////////////
   
   
   if (usingMC){
     edm::Handle<reco::GenJetCollection> genJets;
     iEvent.getByLabel(genJetsCollection, genJets );
     int numbOfJets=0;     
     
    isAnyGenJetTooCloseToLepton=false;

     for (reco::GenJetCollection::const_iterator jet=genJets->begin();jet!=genJets->end();++jet){
       
   // check if the jet is equal to one of the isolated electrons

       double deltaR1=0;
       double deltaR2=0;

       if (leptonsGen.size()>0){
	 deltaPhi = fabs(jet->phi()-leptonsGen[0].Phi());
	 if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	 deltaR1 = sqrt( deltaPhi*deltaPhi  + pow(jet->eta()-leptonsGen[0].Eta(),2) );
	 
	 deltaPhi = fabs(jet->phi()-leptonsGen[1].Phi());
	 if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	 deltaR2= sqrt( deltaPhi*deltaPhi  + pow(jet->eta()-leptonsGen[1].Eta(),2) );
       }
       else{
       deltaR1=999;
       deltaR2=999;
       }

       leptonsGen.clear(); //Clearing the leptonGen to avoid memory leak!

       if (
	   // cut on the jet pt 
	   jet->pt()> genJetPtThreshold //A minimux allowed energy for GEN-JET!!!!!
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
	   if (Debug) cout<<"Charge of constituents->"<<(abs((**thepart).charge()))<<endl;
	   if ( (**thepart).charge()!=0 ){
	     isChargedJet=true;
	   }
	 }
	 if (Debug) cout<<"final charge->"<<isChargedJet<<endl;
	 TLorentzVector vec;
	 vec.SetPtEtaPhiM(jet->pt(),jet->eta(),jet->phi(),jet->mass());
	 if (isChargedJet) { //Cut for lepton proximity

	   if (Debug) cout<<"filling Container "<<jet->pt()<<endl; 
	   math::XYZTLorentzVector mygjet(jet->px(), jet->py(), jet->pz(), jet->p());
	   
	   GenJetContainerFullEvent.push_back(mygjet);

	   if (deltaR1 < deltaRConeJet || deltaR2 < deltaRConeJet){ 
	     isAnyGenJetTooCloseToLepton=true; 
	     cout<<"Jet Too Close (gen level), discarge the jet"<<endl;
	   }
	   
	   if (deltaR1 > deltaRConeJet && deltaR2 > deltaRConeJet){
	     GenJetContainerForAbsolutePtValue.push_back(mygjet);
	     GenJetContainer.push_back(vec); 
	   }
	 }
	 if (isChargedJet && (deltaR1 > deltaRConeJet && deltaR2 > deltaRConeJet) ) GenJetContainer2.push_back(vec); 
	 isChargedJet=false;
	 if (isChargedJet)  numbOfJets++;
	 if (Debug) cout<<"Jet has energy:"<<jet->pt()<<" and eta:"<<jet->eta()<<endl;
       }
     }
     if (Debug) cout<<"Jet Multiplicity (GEN) "<<numbOfJets<<endl;
     if (numbOfJets<100) {
       if (genZInAcceptance==1) Jet_multiplicity_gen=GenJetContainer.size();
       if (genZInAcceptance==0) Jet_multiplicity_gen=-9999;
     }
     //std::stable_sort(GenJetContainer.begin(),GenJetContainer.end(),GreaterPt()); 
   }

   
      ////// Checking also if the Z boson has decayed int taus or muons, and then misreconstructed!
   
   isMugen=false;
   isTaugen=false;
   
   if (usingMC){
     int response=isTauOrMu(genPart);
     if (response==1) isTaugen=true; // if response is 1 is a tau, see function isTauOrMu
     if (response==2) isMugen=true; // if 2 is a muon
   }

      //bUILDING THE Z GEN BOSON

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
	if (isSherpa) {
	   ele_gen.SetPxPyPzE(1,1,1,1); 
	   ele_gen_vec.push_back(ele_gen);
	   ele_gen_vec.push_back(ele_gen);
	}
      }


      ///////////////////
      ///// Matching Gen-RECO
      ///////////////////
      
      if (usingMC){
	// Loop sui RecoGet ordinati in pt
	std::vector <double> jetpt_gen; 
	std::vector <double> jeteta_gen;
	std::vector <double> jetphi_gen;
	std::vector <double> vectordeltaRRecoGenJet;
	//int jetRecoIndex=0;

	for (std::vector<math::XYZTLorentzVector>::const_iterator jet = JetContainer.begin (); jet != JetContainer.end (); jet++) {
	  // Calcolare il DeltaR verso tutti i GenJet
	  double deltaRGenReco=0.5;
	  double matchedGJetpt=-9999;
          double matchedGJeteta=-9999;
          double matchedGJetphi=-9999;

	  //jetRecoIndex++;
	  unsigned int matchedGenJetIndex=0;
	  int GenJetIndex=0;

	  //to avoid gen jet duplication
	  int JetContainerSize=JetContainer.size();
	  int GenJetContainerSize=GenJetContainer.size();
	  if (Debug) cout<<"JetContainerSize "<<JetContainerSize<<" GenJetContainerSize "<<GenJetContainerSize<<endl;

	  if (Debug) cout<<"reco jet pt in the loop. Starting the match for jet pt "<<jet->pt()<<" and eta "<<jet->eta()<<endl;
	  //jetPtVector.push_back(jet->Pt());
	  

	  for (std::vector<TLorentzVector>::const_iterator gjet = GenJetContainer.begin (); gjet != GenJetContainer.end (); gjet++) {
	    if (Debug) cout<<"gen jet pt in the loop. Starting the match for gen jet pt "<<gjet->Pt()<<" and eta "<<gjet->Eta()<<endl;
	  GenJetIndex++;
	     deltaPhi = fabs(jet->phi()-gjet->Phi());
	     if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	     double deltaRswap= sqrt( pow(jet->eta()-gjet->Eta(),2)+pow(deltaPhi,2) );
	     if (deltaRswap < deltaRGenReco) { //to avoid gen jet duplication
		deltaRGenReco=deltaRswap;
		matchedGJetpt=gjet->Pt();
		matchedGJeteta=gjet->Eta();
		matchedGJetphi=gjet->Phi();
		matchedGenJetIndex=GenJetIndex;
		if (Debug) cout<<"inside->Gen Jet Matched: pt->"<<matchedGJetpt<<" and eta->"<<matchedGJeteta<<" and with deltaR of "<<deltaRGenReco<<endl;
	     }
	     //if (deltaRswap>0.1) {
	     //jetRecoIndex--;
	     //}
	  }
	  vectordeltaRRecoGenJet.push_back(deltaRGenReco);
	  jetpt_gen.push_back(matchedGJetpt);
          jeteta_gen.push_back(matchedGJeteta);
          jetphi_gen.push_back(matchedGJetphi);
	  if (deltaRGenReco<0.5) GenJetContainer.erase(GenJetContainer.begin()+matchedGenJetIndex-1);
	  if (Debug) cout<<"Gen Jet Matched: pt->"<<matchedGJetpt<<" and eta->"<<matchedGJeteta<<" and phi "<<matchedGJetphi<<" and with deltaR of "<<deltaRGenReco<<endl;
	}
	
	deltaRRecoGenJet=vectordeltaRRecoGenJet;
	// In the above loop, in jetpt_gen you have the collection of gen jets matched by the detector. Now evaluating the viceversa,
	// jets generated > 30 but not reconstructed
	
	if (GenJetContainer.size()>0){    // check if some gen jets are somehow missing... 
	  if (Debug) cout<<"There are more genjets than jetReco. # matched jets->"<<jetpt_gen.size()<<" # jets gen->"<<GenJetContainer.size()<<" you will see the entire list of jets, for residual matching"<<endl;
	  for (std::vector<TLorentzVector>::const_iterator gjet = GenJetContainer.begin (); gjet != GenJetContainer.end (); gjet++) {
	    if (Debug) cout<<"gen jet pt->"<<gjet->Pt()<<" and eta->"<<gjet->Eta()<<endl;
	    bool isAgoodJet=false;
	    if (gjet->Pt()>genJetPtThreshold && fabs(gjet->Eta())<genJetEtaThreshold ){ // it should be above thresholds.. ADD the CHARGE information!
	      isAgoodJet=true; // it has at least one charged track
	    }
	    if (isAgoodJet){
	      if (Debug) cout<<"this is a overthreshold gen jet!"<<endl;
	      //bool matchedalready=false;
	      //for (unsigned int k=0; k < jetpt_gen.size(); k++){
	      //Check if it has already been added
	      //cout<<"loop per vedere i jet gia' matchiati. jetpt_gen->"<<jetpt_gen[k]<<" and jet Pt del loop "<<gjet->Pt()<<endl;
	      //if (jetpt_gen[k]==gjet->Pt()) {
	      //matchedalready=true;
	      // cout<<"jet gia' presente!! non necessita inserimento aggiuntivo "<<endl;
	      ///}
	      //}
	      //if (!matchedalready) {
	      jetpt_gen.push_back(gjet->Pt());
	      jeteta_gen.push_back(gjet->Eta());
	      jetphi_gen.push_back(gjet->Phi());
	      //if (Debug) cout<<"adding JET not reconstructed! pt->"<<gjet->Pt()<<" eta->"<<gjet->Eta()<<endl;
	      //}
	      //else if (Debug) cout<<"gen jet already stored!"<<endl;
	    }
	  }
	}
	int gvectorsize=jetpt_gen.size();
	if (Debug) cout<<"Gen Jet found->"<<gvectorsize<<" size of JetContainer->"<<JetContainer.size()<<endl;

	//genJetPtVector=jetpt_gen; // If works, cancel th following lines

	//Storing absolute information about jet Pt (sorting) it in pt!
	std::stable_sort(GenJetContainerForAbsolutePtValue.begin(),GenJetContainerForAbsolutePtValue.end(),GreaterPt()); 

       for (unsigned int kk=0; kk<GenJetContainerForAbsolutePtValue.size();kk++){

	 if (kk==0) jet1_pt_gen_abs=GenJetContainerForAbsolutePtValue[0].Pt();
	 if (kk==1) jet2_pt_gen_abs=GenJetContainerForAbsolutePtValue[1].Pt();
	 if (kk==2) jet3_pt_gen_abs=GenJetContainerForAbsolutePtValue[2].Pt();
	 if (kk==3) jet4_pt_gen_abs=GenJetContainerForAbsolutePtValue[3].Pt();
	 if (kk==4) jet5_pt_gen_abs=GenJetContainerForAbsolutePtValue[4].Pt();
	 if (kk==5) jet6_pt_gen_abs=GenJetContainerForAbsolutePtValue[5].Pt();
	 if (kk==6) jet7_pt_gen_abs=GenJetContainerForAbsolutePtValue[6].Pt();

	 if (kk==0) jet1_eta_gen_abs=GenJetContainerForAbsolutePtValue[0].Eta();
	 if (kk==1) jet2_eta_gen_abs=GenJetContainerForAbsolutePtValue[1].Eta();
	 if (kk==2) jet3_eta_gen_abs=GenJetContainerForAbsolutePtValue[2].Eta();
	 if (kk==3) jet4_eta_gen_abs=GenJetContainerForAbsolutePtValue[3].Eta();
	 if (kk==4) jet5_eta_gen_abs=GenJetContainerForAbsolutePtValue[4].Eta();
	 if (kk==5) jet6_eta_gen_abs=GenJetContainerForAbsolutePtValue[5].Eta();
	 if (kk==6) jet7_eta_gen_abs=GenJetContainerForAbsolutePtValue[6].Eta();
       }

       //Storing matched jets

	if (gvectorsize>0) {
	  jet1_pt_gen=jetpt_gen[0];
	  jet1_eta_gen=jeteta_gen[0];
	  jet1_phi_gen=jetphi_gen[0];
	}
	if (gvectorsize>1) {
	  jet2_pt_gen=jetpt_gen[1];
	  jet2_eta_gen=jeteta_gen[1];
	  jet2_phi_gen=jetphi_gen[1];
	}
	if (gvectorsize>2) {
	  jet3_pt_gen=jetpt_gen[2];
	  jet3_eta_gen=jeteta_gen[2];
	  jet3_phi_gen=jetphi_gen[2];
	}
	if (gvectorsize>3) {
	  jet4_pt_gen=jetpt_gen[3];
	  jet4_eta_gen=jeteta_gen[3];
	  jet4_phi_gen=jetphi_gen[3];
	}
	if (gvectorsize>4) {
	  jet5_pt_gen=jetpt_gen[4];
	  jet5_eta_gen=jeteta_gen[4];
	  jet5_phi_gen=jetphi_gen[4];
	}
	if (gvectorsize>5) {
	  jet6_pt_gen=jetpt_gen[5];
	  jet6_eta_gen=jeteta_gen[5];
	  jet6_phi_gen=jetphi_gen[5];
	}
	if (gvectorsize>6) {
	  jet7_pt_gen=jetpt_gen[6];
	  jet7_eta_gen=jeteta_gen[6];
	  jet7_phi_gen=jetphi_gen[6];
	}

	//cout<<"gen jet1 has pt "<<jet1_pt_gen<<" jet2 "<<jet2_pt_gen<<" jet3 "<<jet3_pt_gen<<" jet4_pt_gen "<<jet4_pt_gen<<endl;
      }

      //Store full information
      GenJetContainerFull=GenJetContainerFullEvent;

      GenJetContainer.clear();
      GenJetContainerFullEvent.clear();
      GenJetContainerForAbsolutePtValue.clear();
      //cout<<"------"<<endl;

      if (jet1_pt_gen==jet2_pt_gen && jet1_pt_gen>0) cout<<"Evento maleficissimo!!!"<<endl;      

      //Fill Unfolding rootuple!
      if (Debug) cout<<"After: recoZInAcceptance->"<<recoZInAcceptance<<" genZInAcceptance->"<<genZInAcceptance<<" Jet_multi->"<<Jet_multiplicity<<" Jet_multi_gen->"<<Jet_multiplicity_gen<<endl;
      if (Jet_multiplicity>0 || Jet_multiplicity_gen>0) treeUN_->Fill();


      ///////////////////////
      /// Filling Static Histos
      ///////////////////////

      int totJets=Jet_multiplicity;
      double inclHt=0;

      h_zYieldVsjets->Fill(totJets,myweight[0]);

      if (totJets >= 1) h_zEtaNjet1Incl->Fill(e_pair.Eta(),myweight[0]);
      if (totJets >= 2) h_zEtaNjet2Incl->Fill(e_pair.Eta(),myweight[0]);
      if (totJets >= 3) h_zEtaNjet3Incl->Fill(e_pair.Eta(),myweight[0]);
      if (totJets >= 4) h_zEtaNjet4Incl->Fill(e_pair.Eta(),myweight[0]);
      
      
      for (std::vector<math::XYZTLorentzVector>::const_iterator jet = JetContainer.begin ();
	   jet != JetContainer.end (); jet++) {
	inclHt += jet->Pt();
	
	if (totJets == 1) h_jetPtNjet1->Fill(jet->Pt(),myweight[0]);
	if (totJets == 2) h_jetPtNjet2->Fill(jet->Pt(),myweight[0]);
	if (totJets == 3) h_jetPtNjet3->Fill(jet->Pt(),myweight[0]);
	if (totJets == 4) h_jetPtNjet4->Fill(jet->Pt(),myweight[0]);
	
	if (totJets == 1) h_jetEtaNjet1->Fill(jet->Eta(),myweight[0]);
	if (totJets == 2) h_jetEtaNjet2->Fill(jet->Eta(),myweight[0]);
	if (totJets == 3) h_jetEtaNjet3->Fill(jet->Eta(),myweight[0]);
	if (totJets == 4) h_jetEtaNjet4->Fill(jet->Eta(),myweight[0]);
	
	if (totJets >= 1) h_jetPtNjet1Incl->Fill(jet->Pt(),myweight[0]);
	if (totJets >= 2) h_jetPtNjet2Incl->Fill(jet->Pt(),myweight[0]);
	if (totJets >= 3) h_jetPtNjet3Incl->Fill(jet->Pt(),myweight[0]);
	if (totJets >= 4) h_jetPtNjet4Incl->Fill(jet->Pt(),myweight[0]);
	
	if (totJets >= 1) h_jetEtaNjet1Incl->Fill(jet->Eta(),myweight[0]);
	if (totJets >= 2) h_jetEtaNjet2Incl->Fill(jet->Eta(),myweight[0]);
	if (totJets >= 3) h_jetEtaNjet3Incl->Fill(jet->Eta(),myweight[0]);
	if (totJets >= 4) h_jetEtaNjet4Incl->Fill(jet->Eta(),myweight[0]);
      }
      
      if (totJets >= 1) h_jetHtNjet1->Fill(inclHt,myweight[0]);
      if (totJets >= 2) h_jetHtNjet2->Fill(inclHt,myweight[0]);
      if (totJets >= 3) h_jetHtNjet3->Fill(inclHt,myweight[0]);
      if (totJets >= 4) h_jetHtNjet4->Fill(inclHt,myweight[0]);
      
      
      




      ////////////////////
      // CHS and PU residual effect in jets
      ////////////////////


      ///////////////////
      //Analtysis on reco but not gen jet. Caracterization over the full PFCandidates!!!!!!!!!!!za
      ////////////////


      Handle<reco::PFCandidateCollection> pfCandidatesReco;
      iEvent.getByLabel("particleFlow", pfCandidatesReco);

      reco::PFCandidateCollection pfReco, pfReReco;  
      
      // to sort, one needs to copy
      pfReco=*pfCandidatesReco;
      sort(pfReco.begin(),pfReco.end(),greaterPtJet);

      // 0 -> Unknown
      // 1 -> charged hadron
      // 2,3 -> ele,mu
      // 4 -> gamma
      // 5 -> neautral hadron 
      // 6 -> hadronic energy in HF
      // 7 -> electrom. energy in HF

      
      if (jet1_pt>30 && jet1_pt_gen<0){
	if (Debug) cout<<"Caso spinoso (see above). jet1_pt "<<jet1_pt<<" , eta "<<jet1_eta<<" while jet1_gen "<<jet1_pt_gen<<endl;
      }
      /*
	for( unsigned i=0; i<pfCandidatesReco->size(); i++ ) {
	  const reco::PFCandidate & cand = (pfReco)[i];
	double candEnergy=cand.energy();
	double candEta=cand.eta();
	double candPhi=cand.phi();
	int candId=cand.particleId();

	double deltaPhiJetParton = fabs(jet1_phi-candPhi);
	if (deltaPhiJetParton > acos(-1)) deltaPhiJetParton= 2*acos(-1) - deltaPhiJetParton;
	double deltaR1 = sqrt( deltaPhiJetParton*deltaPhiJetParton  + pow(jet1_eta-candEta,2) );

	cout<<"component number "<<i<<" has energy "<<candEnergy<<" deltaR "<<deltaR1<<" particle iD "<<candId;
	if (deltaR1<0.5 ) cout<<" ***close to jet <0.5 in eta *** "<<endl;
	else cout<<endl; 
	}
      }
      */

      ///////////////////////
      //Investigating on jet reco "components"
     ///////////////////

	/*     
     Handle<PFJetCollection> pfJetsCharac;
     iEvent.getByLabel(jetCollection_, pfJetsCharac);
     if (pfJetsCharac.isValid()) {

       //  
       // ===== riordina in pt i jets
       //

       for(reco::PFJetCollection::const_iterator jet = pfJetsCharac->begin(); jet!=pfJetsCharac->end (); jet++) {
	 cout<<"Loop on reco jet constituents directly. Jet with pt="<<jet->pt()<<endl;
	 pat::PFCandidateFwdPtrCollection iparticlesRef;
	 std::vector< reco::PFCandidatePtr > iparticles = jet->getPFConstituents();
	 int i=0;
	 
	 fractionOfPFID0=0;
	 fractionOfPFID1=0;
	 fractionOfPFID2=0;
	 fractionOfPFID3=0;
	 fractionOfPFID4=0;
	 fractionOfPFID5=0;
	 fractionOfPFID6=0;
	 fractionOfPFID7=0;
	 double totalJetEnergy=0;

	 for ( std::vector<reco::PFCandidatePtr>::const_iterator partBegin = iparticles.begin(), partEnd = iparticles.end(), ipart = partBegin;ipart != partEnd; ++ipart ) {
	   const reco::PFCandidate & cand = (*ipart);
	   double candEnergy=cand.pt();
	   double candEta=cand.eta();
	   double candPhi=cand.phi();
	   int candId=cand.particleId();
	   i++;
	   cout<<"component number "<<i<<" has energy "<<candEnergy<<" particle iD "<<candId<<" candEta "<<candEta<<" candPhi "<<candPhi<<endl;
	   if (candId==0) fractionOfPFID0+=candEnergy;
	   if (candId==1) fractionOfPFID1+=candEnergy;
	   if (candId==2) fractionOfPFID2+=candEnergy;
	   if (candId==3) fractionOfPFID3+=candEnergy;
	   if (candId==4) fractionOfPFID4+=candEnergy;
	   if (candId==5) fractionOfPFID5+=candEnergy;
	   if (candId==6) fractionOfPFID6+=candEnergy;
	   if (candId==7) fractionOfPFID7+=candEnergy;
	   totalJetEnergy+=candEnergy;
	 }
	 fractionOfPFID0RecoJet.push_back(fractionOfPFID0/totalJetEnergy);
	 fractionOfPFID1RecoJet.push_back(fractionOfPFID1/totalJetEnergy);
	 fractionOfPFID2RecoJet.push_back(fractionOfPFID2/totalJetEnergy);
	 fractionOfPFID3RecoJet.push_back(fractionOfPFID3/totalJetEnergy);
	 fractionOfPFID4RecoJet.push_back(fractionOfPFID4/totalJetEnergy);
	 fractionOfPFID5RecoJet.push_back(fractionOfPFID5/totalJetEnergy);
	 fractionOfPFID6RecoJet.push_back(fractionOfPFID6/totalJetEnergy);
	 fractionOfPFID7RecoJet.push_back(fractionOfPFID7/totalJetEnergy);
	 cout<<" Fractions: 0:"<<fractionOfPFID0/totalJetEnergy;
	 cout<<" 1:"<<fractionOfPFID1/totalJetEnergy; 
	 cout<<" 2:"<<fractionOfPFID2/totalJetEnergy; 
	 cout<<" 3:"<<fractionOfPFID3/totalJetEnergy; 
	 cout<<" 4:"<<fractionOfPFID4/totalJetEnergy; 
	 cout<<" 5:"<<fractionOfPFID5/totalJetEnergy; 
	 cout<<" 6:"<<fractionOfPFID6/totalJetEnergy; 
	 cout<<" 7:"<<fractionOfPFID7/totalJetEnergy;
	 cout<<" total energy:"<<totalJetEnergy<<endl; 
       }
     }
	*/
}


// ------------ method called once each job just before starting event loop  ------------
void 
jetValidationUnfolding::beginJob()
{

  //TFile and TTree initialization
   
   treeUN_= new TTree(rootuplaname.c_str(),rootuplaname.c_str());
  
  //EB PileUp REMOVED

  treeUN_->Branch("evWeight",&evWeight);
  treeUN_->Branch("evWeightSherpa",&evWeightSherpa);
  treeUN_->Branch("Z_pt",&Z_pt);
  treeUN_->Branch("Z_y",&Z_y);
  treeUN_->Branch("Jet_multiplicity",&Jet_multiplicity);
  treeUN_->Branch("Z_pt_gen",&Z_pt_gen);
  treeUN_->Branch("Z_y_gen",&Z_y_gen);
  treeUN_->Branch("Jet_multiplicity_gen",&Jet_multiplicity_gen);
  treeUN_->Branch("jet1_pt_gen",&jet1_pt_gen);
  treeUN_->Branch("jet2_pt_gen",&jet2_pt_gen);
  treeUN_->Branch("jet3_pt_gen",&jet3_pt_gen);
  treeUN_->Branch("jet4_pt_gen",&jet4_pt_gen);
  treeUN_->Branch("jet5_pt_gen",&jet5_pt_gen);
  treeUN_->Branch("jet6_pt_gen",&jet6_pt_gen);
  treeUN_->Branch("jet7_pt_gen",&jet7_pt_gen);

  treeUN_->Branch("jet1_pt_gen_abs",&jet1_pt_gen_abs);
  treeUN_->Branch("jet2_pt_gen_abs",&jet2_pt_gen_abs);
  treeUN_->Branch("jet3_pt_gen_abs",&jet3_pt_gen_abs);
  treeUN_->Branch("jet4_pt_gen_abs",&jet4_pt_gen_abs);
  treeUN_->Branch("jet5_pt_gen_abs",&jet5_pt_gen_abs);
  treeUN_->Branch("jet6_pt_gen_abs",&jet6_pt_gen_abs);
  treeUN_->Branch("jet7_pt_gen_abs",&jet7_pt_gen_abs);

  treeUN_->Branch("jet1_eta_gen_abs",&jet1_eta_gen_abs);
  treeUN_->Branch("jet2_eta_gen_abs",&jet2_eta_gen_abs);
  treeUN_->Branch("jet3_eta_gen_abs",&jet3_eta_gen_abs);
  treeUN_->Branch("jet4_eta_gen_abs",&jet4_eta_gen_abs);
  treeUN_->Branch("jet5_eta_gen_abs",&jet5_eta_gen_abs);
  treeUN_->Branch("jet6_eta_gen_abs",&jet6_eta_gen_abs);
  treeUN_->Branch("jet7_eta_gen_abs",&jet7_eta_gen_abs);

  treeUN_->Branch("jet1_eta_gen",&jet1_eta_gen);
  treeUN_->Branch("jet2_eta_gen",&jet2_eta_gen);
  treeUN_->Branch("jet3_eta_gen",&jet3_eta_gen);
  treeUN_->Branch("jet4_eta_gen",&jet4_eta_gen);
  treeUN_->Branch("jet5_eta_gen",&jet5_eta_gen);
  treeUN_->Branch("jet6_eta_gen",&jet6_eta_gen);
  treeUN_->Branch("jet7_eta_gen",&jet6_eta_gen);

  treeUN_->Branch("jet1_phi_gen",&jet1_phi_gen);
  treeUN_->Branch("jet2_phi_gen",&jet2_phi_gen);
  treeUN_->Branch("jet3_phi_gen",&jet3_phi_gen);
  treeUN_->Branch("jet4_phi_gen",&jet4_phi_gen);
  treeUN_->Branch("jet5_phi_gen",&jet5_phi_gen);
  treeUN_->Branch("jet6_phi_gen",&jet6_phi_gen);
  treeUN_->Branch("jet7_phi_gen",&jet6_phi_gen);

  //treeUN_->Branch("jetPtVector",&jetPtVector);
  //treeUN_->Branch("genJetPtVector",&genJetPtVector);

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
  treeUN_->Branch("jet5_pt",&jet5_pt);
  treeUN_->Branch("jet6_pt",&jet6_pt);
  treeUN_->Branch("jet7_pt",&jet7_pt);

  treeUN_->Branch("jet1_eta",&jet1_eta);
  treeUN_->Branch("jet2_eta",&jet2_eta);
  treeUN_->Branch("jet3_eta",&jet3_eta);
  treeUN_->Branch("jet4_eta",&jet4_eta);
  treeUN_->Branch("jet5_eta",&jet5_eta);
  treeUN_->Branch("jet6_eta",&jet6_eta);
  treeUN_->Branch("jet7_eta",&jet7_eta);

  treeUN_->Branch("jet1_phi",&jet1_phi);
  treeUN_->Branch("jet2_phi",&jet2_phi);
  treeUN_->Branch("jet3_phi",&jet3_phi);
  treeUN_->Branch("jet4_phi",&jet4_phi);
  treeUN_->Branch("jet1_mass",&jet1_mass);
  treeUN_->Branch("jet2_mass",&jet2_mass);
  treeUN_->Branch("jet3_mass",&jet3_mass);
  treeUN_->Branch("jet4_mass",&jet4_mass);
  treeUN_->Branch("jetHt",&jetHt);
  treeUN_->Branch("isMugen",&isMugen);
  treeUN_->Branch("isTaugen",&isTaugen);
  treeUN_->Branch("z_mass",&z_mass);
  treeUN_->Branch("isElectron",&isElectron);
  treeUN_->Branch("invMass_gen",&invMass_gen);
  treeUN_->Branch("l1_eta_gen",&l1_eta_gen);
  treeUN_->Branch("l2_eta_gen",&l2_eta_gen);
  treeUN_->Branch("l1_pt_gen",&l1_pt_gen);
  treeUN_->Branch("l2_pt_gen",&l2_pt_gen);
  treeUN_->Branch("genZInAcceptance",&genZInAcceptance);
  treeUN_->Branch("recoZInAcceptance",&recoZInAcceptance);
  treeUN_->Branch("deltaRRecoGenJet",&deltaRRecoGenJet);
  treeUN_->Branch("numberOfVertices",&numberOfVertices);
  treeUN_->Branch("isAnyJetTooCloseToLepton",&isAnyJetTooCloseToLepton);
  treeUN_->Branch("isAnyGenJetTooCloseToLepton",&isAnyGenJetTooCloseToLepton);
  treeUN_->Branch("JetContainerFull",&JetContainerFull);
  treeUN_->Branch("GenJetContainerFull",&GenJetContainerFull);

  treeUN_->Branch("fractionOfPFID0RecoJet",&fractionOfPFID0RecoJet);
  treeUN_->Branch("fractionOfPFID1RecoJet",&fractionOfPFID1RecoJet);
  treeUN_->Branch("fractionOfPFID2RecoJet",&fractionOfPFID2RecoJet);
  treeUN_->Branch("fractionOfPFID3RecoJet",&fractionOfPFID3RecoJet);
  treeUN_->Branch("fractionOfPFID4RecoJet",&fractionOfPFID4RecoJet);
  treeUN_->Branch("fractionOfPFID5RecoJet",&fractionOfPFID5RecoJet);
  treeUN_->Branch("fractionOfPFID6RecoJet",&fractionOfPFID6RecoJet);
  treeUN_->Branch("fractionOfPFID7RecoJet",&fractionOfPFID7RecoJet);

  cout<<endl;
  cout<<"##############################"<<endl;
  cout<<"#   Jet Studies Parameters   #"<<endl;
  cout<<"##############################"<<endl;
  cout<<endl; 
  cout<<"Jet Min Pt="<<minPtJets<<", within |eta|<"<<maxEtaJets<<endl;
  cout<<"DR isolation cone="<<deltaRCone<<", at gen Level="<<deltaConeGen<<endl;
  cout<<"chargedEmEnergyFraction<"<<chargedEmEnergyFraction<<endl;
  cout<<"neutralHadronEnergyFraction<"<<neutralHadronEnergyFraction<<endl;
  cout<<"neutralEmEnergyFraction<"<<neutralEmEnergyFraction<<endl;
  cout<<"chargedHadronEnergyFraction>"<<chargedHadronEnergyFraction<<endl;
  cout<<"chargedMultiplicity>"<<chargedMultiplicity<<endl;
  cout<<"JEC scale Uncertainty parameter "<<param<<endl;
  cout<<endl;



  //Initilize the JEDC
  p = new JetCorrectorParameters("JEC11_V12_AK5PF_UncertaintySources.txt", "Total");
  //p = new JetCorrectorParameters("JEC11_V12_UncertaintyDataMC_AK5PF.txt", "Total");
  t = new JetCorrectionUncertainty(*p);  
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
jetValidationUnfolding::endJob() 
{
    
 //Histograms
  h_weights->GetXaxis()->SetTitle("Weight");
  h_weightsSherpa->GetXaxis()->SetTitle("WeightSherpa");
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
 h_jetPtNjet1->GetXaxis()->SetTitle("p_{T} leading jet");
 h_jetPtNjet2->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet2->GetXaxis()->SetTitle("p_{T} subleading jet");
 h_jetPtNjet3->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet3->GetXaxis()->SetTitle("p_{T} subsubleading jet");
 h_jetPtNjet4->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet4->GetXaxis()->SetTitle("p_{T} subsubsubleading jet");

 h_jetEtaNjet1->GetYaxis()->SetTitle("N_{jets}");
 h_jetEtaNjet1->GetXaxis()->SetTitle("#eta leading jet");
 h_jetEtaNjet2->GetYaxis()->SetTitle("N_{jets}");
 h_jetEtaNjet2->GetXaxis()->SetTitle("#eta subleading jet");
 h_jetEtaNjet3->GetYaxis()->SetTitle("N_{jets}");
 h_jetEtaNjet3->GetXaxis()->SetTitle("#eta subsubleading jet");
 h_jetEtaNjet4->GetYaxis()->SetTitle("N_{jets}");
 h_jetEtaNjet4->GetXaxis()->SetTitle("#eta subsubsubleading jet");

 h_jetHtNjet1->GetYaxis()->SetTitle("N_{events}");
 h_jetHtNjet1->GetXaxis()->SetTitle("Ht leading jet");
 h_jetHtNjet2->GetYaxis()->SetTitle("N_{events}");
 h_jetHtNjet2->GetXaxis()->SetTitle("Ht subleading jet");
 h_jetHtNjet3->GetYaxis()->SetTitle("N_{events}");
 h_jetHtNjet3->GetXaxis()->SetTitle("Ht subsubleading jet");
 h_jetHtNjet4->GetYaxis()->SetTitle("N_{events}");
 h_jetHtNjet4->GetXaxis()->SetTitle("Ht subsubsubleading jet");

 h_jetPtNjet1Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet1Incl->GetXaxis()->SetTitle("p_{T} leading jet");
 h_jetPtNjet2Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet2Incl->GetXaxis()->SetTitle("p_{T} subleading jet");
 h_jetPtNjet3Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet3Incl->GetXaxis()->SetTitle("p_{T} subsubleading jet");
 h_jetPtNjet4Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtNjet4Incl->GetXaxis()->SetTitle("p_{T} subsubsubleading jet");

 h_jetEtaNjet1Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetEtaNjet1Incl->GetXaxis()->SetTitle("#eta leading jet");
 h_jetEtaNjet2Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetEtaNjet2Incl->GetXaxis()->SetTitle("#eta subleading jet");
 h_jetEtaNjet3Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetEtaNjet3Incl->GetXaxis()->SetTitle("#eta subsubleading jet");
 h_jetEtaNjet4Incl->GetYaxis()->SetTitle("N_{jets}");
 h_jetEtaNjet4Incl->GetXaxis()->SetTitle("#eta subsubsubleading jet");

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

    if (doPlotsJetComposition){
       h_idPdgAroundE->GetXaxis()->SetTitle("particle type"); 
       h_idPdgAroundE->GetYaxis()->SetTitle("N_{particles}");
       h_idPdgJet->GetXaxis()->SetTitle("particle type");
       h_idPdgJet->GetYaxis()->SetTitle("N_{jets}");
    }
 }  

}

// Evalaute the systematics on JEC
double jetValidationUnfolding::evaluateJECUncertainties(double jetpt,double jeteta){
  
  t->setJetPt(jetpt);
  t->setJetEta(jeteta);
  double uncert = t->getUncertainty(true);

  //Increase the efficiencies by an extra factor, according to https://hypernews.cern.ch/HyperNews/CMS/get/jes/316.html
  if (fabs(jeteta)<1.3 ) uncert+=0.01;
  else uncert+=0.015;
  return uncert;
}

int jetValidationUnfolding::isTauOrMu(edm::Handle<GenParticleCollection> genParticlesCollection)
{
   bool theFilter=false;
   int ntausFromZ(0);
   int ntaus(0);
   int nmuFromZ(0);

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
	   std::cout<<"found a tau from Z"<<std::endl;
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

// ------------ method called when starting to processes a run  ------------
void 
jetValidationUnfolding::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
jetValidationUnfolding::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
jetValidationUnfolding::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
jetValidationUnfolding::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(jetValidationUnfolding);
