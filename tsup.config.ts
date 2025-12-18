import { defineConfig } from 'tsup';

export default defineConfig([
  {
    entry: { index: 'dist/encode.ts' },
    outDir: 'release/encode',
    format: ['esm'],
    dts: true,
    clean: true,
    sourcemap: false,
    minify: false,
  },
  {
    entry: { index: 'dist/decode.ts' },
    outDir: 'release/decode',
    format: ['esm'],
    dts: true,
    clean: true,
    sourcemap: false,
    minify: false,
  },
  {
    entry: { index: 'dist/encode.cts' },
    outDir: 'release/encode',
    format: ['cjs'],
    dts: true,
    clean: true,
    sourcemap: false,
    minify: false,
  },
  {
    entry: { index: 'dist/decode.cts' },
    outDir: 'release/decode',
    format: ['cjs'],
    dts: true,
    clean: true,
    sourcemap: false,
    minify: false,
  }
]);
