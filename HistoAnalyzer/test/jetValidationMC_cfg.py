import FWCore.ParameterSet.Config as cms

import os

process = cms.Process("JetValidation")


##-------------------- Import the JEC services -----------------------
process.load("JetMETCorrections.Configuration.DefaultJEC_cff")
process.load("JetMETCorrections.Configuration.JetCorrectionServices_cff")
process.load("JetMETCorrections.Configuration.JetCorrectionServicesAllAlgos_cff")
##process.load("JetMETCorrections.Configuration.JetCorrectionProducers_cff")

##-------------------- Import the Jet RECO modules -----------------------
process.load('RecoJets.Configuration.RecoPFJets_cff')
##-------------------- Turn-on the FastJet density calculation -----------------------
process.kt6PFJets.doRhoFastjet = True
##-------------------- Turn-on the FastJet jet area calculation for your favorite algorithm -----------------------
process.kt6PFJets.doAreaFastjet = True

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_R_41_V0::All'

process.load("MagneticField.Engine.uniformMagneticField_cfi") 

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.options   = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True) )

process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(True),
                                     makeTriggerResults=cms.untracked.bool(True),
                                     )

###########
# HLT Summary
#########

#process.MessageLogger.destinations = ['HLTreport_Mu_All.txt']
#from HLTrigger.HLTanalyzers.hlTrigReport_cfi import hlTrigReport
#process.hltReport = hlTrigReport.clone(
#    HLTriggerResults = cms.InputTag("TriggerResults","","HLT")
#    )

#process.endpath = cms.EndPath(process.hltReport) 
#process.MessageLogger.categories.append("HLTrigReport")



readFiles = cms.untracked.vstring()
readFiles.extend([
    #"file:/gpfs/grid/srm/cms/store/data/Run2011A/DoubleElectron/RAW-RECO/ZElectron-May10ReReco-v1/0000/0234F556-657C-E011-9556-002618943948.root",
    #"file:/gpfs/grid/srm/cms/store/data/Run2011A/DoubleElectron/RAW-RECO/ZElectron-May10ReReco-v1/0000/FE8C3F99-D97B-E011-BEA4-0018F3D096EE.root",
    ])

process.MessageLogger.cerr.FwkReport  = cms.untracked.PSet(
     reportEvery = cms.untracked.int32(500),
 )

process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                            #fileNames = readFiles,
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            fileNames =cms.untracked.vstring(
    'file:/gpfs/cms/data/2011/r9test/pythiaZ2tunesroot/FEF7EE7B-8780-E011-837F-E41F131816A8.root'),
                            )

trigger2011v1  = cms.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_SC8_Mass30_v3","HLT_Ele17_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_Ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_v3","HLT_Ele27_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v3","HLT_Ele32_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_v2","HLT_Ele32_CaloIdL_CaloIsoVL_SC17_v3","HLT_Ele45_CaloIdVT_TrkIdT_v3","HLT_Ele15_CaloIdVT_TrkIdT_LooseIsoPFTau15_v4","HLT_Ele15_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_LooseIsoPFTau15_v4","HLT_Ele15_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_LooseIsoPFTau20_v4")

trigger2010    = cms.vstring("HLT_Ele17_CaloIdl_Ele8_CaloIsoIdL_CaloIsoVL_v3","HLT_Ele15_SW_L1R","HLT_Ele15_SW_CaloEleId_L1R","HLT_Ele17_SW_CaloEleId_L1R","HLT_Ele17_SW_TightEleId_L1R","HLT_Ele17_SW_TightEleId_L1R_v2","HLT_Ele17_SW_TightEleId_L1R_v3","HLT_Photon10_L1R","HLT_Photon15_L1R","HTL_Photon15_Cleaned_L1R")

alltriggers    = cms.vstring() # In this way, the HLT string is empty and it will trigger every event

trigger2011v2 = cms.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v4","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v5","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8")

# from dav HLT analysis
triggersMay10Jul05 = cms.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v4","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v5","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v6")

triggersAug05 = cms.vstring("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass30_v6")

triggersOct03 = cms.vstring("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass30_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8","HLT_Ele17_CaloIdVT_CaloIsoVT_TrkIdT_TrkIsoVT_Ele8_Mass30_v7","HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_Ele17_v1")




#Jet energy correction
# kt6PFL1FastL2L3Residual = Service

# Producer
#process.kt6PFJetsL1FastL2L3Residual = cms.EDProducer(
#    'PFJetCorrectionProducer',
#    src        = cms.InputTag('kt6PFJets'),
#    correctors = cms.vstring('kt6PFL1FastL2L3Residual')
#    )


process.Selection = cms.EDFilter('ZanalyzerFilter',
		electronCollection = cms.InputTag("gsfElectrons"),
		triggerCollectionTag = cms.InputTag("TriggerResults","","HLT"),
		UseCombinedPrescales = cms.bool(False),
		doTheHLTAnalysis = cms.bool(True),
		#TriggerNames = alltriggers
		TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03
)

process.goodEPair = cms.EDProducer('ZanalyzerProducer',
		electronCollection = cms.InputTag("gsfElectrons")
                                   )
                                   
process.validationJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("gsfElectrons"),
                                       jetCollection = cms.InputTag("kt6PFJetsL1FastL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       usingMC  = cms.untracked.bool(True),
##                                       weightCollection = cms.string('EventWeight'),
                                       )

process.validation = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("gsfElectrons"),
                                    jetCollection = cms.InputTag("kt6PFJets"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    tpMapName = cms.string('EventWeight'),
                                    usingMC  = cms.untracked.bool(True),
  ##                                  weightCollection = cms.string('EventWeight'),
                                    )

process.demo = cms.EDProducer('HistoProducer',
#process.demo = cms.EDProducer('HistoAnalyzer',
                              electronCollection = cms.InputTag('gsfElectrons'),
                              triggerCollection = cms.InputTag("TriggerResults","","HLT"),
                              UseCombinedPrescales = cms.bool(False),
                              #TriggerNames = alltriggers,
			      TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03,
                              removePU=  cms.bool(True),
                              usingMC=  cms.bool(True),
                              doTheHLTAnalysis = cms.bool(True),
                              VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),              
)


process.genpAna = cms.EDAnalyzer('GENPAnalyzer',
                                 goodEPair = cms.InputTag("goodEPair"),
                                 usingMC   = cms.untracked.bool(True),
                                 )


process.load("JetCollections_cfi")

process.out = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
       SelectEvents = cms.vstring('JetValidation')
    ),
    fileName = cms.untracked.string('test_filtering.root')
)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('jetValidationMC.root')
)

process.JetValidation = cms.Path(
    process.PFJetPath*
    process.Selection*
    process.demo*
    process.goodEPair*
    #process.genpAna*
    process.kt6PFJets*process.validation*
    process.kt6PFJetsL1FastL2L3Residual*process.validationJEC
     )

#process.e= cms.EndPath(process.out)
