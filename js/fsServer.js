var parser = require("xml2json");
var http = require("http");
var Particle = require("./particle.js");
var addCommas = require("add-commas");
var numeral = require("numeral");

// Parameters for the HTTP request to get the XML data
var fsServerParams = {
  host: process.env.SERV_HOST,
  path: process.env.SERV_PATH,
  port: process.env.SERV_PORT
};

// Load in the english abbreviations for Numeral.js
numeral.language('en', {
    delimiters: {
        thousands: ' ',
        decimal: '.'
    },
    abbreviations: {
        thousand: 'k',
        million: 'mil',
        billion: 'bn',
        trillion: 't'
    },
    ordinal: function (number) {
            var b = number % 10;
            return (~~ (number % 100 / 10) === 1) ? 'th' :
                (b === 1) ? 'st' :
                (b === 2) ? 'nd' :
                (b === 3) ? 'rd' : 'th';
        },
        currency: {
            symbol: '$'
        }
});

// switch between languages
numeral.language('en');

// Handle the data returned from the FS15 server
var callback = function(response) {
  var xml = '';
  // Server XML data received and stored
  response.on('data', function (chunk) {
    xml += chunk;
  });

  // Reponse is complete, so we just parse out what we need and print it out here
  response.on('end', function () {
    var option = {
        object: true
    };
    var json = parser.toJson(xml, option);
    var int = JSON.parse(json.Server.Slots.numUsed);
    console.log("Number of users online:", int);
    if (int === 0) {
        Particle.toggleLED("0");
    } else {
        Particle.toggleLED("1");
    }
    var cash = JSON.parse(json.Server.money);
    console.log("Cash on hand: $" + addCommas(cash));
    Particle.setUsers(int.toString());
    if (cash.toString().length > 7) {
      Particle.setCash(numeral(cash).format('0.00 a'));
      console.log(numeral(cash).format('0.00 a'));
    } else {
      Particle.setCash(addCommas(cash.toString()));
    }
  });
};

exports.pollServer = function () {
  http.request(fsServerParams, callback).end();
};

