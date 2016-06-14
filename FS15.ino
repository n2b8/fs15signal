// -----------------------------------
// FS15 Signaler
// -----------------------------------

// LED Pin
int led1 = D0;

void setup()
{

   // Configure the pin as an output
   pinMode(led1, OUTPUT);

   // Declare a Particle function to open up the LED to the cloud.
   // This is saying that when we ask the cloud for the function "led", it will employ the function ledToggle() from this app.
   Particle.function("led",ledToggle);

   // Just making sure the LED is off when the app starts up.
   digitalWrite(led1, LOW);

}

// Obligitory loop() function
void loop()
{
   // Nothing to do here
}

// Function that will be called if a request is received from the cloud.
int ledToggle(String command) {

    if (command=="1") {
        digitalWrite(led1,HIGH);
        return 1;
    }
    else if (command=="0") {
        digitalWrite(led1,LOW);
        return 0;
    }
    else {
        return -1;
    }
}