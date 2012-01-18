
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
from RecoJets.JetProducers.FastjetParameters_cfi import *
from RecoJets.JetProducers.ak5TrackJets_cfi import *
from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

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

#################################################################
############ WARNING! to be run on data only! (r.c. 2011)########
############        need to be adapted for MC            ########
#################################################################
removeMCMatching(process, ['All'])###############################
#################################################################

process.options = cms.untracked.PSet(wantSummary=cms.untracked.bool(True),
                                     makeTriggerResults=cms.untracked.bool(True),
                                     )

process.GlobalTag.globaltag = 'GR_R_41_V0::All'

####################
#### Files
###################

readFiles = cms.untracked.vstring()
readFiles.extend([
    "file:/gpfs/grid/srm/cms/store/data/Run2011A/DoubleElectron/RAW-RECO/ZElectron-03Oct2011-v1/0000/FEAF4709-07EF-E011-A071-002618FDA208.root"
    ])

process.MessageLogger.cerr.FwkReport  = cms.untracked.PSet(
     reportEvery = cms.untracked.int32(500),
 )

process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                            fileNames = readFiles,
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            )

####################
#### Trigger
###################

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

process.Selection = cms.EDFilter('ZpatFilter',
                                 electronCollection = cms.InputTag("patElectronsWithTrigger"),
                                 triggerCollectionTag = cms.InputTag("TriggerResults","","HLT"),
                                 UseCombinedPrescales = cms.bool(False),
                                 doTheHLTAnalysis = cms.bool(True),
                                 removePU=  cms.bool(True),
                                 TriggerNames = alltriggers ##triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB
)

####################
#### TAP
###################

process.TAP = cms.EDFilter('EfficiencyFilter',
                           electronCollection = cms.InputTag("patElectronsWithTrigger"),
                           triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
                           filename=cms.untracked.string("ZAnalysisFilter.root"),
                           UseCombinedPrescales = cms.bool(True),
                           removePU=  cms.bool(True),
                           electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
                           candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
                           JetCollectionLabel = cms.InputTag("ak5PFJets"),
                           TriggerNames = alltriggers ##triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB
                           )

####################
#### Jets..
###################

process.goodEPair = cms.EDProducer('ZanalyzerProducer',
                                   electronCollection = cms.InputTag("gsfElectrons"),
                                   removePU=  cms.bool(True),
                                   )
                                   
process.validationJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("gsfElectrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsL1FastL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(False),
                                       )
                                   
process.validationL2L3Residual = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("gsfElectrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(False),
                                       )

process.validation = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("gsfElectrons"),
                                    jetCollection = cms.InputTag("ak5PFJets"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    tpMapName = cms.string('EventWeight'),
                                    genJets = cms.InputTag("ak5GenJets"),
                                    usingMC = cms.untracked.bool(False),
                                    )

####################
#### HLT Analysis, MC reweight, and other stuff
###################

process.demo = cms.EDProducer('HistoProducer',
                              electronCollection = cms.InputTag('gsfElectrons'),
                              triggerCollection = cms.InputTag("TriggerResults","","HLT"),
                              UseCombinedPrescales = cms.bool(False),
                              TriggerNames = alltriggers, ## triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB, 
                              removePU=  cms.bool(True),
                              usingMC=  cms.bool(False),
                              doTheHLTAnalysis = cms.bool(True),
                              VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                              TotalNEventTag = cms.vstring('TotalEventCounter'),
)


######################
#                    #
#  TRG MATCHING -ON- #
#                    #
######################


process.eleTriggerMatchHLT = cms.EDProducer( "PATTriggerMatcherDRLessByR",
                                             src     = cms.InputTag( "patElectrons" ),
                                             matched = cms.InputTag( "patTrigger"),##patTriggerObjectStandAlones_patTrigger__PAT
                                             matchedCuts = cms.string('(path("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*",0,0) && filter("hltEle17CaloIdIsoEle8CaloIdIsoPixelMatchDoubleFilter")) || (path("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*",0,0) && filter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolDoubleFilter"))'),
                                             maxDPtRel = cms.double( 5 ),
                                             maxDeltaR = cms.double( 0.3 ),
                                             resolveAmbiguities    = cms.bool( True ),
                                             resolveByMatchQuality = cms.bool( True )
                                             )

### patElectronsWithTrigger ###########################################
process.patElectronsWithTrigger = cms.EDProducer("PATTriggerMatchElectronEmbedder",
                                                    src     = cms.InputTag("patElectrons"),
                                                    matches = cms.VInputTag(cms.InputTag('eleTriggerMatchHLT'))
                                                 )

switchOnTriggerMatching( process, ['eleTriggerMatchHLT' ],sequence ='patDefaultSequence', hltProcess = '*' )



#####################
#                   #
#      OUTPUT       #
#                   #
#####################


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


#####################
#                   #
#    SEQUENCE       #
#                   #
#####################

process.TAPAnalysis = cms.Path(
    process.TotalEventCounter*
    process.kt6PFJetsForIsolation*
    process.kt6PFJets*
    process.ak5PFJets*
    process.patTrigger*
    process.patDefaultSequence*
    process.eleTriggerMatchHLT*
    process.patElectronsWithTrigger*
    process.TAP
    )

process.JetValidation = cms.Path(
    process.kt6PFJetsForIsolation*
    #process.kt6PFJets*
    process.Selection*
    process.demo*
    process.goodEPair*
    process.ak5PFJets*
    #process.validation*
    process.ak5PFJetsL2L3Residual*
    process.validationL2L3Residual*
    process.ak5PFJetsL1FastL2L3Residual
    *process.validationJEC
     )

#####################
#                   #
#    Outpath        #
#                   #
#####################

process.outpath = cms.EndPath(
    #process.out
    )
