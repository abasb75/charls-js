import CharLSDecoder from './jls_es6_decoder.js';
import wasmUrl from './jls_decoder.wasm?url'

export interface DecodedJPEGLS {
    data: Uint8Array;
    components:number;
    height:number;
    width:number;
    interleaveMode:0|1|2;
    nearLossless:number;
    bitsPerSample:number;
}

export interface DecodeOptions{

}

var charls:any;

async function decode(imageData:Uint8Array):Promise<DecodedJPEGLS>{

    if(!charls){
        charls = await CharLSDecoder({
            locateFile: (path:any) => {
                return new URL(wasmUrl, import.meta.url).href;
            }
        });
    }

    const image = charls.decode(imageData);

    return image;

}

export default decode;