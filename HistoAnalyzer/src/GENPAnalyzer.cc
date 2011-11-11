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

  edm::Handle<reco::GsfElectronCollection > goodEPair;
  iEvent.getByLabel (goodEPairTag, goodEPair);


  // Use only events with two good electrons:
  if ( goodEPair->size()==2 ) {


    TLorentzVector p_e1( (*goodEPair)[0].px(),
			 (*goodEPair)[0].py(),
			 (*goodEPair)[0].pz(),
			 (*goodEPair)[0].energy() );
    TLorentzVector p_e2( (*goodEPair)[1].px(),
			 (*goodEPair)[1].py(),
			 (*goodEPair)[1].pz(),
			 (*goodEPair)[1].energy() );

    h_Mee->Fill((p_e1+p_e2).M());

    

    if (isMC) {

      edm::Handle<reco::GenParticleCollection> genPart;
      iEvent.getByLabel (genParticleCollection_,genPart);
    

      // --- Match the reconstructed electrons to the GENP particles

      double dR1_min = 999.;
      double dR2_min = 999.;
      TLorentzVector pgen_e1(0.,0.,0.,0.), pgen_e2(0.,0.,0.,0.);
      reco::GenParticleCollection::const_iterator e1;
      reco::GenParticleCollection::const_iterator e2;
      for(reco::GenParticleCollection::const_iterator genp=genPart->begin();genp!=genPart->end();genp++){

	if ( fabs(genp->pdgId())!=11 || genp->status() !=1 ) continue;
	
	TLorentzVector p_gen( genp->px(),
			      genp->py(),
			      genp->pz(),
			      genp->energy() );
	
	double dR1 = p_gen.DeltaR(p_e1);
	double dR2 = p_gen.DeltaR(p_e2);

	if ( dR1<dR1_min && dR1<0.3 ){
	  dR1_min = dR1;
	  e1      = genp;
	  pgen_e1 = p_gen; 
	}

	if ( dR2<dR2_min && dR2<0.3 ){
	  dR2_min = dR2;
	  e2      = genp;
	  pgen_e2 = p_gen; 
	}

      } // for itgen


      // --- Order the two electrons by charge
      if ( e1->charge() > 0. ){
	reco::GenParticleCollection::const_iterator e_tmp = e1;
	e1 = e2;
	e2 = e_tmp;
      }

      // --- Look for GENP particles in the electron isolation cone
 
      for(reco::GenParticleCollection::const_iterator genp=genPart->begin();genp!=genPart->end();genp++){

	if ( genp==e1 || genp==e2 || genp->status()!=1 ) continue;

	TLorentzVector p_gen( genp->px(),
			      genp->py(),
			      genp->pz(),
			      genp->energy() );

	double dR1 = p_gen.DeltaR(pgen_e1);
	double dR2 = p_gen.DeltaR(pgen_e2);


	if ( dR1 < 0.3 ) {

	  h_ID_iso1->Fill(genp->pdgId());
	  h_ID_iso->Fill(genp->pdgId());

	  h_pt_iso1->Fill(genp->pt());
	  h_pt_iso->Fill(genp->pt());

	  if ( fabs(genp->pdgId())==11 )
	    h_pt_iso_e->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==13 )
	    h_pt_iso_mu->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==22 )
	    h_pt_iso_ph->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==211 )
	    h_pt_iso_pi->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==321 )
	    h_pt_iso_K->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==130 )
	    h_pt_iso_KL->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==310 )
	    h_pt_iso_KS->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==2212 )
	    h_pt_iso_p->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==2112 )
	    h_pt_iso_n->Fill(genp->pt());

	}
 

	if ( dR2 < 0.3 ) {

	  h_ID_iso2->Fill(genp->pdgId());
	  h_ID_iso->Fill(genp->pdgId());

	  h_pt_iso2->Fill(genp->pt());
	  h_pt_iso->Fill(genp->pt());


	  if ( fabs(genp->pdgId())==11 )
	    h_pt_iso_e->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==13 )
	    h_pt_iso_mu->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==22 )
	    h_pt_iso_ph->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==211 )
	    h_pt_iso_pi->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==321 )
	    h_pt_iso_K->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==130 )
	    h_pt_iso_KL->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==310 )
	    h_pt_iso_KS->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==2212 )
	    h_pt_iso_p->Fill(genp->pt());
	  else if ( fabs(genp->pdgId())==2112 )
	    h_pt_iso_n->Fill(genp->pt());

	}

      } // for itgen 



    } // if (isMC)

  } // if ( goodEPair->size()==2 )

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
  //Histograms
  h_Mee->GetXaxis()->SetTitle("M_{ee} [Gev/c^2]");
  h_Mee->GetYaxis()->SetTitle("Entries");

  h_ID_iso->GetXaxis()->SetTitle("GENP ID");
  h_ID_iso->GetYaxis()->SetTitle("Entries");
  h_ID_iso1->GetXaxis()->SetTitle("GENP ID");
  h_ID_iso1->GetYaxis()->SetTitle("Entries");
  h_ID_iso2->GetXaxis()->SetTitle("GENP ID");
  h_ID_iso2->GetYaxis()->SetTitle("Entries");
  h_pt_iso->GetXaxis()->SetTitle("P_{T} [GeV/c]");
  h_pt_iso->GetYaxis()->SetTitle("Entries");
  h_pt_iso1->GetXaxis()->SetTitle("P_{T} [GeV/c]");
  h_pt_iso1->GetYaxis()->SetTitle("Entries");
  h_pt_iso2->GetXaxis()->SetTitle("P_{T} [GeV/c]");
  h_pt_iso2->GetYaxis()->SetTitle("Entries");      

  h_pt_iso_mu->GetXaxis()->SetTitle("P_{T} [GeV/c]");
  h_pt_iso_mu->GetYaxis()->SetTitle("Entries");      
  h_pt_iso_ph->GetXaxis()->SetTitle("P_{T} [GeV/c]");
  h_pt_iso_ph->GetYaxis()->SetTitle("Entries");      
  h_pt_iso_pi->GetXaxis()->SetTitle("P_{T} [GeV/c]");
  h_pt_iso_pi->GetYaxis()->SetTitle("Entries");      
  h_pt_iso_K ->GetXaxis()->SetTitle("P_{T} [GeV/c]");
  h_pt_iso_KL->GetYaxis()->SetTitle("Entries");      
  h_pt_iso_KL->GetXaxis()->SetTitle("P_{T} [GeV/c]");
  h_pt_iso_KS->GetYaxis()->SetTitle("Entries");      
  h_pt_iso_KS->GetXaxis()->SetTitle("P_{T} [GeV/c]");
  h_pt_iso_p ->GetYaxis()->SetTitle("Entries");      
  h_pt_iso_p ->GetXaxis()->SetTitle("P_{T} [GeV/c]");
  h_pt_iso_n ->GetYaxis()->SetTitle("Entries");      
  h_pt_iso_n ->GetXaxis()->SetTitle("P_{T} [GeV/c]");


}  

// ------------ method called when starting to processes a run  ------------
void 
GENPAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
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

//define this as a plug-in
DEFINE_FWK_MODULE(GENPAnalyzer);
