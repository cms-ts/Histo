#include "TSVDUnfold.h"

double getGenJetEtaOfAGivenOrder(int Jet_multiplicity_gen, int whichjet, double thresh, double jet1_pt_gen, double jet2_pt_gen, double jet3_pt_gen, double jet4_pt_gen, double jet1_eta_gen, double jet2_eta_gen, double jet3_eta_gen, double jet4_eta_gen){

  double jetPt=0.0;
  //Stabilisci chi e' il piu' grande e l'ordine in pt, togliendo jet fuori l'accettanza o a pt sotto treshold
  //cout<<"jet multipl->"<<Jet_multiplicity_gen<<" jet1pt->"<<jet1_pt_gen<<" jet2pt->"<<jet2_pt_gen<<" jet3_pt->"<<jet3_pt_gen<<" jet4_pt->"<<jet4_pt_gen<<" jet1eta->"<<jet1_eta_gen<<" jet2eta->"<<jet2_eta_gen<<" jet3_eta->"<<jet3_eta_gen<<" jet4_eta->"<<jet4_eta_gen<<endl;

  if (Jet_multiplicity_gen==0 && jet1_pt_gen<thresh) return 0;

  //Immagazzino le info di pt e eta in un vettore di vettori
  std::vector<double> pt;
  typedef std::map<double, double> MapType;
  MapType mappteta;
  
  // insert elements using insert function

  if (Jet_multiplicity_gen==0 && fabs(jet1_eta_gen)<=2.4) pt.push_back(jet1_pt_gen);  
   
  for (int i=1;i<=4; i++){
    if (i==1){
      if (jet1_pt_gen>thresh && fabs(jet1_eta_gen)<=2.4 ) {
	pt.push_back(jet1_pt_gen);
	mappteta.insert(std::pair<double, double>(jet1_pt_gen, jet1_eta_gen));
      }
    } 
    if (i==2){
      if (jet2_pt_gen>thresh && fabs(jet2_eta_gen)<=2.4 ) {
	pt.push_back(jet2_pt_gen);
	mappteta.insert(std::pair<double, double>(jet2_pt_gen, jet2_eta_gen));
      }
    } 
    if (i==3){
      if (jet3_pt_gen>thresh && fabs(jet3_eta_gen)<=2.4 ) {
	pt.push_back(jet3_pt_gen);
	mappteta.insert(std::pair<double, double>(jet3_pt_gen, jet3_eta_gen));
      }
    } 
    if (i==4){
      if (jet4_pt_gen>thresh && fabs(jet4_eta_gen)<=2.4 ) {
	pt.push_back(jet4_pt_gen);
	mappteta.insert(std::pair<double, double>(jet4_pt_gen, jet4_eta_gen));
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
  
  MapType::iterator iter = mappteta.begin();
  iter = mappteta.find(jetPt);
  if (iter != mappteta.end() ) {
    return iter->second;
  }
  return -9999;
}


void Unfolding::LoopJetEta (int numbOfJets)
{
  cout<<"*********************************"<<endl;
  cout<<"Unfolding Eta Spectra"<<endl;
  cout<<"*********************************"<<endl;

minPtPlot=-2.4;
maxPtPlot=2.4;
divPlot=48;
kmin=1;
kmax=1;
spanKvalues=false;
 bool Unfold=true;

TH1F *relativebkg = new TH1F("relativebkg", "relativebkg bin contribution",divPlot,0,divPlot);
  
#ifdef __CINT__
  gSystem->Load ("libRooUnfold");
#endif

  ///////////
  // Format the plots in thew proper way
  ///////////

  if (numbOfJets==1) {
    kmin=9;
    kmax=10;
    divPlot=24;
  }

  if (numbOfJets==2){
    kmin=20;
    kmax=21;
    divPlot=20;
  }

  if (numbOfJets==3){
    kmin=20;
    kmax=21;
    divPlot=16;
  }
  
  if (numbOfJets==4){
    kmin=20;
    kmax=21;
    divPlot=12;
  }

  if (spanKvalues){
    int kmin=1;
    int kmax=divPlot-1; 
  }
  

  TH1D *jTrue = new TH1D ("jTrue", "jetpT Truth",divPlot,minPtPlot,maxPtPlot);
  TH1D *jTruepythia = new TH1D ("jTruepythia", "jetpT Truth using Pythia",divPlot,minPtPlot,maxPtPlot);
  TH1D *jData = new TH1D ("jData", "jetpT DATA Measured",divPlot,minPtPlot,maxPtPlot);
  TH1D *jReco = new TH1D ("jReco", "jetpT Unfolded DATA",divPlot,minPtPlot,maxPtPlot);
  TH2D *jMatx = new TH2D ("jMatx", "Unfolding Matrix jetpT Rapidity ",divPlot,minPtPlot,maxPtPlot,divPlot,minPtPlot,maxPtPlot);
  TH2D *jMatxpythia = new TH2D ("jMatxpythia", "Unfolding Matrix jetpT Rapidity using pythia",divPlot,minPtPlot,maxPtPlot,divPlot,minPtPlot,maxPtPlot);
  TH1D *jMCreco = new TH1D ("jMCreco", "jetpT mcreco",divPlot,minPtPlot,maxPtPlot);
  TH1D *jData2 = new TH1D ("jData2", "jetpT DATA Measured2",divPlot,minPtPlot,maxPtPlot);
  TH1D *jRatio_ = new TH1D ("jRatio_", "jetpTRatio",divPlot,minPtPlot,maxPtPlot);
  
  //To compute errors
  TH1F *staterror = new TH1F ("staterror", "staterror",divPlot,0,divPlot);
  TH1F *staterrorsqrt = new TH1F ("staterrorsqrt", "staterrorsqrt",divPlot,0,divPlot);
  TH1F *unfoerror = new TH1F ("unfoerror", "unfoerror",divPlot,0,divPlot);
  TH1F *unfoerrormat = new TH1F ("unfoerrormat", "unfoerrormat",divPlot,0,divPlot);
  TH1F *unfoerrordiag = new TH1F ("unfoerrordiag", "unfoerrordiag",divPlot,0,divPlot);
  TH1F *efficiencycorrections = new TH1F ("efficiencycorrections", "efficiencycorrections",60,0,3);
  TH1F *efficiencycorrectionsmc = new TH1F ("efficiencycorrectionsmc", "efficiencycorrectionsmc",60,0,3);	
  
  //Module D histo
  TH1D* modD;

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

  int categoryCounter=0;
  double fillCounter=0;
  double missCounter=0;
  double fakeCounter=0;

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

  RooUnfoldResponse unfold_jBayespythia(jMCreco,jTrue);
  unfold_jBayespythia.UseOverflow();

  if (pythiaCheck){
    //fill the matrix --->
    string pythiaold=smcpythia;
    fPythia = new TFile (smcpythia.c_str());
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
      
      if (Jet_multiplicity > 30 || Jet_multiplicity_gen > 30 ) continue;
      
      if (isElectron!=isEle) {
	cout<<"is_Electron(rootupla) is ->"<<isElectron<<", while the isElectron(unfolding) is "<<isEle<<" You are using the wrong TTree, ele instead of muons or viceversa..exit"<<endl;
	return;
      }
      
      int offsetJetMultiplicity=0;
      double thresh=15.0;
      double correctGenJetEta=getGenJetEtaOfAGivenOrder(Jet_multiplicity_gen,numbOfJets,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen);
      if (correctGenJetEta==0) continue;
      /////////////////////////
      if(numbOfJets==1 && ( (jet1_pt>0 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) || fabs(correctGenJetEta)<=2.4) ){
	jMatxpythia->Fill(jet1_eta, correctGenJetEta);	 
	jTruepythia->Fill (correctGenJetEta);
	if ((jet1_pt>0 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) && fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Fill(jet1_eta, correctGenJetEta);
	if ((jet1_pt>0 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) && !fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Fake(jet1_eta);
	if (!(jet1_pt>0 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) && fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Miss(correctGenJetEta);
      }

      if(numbOfJets==2 && ( (jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) || fabs(correctGenJetEta)<=2.4) ){
	jMatxpythia->Fill(jet2_eta, correctGenJetEta);	 
	jTruepythia->Fill (correctGenJetEta);
	if ((jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) && fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Fill(jet2_eta, correctGenJetEta);
	if ((jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) && !fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Fake(jet2_eta);
	if (!(jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) && fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Miss(correctGenJetEta);
      }

      if(numbOfJets==3 && ( (jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) || fabs(correctGenJetEta)<=2.4) ){
	jMatxpythia->Fill(jet3_eta, correctGenJetEta);	 
	jTruepythia->Fill (correctGenJetEta);
	if ((jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) && fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Fill(jet3_eta, correctGenJetEta);
	if ((jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) && !fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Fake(jet3_eta);
	if (!(jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) && fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Miss(correctGenJetEta);
      }

      if(numbOfJets==4 && ( (jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) || fabs(correctGenJetEta)<=2.4) ){
	jMatxpythia->Fill(jet4_eta, correctGenJetEta);	 
	jTruepythia->Fill (correctGenJetEta);
	if ((jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) && fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Fill(jet4_eta, correctGenJetEta);
	if ((jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) && !fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Fake(jet4_eta);
	if (!(jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) && fabs(correctGenJetEta)<=2.4 ) unfold_jBayespythia.Miss(correctGenJetEta);
      }

      
      ///////////////////////
    }
    smcpythia=pythiaold;
  }

  //Setting the errors
  jTrue->Sumw2();
  jMCreco->Sumw2();
  jData->Sumw2();

  double thresh=30.0;

  /*costruisco la matrice di unfolding */

  fChain = tree_fA;		/* Loop Montecarlo */
  Init (fChain);
  Long64_t nentries = fChain->GetEntriesFast ();
  Long64_t nbytes = 0, nb = 0;

  if (splitCheck) {
    nentries=(int) 2.0*(nentries/3.);
    cout<<"Slitcheck is active, so Dataset A has now "<<nentries<<endl;
  }


  if (fChain == 0)
    return;
  
  for (Long64_t jentry = 0; jentry < nentries; jentry++)
    {
      
      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb = fChain->GetEntry (jentry);
      nbytes += nb;

      if (Jet_multiplicity > 30 || Jet_multiplicity_gen > 30 ) continue;
      double jet_eta_gen=0;
      double jet_eta=0;
      double jet_pt_gen=0;
      double jet_pt=0;

      if (numbOfJets==1) {
	jet_eta_gen=jet1_eta_gen;
	jet_eta=jet1_eta;
	jet_pt_gen=jet1_pt_gen;
	jet_pt=jet1_pt;
      }
      if (numbOfJets==2) {
	jet_eta_gen=jet2_eta_gen;
	jet_eta=jet2_eta;
	jet_pt_gen=jet2_pt_gen;
	jet_pt=jet2_pt;
      }
      if (numbOfJets==3) {
	jet_eta_gen=jet3_eta_gen;
	jet_eta=jet3_eta;
	jet_pt_gen=jet3_pt_gen;
	jet_pt=jet3_pt;
      }
      if (numbOfJets==4) {
	jet_eta_gen=jet4_eta_gen;
	jet_eta=jet4_eta;
	jet_pt_gen=jet4_pt_gen;
	jet_pt=jet4_pt;
      }
	
      if (correctForSecondaryMigrations){
	//double realGenJetMultiplicity=getNumberOfValidGenJets(threshPt,threshEta,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet5_pt_gen,jet6_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen,jet5_eta_gen,jet6_eta_gen);
       
	
	if ( (l1_pt_gen<20 || l2_pt_gen<20) & (recoZInAcceptance==1) ){
	  unfold_jBayes.Fake(jet_eta);
	  continue;
	}
	
	if ( (invMass_gen>111 || invMass_gen<71) & (recoZInAcceptance==1) ){
	  unfold_jBayes.Fake(jet_eta);
	  continue;
	}
	
	//account for the gap!
	if ( (( fabs(l1_eta_gen)>1.442 & fabs(l1_eta_gen)<1.566 && fabs(l2_eta_gen)<2.4) || ( fabs(l2_eta_gen)>1.442 & fabs(l2_eta_gen)<1.566)&& fabs(l1_eta_gen)<2.4) && Jet_multiplicity==0 && isElectron){
	  unfold_jBayes.Miss(jet_eta);
	  continue;
	}
	
	if (recoZInAcceptance==1 && genZInAcceptance==0){
	  unfold_jBayes.Fake(jet_eta);
	  continue;
	}
      }
      
    
      if (recoZInAcceptance==0) continue;  

   if (isElectron!=isEle) {
      cout<<"is_Electron(rootupla) is ->"<<isElectron<<", while the isElectron(unfolding) is "<<isEle<<" You are using the wrong TTree, ele instead of muons or viceversa..exit"<<endl;
      return;
    }
      double correctGenJetEta=0.0;
      double correctGenJetPt=0.0;
      double correctJetPt=0.0;
      double correctJetEta=0.0;

      if (numbOfJets<=1){
	correctGenJetPt=jet1_pt_gen;
	correctJetPt=jet1_pt;
	correctGenJetEta=jet1_eta_gen;
	correctJetEta=jet1_eta;
      }

      if (numbOfJets==2){
	correctGenJetPt=jet2_pt_gen;
	correctJetPt=jet2_pt;
	correctGenJetEta=jet2_eta_gen;
	correctJetEta=jet2_eta;
      }

      if (numbOfJets==3){
	correctGenJetPt=jet3_pt_gen;
	correctJetPt=jet3_pt;
	correctGenJetEta=jet3_eta_gen;
	correctJetEta=jet3_eta;
      }

      if (numbOfJets==4){
	correctGenJetPt=jet4_pt_gen;
	correctJetPt=jet4_pt;
	correctGenJetEta=jet4_eta_gen;
	correctJetEta=jet4_eta;
      }

   double realGenJetMultiplicity=getNumberOfValidGenJets(threshPt,threshEta,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet5_pt_gen,jet6_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen,jet5_eta_gen,jet6_eta_gen);
   
   // To control and exclude jets having energy below "thresh"
   int offsetJetMultiplicity=0;
   offsetJetMultiplicity=getNumberOfValidGenJetsPt(Jet_multiplicity_gen,threshPt,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen);
   
   double thresh=threshPt;

   double effcorrmc=1.0;
   if (!identityCheck) effcorrmc = 1.0 * evWeight; 

   //      if (numbOfJets<=1){

   if (correctForEff) effcorrmc=effcorrmc*1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);
   
   if ((Jet_multiplicity >= numbOfJets ||  (realGenJetMultiplicity) >=numbOfJets)){
     categoryCounter++;
	  jTrue->Fill (correctGenJetEta);
	  supplabel="_jet1";
	  
	  // Questa e' quando c'e' tutto
	if ((correctJetPt>30 && fabs(correctJetEta)<2.4) && (correctGenJetPt>30 && correctGenJetPt<7000 &&  fabs(correctGenJetEta)<2.4)) {
	    jMatx->Fill (jet_eta, correctGenJetEta,effcorrmc);	
	    unfold_jBayes.Fill(jet_eta, correctGenJetEta,effcorrmc);
	    fillCounter+=effcorrmc;
	  }
	if ( (correctJetPt>30 && fabs(correctJetEta)<2.4) && !(correctGenJetPt>30 && correctGenJetPt<7000 &&  fabs(correctGenJetEta)<2.4)) {
	    unfold_jBayes.Fake(jet_eta,effcorrmc);
	    fakeCounter+=1*effcorrmc;
	  }
	  //Questa e' facili, c'era e non l'ho visto
	if (!(correctJetPt>30 && fabs(correctJetEta)<2.4) && (correctGenJetPt>30 && correctGenJetPt<7000 &&  fabs(correctGenJetEta)<2.4)){
	    jMatx->Fill (jet_eta, correctGenJetEta,effcorrmc);	
	    unfold_jBayes.Miss(correctGenJetEta);
	    missCounter+=1*effcorrmc;
	  }
	}
	else{
	  //if (Jet_multiplicity == 0 && ( (realGenJetMultiplicity) ==0)) unfold_jBayes.Fill(jet_eta,correctGenJetEta,effcorrmc); //zeri
	  //jTrue->Fill (correctGenJetEta);
/* 	  if (!(fabs(correctGenJetEta)<=2.4 && jet_pt_gen>30) && Jet_multiplicity>=numbOfJets){ */
/* 	      jMatx->Fill (jet_eta, correctGenJetEta,effcorrmc);	 */
/* 	      unfold_jBayes.Fake(jet_eta,effcorrmc); */
/* 	    fakeCounter+=effcorrmc; */
/* 	  } */
/* 	  if (((fabs(correctGenJetEta)<=2.4) && jet_pt_gen>30 )  && Jet_multiplicity==0){ */
/* 	    jMatx->Fill (jet_eta, correctGenJetEta,effcorrmc);	 */
/* 	    unfold_jBayes.Miss(correctGenJetEta); */
/* 	    missCounter+=1*effcorrmc; */
/* 	  } */
/* 	  if (((fabs(correctGenJetEta)<=2.4)  && jet_pt_gen>30) && Jet_multiplicity>=numbOfJets){ */
/* 	    jMatx->Fill (jet_eta, correctGenJetEta,effcorrmc);	 */
/* 	    fillCounter+=effcorrmc; */
/* 	    unfold_jBayes.Fill(jet_eta,correctGenJetEta,effcorrmc); */
/* 	  } */
	}
	//}

   /**************   
   if (numbOfJets<=1){
     double correctGenJetEta=jet1_eta_gen;
     //     if ((Jet_multiplicity >= 1 ||  (realGenJetMultiplicity) >=1) && offsetJetMultiplicity==0){
       //	double correctGenJetEta=getGenJetEtaOfAGivenOrder(Jet_multiplicity_gen,numbOfJets,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen);

       effcorrmc=effcorrmc*1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle);	
       
       if((jet1_pt>30 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) || fabs(correctGenJetEta)<=2.4 ){ 
	 //if (correctGenJetEta==0 & jet1_pt>0) continue;
	 //Correct for efficiencies event per event
	 if (correctForEff){
	   jMatx->Fill (jet1_eta, correctGenJetEta,effcorrmc);	 
	 jMCreco->Fill (jet1_eta,effcorrmc);
	 }
	 else {
	   jMatx->Fill (jet1_eta, jet1_eta_gen);
	   jMCreco->Fill (jet1_eta);
	 }
	 jTrue->Fill (jet1_eta_gen);
	 supplabel="_jet1";
       }
       if ((jet1_pt>30 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) && fabs(correctGenJetEta)<=2.4 ) {
	 unfold_jBayes.Fill(jet1_eta, correctGenJetEta,effcorrmc);
	 fillCounter+=effcorrmc;
       }
       if ((jet1_pt>30 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) && !fabs(correctGenJetEta)<=2.4 ) {
	 unfold_jBayes.Fake(jet1_eta,effcorrmc);
	 fakeCounter+=effcorrmc;
       }
       if (!(jet1_pt>30 && jet1_pt<7000 && fabs(jet1_eta)<=2.4) && fabs(correctGenJetEta)<=2.4 ) {
	 unfold_jBayes.Miss(correctGenJetEta);
	 missCounter+=effcorrmc;
       }
   }
   // }
  //   else{
  // if (!(jet1_eta_gen>0) && Jet_multiplicity>=1){
  //   jMatx->Fill (jet1_eta, jet1_eta_gen,effcorrmc);	
  //   unfold_jBayes.Fake(jet1_eta,effcorrmc);
  // }
   //}
   ***************************/

/*    if (numbOfJets==2){ */
/*      //	double correctGenJetPt=getGenJetEtaOfAGivenOrder(Jet_multiplicity_gen,numbOfJets,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen); */
/*      double correctGenJetEta=jet2_eta_gen; */
/*      double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle); */
     
/*      if((jet2_pt>0 && jet2_pt<7000 && fabs(jet2_eta)<=2.4) ){ */
/*        //Correct for efficiencies event per event */
/* 	  if (correctForEff){ */
/* 	    jMatx->Fill (jet2_eta, correctGenJetEta,effcorrmc);	  */
/* 	    jMCreco->Fill (jet2_eta,effcorrmc); */
/* 	  } */
/* 	  else { */
/* 	    jMatx->Fill (jet2_eta, jet2_eta_gen); */
/* 	    jMCreco->Fill (jet2_eta); */
/* 	  } */
/* 	  jTrue->Fill (jet2_eta_gen); */
/* 	  supplabel="_jet2"; */
/*      } */
/*    } */
   
/*    if (numbOfJets==3){ */
/*      //	double correctGenJetPt=getGenJetEtaOfAGivenOrder(Jet_multiplicity_gen,numbOfJets,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen); */
/*      double correctGenJetEta=jet3_eta_gen; */
/*      double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle); */
     
/*      if((jet3_pt>0 && jet3_pt<7000 && fabs(jet3_eta)<=2.4) ){ */
/*        //Correct for efficiencies event per event */
/*        if (correctForEff){ */
/* 	 jMatx->Fill (jet3_eta, correctGenJetEta,effcorrmc);	  */
/* 	    jMCreco->Fill (jet3_eta,effcorrmc); */
/*        } */
/*        else { */
/* 	 jMatx->Fill (jet3_eta, jet3_eta_gen); */
/* 	 jMCreco->Fill (jet3_eta); */
/*        } */
/*        jTrue->Fill (jet3_eta_gen); */
/*        supplabel="_jet3"; */
/*      } */
/*    } */
   
/*    if (numbOfJets==4){ */
/*      //	double correctGenJetPt=getGenJetEtaOfAGivenOrder(Jet_multiplicity_gen,numbOfJets,thresh,jet1_pt_gen,jet2_pt_gen,jet3_pt_gen,jet4_pt_gen,jet1_eta_gen,jet2_eta_gen,jet3_eta_gen,jet4_eta_gen); */
/*      double correctGenJetEta=jet4_eta_gen; */
/*      double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"MC",isEle); */
/*      if((jet4_pt>0 && jet4_pt<7000 && fabs(jet4_eta)<=2.4) ){ */
/*        //Correct for efficiencies event per event */
/*        if (correctForEff){ */
/* 	 jMatx->Fill (jet4_eta, correctGenJetEta,effcorrmc);	  */
/* 	 jMCreco->Fill (jet4_eta,effcorrmc); */
/*        } */
/*        else { */
/* 	 jMatx->Fill (jet4_eta, jet4_eta_gen); */
/* 	 jMCreco->Fill (jet4_eta); */
/*        } */
/*        jTrue->Fill (jet4_eta_gen); */
/*        supplabel="_jet4"; */
/*      } */
/*    } */
    }
  
  jTrue->Sumw2();
  jMCreco->Sumw2();
  
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
  
  for (Long64_t jentry = 0; jentry < nentries2; jentry++)
    {

      Long64_t ientry = LoadTree (jentry);
      if (ientry < 0)
	break;
      nb2 = fChain->GetEntry (jentry);
      nbytes += nb2;

      double effcorrmc=1.00;
	    
      if (numbOfJets==1){      
	if( jet1_pt>30 && jet1_pt<7000 && fabs(jet1_eta)<2.4){    // Old        if( jet1_eta>=0 && jet1_eta<7000 ){
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
	    jData->Fill (jet1_eta,effcorrmc);	 
	    jData2->Fill (jet1_eta,effcorrmc);	
	  }
	  else {
	    jData->Fill (jet1_eta);
	    jData2->Fill (jet1_eta);
	  }
	}
	efficiencycorrections->Fill(effcorrmc);
      }

      if (numbOfJets==2){      
	if( jet2_pt>30 && jet2_pt<7000 && fabs(jet2_eta)<2.4 ){ 
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
	    jData->Fill (jet2_eta,effcorrmc);	 
	    jData2->Fill (jet2_eta,effcorrmc);	
	  }
	  else {
	    jData->Fill (jet2_eta);
	    jData2->Fill (jet2_eta);
	  }
	}
      }

      if (numbOfJets==3){      
	if( jet3_pt>30 && jet3_pt<7000 && fabs(jet3_eta)<2.4 ){ 
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
	    jData->Fill (jet3_eta,effcorrmc);	 
	    jData2->Fill (jet3_eta,effcorrmc);
	  }
	  else {
	    jData->Fill (jet3_eta);
	    jData2->Fill (jet3_eta);
	  }
	}
      }

      if (numbOfJets==4){      
	if( jet4_pt>30 && jet4_pt<7000 && fabs(jet4_eta)<2.4 ){ 
	  //Correct for efficiencies, event per event
	  if (correctForEff){
	    double effcorrmc=1.00/getEfficiencyCorrectionPtUsingElectron(fAeff,fBeff,e1_pt,e1_eta,e2_pt,e2_eta,"Data",isEle);
	    jData->Fill (jet4_eta,effcorrmc);	 
	    jData2->Fill (jet4_eta,effcorrmc);
	  }
	  else {
	    jData->Fill (jet4_eta);
	    jData2->Fill (jet4_eta);
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
    ofstream backSignificance;
    if (numbOfJets==1) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet1EtaMu.txt");
    }
    if (numbOfJets==2) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta2");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet2EtaMu.txt");
    }
    if (numbOfJets==3) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta3");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet3EtaMu.txt");
    }
    if (numbOfJets==4) {
      bckcoeff=getBackgroundContributions(bkgstring,"jet_eta4");
      if (MCstatError && !isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4Eta.txt");
      if (MCstatError && isMu) backSignificance.open ("/gpfs/cms/data/2011/BackgroundEvaluation/backgroundStatErrorJet4EtaMu.txt");
    }
    
    for (unsigned int k=0; k<divPlot; k++){
    double backvalue=bckcoeff[k];
      jData->SetBinContent(k+1, jData->GetBinContent(k+1) - bckcoeff[k]);
      jData2->SetBinContent(k+1, jData2->GetBinContent(k+1) - bckcoeff[k]);	
      if (jData->GetBinContent(k+1)>0) {
	if (bckcoeff[k]<0.000000001) backvalue=0.0;
	relativebkg->SetBinContent(k+1,bckcoeff[k]/jData->GetBinContent(k+1));
	cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is "<<bckcoeff[k]/jData->GetBinContent(k+1)<<endl;	
      }
      else {
	relativebkg->SetBinContent(k+1,0);
	if (bckcoeff[k]<0.000000001) backvalue=0.0;
	cout<<"Data:"<<jData->GetBinContent(k+1)<<" bck:"<<bckcoeff[k]<<" (coefficient is "<<bckcoeff[k]<<"). Relative bin ratio is 0"<<endl;
      }
      backSignificance<<jData->GetBinContent(k+1)<<" "<<backvalue<<endl;
      cout<<"after "<<bckcoeff[k]/jData->GetBinContent(k+1)<<endl;
    }
    backSignificance.close();
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
    response_j=unfold_jBayespythia;
  }

  TH1F *vstatistics=new TH1F("vstatistics","vstatistics",divPlot,0,divPlot);
  string title2,title;
  stringstream num;
 
  int k0=1;
  int k1=2;
  if (bayesianTests){
    k0=0;
    k1=1;    
  }

  for (int j=k0; j<k1; j++){
    string method;
    if (j==0) method="Bayesian";
    if (j==1) method="Svd";
    cout<<"Running "<<method<<" method"<<endl;
    for (int k=kmin; k< kmax; k++){
      int myNumber=k;
      if (myNumber>=divPlot) myNumber=divPlot-1;
      num<<myNumber;
      string title="Data unfolding "+method+" method with K="+num.str();
      title2="Jet eta diff xsec distribution. "+title;
      cout<<"ongoing:"<<title<<endl;
      
      if (Unfold){
      if (method=="Bayesian") {
	RooUnfoldBayes unfold_j (&unfold_jBayes, jData, myNumber, 1000);
	//RooUnfoldBayes unfold_j(&response_j, jData, myNumber, 1000);
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

      }

      if (method=="Svd"){
	jReco->Sumw2();
	RooUnfoldSvd unfold_j (&unfold_jBayes, jData, myNumber, 1000);	// OR
	TSVDUnfold unfold_t (jData, jTrue,jMCreco,jMatx); // per IL TEST PYTHIA!!!!!!!!!!!!!!!!!!!!!!
	jReco = (TH1D *) unfold_j.Hreco ();
	unfold_j.PrintTable(cout,jTrue);
	// Extract covariance matrix TMatrixD m= unfold_j.Ereco();
	TVectorD vstat= unfold_j.ErecoV();
	TVectorD vunfo= unfold_j.ErecoV(RooUnfold::kCovToy);
	TVectorD vunfomat= unfold_j.ErecoV(RooUnfold::kCovariance);
	TVectorD vunfodiag= unfold_j.ErecoV(RooUnfold::kErrors);
	
	TH1D* unfresult = unfold_t.Unfold( myNumber );
	modD = unfold_t.GetD();

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
      }
    
      if (!Unfold) jReco=(TH1D*) jData->Clone();
      cout<<"area jReco:"<<jReco->Integral()<<" and MCreco "<<jMCreco->Integral()<<endl;
      cout<<"Zarea "<<Zarea<<endl;

      /////////////////////
      /// Error treatment
      /////////////////////
      
      std::vector<double> erre;
      for (unsigned int k=0; k<jData->GetNbinsX(); k++){
	// Old hipothesis with giuseppe!! jReco->SetBinError(k+1,sqrt(pow(vstat[k],2) + sqrt(pow(vunfo[k],2)) )); // How we chose to treat the eerros.. quatradutre sum
	//jReco->SetBinError(k+1,vunfo[k] ); // Suggerita da andrea... conta il toy, quando e' simile a quello di partenza
	jReco->SetBinError(k+1,sqrt(jReco->GetBinContent(k+1)) );
	  //err.push_back(sqrt(pow(vstat[k],2) + sqrt(pow(vunfo[k],2))));
	//erre.push_back(vunfo[k]);
      }
      kcontainer.push_back(erre);
      
      TCanvas *c = new TCanvas ("c", "c", 1000, 700);
      c->cd ();
      TPad *pad1 = new TPad ("pad1", "pad1",0.01,0.33,0.99,0.99);

      pad1->Draw ();
      pad1->cd ();
      //gPad->SetLogy (1);
      pad1->SetTopMargin(0.1);
      pad1->SetBottomMargin(0.01);
      pad1->SetRightMargin(0.1);
      pad1->SetFillStyle(0);

      string whichjet="";
      if (numbOfJets==1) whichjet="Leading "; 
      if (numbOfJets==2) whichjet="Second leading "; 
      if (numbOfJets==3) whichjet="Third leading "; 
      if (numbOfJets==4) whichjet="Fourth leading "; 
      title2=whichjet+"jet eta diff xsec distribution. "+title;
      jReco->SetTitle (title2.c_str());
      jReco->GetXaxis ()->SetTitle ("");
      if (!isMu) jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d#eta");
      if (isMu) jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d#eta");
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
      jReco->GetXaxis()->SetTitle("jet eta [GeV/c]");
      jReco->SetLineColor (kBlack); 
      jReco->SetTitle("");
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
    
      //pad1->SetBottomMargin (0.1);
    
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
      jRecoClone->GetXaxis ()->SetRangeUser (-5, 5);
      jRecoClone->GetYaxis ()->SetTitle ("Ratios");
      jRecoClone->GetXaxis ()->SetTitle("jet eta [GeV/c]");
      jRecoClone->GetXaxis ()->SetTitleSize(0.06);
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

      TF1 *f = new TF1("f","1",-2.4,2.4);
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
      string title3= s+"JETETAXSEC"+method+"_"+num.str()+supplabel+".pdf";
      //c->cd ();
      c->Print(title3.c_str());

      TCanvas *err = new TCanvas ("err", "err", 1000, 700);
      err->cd ();
      staterror->SetStats (0);
      staterror->GetXaxis()->SetTitle("Jet Eta bin");
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

      string title4= s+"JETETAerror"+method+"_"+num.str()+supplabel+".pdf";
      err->Print(title4.c_str());

      TCanvas *N =new TCanvas ("jet eta response matrix", "jet eta response matrix", 1000, 700);
      N->cd ();
      jMatx->SetStats (0);
      gPad->SetLogz (1);

      gPad->SetRightMargin(0.15);
      jMatx->GetZaxis()->SetRangeUser(0.01,1);
      jMatx->GetXaxis()->SetTitle("Reconstructed jet eta [GeV/c]");
      jMatx->GetYaxis()->SetTitle("Generated jet eta [GeV/c]");
      jMatx->SetTitle("");
      gStyle->SetPalette (1);
      gStyle->SetPaintTextFormat ("5.3f");
      gStyle->SetNumberContours (999);
      jMatx->SetMarkerColor (kBlack);
      double entries=1.000/(double)jMatx->Integral();
      jMatx->Scale(entries);
      jMatx->Draw ("COLZ,text");
      string title5= s+"JetEtaUnfoMatrix"+method+"_"+num.str()+supplabel+".pdf";
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
      
  ///////////
  ///SAve unfolded distribution
  /////////// 

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

   if (!bayesianTests){
    TCanvas *moduloD= new TCanvas ("moduloD", "moduloD", 1000, 700);
    moduloD->cd ();
    gPad->SetLogy (1);
    modD->SetStats (111111);
    modD->GetXaxis()->SetTitle("K Parameters");
    modD->GetYaxis()->SetTitle("Value");
    modD->SetLineColor(kRed);
    modD->Draw();
    string whichjet="";
    if (numbOfJets==1) whichjet="Leading "; 
    if (numbOfJets==2) whichjet="Second leading "; 
    if (numbOfJets==3) whichjet="Third leading "; 
    if (numbOfJets==4) whichjet="Fourth leading "; 
    string title7=s+"moduloD_jetEta_"+whichjet+".pdf";
    moduloD->Print(title7.c_str()); 
  }     

   double unfarea=jReco->Integral()/4890.0;
   cout<<"Your unfolding has an integral value of "<<unfarea<<endl;
   
   if (activateXSSuperseding){
     if (!isMu) {
       cout<<"Rescaled to "<<XSElectron[numbOfJets-1]<<endl;
       jReco->Scale(XSElectron[numbOfJets-1]/unfarea);
     }
     if (isMu) {
       cout<<"Rescaled to "<<XSMuon[numbOfJets-1]<<endl;
       jReco->Scale(XSMuon[numbOfJets-1]/unfarea);
     }
   }

  if (saveFile){
    TFile* w = new TFile(filename.c_str(), "UPDATE");
    w->cd();

    if (numbOfJets==1) {
      TH1F *jReco_leadingeta= (TH1F*) jReco->Clone("jReco");
      jReco_leadingeta->SetName("jReco_leadingeta");
      jReco_leadingeta->Write();
    }
    if (numbOfJets==2) {
      TH1F *jReco_subleadingeta= (TH1F*) jReco->Clone("jReco");
      jReco_subleadingeta->SetName("jReco_subleadingeta");
      jReco_subleadingeta->Write();
    }
    if (numbOfJets==3) {
      TH1F *jReco_subsubleadingeta= (TH1F*) jReco->Clone("jReco");
      jReco_subsubleadingeta->SetName("jReco_subsubleadingeta");
      jReco_subsubleadingeta->Write();
    }
    if (numbOfJets==4) {
      TH1F *jReco_subsubsubleadingeta= (TH1F*) jReco->Clone("jReco");
      jReco_subsubsubleadingeta->SetName("jReco_subsubsubleadingeta");
      jReco_subsubsubleadingeta->Write();
    }

    w->Close();
  }  
}
