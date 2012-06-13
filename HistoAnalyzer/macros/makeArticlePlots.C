#include "Unfolding/tdrstyle.C"
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include "Unfolding/MakePlotLumiLabel.C"
#include <TH2.h>
#include "TF1.h"
#include <TStyle.h>
#include <TCanvas.h>
#include "TRandom.h"
#include "TH1D.h"
#include "TFile.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include "TLatex.h"
#include <vector>
#include <iostream>
#include "tdrStyle.C"
#include <TROOT.h>
#include "TObject.h"
#include <iostream>
#include <sstream>
#include "TTree.h"
#include "TH2.h"
#include "THStack.h"
#include "TLatex.h"
#include <string.h>

TCanvas * plots;
string version="_v2_27";
//string s = "/afs/infn.it/ts/user/marone/html/ZJets/articlePlots/";
string s = "plotArticle"+version+"/";

void makeArticlePlots(){

  setTDRStyle();

  int whichjet=1;
  string plotpath="/gpfs/cms/data/2011/Uncertainties/";

  //string pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions"+version+".root";
  string pathFile="/gpfs/cms/data/2011/Unfolding/UnfoldedDistributions_v2_24.root";
  TFile *histof = TFile::Open(pathFile.c_str());
  plots = new TCanvas("plots","EB",400,20,1200,800);
  histof->cd("");
  TDirectory *dir=gDirectory;
  TList *mylist=(TList*)dir->GetListOfKeys();
  TIter iter(mylist);	
  // Use TIter::Next() to get each TObject mom owns.
  TObject* tobj = 0;
  string tmpname;

    plots->cd();
  int i=0; // solo di servizio quando debuggo...
  while ( (tobj = iter.Next()) ) {
    string name=tobj->GetName();
    string stringmatch;
    string systPathFile;
    if (whichjet==1) {
       stringmatch="jReco_leading";
       systPathFile = plotpath+"jet1PtFinalSyst"+version+".txt";}
    if (whichjet==2) {
       stringmatch="jReco_subleading";
       systPathFile = plotpath+"jet2PtFinalSyst"+version+".txt";}
    if (whichjet==3) {
       stringmatch="jReco_subsubleading";
       systPathFile = plotpath+"jet3PtFinalSyst"+version+".txt";}
    if (whichjet==4) {
       stringmatch="jReco_subsubsubleading";
       systPathFile = plotpath+"jet4PtFinalSyst"+version+".txt";}

    //Leading Jet Pt
    if(name==stringmatch){
      cout<<"processing histogram->"<<name<<endl;
      gPad->SetLogy(1);
      TH1D* leading;
      gDirectory->GetObject(name.c_str(),leading);
      TH1D* leadingSystematics;
      leadingSystematics=(TH1D*) leading->Clone("leading");

      // read from file ---------------------------------------------
      double dat;
      ifstream in;
      cout<< "reading ...  "<< systPathFile <<endl;
      in.open (systPathFile.c_str());
      //int l2 =0;
      std::vector<double> systTmp;
      while (1) {
	 in >> dat;
	 if (!in.good()) break;
	 systTmp.push_back(dat);
	 //l2++;  
      }    
      in.close();
      // ------------------------------------------------------------

      // double sysv_lead[15] ={5.90857,4.31947,4.07386,4.47094,4.83375,5.77636,5.59512,6.06586,5.76923,5.76923,5.76923,5.76923,5.76923,5.76923,5.76923}; //in %
//       double sysv_sublead[15]={9.31662,8.10951,5.86788,5.6427,5.2652,6.44753,7.49487,5.0571,10,10,10,10,10,10,10};
//       double sysv_subsublead[15]={10.6758,10.2108,8.77832,10.6999,7.89177,8.125,7.59494,11.3793,14.7929,14.7929,14.7929,14.7929,14.7929,14.7929,14.7929};	    
//       double sysv_subsubsublead[15]={16.3347,13.6889,15.7618,13.2791,21.0084,22.2222,5.17241,3.44828,26.2295,26.2295,26.2295,26.2295,26.2295,26.2295,26.2295};
      
       leadingSystematics->SetName("leadingSystematics"); 
      if ( systTmp.size()!= leadingSystematics->GetNbinsX())
	 cout<<"WRONG NUMBER OF BINS"<<endl;
       for (int i=0; i<=leadingSystematics->GetNbinsX();i++){
	  //cout<<"jetPt"<<whichjet<<" - syst = "<<leadingSystematics->GetBinError(i+1)<<endl;
	  //leadingSystematics->SetBinError(i+1,systTmp[i]*leadingSystematics->GetBinContent(i+1));
	  double err = sqrt( pow(leading->GetBinError(i+1),2) + pow(systTmp[i]*leadingSystematics->GetBinContent(i+1),2)); 
	  leadingSystematics->SetBinError(i+1,err);
       }
      
//       for (int i=0; i<=leadingSystematics->GetNbinsX();i++){
// 	cout<<leadingSystematics->GetBinError(i+1)<<endl;
// 	if (whichjet==1) leadingSystematics->SetBinError(i+1,0.01*sysv_lead[i]*leadingSystematics->GetBinContent(i+1));
// 	if (whichjet==2) leadingSystematics->SetBinError(i+1,0.01*sysv_sublead[i]*leadingSystematics->GetBinContent(i+1));
// 	if (whichjet==3) leadingSystematics->SetBinError(i+1,0.01*sysv_subsublead[i]*leadingSystematics->GetBinContent(i+1));
// 	if (whichjet==4) leadingSystematics->SetBinError(i+1,0.01*sysv_subsubsublead[i]*leadingSystematics->GetBinContent(i+1));
//       }

      leadingSystematics->SetLineColor(kBlack);
      leadingSystematics->SetMarkerStyle(20);
      leadingSystematics->SetFillStyle(3003);
      leadingSystematics->SetFillColor(kRed); 
      leadingSystematics->SetMarkerColor(kBlack);
      leadingSystematics->Draw("E3");
      leading->SetFillColor(kBlack);
      leading->SetFillStyle(3001);
      leading->Draw("E3SAMES");
      
      TLatex *latexLabel=CMSPrel(4.890,""); // make fancy label
      latexLabel->Draw("same");  
      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (leading, "Statistical Error", "F");
      legend_d->AddEntry (leadingSystematics, "Total Error", "F");
      legend_d->Draw ("same");
      
      string title1= s+"DifferentialX"+stringmatch+".pdf";
      cout<<title1<<endl;
      plots->Print(title1.c_str());
    }
    
    // Jet Multiplicity
    if(name=="JetMultiplicityUnfolded"){
      gPad->SetLogy(1);
      TH1D* leading;
      gDirectory->GetObject(name.c_str(),leading);
      TH1D* leadingSystematics;
      leadingSystematics=(TH1D*) leading->Clone("leading");
      systPathFile = plotpath+"jetMultFinalSyst"+version+".txt";

      // read from file ---------------------------------------------
      ifstream inM;
      cout<< "reading ...  "<< systPathFile <<endl;
      inM.open (systPathFile.c_str());
      //int l2 =0;
      std::vector<double> systTmpM;
      while (1) {
	 inM >> dat;
	 if (!inM.good()) break;
	 systTmpM.push_back(dat);
	 //l2++;  
      }    
      inM.close();
      // ------------------------------------------------------------
      //double sysv[6] ={1.01766,4.83302,7.63652,9.28372,14.0438,10.5528}; //in %
      
      leadingSystematics->SetName("leadingSystematics");
      if ( systTmpM.size()!= leadingSystematics->GetNbinsX())
	 cout<<"WRONG NUMBER OF BINS"<<endl;
      for (int i=0; i<=leadingSystematics->GetNbinsX();i++){
	 //cout<<"jetMulti - syst = "<<leadingSystematics->GetBinError(i+1)<<endl;	 
	 double err = sqrt( pow(leading->GetBinError(i+1),2) + pow(systTmpM[i]*leadingSystematics->GetBinContent(i+1),2)); 
	leadingSystematics->SetBinError(i+1,err);
      }
      leadingSystematics->SetLineColor(kBlack);
      leadingSystematics->SetMarkerStyle(20);
      leadingSystematics->SetFillStyle(3003);
      leadingSystematics->SetFillColor(kRed); 
      leadingSystematics->SetMarkerColor(kBlack);
      leadingSystematics->Draw("E3");
      leading->SetFillColor(kBlack);
      leading->SetFillStyle(3001);
      leading->Draw("E3SAMES");
      
      TLatex *latexLabel=CMSPrel(4.890,""); // make fancy label
      latexLabel->Draw("same");  
      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (leading, "Statistical Error", "F");
      legend_d->AddEntry (leadingSystematics, "Total Error", "F");
      legend_d->Draw ("same");
      
      string title1= s+"DifferentialXSJetMultiplicity.pdf";
      cout<<title1<<endl;
      plots->Print(title1.c_str());
    }
    
    
    //////////////////////
    /// Eta
    ////////////////////
    
    if (whichjet==1) {
       stringmatch="jReco_leadingeta";
       systPathFile = plotpath+"jet1EtaFinalSyst"+version+".txt";}
    if (whichjet==2) {
       stringmatch="jReco_subleadingeta";
       systPathFile = plotpath+"jet2EtaFinalSyst"+version+".txt";}
    if (whichjet==3) {
       stringmatch="jReco_subsubleadingeta";
       systPathFile = plotpath+"jet3EtaFinalSyst"+version+".txt";}
    if (whichjet==4) {
       stringmatch="jReco_subsubsubleadingeta";
       systPathFile = plotpath+"jet4EtaFinalSyst"+version+".txt";}
    
    if(name==stringmatch){
      cout<<"processing histogram->"<<name<<endl;
      gPad->SetLogy(1);
      TH1D* leading;
      gDirectory->GetObject(name.c_str(),leading);
      TH1D* leadingSystematics;
      leadingSystematics=(TH1D*) leading->Clone("leading");

//
//   COMMENTED ONLY FOR NOW  **********************************
//
     //  // read from file --------------------------------------------
      ifstream in2;
      cout<< "reading ...  "<< systPathFile <<endl;
      in2.open (systPathFile.c_str());
      //int l2 =0;
      std::vector<double> systTmpEta;
      while (1) {
	 in2 >> dat;
	 if (!in2.good()) break;
	 systTmpEta.push_back(dat);
	 //l2++;  
      }    
      in2.close();
      // ------------------------------------------------------------
      leadingSystematics->SetName("leadingSystematics");
      if ( systTmpEta.size()!= leadingSystematics->GetNbinsX())
	 cout<<"WRONG NUMBER OF BINS"<<endl;
      for (int i=0; i<=leadingSystematics->GetNbinsX();i++){
	 double err = sqrt( pow(leading->GetBinError(i+1),2) + pow(systTmpEta[i]*leadingSystematics->GetBinContent(i+1),2)); 
	leadingSystematics->SetBinError(i+1,err);
      }
//******************************************************************************************************

      
    //   double sysv_lead[15] ={5.90857,4.31947,4.07386,4.47094,4.83375,5.77636,5.59512,6.06586,5.76923,5.76923,5.76923,5.76923,5.76923,5.76923,5.76923}; //in %
//       double sysv_sublead[15]={9.31662,8.10951,5.86788,5.6427,5.2652,6.44753,7.49487,5.0571,10,10,10,10,10,10,10};
//       double sysv_subsublead[15]={10.6758,10.2108,8.77832,10.6999,7.89177,8.125,7.59494,11.3793,14.7929,14.7929,14.7929,14.7929,14.7929,14.7929,14.7929};	    
//       double sysv_subsubsublead[15]={16.3347,13.6889,15.7618,13.2791,21.0084,22.2222,5.17241,3.44828,26.2295,26.2295,26.2295,26.2295,26.2295,26.2295,26.2295};
      
//       leadingSystematics->SetName("leadingSystematics");
      
//       for (int i=0; i<=leadingSystematics->GetNbinsX();i++){
// 	leadingSystematics->SetBinError(i+1,0.05*leadingSystematics->GetBinContent(i+1));

// 	//if (whichjet==1) leadingSystematics->SetBinError(i+1,0.01*sysv_lead[i]*leadingSystematics->GetBinContent(i+1));
// 	//if (whichjet==2) leadingSystematics->SetBinError(i+1,0.01*sysv_sublead[i]*leadingSystematics->GetBinContent(i+1));
// 	//if (whichjet==3) leadingSystematics->SetBinError(i+1,0.01*sysv_subsublead[i]*leadingSystematics->GetBinContent(i+1));
// 	//if (whichjet==4) leadingSystematics->SetBinError(i+1,0.01*sysv_subsubsublead[i]*leadingSystematics->GetBinContent(i+1));
//       }


      leadingSystematics->SetLineColor(kBlack);
      leadingSystematics->SetMarkerStyle(20);
      leadingSystematics->SetFillStyle(3003);
      leadingSystematics->SetFillColor(kRed); 
      leadingSystematics->SetMarkerColor(kBlack);
      leadingSystematics->Draw("E3");
      leading->SetFillColor(kBlack);
      leading->SetFillStyle(3001);
      leading->Draw("E3SAMES");
      
      TLatex *latexLabel=CMSPrel(4.890,""); // make fancy label
      latexLabel->Draw("same");  
      TLegend *legend_d = new TLegend (0.73494, 0.63, 0.931727, 0.83);
      legend_d->SetFillColor (0);
      legend_d->SetFillStyle (0);
      legend_d->SetBorderSize (0);
      legend_d->AddEntry (leading, "Statistical Error", "F");
      legend_d->AddEntry (leadingSystematics, "Total Error", "F");
      legend_d->Draw ("same");
      
      string title1= s+"DifferentialXSEta"+stringmatch+".pdf";
      cout<<title1<<endl;
      plots->Print(title1.c_str());
    }
    
  }
}
