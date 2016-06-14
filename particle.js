var Particle = require("particle-api-js");
var particle = new Particle();

var token = process.env.PARTICLE_ACCESS_TOKEN;
var devicesPr = particle.listDevices({ auth: token });

exports.login = function () {
  particle.login({username: process.env.USER, password: process.env.PASS}).then(
    function(data){
        console.log('Particle Cloud log in successful. Access Key: ', data.body.access_token);
    },
    function(err) {
        console.log('Particle Cloud log in unsuccessful. Error Data: ', err);
    }
  ); 
};

exports.getDevices = function () {
    devicesPr.then(
        function(devices){
        console.log('Devices: ', devices);
    },
    function(err) {
        console.log('List devices call failed: ', err);
    }
    );
};

exports.toggleLED = function(int) {
    var fnPr = particle.callFunction({ deviceId: process.env.PARTICLE_DEVICE_ID, name: 'led', argument: int, auth: token });

    fnPr.then(
        function(data) {
            console.log('Function called succesfully:', data);
        }, function(err) {
        console.log('An error occurred:', err);
    });
};

exports.getAttributes = function() {
  var devicesPr = particle.getDevice({ deviceId: process.env.PARTICLE_DEVICE_ID, auth: token });

devicesPr.then(
  function(data){
    console.log('Device attrs retrieved successfully:', data);
  },
  function(err) {
    console.log('API call failed: ', err);
  }
)};