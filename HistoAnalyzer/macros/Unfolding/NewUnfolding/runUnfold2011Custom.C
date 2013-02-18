{
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
using namespace std;

 gSystem->Load("libRooUnfold");
 // gROOT->LoadMacro("UnfoldingVJets2011.C++");
 // gROOT->ProcessLine("UnfoldingVJets2011 a;");
//  gROOT->ForceStyle();
//  gROOT->LoadMacro("tdrStyle.C++");
//  tdrStyle();	
//  gROOT->SetStyle("Plain");
//  gROOT->ProcessLine("a.LoopText(\"SVD\",\"Multiplicity\"\,1);");

//  gROOT->LoadMacro("UnfoldingVJets2011.C++");
//  gROOT->ProcessLine("UnfoldingVJets2011 a;");
//  gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,1);");

//  gROOT->LoadMacro("UnfoldingVJets2011.C++");
//  gROOT->ProcessLine("UnfoldingVJets2011 a;");
//  gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,2);");

//  gROOT->LoadMacro("UnfoldingVJets2011.C++");
//  gROOT->ProcessLine("UnfoldingVJets2011 a;");
//  gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,3);");

//  gROOT->LoadMacro("UnfoldingVJets2011.C++");
//  gROOT->ProcessLine("UnfoldingVJets2011 a;");
//  gROOT->ProcessLine("a.LoopText(\"SVD\",\"Pt\"\,4);");

//  gROOT->LoadMacro("UnfoldingVJets2011.C++");
//  gROOT->ProcessLine("UnfoldingVJets2011 a;");
//  gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,1);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,2);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,3);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Ht\"\,4);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,1);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,2);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,3);");

 gROOT->LoadMacro("UnfoldingVJets2011.C++");
 gROOT->ProcessLine("UnfoldingVJets2011 a;");
 gROOT->ProcessLine("a.LoopText(\"SVD\",\"Eta\"\,4);");


 //gROOT->LoadMacro("/afs/infn.it/ts/user/marone/html/ZJets/Unfolding/diow.C++");
 //gROOT->ProcessLine("diow();");
}
