#include <stdlib.h>
#include "Arduino.h"
#include <HardwareSerial.h>


unsigned long prev = 0;
unsigned long elapsed = 0;




void setTime() {
  Serial.println("enter time hh:mm:ss format:");
  while (Serial.available() == 0) {
  }
  String line = Serial.readStringUntil('\n');
  unsigned int h, m, s;
  if (sscanf(line.c_str(), "%u:%u:%u", &h, &m, &s) == 3) {
    elapsed = h * 3600UL + m * 60UL + s;
    Serial.print("time: ");
    Serial.println(line);
  } else {
    Serial.println("invalid format - 00:00:00");
  }
}

unsigned int* getTime() {
  unsigned long curr = millis();
  unsigned int* time = (unsigned int * )malloc(sizeof(unsigned int)*2);
  if (curr - prev >= 1000) {
    prev += 1000;
    elapsed++;

    unsigned int hours = (elapsed / 3600) % 24;
    unsigned int minutes = (elapsed / 60) % 60;
    unsigned int seconds = elapsed % 60;

    time[0]= hours;
    time[1]= minutes;
    return time;
  }
  return time;
}
