/* Z boson rapidity distribution */
TH1D *yTrue = new TH1D ("y true", "y Truth", 25, -2.5, 2.5);
TH1D *yData = new TH1D ("y data", "y DATA Measured", 25, -2.5, 2.5);
TH2D *yMatx = new TH2D ("y hMatx", "Unfolding Matrix y Rapidity ", 25, -2.5, 2.5, 25, -2.5, 2.5);
TH1D *yMCreco = new TH1D ("y mcreco", "y mcreco", 25, -2.5, 2.5);
TH1D *yData2 = new TH1D ("y data2", "y DATA Measured2", 25, -2.5, 2.5);
TH1D *yRatio_ = new TH1D ("yRatio", "yRatio", 25, -2.5, 2.5);

void Unfolding::LoopZy ()
{
  response_y.UseOverflow();
  cout<<"*********************************"<<endl;
  cout<<" Unfolding Zy"<<endl;
  cout<<"*********************************"<<endl;
  
#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif
  
  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_17.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  fB->cd ("/gpfs/cms/data/2011/jet/jetValidation_DATA_2011_v2_17.root:/validationJEC");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");
  /*costruisco la matrice di unfolding */
  
  fChain = tree_fA;		/* Loop RunA */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;
  
  if (fChain == 0)
    return;
  

  //COnsider the events outside range...
  response_pT.UseOverflow();
  
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      response_y.Fill (Z_y, Z_y_gen);
      
      yTrue->Fill (Z_y_gen);
      yMCreco->Fill (Z_y);
      yMatx->Fill (Z_y, Z_y_gen);
      yRatio_->Fill(Z_y); 
    }
  
  fChain = tree_fB;		 /*Loop RunB */
  Init (fChain);	
  Long64_t nentries2 = fChain->GetEntriesFast ();
  Long64_t nb2 = 0;
  
  if (fChain == 0)
    return;
  
  for (Long64_t jentry = 0; jentry < nentries2; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb2 = fChain->GetEntry (jentry);
      nbytes += nb2;
      //Correct for efficiencies...
      yData->Fill (Z_y);
      yData2->Fill (Z_y);
    }
  
  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=1; k<31; k++){
      int myNumber=k;
      stringstream num;
      num<<myNumber;
      string title="Data Unfolding, using "+method+" method with K="+num.str();
      std::string title2="Z rapidity distribution. "+title;
      cout<<title<<endl;
      
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_y (&response_y, yData, myNumber);
	yReco = (TH1D *) unfold_y.Hreco ();
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_y (&response_y, yData, myNumber);
	yReco = (TH1D *) unfold_y.Hreco ();
      }
  
      TH1F* yRatio = (TH1F*) yRatio_ -> Clone("yRatio");
      

      TCanvas *e = new TCanvas ("e", "e", 1000, 700);
      e->cd ();
      title2="Z rapidity distribution. "+title;
      yReco->SetTitle (title2.c_str());
      yReco->GetXaxis ()->SetTitle ("");
      yReco->GetYaxis ()->SetTitle ("Entries");
      yReco->SetMarkerStyle (20);
      double area3 = ((yReco->Integral ()) / yTrue->Integral ());
      yReco->Scale (1.00000 / area3);
      yData->Scale (1.00000 / area3);
      yReco->Draw ();		//risultato dell'unfolding
      yReco->SetLineColor (kRed);
      yReco->SetLineWidth (2);
      yMCreco->SetLineWidth (2);
      yData->SetLineWidth (2);
      yMCreco->SetLineStyle (2);
      yMCreco->Draw ("SAME");
      yMCreco->SetLineColor (kBlue + 1);
      yTrue->SetLineColor (kBlack);
      yReco->SetMarkerStyle (20);
      yTrue->Draw ("SAME");
      yData->SetLineColor(kGreen+1);
      yData->SetLineWidth(.5);
      yData->SetLineStyle(2);
      yData->SetMarkerStyle(20);
      yData->Draw("SAME");
      
      TPad *pad13 = new TPad ("pad13", "pad13", 0, 0.3, 1, 1);
      pad13->Draw ();
      pad13->cd ();
      yReco->DrawCopy ();
      pad13->SetLogy (1);
      yTrue->Draw ("same");
      yMCreco->Draw ("same");
      yData->Draw("same");
      
      pad13->SetBottomMargin (0);
      yReco->SetTitleSize (0);
      
      yTrue->SetTitleSize (0);
      
      
      TLegend *legend_d3 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d3->SetFillColor (0);
      legend_d3->SetFillStyle (0);
      legend_d3->SetBorderSize (0);
      legend_d3->AddEntry (yReco, "MC Unfolded", "LP20");
      legend_d3->AddEntry (yTrue, "MC truth", "L");
      legend_d3->AddEntry (yMCreco, "MC reco", "L");
      legend_d3->AddEntry(yData, "Data Folded", "L");
      legend_d3->Draw ("same");
      
      e->cd ();
      
      TPad *pad14 = new TPad ("pad14", "pad14", 0, 0, 1, 0.3);
      pad14->SetTopMargin (0);
      pad14->Draw ();
      pad14->cd ();
      yReco->GetXaxis ()->SetLabelSize (0.1);
      yReco->GetYaxis ()->SetLabelSize (0.08);
      yReco->SetStats (0);
      yReco->Divide (yData);
      yReco->SetMarkerStyle (6);
      yReco->GetXaxis ()->SetLabelSize (0.06);
      yReco->GetYaxis ()->SetLabelSize (0.06);
      yReco->GetXaxis ()->SetTitleSize (0);
      yReco->GetYaxis ()->SetTitleSize (0.06);
      yReco->GetYaxis ()->SetTitleOffset (0.5);
      
      yReco->GetYaxis ()->SetRangeUser (0.9, 1.1);
      yReco->GetXaxis ()->SetRangeUser (-2.5, 2.5);
      yReco->GetYaxis ()->SetTitle ("Ratios");
      yReco->SetMarkerStyle (20);
      yReco->SetLineWidth (1);
      yReco->SetTitle ("");
      double max=yReco->GetMaximum();
      double min=yReco->GetMinimum();
      yReco->GetYaxis()->SetRangeUser(min,max);
      yReco->SetStats(1);
      yReco->Draw ("ep");
      
      yRatio->Divide(yTrue);		
      yRatio->SetMarkerStyle (20);
      yRatio->SetMarkerSize(0.0);
      yRatio->SetTitle ("");
      yRatio->SetStats(1);
      yRatio->SetLineStyle(3);
      yRatio->SetLineColor(kMagenta+3);
      yRatio->Draw ("HIST SAME");
      
      TLegend *legend_w3 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_w3->SetFillColor (0);
      legend_w3->SetFillStyle (0);
      legend_w3->SetBorderSize (0);
      legend_w3->AddEntry (yReco, "Data Unfolded / MC truth", "LP20");
      legend_w3->AddEntry (yRatio, "MC reco / MC truth", "L");
      legend_w3->Draw ("same");
    
      pad14->Update(); 

      /*n->SetLineColor (kBlue + 1);
	n->SetLineWidth (1);
	n->SetLineStyle (2);
	n->Draw ("same");
	jj3->SetParameter(0, 1);
	jj3->SetLineWidth(.5);
	jj3->SetLineColor(kWhite);
	yReco->Fit(jj3);
	jj3->Draw ("same");
	n->Draw ("same");
      
	e->cd ();*/
      string title3= s+"Zy_"+method+"_"+num.str()+".png";
      e->Print(title3.c_str());
      num.str("");
    }
  }
  TCanvas *Y =    new TCanvas ("rapidity response matrix", "rapidity response", 1000, 700);
  Y->cd ();
  
  gStyle->SetPalette (1.);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  double entries=1.000/(double)yMatx->GetEntries();
  yMatx->Scale(entries);
  yMatx->SetMarkerColor (kBlack);
  gPad->SetLogz(1);
  yMatx->Draw ("COLZ,text");
  string title3= s+"/MatrixZy.png";
  Y->Print(title3.c_str());
}
