var enctypex = require('./');

enctypex.encode(new Buffer('f0000000000'), new Buffer('12345'), new Buffer('123412fdsafdsafdsafdsafdsa3131'), function(e, c) {
    console.log(c);
    enctypex.decode(c, new Buffer('12345'), new Buffer('123412fdsafdsafdsafdsafdsa3131'), function(ee, ce) {
        console.log(ce.toString());
    });
});
