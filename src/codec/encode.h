#ifndef ENCODE_H
#define ENCODE_H

#include <cstdint>
#include <cstddef>


uint8_t* encode(
    const uint8_t* input,           //(raw pixel data)
    size_t input_size,              //
    int width,
    int height,
    int components,                 // 1 or 3
    int bits_per_sample,            // 8 or 16
    int interleave_mode,            // -1 = auto, 0=none, 1=line, 2=sample
    int near_lossless,              // 
    size_t* output_size             // 
);

#endif