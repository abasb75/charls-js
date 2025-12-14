# @abasb75/charls

A JavaScript/TypeScript package built on top of the CharLS reference implementation, providing full client-side JPEG-LS encoding and decoding capabilities using WebAssembly.

Perfect for web applications that need lossless or near-lossless image compression (e.g., DICOM viewers, medical imaging tools, or any project dealing with high-fidelity image data).

<p>
  <a href="https://abasb75.github.io/charls-js/" target="_blank">
    CharLS JavaScript implementation
  </a>
</p>


Installation
Bash

```bash
npm install @abasb75/charls

```

## How to use

Your project must support ES modules (e.g., Vite, Webpack, Next.js, etc.).
The bundler should correctly handle WASM files (using ?url import is required).
Usage
Required Imports

```typescript

import CharLSDecoder from "@abasb75/charls/decode";
import CharLSEncoder from "@abasb75/charls/encode";
import decoderUrl from "@abasb75/charls/jls_decoder.wasm?url";
import encoderUrl from "@abasb75/charls/jls_encoder.wasm?url";

let decoderInstance: any = null;
let encoderInstance: any = null;
let decodeFn: any = null;
let encodeFn: any = null;
    
async function decodeAndReencode(pixelData: DataView): Promiseuint8array {
    // Load decoder if not already loaded
    if (!decoderInstance) {
        decoderInstance = await CharLSDecoder({
            locateFile: () => new URL(decoderUrl, import.meta.url).href
        });
        decodeFn = decoderInstance.decode;
    }

    // Load encoder if not already loaded
    if (!encoderInstance) {
        encoderInstance = await CharLSEncoder({
            locateFile: () => new URL(encoderUrl, import.meta.url).href
        });
        encodeFn = encoderInstance.encode;
    }

    const buffer = new Uint8Array(pixelData.buffer, pixelData.byteOffset, pixelData.byteLength);

    // Decode
    const decoded = await decodeFn(buffer);

    // Re-encode (useful for validation)
    const encoded = await encodeFn(
        decoded.data,
        decoded.width,
        decoded.height,
        decoded.components,
        decoded.bitsPerSample,
        decoded.interleave_mode,
        decoded.nearLossless || 0
    );

    // Decode again to get final pixel data
    const final = await decodeFn(encoded.data);

    return final.data;
}
```


## Javascript

```html
  <script src="./dist/jls_decoder.js"></script>
  <script src="./dist/jls_encoder.js"></script>
  <script type="module">

    let decode = null;
    let encode = null;

    async function init() {
      const decoderModule = await CharLSDecoder();
      const encoderModule = await CharLSEncoder();
      decode = decoderModule.decode;
      encode = encoderModule.encode;
    }

    await init();
</script>
```