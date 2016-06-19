var Particle = require("particle-api-js");
var particle = new Particle();

var token = process.env.PARTICLE_ACCESS_TOKEN;

exports.toggleLED = function(int) {
    var fnPr = particle.callFunction({ deviceId: process.env.PARTICLE_DEVICE_ID, name: 'led', argument: int, auth: token });
    
    fnPr.then(
        function(data) {
            console.log('Particle function called succesfully');
        }, function(err) {
        console.log('An error occurred:', err);
    });
};

exports.publishUsers = function(users) {
    var publishEventPr = particle.publishEvent({ name: 'users', data: {users}, auth: token });

    publishEventPr.then(
        function(data) {
            if (data.body.ok) { console.log("User quantity published succesfully"); }
        },
        function(err) {
            console.log("Failed to publish user quantity: " + err);
        }
    );
};
