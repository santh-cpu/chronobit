#include <WebServer.h>
#include <Arduino.h>
#include <FastLED.h>


#define IMAGE_WIDTH 16
#define IMAGE_HEIGHT 8
#define NUM_LEDS (IMAGE_WIDTH * IMAGE_HEIGHT)



void flashColor(CRGB color,CRGB* leds, int flashes = 3, int delayMs = 300) {
  for (int i = 0; i < flashes; i++) {
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
    delay(delayMs);
    FastLED.clear();
    delay(delayMs);
  }
}


void showNotification(String msg,CRGB* leds) {
  msg.toLowerCase();
  if (msg == "call") {
    flashColor(CRGB::Red,leds,3, 250); 
  }
  else if (msg == "msg") {
    flashColor(CRGB::Green,leds, 3, 250); 
  }
  else if (msg == "alarm") {
    flashColor(CRGB::Blue,leds, 5, 150); 
  }
  else {
    flashColor(CRGB::Purple, leds,2, 400);
  }
}

