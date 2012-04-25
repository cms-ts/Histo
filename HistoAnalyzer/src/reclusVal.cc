// -*- C++ -*-
//

#include "Histo/HistoAnalyzer/interface/reclusVal.h"
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

double
reclusVal::distR(TLorentzVector a ,math::XYZTLorentzVector b){

   double deltaPhi = fabs(a.Phi()-b.Phi());
   if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
   double delta = sqrt( deltaPhi*deltaPhi  + ((a.Eta()-b.Eta())*(a.Eta()-b.Eta())));
   return delta;
}

// ------------ method called for each event  ------------
void
reclusVal::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  bool Debug=false;
  
  int runNumber = -99;
  int eventNumber= -99;
  if (testMC){
     runNumber = iEvent.id().run();
     eventNumber = iEvent.id().event();
     //cout << "run = "<< runNumber<< " ; event number = "<< eventNumber<<endl;
  }
  ////////
  //  Get The Weights
  ///////

  edm::Handle< std::vector<float> > weight;
  iEvent.getByLabel("demo","EventWeight",weight);
  const std::vector<float> & myweight=*weight;

   //IMPORTANTE  
   numberOfVertices=0;

   ///////////////////////
   ///// Vertex Analysis
   ///////////////////////

   edm::Handle<reco::VertexCollection> Vertexes;
   iEvent.getByLabel(VertexCollection_, Vertexes);
   numberOfVertices = Vertexes->size();  
   //h_nVtx->Fill(numberOfVertices,myweight[0]);
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
   
   // edm::Handle<reco::GenParticleCollection> genPart;
//    if (usingMC){
//       iEvent.getByLabel (genParticleCollection_,genPart);
//    }

   edm::Handle<reco::PFCandidateCollection> pfPart;
   iEvent.getByLabel (pflowCollection_,pfPart);
  

   if (checkGoodEPairSize==2)
 
   {   
     double dist1=99999;
     double dist2=99999;
     math::XYZTLorentzVector jet1,jet2;
      // ================================
      // FIll the Weights info
      // ================================
      double wei=myweight[0];
      h_weights->Fill(wei);
      // ================================

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

   
      // ================================
     
      ///////////////////
      /// Jet Validation
      ///////////////////
      
      std::vector<math::XYZTLorentzVector> JetContainerBV, JetContainerAV, JetContainerPU, JetContainerRC;  
      JetContainerBV.clear();  
      JetContainerAV.clear();  
      JetContainerPU.clear();  
      JetContainerRC.clear();
      Handle<PFJetCollection> pfJets, pfJetsPU, pfJetsRC;
      iEvent.getByLabel(jetCollection_, pfJets);
      iEvent.getByLabel(jetCollectionPU_, pfJetsPU);
      iEvent.getByLabel(jetCollectionRC_, pfJetsRC);

      if (pfJets.isValid()) {
         for(reco::PFJetCollection::const_iterator jet = pfJets->begin(); 
	     jet!=pfJets->end (); jet++) {
	    
	    // check if the jet is equal to one of the isolated electrons
	    double deltaR1= distR(e1,(jet->p4()));
	    double deltaR2= distR(e2,(jet->p4()));
	    if (// cut on the jet pt 
		jet->pt()> minPtJets
		&& fabs(jet->eta())<maxEtaJets
		&& jet->chargedEmEnergyFraction()<chargedEmEnergyFraction
		&& jet->neutralHadronEnergyFraction()<neutralHadronEnergyFraction
		&& jet->neutralEmEnergyFraction()<neutralEmEnergyFraction
		&& jet->chargedHadronEnergyFraction()>chargedHadronEnergyFraction
		&& jet->chargedMultiplicity()>chargedMultiplicity
	       ){ 
	       JetContainerBV.push_back(jet->p4());
	       if (deltaR1 > deltaRCone && deltaR2 > deltaRCone) {JetContainerAV.push_back(jet->p4());}
	    }
	 }
         std::stable_sort(JetContainerBV.begin(),JetContainerBV.end(),GreaterPt()); 
         std::stable_sort(JetContainerAV.begin(),JetContainerAV.end(),GreaterPt()); 
      }
      else{cout<<"No valid Jets Collection"<<endl;}

      if (pfJetsPU.isValid()) {
         for(reco::PFJetCollection::const_iterator jet = pfJetsPU->begin(); 
	     jet!=pfJetsPU->end (); jet++) {
	    
	    // check if the jet is equal to one of the isolated electrons
	    double deltaR1= distR(e1,(jet->p4()));
	    double deltaR2= distR(e2,(jet->p4()));
	    if (// cut on the jet pt 
		jet->pt()> minPtJets
		&& fabs(jet->eta())<maxEtaJets
		&& jet->chargedEmEnergyFraction()<chargedEmEnergyFraction
		&& jet->neutralHadronEnergyFraction()<neutralHadronEnergyFraction
		&& jet->neutralEmEnergyFraction()<neutralEmEnergyFraction
		&& jet->chargedHadronEnergyFraction()>chargedHadronEnergyFraction
		&& jet->chargedMultiplicity()>chargedMultiplicity
		&& deltaR1 > deltaRCone && deltaR2 > deltaRCone
	       ){ 
	       JetContainerPU.push_back(jet->p4());
	    }
	 }
         std::stable_sort(JetContainerPU.begin(),JetContainerPU.end(),GreaterPt()); 
      }
      else{cout<<"No valid Jets Collection PU"<<endl;}

      if (pfJetsRC.isValid()) {
         for(reco::PFJetCollection::const_iterator jet = pfJetsRC->begin(); 
	     jet!=pfJetsRC->end (); jet++) {
	    
	    if (// cut on the jet pt 
		jet->pt()> minPtJets
		&& fabs(jet->eta())<maxEtaJets
		&& jet->chargedEmEnergyFraction()<chargedEmEnergyFraction
		&& jet->neutralHadronEnergyFraction()<neutralHadronEnergyFraction
		&& jet->neutralEmEnergyFraction()<neutralEmEnergyFraction
		&& jet->chargedHadronEnergyFraction()>chargedHadronEnergyFraction
		&& jet->chargedMultiplicity()>chargedMultiplicity
	       ){ 
	       JetContainerRC.push_back(jet->p4());
	    }
	 }
         std::stable_sort(JetContainerRC.begin(),JetContainerRC.end(),GreaterPt()); 
      }
      else{cout<<"reclusVal: No valid Jets Collection RC"<<endl;}
//

//------------------------------------------------------------------------------------------------- 
// study on discrepancy n jets *************************************************************************
//-------------------------------------------------------------------------------------------------
      
      bool passPU=false;
      bool passRC=false;
      bool passInclPU=false;
      bool passInclRC=false;
      if (JetContainerPU.size()==1) {
	 h_zPt_1jetPU->Fill(e_pair.Pt());
	 passPU=true;}
      if (JetContainerRC.size()==1) {
	 h_zPt_1jetRC->Fill(e_pair.Pt());
	 passRC=true;}
      if (JetContainerPU.size()>=1) {
	 h_zPt_1jetInclPU->Fill(e_pair.Pt());
	 passInclPU= true;}
      if (JetContainerRC.size()>=1) {
	 h_zPt_1jetInclRC->Fill(e_pair.Pt());
	 passInclRC=true;}

      if (testMC){
	 if (!(passPU && passRC) && (passPU || passRC) && e_pair.Pt()< 20){
	    cout << "-----------------------------------------------------------"<< endl;
	    cout << "zPt1jet - discrepancy in this run = "<< runNumber<< " ; event number = "<< eventNumber<<endl;
	    cout << "Number of PU jets = "<< JetContainerPU.size()<< " ; number of RC jets = "<<JetContainerRC.size() <<endl;
	    int kjet=1;
	    cout << "Z - pt = "<< e_pair.Pt() <<" - eta = "<<e_pair.Eta()<< " - phi = "<< e_pair.Phi()<< endl;
	    cout << "e1 - pt = "<< e1.Pt() <<" - eta = "<<e1.Eta()<< " - phi = "<< e1.Phi()<< endl;
	    cout << "e2 - pt = "<< e2.Pt() <<" - eta = "<<e2.Eta()<< " - phi = "<< e2.Phi()<< endl;
	    for(reco::PFJetCollection::const_iterator jet = pfJetsPU->begin(); 
		jet!=pfJetsPU->end (); jet++) {
	       cout << kjet << " PU jet - pt = "<<jet->pt()<<" - eta = "<<jet->eta()<<" - phi = "<<jet->phi()<<endl;
	       kjet++;
	    }
	    kjet=1;
	    for(reco::PFJetCollection::const_iterator jet = pfJetsRC->begin(); 
		jet!=pfJetsRC->end (); jet++) {
	       cout << kjet << " RC jet - pt = "<<jet->pt()<<" - eta = "<<jet->eta()<<" - phi = "<<jet->phi()<<endl;
	       kjet++;
	    }
	       
	 }
	 if (passInclPU && !passInclRC && e_pair.Pt()< 20){
	    cout << "-----------------------------------------------------------"<< endl;
	    cout << "zPt1jetIncl - discrepancy in this run = "<< runNumber<< " ; event number = "<< eventNumber<<endl;
	    cout << "Number of PU jets = "<< JetContainerPU.size()<< " ; number of RC jets = "<<JetContainerRC.size() <<endl;
	    int kjet=1;
	    cout << "Z - pt = "<< e_pair.Pt() <<" - eta = "<<e_pair.Eta()<< " - phi = "<< e_pair.Phi()<< endl;
	    cout << "e1 - pt = "<< e1.Pt() <<" - eta = "<<e1.Eta()<< " - phi = "<< e1.Phi()<< endl;
	    cout << "e2 - pt = "<< e2.Pt() <<" - eta = "<<e2.Eta()<< " - phi = "<< e2.Phi()<< endl;
	    for(reco::PFJetCollection::const_iterator jet = pfJetsPU->begin(); 
		jet!=pfJetsPU->end (); jet++) {
	       cout << kjet << " PU jet - pt = "<<jet->pt()<<" - eta = "<<jet->eta()<<" - phi = "<<jet->phi()<<endl;
	       kjet++;
	    }
	    kjet=1;
	    for(reco::PFJetCollection::const_iterator jet = pfJetsRC->begin(); 
		jet!=pfJetsRC->end (); jet++) {
	       cout << kjet << " RC jet - pt = "<<jet->pt()<<" - eta = "<<jet->eta()<<" - phi = "<<jet->phi()<<endl;
	       kjet++;
	    }
	 }
      }

//------------------------------------------------------------------------------------------------- 
// study on BEFORE VETO  jets *************************************************************************
//-------------------------------------------------------------------------------------------------
      double deltaEJ, deltaEE;
      double deltaPhi;
      dist1=999;
      dist2=999;
      for (std::vector<math::XYZTLorentzVector>::const_iterator jet = JetContainerBV.begin (); 
	   jet != JetContainerBV.end (); jet++) {
	 
	 deltaEJ= distR(e1,(*jet));
	 //cout <<"dist calcolata con la funzione = "<< deltaEJ<< " ; calcolata a mano = "<<
	 // sqrt(pow(e1.Phi()-jet->Phi(),2)+ pow(e1.Eta()-jet->Eta(),2))<< endl;
	 deltaEE = distR(e2,(*jet));
	 //if (deltaEJ<dist1 && deltaEE>0.3){
	 if (deltaEJ<dist1){
	    jet1=*jet;
	    dist1 = deltaEJ;
	 }
	 deltaEJ= distR(e2,(*jet));
	 deltaEE = distR(e1,(*jet));
	 //if (deltaEJ<dist2 && deltaEE>0.3){
	 if (deltaEJ<dist2){
	    jet2=*jet;
	    dist2 = deltaEJ;
	 }	 
      }
      if (JetContainerBV.size()>0){
	 // jet in the BARREL
	 if (fabs(jet1.Eta())<edgeEB){	    
	    deltaPhi = fabs(e1.Phi()-jet1.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_deltaEtaBV_EB->Fill(fabs(e1.Eta()-jet1.Eta()),myweight[0]);
	    if (distR(e1,jet1)<deltaRCone ||distR(e2,jet1)<deltaRCone){	       
	       h_deltaEtaBVe_EB->Fill(fabs(e1.Eta()-jet1.Eta()),myweight[0]);
	       h_totEtaBVe_EB->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    }else {
	       h_deltaEtaBVjet_EB->Fill(fabs(e1.Eta()-jet1.Eta()),myweight[0]);
	       h_totEtaBVjet_EB->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    }
	    h_totEtaBV_EB->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    if (fabs(e1.Eta()-jet1.Eta()) > 1.3 && fabs(e1.Eta()-jet1.Eta()) < 1.7){
	       h_cracksEtaBVe_EB->Fill(e1.Eta(),myweight[0]);
	       h_cracksEtaBVjet_EB->Fill(jet1.Eta(),myweight[0]);
	       h_cracksEtaBV_EB->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    }
	    if (fabs(e1.Eta()-jet1.Eta()) > 2.2 && fabs(e1.Eta()-jet1.Eta()) < 2.5){
	       h_cracks2EtaBVe_EB->Fill(e1.Eta(),myweight[0]);
	       h_cracks2EtaBVjet_EB->Fill(jet1.Eta(),myweight[0]);
	       h_cracks2EtaBV_EB->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    }
	    h_deltaPhiBV_EB->Fill(deltaPhi,myweight[0]);
	    h_deltaRBV_EB->Fill(dist1,myweight[0]);
	    h_deltaEtaPhiBV_EB->Fill(fabs(e1.Eta()-jet1.Eta()),deltaPhi,myweight[0]);
	 }
	 // jet in the ENDCAP
	 if (fabs(jet1.Eta())>edgeEB && fabs(jet1.Eta())<edgeEE){
	    deltaPhi = fabs(e1.Phi()-jet1.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_deltaEtaBV_EE->Fill(fabs(e1.Eta()-jet1.Eta()),myweight[0]);
	    if (distR(e1,jet1)<deltaRCone ||distR(e2,jet1)<deltaRCone ){	       
	       h_deltaEtaBVe_EE->Fill(fabs(e1.Eta()-jet1.Eta()),myweight[0]);
	       h_totEtaBVe_EE->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    }else {
	       h_deltaEtaBVjet_EE->Fill(fabs(e1.Eta()-jet1.Eta()),myweight[0]);
	       h_totEtaBVjet_EE->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    }
	    h_totEtaBV_EE->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    h_deltaPhiBV_EE->Fill(deltaPhi,myweight[0]);
	    h_deltaRBV_EE->Fill(dist1,myweight[0]);
	    h_deltaEtaPhiBV_EE->Fill(fabs(e1.Eta()-jet1.Eta()),deltaPhi,myweight[0]);	 
	 } 
	 // jet in the BARREL
	 if (fabs(jet2.Eta())<edgeEB){
	    deltaPhi = fabs(e2.Phi()-jet2.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_deltaEtaBV_EB->Fill(fabs(e2.Eta()-jet2.Eta()),myweight[0]);
	    if (distR(e1,jet2)<deltaRCone ||distR(e2,jet2)<deltaRCone ){	       
	       h_deltaEtaBVe_EB->Fill(fabs(e2.Eta()-jet2.Eta()),myweight[0]);
	       h_totEtaBVe_EB->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    }else {
	       h_deltaEtaBVjet_EB->Fill(fabs(e2.Eta()-jet2.Eta()),myweight[0]);
	       h_totEtaBVjet_EB->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    }
	    h_totEtaBV_EB->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    if (fabs(e2.Eta()-jet2.Eta()) > 1.3 && fabs(e2.Eta()-jet2.Eta()) < 1.7){
	       h_cracksEtaBVe_EB->Fill(e2.Eta(),myweight[0]);
	       h_cracksEtaBVjet_EB->Fill(jet2.Eta(),myweight[0]);
	       h_cracksEtaBV_EB->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    }
	    if (fabs(e2.Eta()-jet2.Eta()) > 2.2 && fabs(e2.Eta()-jet2.Eta()) < 2.5){
	       h_cracks2EtaBVe_EB->Fill(e2.Eta(),myweight[0]);
	       h_cracks2EtaBVjet_EB->Fill(jet2.Eta(),myweight[0]);
	       h_cracks2EtaBV_EB->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    }
	    h_deltaPhiBV_EB->Fill(deltaPhi,myweight[0]);
	    h_deltaRBV_EB->Fill(dist2,myweight[0]);
	    h_deltaEtaPhiBV_EB->Fill(fabs(e2.Eta()-jet2.Eta()),deltaPhi,myweight[0]);
	 }
	 // jet in the ENDCAP
	 if (fabs(jet2.Eta())>edgeEB && fabs(jet2.Eta())<edgeEE){
	    deltaPhi = fabs(e2.Phi()-jet2.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_deltaEtaBV_EE->Fill(fabs(e2.Eta()-jet2.Eta()),myweight[0]);
	    if (distR(e1,jet2)<deltaRCone ||distR(e2,jet2)<deltaRCone ){	       
	       h_deltaEtaBVe_EE->Fill(fabs(e2.Eta()-jet2.Eta()),myweight[0]);
	       h_totEtaBVe_EE->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    }else {
	       h_deltaEtaBVjet_EE->Fill(fabs(e2.Eta()-jet2.Eta()),myweight[0]);
	       h_totEtaBVjet_EE->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    }
	    h_totEtaBV_EE->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    h_deltaPhiBV_EE->Fill(deltaPhi,myweight[0]);
	    h_deltaRBV_EE->Fill(dist2,myweight[0]);
	    h_deltaEtaPhiBV_EE->Fill(fabs(e2.Eta()-jet2.Eta()),deltaPhi,myweight[0]);	 
	 }
      } 
      dist1=99999;
      dist2=99999; 
      for (std::vector<math::XYZTLorentzVector>::const_iterator jet = JetContainerAV.begin (); 
	   jet != JetContainerAV.end (); jet++) {
	 
	 deltaEJ= distR(e1,(*jet));
	 if (deltaEJ<dist1){
	    jet1=*jet;
	    dist1 = deltaEJ;
	 }
	 deltaEJ= distR(e2,(*jet));
	 if (deltaEJ<dist2){
	    jet2=*jet;
	    dist2 = deltaEJ;
	 }	 
      }    
      if (JetContainerAV.size()>0){
	 // jet in the BARREL
	 if (fabs(jet1.Eta())<edgeEB){
	    deltaPhi = fabs(e1.Phi()-jet1.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_totEtaAV_EB->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    h_deltaEtaAV_EB->Fill(fabs(e1.Eta()-jet1.Eta()),myweight[0]);
	    h_deltaPhiAV_EB->Fill(deltaPhi,myweight[0]);
	    h_deltaRAV_EB->Fill(dist1,myweight[0]);
	    h_deltaEtaPhiAV_EB->Fill(fabs(e1.Eta()-jet1.Eta()),deltaPhi,myweight[0]);
	 }
	 // jet in the ENDCAP
	 if (fabs(jet1.Eta())>edgeEB && fabs(jet1.Eta())<edgeEE){
	    deltaPhi = fabs(e1.Phi()-jet1.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_totEtaAV_EE->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    h_deltaEtaAV_EE->Fill(fabs(e1.Eta()-jet1.Eta()),myweight[0]);
	    h_deltaPhiAV_EE->Fill(deltaPhi,myweight[0]);
	    h_deltaRAV_EE->Fill(dist1,myweight[0]);
	    h_deltaEtaPhiAV_EE->Fill(fabs(e1.Eta()-jet1.Eta()),deltaPhi,myweight[0]);	 
	 } 
	 // jet in the BARREL
	 if (fabs(jet2.Eta())<edgeEB){
	    deltaPhi = fabs(e2.Phi()-jet2.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_totEtaAV_EB->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    h_deltaEtaAV_EB->Fill(fabs(e2.Eta()-jet2.Eta()),myweight[0]);
	    h_deltaPhiAV_EB->Fill(deltaPhi,myweight[0]);
	    h_deltaRAV_EB->Fill(dist2,myweight[0]);
	    h_deltaEtaPhiAV_EB->Fill(fabs(e2.Eta()-jet2.Eta()),deltaPhi,myweight[0]);
	 }
	 // jet in the ENDCAP
	 if (fabs(jet2.Eta())>edgeEB && fabs(jet2.Eta())<edgeEE){
	    deltaPhi = fabs(e2.Phi()-jet2.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_totEtaAV_EE->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    h_deltaEtaAV_EE->Fill(fabs(e2.Eta()-jet2.Eta()),myweight[0]);
	    h_deltaPhiAV_EE->Fill(deltaPhi,myweight[0]);
	    h_deltaRAV_EE->Fill(dist2,myweight[0]);
	    h_deltaEtaPhiAV_EE->Fill(fabs(e2.Eta()-jet2.Eta()),deltaPhi,myweight[0]);	 
	 }
      } 
      dist1=99999;
      dist2=99999; 
      for (std::vector<math::XYZTLorentzVector>::const_iterator jet = JetContainerRC.begin (); 
	   jet != JetContainerRC.end (); jet++) {
	 
	 deltaEJ= distR(e1,(*jet));
	 if (deltaEJ<dist1){
	    jet1=*jet;
	    dist1 = deltaEJ;
	 }
	 deltaEJ= distR(e2,(*jet));
	 if (deltaEJ<dist2){
	    jet2=*jet;
	    dist2 = deltaEJ;
	 }	 
      }  
      if (JetContainerRC.size()>0){  
	 // jet in the BARREL
	 if (fabs(jet1.Eta())<edgeEB){
	    deltaPhi = fabs(e1.Phi()-jet1.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_totEtaRC_EB->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    h_deltaEtaRC_EB->Fill(fabs(e1.Eta()-jet1.Eta()),myweight[0]);
	    h_deltaPhiRC_EB->Fill(deltaPhi,myweight[0]);
	    h_deltaRRC_EB->Fill(dist1,myweight[0]);
	    h_deltaEtaPhiRC_EB->Fill(fabs(e1.Eta()-jet1.Eta()),deltaPhi,myweight[0]);
	 }
	 // jet in the ENDCAP
	 if (fabs(jet1.Eta())>edgeEB && fabs(jet1.Eta())<edgeEE){
	    deltaPhi = fabs(e1.Phi()-jet1.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_totEtaRC_EE->Fill(e1.Eta(),jet1.Eta(),myweight[0]);
	    h_deltaEtaRC_EE->Fill(fabs(e1.Eta()-jet1.Eta()),myweight[0]);
	    h_deltaPhiRC_EE->Fill(deltaPhi,myweight[0]);
	    h_deltaRRC_EE->Fill(dist1,myweight[0]);
	    h_deltaEtaPhiRC_EE->Fill(fabs(e1.Eta()-jet1.Eta()),deltaPhi,myweight[0]);	 
	 } 
	 // jet in the BARREL
	 if (fabs(jet2.Eta())<edgeEB){
	    deltaPhi = fabs(e2.Phi()-jet2.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_totEtaRC_EB->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    h_deltaEtaRC_EB->Fill(fabs(e2.Eta()-jet2.Eta()),myweight[0]);
	    h_deltaPhiRC_EB->Fill(deltaPhi,myweight[0]);
	    h_deltaRRC_EB->Fill(dist2,myweight[0]);
	    h_deltaEtaPhiRC_EB->Fill(fabs(e2.Eta()-jet2.Eta()),deltaPhi,myweight[0]);
	 }
	 // jet in the ENDCAP
	 if (fabs(jet2.Eta())>edgeEB && fabs(jet2.Eta())<edgeEE){
	    deltaPhi = fabs(e2.Phi()-jet2.Phi());
	    if (deltaPhi > acos(-1)) deltaPhi= 2*acos(-1) - deltaPhi;
	    h_totEtaRC_EE->Fill(e2.Eta(),jet2.Eta(),myweight[0]);
	    h_deltaEtaRC_EE->Fill(fabs(e2.Eta()-jet2.Eta()),myweight[0]);
	    h_deltaPhiRC_EE->Fill(deltaPhi,myweight[0]);
	    h_deltaRRC_EE->Fill(dist2,myweight[0]);
	    h_deltaEtaPhiRC_EE->Fill(fabs(e2.Eta()-jet2.Eta()),deltaPhi,myweight[0]);	 
	 }
	 
      }
   } else if (Debug){std::cout << "WARNING: More than two electron selected"<< std::endl;}  
   
}


// ------------ method called once each job just before starting event loop  ------------
void 
reclusVal::beginJob()
{


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
  cout<<endl;


}

// ------------ method called once each job just after ending the event loop  ------------
void 
reclusVal::endJob() 
{
    
 //Histograms
  h_weights->GetXaxis()->SetTitle("Weight");
  // h_jetPt_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
//   h_jetPt_EB->GetYaxis()->SetTitle("N_{jets}");
//   h_jetEta_EB->GetXaxis()->SetTitle("#eta_{jets}");
//   h_jetEta_EB->GetYaxis()->SetTitle("N_{jets}");
  
//   h_jetPt_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
//   h_jetPt_EE->GetYaxis()->SetTitle("N_{jets}");
//   h_jetEta_EE->GetXaxis()->SetTitle("#eta_{jets}");
//   h_jetEta_EE->GetYaxis()->SetTitle("N_{jets}");

}

// ------------ method called when starting to processes a run  ------------
void 
reclusVal::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
reclusVal::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
reclusVal::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
reclusVal::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(reclusVal);
