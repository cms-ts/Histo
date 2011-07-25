import FWCore.ParameterSet.Config as cms

demo = cms.EDAnalyzer('HistoAnalyzer'
    #,tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
    , electronCollection = cms.untracked.InputTag('gsfElectrons')
)
