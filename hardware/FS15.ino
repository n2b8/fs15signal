// This #include statement was automatically added by the Particle IDE.
#include "neopixel/neopixel.h"

// This #include statement was automatically added by the Particle IDE.
#include "SparkFunMicroOLED/SparkFunMicroOLED.h"

// -----------------------------------
// FS15 Signaler
// -----------------------------------

// variables
char users[10];
char cash[10];
int neoCommand = 0;

// OLED initialization
#define PIN_RESET D5  // Connect RST to pin 7 (req. for SPI and I2C)
#define PIN_DC    D4  // Connect DC to pin 6 (required for SPI)
#define PIN_CS    A2 // Connect CS to pin A2 (required for SPI)
MicroOLED oled(MODE_SPI, PIN_RESET, PIN_DC, PIN_CS);

// NeoPixel Ring
#define PIXEL_COUNT 24
#define PIXEL_PIN D6
#define PIXEL_TYPE WS2812B
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
uint32_t fire_color   = strip.Color ( 80,  35,  00);
uint32_t off_color    = strip.Color (  0,  0,  0);

//
// NeoFire
// Thanks to http://www.arduinoslovakia.eu/blog/2015/9/simulacia-ohna
//
class NeoFire
{
  Adafruit_NeoPixel &strip;
 public:

  NeoFire(Adafruit_NeoPixel&);
  void Draw();
  void Clear();
  void AddColor(uint8_t position, uint32_t color);
  void SubstractColor(uint8_t position, uint32_t color);
  uint32_t Blend(uint32_t color1, uint32_t color2);
  uint32_t Substract(uint32_t color1, uint32_t color2);
};

///
/// Constructor
///
NeoFire::NeoFire(Adafruit_NeoPixel& n_strip)
: strip (n_strip)
{
}

///
/// Set all colors
///
void NeoFire::Draw()
{
Clear();

for(int i=0;i<PIXEL_COUNT;i++)
  {
  AddColor(i, fire_color);
  int r = random(80);
  uint32_t diff_color = strip.Color ( r, r/2, r/2);
  SubstractColor(i, diff_color);
  }
  
strip.show();
}

///
/// Set color of LED
///
void NeoFire::AddColor(uint8_t position, uint32_t color)
{
uint32_t blended_color = Blend(strip.getPixelColor(position), color);
strip.setPixelColor(position, blended_color);
}

///
/// Set color of LED
///
void NeoFire::SubstractColor(uint8_t position, uint32_t color)
{
uint32_t blended_color = Substract(strip.getPixelColor(position), color);
strip.setPixelColor(position, blended_color);
}

///
/// Color blending
///
uint32_t NeoFire::Blend(uint32_t color1, uint32_t color2)
{
uint8_t r1,g1,b1;
uint8_t r2,g2,b2;
uint8_t r3,g3,b3;

r1 = (uint8_t)(color1 >> 16),
g1 = (uint8_t)(color1 >>  8),
b1 = (uint8_t)(color1 >>  0);

r2 = (uint8_t)(color2 >> 16),
g2 = (uint8_t)(color2 >>  8),
b2 = (uint8_t)(color2 >>  0);

return strip.Color(constrain(r1+r2, 0, 255), constrain(g1+g2, 0, 255), constrain(b1+b2, 0, 255));
}

///
/// Color blending
///
uint32_t NeoFire::Substract(uint32_t color1, uint32_t color2)
{
uint8_t r1,g1,b1;
uint8_t r2,g2,b2;
uint8_t r3,g3,b3;
int16_t r,g,b;

r1 = (uint8_t)(color1 >> 16),
g1 = (uint8_t)(color1 >>  8),
b1 = (uint8_t)(color1 >>  0);

r2 = (uint8_t)(color2 >> 16),
g2 = (uint8_t)(color2 >>  8),
b2 = (uint8_t)(color2 >>  0);

r=(int16_t)r1-(int16_t)r2;
g=(int16_t)g1-(int16_t)g2;
b=(int16_t)b1-(int16_t)b2;
if(r<0) r=0;
if(g<0) g=0;
if(b<0) b=0;

return strip.Color(r, g, b);
}

///
/// Every LED to black
///
void NeoFire::Clear()
{
for(uint16_t i=0; i<PIXEL_COUNT; i++)
  strip.setPixelColor(i, off_color);
}

NeoFire fire(strip);

void setup()
{

    // Declare Paticle functions to open up to the cloud
    Particle.function("led",ledToggle);
    Particle.function("users",setUsers);
    Particle.function("cash",setCash);
   
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
    // Running logic to turn a neopixel ring on and off
    if (neoCommand==1) {
        lightThisCandle();
    }
    else {
        fire.Clear();
        strip.show();
    }
}

// Function that will be called if a request is received from the cloud.
int ledToggle(String command) {

    if (command=="1") {
        neoCommand = 1;
        return 1;
    }
    else if (command=="0") {
        neoCommand = 0;
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

void lightThisCandle() {
    fire.Draw();
    delay(random(50,150));
}
