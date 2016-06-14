var Particle = require("particle-api-js");
var particle = new Particle();

var token = process.env.PARTICLE_ACCESS_TOKEN;

exports.toggleLED = function(int) {
    var fnPr = particle.callFunction({ deviceId: process.env.PARTICLE_DEVICE_ID, name: 'led', argument: int, auth: token });

    fnPr.then(
        function(data) {
            console.log('Function called succesfully:', data);
        }, function(err) {
        console.log('An error occurred:', err);
    });
};