double returnJERCorrection(double jetEta, double jetPt, int systematics){

  if (systematics==-9999) return jetPt; //deactivate JER smering
  if (jetPt==-9999) return -9999;

  //cout<<"jetEta "<<jetEta<<" jetPt "<<jetPt<<" systematics "<<systematics<<endl;
  int newJetRecoCIndex=0;
  double newJetRecoPt=0.0;

  double correctionFactor[5]={1.052,1.057,1.096,1.134,1.288};
  double systUp[5]={0.062,0.056,0.063,0.087,0.155};
  double systDown[5]={0.061,0.055,0.062,0.085,0.153};


  if ( fabs(jetEta)<=0.5 ) newJetRecoCIndex=0;
  if ( fabs(jetEta)>0.5 && fabs(jetEta)<=1.1 )  newJetRecoCIndex=1;
  if ( fabs(jetEta)>1.1 && fabs(jetEta)<=1.7 )  newJetRecoCIndex=2;
  if ( fabs(jetEta)>1.7 && fabs(jetEta)<=2.3 )  newJetRecoCIndex=3;
  if ( fabs(jetEta)>2.3 && fabs(jetEta)<=3.0 )  newJetRecoCIndex=4;

  //cout<<" newJetRecoCIndex "<<newJetRecoCIndex<<" correctionFactor  "<<correctionFactor[newJetRecoCIndex]<<" -systDown[newJetRecoCIndex]) "<<-systDown[newJetRecoCIndex]<<" systUp[newJetRecoCIndex] "<<systUp[newJetRecoCIndex]<<endl;

  //smearing
  TRandom3 *r = new TRandom3(0); 
  
  double sigmaMC=7.726;
  double sigmaPt;
  if (systematics==0) sigmaPt=sqrt( (pow(correctionFactor[newJetRecoCIndex],2)-1)*sigmaMC);
  if (systematics==1) sigmaPt=sqrt( (pow(correctionFactor[newJetRecoCIndex]+systUp[newJetRecoCIndex],2)-1)*sigmaMC);
  if (systematics==-1) sigmaPt=sqrt( fabs((pow(correctionFactor[newJetRecoCIndex]-systDown[newJetRecoCIndex],2)-1)*sigmaMC));

  double numberRandom = r->Gaus(0,sigmaPt);    // use mu = 0, sigma = sigmaMC;
  newJetRecoPt=jetPt+numberRandom;
  //cout<<"Sigma Pt "<<sigmaPt<<" numberRandom "<<numberRandom<<" newJetRecoPt "<<newJetRecoPt<<endl;
  delete r;
  if (newJetRecoPt>0.0) return newJetRecoPt;
  return -9999;
}

double returnJERCorrectionSimplifiedFormula(double jetEta, double jetPt, double jetPtGen, int systematics){

  //It works using -> pT->max[0.,pTgen+c*(pT–pTgen)], 
  if (jetPtGen<0 || jetPtGen==9999) {
    return jetPt; //No reco, no smering
  }
  if (jetPt==-9999) return -9999; //No reco, no smering
  if (jetPt==0) return 0.0; //No reco, no smering

  if (systematics==-9999) return jetPt; //deactivate JER smering
  if (jetPt==-9999) return -9999;

  //cout<<"jetEta "<<jetEta<<" jetPt "<<jetPt<<" jet pt gen "<<jetPtGen <<" systematics "<<systematics<<endl;
  int newJetRecoCIndex=0;
  double newJetRecoPt=0.0;

  double correctionFactor[5]={1.052,1.057,1.096,1.134,1.288};
  double systUp[5]={0.062,0.056,0.063,0.087,0.155};
  double systDown[5]={0.061,0.055,0.062,0.085,0.153};


  if ( fabs(jetEta)<=0.5 ) newJetRecoCIndex=0;
  if ( fabs(jetEta)>0.5 && fabs(jetEta)<=1.1 )  newJetRecoCIndex=1;
  if ( fabs(jetEta)>1.1 && fabs(jetEta)<=1.7 )  newJetRecoCIndex=2;
  if ( fabs(jetEta)>1.7 && fabs(jetEta)<=2.3 )  newJetRecoCIndex=3;
  if ( fabs(jetEta)>2.3 && fabs(jetEta)<=3.0 )  newJetRecoCIndex=4;

  //cout<<" newJetRecoCIndex "<<newJetRecoCIndex<<" correctionFactor  "<<correctionFactor[newJetRecoCIndex]<<" -systDown[newJetRecoCIndex]) "<<-systDown[newJetRecoCIndex]<<" systUp[newJetRecoCIndex] "<<systUp[newJetRecoCIndex]<<endl;

 //It works using -> pT->max[0.,pTgen+c*(pT–pTgen)], 
   if (systematics==0) newJetRecoPt=jetPtGen+correctionFactor[newJetRecoCIndex]*(jetPt-jetPtGen);
   if (systematics==1) newJetRecoPt=jetPtGen+(correctionFactor[newJetRecoCIndex]+systUp[newJetRecoCIndex])*(jetPt-jetPtGen);
   if (systematics==-1) newJetRecoPt=jetPtGen+(correctionFactor[newJetRecoCIndex]-systDown[newJetRecoCIndex])*(jetPt-jetPtGen);

  //cout<<"net Jet pt "<<newJetRecoPt<<endl;
  if (newJetRecoPt>0.0) return newJetRecoPt;
  return -9999;
}
