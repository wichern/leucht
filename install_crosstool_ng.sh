#!/bin/bash

sudo apt install bison wget flex texinfo help2man libtool-bin libtool-doc

CTNG_VERSION=1.24.0

wget http://crosstool-ng.org/download/crosstool-ng/crosstool-ng-$CTNG_VERSION.tar.xz
tar -xf crosstool-ng-$CTNG_VERSION.tar.xz
cd crosstool-ng-$CTNG_VERSION
./configure
make -j
sudo make install
cd ..
rm -rf $CTNG_VERSION
rm crosstool-ng-$CTNG_VERSION.tar.xz

