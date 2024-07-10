/*

                    CLI Software for Arduino

               A Simple Command Line Interface 
  Example functions:              
              Feature                |  CLI Usage
___________________________________________________
 Digial Write HIGH to a specific pin |  h (pin)
 Digial Write LOW to a specific pin  |  l (pin)
 Shoot command                       |  s (angle)
 Digital Read                        |  r (pin)
 Analog Read                         |  e (pin) 

               
      by Gal Arbel
      Oct 2022
*/


#include "clicli.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include <SoftwareSerial.h>

const unsigned int MAX_MESSAGE_LENGTH = 128;

SoftwareSerial mySerial(10, 11); // RX, TX

//clicli::clicli(hvacontrol &hvacontrol):myhvacontrol(hvacontrol), number(7) {

//}

void clicli::begin(int bdrate) {
   mySerial.begin(bdrate);
  //
}

void clicli::run() {
  static char message[MAX_MESSAGE_LENGTH];
  static unsigned int message_pos = 0;

  while (mySerial.available() > 0) {
    char inByte = mySerial.read();   // Read the next available byte in the serial receive buffer

    // Check for end of message character (newline)
    if (inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1)) {
      message[message_pos] = inByte;  // Add the incoming byte to our message
      message_pos++;
    } else {
      // End of message received
      message[message_pos] = '\0';  // Add null character to string

      // Debug print the received message
      Serial.print("Received message: ");
      Serial.println(message);
      
      // Parse message
      int command[7] = {0};
      int argindex = 0;
      char cmd = '\0';
      char delim[] = " ";
      char tmpmsg[MAX_MESSAGE_LENGTH];
      strcpy(tmpmsg, message);  // Copy message to temporary buffer for strtok

      char *ptr = strtok(tmpmsg, delim);
      while (ptr != NULL) {
        if (argindex == 0) {
          cmd = ptr[0];
          // Debug print the command character
          Serial.print("Command: ");
          Serial.println(cmd);
        } else if (argindex <= 7) {
          command[argindex - 1] = atoi(ptr);
          // Debug print each argument
          Serial.print("Argument ");
          Serial.print(argindex);
          Serial.print(": ");
          Serial.println(command[argindex - 1]);
        }
        argindex++;
        ptr = strtok(NULL, delim);
      }

      // Handle command
      switch (cmd) {
        case 'a': // Print arguments
          for (int i = 0; i < 6; i++) {
            Serial.print("arg");
            Serial.print(i + 1);
            Serial.print(" = ");
            Serial.println(command[i]);
          }
          break;

        // Add more cases as needed

        default:
          Serial.println("Unknown command");
          break;
      }

      // Reset for the next message
      message_pos = 0;
    }
  }
  delay(1000);
}