#Kiwi - NodeJS Wrapper [![Build Status](https://secure.travis-ci.org/TotenDev/TDevShortener-LibNode.png?branch=master)](http://travis-ci.org/TotenDev/Kiwi-LibNode)

NodeJS V8 module to send a messages to [Kiwi](https://github.com/TotenDev/Kiwi)

## Requirements

- [npm](https://github.com/isaacs/npm)
- [nodejs](https://github.com/joyent/node)
- [node-gyp](https://github.com/TooTallNate/node-gyp)

## Installation

Configure and Build

    $ node-gyp configure build


##Usage

    var Kiwi = require('./build/Release/Kiwi.node');
	if (Kiwi.send_msg(9090,"com.queueIdentifier","/var/myscript.js","--test --output")) { 
		console.log("Sent :)"); 
	}
	else { 
		console.log("Not sent :("); 
	}
	
If you don't know what this parameters are please read [`How it works`](git@github.com:TotenDev/Kiwi-LibNode.git).

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Added some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

##License

[GNU GENERAL PUBLIC LICENSE V3](Kiwi/raw/master/LICENSE)