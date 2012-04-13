{
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
  gROOT->LoadMacro("EvaluateDifferenceBetweenVersions.C++");
  gROOT->ProcessLine("DrawDifferences()");
}
