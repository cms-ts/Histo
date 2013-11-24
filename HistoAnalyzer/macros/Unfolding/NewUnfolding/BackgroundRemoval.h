//Background

void correctForBackground(int numbOfJetsSelected, string whichtype, TH1D* jData, bool verbose){
  ofstream backSignificance;
  std::vector<double> bckcoeff;

  if (whichtype=="Pt"){
    if (numbOfJetsSelected==1) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_pT");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1Pt.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1PtMu.txt");
    }
    if (numbOfJetsSelected==2) {
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2Pt.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2PtMu.txt");
      bckcoeff=getBackgroundContributions(bkgstring,"jet_pT2");
    }
    if (numbOfJetsSelected==3) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_pT3");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3Pt.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3PtMu.txt");
    }
    if (numbOfJetsSelected==4) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_pT4");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4Pt.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4PtMu.txt");
    }
  }
  
  if (whichtype=="Eta"){
    if (numbOfJetsSelected==1) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1EtaMu.txt");
    }
    if (numbOfJetsSelected==2) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta2");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2EtaMu.txt");
    }
    if (numbOfJetsSelected==3) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta3");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3EtaMu.txt");
    }
    if (numbOfJetsSelected==4) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta4");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4EtaMu.txt");
    } 
  }

  if (whichtype=="Ht"){
    if (numbOfJetsSelected == 1){
      bckcoeff = getBackgroundContributions (bkgstring, "HT1");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1Ht.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1HtMu.txt");
    }      
    if (numbOfJetsSelected == 2){
      bckcoeff = getBackgroundContributions (bkgstring, "HT2");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2Ht.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2HtMu.txt");
    }
    if (numbOfJetsSelected == 3){
      bckcoeff = getBackgroundContributions (bkgstring, "HT3");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3Ht.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3HtMu.txt");
    }
    if (numbOfJetsSelected == 4){
      bckcoeff = getBackgroundContributions (bkgstring, "HT4");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4Ht.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4HtMu.txt");
    }
  }
  
  if (whichtype=="Multiplicity"){
    bckcoeff=getBackgroundContributions(bkgstring,"jet_Multiplicity");
    if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJetMulti.txt");
    if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJetMultiMu.txt");
  }

  for (int k=0; k<divPlot; k++){
    cout<<bckcoeff[k]<<endl;
      jData->SetBinContent(k+1, jData->GetBinContent(k+1) - bckcoeff[k]);
      jData->SetBinError(k+1, sqrt(pow(jData->GetBinError(k+1),2) + pow(sqrt(bckcoeff[k]),2)) );  //Set also the error
      
      double backvalue=bckcoeff[k];
      if (jData->GetBinContent(k+1)>0) {
        if (bckcoeff[k]<0.000000001) backvalue=0.0;
        relativebkg->SetBinContent(k+1,bckcoeff[k]/jData->GetBinContent(k+1));
        if (verbose) cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is "<<bckcoeff[k]/jData->GetBinContent(k+1)<<endl;     
      }
      else {
        if (bckcoeff[k]<0.000000001) backvalue=0.0;
        relativebkg->SetBinContent(k+1,0);
        if (verbose) cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is 0"<<endl;
      }
      if (MCstatError) backSignificance<<jData->GetBinContent(k+1)<<" "<<backvalue<<endl;
  }
}
