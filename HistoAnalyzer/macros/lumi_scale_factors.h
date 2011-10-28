// Montecarlo scale factors for 2011A Run
// search here https://cmsweb.cern.ch/das/
// integrated cross sections expressed in pb
double dataLumi2011A = 2.090e03;
double zjetsXsect = 2475.0;	double zjetsNevts = 36277961; // /DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM
double ttbarXsect = 94.76;	double ttbarNevts = 3701947; // /TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM
double wjetsXsect = 27770.0;	double wjetsNevts = 81352581; // /WJetsToLNu_TuneZ2_7TeV-madgraph-tauola/Summer11-PU_S4_START42_V11-v1/AODSIM
double qcdEM23Xsect = 2.361e8 * 0.0106;	double qcdEM23Nevts = 35729669; // /QCD_Pt-20to30_EMEnriched_TuneZ2_7TeV-pythia6/Summer11-PU_S4_START42_V11-v1/AODSIM
double qcdEM38Xsect = 5.944e7 * 0.061;	double qcdEM38Nevts = 70392060; // /QCD_Pt-30to80_EMEnriched_TuneZ2_7TeV-pythia/Summer11-PU_S4_START42_V11-v1/AODSIM
double qcdEM817Xsect = 898200.0 * 0.159;double qcdEM817Nevts = 8150672; // /QCD_Pt-80to170_EMEnriched_TuneZ2_7TeV-pythia6/Summer11-PU_S4_START42_V11-v1/AODSIM
double qcdBC23Xsect = 2.361e8 * 5.9E-4;	double qcdBC23Nevts = 2081560; // /QCD_Pt-20to30_BCtoE_TuneZ2_7TeV-pythia6/Summer11-PU_S3_START42_V11-v2/AODSIM
double qcdBC38Xsect = 5.944e7 * 0.00242;double qcdBC38Nevts = 2030033; // /QCD_Pt-30to80_BCtoE_TuneZ2_7TeV-pythia6/Summer11-PU_S4_START42_V11-v1/AODSIM
double qcdBC817Xsect = 898200.0 * 0.0105;double qcdBC817Nevts = 1082691; // /QCD_Pt-80to170_BCtoE_TuneZ2_7TeV-pythia/Summer11-PU_S4_START42_V11-v1/AODSIM



//======================================//
//		Calc ratios		//
//======================================//

double zjetsScale = dataLumi2011A / (zjetsNevts / zjetsXsect);
double ttbarScale = dataLumi2011A / (ttbarNevts / ttbarXsect);
double wjetsScale = dataLumi2011A / (wjetsNevts / wjetsXsect);
