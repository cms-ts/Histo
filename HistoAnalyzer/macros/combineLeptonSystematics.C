#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"
#include "TLine.h"
#include <TH2.h>
#include "TF1.h"
#include <TStyle.h>
#include <TCanvas.h>
#include "TRandom.h"
#include "TH1D.h"
#include "TFile.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TLine.h"
#include <sstream>
#include "TCut.h"
#include "TLatex.h"
#include <vector>
#include <iostream>
#include "tdrStyle.C"
#include <TROOT.h>
#include "TObject.h"
#include <iostream>
#include <sstream>
#include "TTree.h"
#include "TH2.h"
#include "THStack.h"
#include "TLatex.h"
#include "TColor.h"
#include <string.h>


int combineLeptonSystematics () {
   
  string version="_v2_32";
  string plotpathIn="/gpfs/cms/users/schizzi/Systematics/";
  string plotpathOut="/gpfs/cms/users/schizzi/Systematics/";

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

  for (int var=0; var<variablesName.size(); var++){
    string nameFile = plotpathIn+variablesName[var]+"SystFile.dat";
    std::vector<double> jetSyst = systSum(nameFile);   
    cout << "writing ...   "<<endl;
    string output=plotpathOut+variablesName[var]+"FinalSyst"+version+".txt";
    ofstream syste;
    syste.open(output.c_str());
    for (int i=0;i<jetSyst.size();i++){
      syste<<jetSyst[i]<<endl;
    }
    cout << "written   "<<output<<endl;
    cout <<"............................................"<<endl;
  }

  return 0;
}


std::vector<double> systSum(string nameFile){
	
  //_______leggere nomi dei file da aprire__________________
   
  std::vector<double> syst;
  std::vector<string> name;
  name.clear();
   
  ifstream in;
  in.open (nameFile.c_str());
   
  int i=0;
  string nameTmp;
  cout <<"reading the files ... "<< endl;
  while (1) {
    getline (in, nameTmp);
    //cout <<i<<" "<< nameTmp<<endl;
    if (!in.good()) break;
    name.push_back(nameTmp);
    cout <<i+1<<" "<< name[i]<<endl;
    i++;
  }
  in.close();
   
  //__________leggere in un ciclo	i file corrispondenti_______
   
  string indi;
  double dat;
  int l1=0;
   
  for (int it=0; it< name.size(); it++) {
    indi=name[it];
    ifstream in;
    in.open (indi.c_str());
    int l2 =0;
    while (1) {
      in >> dat;
      if (!in.good()) break;
      if (l1==0){syst.push_back(dat);}
      else {
	double systTmp = sqrt(syst[l2]*syst[l2]+dat*dat);
	syst[l2]=systTmp;
      }
      l2++;  
    }
      
    in.close();      
    l1++;
  }
   
  return syst;

}
