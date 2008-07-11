#!/bin/bash 
# Requires libtool

PLATFORM=`uname -m`
if [ $PLATFORM != "x86_64" ]; then
   PLATFORM="osx"
fi

autoreconf -vif &&
./configure && 
make &&

echo wrapping libnetembryo &&
gcc -shared -fpic --soname -dynamiclib -flat_namespace -undefined suppress -o libnetembryo-$PLATFORM.so -rdynamic utils/*.o wsocket/*.o 
