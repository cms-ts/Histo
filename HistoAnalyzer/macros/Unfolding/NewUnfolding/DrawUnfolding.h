//////////////////////
//Draw options
///////////////////////

TCanvas* drawPlots(TH1D *jReco,TH1D* jData, TH1D *jTrue, TH1D* jMCreco, int numbOfJetsSelected, string whichtype, string whichalgo, int k){
  TCanvas *c=new TCanvas("c", "c", 1000, 700);
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
  string title2=whichjet+"jet pT diff xsec distribution. "+whichtype;
  jReco->SetTitle (title2.c_str());
  jReco->GetXaxis ()->SetTitle ("");
  if (!isMu) jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow e^{+}e^{-}}) d #sigma/d p_{T}");
  if (isMu) jReco->GetYaxis ()->SetTitle ("(1/#sigma_{Z #rightarrow #mu^{+}#mu^{-}}) d #sigma/d p_{T}");
  jReco->SetMarkerStyle (20);
  jData->SetMarkerStyle (21);
  jData->SetLineColor(kGreen);
  
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
  jReco->Draw("EP");        //risultato dell'unfolding
  
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
  
  TH1D *jRecoClone= (TH1D*) jReco->Clone("jReco");
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
  jRecoClone->Draw();
  
  TH1D *jDataClone= (TH1D*) jReco->Clone("jReco");
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
  string title3= s+"JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+".pdf";
  num.str("");
  c->cd ();
  c->Print(title3.c_str());
  
  if (whichalgo == "SVD"){
    TCanvas *moduloD= new TCanvas ("moduloD", "moduloD", 1000, 700);
    moduloD->cd ();
    gPad->SetLogy (1); modD->SetStats (111111);
    modD->GetXaxis()->SetTitle("K Parameters"); modD->GetYaxis()->SetTitle("Value");
    modD->SetLineColor(kRed);
    modD->Draw(); 
    string title= s+"JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+"_moduloD.pdf";
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
  string titlerr= s+"JET"+whichtype+"_"+whichalgo+"_k"+num.str()+"_"+whichjetname+"_errors.pdf";
  errCanv->Print(titlerr.c_str()); 

  return c;
}
