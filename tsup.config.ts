import { defineConfig } from 'tsup';

export default defineConfig([
  {
    entry: { index: 'src/encode.ts' },
    outDir: 'package/encode',
    format: ['esm'],
    dts: true,
    clean: true,
    sourcemap: false,
    // minify: true,
  },
  {
    entry: { index: 'src/decode.ts' },
    outDir: 'package/decode',
    format: ['esm'],
    dts: true,
    clean: true,
    sourcemap: false,
    // minify: true,
  }
]);
