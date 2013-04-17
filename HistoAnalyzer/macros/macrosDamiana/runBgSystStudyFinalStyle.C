{
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include <iostream>
  gROOT->LoadMacro("bgSystStudyFinalStyle.c");
  gROOT->ProcessLine("bgSystStudyFinalStyle()");
}
