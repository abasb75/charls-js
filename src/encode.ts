// @ts-ignore
import CharLSEncoder from '../dist/jls_encoder.js';

export interface EncodedJPEGLS {
    data:Uint8Array;
    size:number;
}

var charls:any;
var encodeImage:any = null;

async function decode(
    imageData:Uint8Array,
    width:number,
    height:number,
    components:number,
    bitsPerSample:number,
    interleaveMode:-1|0|1|2=-1,
    nearLossless:number=0
):Promise<EncodedJPEGLS> {

    if(!charls){
        charls = await CharLSEncoder({
            locateFile: (path:any) => {
                console.log({path});
                return new URL(`../dist/${path}`, import.meta.url).href;
            }
        });
        encodeImage = charls.encode;
    }

    const image = await encodeImage(
        imageData,
        width,
        height,
        components,
        bitsPerSample,
        interleaveMode,
        nearLossless
    );

    console.log({i:2,image})

    return image;

}

export default decode;