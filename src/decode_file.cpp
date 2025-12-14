#include "codec/decode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <string>

void write_bmp_24(const std::string& filename, const uint8_t* src,
                  int width, int height, int components, int bits_per_sample)
{
    int bps = (bits_per_sample + 7)/8;
    int src_row_stride = width * components * bps;
    int dst_row_stride = width * 3;
    int padding = (4 - (dst_row_stride % 4)) % 4;
    int row_size_padded = dst_row_stride + padding;
    int pixel_data_size = row_size_padded * height;
    int file_size = 14 + 40 + pixel_data_size;

    std::ofstream out(filename, std::ios::binary);

    uint8_t bfType[2] = {'B','M'};
    out.write((char*)bfType,2);
    uint32_t bfSize = file_size;
    out.write((char*)&bfSize,4);
    uint32_t reserved = 0;
    out.write((char*)&reserved,4);
    uint32_t pixel_offset = 14 + 40;
    out.write((char*)&pixel_offset,4);

    uint32_t biSize = 40;
    out.write((char*)&biSize,4);
    int32_t biWidth = width;
    int32_t biHeight = -height;  // top-down
    out.write((char*)&biWidth,4);
    out.write((char*)&biHeight,4);
    uint16_t biPlanes = 1;
    out.write((char*)&biPlanes,2);
    uint16_t biBitCount = 24;
    out.write((char*)&biBitCount,2);
    uint32_t biCompression = 0;
    out.write((char*)&biCompression,4);
    uint32_t biSizeImage = pixel_data_size;
    out.write((char*)&biSizeImage,4);
    int32_t biXPelsPerMeter = 2835;
    int32_t biYPelsPerMeter = 2835;
    out.write((char*)&biXPelsPerMeter,4);
    out.write((char*)&biYPelsPerMeter,4);
    uint32_t biClrUsed = 0;
    uint32_t biClrImportant = 0;
    out.write((char*)&biClrUsed,4);
    out.write((char*)&biClrImportant,4);

    std::vector<uint8_t> row(dst_row_stride);
    std::vector<uint8_t> pad(padding, 0);

    // برای تبدیل 16-bit → 8-bit ساده (>>8) یا می‌تونی بعداً normalize پیشرفته اضافه کنی
    int shift_down = (bits_per_sample > 8) ? (bits_per_sample - 8) : 0;

    for (int y = 0; y < height; y++) {
        const uint8_t* src_row = src + size_t(y) * src_row_stride;

        for (int x = 0; x < width; x++) {
            uint8_t r, g, b;

            if (components == 1) {  // Grayscale
                uint16_t sample;
                if (bps == 1) {
                    sample = src_row[x];
                } else {  // bps == 2 (16-bit)
                    sample = src_row[2 * x] | (uint16_t(src_row[2 * x + 1]) << 8);
                }
                uint8_t v = uint8_t(sample >> shift_down);
                r = g = b = v;
            } else if (components == 3) {  // RGB
                if (bps == 1) {
                    r = src_row[3 * x + 0];
                    g = src_row[3 * x + 1];
                    b = src_row[3 * x + 2];
                } else {  // 16-bit RGB
                    uint16_t rr = src_row[6 * x + 0] | (uint16_t(src_row[6 * x + 1]) << 8);
                    uint16_t gg = src_row[6 * x + 2] | (uint16_t(src_row[6 * x + 3]) << 8);
                    uint16_t bb = src_row[6 * x + 4] | (uint16_t(src_row[6 * x + 5]) << 8);
                    r = uint8_t(rr >> shift_down);
                    g = uint8_t(gg >> shift_down);
                    b = uint8_t(bb >> shift_down);
                }
            }

            row[3 * x + 0] = b;
            row[3 * x + 1] = g;
            row[3 * x + 2] = r;
        }

        out.write((char*)row.data(), row.size());
        if (padding) out.write((char*)pad.data(), padding);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: ./decode_file input.jls\n";
        return 1;
    }

    // Load .jls file
    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open input file\n";
        return 1;
    }
    std::vector<uint8_t> input((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());

    int width = 0, height = 0, components = 0, bits_per_sample = 0, near_lossless =0,interleave_mode=0;
    size_t output_size = 0;

    // فرض می‌کنیم تابع decode جدیدت bits_per_sample رو هم پر می‌کنه
    // اگر هنوز پر نمی‌کنه، باید تو codec/decode.h و پیاده‌سازی‌اش اضافه کنی
    uint8_t* decoded = decode(
        input.data(),
        input.size(),
        &width,
        &height,
        &components,
        &bits_per_sample,
        &interleave_mode,
        &near_lossless, 
        &output_size
    );

    if (!decoded) {
        std::cerr << "Decode failed!\n";
        return 1;
    }

    std::cout << "Decoded: " << width << "x" << height
              << " components=" << components
              << " bits=" << bits_per_sample
              << " size=" << output_size << "\n";

    std::string bmp_file = std::string(argv[1]) + ".bmp";

    // ← اصلاح اصلی: به جای 8 ثابت، bits_per_sample واقعی پاس داده می‌شه
    write_bmp_24(bmp_file,
                 decoded,
                 width,
                 height,
                 components,
                 bits_per_sample);  // حالا درست کار می‌کنه (هم 8-bit هم 16-bit)

    std::cout << "Saved BMP → " << bmp_file << "\n";

    free(decoded);
    return 0;
}