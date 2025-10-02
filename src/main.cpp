#include <FastLED.h>
#include "font.h"

#define DATA_PIN   12 
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  50

#define IMAGE_WIDTH 16
#define IMAGE_HEIGHT 8
#define NUM_LEDS (IMAGE_WIDTH * IMAGE_HEIGHT)

CRGB leds[NUM_LEDS];

int XY2Index(int x,int y){
  return (7-y)+(8*x);
}

void drawNum(int num, int start_x,int start_y,CRGB color){
  if (num > 9 || num < 0)
  {
    Serial.println("ERROR:Number Out of Bounds");
    return;
  }
  const byte* font_data = font_bitmaps[num];

  for (int char_y = 0 ; char_y < FONT_HEIGHT;char_y++){
    for (int char_x = 0 ; char_x < FONT_WIDTH;char_x++){
      int grid_x = start_x + char_x;
      int grid_y = start_y + char_y;
      if (font_data[char_y*FONT_WIDTH+char_x]){
	if (grid_x >= 0&& grid_x<IMAGE_WIDTH&&grid_y >= 0 && grid_y<IMAGE_HEIGHT){
	  leds[XY2Index(grid_x, grid_y)] = color;
	}
      }


    }
  }

}

void displayTime(int hour,int minute,CRGB hourColor,CRGB minuteColor){
  if (minute >= 60 || hour >= 24) {
    Serial.println("ERROR:Time Out OF Bound");
    return;
  }
  int h_0 = hour%10;
  int h_1 = hour/10;
  int m_0 = minute%10;
  int m_1 = minute/10;

  drawNum(h_1, 0, 1, hourColor);
  drawNum(h_0, 4, 1, hourColor);
  drawNum(m_1, 9, 1, minuteColor);
  drawNum(m_0, 13, 1, minuteColor); 


}


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
 }
int iter = 0;
void loop() {
  if (iter > 9)
    iter =0;
  if(iter %2 == 0 ){
    displayTime(11,20,CRGB::Blue, CRGB::Green);
 }
  else{
    displayTime(11,20,CRGB::Green, CRGB::Blue);
  }
  FastLED.show();
  delay(500);
  FastLED.clear();
  iter ++;
  // Nothing to do here for a static image
}

