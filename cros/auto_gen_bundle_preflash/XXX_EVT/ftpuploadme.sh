#!/bin/bash

ftp_user=UUU
ftp_password=PPP
ftp_addr=ftp.AA.BB.CC

if [ $# -ge 2 ]; then

echo curl -T $1  -u $ftp_user:$ftp_password ftp://$ftp_addr/$2/
time curl -T $1  -u $ftp_user:$ftp_password ftp://$ftp_addr/$2/

fi
