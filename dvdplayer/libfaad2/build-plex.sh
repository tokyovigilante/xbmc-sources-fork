#!/bin/bash 
# Requires libtool

PLATFORM=`uname -m`
if [ $PLATFORM != "x86_64" ]; then
   PLATFORM="osx"
fi

autoreconf -vif &&
./configure --with-mp4v2 --with-pic &&
make &&