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

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
#process.load("MagneticField.Engine.uniformMagneticField_cfi") 
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

##-------------------- Import the Jet RECO modules -----------------------
process.load('RecoJets.Configuration.RecoPFJets_cff')
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

process.GlobalTag.globaltag = 'FT_R_44_V9::All'

####################
#### Files
###################

readFiles = cms.untracked.vstring()
readFiles.extend([
#"file:/gpfs/grid/srm/cms/store/data/Run2011A/DoubleElectron/RAW-RECO/ZElectron-08Nov2011-v1/0000/9213ACEA-B01B-E111-9BD9-002618943833.root"
   "file:/gpfs/grid/srm/cms/store/data/Run2011B/DoubleElectron/RAW-RECO/ZElectron-19Nov2011-v1/0000/08EABC25-971A-E111-9EDC-001D0967D625.root"
    ])

process.MessageLogger.cerr.FwkReport  = cms.untracked.PSet(
     reportEvery = cms.untracked.int32(500),
 )

process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(200) )

process.source = cms.Source("PoolSource",
                            fileNames = readFiles,
                            duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
                            )

####################
#### Trigger
###################

trigger2011v3 = cms.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v4","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v5","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9", "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10")



####################
#### TAP
###################

process.TAPgsftopf = cms.EDFilter('EfficiencyGSFtoPFfilter',
                               matchMC = cms.bool(False),
                               HLT_efficiency = cms.bool(False),
                               electronGSFCollection = cms.InputTag("gsfElectrons"),
                               electronTagHLTCollection = cms.InputTag("trgmatchGsfElectronsEle8"),
                               electronProbeHLTCollection = cms.InputTag("trgmatchGsfElectronsEle8"),
                               electronPFCollection  = cms.InputTag("patElectrons"),
                               triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
                               filename=cms.untracked.string("ZAnalysisFilter.root"),
                               UseCombinedPrescales = cms.bool(False),
                               isoValInputTags       = cms.VInputTag(cms.InputTag('elPFIsoValueCharged03PFIso'),
                                                                     cms.InputTag('elPFIsoValueGamma03PFIso'),
                                                                     cms.InputTag('elPFIsoValueNeutral03PFIso')),
                               VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                               electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
                               candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
                               JetCollectionLabel = cms.InputTag("ak5PFchsJetsRCL1FastL2L3Residual"),
                               TriggerNames = trigger2011v3
                               )

#process.TAPgsftopf_MC = process.TAPgsftopf.clone( matchMC = True )

process.TAPhltele8NOTele17 = process.TAPgsftopf.clone(HLT_efficiency = cms.bool(True),
                                                      electronTagHLTCollection = cms.InputTag("trgmatchGsfElectronsReco"),
                                                      electronProbeHLTCollection = cms.InputTag("trgmatchGsfElectronsEle8NOTEle17"),
                                                      )

#process.TAPhltele8NOTele17_MC = process.TAPhltele8NOTele17.clone( matchMC = True )

process.TAPhltele17 = process.TAPgsftopf.clone(HLT_efficiency = cms.bool(True),
                                                      electronTagHLTCollection = cms.InputTag("trgmatchGsfElectronsReco"),
                                                      electronProbeHLTCollection = cms.InputTag("trgmatchGsfElectronsEle17"),
                                                      )

#process.TAPhltele17_MC = process.TAPhltele17.clone( matchMC = True )

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
# Residual Correction Services
process.ak5PFchsResidual = ak5PFResidual.clone(algorithm = 'AK5PFchs' )
process.ak5PFchsL1FastL2L3Residual = cms.ESSource(
     'JetCorrectionServiceChain',
     correctors = cms.vstring('ak5PFchsL1Fastjet','ak5PFchsL2Relative','ak5PFchsL3Absolute','ak5PFchsResidual')
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
process.ak5PFJetsOLDL1FastL2L3Residual = process.ak5PFJetsL1FastL2L3Residual.clone(src = 'ak5PFJetsOLD')

process.ak5PFJetsRC = cms.EDProducer("FastjetJetProducer",
     PFJetParametersRC,
     AnomalousCellParameters,
     jetAlgorithm = cms.string("AntiKt"),
     rParam       = cms.double(0.5)
     )
process.ak5PFJetsRC.doAreaFastjet = True
process.ak5PFJetsRC.doRhoFastjet = False  # recipe 15th March JEC
process.ak5PFJetsRCL2L3Residual = process.ak5PFJetsL2L3Residual.clone(src = 'ak5PFJetsRC')
process.ak5PFchsJetsRCL1FastL2L3Residual = process.ak5PFJetsL1FastL2L3Residual.clone(src = 'ak5PFJetsRC', correctors = ['ak5PFchsL1FastL2L3Residual'])

process.ak5PFJetsPU = cms.EDProducer("FastjetJetProducer",
     PFJetParametersPU,
     AnomalousCellParameters,
     jetAlgorithm = cms.string("AntiKt"),
     rParam       = cms.double(0.5)
     )
process.ak5PFJetsPU.doAreaFastjet = True
process.ak5PFJetsPU.doRhoFastjet = False  # recipe 15th March JEC
process.ak5PFchsJetsPUL1FastL2L3Residual = process.ak5PFJetsL1FastL2L3Residual.clone(src = 'ak5PFJetsPU', correctors = ['ak5PFchsL1FastL2L3Residual'])

process.validationOldJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsL1FastL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       WeightName = cms.string('EventWeight'),
                                       WeightNameSherpa = cms.string('EventWeightSherpa'),                                          
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(False),
                                       usingPF = cms.untracked.bool(True),
                                       deltaRConeJet        = cms.double(0.3),
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
                                       RootuplaName = cms.string("treeOLDJEC_"),
                                       isElectron= cms.untracked.bool(True)  
                                       )
                                 
process.validationTESTJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsOLDL1FastL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       WeightName = cms.string('EventWeight'),
                                       WeightNameSherpa = cms.string('EventWeightSherpa'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(False),
                                       usingPF = cms.untracked.bool(True),
                                       deltaRConeJet        = cms.double(0.3),
                                       deltaRCone           = cms.double(0.3),
                                       deltaRConeGen        = cms.double(0.1),
                                       maxEtaJets           = cms.double(2.4),
                                       minPtJets            = cms.double(30.0),
                                       chargedEmEnergyFraction = cms.double(0.99),
                                       neutralHadronEnergyFraction= cms.double(0.99),
                                       neutralEmEnergyFraction= cms.double(0.99),
                                       chargedHadronEnergyFraction= cms.double(0.0),
                                       chargedMultiplicity= cms.int32(0),
                                      JECUncertainties= cms.double(0),
                                       RootuplaName = cms.string("treeTESTJEC_"),
                                       isElectron= cms.untracked.bool(True)   
                                       )
                                 
process.validationPUJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFchsJetsPUL1FastL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       WeightName = cms.string('EventWeight'),
                                       WeightNameSherpa = cms.string('EventWeightSherpa'),                                         
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(False),
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
                                       RootuplaName = cms.string("treePUJEC_"),
                                       isElectron= cms.untracked.bool(True)   
                                       )


process.validationJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFchsJetsRCL1FastL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       WeightName = cms.string('EventWeight'),
                                       WeightNameSherpa = cms.string('EventWeightSherpa'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(False),
                                       usingPF = cms.untracked.bool(True),
                                       #deltaRConeJet           = cms.double(0.3),
                                       #deltaRCone           = cms.double(0.3),
                                       deltaRConeJet           = cms.double(-1),
                                       deltaRCone           = cms.double(-1),
                                       deltaRConeGen         = cms.double(0.1),
                                       maxEtaJets           = cms.double(2.4),
                                       minPtJets            = cms.double(30.0),
                                       chargedEmEnergyFraction = cms.double(0.99),
                                       neutralHadronEnergyFraction= cms.double(0.99),
                                       neutralEmEnergyFraction= cms.double(0.99),
                                       chargedHadronEnergyFraction= cms.double(0.0),
                                       chargedMultiplicity= cms.int32(0),
                                      JECUncertainties= cms.double(0), 
                                       RootuplaName = cms.string("treeValidationJEC_"),
                                       isElectron= cms.untracked.bool(True)  
                                       )
                                   
process.validationL2L3Residual = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       WeightName = cms.string('EventWeight'),
                                                WeightNameSherpa = cms.string('EventWeightSherpa'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(False),
                                       usingPF = cms.untracked.bool(True),
                                       deltaRConeJet          = cms.double(0.3),
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
                                       RootuplaName = cms.string("treeL2L3_"),
                                       isElectron= cms.untracked.bool(True)                                               
                                       )

process.validationPU = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFJetsPU"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    WeightName = cms.string('EventWeight'),
                                      WeightNameSherpa = cms.string('EventWeightSherpa'),
                                    genJets = cms.InputTag("ak5GenJets"),
                                    usingMC = cms.untracked.bool(False),
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
                                       RootuplaName = cms.string("treePU_"),
                                       isElectron= cms.untracked.bool(True)                                   
                                    )


process.validationRC = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFJetsRC"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    WeightName = cms.string('EventWeight'),
                                      WeightNameSherpa = cms.string('EventWeightSherpa'),
                                    genJets = cms.InputTag("ak5GenJets"),
                                    usingMC = cms.untracked.bool(False),
                                    usingPF = cms.untracked.bool(True),
                                    #deltaRConeJet           = cms.double(0.3),
                                    #deltaRCone           = cms.double(0.3),
                                    deltaRConeJet           = cms.double(-1),
                                    deltaRCone           = cms.double(-1),
                                    deltaRConeGen         = cms.double(0.1),
                                    maxEtaJets           = cms.double(2.4),
                                    minPtJets            = cms.double(30.0),
                                    chargedEmEnergyFraction = cms.double(0.99),
                                    neutralHadronEnergyFraction= cms.double(0.99),
                                    neutralEmEnergyFraction= cms.double(0.99),
                                    chargedHadronEnergyFraction= cms.double(0.0),
                                    chargedMultiplicity= cms.int32(0),
                                      JECUncertainties= cms.double(0), 
                                       RootuplaName = cms.string("treeRC_"),
                                       isElectron= cms.untracked.bool(True)                                     
                                    )


process.validationJECScaleUp = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFchsJetsRCL1FastL2L3Residual"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    WeightName = cms.string('EventWeight'),
                                              WeightNameSherpa = cms.string('EventWeightSherpa'),
                                    genJets = cms.InputTag("ak5GenJets"),
                                    usingMC = cms.untracked.bool(False),
                                    usingPF = cms.untracked.bool(True),
                                    #deltaRConeJet           = cms.double(0.3),
                                    #deltaRCone           = cms.double(0.3),
                                    deltaRConeJet           = cms.double(-1),
                                    deltaRCone           = cms.double(-1),
                                    deltaRConeGen         = cms.double(0.1),
                                    maxEtaJets           = cms.double(2.4),
                                    minPtJets            = cms.double(30.0),
                                    chargedEmEnergyFraction = cms.double(0.99),
                                    neutralHadronEnergyFraction= cms.double(0.99),
                                    neutralEmEnergyFraction= cms.double(0.99),
                                    chargedHadronEnergyFraction= cms.double(0.0),
                                    chargedMultiplicity= cms.int32(0),
                                      JECUncertainties= cms.double(1), 
                                       RootuplaName = cms.string("treeJECScaleUp_"),
                                       isElectron= cms.untracked.bool(True) 
                                    )

process.validationJECScaleDown = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFchsJetsRCL1FastL2L3Residual"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    WeightName = cms.string('EventWeight'),
                                                WeightNameSherpa = cms.string('EventWeightSherpa'),
                                    genJets = cms.InputTag("ak5GenJets"),
                                    usingMC = cms.untracked.bool(False),
                                    usingPF = cms.untracked.bool(True),
                                    #deltaRConeJet           = cms.double(0.3),
                                    #deltaRCone           = cms.double(0.3),
                                    deltaRConeJet           = cms.double(-1),
                                    deltaRCone           = cms.double(-1),
                                    deltaRConeGen         = cms.double(0.1),
                                    maxEtaJets           = cms.double(2.4),
                                    minPtJets            = cms.double(30.0),
                                    chargedEmEnergyFraction = cms.double(0.99),
                                    neutralHadronEnergyFraction= cms.double(0.99),
                                    neutralEmEnergyFraction= cms.double(0.99),
                                    chargedHadronEnergyFraction= cms.double(0.0),
                                    chargedMultiplicity= cms.int32(0),
                                      JECUncertainties= cms.double(-1),
                                       RootuplaName = cms.string("treeJECScaleDown_"),
                                       isElectron= cms.untracked.bool(True) 
                                    )
                                  
process.reclusValidation = cms.EDAnalyzer('reclusVal',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsL1FastL2L3Residual"),
                                       jetCollectionPU = cms.InputTag("ak5PFchsJetsPUL1FastL2L3Residual"),
                                       jetCollectionRC = cms.InputTag("ak5PFchsJetsRCL1FastL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       tpMapName = cms.string('EventWeight'),
                                       genJets = cms.InputTag("ak5GenJets"),
                                       usingMC = cms.untracked.bool(False),
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

process.demo = cms.EDProducer('HistoAnalyzer',
                              particleCollection = cms.InputTag('pfNoPileUp'),
                              electronCollection = cms.InputTag('patElectronsWithTrigger'),# Change it, sooner or later...
                              triggerCollection = cms.InputTag("TriggerResults","","HLT"),
                              UseCombinedPrescales = cms.bool(False),
                              #TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB, 
                              TriggerNames = trigger2011v3,
                              removePU=  cms.bool(True),
                              usingMC=  cms.bool(False),
                              conversionsInputTag   = cms.InputTag("allConversions"),
                              beamSpotInputTag      = cms.InputTag("offlineBeamSpot"),
                              primaryVertexInputTag = cms.InputTag("offlinePrimaryVertices"),
                              isoValInputTags       = cms.VInputTag(cms.InputTag('elPFIsoValueCharged03PFIso'),
                                                                    cms.InputTag('elPFIsoValueGamma03PFIso'),
                                                                    cms.InputTag('elPFIsoValueNeutral03PFIso')),
                              doTheHLTAnalysis = cms.bool(True),
                              VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                              TotalNEventTag = cms.vstring('TotalEventCounter'),
                              WhichRun = cms.string("Run2011AB"), ##UNESSENTIAL FOR DATA:Select which datasets you wonna use to reweight..
                              eventWeightsCollection= cms.string("EventWeight"),
                              giveEventWeightEqualToOne= cms.bool(False),
                              RootuplaName = cms.string("treeVJ_")
)

process.demobefore = cms.EDProducer('HistoAnalyzer',
                                    particleCollection = cms.InputTag('pfNoPileUp'),
                                    electronCollection = cms.InputTag('patElectronsWithTrigger'),# Change it, sooner or later...
                                    triggerCollection = cms.InputTag("TriggerResults","","HLT"),
                                    UseCombinedPrescales = cms.bool(False),
                                    #TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB,
                                    TriggerNames = trigger2011v3,
                                    removePU=  cms.bool(True),
                                    usingMC=  cms.bool(False),
                                    conversionsInputTag   = cms.InputTag("allConversions"),
                                    beamSpotInputTag      = cms.InputTag("offlineBeamSpot"),
                                    primaryVertexInputTag = cms.InputTag("offlinePrimaryVertices"),
                                    isoValInputTags       = cms.VInputTag(cms.InputTag('elPFIsoValueCharged03PFIso'),
                                                                          cms.InputTag('elPFIsoValueGamma03PFIso'),
                                                                          cms.InputTag('elPFIsoValueNeutral03PFIso')),
                                    doTheHLTAnalysis = cms.bool(True),
                                    VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                                    TotalNEventTag = cms.vstring('TotalEventCounter'),
                                    WhichRun = cms.string("Run2011AB"), ##UNESSENTIAL FOR DATA:Select which datasets you wonna use to reweight..
                                    eventWeightsCollection= cms.string("EventWeight"),
                                    giveEventWeightEqualToOne= cms.bool(False),
                                    RootuplaName = cms.string("treeVJBefore_"),
                                    )


####################
#### Lepton Selection
###################

process.Selection = cms.EDFilter('ZpatFilter2011',
                                 electronCollection = cms.InputTag("patElectronsWithTrigger"),
                                 triggerCollectionTag = cms.InputTag("TriggerResults","","HLT"),
                                 UseCombinedPrescales = cms.bool(False),
                                 doTheHLTAnalysis = cms.bool(True),
                                 useNewID=  cms.bool(False),
                                 doWP90 =  cms.untracked.bool(True),
                                 #TriggerNames = triggersMay10Jul05+triggersAug05+triggersOct03+trigger2011RunB,
                                 TriggerNames = trigger2011v3,
                                 secondEleEnThrhold    = cms.double(20.0),
                                 firstEleEnThrhold     = cms.double(20.0),
                                 lowZmassLimit         = cms.double(71.0),
                                 highZmassLimit        = cms.double(111.0),
                                 maxEtaForElectron     = cms.double(2.4),                               
                                 conversionsInputTag   = cms.InputTag("allConversions"),
                                 beamSpotInputTag      = cms.InputTag("offlineBeamSpot"),
                                 primaryVertexInputTag = cms.InputTag("offlinePrimaryVertices"),
                                 isoValInputTags       = cms.VInputTag(cms.InputTag('elPFIsoValueCharged03PFIso'),
                                                                       cms.InputTag('elPFIsoValueGamma03PFIso'),
                                                                       cms.InputTag('elPFIsoValueNeutral03PFIso')),
                                 )



process.goodEPair = cms.EDProducer('goodEPairProducer2011',
                                   electronCollection = cms.InputTag("patElectronsWithTrigger"),
                                   pflowEleCollection = cms.untracked.InputTag("pfIsolatedElectrons"),
                                   pflowMuCollection = cms.untracked.InputTag("pfIsolatedMuons"), 
                                   useNewID=  cms.bool(False),
                                   doWP90 =  cms.untracked.bool(True),
                                   secondEleEnThrhold   = cms.double(20.0),
                                   firstEleEnThrhold    = cms.double(20.0),
                                   lowZmassLimit        = cms.double(71.0),
                                   highZmassLimit       = cms.double(111.0),
                                   maxEtaForElectron    = cms.double(2.4),                             
                                   conversionsInputTag   = cms.InputTag("allConversions"),
                                   beamSpotInputTag      = cms.InputTag("offlineBeamSpot"),
                                   primaryVertexInputTag = cms.InputTag("offlinePrimaryVertices"),
                                   isoValInputTags       = cms.VInputTag(cms.InputTag('elPFIsoValueCharged03PFIso'),
                                                                         cms.InputTag('elPFIsoValueGamma03PFIso'),
                                                                         cms.InputTag('elPFIsoValueNeutral03PFIso')),
                                   ZmumuCandidates = cms.untracked.InputTag("matchedMuons"),
                                   isElectron= cms.untracked.bool(True)
                                   )

process.goodElec = cms.EDProducer('goodEleProducer2011',
                                  electronCollection = cms.InputTag("patElectronsWithTrigger"),
                                  pflowEleCollection = cms.untracked.InputTag("pfIsolatedElectrons"),
                                  useNewID=  cms.bool(False),  
                                  doWP90 =  cms.untracked.bool(True),                           
                                  conversionsInputTag   = cms.InputTag("allConversions"),
                                  beamSpotInputTag      = cms.InputTag("offlineBeamSpot"),
                                  primaryVertexInputTag = cms.InputTag("offlinePrimaryVertices"),
                                  isoValInputTags       = cms.VInputTag(cms.InputTag('elPFIsoValueCharged03PFIso'),
                                                                        cms.InputTag('elPFIsoValueGamma03PFIso'),
                                                                        cms.InputTag('elPFIsoValueNeutral03PFIso')),
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

###########################
###   ISOLATION
###########################
from CommonTools.ParticleFlow.Tools.pfIsolation import setupPFElectronIso
process.eleIsoSequence = setupPFElectronIso(process, 'gsfElectrons')
process.pfIsolatedElectrons.isolationCut = 999 ### VERY loose, true isolation done later, exploiting deposits...

#from CommonTools.ParticleFlow.Tools.pfIsolation import setupPFMuonIso
#process.muIsoSequence = setupPFMuonIso(process, 'muons')

###########################
### Electron Removal
###########################
process.pfNoElectron.bottomCollection = cms.InputTag("pfNoPileUp")
#process.pfNoElectron.topCollection = cms.InputTag("goodEPair")   #remove only the two electron candidates
process.pfNoElectron.topCollection = cms.InputTag("goodElec")   #remove all the electron passing the selections

######################
#                    #
#  TRG MATCHING -ON- #
#                    #
######################


##################################
### Standard trigger matching: ###
##################################

process.eleTriggerMatchHLT = cms.EDProducer( "PATTriggerMatcherDRLessByR",
                                             #src     = cms.InputTag( "selectedPatElectrons" ), #common cfg
                                             src     = cms.InputTag( "patElectrons" ),
                                             matched = cms.InputTag( "patTrigger"),
                                             matchedCuts = cms.string('(path("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v*",0,0) && filter("hltEle17CaloIdIsoEle8CaloIdIsoPixelMatchDoubleFilter")) || (path("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*",0,0) && filter("hltEle17TightIdLooseIsoEle8TightIdLooseIsoTrackIsolDoubleFilter"))'),
                                             maxDPtRel = cms.double( 5 ),
                                             maxDeltaR = cms.double( 0.3 ),
                                             resolveAmbiguities    = cms.bool( True ),
                                             resolveByMatchQuality = cms.bool( True )
                                             )

process.patElectronsWithTrigger = cms.EDProducer("PATTriggerMatchElectronEmbedder",
                                                 #src     = cms.InputTag("selectedPatElectrons"),  #common cfg
                                                    src     = cms.InputTag("patElectrons"),
                                                    matches = cms.VInputTag(cms.InputTag('eleTriggerMatchHLT'))
                                                 )

switchOnTriggerMatching( process, ['eleTriggerMatchHLT' ],sequence ='patDefaultSequence', hltProcess = '*' )

#####################################################
### Trigger matching without EMBEDDING into PATs: ###
#####################################################

HLTProcessName = "HLT"

### ELECTRON trigger matching:
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

process.trgmatchGsfElectronsEle8 = cms.EDProducer("trgMatchedGsfElectronProducer",
                                        InputProducer = cms.InputTag("gsfElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        hltTags = hltTagsForEle8,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchGsfElectronsEle17 = cms.EDProducer("trgMatchedGsfElectronProducer",
                                        InputProducer = cms.InputTag("gsfElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        hltTags = hltTagsForEle17,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchGsfElectronsNOTEle17 = cms.EDProducer("trgMatchedGsfElectronProducer",
                                        InputProducer = cms.InputTag("gsfElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        antiSelect = cms.untracked.bool(True),
                                        hltTags = hltTagsForEle17,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchGsfElectronsEle8NOTEle17 = cms.EDProducer("trgMatchedGsfElectronProducer",
                                        InputProducer = cms.InputTag("trgmatchGsfElectronsNOTEle17"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        hltTags = hltTagsForEle8,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

HLTeleRecoPath1  = "HLT_Ele32_CaloIdL_CaloIsoVL_SC17_v1"
HLTeleRecoPath2  = "HLT_Ele32_CaloIdL_CaloIsoVL_SC17_v2"
HLTeleRecoPath3  = "HLT_Ele32_CaloIdL_CaloIsoVL_SC17_v3"
HLTeleRecoPath4  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v1"
HLTeleRecoPath5  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v2"
HLTeleRecoPath6  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v3"
HLTeleRecoPath7  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v4"
HLTeleRecoPath8  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v5"
HLTeleRecoPath9  = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v6"
HLTeleRecoPath10 = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v7"
HLTeleRecoPath11 = "HLT_Ele32_CaloIdT_CaloIsoT_TrkIdT_TrkIsoT_SC17_v8"
HLTeleRecoFilter  = "hltEle32CaloIdLCaloIsoVLSC17PixelMatchFilter"
HLTeleRecoFilterH = "hltEle32CaloIdTCaloIsoTTrkIdTTrkIsoTSC17TrackIsolFilter"

hltTagsForEleReco = cms.VInputTag(
    cms.InputTag(HLTeleRecoPath1,  HLTeleRecoFilter , HLTProcessName),
    cms.InputTag(HLTeleRecoPath2,  HLTeleRecoFilter , HLTProcessName),
    cms.InputTag(HLTeleRecoPath3,  HLTeleRecoFilter , HLTProcessName),
    cms.InputTag(HLTeleRecoPath4,  HLTeleRecoFilterH , HLTProcessName),
    cms.InputTag(HLTeleRecoPath5,  HLTeleRecoFilterH , HLTProcessName),
    cms.InputTag(HLTeleRecoPath6,  HLTeleRecoFilterH , HLTProcessName),
    cms.InputTag(HLTeleRecoPath7,  HLTeleRecoFilterH , HLTProcessName),
    cms.InputTag(HLTeleRecoPath8,  HLTeleRecoFilterH , HLTProcessName),
    cms.InputTag(HLTeleRecoPath9,  HLTeleRecoFilterH , HLTProcessName),
    cms.InputTag(HLTeleRecoPath10, HLTeleRecoFilterH , HLTProcessName),
    cms.InputTag(HLTeleRecoPath11, HLTeleRecoFilterH , HLTProcessName),
    )

process.trgmatchGsfElectronsReco = cms.EDProducer("trgMatchedGsfElectronProducer",
                                        InputProducer = cms.InputTag("gsfElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        matchUnprescaledTriggerOnly = cms.untracked.bool(False),
                                        hltTags = hltTagsForEleReco,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

#####################
#                   #
#      OUTPUT       #
#                   #
#####################


process.out.fileName = cms.untracked.string('test-filtering.root')
process.out.outputCommands =  cms.untracked.vstring(
    'keep *_*_*_PAT',
    )
process.out.outputCommands.extend(['keep *'
    #'keep *_offlinePrimaryVertices*_*_*',
    #'keep *_pat*METs*_*_*',
    #'keep *_patTriggerEvent_*_*',
    #'keep patTriggerPaths_patTrigger_*_*',
    #'keep *_*Tracks_*_*',
    #'keep *_*_*_PAT',
    #'keep *_zmumurec*_*_*',
    #'keep *_selectedMuons_*_*'
    ])
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

process.ToolInizialization = cms.Path(
    process.kt6PFJetsForIsolation*
    process.kt6PFJets*
    process.ak5PFJets*
    process.ak5PFJetsL1FastL2L3Residual*
    process.goodOfflinePrimaryVertices*
    process.pfNoPileUpSequence*
    process.pfParticleSelectionSequence*
    process.eleIsoSequence*
    process.pfElectronSequence*
    process.patTrigger*
    process.patDefaultSequence*
    process.eleTriggerMatchHLT*
    process.patElectronsWithTrigger*
    process.goodElec*
    process.pfNoElectron*
    process.ak5PFJetsRC*
    process.ak5PFchsJetsRCL1FastL2L3Residual
    )

process.TAPAnalysisGSFtoPF = cms.Path(
        process.goodOfflinePrimaryVertices*
        process.trgmatchGsfElectronsEle8*
        process.TAPgsftopf
        )

process.TAPAnalysisHLTele8NOTele17 = cms.Path(
        process.goodOfflinePrimaryVertices*
        process.trgmatchGsfElectronsReco*
        process.trgmatchGsfElectronsNOTEle17*
        process.trgmatchGsfElectronsEle8NOTEle17*
        process.TAPhltele8NOTele17
        )

process.TAPAnalysisHLTele17 = cms.Path(
        process.goodOfflinePrimaryVertices*
        process.trgmatchGsfElectronsReco*
        process.trgmatchGsfElectronsEle17*
        process.TAPhltele17
        )

#process.JetValidation = cms.Path(
#    process.TotalEventCounter*
#    process.eleTriggerMatchHLT*
#    process.patElectronsWithTrigger*  
#    process.demobefore*   
#    process.goodOfflinePrimaryVertices*
#    process.Selection*
#    process.goodEPair*
#    process.demo*
#    #process.reclusValidation*
#    #process.validationOldJEC*
#    #process.validationPUJEC*
#    #process.validationPU*
#    #process.validationRC*
#    #process.validationJECScaleUp*
#    #process.validationJECScaleDown* 
#    #process.validationTESTJEC*
#    process.validationJEC
#    )

#####################
#                   #
#    Outpath        #
#                   #
#####################

process.outpath = cms.EndPath(
#    process.out
    )
