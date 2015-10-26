import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile('/afs/cern.ch/user/m/mshi/amumu_gen_analyzer/CMSSW_7_1_11_patch2/src/Amumu/AmumuAnalyzer/allInfoIWant_amumu.txt')
process = cms.Process("Demo")
process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(*mylist)
)


process.demo = cms.EDAnalyzer('AmumuAnalyzer',
    genParticleTag=cms.InputTag("genParticles")  
)

process.TFileService = cms.Service("TFileService",
					fileName = cms.string('histodemo.root')
)
process.p = cms.Path(process.demo)
