#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>
#include <time.h>
#include "notification.cpp"
#include "timeFunctions.cpp"
#include "font.h"
#include "math.h"

#define DATA_PIN   12 
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  50

#define IMAGE_WIDTH 16
#define IMAGE_HEIGHT 8
#define NUM_LEDS (IMAGE_WIDTH * IMAGE_HEIGHT)

CRGB leds[NUM_LEDS];


const char* ssid     = "SamsungA22";
const char* password = "passwrdhehe";
extern unsigned long lastTimeSync;

WebServer server(80);


int XY2Index(int x,int y){
  return (7-y)+(8*x);
}


void handleNotify() {
  if (server.hasArg("msg")) {
    String message = server.arg("msg");
    Serial.println("Notification received: " + message);
    showNotification(message,leds);
    server.send(200, "text/plain", "OK: " + message);
  } else {
    server.send(400, "text/plain", "Missing msg parameter. Use /notify?msg=call");
  }
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 Control</title></head><body>";
  html += "<h2>ESP32 Notification & Clock</h2>";

  // Clock controls
  html += "<h3>Clock</h3>";
  html += "<a href=\"/clock\">Show Clock</a><br>";

  // Stopwatch controls
  html += "<h3>Stopwatch</h3>";
  html += "<a href=\"/stopwatch/start\">Start Stopwatch</a><br>";
  html += "<a href=\"/stopwatch/stop\">Stop Stopwatch</a><br>";
  html += "<a href=\"/stopwatch/reset\">Reset Stopwatch</a><br>";

  // Timer controls
  html += "<h3>Timer</h3>";
  html += "<form action=\"/timer/start\" method=\"get\">";
  html += "Duration (sec): <input type=\"text\" name=\"sec\">";
  html += "<input type=\"submit\" value=\"Start Timer\">";
  html += "</form>";
  html += "<a href=\"/timer/stop\">Stop Timer</a><br>";

  // Notification test
  html += "<h3>Notifications</h3>";
  html += "<a href=\"/notify?msg=call\">Notify: Call</a><br>";
  html += "<a href=\"/notify?msg=msg\">Notify: Message</a><br>";
  html += "<a href=\"/notify?msg=alarm\">Notify: Alarm</a><br>";

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleClock() {
  server.send(200, "text/plain", "Clock mode activated");
}

unsigned long stopwatchStart = 0;
bool stopwatchRunning = false;

void handleStopwatchStart() {
  stopwatchStart = millis();
  stopwatchRunning = true;
  server.send(200, "text/plain", "Stopwatch started!");
}

void handleStopwatchStop() {
  stopwatchRunning = false;
  server.send(200, "text/plain", "Stopwatch stopped!");
}

void handleStopwatchReset() {
  stopwatchStart = millis();
  stopwatchRunning = false;
  server.send(200, "text/plain", "Stopwatch reset!");
}

unsigned long timerDuration = 0;
unsigned long timerStart = 0;
bool timerRunning = false;

void handleTimerStart() {
  if (server.hasArg("sec")) {
    timerDuration = server.arg("sec").toInt();
    timerStart = millis();
    timerRunning = true;
    server.send(200, "text/plain", "Timer started for " + String(timerDuration) + " sec");
  } else {
    server.send(400, "text/plain", "Missing ?sec parameter");
  }
}

void handleTimerStop() {
  timerRunning = false;
  server.send(200, "text/plain", "Timer stopped");
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
  setupTime();
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.on("/",handleRoot);
  server.on("/notify",handleNotify);
  
server.on("/clock", handleClock);

server.on("/stopwatch/start", handleStopwatchStart);
server.on("/stopwatch/stop", handleStopwatchStop);
server.on("/stopwatch/reset", handleStopwatchReset);

server.on("/timer/start", handleTimerStart);
server.on("/timer/stop", handleTimerStop);
  server.begin();
  Serial.println("\nWeb Server Started! \n");
}

int iter = 0;

void loop() {
 
  if (millis() - lastTimeSync > 3600000) {  
    setupTime();
  }
  
  if (!getLocalTime(&timeinfo)) {
    timeValid = false;
  } else {
    timeValid = true;
  }
  
  struct tm time = getTime();
  server.handleClient();
  displayTime(time.tm_hour,time.tm_min,CRGB::Blue, CRGB::Green);
  FastLED.show();
  delay(500);
  FastLED.clear();
}

