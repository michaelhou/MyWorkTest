#!/bin/bash
bundlename=$1

cd $bundlename/
echo ../../factory/bin/finalize_bundle .
../../factory/bin/finalize_bundle .
cd ..

file ${bundlename}.tar.bz2
md5sum ${bundlename}.tar.bz2 >> md5.txt
