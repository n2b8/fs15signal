// This #include statement was automatically added by the Particle IDE.
#include "neopixel/neopixel.h"

// This #include statement was automatically added by the Particle IDE.
#include "SparkFunMicroOLED/SparkFunMicroOLED.h"

// -----------------------------------
// FS15 Signaler
// -----------------------------------

// LED Pin
int led1 = D0;

// variables
char users[1];
char cash[8];

// OLED initialization
MicroOLED oled;

// NeoPixel Ring
#define PIXEL_COUNT 24
#define PIXEL_PIN D2
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);

void setup()
{

   // Configure the pin as an output
   pinMode(led1, OUTPUT);

   // Declare Paticle functions to open up to the cloud
   Particle.function("led",ledToggle);
   Particle.function("users",setUsers);
   Particle.function("cash",setCash);

   // Just making sure the LED is off when the app starts up.
   digitalWrite(led1, LOW);
   
   // OLED setup
    oled.begin();        // Initialize the OLED
    oled.clear(ALL);     // Clear the display's internal memory
    oled.clear(PAGE);    // Clear the buffer.
    
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'

}

// Obligitory loop() function
void loop()
{
    // Calling the printData function to continuously update the OLED
    printData();
    // Just calling a couple of temporary neopixel functions
    colorWipe(strip.Color(255, 0, 0), 50); // Red
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
   
    rainbow(20);
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

// This is the best way I can figure to grab the data for printing to the OLED
// If you know a better way, please submit a pull request
int setUsers(String numUsed) {
    if (numUsed != "") {
        numUsed.toCharArray(users, 10);
        return 1;
    } else {
        return -1;
    }
}

int setCash(String numCash) {
    if (numCash != "") {
        numCash.toCharArray(cash, 10);
        return 1;
    } else {
        return -1;
    }
}

// Print the stats to the OLED
void printData() {
    oled.clear(PAGE);            // Clear the display
    
    oled.setCursor(0, 0);        // Set cursor to top-left
    oled.setFontType(0);         // Smallest font
    oled.print("Users: ");       // Print Users label
    oled.setFontType(0);         // Smallest font
    oled.print(users);           // Print number of users
    oled.print("/8");            // Print total slots available
    
    oled.setCursor(0, 20);       // Repeat for cash on hand
    oled.setFontType(0);         
    oled.print("$");
    oled.setFontType(0);
    oled.print(cash);
    
    oled.display();
}

// Various neopixel functions
// These are only temporary
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

