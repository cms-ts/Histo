import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = 'GR_P_V20::All'

#DS! added to suppress error messages
process.MessageLogger.debugModules.append("ZAnalyzerFilter")
process.MessageLogger.cerr.threshold = 'ERROR'

process.MessageLogger.debugModules.append("HLTConfigData")
process.MessageLogger.cerr.threshold = 'ERROR'

process.MessageLogger.cerr.FwkReport  = cms.untracked.PSet(
     reportEvery = cms.untracked.int32(5000),
 )
#DS! it was: "report every 500, but changed due to enormous stdout

process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

###########
# HLT Summary. If you don't trust the online, dump the information decommenting the following lines
#########

#process.MessageLogger.destinations = ['HLTreport.txt']
#from HLTrigger.HLTanalyzers.hlTrigReport_cfi import hlTrigReport
#process.hltReport = hlTrigReport.clone(
#   HLTriggerResults = cms.InputTag("TriggerResults","","HLT")
#    )

#process.endpath = cms.EndPath(process.hltReport) 
#process.MessageLogger.categories.append("HLTrigReport")

readFiles = cms.untracked.vstring()
readFiles.extend([
"/store/data/Run2011A/DoubleElectron/RAW-RECO/ZElectron-May10ReReco-v1/0000/7034100E-DF7B-E011-A9F1-002618943939.root",
    ])

process.source = cms.Source("PoolSource", fileNames = readFiles,
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
                            )

######
### Define how to match the HLT Trigger
#####

# electron triggers are taken accroding to https://twiki.cern.ch/twiki/bin/viewauth/CMS/VbtfZeeBaselineSelection

muontriggers      = cms.vstring("HLT_Mu3","HLT_Mu5","HLT_Mu7","HLT_Mu9","HLT_Mu11","HLT_Mu15_v1")
electrontriggers  = cms.vstring("HLT_Photon10_L1R","HLT_Photon15_Cleaned_L1R","HLT_Ele15_SW_CaloEleId_L1R","HLT_Ele17_SW_CaloEleId_L1R","HLT_Ele17_SW_TightEleId_L1R")
electrontriggers += cms.vstring("HLT_Ele22_SW_TighterCaloIdIsol_L1R_v1","HLT_Ele22_SW_TighterCaloIdIsol_L1R_v2")
alltriggers       = muontriggers + electrontriggers
alltriggers = cms.vstring() # In this way, the HLT string is empty and it will trigger every event


process.Selection = cms.EDFilter('ZanalyzerFilter',
		electronCollection = cms.InputTag("gsfElectrons"),
		triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
		UseCombinedPrescales = cms.bool(False),
		doTheHLTAnalysis = cms.bool(False),
		TriggerNames = alltriggers
)

process.demo = cms.EDProducer('HistoProducer',
                              electronCollection = cms.InputTag('gsfElectrons'),
                              triggerCollection = cms.InputTag("TriggerResults","","HLT"),
                              UseCombinedPrescales = cms.bool(False),
                              TriggerNames = alltriggers,
                              removePU=  cms.bool(True),
                              usingMC=  cms.bool(False),
                              doTheHLTAnalysis = cms.bool(False),
                              VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),              
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('histo.root')
)

process.load("JetCollections_cfi")


process.p = cms.Path(process.Selection*process.PFJetPath*process.demo)
