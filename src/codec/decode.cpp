#include "decode.h"
#include <charls/charls.h>
#include <vector>
#include <cstring>
#include <cstdlib>

static void convert_planar_to_interleaved(
    std::vector<uint8_t>& decoded,
    int width, int height,
    int bits_per_sample
) {
    int bps = (bits_per_sample + 7) / 8;
    size_t plane_size = (size_t)width * height * bps;
    std::vector<uint8_t> interleaved(plane_size * 3);

    uint8_t* R = decoded.data();
    uint8_t* G = decoded.data() + plane_size;
    uint8_t* B = decoded.data() + plane_size * 2;

    for (size_t i = 0; i < (size_t)width * height; ++i) {
        for (int k = 0; k < bps; ++k) {
            interleaved[3 * i * bps + k] = R[i * bps + k];
            interleaved[3 * i * bps + bps + k] = G[i * bps + k];
            interleaved[3 * i * bps + 2 * bps + k] = B[i * bps + k];
        }
    }

    decoded = std::move(interleaved);
}

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
){

    std::vector<uint8_t> encoded(input_size);
    std::memcpy(encoded.data(), input, input_size);

    // Initialize decoder
    charls::jpegls_decoder decoder;
    decoder.source(encoded);
    decoder.read_header();

    auto info = decoder.frame_info();
    *width = info.width;
    *height = info.height;
    *components = info.component_count;
    *bits_per_sample =info.bits_per_sample;
    *near_lossless = decoder.near_lossless();

    size_t bps = (info.bits_per_sample + 7) / 8;
    size_t decoded_size = (size_t)info.width * info.height * info.component_count * bps;

    std::vector<uint8_t> decoded(decoded_size);

    decoder.decode(decoded);
    *interleave_mode = static_cast<int>(decoder.interleave_mode());

    // If planar, convert to interleaved (RGB)
    if (info.component_count == 3 &&
        decoder.interleave_mode() == charls::interleave_mode::none) {

        convert_planar_to_interleaved(decoded, info.width, info.height, info.bits_per_sample);
    }

    // Allocate output buffer for WASM (caller frees)
    *output_size = decoded.size();
    uint8_t* out = (uint8_t*)malloc(*output_size);
    memcpy(out, decoded.data(), *output_size);

    return out;
}
