/**********************************
 * Get the efficiencies to correct plots
 * Matteo Marone
 *********************************/
#include <TH2.h>
#include "TF1.h"
#include <TStyle.h>
#include <TCanvas.h>
#include "TRandom.h"
#include "TH1D.h"
#include "TFile.h"
#include "TPaveStats.h"
#include "TLegend.h"
#include "TH1.h"

//////// Muon POG HLT:
Double_t Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATA(Double_t eta1, Double_t eta2) {
  if( eta1>=-2.4 && eta1<-2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.814586;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.854611;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.86971;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.875898;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.875702;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.8851;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.846657;
    else if( eta2>=-0.2 && eta2<0) return 0.883122;
    else if( eta2>=0 && eta2<0.2) return 0.884678;
    else if( eta2>=0.2 && eta2<0.3) return 0.854316;
    else if( eta2>=0.3 && eta2<0.6) return 0.882569;
    else if( eta2>=0.6 && eta2<0.9) return 0.876532;
    else if( eta2>=0.9 && eta2<1.2) return 0.873346;
    else if( eta2>=1.2 && eta2<1.6) return 0.867453;
    else if( eta2>=1.6 && eta2<2.1) return 0.859233;
    else if( eta2>=2.1 && eta2<=2.4) return 0.812599;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-2.1 && eta1<-1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.854611;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.896249;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.912003;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.918465;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.918238;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.928077;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.887775;
    else if( eta2>=-0.2 && eta2<0) return 0.926008;
    else if( eta2>=0 && eta2<0.2) return 0.927634;
    else if( eta2>=0.2 && eta2<0.3) return 0.895801;
    else if( eta2>=0.3 && eta2<0.6) return 0.925424;
    else if( eta2>=0.6 && eta2<0.9) return 0.919108;
    else if( eta2>=0.9 && eta2<1.2) return 0.915799;
    else if( eta2>=1.2 && eta2<1.6) return 0.909644;
    else if( eta2>=1.6 && eta2<2.1) return 0.901108;
    else if( eta2>=2.1 && eta2<=2.4) return 0.8525;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.6 && eta1<-1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.86971;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.912003;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.928013;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.934583;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.934348;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.944355;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.903349;
    else if( eta2>=-0.2 && eta2<0) return 0.942251;
    else if( eta2>=0 && eta2<0.2) return 0.943905;
    else if( eta2>=0.2 && eta2<0.3) return 0.911514;
    else if( eta2>=0.3 && eta2<0.6) return 0.941656;
    else if( eta2>=0.6 && eta2<0.9) return 0.935232;
    else if( eta2>=0.9 && eta2<1.2) return 0.931873;
    else if( eta2>=1.2 && eta2<1.6) return 0.925616;
    else if( eta2>=1.6 && eta2<2.1) return 0.916949;
    else if( eta2>=2.1 && eta2<=2.4) return 0.867556;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.2 && eta1<-0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.875898;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.918465;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.934583;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.941198;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.940959;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.951036;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.90974;
    else if( eta2>=-0.2 && eta2<0) return 0.948918;
    else if( eta2>=0 && eta2<0.2) return 0.950582;
    else if( eta2>=0.2 && eta2<0.3) return 0.917963;
    else if( eta2>=0.3 && eta2<0.6) return 0.948318;
    else if( eta2>=0.6 && eta2<0.9) return 0.941849;
    else if( eta2>=0.9 && eta2<1.2) return 0.938469;
    else if( eta2>=1.2 && eta2<1.6) return 0.932169;
    else if( eta2>=1.6 && eta2<2.1) return 0.923447;
    else if( eta2>=2.1 && eta2<=2.4) return 0.873727;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.9 && eta1<-0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.875702;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.918238;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.934348;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.940959;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.940719;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.950792;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.909507;
    else if( eta2>=-0.2 && eta2<0) return 0.948675;
    else if( eta2>=0 && eta2<0.2) return 0.950339;
    else if( eta2>=0.2 && eta2<0.3) return 0.917728;
    else if( eta2>=0.3 && eta2<0.6) return 0.948075;
    else if( eta2>=0.6 && eta2<0.9) return 0.941609;
    else if( eta2>=0.9 && eta2<1.2) return 0.938231;
    else if( eta2>=1.2 && eta2<1.6) return 0.931935;
    else if( eta2>=1.6 && eta2<2.1) return 0.92322;
    else if( eta2>=2.1 && eta2<=2.4) return 0.873529;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.6 && eta1<-0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.8851;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.928077;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.944355;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.951036;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.950792;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.960973;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.919246;
    else if( eta2>=-0.2 && eta2<0) return 0.958833;
    else if( eta2>=0 && eta2<0.2) return 0.960515;
    else if( eta2>=0.2 && eta2<0.3) return 0.927555;
    else if( eta2>=0.3 && eta2<0.6) return 0.958226;
    else if( eta2>=0.6 && eta2<0.9) return 0.951692;
    else if( eta2>=0.9 && eta2<1.2) return 0.94828;
    else if( eta2>=1.2 && eta2<1.6) return 0.941917;
    else if( eta2>=1.6 && eta2<2.1) return 0.933112;
    else if( eta2>=2.1 && eta2<=2.4) return 0.882904;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.3 && eta1<-0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.846657;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.887775;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.903349;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.90974;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.909507;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.919246;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.879331;
    else if( eta2>=-0.2 && eta2<0) return 0.917199;
    else if( eta2>=0 && eta2<0.2) return 0.918808;
    else if( eta2>=0.2 && eta2<0.3) return 0.887279;
    else if( eta2>=0.3 && eta2<0.6) return 0.916619;
    else if( eta2>=0.6 && eta2<0.9) return 0.910368;
    else if( eta2>=0.9 && eta2<1.2) return 0.907103;
    else if( eta2>=1.2 && eta2<1.6) return 0.901016;
    else if( eta2>=1.6 && eta2<2.1) return 0.892592;
    else if( eta2>=2.1 && eta2<=2.4) return 0.844556;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.2 && eta1<0) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.883122;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.926008;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.942251;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.948918;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.948675;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.958833;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.917199;
    else if( eta2>=-0.2 && eta2<0) return 0.956698;
    else if( eta2>=0 && eta2<0.2) return 0.958376;
    else if( eta2>=0.2 && eta2<0.3) return 0.925489;
    else if( eta2>=0.3 && eta2<0.6) return 0.956093;
    else if( eta2>=0.6 && eta2<0.9) return 0.949573;
    else if( eta2>=0.9 && eta2<1.2) return 0.946167;
    else if( eta2>=1.2 && eta2<1.6) return 0.939818;
    else if( eta2>=1.6 && eta2<2.1) return 0.931032;
    else if( eta2>=2.1 && eta2<=2.4) return 0.880931;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0 && eta1<0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.884678;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.927634;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.943905;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.950582;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.950339;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.960515;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.918808;
    else if( eta2>=-0.2 && eta2<0) return 0.958376;
    else if( eta2>=0 && eta2<0.2) return 0.960057;
    else if( eta2>=0.2 && eta2<0.3) return 0.927112;
    else if( eta2>=0.3 && eta2<0.6) return 0.957769;
    else if( eta2>=0.6 && eta2<0.9) return 0.951238;
    else if( eta2>=0.9 && eta2<1.2) return 0.947827;
    else if( eta2>=1.2 && eta2<1.6) return 0.941468;
    else if( eta2>=1.6 && eta2<2.1) return 0.932667;
    else if( eta2>=2.1 && eta2<=2.4) return 0.882482;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.2 && eta1<0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.854316;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.895801;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.911514;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.917963;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.917728;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.927555;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.887279;
    else if( eta2>=-0.2 && eta2<0) return 0.925489;
    else if( eta2>=0 && eta2<0.2) return 0.927112;
    else if( eta2>=0.2 && eta2<0.3) return 0.895298;
    else if( eta2>=0.3 && eta2<0.6) return 0.924903;
    else if( eta2>=0.6 && eta2<0.9) return 0.918596;
    else if( eta2>=0.9 && eta2<1.2) return 0.915302;
    else if( eta2>=1.2 && eta2<1.6) return 0.90916;
    else if( eta2>=1.6 && eta2<2.1) return 0.900661;
    else if( eta2>=2.1 && eta2<=2.4) return 0.852196;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.3 && eta1<0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.882569;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.925424;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.941656;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.948318;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.948075;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.958226;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.916619;
    else if( eta2>=-0.2 && eta2<0) return 0.956093;
    else if( eta2>=0 && eta2<0.2) return 0.957769;
    else if( eta2>=0.2 && eta2<0.3) return 0.924903;
    else if( eta2>=0.3 && eta2<0.6) return 0.955488;
    else if( eta2>=0.6 && eta2<0.9) return 0.948972;
    else if( eta2>=0.9 && eta2<1.2) return 0.945569;
    else if( eta2>=1.2 && eta2<1.6) return 0.939225;
    else if( eta2>=1.6 && eta2<2.1) return 0.930445;
    else if( eta2>=2.1 && eta2<=2.4) return 0.880379;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.6 && eta1<0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.876532;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.919108;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.935232;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.941849;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.941609;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.951692;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.910368;
    else if( eta2>=-0.2 && eta2<0) return 0.949573;
    else if( eta2>=0 && eta2<0.2) return 0.951238;
    else if( eta2>=0.2 && eta2<0.3) return 0.918596;
    else if( eta2>=0.3 && eta2<0.6) return 0.948972;
    else if( eta2>=0.6 && eta2<0.9) return 0.9425;
    else if( eta2>=0.9 && eta2<1.2) return 0.939119;
    else if( eta2>=1.2 && eta2<1.6) return 0.932817;
    else if( eta2>=1.6 && eta2<2.1) return 0.924094;
    else if( eta2>=2.1 && eta2<=2.4) return 0.874358;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.9 && eta1<1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.873346;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.915799;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.931873;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.938469;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.938231;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.94828;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.907103;
    else if( eta2>=-0.2 && eta2<0) return 0.946167;
    else if( eta2>=0 && eta2<0.2) return 0.947827;
    else if( eta2>=0.2 && eta2<0.3) return 0.915302;
    else if( eta2>=0.3 && eta2<0.6) return 0.945569;
    else if( eta2>=0.6 && eta2<0.9) return 0.939119;
    else if( eta2>=0.9 && eta2<1.2) return 0.935747;
    else if( eta2>=1.2 && eta2<1.6) return 0.929465;
    else if( eta2>=1.6 && eta2<2.1) return 0.920766;
    else if( eta2>=2.1 && eta2<=2.4) return 0.871181;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.2 && eta1<1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.867453;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.909644;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.925616;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.932169;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.931935;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.941917;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.901016;
    else if( eta2>=-0.2 && eta2<0) return 0.939818;
    else if( eta2>=0 && eta2<0.2) return 0.941468;
    else if( eta2>=0.2 && eta2<0.3) return 0.90916;
    else if( eta2>=0.3 && eta2<0.6) return 0.939225;
    else if( eta2>=0.6 && eta2<0.9) return 0.932817;
    else if( eta2>=0.9 && eta2<1.2) return 0.929465;
    else if( eta2>=1.2 && eta2<1.6) return 0.923224;
    else if( eta2>=1.6 && eta2<2.1) return 0.914577;
    else if( eta2>=2.1 && eta2<=2.4) return 0.865305;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.6 && eta1<2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.859233;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.901108;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.916949;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.923447;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.92322;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.933112;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.892592;
    else if( eta2>=-0.2 && eta2<0) return 0.931032;
    else if( eta2>=0 && eta2<0.2) return 0.932667;
    else if( eta2>=0.2 && eta2<0.3) return 0.900661;
    else if( eta2>=0.3 && eta2<0.6) return 0.930445;
    else if( eta2>=0.6 && eta2<0.9) return 0.924094;
    else if( eta2>=0.9 && eta2<1.2) return 0.920766;
    else if( eta2>=1.2 && eta2<1.6) return 0.914577;
    else if( eta2>=1.6 && eta2<2.1) return 0.905992;
    else if( eta2>=2.1 && eta2<=2.4) return 0.857112;
    else return 0.;
    return 0.;
  }
  else if( eta1>=2.1 && eta1<=2.4) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.812599;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.8525;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.867556;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.873727;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.873529;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.882904;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.844556;
    else if( eta2>=-0.2 && eta2<0) return 0.880931;
    else if( eta2>=0 && eta2<0.2) return 0.882482;
    else if( eta2>=0.2 && eta2<0.3) return 0.852196;
    else if( eta2>=0.3 && eta2<0.6) return 0.880379;
    else if( eta2>=0.6 && eta2<0.9) return 0.874358;
    else if( eta2>=0.9 && eta2<1.2) return 0.871181;
    else if( eta2>=1.2 && eta2<1.6) return 0.865305;
    else if( eta2>=1.6 && eta2<2.1) return 0.857112;
    else if( eta2>=2.1 && eta2<=2.4) return 0.810614;
    else return 0.;
    return 0.;
  }
  else return 0.;
  return 0.;
}

Double_t Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_MC(Double_t eta1, Double_t eta2) {
  if( eta1>=-2.4 && eta1<-2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.846665;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.885059;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.896988;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.900202;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.899378;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.909826;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.887235;
    else if( eta2>=-0.2 && eta2<0) return 0.907031;
    else if( eta2>=0 && eta2<0.2) return 0.907324;
    else if( eta2>=0.2 && eta2<0.3) return 0.886888;
    else if( eta2>=0.3 && eta2<0.6) return 0.909496;
    else if( eta2>=0.6 && eta2<0.9) return 0.895606;
    else if( eta2>=0.9 && eta2<1.2) return 0.899665;
    else if( eta2>=1.2 && eta2<1.6) return 0.8952;
    else if( eta2>=1.6 && eta2<2.1) return 0.880749;
    else if( eta2>=2.1 && eta2<=2.4) return 0.839691;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-2.1 && eta1<-1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.885059;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.92487;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.937251;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.940604;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.939721;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.950636;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.927033;
    else if( eta2>=-0.2 && eta2<0) return 0.947715;
    else if( eta2>=0 && eta2<0.2) return 0.948022;
    else if( eta2>=0.2 && eta2<0.3) return 0.92667;
    else if( eta2>=0.3 && eta2<0.6) return 0.950293;
    else if( eta2>=0.6 && eta2<0.9) return 0.935781;
    else if( eta2>=0.9 && eta2<1.2) return 0.940049;
    else if( eta2>=1.2 && eta2<1.6) return 0.935387;
    else if( eta2>=1.6 && eta2<2.1) return 0.920379;
    else if( eta2>=2.1 && eta2<=2.4) return 0.877748;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.6 && eta1<-1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.896988;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.937251;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.949775;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.953171;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.952271;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.963331;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.939414;
    else if( eta2>=-0.2 && eta2<0) return 0.960372;
    else if( eta2>=0 && eta2<0.2) return 0.960683;
    else if( eta2>=0.2 && eta2<0.3) return 0.939046;
    else if( eta2>=0.3 && eta2<0.6) return 0.962984;
    else if( eta2>=0.6 && eta2<0.9) return 0.948279;
    else if( eta2>=0.9 && eta2<1.2) return 0.952611;
    else if( eta2>=1.2 && eta2<1.6) return 0.947887;
    else if( eta2>=1.6 && eta2<2.1) return 0.932703;
    else if( eta2>=2.1 && eta2<=2.4) return 0.889573;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.2 && eta1<-0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.900202;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.940604;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.953171;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.956579;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.955676;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.966775;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.942773;
    else if( eta2>=-0.2 && eta2<0) return 0.963805;
    else if( eta2>=0 && eta2<0.2) return 0.964117;
    else if( eta2>=0.2 && eta2<0.3) return 0.942403;
    else if( eta2>=0.3 && eta2<0.6) return 0.966427;
    else if( eta2>=0.6 && eta2<0.9) return 0.951669;
    else if( eta2>=0.9 && eta2<1.2) return 0.956017;
    else if( eta2>=1.2 && eta2<1.6) return 0.951276;
    else if( eta2>=1.6 && eta2<2.1) return 0.936039;
    else if( eta2>=2.1 && eta2<=2.4) return 0.892759;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.9 && eta1<-0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.899378;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.939721;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.952271;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.955676;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.954772;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.96586;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.941881;
    else if( eta2>=-0.2 && eta2<0) return 0.962893;
    else if( eta2>=0 && eta2<0.2) return 0.963205;
    else if( eta2>=0.2 && eta2<0.3) return 0.941512;
    else if( eta2>=0.3 && eta2<0.6) return 0.965512;
    else if( eta2>=0.6 && eta2<0.9) return 0.950769;
    else if( eta2>=0.9 && eta2<1.2) return 0.955114;
    else if( eta2>=1.2 && eta2<1.6) return 0.950379;
    else if( eta2>=1.6 && eta2<2.1) return 0.935162;
    else if( eta2>=2.1 && eta2<=2.4) return 0.891941;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.6 && eta1<-0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.909826;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.950636;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.963331;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.966775;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.96586;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.977077;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.952819;
    else if( eta2>=-0.2 && eta2<0) return 0.974076;
    else if( eta2>=0 && eta2<0.2) return 0.974391;
    else if( eta2>=0.2 && eta2<0.3) return 0.952446;
    else if( eta2>=0.3 && eta2<0.6) return 0.976725;
    else if( eta2>=0.6 && eta2<0.9) return 0.96181;
    else if( eta2>=0.9 && eta2<1.2) return 0.966207;
    else if( eta2>=1.2 && eta2<1.6) return 0.961416;
    else if( eta2>=1.6 && eta2<2.1) return 0.946024;
    else if( eta2>=2.1 && eta2<=2.4) return 0.902303;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.3 && eta1<-0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.887235;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.927033;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.939414;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.942773;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.941881;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.952819;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.929164;
    else if( eta2>=-0.2 && eta2<0) return 0.949892;
    else if( eta2>=0 && eta2<0.2) return 0.9502;
    else if( eta2>=0.2 && eta2<0.3) return 0.9288;
    else if( eta2>=0.3 && eta2<0.6) return 0.952476;
    else if( eta2>=0.6 && eta2<0.9) return 0.937932;
    else if( eta2>=0.9 && eta2<1.2) return 0.942218;
    else if( eta2>=1.2 && eta2<1.6) return 0.937547;
    else if( eta2>=1.6 && eta2<2.1) return 0.922536;
    else if( eta2>=2.1 && eta2<=2.4) return 0.879899;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.2 && eta1<0) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.907031;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.947715;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.960372;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.963805;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.962893;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.974076;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.949892;
    else if( eta2>=-0.2 && eta2<0) return 0.971084;
    else if( eta2>=0 && eta2<0.2) return 0.971398;
    else if( eta2>=0.2 && eta2<0.3) return 0.94952;
    else if( eta2>=0.3 && eta2<0.6) return 0.973725;
    else if( eta2>=0.6 && eta2<0.9) return 0.958856;
    else if( eta2>=0.9 && eta2<1.2) return 0.963239;
    else if( eta2>=1.2 && eta2<1.6) return 0.958463;
    else if( eta2>=1.6 && eta2<2.1) return 0.943117;
    else if( eta2>=2.1 && eta2<=2.4) return 0.89953;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0 && eta1<0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.907324;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.948022;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.960683;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.964117;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.963205;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.974391;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.9502;
    else if( eta2>=-0.2 && eta2<0) return 0.971398;
    else if( eta2>=0 && eta2<0.2) return 0.971713;
    else if( eta2>=0.2 && eta2<0.3) return 0.949828;
    else if( eta2>=0.3 && eta2<0.6) return 0.97404;
    else if( eta2>=0.6 && eta2<0.9) return 0.959166;
    else if( eta2>=0.9 && eta2<1.2) return 0.963551;
    else if( eta2>=1.2 && eta2<1.6) return 0.958773;
    else if( eta2>=1.6 && eta2<2.1) return 0.943423;
    else if( eta2>=2.1 && eta2<=2.4) return 0.899822;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.2 && eta1<0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.886888;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.92667;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.939046;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.942403;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.941512;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.952446;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.9288;
    else if( eta2>=-0.2 && eta2<0) return 0.94952;
    else if( eta2>=0 && eta2<0.2) return 0.949828;
    else if( eta2>=0.2 && eta2<0.3) return 0.928436;
    else if( eta2>=0.3 && eta2<0.6) return 0.952103;
    else if( eta2>=0.6 && eta2<0.9) return 0.937564;
    else if( eta2>=0.9 && eta2<1.2) return 0.941849;
    else if( eta2>=1.2 && eta2<1.6) return 0.93718;
    else if( eta2>=1.6 && eta2<2.1) return 0.922174;
    else if( eta2>=2.1 && eta2<=2.4) return 0.879554;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.3 && eta1<0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.909496;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.950293;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.962984;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.966427;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.965512;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.976725;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.952476;
    else if( eta2>=-0.2 && eta2<0) return 0.973725;
    else if( eta2>=0 && eta2<0.2) return 0.97404;
    else if( eta2>=0.2 && eta2<0.3) return 0.952103;
    else if( eta2>=0.3 && eta2<0.6) return 0.976374;
    else if( eta2>=0.6 && eta2<0.9) return 0.961464;
    else if( eta2>=0.9 && eta2<1.2) return 0.965859;
    else if( eta2>=1.2 && eta2<1.6) return 0.96107;
    else if( eta2>=1.6 && eta2<2.1) return 0.945682;
    else if( eta2>=2.1 && eta2<=2.4) return 0.901975;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.6 && eta1<0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.895606;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.935781;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.948279;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.951669;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.950769;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.96181;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.937932;
    else if( eta2>=-0.2 && eta2<0) return 0.958856;
    else if( eta2>=0 && eta2<0.2) return 0.959166;
    else if( eta2>=0.2 && eta2<0.3) return 0.937564;
    else if( eta2>=0.3 && eta2<0.6) return 0.961464;
    else if( eta2>=0.6 && eta2<0.9) return 0.946782;
    else if( eta2>=0.9 && eta2<1.2) return 0.951109;
    else if( eta2>=1.2 && eta2<1.6) return 0.946394;
    else if( eta2>=1.6 && eta2<2.1) return 0.931241;
    else if( eta2>=2.1 && eta2<=2.4) return 0.8882;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.9 && eta1<1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.899665;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.940049;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.952611;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.956017;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.955114;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.966207;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.942218;
    else if( eta2>=-0.2 && eta2<0) return 0.963239;
    else if( eta2>=0 && eta2<0.2) return 0.963551;
    else if( eta2>=0.2 && eta2<0.3) return 0.941849;
    else if( eta2>=0.3 && eta2<0.6) return 0.965859;
    else if( eta2>=0.6 && eta2<0.9) return 0.951109;
    else if( eta2>=0.9 && eta2<1.2) return 0.955454;
    else if( eta2>=1.2 && eta2<1.6) return 0.950717;
    else if( eta2>=1.6 && eta2<2.1) return 0.935487;
    else if( eta2>=2.1 && eta2<=2.4) return 0.892228;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.2 && eta1<1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.8952;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.935387;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.947887;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.951276;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.950379;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.961416;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.937547;
    else if( eta2>=-0.2 && eta2<0) return 0.958463;
    else if( eta2>=0 && eta2<0.2) return 0.958773;
    else if( eta2>=0.2 && eta2<0.3) return 0.93718;
    else if( eta2>=0.3 && eta2<0.6) return 0.96107;
    else if( eta2>=0.6 && eta2<0.9) return 0.946394;
    else if( eta2>=0.9 && eta2<1.2) return 0.950717;
    else if( eta2>=1.2 && eta2<1.6) return 0.946003;
    else if( eta2>=1.6 && eta2<2.1) return 0.930847;
    else if( eta2>=2.1 && eta2<=2.4) return 0.8878;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.6 && eta1<2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.880749;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.920379;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.932703;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.936039;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.935162;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.946024;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.922536;
    else if( eta2>=-0.2 && eta2<0) return 0.943117;
    else if( eta2>=0 && eta2<0.2) return 0.943423;
    else if( eta2>=0.2 && eta2<0.3) return 0.922174;
    else if( eta2>=0.3 && eta2<0.6) return 0.945682;
    else if( eta2>=0.6 && eta2<0.9) return 0.931241;
    else if( eta2>=0.9 && eta2<1.2) return 0.935487;
    else if( eta2>=1.2 && eta2<1.6) return 0.930847;
    else if( eta2>=1.6 && eta2<2.1) return 0.915909;
    else if( eta2>=2.1 && eta2<=2.4) return 0.873474;
    else return 0.;
    return 0.;
  }
  else if( eta1>=2.1 && eta1<=2.4) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.839691;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.877748;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.889573;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.892759;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.891941;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.902303;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.879899;
    else if( eta2>=-0.2 && eta2<0) return 0.89953;
    else if( eta2>=0 && eta2<0.2) return 0.899822;
    else if( eta2>=0.2 && eta2<0.3) return 0.879554;
    else if( eta2>=0.3 && eta2<0.6) return 0.901975;
    else if( eta2>=0.6 && eta2<0.9) return 0.8882;
    else if( eta2>=0.9 && eta2<1.2) return 0.892228;
    else if( eta2>=1.2 && eta2<1.6) return 0.8878;
    else if( eta2>=1.6 && eta2<2.1) return 0.873474;
    else if( eta2>=2.1 && eta2<=2.4) return 0.832773;
    else return 0.;
    return 0.;
  }
  else return 0.;
  return 0.;
}

Double_t Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(Double_t eta1, Double_t eta2) {
  if( eta1>=-2.4 && eta1<-2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.962112;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.965597;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.96959;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.973002;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.973675;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.972823;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.954265;
    else if( eta2>=-0.2 && eta2<0) return 0.973641;
    else if( eta2>=0 && eta2<0.2) return 0.97504;
    else if( eta2>=0.2 && eta2<0.3) return 0.963274;
    else if( eta2>=0.3 && eta2<0.6) return 0.970394;
    else if( eta2>=0.6 && eta2<0.9) return 0.978703;
    else if( eta2>=0.9 && eta2<1.2) return 0.970745;
    else if( eta2>=1.2 && eta2<1.6) return 0.969005;
    else if( eta2>=1.6 && eta2<2.1) return 0.975571;
    else if( eta2>=2.1 && eta2<=2.4) return 0.967735;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-2.1 && eta1<-1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.965597;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.969054;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.973061;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.976463;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.977139;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.97627;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.957652;
    else if( eta2>=-0.2 && eta2<0) return 0.977096;
    else if( eta2>=0 && eta2<0.2) return 0.978494;
    else if( eta2>=0.2 && eta2<0.3) return 0.966688;
    else if( eta2>=0.3 && eta2<0.6) return 0.973831;
    else if( eta2>=0.6 && eta2<0.9) return 0.982183;
    else if( eta2>=0.9 && eta2<1.2) return 0.974204;
    else if( eta2>=1.2 && eta2<1.6) return 0.972479;
    else if( eta2>=1.6 && eta2<2.1) return 0.979062;
    else if( eta2>=2.1 && eta2<=2.4) return 0.971235;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.6 && eta1<-1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.96959;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.973061;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.977087;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.980499;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.981178;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.980302;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.961609;
    else if( eta2>=-0.2 && eta2<0) return 0.981132;
    else if( eta2>=0 && eta2<0.2) return 0.982535;
    else if( eta2>=0.2 && eta2<0.3) return 0.970681;
    else if( eta2>=0.3 && eta2<0.6) return 0.977852;
    else if( eta2>=0.6 && eta2<0.9) return 0.986242;
    else if( eta2>=0.9 && eta2<1.2) return 0.978231;
    else if( eta2>=1.2 && eta2<1.6) return 0.976504;
    else if( eta2>=1.6 && eta2<2.1) return 0.98311;
    else if( eta2>=2.1 && eta2<=2.4) return 0.975251;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.2 && eta1<-0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.973002;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.976463;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.980499;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.98392;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.9846;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98372;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.964962;
    else if( eta2>=-0.2 && eta2<0) return 0.984554;
    else if( eta2>=0 && eta2<0.2) return 0.985961;
    else if( eta2>=0.2 && eta2<0.3) return 0.974066;
    else if( eta2>=0.3 && eta2<0.6) return 0.981262;
    else if( eta2>=0.6 && eta2<0.9) return 0.989682;
    else if( eta2>=0.9 && eta2<1.2) return 0.981645;
    else if( eta2>=1.2 && eta2<1.6) return 0.979914;
    else if( eta2>=1.6 && eta2<2.1) return 0.986547;
    else if( eta2>=2.1 && eta2<=2.4) return 0.978681;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.9 && eta1<-0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.973675;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.977139;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.981178;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.9846;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.985281;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.9844;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.965629;
    else if( eta2>=-0.2 && eta2<0) return 0.985234;
    else if( eta2>=0 && eta2<0.2) return 0.986642;
    else if( eta2>=0.2 && eta2<0.3) return 0.974739;
    else if( eta2>=0.3 && eta2<0.6) return 0.98194;
    else if( eta2>=0.6 && eta2<0.9) return 0.990366;
    else if( eta2>=0.9 && eta2<1.2) return 0.982324;
    else if( eta2>=1.2 && eta2<1.6) return 0.980593;
    else if( eta2>=1.6 && eta2<2.1) return 0.98723;
    else if( eta2>=2.1 && eta2<=2.4) return 0.979358;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.6 && eta1<-0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.972823;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.97627;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.980302;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.98372;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.9844;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.983518;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.964765;
    else if( eta2>=-0.2 && eta2<0) return 0.984352;
    else if( eta2>=0 && eta2<0.2) return 0.985759;
    else if( eta2>=0.2 && eta2<0.3) return 0.973866;
    else if( eta2>=0.3 && eta2<0.6) return 0.98106;
    else if( eta2>=0.6 && eta2<0.9) return 0.98948;
    else if( eta2>=0.9 && eta2<1.2) return 0.981446;
    else if( eta2>=1.2 && eta2<1.6) return 0.979718;
    else if( eta2>=1.6 && eta2<2.1) return 0.986352;
    else if( eta2>=2.1 && eta2<=2.4) return 0.9785;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.3 && eta1<-0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.954265;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.957652;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.961609;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.964962;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.965629;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.964765;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.946369;
    else if( eta2>=-0.2 && eta2<0) return 0.965582;
    else if( eta2>=0 && eta2<0.2) return 0.966963;
    else if( eta2>=0.2 && eta2<0.3) return 0.955296;
    else if( eta2>=0.3 && eta2<0.6) return 0.962354;
    else if( eta2>=0.6 && eta2<0.9) return 0.970612;
    else if( eta2>=0.9 && eta2<1.2) return 0.962731;
    else if( eta2>=1.2 && eta2<1.6) return 0.961036;
    else if( eta2>=1.6 && eta2<2.1) return 0.967542;
    else if( eta2>=2.1 && eta2<=2.4) return 0.959834;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.2 && eta1<0) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.973641;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.977096;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.981132;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.984554;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.985234;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.984352;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.965582;
    else if( eta2>=-0.2 && eta2<0) return 0.985186;
    else if( eta2>=0 && eta2<0.2) return 0.986594;
    else if( eta2>=0.2 && eta2<0.3) return 0.974691;
    else if( eta2>=0.3 && eta2<0.6) return 0.981892;
    else if( eta2>=0.6 && eta2<0.9) return 0.990318;
    else if( eta2>=0.9 && eta2<1.2) return 0.982277;
    else if( eta2>=1.2 && eta2<1.6) return 0.980548;
    else if( eta2>=1.6 && eta2<2.1) return 0.987186;
    else if( eta2>=2.1 && eta2<=2.4) return 0.979323;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0 && eta1<0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.97504;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.978494;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.982535;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.985961;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.986642;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.985759;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.966963;
    else if( eta2>=-0.2 && eta2<0) return 0.986594;
    else if( eta2>=0 && eta2<0.2) return 0.988005;
    else if( eta2>=0.2 && eta2<0.3) return 0.976085;
    else if( eta2>=0.3 && eta2<0.6) return 0.983295;
    else if( eta2>=0.6 && eta2<0.9) return 0.991734;
    else if( eta2>=0.9 && eta2<1.2) return 0.983682;
    else if( eta2>=1.2 && eta2<1.6) return 0.98195;
    else if( eta2>=1.6 && eta2<2.1) return 0.9886;
    else if( eta2>=2.1 && eta2<=2.4) return 0.98073;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.2 && eta1<0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.963274;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.966688;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.970681;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.974066;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.974739;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.973866;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.955296;
    else if( eta2>=-0.2 && eta2<0) return 0.974691;
    else if( eta2>=0 && eta2<0.2) return 0.976085;
    else if( eta2>=0.2 && eta2<0.3) return 0.964308;
    else if( eta2>=0.3 && eta2<0.6) return 0.971432;
    else if( eta2>=0.6 && eta2<0.9) return 0.979769;
    else if( eta2>=0.9 && eta2<1.2) return 0.971814;
    else if( eta2>=1.2 && eta2<1.6) return 0.970103;
    else if( eta2>=1.6 && eta2<2.1) return 0.976671;
    else if( eta2>=2.1 && eta2<=2.4) return 0.968895;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.3 && eta1<0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.970394;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.973831;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.977852;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.981262;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.98194;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98106;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.962354;
    else if( eta2>=-0.2 && eta2<0) return 0.981892;
    else if( eta2>=0 && eta2<0.2) return 0.983295;
    else if( eta2>=0.2 && eta2<0.3) return 0.971432;
    else if( eta2>=0.3 && eta2<0.6) return 0.978608;
    else if( eta2>=0.6 && eta2<0.9) return 0.987007;
    else if( eta2>=0.9 && eta2<1.2) return 0.978993;
    else if( eta2>=1.2 && eta2<1.6) return 0.97727;
    else if( eta2>=1.6 && eta2<2.1) return 0.983888;
    else if( eta2>=2.1 && eta2<=2.4) return 0.976057;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.6 && eta1<0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.978703;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.982183;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.986242;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.989682;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.990366;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98948;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.970612;
    else if( eta2>=-0.2 && eta2<0) return 0.990318;
    else if( eta2>=0 && eta2<0.2) return 0.991734;
    else if( eta2>=0.2 && eta2<0.3) return 0.979769;
    else if( eta2>=0.3 && eta2<0.6) return 0.987007;
    else if( eta2>=0.6 && eta2<0.9) return 0.995477;
    else if( eta2>=0.9 && eta2<1.2) return 0.987393;
    else if( eta2>=1.2 && eta2<1.6) return 0.985654;
    else if( eta2>=1.6 && eta2<2.1) return 0.992326;
    else if( eta2>=2.1 && eta2<=2.4) return 0.984415;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.9 && eta1<1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.970745;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.974204;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.978231;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.981645;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.982324;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.981446;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.962731;
    else if( eta2>=-0.2 && eta2<0) return 0.982277;
    else if( eta2>=0 && eta2<0.2) return 0.983682;
    else if( eta2>=0.2 && eta2<0.3) return 0.971814;
    else if( eta2>=0.3 && eta2<0.6) return 0.978993;
    else if( eta2>=0.6 && eta2<0.9) return 0.987393;
    else if( eta2>=0.9 && eta2<1.2) return 0.979374;
    else if( eta2>=1.2 && eta2<1.6) return 0.977647;
    else if( eta2>=1.6 && eta2<2.1) return 0.984264;
    else if( eta2>=2.1 && eta2<=2.4) return 0.976411;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.2 && eta1<1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.969005;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.972479;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.976504;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.979914;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.980593;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.979718;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.961036;
    else if( eta2>=-0.2 && eta2<0) return 0.980548;
    else if( eta2>=0 && eta2<0.2) return 0.98195;
    else if( eta2>=0.2 && eta2<0.3) return 0.970103;
    else if( eta2>=0.3 && eta2<0.6) return 0.97727;
    else if( eta2>=0.6 && eta2<0.9) return 0.985654;
    else if( eta2>=0.9 && eta2<1.2) return 0.977647;
    else if( eta2>=1.2 && eta2<1.6) return 0.975921;
    else if( eta2>=1.6 && eta2<2.1) return 0.982521;
    else if( eta2>=2.1 && eta2<=2.4) return 0.974662;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.6 && eta1<2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.975571;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.979062;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.98311;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.986547;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.98723;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.986352;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.967542;
    else if( eta2>=-0.2 && eta2<0) return 0.987186;
    else if( eta2>=0 && eta2<0.2) return 0.9886;
    else if( eta2>=0.2 && eta2<0.3) return 0.976671;
    else if( eta2>=0.3 && eta2<0.6) return 0.983888;
    else if( eta2>=0.6 && eta2<0.9) return 0.992326;
    else if( eta2>=0.9 && eta2<1.2) return 0.984264;
    else if( eta2>=1.2 && eta2<1.6) return 0.982521;
    else if( eta2>=1.6 && eta2<2.1) return 0.989173;
    else if( eta2>=2.1 && eta2<=2.4) return 0.981267;
    else return 0.;
    return 0.;
  }
  else if( eta1>=2.1 && eta1<=2.4) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.967735;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.971235;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.975251;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.978681;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.979358;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.9785;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.959834;
    else if( eta2>=-0.2 && eta2<0) return 0.979323;
    else if( eta2>=0 && eta2<0.2) return 0.98073;
    else if( eta2>=0.2 && eta2<0.3) return 0.968895;
    else if( eta2>=0.3 && eta2<0.6) return 0.976057;
    else if( eta2>=0.6 && eta2<0.9) return 0.984415;
    else if( eta2>=0.9 && eta2<1.2) return 0.976411;
    else if( eta2>=1.2 && eta2<1.6) return 0.974662;
    else if( eta2>=1.6 && eta2<2.1) return 0.981267;
    else if( eta2>=2.1 && eta2<=2.4) return 0.973391;
    else return 0.;
    return 0.;
  }
  else return 0.;
  return 0.;
}

Double_t Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_DATA(Double_t eta1, Double_t eta2) {
  if( eta1>=-2.4 && eta1<-2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.683784;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.783309;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.797219;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.802663;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.802375;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.81108;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.775747;
    else if( eta2>=-0.2 && eta2<0) return 0.809198;
    else if( eta2>=0 && eta2<0.2) return 0.810635;
    else if( eta2>=0.2 && eta2<0.3) return 0.783068;
    else if( eta2>=0.3 && eta2<0.6) return 0.808557;
    else if( eta2>=0.6 && eta2<0.9) return 0.803173;
    else if( eta2>=0.9 && eta2<1.2) return 0.800397;
    else if( eta2>=1.2 && eta2<1.6) return 0.794997;
    else if( eta2>=1.6 && eta2<2.1) return 0.787449;
    else if( eta2>=2.1 && eta2<=2.4) return 0.742006;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-2.1 && eta1<-1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.783309;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.897;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.912839;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.919061;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.918718;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.928674;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.888225;
    else if( eta2>=-0.2 && eta2<0) return 0.926524;
    else if( eta2>=0 && eta2<0.2) return 0.928164;
    else if( eta2>=0.2 && eta2<0.3) return 0.896602;
    else if( eta2>=0.3 && eta2<0.6) return 0.925783;
    else if( eta2>=0.6 && eta2<0.9) return 0.919631;
    else if( eta2>=0.9 && eta2<1.2) return 0.916467;
    else if( eta2>=1.2 && eta2<1.6) return 0.910305;
    else if( eta2>=1.6 && eta2<2.1) return 0.901755;
    else if( eta2>=2.1 && eta2<=2.4) return 0.849978;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.6 && eta1<-1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.797219;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.912839;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.928934;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.935262;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.93491;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.945037;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.903878;
    else if( eta2>=-0.2 && eta2<0) return 0.942851;
    else if( eta2>=0 && eta2<0.2) return 0.944518;
    else if( eta2>=0.2 && eta2<0.3) return 0.912401;
    else if( eta2>=0.3 && eta2<0.6) return 0.942095;
    else if( eta2>=0.6 && eta2<0.9) return 0.935838;
    else if( eta2>=0.9 && eta2<1.2) return 0.932622;
    else if( eta2>=1.2 && eta2<1.6) return 0.926358;
    else if( eta2>=1.6 && eta2<2.1) return 0.917683;
    else if( eta2>=2.1 && eta2<=2.4) return 0.865065;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.2 && eta1<-0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.802663;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.919061;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.935262;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.941632;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.941278;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.951473;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.910034;
    else if( eta2>=-0.2 && eta2<0) return 0.949273;
    else if( eta2>=0 && eta2<0.2) return 0.950951;
    else if( eta2>=0.2 && eta2<0.3) return 0.918615;
    else if( eta2>=0.3 && eta2<0.6) return 0.948511;
    else if( eta2>=0.6 && eta2<0.9) return 0.942212;
    else if( eta2>=0.9 && eta2<1.2) return 0.938975;
    else if( eta2>=1.2 && eta2<1.6) return 0.932669;
    else if( eta2>=1.6 && eta2<2.1) return 0.923938;
    else if( eta2>=2.1 && eta2<=2.4) return 0.87097;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.9 && eta1<-0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.802375;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.918718;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.93491;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.941278;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.940922;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.951114;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.909691;
    else if( eta2>=-0.2 && eta2<0) return 0.948914;
    else if( eta2>=0 && eta2<0.2) return 0.950591;
    else if( eta2>=0.2 && eta2<0.3) return 0.918268;
    else if( eta2>=0.3 && eta2<0.6) return 0.948152;
    else if( eta2>=0.6 && eta2<0.9) return 0.941856;
    else if( eta2>=0.9 && eta2<1.2) return 0.938621;
    else if( eta2>=1.2 && eta2<1.6) return 0.932318;
    else if( eta2>=1.6 && eta2<2.1) return 0.923594;
    else if( eta2>=2.1 && eta2<=2.4) return 0.870657;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.6 && eta1<-0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.81108;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.928674;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.945037;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.951473;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.951114;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.961415;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.919544;
    else if( eta2>=-0.2 && eta2<0) return 0.959192;
    else if( eta2>=0 && eta2<0.2) return 0.960887;
    else if( eta2>=0.2 && eta2<0.3) return 0.928214;
    else if( eta2>=0.3 && eta2<0.6) return 0.958422;
    else if( eta2>=0.6 && eta2<0.9) return 0.952058;
    else if( eta2>=0.9 && eta2<1.2) return 0.948788;
    else if( eta2>=1.2 && eta2<1.6) return 0.942418;
    else if( eta2>=1.6 && eta2<2.1) return 0.933603;
    else if( eta2>=2.1 && eta2<=2.4) return 0.880102;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.3 && eta1<-0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.775747;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.888225;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.903878;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.910034;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.909691;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.919544;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.879496;
    else if( eta2>=-0.2 && eta2<0) return 0.917417;
    else if( eta2>=0 && eta2<0.2) return 0.919038;
    else if( eta2>=0.2 && eta2<0.3) return 0.887788;
    else if( eta2>=0.3 && eta2<0.6) return 0.916681;
    else if( eta2>=0.6 && eta2<0.9) return 0.910594;
    else if( eta2>=0.9 && eta2<1.2) return 0.907466;
    else if( eta2>=1.2 && eta2<1.6) return 0.901373;
    else if( eta2>=1.6 && eta2<2.1) return 0.89294;
    else if( eta2>=2.1 && eta2<=2.4) return 0.841763;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.2 && eta1<0) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.809198;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.926524;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.942851;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.949273;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.948914;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.959192;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.917417;
    else if( eta2>=-0.2 && eta2<0) return 0.956974;
    else if( eta2>=0 && eta2<0.2) return 0.958665;
    else if( eta2>=0.2 && eta2<0.3) return 0.926067;
    else if( eta2>=0.3 && eta2<0.6) return 0.956205;
    else if( eta2>=0.6 && eta2<0.9) return 0.949856;
    else if( eta2>=0.9 && eta2<1.2) return 0.946593;
    else if( eta2>=1.2 && eta2<1.6) return 0.940237;
    else if( eta2>=1.6 && eta2<2.1) return 0.931441;
    else if( eta2>=2.1 && eta2<=2.4) return 0.87806;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0 && eta1<0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.810635;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.928164;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.944518;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.950951;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.950591;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.960887;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.919038;
    else if( eta2>=-0.2 && eta2<0) return 0.958665;
    else if( eta2>=0 && eta2<0.2) return 0.960359;
    else if( eta2>=0.2 && eta2<0.3) return 0.927704;
    else if( eta2>=0.3 && eta2<0.6) return 0.957895;
    else if( eta2>=0.6 && eta2<0.9) return 0.951535;
    else if( eta2>=0.9 && eta2<1.2) return 0.948266;
    else if( eta2>=1.2 && eta2<1.6) return 0.9419;
    else if( eta2>=1.6 && eta2<2.1) return 0.93309;
    else if( eta2>=2.1 && eta2<=2.4) return 0.879619;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.2 && eta1<0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.783068;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.896602;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.912401;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.918615;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.918268;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.928214;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.887788;
    else if( eta2>=-0.2 && eta2<0) return 0.926067;
    else if( eta2>=0 && eta2<0.2) return 0.927704;
    else if( eta2>=0.2 && eta2<0.3) return 0.896159;
    else if( eta2>=0.3 && eta2<0.6) return 0.925324;
    else if( eta2>=0.6 && eta2<0.9) return 0.919179;
    else if( eta2>=0.9 && eta2<1.2) return 0.916022;
    else if( eta2>=1.2 && eta2<1.6) return 0.909872;
    else if( eta2>=1.6 && eta2<2.1) return 0.901361;
    else if( eta2>=2.1 && eta2<=2.4) return 0.849706;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.3 && eta1<0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.808557;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.925783;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.942095;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.948511;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.948152;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.958422;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.916681;
    else if( eta2>=-0.2 && eta2<0) return 0.956205;
    else if( eta2>=0 && eta2<0.2) return 0.957895;
    else if( eta2>=0.2 && eta2<0.3) return 0.925324;
    else if( eta2>=0.3 && eta2<0.6) return 0.955438;
    else if( eta2>=0.6 && eta2<0.9) return 0.949094;
    else if( eta2>=0.9 && eta2<1.2) return 0.945834;
    else if( eta2>=1.2 && eta2<1.6) return 0.939484;
    else if( eta2>=1.6 && eta2<2.1) return 0.930697;
    else if( eta2>=2.1 && eta2<=2.4) return 0.877364;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.6 && eta1<0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.803173;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.919631;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.935838;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.942212;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.941856;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.952058;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.910594;
    else if( eta2>=-0.2 && eta2<0) return 0.949856;
    else if( eta2>=0 && eta2<0.2) return 0.951535;
    else if( eta2>=0.2 && eta2<0.3) return 0.919179;
    else if( eta2>=0.3 && eta2<0.6) return 0.949094;
    else if( eta2>=0.6 && eta2<0.9) return 0.942791;
    else if( eta2>=0.9 && eta2<1.2) return 0.939553;
    else if( eta2>=1.2 && eta2<1.6) return 0.933244;
    else if( eta2>=1.6 && eta2<2.1) return 0.924512;
    else if( eta2>=2.1 && eta2<=2.4) return 0.871523;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.9 && eta1<1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.800397;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.916467;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.932622;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.938975;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.938621;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.948788;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.907466;
    else if( eta2>=-0.2 && eta2<0) return 0.946593;
    else if( eta2>=0 && eta2<0.2) return 0.948266;
    else if( eta2>=0.2 && eta2<0.3) return 0.916022;
    else if( eta2>=0.3 && eta2<0.6) return 0.945834;
    else if( eta2>=0.6 && eta2<0.9) return 0.939553;
    else if( eta2>=0.9 && eta2<1.2) return 0.936324;
    else if( eta2>=1.2 && eta2<1.6) return 0.930036;
    else if( eta2>=1.6 && eta2<2.1) return 0.92133;
    else if( eta2>=2.1 && eta2<=2.4) return 0.868512;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.2 && eta1<1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.794997;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.910305;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.926358;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.932669;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.932318;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.942418;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.901373;
    else if( eta2>=-0.2 && eta2<0) return 0.940237;
    else if( eta2>=0 && eta2<0.2) return 0.9419;
    else if( eta2>=0.2 && eta2<0.3) return 0.909872;
    else if( eta2>=0.3 && eta2<0.6) return 0.939484;
    else if( eta2>=0.6 && eta2<0.9) return 0.933244;
    else if( eta2>=0.9 && eta2<1.2) return 0.930036;
    else if( eta2>=1.2 && eta2<1.6) return 0.923789;
    else if( eta2>=1.6 && eta2<2.1) return 0.915135;
    else if( eta2>=2.1 && eta2<=2.4) return 0.862654;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.6 && eta1<2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.787449;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.901755;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.917683;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.923938;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.923594;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.933603;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.89294;
    else if( eta2>=-0.2 && eta2<0) return 0.931441;
    else if( eta2>=0 && eta2<0.2) return 0.93309;
    else if( eta2>=0.2 && eta2<0.3) return 0.901361;
    else if( eta2>=0.3 && eta2<0.6) return 0.930697;
    else if( eta2>=0.6 && eta2<0.9) return 0.924512;
    else if( eta2>=0.9 && eta2<1.2) return 0.92133;
    else if( eta2>=1.2 && eta2<1.6) return 0.915135;
    else if( eta2>=1.6 && eta2<2.1) return 0.906535;
    else if( eta2>=2.1 && eta2<=2.4) return 0.854471;
    else return 0.;
    return 0.;
  }
  else if( eta1>=2.1 && eta1<=2.4) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.742006;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.849978;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.865065;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.87097;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.870657;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.880102;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.841763;
    else if( eta2>=-0.2 && eta2<0) return 0.87806;
    else if( eta2>=0 && eta2<0.2) return 0.879619;
    else if( eta2>=0.2 && eta2<0.3) return 0.849706;
    else if( eta2>=0.3 && eta2<0.6) return 0.877364;
    else if( eta2>=0.6 && eta2<0.9) return 0.871523;
    else if( eta2>=0.9 && eta2<1.2) return 0.868512;
    else if( eta2>=1.2 && eta2<1.6) return 0.862654;
    else if( eta2>=1.6 && eta2<2.1) return 0.854471;
    else if( eta2>=2.1 && eta2<=2.4) return 0.805183;
    else return 0.;
    return 0.;
  }
  else return 0.;
  return 0.;
}

Double_t Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_MC(Double_t eta1, Double_t eta2) {
  if( eta1>=-2.4 && eta1<-2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.846754;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.885084;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.897003;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.900219;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.899382;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.909829;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.887239;
    else if( eta2>=-0.2 && eta2<0) return 0.907034;
    else if( eta2>=0 && eta2<0.2) return 0.907328;
    else if( eta2>=0.2 && eta2<0.3) return 0.886891;
    else if( eta2>=0.3 && eta2<0.6) return 0.9095;
    else if( eta2>=0.6 && eta2<0.9) return 0.895609;
    else if( eta2>=0.9 && eta2<1.2) return 0.899687;
    else if( eta2>=1.2 && eta2<1.6) return 0.895219;
    else if( eta2>=1.6 && eta2<2.1) return 0.880775;
    else if( eta2>=2.1 && eta2<=2.4) return 0.839747;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-2.1 && eta1<-1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.885084;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.924877;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.937255;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.940608;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.939722;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.950636;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.927034;
    else if( eta2>=-0.2 && eta2<0) return 0.947716;
    else if( eta2>=0 && eta2<0.2) return 0.948023;
    else if( eta2>=0.2 && eta2<0.3) return 0.926671;
    else if( eta2>=0.3 && eta2<0.6) return 0.950294;
    else if( eta2>=0.6 && eta2<0.9) return 0.935782;
    else if( eta2>=0.9 && eta2<1.2) return 0.940055;
    else if( eta2>=1.2 && eta2<1.6) return 0.935392;
    else if( eta2>=1.6 && eta2<2.1) return 0.920386;
    else if( eta2>=2.1 && eta2<=2.4) return 0.877763;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.6 && eta1<-1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.897003;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.937255;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.949777;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.953173;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.952272;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.963331;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.939414;
    else if( eta2>=-0.2 && eta2<0) return 0.960372;
    else if( eta2>=0 && eta2<0.2) return 0.960683;
    else if( eta2>=0.2 && eta2<0.3) return 0.939046;
    else if( eta2>=0.3 && eta2<0.6) return 0.962984;
    else if( eta2>=0.6 && eta2<0.9) return 0.948279;
    else if( eta2>=0.9 && eta2<1.2) return 0.952613;
    else if( eta2>=1.2 && eta2<1.6) return 0.947889;
    else if( eta2>=1.6 && eta2<2.1) return 0.932707;
    else if( eta2>=2.1 && eta2<=2.4) return 0.889585;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.2 && eta1<-0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.900219;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.940608;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.953173;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.956581;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.955676;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.966775;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.942773;
    else if( eta2>=-0.2 && eta2<0) return 0.963805;
    else if( eta2>=0 && eta2<0.2) return 0.964117;
    else if( eta2>=0.2 && eta2<0.3) return 0.942404;
    else if( eta2>=0.3 && eta2<0.6) return 0.966427;
    else if( eta2>=0.6 && eta2<0.9) return 0.951669;
    else if( eta2>=0.9 && eta2<1.2) return 0.956019;
    else if( eta2>=1.2 && eta2<1.6) return 0.951278;
    else if( eta2>=1.6 && eta2<2.1) return 0.936045;
    else if( eta2>=2.1 && eta2<=2.4) return 0.892774;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.9 && eta1<-0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.899382;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.939722;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.952272;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.955676;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.954772;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.96586;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.941881;
    else if( eta2>=-0.2 && eta2<0) return 0.962893;
    else if( eta2>=0 && eta2<0.2) return 0.963205;
    else if( eta2>=0.2 && eta2<0.3) return 0.941512;
    else if( eta2>=0.3 && eta2<0.6) return 0.965513;
    else if( eta2>=0.6 && eta2<0.9) return 0.950769;
    else if( eta2>=0.9 && eta2<1.2) return 0.955115;
    else if( eta2>=1.2 && eta2<1.6) return 0.950379;
    else if( eta2>=1.6 && eta2<2.1) return 0.935163;
    else if( eta2>=2.1 && eta2<=2.4) return 0.891944;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.6 && eta1<-0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.909829;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.950636;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.963331;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.966775;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.96586;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.977077;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.952819;
    else if( eta2>=-0.2 && eta2<0) return 0.974076;
    else if( eta2>=0 && eta2<0.2) return 0.974391;
    else if( eta2>=0.2 && eta2<0.3) return 0.952446;
    else if( eta2>=0.3 && eta2<0.6) return 0.976725;
    else if( eta2>=0.6 && eta2<0.9) return 0.96181;
    else if( eta2>=0.9 && eta2<1.2) return 0.966207;
    else if( eta2>=1.2 && eta2<1.6) return 0.961416;
    else if( eta2>=1.6 && eta2<2.1) return 0.946024;
    else if( eta2>=2.1 && eta2<=2.4) return 0.902305;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.3 && eta1<-0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.887239;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.927034;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.939414;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.942773;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.941881;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.952819;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.929164;
    else if( eta2>=-0.2 && eta2<0) return 0.949892;
    else if( eta2>=0 && eta2<0.2) return 0.9502;
    else if( eta2>=0.2 && eta2<0.3) return 0.9288;
    else if( eta2>=0.3 && eta2<0.6) return 0.952476;
    else if( eta2>=0.6 && eta2<0.9) return 0.937932;
    else if( eta2>=0.9 && eta2<1.2) return 0.942219;
    else if( eta2>=1.2 && eta2<1.6) return 0.937547;
    else if( eta2>=1.6 && eta2<2.1) return 0.922537;
    else if( eta2>=2.1 && eta2<=2.4) return 0.879902;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.2 && eta1<0) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.907034;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.947716;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.960372;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.963805;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.962893;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.974076;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.949892;
    else if( eta2>=-0.2 && eta2<0) return 0.971084;
    else if( eta2>=0 && eta2<0.2) return 0.971398;
    else if( eta2>=0.2 && eta2<0.3) return 0.94952;
    else if( eta2>=0.3 && eta2<0.6) return 0.973725;
    else if( eta2>=0.6 && eta2<0.9) return 0.958856;
    else if( eta2>=0.9 && eta2<1.2) return 0.963239;
    else if( eta2>=1.2 && eta2<1.6) return 0.958463;
    else if( eta2>=1.6 && eta2<2.1) return 0.943118;
    else if( eta2>=2.1 && eta2<=2.4) return 0.899534;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0 && eta1<0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.907328;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.948023;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.960683;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.964117;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.963205;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.974391;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.9502;
    else if( eta2>=-0.2 && eta2<0) return 0.971398;
    else if( eta2>=0 && eta2<0.2) return 0.971713;
    else if( eta2>=0.2 && eta2<0.3) return 0.949828;
    else if( eta2>=0.3 && eta2<0.6) return 0.974041;
    else if( eta2>=0.6 && eta2<0.9) return 0.959166;
    else if( eta2>=0.9 && eta2<1.2) return 0.963551;
    else if( eta2>=1.2 && eta2<1.6) return 0.958773;
    else if( eta2>=1.6 && eta2<2.1) return 0.943424;
    else if( eta2>=2.1 && eta2<=2.4) return 0.899825;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.2 && eta1<0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.886891;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.926671;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.939046;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.942404;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.941512;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.952446;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.9288;
    else if( eta2>=-0.2 && eta2<0) return 0.94952;
    else if( eta2>=0 && eta2<0.2) return 0.949828;
    else if( eta2>=0.2 && eta2<0.3) return 0.928436;
    else if( eta2>=0.3 && eta2<0.6) return 0.952103;
    else if( eta2>=0.6 && eta2<0.9) return 0.937564;
    else if( eta2>=0.9 && eta2<1.2) return 0.94185;
    else if( eta2>=1.2 && eta2<1.6) return 0.93718;
    else if( eta2>=1.6 && eta2<2.1) return 0.922175;
    else if( eta2>=2.1 && eta2<=2.4) return 0.879557;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.3 && eta1<0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.9095;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.950294;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.962984;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.966427;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.965513;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.976725;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.952476;
    else if( eta2>=-0.2 && eta2<0) return 0.973725;
    else if( eta2>=0 && eta2<0.2) return 0.974041;
    else if( eta2>=0.2 && eta2<0.3) return 0.952103;
    else if( eta2>=0.3 && eta2<0.6) return 0.976374;
    else if( eta2>=0.6 && eta2<0.9) return 0.961464;
    else if( eta2>=0.9 && eta2<1.2) return 0.965859;
    else if( eta2>=1.2 && eta2<1.6) return 0.96107;
    else if( eta2>=1.6 && eta2<2.1) return 0.945683;
    else if( eta2>=2.1 && eta2<=2.4) return 0.901979;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.6 && eta1<0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.895609;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.935782;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.948279;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.951669;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.950769;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.96181;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.937932;
    else if( eta2>=-0.2 && eta2<0) return 0.958856;
    else if( eta2>=0 && eta2<0.2) return 0.959166;
    else if( eta2>=0.2 && eta2<0.3) return 0.937564;
    else if( eta2>=0.3 && eta2<0.6) return 0.961464;
    else if( eta2>=0.6 && eta2<0.9) return 0.946782;
    else if( eta2>=0.9 && eta2<1.2) return 0.95111;
    else if( eta2>=1.2 && eta2<1.6) return 0.946394;
    else if( eta2>=1.6 && eta2<2.1) return 0.931242;
    else if( eta2>=2.1 && eta2<=2.4) return 0.888203;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.9 && eta1<1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.899687;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.940055;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.952613;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.956019;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.955115;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.966207;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.942219;
    else if( eta2>=-0.2 && eta2<0) return 0.963239;
    else if( eta2>=0 && eta2<0.2) return 0.963551;
    else if( eta2>=0.2 && eta2<0.3) return 0.94185;
    else if( eta2>=0.3 && eta2<0.6) return 0.965859;
    else if( eta2>=0.6 && eta2<0.9) return 0.95111;
    else if( eta2>=0.9 && eta2<1.2) return 0.955457;
    else if( eta2>=1.2 && eta2<1.6) return 0.950719;
    else if( eta2>=1.6 && eta2<2.1) return 0.935493;
    else if( eta2>=2.1 && eta2<=2.4) return 0.892246;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.2 && eta1<1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.895219;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.935392;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.947889;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.951278;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.950379;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.961416;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.937547;
    else if( eta2>=-0.2 && eta2<0) return 0.958463;
    else if( eta2>=0 && eta2<0.2) return 0.958773;
    else if( eta2>=0.2 && eta2<0.3) return 0.93718;
    else if( eta2>=0.3 && eta2<0.6) return 0.96107;
    else if( eta2>=0.6 && eta2<0.9) return 0.946394;
    else if( eta2>=0.9 && eta2<1.2) return 0.950719;
    else if( eta2>=1.2 && eta2<1.6) return 0.946005;
    else if( eta2>=1.6 && eta2<2.1) return 0.930853;
    else if( eta2>=2.1 && eta2<=2.4) return 0.887816;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.6 && eta1<2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.880775;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.920386;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.932707;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.936045;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.935163;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.946024;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.922537;
    else if( eta2>=-0.2 && eta2<0) return 0.943118;
    else if( eta2>=0 && eta2<0.2) return 0.943424;
    else if( eta2>=0.2 && eta2<0.3) return 0.922175;
    else if( eta2>=0.3 && eta2<0.6) return 0.945683;
    else if( eta2>=0.6 && eta2<0.9) return 0.931242;
    else if( eta2>=0.9 && eta2<1.2) return 0.935493;
    else if( eta2>=1.2 && eta2<1.6) return 0.930853;
    else if( eta2>=1.6 && eta2<2.1) return 0.915916;
    else if( eta2>=2.1 && eta2<=2.4) return 0.87349;
    else return 0.;
    return 0.;
  }
  else if( eta1>=2.1 && eta1<=2.4) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.839747;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.877763;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.889585;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.892774;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.891944;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.902305;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.879902;
    else if( eta2>=-0.2 && eta2<0) return 0.899534;
    else if( eta2>=0 && eta2<0.2) return 0.899825;
    else if( eta2>=0.2 && eta2<0.3) return 0.879557;
    else if( eta2>=0.3 && eta2<0.6) return 0.901979;
    else if( eta2>=0.6 && eta2<0.9) return 0.888203;
    else if( eta2>=0.9 && eta2<1.2) return 0.892246;
    else if( eta2>=1.2 && eta2<1.6) return 0.887816;
    else if( eta2>=1.6 && eta2<2.1) return 0.87349;
    else if( eta2>=2.1 && eta2<=2.4) return 0.832798;
    else return 0.;
    return 0.;
  }
  else return 0.;
  return 0.;
}

Double_t Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(Double_t eta1, Double_t eta2) {
  if( eta1>=-2.4 && eta1<-2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.807536;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.885011;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.888759;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.89163;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.892141;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.891464;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.874339;
    else if( eta2>=-0.2 && eta2<0) return 0.892135;
    else if( eta2>=0 && eta2<0.2) return 0.893432;
    else if( eta2>=0.2 && eta2<0.3) return 0.882935;
    else if( eta2>=0.3 && eta2<0.6) return 0.889012;
    else if( eta2>=0.6 && eta2<0.9) return 0.896789;
    else if( eta2>=0.9 && eta2<1.2) return 0.88964;
    else if( eta2>=1.2 && eta2<1.6) return 0.888047;
    else if( eta2>=1.6 && eta2<2.1) return 0.894041;
    else if( eta2>=2.1 && eta2<=2.4) return 0.883607;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-2.1 && eta1<-1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.885011;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.969858;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.97395;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.977092;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.977649;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.976897;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.958137;
    else if( eta2>=-0.2 && eta2<0) return 0.977639;
    else if( eta2>=0 && eta2<0.2) return 0.979052;
    else if( eta2>=0.2 && eta2<0.3) return 0.967551;
    else if( eta2>=0.3 && eta2<0.6) return 0.974207;
    else if( eta2>=0.6 && eta2<0.9) return 0.982741;
    else if( eta2>=0.9 && eta2<1.2) return 0.974908;
    else if( eta2>=1.2 && eta2<1.6) return 0.97318;
    else if( eta2>=1.6 && eta2<2.1) return 0.979757;
    else if( eta2>=2.1 && eta2<=2.4) return 0.968346;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.6 && eta1<-1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.888759;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.97395;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.978055;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.981209;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.981768;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98101;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.962172;
    else if( eta2>=-0.2 && eta2<0) return 0.981756;
    else if( eta2>=0 && eta2<0.2) return 0.983173;
    else if( eta2>=0.2 && eta2<0.3) return 0.971625;
    else if( eta2>=0.3 && eta2<0.6) return 0.978308;
    else if( eta2>=0.6 && eta2<0.9) return 0.98688;
    else if( eta2>=0.9 && eta2<1.2) return 0.979015;
    else if( eta2>=1.2 && eta2<1.6) return 0.977285;
    else if( eta2>=1.6 && eta2<2.1) return 0.983892;
    else if( eta2>=2.1 && eta2<=2.4) return 0.972436;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-1.2 && eta1<-0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.89163;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.977092;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.981209;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.984373;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.984933;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.984173;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.965274;
    else if( eta2>=-0.2 && eta2<0) return 0.984921;
    else if( eta2>=0 && eta2<0.2) return 0.986343;
    else if( eta2>=0.2 && eta2<0.3) return 0.974758;
    else if( eta2>=0.3 && eta2<0.6) return 0.981462;
    else if( eta2>=0.6 && eta2<0.9) return 0.990062;
    else if( eta2>=0.9 && eta2<1.2) return 0.982172;
    else if( eta2>=1.2 && eta2<1.6) return 0.980437;
    else if( eta2>=1.6 && eta2<2.1) return 0.987066;
    else if( eta2>=2.1 && eta2<=2.4) return 0.975577;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.9 && eta1<-0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.892141;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.977649;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.981768;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.984933;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.985494;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.984732;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.965824;
    else if( eta2>=-0.2 && eta2<0) return 0.985482;
    else if( eta2>=0 && eta2<0.2) return 0.986904;
    else if( eta2>=0.2 && eta2<0.3) return 0.975312;
    else if( eta2>=0.3 && eta2<0.6) return 0.98202;
    else if( eta2>=0.6 && eta2<0.9) return 0.990626;
    else if( eta2>=0.9 && eta2<1.2) return 0.982731;
    else if( eta2>=1.2 && eta2<1.6) return 0.980996;
    else if( eta2>=1.6 && eta2<2.1) return 0.987629;
    else if( eta2>=2.1 && eta2<=2.4) return 0.976134;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.6 && eta1<-0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.891464;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.976897;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.98101;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.984173;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.984732;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.983971;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.965077;
    else if( eta2>=-0.2 && eta2<0) return 0.98472;
    else if( eta2>=0 && eta2<0.2) return 0.986141;
    else if( eta2>=0.2 && eta2<0.3) return 0.974558;
    else if( eta2>=0.3 && eta2<0.6) return 0.98126;
    else if( eta2>=0.6 && eta2<0.9) return 0.98986;
    else if( eta2>=0.9 && eta2<1.2) return 0.981972;
    else if( eta2>=1.2 && eta2<1.6) return 0.980239;
    else if( eta2>=1.6 && eta2<2.1) return 0.98687;
    else if( eta2>=2.1 && eta2<=2.4) return 0.975393;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.3 && eta1<-0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.874339;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.958137;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.962172;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.965274;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.965824;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.965077;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.946546;
    else if( eta2>=-0.2 && eta2<0) return 0.965812;
    else if( eta2>=0 && eta2<0.2) return 0.967205;
    else if( eta2>=0.2 && eta2<0.3) return 0.955845;
    else if( eta2>=0.3 && eta2<0.6) return 0.962418;
    else if( eta2>=0.6 && eta2<0.9) return 0.970853;
    else if( eta2>=0.9 && eta2<1.2) return 0.963116;
    else if( eta2>=1.2 && eta2<1.6) return 0.961416;
    else if( eta2>=1.6 && eta2<2.1) return 0.967918;
    else if( eta2>=2.1 && eta2<=2.4) return 0.956656;
    else return 0.;
    return 0.;
  }
  else if( eta1>=-0.2 && eta1<0) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.892135;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.977639;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.981756;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.984921;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.985482;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98472;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.965812;
    else if( eta2>=-0.2 && eta2<0) return 0.98547;
    else if( eta2>=0 && eta2<0.2) return 0.986892;
    else if( eta2>=0.2 && eta2<0.3) return 0.9753;
    else if( eta2>=0.3 && eta2<0.6) return 0.982007;
    else if( eta2>=0.6 && eta2<0.9) return 0.990614;
    else if( eta2>=0.9 && eta2<1.2) return 0.982719;
    else if( eta2>=1.2 && eta2<1.6) return 0.980984;
    else if( eta2>=1.6 && eta2<2.1) return 0.987619;
    else if( eta2>=2.1 && eta2<=2.4) return 0.976128;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0 && eta1<0.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.893432;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.979052;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.983173;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.986343;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.986904;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.986141;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.967205;
    else if( eta2>=-0.2 && eta2<0) return 0.986892;
    else if( eta2>=0 && eta2<0.2) return 0.988315;
    else if( eta2>=0.2 && eta2<0.3) return 0.976707;
    else if( eta2>=0.3 && eta2<0.6) return 0.983424;
    else if( eta2>=0.6 && eta2<0.9) return 0.992043;
    else if( eta2>=0.9 && eta2<1.2) return 0.984137;
    else if( eta2>=1.2 && eta2<1.6) return 0.982401;
    else if( eta2>=1.6 && eta2<2.1) return 0.989047;
    else if( eta2>=2.1 && eta2<=2.4) return 0.977545;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.2 && eta1<0.3) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.882935;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.967551;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.971625;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.974758;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.975312;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.974558;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.955845;
    else if( eta2>=-0.2 && eta2<0) return 0.9753;
    else if( eta2>=0 && eta2<0.2) return 0.976707;
    else if( eta2>=0.2 && eta2<0.3) return 0.965235;
    else if( eta2>=0.3 && eta2<0.6) return 0.971873;
    else if( eta2>=0.6 && eta2<0.9) return 0.980391;
    else if( eta2>=0.9 && eta2<1.2) return 0.972578;
    else if( eta2>=1.2 && eta2<1.6) return 0.970862;
    else if( eta2>=1.6 && eta2<2.1) return 0.977429;
    else if( eta2>=2.1 && eta2<=2.4) return 0.966061;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.3 && eta1<0.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.889012;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.974207;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.978308;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.981462;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.98202;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98126;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.962418;
    else if( eta2>=-0.2 && eta2<0) return 0.982007;
    else if( eta2>=0 && eta2<0.2) return 0.983424;
    else if( eta2>=0.2 && eta2<0.3) return 0.971873;
    else if( eta2>=0.3 && eta2<0.6) return 0.978557;
    else if( eta2>=0.6 && eta2<0.9) return 0.987134;
    else if( eta2>=0.9 && eta2<1.2) return 0.979267;
    else if( eta2>=1.2 && eta2<1.6) return 0.977539;
    else if( eta2>=1.6 && eta2<2.1) return 0.984153;
    else if( eta2>=2.1 && eta2<=2.4) return 0.97271;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.6 && eta1<0.9) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.896789;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.982741;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.98688;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.990062;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.990626;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98986;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.970853;
    else if( eta2>=-0.2 && eta2<0) return 0.990614;
    else if( eta2>=0 && eta2<0.2) return 0.992043;
    else if( eta2>=0.2 && eta2<0.3) return 0.980391;
    else if( eta2>=0.3 && eta2<0.6) return 0.987134;
    else if( eta2>=0.6 && eta2<0.9) return 0.995785;
    else if( eta2>=0.9 && eta2<1.2) return 0.987849;
    else if( eta2>=1.2 && eta2<1.6) return 0.986105;
    else if( eta2>=1.6 && eta2<2.1) return 0.992773;
    else if( eta2>=2.1 && eta2<=2.4) return 0.98122;
    else return 0.;
    return 0.;
  }
  else if( eta1>=0.9 && eta1<1.2) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.88964;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.974908;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.979015;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.982172;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.982731;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.981972;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.963116;
    else if( eta2>=-0.2 && eta2<0) return 0.982719;
    else if( eta2>=0 && eta2<0.2) return 0.984137;
    else if( eta2>=0.2 && eta2<0.3) return 0.972578;
    else if( eta2>=0.3 && eta2<0.6) return 0.979267;
    else if( eta2>=0.6 && eta2<0.9) return 0.987849;
    else if( eta2>=0.9 && eta2<1.2) return 0.979976;
    else if( eta2>=1.2 && eta2<1.6) return 0.978245;
    else if( eta2>=1.6 && eta2<2.1) return 0.98486;
    else if( eta2>=2.1 && eta2<=2.4) return 0.973399;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.2 && eta1<1.6) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.888047;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.97318;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.977285;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.980437;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.980996;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.980239;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.961416;
    else if( eta2>=-0.2 && eta2<0) return 0.980984;
    else if( eta2>=0 && eta2<0.2) return 0.982401;
    else if( eta2>=0.2 && eta2<0.3) return 0.970862;
    else if( eta2>=0.3 && eta2<0.6) return 0.977539;
    else if( eta2>=0.6 && eta2<0.9) return 0.986105;
    else if( eta2>=0.9 && eta2<1.2) return 0.978245;
    else if( eta2>=1.2 && eta2<1.6) return 0.976515;
    else if( eta2>=1.6 && eta2<2.1) return 0.983114;
    else if( eta2>=2.1 && eta2<=2.4) return 0.971658;
    else return 0.;
    return 0.;
  }
  else if( eta1>=1.6 && eta1<2.1) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.894041;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.979757;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.983892;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.987066;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.987629;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.98687;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.967918;
    else if( eta2>=-0.2 && eta2<0) return 0.987619;
    else if( eta2>=0 && eta2<0.2) return 0.989047;
    else if( eta2>=0.2 && eta2<0.3) return 0.977429;
    else if( eta2>=0.3 && eta2<0.6) return 0.984153;
    else if( eta2>=0.6 && eta2<0.9) return 0.992773;
    else if( eta2>=0.9 && eta2<1.2) return 0.98486;
    else if( eta2>=1.2 && eta2<1.6) return 0.983114;
    else if( eta2>=1.6 && eta2<2.1) return 0.989757;
    else if( eta2>=2.1 && eta2<=2.4) return 0.978227;
    else return 0.;
    return 0.;
  }
  else if( eta1>=2.1 && eta1<=2.4) { 
    if( eta2>=-2.4 && eta2<-2.1) return 0.883607;
    else if( eta2>=-2.1 && eta2<-1.6) return 0.968346;
    else if( eta2>=-1.6 && eta2<-1.2) return 0.972436;
    else if( eta2>=-1.2 && eta2<-0.9) return 0.975577;
    else if( eta2>=-0.9 && eta2<-0.6) return 0.976134;
    else if( eta2>=-0.6 && eta2<-0.3) return 0.975393;
    else if( eta2>=-0.3 && eta2<-0.2) return 0.956656;
    else if( eta2>=-0.2 && eta2<0) return 0.976128;
    else if( eta2>=0 && eta2<0.2) return 0.977545;
    else if( eta2>=0.2 && eta2<0.3) return 0.966061;
    else if( eta2>=0.3 && eta2<0.6) return 0.97271;
    else if( eta2>=0.6 && eta2<0.9) return 0.98122;
    else if( eta2>=0.9 && eta2<1.2) return 0.973399;
    else if( eta2>=1.2 && eta2<1.6) return 0.971658;
    else if( eta2>=1.6 && eta2<2.1) return 0.978227;
    else if( eta2>=2.1 && eta2<=2.4) return 0.966841;
    else return 0.;
    return 0.;
  }
  else return 0.;
  return 0.;
}
 
double getEfficiencyMuonPOG(bool is2011A , bool isMC,double muopt1 ,double muoeta1, double muopt2,double muoeta2, bool scaleUp, bool scaleDown){
  double muoIDrunA[15]={0.9111, 0.9429, 0.9661, 0.9398, 0.9639, 0.9789, 0.8731, 0.9665, 0.8643, 0.9777, 0.9616, 0.9334, 0.9614, 0.9499, 0.9164};

  double muoIDrunA_error[15]={0.0018677027196907943,0.0009620931827499634,0.00083857378852558284,0.001064086117175767,0.00084960826027844622,0.00070793456706362491,0.0021350787883431051,0.0006880431780112861,0.0021884902478001575,0.00071060369069667257,0.00086291256476993575,0.0010868097948907689,0.00085834394005120584,0.00090252496527338329,0.0017812948328828611};

  double muoISOrunA[2][7]={{0.8358, 0.9282, 0.9721, 0.9909, 0.9930, 0.9959, 0.9950},
			   {0.8418, 0.9433, 0.9777, 0.9930, 0.9957, 0.9957, 0.9943}};

  double muoISOrunA_error[2][7]={{0.0039474094806490065,0.001075456204282168,0.00039876977976236936,0.00019914259741383943,0.0004249745512238779,0.00010796563511328294,0.0013400178437347253},
				 {0.0031022389109825596,0.0010593413884468327,0.00046136170880504827,0.00023160057797250166,0.00051340946120276287,1.8555655801777426e-05,0.0016183498431985648}};

  double muoIDrunB[15]={0.8915, 0.8982, 0.9255, 0.9235, 0.9626, 0.9788, 0.8701, 0.9640, 0.8601, 0.9772, 0.9578, 0.9154, 0.9252, 0.9097, 0.8926};

  double muoIDrunB_error[15]={0.0023452318125499849,0.0013102277566272844,0.0012468537277680195,0.0013040826255456307,0.001003071935598625,0.00084295917828939801,0.0023692027038618299,0.00081021307806378412,0.0024134454940258161,0.00085434146767891577,0.0010263216958359351,0.001345657131895551,0.0012230984447312127,0.001249972630612856,0.0022593416652316031};

  double muoISOrunB[2][7]={{0.7800, 0.9052, 0.9614, 0.9860, 0.9923, 0.9922, 0.9985},
			   {0.7881, 0.9179, 0.9777, 0.9881, 0.9951, 0.9954, 0.9960}};

  double muoISOrunB_error[2][7]={{0.0046225252834390402,0.0012932809273530647,0.00048475082046020427,5.0767885528824053e-07,0.0076788646699996743,2.0666295936166978e-05,0.0010385424753719228},
				 {0.0037079192250058968,0.0012554244663553285,0.00056986289985867084,0.00063743014988659752,0.00057299117464869906,0.00077878078746219037,0.0017664950871402185}};

  double muoIDrunA_MC[15]={0.9208, 0.9559, 0.9767, 0.9498, 0.9663, 0.9791, 0.8916, 0.9698, 0.8743, 0.9766, 0.9634, 0.9323, 0.9634, 0.9472, 0.9148};

  double muoIDrunA_MC_error[15]={0.001403773609217494,0.00067865856839786562,0.00051500065749497041,0.00079729299933557448,0.00063793121371789722,0.00049457514274073701,0.0017656466502473853,0.00049853392069020778,0.0017903541955377844,0.00051562728435320759,0.00066482378173012241,0.00092411269979289208,0.00064535359937876969,0.00074733889964153006,0.0014302092667733909};

  double muoISOrunA_MC[2][7]={{0.8503, 0.9361, 0.9742, 0.9926, 0.9964, 0.9974, 0.9968},
			      {0.8535, 0.9413, 0.9771, 0.9913, 0.9970, 0.9986, 0.9999}};

  double muoISOrunA_MC_error[2][7]={{0.0038160895307147238,0.0010130358017453134,0.00037957755459896531,0.007390878600653128,0.00034782737290117716,3.277510919663662e-06,6.4904553396472053e-05},
				    {0.0028814921305030153,0.00097540361768596174,0.00044548029714037637,0.00060110417761066737,2.9477582297321447e-07,0.00064497591734868909,3.1704110564634291e-07}};

  double muoIDrunB_MC[15]={0.9214, 0.9549, 0.9756, 0.9497, 0.9656, 0.9791, 0.8895, 0.9684, 0.8730, 0.9760, 0.9633, 0.9288, 0.9613, 0.9470, 0.9159};

  double muoIDrunB_MC_error[15]={0.0014827110679831986,0.00071536381767677102,0.00055747731990146634,0.00082799276894812105,0.00066694701228632179,0.00051051923611558289,0.0017793695685200494,0.00052539318953027968,0.0020048521395556831,0.00054957918060885872,0.00068448924192564872,0.00097717059021705565,0.00068959128310875685,0.00077306797408858855,0.0015088460751774145};

  double muoISOrunB_MC[2][7]={{0.8030, 0.9139, 0.9667, 0.9889, 0.9952, 0.9977, 0.9952},
			      {0.7886, 0.9134, 0.9653, 0.9876, 0.9940, 0.9967, 0.9999}};

  double muoISOrunB_MC_error[2][7]={{0.0042340415917311849,0.0011650543957748766,0.00043354912899483725,0.00021135996854737549,0.0003809771716774546,0.00054262073306587943,0.00011091679750635519},
				    {0.0034048873725449182,0.0011704169332830479,0.00054107745793138113,4.6756468242981075e-05,0.00056037685041165908,0.0032814997898342746,4.3861087511976038e-07}};

  int muoId1=-1; int muoIso1=-1;
  int muoId2=-1; int muoIso2=-1;
  int highEta1=0; int highEta2=0;
  double efficiencyMuonPOG;
  double efficiencyHLTmu;
  if (muoeta1>1.2) highEta1=1;
  if (muoeta2>1.2) highEta2=1;
  if (muoeta1>=-2.4 && muoeta1<-2.1) muoId1=0;
  if (muoeta1>=-2.1 && muoeta1<-1.6) muoId1=1;
  if (muoeta1>=-1.6 && muoeta1<-1.2) muoId1=2;
  if (muoeta1>=-1.2 && muoeta1<-0.9) muoId1=3;
  if (muoeta1>=-0.9 && muoeta1<-0.6) muoId1=4;
  if (muoeta1>=-0.6 && muoeta1<-0.3) muoId1=5;
  if (muoeta1>=-0.3 && muoeta1<-0.2) muoId1=6;
  if (muoeta1>=-0.2 &&  muoeta1<0.2) muoId1=7;
  if (muoeta1>=0.2  &&  muoeta1<0.3) muoId1=8;
  if (muoeta1>=0.3  &&  muoeta1<0.6) muoId1=9;
  if (muoeta1>=0.6  &&  muoeta1<0.9) muoId1=10;
  if (muoeta1>=0.9  &&  muoeta1<1.2) muoId1=11;
  if (muoeta1>=1.2  &&  muoeta1<1.6) muoId1=12;
  if (muoeta1>=1.6  &&  muoeta1<2.1) muoId1=13;
  if (muoeta1>=2.1  &&  muoeta1<2.4) muoId1=14;
  if (muopt1>=10 && muopt1<20) muoIso1=0;
  if (muopt1>=20 && muopt1<30) muoIso1=1;
  if (muopt1>=30 && muopt1<40) muoIso1=2;
  if (muopt1>=40 && muopt1<50) muoIso1=3;
  if (muopt1>=50 && muopt1<60) muoIso1=4;
  if (muopt1>=60 && muopt1<80) muoIso1=5;
  if (muopt1>=80             ) muoIso1=6;
  if (muoeta2>=-2.4 && muoeta2<-2.1) muoId2=0;
  if (muoeta2>=-2.1 && muoeta2<-1.6) muoId2=1;
  if (muoeta2>=-1.6 && muoeta2<-1.2) muoId2=2;
  if (muoeta2>=-1.2 && muoeta2<-0.9) muoId2=3;
  if (muoeta2>=-0.9 && muoeta2<-0.6) muoId2=4;
  if (muoeta2>=-0.6 && muoeta2<-0.3) muoId2=5;
  if (muoeta2>=-0.3 && muoeta2<-0.2) muoId2=6;
  if (muoeta2>=-0.2 &&  muoeta2<0.2) muoId2=7;
  if (muoeta2>=0.2  &&  muoeta2<0.3) muoId2=8;
  if (muoeta2>=0.3  &&  muoeta2<0.6) muoId2=9;
  if (muoeta2>=0.6  &&  muoeta2<0.9) muoId2=10;
  if (muoeta2>=0.9  &&  muoeta2<1.2) muoId2=11;
  if (muoeta2>=1.2  &&  muoeta2<1.6) muoId2=12;
  if (muoeta2>=1.6  &&  muoeta2<2.1) muoId2=13;
  if (muoeta2>=2.1  &&  muoeta2<2.4) muoId2=14;
  if (muopt2>=10 && muopt2<20) muoIso2=0;
  if (muopt2>=20 && muopt2<30) muoIso2=1;
  if (muopt2>=30 && muopt2<40) muoIso2=2;
  if (muopt2>=40 && muopt2<50) muoIso2=3;
  if (muopt2>=50 && muopt2<60) muoIso2=4;
  if (muopt2>=60 && muopt2<80) muoIso2=5;
  if (muopt2>=80             ) muoIso2=6;
  if (muoId1==-1 || muoIso1==-1 || muoId2==-1 || muoIso2==-1) return 1.0;
  if (!isMC) {
    efficiencyHLTmu = Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_DATA(muoeta1,muoeta2);
    if (scaleUp) efficiencyHLTmu = efficiencyHLTmu*1.0004;
    if (scaleDown) efficiencyHLTmu = efficiencyHLTmu*0.9996;
  } else {
    efficiencyHLTmu = Eff_HLT_Mu17_Mu8_2011_TPfit_RunAB_EtaEta_MC(muoeta1,muoeta2);
    if (scaleUp) efficiencyHLTmu = efficiencyHLTmu*1.0004;
    if (scaleDown) efficiencyHLTmu = efficiencyHLTmu*0.9996;
  }
  if (!isMC) {
    if (is2011A) {
      efficiencyMuonPOG = muoIDrunA[muoId1] * muoISOrunA[highEta1][muoIso1] * muoIDrunA[muoId2] * muoISOrunA[highEta2][muoIso2];
      if (scaleUp) efficiencyMuonPOG = (muoIDrunA[muoId1]+muoIDrunA_error[muoId1]) * (muoISOrunA[highEta1][muoIso1]+muoISOrunA_error[highEta1][muoIso1]) * (muoIDrunA[muoId2]+muoIDrunA_error[muoId2]) * (muoISOrunA[highEta2][muoIso2]+muoISOrunA_error[highEta2][muoIso2]);
      if (scaleDown) efficiencyMuonPOG = (muoIDrunA[muoId1]-muoIDrunA_error[muoId1]) * (muoISOrunA[highEta1][muoIso1]-muoISOrunA_error[highEta1][muoIso1]) * (muoIDrunA[muoId2]-muoIDrunA_error[muoId2]) * (muoISOrunA[highEta2][muoIso2]-muoISOrunA_error[highEta2][muoIso2]);
    } else {
      efficiencyMuonPOG = muoIDrunB[muoId1] * muoISOrunB[highEta1][muoIso1] * muoIDrunB[muoId2] * muoISOrunB[highEta2][muoIso2];
      if (scaleUp) efficiencyMuonPOG = (muoIDrunB[muoId1]+muoIDrunB_error[muoId1]) * (muoISOrunB[highEta1][muoIso1]+muoISOrunB_error[highEta1][muoIso1]) * (muoIDrunB[muoId2]+muoIDrunB_error[muoId2]) * (muoISOrunB[highEta2][muoIso2]+muoISOrunB_error[highEta2][muoIso2]);
      if (scaleDown) efficiencyMuonPOG = (muoIDrunB[muoId1]-muoIDrunB_error[muoId1]) * (muoISOrunB[highEta1][muoIso1]-muoISOrunB_error[highEta1][muoIso1]) * (muoIDrunB[muoId2]-muoIDrunB_error[muoId2]) * (muoISOrunB[highEta2][muoIso2]-muoISOrunB_error[highEta2][muoIso2]);
    }
  } else {
    if (is2011A) {
      efficiencyMuonPOG = muoIDrunA_MC[muoId1] * muoISOrunA_MC[highEta1][muoIso1] * muoIDrunA_MC[muoId2] * muoISOrunA_MC[highEta2][muoIso2];
      if (scaleUp) efficiencyMuonPOG = (muoIDrunA_MC[muoId1]+muoIDrunA_MC_error[muoId1]) * (muoISOrunA_MC[highEta1][muoIso1]+muoISOrunA_MC_error[highEta1][muoIso1]) * (muoIDrunA_MC[muoId2]+muoIDrunA_MC_error[muoId2]) * (muoISOrunA_MC[highEta2][muoIso2]+muoISOrunA_MC_error[highEta2][muoIso2]);
      if (scaleDown) efficiencyMuonPOG = (muoIDrunA_MC[muoId1]-muoIDrunA_MC_error[muoId1]) * (muoISOrunA_MC[highEta1][muoIso1]-muoISOrunA_MC_error[highEta1][muoIso1]) * (muoIDrunA_MC[muoId2]-muoIDrunA_MC_error[muoId2]) * (muoISOrunA_MC[highEta2][muoIso2]-muoISOrunA_MC_error[highEta2][muoIso2]);
    } else {
      efficiencyMuonPOG = muoIDrunB_MC[muoId1] * muoISOrunB_MC[highEta1][muoIso1] * muoIDrunB_MC[muoId2] * muoISOrunB_MC[highEta2][muoIso2];
      if (scaleUp) efficiencyMuonPOG = (muoIDrunB_MC[muoId1]+muoIDrunB_MC_error[muoId1]) * (muoISOrunB_MC[highEta1][muoIso1]+muoISOrunB_MC_error[highEta1][muoIso1]) * (muoIDrunB_MC[muoId2]+muoIDrunB_MC_error[muoId2]) * (muoISOrunB_MC[highEta2][muoIso2]+muoISOrunB_MC_error[highEta2][muoIso2]);
      if (scaleDown) efficiencyMuonPOG = (muoIDrunB_MC[muoId1]-muoIDrunB_MC_error[muoId1]) * (muoISOrunB_MC[highEta1][muoIso1]-muoISOrunB_MC_error[highEta1][muoIso1]) * (muoIDrunB_MC[muoId2]-muoIDrunB_MC_error[muoId2]) * (muoISOrunB_MC[highEta2][muoIso2]-muoISOrunB_MC_error[highEta2][muoIso2]);
    }
  }
  return efficiencyMuonPOG*efficiencyHLTmu;
}

double getSfMuonPOG(bool is2011A,double muopt1,double muoeta1,double muopt2,double muoeta2){
  double muoIDrunA[15]={0.98944468260411311,0.98638928744572119,0.98921369419005389,0.98953056317335875,0.99752115874592484,0.99984454286866753,0.97919789200893859,0.99650005782256434,0.98857962577941372,1.0011652331934688,0.99808684018259897,1.0011534388712648,0.99791508918425875,1.0027951812574147,1.0017222271148787};

  double muoISOrunA[2][7]={{0.98294832702660029,0.99153016820013107,0.9978251309255376,0.99822975449496276,0.9966142636270876,0.99851288044807918,0.99818953812285482},
			   {0.98624704284147213,1.002053957635664,1.0005697922317094,1.0017473109726096,0.99874727165665256,0.99712814059206767,0.99433855146797345}};

  double muoIDrunB[15]={0.9675425686027912,0.94063118735412588,0.94911505235668192,0.97236031644744203,0.99691429303027845,0.9996592756991195,0.97813138704431146,0.99544449653092759,0.98517517807162758,1.0012385520890255,0.99428744628850396,0.9855480284055832,0.96239802584510592,0.96054611620996821,0.97458486800299127};

  double muoISOrunB[2][7]={{0.97137078088748319,0.99049297337420161,0.99450321137600328,0.99699375666729895,0.99713206139681287,0.99447867709699855,1.0032848320319512},
			   {0.99934266307723185,1.0049252265431443,1.0013438827920791,1.0005512822595006,1.0010648294284554,0.99868520463760224,0.99602676239916244}};

  int muoId1=-1; int muoIso1=-1;
  int muoId2=-1; int muoIso2=-1;
  int highEta1=0; int highEta2=0;
  double sfMuonPOG=1.0;
  double sfHLTmu=1.0;
  if (muoeta1>1.2) highEta1=1;
  if (muoeta2>1.2) highEta2=1;
  if (muoeta1>=-2.4 && muoeta1<-2.1) muoId1=0;
  if (muoeta1>=-2.1 && muoeta1<-1.6) muoId1=1;
  if (muoeta1>=-1.6 && muoeta1<-1.2) muoId1=2;
  if (muoeta1>=-1.2 && muoeta1<-0.9) muoId1=3;
  if (muoeta1>=-0.9 && muoeta1<-0.6) muoId1=4;
  if (muoeta1>=-0.6 && muoeta1<-0.3) muoId1=5;
  if (muoeta1>=-0.3 && muoeta1<-0.2) muoId1=6;
  if (muoeta1>=-0.2 &&  muoeta1<0.2) muoId1=7;
  if (muoeta1>=0.2  &&  muoeta1<0.3) muoId1=8;
  if (muoeta1>=0.3  &&  muoeta1<0.6) muoId1=9;
  if (muoeta1>=0.6  &&  muoeta1<0.9) muoId1=10;
  if (muoeta1>=0.9  &&  muoeta1<1.2) muoId1=11;
  if (muoeta1>=1.2  &&  muoeta1<1.6) muoId1=12;
  if (muoeta1>=1.6  &&  muoeta1<2.1) muoId1=13;
  if (muoeta1>=2.1  &&  muoeta1<2.4) muoId1=14;
  if (muopt1>=10 && muopt1<20) muoIso1=0;
  if (muopt1>=20 && muopt1<30) muoIso1=1;
  if (muopt1>=30 && muopt1<40) muoIso1=2;
  if (muopt1>=40 && muopt1<50) muoIso1=3;
  if (muopt1>=50 && muopt1<60) muoIso1=4;
  if (muopt1>=60 && muopt1<80) muoIso1=5;
  if (muopt1>=80             ) muoIso1=6;
  if (muoeta2>=-2.4 && muoeta2<-2.1) muoId2=0;
  if (muoeta2>=-2.1 && muoeta2<-1.6) muoId2=1;
  if (muoeta2>=-1.6 && muoeta2<-1.2) muoId2=2;
  if (muoeta2>=-1.2 && muoeta2<-0.9) muoId2=3;
  if (muoeta2>=-0.9 && muoeta2<-0.6) muoId2=4;
  if (muoeta2>=-0.6 && muoeta2<-0.3) muoId2=5;
  if (muoeta2>=-0.3 && muoeta2<-0.2) muoId2=6;
  if (muoeta2>=-0.2 &&  muoeta2<0.2) muoId2=7;
  if (muoeta2>=0.2  &&  muoeta2<0.3) muoId2=8;
  if (muoeta2>=0.3  &&  muoeta2<0.6) muoId2=9;
  if (muoeta2>=0.6  &&  muoeta2<0.9) muoId2=10;
  if (muoeta2>=0.9  &&  muoeta2<1.2) muoId2=11;
  if (muoeta2>=1.2  &&  muoeta2<1.6) muoId2=12;
  if (muoeta2>=1.6  &&  muoeta2<2.1) muoId2=13;
  if (muoeta2>=2.1  &&  muoeta2<2.4) muoId2=14;
  if (muopt2>=10 && muopt2<20) muoIso2=0;
  if (muopt2>=20 && muopt2<30) muoIso2=1;
  if (muopt2>=30 && muopt2<40) muoIso2=2;
  if (muopt2>=40 && muopt2<50) muoIso2=3;
  if (muopt2>=50 && muopt2<60) muoIso2=4;
  if (muopt2>=60 && muopt2<80) muoIso2=5;
  if (muopt2>=80             ) muoIso2=6;
  if (muoId1==-1 || muoIso1==-1 || muoId2==-1 || muoIso2==-1) return 1.0;
  sfHLTmu = Eff_HLT_Mu13_Mu8_2011_TPfit_RunAB_EtaEta_DATAoverMC(muoeta1,muoeta2);
  if (is2011A) {
    sfMuonPOG = muoIDrunA[muoId1] * muoISOrunA[highEta1][muoIso1] * muoIDrunA[muoId2] * muoISOrunA[highEta2][muoIso2];
  } else {
    sfMuonPOG = muoIDrunB[muoId1] * muoISOrunB[highEta1][muoIso1] * muoIDrunB[muoId2] * muoISOrunB[highEta2][muoIso2];
  }
  return sfMuonPOG*sfHLTmu;
}

double getSfEGammaPOG(double elept1 ,double eleeta1, double elept2,double eleeta2, bool scaleUp, bool scaleDown){
  double sf_ele=1.0;
  double matrixIDISO[6][5]={
    {1.028,1.084,1.805,1.213,1.022},
    {0.999,0.947,1.041,1.064,1.085},
    {0.990,0.973,0.946,0.996,1.020},
    {0.990,0.982,0.974,0.992,1.006},
    {0.993,0.992,0.980,0.999,1.010},
    {0.990,0.988,0.996,1.000,1.008},
  };
  double matrixIDISO_errorUP[6][5]={
    {0.069,0.095,0.716,0.117,0.074},
    {0.014,0.017,0.065,0.025,0.031},
    {0.003,0.001,0.010,0.002,0.006},
    {0.001,0.001,0.002,0.001,0.001},
    {0.000,0.000,0.004,0.001,0.002},
    {0.001,0.002,0.003,0.001,0.002},
  };
  double matrixIDISO_errorDOWN[6][5]={
    {0.075,0.111,0.914,0.132,0.079},
    {0.014,0.018,0.069,0.026,0.031},
    {0.003,0.001,0.012,0.006,0.006},
    {0.001,0.001,0.002,0.002,0.002},
    {0.000,0.000,0.004,0.001,0.002},
    {0.001,0.002,0.003,0.001,0.002},
  };

  int id1y=-1; int iso1y=-1;
  int id2y=-1; int iso2y=-1;
  if (fabs(eleeta1)<=0.8) {
    id1y  =0;
  } else if (fabs(eleeta1)>0.8 && fabs(eleeta1)<=1.4442) {   
    id1y  =1;
  } else if (fabs(eleeta1)>1.4442 && fabs(eleeta1)<=1.566) {
    id1y  =2;
  } else if (fabs(eleeta1)>1.566 && fabs(eleeta1)<=2.0) {
    id1y  =3;
  } else if (fabs(eleeta1)>2.0 && fabs(eleeta1)<=2.5) {
    id1y =4;
  }
  if (elept1<=15){
    iso1y=0;
  }  else if (elept1 > 15 && elept1 <=20){
    iso1y=1;
  }  else if (elept1 > 20 && elept1 <=30){
    iso1y=2;
  }  else if (elept1 > 30 && elept1 <=40){
    iso1y=3;
  }  else if (elept1 > 40 && elept1 <=50){
    iso1y=4;
  }  else if (elept1 > 50){
    iso1y=5;
  }  
  if (fabs(eleeta2)<=0.8) {
    id2y  =0;
  } else if (fabs(eleeta2)>0.8 && fabs(eleeta2)<=1.4442) {   
    id2y  =1;
  } else if (fabs(eleeta2)>1.4442 && fabs(eleeta2)<=1.566) {
    id2y  =2;
  } else if (fabs(eleeta2)>1.566 && fabs(eleeta2)<=2.0) {
    id2y  =3;
  } else if (fabs(eleeta2)>2.0 && fabs(eleeta2)<=2.5) {
    id2y =4;
  }
  if (elept2<=15){
    iso2y=0;
  }  else if (elept2 > 15 && elept2 <=20){
    iso2y=1;
  }  else if (elept2 > 20 && elept2 <=30){
    iso2y=2;
  }  else if (elept2 > 30 && elept2 <=40){
    iso2y=3;
  }  else if (elept2 > 40 && elept2 <=50){
    iso2y=4;
  }  else if (elept2 > 50){
    iso2y=5;
  }  
  sf_ele = matrixIDISO[iso1y][id1y] * matrixIDISO[iso2y][id2y];
  if (scaleUp) sf_ele = (matrixIDISO[iso1y][id1y]+matrixIDISO_errorUP[iso1y][id1y]) 
    * (matrixIDISO[iso2y][id2y]+matrixIDISO_errorUP[iso2y][id2y]);
  if (scaleDown) sf_ele = (matrixIDISO[iso1y][id1y]-matrixIDISO_errorDOWN[iso1y][id1y]) 
    * (matrixIDISO[iso2y][id2y]-matrixIDISO_errorDOWN[iso2y][id2y]);
  if (iso1y<0 || id1y<0 || iso1y>5 || id1y>4 || iso2y<0 || id2y<0 || iso2y>5 || id2y>4) return 1.0;
  return sf_ele;
}


double getEfficiencyEGammaPOG(double elept1 ,double eleeta1, double elept2,double eleeta2, bool isMC, bool scaleUp, bool scaleDown){
  double sf_ele=1.0;
  double matrixIDISO[6][5]={
    {0.418,0.502,0.664,0.343,0.363},
    {0.620,0.608,0.485,0.506,0.559},
    {0.775,0.765,0.559,0.688,0.684},
    {0.858,0.858,0.723,0.787,0.749},
    {0.891,0.903,0.834,0.845,0.798},
    {0.896,0.908,0.854,0.863,0.816},
  };
  double matrixIDISO_errorDOWN[6][5]={
    {0.028,0.044,0.263,0.033,0.026},
    {0.008,0.011,0.030,0.012,0.016},
    {0.003,0.000,0.005,0.000,0.004},
    {0.001,0.001,0.000,0.000,0.000},
    {0.000,0.000,0.003,0.000,0.001},
    {0.000,0.001,0.000,0.000,0.000},
  };
  double matrixIDISO_errorUP[6][5]={
    {0.030,0.051,0.336,0.037,0.028},
    {0.009,0.011,0.032,0.012,0.016},
    {0.003,0.000,0.007,0.004,0.004},
    {0.001,0.001,0.000,0.001,0.002},
    {0.000,0.000,0.003,0.000,0.001},
    {0.000,0.002,0.000,0.000,0.000},
  };
  double matrixIDISO_MC[6][5]={
    {0.407,0.463,0.368,0.283,0.355},
    {0.621,0.642,0.465,0.476,0.515},
    {0.783,0.786,0.590,0.691,0.671},
    {0.867,0.873,0.742,0.794,0.744},
    {0.897,0.910,0.851,0.846,0.790},
    {0.905,0.919,0.858,0.863,0.809},
  };
  double matrixIDISO_MC_errorUP[6][5]={
    {0.003,0.003,0.008,0.003,0.004},
    {0.002,0.002,0.006,0.003,0.003},
    {0.001,0.001,0.002,0.001,0.001},
    {0.000,0.000,0.002,0.001,0.001},
    {0.000,0.000,0.001,0.001,0.001},
    {0.000,0.001,0.003,0.001,0.001},
  };
  double matrixIDISO_MC_errorDOWN[6][5]={
    {0.003,0.003,0.008,0.003,0.004},
    {0.002,0.002,0.006,0.003,0.003},
    {0.001,0.001,0.002,0.001,0.001},
    {0.000,0.000,0.002,0.001,0.001},
    {0.000,0.000,0.001,0.001,0.001},
    {0.000,0.001,0.003,0.001,0.001},
  };
  int id1y=-1; int iso1y=-1;
  int id2y=-1; int iso2y=-1;
  if (fabs(eleeta1)<=0.8) {
    id1y  =0;
  } else if (fabs(eleeta1)>0.8 && fabs(eleeta1)<=1.4442) {   
    id1y  =1;
  } else if (fabs(eleeta1)>1.4442 && fabs(eleeta1)<=1.566) {
    id1y  =2;
  } else if (fabs(eleeta1)>1.566 && fabs(eleeta1)<=2.0) {
    id1y  =3;
  } else if (fabs(eleeta1)>2.0 && fabs(eleeta1)<=2.5) {
    id1y =4;
  }
  if (elept1<=15){
    iso1y=0;
  }  else if (elept1 > 15 && elept1 <=20){
    iso1y=1;
  }  else if (elept1 > 20 && elept1 <=30){
    iso1y=2;
  }  else if (elept1 > 30 && elept1 <=40){
    iso1y=3;
  }  else if (elept1 > 40 && elept1 <=50){
    iso1y=4;
  }  else if (elept1 > 50){
    iso1y=5;
  }  
  if (fabs(eleeta2)<=0.8) {
    id2y  =0;
  } else if (fabs(eleeta2)>0.8 && fabs(eleeta2)<=1.4442) {   
    id2y  =1;
  } else if (fabs(eleeta2)>1.4442 && fabs(eleeta2)<=1.566) {
    id2y  =2;
  } else if (fabs(eleeta2)>1.566 && fabs(eleeta2)<=2.0) {
    id2y  =3;
  } else if (fabs(eleeta2)>2.0 && fabs(eleeta2)<=2.5) {
    id2y =4;
  }
  if (elept2<=15){
    iso2y=0;
  }  else if (elept2 > 15 && elept2 <=20){
    iso2y=1;
  }  else if (elept2 > 20 && elept2 <=30){
    iso2y=2;
  }  else if (elept2 > 30 && elept2 <=40){
    iso2y=3;
  }  else if (elept2 > 40 && elept2 <=50){
    iso2y=4;
  }  else if (elept2 > 50){
    iso2y=5;
  }  
  sf_ele = matrixIDISO[iso1y][id1y] * matrixIDISO[iso2y][id2y];
  if (isMC) sf_ele = matrixIDISO_MC[iso1y][id1y] * matrixIDISO_MC[iso2y][id2y];
  if (scaleUp) sf_ele = (matrixIDISO[iso1y][id1y]+matrixIDISO_errorUP[iso1y][id1y]) 
    * (matrixIDISO[iso2y][id2y]+matrixIDISO_errorUP[iso2y][id2y]);
  if (scaleUp && isMC) sf_ele = (matrixIDISO_MC[iso1y][id1y]+matrixIDISO_MC_errorUP[iso1y][id1y]) 
    * (matrixIDISO_MC[iso2y][id2y]+matrixIDISO_MC_errorUP[iso2y][id2y]);
  if (scaleDown) sf_ele = (matrixIDISO[iso1y][id1y]-matrixIDISO_errorDOWN[iso1y][id1y]) 
    * (matrixIDISO[iso2y][id2y]-matrixIDISO_errorDOWN[iso2y][id2y]);
  if (scaleDown && isMC) sf_ele = (matrixIDISO_MC[iso1y][id1y]-matrixIDISO_MC_errorDOWN[iso1y][id1y]) 
    * (matrixIDISO_MC[iso2y][id2y]-matrixIDISO_MC_errorDOWN[iso2y][id2y]);
  if (iso1y<0 || id1y<0 || iso1y>5 || id1y>4 || iso2y<0 || id2y<0 || iso2y>5 || id2y>4) return 1.0;
  return sf_ele;
}

//////// Efficiency using pt electron...
int getPtRangeElectron(double ele_pt){
  int x=0;
  if (ele_pt>=20 && ele_pt<30){
    x=1;
  }
  if (ele_pt>=30 && ele_pt<40){
    x=2;
  }
  if (ele_pt>=40 && ele_pt<50){
    x=3;
  }
  if (ele_pt>=50){
    x=4;
  }
  return x;
}
int getEtaRangeElectron(double ele_eta){
  int x=-1;
  if (fabs(ele_eta)>=0 && fabs(ele_eta)<0.8 ){
    x=1;
  }
  if (fabs(ele_eta)>=0.8 && fabs(ele_eta)<1.4442 ){
    x=2;
  }
  if (fabs(ele_eta)>=1.5666 && fabs(ele_eta)<2.0 ){
    x=3;
  }
  if (fabs(ele_eta)>=2.0 && fabs(ele_eta)<2.5 ){
    x=4;
  }
  return x;
}

double getEfficiencyCorrectionPtUsingElectron(TFile *fB, double ele1_pt ,double ele1_eta, double ele2_pt, double ele2_eta, string dataOrMC)
{
  //  TH2F* RECO_effPt;
  TH2F* ele17_effPt;
  TH2F* ele8NOTele17_effPt;
  TH2F* WP80_effPt;
  TDirectory *dir2;
  fB->cd("efficiency_vs_PtEta");
  dir2=(TDirectory*)fB->Get("efficiency_vs_PtEta");
  TList *mylist2=(TList*)dir2->GetListOfKeys();
  TIter iter2(mylist2); 
  TObject* tobj2 = 0;
  //Check for the interesting plots, regardless the content..
  while ( (tobj2 = iter2.Next()) ) {
    string name=tobj2->GetName();
    TString temp = (TString)name;
    if (dataOrMC=="Data"){
      if(temp.Contains("DATA_WP80_Probe")){
	gDirectory->GetObject(name.c_str(),WP80_effPt);
      }    
      if(temp.Contains("DATA_HLTele17_Probe")){
	gDirectory->GetObject(name.c_str(),ele17_effPt);
      }    
      if(temp.Contains("DATA_HLTele8NOTele17_Probe")){
	gDirectory->GetObject(name.c_str(),ele8NOTele17_effPt);
      }    
      //      if(temp.Contains("DATA_RECO_Probe")){
      //	gDirectory->GetObject(name.c_str(),RECO_effPt);
      //      }    
    }
    else{
      if(temp.Contains("MC_WP80_Probe")){
	gDirectory->GetObject(name.c_str(),WP80_effPt);
      }    
      if(temp.Contains("MC_HLTele17_Probe")){
	gDirectory->GetObject(name.c_str(),ele17_effPt);
      }    
      if(temp.Contains("MC_HLTele8NOTele17_Probe")){
	gDirectory->GetObject(name.c_str(),ele8NOTele17_effPt);
      }    
      //      if(temp.Contains("MC_RECO_Probe")){
      //	gDirectory->GetObject(name.c_str(),RECO_effPt);
      //      }    
    }
  }
  // Get the right pt bins
  int pt1=getPtRangeElectron(ele1_pt);
  int pt2=getPtRangeElectron(ele2_pt);
  // Get the right eta bins
  int eta1=getEtaRangeElectron(ele1_eta);
  int eta2=getEtaRangeElectron(ele2_eta);
  if (pt1<1 || pt2<1 || eta1<1 || eta2<2) return 1.0;
  double eff_global=0;
  eff_global = WP80_effPt->GetBinContent(eta1,pt1)*
    WP80_effPt->GetBinContent(eta2,pt2)*
    (ele17_effPt->GetBinContent(eta1,pt1)*ele17_effPt->GetBinContent(eta2,pt2) +
     ele17_effPt->GetBinContent(eta1,pt1)*ele8NOTele17_effPt->GetBinContent(eta2,pt2) +
     ele8NOTele17_effPt->GetBinContent(eta1,pt1)*ele17_effPt->GetBinContent(eta2,pt2));
  if (eff_global>0) return eff_global;
  return 1;
}

double getScaleFactorPtUsingElectron(TFile *fB, double ele1_pt ,double ele1_eta, double ele2_pt, double ele2_eta)
{
  TH2F* ele17_effPt;
  TH2F* ele8NOTele17_effPt;
  TH2F* WP80_effPt;
  TH2F* ele17_effPt_MC;
  TH2F* ele8NOTele17_effPt_MC;
  TH2F* WP80_effPt_MC;
  //TH2F* MC_effPt;
  //TH2F* DATA_effPt;
  TDirectory *dir2;
  fB->cd("efficiency_vs_PtEta");
  dir2=(TDirectory*)fB->Get("efficiency_vs_PtEta");
  TList *mylist2=(TList*)dir2->GetListOfKeys();
  TIter iter2(mylist2); 
  TObject* tobj2 = 0;
  //Check for the interesting plots, regardless the content..
  while ( (tobj2 = iter2.Next()) ) {
    string name=tobj2->GetName();
    TString temp = (TString)name;
    if(temp.Contains("DATA_WP80_Probe")){
      gDirectory->GetObject(name.c_str(),WP80_effPt);
    }    
    if(temp.Contains("DATA_HLTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele17_effPt);
    }    
    if(temp.Contains("DATA_HLTele8NOTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele8NOTele17_effPt);
    }    
    if(temp.Contains("MC_WP80_Probe")){
      gDirectory->GetObject(name.c_str(),WP80_effPt_MC);
    }    
    if(temp.Contains("MC_HLTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele17_effPt_MC);
    }    
    if(temp.Contains("MC_HLTele8NOTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele8NOTele17_effPt_MC);
    }
  }
  // Get the right pt bins
  int pt1=getPtRangeElectron(ele1_pt);
  int pt2=getPtRangeElectron(ele2_pt);
  // Get the right eta bins
  int eta1=getEtaRangeElectron(ele1_eta);
  int eta2=getEtaRangeElectron(ele2_eta);
  if (pt1<1 || pt2<1 || eta1<1 || eta2<2) return 1.0;
  double eff_global=1.0;
  double eff_globalMC=1.0;
  eff_global = WP80_effPt->GetBinContent(eta1,pt1)*
    WP80_effPt->GetBinContent(eta2,pt2)*
    (ele17_effPt->GetBinContent(eta1,pt1)*ele17_effPt->GetBinContent(eta2,pt2) +
     ele17_effPt->GetBinContent(eta1,pt1)*ele8NOTele17_effPt->GetBinContent(eta2,pt2) +
     ele8NOTele17_effPt->GetBinContent(eta1,pt1)*ele17_effPt->GetBinContent(eta2,pt2));
  eff_globalMC = WP80_effPt_MC->GetBinContent(eta1,pt1)*
    WP80_effPt_MC->GetBinContent(eta2,pt2)*
    (ele17_effPt_MC->GetBinContent(eta1,pt1)*ele17_effPt_MC->GetBinContent(eta2,pt2) +
     ele17_effPt_MC->GetBinContent(eta1,pt1)*ele8NOTele17_effPt_MC->GetBinContent(eta2,pt2) +
     ele8NOTele17_effPt_MC->GetBinContent(eta1,pt1)*ele17_effPt_MC->GetBinContent(eta2,pt2));
  return eff_global/eff_globalMC;
}









////////////////////////////
////////////////////////////
// !!! OBSOLETE STUFF !!! //
////////////////////////////
////////////////////////////

///////////////////
// Leading Jet Pt 
///////////////////

std::vector<double> getEfficiencyLeadingJet(double jetPt,  TH1F* effPt){
  double effPtJet=1.0;
  double effPtJeterror=0.0;

  if (jetPt>=30 && jetPt<40){
    effPtJet=effPt->GetBinContent(1);
    effPtJeterror=effPt->GetBinError(1);
  }
  if (jetPt>=40 && jetPt<50) {
    effPtJet=effPt->GetBinContent(2);
    effPtJeterror=effPt->GetBinError(2);
  }
  if (jetPt>=50 && jetPt<70) {
    effPtJet=effPt->GetBinContent(3);
    effPtJeterror=effPt->GetBinError(3);
  }
  if (jetPt>=70 && jetPt<90) {
    effPtJet=effPt->GetBinContent(4);
    effPtJeterror=effPt->GetBinError(4);
  }
  if (jetPt>=90 && jetPt<120) {
    effPtJet=effPt->GetBinContent(5);
    effPtJeterror=effPt->GetBinError(5);
  }
  if (jetPt>=120 && jetPt<150) {
    effPtJet=effPt->GetBinContent(6);
    effPtJeterror=effPt->GetBinError(6);
  }
  if (jetPt>=150 && jetPt<190) {
    effPtJet=effPt->GetBinContent(7);
    effPtJeterror=effPt->GetBinError(7);
  }
  if (jetPt>=190 && jetPt<230) {
    effPtJet=effPt->GetBinContent(8);
    effPtJeterror=effPt->GetBinError(8);
  }
  if (jetPt>=230) {
    effPtJet=effPt->GetBinContent(9);
    effPtJeterror=effPt->GetBinError(9);
  }
  std::vector<double> values;
  values.push_back(effPtJet);
  values.push_back(effPtJeterror);

  return values;
}

//Sub leading Correction
std::vector<double> getEfficiencySubLeadingJet(double jetPt,  TH1F* effPt){

  double effPtJet=1.0;
  double effPtJeterror=0.0;

  if (jetPt>=30 && jetPt<40){
    effPtJet=effPt->GetBinContent(1);
    effPtJeterror=effPt->GetBinError(1);
  }

  if (jetPt>=40 && jetPt<50){
    effPtJet=effPt->GetBinContent(2);
    effPtJeterror=effPt->GetBinError(2);
  }
  
  if (jetPt>=50 && jetPt<90){
    effPtJet=effPt->GetBinContent(3);
    effPtJeterror=effPt->GetBinError(3);
  }

  if (jetPt>=90 && jetPt<150){
    effPtJet=effPt->GetBinContent(4);
    effPtJeterror=effPt->GetBinError(4);
  }

  if (jetPt>=150){
    effPtJet=effPt->GetBinContent(5);
    effPtJeterror=effPt->GetBinError(5);
  }

  std::vector<double> values;
  values.push_back(effPtJet);
  values.push_back(effPtJeterror);

  //cout<<"2nd Jet ---------- input: jetPt -> "<<jetPt<<" ; output effPtJet -> "<<values[0]<<" ( error = "<< values[1] <<" )"<<endl;
  return values;
}

//Sub leading Correction
std::vector<double> getEfficiencySubSubLeadingJet(double jetPt,  TH1F* effPt){
  double effPtJet=1.0;
  double effPtJeterror=0.0;

  if (jetPt>=30 && jetPt<50){
    effPtJet=effPt->GetBinContent(1);
    effPtJeterror=effPt->GetBinError(1);
  }

  if (jetPt>=50 && jetPt<150){
    effPtJet=effPt->GetBinContent(2);
    effPtJeterror=effPt->GetBinError(2);
  }
  
  if (jetPt>=150){
    effPtJet=effPt->GetBinContent(3);
    effPtJeterror=effPt->GetBinError(3);
  }

  std::vector<double> values;
  values.push_back(effPtJet);
  values.push_back(effPtJeterror);

  return values;
}

std::vector<double> getEfficiencyCorrectionPt(TFile *fA, TFile *fB, int jetMultiplicity,double jetPt, string dataOrMC)
{

  std::vector<double> values;
  TH1F* effPt;

  ///////////////////////////////////////////

  //////////////
  // jET pT
  //////////////

  TDirectory *dir2;

  if (jetMultiplicity==1) {
    fB->cd("efficiency_vs_leadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_leadjetpt");
  }
  if (jetMultiplicity==2) {
    fB->cd("efficiency_vs_subleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subleadjetpt");
  }
  if (jetMultiplicity==3) {
    fB->cd("efficiency_vs_subsubleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subsubleadjetpt");
  }
  if (jetMultiplicity==4) {
    fB->cd("efficiency_vs_subsubsubleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subsubsubleadjetpt");
  }

  TList *mylist2=(TList*)dir2->GetListOfKeys();
  TIter iter2(mylist2); 
  TObject* tobj2 = 0;
  
 
  //Check for the interesting plots, regardless the content..
  while ( (tobj2 = iter2.Next()) ) {
    string name=tobj2->GetName();
    TString temp = (TString)name;
    if (dataOrMC=="Data"){
      if(temp.Contains("DATA_globalEfficiency")){
	gDirectory->GetObject(name.c_str(),effPt);
      }    
    }
    else{
      if(temp.Contains("MC_globalEfficiency")){
	gDirectory->GetObject(name.c_str(),effPt);
      }    
    }
  }
    
  if (jetPt <1000)
    {
      // insert the matrixes
      if (jetMultiplicity==1) values=getEfficiencyLeadingJet(jetPt,effPt);
      if (jetMultiplicity==2) {
	values=getEfficiencySubLeadingJet(jetPt,effPt);
      }
      if (jetMultiplicity==3) values=getEfficiencySubSubLeadingJet(jetPt,effPt);
      //if (jetMultiplicity==4) values=getEfficiencySubSubSubLeadingJet(jetPt,effPt);
    }
  else {
    cout<<"WARNING: events with too high pt. Efficiency put to 1"<<endl;
    values.push_back(1.0);
    values.push_back(0.0);    
  }

  return values;
 }

std::vector<double> getEfficiencyCorrectionJetMultiplicity(TFile *fA, TFile *fB, int jetMultiplicity, string dataOrMC)
{

 
  std::vector<double> values;
  TH1F* effJets;

  //////////////
  // Efficinecy as a function of # jets
  //////////////

  fA->cd("efficiency_vs_nJets");
  TDirectory *dir=(TDirectory*)fA->Get("efficiency_vs_nJets");
  TList *mylist=(TList*)dir->GetListOfKeys();
  TIter iter(mylist); 
  TObject* tobj = 0;

  
  //Check for the interesting plots, regardless the content..
  while ( (tobj = iter.Next()) ) {
    string name=tobj->GetName();
    TString temp = (TString)name;
    if (dataOrMC=="Data"){
      if(temp.Contains("DATA_globalEfficiency")){
	gDirectory->GetObject(name.c_str(),effJets);
      }    
    }
    else{
      if(temp.Contains("MC_globalEfficiency")){
	gDirectory->GetObject(name.c_str(),effJets);
      }    
    }
  }
  
  double effNJet=1.0;
  double effNJeterror=0.0;

  if (jetMultiplicity<=5) {
    effNJet=effJets->GetBinContent(jetMultiplicity+1);
    effNJeterror=effJets->GetBinError(jetMultiplicity+1);
    values.push_back(effNJet);
    values.push_back(effNJeterror); 
  }
  else {
    cout<<"WARNING: events with too much jets. Efficiency put to 1"<<endl;
    effNJet=1.0;
    values.push_back(1.0);
    values.push_back(0.0); 
  }

  return values;
}



//////////////////////////////
///   Scale Factors
/////////////////////////////


double getScaleFactorPtUsingElectron(TFile *fA, TFile *fB, double ele1_pt ,double ele1_eta, double ele2_pt, double ele2_eta, bool isElectron)
{
  TH2F* RECO_effPt_DATA;
  TH2F* ele17_effPt_DATA;
  TH2F* ele8NOTele17_effPt_DATA;
  TH2F* WP80_effPt_DATA;

  TH2F* RECO_effPt_MC;
  TH2F* ele17_effPt_MC;
  TH2F* ele8NOTele17_effPt_MC;
  TH2F* WP80_effPt_MC;

  TDirectory *dir2;

  fB->cd("efficiency_vs_PtEta");
  dir2=(TDirectory*)fB->Get("efficiency_vs_PtEta");

  TList *mylist2=(TList*)dir2->GetListOfKeys();
  TIter iter2(mylist2); 
  TObject* tobj2 = 0;
 
  //Check for the interesting plots, regardless the content..
  while ( (tobj2 = iter2.Next()) ) {
    string name=tobj2->GetName();
    TString temp = (TString)name;
    if(temp.Contains("DATA_WP80_Probe")){
      gDirectory->GetObject(name.c_str(),WP80_effPt_DATA);
    }    
    if(temp.Contains("DATA_HLTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele17_effPt_DATA);
    }    
    if(temp.Contains("DATA_HLTele8NOTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele8NOTele17_effPt_DATA);
    }    
    if(temp.Contains("DATA_RECO_Probe")){
      gDirectory->GetObject(name.c_str(),RECO_effPt_DATA);
    }    
    if(temp.Contains("MC_WP80_Probe")){
      gDirectory->GetObject(name.c_str(),WP80_effPt_MC);
    }    
    if(temp.Contains("MC_HLTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele17_effPt_MC);
    }    
    if(temp.Contains("MC_HLTele8NOTele17_Probe")){
      gDirectory->GetObject(name.c_str(),ele8NOTele17_effPt_MC);
    }    
    if(temp.Contains("MC_RECO_Probe")){
      gDirectory->GetObject(name.c_str(),RECO_effPt_MC);
    }    
  }

  // Get the right pt bins
  int pt1=getPtRangeElectron(ele1_pt);
  int pt2=getPtRangeElectron(ele2_pt);
  // Get the right eta bins
  int eta1=getEtaRangeElectron(ele1_eta);
  int eta2=getEtaRangeElectron(ele2_eta);

  double eff_global_DATA=0;
  double eff_global_MC=0;

  if (isElectron) {
    eff_global_DATA = WP80_effPt_DATA->GetBinContent(eta1,pt1)*
      WP80_effPt_DATA->GetBinContent(eta2,pt2)*
      RECO_effPt_DATA->GetBinContent(eta1,pt1)*
      RECO_effPt_DATA->GetBinContent(eta2,pt2)*
      (ele17_effPt_DATA->GetBinContent(eta1,pt1)*ele17_effPt_DATA->GetBinContent(eta2,pt2) +
      ele17_effPt_DATA->GetBinContent(eta1,pt1)*ele8NOTele17_effPt_DATA->GetBinContent(eta2,pt2) +
      ele8NOTele17_effPt_DATA->GetBinContent(eta1,pt1)*ele17_effPt_DATA->GetBinContent(eta2,pt2));
    eff_global_MC = WP80_effPt_MC->GetBinContent(eta1,pt1)*
      WP80_effPt_MC->GetBinContent(eta2,pt2)*
      RECO_effPt_MC->GetBinContent(eta1,pt1)*
      RECO_effPt_MC->GetBinContent(eta2,pt2)*
      (ele17_effPt_MC->GetBinContent(eta1,pt1)*ele17_effPt_MC->GetBinContent(eta2,pt2) +
       ele17_effPt_MC->GetBinContent(eta1,pt1)*ele8NOTele17_effPt_MC->GetBinContent(eta2,pt2) +
       ele8NOTele17_effPt_MC->GetBinContent(eta1,pt1)*ele17_effPt_MC->GetBinContent(eta2,pt2));
  } else {
    eff_global_DATA = WP80_effPt_DATA->GetBinContent(eta1,pt1)*
      WP80_effPt_DATA->GetBinContent(eta2,pt2)*
      RECO_effPt_DATA->GetBinContent(eta1,pt1)*
      RECO_effPt_DATA->GetBinContent(eta2,pt2)*
      ele17_effPt_DATA->GetBinContent(eta1,pt1)*
      ele17_effPt_DATA->GetBinContent(eta2,pt2);
    eff_global_MC = WP80_effPt_MC->GetBinContent(eta1,pt1)*
      WP80_effPt_MC->GetBinContent(eta2,pt2)*
      RECO_effPt_MC->GetBinContent(eta1,pt1)*
      RECO_effPt_MC->GetBinContent(eta2,pt2)*
      ele17_effPt_MC->GetBinContent(eta1,pt1)*
      ele17_effPt_MC->GetBinContent(eta2,pt2);
  }

  if (eff_global_DATA>0 && eff_global_MC>0) return eff_global_DATA/eff_global_MC;
  return 1;
}

// Leading Jet Pt 
double getScaleFactorsLeadingJet(double jetPt_MC,  TH1F* effPtData,  TH1F* effPtMC){
  double effPtJet=1.0;

  if (jetPt_MC>=30 && jetPt_MC<40){
    effPtJet=effPtData->GetBinContent(1)/effPtMC->GetBinContent(1);
  }
  if (jetPt_MC>=40 && jetPt_MC<50) {
    effPtJet=effPtData->GetBinContent(2)/effPtMC->GetBinContent(2);
  }
  if (jetPt_MC>=50 && jetPt_MC<70) {
    effPtJet=effPtData->GetBinContent(3)/effPtMC->GetBinContent(3);
  }
  if (jetPt_MC>=70 && jetPt_MC<90) {
    effPtJet=effPtData->GetBinContent(4)/effPtMC->GetBinContent(4);
  }
  if (jetPt_MC>=90 && jetPt_MC<120) {
    effPtJet=effPtData->GetBinContent(5)/effPtMC->GetBinContent(5);
  }
  if (jetPt_MC>=120 && jetPt_MC<150) {
    effPtJet=effPtData->GetBinContent(6)/effPtMC->GetBinContent(6);
  }
  if (jetPt_MC>=150 && jetPt_MC<190) {
    effPtJet=effPtData->GetBinContent(7)/effPtMC->GetBinContent(7);
  }
  if (jetPt_MC>=190 && jetPt_MC<230) {
    effPtJet=effPtData->GetBinContent(8)/effPtMC->GetBinContent(8);
  }
  if (jetPt_MC>=230) {
    effPtJet=effPtData->GetBinContent(9)/effPtMC->GetBinContent(9);
  }
  cout<<"scale factor Data/MC is "<<effPtJet<<endl;
  return effPtJet;
}

// Leading Jet Pt 
double getScaleFactorsSubLeadingJet(double jetPt_MC,  TH1F* effPtData,  TH1F* effPtMC){
  double effPtJet=1.0;

  if (jetPt_MC>=30 && jetPt_MC<40){
    effPtJet=effPtData->GetBinContent(1)/effPtMC->GetBinContent(1);
  }
  if (jetPt_MC>=40 && jetPt_MC<50) {
    effPtJet=effPtData->GetBinContent(2)/effPtMC->GetBinContent(2);
  }
  if (jetPt_MC>=50 && jetPt_MC<90) {
    effPtJet=effPtData->GetBinContent(3)/effPtMC->GetBinContent(3);
  }
  if (jetPt_MC>=90 && jetPt_MC<150) {
    effPtJet=effPtData->GetBinContent(4)/effPtMC->GetBinContent(4);
  }
  if (jetPt_MC>=150) {
    effPtJet=effPtData->GetBinContent(5)/effPtMC->GetBinContent(5);
  }

  //cout<<"2nd Jet scale factor Data/MC is "<<effPtJet<<endl;
  return effPtJet;
}

// Leading Jet Pt 
double getScaleFactorsSubSubLeadingJet(double jetPt_MC,  TH1F* effPtData,  TH1F* effPtMC){
  double effPtJet=1.0;

  if (jetPt_MC>=30 && jetPt_MC<50){
    effPtJet=effPtData->GetBinContent(1)/effPtMC->GetBinContent(1);
  }
  if (jetPt_MC>=50 && jetPt_MC<150) {
    effPtJet=effPtData->GetBinContent(2)/effPtMC->GetBinContent(2);
  }
  if (jetPt_MC>=150) {
    effPtJet=effPtData->GetBinContent(3)/effPtMC->GetBinContent(3);
  }
  //cout<<"scale factor Data/MC is "<<effPtJet<<endl;
  return effPtJet;
}

double getScaleFactorJetPt(TFile *fA, TFile *fB, int jetMultiplicity_MC,double jetPt_MC)
{

  double values;
  TH1F* effJets;
  TH1F* effPtMC;
  TH1F* effPtData;

  ///////////////////////////////////////////

  //////////////
  // jET pT
  //////////////

  TDirectory *dir2;

  if (jetMultiplicity_MC==1) {
    fB->cd("efficiency_vs_leadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_leadjetpt");
  }
  if (jetMultiplicity_MC==2) {
    fB->cd("efficiency_vs_subleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subleadjetpt");
  }
  if (jetMultiplicity_MC==3) {
    fB->cd("efficiency_vs_subsubleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subsubleadjetpt");
  }
  if (jetMultiplicity_MC==4) {
    fB->cd("efficiency_vs_subsubsubleadjetpt");
    dir2=(TDirectory*)fB->Get("efficiency_vs_subsubsubleadjetpt");
  }

  TList *mylist2=(TList*)dir2->GetListOfKeys();
  TIter iter2(mylist2); 
  TObject* tobj2 = 0;
  
 
  //Check for the interesting plots, regardless the content..
  while ( (tobj2 = iter2.Next()) ) {
    string name=tobj2->GetName();
    TString temp = (TString)name;
    if(temp.Contains("DATA_globalEfficiency")){
      gDirectory->GetObject(name.c_str(),effPtData);
    }    
    if(temp.Contains("MC_globalEfficiency")){
      gDirectory->GetObject(name.c_str(),effPtMC);
    }    
  }
    
  if (jetPt_MC <1000)
    {
      // insert the matrixes
      if (jetMultiplicity_MC==1) values=getScaleFactorsLeadingJet(jetPt_MC,effPtData, effPtMC);
      if (jetMultiplicity_MC==2) {
	values=getScaleFactorsSubLeadingJet(jetPt_MC,effPtData, effPtMC);
      }
      if (jetMultiplicity_MC==3) values=getScaleFactorsSubSubLeadingJet(jetPt_MC,effPtData, effPtMC);
      //if (jetMultiplicity==4) values=getScaleFactorsSubSubSubLeadingJet(jetPt_MC,effPtData, effPtMC);
    }
  else {
    cout<<"WARNING: events with too high pt. Efficiency put to 1"<<endl;
    values=1.0;
  }

  return values;
 }
