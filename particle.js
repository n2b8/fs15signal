var Particle = require("particle-api-js");
var particle = new Particle();

var token;
var devicesPr = particle.listDevices({ auth: token });

exports.login = function () {
  particle.login({username: process.env.USER, password: process.env.PASS}).then(
    function(data){
        token = data.body.access_token;
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
}

