import FWCore.ParameterSet.Config as cms
import os
process = cms.Process("JetValidation")

###################
##### Loading what we need!
###################

from PhysicsTools.PatAlgos.patTemplate_cfg import *
from PhysicsTools.PatAlgos.tools.trigTools import *
switchOnTrigger(process,sequence='patDefaultSequence',hltProcess = '*')
from PhysicsTools.PatAlgos.tools.coreTools import *
from PhysicsTools.PatAlgos.tools.pfTools import *
from RecoJets.JetProducers.FastjetParameters_cfi import *
from RecoJets.JetProducers.ak5TrackJets_cfi import *
from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

process.load("CommonTools.ParticleFlow.pfElectrons_cff")
process.load("CommonTools.ParticleFlow.pfMuons_cff")
process.load("CommonTools.ParticleFlow.ParticleSelectors.pfSortByType_cff")
process.load("CommonTools.ParticleFlow.pfNoPileUp_cff")
process.load("CommonTools.ParticleFlow.TopProjectors.pfNoElectron_cfi")
process.load("CommonTools.ParticleFlow.TopProjectors.pfNoMuon_cfi")
process.load("CommonTools.ParticleFlow.goodOfflinePrimaryVertices_cfi")
##-------------------- Import the JEC services -----------------------
process.load("JetMETCorrections.Configuration.DefaultJEC_cff")
process.load("JetMETCorrections.Configuration.JetCorrectionServices_cff")
process.load("JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff")
##process.load("JetMETCorrections.Configuration.JetCorrectionProducers_cff")

##-------------------- Import the Jet RECO modules -----------------------
process.load('RecoJets.Configuration.RecoPFJets_cff')
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
#process.load("MagneticField.Engine.uniformMagneticField_cfi") 
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("RecoJets.Configuration.GenJetParticles_cff")
process.load("RecoJets.Configuration.RecoGenJets_cff")

##-------------------- Turn-on the FastJet density calculation -----------------------
process.kt6PFJets.doRhoFastjet = True

##-------------------- Turn-on the FastJet jet area calculation for your favorite algorithm -----------------------
process.kt6PFJets.doAreaFastjet = True
process.ak5PFJets.doAreaFastjet = True

# to compute FastJet rho to correct isolation (note: EtaMax restricted to 2.5)
process.kt6PFJetsForIsolation = process.kt4PFJets.clone( rParam = 0.6, doRhoFastjet = True)
process.kt6PFJetsForIsolation.Rho_EtaMax = cms.double(2.5)


process.options   = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True) )

process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(True),
                                     makeTriggerResults=cms.untracked.bool(True),
                                     )

process.GlobalTag.globaltag = 'MC_44_V5D::All'

####################
#### Files
###################

# readFiles = cms.untracked.vstring()
# readFiles.extend([
# #"file:/gpfs/cms/data/2011/r9test/pythiaZ2tunesroot/FEF7EE7B-8780-E011-837F-E41F131816A8.root",
# "file:/gpfs/cms/data/2011/SynchTest/DYJetsToLL_TuneZ2_PU_S6_START44.root",
#     ])

#No FSR
# readFiles = cms.untracked.vstring()
# readFiles.extend([    
# "file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_nolepfsr_cff_py_RAW2DIGI_L1Reco_RECO_5_1_gjk.root",
# "file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_nolepfsr_cff_py_RAW2DIGI_L1Reco_RECO_2_1_zEi.root",
# "file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_nolepfsr_cff_py_RAW2DIGI_L1Reco_RECO_3_1_fL9.root",
# "file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_nolepfsr_cff_py_RAW2DIGI_L1Reco_RECO_1_1_BaG.root",
# "file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_nolepfsr_cff_py_RAW2DIGI_L1Reco_RECO_4_1_Rhn.root",
# "file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_nolepfsr_cff_py_RAW2DIGI_L1Reco_RECO_6_1_5wf.root",
# "file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_nolepfsr_cff_py_RAW2DIGI_L1Reco_RECO_7_1_jrE.root",
# "file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_nolepfsr_cff_py_RAW2DIGI_L1Reco_RECO_9_1_AeS.root",
# "file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_nolepfsr_cff_py_RAW2DIGI_L1Reco_RECO_8_1_tEX.root",
#     ])

# #Tauola
readFiles = cms.untracked.vstring()
readFiles.extend([
    "file:/gpfs/grid/srm/cms/store/data/Fall11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S6-START44_V5-v1/0001/B48B1A68-460A-E111-88DF-485B39800BAB.root"
#"file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_tauola_cff_py_RAW2DIGI_L1Reco_RECO_2_1_vpH.root",
#"file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_tauola_cff_py_RAW2DIGI_L1Reco_RECO_1_1_5GF.root",
#"file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_tauola_cff_py_RAW2DIGI_L1Reco_RECO_6_1_JKT.root",
#"file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_tauola_cff_py_RAW2DIGI_L1Reco_RECO_7_1_BcD.root",
#"file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_tauola_cff_py_RAW2DIGI_L1Reco_RECO_4_1_LZx.root",
#"file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_tauola_cff_py_RAW2DIGI_L1Reco_RECO_3_1_s7f.root",
#"file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_tauola_cff_py_RAW2DIGI_L1Reco_RECO_8_1_kAs.root",
#"file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_tauola_cff_py_RAW2DIGI_L1Reco_RECO_5_1_lkN.root",
#"file:/gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph_tauola_cff_py_RAW2DIGI_L1Reco_RECO_9_1_0zt.root",
    ])
    
process.MessageLogger.cerr.FwkReport  = cms.untracked.PSet(
     #reportEvery = cms.untracked.int32(10),
     reportEvery = cms.untracked.int32(500),
 )

process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                            fileNames = readFiles,
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            )


####################
#### Trigger...
###################

trigger2011v3 = cms.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v4","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v5","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9", "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10")

trigger2011RunB= cms.vstring("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8", "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9", "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10")

trigger2011v1  = cms.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC8_Mass30_v3","HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v3","HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v3","HLT_Ele32_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v2","HLT_Ele32_CaloIdL_CaloIsoVL_SC17_v3","HLT_Ele45_CaloIdVT_TrkIdT_v3","HLT_Ele15_CaloIdVT_TrkIdT_LooseIsoPFTau15_v4","HLT_Ele15_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_LooseIsoPFTau15_v4","HLT_Ele15_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_LooseIsoPFTau20_v4")

trigger2010    = cms.vstring("HLT_Ele17_CaloIdl_Ele8_CaloIsoIdL_CaloIsoVL_v3","HLT_Ele15_SW_L1R","HLT_Ele15_SW_CaloEleId_L1R","HLT_Ele17_SW_CaloEleId_L1R","HLT_Ele17_SW_TightEleId_L1R","HLT_Ele17_SW_TightEleId_L1R_v2","HLT_Ele17_SW_TightEleId_L1R_v3","HLT_Photon10_L1R","HLT_Photon15_L1R","HTL_Photon15_Cleaned_L1R")

alltriggers    = cms.vstring() # In this way, the HLT string is empty and it will trigger every event

trigger2011v2 = cms.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v4","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v5","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8")

# from dav HLT analysis
triggersMay10Jul05 = cms.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v4","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v5","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v6")

triggersAug05 = cms.vstring("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass30_v6")

triggersOct03 = cms.vstring("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass30_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass30_v7","HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_Ele17_v1")


####################
#### Lepton Selection
###################


process.Selection = cms.EDFilter('ZpatFilterPf',
                                 electronCollection = cms.InputTag("patElectronsWithTrigger"),
                                 triggerCollectionTag = cms.InputTag("TriggerResults","","HLT"),
                                 UseCombinedPrescales = cms.bool(False),
                                 doTheHLTAnalysis = cms.bool(False),
                                 removePU=  cms.bool(False),
                                 #TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011v2+trigger2010,
                                 TriggerNames = trigger2011v3,
                                 secondEleEnThrhold   = cms.double(20.0),
                                 firstEleEnThrhold    = cms.double(20.0),
                                 lowZmassLimit        = cms.double(71.0),
                                 highZmassLimit       = cms.double(111.0),
                                 maxEtaForElectron    = cms.double(2.4),
                                 )

####################
#### TAP
###################


process.TAPwp80 = cms.EDFilter('EfficiencyFilter',
                           electronCollection = cms.InputTag("patElectrons"),
                           HLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle17"),
                           superClusterCollection_EB = cms.InputTag("correctedHybridSuperClusters"),
                           superClusterCollection_EE = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
                           triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
                           filename=cms.untracked.string("ZAnalysisFilter.root"),
                           UseCombinedPrescales = cms.bool(False),
                           removePU=  cms.bool(False),
                           WP80_efficiency  =  cms.bool(True),
                           HLTele17_efficiency  =  cms.bool(False),
                           HLTele8_efficiency  =  cms.bool(False),
                           RECO_efficiency  =  cms.bool(False),
                           New_HE  =  cms.bool(False),
                           VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                           electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
                           candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
                           JetCollectionLabel = cms.InputTag("ak5PFchsJetsRCL1FastL2L3"),
                           #TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB,
                           TriggerNames = trigger2011v3
                           )

process.TAPwp80newHE = cms.EDFilter('EfficiencyFilter',
                           electronCollection = cms.InputTag("patElectrons"),
                           HLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle17"),                                    
                           superClusterCollection_EB = cms.InputTag("correctedHybridSuperClusters"),
                           superClusterCollection_EE = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
                           triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
                           filename=cms.untracked.string("ZAnalysisFilter.root"),
                           UseCombinedPrescales = cms.bool(False),
                           removePU=  cms.bool(False),
                           WP80_efficiency  =  cms.bool(True),
                           HLTele17_efficiency  =  cms.bool(False),
                           HLTele8_efficiency  =  cms.bool(False),
                           RECO_efficiency  =  cms.bool(False),
                           New_HE  =  cms.bool(True),
                           VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                           electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
                           candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
                           JetCollectionLabel = cms.InputTag("ak5PFchsJetsRCL1FastL2L3"),
                           #TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB
                           TriggerNames = trigger2011v3
                           )

process.TAPhltele8NOTele17 = cms.EDFilter('EfficiencyFilter',
                           electronCollection = cms.InputTag("patElectrons"),
                           HLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle8NOTEle17"),                                  
                           superClusterCollection_EB = cms.InputTag("correctedHybridSuperClusters"),
                           superClusterCollection_EE = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
                           triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
                           filename=cms.untracked.string("ZAnalysisFilter.root"),
                           UseCombinedPrescales = cms.bool(False),
                           removePU=  cms.bool(False),
                           WP80_efficiency  =  cms.bool(False),
                           HLTele17_efficiency  =  cms.bool(False),
                           HLTele8_efficiency  =  cms.bool(True),
                           RECO_efficiency  =  cms.bool(False),
                           New_HE  =  cms.bool(False),
                           VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                           electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
                           candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
                           JetCollectionLabel = cms.InputTag("ak5PFchsJetsRCL1FastL2L3"),
                           #TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB
                           TriggerNames = trigger2011v3       
                           )

process.TAPhltele17 = cms.EDFilter('EfficiencyFilter',
                           electronCollection = cms.InputTag("patElectrons"),
                           HLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle17"),                                   
                           superClusterCollection_EB = cms.InputTag("correctedHybridSuperClusters"),
                           superClusterCollection_EE = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
                           triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
                           filename=cms.untracked.string("ZAnalysisFilter.root"),
                           UseCombinedPrescales = cms.bool(False),
                           removePU=  cms.bool(False),
                           WP80_efficiency  =  cms.bool(False),
                           HLTele17_efficiency  =  cms.bool(True),
                           HLTele8_efficiency  =  cms.bool(False),
                           RECO_efficiency  =  cms.bool(False),
                           New_HE  =  cms.bool(False),
                           VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                           electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
                           candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
                           JetCollectionLabel = cms.InputTag("ak5PFchsJetsRCL1FastL2L3"),
                           #TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB
                           TriggerNames = trigger2011v3
                           )

process.TAPreco = cms.EDFilter('EfficiencyFilter',
                           electronCollection = cms.InputTag("patElectrons"),
                           HLTelectronCollection = cms.InputTag("trgmatchPatElectronsReco"),                               
                           superClusterCollection_EB = cms.InputTag("correctedHybridSuperClusters"),
                           superClusterCollection_EE = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
                           triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
                           filename=cms.untracked.string("ZAnalysisFilter.root"),
                           UseCombinedPrescales = cms.bool(False),
                           removePU=  cms.bool(False),
                           WP80_efficiency  =  cms.bool(False),
                           HLTele17_efficiency  =  cms.bool(False),
                           HLTele8_efficiency  =  cms.bool(False),
                           RECO_efficiency  =  cms.bool(True),
                           New_HE  =  cms.bool(False),
                           VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                           electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
                           candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
                           JetCollectionLabel = cms.InputTag("ak5PFchsJetsRCL1FastL2L3"),
                           #TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB
                           TriggerNames = trigger2011v3
                           )

####################
###
###    JEC for CHS
###
###################

#from Histo.HistoAnalyzer.jecChsConfig_cfi import *
from JetMETCorrections.Configuration.JetCorrectionServices_cff import *
# L1 FastJet PU Subtraction
process.ak5PFchsL1Fastjet = ak5PFL1Fastjet.clone(algorithm = 'AK5PFchs' )
# L2 (relative eta-conformity) Correction Services
process.ak5PFchsL2Relative = ak5PFL2Relative.clone(algorithm = 'AK5PFchs' )
# L3 (absolute) Correction Services
process.ak5PFchsL3Absolute = ak5PFL3Absolute.clone(algorithm = 'AK5PFchs' )
process.ak5PFchsL1FastL2L3 = cms.ESSource(
     'JetCorrectionServiceChain',
     correctors = cms.vstring('ak5PFchsL1Fastjet','ak5PFchsL2Relative','ak5PFchsL3Absolute')
     )



####################
#### 
#### Jets..
#### 
###################

from Histo.HistoAnalyzer.PFJetParametersRC_cfi import *

process.ak5PFJetsOLD = cms.EDProducer("FastjetJetProducer",
     PFJetParametersOLD,
     AnomalousCellParameters,
     jetAlgorithm = cms.string("AntiKt"),
     rParam       = cms.double(0.5)
     )
process.ak5PFJetsOLD.doAreaFastjet = True
process.ak5PFJetsOLDL1FastL2L3 = process.ak5PFJetsL1FastL2L3.clone(src = 'ak5PFJetsOLD')

process.ak5PFJetsRC = cms.EDProducer("FastjetJetProducer",
     PFJetParametersRC,
     AnomalousCellParameters,
     jetAlgorithm = cms.string("AntiKt"),
     rParam       = cms.double(0.5)
     )
process.ak5PFJetsRC.doAreaFastjet = True
process.ak5PFJetsRC.doRhoFastjet = False  # recipe 15th March JEC
process.ak5PFJetsRCL2L3 = process.ak5PFJetsL2L3.clone(src = 'ak5PFJetsRC')
#process.ak5PFJetsRCL1FastL2L3Residual = process.ak5PFJetsL1FastL2L3Residual.clone(src = 'ak5PFJetsRC')
process.ak5PFchsJetsRCL1FastL2L3 = process.ak5PFJetsL1FastL2L3.clone(src = 'ak5PFJetsRC', correctors = ['ak5PFchsL1FastL2L3'])

process.ak5PFJetsPU = cms.EDProducer("FastjetJetProducer",
     PFJetParametersPU,
     AnomalousCellParameters,
     jetAlgorithm = cms.string("AntiKt"),
     rParam       = cms.double(0.5)
     )
process.ak5PFJetsPU.doAreaFastjet = True
process.ak5PFJetsPU.doRhoFastjet = False  # recipe 15th March JEC
#process.ak5PFJetsPUL1FastL2L3Residual = process.ak5PFJetsL1FastL2L3Residual.clone(src = 'ak5PFJetsPU')
process.ak5PFchsJetsPUL1FastL2L3 = process.ak5PFJetsL1FastL2L3.clone(src = 'ak5PFJetsPU', correctors = ['ak5PFchsL1FastL2L3'])

process.goodEPair = cms.EDProducer('pfAnalyzer',
                                   electronCollection = cms.InputTag("patElectronsWithTrigger"),
                                   pflowEleCollection = cms.untracked.InputTag("pfIsolatedElectrons"),
                                   removePU=  cms.bool(False),
                                   secondEleEnThrhold   = cms.double(20.0),
                                   firstEleEnThrhold    = cms.double(20.0),
                                   lowZmassLimit        = cms.double(71.0),
                                   highZmassLimit       = cms.double(111.0),
                                   maxEtaForElectron    = cms.double(2.4),
                                   )

process.goodElec = cms.EDProducer('goodEleProducer',
                                   electronCollection = cms.InputTag("patElectronsWithTrigger"),
                                   pflowEleCollection = cms.untracked.InputTag("pfIsolatedElectrons"),
                                   removePU=  cms.bool(False),
                                   )
                                   
process.validationOldJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsL1FastL2L3"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(True),
                                       usingPF = cms.untracked.bool(True),
                                       deltaRConeJet           = cms.double(0.3),
                                       deltaRCone           = cms.double(0.3),
                                       deltaRConeGen         = cms.double(0.1),
                                       maxEtaJets           = cms.double(2.4),
                                       minPtJets            = cms.double(30.0),
                                       chargedEmEnergyFraction = cms.double(0.99),
                                       neutralHadronEnergyFraction= cms.double(0.99),
                                       neutralEmEnergyFraction= cms.double(0.99),
                                       chargedHadronEnergyFraction= cms.double(0.0),
                                       chargedMultiplicity= cms.int32(0),
                                      JECUncertainties= cms.double(0),                                        
                                       )
                                   
process.validationTESTJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsOLDL1FastL2L3"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(True),
                                       usingPF = cms.untracked.bool(True),
                                       deltaRConeJet           = cms.double(0.3),
                                       deltaRCone           = cms.double(0.3),
                                       deltaRConeGen         = cms.double(0.1),
                                       maxEtaJets           = cms.double(2.4),
                                       minPtJets            = cms.double(30.0),
                                       chargedEmEnergyFraction = cms.double(0.99),
                                       neutralHadronEnergyFraction= cms.double(0.99),
                                       neutralEmEnergyFraction= cms.double(0.99),
                                       chargedHadronEnergyFraction= cms.double(0.0),
                                       chargedMultiplicity= cms.int32(0),   
                                      JECUncertainties= cms.double(0),                                     
                                       )
                                   
process.validationPUJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFchsJetsPUL1FastL2L3"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(True),
                                       usingPF = cms.untracked.bool(True),
                                       deltaRConeJet           = cms.double(0.3),
                                       deltaRCone           = cms.double(0.3),
                                       deltaRConeGen         = cms.double(0.1),
                                       maxEtaJets           = cms.double(2.4),
                                       minPtJets            = cms.double(30.0),
                                       chargedEmEnergyFraction = cms.double(0.99),
                                       neutralHadronEnergyFraction= cms.double(0.99),
                                       neutralEmEnergyFraction= cms.double(0.99),
                                       chargedHadronEnergyFraction= cms.double(0.0),
                                       chargedMultiplicity= cms.int32(0),  
                                      JECUncertainties= cms.double(0),                                      
                                       )
                                   
process.validationJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFchsJetsRCL1FastL2L3"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(True),
                                       usingPF = cms.untracked.bool(True),
                                       deltaRConeJet           = cms.double(0.3),
                                       deltaRCone           = cms.double(0.3),
                                       deltaRConeGen         = cms.double(0.1),
                                       maxEtaJets           = cms.double(2.4),
                                       minPtJets            = cms.double(30.0),
                                       chargedEmEnergyFraction = cms.double(0.99),
                                       neutralHadronEnergyFraction= cms.double(0.99),
                                       neutralEmEnergyFraction= cms.double(0.99),
                                       chargedHadronEnergyFraction= cms.double(0.0),
                                       chargedMultiplicity= cms.int32(0),     
                                      JECUncertainties= cms.double(0),                                   
                                       )

process.validationRC = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFJetsRC"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    tpMapName = cms.string('EventWeight'),
                                    genJets = cms.InputTag("ak5GenJets"),
                                    usingMC = cms.untracked.bool(True),
                                    usingPF = cms.untracked.bool(True),
                                    deltaRConeJet           = cms.double(0.3),
                                    deltaRCone           = cms.double(0.3),
                                    deltaRConeGen         = cms.double(0.1),
                                    maxEtaJets           = cms.double(2.4),
                                    minPtJets            = cms.double(30.0),
                                    chargedEmEnergyFraction = cms.double(0.99),
                                    neutralHadronEnergyFraction= cms.double(0.99),
                                    neutralEmEnergyFraction= cms.double(0.99),
                                    chargedHadronEnergyFraction= cms.double(0.0),
                                    chargedMultiplicity= cms.int32(0),  
                                      JECUncertainties= cms.double(0),                                   
                                    )

process.validationPU = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFJetsPU"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    tpMapName = cms.string('EventWeight'),
                                    genJets = cms.InputTag("ak5GenJets"),
                                    usingMC = cms.untracked.bool(True),
                                    usingPF = cms.untracked.bool(True),
                                    deltaRConeJet           = cms.double(0.3),
                                    deltaRCone           = cms.double(0.3),
                                    deltaRConeGen         = cms.double(0.1),
                                    maxEtaJets           = cms.double(2.4),
                                    minPtJets            = cms.double(30.0),
                                    chargedEmEnergyFraction = cms.double(0.99),
                                    neutralHadronEnergyFraction= cms.double(0.99),
                                    neutralEmEnergyFraction= cms.double(0.99),
                                    chargedHadronEnergyFraction= cms.double(0.0),
                                    chargedMultiplicity= cms.int32(0),  
                                      JECUncertainties= cms.double(0),                                   
                                    )

                                  
process.reclusValidation = cms.EDAnalyzer('reclusVal',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsL1FastL2L3"),
                                       jetCollectionPU = cms.InputTag("ak5PFchsJetsPUL1FastL2L3"),
                                       jetCollectionRC = cms.InputTag("ak5PFchsJetsRCL1FastL2L3"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(True),
                                       usingPF = cms.untracked.bool(True),
                                       deltaRCone           = cms.double(0.3),
                                       deltaRConeGen         = cms.double(0.1),
                                       maxEtaJets           = cms.double(2.4),
                                       minPtJets            = cms.double(30.0),
                                       chargedEmEnergyFraction = cms.double(0.99),
                                       neutralHadronEnergyFraction= cms.double(0.99),
                                       neutralEmEnergyFraction= cms.double(0.99),
                                       chargedHadronEnergyFraction= cms.double(0.0),
                                       chargedMultiplicity= cms.int32(0),
                                       )

####################
#### HLT Analysis, MC reweight, and other stuff
###################

process.demo = cms.EDProducer('HistoProducer',
                              electronCollection = cms.InputTag('patElectronsWithTrigger'),
                              triggerCollection = cms.InputTag("TriggerResults","","HLT"),
                              UseCombinedPrescales = cms.bool(False),
                              #TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03,
                              TriggerNames = trigger2011v3,
                              removePU=  cms.bool(True),
                              usingMC=  cms.bool(True),
                              doTheHLTAnalysis = cms.bool(False),
                              VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),              
                              TotalNEventTag = cms.vstring('TotalEventCounter'),
                              WhichRun = cms.string("Run2011AB"), ##Select which datasets you wonna use to reweight
                              RootuplaName = cms.string("treeVJ_"),
                              eventWeightsCollection= cms.string("EventWeight"),
                              giveEventWeightEqualToOne= cms.bool(False)
)



######################
#                    #
#     pfNoPileUP     #
#                    #
######################

process.pfPileUp.Vertices = 'goodOfflinePrimaryVertices'  # recipe 15th March JEC
process.pfPileUp.checkClosestZVertex = cms.bool(False) # recipe 15th March JEC
process.pfPileUp.PFCandidates = cms.InputTag("particleFlow")
process.pfNoPileUp.bottomCollection = cms.InputTag("particleFlow")

######################
#                    #
#    pfElectrons     #
#                    #
######################

process.patElectrons.useParticleFlow=True
#process.pfAllElectrons.src = "particleFlow"
process.pfAllElectrons.src = "pfNoPileUp"
process.isoValElectronWithNeutral.deposits[0].deltaR = 0.4
process.isoValElectronWithCharged.deposits[0].deltaR = 0.4
process.isoValElectronWithPhotons.deposits[0].deltaR = 0.4
process.pfIsolatedElectrons.isolationCut = 0.2
process.pfNoElectron.bottomCollection = cms.InputTag("pfNoPileUp")
#process.pfNoElectron.topCollection = cms.InputTag("goodEPair")   #remove only the two electron candidates
process.pfNoElectron.topCollection = cms.InputTag("goodElec")   #remove all the electron passing the selections


######################
#                    #
#  TRG MATCHING -ON- #
#                    #
######################

### Standard trigger matching:
process.eleTriggerMatchHLT = cms.EDProducer( "PATTriggerMatcherDRLessByR",
                                             src     = cms.InputTag( "patElectrons" ),
                                             matched = cms.InputTag( "patTrigger"),
                                             matchedCuts = cms.string('(path("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*",0,0) && filter("hltEle17CaloIdIsoEle8CaloIdIsoPixelMatchDoubleFilter")) || (path("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*",0,0) && filter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolDoubleFilter"))'),
                                             maxDPtRel = cms.double( 5 ),
                                             maxDeltaR = cms.double( 0.3 ),
                                             resolveAmbiguities    = cms.bool( True ),
                                             resolveByMatchQuality = cms.bool( True )
                                             )

process.patElectronsWithTrigger = cms.EDProducer("PATTriggerMatchElectronEmbedder",
                                                    src     = cms.InputTag("patElectrons"),
                                                    matches = cms.VInputTag(cms.InputTag('eleTriggerMatchHLT'))
                                                 )

switchOnTriggerMatching( process, ['eleTriggerMatchHLT' ],sequence ='patDefaultSequence', hltProcess = '*' )

### Trigger matching without EMBEDDING into PATs:

HLTEle8Path1 = "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1"
HLTEle8Path2 = "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2"
HLTEle8Path3 = "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3"
HLTEle8Path4 = "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v4"
HLTEle8Path5 = "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v5"
HLTEle8Path6 = "HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v6"
HLTEle8Path7 = "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6"
HLTEle8Path8 = "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7"
HLTEle8Path9 = "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8"
HLTEle8Path10 = "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9"
HLTEle8Path11 = "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10"

hltEle8Filter = "hltEle17CaloIdIsoEle8CaloIdIsoPixelMatchDoubleFilter"
hltEle17Filter = "hltEle17CaloIdLCaloIsoVLPixelMatchFilter"
hltEle8Filter7 = "hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolDoubleFilter"
hltEle17Filter7 = "hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolFilter"

HLTProcessName = "HLT"

hltTagsForEle8 = cms.VInputTag(
    cms.InputTag(HLTEle8Path1, hltEle8Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path2, hltEle8Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path3, hltEle8Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path4, hltEle8Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path5, hltEle8Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path6, hltEle8Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path7, hltEle8Filter7 , HLTProcessName),
    cms.InputTag(HLTEle8Path8, hltEle8Filter7 , HLTProcessName),
    cms.InputTag(HLTEle8Path9, hltEle8Filter7 , HLTProcessName),
    cms.InputTag(HLTEle8Path10, hltEle8Filter7 , HLTProcessName),
    cms.InputTag(HLTEle8Path11, hltEle8Filter7 , HLTProcessName),
    )

hltTagsForEle17 = cms.VInputTag(
    cms.InputTag(HLTEle8Path1, hltEle17Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path2, hltEle17Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path3, hltEle17Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path4, hltEle17Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path5, hltEle17Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path6, hltEle17Filter , HLTProcessName),
    cms.InputTag(HLTEle8Path7, hltEle17Filter7 , HLTProcessName),
    cms.InputTag(HLTEle8Path8, hltEle17Filter7 , HLTProcessName),
    cms.InputTag(HLTEle8Path9, hltEle17Filter7 , HLTProcessName),
    cms.InputTag(HLTEle8Path10, hltEle17Filter7 , HLTProcessName),
    cms.InputTag(HLTEle8Path11, hltEle17Filter7 , HLTProcessName),
    )


process.trgmatchPatElectronsEle8 = cms.EDProducer("trgMatchedPatElectronProducer",
                                        InputProducer = cms.InputTag("patElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        noHltFiring = cms.untracked.bool(False),
                                        hltTags = hltTagsForEle8,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchPatElectronsEle17 = cms.EDProducer("trgMatchedPatElectronProducer",
                                        InputProducer = cms.InputTag("patElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        noHltFiring = cms.untracked.bool(True),
                                        hltTags = hltTagsForEle17,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchPatElectronsNOTEle17 = cms.EDProducer("trgMatchedPatElectronProducer",
                                        InputProducer = cms.InputTag("patElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        noHltFiring = cms.untracked.bool(True),
                                        antiSelect = cms.untracked.bool(True),
                                        hltTags = hltTagsForEle17,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchPatElectronsEle8NOTEle17 = cms.EDProducer("trgMatchedPatElectronProducer",
                                        InputProducer = cms.InputTag("trgmatchPatElectronsNOTEle17"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        noHltFiring = cms.untracked.bool(False),
                                        hltTags = hltTagsForEle8,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

HLTRecoPath1  = "HLT_Ele32_CaloIdL_CaloIsoVL_SC17_v1"
HLTRecoPath2  = "HLT_Ele32_CaloIdL_CaloIsoVL_SC17_v2"
HLTRecoPath3  = "HLT_Ele32_CaloIdL_CaloIsoVL_SC17_v3"
HLTRecoPath4  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v1"
HLTRecoPath5  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v2"
HLTRecoPath6  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v3"
HLTRecoPath7  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v4"
HLTRecoPath8  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v5"
HLTRecoPath9  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v6"
HLTRecoPath10 = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v7"
HLTRecoPath11 = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v8"

hltRecoFilter  = "hltEle32CaloIdLCaloIsoVLSC17PixelMatchFilter"
hltRecoFilterH = "hltEle32CaloIdTCaloIsoTTrkIdTTrkIsoTSC17TrackIsolFilter"

hltTagsForReco = cms.VInputTag(
    cms.InputTag(HLTRecoPath1,  hltRecoFilter , HLTProcessName),
    cms.InputTag(HLTRecoPath2,  hltRecoFilter , HLTProcessName),
    cms.InputTag(HLTRecoPath3,  hltRecoFilter , HLTProcessName),
    cms.InputTag(HLTRecoPath4,  hltRecoFilterH , HLTProcessName),
    cms.InputTag(HLTRecoPath5,  hltRecoFilterH , HLTProcessName),
    cms.InputTag(HLTRecoPath6,  hltRecoFilterH , HLTProcessName),
    cms.InputTag(HLTRecoPath7,  hltRecoFilterH , HLTProcessName),
    cms.InputTag(HLTRecoPath8,  hltRecoFilterH , HLTProcessName),
    cms.InputTag(HLTRecoPath9,  hltRecoFilterH , HLTProcessName),
    cms.InputTag(HLTRecoPath10, hltRecoFilterH , HLTProcessName),
    cms.InputTag(HLTRecoPath11, hltRecoFilterH , HLTProcessName),
    )

process.trgmatchPatElectronsReco = cms.EDProducer("trgMatchedPatElectronProducer",
                                        InputProducer = cms.InputTag("patElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        noHltFiring = cms.untracked.bool(True),
                                        matchUnprescaledTriggerOnly = cms.untracked.bool(False),
                                        hltTags = hltTagsForReco,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )


#####################
#                   #
#   GEN JET PROP    #
#                   #
#####################

genParticlesForJetsNoNu = process.genParticlesForJets.clone()
process.genParticlesForJetsNoNu.ignoreParticleIDs += cms.vuint32( 12,14,16)


GenJetParameters = cms.PSet(
    src            = cms.InputTag("genParticlesForJets"),
    srcPVs         = cms.InputTag(''),
    jetType        = cms.string('GenJet'),
    jetPtMin       = cms.double(3.0),
    inputEtMin     = cms.double(0.0),
    inputEMin      = cms.double(0.0),
    doPVCorrection = cms.bool(False),
    # pileup with offset correction
    doPUOffsetCorr = cms.bool(False),
    # if pileup is false, these are not read:
    nSigmaPU = cms.double(1.0),
    radiusPU = cms.double(0.5),  
    # fastjet-style pileup     
    doAreaFastjet  = cms.bool(False),
    doRhoFastjet   = cms.bool(False),
    # if doPU is false, these are not read:
    Active_Area_Repeats = cms.int32(5),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(6.0),
    Rho_EtaMax = cms.double(4.5),
    useDeterministicSeed= cms.bool( True ),
    minSeed             = cms.uint32( 14327 )
    )

process.ak5GenJets = cms.EDProducer(
    "FastjetJetProducer",
     GenJetParameters,
    AnomalousCellParameters,
    jetAlgorithm = cms.string("AntiKt"),
    rParam       = cms.double(0.5)
    )


######################
#                    #
#  PROCESS OUT       #
#                    #
######################

process.out.fileName = cms.untracked.string('test-filtering.root')
process.out.outputCommands =  cms.untracked.vstring(
    'drop *',
    )
process.out.SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('JetValidation'))

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('jetValidation.root')
                                   )


#####################
#                   #
#    Counting       #
#                   #
#####################


process.TotalEventCounter = cms.EDProducer("EventCountProducer")

######################
#                    #
#  SEQUENCE          #
#                    #
######################

process.ToolInizialization = cms.Path(
    process.kt6PFJetsForIsolation*
    process.kt6PFJets*
    process.ak5PFJets*
    process.ak5PFJetsL1FastL2L3*
    process.goodOfflinePrimaryVertices*
    process.pfNoPileUpSequence*
    process.pfAllNeutralHadrons*
    process.pfAllChargedHadrons*
    process.pfAllPhotons*
    process.pfElectronSequence*
    process.patTrigger*
    process.patDefaultSequence*
    process.eleTriggerMatchHLT*
    process.patElectronsWithTrigger*
    process.goodElec*
    #process.goodEPair*
    process.pfNoElectron*
    process.ak5PFJetsRC*
    process.ak5PFchsJetsRCL1FastL2L3*
    process.ak5PFJetsOLD*
    process.ak5PFJetsOLDL1FastL2L3*
    process.ak5PFJetsPU*
    process.ak5PFchsJetsPUL1FastL2L3
    )


process.TAPAnalysisWP80 = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchPatElectronsEle17*
    process.TAPwp80
    )

process.TAPAnalysisWP80newHE = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchPatElectronsEle17*
    process.TAPwp80newHE
    )

process.TAPAnalysisHLTele8NOTele17 = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchPatElectronsNOTEle17*
    process.trgmatchPatElectronsEle8NOTEle17*
    process.TAPhltele8NOTele17
    )

process.TAPAnalysisHLTele17 = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchPatElectronsEle17*
    process.TAPhltele17
    )

process.TAPAnalysisRECO = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchPatElectronsReco*
    process.TAPreco
    )

process.JetValidation = cms.Path(
    process.TotalEventCounter* 
    process.eleTriggerMatchHLT*
    process.patElectronsWithTrigger*  
    process.goodOfflinePrimaryVertices*   
    process.Selection*
    process.demo*
    process.goodEPair*
    process.reclusValidation*
    process.validationOldJEC*
    process.validationPUJEC*
    #process.validationPU*
    process.validationRC*
    #process.validationTESTJEC*
    process.validationJEC
    )

#####################
#                   #
#    Outpath        #
#                   #
#####################

process.outpath = cms.EndPath(
        #process.out
        )
