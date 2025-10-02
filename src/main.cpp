#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>
#include "Arduino.h"
#include "font.h"
#include "./modules/timeFunctions.c"

#define DATA_PIN   12 
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  50

#define IMAGE_WIDTH 16
#define IMAGE_HEIGHT 8
#define NUM_LEDS (IMAGE_WIDTH * IMAGE_HEIGHT)

CRGB leds[NUM_LEDS];


const char* ssid     = "THINDIPARAMBATH";         // change this
const char* password = "9447199935@V";     // change this

WebServer server(80);

void flashColor(CRGB color, int flashes = 3, int delayMs = 300) {
  for (int i = 0; i < flashes; i++) {
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
    delay(delayMs);
    FastLED.clear();
    delay(delayMs);
  }
}

void showNotification(String msg) {
  
  msg.toLowerCase();
  if (msg == "call") {
    flashColor(CRGB::Red, 5, 200);  // Flash red for call
  }
  else if (msg == "msg") {
    flashColor(CRGB::Green, 3, 250); // Flash green for message
  }
  else if (msg == "alarm") {
    flashColor(CRGB::Blue, 5, 150);  // Flash blue for alarm
  }
  else {
    flashColor(CRGB::Purple, 2, 400); // Unknown -> purple
  }
}

void handleNotify() {
  if (server.hasArg("msg")) {
    String message = server.arg("msg");
    Serial.println("Notification received: " + message);
    showNotification(message);
    server.send(200, "text/plain", "OK: " + message);
  } else {
    server.send(400, "text/plain", "Missing msg parameter. Use /notify?msg=call");
  }
}

void handleRoot() {
  server.send(200, "text/html",
              "<h2>ESP32 Notification Server</h2>"
              "<p>Use <b>/notify?msg=call</b>, <b>msg</b>, or <b>alarm</b></p>");
}



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
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.on("/",handleRoot);
  server.on("/notify",handleNotify);
  server.begin();
  Serial.println("\nWeb Server Started! \n");
  setTime();
  }
int iter = 0;
void loop() {
  unsigned int* time = getTime();
  server.handleClient();
  displayTime(time[0],time[1],CRGB::Blue, CRGB::Green);
  FastLED.show();
  delay(500);
  FastLED.clear();
  // Nothing to do here for a static image
}

