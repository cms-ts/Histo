#include "tdrStyle.C"
#include "PlotsFeeder.C"
#include "TFile.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include <vector>

  void DataMCValidation(){

  std::vector<TH1D*> IsoEcalplotsBarrelNotRemoved;
  std::vector<TH1*> IsoEcalplotsMC;

  gROOT->LoadMacro("PlotsFeeder.C++");
  PlotsFeeder p;

  int numbofvertices=15;

	gROOT->ForceStyle();
	tdrStyle();
	TFile *dataf = TFile::Open("/gpfs/cms/data/2011/v1/data-v1-singlele-zfilt.root"); //data file

	TDirectory *dir=(TDirectory*)dataf->Get("demo");
	TTree *treeVJ_ = (TTree*)dir->Get("treeVJ_");

	for (int i=1;i<=numbofvertices;i++){
	
	  	
	  IsoEcalplotsMC = p.Loop(i);
		
	  IsoEcalplotsMC[0] -> Draw();
	  IsoEcalplotsMC[1] -> Draw();
	  IsoEcalplotsMC[2] -> Draw();
	  //IsoEcalplotsMC[3] -> Draw();
	  //IsoEcalplotsMC[4] -> Draw();
	  //IsoEcalplotsMC[5] -> Draw();
	  //IsoEcalplotsMC[6] -> Draw();
	  IsoEcalplotsMC[7] -> Draw(); 
	  IsoEcalplotsMC[8] -> Draw();
	  IsoEcalplotsMC[9] -> Draw();
	  //IsoEcalplotsMC[10] -> Draw();
	  //IsoEcalplotsMC[11] -> Draw();
	  //IsoEcalplotsMC[12] -> Draw();
	  //IsoEcalplotsMC[13] -> Draw();      
	 
	  
	  //set the string
	  stringstream oss;
	  oss<<i;
	  string name=" Number of Vertices="+oss.str();
	  string cut="numberOfVertices=="+oss.str();

	  //DATA: scrive gli istogrammi tagliati al numero di verici
	
	  dataf->cd("demo");
	
	//EB data
	TH1D *h_trkEB_data = new TH1D("h_trkEB_data","IsoTracker EB",36,0.,0.09);
	treeVJ_->Draw("IsoTrkEB>>h_trkEB_data",cut.c_str());

	TH1D *h_ieEB_data = new TH1D("h_ieEB_data","IsoEcal EB",28,0.,0.07);
	treeVJ_->Draw("IsoEcalEB>>h_ieEB_data",cut.c_str());

	TH1D *h_ihEB_data = new TH1D("h_ihEB_data","IsoHcal EB",40,0.,0.10);
	treeVJ_->Draw("IsoHcalEB>>h_ihEB_data",cut.c_str());

	//EE data
	TH1D *h_trkEE_data = new TH1D("h_trkEE_data","IsoTracker EE",16,0.,0.04);
	treeVJ_->Draw("IsoTrkEE>>h_trkEE_data",cut.c_str());

	TH1D *h_ieEE_data = new TH1D("h_ieEE_data","IsoEcal EE",20,0.,0.05);
	treeVJ_->Draw("IsoEcalEE>>h_ieEE_data",cut.c_str());

	TH1D *h_ihEE_data = new TH1D("h_ihEE_data","IsoHcal EE",10,0.,0.025);
	treeVJ_->Draw("IsoHcalEE>>h_ihEE_data",cut.c_str());

	
	//Definizione canvas e riempimento
	//EB
	
	TCanvas *Comp = new TCanvas("Comp","Comp",0,0,800,600);
	Comp->Divide(2,3);
	Comp->cd(1);
	MLogAxis(0,1);
	h_ieEB_data->SetTitle(name.c_str());
	h_ieEB_data->SetMarkerColor(kBlack);
	h_ieEB_data->GetXaxis()->SetTitle("IsoEcal Barrel");
	h_ieEB_data->GetYaxis()->SetTitle("Entries");
	h_ieEB_data->SetLineColor(kBlack);
	h_ieEB_data->SetMarkerColor(kBlack);
	h_ieEB_data->Draw("E1");
	IsoEcalplotsMC[1]->SetMarkerColor(kRed);
	IsoEcalplotsMC[1]->SetLineColor(kRed);
	IsoEcalplotsMC[1]->Draw("HIST SAMES");
	
	Comp->Update();
	
	double plotentries = ((h_ieEB_data->Integral()) / IsoEcalplotsMC[1]->Integral()) ;
	IsoEcalplotsMC[1]->Scale(plotentries);
	

	TPaveStats *r2 = (TPaveStats*)IsoEcalplotsMC[1]->FindObject("stats"); 
	r2->SetY1NDC(0.875); 
	r2->SetY2NDC(0.75); 
	r2->SetTextColor(kRed);
	r2->Draw();
	Comp->Update();

	TLegend *leg = new TLegend(0.6,0.75,0.825,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_ieEB_data,"data","p");
	leg->AddEntry( IsoEcalplotsMC[1],"MonteCarlo","l");
	leg->Draw();
	Comp->Update();


	//
	Comp->cd(2);
	MLogAxis(0,1);
	h_ieEE_data->SetTitle(name.c_str());
	h_ieEE_data->SetMarkerColor(kBlack);
	h_ieEE_data->SetLineColor(kBlack);
	h_ieEE_data->GetXaxis()->SetTitle("IsoEcal Endcap");
	h_ieEE_data->GetYaxis()->SetTitle("Entries");
	h_ieEE_data->Draw("E1");
	IsoEcalplotsMC[8]->SetMarkerColor(kRed);
	IsoEcalplotsMC[8]->SetLineColor(kRed);
	IsoEcalplotsMC[8]->Draw("HIST SAMES");
	Comp->Update();
	

	double plotentries3 = ( (h_ieEE_data->Integral())/ IsoEcalplotsMC[8]->Integral());
	IsoEcalplotsMC[8]->Scale(plotentries3);



	TPaveStats *r5 = (TPaveStats*) IsoEcalplotsMC[8]->FindObject("stats"); 
	r5->SetY1NDC(0.878); 
	r5->SetY2NDC(0.75); 
	r5->SetTextColor(kRed);
	r5->Draw();
	Comp->Update();
	
	TLegend *leg3 = new TLegend(0.6,0.75,0.825,0.9);
	leg3->SetBorderSize(0);
	leg3->SetEntrySeparation(0.01);
	leg3->SetFillColor(0);
	leg3->AddEntry(h_ieEE_data,"data","p");
	leg3->AddEntry(IsoEcalplotsMC[8],"MonteCarlo","l");
	leg3->Draw();
	Comp->Update();

	//
	Comp->cd(3);
	MLogAxis(0,1);
	h_ihEB_data->SetTitle(name.c_str());
	h_ihEB_data->SetMarkerColor(kBlack);
	h_ihEB_data->SetLineColor(kBlack);
	h_ihEB_data->GetXaxis()->SetTitle("IsoHcal Barrel");
	h_ihEB_data->GetYaxis()->SetTitle("Entries");
	h_ihEB_data->Draw("E1");
	 IsoEcalplotsMC[2]->SetMarkerColor(kRed);
	 IsoEcalplotsMC[2]->SetLineColor(kRed);
	 IsoEcalplotsMC[2]->Draw("HIST SAMES");
	Comp->Update();

	double plotentries2 = ( (h_ihEB_data->Integral()) / IsoEcalplotsMC[2]->Integral());
	IsoEcalplotsMC[2]->Scale(plotentries2);



	TPaveStats *r3 = (TPaveStats*) IsoEcalplotsMC[2]->FindObject("stats"); 
	r3->SetY1NDC(0.878); 
	r3->SetY2NDC(0.75); 
	r3->SetTextColor(kRed);
	r3->Draw();
	Comp->Update();
	
	TLegend *leg2 = new TLegend(0.6,0.75,0.825,0.9);
	leg2->SetBorderSize(0);
	leg2->SetEntrySeparation(0.01);
	leg2->SetFillColor(0);
	leg2->AddEntry(h_ihEB_data,"data","p");
	leg2->AddEntry( IsoEcalplotsMC[1],"MonteCarlo","l");
	leg2->Draw();
	Comp->Update();

	//
	Comp->cd(4);
	MLogAxis(0,1);
	h_ihEE_data->SetTitle(name.c_str());
	h_ihEE_data->SetMarkerColor(kBlack);
	h_ihEE_data->SetLineColor(kBlack);
	h_ihEE_data->GetXaxis()->SetTitle("IsoHcal Endcap");
	h_ihEE_data->GetYaxis()->SetTitle("Entries");
	h_ihEE_data->Draw("E1");
	IsoEcalplotsMC[9]->SetMarkerColor(kRed);
	IsoEcalplotsMC[9]->SetLineColor(kRed);
	IsoEcalplotsMC[9]->Draw("HIST SAMES");
	Comp->Update();
	
	double plotentries4 = ( (h_ihEE_data->Integral())/ IsoEcalplotsMC[9]->Integral());
	IsoEcalplotsMC[9]->Scale(plotentries4);



	TPaveStats *r6 = (TPaveStats*)IsoEcalplotsMC[9]->FindObject("stats"); 
	r6->SetY1NDC(0.878); 
	r6->SetY2NDC(0.75); 
	r6->SetTextColor(kRed);
	r6->Draw();
	Comp->Update();
	
	TLegend *leg4 = new TLegend(0.6,0.75,0.825,0.9);
	leg4->SetBorderSize(0);
	leg4->SetEntrySeparation(0.01);
	leg4->SetFillColor(0);
	leg4->AddEntry(h_ihEE_data,"data","p");
	leg4->AddEntry(IsoEcalplotsMC[9],"MonteCarlo","l");
	leg4->Draw();
	Comp->Update();

	Comp->cd(5);
	MLogAxis(0,1);
	h_trkEB_data->SetTitle(name.c_str());
	h_trkEB_data->SetMarkerColor(kBlack);
	h_trkEB_data->GetXaxis()->SetTitle("IsoTrk Barrel");
	h_trkEB_data->GetYaxis()->SetTitle("Entries");
	h_trkEB_data->SetLineColor(kBlack);
	h_trkEB_data->SetMarkerColor(kBlack);
	h_trkEB_data->Draw("E1");
	IsoEcalplotsMC[0]->SetMarkerColor(kRed);
	IsoEcalplotsMC[0]->SetLineColor(kRed);
	IsoEcalplotsMC[0]->Draw("HIST SAMES");
	
	Comp->Update();
	
	double plotentries7 = ( (h_trkEB_data->Integral())/ IsoEcalplotsMC[0]->Integral());
	IsoEcalplotsMC[0]->Scale(plotentries7);
	

	TPaveStats *r7 = (TPaveStats*)IsoEcalplotsMC[0]->FindObject("stats"); 
	r7->SetY1NDC(0.875); 
	r7->SetY2NDC(0.75); 
	r7->SetTextColor(kRed);
	r7->Draw();
	Comp->Update();

	TLegend *leg7 = new TLegend(0.6,0.75,0.825,0.9);
	leg7->SetBorderSize(0);
	leg7->SetEntrySeparation(0.01);
	leg7->SetFillColor(0);
	leg7->AddEntry(h_trkEB_data,"data","p");
	leg7->AddEntry( IsoEcalplotsMC[0],"MonteCarlo","l");
	leg7->Draw();

	Comp->cd(6);
	MLogAxis(0,1);
	h_trkEE_data->SetTitle(name.c_str());
	h_trkEE_data->SetMarkerColor(kBlack);
	h_trkEE_data->GetXaxis()->SetTitle("IsoTrk Endcap");
	h_trkEE_data->GetYaxis()->SetTitle("Entries");
	h_trkEE_data->SetLineColor(kBlack);
	h_trkEE_data->SetMarkerColor(kBlack);
	h_trkEE_data->Draw("E1");
	IsoEcalplotsMC[7]->SetMarkerColor(kRed);
	IsoEcalplotsMC[7]->SetLineColor(kRed);
	IsoEcalplotsMC[7]->Draw("HIST SAMES");
	
	Comp->Update();
	
	double plotentries8 = ( (h_trkEE_data->Integral())/ IsoEcalplotsMC[7]->Integral());
	IsoEcalplotsMC[7]->Scale(plotentries8);
	

	TPaveStats *r8 = (TPaveStats*)IsoEcalplotsMC[7]->FindObject("stats"); 
	r8->SetY1NDC(0.875); 
	r8->SetY2NDC(0.75); 
	r8->SetTextColor(kRed);
	r8->Draw();
	Comp->Update();

	TLegend *leg8 = new TLegend(0.6,0.75,0.825,0.9);
	leg8->SetBorderSize(0);
	leg8->SetEntrySeparation(0.01);
	leg8->SetFillColor(0);
	leg8->AddEntry(h_trkEE_data,"data","p");
	leg8->AddEntry(IsoEcalplotsMC[7],"MonteCarlo","l");
	leg8->Draw();

	Comp->Update();



	string picname="Trk-Ecal-Hcal-Isolation"+oss.str()+".png";
	string eps="Trk-Ecal-Hcal-Isolation"+oss.str()+".eps";
	Comp->Print(picname.c_str());
	Comp->Print(eps.c_str());
	oss.clear();
	oss.str("");


	  //IsoEcalplotsMC.push_back(IsoEcalplotsMC[1]);
	  //IsoEcalplotsBarrelNotRemoved.push_back(h_ieEB_data);
	  //cout<<"entries "<<IsoEcalplotsMC[i-1]->GetEntries();
	  //cout<<"entries "<<IsoEcalplotsBarrelNotRemoved[i-1]->GetEntries();
	
	}


	  //if (h_ieEB_data) delete h_ieEB_data;
	  //if (h_ihEB_data) delete h_ihEB_:data;
	  //if (h_ieEE_data) delete h_ieEE_data;
	  //if (h_ihEE_data) delete h_ihEE_data;	
	  // if (h_ieEB_rem) delete h_ieEB_rem;
	  //if (h_ihEB_rem) delete h_ihEB_rem;
	  //if (h_ieEE_rem) delete h_ieEE_rem;
	  //if (h_ihEE_rem) delete h_ihEE_rem;
	  //if (Comp) delete Comp;
	  //if (r2) delete r2;
	  //if (leg) delete leg;
	  //if (r3) delete r3;
	  //if (r5) delete r5;
	  //if (r6) delete r6;

	
	return;
	}



