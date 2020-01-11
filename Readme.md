# Leucht

## Compile

```bash
# For pistache
sudo apt install libssl-dev

# For simulation with SDL
sudo apt install libsdl1.2-dev

# For playing radio streams
sudo apt install vlc

./get_externals.sh
mkdir build
cd build
cmake ..
make -j
```

## Hardware Setup

The wall is made up of 252 [WS2801](https://www.adafruit.com/product/738) pixels.
See https://learn.adafruit.com/12mm-led-pixels/wiring on how to set them up.
