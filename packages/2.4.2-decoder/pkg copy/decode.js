var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
import CharLSWasm from "./charlsjs";
let charls;
export default function decode(imageBuffer) {
    return __awaiter(this, void 0, void 0, function* () {
        if (!charls) {
            charls = yield CharLSWasm();
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
        };
    });
}
