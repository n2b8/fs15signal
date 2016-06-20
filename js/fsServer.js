var parser = require("xml2json");
var http = require("http");
var Particle = require("./particle.js");

// Parameters for the HTTP request to get the XML data
var fsServerParams = {
  host: process.env.SERV_HOST,
  path: process.env.SERV_PATH,
  port: process.env.SERV_PORT
};

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
    console.log("Cash on hand: $" + cash);
    Particle.setUsers(int.toString());
    Particle.setCash(cash.toString());
  });
};

exports.pollServer = function () {
  http.request(fsServerParams, callback).end();
};

