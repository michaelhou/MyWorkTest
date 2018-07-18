#!/bin/bash

while [ 1 ]; do time repo sync; if [ $? -eq 0 ]; then echo sync over; break;else echo not ok;sleep 1; fi;done

### you should note that, we should add ; after ] but not ; after do/then/else
### we should add space around [ and ] ; space number is not care.
while [ 1 ];do time repo sync; if [ $? -eq 0 ];then echo sync over...;break; else echo not ok...;sleep 1;fi;done

# run in background and no console output. 
while [ 1 ];do time ./syncme.sh ;sleep 1;done >/dev/null 2>1 &

find . -maxdepth 1 -type d -and -not -name . |xargs -I {} bash -c 'echo $0;cd $0;mkdir ext ;tar -xf *.bz2 -C ext >/dev/null 2>/dev/null ;grep -rniI crc' {}
find . -maxdepth 1 -type d -and -not -name . |xargs -I {} bash -c 'echo $0;cd $0;rm -rf ext' {}

jobs;kill %1