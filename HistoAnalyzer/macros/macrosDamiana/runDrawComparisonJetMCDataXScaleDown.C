{
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
  gROOT->LoadMacro("DrawComparisonJetMCDataScaleDown.C++");
  gROOT->ProcessLine("DrawComparisonJetMCDataScaleDown()");
}
