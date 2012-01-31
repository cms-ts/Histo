{
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
using namespace std;


 gSystem->Load("libRooUnfold");
 gROOT->LoadMacro("UnfoldingIdentityCheck.C++");
 gROOT->ProcessLine("UnfoldingIdentityCheck a;");
 gROOT->ForceStyle();
 gROOT->LoadMacro("tdrStyle.C++");
 tdrStyle();	
 gROOT->SetStyle("Plain");
 gROOT->ProcessLine("a.Loop();");
 //gROOT->LoadMacro("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/diow.C++");
 //diow("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/PythiaZ2Check/","/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/PythiaZ2Check/index.html");

}
