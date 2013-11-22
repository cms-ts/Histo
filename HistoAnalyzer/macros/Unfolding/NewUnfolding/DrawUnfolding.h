//////////////////////
//Draw options
///////////////////////
void loopEntries(TH1D *jData){
  for (int p=0;p<jData->GetNbinsX();p++){
    cout<<"Bin "<<p+1<<" has "<<jData->GetBinContent(p+1)<<" and error "<<jData->GetBinError(p+1)<<endl;;
  }
}

TCanvas* drawPlots(TH1D *jReco,TH1D* jData, TH1D *jTrue, TH1D* jMCreco, TH2D* jMatx, int numbOfJetsSelected, string whichtype, string whichalgo, int k){
  TCanvas *C=new TCanvas("C", "C", 1000, 700);
  C->cd ();
  TPad *pad1 = new TPad ("pad1", "pad1",0.01,0.33,0.99,0.99);
  pad1->Draw ();
  pad1->cd ();
  gPad->SetLogy (1);
  pad1->SetTopMargin(0.1);
  pad1->SetBottomMargin(0.01);
  pad1->SetRightMargin(0.1);
  pad1->SetFillStyle(0);
 
  TH1D *jRecoNorm= (TH1D*) jReco->Clone("jReco");
  jRecoNorm->SetName("jRecoNorm");   
  TH1D *jTrueNorm= (TH1D*) jTrue->Clone("jTrue");
  jTrueNorm->SetName("jRecoNorm");   
  TH1D *jMCrecoNorm= (TH1D*) jMCreco->Clone("jMCreco");
  jMCrecoNorm->SetName("jMCRecoNorm");
  TH1D *jDataNorm= (TH1D*) jData->Clone("jData");
  jDataNorm->SetName("jDataNorm");      

 //Normalizing output
  jRecoNorm->Scale(1./jReco->Integral());             
  jTrueNorm->Scale(1./jTrue->Integral());
  jMCrecoNorm->Scale(1./jMCreco->Integral());
  jDataNorm->Scale(1./jData->Integral());
 
  string whichjet="";
  if (numbOfJetsSelected==1) whichjet="Leading "; 
  if (numbOfJetsSelected==2) whichjet="Second leading "; 
  if (numbOfJetsSelected==3) whichjet="Third leading "; 
  if (numbOfJetsSelected==4) whichjet="Fourth leading "; 
  string title2=whichjet+"jet pT diff xsec distribution. "+whichtype;
  jRecoNorm->SetTitle (title2.c_str());
  jRecoNorm->GetXaxis ()->SetTitle ("");
  if (!isMu) jRecoNorm->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d p_{T}");
  if (isMu) jRecoNorm->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d p_{T}");
  jRecoNorm->SetMarkerStyle (20);
  jDataNorm->SetMarkerStyle (21);
  jDataNorm->SetLineColor(kGreen);
  
  cout<<"area jReco:"<<jReco->Integral()<<" and MCreco "<<jMCreco->Integral()<<endl;
  
  jRecoNorm->SetMarkerStyle (20);
  jMCrecoNorm->SetStats(0);
  jDataNorm->SetStats(0);
  jTrueNorm->SetStats(0);
  jRecoNorm->SetStats(0);
  if (whichtype=="Multiplicity") jRecoNorm->GetXaxis()->SetTitle("jet Multiplicity");
  if (whichtype=="Pt") jRecoNorm->GetXaxis()->SetTitle("jet  pT [GeV]"); 
  if (whichtype=="Eta") jRecoNorm->GetXaxis()->SetTitle("jet  Eta");
  jRecoNorm->SetLineColor (kBlack); 
  
  jRecoNorm->SetLabelSize(0.0);
  jRecoNorm->GetXaxis()->SetTitleSize(0.00);
  jRecoNorm->GetYaxis()->SetLabelSize(0.07);
  jRecoNorm->GetYaxis()->SetTitleSize(0.08);
  jRecoNorm->GetYaxis()->SetTitleOffset(0.76);
  jRecoNorm->SetTitle("");
  jRecoNorm->Draw("EP");        //risultato dell'unfolding
  
  jMCrecoNorm->SetLineColor (kBlue + 1);
  jMCrecoNorm->SetLineStyle (2);
  jMCrecoNorm->SetLineWidth (2); 
  if (!pythiaCheck) jMCrecoNorm->Draw("HISTSAMES");
  jTrueNorm->SetLineColor (kRed);
  jTrueNorm->SetLineWidth (2);
  jTrueNorm->Draw ("HISTSAME");
  jDataNorm->SetLineColor(kGreen+1);
  pad1->SetLogy (1);
  jDataNorm->SetMarkerStyle (4);
  jDataNorm->SetMarkerColor(kGreen+1);
  jDataNorm->SetStats(0);
  jDataNorm->Draw("EPSAME");
  if (!pythiaCheck || !identityCheck) jMCrecoNorm->Draw("EPSAME");
  
  //pad1->SetBottomMargin (0.1);
  
  TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
  legend_d->SetFillColor (0);
  legend_d->SetFillStyle (0);
  legend_d->SetBorderSize (0);
  legend_d->AddEntry (jRecoNorm, "Data Unfolded", "P20");
  legend_d->AddEntry (jTrueNorm, "MC truth", "L");
  if (!pythiaCheck || !identityCheck) legend_d->AddEntry (jMCrecoNorm, "MC reco", "L");
  legend_d->AddEntry(jDataNorm,"Data Folded","P20");
  legend_d->Draw ("same");
  
  TLatex *latexLabel=CMSPrel(4.890,""); // make fancy label
  latexLabel->Draw("same");   
  pad1->Update();      
  C->cd ();
  
  TPad *pad2 = new TPad ("pad2", "pad2",0.01,0.01,0.99,0.32);
  pad2->SetTopMargin (0);
  pad2->Draw ();
  pad2->cd ();
  pad2->SetTopMargin(0.01);
  pad2->SetBottomMargin(0.3);
  pad2->SetRightMargin(0.1);
  pad2->SetFillStyle(0);
  
  TH1D *jRecoClone= (TH1D*) jRecoNorm->Clone("jRecoNorm");
  jRecoClone->SetName("jRecoClone");      
  jRecoClone->SetStats(0);
  jRecoClone->GetXaxis ()->SetLabelSize (0.1);
  jRecoClone->GetYaxis ()->SetLabelSize (0.08);
  jRecoClone->Sumw2();
  jRecoClone->Divide(jTrueNorm);
  jRecoClone->SetMarkerStyle (6);
  jRecoClone->GetXaxis ()->SetLabelSize (0.06);
  jRecoClone->GetYaxis ()->SetLabelSize (0.06);
  jRecoClone->GetXaxis ()->SetTitleSize (0);
  jRecoClone->GetYaxis ()->SetTitleSize (0.06);
  jRecoClone->GetYaxis ()->SetTitleOffset (0.5);

  cout<<"Data for unfolding Uncertainties!"<<endl;
  cout<<"======================================"<<endl;
  for (int p=0;p<jRecoClone->GetNbinsX();p++){
    cout<<fabs(1.0000-jRecoClone->GetBinContent(p+1))<<endl;
  }
  cout<<"======================================"<<endl;

  jRecoClone->GetYaxis ()->SetRangeUser (0.5, 1.5);
  jRecoClone->GetYaxis ()->SetTitle ("Ratios");
  if (whichtype=="Multiplicity") jRecoClone->GetXaxis()->SetTitle("jet Multiplicity");
  else jRecoClone->GetXaxis()->SetTitle("jet  pT [GeV]"); 
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
  jRecoClone->Draw();
  
  TH1D *jDataClone= (TH1D*) jRecoNorm->Clone("jRecoNorm");
  jDataClone->SetName("jDataClone"); 
  jDataClone->Sumw2();
  jDataClone->Divide(jDataNorm);
  jDataClone->SetLineStyle (2); 
  jDataClone->SetMarkerSize (0);       
  jDataClone->SetLineWidth (0.05);
  jDataClone->SetLineColor(kViolet);
  jDataClone->Draw ("HISTSAME");
  jDataClone->SetLineWidth (0.1);
  
  TF1 *f = new TF1("f","1",-1000,1000);
  f->SetLineWidth(1);
  f->Draw("SAMES");
  
  TLegend *legend_w = new TLegend(0.197791, 0.736607, 0.394578, 0.9375);
  legend_w->SetFillColor (0);
  legend_w->SetFillStyle (0);
  legend_w->SetBorderSize (0);
  legend_w->AddEntry (jRecoClone, "Data Unfolded / MC truth", "P20");
  //legend_w->AddEntry (jMCRecoClone, "MC reco / MC truth", "L");
  legend_w->AddEntry (jDataClone, "Data Unfolded / Data Folded", "L");
  legend_w->Draw ("same");
  //pad2->Update();
  stringstream num;
  num<<k;
  string whichjetname="";
  if (numbOfJetsSelected==1) whichjetname="Leading"; 
  if (numbOfJetsSelected==2) whichjetname="Second leading "; 
  if (numbOfJetsSelected==3) whichjetname="Third leading "; 
  if (numbOfJetsSelected==4) whichjetname="Fourth leading ";
  string title3= s+"/"+whichtype+"/JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+".pdf";   
  if (identityCheck) title3= s+"/IdentityTest/JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+".pdf";
  if (pythiaCheck) title3= s+"/PowhegTest/JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+".pdf";      
  num.str("");
  cout<<title3<<endl;
  C->Print(title3.c_str());

  if (whichalgo == "SVD"){
    TCanvas *moduloD= new TCanvas ("moduloD", "moduloD", 1000, 700);
    moduloD->cd ();
    gPad->SetLogy (1); modD->SetStats (111111);
    modD->GetXaxis()->SetTitle("K Parameters"); modD->GetYaxis()->SetTitle("Value");
    modD->SetLineColor(kRed);
    modD->Draw(); 
    string title= s+"/"+whichtype+"/JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+"_moduloD.pdf";
    moduloD->Print(title.c_str()); 
  }
  TCanvas *errCanv= new TCanvas ("errCanv", "errCanv", 1000, 700);
  errCanv->cd ();
  gPad->SetLogy (1); errors->SetStats (111111);
  errors->GetXaxis()->SetTitle("Bin"); errors->GetYaxis()->SetTitle("Error");
  errors->SetLineColor(kRed);
  errors->Draw(); 
  errorstat->Draw("SAMES");
  TLegend *legend_ = new TLegend(0.697791, 0.736607, 0.894578, 0.9375);
  legend_->SetFillColor (0); legend_w->SetFillStyle (0); legend_w->SetBorderSize (0);
  legend_->AddEntry (errors, "Unfolding error", "L");
  legend_->AddEntry (errorstat, "Stat Error", "L");
  legend_->Draw("");
  string titlerr= s+"/"+whichtype+"/JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+"_errors.pdf";
  errCanv->Print(titlerr.c_str()); 

  TCanvas *N =new TCanvas ("N jet response matrix", "N jet response matrix", 1000, 700);
  N->cd ();
  jMatx->SetStats (0);
  gPad->SetLogz (1);
  gPad->SetRightMargin(0.15);
  jMatx->SetTitle("");
  jMatx->GetXaxis()->SetTitle("Reconstructed # of Jets");
  jMatx->GetYaxis()->SetTitle("Generated # of Jets");
  gStyle->SetPalette (1);
  gStyle->SetPaintTextFormat ("5.0f");
  gStyle->SetNumberContours (999);
  jMatx->SetMarkerColor (kBlack);
  //double entries=1.000/(double)jMatx->Integral();
  //jMatx->Scale(entries);
  jMatx->Draw ("COLZ,text");
  string titlem= s+"/"+whichtype+"/JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+"_matrix.pdf";
  N->Print(titlem.c_str());

  TCanvas *efficiency = new TCanvas ("efficiency", "efficiency", 1000, 700);
  efficiency->cd ();
  gPad->SetLogy (1);
  gStyle->SetOptStat(111111);
  efficiencycorrectionsmc->GetXaxis()->SetTitle("Coefficients");
  efficiencycorrectionsmc->GetYaxis()->SetTitle("#");
  efficiencycorrectionsmc->SetLineColor(kRed);
  efficiencycorrectionsmc->Draw();
  efficiencycorrections->SetLineColor(kBlack);
  efficiencycorrections->Draw("SAME");
  
  TLegend *legend_eff = new TLegend (0.23494, 0.696429, 0.431727, 0.895833);
  legend_eff->SetFillColor (0);
  legend_eff->SetFillStyle (0);
  legend_eff->SetBorderSize (0);
  legend_eff->AddEntry (efficiencycorrectionsmc, "Montecarlo", "L");
  legend_eff->AddEntry (efficiencycorrections, "Data", "L");
  legend_eff->Draw ("same");
  string titleeff= s+"/"+whichtype+"/JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+"_efficiencies.pdf";
  efficiency->Print(titleeff.c_str());

  return C;
}

void performCrossChecks(TH1D *jReco,TH1D* jData, TH1D *jTrue, TH1D* jTrueMatched, TH1D* jMCreco, TH2D* jMatx, int numbOfJetsSelected, string whichtype, string whichalgo, int k, TH1D *jRecoMatched, TH1D *jRecoAnne){
  TCanvas *C=new TCanvas("C", "C", 1000, 700);
  C->cd ();
  TPad *pad1 = new TPad ("pad1", "pad1",0.01,0.33,0.99,0.99);
  pad1->Draw ();
  pad1->cd ();
  gPad->SetLogy (1);
  pad1->SetTopMargin(0.1);
  pad1->SetBottomMargin(0.01);
  pad1->SetRightMargin(0.1);
  pad1->SetFillStyle(0);

  ///// Check 2D projection and Rivet
  TH1D *projection=jMatx->ProjectionY();
  cout<<"MC rivet distribution"<<endl;
  loopEntries(jTrue);
  cout<<"GEN projection of the 2D matrix"<<endl;
  loopEntries(projection);

  jTrue->SetMarkerStyle (20);
  if (whichtype=="Multiplicity") jTrue->GetXaxis()->SetTitle("jet Multiplicity");
  if (whichtype=="Pt") jTrue->GetXaxis()->SetTitle("jet  pT [GeV]"); 
  if (whichtype=="Ht") jTrue->GetXaxis()->SetTitle("HT [GeV]"); 
  if (whichtype=="Eta") jTrue->GetXaxis()->SetTitle("jet  Eta");
  jTrue->SetLineColor (kBlack); 
  projection->SetLineColor (kRed); 
  
  jTrue->GetXaxis()->SetTitleSize(0.00);
  jTrue->GetYaxis()->SetLabelSize(0.07);
  jTrue->GetYaxis()->SetTitleSize(0.08);
  jTrue->GetYaxis()->SetTitleOffset(0.76);
  jTrue->Draw("EP");        //risultato dell'unfolding
  projection->Draw("SAMES");

  //pad1->SetBottomMargin (0.1);
  
  TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
  legend_d->SetFillColor (0);
  legend_d->SetFillStyle (0);
  legend_d->SetBorderSize (0);
  legend_d->SetTextSize(0.03);
  legend_d->AddEntry (jTrue, "Rivet", "LP");
  legend_d->AddEntry (projection, "Proj. on GEN", "LP");
  legend_d->Draw ("same");
  
  TLatex *latexLabel=CMSPrel(4.890,""); // make fancy label
  latexLabel->Draw("same");   
  pad1->Update();      
  C->cd ();
  
  TPad *pad2 = new TPad ("pad2", "pad2",0.01,0.01,0.99,0.32);
  pad2->SetTopMargin (0);
  pad2->Draw ();
  pad2->cd ();
  pad2->SetTopMargin(0.01);
  pad2->SetBottomMargin(0.3);
  pad2->SetRightMargin(0.1);
  pad2->SetFillStyle(0);
  
  TH1D *jRecoClone= (TH1D*) jTrue->Clone("jTrue");
  jRecoClone->SetName("jTrue");      
  jRecoClone->SetStats(0);
  jRecoClone->GetXaxis ()->SetLabelSize (0.1);
  jRecoClone->GetYaxis ()->SetLabelSize (0.08);
  jRecoClone->Sumw2();
  jRecoClone->Divide(projection);
  jRecoClone->SetMarkerStyle (6);
  jRecoClone->GetXaxis ()->SetLabelSize (0.06);
  jRecoClone->GetYaxis ()->SetLabelSize (0.06);
  jRecoClone->GetXaxis ()->SetTitleSize (0);
  jRecoClone->GetYaxis ()->SetTitleSize (0.06);
  jRecoClone->GetYaxis ()->SetTitleOffset (0.5);
  jRecoClone->GetYaxis()->SetRangeUser(0.5,3);
  jRecoClone->Draw();

  TF1 *f = new TF1("f","1",-1000,1000);
  f->SetLineWidth(1);
  f->Draw("SAMES");
  
  stringstream num;
  num<<k;
  string whichjetname="";
  if (numbOfJetsSelected==1) whichjetname="Leading"; 
  if (numbOfJetsSelected==2) whichjetname="Second leading "; 
  if (numbOfJetsSelected==3) whichjetname="Third leading "; 
  if (numbOfJetsSelected==4) whichjetname="Fourth leading ";
  string title3= s+"/CrossChecks/"+whichtype+"/JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+".pdf";   
  cout<<title3<<endl;
  //C->Print(title3.c_str());
  
  ///////////////////
  // Method 1 Vs Method 3
  ///////////////////

  cout<<"jTrue/jTrueMatched Correction"<<endl;
  TH1D *correctionMethod1Over3=(TH1D*) jTrue->Clone("jTrue");
  correctionMethod1Over3->SetName("correctionMethod1Over3");
  correctionMethod1Over3->Divide(jTrueMatched);
  loopEntries(correctionMethod1Over3); 

  TCanvas *CC=new TCanvas("C", "C", 1000, 700);
  CC->Divide(2,1);
  CC->cd(1);

  TPad *pad11 = new TPad ("pad11", "pad11",0.01,0.33,0.99,0.99);
  pad11->Draw ();
  pad11->cd ();
  gPad->SetLogy (1);
  pad11->SetTopMargin(0.1);
  pad11->SetBottomMargin(0.01);
  pad11->SetRightMargin(0.1);
  pad11->SetFillStyle(0);

  jTrue->SetMarkerStyle (20);
  if (whichtype=="Multiplicity") jTrue->GetXaxis()->SetTitle("jet Multiplicity");
  if (whichtype=="Pt") jTrue->GetXaxis()->SetTitle("jet  pT [GeV]"); 
  if (whichtype=="Ht") jTrue->GetXaxis()->SetTitle("HT [GeV]"); 
  if (whichtype=="Eta") jTrue->GetXaxis()->SetTitle("jet  Eta");
  jTrue->SetLineColor (kBlack); 
  jTrueMatched->SetLineColor (kRed); 
  
  jTrue->GetXaxis()->SetTitleSize(0.00);
  jTrue->GetYaxis()->SetLabelSize(0.07);
  jTrue->GetYaxis()->SetTitleSize(0.08);
  jTrue->GetYaxis()->SetTitleOffset(0.76);
  jTrue->SetTitle("Bin by bin correction");
  jTrue->Draw("EP");        //risultato dell'unfolding
  jTrueMatched->Draw("SAMES");

  //pad1->SetBottomMargin (0.1);
  
  TLegend *legend_d2 = new TLegend (0.53494, 0.63, 0.731727, 0.83);
  legend_d2->SetFillColor (0);
  legend_d2->SetFillStyle (0);
  legend_d2->SetBorderSize (0);
  legend_d2->SetTextSize(0.03);
  legend_d2->AddEntry (jTrue, "Absolute MC Truth", "LP");
  legend_d2->AddEntry (jTrueMatched, "Matched MC Truth", "L");
  legend_d2->Draw ("same");
  
  TLatex *latexLabel2=CMSPrel(4.890,""); // make fancy label
  latexLabel2->Draw("same");   
  pad11->Update();      
  CC->cd (1);
  
  TPad *pad21 = new TPad ("pad21", "pad21",0.01,0.01,0.99,0.32);
  pad21->SetTopMargin (0);
  pad21->Draw ();
  pad21->cd ();
  pad21->SetTopMargin(0.01);
  pad21->SetBottomMargin(0.3);
  pad21->SetRightMargin(0.1);
  pad21->SetFillStyle(0);
  
  TH1D *jRecoClone2= (TH1D*) jTrue->Clone("jTrue");
  jRecoClone2->SetName("jTrue");      
  jRecoClone2->SetStats(0);
  jRecoClone2->GetXaxis ()->SetLabelSize (0.1);
  jRecoClone2->GetYaxis ()->SetLabelSize (0.08);
  jRecoClone2->Sumw2();
  jRecoClone2->Divide(jTrueMatched);
  jRecoClone2->SetMarkerStyle (6);
  jRecoClone2->GetXaxis ()->SetLabelSize (0.06);
  jRecoClone2->GetYaxis ()->SetLabelSize (0.06);
  jRecoClone2->GetXaxis ()->SetTitleSize (0);
  jRecoClone2->GetYaxis ()->SetTitleSize (0.06);
  jRecoClone2->GetYaxis ()->SetTitleOffset (0.5);
  jRecoClone2->GetYaxis()->SetRangeUser(0.9,2.5);
  jRecoClone2->Draw();

  f->Draw("SAMES");
  CC->cd(2);

  TPad *pad12 = new TPad ("pad12", "pad12",0.01,0.33,0.99,0.99);
  pad12->Draw ();
  pad12->cd ();
  gPad->SetLogy (1);
  pad12->SetTopMargin(0.1);
  pad12->SetBottomMargin(0.01);
  pad12->SetRightMargin(0.1);
  pad12->SetFillStyle(0);
  cout<<whichtype<<endl;
  jReco->SetMarkerStyle (14);
  if (whichtype=="Multiplicity") jReco->GetXaxis()->SetTitle("jet Multiplicity");
  if (whichtype=="Pt") jReco->GetXaxis()->SetTitle("jet  pT [GeV]"); 
  if (whichtype=="Ht") jReco->GetXaxis()->SetTitle("HT [GeV]"); 
  if (whichtype=="Eta") jReco->GetXaxis()->SetTitle("jet  Eta");
  jReco->SetLineColor (kBlack); 
  jRecoMatched->SetLineColor (kRed); 
  
  //jReco->GetXaxis()->SetTitleSize(0.00);
  //jReco->GetYaxis()->SetLabelSize(0.07);
  //jReco->GetYaxis()->SetTitleSize(0.08);
  //jReco->GetYaxis()->SetTitleOffset(0.76);
  //jReco->SetTitle("");

  //pad1->SetBottomMargin (0.1);    

  //Correggiamo histo
  ////

  TH1D *jRecoCorrected= (TH1D*) jReco->Clone("jReco");
  jRecoCorrected->SetName("jRecoCorrected"); 
  
  for (int p=0;p<jReco->GetNbinsX();p++){
    jRecoCorrected->SetBinContent(p+1,jRecoMatched->GetBinContent(p+1)*correctionMethod1Over3->GetBinContent(p+1) );
  }
  jReco->SetTitle("Comparison on different unfolding strategies");

  //jReco->SetMarkerSize(1);
  //jReco->SetMarkerStyle(1);
  //jReco->SetTitle("Clos.test Method I and III");
  jReco->Draw("EP");        //risultato dell'unfolding
  
  jRecoMatched->SetLineColor(kGreen);
  //jRecoMatched->Draw("SAMES");
  jRecoCorrected->SetLineStyle(4);
  jRecoCorrected->SetLineColor(kRed);
  jRecoCorrected->Draw("HISTSAMES");
  jRecoAnne->SetLineColor(kBlue);
  jRecoAnne->SetLineStyle(2);
  jRecoAnne->Draw("HISTSAMES");

  TLegend *legend_d3 = new TLegend (0.53494, 0.63, 0.731727, 0.83);
  legend_d3->SetFillColor (0);
  legend_d3->SetFillStyle (0);
  legend_d3->SetBorderSize (0);
  legend_d3->SetTextSize(0.03);
  legend_d3->AddEntry (jReco, "Method 1 (Reference)", "LP");
  //legend_d3->AddEntry (jRecoMatched, "Method 1 ", "LP");
  legend_d3->AddEntry (jRecoCorrected, "Method 2 + bin-by-bin", "L");
  legend_d3->AddEntry (jRecoAnne, "Method 3", "L");
  legend_d3->Draw ("same");
  TLatex *latexLabel3=CMSPrel(4.890,""); // make fancy label
  latexLabel3->Draw("same");   
 

  ////////////////

  CC->cd (2);
 
  TPad *pad31 = new TPad ("pad31", "pad31",0.01,0.01,0.99,0.32);
  pad31->SetTopMargin (0);
  pad31->Draw ();
  pad31->cd ();
  pad31->SetTopMargin(0.01);
  pad31->SetBottomMargin(0.3);
  pad31->SetRightMargin(0.1);
  pad31->SetFillStyle(0);
   
  TH1D *jRecoClone3= (TH1D*) jReco->Clone("jRecoCorrected");
  jRecoClone3->SetName("jRecoClone3");      
  jRecoClone3->SetStats(0);
  jRecoClone3->GetXaxis ()->SetLabelSize (0.1);
  jRecoClone3->GetYaxis ()->SetLabelSize (0.08);
  jRecoClone3->Sumw2();
  jRecoClone3->Divide(jReco);
  jRecoClone3->SetMarkerStyle (6);
  jRecoClone3->SetLineColor(kRed);
  jRecoClone3->SetLineStyle(4);
  jRecoClone3->GetXaxis ()->SetLabelSize (0.06);
  jRecoClone3->GetYaxis ()->SetLabelSize (0.06);
  jRecoClone3->GetXaxis ()->SetTitleSize (0);
  jRecoClone3->GetYaxis ()->SetTitleSize (0.06);
  jRecoClone3->GetYaxis ()->SetTitleOffset (0.5);
  jRecoClone3->GetYaxis()->SetRangeUser(0.975,1.025);
  jRecoClone3->Draw("HIST");

  TH1D *jRecoClone4= (TH1D*) jRecoAnne->Clone("jRecoAnne");
  jRecoClone4->SetName("jRecoClone4");      
  jRecoClone4->Divide(jReco);
  jRecoClone4->SetLineColor(kBlue);
  jRecoClone4->Draw("HISTSAMES");

  //  f->Draw("SAMES");
  

  string title4= s+"/CrossChecks/"+whichtype+"/JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+"_ratioTrueMatched.pdf";   
  num.str("");
  cout<<title4<<endl;
  CC->Print(title4.c_str());

  return ;
  
}
