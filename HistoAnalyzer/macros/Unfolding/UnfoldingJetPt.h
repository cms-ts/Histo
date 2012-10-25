#include <vector>
#include <iostream>
#include <algorithm>

/*Leading jet pt*/
double minPtPlot=30;
double maxPtPlot=330;
int divPlot=15;
int kmin=1;
int kmax=1;
bool spanKvalues=true;
bool Unfold=true;
bool UnfoldDistributionsPt=true;

TCanvas cc;

TH1F *relativebkg = new TH1F("relativebkg", "relativebkg bin contribution",divPlot,0,divPlot);
TH1F *efficiencycorrections = new TH1F ("efficiencycorrections", "efficiencycorrections",60,0,3);	
TH1F *efficiencycorrectionsmc = new TH1F ("efficiencycorrections", "efficiencycorrections",60,0,3);

int getNumberOfValidGenJetsPt(int Jet_multiplicity_gen, double thresh, double jet1_pt_gen, double jet2_pt_gen, double jet3_pt_gen, double jet4_pt_gen, double jet1_eta_gen, double jet2_eta_gen, double jet3_eta_gen, double jet4_eta_gen){
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
  }// for
  return counter;
}// end

bool myfunction (int i,int j) { return (i>j); }

double getGenJetPtOfAGivenOrder(int Jet_multiplicity_gen, int whichjet, double thresh, double jet1_pt_gen, double jet2_pt_gen, double jet3_pt_gen, double jet4_pt_gen, double jet1_eta_gen, double jet2_eta_gen, double jet3_eta_gen, double jet4_eta_gen){

  double jetPt=0.0;
  //Stabilisci chi e' il piu' grande e l'ordine in pt, togliendo jet fuori l'accettanza o a pt sotto treshold
  //cout<<"jet multipl->"<<Jet_multiplicity_gen<<" jet1pt->"<<jet1_pt_gen<<" jet2pt->"<<jet2_pt_gen<<" jet3_pt->"<<jet3_pt_gen<<" jet4_pt->"<<jet4_pt_gen<<" jet1eta->"<<jet1_eta_gen<<" jet2eta->"<<jet2_eta_gen<<" jet3_eta->"<<jet3_eta_gen<<" jet4_eta->"<<jet4_eta_gen<<endl;

    if (Jet_multiplicity_gen==0 && jet1_pt_gen<thresh) return 0;

  //Immagazzino le info di pt e eta in un vettore di vettori
  std::vector<double> pt;

  if (Jet_multiplicity_gen==0 && fabs(jet1_eta_gen)<=2.4) pt.push_back(jet1_pt_gen);  
   
  for (int i=1;i<=4; i++){
    if (i==1){
      if (jet1_pt_gen>thresh && fabs(jet1_eta_gen)<=2.4 ) {
	pt.push_back(jet1_pt_gen);
      }
    } 
    if (i==2){
      if (jet2_pt_gen>thresh && fabs(jet2_eta_gen)<=2.4 ) {
	pt.push_back(jet2_pt_gen);
      }
    } 
    if (i==3){
      if (jet3_pt_gen>thresh && fabs(jet3_eta_gen)<=2.4 ) {
	pt.push_back(jet3_pt_gen);
      }
    } 
    if (i==4){
      if (jet4_pt_gen>thresh && fabs(jet4_eta_gen)<=2.4 ) {
	pt.push_back(jet4_pt_gen);
      }
    } 
  }// for
  
  if (pt.size()>0) sort( pt.begin(), pt.end(), myfunction);
  for(int i=0;i<pt.size();i++){
    //cout<<pt[i]<<endl;
  }

  if (whichjet<=pt.size()) jetPt=pt[whichjet-1];
  //restituisci il pt (se valido) del get che ti chiede corrispondene all'oridne che chiedsi

  //if (jetPt != jet1_pt_gen) cout<<"jet multipl->"<<Jet_multiplicity_gen<<" jet1pt->"<<jet1_pt_gen<<" jet2pt->"<<jet2_pt_gen<<" jet3_pt->"<<jet3_pt_gen<<" jet4_pt->"<<jet4_pt_gen<<" jet1eta->"<<jet1_eta_gen<<" jet2eta->"<<jet2_eta_gen<<" jet3_eta->"<<jet3_eta_gen<<" jet4_eta->"<<jet4_eta_gen<<" (return "<<jetPt<<")"<<endl;
  
  return jetPt;
}

void Unfolding::LoopJetPt (int numbOfJetsSelected)
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

  if (numbOfJetsSelected==1) {
    kmin=11;
    kmax=12;
  }

  if (numbOfJetsSelected==2){
    minPtPlot=30;
    maxPtPlot=330;
    divPlot=10;
    kmin=8;
    kmax=9;
  }

  if (numbOfJetsSelected==3){
    minPtPlot=30;
    maxPtPlot=190;
    divPlot=8;
    kmin=6;
    kmax=7;
  }

  if (numbOfJetsSelected==4){
    minPtPlot=30;
    maxPtPlot=100;
    divPlot=7;
    kmin=3;
    kmax=4;
  }

  if (spanKvalues){
    int kmin=2;
    int kmax=divPlot; 
  }
  

  TH1D *jTrue = new TH1D ("jTrue", "jetpT Truth",divPlot,minPtPlot,maxPtPlot);
  TH1D *jTruepythia = new TH1D ("jTruepythia", "jetpT Truth with pythia",divPlot,minPtPlot,maxPtPlot);
  TH1D *jData = new TH1D ("jData", "jetpT DATA Measured",divPlot,minPtPlot,maxPtPlot);
  TH1F *jReco = new TH1F ("jReco", "jetpT Unfolded DATA",divPlot,minPtPlot,maxPtPlot);
  TH2D *jMatx = new TH2D ("jMatx", "Unfolding Matrix jetpT Rapidity ",divPlot,minPtPlot,maxPtPlot,divPlot,minPtPlot,maxPtPlot);
  TH2D *jCorr = new TH2D ("jCorr", "Unfolding Matrix jetpT Rapidity ",4,0,4,4,0,4);

  TH2D *jMatxlong = new TH2D ("jMatxlong", "Unfolding Matrix jetpT Rapidity ",divPlot+2,minPtPlot-40,maxPtPlot,divPlot+2,minPtPlot-40,maxPtPlot);
  TH2D *jMatxpythia = new TH2D ("jMatxpythia", "Unfolding Matrix jetpT Rapidity using pythia",divPlot+1,minPtPlot-30,maxPtPlot,divPlot+1,minPtPlot-30,maxPtPlot);
  TH1D *jMCreco = new TH1D ("jMCreco", "jetpT mcreco",divPlot,minPtPlot,maxPtPlot);
  TH1D *jData2 = new TH1D ("jData2", "jetpT DATA Measured2",divPlot,minPtPlot,maxPtPlot);
  TH1D *jRatio_ = new TH1D ("jRatio_", "jetpTRatio",divPlot,minPtPlot,maxPtPlot);

  TH1D *NData = new TH1D ("NData", "N DATA Measured", maxNJets-0.5, 0.5, maxNJets-0.5);
  TH1D *NMCreco = new TH1D ("N mcreco", "N mcreco", maxNJets-0.5, 0.5, maxNJets-0.5);
  TH1D *NTrue = new TH1D ("NTrue", "N Truth", maxNJets-0.5, 0.5, maxNJets-0.5);

  // Efficinency tests
  TProfile *effAndrea = new TProfile ("effAndrea", "efficiency as a function of the leading jet pt",divPlot,minPtPlot,maxPtPlot);
  TProfile *effAnne = new TProfile ("effAnne", "efficiency as a function of the leading jet pt",divPlot,minPtPlot,maxPtPlot);
  effAndrea->Sumw2();
  effAnne->Sumw2();  
  
  //To compute errors
  TH1F *staterror = new TH1F ("staterror", "staterror",divPlot,0,divPlot);
  TH1F *staterrorsqrt = new TH1F ("staterrorsqrt", "staterrorsqrt",divPlot,0,divPlot);
  TH1F *unfoerror = new TH1F ("unfoerror", "unfoerror",divPlot,0,divPlot);
  TH1F *unfoerrormat = new TH1F ("unfoerrormat", "unfoerrormat",divPlot,0,divPlot);
  TH1F *unfoerrordiag = new TH1F ("unfoerrordiag", "unfoerrordiag",divPlot,0,divPlot);
  
  /////////////

  //////////////////////// VARIOUS CLOSURE TESTS ///////////////////
  bool identityCheck=false;    //to perform identity check
  bool splitCheck=false;
  bool pythiaCheck=false;
  bool bayesianTests=false;
  //////////////////////////////////////////////////////////////////

  if (splitCheck) identityCheck=true;
  if (pythiaCheck) identityCheck=true;
  
  if (identityCheck) {
    correctForEff=false;
    correctForBkg=false;
  }
  
  jReco->Sumw2();
  jReco->SetName("jReco"); // After unfolding, it changed the name...
  jData->Sumw2();
  jMCreco->Sumw2();
  jTrue->Sumw2();	

  RooUnfoldResponse unfold_jBayespythia(jMCreco,jTrue);
  unfold_jBayespythia.UseOverflow();

  if (pythiaCheck){
    //fill the matrix --->
    fPythia = new TFile (smcpythia.c_str());
    string pythiaold=smcpythia;
    smcpythia=smcpythia+":/EPTmuoReco_MC";
    cout<<"-------------------------------------- Pythia check! -------------------"<<endl;
    cout<<smcpythia<<endl;
    fPythia->cd (smcpythia.c_str());
    gDirectory->ls("tree*");
    TTree *tree_fC= (TTree *) gDirectory->Get ("treeValidationJEC_");
    if (isMu) tree_fC= (TTree *) gDirectory->Get ("treeValidationJECMu_");

    //Filling the other response Matrix
    fChain = tree_fC;
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
      //do the analysis, basically
      //if (ientry>80000) continue;
      double thresh=30.0;
      
      if (isElectron!=isEle) {
	cout<<"is_Electron(rootupla) is ->"<<isElectron<<", while the isElectron(unfolding) is "<<isEle<<" You are using the wrong TTree, ele instead of muons or viceversa..exit"<<endl;
	return;
      }
      
      // To control and exclude jets having energy below "thresh"
      int offsetJetMultiplicity=0;
      offsetJetMultiplicity=getNumberOfValidGenJetsPt(Jet_multiplicity_gen,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen);
      
      //Case that were Z+0 Jets and not properly addressed!
      if ((offsetJetMultiplicity-Jet_multiplicity_gen)==0 && Jet_multiplicity==0) {
        continue;
      }

        double correctGenJetPt=getGenJetPtOfAGivenOrder(Jet_multiplicity_gen,numbOfJetsSelected,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen);
	
        //correctGenJetPt=jet1_pt_gen;
        if(numbOfJetsSelected==1 && ((jet1_pt>0 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) || (correctGenJetPt>0 && correctGenJetPt<7000))){
	  jMatxpythia->Fill(jet1_pt, correctGenJetPt,evWeightSherpa);	 
	  jTruepythia->Fill (correctGenJetPt,evWeightSherpa);
	  if ((jet1_pt>0 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Fill(jet1_pt, correctGenJetPt,evWeightSherpa);
	  if ((jet1_pt>0 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) && !(correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Fake(jet1_pt,evWeightSherpa);
	  if (!(jet1_pt>0 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Miss(correctGenJetPt,evWeightSherpa);
	}
	
        if(numbOfJetsSelected==2 && ((jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) || (correctGenJetPt>0 && correctGenJetPt<7000))){
	  jMatxpythia->Fill(jet2_pt, correctGenJetPt);	 
	  jTruepythia->Fill (correctGenJetPt);
	  if ((jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Fill(jet2_pt, correctGenJetPt);
	  if ((jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) && !(correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Fake(jet2_pt);
	  if (!(jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Miss(correctGenJetPt);
	}
        if(numbOfJetsSelected==3 && ((jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) || (correctGenJetPt>0 && correctGenJetPt<7000))){
	  jMatxpythia->Fill(jet3_pt, correctGenJetPt);
	  jTruepythia->Fill (correctGenJetPt);
	  if ((jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Fill(jet3_pt, correctGenJetPt);
	  if ((jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) && !(correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Fake(jet3_pt);
	  if (!(jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Miss(correctGenJetPt);
	}
	
        if(numbOfJetsSelected==4 && ((jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) || (correctGenJetPt>0 && correctGenJetPt<7000))){
	  jMatxpythia->Fill(jet4_pt, correctGenJetPt);	 
	  jTruepythia->Fill (correctGenJetPt);
	  if ((jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Fill(jet4_pt, correctGenJetPt);
	  if ((jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) && !(correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Fake(jet4_pt);
	  if (!(jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayespythia.Miss(correctGenJetPt);
	}
    }
    smcpythia=pythiaold;
  }

  string sdatadir=sdata+":/validationJEC";
  if (isMu) sdatadir=sdata+":/EPTmuoReco";

  //string smcdir=smc+":/validationJEC";
  string smcdir=smc+":/EPTmuoReco_MC";  
  if (isMu) {
    smcdir=smc+":/EPTmuoReco_MC";
  }
  if (identityCheck) {
    sdatadir=smcdir;
    //correctForEff=false;
    //correctForBkg=false;
  }

  fA->cd (smcdir.c_str());
  gDirectory->ls("tree*");
  TTree *tree_fA= (TTree *) gDirectory->Get ("treeValidationJEC_");
  if (isMu) tree_fA= (TTree *) gDirectory->Get ("treeValidationJECMu_");

  fB->cd (sdatadir.c_str());
  gDirectory->ls("tree*");
  TTree *tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");
  //FOR closure tests
  if (identityCheck){  
    fB->cd (smcdir.c_str());
    tree_fB = (TTree *) gDirectory->Get ("treeValidationJEC_");
    if (isMu) tree_fB= (TTree *) gDirectory->Get ("treeValidationJECMu_");
  }
  
  RooUnfoldResponse unfold_jBayes(jMCreco,jTrue);
  unfold_jBayes.UseOverflow();
  RooUnfoldResponse unfold_second(NMCreco,NTrue);
  unfold_second.UseOverflow();
 
  cout<<"#####################"<<endl;
  cout<<"You'are using"<<endl;
  cout<<sdatadir<<endl;
  cout<<smcdir<<endl;  
  cout<<"MC tree  is ->"<<tree_fA->GetName()<<endl;
  cout<<"Data tree is->"<<tree_fB->GetName()<<endl;  
  cout<<"#####################"<<endl;

  //Setting the errors
  jTrue->Sumw2();
  jMCreco->Sumw2();
  jData->Sumw2();

  int categoryCounter=0;
  double fillCounter=0;
  double missCounter=0;
  double fakeCounter=0;

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;		/* Loop Montecarlo */
  Init (fChain);
  
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  int counter3=0;

  if (splitCheck) {
    nentries=(int) 2.0*(nentries/3.);
    cout<<"Slitcheck is active, so Dataset A has now "<<nentries<<endl;
  }

  if (fChain == 0)
    return;
  int counter=0;  
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;

      if (Jet_multiplicity > 30 || Jet_multiplicity_gen > 30 ) continue;

   if (isElectron!=isEle) {
      cout<<"is_Electron(rootupla) is ->"<<isElectron<<", while the isElectron(unfolding) is "<<isEle<<" You are using the wrong TTree, ele instead of muons or viceversa..exit"<<endl;
      return;
    }

   //if (ientry>10) continue;
      double thresh=30.0;
      double realGenJetMultiplicity=getNumberOfValidGenJets(thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet5_pt_gen,jet6_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen,jet5_eta_gen,jet6_eta_gen);
      
      // To control and exclude jets having energy below "thresh"
      int offsetJetMultiplicity=0;
      offsetJetMultiplicity=getNumberOfValidGenJetsPt(Jet_multiplicity_gen,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen);
      
      //Case that were Z+0 Jets and not properly addressed!
      if ((offsetJetMultiplicity-Jet_multiplicity_gen)==0 && Jet_multiplicity==0) {
	counter++;
	//continue;
      }

      categoryCounter++;

      double effcorrmc=1.0;
      if (!identityCheck) effcorrmc = 1.0 * evWeight; 
      if (numbOfJetsSelected<=1){
	double correctGenJetPt=getGenJetPtOfAGivenOrder(realGenJetMultiplicity,1,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen);
	effcorrmc=effcorrmc*1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);
	
	if ((Jet_multiplicity >= 1 ||  (realGenJetMultiplicity) >=1) && offsetJetMultiplicity==0){
	  counter3++;
	  //Correct for efficiencies event per event
	  if (correctForEff){
	    if (!useElectronsToCorrect){
	      std::vector<double> valuesmc=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJetsSelected,jet1_pt,"MC");
	      effcorrmc=effcorrmc*1.00/valuesmc[0];	
	      double efferrmc=valuesmc[1]/pow(valuesmc[0],2);
	      jMatx->Fill (jet1_pt, correctGenJetPt,effcorrmc);	
	      jMCreco->Fill (jet1_pt,effcorrmc);
	    }
	    else{
	      //effcorrmc=effcorrmc*1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);
	      efficiencycorrectionsmc->Fill(effcorrmc);
	      jMatx->Fill (jet1_pt, correctGenJetPt,effcorrmc);	 
	      jMCreco->Fill (jet1_pt,effcorrmc);
	    }
	  }
	  else {
	    jMatx->Fill (jet1_pt, correctGenJetPt);
	    jMCreco->Fill (jet1_pt);
	  }
	  jTrue->Fill (correctGenJetPt);
	  supplabel="_jet1";

	  // Questa e' quando c'e' tutto
	  if ((Jet_multiplicity>=1) && (correctGenJetPt>0 && correctGenJetPt<7000)) {
	    unfold_jBayes.Fill(jet1_pt, correctGenJetPt,effcorrmc);
	    fillCounter+=effcorrmc;
	    unfold_second.Fill(Jet_multiplicity, realGenJetMultiplicity,effcorrmc);
	  }
	  if (Jet_multiplicity>=1 && !(correctGenJetPt>0 && correctGenJetPt<7000)) {
	    unfold_jBayes.Fake(jet1_pt,effcorrmc);
	    fakeCounter+=1*effcorrmc;
	    unfold_second.Fake(Jet_multiplicity,effcorrmc);
	  }
	  //Questa e' facili, c'era e non l'ho visto
	  if (!(Jet_multiplicity>=1) && (correctGenJetPt>0 && correctGenJetPt<7000)){
	    unfold_jBayes.Miss(correctGenJetPt);
	    missCounter+=1*effcorrmc;
	    unfold_second.Miss(realGenJetMultiplicity);
	  }
	}
	else{
	  counter3++;
	  //if (Jet_multiplicity == 0 && ( (realGenJetMultiplicity) ==0)) unfold_jBayes.Fill(jet1_pt,correctGenJetPt,effcorrmc); //zeri

	  if (!(correctGenJetPt>0) && Jet_multiplicity>=1){
	    unfold_jBayes.Fake(jet1_pt,effcorrmc);
	    fakeCounter+=effcorrmc;
	    unfold_second.Fake(Jet_multiplicity,effcorrmc);
	  }
	  if (correctGenJetPt>0 && Jet_multiplicity==0){
		unfold_jBayes.Miss(correctGenJetPt);
		missCounter+=1*effcorrmc;
		unfold_second.Miss(realGenJetMultiplicity);
	  }
	  if (correctGenJetPt>0 && Jet_multiplicity>0){
	    fillCounter+=effcorrmc;
	    unfold_jBayes.Fill(jet1_pt,correctGenJetPt,effcorrmc);
	    unfold_second.Fill(Jet_multiplicity, realGenJetMultiplicity,effcorrmc);
	  }
	}
	jMatxlong->Fill (jet1_pt, correctGenJetPt,effcorrmc);	 
      }
      
      if (numbOfJetsSelected==2){
	double correctGenJetPt=getGenJetPtOfAGivenOrder(Jet_multiplicity_gen,numbOfJetsSelected,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen);
        if((jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) || (correctGenJetPt>0 && correctGenJetPt<7000)){ 
	  //Correct for efficiencies event per event
	  if (correctForEff){
	    if (!useElectronsToCorrect){
	      std::vector<double> valuesmc=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJetsSelected,jet2_pt,"MC");
	      double effcorrmc=1.00/valuesmc[0];	
	      double efferrmc=valuesmc[1]/pow(valuesmc[0],2);
	      jMatx->Fill (jet2_pt, correctGenJetPt,effcorrmc);	  
	      jMCreco->Fill (jet2_pt,effcorrmc);  
	    }
	    else{
	      double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);
	      jMatx->Fill (jet2_pt, correctGenJetPt,effcorrmc);	  
	      jMCreco->Fill (jet2_pt,effcorrmc);	      
	    }
	  }
	  else {
	    jMatx->Fill (jet2_pt, correctGenJetPt);
	    jMCreco->Fill (jet2_pt);
	  }
	  jTrue->Fill (correctGenJetPt);
	}
	supplabel="_jet2";
	if ((jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayes.Fill(jet2_pt, correctGenJetPt);
	if ((jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) && !(correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayes.Fake(jet2_pt);
	if (!(jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayes.Miss(correctGenJetPt);

      }

      if (numbOfJetsSelected==3){
        double correctGenJetPt=getGenJetPtOfAGivenOrder(Jet_multiplicity_gen,numbOfJetsSelected,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen);
        if((jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) || (correctGenJetPt>0 && correctGenJetPt<7000)){
	  //Correct for efficiencies event per event
	  if (correctForEff){
	    if (!useElectronsToCorrect){
	      std::vector<double> valuesmc=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJetsSelected,jet3_pt,"MC");
	      double effcorrmc=1.00/valuesmc[0];	
	      double efferrmc=valuesmc[1]/pow(valuesmc[0],2);
	      jMatx->Fill (jet3_pt, correctGenJetPt,effcorrmc);	  
	      jMCreco->Fill (jet3_pt,effcorrmc);  
	    }
	    else{
	      double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);
	      jMatx->Fill (jet3_pt, correctGenJetPt,effcorrmc);	  
	      jMCreco->Fill (jet3_pt,effcorrmc);
	    }
	  }
	  else {
	    jMatx->Fill (jet3_pt, correctGenJetPt);
	    jMCreco->Fill (jet3_pt);
	  }
	  jTrue->Fill (correctGenJetPt);
	}
	supplabel="_jet3";
	if ((jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayes.Fill(jet3_pt, correctGenJetPt);
	if ((jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) && !(correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayes.Fake(jet3_pt);
	if (!(jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayes.Miss(correctGenJetPt);

      }

      if (numbOfJetsSelected==4){
        double correctGenJetPt=getGenJetPtOfAGivenOrder(Jet_multiplicity_gen,numbOfJetsSelected,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen);
        if((jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) || (correctGenJetPt>0 && correctGenJetPt<7000)){
	  //Correct for efficiencies event per event
	  if (correctForEff){
	    if (!useElectronsToCorrect){
	      std::vector<double> valuesmc=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJetsSelected,jet4_pt,"MC");
	      double effcorrmc=1.00/valuesmc[0];	
	      double efferrmc=valuesmc[1]/pow(valuesmc[0],2);
	      jMatx->Fill (jet4_pt, correctGenJetPt,effcorrmc);	  
	      jMCreco->Fill (jet4_pt,effcorrmc);  
	    }
	    else{
	      double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);
	      jMatx->Fill (jet4_pt, correctGenJetPt,effcorrmc);	  
	      jMCreco->Fill (jet4_pt,effcorrmc);	      
	    }
	  }
	  else {
	    jMatx->Fill (jet4_pt, correctGenJetPt);
	    jMCreco->Fill (jet4_pt);
	  }
	  jTrue->Fill (correctGenJetPt);
	}
	supplabel="_jet4";
	if ((jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayes.Fill(jet4_pt, correctGenJetPt);
	if ((jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) && !(correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayes.Fake(jet4_pt);
	if (!(jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) && (correctGenJetPt>0 && correctGenJetPt<7000)) unfold_jBayes.Miss(correctGenJetPt);

      }
    }
  jTrue->Sumw2();
  jMCreco->Sumw2();
  
  cout<<"I missed "<<counter<<" events (zero jets both in reco and truth)"<<endl;
  cout<<"the loop on MC has selected ->"<<counter3<<endl;

  cout<<"********************"<<endl;
  cout<<"number of events in MC training "<<categoryCounter<<endl;
  cout<<"number of events in MC training that fall in Fill "<<fillCounter<<endl;
  cout<<"number of events in MC training that fall in Miss "<<missCounter<<endl;
  cout<<"number of events in MC training that fall in Fakw "<<fakeCounter<<endl;
  cout<<"********************"<<endl;

  fChain = tree_fB;		/* Loop Data */
  Init (fChain);	
  Long64_t nentries2 = fChain->GetEntriesFast ();
  Long64_t nb2 = 0;
  
  if (fChain == 0)
    return;

  NData->Sumw2();
  
  for (Long64_t jentry = 0; jentry < nentries2; jentry++)
    {

      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb2 = fChain->GetEntry (jentry);
      nbytes += nb2;

      if (Jet_multiplicity > 30) continue;

      if (numbOfJetsSelected==1){      
	if( Jet_multiplicity>=0){    // Old        if( jet1_pt>=0 && jet1_pt<7000 ){
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    if (!useElectronsToCorrect){
	      std::vector<double> valuesdata=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJetsSelected,jet1_pt,"Data");
	      double effcorrdata=1.00/valuesdata[0];	
	      double efferrdata=valuesdata[1]/pow(valuesdata[0],2);
	      jData->Fill (jet1_pt,effcorrdata);
	      jData2->Fill (jet1_pt,effcorrdata);
	      effAndrea->Fill(jet1_pt,effcorrdata);
	    }
	    else{
	      double effcorrdata=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
	      efficiencycorrections->Fill(effcorrdata);
	      jData->Fill (jet1_pt,effcorrdata);
	      jData2->Fill (jet1_pt,effcorrdata);
	      effAnne->Fill(jet1_pt,effcorrdata);
	      NData->Fill (Jet_multiplicity,effcorrdata);
	    }
	  }
	  else {
	    jData->Fill (jet1_pt);
	    jData2->Fill (jet1_pt);
	  }
	}
      }

      if (numbOfJetsSelected==2){      
	if(jet2_pt>jetPtthreshold && jet2_pt<7000){
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    if (!useElectronsToCorrect){
	      std::vector<double> valuesdata=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJetsSelected,jet2_pt,"Data");
	      double effcorrdata=1.00/valuesdata[0];	
	      double efferrdata=valuesdata[1]/pow(valuesdata[0],2);
	      jData->Fill (jet2_pt,effcorrdata);
	      jData2->Fill (jet2_pt,effcorrdata);
	    }
	    else{
	      double effcorrdata=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
	      jData->Fill (jet2_pt,effcorrdata);
	      jData2->Fill (jet2_pt,effcorrdata);	      
	    }
	  }
	  else {
	    jData->Fill (jet2_pt);
	    jData2->Fill (jet2_pt);
	  }
	}
      }

      if (numbOfJetsSelected==3){      
	if(jet3_pt>jetPtthreshold && jet3_pt<7000){
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    if (!useElectronsToCorrect){
	      std::vector<double> valuesdata=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJetsSelected,jet3_pt,"Data");
	      double effcorrdata=1.00/valuesdata[0];	
	      double efferrdata=valuesdata[1]/pow(valuesdata[0],2);
	      jData->Fill (jet3_pt,effcorrdata);
	      jData2->Fill (jet3_pt,effcorrdata);
	    }
	    else{
	      double effcorrdata=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
	      jData->Fill (jet3_pt,effcorrdata);
	      jData2->Fill (jet3_pt,effcorrdata);
	    }
	  }
	  else {
	    jData->Fill (jet3_pt);
	    jData2->Fill (jet3_pt);
	  }
	}
      }
      
      if (numbOfJetsSelected==4){      
	if(jet4_pt>jetPtthreshold && jet4_pt<7000){
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    if (!useElectronsToCorrect){
	      std::vector<double> valuesdata=getEfficiencyCorrectionPt(fAeff,fBeff,numbOfJetsSelected,jet4_pt,"Data");
	      double effcorrdata=1.00/valuesdata[0];	
	      double efferrdata=valuesdata[1]/pow(valuesdata[0],2);
	      jData->Fill (jet4_pt,effcorrdata);
	      jData2->Fill (jet4_pt,effcorrdata);
	    }
	    else{
	      double effcorrdata=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
	      jData->Fill (jet4_pt,effcorrdata);
	      jData2->Fill (jet4_pt,effcorrdata);	      
	    }
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

  /////////////////////////
  //  Correct for background
  /////////////////////////
  
  if (correctForBkg){
    std::vector<double> bckcoeff;
    if (numbOfJetsSelected==1) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT");
    if (numbOfJetsSelected==2) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT2");
    if (numbOfJetsSelected==3) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT3");
    if (numbOfJetsSelected==4) bckcoeff=getBackgroundContributions(bkgstring,"jet_pT4");

    for (unsigned int k=0; k<divPlot; k++){
      jData->SetBinContent(k+1, jData->GetBinContent(k+1) - bckcoeff[k]);
      jData2->SetBinContent(k+1, jData2->GetBinContent(k+1) - bckcoeff[k]);	
      if (jData->GetBinContent(k+1)>0) {
	relativebkg->SetBinContent(k+1,bckcoeff[k]/jData->GetBinContent(k+1));
	cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is "<<bckcoeff[k]/jData->GetBinContent(k+1)<<endl;	
      }
      else {
	relativebkg->SetBinContent(k+1,0);
	cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is 0"<<endl;
      }
      cout<<"after "<<bckcoeff[k]/jData->GetBinContent(k+1)<<endl;
    }
  }

  TH1D *jTrueSwap;
  
  if (pythiaCheck) {
    jMatx=jMatxpythia;
    jTrueSwap= (TH1D*) jTrue->Clone("jTrue");
    jTrueSwap->SetName("jTrueSwap"); 
    jTrue=jTruepythia;
    unfold_jBayes=unfold_jBayespythia;
  }

  RooUnfoldResponse response_j(jMCreco, jTrue, jMatx); 
  response_j.UseOverflow();

  if (pythiaCheck) {
    jTrue=jTrueSwap; //Perche' fai questo? Per riprendere la MD MC truth e confrontare con il ratio
  }
  
  TH1F *vstatistics=new TH1F("vstatistics","vstatistics",divPlot,0,divPlot);
  int k0=1;
  int k1=2;
  if (bayesianTests){
    k0=0;
    k1=1;    
  }
  
  if (UnfoldDistributionsPt){
  for (int j=k0; j<k1; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=kmin; k< kmax; k++){
      int myNumber=k;
      if (j==0) myNumber=1;
      stringstream num;
      //if (myNumber>=divPlot) myNumber=divPlot-1;
      num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      std::string title2="Jet pT diff xsec distribution. "+title;
      cout<<"ongoing:"<<title<<endl;
      
      if (method=="Bayesian") {
	jReco->Sumw2();
	RooUnfoldBayes unfold_j (&unfold_jBayes, jData, myNumber, 1000);
	//RooUnfoldBayes unfold_j (&response_j, jData, myNumber+1, 1000);
	jReco = (TH1F *) unfold_j.Hreco ();
	unfold_j.PrintTable(cout,jTrue);
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
	
      }

      if (method=="Svd"){
	jReco->Sumw2();
	RooUnfoldSvd unfold_j (&unfold_jBayes, jData, 15, 1000); // per IL TEST PYTHIA!!!!!!!!!!!!!!!!!!!!!!
	//RooUnfoldSvd unfold_j (&response_j, jData, myNumber, 1000);	// OR
	jReco = (TH1F *) unfold_j.Hreco ();
	unfold_j.PrintTable(cout,jTrue);
	cout<<"Chi2 of this k parameter(k="<<myNumber<<")<< is "<<unfold_j.Chi2(jTrue,RooUnfold::kCovariance)<<endl;
	//RooUnfoldSvd unfold_j2 (&unfold_second, NData,6); // per IL TEST PYTHIA!!!!!!!!!!!!!!!!!!!!!!
	//TH1D *jReco2 = (TH1D *) unfold_j2.Hreco ();
	//cout<<"AAAAAAAAAAAAAAA"<<jReco2->Integral()/4890.0<<endl;
	//unfold_j2.PrintTable(cout);

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
	  jReco->SetBinError(k+1,sqrt(jReco->GetBinContent(k+1))); //FIXME!!!!!!!!!!!!!!!!!!!!!
	  //err.push_back(sqrt(pow(vstat[k],2) + sqrt(pow(vunfo[k],2))));
	  err.push_back(vunfo[k]);
	}
	kcontainer.push_back(err);
      }
      

      cout<<"area jReco:"<<jReco->Integral()<<" and MCreco "<<jMCreco->Integral()<<endl;
      cout<<"Zarea "<<Zarea<<endl;
      
      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1",0.01,0.33,0.99,0.99);
      pad1->Draw ();
      pad1->cd ();
      gPad->SetLogy (1);
      pad1->SetTopMargin(0.1);
      pad1->SetBottomMargin(0.01);
      pad1->SetRightMargin(0.1);
      pad1->SetFillStyle(0);

      string whichjet="";
      if (numbOfJetsSelected==1) whichjet="Leading "; 
      if (numbOfJetsSelected==2) whichjet="Second leading "; 
      if (numbOfJetsSelected==3) whichjet="Third leading "; 
      if (numbOfJetsSelected==4) whichjet="Fourth leading "; 
      title2=whichjet+"jet pT diff xsec distribution. "+title;
      jReco->SetTitle (title2.c_str());
      jReco->GetXaxis ()->SetTitle ("");
      if (!isMu) jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d p_{T}");
      if (isMu) jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d p_{T}");
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

      jReco->SetLabelSize(0.0);
      jReco->GetXaxis()->SetTitleSize(0.00);
      jReco->GetYaxis()->SetLabelSize(0.07);
      jReco->GetYaxis()->SetTitleSize(0.08);
      jReco->GetYaxis()->SetTitleOffset(0.76);
      jReco->SetTitle("");
      jReco->Draw("EP");	//risultato dell'unfolding

      jMCreco->SetLineColor (kBlue + 1);
      jMCreco->SetLineStyle (2);
      jMCreco->SetLineWidth (2); 
      if (!pythiaCheck) jMCreco->Draw("HISTSAMES");
      jTrue->SetLineColor (kRed);
      jTrue->SetLineWidth (2);
      jTrue->Draw ("HISTSAME");
      jData->SetLineColor(kGreen+1);
      pad1->SetLogy (1);
      jData->SetMarkerStyle (4);
      jData->SetMarkerColor(kGreen+1);
      jData->SetStats(0);
      jData->Draw("EPSAME");
   
      //pad1->SetBottomMargin (0.1);
      
      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (jReco, "Data Unfolded", "P20");
      legend_d->AddEntry (jTrue, "MC truth", "L");
      if (!pythiaCheck) legend_d->AddEntry (jMCreco, "MC reco", "L");
      legend_d->AddEntry(jData,"Data Folded","P20");
      legend_d->Draw ("same");
 
      TLatex *latexLabel=CMSPrel(4.890,""); // make fancy label
      latexLabel->Draw("same");   
      pad1->Update();      
      c->cd ();

      TPad *pad2 = new TPad ("pad2", "pad2",0.01,0.01,0.99,0.32);
      pad2->SetTopMargin (0);
      pad2->Draw ();
      pad2->cd ();
      pad2->SetTopMargin(0.01);
      pad2->SetBottomMargin(0.3);
      pad2->SetRightMargin(0.1);
      pad2->SetFillStyle(0);

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
      jRecoClone->GetYaxis()->SetNdivisions(5);
      jRecoClone->GetXaxis()->SetTitleSize(0.14);
      jRecoClone->GetXaxis()->SetLabelSize(0.14);
      jRecoClone->GetYaxis()->SetLabelSize(0.11);
      jRecoClone->GetYaxis()->SetTitleSize(0.11);
      jRecoClone->GetYaxis()->SetTitleOffset(0.28);
      jRecoClone->GetYaxis()->SetTitle("ratio data/MC");
      jRecoClone->Draw("ep");
      
      TH1F *jDataClone= (TH1F*) jReco->Clone("jReco");
      jDataClone->SetName("jDataClone"); 
      jDataClone->Divide(jData);
      jDataClone->SetLineStyle (2); 
      jDataClone->SetMarkerSize (0);       
      jDataClone->SetLineWidth (0.05);
      jDataClone->SetLineColor(kViolet);
      if (!pythiaCheck) jDataClone->Draw ("E1HISTSAME");
      jDataClone->SetLineWidth (0.1);

      TF1 *f = new TF1("f","1",0,410);
      f->SetLineWidth(1);
      f->Draw("SAMES");

      TLegend *legend_w = new TLegend(0.197791, 0.736607, 0.394578, 0.9375);
      legend_w->SetFillColor (0);
      legend_w->SetFillStyle (0);
      legend_w->SetBorderSize (0);
      legend_w->AddEntry (jRecoClone, "Data Unfolded / MC truth", "P20");
      //legend_w->AddEntry (jMCRecoClone, "MC reco / MC truth", "L");
      if (!pythiaCheck) legend_w->AddEntry (jDataClone, "Data Unfolded / Data Folded", "L");
      legend_w->Draw ("same");
      //pad2->Update();
      string title3= s+"JETPTXSEC"+method+"_"+num.str()+supplabel+".pdf";
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
  cout<<"area jReco:"<<jReco->Integral()<<" and MCreco "<<jMCreco->Integral()<<endl;
  cout<<"Zarea "<<Zarea<<endl;

      TLegend *legend_e = new TLegend (0.23494, 0.696429, 0.431727, 0.895833);
      legend_e->SetFillColor (0);
      legend_e->SetFillStyle (0);
      legend_e->SetBorderSize (0);
      legend_e->AddEntry (staterror, "Statistical Errors", "L");
      legend_e->AddEntry (unfoerror, "Unf. Errors with Toy", "L");
      legend_e->AddEntry (staterrorsqrt, "Statistical Errors, sqrt of data", "L");
      legend_e->Draw ("same");  cout<<"area jReco:"<<jReco->Integral()<<" and MCreco "<<jMCreco->Integral()<<endl;
  cout<<"Zarea "<<Zarea<<endl;


      string title4= s+"JETPTerror"+method+"_"+num.str()+supplabel+".pdf";
      err->Print(title4.c_str());

      TCanvas *N =new TCanvas ("jet pT response matrix", "jet pT response matrix", 1000, 700);
      N->cd ();
      jMatxlong->SetStats (0);
      gPad->SetLogz (1);
      gPad->SetRightMargin(0.15);
      jMatxlong->SetTitle("");
      jMatxlong->GetZaxis()->SetRangeUser(0.002,1);
      jMatxlong->GetXaxis()->SetTitle("Reconstructed jet pT [GeV/c]");
      jMatxlong->GetYaxis()->SetTitle("Generated jet pT [GeV/c]");
      gStyle->SetPalette (1);
      gStyle->SetPaintTextFormat ("5.3f");
      gStyle->SetNumberContours (999);
      jMatxlong->SetMarkerColor (kBlack);
      double entries=1.000/(double)jMatxlong->Integral();
      jMatxlong->Scale(entries);
      jMatxlong->Draw ("COLZ,text");
      string title5= s+"JetPtUnfoMatrix"+method+"_"+num.str()+supplabel+".pdf";
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
  }
  

  if (!UnfoldDistributionsPt) jReco=(TH1F*) jData->Clone();

  if (cold){
    cold=false;
  }
  
  TCanvas *rel =new TCanvas ("rel", "Background relative contribution, bin by bin", 1000, 700);
  rel->cd ();
  relativebkg->SetLineColor(kRed);
  relativebkg->GetXaxis()->SetTitle("Jet Pt Bin");
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
  
  string title6= s+"Kparam.pdf";
  kparam->Print(title6.c_str()); 


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
      
  ///////////
  ///SAve unfolded distribution
  /////////// 
  
  if (saveFile){
    TFile* w = new TFile(filename.c_str(), "UPDATE");
    w->cd();

    if (numbOfJetsSelected==1) {
      TH1F *jReco_leading= (TH1F*) jReco->Clone("jReco");
      jReco_leading->SetName("jReco_leading");
      jReco_leading->Write();
      TH1F *jTrue_leading= (TH1F*) jTrue->Clone("jTrue");
      jTrue_leading->Write();
      TH2F *jMatx_leading= (TH2F*) jMatx->Clone("jMatx");
      jMatx_leading->Write();
      TH1F *jData_leading= (TH1F*) jData->Clone("jData");
      jData_leading->Write();
      TH1F *jMCreco_leading= (TH1F*) jMCreco->Clone("jMCreco");
      jMCreco_leading->Write();
    }
    if (numbOfJetsSelected==2) {
      TH1F *jReco_subleading= (TH1F*) jReco->Clone("jReco");
      jReco_subleading->SetName("jReco_subleading");
      jReco_subleading->Write();
      TH1F *jTrue_subleading= (TH1F*) jTrue->Clone("jTrue");
      jTrue_subleading->Write();

    }
    if (numbOfJetsSelected==3) {
      TH1F *jReco_subsubleading= (TH1F*) jReco->Clone("jReco");
      jReco_subsubleading->SetName("jReco_subsubleading");
      jReco_subsubleading->Write();
      TH1F *jTrue_subsubleading= (TH1F*) jTrue->Clone("jTrue");
      jTrue_subsubleading->Write();

    }
    if (numbOfJetsSelected==4) {
      TH1F *jReco_subsubsubleading= (TH1F*) jReco->Clone("jReco");
      jReco_subsubsubleading->SetName("jReco_subsubsubleading");
      jReco_subsubsubleading->Write();
      TH1F *jTrue_subsubsubleading= (TH1F*) jTrue->Clone("jTrue");
      jTrue_subsubsubleading->Write();

    }

    w->Close();
  }  
}
