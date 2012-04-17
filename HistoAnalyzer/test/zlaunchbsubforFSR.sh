#!/bin/sh

cwd=`pwd`

#list=`find /gpfs/grid/srm/cms/store/data/Run2011A/SingleElectron/AOD/May10ReReco-v1/ -type f`
#list=`find /gpfs/grid/srm/cms/store/data/Run2011A/DoubleElectron/RAW-RECO/ZElectron-May10ReReco-v1 -type f`
#list='/gpfs/grid/srm/cms/store/data/Run2011A/DoubleElectron/RAW-RECO/ZElectron-May10ReReco-v1/0000/EC04DB0E-D97D-E011-B60B-00261894396F.root'
#list=`find ls /gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/ -type f | grep "fsr"`
list=`find ls /gpfs/cms/data/2012/Hadronizer_MgmMatchTuneZ2_7TeV_madgraph/20120410-RAW2DIGI_L1Reco_RECO-CMSSW_4_4_2_patch8/ -type f | grep "tauola"`

i=0

for f in $list; do

  i=`expr $i + 1`

  #f=`echo $f | sed -e 's;/gpfs/grid/srm/cms;;'`

  echo $i $f

  workdir=`printf "NoFSRLdir-%06d" $i`

  rm -fr $cwd/$workdir
  mkdir $cwd/$workdir
  cd $cwd/$workdir

  cp $cwd/jetValidationWithPfAK5ChsLastMC_cfg.py .
  cp $cwd/*.root .

  echo "process.source.fileNames = ['file:"$f"']" >> jetValidationWithPfAK5ChsLastMC_cfg.py

  #queue=normal
  queue=ts_cms
  #queue=short

  bsub -q $queue -J $f -e job.log -o job.log cmsRun $cwd/$workdir/jetValidationWithPfAK5ChsLastMC_cfg.py

  cd $cwd

done

