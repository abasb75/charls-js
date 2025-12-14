#include "encode.h"
#include <charls/charls.h>
#include <vector>
#include <cstring>
#include <cstdlib>

uint8_t* encode(
    const uint8_t* input,
    size_t input_size,
    int width,
    int height,
    int components,
    int bits_per_sample,
    int interleave_mode,
    int near_lossless,
    size_t* output_size
) {
    if (!input || input_size == 0 || width <= 0 || height <= 0 || (components != 1 && components != 3)){
        return nullptr;
    }

    size_t bps = (bits_per_sample + 7) / 8;
    size_t expected_size = (size_t)width * height * components * bps;
    if (input_size != expected_size) {
        return nullptr;
    }

    charls::interleave_mode ilv = charls::interleave_mode::none;
    if (components == 1) {
        ilv = charls::interleave_mode::none;
    } else {
        if (interleave_mode == -1) {
            ilv = charls::interleave_mode::sample; 
        } else {
            ilv = static_cast<charls::interleave_mode>(interleave_mode);
        }
    }

    charls::jpegls_encoder encoder;
    encoder.frame_info({(uint32_t)width, (uint32_t)height, (int32_t)bits_per_sample, (int32_t)components});
    encoder.interleave_mode(ilv);
    encoder.near_lossless((uint32_t)near_lossless);

    uint32_t stride = (uint32_t)width * components * bps;

    size_t dest_est = encoder.estimated_destination_size();
    std::vector<uint8_t> encoded(dest_est + dest_est / 2);

    encoder.destination(encoded.data(), encoded.size());

    try {
        size_t encoded_bytes = encoder.encode(input, input_size, stride);
        encoded.resize(encoded_bytes);

        uint8_t* out = (uint8_t*)malloc(encoded_bytes);
        if (out) {
            memcpy(out, encoded.data(), encoded_bytes);
            *output_size = encoded_bytes;
            return out;
        }
    } catch (...) {

    }

    return nullptr;
}