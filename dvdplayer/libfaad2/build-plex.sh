#!/bin/bash 

autoreconf -vif &&
./configure --with-pic &&
make
