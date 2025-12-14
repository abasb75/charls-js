## charls-js

A JavaScript/TypeScript project that compiles the official CharLS (JPEG-LS reference implementation in C++) to WebAssembly using Emscripten.
This allows lossless/near-lossless JPEG-LS encoding and decoding directly in the browser or Node.js without any server-side processing.
The resulting WASM modules are published as the npm package @abasb75/charls.
Project Structure (relevant part)
textcharls-js/
├── scripts/
│   ├── docker-build.sh     # Builds the Docker image with Emscripten toolchain
│   ├── docker-sh.sh        # Starts an interactive shell inside the container
│   ├── wasm-build.sh       # Main script that compiles CharLS to WASM
│   └── README.md
├── src/                    # Original CharLS C++ source code (submodule or copied)
└── ...                     # Other build/config files
Build Process (Step-by-Step)
The entire build is done inside a Docker container to ensure a clean, reproducible Emscripten environment.

# Build the Docker Image

```sh
./script/docker-build.sh
```

This script:

Uses the official emscripten/emsdk base image.
Installs any additional dependencies if needed.
Creates an image tagged charls-builder.

# Start an Interactive Shell Inside the Container

```sh
Bash./docker-sh.sh

```

This command:

Runs the previously built charls-builder image.
Mounts the current project directory (/var/www/html/charls-js or your local path) as /src inside the container.
Drops you into a bash shell as root inside the container, with the Emscripten toolchain already activated.

# Compile CharLS to WebAssembly

Inside the container shell, run:

```sh
./scripts/wasm-build.sh

```

What this script does:

Configures Emscripten build flags (optimizations, export functions, etc.).
Compiles two separate modules:
jls_decoder.wasm → JPEG-LS decoder
jls_encoder.wasm → JPEG-LS encoder

Generates accompanying JavaScript glue code (decode.js and encode.js).
Places the final .wasm and .js files in the appropriate location for the npm package.

# compile c++ encode_file/decode_file.cpp

test codecs:

```bash
g++ -std=c++17 ./src/decode_file.cpp ./src/codec/decode.cpp
-I/usr/local/include -L/usr/local/lib -lcharls
-o decode_file
```

encode

```bash
g++ -std=c++17 ./src/encode_file.cpp ./src/codec/encode.cpp -I/usr/local/include -L/usr/local/lib -lcharls -o encode_file
```

```bash
encode_file <input.raw> <output.jls> <width> <height> <components> <bits> <interleave> [near]
```

```bash
// gray scale
./encode_file ./test-files/pixel.raw ./test-files/pixel.jls  512 512 1 16 0 0
./decode_file ./test-files/pixel.jls./encode_file ./test-files/pixel2.raw ./test-files/pixel2.jls  256 256 3 8 1 0./encode_file ./test-files/pixel3.raw ./test-files/pixel3.jls  10 45 1 8 0 0
./decode_file ./test-files/pixel4.jls./encode_file ./test-files/pixel4.raw ./test-files/pixel4.jls  10 50 1 16 0 0
./decode_file ./test-files/pixel4.jls./encode_file ./test-files/decoded.raw ./test-files/encoded.jls 128 128 1 7 0 0
```
