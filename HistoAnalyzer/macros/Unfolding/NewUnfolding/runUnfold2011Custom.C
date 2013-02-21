{
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
using namespace std;

//////////////////////// Mu ////////////////////////////////////////

 gSystem->Load("libRooUnfold");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ForceStyle();
 gROOT->LoadMacro("tdrStyle.C++");
 tdrStyle();	
 gROOT->SetStyle("Plain");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Multiplicity\"\,1,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,1,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,2,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,3,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,4,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,1,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,2,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,3,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,4,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,1,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,2,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,3,true);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,4,true);");


 //////////////////////////////////  Ele 


 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ForceStyle();
 gROOT->LoadMacro("tdrStyle.C++");
 tdrStyle();	
 gROOT->SetStyle("Plain");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Multiplicity\"\,1,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,1,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,2,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,3,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,4,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,1,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,2,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,3,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,4,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,1,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,2,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,3,false);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,4,false);");

}
