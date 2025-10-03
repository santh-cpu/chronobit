/*
* Use: Displaying the notifications from the users device   
* Authors: Sharmin A S, Vibin Ragav
*/


#include <WebServer.h>
#include <Arduino.h>
#include <FastLED.h>


#define IMAGE_WIDTH 16
#define IMAGE_HEIGHT 8
#define NUM_LEDS (IMAGE_WIDTH * IMAGE_HEIGHT)


const long ANIM_INTERVAL = 100;  // ms per pixel

unsigned long prevMillis = 0;
int animStep = 0;
const int TOTAL_STEPS = (IMAGE_WIDTH + IMAGE_HEIGHT) * 2 - 4;  // total pixels around border

enum ChronoBitNotificationModes{
  NONE,
  ALARM,
  MESSAGE,
  CALL
};

void drawOutlineStep(CRGB* leds,int step,CRGB color); 

int XY2Index(int x,int y){
  return (7-y)+(8*x);
}

enum ChronoBitNotificationModes notifMode = NONE;

void flashColor(CRGB color,CRGB* leds, int flashes = 3, int delayMs = 1000) {
  switch (notifMode) {
    case CALL:{
      unsigned long curMillis = millis();
      if (curMillis - prevMillis >= ANIM_INTERVAL) {
        prevMillis = curMillis;
        if (animStep < TOTAL_STEPS) {
          drawOutlineStep(leds,animStep,color);
          animStep++;
        }
      }
      else {
        notifMode= NONE;
      }
      flashColor(color,leds);
      return;
    }
    default:{
      for (int i = 0; i < flashes; i++) {
        fill_solid(leds, NUM_LEDS, color);
        FastLED.show();
        delay(delayMs);
        FastLED.clear();
        delay(delayMs);
      }
      notifMode= NONE;
    }
  }
  
    
}

void drawOutlineStep(CRGB* leds,int step,CRGB color) {
  if (step < IMAGE_WIDTH) {                 // Top border
    leds[XY2Index(step, 0)] = color;
  } 
  else if (step < IMAGE_WIDTH + IMAGE_HEIGHT - 1) {  // Right border
    leds[XY2Index(IMAGE_WIDTH-1, step-IMAGE_WIDTH)] = color;
  } 
  else if (step < IMAGE_WIDTH*2 + IMAGE_HEIGHT - 2) { // Bottom border
    leds[XY2Index(IMAGE_WIDTH*2+IMAGE_HEIGHT-3-step, IMAGE_HEIGHT-1)] = color;
  } 
  else if (step < (IMAGE_WIDTH*2) + (IMAGE_HEIGHT*2) - 4) { // Left border
    leds[XY2Index(0,IMAGE_WIDTH*2+IMAGE_HEIGHT*2-5)] = color;
  }
  else{
    notifMode = NONE;
  }
}


void showNotification(String msg,CRGB* leds) {
  msg.toLowerCase();
  if (msg == "call") {
    notifMode = CALL;
    flashColor(CRGB::Red,leds,3, 250); 
  }
  else if (msg == "msg") {
    notifMode = MESSAGE;
    flashColor(CRGB::Green,leds, 3, 250); 
  }
  else if (msg == "alarm") {
    notifMode = ALARM;
    flashColor(CRGB::Blue,leds, 5, 150); 
  }
  else {
    flashColor(CRGB::Purple, leds,2, 400);
  }
}

