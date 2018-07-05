#!/bin/bash

while [ 1 ]; do time repo sync; if [ $? -eq 0 ]; then echo sync over; break;else echo not ok;sleep 1; fi;done

### you should note that, we should add ; after ] but not ; after do/then/else
### we should add space around [ and ] ; space number is not care.
while [ 1 ];do time repo sync; if [ $? -eq 0 ];then echo sync over...;break; else echo not ok...;sleep 1;fi;done
