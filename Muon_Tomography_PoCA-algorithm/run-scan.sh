#! /bin/bash
echo ${1}
echo ${2}
echo ${3}
Rnd=${2}*10
DIR=`pwd`
source  /cvmfs/sft.cern.ch/lcg/views/LCG_101/x86_64-centos7-gcc11-opt/setup.sh
 
/lustre/collider/wangjiangtao/musrSIM/musrsim-sms-surface_muon/build/musrSim ${1}.mac ${1}-${3}-${2} ${Rnd}

cd ${DIR}/data/
ls musrSim_*_${1}-${3}-${2}.root > input${3}_${2}.script
../particleTreeAna/ana input${3}_${2}.script  ${1}  > ${1}-Tracks.txt 

rm input${3}_${2}.script

rm musrSim_*_${1}-${3}-${2}.root

sed -i '1,7d' ${1}-Tracks.txt    #delete first 7 lines

sed -i '$d' ${1}-Tracks.txt      #delete last 4 lines
sed -i '$d' ${1}-Tracks.txt
sed -i '$d' ${1}-Tracks.txt
sed -i '$d' ${1}-Tracks.txt

cd ${DIR}

