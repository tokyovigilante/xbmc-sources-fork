#!/bin/bash 
# Requires libtool

PLATFORM=`uname -m`
if [ $PLATFORM != "x86_64" ]; then
   PLATFORM="osx"
fi

autoreconf -vif &&
./configure --with-mp4v2 --with-pic &&
make &&

echo wrapping libfaad &&
gcc -shared -fpic --soname -dynamiclib -flat_namespace -undefined 	suppress -o libfaad2-$PLATFORM.so -rdynamic libfaad/*.o 
