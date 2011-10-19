#define HLTAnalysis_cxx
#include "HLTAnalysis.h"
#include <TProfile.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TString.h>
#include <TMath.h>
#include <TPaveStats.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "tdrStyle.C"


using namespace std;

void HLTAnalysis::Loop()
{

	//   In a ROOT session, you can do:
	//      Root > .L HLTAnalysis.C
	//      Root > HLTAnalysis t
	//      Root > t.GetEntry(12); // Fill t data members with entry number 12
	//      Root > t.Show();       // Show values of entry 12
	//      Root > t.Show(16);     // Read and show values of entry 16
	//      Root > t.Loop();       // Loop on all entries
	//

	//     This is the loop skeleton where:
	//    jentry is the global entry number in the chain
	//    ientry is the entry number in the current Tree
	//  Note that the argument to GetEntry must be:
	//    jentry for TChain::GetEntry
	//    ientry for TTree::GetEntry and TBranch::GetEntry
	//
	//       To read only selected branches, Insert statements like:
	// METHOD1:
	//    fChain->SetBranchStatus("*",0);  // disable all branches
	//    fChain->SetBranchStatus("branchname",1);  // activate branchname
	// METHOD2: replace line
	//    fChain->GetEntry(jentry);       //read all branches
	//by  b_branchname->GetEntry(ientry); //read only this branch

	tdrStyle();
	int maxRun=0;
	int minRun=0;
	int maxPres=0;
	double maxRatio=1.1;
	//string paths[6]={"HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v4","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v5","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v6"};//May10 - Jul05 //controlla che non ricordo bene

	//string paths[6]={"HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass30_v6"};//Aug05

	string paths[6]={"HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass30_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass30_v7","HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_Ele17_v1"};//Aug05
	
	bool forminRun=true;
	Long64_t nentries = fChain->GetEntriesFast();
	cout << nentries << " numero di entries \n";
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++){  //nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry); // nbytes += nb;
	
	if(forminRun && (vRun->size()!=0)){minRun=vRun->at(0); forminRun=false;}
	if((vRun->size()!=0) && (vRun->at(0)>maxRun)){maxRun=vRun->at(0);}
	if(vRun->size()!=0) cout <<"Entry "<<jentry<<" Run number "<<vRun->at(0)<<"\n";
	}

cout << "FIRST RUN "<< minRun << "\n";
cout << "LAST RUN "<< maxRun << "\n";

	TCanvas* Presc = (TCanvas*)gDirectory->GetList()->FindObject("Presc");
	if (Presc) delete Presc;
	Presc = new TCanvas("Presc","Presc",0,0,900,600);

	TH1I* histogram = (TH1I*)gDirectory->GetList()->FindObject("histogram");
	if (histogram) delete histogram;


	std::vector<TH1I*> vec;
	vec.clear();

	TLegend *leg = new TLegend(0.6,0.75,0.825,0.9);

	int lowx = minRun-100; int highx = maxRun+100; int binx = highx - lowx;

	for (Long64_t jentry=0; jentry<nentries;jentry++){
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry); // nbytes += nb;
		if (fChain == 0) return;
		// if (Cut(ientry) < 0) continue;

		for(int it = 0; it < HLTPrescales->size(); it++) { //questo for dovresti farlo solo sui path che ti interessano
				if(jentry==0){
					//cout << "-> " << Run << " this is run number \n";
					//cout << HLTPrescales->at(it) << " this is prescale \n";
					//cout << HLTPaths->at(it) << " this is path name \n";
					if((HLTPrescales->at(it))>maxPres){maxPres=HLTPrescales->at(it);}
					delete histogram;
					histogram = new TH1I("histogram","prescale",binx,lowx,highx);
					histogram->SetBinContent(vRun->at(it)-lowx+1,HLTPrescales->at(it));
					vec.push_back((TH1I*)histogram->Clone(HLTPaths->at(it).c_str()));

				}
				else{ 
				//se nel vettore esiste un oggetto col nome del path lo riempi e basta, se non esiste lo aggiungi
					int existent = 0;
					int temp;
					for (unsigned int ui=0;ui<vec.size();ui++){
						if( ((string)vec[ui]->GetName())==(HLTPaths->at(it).c_str()) ){ 
						existent = 1; 
						temp=ui; 
						}
					}//for sul vettore di TH1I
					if(existent==1){
						if((HLTPrescales->at(it))>maxPres){maxPres=HLTPrescales->at(it);}
						vec[temp]->SetBinContent(vRun->at(it)-lowx+1,HLTPrescales->at(it));
					}
					else if(existent!=1){ 
						if((HLTPrescales->at(it))>maxPres){maxPres=HLTPrescales->at(it);}
						delete histogram;
						histogram = new TH1I("histogram","prescale",binx,lowx,highx);
						histogram->SetBinContent(vRun->at(it)-lowx+1,HLTPrescales->at(it));
						vec.push_back((TH1I*)histogram->Clone(HLTPaths->at(it).c_str()));

					}//else

				}//jentry != 0
		}//for sui path e prescales

	}//for sulle entries del branch

	int serv = 1;
	cout << " vec size " << vec.size() << "\n";
	cout << "selected paths: \n";
	for (unsigned int u=0;u<(vec.size());u++){
		vec[u]->SetLineColor((u % 8)+1);
		vec[u]->SetFillColor((u % 8)+1);
		//vec[u]->SetLineColor((int)(u % 80)+20);
		//vec[u]->SetFillColor((int)(u % 80)+20);
		vec[u]->SetFillStyle(3200+(u*2));
		for(int p=0; p<6;p++){ //per selezionare i path d'interesse
			if(((string)vec[u]->GetName())==paths[p]){//per selezionare i path d'interesse
		//		if(((TString)vec[u]->GetName()).Contains("Ele17")){
				if(serv==1){	
					gPad->SetLogy(1);
					vec[u]->SetMaximum((double)maxPres+1);
					vec[u]->Draw();
					vec[u]->GetXaxis()->SetTitle("run");
					vec[u]->GetYaxis()->SetTitle("prescale");
					leg->AddEntry(vec[u],vec[u]->GetName(),"f");
					vec[u]->SetStats(0);
					serv++;
					cout << ((string)vec[u]->GetName()) << "\n";
				}
				else if(serv>1) { 
					vec[u]->Draw("SAME"); 
			//		Presc->Update();
					leg->AddEntry(vec[u],vec[u]->GetName(),"f");
					vec[u]->SetStats(0);
					cout << ((string)vec[u]->GetName()) << "\n";
				}
			}
		}
	}
	leg->SetBorderSize(0);
	leg->SetFillColor(0);
	leg->Draw();



	//=====================================================================//
	//=============================== RATIO ===============================//
	//=====================================================================//


	TCanvas* Ratio = (TCanvas*)gDirectory->GetList()->FindObject("Ratio");
	if (Ratio) delete Ratio;
	Ratio = new TCanvas("Ratio","Ratio",0,0,900,600);

	TH1F* historatio = (TH1F*)gDirectory->GetList()->FindObject("historatio");
	if (historatio) delete historatio;


	std::vector<TH1F*> dvec;
	dvec.clear();

	TLegend *ratleg = new TLegend(0.6,0.75,0.825,0.9);


	vector<double> HLTRatio;
	int HTFPmax;
	double ratio;
	for (Long64_t jentry=0; jentry<nentries;jentry++){
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry); // nbytes += nb;
		if (fChain == 0) return;
		// if (Cut(ientry) < 0) continue;

		HLTRatio.clear();
		for(unsigned int y=0;y<HLTNames->size();y++){
			if(HLTNames->at(y)=="HLTriggerFinalPath"){HTFPmax = HLTValue->at(y); break; }
		}

		for(unsigned int y=0;y<HLTValue->size();y++){
			ratio = (double)HLTValue->at(y) / (double)HTFPmax;
			HLTRatio.push_back(ratio);
		}

		for(int it = 0; it < HLTRatio.size(); it++) { //questo for dovresti farlo solo sui path che ti interessano
				if(jentry==0){
					//cout << "-> " << Run << " this is run number \n";
					//cout << HLTRatio->at(it) << " this is ratio \n";
					//cout << HLTNames->at(it) << " this is path name \n";
					delete historatio;
					historatio = new TH1F("historatio","ratio",binx,lowx,highx);
					historatio->SetBinContent(vRun->at(it)-lowx+1,HLTRatio.at(it));
					historatio->SetBinError(vRun->at(it)-lowx+1,(TMath::Sqrt(HLTValue->at(it)))/HTFPmax);
					dvec.push_back((TH1F*)historatio->Clone(HLTNames->at(it).c_str()));

				}
				else{ //se nel vettore esiste un oggetto col nome del path lo riempi e basta, se non esiste lo aggiungi
					bool existent = 0;
					int temp;
					for (unsigned int ui=0;ui<(dvec.size());ui++){
						if( ((string)dvec[ui]->GetName())==(HLTNames->at(it).c_str()) ){ 
						existent = 1; 
						temp=ui; 
						}
					}//for sul vettore di TH1F
					if(existent){
						dvec[temp]->SetBinContent(vRun->at(it)-lowx+1,HLTRatio.at(it));
						dvec[temp]->SetBinError(vRun->at(it)-lowx+1,(TMath::Sqrt(HLTValue->at(it)))/HTFPmax);
						}
					else if(!existent){ 
						delete historatio;
						historatio = new TH1F("historatio","ratio",binx,lowx,highx);
						historatio->SetBinContent(vRun->at(it)-lowx+1,HLTRatio.at(it));
						historatio->SetBinError(vRun->at(it)-lowx+1,(TMath::Sqrt(HLTValue->at(it)))/HTFPmax);
						dvec.push_back((TH1F*)historatio->Clone(HLTNames->at(it).c_str()));
					}//else

				}//jentry != 0
		}//for sui path e prescales

	}//for sulle entries del branch

	serv = 1;
	cout << " dvec size " << dvec.size() << "\n";
	for (unsigned int u=0;u<(dvec.size());u++){
		dvec[u]->SetLineColor((u % 8)+1);
		dvec[u]->SetMarkerColor((u % 8)+1);
		//dvec[u]->SetLineColor((int)(u % 80)+20);
		//dvec[u]->SetMarkerColor((int)(u % 80)+20);
		dvec[u]->SetMarkerStyle((u%3)+24);
		dvec[u]->SetMarkerSize(1.0+(((double)(u%5))/10.));
		for(int p=0; p<6;p++){//per selezionare i path d'interesse
			if(((string)dvec[u]->GetName())==paths[p]){//per selezionare i path d'interesse
		//	if(((TString)dvec[u]->GetName()).Contains("Ele17")){
				if(serv==1){	
					dvec[u]->SetMaximum((double)maxRatio);
					dvec[u]->Draw("E1 9");
					dvec[u]->GetXaxis()->SetTitle("run");
					dvec[u]->GetYaxis()->SetTitle("ratio");
					ratleg->AddEntry(dvec[u],dvec[u]->GetName(),"p");
					dvec[u]->SetStats(0);
					serv++;
				}
				else if(serv>1){
					dvec[u]->Draw("E1 9 SAME"); 
				//	Ratio->Update();
					ratleg->AddEntry(dvec[u],dvec[u]->GetName(),"p");
					dvec[u]->SetStats(0);
				}
			}
		}
	}
	ratleg->SetBorderSize(0);
	ratleg->SetFillColor(0);
	ratleg->Draw();


}
