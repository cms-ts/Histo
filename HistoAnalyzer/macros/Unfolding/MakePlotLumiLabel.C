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
  latexLabel->SetTextSize(0.0405);
  latexLabel->SetTextFont(42);
  latexLabel->SetLineWidth(2);
  latexLabel->SetNDC();

  latexLabel->DrawLatex(x,y,"CMS Preliminary");
  latexLabel->DrawLatex(x,y-0.05,"#sqrt{s} = 7 TeV #int Ldt = 4.890 fb^{-1}");
  latexLabel->DrawLatex(x,y-0.11,"anti-k_{T} (R = 0.5) PF Jets > 30 GeV ");
  latexLabel->DrawLatex(x,y-0.16,_decaychannel);

}
