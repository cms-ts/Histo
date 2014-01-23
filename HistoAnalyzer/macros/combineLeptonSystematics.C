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
  int letscombine ();
  int printLatex (std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, TH1D*, TH1D*, TH1D*,string, string);
  std::vector<double> systSum(std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, TH1D*, TH1D*);
  std::vector<double> systPar(std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>, std::vector<double>);
  std::vector<double> systOne(string);
  std::vector<double> systUnfArea(int, string, string);
  TH1D* getDataHisto(int, string);
};

int combineLeptonSystematics::letscombine () {
   
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
  string eleUnf;
  string muoUnf;
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

    output=plotpath+"combination/"+variablesName[var]+"FinalSyst"+version+".txt";
    cout << "-------------------------" << endl;
    cout << "Writing " << output  << " ..."<< endl;

    //    Systematics file paths:

    eleEff = plotpath+"ele/systematicsEff_"+variablesName[var]+version+".txt";
    muoEff = plotpath+"muo/systematicsEff_"+variablesName[var]+version+".txt";
    eleJEC = plotpath+"ele/systematicsJEC_"+variablesName[var]+version+".txt";
    muoJEC = plotpath+"muo/systematicsJEC_"+variablesName[var]+version+".txt";
    eleUnf = plotpath+"ele/systematicsUnfMethod_"+variablesName[var]+version+".txt";
    muoUnf = plotpath+"muo/systematicsUnfMethod_"+variablesName[var]+version+".txt";
    elePU  = plotpath+"ele/systematicsPU_"+variablesName[var]+version+".txt";
    muoPU  = plotpath+"muo/systematicsPU_"+variablesName[var]+version+".txt";
    eleBkg = plotpath+"ele/BkgCrossSection_"+variablesName[var]+version+".txt";
    muoBkg = plotpath+"muo/BkgCrossSection_"+variablesName[var]+version+".txt";

    //    Statistical errors file paths:
    eleBkgStat = plotpath+"ele/backgroundStatError_"+variablesName[var]+version+".txt";
    muoBkgStat = plotpath+"muo/backgroundStatError_"+variablesName[var]+version+".txt";

    datahisto_ele   = combineLeptonSystematics::getDataHisto(var,"/gpfs/cms/data/2011/Unfolding/UlfoldedDistributions_v2_35.root");
    datahisto_muo   = combineLeptonSystematics::getDataHisto(var,"/gpfs/cms/data/2011/Unfolding/UlfoldedDistributionsMu_v2_35.root");
    datahisto_combi = combineLeptonSystematics::getDataHisto(var,"/gpfs/cms/data/2011/Unfolding/UlfoldedDistributionsCombined_v2_35.root");

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
    std::vector<double> jetEleUnf = combineLeptonSystematics::systOne(eleUnf);
    std::vector<double> jetMuoUnf = combineLeptonSystematics::systOne(muoUnf);
    std::vector<double> jetElePU  = combineLeptonSystematics::systOne(elePU); 
    std::vector<double> jetMuoPU  = combineLeptonSystematics::systOne(muoPU); 
    std::vector<double> jetEleBkg = combineLeptonSystematics::systOne(eleBkg);
    std::vector<double> jetMuoBkg = combineLeptonSystematics::systOne(muoBkg);

    std::vector<double> jetEff;
    jetEff.clear();
    std::vector<double> jetEffOld;
    jetEffOld.clear();
    std::vector<double> jetStat;
    jetStat.clear();

    // Correct Unfolding syst for Area uncertainty:
    for (Int_t nel=0;nel<jetMuoUnf.size();nel++) {
      jetEleUnf[nel] = sqrt(jetEleUnf[nel]*jetEleUnf[nel] + pow(jetEleUnfArea[var] * datahisto_ele->GetBinContent(nel+1),2));
      jetMuoUnf[nel] = sqrt(jetMuoUnf[nel]*jetMuoUnf[nel] + pow(jetMuoUnfArea[var] * datahisto_muo->GetBinContent(nel+1),2));
    }

    // Statistical uncertainties (data and bkg):
    std::vector<double> jetEleDataStat;
    jetEleDataStat.clear();
    std::vector<double> jetEleBkgStat;
    jetEleBkgStat.clear();
    ifstream inStat1;
    inStat1.open (eleBkgStat.c_str());
    double tmpStat1;
    double tmpStat2;
    while (1) {
      inStat1 >> tmpStat1 >> tmpStat2;
      if (!inStat1.good()) {
	break;
      }
      jetEleDataStat.push_back(sqrt(tmpStat1)/4890.0);
      jetEleBkgStat.push_back(sqrt(tmpStat2)/4890.0);
    }
    inStat1.close();

    std::vector<double> jetMuoDataStat;
    jetMuoDataStat.clear();
    std::vector<double> jetMuoBkgStat;
    jetMuoBkgStat.clear();
    ifstream inStat2;
    inStat2.open (muoBkgStat.c_str());
    while (1) {
      inStat2 >> tmpStat1 >> tmpStat2;
      if (!inStat2.good()) {
	break;
      }
      jetMuoDataStat.push_back(sqrt(tmpStat1)/4890.0);
      jetMuoBkgStat.push_back(sqrt(tmpStat2)/4890.0);
    }
    inStat2.close();

    // Compute the right contrib from efficiency:
    double epsilon=0.1;
    double dplus2ele=0.0;
    double dminus2ele=0.0;
    double dplus2muo=0.0;
    double dminus2muo=0.0;
    double sigmaplus2=0.0;
    double sigmaminus2=0.0;
    for (Int_t nec=0;nec<jetMuoUnf.size();nec++) {
      dplus2ele  = (1+epsilon)*(1+epsilon)*jetEleEff[nec]*jetEleEff[nec];
      dminus2ele = (1-epsilon)*(1-epsilon)*jetEleEff[nec]*jetEleEff[nec];
      dplus2muo  = (1+epsilon)*(1+epsilon)*jetMuoEff[nec]*jetMuoEff[nec];
      dminus2muo = (1-epsilon)*(1-epsilon)*jetMuoEff[nec]*jetMuoEff[nec];

      sigmaplus2  = 1.0/(1.0/(datahisto_ele->GetBinError(nec+1)*datahisto_ele->GetBinError(nec+1) + dplus2ele) 
			 + 1.0/(datahisto_muo->GetBinError(nec+1)*datahisto_muo->GetBinError(nec+1) + dplus2muo));
      sigmaminus2 = 1.0/(1.0/(datahisto_ele->GetBinError(nec+1)*datahisto_ele->GetBinError(nec+1) + dminus2ele) 
			 + 1.0/(datahisto_muo->GetBinError(nec+1)*datahisto_muo->GetBinError(nec+1) + dminus2muo));
      //      sigmaplus2  = 1.0/(1.0/(jetEleDataStat[nec]*jetEleDataStat[nec] + jetEleBkgStat[nec]*jetEleBkgStat[nec] + dplus2ele) 
      //		     + 1.0/(jetMuoDataStat[nec]*jetMuoDataStat[nec] + jetMuoBkgStat[nec]*jetMuoBkgStat[nec] + dplus2muo));
      //      sigmaminus2 = 1.0/(1.0/(jetEleDataStat[nec]*jetEleDataStat[nec] + jetEleBkgStat[nec]*jetEleBkgStat[nec] + dminus2ele) 
      //		     + 1.0/(jetMuoDataStat[nec]*jetMuoDataStat[nec] + jetMuoBkgStat[nec]*jetMuoBkgStat[nec] + dminus2muo));

      jetEff.push_back(sqrt((sigmaplus2 - sigmaminus2)/(4*epsilon)));
      //      jetStat.push_back(sqrt( 1.0/(1.0/(jetEleDataStat[nec]*jetEleDataStat[nec] + jetEleBkgStat[nec]*jetEleBkgStat[nec] + jetEleEff[nec]*jetEleEff[nec]) 
      //				 + 1.0/(jetMuoDataStat[nec]*jetMuoDataStat[nec] + jetMuoBkgStat[nec]*jetMuoBkgStat[nec] + jetMuoEff[nec]*jetMuoEff[nec]))
      //			     - (sigmaplus2 - sigmaminus2)/(4*epsilon)));
      jetStat.push_back(sqrt( 1.0/(1.0/(datahisto_ele->GetBinError(nec+1)*datahisto_ele->GetBinError(nec+1) + jetEleEff[nec]*jetEleEff[nec]) 
				 + 1.0/(datahisto_ele->GetBinError(nec+1)*datahisto_ele->GetBinError(nec+1) + jetMuoEff[nec]*jetMuoEff[nec]))
			      - (sigmaplus2 - sigmaminus2)/(4*epsilon)));
      jetEffOld.push_back(sqrt(1/(1/(jetEleEff[nec]*jetEleEff[nec]) + 1/(jetMuoEff[nec]*jetMuoEff[nec]))));

      if (variablesName[var] == "jetMult") cout << "jetEleDataStat = " << jetEleDataStat[nec] << " jetMuoDataStat = " << jetMuoDataStat[nec] << " jetEleBkgStat = " << jetEleBkgStat[nec] << " jetMuoBkgStat = " << jetMuoBkgStat[nec]  << endl;
    }

    cout << "   -> Computing combined systematics..." << endl;
    std::vector<double> jetSyst = combineLeptonSystematics::systSum(jetEff,jetEleJEC,jetEleUnf,jetElePU,jetEleBkg,jetEff,jetMuoJEC,jetMuoUnf,jetMuoPU,jetMuoBkg,datahisto_ele,datahisto_muo);   
    cout << "   -> Computing global systematics for electrons and muons..." << endl;
    std::vector<double> jetEleS = combineLeptonSystematics::systPar(jetEleEff,jetEleJEC,jetEleUnf,jetElePU,jetEleBkg);   
    std::vector<double> jetMuoS = combineLeptonSystematics::systPar(jetMuoEff,jetMuoJEC,jetMuoUnf,jetMuoPU,jetMuoBkg);   

    if ((jetSyst.size() != jetEleS.size()) || (jetSyst.size() != jetMuoS.size())) 
      cout << "Muon, electron and combined histos have different binnings!!! That may be a problem..."  << jetSyst.size() << "  " << jetEleS.size() << "  " << jetMuoS.size() << endl;

    if (datahisto_combi->GetNbinsX() != jetSyst.size()) cout << "TH1D's have different size from std::vector's!!!" << " TH1D: " << datahisto_ele->GetNbinsX() << " std::vector: " << jetSyst.size() << endl;

    // Write Systematics combination to file!!
    ofstream syste;
    syste.open(output.c_str());
    for (int i=0;i<jetSyst.size();i++){
      syste<<jetSyst[i]<<endl;
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

  std::vector<double> jetUnfArea;   
  jetUnfArea.clear();

  string UnfArea;
  double centralValue, rms;
  ifstream inUnfArea;

  if (isEleOrMuo == 1) UnfArea = plotpath+"ele/systematicsUnfArea_"+variablesUnfArea[1]+version+".txt";
  if (isEleOrMuo == 2) UnfArea = plotpath+"muo/systematicsUnfArea_"+variablesUnfArea[1]+version+".txt";
  inUnfArea.open (UnfArea.c_str());
  inUnfArea >> centralValue >> rms;
  inUnfArea.close ();
  jetUnfArea.push_back(fabs(rms/centralValue));

  for (Int_t n=0;n<3;n++) {
    for (Int_t m=0;m<4;m++) {
      if (isEleOrMuo == 1) UnfArea = plotpath+"ele/systematicsUnfArea_"+variablesUnfArea[m]+version+".txt";
      if (isEleOrMuo == 2) UnfArea = plotpath+"muo/systematicsUnfArea_"+variablesUnfArea[m]+version+".txt";
      inUnfArea.open (UnfArea.c_str());
      inUnfArea >> centralValue >> rms;
      inUnfArea.close ();
      jetUnfArea.push_back(fabs(rms/centralValue));
    }
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

  // singular systs
  textfile << "\\begin{sidewaystable}[htbH]" << endl
	   << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|}" << endl
           << "\\hline" << endl 
    	   << "\\multicolumn{5}{|c|}{Electron Systematics} \t&\t \\multicolumn{5}{|c|}{Muon Systematics} \t\\\\" << endl
           << "\\hline" << endl; 

  textfile << "Efficiency \t&\t JEC \t&\t Unfolding \t&\t PU \t&\t Bkg subtr. \t&\t Efficiency \t&\t JEC \t&\t Unfolding \t&\t PU \t&\t Bkg subtr. \t\\\\" << endl
	   << "\\hline" << endl; 

  for (Int_t i=0; i<jetSyst.size(); i++) {
    textfile.precision(3);
    textfile << jetEleEff[i] << "\t&\t" << jetEleJEC[i] << "\t&\t" << jetEleUnf[i] << "\t&\t" << jetElePU[i] << "\t&\t" << jetEleBkg[i] << "\t&\t"
  	     << jetMuoEff[i] << "\t&\t" << jetMuoJEC[i] << "\t&\t" << jetMuoUnf[i] << "\t&\t" << jetMuoPU[i] << "\t&\t" << jetMuoBkg[i] << "\t\\\\" << endl;
  }
  
  // combination systs
  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\caption{" << variablesName << "}" << endl
           << "\\label{tab:systematicstab}" << endl
	   << "\\end{center}" << endl
           << "\\end{sidewaystable}" << endl;

  textfile << "\\begin{sidewaystable}[htbH]" << endl
	   << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|c|c|}" << endl
           << "\\hline" << endl 
    	   << "\\multicolumn{3}{|c|}{DATA xsec (/pb)} \t&\t \\multicolumn{4}{|c|}{Data Uncertainties} \t&\t \\multicolumn{5}{|c|}{Global Systematics} \t\\\\" << endl
           << "\\hline" << endl; 

  textfile << "Electrons \t&\t Muons \t&\t Combined \t&\t Electrons \t&\t Muons \t&\t Combined \t&\t Combined 2 \t&\t Efficiency comb. \t&\t Efficiency comb.2 \t&\t Electrons \t&\t Muons \t&\t Combined \t\\\\" << endl
	   << "\\hline" << endl; 

  for (Int_t i=0; i<jetSyst.size(); i++) {
    textfile.precision(3);
    textfile << datahisto_ele->GetBinContent(i+1) << "\t&\t" << datahisto_muo->GetBinContent(i+1) << "\t&\t" << datahisto_combi->GetBinContent(i+1) << "\t&\t" ;
    textfile << datahisto_ele->GetBinError(i+1) << "\t&\t" << datahisto_muo->GetBinError(i+1)  << "\t&\t" <<  datahisto_combi->GetBinError(i+1)  << "\t&\t" <<  jetStat[i]  << "\t&\t" ;
    textfile << jetEffOld[i] << "\t&\t" << jetEff[i] << "\t&\t" << jetEleS[i]  << "\t&\t" << jetMuoS[i]   << "\t&\t" << jetSyst[i]   << "\t\\\\" << endl;
  }
  
  textfile << "\\hline" << endl
           << "\\end{tabular}" << endl
           << "\\caption{" << variablesName << "}" << endl
           << "\\label{tab:systematicstab}" << endl
	   << "\\end{center}" << endl
           << "\\end{sidewaystable}" << endl;

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
