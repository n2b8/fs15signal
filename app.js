var http = require("http");
var Particle = require("./particle.js");
var express = require("express");
var parser = require("xml2json");

var ledStatus = 0;
//Particle.login();

// Parameters for the HTTP request to get the XML data
var fsServerParams = {
  host: process.env.SERV_HOST,
  path: process.env.SERV_PATH,
  port: process.env.SERV_PORT
};

var callback = function(response) {
  // Log into the Particle.io Cloud
  var xml = '';
  // Server XML data received and stored
  response.on('data', function (chunk) {
    xml = chunk;
  });

  // Reponse is complete, so we just parse out what we need and print it out here
  response.on('end', function () {
    var option = {
        object: true
    };
    var json = parser.toJson(xml, option);
    var int = JSON.stringify(json.Server.Slots.numUsed);
    console.log("Number of users online: ", int);
    if (int == "0") {
        ledStatus = 0;
        Particle.toggleLED("0");
    } else {
        ledStatus = 1;
        Particle.toggleLED("1");
    }
    console.log(ledStatus);
    //Particle.toggleLED(int);
  });
};

// Call http request upon intial server startup then once every minute
http.request(fsServerParams, callback).end();
setInterval(function() { http.request(fsServerParams, callback).end(); }, 15000);

// Spin up the server
var router = express();
var server = http.createServer(router);
server.listen(process.env.PORT || 3000, process.env.IP || "0.0.0.0", function(){
    var addr = server.address();
    console.log("Checking for users on the FS15 server...");
})