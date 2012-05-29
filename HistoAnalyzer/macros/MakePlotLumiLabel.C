TLatex* CMSPrel(Float_t Lumi,TString _decaychannel){
  
  TLatex *latexLabel = new TLatex();
  latexLabel->SetTextSize(0.0275);
  latexLabel->SetTextFont(42);
  latexLabel->SetLineWidth(2);
  latexLabel->SetNDC();

  latexLabel->DrawLatex(0.25,0.35,"CMS SMP-VJ Preliminary");
  latexLabel->DrawLatex(0.25,0.30,"#sqrt{s} = 7 TeV"); 
  latexLabel->DrawLatex(0.25,0.25,"anti-k_{T} (R = 0.5) PF Jets ");
  latexLabel->DrawLatex(0.25,0.18,(TString)Form("#int Ldt = %.3f fb^{-1}",Lumi));  
  latexLabel->DrawLatex(0.25,0.13,"Z#rightarrow ee channel");
  latexLabel->DrawLatex(0.25,0.08,_decaychannel);


  //return latexLabel;
}
