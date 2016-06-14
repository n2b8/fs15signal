      _   _ ___  ____   ___             ______ _____ __ _____    _____ _                   _           
     | \ | |__ \|  _ \ / _ \           |  ____/ ____/_ | ____|  / ____(_)                 | |          
     |  \| |  ) | |_) | (_) |  ______  | |__ | (___  | | |__   | (___  _  __ _ _ __   __ _| | ___ _ __ 
     | . ` | / /|  _ < > _ <  |______| |  __| \___ \ | |___ \   \___ \| |/ _` | '_ \ / _` | |/ _ \ '__|
     | |\  |/ /_| |_) | (_) |          | |    ____) || |___) |  ____) | | (_| | | | | (_| | |  __/ |   
     |_| \_|____|____/ \___/           |_|   |_____/ |_|____/  |_____/|_|\__, |_| |_|\__,_|_|\___|_|   
                                                                          __/ |                        
                                                                         |___/                         
                         

Simple NodeJS application that monitors my Farming Simulator 15 dedicated server to see if users are online and tells a Particle Photon powered device on my desk to give a visual signal that 'farm equipment is in use'.

## Running the app

1) I recommend using Heroku

2) Be sure to update your environment variables. (This keeps important data like access tokens secret). I use the following:

    SERV_HOST - For me this is the IP address to my FS15 server.
    SERV_PORT - The port used to access my FS15 server.
    SERV_PATH - Path to the XML data holding the current stats of my FS15 server.
    PARTICLE_ACCESS_TOKEN - The access token to my Particle.io account.
    PARTICLE_DEVICE_ID - The alphanumeric string identifying my specific Particle Photon device.
    
3) If using Heroku, set up a Procfile with the following:
    
    web: node app.js

Once the app is running, it will poll the FS15 server every 15 seconds to see if anyone is currently online and playing. If there is anyone on the server, it currently tells the Particle Photon to toggle an LED on pin D0.

## Future plans...

Not sure what all I'll end up doing since this is just a bored afternoon's worth of work but I definitely plan on 3D printing an enclosure. I'd also like to add an OLED screen with a running count of the in game cash. We'll see.

www.JakeMcCaig.com