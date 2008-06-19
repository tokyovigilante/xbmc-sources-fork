#!/bin/sh
#./configure --enable-asm=no
#make
cd src/MACDll
g++ -g -DHAVE_CONFIG_H -I. -I. -I../../src/Shared -I../../src/Shared -Wall -pedantic -Wno-long-long -c -fno-common -DPIC *.cpp -I ../MACLib/
cd ../../
gcc -bundle -flat_namespace -undefined suppress -o MACDll-osx.so `find . -name \*.o | grep .libs` src/MACDll/MACDll.o
