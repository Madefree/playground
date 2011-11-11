#include "Daisy4.h"

//Daisy4 plugged to W3 with DIP1 ON
Daisy4 relay(W3,DIP1);

void setup() {
  Serial.begin(9600);
  relay.begin();
}

void loop() {
  relay.relayOn();
  Serial.print("Relay state: ");
  Serial.println(relay.readState());
  delay(1000);
  relay.relayOff();
  Serial.print("Relay state: ");
  Serial.println(relay.readState());
  delay(1000);
}
