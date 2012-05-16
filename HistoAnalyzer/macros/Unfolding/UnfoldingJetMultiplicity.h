void
Unfolding::LoopJetMultiplicity ()
{
  cout<<endl;
  cout<<"*********************************"<<endl;
  cout<<"Unfolding number of Jets"<<endl;
  cout<<"*********************************"<<endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  string sdatadir=sdata+":/validationJEC";
  string smcdir=smc+":/validationJEC";
  fA->cd (smcdir.c_str());
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  fB->cd (sdatadir.c_str());
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");
  
  //Setting the errors
  NTrue->Sumw2();
  NMCreco->Sumw2();
  NMCrecoratio_->Sumw2();
  NData->Sumw2();
  
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
    
    if (Jet_multiplicity > 0 || Jet_multiplicity_gen > 0){
      NTrue->Fill (Jet_multiplicity_gen);
      NMCreco->Fill (Jet_multiplicity);
      NMCrecoratio_->Fill(Jet_multiplicity);
      NMatx->Fill (Jet_multiplicity, Jet_multiplicity_gen);
    }
  }
  		

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
    if (Jet_multiplicity > 0){
      NData->Fill (Jet_multiplicity);
      NData2->Fill (Jet_multiplicity);
    }
  }

  ///   NOTA BENE!!
  //PER QUALCHE RAGIONE NON BISOGNA NORMALIZZARE NULLA PRIMA DI FARE LA RESPONSE MATRIX!!
  //////////////
  // MC Normalization
  //////////////
  double ScaleMCData = ((double)NData->GetEntries()/(double)NMCreco->GetEntries());
 
  /////////////////
  // Efficiency Correction
  /////////////////

  double areaRecoVsTruth=1.000;
  TH1F* DataCorr;
  TH1F* JetMultiplicityUnfolded;
  //JetMultiplicityUnfolded->Sumw2();

  if(correctForEff) {
    TDirectory *dir=(TDirectory*)eff->cd("efficiency_vs_nJets");
    //dir->cd();
    TH1F *h1 = (TH1F*)gDirectory->Get("MC_WP80_Tag");
    TH1F *h2 = (TH1F*)gDirectory->Get("MC_WP80_Probe");
    TH1F *h3 = (TH1F*)gDirectory->Get("MC_RECO_Probe");
    TH1F *h4 = (TH1F*)gDirectory->Get("MC_HLTele8_Probe");
    TH1F *h5 = (TH1F*)gDirectory->Get("MC_HLTele8_Tag");
    TH1F *h6 = (TH1F*)gDirectory->Get("MC_HLTele17_Probe");
    TH1F *h7 = (TH1F*)gDirectory->Get("MC_HLTele17_Tag"); 
   
    TH1F *k1 = (TH1F*)gDirectory->Get("DATA_WP80_Tag");
    TH1F *k2 = (TH1F*)gDirectory->Get("DATA_WP80_Probe");
    TH1F *k3 = (TH1F*)gDirectory->Get("DATA_RECO_Probe");
    TH1F *k4 = (TH1F*)gDirectory->Get("DATA_HLTele8_Probe");
    TH1F *k5 = (TH1F*)gDirectory->Get("DATA_HLTele8_Tag");
    TH1F *k6 = (TH1F*)gDirectory->Get("DATA_HLTele17_Probe");
    TH1F *k7 = (TH1F*)gDirectory->Get("DATA_HLTele17_Tag");
    
    //Draw histos releated to efficinency
    
    C->Divide(2,2);
    C->cd(1);
    k1->SetMarkerColor(kBlack);
    k1->SetTitle("WP80 eff");
    k1->GetXaxis()->SetTitle("# Jets");
    k1->GetYaxis()->SetRangeUser(0.7, 1);
    k1->SetLineColor(kBlack);
    k1->SetMarkerColor(kBlack);
    k1->Draw("E1");
    k2->SetLineColor(kBlack);
    k2->SetMarkerColor(kBlack);
    k2->SetLineStyle(3);
    k1->GetYaxis()->SetRangeUser(0.7, 1);
    k2->Draw("E1 SAMES");
    h1  ->SetMarkerColor(kRed);
    h1  ->SetLineColor(kRed);
    h1->GetYaxis()->SetRangeUser(0.7, 1);
    h1  ->Draw("E1 SAMES");
    h2  ->SetMarkerColor(kRed);
    h2  ->SetLineColor(kRed);
    h2->SetLineStyle(3);
    h2->GetYaxis()->SetRangeUser(0.7, 1);
    h2  ->Draw("E1 SAMES");

    TLegend *legend_1 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
    legend_1->SetFillColor (0);
    legend_1->SetFillStyle (0);
    legend_1->SetBorderSize (0);
    legend_1->AddEntry (k1, "data Tag", "LP20");
    legend_1->AddEntry (k2, "data Probe", "LP20");
    legend_1->AddEntry (h1, "MC Tag", "L");
    legend_1->AddEntry (h2, "MC Probe", "L");
    legend_1->Draw ("same");

    C->cd(2);
    k4->SetMarkerColor(kBlack);
    k4->SetTitle("HLT");
    k4->GetXaxis()->SetTitle("# Jets");
    k4->GetYaxis()->SetRangeUser(0.93, 1);
    k4->SetLineColor(kBlack);
    k4->SetMarkerColor(kBlack);
    k4->Draw("E1");
    k5->SetMarkerColor(kBlack);
    k5->GetXaxis()->SetTitle("HLT");
    k5->SetLineColor(kBlack);
    k5->SetMarkerColor(kBlack);
    k5->SetLineStyle(3);
    k5->Draw("E1 SAMES");

    k6->SetMarkerColor(kBlack);
    k6->SetLineColor(kBlue);
    k6->SetMarkerColor(kBlue);
    k6->Draw("E1 SAMES");
    k7->SetMarkerColor(kBlue);
    k7->GetXaxis()->SetTitle("HLT");
    k7->SetLineColor(kBlue);
    k7->SetMarkerColor(kBlue);
    k7->SetLineStyle(3);
    k7->Draw("E1 SAMES");

    h4->SetMarkerColor(kRed);
    h4->GetXaxis()->SetTitle("HLT");
    h4->SetLineColor(kRed);
    h4->SetMarkerColor(kRed);
    h4->Draw("E1 SAMES");
    h5->SetMarkerColor(kRed);
    h5->GetXaxis()->SetTitle("HLT");
    h5->SetLineColor(kRed);
    h5->SetMarkerColor(kRed);
    h5->SetLineStyle(3);
    h5->Draw("E1 SAMES");

    h6->SetMarkerColor(kOrange);
    h6->SetLineColor(kOrange);
    h6->SetMarkerColor(kOrange);
    h6->Draw("E1 SAMES");
    h7->SetMarkerColor(kBlack);
    h7->GetXaxis()->SetTitle("HLT");
    h7->SetLineColor(kOrange);
    h7->SetMarkerColor(kOrange);
    h7->SetLineStyle(3);
    h7->Draw("E1 SAMES");

    TLegend *legend_2 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
    legend_2->SetFillColor (0);
    legend_2->SetFillStyle (0);
    legend_2->SetBorderSize (0);
    legend_2->AddEntry (k4, "data Ele8 Probe", "LP20");
    legend_2->AddEntry (k5, "data Ele8 Tag", "LP20");
    legend_2->AddEntry (k6, "data Ele 17 Probe", "LP20");
    legend_2->AddEntry (k7, "data Ele 8 Tag", "LP20");
    legend_2->AddEntry (h4, "MC Ele8 Probe", "LP20");
    legend_2->AddEntry (h5, "MC Ele8 Tag", "LP20");
    legend_2->AddEntry (h6, "MC Ele 17 Probe", "LP20");
    legend_2->AddEntry (h7, "MC Ele 8 Tag", "LP20");
    legend_2->Draw ("same");
    
    C->cd(3);
    k3->SetMarkerColor(kBlack);
    k3->SetTitle("RECO");
    k3->GetXaxis()->SetTitle("# Jets");
    k3->GetYaxis()->SetRangeUser(0.93, 1);
    k3->SetLineColor(kBlack);
    k3->SetMarkerColor(kBlack);
    k3->Draw("E1");
    h3->SetMarkerColor(kRed);
    h3->SetLineColor(kRed);
    h3->SetMarkerColor(kRed);
    h3->Draw("E1 SAMES");
    TLegend *legend_3 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
    legend_3->AddEntry (k3, "data RECO", "LP20");
    legend_3->AddEntry (h3, "MC RECO", "L");
    legend_3->Draw ("same");    


    /*********************************************************/  
    //Perform the efficiency correction

    TH1F* NMCrecoNoEffCorr = (TH1F*)  NMCreco -> Clone("NMCreco");
    NMCrecoNoEffCorr->SetName("NMCrecoNoEffCorr");
    TH1F* NDataNoEffCorr = (TH1F*)  NData -> Clone("NData");
    NDataNoEffCorr->SetName("NDataNoEffCorr");

    TH1F* MCCorr = (TH1F*)  h1 -> Clone("h1");    
    MCCorr->SetName("MCCorr");
    MCCorr->Multiply(h2);
    MCCorr->Multiply(h3);
    MCCorr->Multiply(h4);      
    MCCorr->Multiply(h5);
    MCCorr->Multiply(h6); 
    MCCorr->Multiply(h7);

    //Correct the MC for efficiency
    NMCreco->Divide(MCCorr);

    // Now NTrue has a huge difference in area...Account for it.
    areaRecoVsTruth=((double)NMCreco->Integral())/((double)NTrue->Integral());
    cout<<"NTrue renormalized to the MC eff corrected area! ratio->"<<areaRecoVsTruth<<endl;
    NTrue->Scale(areaRecoVsTruth); 
    cout<<"Warning: data unfolded distribution, obtained after matrix re3sponse, is somehow not rescaled to the area after the eff correction...I correct but CHECK!!!!!!!!!!!!!!!"<<endl;

    DataCorr = (TH1F*)  k1 -> Clone("h1");    
    DataCorr->SetName("DataCorr");
    DataCorr->Multiply(k2);
    DataCorr->Multiply(k3);
    DataCorr->Multiply(k4);      
    DataCorr->Multiply(k5);
    DataCorr->Multiply(k6);
    DataCorr->Multiply(k7);   
    //Correct Data for efficiency
    NData->Divide(DataCorr);

    C->cd(4);
    NMCrecoNoEffCorr->SetMarkerColor(kRed);
    NMCrecoNoEffCorr->SetTitle("Effect of the correction");
    NMCrecoNoEffCorr->GetXaxis()->SetTitle("# Jets");
    NMCrecoNoEffCorr->SetLineColor(kRed);
    NMCreco->Draw("E1");
    NMCreco->SetMarkerColor(kRed);
    NMCreco->SetLineColor(kRed);
    NMCreco->SetLineStyle(3);
    NMCrecoNoEffCorr->Draw("E1 SAMES");
    NDataNoEffCorr->SetMarkerColor(kBlack);
    NDataNoEffCorr->GetXaxis()->SetTitle("Effect of the correction");
    NDataNoEffCorr->SetLineColor(kBlack);
    NDataNoEffCorr->Draw("E1 SAMES");
    NData->SetMarkerColor(kBlack);
    NData->SetLineColor(kBlack);
    NData->SetLineStyle(3);
    NData->Draw("E1 SAMES");
    gPad->SetLogy(0);
    TLegend *legend_4 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
    legend_4->AddEntry (NMCreco, "MC Corr", "LP20");
    legend_4->AddEntry (NMCrecoNoEffCorr, "MC No Corr", "L");
    legend_4->AddEntry (NData, "Data Corr", "LP20");
    legend_4->AddEntry (NDataNoEffCorr, "Data No Corr", "L");
    legend_4->Draw ("same");    

    string title3= s+"JETMULTIControlPlot.png";
    C->Print(title3.c_str());
    cout<<"PNG file saved (maybe) on "<<title3<<endl;

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
  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";

    cout<<"Running "<<method<<" method"<<endl;
    
    //Optimizing the k value
    for (int k=2; k<=maxNJets; k++){
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
      if (correctForEff) NReco->Multiply(DataCorr); // Necessary to have same area... Investigate, please
      JetMultiplicityUnfolded=(TH1F*) NReco->Clone("NReco");
      JetMultiplicityUnfolded->SetName("JetMultiplicityUnfolded");

      //Save info to evaluate the unfolding uncertainties... Da fare a mano ogni volta cambiando il MC e vedendo la differenza nei dati... poi prendi i dati, e li trascrivi nella macro!
      for (int c=0;c<6;c ++){
	cout<<NReco->GetBinContent(c+1)<<endl;
      }

      cmultip->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.3, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      title2="Number of jet + Z distribution. "+title;
      NReco->SetTitle (title2.c_str());
      NReco->GetXaxis ()->SetTitle ("");
      NReco->GetYaxis ()->SetTitle ("Entries");
      NReco->SetMarkerStyle (20);
      NData->SetMarkerStyle (21);
      NData->SetLineColor(kGreen);
      
      NReco->SetMarkerStyle (20);
      NReco->SetStats(0);
      NReco->GetXaxis()->SetTitle("# of Jets");
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

      pad1->SetBottomMargin (0);
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

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.3);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
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
      NReco->GetXaxis ()->SetRangeUser (0, 7.5);
      NReco->GetYaxis ()->SetTitle ("Ratios");
      NReco->GetXaxis()->SetTitle("# of Jets");
      NReco->SetMarkerStyle (20);
      NReco->SetLineWidth (0);
      NReco->SetTitle ("");
      double max=NReco->GetMaximum();
      double min=NReco->GetMinimum();
      NReco->GetYaxis()->SetRangeUser(min,max);
      NReco->SetStats(1);
    
      NReco->Draw ("ep");

      TH1F *NRecoClone= (TH1F*) NMCreco->Clone("NReco");
      NRecoClone->SetName("NRecoClone");

      NRecoClone->Divide(NTrue);		
      NRecoClone->SetMarkerStyle (20);
      NRecoClone->SetMarkerSize(0.0);
      NRecoClone->SetTitle ("");
      NRecoClone->SetStats(1);
      NRecoClone->SetLineStyle(3);
      NRecoClone->SetLineColor(kMagenta+3);
      NRecoClone->Draw ("ep SAMES");
      
      TF1 *f = new TF1("f","1",0,10);
      f->SetLineWidth(1);
      f->Draw("SAMES");

      TLegend *legend_w = new TLegend (0.73494, 0.63, 0.931727, 0.83);
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
      cmultip->cd ();
      cmultip->Print(title3.c_str());
      num.str("");
      cout<<"PNG file saved (maybe) on "<<title3<<endl;
    }
  }

  if (saveFile){
    TFile* w = new TFile(filename.c_str(), "RECREATE");
    w->cd();
    JetMultiplicityUnfolded->Write();
    w->Close();
  }  

  TCanvas *N =new TCanvas ("N jet response matrix", "N jet response matrix", 1000, 700);
  N->cd ();
  NMatx->SetStats (0);
  NMatx->GetXaxis()->SetTitle("Reconstructed # of Jets");
  NMatx->GetYaxis()->SetTitle("Generated # of Jets");
  gStyle->SetPalette (1);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  NMatx->SetMarkerColor (kBlack);
  double entries=1.000/(double)NMatx->GetEntries();
  NMatx->Scale(entries);
  NMatx->Draw ("COLZ,text");
  //N->Print(s+"/MatrixjetMultiplicity.png");

}
