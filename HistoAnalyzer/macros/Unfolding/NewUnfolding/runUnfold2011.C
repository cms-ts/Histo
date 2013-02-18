{
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
using namespace std;

 gSystem->Load("libRooUnfold");
 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ForceStyle();
 gROOT->LoadMacro("tdrStyle.C++");
 tdrStyle();	
 gROOT->SetStyle("Plain");
 gROOT->ProcessLine("a.Loop();");
 //gROOT->LoadMacro("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/diow.C++");
 //gROOT->ProcessLine("diow();");
}
