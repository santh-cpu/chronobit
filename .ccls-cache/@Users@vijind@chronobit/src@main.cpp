#include "Arduino.h"
#include "FastLED.h"
#define NUM_LEDS 64

//CRGB leds[64];

void setup(){
	  //FastLED.addLeds<WS2812, 2>(leds, NUM_LEDS);
	pinMode(3,OUTPUT);
}

void loop(){
	digitalWrite(3, HIGH);
	  //leds[0] = CRGB::Red; FastLED.show(); delay(500);
	  //leds[0] = CRGB::Blue; FastLED.show(); delay(500);
}
