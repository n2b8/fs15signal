var http = require("http");
var FarmServer = require("./js/fsServer.js");
var express = require("express");

// Poll the server upon start up and then every 15 seconds...FOR ETERNITY!
FarmServer.pollServer();
setInterval(function() { 
    FarmServer.pollServer();
}, 15000);

// Spin up the server
var router = express();
var server = http.createServer(router);
server.listen(process.env.PORT || 3000, process.env.IP || "0.0.0.0", function(){
    console.log("Checking for users on the FS15 server...");
    console.log("This is a test");
});