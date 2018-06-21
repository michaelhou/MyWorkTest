#!/bin/bash

gfolder=$1
commonname=$2

function makeimage()
{
 imagesize=$1
 imagename=$2
 sectorsize=$((60000000*$1/32))
 filename=${imagename}_${imagesize}.bin
 echo sectorsize=$sectorsize
 echo filename=$filename
 cd $gfolder
 
  echo ../factory/setup/image_tool preflash --sectors $sectorsize -o ../$filename
  ../../factory/setup/image_tool preflash --sectors $sectorsize -o ../$filename
  cd ..
  bzip2 -z -9 $filename
  md5sum $filename.bz2 >> md5sum.txt

}
makeimage $3  $commonname