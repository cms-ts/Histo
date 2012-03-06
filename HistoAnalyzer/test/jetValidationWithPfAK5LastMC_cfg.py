
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
from PhysicsTools.PatAlgos.tools.helpers import listModules, applyPostfix
from RecoJets.JetProducers.FastjetParameters_cfi import *
from RecoJets.JetProducers.ak5TrackJets_cfi import *
from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

process.load("CommonTools.ParticleFlow.pfElectrons_cff")
process.load("CommonTools.ParticleFlow.pfMuons_cff")
process.load("CommonTools.ParticleFlow.ParticleSelectors.pfSortByType_cff")
process.load("CommonTools.ParticleFlow.pfNoPileUp_cff")
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

process.GlobalTag.globaltag = 'MC_42_V17::All'

####################
#### Files
###################

readFiles = cms.untracked.vstring()
readFiles.extend([
"file:/gpfs/cms/data/2011/r9test/pythiaZ2tunesroot/FEF7EE7B-8780-E011-837F-E41F131816A8.root"
    ])

process.MessageLogger.cerr.FwkReport  = cms.untracked.PSet(
     reportEvery = cms.untracked.int32(500),
 )

process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(100) )

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

process.Selection = cms.EDFilter('ZpatFilterPf',
                                 electronCollection = cms.InputTag("patElectronsWithTrigger"),
                                 triggerCollectionTag = cms.InputTag("TriggerResults","","HLT"),
                                 UseCombinedPrescales = cms.bool(False),
                                 doTheHLTAnalysis = cms.bool(False),
                                 #removePU=  cms.bool(True),
                                 removePU=  cms.bool(False),
                                 TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB
)

####################
#### TAP
###################


process.TAPwp80 = cms.EDFilter('EfficiencyFilter',
                           electronCollection = cms.InputTag("patElectronsWithTrigger"),
                           superClusterCollection_EB = cms.InputTag("correctedHybridSuperClusters"),
                           superClusterCollection_EE = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
                           triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
                           filename=cms.untracked.string("ZAnalysisFilter.root"),
                           UseCombinedPrescales = cms.bool(False),
                           #removePU=  cms.bool(True),
                           removePU=  cms.bool(False),
                           WP80_efficiency  =  cms.bool(True),
                           HLTele17_efficiency  =  cms.bool(False),
                           HLTele8NOTele17_efficiency  =  cms.bool(False),
                           RECO_efficiency  =  cms.bool(False),
                           VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                           electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
                           candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
                           JetCollectionLabel = cms.InputTag("ak5PFJets"),
                           TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB
                           )

process.TAPreco = cms.EDFilter('EfficiencyFilter',
                           electronCollection = cms.InputTag("patElectronsWithTrigger"),
                           superClusterCollection_EB = cms.InputTag("correctedHybridSuperClusters"),
                           superClusterCollection_EE = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
                           triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
                           filename=cms.untracked.string("ZAnalysisFilter.root"),
                           UseCombinedPrescales = cms.bool(False),
                           #removePU=  cms.bool(True),
                           removePU=  cms.bool(False),
                           WP80_efficiency  =  cms.bool(False),
                           HLTele17_efficiency  =  cms.bool(False),
                           HLTele8NOTele17_efficiency  =  cms.bool(False),
                           RECO_efficiency  =  cms.bool(True),
                           VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                           electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
                           candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
                           JetCollectionLabel = cms.InputTag("ak5PFJets"),
                           TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB
                           )

####################
#### Jets..
###################

process.goodEPair = cms.EDProducer('pfAnalyzer',
                                   electronCollection = cms.InputTag("patElectronsWithTrigger"),
                                   #removePU=  cms.bool(True),
                                   removePU=  cms.bool(False),
                                   )
                                   
process.validationJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsL1FastL2L3"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(True),
                                       usingPF = cms.untracked.bool(True)
                                       )
                                   
process.validationL2L3 = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsL2L3"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(True),
                                       usingPF = cms.untracked.bool(True)
                                       )

process.validation = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFJets"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    tpMapName = cms.string('EventWeight'),
                                    genJets = cms.InputTag("ak5GenJets"),
                                    usingMC = cms.untracked.bool(True),
                                    usingPF = cms.untracked.bool(True)
                                    )

####################
#### HLT Analysis, MC reweight, and other stuff
###################

process.demo = cms.EDProducer('HistoProducer',
                              electronCollection = cms.InputTag('patElectronsWithTrigger'),# Change it, sooner or later...
                              triggerCollection = cms.InputTag("TriggerResults","","HLT"),
                              UseCombinedPrescales = cms.bool(False),
                              TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB, 
                              removePU=  cms.bool(True),
                              usingMC=  cms.bool(True),
                              doTheHLTAnalysis = cms.bool(False),
                              VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                              TotalNEventTag = cms.vstring('TotalEventCounter'),
                              WhichRun = cms.string("Run2011B"), ##UNESSENTIAL FOR DATA:Select which datasets you wonna use to reweight..
                              RootuplaName = cms.string("treeVJ_"), 
                              eventWeightsCollection= cms.string("EventWeight")
)

process.demobefore = cms.EDProducer('HistoProducer',
                              electronCollection = cms.InputTag('patElectronsWithTrigger'),# Change it, sooner or later...
                              triggerCollection = cms.InputTag("TriggerResults","","HLT"),
                              UseCombinedPrescales = cms.bool(False),
                              TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB, 
                              removePU=  cms.bool(True),
                              usingMC=  cms.bool(True),
                              doTheHLTAnalysis = cms.bool(False),
                              VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                              TotalNEventTag = cms.vstring('TotalEventCounter'),
                              WhichRun = cms.string("Run2011B"), ##UNESSENTIAL FOR DATA:Select which datasets you wonna use to reweight..
                              RootuplaName = cms.string("treeVJBefore_"),
                              eventWeightsCollection= cms.string("EventWeight")     
)
######################
#                    #
#  TRG MATCHING -ON- #
#                    #
######################
#adaptPFElectrons(process,"patElectrons","PF")
#postfix = ""
#adaptPFElectrons(process,applyPostfix(process,"patElectrons",postfix),postfix)

process.patElectrons.useParticleFlow=True
process.isoValElectronWithNeutral.deposits[0].deltaR = 0.4
process.isoValElectronWithCharged.deposits[0].deltaR = 0.4
process.isoValElectronWithPhotons.deposits[0].deltaR = 0.4
process.pfIsolatedElectrons.combinedIsolationCut = 0.2
process.pfAllElectrons.src = "particleFlow:electrons"
#process.pfAllElectrons.src = "pfNoPileUp"


process.patElectronsForTap=process.patElectrons.clone()
process.patElectronsForTap.pfElectronSource = "particleFlow:electrons"

process.eleTriggerMatchHLT = cms.EDProducer( "PATTriggerMatcherDRLessByR",
                                             src     = cms.InputTag( "patElectrons" ),# This one shold become a PFpat
                                             matched = cms.InputTag( "patTrigger"),##patTriggerObjectStandAlones_patTrigger__PAT
                                             matchedCuts = cms.string('(path("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*",0,0) && filter("hltEle17CaloIdIsoEle8CaloIdIsoPixelMatchDoubleFilter")) || (path("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*",0,0) && filter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolDoubleFilter"))'),
                                             maxDPtRel = cms.double( 5 ),
                                             maxDeltaR = cms.double( 0.3 ),
                                             resolveAmbiguities    = cms.bool( True ),
                                             resolveByMatchQuality = cms.bool( True )
                                             )

### patElectronsWithTrigger ###########################################
process.patElectronsWithTrigger = cms.EDProducer("PATTriggerMatchElectronEmbedder",
                                                    src     = cms.InputTag("patElectrons"),# This one shold become a PFpat 
                                                    matches = cms.VInputTag(cms.InputTag('eleTriggerMatchHLT'))
                                                 )

switchOnTriggerMatching( process, ['eleTriggerMatchHLT' ],sequence ='patDefaultSequence', hltProcess = '*' )

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


#####################
#                   #
#      OUTPUT       #
#                   #
#####################


process.out.fileName = cms.untracked.string('test-filteringPf.root')
process.out.outputCommands =  cms.untracked.vstring(
    'keep *_*_*_PAT',
    )
process.out.SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('JetValidation'))

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('jetValidationWithPf.root')
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

process.TAPAnalysisWP80 = cms.Path(
    process.kt6PFJetsForIsolation*
    process.kt6PFJets*
    process.ak5PFJets*
    process.pfNoPileUpSequence*
    process.pfAllNeutralHadrons*
    process.pfAllChargedHadrons*
    process.pfAllPhotons*
    process.pfElectronSequence*
    process.patTrigger*
    process.patDefaultSequence*
    process.eleTriggerMatchHLT*
    process.patElectronsWithTrigger*
    process.TAPwp80
    )

process.TAPAnalysisRECO = cms.Path(
    process.kt6PFJetsForIsolation*
    process.kt6PFJets*
    process.ak5PFJets*
    process.pfNoPileUpSequence*
    process.pfAllNeutralHadrons*
    process.pfAllChargedHadrons*
    process.pfAllPhotons*
    process.pfElectronSequence*
    process.patTrigger*
    process.patDefaultSequence*
    process.eleTriggerMatchHLT*
    process.patElectronsWithTrigger*
    process.TAPreco
    )

process.JetValidation = cms.Path(
    process.TotalEventCounter*
    process.kt6PFJetsForIsolation*
    #process.kt6PFJets*
#    #process.kt6PFJets*
    #process.ak5PFJets*
    process.pfNoPileUpSequence*
    process.pfAllNeutralHadrons*
    process.pfAllChargedHadrons*
    process.pfAllPhotons*
    process.pfElectronSequence*
    process.patTrigger*
    process.patDefaultSequence*
    process.eleTriggerMatchHLT*
    process.patElectronsWithTrigger*     
    process.demobefore*
    process.Selection*
    process.demo*
    process.goodEPair*
    process.ak5PFJets*
    process.validation*
    #process.ak5PFJetsL2L3*
    #process.validationL2L3*
    process.ak5PFJetsL1FastL2L3
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
