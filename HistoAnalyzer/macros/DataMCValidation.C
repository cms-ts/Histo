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
	std::vector<TH1*> IsoPlotsMC;

	gROOT->LoadMacro("PlotsFeeder.C++");
	PlotsFeeder p;

	int numbofvertices=15;

	gROOT->ForceStyle();
	tdrStyle();
	TFile *dataf = TFile::Open("/gpfs/cms/data/2011/v1/data-v1-singlele-zfilt.root"); //data file

	TDirectory *dir=(TDirectory*)dataf->Get("demo");
	TTree *treeVJ_ = (TTree*)dir->Get("treeVJ_");

	//DEFINITIONS (please outside the loop!)
	stringstream oss;
	string name;
	string cut;

	//HISTOGRAMS FOR VTX CUT
	//EB data
	TH1D* h_trkEB_data = (TH1D*)gDirectory->GetList()->FindObject("h_trkEB_data");
	if (h_trkEB_data) delete h_trkEB_data;
	h_trkEB_data = new TH1D("h_trkEB_data","IsoTracker EB",36,0.,0.09);

	TH1D* h_ieEB_data = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB_data");
	if (h_ieEB_data) delete h_ieEB_data;
	h_ieEB_data = new TH1D("h_ieEB_data","IsoEcal EB",28,0.,0.07);

	TH1D* h_ihEB_data = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB_data");
	if (h_ihEB_data) delete h_ihEB_data;
	h_ihEB_data = new TH1D("h_ihEB_data","IsoHcal EB",40,0.,0.10);

	//EE data
	TH1D* h_trkEE_data = (TH1D*)gDirectory->GetList()->FindObject("h_trkEE_data");
	if (h_trkEE_data) delete h_trkEE_data;
	h_trkEE_data = new TH1D("h_trkEE_data","IsoTracker EE",16,0.,0.04);

	TH1D* h_ieEE_data = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE_data");
	if (h_ieEE_data) delete h_ieEE_data;
	h_ieEE_data = new TH1D("h_ieEE_data","IsoEcal EE",20,0.,0.05);

	TH1D* h_ihEE_data = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE_data");
	if (h_ihEE_data) delete h_ihEE_data;
	h_ihEE_data = new TH1D("h_ihEE_data","IsoHcal EE",10,0.,0.025);

	//--------------//
	//    TOTALE    //
	//--------------//
	//EB data
	TH1D* h_trkEB = (TH1D*)gDirectory->GetList()->FindObject("h_trkEB");
	if (h_trkEB) delete h_trkEB;
	h_trkEB = new TH1D("h_trkEB","IsoTracker EB",36,0.,0.09);

	TH1D* h_ieEB = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB");
	if (h_ieEB) delete h_ieEB;
	h_ieEB = new TH1D("h_ieEB","IsoEcal EB",28,0.,0.07);

	TH1D* h_ihEB = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB");
	if (h_ihEB) delete h_ihEB;
	h_ihEB = new TH1D("h_ihEB","IsoHcal EB",40,0.,0.10);

	//EB mc
	TH1D* h_trkEB_mc = (TH1D*)gDirectory->GetList()->FindObject("h_trkEB_mc");
	if (h_trkEB_mc) delete h_trkEB_mc;
	h_trkEB_mc = new TH1D("h_trkEB_mc","IsoTracker EB_mc",36,0.,0.09);

	TH1D* h_ieEB_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ieEB_mc");
	if (h_ieEB_mc) delete h_ieEB_mc;
	h_ieEB_mc = new TH1D("h_ieEB_mc","IsoEcal EB_mc",28,0.,0.07);

	TH1D* h_ihEB_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ihEB_mc");
	if (h_ihEB_mc) delete h_ihEB_mc;
	h_ihEB_mc = new TH1D("h_ihEB_mc","IsoHcal EB_mc",40,0.,0.10);

	//EE data
	TH1D* h_trkEE = (TH1D*)gDirectory->GetList()->FindObject("h_trkEE");
	if (h_trkEE) delete h_trkEE;
	h_trkEE = new TH1D("h_trkEE","IsoTracker EE",16,0.,0.04);

	TH1D* h_ieEE = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE");
	if (h_ieEE) delete h_ieEE;
	h_ieEE = new TH1D("h_ieEE","IsoEcal EE",20,0.,0.05);

	TH1D* h_ihEE = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE");
	if (h_ihEE) delete h_ihEE;
	h_ihEE = new TH1D("h_ihEE","IsoHcal EE",10,0.,0.025);

	//EE mc
	TH1D* h_trkEE_mc = (TH1D*)gDirectory->GetList()->FindObject("h_trkEE_mc");
	if (h_trkEE_mc) delete h_trkEE_mc;
	h_trkEE_mc = new TH1D("h_trkEE_mc","IsoTracker EE_mc",16,0.,0.04);

	TH1D* h_ieEE_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ieEE_mc");
	if (h_ieEE_mc) delete h_ieEE_mc;
	h_ieEE_mc = new TH1D("h_ieEE_mc","IsoEcal EE_mc",20,0.,0.05);

	TH1D* h_ihEE_mc = (TH1D*)gDirectory->GetList()->FindObject("h_ihEE_mc");
	if (h_ihEE_mc) delete h_ihEE_mc;
	h_ihEE_mc = new TH1D("h_ihEE_mc","IsoHcal EE_mc",10,0.,0.025);




	//----------
	//  LOOP!
	for (int i=1;i<=numbofvertices;i++){


		IsoPlotsMC = p.Loop(i);


		IsoPlotsMC[0] -> Draw(); //EB//IsoTrk EB PUR
		IsoPlotsMC[1] -> Draw();     //IsoEcal EB PUR
		IsoPlotsMC[2] -> Draw();     //IsoHcal EB PUR
		//  IsoPlotsMC[3] -> Draw();     //HE EB PUR
		//  IsoPlotsMC[4] -> Draw();     //DeltaPhiTkClu EB PUR
		//  IsoPlotsMC[5] -> Draw();     //DeltaEtaTkClu EB PUR
		//  IsoPlotsMC[6] -> Draw();     //SigmaIeIe EB PUR
		IsoPlotsMC[7] -> Draw(); //EE//IsoTrk EE PUR
		IsoPlotsMC[8] -> Draw();     //IsoEcal EE PUR
		IsoPlotsMC[9] -> Draw();     //IsoHcal EE PUR
		//  IsoPlotsMC[10] -> Draw();    //HE EE PUR
		//  IsoPlotsMC[11] -> Draw();    //DeltaPhiTkClu EE PUR
		//  IsoPlotsMC[12] -> Draw();    //DeltaEtaTkClu EE PUR
		//  IsoPlotsMC[13] -> Draw();    //SigmaIeIe EE PUR


		//set the string
		oss<<i;
		name=" Number of Vertices="+oss.str();
		cut="numberOfVertices=="+oss.str();

		//DATA: scrive gli istogrammi tagliati al numero di verici
		//EB data
		treeVJ_->Draw("IsoTrkEB>>h_trkEB_data",cut.c_str());
		treeVJ_->Draw("IsoEcalEB>>h_ieEB_data",cut.c_str());
		treeVJ_->Draw("IsoHcalEB>>h_ihEB_data",cut.c_str());

		//EE data
		treeVJ_->Draw("IsoTrkEE>>h_trkEE_data",cut.c_str());
		treeVJ_->Draw("IsoEcalEE>>h_ieEE_data",cut.c_str());
		treeVJ_->Draw("IsoHcalEE>>h_ihEE_data",cut.c_str());


		//Definizione canvas e riempimento
		//EB
		TCanvas* Comp = (TCanvas*)gDirectory->GetList()->FindObject("Comp");
		if (Comp) delete Comp;
		Comp = new TCanvas("Comp","Comp",0,0,800,600);
		Comp->Divide(2,3);
		Comp->cd(1);

		gPad->SetLogy(1);
		h_ieEB_data->SetTitle(name.c_str());
		h_ieEB_data->SetMarkerColor(kBlack);
		h_ieEB_data->GetXaxis()->SetTitle("IsoEcal Barrel");
		h_ieEB_data->GetYaxis()->SetTitle("Entries");
		h_ieEB_data->SetLineColor(kBlack);
		h_ieEB_data->SetMarkerColor(kBlack);
		h_ieEB_data->Draw("E1");
		IsoPlotsMC[1]->SetMarkerColor(kRed);
		IsoPlotsMC[1]->SetLineColor(kRed);
		IsoPlotsMC[1]->Draw("HIST SAMES");
		Comp->Update();
		double plotentries = ((h_ieEB_data->Integral()) / IsoPlotsMC[1]->Integral()) ;
		IsoPlotsMC[1]->Scale(plotentries);

		TPaveStats *r2 = (TPaveStats*)IsoPlotsMC[1]->FindObject("stats"); 
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
		leg->AddEntry( IsoPlotsMC[1],"MonteCarlo","l");
		leg->Draw();
		Comp->Update();


		//
		Comp->cd(2);
		gPad->SetLogy(1);
		h_ieEE_data->SetTitle(name.c_str());
		h_ieEE_data->SetMarkerColor(kBlack);
		h_ieEE_data->SetLineColor(kBlack);
		h_ieEE_data->GetXaxis()->SetTitle("IsoEcal Endcap");
		h_ieEE_data->GetYaxis()->SetTitle("Entries");
		h_ieEE_data->Draw("E1");
		IsoPlotsMC[8]->SetMarkerColor(kRed);
		IsoPlotsMC[8]->SetLineColor(kRed);
		IsoPlotsMC[8]->Draw("HIST SAMES");
		Comp->Update();
		double plotentries3 = ( (h_ieEE_data->Integral())/ IsoPlotsMC[8]->Integral());
		IsoPlotsMC[8]->Scale(plotentries3);

		TPaveStats *r5 = (TPaveStats*) IsoPlotsMC[8]->FindObject("stats"); 
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
		leg3->AddEntry(IsoPlotsMC[8],"MonteCarlo","l");
		leg3->Draw();
		Comp->Update();

		//
		Comp->cd(3);
		gPad->SetLogy(1);
		h_ihEB_data->SetTitle(name.c_str());
		h_ihEB_data->SetMarkerColor(kBlack);
		h_ihEB_data->SetLineColor(kBlack);
		h_ihEB_data->GetXaxis()->SetTitle("IsoHcal Barrel");
		h_ihEB_data->GetYaxis()->SetTitle("Entries");
		h_ihEB_data->Draw("E1");
		IsoPlotsMC[2]->SetMarkerColor(kRed);
		IsoPlotsMC[2]->SetLineColor(kRed);
		IsoPlotsMC[2]->Draw("HIST SAMES");
		Comp->Update();
		double plotentries2 = ( (h_ihEB_data->Integral()) / IsoPlotsMC[2]->Integral());
		IsoPlotsMC[2]->Scale(plotentries2);

		TPaveStats *r3 = (TPaveStats*) IsoPlotsMC[2]->FindObject("stats"); 
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
		leg2->AddEntry( IsoPlotsMC[2],"MonteCarlo","l");
		leg2->Draw();
		Comp->Update();

		//
		Comp->cd(4);
		gPad->SetLogy(1);
		h_ihEE_data->SetTitle(name.c_str());
		h_ihEE_data->SetMarkerColor(kBlack);
		h_ihEE_data->SetLineColor(kBlack);
		h_ihEE_data->GetXaxis()->SetTitle("IsoHcal Endcap");
		h_ihEE_data->GetYaxis()->SetTitle("Entries");
		h_ihEE_data->Draw("E1");
		IsoPlotsMC[9]->SetMarkerColor(kRed);
		IsoPlotsMC[9]->SetLineColor(kRed);
		IsoPlotsMC[9]->Draw("HIST SAMES");
		Comp->Update();
		double plotentries4 = ( (h_ihEE_data->Integral())/ IsoPlotsMC[9]->Integral());
		IsoPlotsMC[9]->Scale(plotentries4);

		TPaveStats *r6 = (TPaveStats*)IsoPlotsMC[9]->FindObject("stats"); 
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
		leg4->AddEntry(IsoPlotsMC[9],"MonteCarlo","l");
		leg4->Draw();
		Comp->Update();

		Comp->cd(5);
		gPad->SetLogy(1);
		h_trkEB_data->SetTitle(name.c_str());
		h_trkEB_data->SetMarkerColor(kBlack);
		h_trkEB_data->GetXaxis()->SetTitle("IsoTrk Barrel");
		h_trkEB_data->GetYaxis()->SetTitle("Entries");
		h_trkEB_data->SetLineColor(kBlack);
		h_trkEB_data->SetMarkerColor(kBlack);
		h_trkEB_data->Draw("E1");
		IsoPlotsMC[0]->SetMarkerColor(kRed);
		IsoPlotsMC[0]->SetLineColor(kRed);
		IsoPlotsMC[0]->Draw("HIST SAMES");
		Comp->Update();
		double plotentries7 = ( (h_trkEB_data->Integral())/ IsoPlotsMC[0]->Integral());
		IsoPlotsMC[0]->Scale(plotentries7);

		TPaveStats *r7 = (TPaveStats*)IsoPlotsMC[0]->FindObject("stats"); 
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
		leg7->AddEntry( IsoPlotsMC[0],"MonteCarlo","l");
		leg7->Draw();

		Comp->cd(6);
		gPad->SetLogy(1);
		h_trkEE_data->SetTitle(name.c_str());
		h_trkEE_data->GetXaxis()->SetTitle("IsoTrk Endcap");
		h_trkEE_data->GetYaxis()->SetTitle("Entries");
		h_trkEE_data->SetLineColor(kBlack);
		h_trkEE_data->SetMarkerColor(kBlack);
		h_trkEE_data->Draw("E1");
		IsoPlotsMC[7]->SetMarkerColor(kRed);
		IsoPlotsMC[7]->SetLineColor(kRed);
		IsoPlotsMC[7]->Draw("HIST SAMES");
		Comp->Update();
		double plotentries8 = ( (h_trkEE_data->Integral())/ IsoPlotsMC[7]->Integral());
		IsoPlotsMC[7]->Scale(plotentries8);

		TPaveStats *r8 = (TPaveStats*)IsoPlotsMC[7]->FindObject("stats"); 
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
		leg8->AddEntry(IsoPlotsMC[7],"MonteCarlo","l");
		leg8->Draw();
		Comp->Update();

		string picname="Trk-Ecal-Hcal-Isolation"+oss.str()+".png";
		string eps="Trk-Ecal-Hcal-Isolation"+oss.str()+".eps";
		Comp->Print(picname.c_str());
		Comp->Print(eps.c_str());
		oss.clear();
		oss.str("");


		//TOTALE
		h_ieEB->Add(h_ieEB_data);
		h_ieEB_mc->Add(IsoPlotsMC[1]);

		h_ihEB->Add(h_ihEB_data);
		h_ihEB_mc->Add(IsoPlotsMC[2]);

		h_trkEB->Add(h_trkEB_data);
		h_trkEB_mc->Add(IsoPlotsMC[0]);

		h_ieEE->Add(h_ieEE_data);
		h_ieEE_mc->Add(IsoPlotsMC[8]);

		h_ihEE->Add(h_ihEE_data);
		h_ihEE_mc->Add(IsoPlotsMC[9]);

		h_trkEE->Add(h_trkEE_data);
		h_trkEE_mc->Add(IsoPlotsMC[7]);



	}

	//TOTALE
	TCanvas* Tot = (TCanvas*)gDirectory->GetList()->FindObject("Tot");
	if (Tot) delete Tot;
	Tot = new TCanvas("Totale","Totale",0,0,800,600);
	Tot->Divide(2,3);

	Tot->cd(1);
	gPad->SetLogy(1);
	h_ieEB->GetXaxis()->SetTitle("IsoEcal Barrel");
	h_ieEB->GetYaxis()->SetTitle("Entries");
	h_ieEB->SetLineColor(kBlack);
	h_ieEB->SetMarkerColor(kBlack);
	h_ieEB->Draw("E1");
	h_ieEB_mc->SetMarkerColor(kRed);
	h_ieEB_mc->SetLineColor(kRed);
	h_ieEB_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t3 = (TPaveStats*)h_ieEB_mc->FindObject("stats"); 
	t3->SetY1NDC(0.875); 
	t3->SetY2NDC(0.75); 
	t3->SetTextColor(kRed);
	t3->Draw();
	Tot->Update();

	Tot->cd(2);
	gPad->SetLogy(1);
	h_ieEE->GetXaxis()->SetTitle("IsoEcal Endcap");
	h_ieEE->GetYaxis()->SetTitle("Entries");
	h_ieEE->SetLineColor(kBlack);
	h_ieEE->SetMarkerColor(kBlack);
	h_ieEE->Draw("E1");
	h_ieEE_mc->SetMarkerColor(kRed);
	h_ieEE_mc->SetLineColor(kRed);
	h_ieEE_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t4 = (TPaveStats*)h_ieEE_mc->FindObject("stats"); 
	t4->SetY1NDC(0.875); 
	t4->SetY2NDC(0.75); 
	t4->SetTextColor(kRed);
	t4->Draw();
	Tot->Update();

//////////////////

	Tot->cd(3);
	gPad->SetLogy(1);
	h_ihEB->GetXaxis()->SetTitle("IsoHcal Barrel");
	h_ihEB->GetYaxis()->SetTitle("Entries");
	h_ihEB->SetLineColor(kBlack);
	h_ihEB->SetMarkerColor(kBlack);
	h_ihEB->Draw("E1");
	h_ihEB_mc->SetMarkerColor(kRed);
	h_ihEB_mc->SetLineColor(kRed);
	h_ihEB_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t5 = (TPaveStats*)h_ihEB_mc->FindObject("stats"); 
	t5->SetY1NDC(0.875); 
	t5->SetY2NDC(0.75); 
	t5->SetTextColor(kRed);
	t5->Draw();
	Tot->Update();

	Tot->cd(4);
	gPad->SetLogy(1);
	h_ihEE->GetXaxis()->SetTitle("IsoHcal Endcap");
	h_ihEE->GetYaxis()->SetTitle("Entries");
	h_ihEE->SetLineColor(kBlack);
	h_ihEE->SetMarkerColor(kBlack);
	h_ihEE->Draw("E1");
	h_ihEE_mc->SetMarkerColor(kRed);
	h_ihEE_mc->SetLineColor(kRed);
	h_ihEE_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t6 = (TPaveStats*)h_ihEE_mc->FindObject("stats"); 
	t6->SetY1NDC(0.875); 
	t6->SetY2NDC(0.75); 
	t6->SetTextColor(kRed);
	t6->Draw();
	Tot->Update();



//////////////

	Tot->cd(5);
	gPad->SetLogy(1);
	h_trkEB->GetXaxis()->SetTitle("IsoTrk Barrel");
	h_trkEB->GetYaxis()->SetTitle("Entries");
	h_trkEB->SetLineColor(kBlack);
	h_trkEB->SetMarkerColor(kBlack);
	h_trkEB->Draw("E1");
	h_trkEB_mc->SetMarkerColor(kRed);
	h_trkEB_mc->SetLineColor(kRed);
	h_trkEB_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t1 = (TPaveStats*)h_trkEB_mc->FindObject("stats"); 
	t1->SetY1NDC(0.875); 
	t1->SetY2NDC(0.75); 
	t1->SetTextColor(kRed);
	t1->Draw();
	Tot->Update();

	Tot->cd(6);
	gPad->SetLogy(1);
	h_trkEE->GetXaxis()->SetTitle("IsoTrk Endcap");
	h_trkEE->GetYaxis()->SetTitle("Entries");
	h_trkEE->SetLineColor(kBlack);
	h_trkEE->SetMarkerColor(kBlack);
	h_trkEE->Draw("E1");
	h_trkEE_mc->SetMarkerColor(kRed);
	h_trkEE_mc->SetLineColor(kRed);
	h_trkEE_mc->Draw("HIST SAMES");
	Tot->Update();
	TPaveStats *t2 = (TPaveStats*)h_trkEE_mc->FindObject("stats"); 
	t2->SetY1NDC(0.875); 
	t2->SetY2NDC(0.75); 
	t2->SetTextColor(kRed);
	t2->Draw();
	Tot->Update();




	Tot->Print("totale.eps");
	Tot->Print("totale.png");

return;
}



