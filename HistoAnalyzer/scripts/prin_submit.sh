#!/bin/sh

# cms
eval `scramv1 runtime -sh`

# grid
source /afs/infn.it/ts/project/cms/LCG/cms_ui_env.sh

# crab
source /afs/infn.it/ts/project/cms/CRAB/crab.sh

user=`whoami`
m=2

echo
echo "user="$user" max jobs="$m
echo

while true; do

  r=`bjobs -u $user 2>&1 | grep RUN | wc -l`

  p=`bjobs -u $user 2>&1 | grep PEND | wc -l`

  t=$(($r + $p))

  d=`date`
  echo $d" - running="$r" pending="$p" total="$t

  if [ $t -lt $m ]; then

    n=$(($m-$t))

    echo "submitting "$n" jobs"

    crab -submit $n

  fi

  sleep 60

done


