TH1D *HTrue = new TH1D ("HTrue", "H Truth", 11, 30, 330);
TH1D *HData = new TH1D ("HData", "H DATA Measured", 11, 30, 330);
TH2D *HMatx =
  new TH2D ("H hMatx", "Unfolding Matrix in # of jets + Z", 11, 30, 330, 11, 30,
	    330);
TH2D *HMatxlong =
  new TH2D ("H hMatxlong", "Unfolding Matrix in # of jets + Z", 12, 0, 330, 12,
	    0, 330);
TH1D *HMCreco = new TH1D ("H mcreco", "H mcreco", 11, 30, 330);
TH1D *HMCrecoratio_ = new TH1D ("H mcrecoratio_", "H mcreco_", 11, 30, 330);
TH1D *HData2 = new TH1D ("H data2", "H DATA Measured2", 11, 30, 330);
TH1F *relativebkgH =
  new TH1F ("relativebkgH", "relativebkg bin contribution", maxNJets - 0.5,
	    0.5, maxNJets - 0.5);
TH1F *HUnfolded;
int kminH = 6;
int kmaxH = 7;
bool spanKvaluesH = false;
double thresh = 15.0;

double
getGenJetPtOfAGivenOrderH (int Jet_multiplicity_gen, int whichjet,
			   double thresh, double jet1_pt_gen,
			   double jet2_pt_gen, double jet3_pt_gen,
			   double jet4_pt_gen, double jet1_eta_gen,
			   double jet2_eta_gen, double jet3_eta_gen,
			   double jet4_eta_gen)
{
  double jetPt = 0.0;
  if (Jet_multiplicity_gen == 0 && jet1_pt_gen < 30)
    return 0;
  std::vector < double >pt;

  if (Jet_multiplicity_gen == 0 && fabs (jet1_eta_gen) <= 2.4)
    pt.push_back (jet1_pt_gen);
  if (Jet_multiplicity_gen == 0 && fabs (jet1_eta_gen) <= 2.4)
    pt.push_back (jet1_pt_gen);

  for (int i = 1; i <= 4; i++)
    {
      if (i == 1)
	{
	  if (jet1_pt_gen > thresh && fabs (jet1_eta_gen) <= 2.4)
	    {
	      pt.push_back (jet1_pt_gen);
	    }
	}
      if (i == 2)
	{
	  if (jet2_pt_gen > thresh && fabs (jet2_eta_gen) <= 2.4)
	    {
	      pt.push_back (jet2_pt_gen);
	    }
	}
      if (i == 3)
	{
	  if (jet3_pt_gen > thresh && fabs (jet3_eta_gen) <= 2.4)
	    {
	      pt.push_back (jet3_pt_gen);
	    }
	}
      if (i == 4)
	{
	  if (jet4_pt_gen > thresh && fabs (jet4_eta_gen) <= 2.4)
	    {
	      pt.push_back (jet4_pt_gen);
	    }
	}
    }				// for


  if (whichjet <= pt.size ())
    jetPt = pt[whichjet - 1];
  //restituisci il pt (se valido) del get che ti chiede corrispondene all'oridne che chiedsi

  //if (jetPt != jet1_pt_gen) cout<<"jet multipl->"<<Jet_multiplicity_gen<<" jet1pt->"<<jet1_pt_gen<<" jet2pt->"<<jet2_pt_gen<<" jet3_pt->"<<jet3_pt_gen<<" jet4_pt->"<<jet4_
//      pt_gen<<" jet1eta->"<<jet1_eta_gen<<" jet2eta->"<<jet2_eta_gen<<" jet3_eta->"<<jet3_eta_gen<<" jet4_eta->"<<jet4_eta_gen<<" (return "<<jetPt<<")"<<endl;

  return jetPt;

}


void
Unfolding::LoopHt ()
{
  cout << endl;
  cout << "*********************************" << endl;
  cout << "Unfolding HT" << endl;
  cout << "*********************************" << endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  if (spanKvaluesH)
    {
      kminH = 1;
      kmaxH = maxNJets - 2;
    }


  string sdatadir = sdata + ":/validationJEC";
  string smcdir = smc + ":/validationJEC";
  fA->cd (smcdir.c_str ());
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeValidationJEC_");
  fB->cd (sdatadir.c_str ());
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");

  //Setting the errors
  HTrue->Sumw2 ();
  HMCreco->Sumw2 ();
  HMCrecoratio_->Sumw2 ();
  HData->Sumw2 ();

  int count = 0;
  /*costruisco la matrice di unfolding */

  fChain = tree_fA;
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (fChain == 0)
    return;

  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;
      
      double Ht, Ht_gen;
      double correctGenJetPt;
	  /*  getGenJetPtOfAGivenOrderH (Jet_multiplicity_gen, 1, 15.0,
				       jet1_pt_gen, jet2_pt_gen, jet3_pt_gen,
				       jet4_pt_gen, jet1_eta_gen,
				       jet2_eta_gen,
				       jet3_eta_gen, jet4_eta_gen);
*/
      for (int i = 1; i <= 4; i++)
	{
	    correctGenJetPt = getGenJetPtOfAGivenOrderH (Jet_multiplicity_gen, i, 30.0,
				       jet1_pt_gen, jet2_pt_gen, jet3_pt_gen,
				       jet4_pt_gen, jet1_eta_gen,
				       jet2_eta_gen,
				       jet3_eta_gen, jet4_eta_gen);



	  if (correctGenJetPt>0 && correctGenJetPt<7000) Ht_gen += correctGenJetPt;

	}


      if (jet1_pt >0 && jet1_pt<7000) Ht += jet1_pt;
      if (jet2_pt >0 && jet2_pt<7000) Ht += jet2_pt;
      if (jet3_pt >0 && jet3_pt<7000) Ht += jet3_pt;
      if (jet4_pt >0 && jet4_pt<7000) Ht += jet4_pt;
      if (jet5_pt >0 && jet5_pt<7000) Ht += jet5_pt;
      if (jet6_pt >0 && jet6_pt<7000) Ht += jet6_pt;


      //cout<<"Ht gen="<<Ht_gen<<"    "<<"Ht="<<Ht<<endl;
      
      
      if (correctForEff)
	{
	  if (!useElectronsToCorrect)
	    {
	      std::vector < double >valuesdata =
		getEfficiencyCorrectionJetMultiplicity (fAeff, fBeff,
							Ht, "Data");
	      double effcorrdata = 1.00 / valuesdata[0];
	      double efferrdata =
		valuesdata[1] / pow (valuesdata[0], 2);
	      HMCreco->Fill (Ht, effcorrdata);
	      HTrue->Fill (Ht_gen, effcorrdata);
	      HMatx->Fill (Ht, Ht_gen,1);
	      HMatxlong->Fill (Ht, Ht_gen,1);

	    }
	  else
	    {
	      double effcorrdata =
		1.00 / getEfficiencyCorrectionPtUsingElectron (fAeff,
							       fBeff,
							       e1_pt,
							       e1_eta,
							       e2_pt,
							       e2_eta,
							       "Data");
	      HMCreco->Fill (Ht, effcorrdata);
	      HTrue->Fill (Ht_gen, effcorrdata);
	      HMatx->Fill (Ht, Ht_gen,1);
	      HMatxlong->Fill (Ht, Ht_gen,1);

	    }
	}
      else
	{
	  HMCreco->Fill (Ht);
	  HTrue->Fill (Ht_gen);
	  HMatx->Fill (Ht, Ht_gen,1);
	  HMatxlong->Fill (Ht, Ht_gen,1);

	}

      Ht=0;
      Ht_gen=0;
    }
  
  /////////////////////////
  //  Correct for background
  /////////////////////////
  
  if (correctForBkg)
    {
      
    }
  
  /*Loop on data */
  fChain = tree_fB;
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

      double Ht ; 
      if (jet1_pt >0 && jet1_pt<7000) Ht += jet1_pt;
      if (jet2_pt >0 && jet2_pt<7000) Ht += jet2_pt;
      if (jet3_pt >0 && jet3_pt<7000) Ht += jet3_pt;
      if (jet4_pt >0 && jet4_pt<7000) Ht += jet4_pt;
      if (jet5_pt >0 && jet5_pt<7000) Ht += jet5_pt;
      if (jet6_pt >0 && jet6_pt<7000) Ht += jet6_pt; 


      //cout<<"Ht data="<<Ht<<endl;
	  
      
      if (correctForEff)
	{
	  if (!useElectronsToCorrect)
	    {
	      std::vector < double >valuesdata =
		getEfficiencyCorrectionJetMultiplicity (fAeff, fBeff,
							Ht, "Data");
	      double effcorrdata = 1.00 / valuesdata[0];
	      double efferrdata = valuesdata[1] / pow (valuesdata[0], 2);
	      HData->Fill (Ht, effcorrdata);
	      HData2->Fill (Ht, effcorrdata);
	    }
	  else
	    {
	      double effcorrdata =
		1.00 / getEfficiencyCorrectionPtUsingElectron (fAeff,
								   fBeff,
							       e1_pt,
							       e1_eta,
							       e2_pt,
							       e2_eta,
							       "Data");
	      HData->Fill (Ht, effcorrdata);
	      HData2->Fill (Ht, effcorrdata);
	    }
	}
      else
	{
	  HData->Fill (Ht);
	  HData2->Fill (Ht);
	    }
      Ht=0;

    }
  ///   NOTA BENE!!
  //PER QUALCHE RAGIONE NON BISOGNA NORMALIZZARE NULLA PRIMA DI FARE LA RESPONSE MATRIX!!
  //////////////
  // MC Normalization
  //////////////
  double ScaleMCData =
    ((double) HData->GetEntries () / (double) HMCreco->GetEntries ());
  cout << "scale=" << ScaleMCData << endl;
  
  /////////////////////////
  //  Correct for background
  /////////////////////////
  
  if (correctForBkg)
    {
      std::vector < double >bckcoeff;
      bckcoeff = getBackgroundContributions (bkgstring, "jet_Multiplicity");
      for (unsigned int k = 0; k < maxNJets; k++)
	{
	  HData->SetBinContent (k + 1, HData->GetBinContent (k + 1) - bckcoeff[k + 1]);	//K+1 perche' c'e' il bkgr a 0 Jets...
	  if (HData->GetBinContent (k + 1) > 0)
	    {
	      relativebkgH->SetBinContent (k + 1,
					   bckcoeff[k +
						    1] /
					   HData->GetBinContent (k + 1));
	      cout << "Data:" << HData->GetBinContent (k +
						       1) << " bck:" <<
		bckcoeff[k + 1] << " (coefficient is " << bckcoeff[k +
								   1] <<
		"). Relative bin ratio is " << bckcoeff[k +
							1] /
		HData->GetBinContent (k + 1) << endl;
	    }
	  else
	    {
	      relativebkgH->SetBinContent (k + 1, 0);
	      cout << "Data:" << HData->GetBinContent (k +
						       1) << " bck:" <<
		bckcoeff[k + 1] << " (coefficient is " << bckcoeff[k +
								   1] <<
		"). Relative bin ratio is 0" << endl;
	    }
	  cout << "after " << bckcoeff[k] / NData->GetBinContent (k +
								  1) << endl;
	}
    }

  // Fill the matrix response with the MC values, this time as histograms!
  RooUnfoldResponse response_H (HMCreco, HTrue, HMatx);
  response_H.UseOverflow ();

  cout << "***********************" << endl;
  cout << "MC will be normalized to data, using entries" << endl;
  cout << "N entries in Data:" << HData->
    GetEntries () << " and MC:" << HMCreco->
    GetEntries () << " ratio->" << ScaleMCData << endl;
  cout << endl;
  HMCreco->Scale (ScaleMCData);
  HTrue->Scale (ScaleMCData);
  HMCrecoratio_->Scale (ScaleMCData);


  //Repeating each algorithm
  for (int j = 0; j < 1; j++)
    {
      string method;
      if (j == 0)
	method = "Bayesian";
      if (j == 1)
	method = "Svd";

      cout << "Running " << method << " method" << endl;

      //Optimizing the k value
      for (int k = kminH; k < kmaxH; k++)
	{
	  int myNumber = k;
	  stringstream num;
	  num << myNumber;
	  string title =
	    "Data unfolding " + method + " method with K=" + num.str ();
	  std::string title2 = "Ht distribution. " + title;
	  cout << title << endl;

	  if (method == "Bayesian")
	    {
	      RooUnfoldBayes unfold_H (&response_H, HData, myNumber);
	      HReco = (TH1D *) unfold_H.Hreco ();
	    }
	  if (method == "Svd")
	    {
	      RooUnfoldSvd unfold_H (&response_H, HData, myNumber);	// OR
	      HReco = (TH1D *) unfold_H.Hreco ();
	    }

	  HReco->Sumw2 ();

	  if (differentialCrossSection)
	    {
	      HReco->Scale (1. / HReco->Integral ());
	      HTrue->Scale (1. / HTrue->Integral ());
	      HMCreco->Scale (1. / HMCreco->Integral ());
	      HData->Scale (1. / HData->Integral ());
	    }

	  HUnfolded = (TH1F *) HReco->Clone ("HReco");
	  HUnfolded->SetName ("HUnfolded");
	  //Save info to evaluate the unfolding uncertainties... Da fare a mano ogni volta cambiando il MC e vedendo la differenza nei dati... poi prendi i dati, e li trascrivi nella macro!
	  for (int c = 0; c < 6; c++)
	    {
	      cout << HReco->GetBinContent (c + 1) << endl;
	    }
	
	  //cmultip->cd ();
	  TCanvas *c = new TCanvas ("c", "c", 1000, 700);
	  c->cd();
	  TPad *pad1 = new TPad ("pad1", "pad1", 0.01, 0.33, 0.99, 0.99);
	  pad1->Draw ();
	  pad1->cd ();
	  gPad->SetLogy (1);
	  pad1->SetTopMargin (0.1);
	  pad1->SetBottomMargin (0.01);
	  pad1->SetRightMargin (0.1);
	  pad1->SetFillStyle (0);

	  title2 = "H_{T} differential cross section" + title;
	  HReco->SetTitle (title2.c_str ());
	  HReco->GetXaxis ()->SetTitle ("");
	  HReco->GetYaxis ()->SetTitle("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/dH_{T}");
	  HReco->SetMarkerStyle (20);
	  HData->SetMarkerStyle (21);
	  HData->SetLineColor (kGreen);

	  HReco->SetMarkerStyle (20);
	  HReco->SetStats (0);
	  HMCreco->SetStats(0);
	  HData->SetStats(0);
          HTrue->SetStats(0);
	  
	  HReco->GetXaxis ()->SetTitle ("H_{T}");
	  HReco->GetXaxis ()->SetTitleSize (0.00);
	  HReco->GetYaxis ()->SetLabelSize (0.07);
	  HReco->GetXaxis ()->SetLabelSize (0.00);
	  HReco->GetYaxis ()->SetTitleSize (0.08);
	  HReco->GetYaxis ()->SetTitleOffset (0.62);
	  HReco->Draw ("EP");	//risultato dell'unfolding
	  HReco->SetLineColor (kRed);
	  HReco->SetLineWidth (2);
	  HMCreco->Draw();
	  HMCreco->SetLineColor (kBlue + 1);
	  HMCreco->SetLineStyle (2);
	  HTrue->SetLineColor (kBlack);
	  HMCreco->SetLineWidth (2);
	  HTrue->SetLineWidth (2);

	  HTrue->Draw ("EPSAME");
	  HData2->SetLineColor (kGreen + 1);
	  HData2->Draw ("EPSAME");

	  HReco->DrawCopy ();
	  pad1->SetLogy (1);
	  HTrue->Draw ("same"); /*same*/
	  HMCreco->Draw ("same");   /*same*/
	  HData->SetLineStyle (2);
	  HData->Draw ("same");

	  //      pad1->SetBottomMargin (0);
	  HReco->SetTitleSize (0);

	  HTrue->SetTitleSize (0);

	  TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
	  legend_d->SetFillColor (0);
	  legend_d->SetFillStyle (0);
	  legend_d->SetBorderSize (0);
	  legend_d->AddEntry (HReco, "Data Unfolded", "LP20");
	  legend_d->AddEntry (HTrue, "MC truth", "L");
	  legend_d->AddEntry (HMCreco, "MC reco", "L");
	  legend_d->AddEntry (HData, "Data Folded", "L");
	  legend_d->Draw ("same");

	  TLatex *latexLabel=CMSPrel(4.890,""); // make fancy label
          latexLabel->Draw("same");
	  pad1->Update();
	  
	  c->cd();
	  //cmultip->cd ();

	  TPad *pad2 = new TPad ("pad2", "pad2", 0.01, 0.01, 0.99, 0.32);
	  pad2->SetTopMargin (0);
	  pad2->Draw ();
	  pad2->cd ();
	  pad2->SetTopMargin (0.01);
	  pad2->SetBottomMargin (0.3);
	  pad2->SetRightMargin (0.1);
	  pad2->SetFillStyle (0);

	  HReco->GetXaxis ()->SetLabelSize (0.1);
	  HReco->GetYaxis ()->SetLabelSize (0.08);
	  HReco->SetStats (0);
	  HReco->Divide (HTrue);
	  HReco->SetMarkerStyle (6);
	  HReco->GetXaxis ()->SetLabelSize (0.06);
	  HReco->GetYaxis ()->SetLabelSize (0.06);
	  HReco->GetXaxis ()->SetTitleSize (0);
	  HReco->GetYaxis ()->SetTitleSize (0.06);
	  HReco->GetYaxis ()->SetTitleOffset (0.5);

	  HReco->GetYaxis ()->SetRangeUser (0.8, 1.2);
	  //NReco->GetXaxis ()->SetRangeUser (0, 7.5);
	  HReco->SetMarkerStyle (20);
	  HReco->SetLineWidth (0);
	  HReco->SetTitle ("");
	  HReco->SetStats (0);
	  HReco->GetXaxis ()->SetLabelSize (0.1);
	  HReco->GetXaxis ()->SetTitleSize (0);
	  HReco->GetYaxis ()->SetTitleSize (0.06);
	  HReco->GetYaxis ()->SetTitleOffset (0.5);

	  //NReco->GetXaxis ()->SetRangeUser (0, 5);
	  HReco->GetYaxis ()->SetTitle ("Ratios");
	  HReco->GetXaxis ()->SetTitle ("H_{T} [GeV/c]");
	  HReco->SetMarkerStyle (20);
	  HReco->SetLineWidth (0);
	  HReco->SetTitle ("");
	  HReco->SetLineWidth (0.1);
	  HReco->GetYaxis ()->SetNdivisions (7);
	  HReco->GetXaxis ()->SetTitleSize (0.14);
	  HReco->GetXaxis ()->SetLabelSize (0.14);
	  HReco->GetYaxis ()->SetLabelSize (0.11);
	  HReco->GetYaxis ()->SetTitleSize (0.11);
	  HReco->GetYaxis ()->SetTitleOffset (0.28);
	  HReco->GetYaxis ()->SetTitle ("ratio data/MC");

	  HReco->Draw ("ep");

	  TH1F *HRecoClone = (TH1F *) HMCreco->Clone ("HReco");
	  HRecoClone->SetName ("HRecoClone");
	  HRecoClone->Sumw2 ();

	  HRecoClone->Divide (HTrue);
	  HRecoClone->SetMarkerStyle (20);
	  HRecoClone->SetMarkerSize (0.0);
	  HRecoClone->SetTitle ("");
	  HRecoClone->SetStats (1);
	  HRecoClone->SetLineStyle (3);
	  HRecoClone->SetLineColor (kMagenta + 3);
	  HRecoClone->SetStats (0);

	  HRecoClone->Draw ("ep SAMES");

	  TF1 *f = new TF1 ("f", "1", 0, 10);
	  f->SetLineWidth (1);
	  f->Draw ("SAMES");

	  TLegend *legend_w =
	    new TLegend (0.197791, 0.736607, 0.394578, 0.9375);
	  legend_w->SetFillColor (0);
	  legend_w->SetFillStyle (0);
	  legend_w->SetBorderSize (0);
	  legend_w->AddEntry (HReco, "Data Unfolded / MC truth", "LP20");
	  legend_w->AddEntry (HRecoClone, "MC reco / MC truth", "L");
	  legend_w->Draw ("same");

	  pad2->Update ();

	  gROOT->SetStyle("Plain");

	  string title3 = s + "HT" + method + "_" + num.str ();
	  if (correctForEff)
	    title3 = s + "HT" + method + "_" + num.str () + "_effcorr.png";
	  else
	    title3 = s + "HT" + method + "_" + num.str () + ".png";
          
	  c->cd();
	  //cmultip->cd ();

	  c/*multip*/->Print (title3.c_str ());
	  num.str ("");
	  cout << "PNG file saved (maybe) on " << title3 << endl;

	}
    }

//  if (saveFile)
//    {
      TFile *w = new TFile ("HT_unfolded"/*filename.c_str ()*/, "UPDATE");
      w->cd ();
      HUnfolded->Write ();
      HTrue->Write ();
      w->Close ();
//    }

  TCanvas *N =
    new TCanvas ("Ht jet response matrix", "Ht jet response matrix", 1000,
		 700);
  N->cd ();
  HMatxlong->SetStats (1);
  gStyle->SetOptStat (1111111);
  HMatxlong->GetXaxis ()->SetTitle ("Reconstructed Ht");
  HMatxlong->GetYaxis ()->SetTitle ("Generated Ht");
  gStyle->SetPalette (1);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  HMatxlong->SetMarkerColor (kBlack);
  double entries=1.000/(double)HMatx->Integral();
  HMatx->Scale(entries);
  HMatxlong->Draw ("COLZ,text");
//  N->Print(s+"/MatrixHt.png");

}
