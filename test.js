//
// test — Kiwi-LibNode
// today is 7/12/12, it is now 01:25 AM
// created by TotenDev
// see LICENSE for details.
//

var Kiwi = require('./build/Release/Kiwi.node');
console.log(Kiwi.send_msg(9090,"queueIdentifier","/var/myscript.js","--test --output")); // hello world