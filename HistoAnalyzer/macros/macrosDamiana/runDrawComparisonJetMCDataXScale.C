{
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
  gROOT->LoadMacro("DrawComparisonJetMCDataXScale.C++");
  gROOT->ProcessLine("DrawComparisonJetMCDataXScale()");
}
