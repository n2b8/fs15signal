var http = require("http");
//var Particle = require("./particle.js");
var FarmServer = require("./fsServer.js");
var express = require("express");
//var parser = require("xml2json");

FarmServer.pollServer();
setInterval(function() { FarmServer.pollServer() }, 15000);

// // Parameters for the HTTP request to get the XML data
// var fsServerParams = {
//   host: process.env.SERV_HOST,
//   path: process.env.SERV_PATH,
//   port: process.env.SERV_PORT
// };

// // Make a call to the FS15 server
// var callback = function(response) {
//   var xml = '';
//   // Server XML data received and stored
//   response.on('data', function (chunk) {
//     xml = chunk;
//   });

//   // Reponse is complete, so we just parse out what we need and print it out here
//   response.on('end', function () {
//     var option = {
//         object: true
//     };
//     var json = parser.toJson(xml, option);
//     var int = JSON.parse(json.Server.Slots.numUsed);
//     console.log("Number of users online: ", int);
//     if (int == 0) {
//         Particle.toggleLED("0");
//         console.log("I'm being called because its 0");
//     } else {
//         Particle.toggleLED("1");
//         console.log("I'm being called because its 1");
//     }
//   });
// };

// // Call http request upon intial server startup then once every 15 seconds
// http.request(fsServerParams, callback).end();
// setInterval(function() { http.request(fsServerParams, callback).end(); }, 15000);

// Spin up the server
var router = express();
var server = http.createServer(router);
server.listen(process.env.PORT || 3000, process.env.IP || "0.0.0.0", function(){
    var addr = server.address();
    console.log("Checking for users on the FS15 server...");
})