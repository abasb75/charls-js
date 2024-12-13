#!/bin/sh
#rm -rf build

mkdir -p build
mkdir -p dist

(cd build && emcmake cmake -DCMAKE_C_FLAGS="" ..) &&
(cd build && emmake make VERBOSE=1 -j ${nprocs})
cp ./build/src/charlsjs.js ./dist &&
cp ./build/src/interface.d.ts ./dist
