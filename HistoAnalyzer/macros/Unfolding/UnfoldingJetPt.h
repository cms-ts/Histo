/*Leading jet pt*/
double minPtPlot=30;
double maxPtPlot=330;
int divPlot=15;
int kmin=1;
int kmax=1;
bool spanKvalues=false;

TH1F *relativebkg = new TH1F("relativebkg", "relativebkg bin contribution",divPlot,0,divPlot);

void Unfolding::LoopJetPt (int numbOfJets)
{
  cout<<"*********************************"<<endl;
  cout<<"Unfolding Jet Pt"<<endl;
  cout<<"*********************************"<<endl;
  
#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  ///////////
  // Format the plots in thew proper way
  ///////////

  if (numbOfJets==1) {
    kmin=12;
    kmax=13;
  }

  if (numbOfJets==2){
    minPtPlot=30;
    maxPtPlot=330;
    divPlot=10;
    kmin=8;
    kmax=9;
  }

  if (numbOfJets==3){
    minPtPlot=30;
    maxPtPlot=190;
    divPlot=8;
    kmin=6;
    kmax=7;
  }

  if (numbOfJets==4){
    minPtPlot=30;
    maxPtPlot=100;
    divPlot=7;
    kmin=3;
    kmax=4;
  }

  if (spanKvalues){
    int kmin=1;
    int kmax=divPlot-1; 
  }
  

  TH1D *jTrue = new TH1D ("jTrue", "jetpT Truth",divPlot,minPtPlot,maxPtPlot);
  TH1D *jData = new TH1D ("jData", "jetpT DATA Measured",divPlot,minPtPlot,maxPtPlot);
  TH1D *jReco = new TH1D ("jReco", "jetpT Unfolded DATA",divPlot,minPtPlot,maxPtPlot);
  TH2D *jMatx = new TH2D ("jMatx", "Unfolding Matrix jetpT Rapidity ",divPlot,minPtPlot,maxPtPlot,divPlot,minPtPlot,maxPtPlot);
  TH1D *jMCreco = new TH1D ("jMCreco", "jetpT mcreco",divPlot,minPtPlot,maxPtPlot);
  TH1D *jData2 = new TH1D ("jData2", "jetpT DATA Measured2",divPlot,minPtPlot,maxPtPlot);
  TH1D *jRatio_ = new TH1D ("jRatio_", "jetpTRatio",divPlot,minPtPlot,maxPtPlot);
  
  //To compute errors
  TH1F *staterror = new TH1F ("staterror", "staterror",divPlot,0,divPlot);
  TH1F *staterrorsqrt = new TH1F ("staterrorsqrt", "staterrorsqrt",divPlot,0,divPlot);
  TH1F *unfoerror = new TH1F ("unfoerror", "unfoerror",divPlot,0,divPlot);
  TH1F *unfoerrormat = new TH1F ("unfoerrormat", "unfoerrormat",divPlot,0,divPlot);
  TH1F *unfoerrordiag = new TH1F ("unfoerrordiag", "unfoerrordiag",divPlot,0,divPlot);
  
  /////////////

  jReco->Sumw2();
  jReco->SetName("jReco"); // After unfolding, it changed the name...
  jData->Sumw2();
  jMCreco->Sumw2();
  jTrue->Sumw2();	
  
  string sdatadir=sdata+":/validationJEC";
  string smcdir=smc+":/validationJEC";
  
  //Enter the files
  fA->cd (smcdir.c_str());
  TTree *tree_fA = (TTree *) gDirectory->Get ("treeUN_");
  //DATA
  fB->cd (sdatadir.c_str());
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeUN_");

  //Setting the errors
  jTrue->Sumw2();
  jMCreco->Sumw2();
  jData->Sumw2();

  //Dummy way to have the total number of Z
  TH1F* obj;
  obj=(TH1F*)gDirectory->Get("h_invMass");
  int NZ=obj->GetEntries();

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;		/* Loop Montecarlo */
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

      //if (ientry>80000) continue;

      if (numbOfJets<=1){
	if((jet1_pt>0 && jet1_pt<7000) || (jet1_pt_gen>=15 && jet1_pt_gen<7000) ){   // Old working if((jet1_pt>=0 && jet1_pt<7000) || (jet1_pt_gen>0 && jet1_pt_gen<7000) ){
	  //Correct for efficiencies event per event
	  if (correctForEff){
	    if (!useElectronsToCorrect){
	      std::vector<double> valuesmc=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJets,jet1_pt,"MC");
	      double effcorrmc=1.00/valuesmc[0];	
	      double efferrmc=valuesmc[1]/pow(valuesmc[0],2);
	      jMatx->Fill (jet1_pt, jet1_pt_gen,effcorrmc);	  
	      jMCreco->Fill (jet1_pt,effcorrmc);
	    }
	    else{
	      double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e2_pt,e1_eta,e2_eta,"MC");
	      jMatx->Fill (jet1_pt, jet1_pt_gen,effcorrmc);	  
	      jMCreco->Fill (jet1_pt,effcorrmc);	      
	    }
	  }
	  else {
	    jMatx->Fill (jet1_pt, jet1_pt_gen);
	    jMCreco->Fill (jet1_pt);
	  }
	  jTrue->Fill (jet1_pt_gen);
	  supplabel="_jet1";
	}
      }

      if (numbOfJets==2){
	if((jet2_pt>0 && jet2_pt<7000) || (jet2_pt_gen>=15 && jet2_pt_gen<7000) ){
	  //Correct for efficiencies event per event
	  if (correctForEff){
	    std::vector<double> valuesmc=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJets,jet2_pt,"MC");
	    double effcorrmc=1.00/valuesmc[0];	
	    double efferrmc=valuesmc[1]/pow(valuesmc[0],2);
	    jMatx->Fill (jet2_pt, jet2_pt_gen,effcorrmc);	  
	    jMCreco->Fill (jet2_pt,effcorrmc);  
	  }
	  else {
	    jMatx->Fill (jet2_pt, jet2_pt_gen);
	    jMCreco->Fill (jet2_pt);
	  }
	  jTrue->Fill (jet2_pt_gen);
	}
	supplabel="_jet2";
      }

      if (numbOfJets==3){
	if((jet3_pt>0 && jet3_pt<7000) || (jet3_pt_gen>=15 && jet3_pt_gen<7000) ){
	  //Correct for efficiencies event per event
	  if (correctForEff){
	    std::vector<double> valuesmc=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJets,jet3_pt,"MC");
	    double effcorrmc=1.00/valuesmc[0];	
	    double efferrmc=valuesmc[1]/pow(valuesmc[0],2);
	    jMatx->Fill (jet3_pt, jet3_pt_gen,effcorrmc);	  
	    jMCreco->Fill (jet3_pt,effcorrmc);  
	  }
	  else {
	    jMatx->Fill (jet3_pt, jet3_pt_gen);
	    jMCreco->Fill (jet3_pt);
	  }
	  jTrue->Fill (jet3_pt_gen);
	}
	supplabel="_jet3";
      }

      if (numbOfJets==4){
	if((jet4_pt>0 && jet4_pt<7000) || (jet4_pt_gen>=15 && jet4_pt_gen<7000) ){
	  //Correct for efficiencies event per event
	  if (correctForEff){
	    std::vector<double> valuesmc=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJets,jet4_pt,"MC");
	    double effcorrmc=1.00/valuesmc[0];	
	    double efferrmc=valuesmc[1]/pow(valuesmc[0],2);
	    jMatx->Fill (jet4_pt, jet4_pt_gen,effcorrmc);	  
	    jMCreco->Fill (jet4_pt,effcorrmc);  
	  }
	  else {
	    jMatx->Fill (jet4_pt, jet4_pt_gen);
	    jMCreco->Fill (jet4_pt);
	  }
	  jTrue->Fill (jet4_pt_gen);
	}
	supplabel="_jet4";
      }
    }
  jTrue->Sumw2();
  jMCreco->Sumw2();
  

  fChain = tree_fB;		/* Loop Data */
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

      if (numbOfJets==1){      
	if( jet1_pt>jetPtthreshold && jet1_pt<7000 ){    // Old        if( jet1_pt>=0 && jet1_pt<7000 ){
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    if (!useElectronsToCorrect){
	      std::vector<double> valuesdata=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJets,jet1_pt,"Data");
	      double effcorrdata=1.00/valuesdata[0];	
	      double efferrdata=valuesdata[1]/pow(valuesdata[0],2);
	      jData->Fill (jet1_pt,effcorrdata);
	      jData2->Fill (jet1_pt,effcorrdata);
	    }
	    else{
	      double effcorrdata=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e2_pt,e1_eta,e2_eta,"Data");
	      jData->Fill (jet1_pt,effcorrdata);
	      jData2->Fill (jet1_pt,effcorrdata);	      
	    }
	  }
	  else {
	    jData->Fill (jet1_pt);
	    jData2->Fill (jet1_pt);
	  }
	}
      }

      if (numbOfJets==2){      
	if(jet2_pt>jetPtthreshold && jet2_pt<7000){
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    std::vector<double> valuesdata=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJets,jet2_pt,"Data");
	    double effcorrdata=1.00/valuesdata[0];	
	    double efferrdata=valuesdata[1]/pow(valuesdata[0],2);
	    jData->Fill (jet2_pt,effcorrdata);
	    jData2->Fill (jet2_pt,effcorrdata);
	  }
	  else {
	    jData->Fill (jet2_pt);
	    jData2->Fill (jet2_pt);
	  }
	}
      }

      if (numbOfJets==3){      
	if(jet3_pt>jetPtthreshold && jet3_pt<7000){
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    std::vector<double> valuesdata=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJets,jet3_pt,"Data");
	    double effcorrdata=1.00/valuesdata[0];	
	    double efferrdata=valuesdata[1]/pow(valuesdata[0],2);
	    jData->Fill (jet3_pt,effcorrdata);
	    jData2->Fill (jet3_pt,effcorrdata);
	  }
	  else {
	    jData->Fill (jet3_pt);
	    jData2->Fill (jet3_pt);
	  }
	}
      }

      if (numbOfJets==4){      
	if(jet4_pt>jetPtthreshold && jet4_pt<7000){
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    std::vector<double> valuesdata=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJets,jet4_pt,"Data");
	    double effcorrdata=1.00/valuesdata[0];	
	    double efferrdata=valuesdata[1]/pow(valuesdata[0],2);
	    jData->Fill (jet4_pt,effcorrdata);
	    jData2->Fill (jet4_pt,effcorrdata);
	  }
	  else {
	    jData->Fill (jet4_pt);
	    jData2->Fill (jet4_pt);
	  }
	}
      }
    }


  // SAVE AREA TO EVALUATE DIFFERENTIAL CROSS SECTIONS
  double scaleFactor=jData->GetEntries();
  double Zarea=jData->Integral();
  double ZMCarea=jMCreco->Integral();
  cout<<"#Z->"<<scaleFactor<<" area->"<<Zarea<<endl;
  
  //////////////
  // MC Normalization
  //////////////
  double ScaleMCData = ((double)jData->Integral()/(double)jMCreco->Integral());

  /*      
  /////////////////
  // Efficiency Correction
  /////////////////
      
  double areaRecoVsTruth=1.000;
  TH1F* DataCorr;
  TH1F* PTJetMultiplicityUnfolded;
  cout<<"jData area before "<<jData->Integral()<<endl;

  if (correctForEff && 2==3){
    for (unsigned int k=0; k<=divPlot; k++){
      // Retrieve efficiency correction and its error for data
      std::vector<double> valuesdata=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJets,(k*((maxPtPlot-minPtPlot)/divPlot)+minPtPlot),"Data");
      //NB: you did: y=1/a -> errors -> sigmay=sqrt(df/da^2 * sigmaa^2 ) -> sigmaa/a^2!

      double effcorrdata=1.00/valuesdata[0];
      double efferrdata=valuesdata[1]/pow(valuesdata[0],2);

      // Retrieve efficiency correction and its error for MC
      std::vector<double> valuesmc=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJets,(k*((maxPtPlot-minPtPlot)/divPlot)+minPtPlot),"MC");
      double effcorrmc=1.00/valuesmc[0];	
      double efferrmc=valuesmc[1]/pow(valuesmc[0],2);	  
      cout<<"efficieiency correction that you're applying are-> MC:"<<effcorrmc<<" data:"<<effcorrdata<<" (errors are MC:"<<efferrmc<<" and data:"<<efferrdata<<"). Those are percentage, multiplied by the bin content you get an error of (data): "<<efferrdata*jDat\a->GetBinContent(k+1);
      cout<<" -- convolution with data-> stat error:"<<jData->GetBinError(k+1);

      //Correct distributions for efficiency
      jMCreco->SetBinContent(k+1, jMCreco->GetBinContent(k+1)*(effcorrmc));
      jData->SetBinContent(k+1, jData->GetBinContent(k+1)*(effcorrdata));
      jData2->SetBinContent(k+1, jData2->GetBinContent(k+1)*(effcorrdata));	 

      //Now, consider the efficiency error and the normal one
      // a=efficiency, sigmaa=eff error, b=stat value, sigmab=stat err
      // f=a*b -> sigmaf=sqrt(b^2*sigmaa^2+a^2*sigmab^2)
      jData->SetBinError(k+1, sqrt( pow(jData->GetBinContent(k+1),2)*pow(efferrdata,2) + pow(effcorrdata,2)*pow(jData->GetBinError(k+1),2) ) );
      jData2->SetBinError(k+1, sqrt( pow(jData2->GetBinContent(k+1),2)*pow(efferrdata,2) + pow(effcorrdata,2)*pow(jData2->GetBinError(k+1),2) ) );
      jMCreco->SetBinError(k+1, sqrt( pow(jMCreco->GetBinContent(k+1),2)*pow(efferrdata,2) + pow(effcorrdata,2)*pow(jMCreco->GetBinError(k+1),2) ) );	  
      cout<<" -- convolution with eff-> final error:"<<jData->GetBinError(k+1)<<" (relative bin error %"<<100.0*jData->GetBinError(k+1)/jData->GetBinContent(k+1)<<")"<<endl;
    }
    jData->Scale(Zarea/jData->Integral());
    jData2->Scale(Zarea/jData2->Integral());
    jMCreco->Scale(ZMCarea/jMCreco->Integral());
    jTrue->Scale(ZMCarea/jTrue->Integral());
  }

  */


  /////////////////////////
  //  Correct for background
  /////////////////////////
  
  if (correctForBkg){
    std::vector<double> bckcoeff;
    if (numbOfJets==1) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT");
    if (numbOfJets==2) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT2");
    if (numbOfJets==3) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT3");
    if (numbOfJets==4) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT4");

    for (unsigned int k=0; k<divPlot; k++){
      jData->SetBinContent(k+1, jData->GetBinContent(k+1) - bckcoeff[k]*Zarea);
      jData2->SetBinContent(k+1, jData2->GetBinContent(k+1) - bckcoeff[k]*Zarea);	
      if (jData->GetBinContent(k+1)>0) {
	relativebkg->SetBinContent(k+1,bckcoeff[k]*Zarea/jData->GetBinContent(k+1));
	cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]*Zarea<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is "<<bckcoeff[k]*Zarea/jData->GetBinContent(k+1)<<endl;	
      }
      else {
	relativebkg->SetBinContent(k+1,0);
	cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]*Zarea<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is 0"<<endl;
      }
      cout<<"after "<<bckcoeff[k]*Zarea/jData->GetBinContent(k+1)<<endl;
    }
  }

  RooUnfoldResponse response_j(jMCreco, jTrue, jMatx); 
  response_j.UseOverflow();

  TH1F *vstatistics=new TH1F("vstatistics","vstatistics",divPlot,0,divPlot);
      
  for (int j=1; j<2; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=kmin; k< kmax; k++){
      int myNumber=k;
      stringstream num;
      if (myNumber>=divPlot) myNumber=divPlot-1;
      num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Jet pT diff xsec distribution. "+title;
      cout<<"ongoing:"<<title<<endl;
      
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_j(&response_j, jData, myNumber, 1000);
	jReco = (TH1D *) unfold_j.Hreco ();
	// Extract covariance matrix TMatrixD m= unfold_j.Ereco();
	TVectorD vstat= unfold_j.ErecoV();
	TVectorD vunfo= unfold_j.ErecoV(RooUnfold::kCovToy);
	TVectorD vunfomat= unfold_j.ErecoV(RooUnfold::kCovariance);
	TVectorD vunfodiag= unfold_j.ErecoV(RooUnfold::kErrors);
	
	for (unsigned int p=0;p<jData->GetNbinsX();p++){
	  cout<<vstat[p]<<" "<<vunfo[p]<<endl;
	  staterrorsqrt->SetBinContent(p+1,sqrt(jData->GetBinContent(p+1))/jData->GetBinContent(p+1));
	  vstatistics->SetBinContent(p+1,sqrt(jData->GetBinContent(p+1)));
	  staterror->SetBinContent(p+1,vstat[p]/jData->GetBinContent(p+1));
	  unfoerrormat->SetBinContent(p+1,vunfomat[p]/jData->GetBinContent(p+1));
	  unfoerror->SetBinContent(p+1,vunfo[p]/jData->GetBinContent(p+1));
	  unfoerrordiag->SetBinContent(p+1,vunfodiag[p]/jData->GetBinContent(p+1));
	  
	  //Returns vector of unfolding errors computed according to the withError flag:
	  //0: Errors are the square root of the bin content
	  //1: Errors from the diagonals of the covariance matrix given by the unfolding
	  //2: Errors from the covariance matrix given by the unfolding
	  //3: Errors from the covariance matrix from the variation of the results in toy MC tests
	  // enum ErrorTreatment { 	kNoError	
	  //kErrors	
	  //kCovariance	
	  //kCovToy	
	}
	
	/////////////////////
	/// Error treatment
	/////////////////////
	
	std::vector<double> err;
	for (unsigned int k=0; k<jData->GetNbinsX(); k++){
	  // Old hipothesis with giuseppe!! jReco->SetBinError(k+1,sqrt(pow(vstat[k],2) + sqrt(pow(vunfo[k],2)) )); // How we chose to treat the eerros.. quatradutre sum
	  jReco->SetBinError(k+1,vunfo[k] ); // Suggerita da andrea... conta il toy, quando e' simile a quello di partenza
	  //err.push_back(sqrt(pow(vstat[k],2) + sqrt(pow(vunfo[k],2))));
	  err.push_back(vunfo[k]);
	}
	kcontainer.push_back(err);
      }

      if (method=="Svd"){
	jReco->Sumw2();
	RooUnfoldSvd unfold_j (&response_j, jData, myNumber, 1000);	// OR
	jReco = (TH1D *) unfold_j.Hreco ();
	// Extract covariance matrix TMatrixD m= unfold_j.Ereco();
	TVectorD vstat= unfold_j.ErecoV();
	TVectorD vunfo= unfold_j.ErecoV(RooUnfold::kCovToy);
	TVectorD vunfomat= unfold_j.ErecoV(RooUnfold::kCovariance);
	TVectorD vunfodiag= unfold_j.ErecoV(RooUnfold::kErrors);
      
	for (unsigned int p=0;p<jData->GetNbinsX();p++){
	  cout<<vstat[p]<<" "<<vunfo[p]<<endl;
	  staterrorsqrt->SetBinContent(p+1,sqrt(jData->GetBinContent(p+1))/jData->GetBinContent(p+1));
	  vstatistics->SetBinContent(p+1,sqrt(jData->GetBinContent(p+1)));
	  staterror->SetBinContent(p+1,vstat[p]/jData->GetBinContent(p+1));
	  unfoerrormat->SetBinContent(p+1,vunfomat[p]/jData->GetBinContent(p+1));
	  unfoerror->SetBinContent(p+1,vunfo[p]/jData->GetBinContent(p+1));
	  unfoerrordiag->SetBinContent(p+1,vunfodiag[p]/jData->GetBinContent(p+1));
	
	  //Returns vector of unfolding errors computed according to the withError flag:
	  //0: Errors are the square root of the bin content
	  //1: Errors from the diagonals of the covariance matrix given by the unfolding
	  //2: Errors from the covariance matrix given by the unfolding
	  //3: Errors from the covariance matrix from the variation of the results in toy MC tests
	  // enum ErrorTreatment { 	kNoError	
	  //kErrors	
	  //kCovariance	
	  //kCovToy	
	}

	/////////////////////
	/// Error treatment
	/////////////////////
      
	std::vector<double> err;
	for (unsigned int k=0; k<jData->GetNbinsX(); k++){
	  // Old hipothesis with giuseppe!! jReco->SetBinError(k+1,sqrt(pow(vstat[k],2) + sqrt(pow(vunfo[k],2)) )); // How we chose to treat the eerros.. quatradutre sum
	  jReco->SetBinError(k+1,vunfo[k] ); // Suggerita da andrea... conta il toy, quando e' simile a quello di partenza
	  //err.push_back(sqrt(pow(vstat[k],2) + sqrt(pow(vunfo[k],2))));
	  err.push_back(vunfo[k]);
	}
	kcontainer.push_back(err);
      } 
        
      cout<<"area jReco:"<<jReco->Integral()<<" and MCreco "<<jMCreco->Integral()<<endl;
      cout<<"Zarea "<<Zarea<<endl;
      
      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1", 0, 0.2, 1, 1);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      string whichjet="";
      if (numbOfJets==1) whichjet="Leading "; 
      if (numbOfJets==2) whichjet="Second leading "; 
      if (numbOfJets==3) whichjet="Third leading "; 
      if (numbOfJets==4) whichjet="Fourth leading "; 
      title2=whichjet+"jet pT diff xsec distribution. "+title;
      jReco->SetTitle (title2.c_str());
      jReco->GetXaxis ()->SetTitle ("");
      jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d p_{T}");
      jReco->SetMarkerStyle (20);
      jData->SetMarkerStyle (21);
      jData->SetLineColor(kGreen);

      //Normalize the area, to fit data with MC!
      double area = (((double)jReco->Integral ()) / (double)jTrue->Integral ());
      //cout<<"area "<<area<<endl;
      //jMCreco->Scale(area);
      //jTrue->Scale  (area);
      

      if (differentialCrossSection){
	jReco->Scale(1./jReco->Integral());		
	jTrue->Scale(1./jTrue->Integral());
	jMCreco->Scale(1./jMCreco->Integral());
	jData->Scale(1./jData->Integral());
      }

      cout<<"area jReco:"<<jReco->Integral()<<" and MCreco "<<jMCreco->Integral()<<endl;
      
      jReco->SetMarkerStyle (20);
      jMCreco->SetStats(0);
      jData->SetStats(0);
      jTrue->SetStats(0);
      jReco->SetStats(0);
      jReco->GetXaxis()->SetTitle("jet pT [GeV/c]");
      jReco->SetLineColor (kBlack); 
      jReco->Draw("EP");	//risultato dell'unfolding

      jMCreco->SetLineColor (kBlue + 1);
      jMCreco->SetLineStyle (2);
      jMCreco->SetLineWidth (2); 
      jMCreco->Draw("HISTSAMES");
      jTrue->SetLineColor (kRed);
      jTrue->SetLineWidth (2);
      jTrue->Draw ("HISTSAME");
      jData->SetLineColor(kGreen+1);
      pad1->SetLogy (1);
      jData->SetMarkerStyle (4);
      jData->SetMarkerColor(kGreen+1);
      jData->SetStats(0);
      jData->Draw("EPSAME");
   
      pad1->SetBottomMargin (0.1);
      
      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (jReco, "Data Unfolded", "P20");
      legend_d->AddEntry (jTrue, "MC truth", "L");
      legend_d->AddEntry (jMCreco, "MC reco", "L");
      legend_d->AddEntry(jData,"Data Folded","P20");
      legend_d->Draw ("same");
 
      TLatex *latexLabel=CMSPrel(4.890,""); // make fancy label
      latexLabel->Draw("same");   
      pad1->Update();      
      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2", 0, 0, 1, 0.2);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      TH1F *jRecoClone= (TH1F*) jReco->Clone("jReco");
      jRecoClone->SetName("jRecoClone");      
      jRecoClone->SetStats(0);
      jRecoClone->GetXaxis ()->SetLabelSize (0.1);
      jRecoClone->GetYaxis ()->SetLabelSize (0.08);
      jRecoClone->Divide(jTrue);
      jRecoClone->SetMarkerStyle (6);
      jRecoClone->GetXaxis ()->SetLabelSize (0.06);
      jRecoClone->GetYaxis ()->SetLabelSize (0.06);
      jRecoClone->GetXaxis ()->SetTitleSize (0);
      jRecoClone->GetYaxis ()->SetTitleSize (0.06);
      jRecoClone->GetYaxis ()->SetTitleOffset (0.5);

      jRecoClone->GetYaxis ()->SetRangeUser (0.5, 1.5);
      jRecoClone->GetXaxis ()->SetRangeUser (0, 5);
      jRecoClone->GetYaxis ()->SetTitle ("Ratios");
      jRecoClone->GetXaxis ()->SetTitle("jet pT [GeV/c]");
      jRecoClone->SetMarkerStyle (20);
      jRecoClone->SetLineWidth (0);
      jRecoClone->SetTitle ("");
      double max=jRecoClone->GetMaximum();
      double min=jRecoClone->GetMinimum();
      jRecoClone->GetYaxis()->SetRangeUser(min,max);
      jRecoClone->Draw("ep");
      
      TH1F *jDataClone= (TH1F*) jReco->Clone("jReco");
      jDataClone->SetName("jDataClone"); 
      jDataClone->Divide(jData);
      jDataClone->SetLineStyle (2); 
      jDataClone->SetMarkerSize (0);       
      jDataClone->SetLineWidth (0.05);
      jDataClone->SetLineColor(kViolet);
      jDataClone->Draw ("E1HISTSAME");
      jDataClone->SetLineWidth (0.1);

      TF1 *f = new TF1("f","1",0,410);
      f->SetLineWidth(1);
      f->Draw("SAMES");

      TLegend *legend_w = new TLegend(0.197791, 0.736607, 0.394578, 0.9375);
      legend_w->SetFillColor (0);
      legend_w->SetFillStyle (0);
      legend_w->SetBorderSize (0);
      legend_w->AddEntry (jRecoClone, "Data unfolded / MC truth", "P20");
      //legend_w->AddEntry (jMCRecoClone, "MC reco / MC truth", "L");
      legend_w->AddEntry (jDataClone, "Data Unfolded / Data Folded", "L");
      legend_w->Draw ("same");
      //pad2->Update();
      string title3= s+"JETPTXSEC"+method+"_"+num.str()+supplabel+".png";
      //c->cd ();
      c->Print(title3.c_str());

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

      TLegend *legend_e = new TLegend (0.23494, 0.696429, 0.431727, 0.895833);
      legend_e->SetFillColor (0);
      legend_e->SetFillStyle (0);
      legend_e->SetBorderSize (0);
      legend_e->AddEntry (staterror, "Statistical Errors", "L");
      legend_e->AddEntry (unfoerror, "Unf. Errors with Toy", "L");
      legend_e->AddEntry (staterrorsqrt, "Statistical Errors, sqrt of data", "L");
      legend_e->Draw ("same");

      string title4= s+"JETPTerror"+method+"_"+num.str()+supplabel+".png";
      err->Print(title4.c_str());

      TCanvas *N =new TCanvas ("jet pT response matrix", "jet pT response matrix", 1000, 700);
      N->cd ();
      jMatx->SetStats (0);
      jMatx->GetZaxis()->SetRangeUser(0.002,1);
      jMatx->GetXaxis()->SetTitle("Reconstructed jet pT [GeV/c]");
      jMatx->GetYaxis()->SetTitle("Generated jet pT [GeV/c]");
      gStyle->SetPalette (1);
      gStyle->SetPaintTextFormat ("5.3f");
      gStyle->SetNumberContours (999);
      jMatx->SetMarkerColor (kBlack);
      double entries=1.000/(double)jMatx->Integral();
      jMatx->Scale(entries);
      jMatx->Draw ("COLZ,text");
      string title5= s+"JetPtUnfoMatrix"+method+"_"+num.str()+supplabel+".png";
      N->Print(title5.c_str());      

      for (unsigned int p=0;p<staterror->GetNbinsX();p++){
	staterror->SetBinContent(p+1,0);	  
	unfoerror->SetBinContent(p+1,0);
	staterrorsqrt->SetBinContent(p+1,0);
      }

      num.str("");
      //delete staterror;
      //delete unfoerror;
      //delete unfoerrormat;
 
      //Bring the scale back again to unfold properly...

      if (differentialCrossSection && !cold){
	jReco->Scale(ZMCarea);		
	jTrue->Scale(Zarea);
	jMCreco->Scale(ZMCarea);
	jData->Scale(Zarea);
      }      
    }
  }
  
  if (cold){
    cold=false;
  }
  
  TCanvas *rel =new TCanvas ("rel", "Background relative contribution, bin by bin", 1000, 700);
  rel->cd ();
  relativebkg->SetLineColor(kRed);
  relativebkg->GetXaxis()->SetTitle("Jet Pt Bin");
  relativebkg->Draw();
  string title4= s+"BakgroundContribution.png";
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
    TH1D *histo= new TH1D("histo","histo",divPlot,0,divPlot);
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
  
  string title6= s+"Kparam.png";
  kparam->Print(title6.c_str()); 
      
  ///////////
  ///SAve unfolded distribution
  /////////// 
  
  if (saveFile){
    TFile* w = new TFile(filename.c_str(), "UPDATE");
    w->cd();

    if (numbOfJets==1) {
      TH1F *jReco_leading= (TH1F*) jReco->Clone("jReco");
      jReco_leading->SetName("jReco_leading");
      jReco_leading->Write();
    }
    if (numbOfJets==2) {
      TH1F *jReco_subleading= (TH1F*) jReco->Clone("jReco");
      jReco_subleading->SetName("jReco_subleading");
      jReco_subleading->Write();
    }
    if (numbOfJets==3) {
      TH1F *jReco_subsubleading= (TH1F*) jReco->Clone("jReco");
      jReco_subsubleading->SetName("jReco_subsubleading");
      jReco_subsubleading->Write();
    }
    if (numbOfJets==4) {
      TH1F *jReco_subsubsubleading= (TH1F*) jReco->Clone("jReco");
      jReco_subsubsubleading->SetName("jReco_subsubsubleading");
      jReco_subsubsubleading->Write();
    }

    w->Close();
  }  
}
