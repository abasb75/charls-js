mv build/jls_decoder.js dist/jls_decoder.js
mv build/jls_decoder.wasm dist/jls_decoder.wasm

mv build/jls_encoder.js dist/jls_encoder.js
mv build/jls_encoder.wasm dist/jls_encoder.wasm#!/bin/sh

rm -rf build dist
mkdir -p dist

if [ ! -d "external/charls" ]; then
    echo "Cloning CharLS 2.4.2..."
    git clone https://github.com/team-charls/charls.git external/charls
    cd external/charls
    git checkout 2.4.2
    cd ../../
fi


mkdir build && cd build
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release
emmake make -j$(nproc)

cd ..
mv build/jls_decoder.js dist/jls_decoder.js
mv build/jls_decoder.wasm dist/jls_decoder.wasm

mv build/jls_encoder.js dist/jls_encoder.js
mv build/jls_encoder.wasm dist/jls_encoder.wasm

mv build/jls_es6_decoder.js dist/jls_es6_decoder.js
mv build/jls_es6_decoder.wasm dist/jls_es6_decoder.wasm

mv build/jls_es6_encoder.js dist/jls_es6_encoder.js
mv build/jls_es6_encoder.wasm dist/jls_es6_encoder.wasm


mv build/jls_inline_decoder.js dist/jls_inline_decoder.js 
mv build/jls_inline_encoder.js dist/jls_inline_encoder.js

echo "Build complete! Files in dist/"
ls dist/