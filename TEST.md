test codecs:

g++ -std=c++17 ./src/decode_file.cpp ./src/codec/decode.cpp \
    -I/usr/local/include -L/usr/local/lib -lcharls \
    -o decode_file

test codecs:

g++ -std=c++17 ./src/encode_file.cpp ./src/codec/encode.cpp -I/usr/local/include -L/usr/local/lib -lcharls -o encod
e_file


----


encode_file <input.raw> <output.jls> <width> <height> <components> <bits> <interleave> [near]

// gray scale
./encode_file ./test-files/pixel.raw ./test-files/pixel.jls  512 512 1 16 0 0
./decode_file ./test-files/pixel.jls

./encode_file ./test-files/pixel2.raw ./test-files/pixel2.jls  256 256 3 8 1 0


./encode_file ./test-files/pixel3.raw ./test-files/pixel3.jls  10 45 1 8 0 0
./decode_file ./test-files/pixel4.jls

./encode_file ./test-files/pixel4.raw ./test-files/pixel4.jls  10 50 1 16 0 0
./decode_file ./test-files/pixel4.jls

./encode_file ./test-files/decoded.raw ./test-files/encoded.jls 128 128 1 7 0 0

