# Leucht

## Compile

```bash
sudo apt install libssl-dev
```

```bash
mkdir -p external/pistache
cd external
git clone https://github.com/oktal/pistache.git build-pistache
cd build-pistache
git submodule update --init
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DPISTACHE_USE_SSL=true -DCMAKE_INSTALL_PREFIX=../pistache
make -j
make install
cd ../..
```

```bash
mkdir build
cd build
cmake ..
make -j
```
