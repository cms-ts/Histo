#definizioni
dir="/afs/infn.it/ts/user/marone/html/ZJets"
#newdir="2011_v2_33Mu/"
newdir="Variables_v2_58_jetRemoval_Mu"
actdir=`pwd`

#azioni
rm /tmp/marone/*
rm -rf $dir/$newdir
#make plots
echo ".L DrawComparisonJetMCData.C++" > tmpfile
echo "DrawComparisonJetMCData()" >> tmpfile
cat tmpfile | root -l -b 

#copy plots
mkdir $dir/$newdir 
mv /tmp/marone/* $dir/$newdir
cp diow.C $dir/$newdir
cd $dir/$newdir
echo ".L diow.C++" > tmpfile
echo "diow()" >> tmpfile
cat tmpfile |root -l
rm tmpfile
cd $actdir

