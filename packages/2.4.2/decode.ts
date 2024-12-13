import CharLSWasm from "./charlsjs";

let charls:any;

export default async function decode(imageBuffer:ArrayBuffer) {
    if(!charls){
        charls = await CharLSWasm()
    }
    const decoder = new charls.JpegLSDecoder();

    const jpeglsEncodedBitStream = new Uint8Array(imageBuffer);
    const encodedBufferInWASM = decoder.getEncodedBuffer(jpeglsEncodedBitStream.length);
    
    encodedBufferInWASM.set(jpeglsEncodedBitStream);
    
    decoder.decode();
    
    const frameInfo = decoder.getFrameInfo();
    const interleaveMode = decoder.getInterleaveMode();
    const nearLossless = decoder.getNearLossless();
    
    const decodedBuffer = decoder.getDecodedBuffer();
    decoder.delete();

    return {
        frameInfo,
        interleaveMode,
        nearLossless,
        decodedBuffer,
    }
}
