#include "codec/decode.h"
#include <charls/charls.h>
#include <emscripten/bind.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

using namespace emscripten;

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

val wasm_decode(val input_array) {
    size_t input_size = input_array["length"].as<size_t>();
    if (input_size == 0) throw std::runtime_error("Empty input buffer");

    std::vector<uint8_t> input(input_size);
    val memoryView = val(emscripten::typed_memory_view(input_size, input.data()));
    memoryView.call<void>("set", input_array);

    int width = 0, height = 0, components = 0, bits_per_sample = 0 , near_lossless=0 , interleave_mode=0;
    size_t output_size = 0;

    uint8_t* out = ::decode(
        input.data(),
        input_size,
        &width,
        &height,
        &components,
        &bits_per_sample,
        &near_lossless,
        &interleave_mode,
        &output_size
    );
    val output_js = val(emscripten::typed_memory_view(output_size, out));

    free(out);

    val result = val::object();
    result.set("width", width);
    result.set("height", height);
    result.set("components", components);
    result.set("bitsPerSample",bits_per_sample);
    result.set("nearLossless",near_lossless);
    result.set("interleaveMode",interleave_mode);
    result.set("data", output_js);


    return result;

}

// Bindings با Embind
EMSCRIPTEN_BINDINGS(WasmDecoderBinding) {
    function("decode", &wasm_decode);
}
