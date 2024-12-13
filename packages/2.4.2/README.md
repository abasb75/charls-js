# charls-js
JS/WebAssembly build of [CharLS](https://github.com/team-charls/charls)

<a href="https://chafey.github.io/charls-js/test/browser/index.html">demo</a>


## Using generated Javascript File:
1. install From `npm`:

```bash
npm i --save charls-js
```

2. import `charls-js`:

```js
import CharLSWasm from 'charls-js'

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

import {decode} from "charls-js";

const decoded = await decode(arrayBuffer); // ArrayBuffer
console.log('decoded',decoded);


```

For see example you can use <a href="https://github.com/abasb75/charls-js/blob/master/test/browser/index.html">this link</a>


