#!/bin/bash

# Pistache
(
	mkdir -p external/pistache
	cd external
	git clone https://github.com/oktal/pistache.git build-pistache
	cd build-pistache
	git submodule update --init
	cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DPISTACHE_USE_SSL=true -DCMAKE_INSTALL_PREFIX=../pistache
	make -j
	make install
)

# bcm2835
(
	mkdir -p external/bcm2835
	cd external/bcm2835
	wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.60.tar.gz
	tar -xzf bcm2835-1.60.tar.gz --strip-components=1
	rm bcm2835-1.60.tar.gz
)

