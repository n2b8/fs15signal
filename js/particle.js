var Particle = require("particle-api-js");
var particle = new Particle();

var token = process.env.PARTICLE_ACCESS_TOKEN;
var device = process.env.PARTICLE_DEVICE_ID

exports.toggleLED = function(int) {
    var fnPr = particle.callFunction({ deviceId: device, name: 'led', argument: int, auth: token });
    
    fnPr.then(
        function(data) {
            console.log('toggleLED function called succesfully');
        }, function(err) {
        console.log('An error occurred calling toggleLED:', err);
    });
};

exports.setUsers = function(numUsers) {
  var fnPr = particle.callFunction({ deviceId: device, name: 'users', argument: numUsers, auth: token});
  
  fnPr.then(
      function(data) {
          console.log('setUsers function called succesfully:');
      }, function(err) {
          console.log('An error occured calling setUsers:', err);
      });
};

exports.setCash = function(numCash) {
  var fnPr = particle.callFunction({ deviceId: device, name: 'cash', argument: numCash, auth: token});
  
  fnPr.then(
      function(data) {
          console.log('setCash function called succesfully: ');
      }, function(err) {
          console.log('An error occured calling setCash:', err);
      });
};