TH1D *NTrue = new TH1D ("NTrue", "N Truth", maxNJets-0.5, 0.5, maxNJets-0.5);
TH1D *NData = new TH1D ("NData", "N DATA Measured", maxNJets-0.5, 0.5, maxNJets-0.5);
TH2D *NMatx = new TH2D ("N hMatx", "Unfolding Matrix in # of jets + Z", maxNJets-0.5, 0.5, maxNJets-0.5, maxNJets-0.5, 0.5, maxNJets-0.5);
TH2D *NMatxlong = new TH2D ("N hMatxlong", "Unfolding Matrix in # of jets + Z", maxNJets, 0, maxNJets, maxNJets, 0, maxNJets);
TH1D *NMCreco = new TH1D ("N mcreco", "N mcreco", maxNJets-0.5, 0.5, maxNJets-0.5);
TH1D *NMCrecoratio_ = new TH1D ("N mcrecoratio_", "N mcreco_", maxNJets-0.5, 0.5, maxNJets-0.5);
TH1D *NData2 = new TH1D ("N data2", "N DATA Measured2", maxNJets-0.5, 0.5, maxNJets-0.5);
TH1F *relativebkgN = new TH1F("relativebkgN", "relativebkg bin contribution",maxNJets-0.5,0.5,maxNJets-0.5);

TH1F *JetMultiplicityUnfolded;
int kminN=maxNJets-1;
int kmaxN=maxNJets;
bool spanKvaluesN=false;


int getNumberOfValidGenJets(int Jet_multiplicity_gen, double thresh, double jet1_pt_gen, double jet2_pt_gen, double jet3_pt_gen, double jet4_pt_gen, double jet5_pt_gen, double jet6_pt_gen, double jet1_eta_gen, double jet2_eta_gen, double jet3_eta_gen, double jet4_eta_gen, double jet5_eta_gen, double jet6_eta_gen){
  int counter=0;
  for (int i=1;i<=Jet_multiplicity_gen; i++){
    if (i==1){
      if (jet1_pt_gen<thresh || fabs(jet1_eta_gen)>2.4 ) counter++;
    }
    
    if (i==2){
      if (jet2_pt_gen<thresh || fabs(jet2_eta_gen)>2.4 ) counter++;
    }

    if (i==3){
      if (jet3_pt_gen<thresh || fabs(jet3_eta_gen)>2.4 ) counter++;
    }

    if (i==4){
      if (jet4_pt_gen<thresh || fabs(jet4_eta_gen)>2.4 ) counter++;
    }

    if (i==5){
      if (jet5_pt_gen<thresh || fabs(jet5_eta_gen)>2.4 ) counter++;
    }

    if (i==6){
      if (jet6_pt_gen<thresh || fabs(jet6_eta_gen)>2.4 ) counter++;
    }
    
  }// for
  return counter;
}// end


void Unfolding::LoopJetMultiplicity ()
{
  cout<<endl;
  cout<<"*********************************"<<endl;
  cout<<"Unfolding number of Jets"<<endl;
  cout<<"*********************************"<<endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  if (spanKvaluesN){
    kminN=1;
    kmaxN=maxNJets-2; 
  }

  
  string sdatadir=sdata+":/validationJEC";
  string smcdir=smc+":/validationJEC";
  if (isMu) {
    smcdir=smc+":/EPTmuoWp80_MC";
  }
  fA->cd (smcdir.c_str());
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeValidationJEC_");
  fB->cd (sdatadir.c_str());
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");

  //Setting the errors
  NTrue->Sumw2();
  NMCreco->Sumw2();
  NMCrecoratio_->Sumw2();
  NData->Sumw2();
  
  int count=0;
  int countGEN=0;  
  /*costruisco la matrice di unfolding */

  fChain = tree_fA;	
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;
  
  if (fChain == 0) return;

  for (Long64_t jentry = 0; jentry < nentries; jentry++){
    Long64_t ientry = LoadTree (jentry);
    if (ientry < 0)
      break;
    nb = fChain->GetEntry (jentry);
    nbytes += nb;
    if (Jet_multiplicity > 30 || Jet_multiplicity_gen > 30 ) continue;
    
    if (Jet_multiplicity >= 0 || Jet_multiplicity_gen >= 0){
      double thresh=15.0;
      
      // To control and exclude jets having energy below "thresh"
      int offsetJetMultiplicity=0;
      
      offsetJetMultiplicity=getNumberOfValidGenJets(Jet_multiplicity_gen,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet5_pt_gen,jet6_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen,jet5_eta_gen,jet6_eta_gen);

      if (correctForEff){
	if (!useElectronsToCorrect){
	  std::vector<double> valuesmc=getEfficiencyCorrectionJetMultiplicity(fAeff,fBeff,Jet_multiplicity,"MC");
	  double effcorrmc=1.00/valuesmc[0];	
	  double efferrmc=valuesmc[1]/pow(valuesmc[0],2); 
	  NTrue->Fill (Jet_multiplicity_gen-offsetJetMultiplicity);
	  NMCreco->Fill (Jet_multiplicity,effcorrmc);
	  NMCrecoratio_->Fill(Jet_multiplicity,effcorrmc);
	  NMatx->Fill (Jet_multiplicity, Jet_multiplicity_gen-offsetJetMultiplicity,effcorrmc);
	  NMatxlong->Fill (Jet_multiplicity, Jet_multiplicity_gen-offsetJetMultiplicity,effcorrmc);
	}
	else{
	  double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC");
	  NTrue->Fill (Jet_multiplicity_gen-offsetJetMultiplicity);
	  NMCreco->Fill (Jet_multiplicity,effcorrmc);
	  NMCrecoratio_->Fill(Jet_multiplicity,effcorrmc);
	  NMatx->Fill (Jet_multiplicity, Jet_multiplicity_gen-offsetJetMultiplicity,effcorrmc);
	  NMatxlong->Fill (Jet_multiplicity, Jet_multiplicity_gen-offsetJetMultiplicity,effcorrmc);
	}
      }
      else{
	NTrue->Fill (Jet_multiplicity_gen-offsetJetMultiplicity);
	NMCreco->Fill (Jet_multiplicity);
	NMCrecoratio_->Fill(Jet_multiplicity);
	if (jet1_pt_gen<30) countGEN++;
	if (jet1_pt<30) count++;	
	NMatx->Fill (Jet_multiplicity, Jet_multiplicity_gen-offsetJetMultiplicity);
	NMatxlong->Fill(Jet_multiplicity, Jet_multiplicity_gen-offsetJetMultiplicity);
	//cout<<"jet_multip_gen->"<<Jet_multiplicity_gen-offsetJetMultiplicity<<"  jet_multip->"<<Jet_multiplicity<<" jet1_pt_gen->"<<jet1_pt_gen<<" jet1_pt->"<<jet1_pt<<" jet1_eta_gen->"<<jet1_eta_gen<<"jet1_eta->"<<jet1_eta<<" jet2_pt_gen->"<<jet2_pt_gen<<" jet2_pt->"<<jet2_pt<<" jet2_eta_gen->"<<jet2_eta_gen<<endl;
      }
    }
  }
  
  cout<<"GEN >0 but <30 ->"<<countGEN<<" while RECO =0 ->"<<count<<endl;
  /*Loop on data */
  fChain = tree_fB;	
  Init (fChain);	
  Long64_t nentries2 = fChain->GetEntriesFast ();
  Long64_t nb2 = 0;
  
  if (fChain == 0) return;
  
  for (Long64_t jentry = 0; jentry < nentries2; jentry++) {
    
    Long64_t ientry = LoadTree (jentry);
    if (ientry < 0)
      break;
    nb2 = fChain->GetEntry (jentry);
    nbytes += nb2;
    if (Jet_multiplicity > 30) continue;
    
    if (Jet_multiplicity >= 0){
      if (correctForEff){
	if (!useElectronsToCorrect){
	  std::vector<double> valuesdata=getEfficiencyCorrectionJetMultiplicity(fAeff,fBeff,Jet_multiplicity,"Data");
	  double effcorrdata=1.00/valuesdata[0];	
	  double efferrdata=valuesdata[1]/pow(valuesdata[0],2);
	  NData->Fill (Jet_multiplicity,effcorrdata);
	  NData2->Fill (Jet_multiplicity,effcorrdata);
	}
	else{
	  double effcorrdata=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data");
	  NData->Fill (Jet_multiplicity,effcorrdata);
	  NData2->Fill (Jet_multiplicity,effcorrdata);
	}
      }
      else{
	NData->Fill (Jet_multiplicity);
	NData2->Fill (Jet_multiplicity);	
      }
    }
  }

  ///   NOTA BENE!!
  //PER QUALCHE RAGIONE NON BISOGNA NORMALIZZARE NULLA PRIMA DI FARE LA RESPONSE MATRIX!!
  //////////////
  // MC Normalization
  //////////////
  double ScaleMCData = ((double)NData->GetEntries()/(double)NMCreco->GetEntries());
 

  /////////////////////////
  //  Correct for background
  /////////////////////////
  
  if (correctForBkg){
    std::vector<double> bckcoeff;
    bckcoeff=getBackgroundContributions(bkgstring,"jet_Multiplicity");
    for (unsigned int k=0; k< maxNJets; k++){
      NData->SetBinContent(k+1, NData->GetBinContent(k+1) - bckcoeff[k+1]);  //K+1 perche' c'e' il bkgr a 0 Jets...
      if (NData->GetBinContent(k+1)>0) {
	relativebkgN->SetBinContent(k+1,bckcoeff[k+1]/NData->GetBinContent(k+1));
	cout<<"Data:"<<NData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k+1]<<" (coefficient is "<<bckcoeff[k+1]<<"). Relative bin ratio is "<<bckcoeff[k+1]/NData->GetBinContent(k+1)<<endl;	
      }
      else {
	relativebkgN->SetBinContent(k+1,0);
	cout<<"Data:"<<NData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k+1]<<" (coefficient is "<<bckcoeff[k+1]<<"). Relative bin ratio is 0"<<endl;
      }
      cout<<"after "<<bckcoeff[k]/NData->GetBinContent(k+1)<<endl;
    }
  }
  
  // Fill the matrix response with the MC values, this time as histograms!
  RooUnfoldResponse response_N(NMCreco, NTrue, NMatx); 
  response_N.UseOverflow();

  cout<<"***********************"<<endl;
  cout<<"MC will be normalized to data, using entries"<<endl;
  cout<<"N entries in Data:"<<NData->GetEntries()<<" and MC:"<<NMCreco->GetEntries()<<" ratio->"<<ScaleMCData<<endl;
  cout<<endl;
  NMCreco->Scale (ScaleMCData);
  NTrue->Scale (ScaleMCData);
  NMCrecoratio_->Scale (ScaleMCData);
  

  //Repeating each algorithm
  for (int j=1; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";

    cout<<"Running "<<method<<" method"<<endl;
    
    //Optimizing the k value
    for (int k=kminN; k<kmaxN; k++){
      int myNumber=k;
      stringstream num;
      num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Z + N Jets distribution. "+title;
      cout<<title<<endl;
      
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_N (&response_N, NData, myNumber);
	NReco = (TH1D *) unfold_N.Hreco ();
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_N (&response_N, NData, myNumber);	// OR
	NReco = (TH1D *) unfold_N.Hreco ();
      }
      
      NReco->Sumw2();

      if (differentialCrossSection){
	NReco->Scale(1./NReco->Integral());		
	NTrue->Scale(1./NTrue->Integral());
	NMCreco->Scale(1./NMCreco->Integral());
	NData->Scale(1./NData->Integral());
      }

      JetMultiplicityUnfolded=(TH1F*) NReco->Clone("NReco");
      JetMultiplicityUnfolded->SetName("JetMultiplicityUnfolded");

      //Save info to evaluate the unfolding uncertainties... Da fare a mano ogni volta cambiando il MC e vedendo la differenza nei dati... poi prendi i dati, e li trascrivi nella macro!
      for (int c=0;c<6;c ++){
	cout<<NReco->GetBinContent(c+1)<<endl;
      }

      cmultip->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1",0.01,0.33,0.99,0.99);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      pad1->SetTopMargin(0.1);
      pad1->SetBottomMargin(0.01);
      pad1->SetRightMargin(0.1);
      pad1->SetFillStyle(0);

      title2="Number of jet + Z distribution. "+title;
      NReco->SetTitle (title2.c_str());
      NReco->GetXaxis ()->SetTitle ("");
      NReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/dN");
      NReco->SetMarkerStyle (20);
      NData->SetMarkerStyle (21);
      NData->SetLineColor(kGreen);
      
      NReco->SetMarkerStyle (20);
      NReco->SetStats(0);
      NReco->GetXaxis()->SetTitle("# of Jets");
      NReco->GetXaxis()->SetTitleSize(0.00);
      NReco->GetYaxis()->SetLabelSize(0.07);
      NReco->GetXaxis()->SetLabelSize(0.00);
      NReco->GetYaxis()->SetTitleSize(0.08);
      NReco->GetYaxis()->SetTitleOffset(0.76);
      NReco->Draw("EP");		//risultato dell'unfolding
      NReco->SetLineColor (kRed);
      NReco->SetLineWidth (2);
      NMCreco->Draw();
      NMCreco->SetLineColor (kBlue + 1);
      NMCreco->SetLineStyle (2);
      NTrue->SetLineColor (kBlack);
      NMCreco->SetLineWidth (2);
      NTrue->SetLineWidth (2);

      NTrue->Draw ("EPSAME");
      NData2->SetLineColor(kGreen+1);
      NData2->Draw("EPSAME");

      NReco->DrawCopy ();
      pad1->SetLogy (1);
      NTrue->Draw ("same");
      NMCreco->Draw ("same");
      NData->SetLineStyle(2);
      NData->Draw("same");

      //      pad1->SetBottomMargin (0);
      NReco->SetTitleSize (0);

      NTrue->SetTitleSize (0);

      for(int i=1; i<=maxNJets; i++){
	double x = NReco->GetBinContent(i);
	cout << x << endl;
      }  

      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (NReco, "Data Unfolded", "LP20");
      legend_d->AddEntry (NTrue, "MC truth", "L");
      legend_d->AddEntry (NMCreco, "MC reco", "L");
      legend_d->AddEntry(NData,"Data Folded","L");
      legend_d->Draw ("same");

      /* Save Jet Multiplicity */

      pad1->Update();
	
      cmultip->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2",0.01,0.01,0.99,0.32);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      pad2->SetTopMargin(0.01);
      pad2->SetBottomMargin(0.3);
      pad2->SetRightMargin(0.1);
      pad2->SetFillStyle(0);

      NReco->GetXaxis ()->SetLabelSize (0.1);
      NReco->GetYaxis ()->SetLabelSize (0.08);
      NReco->SetStats (0);
      NReco->Divide (NTrue);
      NReco->SetMarkerStyle (6);
      NReco->GetXaxis ()->SetLabelSize (0.06);
      NReco->GetYaxis ()->SetLabelSize (0.06);
      NReco->GetXaxis ()->SetTitleSize (0);
      NReco->GetYaxis ()->SetTitleSize (0.06);
      NReco->GetYaxis ()->SetTitleOffset (0.5);

      NReco->GetYaxis ()->SetRangeUser (0.5, 1.5);
      //NReco->GetXaxis ()->SetRangeUser (0, 7.5);
      NReco->SetMarkerStyle (20);
      NReco->SetLineWidth (0);
      NReco->SetTitle ("");
      NReco->SetStats(0);
      NReco->GetXaxis ()->SetLabelSize (0.1);
      NReco->GetXaxis ()->SetTitleSize (0);
      NReco->GetYaxis ()->SetTitleSize (0.06);
      NReco->GetYaxis ()->SetTitleOffset (0.5);

      //NReco->GetXaxis ()->SetRangeUser (0, 5);
      NReco->GetYaxis ()->SetTitle ("Ratios");
      NReco->GetXaxis ()->SetTitle("jet Multiplicity");
      NReco->SetMarkerStyle (20);
      NReco->SetLineWidth (0);
      NReco->SetTitle ("");
      NReco->SetLineWidth (0.1);
      NReco->GetYaxis()->SetNdivisions(7);
      NReco->GetXaxis()->SetTitleSize(0.14);
      NReco->GetXaxis()->SetLabelSize(0.14);
      NReco->GetYaxis()->SetLabelSize(0.11);
      NReco->GetYaxis()->SetTitleSize(0.11);
      NReco->GetYaxis()->SetTitleOffset(0.28);
      NReco->GetYaxis()->SetTitle("ratio data/MC");	    
    
      NReco->Draw ("ep");
      
      TH1F *NRecoClone= (TH1F*) NMCreco->Clone("NReco");
      NRecoClone->SetName("NRecoClone");
      NRecoClone->Sumw2();

      NRecoClone->Divide(NTrue);		
      NRecoClone->SetMarkerStyle (20);
      NRecoClone->SetMarkerSize(0.0);
      NRecoClone->SetTitle ("");
      NRecoClone->SetStats(1);
      NRecoClone->SetLineStyle(3);
      NRecoClone->SetLineColor(kMagenta+3);
      NRecoClone->SetStats(0);

      NRecoClone->Draw ("ep SAMES");
	    
      TF1 *f = new TF1("f","1",0,10);
      f->SetLineWidth(1);
      f->Draw("SAMES");

      TLegend *legend_w = new TLegend (0.197791, 0.736607, 0.394578, 0.9375);
      legend_w->SetFillColor (0);
      legend_w->SetFillStyle (0);
      legend_w->SetBorderSize (0);
      legend_w->AddEntry (NReco, "Data Unfolded / MC truth", "LP20");
      legend_w->AddEntry (NRecoClone, "MC reco / MC truth", "L");
      legend_w->Draw ("same");

      pad2->Update();

      string title3= s+"JETMULTI"+method+"_"+num.str();
      if (correctForEff) title3= s+"JETMULTI"+method+"_"+num.str()+"_effcorr.png";
      else title3= s+"JETMULTI"+method+"_"+num.str()+".png";
      if (isMu) s="Muons:"+s;
      cmultip->cd ();

      cmultip->Print(title3.c_str());
      num.str("");
      cout<<"PNG file saved (maybe) on "<<title3<<endl;
 
    }
  }

  if (saveFile){
    TFile* w = new TFile(filename.c_str(), "UPDATE");
    w->cd();
    JetMultiplicityUnfolded->Write();
    NTrue->Write();
    w->Close();
  }  

  TCanvas *N =new TCanvas ("N jet response matrix", "N jet response matrix", 1000, 700);
  N->cd ();
  NMatxlong->SetStats (1);
  gStyle->SetOptStat(1111111);
  NMatxlong->GetXaxis()->SetTitle("Reconstructed # of Jets");
  NMatxlong->GetYaxis()->SetTitle("Generated # of Jets");
  gStyle->SetPalette (1);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  NMatxlong->SetMarkerColor (kBlack);
  //double entries=1.000/(double)NMatxlong->Integral();
  //NMatxlong->Scale(entries);
  NMatxlong->Draw ("COLZ,text");
  string title3= s+"MatrixjetMultiplicity.png";;
  N->Print(title3.c_str());

}


