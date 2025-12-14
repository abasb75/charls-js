#include "codec/encode.h"
#include <charls/charls.h>
#include <emscripten/bind.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <stdexcept>

using namespace emscripten;

val wasm_encode(
    val input_array,           // Uint8Array
    int width,
    int height,
    int components,            // 1 or 3
    int bits_per_sample,       // 8 or 16
    int interleave_mode = -1,  // -1 = auto ، 0=none, 1=line, 2=sample
    int near_lossless = 0      // lossless
) {
    size_t input_size = input_array["length"].as<size_t>();
    if (input_size == 0) {
        throw std::runtime_error("Empty input buffer");
    }

    if (width <= 0 || height <= 0 || (components != 1 && components != 3)) {
        throw std::runtime_error("Invalid image parameters");
    }

    std::vector<uint8_t> raw_data(input_size);
    val memoryView = val(emscripten::typed_memory_view(input_size, raw_data.data()));
    memoryView.call<void>("set", input_array);

    size_t output_size = 0;
    uint8_t* jls_data = ::encode(
        raw_data.data(),
        raw_data.size(),
        width,
        height,
        components,
        bits_per_sample,
        interleave_mode, 
        near_lossless,
        &output_size
    );

    if (!jls_data) {
        throw std::runtime_error("Encoding failed (CharLS error or invalid data)");
    }

    val output_js = val(emscripten::typed_memory_view(output_size, jls_data));

    val result = val::object();
    result.set("data", output_js);
    result.set("size", static_cast<int>(output_size));

    free(jls_data);

    return result;
}

EMSCRIPTEN_BINDINGS(WasmEncoderBinding) {
    function("encode", &wasm_encode);
}