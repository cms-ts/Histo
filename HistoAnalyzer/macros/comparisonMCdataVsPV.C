#include "MMutil.C"
#include "tdrStyle.C"
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include <vector>


void comparisonMCdataVsPV(){

  std::vector<TH1D*> IsoEcalplotsBarrelNotRemoved;
  std::vector<TH1D*> IsoEcalplotsBarrelRemoved;

  int numbofvertices=15;

	gROOT->ForceStyle();
	setTDRStyle();
	TFile *dataf = TFile::Open("rfio:/castor/cern.ch/user/m/marone/ZJets/results/PreselectionMay10_v1_1.root"); //data file
	TFile *dataremoved = TFile::Open("rfio:/castor/cern.ch/user/m/marone/ZJets/results/PreselectionMay10PURemoved_v1_1.root");


	for (int i=1;i<numbofvertices;i++){
	  //set the string
	  stringstream oss;
	  oss<<i;
	  string name=" Number of Vertices="+oss.str();
	  cout<<name<<endl;
	  string cut="numberOfVertices=="+oss.str();
	  cout<<cut<<endl;

	//DATA	
	dataf->cd("demo");

	//Creazione degli istogrammi
	//FIXME da duplicare per il file di MC
	//EB data

	TH1D *h_ieEB_data = new TH1D("h_ieEB_data","IsoEcal EB",40,0.,0.40);
	treeVJ_->Draw("IsoEcalEB>>h_ieEB_data",cut.c_str());

	TH1D *h_ihEB_data = new TH1D("h_ihEB_data","IsoHcal EB",40,0.,0.40);
	treeVJ_->Draw("IsoHcalEB>>h_ihEB_data",cut.c_str());

	//EE data

	TH1D *h_ieEE_data = new TH1D("h_ieEE_data","IsoEcal EE",40,0.,0.40);
	treeVJ_->Draw("IsoEcalEE>>h_ieEE_data",cut.c_str());

	TH1D *h_ihEE_data = new TH1D("h_ihEE_data","IsoHcal EE",40,0.,0.40);
	treeVJ_->Draw("IsoHcalEE>>h_ihEE_data",cut.c_str());


	//DATA REMOVED PU
	dataremoved->cd("demo");
	//Numero di entries

	//EB data


	TH1D *h_ieEB_rem = new TH1D("h_ieEB_rem","IsoEcal EB",40,0.,0.40);
	treeVJ_->Draw("IsoEcalEB>>h_ieEB_rem",cut.c_str());


	TH1D *h_ihEB_rem = new TH1D("h_ihEB_rem","IsoHcal EB",40,0.,0.40);
	treeVJ_->Draw("IsoHcalEB>>h_ihEB_rem",cut.c_str());

	//EE data


	TH1D *h_ieEE_rem = new TH1D("h_ieEE_rem","IsoEcal EE",40,0.,0.40);
	treeVJ_->Draw("IsoEcalEE>>h_ieEE_rem",cut.c_str());


	TH1D *h_ihEE_rem = new TH1D("h_ihEE_rem","IsoHcal EE",40,0.,0.40);
	treeVJ_->Draw("IsoHcalEE>>h_ihEE_rem",cut.c_str());


	//Definizione canvas e riempimento
	//EB

	TCanvas *Comp = new TCanvas("Comp","Comp",0,0,800,600);
	Comp->Divide(2,2);
	Comp->cd(1);
	MLogAxis(0,1);
	h_ieEB_data->SetTitle(name.c_str());
	h_ieEB_data->SetMarkerColor(kBlack);
	h_ieEB_data->GetXaxis()->SetTitle("IsoECAL Barrel");
	h_ieEB_data->GetYaxis()->SetTitle("Entries");
	h_ieEB_data->SetLineColor(kBlack);
	h_ieEB_data->SetMarkerColor(kBlack);
	h_ieEB_data->Draw("E1");
	h_ieEB_rem->SetMarkerColor(kRed);
	h_ieEB_rem->SetLineColor(kRed);
	h_ieEB_rem->Draw("E1 SAMES");
	Comp->Update();
	TPaveStats *r2 = (TPaveStats*)h_ieEB_rem->FindObject("stats"); 
	r2->SetY1NDC(0.878); 
	r2->SetY2NDC(0.75); 
	r2->SetTextColor(kRed);
	r2->Draw();
	Comp->Update();
	TLegend *leg = new TLegend(0.4,0.75,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_ieEB_data,"data","p");
	leg->AddEntry(h_ieEB_rem,"data removed PU","p");
	leg->Draw();
	Comp->Update();

	Comp->cd(2);
	MLogAxis(0,1);
	h_ihEB_data->SetTitle(name.c_str());
	h_ihEB_data->SetMarkerColor(kBlack);
	h_ihEB_data->SetLineColor(kBlack);
	h_ihEB_data->GetXaxis()->SetTitle("IsoHCAL Barrel");
	h_ihEB_data->GetYaxis()->SetTitle("Entries");
	h_ihEB_data->Draw("E1");
	h_ihEB_rem->SetMarkerColor(kRed);
	h_ihEB_rem->SetLineColor(kRed);
	h_ihEB_rem->Draw("E1 SAMES");
	Comp->Update();

	TPaveStats *r3 = (TPaveStats*)h_ihEB_rem->FindObject("stats"); 
	r3->SetY1NDC(0.878); 
	r3->SetY2NDC(0.75); 
	r3->SetTextColor(kRed);
	r3->Draw();
	Comp->Update();
	
	TLegend *leg = new TLegend(0.4,0.75,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_ihEB_data,"data","p");
	leg->AddEntry(h_ihEB_rem,"data removed PU","p");
	leg->Draw();
	Comp->Update();

	Comp->cd(3);
	MLogAxis(0,1);
	h_ieEE_data->SetTitle(name.c_str());
	h_ieEE_data->SetMarkerColor(kBlack);
	h_ieEE_data->SetLineColor(kBlack);
	h_ieEE_data->GetXaxis()->SetTitle("IsoECAL Endcap");
	h_ieEE_data->GetYaxis()->SetTitle("Entries");
	h_ieEE_data->Draw("E1");
	h_ieEE_rem->SetMarkerColor(kRed);
	h_ieEE_rem->SetLineColor(kRed);
	h_ieEE_rem->Draw("E1 SAMES");
	Comp->Update();
	
	TPaveStats *r5 = (TPaveStats*)h_ieEE_rem->FindObject("stats"); 
	r5->SetY1NDC(0.878); 
	r5->SetY2NDC(0.75); 
	r5->SetTextColor(kRed);
	r5->Draw();
	Comp->Update();
	
	TLegend *leg = new TLegend(0.4,0.75,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_ieEE_data,"data","p");
	leg->AddEntry(h_ieEE_rem,"data removed PU","p");
	leg->Draw();
	Comp->Update();


	Comp->cd(4);
	MLogAxis(0,1);
	h_ihEE_data->SetTitle(name.c_str());
	h_ihEE_data->SetMarkerColor(kBlack);
	h_ihEE_data->SetLineColor(kBlack);
	h_ihEE_data->GetXaxis()->SetTitle("IsoHCAL Endcap");
	h_ihEE_data->GetYaxis()->SetTitle("Entries");
	h_ihEE_data->Draw("E1");
	h_ihEE_rem->SetMarkerColor(kRed);
	h_ihEE_rem->SetLineColor(kRed);
	h_ihEE_rem->Draw("E1 SAMES");
	Comp->Update();
	
	TPaveStats *r6 = (TPaveStats*)h_ihEE_rem->FindObject("stats"); 
	r6->SetY1NDC(0.878); 
	r6->SetY2NDC(0.75); 
	r6->SetTextColor(kRed);
	r6->Draw();
	Comp->Update();
	
	TLegend *leg = new TLegend(0.4,0.75,0.8,0.9);
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.01);
	leg->SetFillColor(0);
	leg->AddEntry(h_ihEE_data,"data","p");
	leg->AddEntry(h_ihEE_rem,"data removed PU","p");
	leg->Draw();
	Comp->Update();

	string picname="IsolationWithWithoutPU"+oss.str()+".png";
	Comp->Print(picname.c_str());
	  oss.clear();
	  oss.str("");

	  IsoEcalplotsBarrelRemoved.push_back(h_ieEB_rem);
	  IsoEcalplotsBarrelNotRemoved.push_back(h_ieEB_data);
	  cout<<"entries "<<IsoEcalplotsBarrelRemoved[i-1]->GetEntries();
	  cout<<"entries "<<IsoEcalplotsBarrelNotRemoved[i-1]->GetEntries();
	}

	  //if (h_ieEB_data) delete h_ieEB_data;
	  //if (h_ihEB_data) delete h_ihEB_data;
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

	TCanvas *ComparisonRemoved = new TCanvas("ComparisonRemoved","ComparisonRemoved",0,0,800,600);
	MLogAxis(0,1);
	TLegend *lege= new TLegend(0.4,0.75,0.8,0.9);
	  stringstream nu;
	for (int i=1;i<numbofvertices;i++){
	  nu<<i;
	  cout<<"a"<<endl;
	  string name="Vertices="+nu.str();
	  IsoEcalplotsBarrelRemoved[i-1]->SetMarkerColor(i);
	  IsoEcalplotsBarrelRemoved[i-1]->Sumw2();
	  IsoEcalplotsBarrelRemoved[i-1]->SetLineColor(i);
	  cout<<"aa"<<endl;
	  double plotentries=1.0/(double)IsoEcalplotsBarrelRemoved[i-1]->GetEntries();
	  IsoEcalplotsBarrelRemoved[i-1]->Scale(plotentries);
	  if (i==1){
	  cout<<"ab"<<endl;
	    //TPaveStats *r7 = (TPaveStats*)IsoEcalplotsBarrelRemoved[i-1]->FindObject("stats");
	    //r7->SetOptStat(0);
	    IsoEcalplotsBarrelRemoved[i-1]->SetTitle("Comparison between PURemoved distributions");
	    IsoEcalplotsBarrelRemoved[i-1]->GetXaxis()->SetTitle("IsoECAL Barrel");
	    IsoEcalplotsBarrelRemoved[i-1]->GetYaxis()->SetTitle("Fraction of Events");
	    IsoEcalplotsBarrelRemoved[i-1]->Draw("E1");
	    lege->AddEntry( IsoEcalplotsBarrelRemoved[i-1],name.c_str(),"p");
	  }
	  else{
	  cout<<"ac"<<endl;
	    IsoEcalplotsBarrelRemoved[i-1]->Draw("E1 SAMES");
	    lege->AddEntry( IsoEcalplotsBarrelRemoved[i-1],name.c_str(),"p");
	  }
	  nu.clear();
	  nu.str("");
	}
	ComparisonRemoved->Update();
	lege->SetBorderSize(0);
	lege->SetEntrySeparation(0.01);
	lege->SetFillColor(0);
	lege->Draw();
      	ComparisonRemoved->Print("AllRemoved.png");

	TCanvas *ComparisonNotRemoved = new TCanvas("ComparisonNotRemoved","ComparisonNotRemoved",0,0,800,600);
	MLogAxis(0,1);
	TLegend *lege= new TLegend(0.4,0.75,0.8,0.9);
	  stringstream nu;
	for (int i=1;i<numbofvertices;i++){
	  nu<<i;
	  cout<<"a"<<endl;
	  string name="Vertices="+nu.str();
	  IsoEcalplotsBarrelNotRemoved[i-1]->SetMarkerColor(i);
	  IsoEcalplotsBarrelNotRemoved[i-1]->Sumw2();
	  IsoEcalplotsBarrelNotRemoved[i-1]->SetLineColor(i);
	  cout<<"aa"<<endl;
	  double plotentries=1.0/(double)IsoEcalplotsBarrelNotRemoved[i-1]->GetEntries();
	  IsoEcalplotsBarrelNotRemoved[i-1]->Scale(plotentries);
	  if (i==1){
	  cout<<"ab"<<endl;
	    //TPaveStats *r7 = (TPaveStats*)IsoEcalplotsBarrelNotRemoved[i-1]->FindObject("stats");
	    //r7->SetOptStat(0);
	    IsoEcalplotsBarrelNotRemoved[i-1]->SetTitle("Comparison between PU Not Removed distributions");
	    IsoEcalplotsBarrelNotRemoved[i-1]->GetXaxis()->SetTitle("IsoECAL Barrel");
	    IsoEcalplotsBarrelNotRemoved[i-1]->GetYaxis()->SetTitle("Fraction of Events");
	    IsoEcalplotsBarrelNotRemoved[i-1]->Draw("E1");
	    lege->AddEntry( IsoEcalplotsBarrelNotRemoved[i-1],name.c_str(),"p");
	  }
	  else{
	  cout<<"ac"<<endl;
	    IsoEcalplotsBarrelNotRemoved[i-1]->Draw("E1 SAMES");
	    lege->AddEntry( IsoEcalplotsBarrelNotRemoved[i-1],name.c_str(),"p");
	  }
	  nu.clear();
	  nu.str("");
	}
	ComparisonNotRemoved->Update();
	lege->SetBorderSize(0);
	lege->SetEntrySeparation(0.01);
	lege->SetFillColor(0);
	lege->Draw();

      	ComparisonNotRemoved->Print("AllNotRemoved.png");
	
	return;

}
