#include "codec/encode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <filesystem>

int main(int argc, char* argv[])
{
    if (argc < 7) {
        std::cerr <<
            "Usage:\n"
            "  encode_file <input.raw> <output.jls> <width> <height> <components> <bits> [interleave] [near]\n"
            "  components: 1 (grayscale) or 3 (RGB)\n"
            "  bits: 8 or 16\n"
            "  interleave: -1=auto (recommended), 0=none, 1=line, 2=sample\n"
            "  near: near-lossless parameter, default 0 (lossless)\n";
        return 1;
    }

    const std::filesystem::path input_path{ argv[1] };
    const std::filesystem::path output_path{ argv[2] };
    const int width = std::atoi(argv[3]);
    const int height = std::atoi(argv[4]);
    const int components = std::atoi(argv[5]);
    const int bits = std::atoi(argv[6]);
    const int ilv_value = (argc >= 8) ? std::atoi(argv[7]) : -1;  // -1 = auto
    const int near_loss = (argc >= 9) ? std::atoi(argv[8]) : 0;

    // اعتبارسنجی ساده
    if (width <= 0 || height <= 0) {
        std::cerr << "Invalid width or height\n";
        return 1;
    }
    if (components != 1 && components != 3) {
        std::cerr << "Components must be 1 or 3\n";
        return 1;
    }
    
    // خواندن فایل raw
    std::ifstream input(input_path, std::ios::binary);
    if (!input) {
        std::cerr << "Cannot open input file: " << input_path << "\n";
        return 1;
    }

    std::vector<uint8_t> raw(std::istreambuf_iterator<char>(input), {});
    input.close();

    // فراخوانی تابع مرکزی encode
    size_t jls_size = 0;
    uint8_t* jls_data = ::encode(
        raw.data(),
        raw.size(),
        width,
        height,
        components,
        bits,
        ilv_value,      // -1 = auto → برای RGB به sample تبدیل می‌شه
        near_loss,
        &jls_size
    );

    if (!jls_data) {
        std::cerr << "Encoding failed!\n";
        return 1;
    }

    // نوشتن فایل .jls
    std::ofstream output(output_path, std::ios::binary);
    if (!output) {
        std::cerr << "Cannot open output file: " << output_path << "\n";
        free(jls_data);
        return 1;
    }
    output.write(reinterpret_cast<const char*>(jls_data), jls_size);
    output.close();

    std::cout << "Encoding successful!\n"
              << "Input:  " << input_path << " (" << raw.size() << " bytes)\n"
              << "Output: " << output_path << " (" << jls_size << " bytes)\n"
              << "Compression ratio: " << std::fixed << std::setprecision(2)
              << (100.0 * jls_size / raw.size()) << "% of original size\n";

    // Round-trip test اختیاری (با decoder مرکزی که داری)
    // اگر بخوای می‌تونی اینجا هم اضافه کنی، ولی فعلاً ساده نگه داشتم

    free(jls_data);  // آزاد کردن حافظه تخصیص‌شده توسط encode()
    return 0;
}