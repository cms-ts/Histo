#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TH1D.h"
#include "TObject.h"
#include "TCollection.h"

class combineLeptonSystematics {
public:
  int letscombine (int);
  int printLatex (std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, TH1D*, TH1D*, TH1D*,string, string);
  std::vector<double> systSum(std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, TH1D*, TH1D*);
  std::vector<double> systPar(std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>);
  std::vector<double> systOne(string);
  std::vector<double> systOneCent(string);
  std::vector<double> systUnfArea(int, string, string);
  TH1D* getDataHisto(int, string);
  std::vector<string> getBinColumn(string,bool);
};

int combineLeptonSystematics::letscombine (int leptonSP) {
   
  string version="_v2_32";
  string plotpath="/gpfs/cms/users/schizzi/Systematics/";

  std::vector<string> variablesName;
  variablesName.clear();
  variablesName.push_back("jetMult");
  variablesName.push_back("jet1Pt");
  variablesName.push_back("jet2Pt");
  variablesName.push_back("jet3Pt");
  variablesName.push_back("jet4Pt");
  variablesName.push_back("jet1Eta");
  variablesName.push_back("jet2Eta");
  variablesName.push_back("jet3Eta");
  variablesName.push_back("jet4Eta");
  variablesName.push_back("jet1Ht");
  variablesName.push_back("jet2Ht");
  variablesName.push_back("jet3Ht");
  variablesName.push_back("jet4Ht");

  string eleEff;
  string muoEff;
  string eleJEC;
  string muoJEC;
  string eleJER;
  string muoJER;
  string eleUnf;
  string muoUnf;
  string eleGen;
  string muoGen;
  string elePU;
  string muoPU;
  string eleBkg;
  string muoBkg;
  string output;

  string eleBkgStat;
  string muoBkgStat;

  TH1D* datahisto_ele;
  TH1D* datahisto_muo;
  TH1D* datahisto_combi;

  // Get systematics from UnfArea:
  std::vector<double> jetEleUnfArea = combineLeptonSystematics::systUnfArea(1,plotpath,version);
  std::vector<double> jetMuoUnfArea = combineLeptonSystematics::systUnfArea(2,plotpath,version);

  // Define proper vstrings for systematics

  for (int var=0; var<variablesName.size(); var++){

    output=plotpath+"ele/"+variablesName[var]+"FinalSyst"+version+".txt";
    if (leptonSP == 2) output=plotpath+"muo/"+variablesName[var]+"FinalSyst"+version+".txt";
    if (leptonSP == 3) output=plotpath+"combination/"+variablesName[var]+"FinalSyst"+version+".txt";
    cout << "-------------------------" << endl;
    cout << "Writing " << output  << " ..."<< endl;

    //    Systematics file paths:

    eleEff = plotpath+"ele/systematicsEff_"+variablesName[var]+version+".txt";
    muoEff = plotpath+"muo/systematicsEff_"+variablesName[var]+version+".txt";
    eleJEC = plotpath+"ele/systematicsJEC_"+variablesName[var]+version+".txt";
    muoJEC = plotpath+"muo/systematicsJEC_"+variablesName[var]+version+".txt";
    eleJER = plotpath+"ele/systematicsJER_"+variablesName[var]+version+".txt";
    muoJER = plotpath+"muo/systematicsJER_"+variablesName[var]+version+".txt";
    eleUnf = plotpath+"ele/systematicsUnfMethod_"+variablesName[var]+version+".txt";
    muoUnf = plotpath+"muo/systematicsUnfMethod_"+variablesName[var]+version+".txt";
    eleGen = plotpath+"ele/systematicsUnfGen_"+variablesName[var]+version+".txt";
    muoGen = plotpath+"muo/systematicsUnfGen_"+variablesName[var]+version+".txt";
    elePU  = plotpath+"ele/systematicsPU_"+variablesName[var]+version+".txt";
    muoPU  = plotpath+"muo/systematicsPU_"+variablesName[var]+version+".txt";
    eleBkg = plotpath+"ele/BkgCrossSection_"+variablesName[var]+version+".txt";
    muoBkg = plotpath+"muo/BkgCrossSection_"+variablesName[var]+version+".txt";

    datahisto_ele   = combineLeptonSystematics::getDataHisto(var,"/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3PostApproval.root");
    datahisto_muo   = combineLeptonSystematics::getDataHisto(var,"/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3PostApprovalMu.root");
    datahisto_combi = combineLeptonSystematics::getDataHisto(var,"/gpfs/cms/data/2011/Unfolding/UnfoldingOfficialV57_3PostApprovalCombined.root");

    datahisto_ele->Sumw2();
    datahisto_muo->Sumw2();
    datahisto_combi->Sumw2();

    datahisto_ele->Scale(1./4890.0);
    datahisto_muo->Scale(1./4890.0);
    datahisto_combi->Scale(1./4890.0);

    cout << "   -> Writing exclusive systematics..." << endl;
    std::vector<double> jetEleEff = combineLeptonSystematics::systOne(eleEff);
    std::vector<double> jetMuoEff = combineLeptonSystematics::systOne(muoEff);
    std::vector<double> jetEleJEC = combineLeptonSystematics::systOne(eleJEC);
    std::vector<double> jetMuoJEC = combineLeptonSystematics::systOne(muoJEC);
    std::vector<double> jetEleJER = combineLeptonSystematics::systOne(eleJER);
    std::vector<double> jetMuoJER = combineLeptonSystematics::systOne(muoJER);
    std::vector<double> jetEleUnf = combineLeptonSystematics::systOne(eleUnf);
    std::vector<double> jetMuoUnf = combineLeptonSystematics::systOne(muoUnf);
    std::vector<double> jetEleGen = combineLeptonSystematics::systOne(eleGen);
    std::vector<double> jetMuoGen = combineLeptonSystematics::systOne(muoGen);
    std::vector<double> jetElePU  = combineLeptonSystematics::systOne(elePU); 
    std::vector<double> jetMuoPU  = combineLeptonSystematics::systOne(muoPU); 
    std::vector<double> jetEleBkg = combineLeptonSystematics::systOne(eleBkg);
    std::vector<double> jetMuoBkg = combineLeptonSystematics::systOne(muoBkg);

    // Correct JEC with JER!!
    for (Int_t nelcul=0;nelcul<jetEleJEC.size();nelcul++) {
      jetEleJEC[nelcul] = sqrt(jetEleJEC[nelcul]*jetEleJEC[nelcul] + jetEleJER[nelcul]*jetEleJER[nelcul]);
      jetMuoJEC[nelcul] = sqrt(jetMuoJEC[nelcul]*jetMuoJEC[nelcul] + jetMuoJER[nelcul]*jetMuoJER[nelcul]);
    }

    std::vector<double> jetEff;
    jetEff.clear();
    std::vector<double> jetEffOld;
    jetEffOld.clear();
    std::vector<double> jetStat;
    jetStat.clear();

    // Correct Unfolding syst for Area uncertainty:
    if (variablesName[var] == "jetMult") {
      for (Int_t nel=0;nel<jetMuoUnf.size();nel++) {
	//	cout << "UNF SYST: Method = " << jetEleUnf[nel] << " Area = " << jetEleUnfArea[nel] << endl;
	//	jetEleUnf[nel] = sqrt(jetEleUnf[nel]*jetEleUnf[nel] + jetEleUnfArea[nel]*jetEleUnfArea[nel]);
	//	jetMuoUnf[nel] = sqrt(jetMuoUnf[nel]*jetMuoUnf[nel] + jetMuoUnfArea[nel]*jetMuoUnfArea[nel]);
	//	jetEleUnf[nel] = max(jetEleGen[nel], jetEleUnfArea[nel]);
	//	jetMuoUnf[nel] = max(jetMuoGen[nel], jetMuoUnfArea[nel]);
	jetEleUnf[nel] = jetEleGen[nel];
	jetMuoUnf[nel] = jetMuoGen[nel];
      }
    }
    if (variablesName[var] == "jet1Pt" || variablesName[var] == "jet1Ht" || variablesName[var] == "jet1Eta") {
      for (Int_t nel=0;nel<jetMuoUnf.size();nel++) {
	//	cout << "UNF SYST: Method = " << jetEleUnf[nel] << " Area = " << jetEleUnfArea[0] << endl;
	//	jetEleUnf[nel] = sqrt(jetEleUnf[nel]*jetEleUnf[nel] + jetEleUnfArea[0]*jetEleUnfArea[0]);
	//	jetMuoUnf[nel] = sqrt(jetMuoUnf[nel]*jetMuoUnf[nel] + jetMuoUnfArea[0]*jetMuoUnfArea[0]);
	//	jetEleUnf[nel] = max(jetEleGen[nel], jetEleUnfArea[0]);
	//	jetMuoUnf[nel] = max(jetMuoGen[nel], jetMuoUnfArea[0]);
	jetEleUnf[nel] = jetEleGen[nel];
	jetMuoUnf[nel] = jetMuoGen[nel];
      }
    }
    if (variablesName[var] == "jet2Pt" || variablesName[var] == "jet2Ht" || variablesName[var] == "jet2Eta") {
      for (Int_t nel=0;nel<jetMuoUnf.size();nel++) {
	//	cout << "UNF SYST: Method = " << jetEleUnf[nel] << " Area = " << jetEleUnfArea[1] << endl;
	//	jetEleUnf[nel] = sqrt(jetEleUnf[nel]*jetEleUnf[nel] + jetEleUnfArea[1]*jetEleUnfArea[1]);
	//	jetMuoUnf[nel] = sqrt(jetMuoUnf[nel]*jetMuoUnf[nel] + jetMuoUnfArea[1]*jetMuoUnfArea[1]);
	//	jetEleUnf[nel] = max(jetEleGen[nel], jetEleUnfArea[1]);
	//	jetMuoUnf[nel] = max(jetMuoGen[nel], jetMuoUnfArea[1]);
	jetEleUnf[nel] = jetEleGen[nel];
	jetMuoUnf[nel] = jetMuoGen[nel];
      }
    }
    if (variablesName[var] == "jet3Pt" || variablesName[var] == "jet3Ht" || variablesName[var] == "jet3Eta") {
      for (Int_t nel=0;nel<jetMuoUnf.size();nel++) {
	//	cout << "UNF SYST: Method = " << jetEleUnf[nel] << " Area = " << jetEleUnfArea[2] << endl;
	//	jetEleUnf[nel] = sqrt(jetEleUnf[nel]*jetEleUnf[nel] + jetEleUnfArea[2]*jetEleUnfArea[2]);
	//	jetMuoUnf[nel] = sqrt(jetMuoUnf[nel]*jetMuoUnf[nel] + jetMuoUnfArea[2]*jetMuoUnfArea[2]);
	//	jetEleUnf[nel] = max(jetEleGen[nel], jetEleUnfArea[2]);
	//	jetMuoUnf[nel] = max(jetMuoGen[nel], jetMuoUnfArea[2]);
	jetEleUnf[nel] = jetEleGen[nel];
	jetMuoUnf[nel] = jetMuoGen[nel];
      }
    }
    if (variablesName[var] == "jet4Pt" || variablesName[var] == "jet4Ht" || variablesName[var] == "jet4Eta") {
      for (Int_t nel=0;nel<jetMuoUnf.size();nel++) {
	//	cout << "UNF SYST: Method = " << jetEleUnf[nel] << " Area = " << jetEleUnfArea[3] << endl;
	//	jetEleUnf[nel] = sqrt(jetEleUnf[nel]*jetEleUnf[nel] + jetEleUnfArea[3]*jetEleUnfArea[3]);
	//	jetMuoUnf[nel] = sqrt(jetMuoUnf[nel]*jetMuoUnf[nel] + jetMuoUnfArea[3]*jetMuoUnfArea[3]);
	//	jetEleUnf[nel] = max(jetEleGen[nel], jetEleUnfArea[3]);
	//	jetMuoUnf[nel] = max(jetMuoGen[nel], jetMuoUnfArea[3]);
	jetEleUnf[nel] = jetEleGen[nel];
	jetMuoUnf[nel] = jetMuoGen[nel];
      }
    }

    // Compute the right contrib from efficiency:
    double epsilon=0.1;
    double dplus2ele=0.0;
    double dminus2ele=0.0;
    double dplus2muo=0.0;
    double dminus2muo=0.0;
    double sigmaplus2=0.0;
    double sigmaminus2=0.0;
    for (Int_t nec=0;nec<jetMuoUnf.size();nec++) {
      dplus2ele  = (1+epsilon)*(1+epsilon)*jetEleEff[nec]*datahisto_ele->GetBinContent(nec+1)*jetEleEff[nec]*datahisto_ele->GetBinContent(nec+1);
      dminus2ele = (1-epsilon)*(1-epsilon)*jetEleEff[nec]*datahisto_ele->GetBinContent(nec+1)*jetEleEff[nec]*datahisto_ele->GetBinContent(nec+1);
      dplus2muo  = (1+epsilon)*(1+epsilon)*jetMuoEff[nec]*datahisto_muo->GetBinContent(nec+1)*jetMuoEff[nec]*datahisto_muo->GetBinContent(nec+1);
      dminus2muo = (1-epsilon)*(1-epsilon)*jetMuoEff[nec]*datahisto_muo->GetBinContent(nec+1)*jetMuoEff[nec]*datahisto_muo->GetBinContent(nec+1);

      sigmaplus2  = 1.0/(1.0/(datahisto_ele->GetBinError(nec+1)*datahisto_ele->GetBinError(nec+1) + dplus2ele) 
			 + 1.0/(datahisto_muo->GetBinError(nec+1)*datahisto_muo->GetBinError(nec+1) + dplus2muo));
      sigmaminus2 = 1.0/(1.0/(datahisto_ele->GetBinError(nec+1)*datahisto_ele->GetBinError(nec+1) + dminus2ele) 
			 + 1.0/(datahisto_muo->GetBinError(nec+1)*datahisto_muo->GetBinError(nec+1) + dminus2muo));
      jetEff.push_back(sqrt((sigmaplus2 - sigmaminus2)/(4*epsilon))/datahisto_combi->GetBinContent(nec+1));
      jetStat.push_back(sqrt( 1.0/(1.0/(datahisto_ele->GetBinError(nec+1)*datahisto_ele->GetBinError(nec+1) + jetEleEff[nec]*datahisto_ele->GetBinContent(nec+1)*jetEleEff[nec]*datahisto_ele->GetBinContent(nec+1)) 
				   + 1.0/(datahisto_ele->GetBinError(nec+1)*datahisto_ele->GetBinError(nec+1) + jetMuoEff[nec]*datahisto_muo->GetBinContent(nec+1)*jetMuoEff[nec]*datahisto_muo->GetBinContent(nec+1)))
			      - (sigmaplus2 - sigmaminus2)/(4*epsilon))/datahisto_combi->GetBinContent(nec+1));
      jetEffOld.push_back(sqrt(1/(1/(jetEleEff[nec]*jetEleEff[nec]) + 1/(jetMuoEff[nec]*jetMuoEff[nec]))));
    }

    cout << "   -> Computing combined systematics..." << endl;
    std::vector<double> jetSyst = combineLeptonSystematics::systSum(jetEff,jetEleJEC,jetEleUnf,jetElePU,jetEleBkg,jetEff,jetMuoJEC,jetMuoUnf,jetMuoPU,jetMuoBkg,datahisto_ele,datahisto_muo);   
    cout << "   -> Computing global systematics for electrons and muons..." << endl;
    std::vector<double> jetEleS = combineLeptonSystematics::systPar(jetEleEff,jetEleJEC,jetEleUnf,jetElePU,jetEleBkg);   
    std::vector<double> jetMuoS = combineLeptonSystematics::systPar(jetMuoEff,jetMuoJEC,jetMuoUnf,jetMuoPU,jetMuoBkg);   

    cout << "Number of bins: " << jetSyst.size() << " " << jetEleS.size() << " " << jetMuoS.size() << endl;
    if ((jetSyst.size() != jetEleS.size()) || (jetSyst.size() != jetMuoS.size())) 
      cout << "Muon, electron and combined histos have different binnings!!! That may be a problem..."  << jetSyst.size() << "  " << jetEleS.size() << "  " << jetMuoS.size() << endl;

    if (datahisto_combi->GetNbinsX() != jetSyst.size()) cout << "TH1D's have different size from std::vector's!!!" << " TH1D: " << datahisto_ele->GetNbinsX() << " std::vector: " << jetSyst.size() << endl;

    // Write Systematics combination to file!!
    ofstream syste;
    syste.open(output.c_str());
    //    if ((jetSyst.size()!=jetMuoS.size()) || (jetSyst.size()!=jetEleS.size()))
    for (int i=0;i<jetSyst.size();i++){
      if (leptonSP==1) syste<<jetEleS[i]<<endl;
      if (leptonSP==2) syste<<jetMuoS[i]<<endl;
      if (leptonSP==3) syste<<jetSyst[i]<<endl;
    }
    syste.close();

    string varnameforlatex = variablesName[var];
    // Writing .tex tables:
    combineLeptonSystematics::printLatex (jetSyst, 
					  jetEleS, 
					  jetMuoS, 
					  jetEleEff, 
					  jetMuoEff, 
					  jetEleJEC, 
					  jetMuoJEC, 
					  jetEleUnf, 
					  jetMuoUnf, 
					  jetElePU , 
					  jetMuoPU , 
					  jetEleBkg , 
					  jetMuoBkg , 
					  jetEff , 
					  jetStat , 
					  jetEffOld , 
					  datahisto_ele, 
					  datahisto_muo,
					  datahisto_combi,
					  varnameforlatex, version);
    
  }

  return 0;
}

std::vector<double> combineLeptonSystematics::systUnfArea(int isEleOrMuo, string plotpath, string version){

  std::vector<string> variablesUnfArea;
  variablesUnfArea.clear();
  variablesUnfArea.push_back("Jet1");
  variablesUnfArea.push_back("Jet2");
  variablesUnfArea.push_back("Jet3");
  variablesUnfArea.push_back("Jet4");
  variablesUnfArea.push_back("Jet5");
  variablesUnfArea.push_back("Jet6");

  std::vector<double> jetUnfArea;   
  jetUnfArea.clear();

  string UnfArea;
  double centralValue, rms;
  //  double relerr;
  ifstream inUnfArea;

  for (Int_t m=0;m<variablesUnfArea.size();m++) {
      if (isEleOrMuo == 1) UnfArea = plotpath+"ele/systematicsUnfArea_"+variablesUnfArea[m]+version+".txt";
      if (isEleOrMuo == 2) UnfArea = plotpath+"muo/systematicsUnfArea_"+variablesUnfArea[m]+version+".txt";
      inUnfArea.open (UnfArea.c_str());
      //      inUnfArea >> centralValue >> rms;
      inUnfArea >> rms;
      inUnfArea.close ();
      jetUnfArea.push_back(fabs(rms));
      //      cout << "UnfArea Syst for "<< variablesUnfArea[m] << " " << rms/centralValue << endl;
    }

  return jetUnfArea;
}


std::vector<double> combineLeptonSystematics::systSum(std::vector<double> jetEleEff, std::vector<double> jetEleJEC, std::vector<double> jetEleUnf, std::vector<double> jetElePU, std::vector<double> jetEleBkg,std::vector<double> jetMuoEff, std::vector<double> jetMuoJEC, std::vector<double> jetMuoUnf, std::vector<double> jetMuoPU, std::vector<double> jetMuoBkg, TH1D* datahisto_ele, TH1D* datahisto_muo){

  std::vector<double> syst;
  double tmpEff;
  double tmpJEC;
  double tmpUnf;
  double tmpPU;
  double tmpBkg;
  double tmpSyst;

  for (Int_t i=0;i<jetEleUnf.size();i++) {

    tmpEff = jetEleEff[i];
    tmpJEC = (jetEleJEC[i]*datahisto_ele->GetBinContent(i+1) + jetMuoJEC[i]*datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1));
    tmpUnf = (jetEleUnf[i]*datahisto_ele->GetBinContent(i+1) + jetMuoUnf[i]*datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1));
    tmpPU  = (jetElePU[i] *datahisto_ele->GetBinContent(i+1) + jetMuoPU[i] *datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1));
    tmpBkg = (jetEleBkg[i]*datahisto_ele->GetBinContent(i+1) + jetMuoBkg[i]*datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1));

    cout << "Eff = " << tmpEff*100. << "; JEC = " << tmpJEC*100. << "; Unf = " << tmpUnf*100. << "; PU = " << tmpPU*100. << "; Bkg = " << tmpBkg*100. << endl;

    tmpSyst = sqrt(tmpEff*tmpEff + tmpJEC*tmpJEC + tmpUnf*tmpUnf + tmpPU*tmpPU + tmpBkg*tmpBkg);

    syst.push_back(tmpSyst);
  }


  return syst;
}


std::vector<double> combineLeptonSystematics::systPar(std::vector<double> jetEff, std::vector<double> jetJEC, std::vector<double> jetUnf, std::vector<double> jetPU, std::vector<double> jetBkg){
	
  std::vector<double> syst;
  double tmpSyst;

  for (Int_t i=0;i<jetUnf.size();i++) {

    tmpSyst = sqrt(jetEff[i]*jetEff[i] + jetJEC[i]*jetJEC[i] + jetUnf[i]*jetUnf[i] + jetPU[i]*jetPU[i] + jetBkg[i]*jetBkg[i]);
    syst.push_back(tmpSyst);
  }

  return syst;
}


std::vector<double> combineLeptonSystematics::systOne(string oneSyst){
	
  // Leggere nomi dei file da aprire
   
  std::vector<double> syst;
   
  ifstream inSyst;
  inSyst.open (oneSyst.c_str());
   
  int i=0;
  double tmpSyst;

  while (1) {
    inSyst >> tmpSyst;

    if (!inSyst.good()) {
      break;
    }

    syst.push_back(tmpSyst);

    i++;  
  }

  inSyst.close();

  return syst;
}


std::vector<double> combineLeptonSystematics::systOneCent(string oneSyst){
	
  // Leggere nomi dei file da aprire
   
  std::vector<double> syst;
   
  ifstream inSyst;
  inSyst.open (oneSyst.c_str());
   
  int i=0;
  double tmpSyst;

  cout << "Attento mona, stai tirando su delle sistematiche percentuali, sapevatelo!" << endl;

  while (1) {
    inSyst >> tmpSyst;

    if (!inSyst.good()) {
      break;
    }

    syst.push_back(tmpSyst/100.);

    i++;  
  }

  inSyst.close();

  return syst;
}


int combineLeptonSystematics::printLatex (std::vector<double> jetSyst, 
					  std::vector<double> jetEleS, 
					  std::vector<double> jetMuoS, 
					  std::vector<double> jetEleEff, 
					  std::vector<double> jetMuoEff, 
					  std::vector<double> jetEleJEC, 
					  std::vector<double> jetMuoJEC, 
					  std::vector<double> jetEleUnf, 
					  std::vector<double> jetMuoUnf, 
					  std::vector<double> jetElePU , 
					  std::vector<double> jetMuoPU , 
					  std::vector<double> jetEleBkg , 
					  std::vector<double> jetMuoBkg , 
					  std::vector<double> jetEff , 
					  std::vector<double> jetStat , 
					  std::vector<double> jetEffOld , 
					  TH1D* datahisto_ele,
					  TH1D* datahisto_muo,
					  TH1D* datahisto_combi,
					  string variablesName, string version) {

  std::vector<string> column = combineLeptonSystematics::getBinColumn(variablesName, false);
  if (column.size() != jetSyst.size()) cout << "WRONG vector of BINS size: " << column.size() << " vs " << jetSyst.size() << endl;
  ofstream textfile;
  string tablepath = "/gpfs/cms/users/schizzi/Systematics/tables/systematics_"+variablesName+version+".tex";
  textfile.open(tablepath.c_str(), ios_base::trunc);

  textfile.precision(2);

  textfile << "\\documentclass{article}" << endl;
  textfile << "\\usepackage{rotating}" << endl;
  textfile << "\\oddsidemargin=0.0mm" << endl;
  textfile << "\\evensidemargin=0.0mm" << endl;
  textfile << "\\topmargin=0.0mm " << endl;
  textfile << "\\headheight=0mm " << endl;
  textfile << "\\headsep=0mm " << endl;
  textfile << "\\textheight=271,5mm " << endl;
  textfile << "\\textwidth=200mm " << endl;
  textfile << "\\begin{document}" << endl;

  // FINAL TABLE:
  textfile << "\\begin{sidewaystable}[htbH]" << endl
	   << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|}" << endl
           << "\\hline" << endl 
    	   << "\\multicolumn{4}{|c|}{DATA xsec (pb)} \t&\t \\multicolumn{3}{|c|}{Stat. Uncertainties (\\%)} \t&\t \\multicolumn{5}{|c|}{Electron Systematics (\\%)} \t&\t \\multicolumn{5}{|c|}{Muon Systematics (\\%)}  \t&\t  \\multicolumn{1}{|c|}{Tot. Syst. (\\%)} \t\\\\" << endl
           << "\\hline" << endl; 

  textfile << "Bin \t&\t Ele \t&\t Mu \t&\t Comb. \t&\t Ele \t&\t Mu \t&\t Comb. \t&\t Eff. \t&\t JEC \t&\t Unf. \t&\t PU \t&\t Bkg. \t&\t Eff. \t&\t JEC \t&\t Unf. \t&\t PU \t&\t Bkg. \t&\t Comb. \t\\\\" << endl
	   << "\\hline" << endl; 

  for (Int_t i=0; i<jetSyst.size(); i++) {
    textfile << column[i] << "\t&\t" ;
    textfile.unsetf(ios_base::floatfield);
    textfile.precision(3);
    textfile << datahisto_ele->GetBinContent(i+1) << "\t&\t" << datahisto_muo->GetBinContent(i+1) << "\t&\t" << datahisto_combi->GetBinContent(i+1) << "\t&\t" ;
    textfile.precision(1);
    textfile << std::fixed << datahisto_ele->GetBinError(i+1)*100./datahisto_ele->GetBinContent(i+1) << "\t&\t" << datahisto_muo->GetBinError(i+1)*100./datahisto_muo->GetBinContent(i+1)  << "\t&\t" <<  jetStat[i]*100.  << "\t&\t" ;
    textfile << jetEleEff[i]*100. << "\t&\t" << jetEleJEC[i]*100. << "\t&\t" << jetEleUnf[i]*100. << "\t&\t" << jetElePU[i]*100. << "\t&\t" << jetEleBkg[i]*100. << "\t&\t"
  	     << jetMuoEff[i]*100. << "\t&\t" << jetMuoJEC[i]*100. << "\t&\t" << jetMuoUnf[i]*100. << "\t&\t" << jetMuoPU[i]*100. << "\t&\t" << jetMuoBkg[i]*100. << "\t&\t";
    textfile << jetSyst[i]*100.   << "\t\\\\" << endl;
  }
  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\caption{" << variablesName << "}" << endl
           << "\\label{tab:papersystematicsbreakdowntab}" << endl
	   << "\\end{center}" << endl
           << "\\end{sidewaystable}" << endl;


  // TABLE for the paper with breakdown of combined systs:
  textfile << "\\begin{sidewaystable}[htbH]" << endl
	   << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|c|}" << endl
           << "\\hline" << endl 
    	   << "\\multicolumn{2}{|c|}{DATA xsec (pb)} \t&\t \\multicolumn{1}{|c|}{Stat. Unc. (\\%)} \t&\t \\multicolumn{6}{|c|}{Syst. Unc. (\\%)}  \t\\\\" << endl
           << "\\hline" << endl; 

  textfile << "Bins \t&\t Comb. Ele/Mu \t&\t Comb. Ele/Mu \t&\t Eff. \t&\t JEC \t&\t Unf. \t&\t PU \t&\t Bkg. \t&\t Total \t\\\\" << endl
	   << "\\hline" << endl; 

  // Folding ETA distributions:
  double wmeanE, wsigmaE;
  if (variablesName == "jet1Eta" || variablesName == "jet2Eta" || variablesName == "jet3Eta" || variablesName == "jet4Eta") {
    for (Int_t i=(jetSyst.size()/2); i<jetSyst.size(); i++) {

      wmeanE =   datahisto_combi->GetBinContent(i+1) + datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i);
      wsigmaE = sqrt((jetStat[i]*jetStat[i]) 
		     + (jetStat[jetSyst.size()-i-1]*jetStat[jetSyst.size()-i-1]));
      datahisto_combi->SetBinContent(i+1,wmeanE);
      jetStat[i]=wsigmaE;

      wsigmaE = (jetEff[i]*datahisto_combi->GetBinContent(i+1) + jetEff[jetSyst.size()-i-1]*datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i))/(datahisto_combi->GetBinContent(i+1)+datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i));
      jetEff[i]=wsigmaE;
      wsigmaE = (jetEleJEC[i]*datahisto_combi->GetBinContent(i+1) + jetEleJEC[jetSyst.size()-i-1]*datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i))/(datahisto_combi->GetBinContent(i+1)+datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i));
      jetEleJEC[i]=wsigmaE;
      wsigmaE = (jetMuoJEC[i]*datahisto_combi->GetBinContent(i+1) + jetMuoJEC[jetSyst.size()-i-1]*datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i))/(datahisto_combi->GetBinContent(i+1)+datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i));
      jetMuoJEC[i]=wsigmaE;
      wsigmaE = (jetEleUnf[i]*datahisto_combi->GetBinContent(i+1) + jetEleUnf[jetSyst.size()-i-1]*datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i))/(datahisto_combi->GetBinContent(i+1)+datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i));
      jetEleUnf[i]=wsigmaE;
      wsigmaE = (jetMuoUnf[i]*datahisto_combi->GetBinContent(i+1) + jetMuoUnf[jetSyst.size()-i-1]*datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i))/(datahisto_combi->GetBinContent(i+1)+datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i));
      jetMuoUnf[i]=wsigmaE;
      wsigmaE = (jetElePU[i]*datahisto_combi->GetBinContent(i+1) + jetElePU[jetSyst.size()-i-1]*datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i))/(datahisto_combi->GetBinContent(i+1)+datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i));
      jetElePU[i]=wsigmaE;
      wsigmaE = (jetMuoPU[i]*datahisto_combi->GetBinContent(i+1) + jetMuoPU[jetSyst.size()-i-1]*datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i))/(datahisto_combi->GetBinContent(i+1)+datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i));
      jetMuoPU[i]=wsigmaE;
      wsigmaE = (jetEleBkg[i]*datahisto_combi->GetBinContent(i+1) + jetEleBkg[jetSyst.size()-i-1]*datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i))/(datahisto_combi->GetBinContent(i+1)+datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i));
      jetEleBkg[i]=wsigmaE;
      wsigmaE = (jetMuoBkg[i]*datahisto_combi->GetBinContent(i+1) + jetMuoBkg[jetSyst.size()-i-1]*datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i))/(datahisto_combi->GetBinContent(i+1)+datahisto_combi->GetBinContent(datahisto_combi->GetNbinsX()-i));
      jetMuoBkg[i]=wsigmaE;


      textfile << column[i] << "\t&\t" ;
      textfile.unsetf(ios_base::floatfield);
      textfile.precision(3);
      textfile << datahisto_combi->GetBinContent(i+1) << "\t&\t" ;
      textfile.precision(1);
      textfile << std::fixed <<  jetStat[i]*100.  << "\t&\t" ;
      textfile << jetEff[i]*100. << "\t&\t";
      textfile << (jetEleJEC[i]*datahisto_ele->GetBinContent(i+1) + jetMuoJEC[i]*datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1))*100. << "\t&\t";
      textfile << (jetEleUnf[i]*datahisto_ele->GetBinContent(i+1) + jetMuoUnf[i]*datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1))*100. << "\t&\t";
      textfile << (jetElePU[i] *datahisto_ele->GetBinContent(i+1) + jetMuoPU[i] *datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1))*100. << "\t&\t";
      textfile << (jetEleBkg[i]*datahisto_ele->GetBinContent(i+1) + jetMuoBkg[i]*datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1))*100. << "\t&\t";
      textfile << jetSyst[i]*100.   << "\t\\\\" << endl;
    }
    
  } else {
    for (Int_t i=0; i<jetSyst.size(); i++) {
      textfile << column[i] << "\t&\t" ;
      textfile.unsetf(ios_base::floatfield);
      textfile.precision(3);
      textfile << datahisto_combi->GetBinContent(i+1) << "\t&\t" ;
      textfile.precision(1);
      textfile << std::fixed <<  jetStat[i]*100.  << "\t&\t" ;
      textfile << jetEff[i]*100. << "\t&\t";
      textfile << (jetEleJEC[i]*datahisto_ele->GetBinContent(i+1) + jetMuoJEC[i]*datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1))*100. << "\t&\t";
      textfile << (jetEleUnf[i]*datahisto_ele->GetBinContent(i+1) + jetMuoUnf[i]*datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1))*100. << "\t&\t";
      textfile << (jetElePU[i] *datahisto_ele->GetBinContent(i+1) + jetMuoPU[i] *datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1))*100. << "\t&\t";
      textfile << (jetEleBkg[i]*datahisto_ele->GetBinContent(i+1) + jetMuoBkg[i]*datahisto_muo->GetBinContent(i+1))/(datahisto_ele->GetBinContent(i+1) + datahisto_muo->GetBinContent(i+1))*100. << "\t&\t";
      textfile << jetSyst[i]*100.   << "\t\\\\" << endl;
    }
  }
  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\caption{" << variablesName << "}" << endl
           << "\\label{tab:finalsupersystematicstab}" << endl
	   << "\\end{center}" << endl
           << "\\end{sidewaystable}" << endl;
  

//  // SYSTEMATICS ONLY:
//  textfile << "\\begin{table}[htbH]" << endl
//	   << "\\begin{center}" << endl
//           << "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|}" << endl
//           << "\\hline" << endl 
//    	   << "\\multicolumn{5}{|c|}{Electron Systematics (\\%)} \t&\t \\multicolumn{5}{|c|}{Muon Systematics (\\%)} \t\\\\" << endl
//           << "\\hline" << endl; 
//
//  textfile << "Eff. \t&\t JEC \t&\t Unf. \t&\t PU \t&\t Bkg. \t&\t Eff. \t&\t JEC \t&\t Unf. \t&\t PU \t&\t Bkg. \t\\\\" << endl
//	   << "\\hline" << endl; 
//
//  for (Int_t i=0; i<jetSyst.size(); i++) {
//    textfile.precision(2);
//    textfile << jetEleEff[i]*100. << "\t&\t" << jetEleJEC[i]*100. << "\t&\t" << jetEleUnf[i]*100. << "\t&\t" << jetElePU[i]*100. << "\t&\t" << jetEleBkg[i]*100. << "\t&\t"
//  	     << jetMuoEff[i]*100. << "\t&\t" << jetMuoJEC[i]*100. << "\t&\t" << jetMuoUnf[i]*100. << "\t&\t" << jetMuoPU[i]*100. << "\t&\t" << jetMuoBkg[i]*100. << "\t\\\\" << endl;
//  }
//  textfile << "\\hline" << endl
//           << "\\end{tabular}" << endl
//           << "\\caption{" << variablesName << "}" << endl
//           << "\\label{tab:systematicstab" << variablesName << "}" << endl
//	   << "\\end{center}" << endl
//           << "\\end{table}" << endl;
//
//  // XSECTIONS ONLY:
//  textfile << "\\begin{table}[htbH]" << endl
//	   << "\\begin{center}" << endl
//           << "\\begin{tabular}{|c|c|c|c|c|c|c|}" << endl
//           << "\\hline" << endl 
//    	   << "\\multicolumn{3}{|c|}{DATA xsec (pb)} \t&\t \\multicolumn{3}{|c|}{Stat. Uncertainties (\\%)}  \t&\t  \\multicolumn{1}{|c|}{Global Syst. (\\%)} \t\\\\" << endl
//           << "\\hline" << endl; 
//
//  textfile << "Ele \t&\t Mu \t&\t Comb. \t&\t Ele \t&\t Mu \t&\t Comb. \t&\t Comb. \t\\\\" << endl
//	   << "\\hline" << endl; 
//
//  for (Int_t i=0; i<jetSyst.size(); i++) {
//    textfile.precision(3);
//    textfile << datahisto_ele->GetBinContent(i+1) << "\t&\t" << datahisto_muo->GetBinContent(i+1) << "\t&\t" << datahisto_combi->GetBinContent(i+1) << "\t&\t" ;
//    textfile << datahisto_ele->GetBinError(i+1)*100./datahisto_ele->GetBinContent(i+1) << "\t&\t" << datahisto_muo->GetBinError(i+1)*100./datahisto_muo->GetBinContent(i+1)  << "\t&\t" <<  jetStat[i]*100.  << "\t&\t" ;
//    textfile.precision(2);
//    textfile << jetSyst[i]*100.   << "\t\\\\" << endl;
//  }
//  textfile << "\\hline" << endl
//           << "\\end{tabular}" << endl
//           << "\\caption{" << variablesName << "}" << endl
//           << "\\label{tab:finalxsectab" << variablesName << "}" << endl
//	   << "\\end{center}" << endl
//           << "\\end{table}" << endl;

  textfile << "\\end{document}" << endl;

  textfile.close();
  return 0;
}


TH1D* combineLeptonSystematics::getDataHisto (int whichHisto, string datapath) {

  TFile *histofile1 = TFile::Open (datapath.c_str ());
  histofile1->cd ("");
  TDirectory *dir1 = gDirectory;
  TList *mylist1 = (TList *) dir1->GetListOfKeys ();
  TIter iter1 (mylist1);
  TObject *tobj1 = 0;

  std::vector<string> histosName;
  histosName.clear();
  histosName.push_back("JetMultiplicityUnfolded");
  histosName.push_back("jReco_leading");
  histosName.push_back("jReco_subleading");
  histosName.push_back("jReco_subsubleading");
  histosName.push_back("jReco_subsubsubleading");
  histosName.push_back("jReco_leadingeta");
  histosName.push_back("jReco_subleadingeta");
  histosName.push_back("jReco_subsubleadingeta");
  histosName.push_back("jReco_subsubsubleadingeta");
  histosName.push_back("HReco_leading");
  histosName.push_back("HReco_subleading");
  histosName.push_back("HReco_subsubleading");
  histosName.push_back("HReco_subsubsubleading");

  string histoname;
  TH1D *histo;

  while ((tobj1 = iter1.Next ())) {
    histoname = tobj1->GetName ();
    if (histoname == histosName[whichHisto]) {
      histofile1->cd ("");
      gDirectory->GetObject (histoname.c_str (), histo); // Save ele histogram!
    }
  }

  return histo;
}

std::vector<string> combineLeptonSystematics::getBinColumn(string observable, bool incMulti) {
  std::vector<string> outputColumn;
  outputColumn.clear();
  if ((observable == "jetMult") && !incMulti){
    outputColumn.push_back("Z + 1j");
    outputColumn.push_back("Z + 2j");
    outputColumn.push_back("Z + 3j");
    outputColumn.push_back("Z + 4j");
    outputColumn.push_back("Z + 5j");
    outputColumn.push_back("Z + 6j");
  }
  if (observable == "jetMult" && incMulti){
    outputColumn.push_back("Z + $geq$ 1j");
    outputColumn.push_back("Z + $geq$ 2j");
    outputColumn.push_back("Z + $geq$ 3j");
    outputColumn.push_back("Z + $geq$ 4j");
    outputColumn.push_back("Z + $geq$ 5j");
    outputColumn.push_back("Z + $geq$ 6j");
  }

  if (observable == "jet1Pt"){
    outputColumn.push_back("30-50");
    outputColumn.push_back("50-70");
    outputColumn.push_back("70-90");
    outputColumn.push_back("90-110");
    outputColumn.push_back("110-130");
    outputColumn.push_back("130-150");
    outputColumn.push_back("150-170");
    outputColumn.push_back("170-190");
    outputColumn.push_back("190-210");
    outputColumn.push_back("210-230");
    outputColumn.push_back("230-250");
    outputColumn.push_back("250-270");
    outputColumn.push_back("270-290");
    outputColumn.push_back("290-310");
    outputColumn.push_back("310-330");
    outputColumn.push_back("330-350");
    outputColumn.push_back("350-370");
    outputColumn.push_back("370-390");
  }
  if (observable == "jet2Pt"){
    outputColumn.push_back("30-50");
    outputColumn.push_back("50-70");
    outputColumn.push_back("70-90");
    outputColumn.push_back("90-110");
    outputColumn.push_back("110-130");
    outputColumn.push_back("130-150");
    outputColumn.push_back("150-170");
    outputColumn.push_back("170-190");
    outputColumn.push_back("190-210");
    outputColumn.push_back("210-230");
    outputColumn.push_back("230-250");
    outputColumn.push_back("250-270");
    outputColumn.push_back("270-290");
    outputColumn.push_back("290-310");
    outputColumn.push_back("310-330");
  }
  if (observable == "jet3Pt"){
    outputColumn.push_back("30-50");
    outputColumn.push_back("50-70");
    outputColumn.push_back("70-90");
    outputColumn.push_back("90-110");
    outputColumn.push_back("110-130");
    outputColumn.push_back("130-150");
    outputColumn.push_back("150-170");
    outputColumn.push_back("170-190");
  }
  if (observable == "jet4Pt"){
    outputColumn.push_back("30-50");
    outputColumn.push_back("50-70");
    outputColumn.push_back("70-90");
    outputColumn.push_back("90-110");
    outputColumn.push_back("110-130");
  }

  if (observable == "jet1Ht"){
    outputColumn.push_back("30-70");
    outputColumn.push_back("70-110");
    outputColumn.push_back("110-150");
    outputColumn.push_back("150-190");
    outputColumn.push_back("190-230");
    outputColumn.push_back("230-270");
    outputColumn.push_back("270-310");
    outputColumn.push_back("310-350");
    outputColumn.push_back("350-390");
    outputColumn.push_back("390-430");
    outputColumn.push_back("430-470");
    outputColumn.push_back("470-510");
    outputColumn.push_back("510-550");
    outputColumn.push_back("550-590");
    outputColumn.push_back("590-630");
    outputColumn.push_back("630-670");
    outputColumn.push_back("670-710");
  }
  if (observable == "jet2Ht"){
    outputColumn.push_back("60-110");
    outputColumn.push_back("110-160");
    outputColumn.push_back("160-210");
    outputColumn.push_back("210-260");
    outputColumn.push_back("260-310");
    outputColumn.push_back("310-360");
    outputColumn.push_back("360-410");
    outputColumn.push_back("410-460");
    outputColumn.push_back("460-510");
    outputColumn.push_back("510-560");
    outputColumn.push_back("560-610");
    outputColumn.push_back("610-660");
    outputColumn.push_back("660-710");
  }
  if (observable == "jet3Ht"){
    outputColumn.push_back("90-140");
    outputColumn.push_back("140-190");
    outputColumn.push_back("190-240");
    outputColumn.push_back("240-290");
    outputColumn.push_back("290-340");
    outputColumn.push_back("340-390");
    outputColumn.push_back("390-440");
    outputColumn.push_back("440-490");
    outputColumn.push_back("490-540");
    outputColumn.push_back("540-590");
    outputColumn.push_back("590-640");
    outputColumn.push_back("640-690");
    outputColumn.push_back("690-740");
    outputColumn.push_back("740-790");
  }
  if (observable == "jet4Ht"){
    outputColumn.push_back("120-180");
    outputColumn.push_back("180-240");
    outputColumn.push_back("240-300");
    outputColumn.push_back("300-360");
    outputColumn.push_back("360-420");
    outputColumn.push_back("420-480");
    outputColumn.push_back("480-540");
    outputColumn.push_back("540-600");
    outputColumn.push_back("600-660");
    outputColumn.push_back("660-720");
  }

  if (observable == "jet1Eta"){
    outputColumn.push_back("-2.4$geqeta<$-2.2");
    outputColumn.push_back("-2.2$geqeta<$-2.0");
    outputColumn.push_back("-2.0$geqeta<$-1.8");
    outputColumn.push_back("-1.8$geqeta<$-1.6");
    outputColumn.push_back("-1.6$geqeta<$-1.4");
    outputColumn.push_back("-1.4$geqeta<$-1.2");
    outputColumn.push_back("-1.2$geqeta<$-1.0");
    outputColumn.push_back("-1.0$geqeta<$-0.8");
    outputColumn.push_back("-0.8$geqeta<$-0.6");
    outputColumn.push_back("-0.6$geqeta<$-0.4");
    outputColumn.push_back("-0.4$geqeta<$-0.2");
    outputColumn.push_back("-0.2$geqeta<$0.0");
    outputColumn.push_back("0.0$geqeta<$0.2");
    outputColumn.push_back("0.2$geqeta<$0.4");
    outputColumn.push_back("0.4$geqeta<$0.6");
    outputColumn.push_back("0.6$geqeta<$0.8");
    outputColumn.push_back("0.8$geqeta<$1.0");
    outputColumn.push_back("1.0$geqeta<$1.2");
    outputColumn.push_back("1.2$geqeta<$1.4");
    outputColumn.push_back("1.4$geqeta<$1.6");
    outputColumn.push_back("1.6$geqeta<$1.8");
    outputColumn.push_back("1.8$geqeta<$2.0");
    outputColumn.push_back("2.0$geqeta<$2.2");
    outputColumn.push_back("2.2$geqeta<$2.4");
  }
  if (observable == "jet2Eta"){
    outputColumn.push_back("2.40$geqeta<$2.16");
    outputColumn.push_back("2.16$geqeta<$1.92");
    outputColumn.push_back("1.92$geqeta<$1.68");
    outputColumn.push_back("1.68$geqeta<$1.44");
    outputColumn.push_back("1.44$geqeta<$1.20");
    outputColumn.push_back("1.20$geqeta<$0.96");
    outputColumn.push_back("0.96$geqeta<$0.72");
    outputColumn.push_back("0.72$geqeta<$0.48");
    outputColumn.push_back("0.48$geqeta<$0.24");
    outputColumn.push_back("0.24$geqeta<$0.00");
    outputColumn.push_back("0.00$geqeta<$0.24");
    outputColumn.push_back("0.24$geqeta<$0.48");
    outputColumn.push_back("0.48$geqeta<$0.72");
    outputColumn.push_back("0.72$geqeta<$0.96");
    outputColumn.push_back("0.96$geqeta<$1.20");
    outputColumn.push_back("1.20$geqeta<$1.44");
    outputColumn.push_back("1.44$geqeta<$1.68");
    outputColumn.push_back("1.68$geqeta<$1.92");
    outputColumn.push_back("1.92$geqeta<$2.16");
    outputColumn.push_back("2.16$geqeta<$2.40");
  }
  if (observable == "jet3Eta"){
    outputColumn.push_back("-2.4$geqeta<$-2.1");
    outputColumn.push_back("-2.1$geqeta<$-1.8");
    outputColumn.push_back("-1.8$geqeta<$-1.5");
    outputColumn.push_back("-1.5$geqeta<$-1.2");
    outputColumn.push_back("-1.2$geqeta<$-1.9");
    outputColumn.push_back("-0.9$geqeta<$-0.6");
    outputColumn.push_back("-0.6$geqeta<$-0.3");
    outputColumn.push_back("-0.3$geqeta<$0.0");
    outputColumn.push_back("0.0$geqeta<$0.3");
    outputColumn.push_back("0.3$geqeta<$0.6");
    outputColumn.push_back("0.6$geqeta<$0.9");
    outputColumn.push_back("0.9$geqeta<$1.2");
    outputColumn.push_back("1.2$geqeta<$1.5");
    outputColumn.push_back("1.5$geqeta<$1.8");
    outputColumn.push_back("1.8$geqeta<$2.1");
    outputColumn.push_back("2.1$geqeta<$2.4");
  }
  if (observable == "jet4Eta"){
    outputColumn.push_back("-2.4$geqeta<$-2.0");
    outputColumn.push_back("-2.0$geqeta<$-1.6");
    outputColumn.push_back("-1.6$geqeta<$-1.2");
    outputColumn.push_back("-1.2$geqeta<$-0.8");
    outputColumn.push_back("-0.8$geqeta<$-0.4");
    outputColumn.push_back("-0.4$geqeta<$0.0 ");
    outputColumn.push_back("0.0$geqeta<$0.4");
    outputColumn.push_back("0.4$geqeta<$0.8");
    outputColumn.push_back("0.8$geqeta<$1.2");
    outputColumn.push_back("1.2$geqeta<$1.6");
    outputColumn.push_back("1.6$geqeta<$2.0");
    outputColumn.push_back("2.0$geqeta<$2.4");
  }

  if (outputColumn.size()<1) cout << "getBinColumn: WRONG input string!" << endl;

  return outputColumn;
}
