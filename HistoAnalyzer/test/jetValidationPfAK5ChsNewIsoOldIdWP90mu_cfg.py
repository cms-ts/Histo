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
                                     SkipEvent = cms.untracked.vstring('MismatchedInputFiles')
                                     )


process.GlobalTag.globaltag = 'FT_R_44_V9::All'

####################
#### Files
###################

readFiles = cms.untracked.vstring()
readFiles.extend([
    #"file:/gpfs/grid/srm/cms/store/data/Run2011A/DoubleElectron/RAW-RECO/ZElectron-08Nov2011-v1/0000/9213ACEA-B01B-E111-9BD9-002618943833.root"
    "file:/gpfs/grid/srm/cms/store/data/Run2011A/DoubleMu/RAW-RECO/ZMu-08Nov2011-v1/0000/4031F103-2D1B-E111-86DC-003048FFCBF0.root"
    #"file:/gpfs/grid/srm/cms/store/data/Run2011B/DoubleMu/RAW-RECO/ZMu-19Nov2011-v1/0000/784E3411-FD1D-E111-92C6-003048D15E24.root"
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

triggerall= cms.vstring() # In this way, the HLT string is empty and it will trigger every event

trigger2011v3 = cms.vstring("HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v1","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v2","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v3","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v4","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v5","HLT_Ele17_CaloIdL_CaloIsoVL_Ele8_CaloIdL_CaloIsoVL_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v6","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v7","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v8","HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v9", "HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v10")

####################
#### Muons... ARGH!!!
###################

### create the particle-based isolation values for gsfElectrons and muons
from CommonTools.ParticleFlow.Tools.pfIsolation import setupPFMuonIso
process.muIsoSequence = setupPFMuonIso(process, 'muons')

# crappy muon collection for RECO efficiency measurement:
from RecoMuon.MuonIdentification.calomuons_cfi import calomuons;
process.crapMuons = cms.EDProducer("CaloMuonMerger",
                                   muons     = cms.InputTag("muons"),
                                   caloMuons = cms.InputTag("calomuons"),
                                   minCaloCompatibility = calomuons.minCaloCompatibility
                                   )

process.patMuons.pfMuonSource = cms.InputTag("pfMuons")
process.patMuons.useParticleFlow=True


######################
#### VERTEX FILTER ###
######################

from RecoVertex.PrimaryVertexProducer.OfflinePrimaryVertices_cfi import *
process.goodPV= offlinePrimaryVertices.clone()
process.goodPV.cut=cms.string('ndof > 4&'
                              'abs(z) <24&'
                              '!isFake &'
                              ' position.Rho <2 '
                              )

###################################################

#################################
#### MUON Trigger matching ######
#################################

pathTriggerMu = 'path("HLT_DoubleMu6_v*",0,0) || path("HLT_DoubleMu7_v*",0,0) || path("HLT_Mu13_Mu8_v*",0,1) || path("HLT_Mu17_Mu8_v*",0,1)'

process.muonTriggerMatchHLTMuons = cms.EDProducer("PATTriggerMatcherDRLessByR",
                                                  src     = cms.InputTag( 'selectedPatMuons' ) ,
                                                  matched = cms.InputTag( 'patTrigger' ),    # selections of trigger objects ,
                                                  matchedCuts = cms.string( pathTriggerMu ),    # selection of matches ,
                                                  maxDPtRel   = cms.double( 0.5 ), 
                                                  maxDeltaR   = cms.double( 0.3 ) ,
                                                  resolveAmbiguities    = cms.bool( True ) ,
                                                  resolveByMatchQuality = cms.bool( True )
                                                  )

switchOnTriggerMatchEmbedding(process ,triggerMatchers = ['muonTriggerMatchHLTMuons'],)
#Switch to selected PAT objects in the trigger matching removeCleaningFromTriggerMatching( process )
#match the trigger object to the reconstructed muon (no cuts on id iso...) 
from CommonTools.ParticleFlow.ParticleSelectors.pfSelectedMuons_cfi import pfSelectedMuons 
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *                       
process.muonTriggerMatchHLTMuons.src = cms.InputTag( 'selectedMuonsWithIsolationData' )
process.selectedPatMuonsTriggerMatch.src = cms.InputTag( 'selectedMuonsWithIsolationData' )
process.selectedPatMuonsTriggerMatch.matches = cms.VInputTag('muonTriggerMatchHLTMuons')

removeCleaningFromTriggerMatching(process)


### Our muon collections: all, tight, matched
process.allMuons = selectedPatMuons.clone(
    src = cms.InputTag('selectedPatMuonsTriggerMatch'),
    cut = cms.string("pt>20  & abs(eta) < 2.4")    
    )

process.tightMuons = selectedPatMuons.clone(
   src = cms.InputTag('selectedPatMuonsTriggerMatch'),
   cut = cms.string('isGlobalMuon & isTrackerMuon &'
                    'innerTrack.hitPattern.trackerLayersWithMeasurement>8 &'  ## new requirement in 44X due to changes in tracking
                    'userFloat("RelativePFIsolationDBetaCorr") < 0.2 &' # PF isolation
                    'abs(dB) < 0.02 &' 
                    'normChi2 < 10 &'
                    'innerTrack.hitPattern.numberOfValidPixelHits > 0 &'
                    'numberOfMatchedStations>1 &'                                 
                    'globalTrack.hitPattern.numberOfValidMuonHits > 0 &'
                    'pt>20 &'
                    'abs(eta) < 2.4')
   )

process.matchedMuons = selectedPatMuons.clone(
    src = cms.InputTag('selectedPatMuonsTriggerMatch'),
    cut = cms.string('isGlobalMuon & isTrackerMuon &'
                     'innerTrack.hitPattern.trackerLayersWithMeasurement>8 &'  ## new requirement in 44X due to changes in tracking
                     'userFloat("RelativePFIsolationDBetaCorr") < 0.2 &' # PF isolation   
                     'abs(dB) < 0.02 &' 
                     'normChi2 < 10 &'
                     'innerTrack.hitPattern.numberOfValidPixelHits > 0 &'
                     'numberOfMatchedStations>1 &'                                   # segments matched in at least two muon stations 
                     'globalTrack.hitPattern.numberOfValidMuonHits > 0 &'    # one muon hit matched to the global fit
                     'pt>20 &'
                     'abs(eta) < 2.4 &'
                     #'(trackIso+caloIso)/pt < 0.15 &'                       # Z+jet choice
                     #' trackIso < 3 &'                                      # VBTF choice
                     'triggerObjectMatches.size > 0')
    )


#################################
### Z muon candidates ###########
#################################

process.zmuAllmuAll = cms.EDProducer('CandViewShallowCloneCombiner',
                                  decay = cms.string('allMuons@+ allMuons@-'),
                                  cut   = cms.string('mass > 71.0 & mass < 111.0'),
                                  name  = cms.string('Zmuallmuall'),
                                  roles = cms.vstring('all1', 'all2')
                                  )

process.zmuTightmuTight = cms.EDProducer('CandViewShallowCloneCombiner',
                                  decay = cms.string('tightMuons@+ tightMuons@-'),
                                  cut   = cms.string('mass > 71.0 & mass < 111.0'),
                                  name  = cms.string('Zmutightmutight'),
                                  roles = cms.vstring('tight1', 'tight2')
                                  )

process.zmuMatchedmuMatched = cms.EDProducer('CandViewShallowCloneCombiner',
                                  decay = cms.string('matchedMuons@+ matchedMuons@-'),
                                  cut   = cms.string('mass > 71.0 & mass < 111.0'),
                                  name  = cms.string('Zmumatchedmumatched'),
                                  roles = cms.vstring('matched1', 'matched2')
                                  )


process.pfIsolatedMuons.isolationCut = 0.5 ## very loose, true isolation done later, exploiting deposits...
## default cone is 0.4, as recommended at: https://twiki.cern.ch/twiki/bin/view/CMS/TWikiSMP-MUO#MuORecommendations

#embedding objects
process.patMuons.embedCombinedMuon = cms.bool(True)
process.patMuons.embedStandAloneMuon = cms.bool(False)
process.patMuons.embedPickyMuon = cms.bool(False)
process.patMuons.embedTpfmsMuon = cms.bool(False)
process.patMuons.embedPFCandidate = cms.bool(True)  # embedding of track info process.patMuons.embedTrack = cms.bool(True)

### Muons with isolation data embedded
process.selectedMuonsWithIsolationData = cms.EDProducer(
   "MuonIsolationEmbedder",
   src = cms.InputTag("selectedPatMuons"),
   rho = cms.InputTag("kt6PFJetsForIsolation:rho")
)



####################
#### TAP
###################

### Observable dependent efficiency: ###

# Electrons:

#process.TAPeleWp80 = cms.EDFilter('EfficiencyFilter',
#                              matchMC = cms.bool(False),
#                              muonEfficiency = cms.bool(False),
#                              electronCollection = cms.InputTag("patElectrons"),
#                              TagHLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle17"),
#                              ProbeHLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle8"),
#                              muonCollection = cms.InputTag("allMuons"),
#                              tightMuonCollection = cms.InputTag("tightMuons"),
#                              TagHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsTight"),
#                              ProbeHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsLoose"),
#                              superClusterCollection_EB = cms.InputTag("correctedHybridSuperClusters"),
#                              superClusterCollection_EE = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
#                              caloMuonCollection = cms.InputTag("muons"),
#                              triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
#                              filename=cms.untracked.string("ZAnalysisFilter.root"),
#                              UseCombinedPrescales = cms.bool(False),
#                              removePU=  cms.bool(False),
#                              WP80_efficiency  =  cms.bool(True),
#                              HLTele17_efficiency  =  cms.bool(False),
#                              HLTele8_efficiency  =  cms.bool(False),
#                              RECO_efficiency  =  cms.bool(False),
#                              isoValInputTags       = cms.VInputTag(cms.InputTag('elPFIsoValueCharged03PFIso'),
#                                                                    cms.InputTag('elPFIsoValueGamma03PFIso'),
#                                                                    cms.InputTag('elPFIsoValueNeutral03PFIso')),
#                              VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
#                              electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
#                              candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
#                              JetCollectionLabel = cms.InputTag("ak5PFchsJetsRCL1FastL2L3Residual"),
#                              TriggerNames = trigger2011v3
#                              )
#
#process.TAPmuoWp80 = process.TAPeleWp80.clone(muonEfficiency = cms.bool(True))
#
#process.TAPhltele8NOTele17 = process.TAPeleWp80.clone(TagHLTelectronCollection = cms.InputTag("trgmatchPatElectronsReco"),
#                                                      ProbeHLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle8NOTEle17"),
#                                                      TagHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsTight"),
#                                                      ProbeHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsLooseNOTtight"),
#                                                      WP80_efficiency  =  cms.bool(False),
#                                                      HLTele17_efficiency  =  cms.bool(False),
#                                                      HLTele8_efficiency  =  cms.bool(True),
#                                                      RECO_efficiency  =  cms.bool(False),
#                                                      )
#
#process.TAPhltmuoLooseNOTtight = process.TAPhltele8NOTele17.clone(muonEfficiency = cms.bool(True))
#
#process.TAPhltele17 = process.TAPeleWp80.clone(TagHLTelectronCollection = cms.InputTag("trgmatchPatElectronsReco"),
#                                               ProbeHLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle17"),
#                                               TagHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsTight"),
#                                               ProbeHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsTight"),
#                                               WP80_efficiency  =  cms.bool(False),
#                                               HLTele17_efficiency  =  cms.bool(True),
#                                               HLTele8_efficiency  =  cms.bool(False),
#                                               RECO_efficiency  =  cms.bool(False),
#                                               )
#
#process.TAPhltmuoTight = process.TAPhltele17.clone(muonEfficiency = cms.bool(True))
#
#process.TAPeleReco = process.TAPeleWp80.clone(TagHLTelectronCollection = cms.InputTag("trgmatchPatElectronsReco"),
#                                          ProbeHLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle8"),
#                                          ProbeHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsLoose"),
#                                          WP80_efficiency  =  cms.bool(False),
#                                          HLTele17_efficiency  =  cms.bool(False),
#                                          HLTele8_efficiency  =  cms.bool(False),
#                                          RECO_efficiency  =  cms.bool(True),
#                                          )
#
#process.TAPmuoReco = process.TAPeleReco.clone(muonEfficiency = cms.bool(True))

### ETA-PT efficiency: ###

process.EPTeleWp80 = cms.EDFilter('EfficiencyPtEtaFilter',
                               matchMC = cms.bool(False),
                               muonEfficiency = cms.bool(False),
                               electronCollection = cms.InputTag("patElectrons"),
                               TagHLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle17"),
                               ProbeHLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle8"),
                               muonCollection = cms.InputTag("allMuons"),                                  
                               tightMuonCollection = cms.InputTag("tightMuons"),
                               TagHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsTight"),
                               ProbeHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsLoose"),
                               superClusterCollection_EB = cms.InputTag("correctedHybridSuperClusters"),
                               superClusterCollection_EE = cms.InputTag("correctedMulti5x5SuperClustersWithPreshower"),
                               caloMuonCollection = cms.InputTag("generalTracks"),
                               triggerCollectionTag = cms.untracked.InputTag("TriggerResults","","HLT"),
                               filename=cms.untracked.string("ZAnalysisFilter.root"),
                               UseCombinedPrescales = cms.bool(False),
                               removePU=  cms.bool(False),
                               WP80_efficiency  =  cms.bool(True),
                               HLTele17_efficiency  =  cms.bool(False),
                               HLTele8_efficiency  =  cms.bool(False),
                               RECO_efficiency  =  cms.bool(False),
                               isoValInputTags       = cms.VInputTag(cms.InputTag('elPFIsoValueCharged03PFIso'),
                                                                     cms.InputTag('elPFIsoValueGamma03PFIso'),
                                                                     cms.InputTag('elPFIsoValueNeutral03PFIso')),
                               VertexCollectionTag = cms.InputTag('offlinePrimaryVertices'),
                               electronIsolatedProducer= cms.InputTag( "hltPixelMatchElectronsL1Iso" ),
                               candTag= cms.InputTag("hltL1NonIsoHLTNonIsoSingleElectronEt15LTIPixelMatchFilter"),
                               JetCollectionLabel = cms.InputTag("ak5PFchsJetsRCL1FastL2L3Residual"),
                               TriggerNames = trigger2011v3
                               )

process.EPTmuoWp80 = process.EPTeleWp80.clone(muonEfficiency = cms.bool(True))

process.EPThltele8NOTele17 = process.EPTeleWp80.clone(TagHLTelectronCollection = cms.InputTag("trgmatchPatElectronsReco"),                                          
                                                  ProbeHLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle8NOTEle17"),                                  
                                                  TagHLTmuonCollection = cms.InputTag("trgmatchSingleMuons"),
                                                  ProbeHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsLooseNOTtight"),
                                                  WP80_efficiency  =  cms.bool(False),
                                                  HLTele17_efficiency  =  cms.bool(False),
                                                  HLTele8_efficiency  =  cms.bool(True),
                                                  RECO_efficiency  =  cms.bool(False),
                                                  )

process.EPThltmuoLooseNOTtight = process.EPThltele8NOTele17.clone(muonEfficiency = cms.bool(True))

process.EPThltele17 = process.EPTeleWp80.clone(TagHLTelectronCollection = cms.InputTag("trgmatchPatElectronsReco"),                                   
                                           ProbeHLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle17"),                                   
                                           TagHLTmuonCollection = cms.InputTag("trgmatchSingleMuons"),
                                           ProbeHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsTight"),
                                           WP80_efficiency  =  cms.bool(False),
                                           HLTele17_efficiency  =  cms.bool(True),
                                           HLTele8_efficiency  =  cms.bool(False),
                                           RECO_efficiency  =  cms.bool(False),
                                           )

process.EPThltmuoTight = process.EPThltele17.clone(muonEfficiency = cms.bool(True))

process.EPTeleReco = process.EPTeleWp80.clone(TagHLTelectronCollection = cms.InputTag("trgmatchPatElectronsReco"),
                                       ProbeHLTelectronCollection = cms.InputTag("trgmatchPatElectronsEle8"),
                                       TagHLTmuonCollection = cms.InputTag("trgmatchSingleMuons"),
                                       ProbeHLTmuonCollection = cms.InputTag("trgmatchAsymMuonsLoose"),
                                       WP80_efficiency  =  cms.bool(False),
                                       HLTele17_efficiency  =  cms.bool(False),
                                       HLTele8_efficiency  =  cms.bool(False),
                                       RECO_efficiency  =  cms.bool(True),
                                       )

process.EPTmuoReco = process.EPTeleReco.clone(muonEfficiency = cms.bool(True))



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
                                       isElectron= cms.untracked.bool(False)  
                                       )
                                 
process.validationTESTJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsOLDL1FastL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       WeightName = cms.string('EventWeight'),
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
                                       isElectron= cms.untracked.bool(False)  
                                       )
                                 
process.validationPUJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFchsJetsPUL1FastL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       WeightName = cms.string('EventWeight'),
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
                                       isElectron= cms.untracked.bool(False)    
                                       )


process.validationJEC = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFchsJetsRCL1FastL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       WeightName = cms.string('EventWeight'),
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
                                       isElectron= cms.untracked.bool(False)  
                                       )
                                   
process.validationL2L3Residual = cms.EDAnalyzer('jetValidation',
                                       electronCollection = cms.InputTag("particleFlow:electrons"),
                                       jetCollection = cms.InputTag("ak5PFJetsL2L3Residual"),
                                       VertexCollection = cms.InputTag("offlinePrimaryVertices"),
                                       goodEPair = cms.InputTag("goodEPair"),
                                       WeightName = cms.string('EventWeight'),
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
                                                isElectron= cms.untracked.bool(False)   
                                       )

process.validationPU = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFJetsPU"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    WeightName = cms.string('EventWeight'),
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
                                      isElectron= cms.untracked.bool(False)  
                                    )


process.validationRC = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFJetsRC"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    WeightName = cms.string('EventWeight'),
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
                                      isElectron= cms.untracked.bool(False)  
                                    )


process.validationJECScaleUp = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFchsJetsRCL1FastL2L3Residual"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    WeightName = cms.string('EventWeight'),
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
                                              isElectron= cms.untracked.bool(False)  
                                    )

process.validationJECScaleDown = cms.EDAnalyzer('jetValidation',
                                    electronCollection = cms.InputTag("particleFlow:electrons"),
                                    jetCollection = cms.InputTag("ak5PFchsJetsRCL1FastL2L3Residual"),
                                    VertexCollection = cms.InputTag("offlinePrimaryVertices"), 
                                    goodEPair = cms.InputTag("goodEPair"),
                                    WeightName = cms.string('EventWeight'),
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
                                                isElectron= cms.untracked.bool(False)  
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
process.SelectionMu = cms.EDFilter('ZpatFilterMu2011',
                                   muonCollection = cms.InputTag('matchedMuons'),
                                   lowZmassLimit  = cms.double(71.0),
                                   highZmassLimit = cms.double(111.0)
                                   )

                                   
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
                                   isElectron= cms.untracked.bool(False)
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

###########################
### Electron Removal
###########################
process.pfNoElectron.bottomCollection = cms.InputTag("pfNoPileUp")
process.pfNoElectron.topCollection = cms.InputTag("goodEPair")   #remove only the two electron candidates
#process.pfNoElectron.topCollection = cms.InputTag("goodElec")   #remove all the electron passing the selections

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

process.trgmatchPatElectronsEle8 = cms.EDProducer("trgMatchedPatElectronProducer",
                                        InputProducer = cms.InputTag("patElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        hltTags = hltTagsForEle8,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchPatElectronsEle17 = cms.EDProducer("trgMatchedPatElectronProducer",
                                        InputProducer = cms.InputTag("patElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        hltTags = hltTagsForEle17,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchPatElectronsNOTEle17 = cms.EDProducer("trgMatchedPatElectronProducer",
                                        InputProducer = cms.InputTag("patElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        antiSelect = cms.untracked.bool(True),
                                        hltTags = hltTagsForEle17,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchPatElectronsEle8NOTEle17 = cms.EDProducer("trgMatchedPatElectronProducer",
                                        InputProducer = cms.InputTag("trgmatchPatElectronsNOTEle17"),
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

process.trgmatchPatElectronsReco = cms.EDProducer("trgMatchedPatElectronProducer",
                                        InputProducer = cms.InputTag("patElectrons"),
                                        isTriggerFilter = cms.untracked.bool(True),
                                        matchUnprescaledTriggerOnly = cms.untracked.bool(False),
                                        hltTags = hltTagsForEleReco,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

### MUON trigger matching:

HLTsymMuonPath1  = "HLT_DoubleMu7_v1"
HLTsymMuonPath2  = "HLT_DoubleMu7_v2"
HLTsymMuonFilter7  = "hltDiMuonL3PreFiltered7"

#HLTasymMuonPath1  = "HLT_Mu13_Mu8_v1"
HLTasymMuonPath2  = "HLT_Mu13_Mu8_v2"
#HLTasymMuonPath3  = "HLT_Mu13_Mu8_v3"
#HLTasymMuonPath4  = "HLT_Mu13_Mu8_v4"
#HLTasymMuonPath5  = "HLT_Mu13_Mu8_v5"
#HLTasymMuonPath6  = "HLT_Mu13_Mu8_v6"
#HLTasymMuonPath7  = "HLT_Mu13_Mu8_v7"
#HLTasymMuonPath8  = "HLT_Mu13_Mu8_v8"
#HLTasymMuonPath9  = "HLT_Mu13_Mu8_v9"
#HLTasymMuonPath10  = "HLT_Mu13_Mu8_v10"
#HLTasymMuonPath11  = "HLT_Mu13_Mu8_v11"
#HLTasymMuonPath12  = "HLT_Mu17_Mu8_v1"
#HLTasymMuonPath13  = "HLT_Mu17_Mu8_v2"
HLTasymMuonPath14  = "HLT_Mu17_Mu8_v3"
HLTasymMuonPath15  = "HLT_Mu17_Mu8_v4"
HLTasymMuonPath16  = "HLT_Mu17_Mu8_v5"
HLTasymMuonPath17  = "HLT_Mu17_Mu8_v6"
HLTasymMuonPath18  = "HLT_Mu17_Mu8_v7"
HLTasymMuonPath19  = "HLT_Mu17_Mu8_v8"
HLTasymMuonPath20  = "HLT_Mu17_Mu8_v9"
HLTasymMuonPath21  = "HLT_Mu17_Mu8_v10"
HLTasymMuonPath22  = "HLT_Mu17_Mu8_v11"

HLTasymMuonFilter8  = "hltDiMuonL3p5PreFiltered8"
HLTasymMuonFilter13  = "hltSingleMu13L3Filtered13"
HLTasymMuonFilter17  = "hltSingleMu13L3Filtered17"

hltTagsForAsymMuonL = cms.VInputTag(
#    cms.InputTag(HLTasymMuonPath1,  HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath2,  HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath3,  HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath4,  HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath5,  HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath6,  HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath7,  HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath8,  HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath9,  HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath10, HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath11, HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath12, HLTasymMuonFilter8 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath13, HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath14, HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath15, HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath16, HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath17, HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath18, HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath19, HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath20, HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath21, HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath22, HLTasymMuonFilter8 , HLTProcessName),
    cms.InputTag(HLTsymMuonPath1,  HLTsymMuonFilter7 , HLTProcessName),
    cms.InputTag(HLTsymMuonPath2,  HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath3,  HLTsymMuonFilter6 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath4,  HLTsymMuonFilter6 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath5,  HLTsymMuonFilter6 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath6,  HLTsymMuonFilter6 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath7,  HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath8,  HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath9,  HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath10, HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath11, HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath12, HLTsymMuonFilter7 , HLTProcessName),
    )


hltTagsForAsymMuonT = cms.VInputTag(
#    cms.InputTag(HLTasymMuonPath1,  HLTasymMuonFilter13 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath2,  HLTasymMuonFilter13 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath3,  HLTasymMuonFilter13 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath4,  HLTasymMuonFilter13 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath5,  HLTasymMuonFilter13 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath6,  HLTasymMuonFilter13 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath7,  HLTasymMuonFilter13 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath8,  HLTasymMuonFilter13 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath9,  HLTasymMuonFilter13 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath10, HLTasymMuonFilter13 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath11, HLTasymMuonFilter13 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath12, HLTasymMuonFilter17 , HLTProcessName),
#    cms.InputTag(HLTasymMuonPath13, HLTasymMuonFilter17 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath14, HLTasymMuonFilter17 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath15, HLTasymMuonFilter17 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath16, HLTasymMuonFilter17 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath17, HLTasymMuonFilter17 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath18, HLTasymMuonFilter17 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath19, HLTasymMuonFilter17 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath20, HLTasymMuonFilter17 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath21, HLTasymMuonFilter17 , HLTProcessName),
    cms.InputTag(HLTasymMuonPath22, HLTasymMuonFilter17 , HLTProcessName),
    cms.InputTag(HLTsymMuonPath1,  HLTsymMuonFilter7 , HLTProcessName),
    cms.InputTag(HLTsymMuonPath2,  HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath3,  HLTsymMuonFilter6 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath4,  HLTsymMuonFilter6 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath5,  HLTsymMuonFilter6 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath6,  HLTsymMuonFilter6 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath7,  HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath8,  HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath9,  HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath10, HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath11, HLTsymMuonFilter7 , HLTProcessName),
#    cms.InputTag(HLTsymMuonPath12, HLTsymMuonFilter7 , HLTProcessName),
    )

process.trgmatchAsymMuonsLoose = cms.EDProducer("trgMatchedMuonProducer",
                                        InputProducer = cms.InputTag("allMuons"),
                                        #isTriggerFilter = cms.untracked.bool(True),
                                        #isTriggerOR = cms.untracked.bool(True),
                                        #matchUnprescaledTriggerOnly = cms.untracked.bool(False),
                                        hltTags = hltTagsForAsymMuonL,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchAsymMuonsTight = cms.EDProducer("trgMatchedMuonProducer",
                                        InputProducer = cms.InputTag("allMuons"),
                                        #isTriggerFilter = cms.untracked.bool(True),
                                        #isTriggerOR = cms.untracked.bool(True),
                                        hltTags = hltTagsForAsymMuonT,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchAsymMuonsNOTtight = cms.EDProducer("trgMatchedMuonProducer",
                                        InputProducer = cms.InputTag("allMuons"),
                                        #isTriggerFilter = cms.untracked.bool(True),
                                        #isTriggerOR = cms.untracked.bool(True),
                                        antiSelect = cms.untracked.bool(True),
                                        hltTags = hltTagsForAsymMuonT,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

process.trgmatchAsymMuonsLooseNOTtight = cms.EDProducer("trgMatchedMuonProducer",
                                        InputProducer = cms.InputTag("trgmatchAsymMuonsNOTtight"),
                                        #isTriggerFilter = cms.untracked.bool(True),
                                        #isTriggerOR = cms.untracked.bool(True),
                                        hltTags = hltTagsForAsymMuonL,
                                        triggerEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","",HLTProcessName),
                                        triggerResultsTag = cms.untracked.InputTag("TriggerResults","",HLTProcessName)
                                    )

HLTmuoRecoPath1  = "HLT_IsoMu17_v5"
HLTmuoRecoPath2  = "HLT_IsoMu17_v6"
HLTmuoRecoPath3  = "HLT_IsoMu17_v7"
HLTmuoRecoPath4  = "HLT_IsoMu17_v8"
HLTmuoRecoPath5  = "HLT_IsoMu17_v9"
HLTmuoRecoPath6  = "HLT_IsoMu17_v10"
HLTmuoRecoPath7  = "HLT_IsoMu17_v11"
HLTmuoRecoPath8  = "HLT_IsoMu17_v12"
HLTmuoRecoPath9  = "HLT_IsoMu17_v13"
HLTmuoRecoPath10  = "HLT_IsoMu17_v14"
HLTmuoRecoPath11  = "HLT_IsoMu24_v1"
HLTmuoRecoPath12  = "HLT_IsoMu24_v2"
HLTmuoRecoPath13  = "HLT_IsoMu24_v3"
HLTmuoRecoPath14  = "HLT_IsoMu24_v4"
HLTmuoRecoPath15  = "HLT_IsoMu24_v5"
HLTmuoRecoPath16  = "HLT_IsoMu24_v6"
HLTmuoRecoPath17  = "HLT_IsoMu24_v7"
HLTmuoRecoPath18  = "HLT_IsoMu24_v8"
HLTmuoRecoPath19  = "HLT_IsoMu24_v9"
HLTmuoRecoPath20  = "HLT_IsoMu24_v10"
HLTmuoRecoPath21  = "HLT_IsoMu24_v11"
HLTmuoRecoPath22  = "HLT_IsoMu24_v12"
HLTmuoRecoPath23  = "HLT_IsoMu24_v13"
HLTmuoRecoFilter17 = "hltSingleMuIsoL3IsoFiltered17"
HLTmuoRecoFilter24 = "hltSingleMuIsoL3IsoFiltered24"
#HLTmuoRecoFilter17 = ""
#HLTmuoRecoFilter24 = ""

hltTagsForMuoReco = cms.VInputTag(
    cms.InputTag(HLTmuoRecoPath1,  HLTmuoRecoFilter17 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath2,  HLTmuoRecoFilter17 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath3,  HLTmuoRecoFilter17 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath4,  HLTmuoRecoFilter17 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath5,  HLTmuoRecoFilter17 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath6,  HLTmuoRecoFilter17 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath7,  HLTmuoRecoFilter17 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath8,  HLTmuoRecoFilter17 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath9,  HLTmuoRecoFilter17 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath10,  HLTmuoRecoFilter17 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath11,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath12,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath13,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath14,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath15,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath16,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath17,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath18,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath19,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath20,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath21,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath22,  HLTmuoRecoFilter24 , HLTProcessName),
    cms.InputTag(HLTmuoRecoPath23,  HLTmuoRecoFilter24 , HLTProcessName),
    )

process.trgmatchSingleMuons = cms.EDProducer("trgMatchedMuonProducer",
                                        InputProducer = cms.InputTag("allMuons"),
                                        #isTriggerFilter = cms.untracked.bool(True),
                                        isTriggerOR = cms.untracked.bool(True),
                                        matchUnprescaledTriggerOnly = cms.untracked.bool(False),
                                        hltTags = hltTagsForMuoReco,
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
    'keep *',
    )

process.out.outputCommands.extend(['keep *'
                                   ])

process.out.SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('ToolInizialization'))

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

process.patDefaultSequence.replace(process.selectedPatMuons,cms.Sequence(process.selectedPatMuons+process.selectedMuonsWithIsolationData))

process.ToolInizialization = cms.Path(
    process.goodPV*
    process.kt6PFJetsForIsolation*
    process.kt6PFJets*
    process.ak5PFJets*
    process.ak5PFJetsL1FastL2L3Residual*
    process.goodOfflinePrimaryVertices*
    ## isolation sequence
    process.pfNoPileUpSequence*
    process.pfParticleSelectionSequence*
    process.eleIsoSequence*
    process.muIsoSequence*
    process.pfElectronSequence*
    process.pfMuonSequence*
    process.patTrigger*
    process.patDefaultSequence*
    #process.crapMuons*
    #process.patElectronsWithTrigger*
    process.allMuons*                                          ## our final muon collection: all muons
    process.tightMuons*                                        ## our final muon collection: tight muons
    process.matchedMuons*                                      ## our final muon collection: matched muons
    (process.zmuAllmuAll+                                      ##
     process.zmuTightmuTight+                                  ##
     process.zmuMatchedmuMatched)*
    process.SelectionMu*
    process.goodEPair*
    process.eleTriggerMatchHLT*
    process.patElectronsWithTrigger*
    process.demo*
    process.goodElec*
    process.pfNoElectron*
    #process.pfNoMuon*
    process.ak5PFJetsRC*
    process.ak5PFchsJetsRCL1FastL2L3Residual*
    process.validationJEC
    )

#process.TAPAnalysisWP80 = cms.Path(
#        process.goodOfflinePrimaryVertices*
#        process.trgmatchPatElectronsEle17*
#        process.trgmatchPatElectronsEle8*
#        process.TAPeleWp80
#        )

# process.TAPAnalysisHLTele8NOTele17 = cms.Path(
#         process.goodOfflinePrimaryVertices*
#         process.trgmatchPatElectronsReco*
#         process.trgmatchPatElectronsNOTEle17*
#         process.trgmatchPatElectronsEle8NOTEle17*
#         process.TAPhltele8NOTele17
#         )

# process.TAPAnalysisHLTele17 = cms.Path(
#         process.goodOfflinePrimaryVertices*
#
#         process.trgmatchPatElectronsEle17*
#         process.TAPhltele17
#         )

# process.TAPAnalysisRECO = cms.Path(
#         process.goodOfflinePrimaryVertices*
#         process.trgmatchPatElectronsReco*
#         process.trgmatchPatElectronsEle8*
#         process.TAPreco
#         )
####===============================================

process.EPTAnalysisEleWP80 = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchPatElectronsEle8*
    process.trgmatchPatElectronsEle17*
    process.EPTeleWp80
    )

process.EPTAnalysisHLTele8NOTele17 = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchPatElectronsNOTEle17*
    process.trgmatchPatElectronsEle8NOTEle17*
    process.trgmatchPatElectronsReco*
    process.EPThltele8NOTele17
    )


process.EPTAnalysisHLTele17 = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchPatElectronsEle17*    
    process.trgmatchPatElectronsReco*
    process.EPThltele17
    )

process.EPTAnalysisEleRECO = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchPatElectronsEle8*
    process.trgmatchPatElectronsReco*
    process.EPTeleReco
    )

process.EPTAnalysisMuoWP80 = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchAsymMuonsLoose*
    process.trgmatchAsymMuonsTight*
    process.EPTmuoWp80
    )

process.EPTAnalysishltmuoTight = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchAsymMuonsLoose*
    process.trgmatchSingleMuons*
    process.EPThltmuoTight
    )

process.EPTAnalysishltmuoLooseNOTtight = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchAsymMuonsNOTtight*
    process.trgmatchAsymMuonsLooseNOTtight*
    process.trgmatchSingleMuons*
    process.EPThltmuoLooseNOTtight
    )

process.EPTAnalysisMuoRECO = cms.Path(
    process.goodOfflinePrimaryVertices*
    process.trgmatchSingleMuons*
    process.trgmatchAsymMuonsLoose*
    process.EPTmuoReco
    )


# process.JetValidation = cms.Path(
#     process.TotalEventCounter*
#     process.eleTriggerMatchHLT*
#     process.patElectronsWithTrigger*  
#     process.demobefore*   
#     process.goodOfflinePrimaryVertices*
#     process.Selection*
#     process.goodEPair*
#     process.demo*
#     #process.reclusValidation*
#     #process.validationOldJEC*
#     #process.validationPUJEC*
#     #process.validationPU*
#     process.validationRC*
#     process.validationJECScaleUp*
#     process.validationJECScaleDown* 
#     #process.validationTESTJEC*
#     process.validationJEC
#     )

#####################
#                   #
#    Outpath        #
#                   #
#####################

process.outpath = cms.EndPath(
    #process.out
    )
