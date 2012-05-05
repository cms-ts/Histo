// Montecarlo scale factors for 2011A Run
// search here https://cmsweb.cern.ch/das/

// integrated cross sections expressed in pb
double dataLumi2011A = 2046.769; double dataXsect = 3048.0;
double dataLumi2011B = 2579.073; //9 febbraio 2012
double dataLumi2011 = dataLumi2011A + dataLumi2011B;

//Repro using pixelcalc 42X
double dataLumi2011Apix = 2151; //2200; //double dataXsect = 3048.0; // 3 may -> 4.890 - 2739 = 2151
double dataLumi2011Bpix = 2739; //3 may 2012 + Giuseppe. Usa il comando crab -c XXXXX -report per stima perfetta!!!!   
double dataLumi2011pix = dataLumi2011Apix + dataLumi2011Bpix;


//Repro using pixelcalc 44X                                                                                                                                                      
//double dataLumi2011A = 2285; double dataXsect = 3048.0;
//double dataLumi2011B = 2733; //5 marzo 2012      

double zjetsXsect = 3048.0;	double zjetsNevts = 36277961; // /DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM
double wjetsXsect = 31314.0;	double wjetsNevts = 81352581; // /WJetsToLNu_TuneZ2_7TeV-madgraph-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM
double ttbarXsect = 157.0;	double ttbarNevts = 3701947; // /TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM
double qcdEM23Xsect = 2.361e8 * 0.0106;	double qcdEM23Nevts = 35729669; // /QCD_Pt-20to30_EMEnriched_TuneZ2_7TeV-pythia6/Summer11-PU_S4_START42_V11-v1/AODSIM
double qcdEM38Xsect = 5.944e7 * 0.061;	double qcdEM38Nevts = 70392060; // /QCD_Pt-30to80_EMEnriched_TuneZ2_7TeV-pythia/Summer11-PU_S4_START42_V11-v1/AODSIM
double qcdEM817Xsect = 898200.0 * 0.159;double qcdEM817Nevts = 8150672; // /QCD_Pt-80to170_EMEnriched_TuneZ2_7TeV-pythia6/Summer11-PU_S4_START42_V11-v1/AODSIM
double qcdBC23Xsect = 2.361e8 * 5.9E-4;	double qcdBC23Nevts = 2081560; // /QCD_Pt-20to30_BCtoE_TuneZ2_7TeV-pythia6/Summer11-PU_S3_START42_V11-v2/AODSIM
double qcdBC38Xsect = 5.944e7 * 0.00242;double qcdBC38Nevts = 2030033; // /QCD_Pt-30to80_BCtoE_TuneZ2_7TeV-pythia6/Summer11-PU_S4_START42_V11-v1/AODSIM
double qcdBC817Xsect = 898200.0 * 0.0105;double qcdBC817Nevts = 1082691; // /QCD_Pt-80to170_BCtoE_TuneZ2_7TeV-pythia/Summer11-PU_S4_START42_V11-v1/AODSIM

//Dibosons bkg
double WZXsect= 18.2; double zwjetsNevts=4265243;
double ZZXsect= 5.9; double zzjetsNevts=4191045;
double WWXsect= 43.0; double wwjetsNevts=4225916;

//======================================//
//		Calc ratios		//
//======================================//

double zjetsScale = dataLumi2011A / (zjetsNevts / zjetsXsect);
double ttbarScale = dataLumi2011A / (ttbarNevts / ttbarXsect);
double wjetsScale = dataLumi2011A / (wjetsNevts / wjetsXsect);
double wzjetsScale = dataLumi2011A / (zwjetsNevts / WZXsect);
double zzjetsScale = dataLumi2011A / (zzjetsNevts / ZZXsect);
double wwjetsScale = dataLumi2011A / (wwjetsNevts / WWXsect);

double qcd23emScale = dataLumi2011A / (qcdEM23Nevts / qcdEM23Xsect);
double qcd38emScale = dataLumi2011A / (qcdEM38Nevts / qcdEM38Xsect);
double qcd817emScale = dataLumi2011A / (qcdEM817Nevts / qcdEM817Xsect);

double qcd23bcScale = dataLumi2011A / (qcdBC23Nevts / qcdBC23Xsect);
double qcd38bcScale = dataLumi2011A / (qcdBC38Nevts / qcdBC38Xsect);
double qcd817bcScale = dataLumi2011A / (qcdBC817Nevts / qcdBC817Xsect);

