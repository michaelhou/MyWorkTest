#!/bin/bash


datenow=20180619
phase=evt
project=XXX

preflashname=${datenow}_XXX_${phase}_preflash
remotedir=/path/to/${datenow}_${project}_${phase^^}
factoryimagedir=factory_bundle_${project}_${datenow}_${phase}

# echo remote=$remotedir
# echo facdir=$factoryimagedir
# echo preflashname=$preflashname
# ls $factoryimagedir
# echo ./build_bundle.sh $factoryimagedir
# echo ./build_preflash.sh $factoryimagedir  $preflashname
# echo ./ftpuploadme.sh md5sum.txt $remotedir
# for lfile in $(ls *.bz2); do
  # echo ./ftpuploadme.sh $lfile $remotedir
# done
# exit

./build_bundle.sh $factoryimagedir
./build_preflash.sh $factoryimagedir  $preflashname 64
./build_preflash.sh $factoryimagedir  $preflashname 32
./ftpuploadme.sh md5sum.txt $remotedir
for lfile in $(ls *.bz2);  do
./ftpuploadme.sh $lfile $remotedir
done
