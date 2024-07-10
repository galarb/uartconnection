#include "clicli.h"
#include <SoftwareSerial.h>
#include <RTClib.h>

clicli mycli;
SoftwareSerial mySerial(10, 11); // RX, TX
RTC_DS3231 rtc;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("master here");
  rtc.begin();

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello master here");
}

void loop() { // run over and over
  //mycli.run();
  DateTime now = rtc.now(); //a structure to hold the time
// Send the `a` command followed by 6 float arguments
  //now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year())
  float arg1 = now.hour();
  float arg2 = now.minute();
  float arg3 = now.second();
  float arg4 = now.day();
  float arg5 = now.month();
  float arg6 = now.year();

  // Create a message string
  String message = "a ";
  message += String(arg1, 2) + " ";
  message += String(arg2, 2) + " ";
  message += String(arg3, 2) + " ";
  message += String(arg4, 2) + " ";
  message += String(arg5, 2) + " ";
  message += String(arg6, 2) + "\n";

  // Send the message
  mySerial.print(message);
  delay(100);
}
