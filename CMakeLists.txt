cmake_minimum_required(VERSION 3.15)
project(jls_wasm_decoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/charls)

# 
add_executable(jls_decoder src/jsdecode.cpp src/codec/decode.cpp)
target_compile_features(jls_decoder PUBLIC cxx_std_17)
target_link_libraries(jls_decoder PRIVATE charls)
set_target_properties(
      jls_decoder
    PROPERTIES 
    LINK_FLAGS "\
      --allowJs \
      --emit-tsd jls_decoder.d.ts \
      --bind \
      -s NO_EXIT_RUNTIME=1 \
      -s DISABLE_EXCEPTION_CATCHING=1 \
      -s MALLOC=emmalloc \
      -s ALLOW_MEMORY_GROWTH=1 \
      -s ASSERTIONS=0 \
      -s FILESYSTEM=0 \
      -s EXPORTED_FUNCTIONS=[] \
      -s EXPORTED_RUNTIME_METHODS=[ccall] \
      -s SINGLE_FILE=0 \
      -s MODULARIZE=1 \
      -s EXPORT_ES6=0 \
      -s EXPORT_NAME=CharLSDecoder \
   ")


#  with export default
add_executable(jls_es6_decoder src/jsdecode.cpp src/codec/decode.cpp)
target_compile_features(jls_es6_decoder PUBLIC cxx_std_17)
target_link_libraries(jls_es6_decoder PRIVATE charls)
set_target_properties(
    jls_es6_decoder 
    PROPERTIES 
    LINK_FLAGS "\
      --allowJs \
      --emit-tsd jls_es6_decoder.d.ts \
      --bind \
      -s NO_EXIT_RUNTIME=1 \
      -s DISABLE_EXCEPTION_CATCHING=1 \
      -s MALLOC=emmalloc \
      -s ALLOW_MEMORY_GROWTH=1 \
      -s ASSERTIONS=0 \
      -s FILESYSTEM=0 \
      -s EXPORTED_FUNCTIONS=[] \
      -s EXPORTED_RUNTIME_METHODS=[ccall] \
      -s SINGLE_FILE=0 \
      -s MODULARIZE=1 \
      -s EXPORT_ES6=1 \
      -s EXPORT_NAME=CharLSDecoder \
   ")

#  with export default & inline wasm base 64
add_executable(jls_inline_decoder src/jsdecode.cpp src/codec/decode.cpp)
target_compile_features(jls_inline_decoder PUBLIC cxx_std_17)
target_link_libraries(jls_inline_decoder PRIVATE charls)
set_target_properties(
    jls_inline_decoder 
    PROPERTIES 
    LINK_FLAGS "\
      --allowJs \
      --emit-tsd jls_inline_decoder.d.ts \
      --bind \
      -s NO_EXIT_RUNTIME=1 \
      -s DISABLE_EXCEPTION_CATCHING=1 \
      -s MALLOC=emmalloc \
      -s ALLOW_MEMORY_GROWTH=1 \
      -s ASSERTIONS=0 \
      -s FILESYSTEM=0 \
      -s EXPORTED_FUNCTIONS=[] \
      -s EXPORTED_RUNTIME_METHODS=[ccall] \
      -s SINGLE_FILE=1 \
      -s MODULARIZE=1 \
      -s EXPORT_ES6=0 \
      -s EXPORT_NAME=CharLSDecoder \
   ")

#  with export default & inline wasm base 64
add_executable(jls_inline_e6_decoder src/jsdecode.cpp src/codec/decode.cpp)
target_compile_features(jls_inline_e6_decoder PUBLIC cxx_std_17)
target_link_libraries(jls_inline_e6_decoder PRIVATE charls)
set_target_properties(
    jls_inline_e6_decoder 
    PROPERTIES 
    LINK_FLAGS "\
      --allowJs \
      --emit-tsd jls_inline_e6_decoder.d.ts \
      --bind \
      -s NO_EXIT_RUNTIME=1 \
      -s DISABLE_EXCEPTION_CATCHING=1 \
      -s MALLOC=emmalloc \
      -s ALLOW_MEMORY_GROWTH=1 \
      -s ASSERTIONS=0 \
      -s FILESYSTEM=0 \
      -s EXPORTED_FUNCTIONS=[] \
      -s EXPORTED_RUNTIME_METHODS=[ccall] \
      -s SINGLE_FILE=1 \
      -s MODULARIZE=1 \
      -s EXPORT_ES6=1 \
      -s EXPORT_NAME=CharLSDecoder \
")


# ecoder
add_executable(jls_encoder src/jsencode.cpp src/codec/encode.cpp)
target_compile_features(jls_encoder PUBLIC cxx_std_17)


target_link_libraries(jls_encoder PRIVATE charls)

set_target_properties(
    jls_encoder 
    PROPERTIES 
    LINK_FLAGS "\
      --allowJs \
      --emit-tsd jls_encoder.d.ts \
      --bind \
      -s NO_EXIT_RUNTIME=1 \
      -s DISABLE_EXCEPTION_CATCHING=1 \
      -s MALLOC=emmalloc \
      -s ALLOW_MEMORY_GROWTH=1 \
      -s ASSERTIONS=0 \
      -s FILESYSTEM=0 \
      -s EXPORTED_FUNCTIONS=[] \
      -s EXPORTED_RUNTIME_METHODS=[ccall] \
      -s SINGLE_FILE=0 \
      -s MODULARIZE=1 \
      -s EXPORT_ES6=0 \
      -s EXPORT_NAME=CharLSEncoder \
   ")



# ecoder with export default
add_executable(jls_es6_encoder src/jsencode.cpp src/codec/encode.cpp)
target_compile_features(jls_es6_encoder PUBLIC cxx_std_17)


target_link_libraries(jls_es6_encoder PRIVATE charls)

set_target_properties(
    jls_es6_encoder 
    PROPERTIES 
    LINK_FLAGS "\
      --allowJs \
      --emit-tsd jls_es6_encoder.d.ts \
      --bind \
      -s NO_EXIT_RUNTIME=1 \
      -s DISABLE_EXCEPTION_CATCHING=1 \
      -s MALLOC=emmalloc \
      -s ALLOW_MEMORY_GROWTH=1 \
      -s ASSERTIONS=0 \
      -s FILESYSTEM=0 \
      -s EXPORTED_FUNCTIONS=[] \
      -s EXPORTED_RUNTIME_METHODS=[ccall] \
      -s SINGLE_FILE=0 \
      -s MODULARIZE=1 \
      -s EXPORT_ES6=1 \
      -s EXPORT_NAME=CharLSEncoder \
   ")

add_executable(jls_inline_encoder src/jsencode.cpp src/codec/encode.cpp)
target_compile_features(jls_inline_encoder PUBLIC cxx_std_17)
target_link_libraries(jls_inline_encoder PRIVATE charls)
set_target_properties(
    jls_inline_encoder 
    PROPERTIES 
    LINK_FLAGS "\
      --allowJs \
      --emit-tsd jls_inline_encoder.d.ts \
      --bind \
      -s NO_EXIT_RUNTIME=1 \
      -s DISABLE_EXCEPTION_CATCHING=1 \
      -s MALLOC=emmalloc \
      -s ALLOW_MEMORY_GROWTH=1 \
      -s ASSERTIONS=0 \
      -s FILESYSTEM=0 \
      -s EXPORTED_FUNCTIONS=[] \
      -s EXPORTED_RUNTIME_METHODS=[ccall] \
      -s SINGLE_FILE=1 \
      -s MODULARIZE=1 \
      -s EXPORT_ES6=0 \
      -s EXPORT_NAME=CharLSEncoder \
   ")


# ecoder with export default & inline file
add_executable(jls_inline_es6_encoder src/jsencode.cpp src/codec/encode.cpp)
target_compile_features(jls_inline_es6_encoder PUBLIC cxx_std_17)
target_link_libraries(jls_inline_es6_encoder PRIVATE charls)
set_target_properties(
    jls_inline_es6_encoder 
    PROPERTIES 
    LINK_FLAGS "\
      --allowJs \
      --emit-tsd jls_inline_es6_encoder.d.ts \
      --bind \
      -s NO_EXIT_RUNTIME=1 \
      -s DISABLE_EXCEPTION_CATCHING=1 \
      -s MALLOC=emmalloc \
      -s ALLOW_MEMORY_GROWTH=1 \
      -s ASSERTIONS=0 \
      -s FILESYSTEM=0 \
      -s EXPORTED_FUNCTIONS=[] \
      -s EXPORTED_RUNTIME_METHODS=[ccall] \
      -s SINGLE_FILE=1 \
      -s MODULARIZE=1 \
      -s EXPORT_ES6=1 \
      -s EXPORT_NAME=CharLSEncoder \
   ")