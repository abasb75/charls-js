interface DecodedJPEGLS {
    data: Uint8Array;
    components: number;
    height: number;
    width: number;
    interleaveMode: 0 | 1 | 2;
    nearLossless: number;
    bitsPerSample: number;
}
interface DecodeOptions {
}
declare function decode(imageData: Uint8Array): Promise<DecodedJPEGLS>;

export { type DecodeOptions, type DecodedJPEGLS, decode as default };
