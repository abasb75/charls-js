# charls-js
JS/WebAssembly build of [CharLS](https://github.com/team-charls/charls)

<a href="https://chafey.github.io/charls-js/test/browser/index.html">demo</a>


## Using generated Javascript File:
1. install From `npm`:

```bash
npm i --save @abasb75/charls
```

2. import `@abasb75/charls`:

```js
import CharLSWasm from '@abasb75/charls'

...
let decoder,encoder;
CharLSWasm().then(function(charlsjs) {
    decoder = new charlsjs.JpegLSDecoder();
    encoder = new charlsjs.JpegLSEncoder();
});
...

```

# Decode

```javascript

import {decode} from "@abasb75/charls";

const decoded = await decode(arrayBuffer); // ArrayBuffer
console.log('decoded',decoded);


```

For see example you can use <a href="https://github.com/abasb75/charls-js/blob/master/test/browser/index.html">this link</a>


# only decoder versions:

<a href="https://www.npmjs.com/package/@abasb75/charls-decoder/v/2.4.2">@abasb75/charls-decoder@2.4.2</a>


