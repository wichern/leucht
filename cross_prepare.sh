#!/bin/bash

ROOT=$(pwd)

(
	mkdir -p external/pistache
	cd external
	git clone https://github.com/oktal/pistache.git build-pistache
	cd build-pistache
	git submodule update --init
	mkdir build_rpi
	cd build_rpi
	cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=$ROOT/Toolchain-rpizero.cmake -DCMAKE_INSTALL_PREFIX=$ROOT/x-tools/armv6-rpi-linux-gnueabi/armv6-rpi-linux-gnueabi/sysroot/usr
	make -j
	sudo make install
)
