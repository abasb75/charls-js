# charls-js (only decoder)
JS/WebAssembly build of [CharLS](https://github.com/team-charls/charls)

<a href="https://chafey.github.io/charls-js/test/browser/index.html">demo</a>


## Using generated Javascript File:
1. install From `npm`:

```bash
npm i --save @abasb75/charls-decoder
```

2. import `@abasb75/charls-decoder`:

```js
import CharLSW5asm from '@abasb75/charls-decoder'

...
let decoder,encoder;
CharLSWasm().then(function(charlsjs) {
    decoder = new charlsjs.JpegLSDecoder();
});
...

```

# Decode

```javascript

import {decode} from "@abasb75/charls-decoder";

const decoded = await decode(arrayBuffer); // ArrayBuffer
console.log('decoded',decoded);


```

For see example you can use <a href="https://github.com/abasb75/charls-js/blob/master/test/browser/index.html">this link</a>


