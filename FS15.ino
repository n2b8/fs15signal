// This #include statement was automatically added by the Particle IDE.
#include "SparkFunMicroOLED/SparkFunMicroOLED.h"

// -----------------------------------
// FS15 Signaler
// -----------------------------------

// LED Pin
int led1 = D0;

// OLED initialization
MicroOLED oled;

void setup()
{

   // Configure the pin as an output
   pinMode(led1, OUTPUT);

   // Declare Paticle functions to open up to the cloud
   Particle.function("led",ledToggle);
   Particle.function("print",printCash);

   // Just making sure the LED is off when the app starts up.
   digitalWrite(led1, LOW);
   
   // OLED setup
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.clear(PAGE);    // Clear the buffer.

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

int printCash(String cash) {
    if (cash != "") {
        oled.clear(PAGE);            // Clear the display
        
        // Center OLED cursor
        int middleX = oled.getLCDWidth() / 2;  // Get X axis center
        int middleY = oled.getLCDHeight() / 2; // Get Y axis center
        oled.setCursor(middleX - (oled.getFontWidth() * (3)), middleY - (oled.getFontWidth() / 2)); // Set cursor as close to the center as possible.
        
        oled.setFontType(0);  // Smallest font
        oled.print("$");      // Print dollar sign
        oled.print(cash);     // Print cash amount
        
        oled.display();
        return 1;
    } else return -1;
}

