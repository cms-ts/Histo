//////
// Save File
///////

void saveIntoFile(int numbOfJetsSelected, string whichtype, TH1D* jReco, TH1D* jTrue, TH2D* jMatx, TH1D* jMCreco, TH1D* jData){
  TFile* w = new TFile(filename.c_str(), "UPDATE");
  w->cd();
  
  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      TH1D *jReco_leading= (TH1D*) jReco->Clone("jReco");
      jReco_leading->SetName("jReco_leading");
      jReco_leading->Write();
      TH1D *jTrue_leading= (TH1D*) jTrue->Clone("jTrue");
      jTrue_leading->Write();
      TH2D *jMatx_leading= (TH2D*) jMatx->Clone("jMatx");
      jMatx_leading->Write();
      TH1D *jData_leading= (TH1D*) jData->Clone("jData");
      jData_leading->Write();
      TH1D *jMCreco_leading= (TH1D*) jMCreco->Clone("jMCreco");
      jMCreco_leading->Write();
    }
    if (numbOfJetsSelected==2) {
      TH1D *jReco_subleading= (TH1D*) jReco->Clone("jReco");
      jReco_subleading->SetName("jReco_subleading");
      jReco_subleading->Write();
      TH1D *jTrue_subleading= (TH1D*) jTrue->Clone("jTrue");
      jTrue_subleading->Write();
      
    }
    if (numbOfJetsSelected==3) {
      TH1D *jReco_subsubleading= (TH1D*) jReco->Clone("jReco");
      jReco_subsubleading->SetName("jReco_subsubleading");
      jReco_subsubleading->Write();
      TH1D *jTrue_subsubleading= (TH1D*) jTrue->Clone("jTrue");
      jTrue_subsubleading->Write();
      
    }
    if (numbOfJetsSelected==4) {
      TH1D *jReco_subsubsubleading= (TH1D*) jReco->Clone("jReco");
      jReco_subsubsubleading->SetName("jReco_subsubsubleading");
      jReco_subsubsubleading->Write();
      TH1D *jTrue_subsubsubleading= (TH1D*) jTrue->Clone("jTrue");
      jTrue_subsubsubleading->Write();
      
    }
  }

  if (whichtype=="Eta"){
    if (numbOfJetsSelected==1) {
      TH1D *jReco_leadingeta= (TH1D*) jReco->Clone("jReco");
      jReco_leadingeta->SetName("jReco_leadingeta");
      jReco_leadingeta->Write();
    }
    if (numbOfJetsSelected==2) {
      TH1D *jReco_subleadingeta= (TH1D*) jReco->Clone("jReco");
      jReco_subleadingeta->SetName("jReco_subleadingeta");
      jReco_subleadingeta->Write();
    }
    if (numbOfJetsSelected==3) {
      TH1D *jReco_subsubleadingeta= (TH1D*) jReco->Clone("jReco");
      jReco_subsubleadingeta->SetName("jReco_subsubleadingeta");
      jReco_subsubleadingeta->Write();
    }
    if (numbOfJetsSelected==4) {
      TH1D *jReco_subsubsubleadingeta= (TH1D*) jReco->Clone("jReco");
      jReco_subsubsubleadingeta->SetName("jReco_subsubsubleadingeta");
      jReco_subsubsubleadingeta->Write();
    }

  }

  if (whichtype=="Ht"){
    if (numbOfJetsSelected==1) {
     TH1D *HReco_leading= (TH1D*) jReco->Clone("jReco");
      HReco_leading->SetName("HReco_leading");
      HReco_leading->Write();
    }
    if (numbOfJetsSelected==2) {
      TH1D *HReco_subleading= (TH1D*) jReco->Clone("jReco");
      HReco_subleading->SetName("HReco_subleading");
      HReco_subleading->Write();
    }
    if (numbOfJetsSelected==3) {
      TH1D *HReco_subsubleading= (TH1D*) jReco->Clone("jReco");
      HReco_subsubleading->SetName("HReco_subsubleading");
      HReco_subsubleading->Write();
    }
    if (numbOfJetsSelected==4) {
      TH1D *HReco_subsubsubleading= (TH1D*) jReco->Clone("jReco");
      HReco_subsubsubleading->SetName("HReco_subsubsubleading");
      HReco_subsubsubleading->Write();
    }

  }

  if (whichtype=="Multiplicity"){
    TH1D* JetMultiplicityUnfolded=(TH1D*) jReco->Clone("jReco");
    JetMultiplicityUnfolded->SetName("JetMultiplicityUnfolded");
    JetMultiplicityUnfolded->Write();
    jTrue->Write();
    jMatx->Write();
    jData->Write();
    jMCreco->Write();
  }

  w->Close();
}
