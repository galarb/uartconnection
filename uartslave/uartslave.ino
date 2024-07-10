#include "clicli.h"

clicli mycli;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial.println("Slave here!");

  mycli.begin(4800);
}

void loop() { // run over and over
  mycli.run();

  
}
