#include <Adafruit_NeoPixel.h>
#define PIN        8 
#define NUMPIXELS  1 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
   pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
   pixels.clear(); // Set all pixel colors to 'off'
}

void loop() {
  delay(1000);                       // wait for a second
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    pixels.show();   
  delay(1000);                       // wait for a second
   pixels.setPixelColor(0, pixels.Color(0, 0, 0));
   pixels.show();   
}
