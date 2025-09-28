// this code has been tested in wowki and works
// idk how you use platform io sry

unsigned long prev = 0;
unsigned long elapsed = 0;

void setup() {
  Serial.begin(9600);

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

void loop() {
  unsigned long curr = millis();

  if (curr - prev >= 1000) {
    prev += 1000;
    elapsed++;

    unsigned int hours = (elapsed / 3600) % 24;
    unsigned int minutes = (elapsed / 60) % 60;
    unsigned int seconds = elapsed % 60;

    char buffer[9];
    sprintf(buffer, "%02u:%02u:%02u", hours, minutes, seconds);
    Serial.println(buffer);
  }
}
