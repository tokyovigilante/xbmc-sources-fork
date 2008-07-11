#!/bin/bash 
# Requires libtool

PLATFORM=`uname -m`
if [ $PLATFORM != "x86_64" ]; then
   PLATFORM="osx"
fi

autoreconf -vif &&
LIBNETEMBRYO_CFLAGS=-L/usr/lib LIBNETEMBRYO_LIBS=-L/usr/lib ./configure && 
make &&

echo wrapping libnemesi &&
gcc -shared -fpic --soname -dynamiclib -flat_namespace -undefined suppress -o libnemesi-$PLATFORM.so -rdynamic bufferpool/*.o creativecommons/*.o parsers/*.o rtcp/*.o rtp/*.o rtsp/*.o sdp/*.o utils/*.o
