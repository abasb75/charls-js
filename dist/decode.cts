import CharLSDecoder from './jls_decoder.js';

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
        charls = await CharLSDecoder();
    }

    const image = charls.decode(imageData);

    return image;

}

export default decode;