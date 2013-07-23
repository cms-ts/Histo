double returnJERCorrection(double jetEta, double jetPt, double jetPtgen, int systematics){

  cout<<"jetEta "<<jetEta<<" jetPt "<<jetPt<<" jetPtgen "<<jetPtgen<<" systematics "<<systematics<<endl;
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
  
  cout<<" newJetRecoCIndex "<<newJetRecoCIndex<<" correctionFactor  "<<correctionFactor[newJetRecoCIndex]<<" -systDown[newJetRecoCIndex]) "<<-systDown[newJetRecoCIndex]<<" systUp[newJetRecoCIndex] "<<systUp[newJetRecoCIndex]<<endl;
  
  if (systematics==-1) newJetRecoPt=jetPtgen+(correctionFactor[newJetRecoCIndex]-systDown[newJetRecoCIndex])*(jetPt-jetPtgen);
  if (systematics==1) newJetRecoPt=jetPtgen+(correctionFactor[newJetRecoCIndex]+systUp[newJetRecoCIndex])*(jetPt-jetPtgen);
  if (systematics==0) newJetRecoPt=jetPtgen+correctionFactor[newJetRecoCIndex]*(jetPt-jetPtgen);
  
  cout<<" newJetRecoPt "<<newJetRecoPt<<endl;
  
  if (newJetRecoPt>0.0) return newJetRecoPt;
  return -9999;
}
