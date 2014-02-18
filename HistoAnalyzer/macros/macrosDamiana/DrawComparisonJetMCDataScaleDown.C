#include "tdrStyle.C"

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
#include <iostream>
#include <sstream>

#include "TH1.h"
#include "TH2.h"
#include "THStack.h"
#include "TTree.h"

#include <string.h>

//#include "lumi_scale_factors_scaleDown50.h"
//include "lumi_scale_factors_scaleDown.h"
//#include "lumi_scale_factors.h"
#include "lumi_scale_factors_scaleDownARC.h"
//#include "lumi_scale_factors_scaleDownARCTTBar.h"


//bool isMu = true;
bool isMu = false;

bool isAngularAnalysis= true;  // If true it will produce the plots connected to the differential and angular analysis. If false the usual control plots

bool lumiweights 	= 1;	//se 0 scala sull'integrale dell'area, se 1 scala sulla luminosita' integrata//
bool WholeStat= true;                // if true, reweing on RunA lumi, if false, on the whole stat. if true, the other variabs are uneffective, except lumipixel 
bool RunA= true;                // if true, reweing on RunA lumi, if false, on RunB
bool lumiPixel = true;           // if true, Lumi estimated using pixel, else with HF

string versionPath      ="_v2_58";
string version          = versionPath+".root";  // which version you wonna analize
string plotpath;
string plotpathEle	="plotEleXSecDOWN"+versionPath+"/"; //put here the path where you want the plots
string plotpathMu	="plotMuXSecDOWN"+versionPath+"/"; //put here the path where you want the plots
//string plotpathEle	="plotEleXSecDOWN50_v2_33/"; //put here the path where you want the plots
//string plotpathMu	="plotMuXSecDOWN50_v2_33/"; //put here the path where you want the plots

string datafile		="/gpfs/cms/data/2011/jet/jetValidation_DATA_2011Mu"+version;
string mcfile		="/gpfs/cms/data/2011/jet/jetValidation_zjets_magd_2011Mu"+version; 
string back_ttbar	="/gpfs/cms/data/2011/jet/jetValidation_ttbar_2011Mu"+version; 
string back_w		="/gpfs/cms/data/2011/jet/jetValidation_w_2011_v2_17pf.root"; //DA RIATTIVARE SOTTO, GREPPA hs->!!!!

string qcd23bc		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-20to30_BCtoE_v1_4.root"; //DA RIATTIVARE SOTTO, GREPPA hs->!!!!
string qcd38bc		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-30to80_BCtoE_v1_4.root"; //DA RIATTIVARE SOTTO, GREPPA hs->!!!!
string qcd817bc		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-80to170_BCtoE_v1_4.root"; //DA RIATTIVARE SOTTO, GREPPA hs->!!!!
string qcd23em		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-20to30_Enriched_v1_10.root"; //DA RIATTIVARE SOTTO, GREPPA hs->!!!!
string qcd38em		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-30to80_Enriched_v1_10.root"; //DA RIATTIVARE SOTTO, GREPPA hs->!!!!
string qcd817em		="/gpfs/cms/data/2011/jet/jetValidation_Qcd_Pt-80to170_Enriched_v1_10.root"; //DA RIATTIVARE SOTTO, GREPPA hs->!!!!

string WZ               ="/gpfs/cms/data/2011/jet/jetValidation_wz_2011Mu"+version;
string ZZ               ="/gpfs/cms/data/2011/jet/jetValidation_zz_2011Mu"+version;
string WW               ="/gpfs/cms/data/2011/jet/jetValidation_ww_2011Mu"+version;


double zwemean=12.; //le inizializzo a valori molto sbagliati, cosÃ¬ se non vengono modificate me ne accorgo
double wwemean=130.;
double ttwemean=140.;
double wzwemean=120;
double zzwemean=120;
double wwwemean=120;

double dataNumEvents=-999;
double zNumEvents=-999; //lo definisco globale anche se non Ã¨ la cosa piÃ¹ bella da fare
double ttNumEvents=-999; //questo lavoro andrebbe fatto anche per i qcd... 
double wNumEvents=-999; //al momento non l'ho fatto perchÃ© passano 0 eventi e e' gran smeno
double wzEvents=-999; 
double zzEvents=-999; 
double wwEvents=-999; 

//storing background infos in:
//string dir="/gpfs/cms/data/2011/BackgroundEvaluation/";
string dir=plotpathEle;
//string version="_DOWN_v2_22.root";
string bkg=dir+"Backgrounds"+version;
TFile* fzj = new TFile(bkg.c_str(), "RECREATE");
//Tree to store vthe values
TTree *treeBKG_= new TTree("treeBKG_","treeBKG_");

std::vector<double> bckg_leadingJetPt;
std::vector<double> bckg_2leadingJetPt;
std::vector<double> bckg_3leadingJetPt;
std::vector<double> bckg_4leadingJetPt;

std::vector<double> bckg_JetMultiplicity;

TCanvas * CanvPlot;
bool cold=true;
TFile* OutputFile;
string outfilename;

using namespace std;

void comparisonJetMCData(string plot,int rebin);
double numEventsPerStep(string filename, string dir);
void evaluateAndFillBackgrounds(TH1* histo, string str);


void DrawComparisonJetMCDataScaleDown(void){
  struct STestFunctor {
    bool operator()(TObject *aObj) {
      cout<<aObj->GetTitle()<<endl;
      //cout<<"pippo"<<endl;
      //comparisonJetMCData(aObj->GetTitle,1);
      return true;
    }
  };
  
  if (!isMu) plotpath=plotpathEle;
  else plotpath=plotpathMu;
  outfilename=plotpath+"ratioPlotBgScaleDown"+version;

  treeBKG_->Branch("bckg_leadingJetPt",&bckg_leadingJetPt);
  treeBKG_->Branch("bckg_2leadingJetPt",&bckg_2leadingJetPt);
  treeBKG_->Branch("bckg_3leadingJetPt",&bckg_3leadingJetPt);
  treeBKG_->Branch("bckg_4leadingJetPt",&bckg_4leadingJetPt);
  treeBKG_->Branch("bckg_JetMultiplicity",&bckg_JetMultiplicity);

  gROOT->Reset();
  gROOT->ForceStyle();
  gROOT->LoadMacro("tdrStyle.C++");
  tdrStyle();

  // Recupero l'informazione sul numero di eventi processati per singolo MC
  dataNumEvents = numEventsPerStep(datafile, "demo"); 
  zNumEvents = numEventsPerStep(mcfile, "demo"); 
  ttNumEvents = numEventsPerStep(back_ttbar, "demo"); 
  wNumEvents = numEventsPerStep(back_w, "demo"); 
  wzEvents = numEventsPerStep(WZ, "demo"); 
  zzEvents = numEventsPerStep(ZZ, "demo"); 
  wwEvents = numEventsPerStep(WW, "demo"); 
  // ---------------------------------------------------

  string direc="/gpfs/cms/data/2011/Observables/Approval/";
  //string direc=dir;
  //string versionO="_v2_30.root";
  string versionO=version;

  if (!isMu){
     if (isAngularAnalysis){
	mcfile=direc+"MC_zjets"+versionO;
	back_w=direc+"MC_wjets"+versionO;
	back_ttbar=direc+"MC_ttbar"+versionO;
	WW=direc+"MC_diW"+versionO;
	ZZ=direc+"MC_siZ"+versionO;
	WZ=direc+"MC_diWZ"+versionO;
	datafile=direc+"DATA"+versionO;
     }
  } else {
     if (isAngularAnalysis){
	mcfile=direc+"MC_zjetsMu"+versionO;
	back_w=direc+"MC_wjetsMu"+versionO;
	back_ttbar=direc+"MC_ttbarMu"+versionO;
	WW=direc+"MC_diWMu"+versionO;
	ZZ=direc+"MC_siZMu"+versionO;
	WZ=direc+"MC_diWZMu"+versionO;
	datafile=direc+"DATAMu"+versionO;
     }
  }


  TFile *mcf = TFile::Open(mcfile.c_str()); //MC file
  if (!isMu) mcf->cd("validationJEC/");
  else mcf->cd("validationJECmu/");
  TDirectory *dir=gDirectory;
  TList *mylist=(TList*)dir->GetListOfKeys();
  TIter iter(mylist);	
  // Use TIter::Next() to get each TObject mom owns.
  TObject* tobj = 0;
  string tmpname;

  // input and output files
  string FileName(outfilename);
  //FileName +=  ".root";
  OutputFile =  TFile::Open(FileName.c_str() , "RECREATE" ) ;

  int i=0; // solo di servizio quando debuggo...
  while ( (tobj = iter.Next()) ) {
    
    gROOT->Reset();
    gROOT->ForceStyle();
    tdrStyle();
    gStyle->SetPadRightMargin(0.15);

    string name=tobj->GetName();
    TString temp = (TString)name;
    
    //int num=tobj->GetUniqueID();

    if(temp.Contains("weight")){
      mcf = TFile::Open(mcfile.c_str()); 
      TFile *ttbarf = TFile::Open(back_ttbar.c_str()); 
      TFile *wf = TFile::Open(back_w.c_str());
      TFile *wzf = TFile::Open(WZ.c_str());
      TFile *zzf = TFile::Open(ZZ.c_str());
      TFile *wwf = TFile::Open(WW.c_str());

      TCanvas * Canvweight = new TCanvas("Canvweight","Canvweight",0,0,800,600);
      //if (Canv) delete Canv;
      //Canv = new TCanvas("Canv","Canv",0,0,800,600);

      gPad->SetLogy(1);
	
      //---- weights
      if (!isMu) mcf->cd("validationJEC");
      else mcf->cd("validationJECmu");
      TH1F* mc;
      gDirectory->GetObject(name.c_str(),mc);
      if(mc){
	mc->SetFillColor(kRed);
	mc->GetXaxis()->SetRangeUser(0.,12.);
	mc->SetMinimum(1.);
	mc->Draw();
	zwemean = mc->GetMean();
	tmpname=plotpath+name+"-zjets.png";
	Canvweight->Print(tmpname.c_str());
      }

      //---- weights
      if (!isMu) ttbarf->cd("validationJEC");
      else ttbarf->cd("validationJECmu");
      TH1F* ttbar;
      gDirectory->GetObject(name.c_str(),ttbar);
	
      if(ttbar){
	ttbar->SetFillColor(kBlue);
	ttbar->GetXaxis()->SetRangeUser(0.,2.);
	ttbar->Draw();
	ttwemean = ttbar->GetMean();
	tmpname=plotpath+name+"-ttbar.png";
	Canvweight->Print(tmpname.c_str());
      }

      //---- weights
      if (!isMu) wf->cd("validationJEC");
      else  wf->cd("validationJECmu");
      TH1F* w;
      gDirectory->GetObject(name.c_str(),w);
      if(w){
	w->SetFillColor(kViolet+2);
	w->GetXaxis()->SetRangeUser(0.,2.);
	w->Draw();
	wwemean = w->GetMean();
	tmpname=plotpath+name+"-wjets.png";
	Canvweight->Print(tmpname.c_str());
      }

      //---- weights
      if (!isMu) wzf->cd("validationJEC");
      else  wzf->cd("validationJECmu");
      TH1F* wz;
      gDirectory->GetObject(name.c_str(),wz);
      if(wz){
	wz->SetFillColor(kYellow+2);
	wz->GetXaxis()->SetRangeUser(0.,2.);
	wz->Draw();
	wzwemean = w->GetMean();
	tmpname=plotpath+name+"-wzjets.png";
	Canvweight->Print(tmpname.c_str());
      }	

      //---- weights
      if (!isMu) zzf->cd("validationJEC");
      else  zzf->cd("validationJECmu");
      TH1F* zz;
      gDirectory->GetObject(name.c_str(),zz);
      if(zz){
	zz->SetFillColor(kOrange+2);
	zz->GetXaxis()->SetRangeUser(0.,2.);
	zz->Draw();
	zzwemean = w->GetMean();
	tmpname=plotpath+name+"-zzjets.png";
	Canvweight->Print(tmpname.c_str());
      }

      //---- weights
      if (!isMu) wwf->cd("validationJEC");
      else  wwf->cd("validationJECmu");
      TH1F* www;
      gDirectory->GetObject(name.c_str(),www);
      if(www){
	www->SetFillColor(kBlack);
	www->GetXaxis()->SetRangeUser(0.,2.);
	www->Draw();
	wwwemean = www->GetMean();
	tmpname=plotpath+name+"-wwwjets.png";
	Canvweight->Print(tmpname.c_str());
      }		
    }
    else comparisonJetMCData(name,1);

    i++;
    //if(i==4)break;
  }


  // AVVISI AI NAVIGANTI
  //if(dataNumEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DEI DATI, quindi ho normalizzato sugli eventi totali del campione\n";
  //else cout << "Il numero di eventi (dati) " << dataNumEvents << "\n";
	
  if(zNumEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DELLO Z+JETS, quindi ho normalizzato sugli eventi totali del campione\n";
  else cout << "Il numero di eventi di Z+jets " << zNumEvents << "\n";
	
  if(ttNumEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DEL TTBAR+JETS, quindi ho normalizzato sugli eventi totali del campione\n";
  else cout << "Il numero di eventi di ttbar+jets " << ttNumEvents << "\n";
	
	
  if(wNumEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DEL W+JETS, quindi ho normalizzato sugli eventi totali del campione\n";
  else cout << "Il numero di eventi di W+jets " << wNumEvents << "\n";

  if(wzEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DEL W+JETS, quindi ho normalizzato sugli eventi totali del campione\n";
  else cout << "Il numero di eventi di ZW+jets " << wzEvents << "\n";

  if(zzEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DEL W+JETS, quindi ho normalizzato sugli eventi totali del campione\n";
  else cout << "Il numero di eventi di ZZ+jets " << zzEvents << "\n";	

  if(wwEvents<0.) cout << "ATTENZIONE: HAI FALLITO LA NORMALIZZAZIONE DEL W+JETS, quindi ho normalizzato sugli eventi totali del campione\n";
  else cout << "Il numero di eventi di WW+jets " << wwEvents << "\n";

  OutputFile->Close();

  return;
}


//==================================
//	      Funzioni
//==================================

void comparisonJetMCData(string plot,int rebin){
  string tmp;

  string dir="/gpfs/cms/data/2011/Observables/Approval/";
  //string dir=plothpath;
  //string versionO="_v2_30.root";
  string versionO=version;

  if (!isMu){
     if (isAngularAnalysis){
	mcfile=dir+"MC_zjets"+versionO;
	back_w=dir+"MC_wjets"+versionO;
	back_ttbar=dir+"MC_ttbar"+versionO;
	WW=dir+"MC_diW"+versionO;
	ZZ=dir+"MC_siZ"+versionO;
	WZ=dir+"MC_diWZ"+versionO;
	datafile=dir+"DATA"+versionO;
     }
  } else {
     if (isAngularAnalysis){
	mcfile=dir+"MC_zjetsMu"+versionO;
	back_w=dir+"MC_wjetsMu"+versionO;
	back_ttbar=dir+"MC_ttbarMu"+versionO;
	WW=dir+"MC_diWMu"+versionO;
	ZZ=dir+"MC_siZMu"+versionO;
	WZ=dir+"MC_diWZMu"+versionO;
	datafile=dir+"DATAMu"+versionO;
     }
  }
  // List of files

  TFile *dataf = TFile::Open(datafile.c_str()); //data file
  TFile *mcf = TFile::Open(mcfile.c_str()); //MC file
  TFile *ttbarf = TFile::Open(back_ttbar.c_str()); //MC background file
  TFile *wf = TFile::Open(back_w.c_str());


 //  TFile *qcd23emf = TFile::Open(qcd23em.c_str());
//   TFile *qcd38emf = TFile::Open(qcd38em.c_str());
//   TFile *qcd817emf = TFile::Open(qcd817em.c_str());

//   TFile *qcd23bcf = TFile::Open(qcd23bc.c_str());
//   TFile *qcd38bcf = TFile::Open(qcd38bc.c_str());
//   TFile *qcd817bcf = TFile::Open(qcd817bc.c_str());

  TFile *WZf = TFile::Open(WZ.c_str());
  TFile *ZZf = TFile::Open(ZZ.c_str());
  TFile *WWf = TFile::Open(WW.c_str());


  // Canvas
  if (CanvPlot) delete CanvPlot;
  CanvPlot = new TCanvas("CanvPlot","CanvPlot",0,0,800,600);

  // Getting, defining ...
  if (!isMu) dataf->cd("validationJEC");
  else dataf->cd("validationJECmu");
	
  TObject * obj;
  gDirectory->GetObject(plot.c_str(),obj);

  TH1 *data; 
  TH2F *data2; 
  TH1D *data3; 

  THStack *hs = new THStack("hs","Total MC");


  int flag=-1;
  if ((data = dynamic_cast<TH1F *>(obj)) ){
    flag=1;
    gROOT->Reset();
    gROOT->ForceStyle();
    gStyle->SetPadRightMargin(0.03);
    gPad->SetLogy(1);
    gPad->Modified();
    gPad->Update();
  }
  if ((data2 = dynamic_cast<TH2F *>(obj)) ){
    flag=2;
    gStyle->SetPalette(1);
    gStyle->SetPadRightMargin(0.15);
    gPad->Modified();
  }



  //===================
  // Dirty jobs :)
  if (flag==1){
    CanvPlot->cd();
    TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
    pad1->Draw();
    pad1->cd();
    pad1->SetLogy(1);
    TString str=data->GetTitle();
    if (str.Contains("jet") && !str.Contains("zMass") && !str.Contains("Num") && !str.Contains("Eta") && !str.Contains("Phi") && !str.Contains("eld") && !str.Contains("meanPtZVsNjet")) {
      if (!isAngularAnalysis) rebin=5;
    }

    //======================
    // DATA
    Double_t dataint = data->Integral();
    data->SetLineColor(kBlack);
    data->Rebin(rebin);
    if(str.Contains("nJetVtx")) data->GetXaxis()->SetRangeUser(0,10);	
    if(str.Contains("zMass")) data->GetXaxis()->SetRangeUser(70,110);	
    data->SetMinimum(1.);
    data->Sumw2();
    data->Draw("E1");

    TLegend* legend = new TLegend(0.825,0.57,0.95,0.72);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->SetBorderSize(0);
    legend->AddEntry(data,"data","p");

    // hack to calculate some yields in restricted regions...
    int num1=0, num2=0, num3=0, num4=0, num5=0;
    if(str.Contains("invMass") && !str.Contains("PF")){
      for(int j=1;j<=data->GetNbinsX();j++){
	num1 += data->GetBinContent(j); 		//conto quante Z ci sono tra 60 e 120 GeV
	if(j>10&&j<=50) num2 += data->GetBinContent(j); // ... tra 70 e 110
	if(j>15&&j<=45) num3 += data->GetBinContent(j); // ... tra 75 e 105
      }
      cout << "\n";
      cout << data->GetNbinsX() <<" Number of bins of the invmass histo\n";
      printf("Number of Z in 60-120 %i --- 70-110 %i --- 75-105 %i \n",num1,num2,num3);
      cout << "\n";
    }
    if(str.Contains("zYieldVsjets") && !str.Contains("Vtx")){
      for(int j=1;j<=data->GetNbinsX();j++){
	num1 += data->GetBinContent(j); 		//conto quante Z
	if(j>1) num2 += data->GetBinContent(j); // ... +1,2,3,4... jets
	if(j>2) num3 += data->GetBinContent(j); // ... +2,3,4... jets
	if(j>3) num4 += data->GetBinContent(j); // ..    if(str=="jet_pT"){
	if(j>4) num5 += data->GetBinContent(j); // ... +4... jets
      }
      cout << "\n";
      cout << data->GetNbinsX() <<" Number of bins of the zYieldVsjets histo\n";
      printf("Number of Z+n jet %i --- >1 %i --- >2 %i --- >3 %i --- >4 %i \n",num1,num2,num3,num4,num5);
      cout << "\n";
    }    

    //======================
    // Z + jets signal
    if (!isMu) mcf->cd("validationJEC");
    else mcf->cd("validationJECmu");
    TH1F* mc;
    gDirectory->GetObject(plot.c_str(),mc);
    TH1D * hsum;
    if(mc){
      hsum =  (TH1D*) mc->Clone();
      hsum->SetTitle("hsum");
      hsum->SetName("hsum");
      hsum->Reset();

      Double_t mcint = mc->Integral();
      mc->SetFillColor(kRed);
      mc->Sumw2();
      if(lumiweights==0) mc->Scale(dataint/mcint);
		
      // Blocco da propagare negli altri MC
      if(zNumEvents>0.){
	if(lumiweights==1) {
	  if (WholeStat){
	    if (lumiPixel) mc->Scale( dataLumi2011pix / (zNumEvents / zjetsXsect));
	    else mc->Scale( dataLumi2011 / (zNumEvents / zjetsXsect));
	  }
	  else{
	    if (RunA){
	      if (lumiPixel) mc->Scale( dataLumi2011Apix / (zNumEvents / zjetsXsect));
	      else mc->Scale( dataLumi2011A / (zNumEvents / zjetsXsect));
	    }
	    if (!RunA){
	      if (lumiPixel) mc->Scale( dataLumi2011Bpix / (zNumEvents / zjetsXsect));
	      else mc->Scale( dataLumi2011B / (zNumEvents / zjetsXsect));
	    }
	  }
	}
      }
      else {
	if(lumiweights==1) mc->Scale(zjetsScale);
      }
      // fin qui
      if(lumiweights==1) mc->Scale(1./zwemean);  // perche' i Weights non fanno 1...
      mc->Rebin(rebin);
      if(lumiweights==0) mc->Draw("HISTO SAMES");
      hsum->Rebin(rebin);
      hsum->Add(mc);
      legend->AddEntry(mc,"Z+jets","f");
    }

    //======================
    // ttbar
    if (!isMu) ttbarf->cd("validationJEC");
    else ttbarf->cd("validationJECmu");
    TH1F* ttbar;
    gDirectory->GetObject(plot.c_str(),ttbar);
	
    if(ttbar){
      ttbar->SetFillColor(kBlue);
      ttbar->Sumw2();

      if(ttNumEvents>0.){
	if(lumiweights==1) {
	  if (WholeStat){
	    if (lumiPixel) ttbar->Scale( dataLumi2011pix / (ttNumEvents / ttbarXsect));
	    else ttbar->Scale( dataLumi2011 / (ttNumEvents / ttbarXsect));
	  }
	  else{
	    if (RunA){
	      if (lumiPixel) ttbar->Scale( dataLumi2011Apix / (ttNumEvents / ttbarXsect));
	      else ttbar->Scale( dataLumi2011A / (ttNumEvents / ttbarXsect));
	    }
	    if (!RunA){
	      if (lumiPixel) ttbar->Scale( dataLumi2011Bpix / (ttNumEvents / ttbarXsect));
	      else ttbar->Scale( dataLumi2011B / (ttNumEvents / ttbarXsect));
	    }
	  }
	}
      }
      else {
	if(lumiweights==1) ttbar->Scale(ttwemean);
      }
      // fin qui
		
      if(lumiweights==1) ttbar->Scale(1./ttwemean);  // perche' i Weights non fanno 1...
      ttbar->Rebin(rebin);
      if(lumiweights==0) ttbar->Draw("HISTO SAMES");
      hsum->Rebin(rebin);
      hsum->Add(ttbar);
      if(lumiweights==1)legend->AddEntry(ttbar,"ttbar","f");

      //////////
      //Storing the bckgrounds!
      //////////
      
      if(str=="jet_pT") evaluateAndFillBackgrounds(ttbar,"jet_pT");
      if(str=="jet_pT2") evaluateAndFillBackgrounds(ttbar,"jet_pT2");
      if(str=="jet_pT3") evaluateAndFillBackgrounds(ttbar,"jet_pT3");
      if(str=="jet_pT4") evaluateAndFillBackgrounds(ttbar,"jet_pT4");
      if(str=="Jet_multi") evaluateAndFillBackgrounds(ttbar,"jet_Multiplicity");
      
    }

    //======================
    // w+jets
    if (!isMu) wf->cd("validationJEC");
    else wf->cd("validationJECmu");
    TH1F* w;
    gDirectory->GetObject(plot.c_str(),w);
    if(w){

      w->SetFillColor(kViolet+2);
      w->Sumw2();

      if(wNumEvents>0.){
	if(lumiweights==1) {
	  if (WholeStat){
	    if (lumiPixel) w->Scale( dataLumi2011pix / (wNumEvents / wjetsXsect));
	    else w->Scale( dataLumi2011 / (wNumEvents / wjetsXsect));
	  }
	  else{
	    if (RunA){
	      if (lumiPixel) w->Scale( dataLumi2011Apix / (wNumEvents / wjetsXsect));
	      else w->Scale( dataLumi2011A / (wNumEvents / wjetsXsect));
	    }
	    if (!RunA){
	      if (lumiPixel) w->Scale( dataLumi2011Bpix / (wNumEvents / wjetsXsect));
	      else w->Scale( dataLumi2011B / (wNumEvents / wjetsXsect));
	    }
	  }
	}
      }
      else {
	if(lumiweights==1) w->Scale(wwemean);
      }
      // fin qui
		
      if(lumiweights==1) w->Scale(1./wwemean);  // perche' i Weights non fanno 1...
      w->Rebin(rebin);
      if(lumiweights==0) w->Draw("HISTO SAMES");
      hsum->Rebin(rebin);
      hsum->Add(w);
      if(lumiweights==1)legend->AddEntry(w,"W+jets","f");
    }

    //======================
    // wz+jets
    if (!isMu) WZf->cd("validationJEC");
    else WZf->cd("validationJECmu");
    TH1F* wz;
    gDirectory->GetObject(plot.c_str(),wz);
    if(wz){
      wz->SetFillColor(kYellow+2);
      wz->Sumw2();

      if(wzEvents>0.){
	if(lumiweights==1) {
	  if (WholeStat){
	    if (lumiPixel) wz->Scale( dataLumi2011pix / (wzEvents / WZXsect));
	    else wz->Scale( dataLumi2011 / (wzEvents / WZXsect));
	  }
	  else{
	    if (RunA){
	      if (lumiPixel) wz->Scale( dataLumi2011Apix / (wzEvents / WZXsect));
	      else wz->Scale( dataLumi2011A / (wzEvents / WZXsect));
	    }
	    if (!RunA){
	      if (lumiPixel) wz->Scale( dataLumi2011Bpix / (wzEvents / WZXsect));
	      else wz->Scale( dataLumi2011B / (wzEvents / WZXsect));
	    }
	  }
	}
      }
      else {
	if(lumiweights==1) wz->Scale(wzjetsScale);
      }
      // fin qui
		
      if(lumiweights==1) wz->Scale(1./wzwemean);  // perche' i Weights non fanno 1...
      wz->Rebin(rebin);
      if(lumiweights==0) wz->Draw("HISTO SAMES");
      hsum->Rebin(rebin);
      hsum->Add(wz);
      legend->AddEntry(wz,"WZ+jets","f");


      //////////
      //Storing the bckgrounds!
      //////////

      if(str=="jet_pT") evaluateAndFillBackgrounds(wz,"jet_pT");
      if(str=="jet_pT2") evaluateAndFillBackgrounds(wz,"jet_pT2");
      if(str=="jet_pT3") evaluateAndFillBackgrounds(wz,"jet_pT3");
      if(str=="jet_pT4") evaluateAndFillBackgrounds(wz,"jet_pT4");
      if(str=="Jet_multi") evaluateAndFillBackgrounds(wz,"jet_Multiplicity");
      
    }
    
		
    //======================
    // zz+jets
    if (!isMu) ZZf->cd("validationJEC");
    else ZZf->cd("validationJECmu");
    TH1F* zz;
    gDirectory->GetObject(plot.c_str(),zz);
    if(zz){
      zz->SetFillColor(kOrange+2);
      zz->Sumw2();

      if(zzEvents>0.){
	if(lumiweights==1) {
	  if (WholeStat){
	    if (lumiPixel) zz->Scale( dataLumi2011pix / (zzEvents / ZZXsect));
	    else zz->Scale( dataLumi2011 / (zzEvents / ZZXsect));
	  }
	  else{
	    if (RunA){
	      if (lumiPixel) zz->Scale( dataLumi2011Apix / (zzEvents / ZZXsect));
	      else zz->Scale( dataLumi2011A / (zzEvents / ZZXsect));
	    }
	    if (!RunA){
	      if (lumiPixel) zz->Scale( dataLumi2011Bpix / (zzEvents / ZZXsect));
	      else zz->Scale( dataLumi2011B / (zzEvents / ZZXsect));
	    }
	  }
	}
      }
      else {
	if(lumiweights==1) zz->Scale(zzjetsScale);
      }
      // fin qui
		
      if(lumiweights==1) zz->Scale(1./zzwemean);  // perche' i Weights non fanno 1...
      zz->Rebin(rebin);
      if(lumiweights==0) zz->Draw("HISTO SAMES");
      hsum->Rebin(rebin);
      hsum->Add(zz);
      legend->AddEntry(zz,"ZZ+jets","f");

      //////////
      //Storing the bckgrounds!
      //////////

      if(str=="jet_pT") evaluateAndFillBackgrounds(zz,"jet_pT");
      if(str=="jet_pT2") evaluateAndFillBackgrounds(zz,"jet_pT2");
      if(str=="jet_pT3") evaluateAndFillBackgrounds(zz,"jet_pT3");
      if(str=="jet_pT4") evaluateAndFillBackgrounds(zz,"jet_pT4");
      if(str=="Jet_multi") evaluateAndFillBackgrounds(zz,"jet_Multiplicity");  
    }
    
    //======================
    // ww+jets
    if (!isMu) WWf->cd("validationJEC");
    else WWf->cd("validationJECmu");

    TH1F* ww;
    gDirectory->GetObject(plot.c_str(),ww);
    if(ww){
      ww->SetFillColor(kBlack);
      ww->Sumw2();

      if(wwEvents>0.){
	if(lumiweights==1) {
	  if (WholeStat){
	    if (lumiPixel) ww->Scale( dataLumi2011pix / (wwEvents / WWXsect));
	    else ww->Scale( dataLumi2011 / (wwEvents / WWXsect));
	  }
	  else{
	    if (RunA){
	      if (lumiPixel) ww->Scale( dataLumi2011Apix / (wwEvents / WWXsect));
	      else ww->Scale( dataLumi2011A / (wwEvents / WWXsect));
	    }
	    if (!RunA){
	      if (lumiPixel) ww->Scale( dataLumi2011Bpix / (wwEvents / WWXsect));
	      else ww->Scale( dataLumi2011B / (wwEvents / WWXsect));
	    }
	  }
	}
      }
      else {
	if(lumiweights==1) ww->Scale(wwjetsScale);
      }
      // fin qui
		
      if(lumiweights==1) ww->Scale(1./wwwemean);  // perche' i Weights non fanno 1...
      ww->Rebin(rebin);
      if(lumiweights==0) ww->Draw("HISTO SAMES");
      hsum->Rebin(rebin);
      hsum->Add(ww);
      legend->AddEntry(ww,"WW+jets","f");

      //////////
      //Storing the bckgrounds!
      //////////

      if(str=="jet_pT") evaluateAndFillBackgrounds(ww,"jet_pT");
      if(str=="jet_pT2") evaluateAndFillBackgrounds(ww,"jet_pT2");
      if(str=="jet_pT3") evaluateAndFillBackgrounds(ww,"jet_pT3");
      if(str=="jet_pT4") evaluateAndFillBackgrounds(ww,"jet_pT4");
      if(str=="Jet_multi") evaluateAndFillBackgrounds(ww,"jet_Multiplicity");

    }

    /////////
    // Print the bkg contributions
    ////////

    for(int j=0;j<bckg_leadingJetPt.size();j++){      
      cout<<bckg_leadingJetPt[j]<<endl;
    }	

    // //======================
//     // QCD EM enriched
//     qcd23emf->cd("validationJEC");
//     TH1F* qcd23emp;
//     gDirectory->GetObject(plot.c_str(),qcd23emp);

//     if(qcd23emp){
//       TH1D * qcdTotEM =  (TH1D*) qcd23emp->Clone(); 
//       qcdTotEM->SetTitle("qcd em");
//       qcdTotEM->SetName("qcd em");
//       qcdTotEM->Reset();
//       qcdTotEM->Rebin(rebin);

//       qcd38emf->cd("validationJEC");
//       TH1F* qcd38emp;
//       gDirectory->GetObject(plot.c_str(),qcd38emp);


//       qcd817emf->cd("validationJEC");
//       TH1F* qcd817emp;
//       gDirectory->GetObject(plot.c_str(),qcd817emp);

//       qcd23emp->Rebin(rebin);
//       qcd23emp->Sumw2();
//       qcd23emp->Scale(qcd23emScale); 
//       qcd38emp->Rebin(rebin);
//       qcd38emp->Sumw2();
//       qcd38emp->Scale(qcd38emScale); 
//       qcd817emp->Rebin(rebin);
//       qcd817emp->Sumw2();
//       qcd817emp->Scale(qcd817emScale); 

//       qcdTotEM->SetFillColor(kOrange+1);
//       qcdTotEM->Add(qcd23emp);
//       qcdTotEM->Add(qcd38emp);
//       qcdTotEM->Add(qcd817emp);

//       hsum->Add(qcdTotEM);

//       if(lumiweights==1)legend->AddEntry(qcdTotEM,"QCD em","f");
//     }

//     //======================
//     // QCD bc
//     qcd23bcf->cd("validationJEC");
//     TH1F* qcd23bcp;
//     TH1D * qcdTotBC;
//     bool  qcdbcempty=true;
//     gDirectory->GetObject(plot.c_str(),qcd23bcp);

//     if(qcd23bcp){
//       qcdTotBC =  (TH1D*) qcd23bcp->Clone(); 
//       qcdTotBC->SetTitle("qcd bc");
//       qcdTotBC->SetName("qcd bc");
//       qcdTotBC->Reset();
//       qcdTotBC->Rebin(rebin);

//       qcd38bcf->cd("validationJEC");
//       TH1F* qcd38bcp;
//       gDirectory->GetObject(plot.c_str(),qcd38bcp);

//       qcd817bcf->cd("validationJEC");
//       TH1F* qcd817bcp;
//       gDirectory->GetObject(plot.c_str(),qcd817bcp);

//       qcd23bcp->Rebin(rebin);
//       qcd23bcp->Sumw2();
//       qcd23bcp->Scale(qcd23bcScale); 
//       qcd38bcp->Rebin(rebin);
//       qcd38bcp->Sumw2();
//       qcd38bcp->Scale(qcd38bcScale); 
//       qcd817bcp->Rebin(rebin);
//       qcd817bcp->Sumw2();
//       qcd817bcp->Scale(qcd817bcScale); 

//       qcdTotBC->SetFillColor(kGreen+2);
//       qcdTotBC->Add(qcd23bcp);
//       qcdTotBC->Add(qcd38bcp);
//       qcdTotBC->Add(qcd817bcp);

//       hsum->Add(qcdTotBC);
//       if (qcdTotBC->GetEntries()>0) qcdbcempty=false; 

//       if(lumiweights==1)legend->AddEntry(qcdTotBC,"QCD bc","f");
//     }

    //======================
    // Add here other backgrounds


    //======================
    // Stacked Histogram
    //if(qcd23em) 	hs->Add(qcdTotEM);
    //if(!qcdbcempty) 	hs->Add(qcdTotBC);
    if (ww)         hs->Add(ww);
    if (ttbar)	hs->Add(ttbar);
    if(w)  	        hs->Add(w);
    if (zz)         hs->Add(zz);
    if (wz)         hs->Add(wz);
    if(mc)		hs->Add(mc); //Z+Jets

		
    // per avere le statistiche
    if(lumiweights==1) hsum->Draw("HISTO SAMES");


    //======================
    // Setting the stats
    pad1->Update(); // altrimenti non becchi la stat
    TPaveStats *r2;
    if(lumiweights==0) r2 = (TPaveStats*)mc->FindObject("stats");
    if(lumiweights==1) r2 = (TPaveStats*)hsum->FindObject("stats");
    r2->SetY1NDC(0.875);
    r2->SetY2NDC(0.75); 
    r2->SetTextColor(kRed);
		
    if(lumiweights==1) hs->Draw("HISTO SAME");
    gPad->RedrawAxis();
    data->Draw("E1 SAMES");
    r2->Draw();
    legend->Draw();
    TLegend* lumi = new TLegend(0.45,0.3,0.75,0.2);
    lumi->SetFillColor(0);
    lumi->SetFillStyle(0);
    lumi->SetBorderSize(0);
    lumi->AddEntry((TObject*)0,"#int L dt =4.9 1/fb","");
    lumi->Draw();
    CanvPlot->Update();

	


    //===============//
    // RATIO DATA MC //
    //===============//
    CanvPlot->cd();
    TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
    pad2->Draw();
    pad2->cd();
    TH1D * ratio =  (TH1D*) data->Clone();
    ratio->SetTitle("ratio");
    ratio->SetName("ratio");
    ratio->Reset();

    ratio->Sumw2();
    //data->Sumw2();
    hsum->Sumw2(); // FIXME controlla che sia corretto questo... 
    ratio->SetMarkerSize(.5);
    ratio->SetLineColor(kBlack);
    ratio->SetMarkerColor(kBlack);
    gStyle->SetOptStat("m");
    ratio->Divide(data,hsum,1.,1.);
    ratio->GetYaxis()->SetRangeUser(0,2);	
    pad2->SetTopMargin(1);
    ratio->Draw("E1");
		
    TLine *OLine = new TLine(ratio->GetXaxis()->GetXmin(),1.,ratio->GetXaxis()->GetXmax(),1.);
    OLine->SetLineColor(kBlack);
    OLine->SetLineStyle(2);
    OLine->Draw();
 
    TLegend* label = new TLegend(0.60,0.9,0.85,0.75);
    label->SetFillColor(0);
    label->SetFillStyle(0);
    label->SetBorderSize(0);
    //horrible mess
    double binContent = 0;
    double binSum = 0;
    double weightSum = 0;
    double binError = 1;
    double totalbins = ratio->GetSize() -2;
    for(unsigned int bin=1;bin<=totalbins;bin++){
      binContent = ratio->GetBinContent(bin);
      binError = ratio->GetBinError(bin);
      if(binError!=0){
	binSum += binContent/binError;
	weightSum += 1./binError;
      }
    }
    double ymean = binSum / weightSum;
    //double ymean = ratio->GetMean(2);
    stringstream sYmean;
    sYmean << ymean;
    string labeltext=sYmean.str()+" mean Y";
    //label->AddEntry((TObject*)0,labeltext.c_str(),""); // mean on Y
    //label->Draw();
		
    TPaveStats *r3 = (TPaveStats*)ratio->FindObject("stats");
    r3->SetX1NDC(0.01);
    r3->SetX2NDC(0.10); 
    r3->SetY1NDC(0.20);
    r3->SetY2NDC(0.50); 
    gStyle->SetOptStat("mr");
    r3->SetTextColor(kWhite);
    r3->SetLineColor(kWhite);
    r3->Draw();
    CanvPlot->Update();

    tmp=plotpath+plot+".pdf";
    CanvPlot->Print(tmp.c_str());
    
    OutputFile->cd();
    string plotTmp;
    plotTmp = plot+"Ratio";
    ratio->SetName(plotTmp.c_str());
    plotTmp = plot+"MC";
    hsum->SetName(plotTmp.c_str());
    hsum->Write();
    ratio->Write();
  }
  else if (flag==2){
    //CanvPlot.Divide(2,1);
    //CanvPlot.cd(1);

    // data
    if (!isMu) dataf->cd("validationJEC");
    else dataf->cd("validationJECmu");
    gDirectory->GetObject(plot.c_str(),data2);
    data2->Draw("COLZ");

    gPad->Update(); // altrimenti non becchi la stat
    TPaveStats *r1 = (TPaveStats*)data2->FindObject("stats");
    r1->SetX1NDC(0.70);
    r1->SetX2NDC(0.85); 
    r1->Draw();
    CanvPlot->Update();

    tmp=plotpath+plot+"data.pdf";
    CanvPlot->Print(tmp.c_str());


    //CanvPlot.cd(2);
    // montecarlo
    if (!isMu) mcf->cd("validationJEC");
    else mcf->cd("validationJECmu");
    gDirectory->GetObject(plot.c_str(),data2);

    data2->SetMinimum(1);
    data2->Draw("COLZ");

    gPad->Update(); // altrimenti non becchi la stat
    TPaveStats *r2 = (TPaveStats*)data2->FindObject("stats");
    r2->SetX1NDC(0.70);
    r2->SetX2NDC(0.85); 
    r2->Draw();
    CanvPlot->Update();

    tmp=plotpath+plot+"mc.pdf";
    CanvPlot->Print(tmp.c_str());
  }
  //	else { cout << "You're getting an exception! Most likely there's no histogram here... \n"; }

  delete data;
  delete data2;
  delete hs;
  //delete CanvPlot;

  dataf->Close();
  mcf->Close();
  ttbarf->Close();
  wf->Close();
  //qcd23emf->Close();
  //qcd38emf->Close();
  //qcd817emf->Close();
  //qcd23bcf->Close();
  //qcd38bcf->Close();
  //qcd817bcf->Close();
  WZf->Close();
  ZZf->Close();
  
  if (bckg_leadingJetPt.size()>0 && bckg_2leadingJetPt.size()>0 && bckg_3leadingJetPt.size()>0 && bckg_4leadingJetPt.size()>0  && bckg_JetMultiplicity.size()>0 && cold){
    fzj->cd();
    treeBKG_->Fill();
    treeBKG_->Write();
    TH1F *leadhisto=new TH1F("leadhisto","leading jet background contribution",bckg_leadingJetPt.size(),0,bckg_leadingJetPt.size());
    TH1F *leadhisto2=new TH1F("leadhisto2","subleading jet background contribution",bckg_leadingJetPt.size(),0,bckg_leadingJetPt.size());
    TH1F *leadhisto3=new TH1F("leadhisto3","subsubleading jet background contribution",bckg_leadingJetPt.size(),0,bckg_leadingJetPt.size());
    TH1F *leadhisto4=new TH1F("leadhisto4","subsubsubleading jet background contribution",bckg_leadingJetPt.size(),0,bckg_leadingJetPt.size());
    TH1F *multiphisto=new TH1F("multiphisto","jet multiplicity background contribution",bckg_JetMultiplicity.size(),0,bckg_JetMultiplicity.size());

    for (int i=0; i< bckg_leadingJetPt.size(); i++){
      leadhisto->Fill(i,bckg_leadingJetPt[i]);
      leadhisto2->Fill(i,bckg_2leadingJetPt[i]);
      leadhisto3->Fill(i,bckg_3leadingJetPt[i]);
      leadhisto4->Fill(i,bckg_4leadingJetPt[i]);
    }
    leadhisto->Write();
    leadhisto2->Write();
    leadhisto3->Write();
    leadhisto4->Write();
    //fzj->Close();
    for (int i=0; i< bckg_JetMultiplicity.size(); i++){
      multiphisto->Fill(i,bckg_JetMultiplicity[i]);
    }
    multiphisto->Write();
    cold=false;
  }
  return;
}


void evaluateAndFillBackgrounds(TH1* histo, string str){
  if(str=="jet_pT"){
    if (bckg_leadingJetPt.size()==0){
      for(int j=0;j<histo->GetNbinsX();j++){
	bckg_leadingJetPt.push_back(histo->GetBinContent(j+1));
      }
    }
    else {
      for(int j=0;j<histo->GetNbinsX();j++){
	bckg_leadingJetPt[j]+=histo->GetBinContent(j+1);
	
      }
    }
      }
  if(str=="jet_pT2"){
    if (bckg_2leadingJetPt.size()==0){
      for(int j=0;j<histo->GetNbinsX();j++){
	bckg_2leadingJetPt.push_back(histo->GetBinContent(j+1));
      }
    }
    else {
      for(int j=0;j<histo->GetNbinsX();j++){
	bckg_2leadingJetPt[j]+=histo->GetBinContent(j+1);
	    
      }
    }
  }
  if(str=="jet_pT3"){
    if (bckg_3leadingJetPt.size()==0){
      for(int j=0;j<histo->GetNbinsX();j++){
	bckg_3leadingJetPt.push_back(histo->GetBinContent(j+1));
	  }
    }
    else {
	  for(int j=0;j<histo->GetNbinsX();j++){
	    bckg_3leadingJetPt[j]+=histo->GetBinContent(j+1);
	    
	  }
    }
  }
  if(str=="jet_pT4"){
    if (bckg_4leadingJetPt.size()==0){
      for(int j=0;j<histo->GetNbinsX();j++){
	bckg_4leadingJetPt.push_back(histo->GetBinContent(j+1));
      }
    }
    else {
      for(int j=0;j<histo->GetNbinsX();j++){
	    bckg_4leadingJetPt[j]+=histo->GetBinContent(j+1);
	    
      }
    }
  }

  //Jet Multiplicity
  if(str=="jet_Multiplicity"){
    if (bckg_JetMultiplicity.size()==0){
      for(int j=0;j<histo->GetNbinsX();j++){
	bckg_JetMultiplicity.push_back(histo->GetBinContent(j+1));
      }
    }
    else {
      for(int j=0;j<histo->GetNbinsX();j++){
	bckg_JetMultiplicity[j]+=histo->GetBinContent(j+1);
	
      }
    }
  }
}


double numEventsPerStep(string filename, string dir){
  double entries=-999;

  TFile *tmp = TFile::Open(filename.c_str()); //MC file
  tmp->cd(dir.c_str());

  TObject * obj;
  gDirectory->GetObject("numEventsPerStep",obj);

  if(obj) entries = ((TH1F*)obj)->GetBinContent(1);

  tmp->Close();

  return entries;

}

