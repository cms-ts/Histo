#include <vector>
#include <iostream>
#include <fstream>
#include <string.h>

class combineLeptonSystematics {
public:
  int letscombine ();
  int printLatex (std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, std::vector<double>, 
		  std::vector<double>, std::vector<double>, string, string);
  std::vector<double> systSum(string, string, string, string, string, string, string, string);
  std::vector<double> systPar(string, string, string, string);
  std::vector<double> systOne(string);
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
    cout << "-------------------------" << endl;
    cout << "Writing " << output  << " ..."<< endl;

    eleEff = plotpath+"ele/systematicsEff_"+variablesName[var]+version+".txt";
    muoEff = plotpath+"muo/systematicsEff_"+variablesName[var]+version+".txt";
    eleJEC = plotpath+"ele/systematicsJEC_"+variablesName[var]+version+".txt";
    muoJEC = plotpath+"muo/systematicsJEC_"+variablesName[var]+version+".txt";
    eleUnf = plotpath+"ele/systematicsUnfMethod_"+variablesName[var]+version+".txt";
    muoUnf = plotpath+"muo/systematicsUnfMethod_"+variablesName[var]+version+".txt";
    elePU  = plotpath+"ele/systematicsPU_"+variablesName[var]+version+".txt";
    muoPU  = plotpath+"muo/systematicsPU_"+variablesName[var]+version+".txt";

    cout << "   -> Computing combined systematics..." << endl;
    std::vector<double> jetSyst = combineLeptonSystematics::systSum(eleEff, muoEff, eleJEC, muoJEC, eleUnf, muoUnf, elePU, muoPU);   
    cout << "   -> Computing global systematics for electrons and muons..." << endl;
    std::vector<double> jetEleS = combineLeptonSystematics::systPar(eleEff, eleJEC, eleUnf, elePU);   
    std::vector<double> jetMuoS = combineLeptonSystematics::systPar(muoEff, muoJEC, muoUnf, muoPU);   

    cout << "   -> Writing exclusive systematics..." << endl;
    std::vector<double> jetEleEff = combineLeptonSystematics::systOne(eleEff);   
    std::vector<double> jetMuoEff = combineLeptonSystematics::systOne(muoEff);   
    std::vector<double> jetEleJEC = combineLeptonSystematics::systOne(eleJEC);   
    std::vector<double> jetMuoJEC = combineLeptonSystematics::systOne(muoJEC);   
    std::vector<double> jetEleUnf = combineLeptonSystematics::systOne(eleUnf);   
    std::vector<double> jetMuoUnf = combineLeptonSystematics::systOne(muoUnf);   
    std::vector<double> jetElePU  = combineLeptonSystematics::systOne(elePU);   
    std::vector<double> jetMuoPU  = combineLeptonSystematics::systOne(muoPU);   

    if ((jetSyst.size() != jetEleS.size()) || (jetSyst.size() != jetMuoS.size())) 
      cout << "Muon, electron and combined histos have different binnings!!! That may be a problem..." << endl;

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
					  jetMuoPU , varnameforlatex, version);
    
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

    tmpEff = sqrt(datEleEff*datEleEff + datMuoEff*datMuoEff);
    tmpJEC = (datEleJEC+datMuoJEC)/2;
    tmpUnf = (datEleUnf+datMuoUnf)/2;
    tmpPU  = sqrt(datElePU*datElePU + datMuoPU*datMuoPU);

    tmpSyst = sqrt(tmpEff*tmpEff + tmpJEC*tmpJEC + tmpUnf*tmpUnf + tmpPU*tmpPU);

    syst.push_back(tmpSyst);

    i++;  
  }

  cout << "   -> Combining " << i << " bins." << endl;

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


std::vector<double> combineLeptonSystematics::systPar(string parEff, string parJEC, string parUnf, string parPU){
	
  // Leggere nomi dei file da aprire
   
  std::vector<double> syst;
   
  ifstream inParEff;
  inParEff.open (parEff.c_str());

  ifstream inParJEC;
  inParJEC.open (parJEC.c_str());

  ifstream inParUnf;
  inParUnf.open (parUnf.c_str());

  ifstream inParPU;
  inParPU.open (parPU.c_str());
   
  int i=0;
  double datParEff;
  double datParJEC;
  double datParUnf;
  double datParPU;

  double tmpSyst;

  while (1) {
    inParEff >> datParEff;
    inParJEC >> datParJEC;
    inParUnf >> datParUnf;
    inParPU  >> datParPU;

    if (!inParEff.good() && !inParJEC.good() &&
	!inParUnf.good() && !inParPU.good()) {
      break;
    }

    // Dummy crosscheck on the number of bins in every file:
    if (!inParEff.good() || !inParJEC.good() ||
	!inParUnf.good() || !inParPU.good()) {
      cout << "PROBLEM WITH BINNING, EXITING COMBINATION LOOP!!!" << endl;
      break;
    }

    tmpSyst = sqrt(datParEff*datParEff + datParJEC*datParJEC + datParUnf*datParUnf + datParPU*datParPU);

    syst.push_back(tmpSyst);

    i++;  
  }

  cout << "   -> Combining " << i << " bins." << endl;

  inParEff.close();
  inParJEC.close();
  inParUnf.close();
  inParPU.close();

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

  cout << "   -> Writing " << i << " bins." << endl;

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
					  std::vector<double> jetMuoPU , string variablesName, string version) {
  
  ofstream textfile;
  string tablepath = "/gpfs/cms/users/schizzi/Systematics/tables/systematics_"+variablesName+version+".tex";
  textfile.open(tablepath.c_str(), ios_base::trunc);

  textfile.precision(2);

  textfile << "\\documentclass{article}" << endl;
  textfile << "\\begin{document}" << endl;
  textfile << "\\usepackage{rotating}" << endl;
  textfile << "\\begin{sidewaystable}[htbH]" << endl
	   << "\\begin{center}" << endl
           << "\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|c|}" << endl
           << "\\hline" << endl 
    	   << "\\multicolumn{4}{|c|}{Electron Systematics} \t&\t \\multicolumn{4}{|c|}{Muon Systematics} \t&\t \\multicolumn{3}{|c|}{Global Systematics} \t\\\\" << endl
           << "\\hline" << endl; 

  textfile << "Efficiency \t&\t JEC \t&\t Unfolding \t&\t PU \t&\t Efficiency \t&\t JEC \t&\t Unfolding \t&\t PU \t&\t Electrons \t&\t Muons \t&\t Combination \t\\\\" << endl
	   << "\\hline" << endl; 

  for (Int_t i=0; i<jetSyst.size(); i++) {
    textfile << jetEleEff[i] << "\t&\t" << jetEleJEC[i] << "\t&\t" << jetEleUnf[i] << "\t&\t" << jetElePU[i] << "\t&\t" 
  	     << jetMuoEff[i] << "\t&\t" << jetMuoJEC[i] << "\t&\t" << jetMuoUnf[i] << "\t&\t" << jetMuoPU[i] << "\t&\t" 
  	     << jetEleS[i]   << "\t&\t" << jetMuoS[i]   << "\t&\t" << jetSyst[i]   << "\t\\\\" << endl;
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
