#include <sstream>
#include <vector>
#include <iostream>
#include <TROOT.h>
#include "TObject.h"
#include <string.h>

class combineLeptonSystematics {
public:
  int letscombine ();
  std::vector<double> systSum(string eleEff, string muoEff, string eleJEC, string muoJEC, string eleUnf, string muoUnf, string elePU, string muoPU);
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
  string output;

  for (int var=0; var<variablesName.size(); var++){

    output=plotpath+"combination/"+variablesName[var]+"FinalSyst"+version+".txt";
    cout << "Writing " << output  << " ..."<< endl;

    eleEff = plotpath+"ele/systematicsEff_"+variablesName[var]+version+".txt";
    muoEff = plotpath+"muo/systematicsEff_"+variablesName[var]+version+".txt";
    eleJEC = plotpath+"ele/systematicsJEC_"+variablesName[var]+version+".txt";
    muoJEC = plotpath+"muo/systematicsJEC_"+variablesName[var]+version+".txt";
    eleUnf = plotpath+"ele/systematicsUnfMethod_"+variablesName[var]+version+".txt";
    muoUnf = plotpath+"muo/systematicsUnfMethod_"+variablesName[var]+version+".txt";
    elePU  = plotpath+"ele/systematicsPU_"+variablesName[var]+version+".txt";
    muoPU  = plotpath+"muo/systematicsPU_"+variablesName[var]+version+".txt";

    std::vector<double> jetSyst = systSum(eleEff, muoEff, eleJEC, muoJEC, eleUnf, muoUnf, elePU, muoPU);   

    ofstream syste;
    syste.open(output.c_str());
    for (int i=0;i<jetSyst.size();i++){
      syste<<jetSyst[i]<<endl;
    }
    syste.close();
  }

  return 0;
}


std::vector<double> combineLeptonSystematics::systSum(string eleEff, string muoEff, string eleJEC, string muoJEC, string eleUnf, string muoUnf, string elePU, string muoPU){
	
  // Leggere nomi dei file da aprire
   
  std::vector<double> syst;
   
  ifstream inEleEff;
  inEleEff.open (eleEff.c_str());
  ifstream inMuoEff;
  inMuoEff.open (muoEff.c_str());

  ifstream inEleJEC;
  inEleJEC.open (eleJEC.c_str());
  ifstream inMuoJEC;
  inMuoJEC.open (muoJEC.c_str());

  ifstream inEleUnf;
  inEleUnf.open (eleUnf.c_str());
  ifstream inMuoUnf;
  inMuoUnf.open (muoUnf.c_str());

  ifstream inElePU;
  inElePU.open (elePU.c_str());
  ifstream inMuoPU;
  inMuoPU.open (muoPU.c_str());
   
  int i=0;
  double datEleEff;
  double datMuoEff;
  double datEleJEC;
  double datMuoJEC;
  double datEleUnf;
  double datMuoUnf;
  double datElePU;
  double datMuoPU;

  double tmpEff;
  double tmpJEC;
  double tmpUnf;
  double tmpPU;

  double tmpSyst;

  while (1) {
    inEleEff >> datEleEff;
    inMuoEff >> datMuoEff;
    inEleJEC >> datEleJEC;
    inMuoJEC >> datMuoJEC;
    inEleUnf >> datEleUnf;
    inMuoUnf >> datMuoUnf;
    inElePU  >> datElePU;
    inMuoPU  >> datMuoPU;

    if (!inEleEff.good() && !inMuoEff.good() && !inEleJEC.good() && !inMuoJEC.good() &&
	!inEleUnf.good() && !inMuoUnf.good() && !inElePU.good()  && !inMuoPU.good()) {
      break;
    }

    // Dummy crosscheck on the number of bins in every file:
    if (!inEleEff.good() || !inMuoEff.good() || !inEleJEC.good() || !inMuoJEC.good() ||
	!inEleUnf.good() || !inMuoUnf.good() || !inElePU.good()  || !inMuoPU.good()) {
      cout << "PROBLEM WITH BINNING, EXITING COMBINATION LOOP!!!" << endl;
      break;
    }

    if (!inMuoEff.good()) break;
    if (!inEleJEC.good()) break;
    if (!inMuoJEC.good()) break;
    if (!inEleUnf.good()) break;
    if (!inMuoUnf.good()) break;
    if (!inElePU.good()) break;
    if (!inMuoPU.good()) break;

    tmpEff = sqrt(datEleEff*datEleEff + datMuoEff*datMuoEff);
    tmpJEC = (datEleJEC+datMuoJEC)/2;
    tmpUnf = (datEleUnf+datMuoUnf)/2;
    tmpPU  = sqrt(datElePU*datElePU + datMuoPU*datMuoPU);

    tmpSyst = sqrt(tmpEff*tmpEff + tmpJEC*tmpJEC + tmpUnf*tmpUnf + tmpPU*tmpPU);

    syst.push_back(tmpSyst);

    i++;  
  }

  cout << "   Combining " << i << " bins." << endl;

  inEleEff.close();
  inMuoEff.close();
  inEleJEC.close();
  inMuoJEC.close();
  inEleUnf.close();
  inMuoUnf.close();
  inElePU.close();
  inMuoPU.close();

  return syst;
}
