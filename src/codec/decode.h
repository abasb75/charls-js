#ifndef DECODER_H
#define DECODER_H

#include <cstdint>
#include <cstddef>

uint8_t* decode(
    const uint8_t* input, 
    size_t input_size,
    int* width, 
    int* height, 
    int* components,
    int* bits_per_sample,
    int* near_lossless,
    int* interleave_mode,
    size_t* output_size
);

#endif
