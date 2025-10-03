/*
* Use: Using an external NTP server to sync the device's time 
* Author: Srisanth Arulkumar
*/

#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>
#include <time.h>
#include "Arduino.h"

#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC 19800  // GMT+5:30 for India
#define DAYLIGHT_OFFSET_SEC 0

struct tm timeinfo;
bool timeValid = false;
bool colonVisible = true;
unsigned long lastColonToggle = 0;
unsigned long lastTimeSync = 0;


void setupTime() {
  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
  Serial.print("Waiting for NTP time sync");
  int attempts = 0;
  while (!getLocalTime(&timeinfo) && attempts < 10) {
    Serial.print(".");
    delay(1000);
    attempts++;
  }
  
  if (getLocalTime(&timeinfo)) {
    Serial.println("\nTime synchronized!");
    timeValid = true;
    lastTimeSync = millis();
  } else {
    Serial.println("\nFailed to obtain time");
    timeValid = false;
  }
}

struct tm getTime(){
  return timeinfo;
}


