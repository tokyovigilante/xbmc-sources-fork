#!/bin/sh
gcc -dynamiclib -flat_namespace -undefined suppress -o .libs/libdvdnav.4.1.0.dylib .libs/*.o -all_load ../src/dvdread/.libs/libdvdread.a ../src/vm/.libs/libdvdvm.a  -lpthread -install_name  /usr/local/lib/libdvdnav.4.dylib -compatibility_version 6 -current_version 6.0
cp .libs/libdvdnav.4.1.0.dylib ~/Code/C++/Eclipse/OSXBMC.app/Contents/Resources/XBMC/system/players/dvdplayer/libdvdnav-osx.so
