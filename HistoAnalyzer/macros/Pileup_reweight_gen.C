//+______________________________________________________________________________
// Generate weights based on two input distributions, intended and generated

//!!DS!! this macro generates a lot of output for immediate debug... feel free to remove unnecessary couts

#include <iostream>
#include <fstream>
using namespace std;

#include <TF1.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>


void Pileup_reweight_gen() {

  TH1F* PU_intended = new TH1F("PU_intended","Intended pileup distribution (i.e. Data)",50,-0.5,49.5);
 TH1F* PU_generated = new TH1F("PU_generated","Generated pileup distribution (i.e., MC)",50,-0.5,49.5);

 Double_t Fall2011[50] = {
   0.003388501,
   0.010357558,
   0.024724258,
   0.042348605,
   0.058279812,
   0.068851751,
   0.072914824,
   0.071579609,
   0.066811668,
   0.060672356,
   0.054528356,
   0.04919354,
   0.044886042,
   0.041341896,
   0.0384679,
   0.035871463,
   0.03341952,
   0.030915649,
   0.028395374,
   0.025798107,
   0.023237445,
   0.020602754,
   0.0180688,
   0.015559693,
   0.013211063,
   0.010964293,
   0.008920993,
   0.007080504,
   0.005499239,
   0.004187022,
   0.003096474,
   0.002237361,
   0.001566428,
   0.001074149,
   0.000721755,
   0.000470838,
   0.00030268,
   0.000184665,
   0.000112883,
   6.74043E-05,
   3.82178E-05,
   2.22847E-05,
   1.20933E-05,
   6.96173E-06,
   3.4689E-06,
   1.96172E-06,
   8.49283E-07,
   5.02393E-07,
   2.15311E-07,
    9.56938E-08
 };

/*
  Double_t TrueDist2011[25] = {
    0.019091,
    0.0293974,
    0.0667931,
    0.108859,
    0.139533,
    0.149342,
    0.138629,
    0.114582,
    0.0859364,
    0.059324,
    0.0381123,
    0.0229881,
    0.0131129,
    0.00711764,
    0.00369635,
    0.00184543,
    0.000889604,
    0.000415683,
    0.000188921,
    0.000146288,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0
  };
*/

  // "Flat10+Tail distribution taken directly from MixingModule input
  Double_t probdistFlat10[25] = {
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0698146584,
    0.0630151648,
    0.0526654164,
    0.0402754482,
    0.0292988928,
    0.0194384503,
    0.0122016783,
    0.007207042,
    0.004003637,
    0.0020278322,
    0.0010739954,
    0.0004595759,
    0.0002229748,
    0.0001028162,
    4.58337152809607E-05
  };

  // "Lumpy" distribution taken from PU_S3 Summer11 samples (also consistent with Spring11)
  Double_t probdist_Lumpy[25] = {
    0.073050961,
    0.073282135,
    0.06588457,
    0.07120157,
    0.064497526,
    0.073513309,
    0.078136788,
    0.073050961,
    0.066809265,
    0.073050961,
    0.06588457,
    0.060105221,
    0.049702395,
    0.03352022,
    0.029821437,
    0.018725088,
    0.012483392,
    0.008322261,
    0.002774087,
    0.002774087,
    0.001849391,
    0.000870009,
    0.000372861,
    0.000211288,
    0.000105644,
  }

  // alternate lumpy scenario, also from Summer11 SU_P3 samples
  Double_t probdist_Lumpy2[25] = {
    0.0662635239567,
    0.0749768160742,
    0.0644551777434,
    0.0768663060278,
    0.0675077279753,
    0.0712751159196,
    0.0687384080371,
    0.0680486862442,
    0.064364374034,
    0.0756530139104,
    0.0686843122102,
    0.0662480680062,
    0.0544165378671,
    0.0318933539413,
    0.0268682380216,
    0.0193836939722,
    0.0162635239567,
    0.0112364760433,
    0.00311244204019,
    0.00312017001546,
    0.000624034003091,
    0.0004,
    0.0002,
    0.0001,
    0.00004
  };

  // Summer11 PU_S4, distribution obtained by averaging the number of interactions
  // in each beam crossing to estimate the true mean
  Double_t PoissonIntDist[25] = {
    0.104109,
    0.0703573,
    0.0698445,
    0.0698254,
    0.0697054,
    0.0697907,
    0.0696751,
    0.0694486,
    0.0680332,
    0.0651044,
    0.0598036,
    0.0527395,
    0.0439513,
    0.0352202,
    0.0266714,
    0.019411,
    0.0133974,
    0.00898536,
    0.0057516,
    0.00351493,
    0.00212087,
    0.00122891,
    0.00070592,
    0.000384744,
    0.000219377
  };

  // Summer11 PU_S4, distribution obtained by only looking at the in-time crossing.
  Double_t PoissonOneXDist[25] = {
    0.14551,
    0.0644453,
    0.0696412,
    0.0700311,
    0.0694257,
    0.0685655,
    0.0670929,
    0.0646049,
    0.0609383,
    0.0564597,
    0.0508014,
    0.0445226,
    0.0378796,
    0.0314746,
    0.0254139,
    0.0200091,
    0.0154191,
    0.0116242,
    0.00846857,
    0.00614328,
    0.00426355,
    0.00300632,
    0.00203485,
    0.00133045,
    0.000893794
  };

  // luminosity distribution from estimatePileup.py for May 10 JSON Muon file
  //scopo prendere i valori della TrueDist2011 da un file *.root

  TFile *histof = TFile::Open("/gpfs/cms/data/2011/MCReweight/totalPUdistro_160404-178078.root"); //here is the histogram
  histof->cd();

  Int_t entries = pileup->GetEntries();
  cout << "entries " << entries << "\n";
  Int_t binn=25+1;
  //if (pileup->GetSize()<binn){
  //binn=pileup->GetSize();
  //}
  
  Double_t sum=0.0;
  Double_t sum2=0.0;
  Double_t temp=0.0;
  Double_t TrueDist2011[25];

  //DS Scrivo su file la distribuzione ripesata, per successivo utilizzo
  ofstream myfile;
  myfile.open ("pudistrodati_160404-178078.h");
  myfile << "Double_t DataUntil178078[25] = { \n";

  //DS calcolo l'integrale dei primi 25 bin
  for (int i=1;i<binn;i++) {
  sum2 = sum2 + pileup->GetBinContent(i);
  }

  //DS calcolo la normalizzazione
  for (int i=1;i<binn;i++) {
	  /*DS - NOTA:
	  bin = 0;       underflow bin
	  bin = 1;       first bin with low-edge xlow INCLUDED
	  bin = nbins;   last bin with upper-edge xup EXCLUDED
	  bin = nbins+1; overflow bin */
	  cout << "truedist " << pileup->GetBinContent(i) << "\n";

	  TrueDist2011[i-1]= pileup->GetBinContent(i)/sum2;
	  temp = TrueDist2011[i-1];
	  cout << "normtruedist " << TrueDist2011[i-1] << "\n\n";
	  
	  myfile << TrueDist2011[i-1];
	  if(i<binn-1){myfile <<",\n";}
	  sum = sum + temp;
	  cout << "somma che deve fare 1 = " << sum << "\n\n\n";
  }


  myfile << "\n};\n";
  myfile.close();

  //Fill histograms with one generated, one desired distribution
  
  for (int i=1;i<26;i++) {
    PU_generated->SetBinContent(i,probdistFlat10[i-1]);
    PU_intended->SetBinContent(i,TrueDist2011[i-1]);
  }

  TCanvas *can1 = new TCanvas("can1","can1",1200,800);
  can1->Divide(2,2);

  can1->cd(1);
  PU_generated->SetLineColor(kRed);
  PU_intended->SetLineColor(kBlue);
  PU_intended->Draw();
  PU_generated->Draw("Same");

  can1->cd(2);
  PU_generated->Draw();

  can1->cd(3);
  PU_intended->Draw();


  TCanvas *can2 = new TCanvas("can2","can2",1200,800);
  PU_intended->SetNameTitle("Computed Weights","Computed Weights");
  PU_intended->Draw();


cout << "\n\n";
  for(int ibin=1; ibin<26; ibin++){
      std::cout << ibin-1 << " " << TrueDist2011[ibin-1] << std::endl;
  }


}

