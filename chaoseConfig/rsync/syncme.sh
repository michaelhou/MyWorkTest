#!/bin/bash

# serverip=10.0.101.18
serverip=vb
export RSYNC_PASSWORD=me

#this sync include myself...
rsync  --progress -rahv me@$serverip::RRT/michael/ .

rsync  --progress -rahv me@$serverip::RRT/michael/ext/usr/local/factory/py/test/ /usr/local/factory/py/test/

