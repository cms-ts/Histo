{
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
using namespace std;

 gROOT->LoadMacro("Observables.C++");
 gROOT->ProcessLine("Observables a;");
 gROOT->ForceStyle();
 gROOT->LoadMacro("tdrStyle.C++");
 tdrStyle();	
 gROOT->SetStyle("Plain");
 gROOT->ProcessLine("a.Loop();");
 //gROOT->LoadMacro("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/diow.C++");
 //gROOT->ProcessLine("diow();");
}
