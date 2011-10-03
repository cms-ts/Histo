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
   h_nVtx->Fill(numberOfVertices);
   ///////////////////////
   ///// Z Analysis
   ///////////////////////

   edm::Handle<reco::GsfElectronCollection > goodEPair;
   iEvent.getByLabel (goodEPairTag, goodEPair);

   if (goodEPair->size()==2)
   {   
      double gsfScEn;
      double gsfScEta;
      double pfScEn;
      double pfScEta;
      reco::GsfElectronCollection::const_iterator it=goodEPair->begin();
      TLorentzVector e1, e2, e_pair;
      e1.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());

      // ================================
      //  GSFelectrons VS PFelectrons 1
      // ================================
      if (it->superCluster().isNonnull() && it->pflowSuperCluster().isNonnull()){
	 gsfScEn = it->superCluster()->energy();
	 gsfScEta= it->superCluster()->eta();
	 pfScEn  = it->pflowSuperCluster()->energy();
	 pfScEta= it->pflowSuperCluster()->eta();

	 h_gsfPfSCEtaVsEta->Fill(it->eta(),gsfScEta/pfScEta);
	 double deltaEta_ = 5.0/100.0;
	 double deltaPhi_ = 2.0*pi_/100;
	 for (int j=0; j< 100; j++){
	    if ( it->eta()> j*deltaEta_ && it->eta()<(j+1)*deltaEta_){
	       for (int k=0; k<100; k++){
		  if ( it->phi()> k*deltaPhi_ && it->phi()<(k+1)*deltaPhi_){
		     h_gsfPfSCEnVsEtaPhi->Fill((j+0.5)*deltaEta_,(k+0.5)*deltaPhi_,gsfScEn/pfScEn);
		  }
	       }
	    }
	 }
	 if (fabs(gsfScEta)<edgeEB){
	    h_gsfPfSCEta_EB->Fill(gsfScEta/pfScEta);
	    h_gsfPfSCEn_EB->Fill(gsfScEn/pfScEn);
	    h_gsfPfSCEnVsEn_EB->Fill(it->energy(),gsfScEn/pfScEn);
	    h_gsfPfSCEtaVsEn_EB->Fill(it->energy(),gsfScEta/pfScEta);
	 } else if (fabs(gsfScEta)<edgeEE){
	    h_gsfPfSCEta_EE->Fill(gsfScEta/pfScEta);
	    h_gsfPfSCEn_EE->Fill(gsfScEn/pfScEn);
	    h_gsfPfSCEnVsEn_EE->Fill(it->energy(),gsfScEn/pfScEn);
	    h_gsfPfSCEtaVsEn_EE->Fill(it->energy(),gsfScEta/pfScEta);
	 }     
      }     
      // ================================
      it++;
      e2.SetPtEtaPhiM(it->pt(),it->eta(),it->phi(),it->mass());
      e_pair = e1 + e2;
      // ================================
      //  GSFelectrons VS PFelectrons 2
      // ================================
      if (it->superCluster().isNonnull() && it->pflowSuperCluster().isNonnull()){
	 gsfScEn = it->superCluster()->energy();
	 gsfScEta= it->superCluster()->eta();
	 pfScEn  = it->pflowSuperCluster()->energy();
	 pfScEta= it->pflowSuperCluster()->eta();

	 h_gsfPfSCEtaVsEta->Fill(it->eta(),gsfScEta/pfScEta);
	 h_gsfPfSCEnVsEtaPhi->Fill(it->eta(),it->phi(),gsfScEn/pfScEn);

	 if (fabs(gsfScEta)<edgeEB){
	    h_gsfPfSCEta_EB->Fill(gsfScEta/pfScEta);
	    h_gsfPfSCEn_EB->Fill(gsfScEn/pfScEn);
	    h_gsfPfSCEnVsEn_EB->Fill(it->energy(),gsfScEn/pfScEn);
	    h_gsfPfSCEtaVsEn_EB->Fill(it->energy(),gsfScEta/pfScEta);
	 } else if (fabs(gsfScEta)<edgeEE){
	    h_gsfPfSCEta_EE->Fill(gsfScEta/pfScEta);
	    h_gsfPfSCEn_EE->Fill(gsfScEn/pfScEn);
	    h_gsfPfSCEnVsEn_EE->Fill(it->energy(),gsfScEn/pfScEn);
	    h_gsfPfSCEtaVsEn_EE->Fill(it->energy(),gsfScEta/pfScEta);
	 }     
      }      
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
	    h_jetPt_EB->Fill(jet->Pt());
	    h_jetEta_EB->Fill(jet->Eta());
	    if (nJetsEB==1) h_jetPtFirst_EB->Fill(jet->Pt());
	    else if (nJetsEB==2) h_jetPtSecond_EB->Fill(jet->Pt());
	    else if (nJetsEB==3) h_jetPtThird_EB->Fill(jet->Pt());
	    else if (nJetsEB==4) h_jetPtFourth_EB->Fill(jet->Pt());
	    if (totJetsCk==1) h_jetPtFirstCk_EB->Fill(jet->Pt());
	    else if (totJetsCk==2) h_jetPtSecondCk_EB->Fill(jet->Pt());
	    else if (totJetsCk==3) h_jetPtThirdCk_EB->Fill(jet->Pt());
	    else if (totJetsCk==4) h_jetPtFourthCk_EB->Fill(jet->Pt());

	    h_jetPtVsEta_EB->Fill(jet->Eta(),jet->Pt());
	    if (numberOfVertices==1) h_jetPtVtx1_EB->Fill(jet->Pt());
	    else if (numberOfVertices==2) h_jetPtVtx2_EB->Fill(jet->Pt());
	    else if (numberOfVertices==3) h_jetPtVtx3_EB->Fill(jet->Pt());
	    else if (numberOfVertices==4) h_jetPtVtx4_EB->Fill(jet->Pt());
	    else if (numberOfVertices==5) h_jetPtVtx5_EB->Fill(jet->Pt());
	 }
	 // jet in the ENDCAP
	 if (fabs(jet->Eta())>edgeEB && fabs(jet->Eta())<edgeEE){
	    totJetsCk++;
	    nJetsEE++;
	    h_jetPt_EE->Fill(jet->Pt());
	    if (nJetsEE==1) h_jetPtFirst_EE->Fill(jet->Pt());
	    else if (nJetsEE==2) h_jetPtSecond_EE->Fill(jet->Pt());
	    else if (nJetsEE==3) h_jetPtThird_EE->Fill(jet->Pt());
	    else if (nJetsEE==4) h_jetPtFourth_EE->Fill(jet->Pt());
	    if (totJetsCk==1) h_jetPtFirstCk_EE->Fill(jet->Pt());
	    else if (totJetsCk==2) h_jetPtSecondCk_EE->Fill(jet->Pt());
	    else if (totJetsCk==3) h_jetPtThirdCk_EE->Fill(jet->Pt());
	    else if (totJetsCk==4) h_jetPtFourthCk_EE->Fill(jet->Pt());
	    
	    if (numberOfVertices==1) h_jetPtVtx1_EE->Fill(jet->Pt());
	    else if (numberOfVertices==2) h_jetPtVtx2_EE->Fill(jet->Pt());
	    else if (numberOfVertices==3) h_jetPtVtx3_EE->Fill(jet->Pt());
	    else if (numberOfVertices==4) h_jetPtVtx4_EE->Fill(jet->Pt());
	    else if (numberOfVertices==5) h_jetPtVtx5_EE->Fill(jet->Pt());
	 }
	 // jet in ECAL
	 if (fabs(jet->Eta())<edgeEE){
	    h_jetEta_EE->Fill(jet->Eta());
	    h_jetPtVsEta_EE->Fill(jet->Eta(),jet->Pt());
	 } 
      }
      h_jetNum_EB->Fill(nJetsEB);
      h_jetNum_EE->Fill(nJetsEE);
      
      totJets = nJetsEB + nJetsEE;
      double zPt = e_pair.Pt();
      double zInvMass = e_pair.M();
      h_invMass->Fill(zInvMass);
      h_zEta->Fill(e_pair.Eta());
      h_zRapidity->Fill(e_pair.Rapidity());
      h_zYieldVsjets->Fill(totJets);
      if (numberOfVertices==1) h_zYieldVsjetsVtx1->Fill(totJets);
      if (numberOfVertices==5) h_zYieldVsjetsVtx5->Fill(totJets);
      
      if (totJets == 1){ 
	 h_zEtaNjet1->Fill(e_pair.Eta());
	 h_zMassNjet1->Fill(zInvMass);
      } else if (totJets == 2){ 
	 h_zEtaNjet2->Fill(e_pair.Eta());
	 h_zMassNjet2->Fill(zInvMass);
      } else if (totJets == 3){ 
	 h_zEtaNjet3->Fill(e_pair.Eta());
	 h_zMassNjet3->Fill(zInvMass);
      } else if (totJets == 4){ 
	 h_zEtaNjet4->Fill(e_pair.Eta());
	 h_zMassNjet4->Fill(zInvMass);
      } 

      if (totJets >= 1) h_zEtaNjet1Incl->Fill(e_pair.Eta());
      if (totJets >= 2) h_zEtaNjet2Incl->Fill(e_pair.Eta());
      if (totJets >= 3) h_zEtaNjet3Incl->Fill(e_pair.Eta());
      if (totJets >= 4) h_zEtaNjet4Incl->Fill(e_pair.Eta());
      
      for (int i=0; i<11; i++)
      {
	 if (totJets == i) h_ptZ_jet[i]->Fill(zPt);
	 if (totJets >= i) h_ptZ_jetIncl[i]->Fill(zPt);
      }     
      
      for (std::vector<math::XYZTLorentzVector>::const_iterator jet = JetContainer.begin ();
	   jet != JetContainer.end (); jet++) {
	 // jet in the BARREL
	 if (fabs(jet->Eta())<edgeEB){
	    if (totJets == 1) h_jetPtNjet1_EB->Fill(jet->Pt());
	    if (totJets == 2) h_jetPtNjet2_EB->Fill(jet->Pt());
	    if (totJets == 3) h_jetPtNjet3_EB->Fill(jet->Pt());
	    if (totJets == 4) h_jetPtNjet4_EB->Fill(jet->Pt());
	 }
	 // jet in the ENDCAP
	 if (fabs(jet->Eta())>edgeEB && fabs(jet->Eta())<edgeEE){
	    if (totJets == 1) h_jetPtNjet1_EE->Fill(jet->Pt());
	    if (totJets == 2) h_jetPtNjet2_EE->Fill(jet->Pt());
	    if (totJets == 3) h_jetPtNjet3_EE->Fill(jet->Pt());
	    if (totJets == 4) h_jetPtNjet4_EE->Fill(jet->Pt());
	 }
	 // jet in ECAL
	 if (fabs(jet->Eta())<edgeEE){
	    if (totJets == 1) h_jetPtNjet1->Fill(jet->Pt());
	    if (totJets == 2) h_jetPtNjet2->Fill(jet->Pt());
	    if (totJets == 3) h_jetPtNjet3->Fill(jet->Pt());
	    if (totJets == 4) h_jetPtNjet4->Fill(jet->Pt());

	    if (totJets >= 1) h_jetPtNjet1Incl->Fill(jet->Pt());
	    if (totJets >= 2) h_jetPtNjet2Incl->Fill(jet->Pt());
	    if (totJets >= 3) h_jetPtNjet3Incl->Fill(jet->Pt());
	    if (totJets >= 4) h_jetPtNjet4Incl->Fill(jet->Pt());
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
 h_jetPtVtx1_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVtx1_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVtx2_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVtx2_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVtx3_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVtx3_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVtx4_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVtx4_EB->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVtx5_EB->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVtx5_EB->GetYaxis()->SetTitle("N_{jets}");

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
 h_jetPtVtx1_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVtx1_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVtx2_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVtx2_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVtx3_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVtx3_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVtx4_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVtx4_EE->GetYaxis()->SetTitle("N_{jets}");
 h_jetPtVtx5_EE->GetXaxis()->SetTitle("p_{T}^{jets}");
 h_jetPtVtx5_EE->GetYaxis()->SetTitle("N_{jets}");

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
