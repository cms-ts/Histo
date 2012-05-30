/* Z boson pT distribution */
TH1D *PTrue = new TH1D ("pT true", "pT Truth", 20, 0, 200);
TH1D *PData = new TH1D ("pT data", "pT DATA Measured", 20, 0, 200);
TH2D *PMatx = new TH2D ("pT hMatx", "Unfolding Matrix Z pT ", 100, 0, 100, 20, 0, 200);
TH1D *PMCreco = new TH1D ("pT mcreco", "pT mcreco", 20, 0, 200);
TH1D *PData2 = new TH1D ("pT data2", "pT DATA Measured2", 20, 0, 200);
TH1D *PRatio_ = new TH1D ("PRatio_", "PRatio_", 20, 0, 200);

void Unfolding::LoopZpt ()
{
  cout<<"*********************************"<<endl;
  cout<<"This Macro will perform a test   "<<endl;
  cout<<"The unfolding matrix will be applied"<<endl;
  cout<<"On the MC reco instead of data"<<endl;
  cout<<"Must be exactly alike"<<endl;
  cout<<"*********************************"<<endl;
  
#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif
  
  fA->cd ("/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011_v2_17.root:/validationJEC");
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  //DATA
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
      
      
      if (Z_pt > 500 || Z_pt_gen > 500 || Z_pt <=0 || Z_pt_gen <=0)
	continue;
      
      response_pT.Fill (Z_pt, Z_pt_gen);
     
      //double R = Z_pt/Z_pt_gen;

      PRatio_->Fill(Z_pt);
       
      PTrue->Fill (Z_pt_gen);
      PMCreco->Fill (Z_pt);
      PMatx->Fill (Z_pt, Z_pt_gen);
      
    }
  
  fChain = tree_fB;		/* Loop RunB */
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
      PData->Fill (Z_pt);
      PData2->Fill (Z_pt);
      
    }
  
  
  for (int j=0; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=2; k<=20; k++){
      int myNumber=k;
      stringstream num;
      num<<myNumber;
      string title="Data Unfolding, using "+method+" method with K="+num.str();
      std::string title2="Z pt distribution. "+title;
      cout<<title<<endl;
      
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_pT (&response_pT, PData, myNumber);
	PReco = (TH1D *) unfold_pT.Hreco ();
      }
      if (method=="Svd"){
	RooUnfoldSvd unfold_pT (&response_pT, PData, myNumber);
	PReco = (TH1D *) unfold_pT.Hreco ();
      }
      
      TCanvas *q = new TCanvas ("q", "q", 1000, 700);
      q->cd ();

      PRatio->Draw();

      //TH1F* PRatio = (TH1F*) PRatio_ -> Clone("PRatio_");

      TCanvas *d = new TCanvas ("d", "d", 1000, 700);
      d->cd ();
      title2="Z pT distribution. "+title;
      PReco->SetTitle (title2.c_str());
      PReco->GetXaxis ()->SetTitle ("");
      PReco->GetYaxis ()->SetTitle ("Entries");
      PReco->SetMarkerStyle (20);
      double area2 = ((PReco->Integral ()) / PTrue->Integral ());
      PReco->Scale (1.00000 / area2);
      PData->Scale (1.00000 / area2);
      PReco->Draw ();		//risultato dell'unfolding
      PReco->SetLineColor (kRed);
      PReco->SetLineWidth (2);
      PMCreco->SetLineWidth (2);
      PData->SetLineWidth (1);
      PData->SetLineColor(kGreen);
      PData->SetLineStyle(2);
      PMCreco->SetLineStyle (2);
      PMCreco->Draw ("SAME");
      PMCreco->SetLineColor (kBlue + 1);
      PTrue->SetLineColor (kBlack);
      PReco->SetMarkerStyle (20);
      PTrue->Draw ("SAME");
      TPad *pad12 = new TPad ("pad12", "pad12", 0, 0.3, 1, 1);
      pad12->Draw ();
      pad12->cd ();
      PReco->DrawCopy ();
      pad12->SetLogy (1);
      PTrue->Draw ("same");
      PMCreco->Draw ("same");
      PData->Draw("same");
      
      pad12->SetBottomMargin (0);
      PReco->SetTitleSize (0);
      
      PTrue->SetTitleSize (0);
      
      TLegend *legend_d2 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d2->SetFillColor (0);
      legend_d2->SetFillStyle (0);
      legend_d2->SetBorderSize (0);
      legend_d2->AddEntry (PReco, "Data Unfolded", "LP20");
      legend_d2->AddEntry (PTrue, "MC truth", "L");
      legend_d2->AddEntry (PMCreco, "MC reco", "L");
      legend_d2->AddEntry(PData, "Data Folded", "L");
      legend_d2->Draw ("same");
      
      d->cd ();
      
      TPad *pad22 = new TPad ("pad22", "pad22", 0, 0, 1, 0.3);
      pad22->SetTopMargin (0);
      pad22->Draw ();
      pad22->cd ();
      PReco->GetXaxis ()->SetLabelSize (0.1);
      PReco->GetYaxis ()->SetLabelSize (0.08);
      PReco->SetStats (0);
      PReco->Divide (PData);
      PReco->SetMarkerStyle (6);
      PReco->GetXaxis ()->SetLabelSize (0.06);
      PReco->GetYaxis ()->SetLabelSize (0.06);
      PReco->GetXaxis ()->SetTitleSize (0);
      PReco->GetYaxis ()->SetTitleSize (0.06);
      PReco->GetYaxis ()->SetTitleOffset (0.5);
      
      //PReco->GetYaxis ()->SetRangeUser (0, 1.1);
      PReco->GetXaxis ()->SetRangeUser (0, 200);
      PReco->GetYaxis ()->SetTitle ("Ratios");
      PReco->SetMarkerStyle (20);
      PReco->SetLineWidth (1);
      PReco->SetTitle ("");
      double max=PReco->GetMaximum();
      double min=PReco->GetMinimum();
      PReco->GetYaxis()->SetRangeUser(min,max+0.1);
      PReco->SetStats(1);
      PReco->Draw ("ep");
      
      
      PRatio->Divide(PTrue);		
      PRatio->SetMarkerStyle (20);
      PRatio->SetMarkerSize(0.0);
      PRatio->SetTitle ("");
      PRatio->SetStats(1);
      PRatio->SetLineStyle(3);
      PRatio->SetLineColor(kMagenta+3);
      PRatio->Draw ("HIST SAME");
      
      TLegend *legend_w2 = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_w2->SetFillColor (0);
      legend_w2->SetFillStyle (0);
      legend_w2->SetBorderSize (0);
      legend_w2->AddEntry (PReco, "Data Unfolded / MC truth", "LP20");
      legend_w2->AddEntry (PRatio, "MC reco / MC truth", "L");
      legend_w2->Draw ("same");

      pad22->Update();

      /*m->SetLineColor (kBlue + 1);
	m->SetLineWidth (1);
	m->SetLineStyle (2);
	m->Draw ("same");
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(111);
	jj2->SetParameter(0, 1);
	jj2->SetLineWidth(.5);
	jj2->SetLineColor(kWhite);
	PReco->Fit(jj2);
	jj2->Draw ("same");
	m->Draw ("same");*/
      
      d->cd ();
      string title3= s+"ZPt"+method+"_"+num.str()+".png";
      d->Print(title3.c_str());
      num.str("");
    }
  }
  TCanvas *P = new TCanvas ("Pt response matrix", "Pt response", 1000, 700);
  P->cd ();
  
  gStyle->SetPalette (1.);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  double entries=1.000/(double)PMatx->GetEntries();
  PMatx->Scale(entries);
  PMatx->SetMarkerColor (kBlack);
  gPad->SetLogz(1);
  PMatx->Draw ("COLZ,text");
  string title3= s+"/MatrixZpt.png";
  P->Print(title3.c_str());
}
