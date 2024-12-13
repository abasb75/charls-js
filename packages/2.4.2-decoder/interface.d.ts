// TypeScript bindings for emscripten-generated code.  Automatically generated at compile time.
declare namespace RuntimeExports {
    /**
     * @param {string|null=} returnType
     * @param {Array=} argTypes
     * @param {Arguments|Array=} args
     * @param {Object=} opts
     */
    function ccall(ident: any, returnType?: (string | null) | undefined, argTypes?: any[] | undefined, args?: (IArguments | any[]) | undefined, opts?: any | undefined): any;
    let HEAPF32: any;
    let HEAPF64: any;
    let HEAP_DATA_VIEW: any;
    let HEAP8: any;
    let HEAPU8: any;
    let HEAP16: any;
    let HEAPU16: any;
    let HEAP32: any;
    let HEAPU32: any;
    let HEAP64: any;
    let HEAPU64: any;
}
interface WasmModule {
}

export interface ClassHandle {
  isAliasOf(other: ClassHandle): boolean;
  delete(): void;
  deleteLater(): this;
  isDeleted(): boolean;
  clone(): this;
}
export type FrameInfo = {
  width: number,
  height: number,
  bitsPerSample: number,
  componentCount: number
};

export interface JpegLSDecoder extends ClassHandle {
  getEncodedBuffer(_0: number): any;
  getDecodedBuffer(): any;
  decode(): void;
  getFrameInfo(): FrameInfo;
  getInterleaveMode(): number;
  getNearLossless(): number;
}

export interface JpegLSEncoder extends ClassHandle {
  getDecodedBuffer(_0: FrameInfo): any;
  setNearLossless(_0: number): void;
  setInterleaveMode(_0: number): void;
}

interface EmbindModule {
  getVersion(): string;
  JpegLSDecoder: {
    new(): JpegLSDecoder;
  };
  JpegLSEncoder: {
    new(): JpegLSEncoder;
  };
}

export type MainModule = WasmModule & typeof RuntimeExports & EmbindModule;
export default function MainModuleFactory (options?: unknown): Promise<MainModule>;

export interface DecodedJpegLS{
  frameInfo:FrameInfo,
  interleaveMode:any,
  nearLossless:any,
  decodedBuffer:ArrayBufferLike,
}

export declare function decode(imageBuffer:ArrayBuffer,): Promise<DecodedJpegLS>;

