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

}
