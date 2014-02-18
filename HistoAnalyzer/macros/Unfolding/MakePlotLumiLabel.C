TLatex* CMSPrel(Float_t Lumi,TString _decaychannel){
  
  TLatex *latexLabel = new TLatex();
  latexLabel->SetTextSize(0.0405);
  latexLabel->SetTextFont(42);
  latexLabel->SetLineWidth(2);
  latexLabel->SetNDC();

  latexLabel->DrawLatex(0.25,0.35,"CMS Preliminary");
  latexLabel->DrawLatex(0.25,0.30,"#sqrt{s} = 7 TeV  #int Ldt = 4.890 fb^{-1}"); 
  latexLabel->DrawLatex(0.25,0.25,"anti-k_{T} (R = 0.5) PF Jets > 30 GeV");
  latexLabel->DrawLatex(0.25,0.08,_decaychannel);


  //return latexLabel;
}

TLatex* CMSPrel(Float_t Lumi,TString _decaychannel,double x, double y){

  TLatex *latexLabel = new TLatex();
  latexLabel->SetTextSize(0.0475);
  latexLabel->SetTextFont(42);
  latexLabel->SetLineWidth(2);
  latexLabel->SetNDC();

  latexLabel->DrawLatex(x,y,"anti-k_{T} (R = 0.5) Jets");
  latexLabel->DrawLatex(x,y-0.06,"p_{T}^{jet} > 30 GeV, |#eta^{jet}| < 2.4");
  latexLabel->DrawLatex(x,y-0.12,_decaychannel);

  TLatex *latexLabel2 = new TLatex();
  latexLabel2->SetTextSize(0.0405);
  latexLabel2->SetTextFont(42);
  latexLabel2->SetLineWidth(2);
  latexLabel2->SetNDC();

  latexLabel2->DrawLatex(0.16,0.965,"CMS Preliminary");
  latexLabel2->DrawLatex(0.16,0.92,"#sqrt{s} = 7 TeV L_{int} = 4.9 fb^{-1}");
}
