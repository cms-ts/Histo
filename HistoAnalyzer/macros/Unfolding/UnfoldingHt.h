int Nbins = 12;
int Nmin = 30;
int Nmax = 630;
int kminH = 11;
int kmaxH = 12;
bool spanKvaluesH = false;
double thresh = 15.0;
TH1F *HReco2;
string numjet;

int
getNumberOfValidGenJetsH (int Jet_multiplicity_gen, double thresh,double jet1_pt_gen, double jet2_pt_gen,double jet3_pt_gen, double jet4_pt_gen,double jet5_pt_gen, double jet6_pt_gen,double jet1_eta_gen, double jet2_eta_gen,double jet3_eta_gen, double jet4_eta_gen,double jet5_eta_gen, double jet6_eta_gen)
{
  int counter = 0;
  for (int i = 1; i <= Jet_multiplicity_gen; i++)
    {

      if (i == 1)
	{
	  if (jet1_pt_gen < thresh || fabs (jet1_eta_gen) > 2.4)
	    counter++;
	}

      if (i == 2)
	{
	  if (jet2_pt_gen < thresh || fabs (jet2_eta_gen) > 2.4)
	    counter++;
	}

      if (i == 3)
	{
	  if (jet3_pt_gen < thresh || fabs (jet3_eta_gen) > 2.4)
	    counter++;
	}

      if (i == 4)
	{
	  if (jet4_pt_gen < thresh || fabs (jet4_eta_gen) > 2.4)
	    counter++;
	}

      if (i == 5)
	{
	  if (jet5_pt_gen < thresh || fabs (jet5_eta_gen) > 2.4)
	    counter++;
	}

      if (i == 6)
	{
	  if (jet6_pt_gen < thresh || fabs (jet6_eta_gen) > 2.4)
	    counter++;
	}

    }				// for
  return counter;

}				// end


double
getGenJetPtOfAGivenOrderH (int Jet_multiplicity_gen, int whichjet,double thresh, double jet1_pt_gen,double jet2_pt_gen, double jet3_pt_gen,double jet4_pt_gen, double jet5_pt_gen,double jet6_pt_gen, double jet1_eta_gen,double jet2_eta_gen, double jet3_eta_gen,double jet4_eta_gen, double jet5_eta_gen,double jet6_eta_gen)
{
  double jetPt = 0.0;
  if (Jet_multiplicity_gen == 0 && jet1_pt_gen < 30)
    return 0;
  std::vector < double >pt;

  if (Jet_multiplicity_gen == 0 && fabs (jet1_eta_gen) <= 2.4) pt.push_back (jet1_pt_gen);
  if (Jet_multiplicity_gen == 0 && fabs (jet1_eta_gen) <= 2.4) pt.push_back (jet1_pt_gen);

  for (int i = 1; i <= Jet_multiplicity_gen; i++)
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

      if (i == 5)
	{
	  if (jet5_pt_gen > thresh && fabs (jet5_eta_gen) <= 2.4)
	    {
	      pt.push_back (jet5_pt_gen);
	    }
	}
      if (i == 6)
	{
	  if (jet6_pt_gen > thresh && fabs (jet6_eta_gen) <= 2.4)
	    {
	      pt.push_back (jet6_pt_gen);
	    }
	}
    }

// for


  if (whichjet <= pt.size ())
    jetPt = pt[whichjet - 1];
  //restituisci il pt (se valido) del get che ti chiede corrispondene all'oridne che chiedsi

  //if (jetPt != jet1_pt_gen) cout<<"jet multipl->"<<Jet_multiplicity_gen<<" jet1pt->"<<jet1_pt_gen<<" jet2pt->"<<jet2_pt_gen<<" jet3_pt->"<<jet3_pt_gen<<" jet4_pt->"<<jet4_
//      pt_gen<<" jet1eta->"<<jet1_eta_gen<<" jet2eta->"<<jet2_eta_gen<<" jet3_eta->"<<jet3_eta_gen<<" jet4_eta->"<<jet4_eta_gen<<" (return "<<jetPt<<")"<<endl;

  return jetPt;

}


void
Unfolding::LoopHt (int Nj)
{
  
  cout << endl;
  cout << "*********************************" << endl;
  cout << "Unfolding HT" << " with Nj equal to "<<Nj<<endl;
  cout << "*********************************" << endl;

#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif
  if (Nj == 1)
    {				//il caso Nj=0 è identico
      kminH = 10;
      kmaxH = 11;
      Nbins = 12;
      Nmin = 30;
      Nmax = 630;
    }
  if (Nj == 2)
    {				//il caso Nj=0 è identico
      kminH = 8;
      kmaxH = 9;
      Nbins = 12;
      Nmin = 60;
      Nmax = 630;
    }
  if (Nj == 3)
    {				//il caso Nj=0 è identico
      kminH = 7;
      kmaxH = 8;
      Nbins = 7;
      Nmin = 90;
      Nmax = 630;
    }
  if (Nj == 4)
    {				//il caso Nj=0 è identico
      kminH = 4;
      kmaxH = 5;
      Nbins = 5;
      Nmin = 120;
      Nmax = 630;
    }
	TH1D *HTrue = new TH1D ("HTrue", "H Truth", Nbins, Nmin, Nmax);
	TH1D *HData = new TH1D ("HData", "H DATA Measured", Nbins, Nmin, Nmax);
	TH2D *HMatx = new TH2D ("H hMatx", "Unfolding Matrix in # of jets + Z", Nbins, Nmin, Nmax,Nbins, Nmin, Nmax);
	TH2D *HMatxlong = new TH2D ("H hMatxlong", "Unfolding Matrix in # of jets + Z", Nbins+1, 0,Nmax, Nbins+1, 0, Nmax);
	TH1D *HMCreco = new TH1D ("H mcreco", "H mcreco", Nbins, Nmin, Nmax);
	TH1D *HMCrecoratio_ = new TH1D ("H mcrecoratio_", "H mcreco_", Nbins, Nmin, Nmax);
	TH1D *HData2 = new TH1D ("H data2", "H DATA Measured2", Nbins, Nmin, Nmax);
	TH1F *relativebkgH =  new TH1F ("relativebkgH", "relativebkg bin contribution", maxNJets - 0.5,0.5, maxNJets - 0.5);
	TH1F *vstatistics=new TH1F("vstatistics","vstatistics",Nbins, Nmin, Nmax);
	TH1F *staterror = new TH1F ("staterror", "staterror",Nbins, Nmin, Nmax);
	TH1F *staterrorsqrt = new TH1F ("staterrorsqrt", "staterrorsqrt",Nbins, Nmin, Nmax);
	TH1F *unfoerror = new TH1F ("unfoerror", "unfoerror",Nbins, Nmin, Nmax);
	TH1F *efficiencycorrections = new TH1F ("efficiencycorrections", "efficiencycorrections",60,0,3);	
	TH1F *efficiencycorrectionsmc = new TH1F ("efficiencycorrections", "efficiencycorrections",60,0,3);

  if (spanKvaluesH)
    {
      kminH = 1;
      kmaxH = maxNJets - 2;
    }

  bool Debug = false;		//decomment it to increase verbosity


  //////////////////////// VARIOUS CLOSURE TESTS ///////////////////
  bool indentityCheck=false;    //to perform identity check
  bool splitCheck=false;
  bool pythiaCheck=false;
  bool bayesianTest=true;
  //////////////////////////////////////////////////////////////////


  if (splitCheck) indentityCheck=true;
  if (pythiaCheck) indentityCheck=true;

  if (indentityCheck) {
    correctForEff=false;
    correctForBkg=false;
  }

 string sdatadir=sdata+":/validationJEC";
  if (isMu) sdatadir=sdata+":/EPTmuoReco";

  string smcdir=smc+":/EPTmuoReco_MC";   

  if (isMu) {
    smcdir=smc+":/EPTmuoReco_MC";
  }
  if (indentityCheck) sdatadir=smcdir;
  if (pythiaCheck) {
    smcdir=smc+":/EPTmuoReco_MC";  
    cout<<"Activate the pythia tests->"<<smcdir<<endl;
  }

  fA->cd (smcdir.c_str());
  gDirectory->ls("tree*");
 
  TTree *tree_fA;
  if (!isMu) tree_fA = (TTree *) gDirectory->Get ("treeValidationJEC_");
  if (isMu) tree_fA= (TTree *) gDirectory->Get ("treeValidationJECMu_");

  fB->cd (sdatadir.c_str());
  gDirectory->ls("tree*");
  TTree *tree_fB;
  if (!indentityCheck) tree_fB= (TTree *) gDirectory->Get ("treeValidationJEC_");
  //FOR closure tests
  if (indentityCheck){  
    fB->cd (smcdir.c_str());
    if (!isMu) tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");
    if (isMu) tree_fB= (TTree *) gDirectory->Get ("treeValidationJECMu_");
  }

  cout<<"#####################"<<endl;
  cout<<"You'are using"<<endl;
  cout<<sdatadir<<endl;
  cout<<smcdir<<endl;  
  cout<<"MC tree  is ->"<<tree_fA->GetName()<<endl;
  cout<<"Data tree is->"<<tree_fB->GetName()<<endl;  
  cout<<"#####################"<<endl;
  
  //Setting the errors
  HTrue->Sumw2 ();
  HMCreco->Sumw2 ();
  HMCrecoratio_->Sumw2 ();
  HData->Sumw2 ();

  int count = 0;

  //Second way to bulid the response matriz
  RooUnfoldResponse unfold_second(HMCreco,HTrue);
  unfold_second.UseOverflow();

  //Entro nei dati
  fChain = tree_fA;
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  cout<<"Dataset A has "<<nentries<<endl;

  if (splitCheck) {
    nentries=(int) 2.0*(nentries/3.);
    cout<<"Slitcheck is active, so Dataset A has now "<<nentries<<endl;
  }

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

   if (isElectron!=isEle) {
      cout<<"is_Electron(rootupla) is ->"<<isElectron<<", while the isElectron(unfolding) is "<<isEle<<" You are using the wrong TTree, ele instead of muons or viceversa..exit"<<endl;
      return;
    }

      double Ht, Ht_gen;
      double correctGenJetPt;
      int genJet;

      genJet = Jet_multiplicity_gen - getNumberOfValidGenJetsH (Jet_multiplicity_gen,30.0, jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet5_pt_gen,jet6_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen,jet5_eta_gen,jet6_eta_gen);

      for (int i = 1; i <= Jet_multiplicity_gen; i++)
	{
	  correctGenJetPt =getGenJetPtOfAGivenOrderH (Jet_multiplicity_gen, i, 30.0,
						      jet1_pt_gen, jet2_pt_gen, jet3_pt_gen,
						      jet4_pt_gen, jet5_pt_gen, jet6_pt_gen,
						      jet1_eta_gen, jet2_eta_gen,
						      jet3_eta_gen, jet4_eta_gen,
						      jet5_eta_gen, jet6_eta_gen);
	  
	  if (Debug) cout << "pT=" << correctGenJetPt << "N=" << genJet << "multi_gen="<< Jet_multiplicity_gen << endl;

	  if (correctGenJetPt > 0 && correctGenJetPt < 7000 && genJet >= Nj)
	    {
	      Ht_gen += correctGenJetPt;
	    }
	}			//!
      

      if (Jet_multiplicity >= Nj)
	{
	  if (jet1_pt > 0 && jet1_pt < 7000) Ht += jet1_pt;
	  if (jet2_pt > 0 && jet2_pt < 7000) Ht += jet2_pt;
	  if (jet3_pt > 0 && jet3_pt < 7000) Ht += jet3_pt;
	  if (jet4_pt > 0 && jet4_pt < 7000) Ht += jet4_pt;
	  if (jet5_pt > 0 && jet5_pt < 7000) Ht += jet5_pt;
	  if (jet6_pt > 0 && jet6_pt < 7000) Ht += jet6_pt;
	}

      //cout<<"Ht gen="<<Ht_gen<<"    "<<"Ht="<<Ht<<endl;

      double effcorrmc=1.0*evWeight;
      if (indentityCheck) effcorrmc=1.0; //Quando fai il closure test non vuoi correggere per i weights...
      double efferrmc=0.0;

      if (correctForEff)
	{
	  if (!useElectronsToCorrect)
	    {
	      std::vector < double >valuesdata = getEfficiencyCorrectionJetMultiplicity (fAeff, fBeff,Ht, "MC");
	      effcorrmc =effcorrmc* (1.00 / valuesdata[0]);
	      efferrmc = valuesdata[1] / pow (valuesdata[0], 2);

	      if (Jet_multiplicity >= Nj) HMCreco->Fill (Ht, effcorrmc);
	      if (genJet >= Nj) HTrue->Fill (Ht_gen, effcorrmc);
	      if (Jet_multiplicity >= Nj || genJet >= Nj) HMatx->Fill (Ht, Ht_gen, 1);
	      if (Jet_multiplicity >= Nj || genJet >= Nj) HMatxlong->Fill (Ht, Ht_gen, 1);
	    }
	  else
	    {
	      effcorrmc = 1.00 / getEfficiencyCorrectionPtUsingElectron (fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);
	      if (Jet_multiplicity >= Nj) HMCreco->Fill (Ht, effcorrmc);
	      if (genJet >= Nj) HTrue->Fill (Ht_gen);
	      if (Jet_multiplicity >= Nj || genJet >= Nj) HMatx->Fill (Ht, Ht_gen, 1);
	      if (Jet_multiplicity >= Nj || genJet >= Nj) HMatxlong->Fill (Ht, Ht_gen, 1);
	    }
	}
      else
	{
	  if (Jet_multiplicity >= Nj) HMCreco->Fill (Ht);
	  if (genJet >= Nj) HTrue->Fill (Ht_gen);
	  if (Jet_multiplicity >= Nj || genJet >= Nj) HMatx->Fill (Ht, Ht_gen, 1);
	  if (Jet_multiplicity >= Nj || genJet >= Nj) HMatxlong->Fill (Ht, Ht_gen, 1);
	}
      
      if (Jet_multiplicity >= Nj && genJet >= Nj) unfold_second.Fill(Ht, Ht_gen,effcorrmc);
      if (Jet_multiplicity >= Nj && !(genJet >= Nj)) unfold_second.Fake(Ht,effcorrmc);
      if (!(Jet_multiplicity >= Nj) && genJet >= Nj) unfold_second.Miss(Ht_gen);
      efficiencycorrectionsmc->Fill(effcorrmc); //Save the corrections that you applyed
      Ht = 0;
      Ht_gen = 0;
    }

  /////////////////////////
  //  Correct for background
  /////////////////////////

//  if (correctForBkg)
//    {
//
//    }

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

      double Ht;

      if (Jet_multiplicity >= Nj)
	{
	  if (jet1_pt > 0 && jet1_pt < 7000)
	    Ht += jet1_pt;
	  if (jet2_pt > 0 && jet2_pt < 7000)
	    Ht += jet2_pt;
	  if (jet3_pt > 0 && jet3_pt < 7000)
	    Ht += jet3_pt;
	  if (jet4_pt > 0 && jet4_pt < 7000)
	    Ht += jet4_pt;
	  if (jet5_pt > 0 && jet5_pt < 7000)
	    Ht += jet5_pt;
	  if (jet6_pt > 0 && jet6_pt < 7000)
	    Ht += jet6_pt;
	}

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
	      if (Jet_multiplicity >= Nj)
		HData->Fill (Ht, effcorrdata);
	      if (Jet_multiplicity >= Nj)
		HData2->Fill (Ht, effcorrdata);
	    }
	  else
	    {
	      double effcorrdata =
		1.00 / getEfficiencyCorrectionPtUsingElectron (fAeff, fBeff,
							       e1_pt,
							       e1_eta,
							       e2_pt,
							       e2_eta,
							       "Data",isEle);
	      efficiencycorrections->Fill(effcorrdata);
	      if (Jet_multiplicity >= Nj)
		HData->Fill (Ht, effcorrdata);
	      if (Jet_multiplicity >= Nj)
		HData2->Fill (Ht, effcorrdata);
	    }
	}
      else
	{
	  if (Jet_multiplicity >= Nj)
	    HData->Fill (Ht);
	  if (Jet_multiplicity >= Nj)
	    HData2->Fill (Ht);
	}
      Ht = 0;

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
      std::vector < double >bckcoeff2;

      if (Nj == 1) bckcoeff2 = getBackgroundContributions ("/gpfs/cms/data/2011/BackgroundEvaluation/Backgrounds_v2_28.root", "HT1");
      if (Nj == 2) bckcoeff2 = getBackgroundContributions ("/gpfs/cms/data/2011/BackgroundEvaluation/Backgrounds_v2_28.root", "HT2");
      if (Nj == 3) bckcoeff2 = getBackgroundContributions ("/gpfs/cms/data/2011/BackgroundEvaluation/Backgrounds_v2_28.root", "HT3");
      if (Nj == 4) bckcoeff2 = getBackgroundContributions ("/gpfs/cms/data/2011/BackgroundEvaluation/Backgrounds_v2_28.root", "HT4");


      for (unsigned int k = 0; k < Nbins; k++)
	{
	  HData->SetBinContent (k + 1, HData->GetBinContent (k + 1) - bckcoeff2[k]);
	  HData2->SetBinContent (k + 1,HData2->GetBinContent (k + 1) - bckcoeff2[k]);
	  if (HData->GetBinContent (k + 1) > 0)
	    {
	      relativebkg->SetBinContent (k + 1,bckcoeff2[k] /HData->GetBinContent (k + 1));
	      cout << "Data:" << HData->GetBinContent (k + 1) << " bck:" <<bckcoeff2[k] << " (coefficient is " << bckcoeff2[k] <<"). Relative bin ratio is " << bckcoeff2[k] /HData->GetBinContent (k + 1) << endl;
	    }
	  else
	    {
	      relativebkg->SetBinContent (k + 1, 0);
	      cout << "Data:" << HData->GetBinContent (k +1) << " bck:" <<bckcoeff2[k] << " (coefficient is " << bckcoeff2[k] <<"). Relative bin ratio is 0" << endl;
	    }
	  cout << "after " << bckcoeff2[k] / HData->GetBinContent (k + 1) << endl;
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

  int k0=1;
  int k1=2;
  if (bayesianTest){
  k0=0;
  k1=1;    
  }
  stringstream num;
  stringstream numJ;
  numJ << Nj;
  //Repeating each algorithm
  for (int j = k0; j < k1; j++)
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
	  if (j == 0) myNumber=5;
	  num << myNumber;
	  string title = "Data unfolding " + method + " method with K=" + num.str ();
	  std::string title2 = "Ht distribution. " + title;
	  cout << title << endl;

	  if (method == "Bayesian")
	    {
	      //RooUnfoldBayes unfold_H (&response_H, HData, myNumber);
	      RooUnfoldBayes unfold_H (&unfold_second, HData, myNumber);
	      HReco = (TH1D *) unfold_H.Hreco ();
	      // Extract covariance matrix TMatrixD m= unfold_j.Ereco();
	      TVectorD vstat= unfold_H.ErecoV();
	      TVectorD vunfo= unfold_H.ErecoV(RooUnfold::kCovToy);
	      TVectorD vunfomat= unfold_H.ErecoV(RooUnfold::kCovariance);
	      TVectorD vunfodiag= unfold_H.ErecoV(RooUnfold::kErrors);	     
	    }
	  if (method == "Svd")
	    {
	      //RooUnfoldSvd unfold_H (&response_H, HData, myNumber);
	      RooUnfoldSvd unfold_H (&unfold_second, HData, myNumber);	// OR
	      HReco = (TH1D *) unfold_H.Hreco ();
	      // Extract covariance matrix TMatrixD m= unfold_j.Ereco();
	      TVectorD vstat= unfold_H.ErecoV();
	      TVectorD vunfo= unfold_H.ErecoV(RooUnfold::kCovToy);
	      TVectorD vunfomat= unfold_H.ErecoV(RooUnfold::kCovariance);
	      TVectorD vunfodiag= unfold_H.ErecoV(RooUnfold::kErrors);	
	      std::vector<double> err;
	      for (unsigned int k=0; k<HReco->GetNbinsX(); k++){
		HReco->SetBinError(k+1,sqrt(HReco->GetBinContent(k+1)) ); //CORREGGERE QUESTA FORZATURA... E' LEFFICIENZA CHE SPARA
		vstatistics->SetBinContent(k+1,sqrt(HData->GetBinContent(k+1)));
		staterror->SetBinContent(k+1,vstat[k]/HData->GetBinContent(k+1));
		staterrorsqrt->SetBinContent(k+1,sqrt(HData->GetBinContent(k+1))/HData->GetBinContent(k+1));
		unfoerror->SetBinContent(k+1,vunfo[k]/HData->GetBinContent(k+1));
		err.push_back(vunfo[k]);
	      } 
	      kcontainer.push_back(err);
	    }


	  if (differentialCrossSection)
	    {
	      HReco->Scale (1. / HReco->Integral ());
	      HTrue->Scale (1. / HTrue->Integral ());
	      HMCreco->Scale (1. / HMCreco->Integral ());
	      HData->Scale (1. / HData->Integral ());
	    }

	  //Save info to evaluate the unfolding uncertainties... Da fare a mano ogni volta cambiando il MC e vedendo la differenza nei dati... poi prendi i dati, e li trascrivi nella macro!
	  for (int c = 0; c < 6; c++)
	    {
	      cout << HReco->GetBinContent (c + 1) << endl;
	    }


	  //cmultip->cd ();
	  TCanvas *c = new TCanvas ("c", "c", 1000, 700);
	  c->cd ();
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
	  HReco->SetTitle("");
	  HReco->GetXaxis ()->SetTitle ("");
	  HReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/dH_{T}");
	  if (isMu) HReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/dH_{T}");
	  HReco->SetMarkerStyle (20);
	  HData->SetMarkerStyle (21);
	  HData->SetLineColor (kGreen);

	  HReco->SetMarkerStyle (20);
	  HReco->SetStats (0);
	  HMCreco->SetStats (0);
	  HData->SetStats (0);
	  HTrue->SetStats (0);

	  HReco->GetXaxis ()->SetTitle ("H_{T}");
	  HReco->GetXaxis ()->SetTitleSize (0.00);
	  HReco->GetYaxis ()->SetLabelSize (0.07);
	  HReco->GetXaxis ()->SetLabelSize (0.00);
	  HReco->GetYaxis ()->SetTitleSize (0.08);
	  HReco->GetYaxis ()->SetTitleOffset (0.62);
	  HReco->Draw ("EP");	//risultato dell'unfolding

	  HReco2= (TH1F*) HReco->Clone("HReco");
	  HReco2->SetName("HReco2");
      
	  HReco->SetLineColor (kRed);
	  HReco->SetLineWidth (2);
	  HMCreco->Draw ();
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
	  HTrue->Draw ("same");	/*same */
	  HMCreco->Draw ("same");	/*same */
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

	  TLatex *latexLabel = CMSPrel (4.890, "");	// make fancy label
	  latexLabel->Draw ("same");
	  pad1->Update ();

	  c->cd ();
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

	  HReco->GetYaxis ()->SetRangeUser (0.7, 1.3);
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

	  TF1 *f = new TF1 ("f", "1", 0, 1000);
	  f->SetLineWidth (1);
	  f->SetLineColor (kBlack);
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

	  gROOT->SetStyle ("Plain");

	  string title3 = s + "HT" + method + "_" + num.str ();
	  if (correctForEff)
	    title3 = s + "HT" + method + "_" + numJ.str () + "_effcorr.pdf";
	  else
	    title3 = s + "HT" + method + "_" + numJ.str () + ".pdf";

	  c->cd ();
	  //cmultip->cd ();

	  c /*multip */ ->Print (title3.c_str ());
	  num.str ("");
	  cout << "PDF file saved (maybe) on " << title3 << endl;

	}
    }

  if (makeSecondaryPlots){
  ///Background and K parameter

  TCanvas *rel =new TCanvas ("rel", "Background relative contribution, bin by bin", 1000, 700);
  rel->cd ();
  relativebkg->SetLineColor(kRed);
  relativebkg->GetXaxis()->SetTitle("Jet Eta Bin");
  relativebkg->Draw();
  string title4= s+"BakgroundContribution.pdf";
  rel->Print(title4.c_str());
  
  TCanvas *kparam =new TCanvas ("kparam", "errors as a function of the k param", 1000, 700);
  bool firstp=true;
  kparam->cd();     
  TLegend *legend_e = new TLegend (0.73494, 0.63, 0.931727, 0.83);
  legend_e->SetFillColor (0);
  legend_e->SetFillStyle (0);
  legend_e->SetBorderSize (0);
  
  for (int i=0; i<kcontainer.size(); i++){
    stringstream num;
    num<<i;
    std::vector<double> ki=kcontainer[i];
    TH1D *histo= new TH1D("histo","histo",Nbins, Nmin, Nmax);
    for (int ii=0; ii<ki.size();ii++){
      histo->SetBinContent(ii+1,ki[ii]);
      histo->SetLineWidth(2);
    }
    histo->SetLineColor(i+2);
    if (firstp) {
      histo->GetYaxis()->SetRangeUser(0,3000);
      histo->Draw();
      firstp=false;
      string stringa="k="+num.str();
      legend_e->AddEntry (histo,stringa.c_str(), "L");
    }
    else {
      histo->Draw("SAME");
      string stringa="k="+num.str();
      legend_e->AddEntry (histo,stringa.c_str(), "L");
    }   
    num.str("");
  }
  vstatistics->SetLineColor(kViolet);
  vstatistics->SetLineWidth(3);
  vstatistics->Draw("SAME");
  legend_e->AddEntry (vstatistics,"Stat errors", "L");
  legend_e->Draw("same");
  
  string title6= s+"Kparam.pdf";
  kparam->Print(title6.c_str()); 

  TCanvas *err = new TCanvas ("err", "err", 1000, 700);
  err->cd ();
  staterror->SetStats (0);
  staterror->GetXaxis()->SetTitle("Jet Pt bin");
  staterror->GetYaxis()->SetTitle("Relative error");
  staterror->GetYaxis()->SetRangeUser(0.,.50);
  staterror->Draw();
  staterrorsqrt->SetLineColor(kViolet);
  staterrorsqrt->Draw("SAME");
  unfoerror->SetLineColor(kRed);
  unfoerror->Draw("SAME");
  
  TLegend *legend_ef = new TLegend (0.23494, 0.696429, 0.431727, 0.895833);
  legend_ef->SetFillColor (0);
  legend_ef->SetFillStyle (0);
  legend_ef->SetBorderSize (0);
  legend_ef->AddEntry (staterror, "Statistical Errors", "L");
  legend_ef->AddEntry (unfoerror, "Unf. Errors with Toy", "L");
  legend_ef->AddEntry (staterrorsqrt, "Statistical Errors, sqrt of data", "L");
  legend_ef->Draw ("same");

  //Efficiency correction
  TCanvas *efficiency = new TCanvas ("efficiency", "efficiency", 1000, 700);
  efficiency->cd ();
  efficiencycorrectionsmc->SetStats (111111);
  efficiencycorrectionsmc->GetXaxis()->SetTitle("Coefficients");
  efficiencycorrectionsmc->GetYaxis()->SetTitle("#");
  efficiencycorrectionsmc->SetLineColor(kRed);
  efficiencycorrectionsmc->Draw();
  efficiencycorrections->SetLineColor(kBlack);
  efficiencycorrections->Draw("SAMES");
  
  TLegend *legend_eff = new TLegend (0.23494, 0.696429, 0.431727, 0.895833);
  legend_eff->SetFillColor (0);
  legend_eff->SetFillStyle (0);
  legend_eff->SetBorderSize (0);
  legend_eff->AddEntry (efficiencycorrectionsmc, "Montecarlo", "L");
  legend_eff->AddEntry (efficiencycorrections, "Data", "L");
  legend_eff->Draw ("same");

  TCanvas *N = new TCanvas ("Ht jet response matrix", "Ht jet response matrix", 1000,700);
  N->cd ();
  HMatx->SetStats (0);
  gPad->SetLogz(1);
  gPad->SetRightMargin(0.1);
  HMatx->SetTitle("");
  gStyle->SetOptStat (1111111);
  HMatx->GetXaxis ()->SetTitle ("Reconstructed Ht");
  HMatx->GetYaxis ()->SetTitle ("Generated Ht");
  gStyle->SetPalette (1);
  gStyle->SetPaintTextFormat ("5.3f");
  gStyle->SetNumberContours (999);
  HMatx->SetMarkerColor (kBlack);
  double entries = 1.000 / (double) HMatx->Integral ();
  HMatx->Scale (entries);
  HMatx->Draw ("COLZ,text");
  string title3 = s + "HT_" + numJ.str () + "_Matrix.pdf";
  N->Print(title3.c_str());
  }
  //Save the info


  if (saveFile){
    TFile* w = new TFile(filename.c_str(), "UPDATE");
    w->cd();

    if (Nj==1) {
     TH1F *HReco_leading= (TH1F*) HReco2->Clone("HReco2");
      HReco_leading->SetName("HReco_leading");
      HReco_leading->Write();
      //TH1F *jTrue_leading= (TH1F*) jTrue->Clone("jTrue");
      //jTrue_leading->Write();
    }
    if (Nj==2) {
      TH1F *HReco_subleading= (TH1F*) HReco2->Clone("HReco2");
      HReco_subleading->SetName("HReco_subleading");
      HReco_subleading->Write();
      //TH1F *jTrue_subleading= (TH1F*) jTrue->Clone("jTrue");
      //jTrue_subleading->Write();

    }
    if (Nj==3) {
      TH1F *HReco_subsubleading= (TH1F*) HReco2->Clone("HReco2");
      HReco_subsubleading->SetName("HReco_subsubleading");
      HReco_subsubleading->Write();
      //TH1F *jTrue_subsubleading= (TH1F*) jTrue->Clone("jTrue");
      //jTrue_subsubleading->Write();

    }
    if (Nj==4) {
      TH1F *HReco_subsubsubleading= (TH1F*) HReco2->Clone("HReco2");
      HReco_subsubsubleading->SetName("HReco_subsubsubleading");
      HReco_subsubsubleading->Write();
      //TH1F *jTrue_subsubsubleading= (TH1F*) jTrue->Clone("jTrue");
      //jTrue_subsubsubleading->Write();

    }

    w->Close();
  }  

}
