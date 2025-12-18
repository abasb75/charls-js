interface EncodedJPEGLS {
    data: Uint8Array;
    size: number;
}
declare function decode(imageData: Uint8Array, width: number, height: number, components: number, bitsPerSample: number, interleaveMode?: -1 | 0 | 1 | 2, nearLossless?: number): Promise<EncodedJPEGLS>;

export { type EncodedJPEGLS, decode as default };
