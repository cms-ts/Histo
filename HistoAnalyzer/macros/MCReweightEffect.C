#define MCReweightEffect_cxx
#include "MCReweightEffect.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>
#include <TPaveStats.h>

#include "tdrStyle.C"
#include "MMutil.C"

TCanvas * EB_plots;
TCanvas * EE_plots;



void MCReweightEffect::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L MCReweightEffect.C
//      Root > MCReweightEffect t
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

	/*=========================*/

	//EB
	TH1D * h_IsoTrk_EB; 
	TH1D * h_IsoEcal_EB;
	TH1D * h_IsoHcal_EB;
	TH1D * h_HE_EB;
	TH1F * h_DeltaPhiTkClu_EB;
	TH1F * h_DeltaEtaTkClu_EB;
	TH1F * h_sigmaIeIe_EB;
	//EB Reweight
	TH1D * h_IsoTrk_EBR; 
	TH1D * h_IsoEcal_EBR;
	TH1D * h_IsoHcal_EBR;
	TH1D * h_HE_EBR;
	TH1F * h_DeltaPhiTkClu_EBR;
	TH1F * h_DeltaEtaTkClu_EBR;
	TH1F * h_sigmaIeIe_EBR;


	//EB
	h_IsoTrk_EB = new TH1D("h_IsoTrk_EB","IsoTrk",20,0.,0.20);
	h_IsoEcal_EB = new TH1D("h_IsoEcal_EB","IsoEcal",20,0.,0.20);
	h_IsoHcal_EB = new TH1D("h_IsoHcal_EB","IsoHcal",20,0.,0.20);
	h_HE_EB = new TH1D("h_HE_EB","H/E",20,0.,0.20);
	h_DeltaPhiTkClu_EB = new TH1F("h_DeltaPhiTkClu_EB","DeltaPhiTkClu",20,0.,0.2);
	h_DeltaEtaTkClu_EB = new TH1F("h_DeltaEtaTkClu_EB","DeltaEtaTkClu",20,0.,.05);
	h_sigmaIeIe_EB = new TH1F("h_sigmaIeIe_EB","sigmaIeIe",20,0.,0.1);
	//EB Reweight
	h_IsoTrk_EBR = new TH1D("h_IsoTrk_EBR","IsoTrk",20,0.,0.20);
	h_IsoEcal_EBR = new TH1D("h_IsoEcal_EBR","IsoEcal",20,0.,0.20);
	h_IsoHcal_EBR = new TH1D("h_IsoHcal_EBR","IsoHcal",20,0.,0.20);
	h_HE_EBR = new TH1D("h_HE_EBR","H/E",20,0.,0.20);
	h_DeltaPhiTkClu_EBR = new TH1F("h_DeltaPhiTkClu_EBR","DeltaPhiTkClu",20,0.,0.2);
	h_DeltaEtaTkClu_EBR = new TH1F("h_DeltaEtaTkClu_EBR","DeltaEtaTkClu",20,0.,.05);
	h_sigmaIeIe_EBR = new TH1F("h_sigmaIeIe_EBR","sigmaIeIe",20,0.,0.1);

	/*=========================*/

	//EE
	TH1D * h_IsoTrk_EE; 
	TH1D * h_IsoEcal_EE;
	TH1D * h_IsoHcal_EE;
	TH1D * h_HE_EE;
	TH1F * h_DeltaPhiTkClu_EE;
	TH1F * h_DeltaEtaTkClu_EE;
	TH1F * h_sigmaIeIe_EE;
	//EE Reweight
	TH1D * h_IsoTrk_EER; 
	TH1D * h_IsoEcal_EER;
	TH1D * h_IsoHcal_EER;
	TH1D * h_HE_EER;
	TH1F * h_DeltaPhiTkClu_EER;
	TH1F * h_DeltaEtaTkClu_EER;
	TH1F * h_sigmaIeIe_EER;

	//EE
	h_IsoTrk_EE = new TH1D("h_IsoTrk_EE","IsoTrk",20,0.,0.20);
	h_IsoEcal_EE = new TH1D("h_IsoEcal_EE","IsoEcal",20,0.,0.20);
	h_IsoHcal_EE = new TH1D("h_IsoHcal_EE","IsoHcal",20,0.,0.20);
	h_HE_EE = new TH1D("h_HE_EE","H/E",20,0.,0.20);
	h_DeltaPhiTkClu_EE = new TH1F("h_DeltaPhiTkClu_EE","DeltaPhiTkClu",20,0.,0.2);
	h_DeltaEtaTkClu_EE = new TH1F("h_DeltaEtaTkClu_EE","DeltaEtaTkClu",20,0.,.05);
	h_sigmaIeIe_EE = new TH1F("h_sigmaIeIe_EE","sigmaIeIe",20,0.,0.1);
	//EE Reweight
	h_IsoTrk_EER = new TH1D("h_IsoTrk_EER","IsoTrk",20,0.,0.20);
	h_IsoEcal_EER = new TH1D("h_IsoEcal_EER","IsoEcal",20,0.,0.20);
	h_IsoHcal_EER = new TH1D("h_IsoHcal_EER","IsoHcal",20,0.,0.20);
	h_HE_EER = new TH1D("h_HE_EER","H/E",20,0.,0.20);
	h_DeltaPhiTkClu_EER = new TH1F("h_DeltaPhiTkClu_EER","DeltaPhiTkClu",20,0.,0.2);
	h_DeltaEtaTkClu_EER = new TH1F("h_DeltaEtaTkClu_EER","DeltaEtaTkClu",20,0.,.05);
	h_sigmaIeIe_EER = new TH1F("h_sigmaIeIe_EER","sigmaIeIe",20,0.,0.1);

	/*=========================*/

	TH1D *vert=new TH1D("vert","Number of vertices, reweighted Distribution",25,0,25);
	TH1D *vert2=new TH1D("vert2","Number of vertices, reweighted Distribution",25,0,25);

	/*=========================*/

	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		vert->Fill(numberOfVertices,Weight);
		vert2->Fill(numberOfVertices,1);

		if (IsoTrkEB->size()>0) {float var=IsoTrkEB->at(0);
			h_IsoTrk_EBR->Fill(var,Weight);
			h_IsoTrk_EB->Fill(var,1);
		}
		if (IsoEcalEB->size()>0) {float var=IsoEcalEB->at(0);
			h_IsoEcal_EBR->Fill(var,Weight);
			h_IsoEcal_EB->Fill(var,1);
		}
		if (IsoHcalEB->size()>0) {float var=IsoHcalEB->at(0);
			h_IsoHcal_EBR->Fill(var,Weight);
			h_IsoHcal_EB->Fill(var,1);
		}
		if (HEEB->size()>0) {float var=HEEB->at(0);
			h_HE_EBR->Fill(var,Weight);
			h_HE_EB->Fill(var,1);
		}
		if (DeltaPhiTkCluEB->size()>0) {float var=DeltaPhiTkCluEB->at(0);
			h_DeltaPhiTkClu_EBR->Fill(var,Weight);
			h_DeltaPhiTkClu_EB->Fill(var,1);
		}
		if (DeltaEtaTkCluEB->size()>0) {float var=DeltaEtaTkCluEB->at(0);
			h_DeltaEtaTkClu_EBR->Fill(var,Weight);
			h_DeltaEtaTkClu_EB->Fill(var,1);
		}
		if (sigmaIeIeEB->size()>0) {float var=sigmaIeIeEB->at(0);
			h_sigmaIeIe_EBR->Fill(var,Weight);
			h_sigmaIeIe_EB->Fill(var,1);
		}

		if (IsoTrkEE->size()>0) {float var=IsoTrkEE->at(0);
			h_IsoTrk_EER->Fill(var,Weight);
			h_IsoTrk_EE->Fill(var,1);
		}
		if (IsoEcalEE->size()>0) {float var=IsoEcalEE->at(0);
			h_IsoEcal_EER->Fill(var,Weight);
			h_IsoEcal_EE->Fill(var,1);
		}
		if (IsoHcalEE->size()>0) {float var=IsoHcalEE->at(0);
			h_IsoHcal_EER->Fill(var,Weight);
			h_IsoHcal_EE->Fill(var,1);
		}
		if (HEEE->size()>0) {float var=HEEE->at(0);
			h_HE_EER->Fill(var,Weight);
			h_HE_EE->Fill(var,1);
		}
		if (DeltaPhiTkCluEE->size()>0) {float var=DeltaPhiTkCluEE->at(0);
			h_DeltaPhiTkClu_EER->Fill(var,Weight);
			h_DeltaPhiTkClu_EE->Fill(var,1);
		}
		if (DeltaEtaTkCluEE->size()>0) {float var=DeltaEtaTkCluEE->at(0);
			h_DeltaEtaTkClu_EER->Fill(var,Weight);
			h_DeltaEtaTkClu_EE->Fill(var,1);
		}
		if (sigmaIeIeEE->size()>0) {float var=sigmaIeIeEE->at(0);
			h_sigmaIeIe_EER->Fill(var,Weight);
			h_sigmaIeIe_EE->Fill(var,1);
		}

}


   // qua dei draw copi diretto da all plots
   //EB - Create a Canvas and divide it in Pads
   EB_plots = new TCanvas("EB_plots","EB",400,20,1200,800);
   EB_plots->Divide(4,2);

   //First histogram
   EB_plots->cd(1);
   h_IsoTrk_EB->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_IsoTrk_EB->SetLineColor(2);
   h_IsoTrk_EB->Draw();
   h_IsoTrk_EBR->SetLineColor(1);
   h_IsoTrk_EBR->Draw("SAMES");

   //WP Lines and Legend
   TLegend *leg = new TLegend(0.4,0.55,0.8,0.9);
   leg->SetBorderSize(0);
   leg->SetEntrySeparation(0.01);
   leg->SetFillColor(0);
   leg->AddEntry(h_IsoTrk_EB,"MC","l");
   leg->AddEntry(h_IsoTrk_EBR,"MC Reweighted","l");
   TLine *Line80 = new TLine(0.09,0.,0.09,h_IsoTrk_EB->GetMaximum());
   Line80->SetLineColor(kBlue);
   Line80->SetLineStyle(2);
   Line80->Draw();
   leg->AddEntry(Line80,"WP 80","l");
   TLine *Line90 = new TLine(0.12,0.,0.12,h_IsoTrk_EB->GetMaximum());
   Line90->SetLineColor(kBlack);
   Line90->SetLineStyle(2);
   Line90->Draw();
   leg->AddEntry(Line90,"WP 90","l");
   leg->Draw();

/*
   //al momento non riesco a spostare le statistiche senza uccidere tutto...
   TPaveStats *p1 = (TPaveStats*)h_IsoTrk_EB->FindObject("stats"); 
   h_IsoTrk_EB->GetListOfFunctions()->Remove(p1);
   p1->SetY2NDC(0.75);
   p1->SetTextColor(kBlue);
   p1->Draw();
   TPaveStats *r1 = (TPaveStats*)h_IsoTrk_EBR->FindObject("stats"); 
   h_IsoTrk_EBR->GetListOfFunctions()->Remove(r1);
   r1->SetY1NDC(0.75); 
   r1->SetY2NDC(0.622); 
   r1->SetTextColor(kBlack);
   r1->Draw();
   EB_plots->Update();
 */


   //Second histogram
   EB_plots->cd(2);
   h_IsoEcal_EB->GetYaxis()->SetTitle("Number of Events");
   h_IsoEcal_EB->SetLineColor(2);
   h_IsoEcal_EBR->SetLineColor(1);
   double primo=h_IsoEcal_EB->GetMaximum();
   double secondo=h_IsoEcal_EBR->GetMaximum();
   if(primo>secondo){
	   h_IsoEcal_EB->Draw();
	   h_IsoEcal_EBR->Draw("SAMES");
   } 
   else {
	   h_IsoEcal_EBR->Draw();
	   h_IsoEcal_EB->Draw("SAMES");
   }
   BLine(0.07,0.,0.07,h_IsoEcal_EB->GetMaximum());
   MLine(0.09,0.,0.09,h_IsoEcal_EB->GetMaximum());

   EB_plots->cd(3);
   h_IsoHcal_EB->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_IsoHcal_EB->SetLineColor(2);
   h_IsoHcal_EB->Draw();
   h_IsoHcal_EBR->SetLineColor(1);
   h_IsoHcal_EBR->Draw("SAMES");
   BLine(0.10,0.,0.10,h_IsoHcal_EB->GetMaximum());
   MLine(0.10,0.,0.10,h_IsoHcal_EB->GetMaximum());

   EB_plots->cd(4);
   h_HE_EB->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_HE_EB->SetLineColor(2);
   h_HE_EB->Draw();
   h_HE_EBR->SetLineColor(1);
   h_HE_EBR->Draw("SAMES");
   BLine(0.04,0.,0.04,h_HE_EB->GetMaximum());
   MLine(0.12,0.,0.12,h_HE_EB->GetMaximum());

   EB_plots->cd(5);
   h_DeltaPhiTkClu_EB->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_DeltaPhiTkClu_EB->SetLineColor(2);
   h_DeltaPhiTkClu_EB->Draw();
   h_DeltaPhiTkClu_EBR->SetLineColor(1);
   h_DeltaPhiTkClu_EBR->Draw("SAMES");
   BLine(0.06,0.,0.06,h_DeltaPhiTkClu_EB->GetMaximum());
   MLine(0.8,0.,0.8,h_DeltaPhiTkClu_EB->GetMaximum());

   EB_plots->cd(6);
   h_DeltaEtaTkClu_EB->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_DeltaEtaTkClu_EB->SetLineColor(2);
   h_DeltaEtaTkClu_EB->Draw();
   h_DeltaEtaTkClu_EBR->SetLineColor(1);
   h_DeltaEtaTkClu_EBR->Draw("SAMES");
   BLine(0.004,0.,0.004,h_DeltaEtaTkClu_EB->GetMaximum());
   MLine(0.007,0.,0.007,h_DeltaEtaTkClu_EB->GetMaximum());

   EB_plots->cd(7);
   h_sigmaIeIe_EB->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_sigmaIeIe_EB->SetLineColor(2);
   h_sigmaIeIe_EB->Draw();
   h_sigmaIeIe_EBR->SetLineColor(1);
   h_sigmaIeIe_EBR->Draw("SAMES");
   BLine(0.004,0.,0.004,h_sigmaIeIe_EB->GetMaximum());
   MLine(0.007,0.,0.007,h_sigmaIeIe_EB->GetMaximum());


/*============================*/

   // qua dei draw copi diretto da all plots
   //EE - Create a Canvas and divide it in Pads
   EE_plots = new TCanvas("EE_plots","EE",400,20,1200,800);
   EE_plots->Divide(4,2);

   //First histogram
   EE_plots->cd(1);
   h_IsoTrk_EE->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_IsoTrk_EE->SetLineColor(2);
   h_IsoTrk_EE->Draw();
   h_IsoTrk_EER->SetLineColor(1);
   h_IsoTrk_EER->Draw("SAMES");

   //WP Lines and Legend
   TLegend *leg2 = new TLegend(0.4,0.55,0.8,0.9);
   leg2->SetBorderSize(0);
   leg2->SetEntrySeparation(0.01);
   leg2->SetFillColor(0);
   leg2->AddEntry(h_IsoTrk_EE,"MC","l");
   leg2->AddEntry(h_IsoTrk_EER,"MC Reweighted","l");
   Line80->SetLineColor(kBlue);
   Line80->SetLineStyle(2);
   Line80->Draw();
   leg2->AddEntry(Line80,"WP 80","l");
   Line90->SetLineColor(kBlack);
   Line90->SetLineStyle(2);
   Line90->Draw();
   leg2->AddEntry(Line90,"WP 90","l");
   leg2->Draw();


   //Second histogram
   EE_plots->cd(2);
   h_IsoEcal_EE->GetYaxis()->SetTitle("Number of Events");
   h_IsoEcal_EE->SetLineColor(2);
   h_IsoEcal_EER->SetLineColor(1);
   
   primo=h_IsoEcal_EE->GetMaximum();
   secondo=h_IsoEcal_EER->GetMaximum();
   if(primo>secondo){
	   h_IsoEcal_EE->Draw();
	   h_IsoEcal_EER->Draw("SAMES");
   } 
   else {
	   h_IsoEcal_EER->Draw();
	   h_IsoEcal_EE->Draw("SAMES");
   }
   BLine(0.07,0.,0.07,h_IsoEcal_EE->GetMaximum());
   MLine(0.09,0.,0.09,h_IsoEcal_EE->GetMaximum());

   EE_plots->cd(3);
   h_IsoHcal_EE->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_IsoHcal_EE->SetLineColor(2);
   h_IsoHcal_EE->Draw();
   h_IsoHcal_EER->SetLineColor(1);
   h_IsoHcal_EER->Draw("SAMES");
   BLine(0.10,0.,0.10,h_IsoHcal_EE->GetMaximum());
   MLine(0.10,0.,0.10,h_IsoHcal_EE->GetMaximum());

   EE_plots->cd(4);
   h_HE_EE->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_HE_EE->SetLineColor(2);
   h_HE_EE->Draw();
   h_HE_EER->SetLineColor(1);
   h_HE_EER->Draw("SAMES");
   BLine(0.04,0.,0.04,h_HE_EE->GetMaximum());
   MLine(0.12,0.,0.12,h_HE_EE->GetMaximum());

   EE_plots->cd(5);
   h_DeltaPhiTkClu_EE->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_DeltaPhiTkClu_EE->SetLineColor(2);
   h_DeltaPhiTkClu_EE->Draw();
   h_DeltaPhiTkClu_EER->SetLineColor(1);
   h_DeltaPhiTkClu_EER->Draw("SAMES");
   BLine(0.06,0.,0.06,h_DeltaPhiTkClu_EE->GetMaximum());
   MLine(0.8,0.,0.8,h_DeltaPhiTkClu_EE->GetMaximum());

   EE_plots->cd(6);
   h_DeltaEtaTkClu_EE->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_DeltaEtaTkClu_EE->SetLineColor(2);
   h_DeltaEtaTkClu_EE->Draw();
   h_DeltaEtaTkClu_EER->SetLineColor(1);
   h_DeltaEtaTkClu_EER->Draw("SAMES");
   BLine(0.004,0.,0.004,h_DeltaEtaTkClu_EE->GetMaximum());
   MLine(0.007,0.,0.007,h_DeltaEtaTkClu_EE->GetMaximum());

   EE_plots->cd(7);
   h_sigmaIeIe_EE->GetYaxis()->SetTitle("Number of Events");
   gPad->SetLogy(1);
   h_sigmaIeIe_EE->SetLineColor(2);
   h_sigmaIeIe_EE->Draw();
   h_sigmaIeIe_EER->SetLineColor(1);
   h_sigmaIeIe_EER->Draw("SAMES");
   BLine(0.004,0.,0.004,h_sigmaIeIe_EE->GetMaximum());
   MLine(0.007,0.,0.007,h_sigmaIeIe_EE->GetMaximum());


}
