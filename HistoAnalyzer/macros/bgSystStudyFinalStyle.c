#include "tdrStyle.C"
#include "plotsHistsAndRatioXSec.C"

#include <iomanip>
#include <cmath>
#include <iostream>
#include <sstream>
//#include <string.h>
#include <string>

#include "TH1.h"
#include "TH2.h"
#include "THStack.h"
#include "TTree.h"
#include "TF1.h"
#include <TROOT.h>
#include "TStyle.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TLine.h"
#include "TObject.h"

using std::cout;
using std::endl;

double myfunc (double *x, double *par) {
	return ( x[0]*par[0] +par[1]);
}


void bgSystStudyFinalStyle(void) {

   /* gROOT->Reset(); */
/*    gROOT->ForceStyle(); */
/*    //tdrStyle(); */
/* 	gStyle->SetOptStat(1111); */
/* 	gStyle->SetOptFit(11111); */
/* 	gStyle->SetFrameBorderMode(0); */
/* 	gStyle->SetCanvasBorderMode(0); */
/* 	gStyle->SetPadBorderMode(0); */
/* 	gStyle->SetFrameFillColor(10); */
/* 	gStyle->SetPadColor(10); */
/* 	gStyle->SetCanvasColor(10); */
/* 	gStyle->SetTitleColor(1); */
/* 	gStyle->SetStatColor(10); */
/* 	gStyle->SetFillColor(10); */
/* 	gStyle->SetAxisColor(1); */
/* 	gStyle->SetLabelColor(1); */
      //gStyle->SetPadRightMargin(0.15);
	
   gROOT->LoadMacro("plotsHistsAndRatioXSec.C");
   gROOT->LoadMacro("tdrStyle.C");
   tdrStyle();
   //setTDRStyle();
   using std::cout;
   using std::endl;
		
   //double pi_ = acos(-1.0);
   
//_______aprire un file root_________________________________
   
   string version="_v2_28";
   string plotpath="plotSigmaRatio"+version+"/";
   string plotpathTxt="/gpfs/cms/data/2011/Uncertainties/"; 
   string namefile1="../macros/plotXSecUP"+version+"/ratioPlotBgScaleUp"+version+".root";
   string namefile2="../macros/plotXSecDOWN"+version+"/ratioPlotBgScaleDown"+version+".root";
   string namefile3="../macros/plotData"+version+"/ratioPlotBgScale"+version+".root";
   TFile *fdata1 = TFile::Open(namefile1.c_str());
   TFile *fdata2 = TFile::Open(namefile2.c_str());
   TFile *fdata3 = TFile::Open(namefile3.c_str());
   
   fdata1->cd();
   TDirectory *dir=gDirectory;
   TList *mylist=(TList*)dir->GetListOfKeys();
   TIter iter(mylist);	
   // Use TIter::Next() to get each TObject mom owns.
   TObject* tobj = 0;
   string tmpname;  
   
   TCanvas * CanvPlot;
   // output files
   //string FileName="bgSystFinal";
   //FileName +=  ".root";
   //TFile* OutputFile =  TFile::Open(FileName.c_str() , "RECREATE" ) ;
   
//  ===================================================================================================================
//  ===================================================================================================================
//  ===================================================================================================================

   while ( (tobj = iter.Next()) ) {
      
      string plot=tobj->GetName();
      TString temp = tobj->GetName();
      string tmp;
      
      if(temp.Contains("Ratio")){
	 
	 fdata1->cd();
	 TH1F * scaleUp;
	 gDirectory->GetObject(plot.c_str(),scaleUp);
	 scaleUp->SetLineColor(kBlue);
	 scaleUp->SetMarkerStyle(20);
	 scaleUp->SetMarkerColor(kBlue);
	 
	 fdata2->cd();
	 TH1F* scaleDown;
	 gDirectory->GetObject(plot.c_str(),scaleDown);
	 scaleDown->SetLineColor(kRed);
	 scaleDown->SetMarkerStyle(20);
	 scaleDown->SetMarkerColor(kRed);
	 
	 fdata3->cd();
	 TH1F* ratio;
	 gDirectory->GetObject(plot.c_str(),ratio);
	 ratio->SetLineColor(kBlack);
	 ratio->SetMarkerStyle(20);
	 ratio->SetMarkerColor(kBlack);  
	 
	 // Canvas
	 if (CanvPlot) delete CanvPlot;
	 CanvPlot = new TCanvas("CanvPlot","CanvPlot",0,0,1000,700);
	 CanvPlot->cd();
	 
	 if(temp.Contains("nJetVtx")) scaleDown->GetXaxis()->SetRangeUser(0,10);	
	 if(temp.Contains("zMass")) scaleDown->GetXaxis()->SetRangeUser(70,110);
	 
	 size_t pos;
	 pos = plot.find("Ratio");
	 string plotSave = plot.substr(0,pos);

	 string title="XSec systematics";
	 plotHistsAndRatio(scaleDown,scaleUp,ratio,title.c_str(),plotSave.c_str()," data/MC"); 
	 TLegend *legend_1 = new TLegend (0.54, 0.63, 0.75, 0.86);
	 legend_1->SetFillColor (0);
	 legend_1->SetFillStyle (0);
	 legend_1->SetBorderSize (0);
	 legend_1->SetTextFont(62);
	 legend_1->AddEntry (ratio, "Original Distribution", "L");
	 legend_1->AddEntry (scaleUp, "Scale Up", "L");
	 legend_1->AddEntry (scaleDown, "Scale Down", "L");
	 legend_1->Draw ("same");
	 
	 tmp=plotpath+"bkgSyst_"+plotSave+".pdf";
	 c1->Print(tmp.c_str());
	 
	 std::vector<double> systs;
	 for (int i=1; i<=ratio->GetNbinsX(); i++){
	    double binDown = scaleDown->GetBinContent(i);
	    double binRatio = ratio->GetBinContent(i);
	    double binUp = scaleUp->GetBinContent(i);
	    if (binRatio!=0){
	       double systV = fabs(binDown - binUp)/(2.0*binRatio);
	       systs.push_back(systV);
	    } else systs.push_back(fabs(0.));
	 }

	 cout<<"Saving systematics in a file"<<endl;
	 //string filename="/gpfs/cms/data/2011/Uncertainties/BkgCrossSection_"+plot+".txt";
	 //string plotSave= plot;
	 //string::iterator it;
	 //it = strstr(plot,"Ratio");
	 //plot.string::erase (it, plot.end());
	 string filename=plotpath+"BkgCrossSection_"+plotSave+version+".txt";
	 ofstream syste;
	 syste.open(filename.c_str());
	 for (int i=0;i<systs.size();i++){
	    syste<<systs[i]<<endl;
	 }
	 //cout <<"written plot "<< tmp <<endl;
	 
	 //OutputFile->cd();
	 //string plotTmp;
	 //plotTmp = plot+"Ratio";
	 //ratio->SetName(plotTmp.c_str());
	 //ratio->Write();
      }
      
   }
   
/* //_______fittare una funzione_________________________________ */

/* 	TH1F *h1 = new TH1F("h1","titolo",10,0,10); */

/* 	TF1 *f1 = new TF1("f1","myfunc",0,1,2);  // range e numero parametri se ci sono */

/* 	// setta i parametri */

/* 	h1->Fit("f1","R"); */
 
	
   return;
	
}
