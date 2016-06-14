var parser = require("xml2json");

var ledStatus = 0;

// Parameters for the HTTP request to get the XML data
var fsServerParams = {
  host: process.env.SERV_HOST,
  path: process.env.SERV_PATH,
  port: process.env.SERV_PORT
};

var callback = function(response) {
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
        ledStatus = 1;
    } else {
        ledStatus = 0;
    }
    console.log(ledStatus);
  });
};