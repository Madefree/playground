#include "Daisy4.h"

//Daisy4 plugged to W3 with DIP1 ON
Daisy4 relay1(W3,DIP1);
//Daisy4 plugged to W3 with DIP2 ON
Daisy4 relay2(W3,DIP2);

void setup() {
  Serial.begin(9600);
  relay1.begin();
  relay2.begin();
}

void loop() {
  relay1.relayOn();
  relay2.relayOn();
  Serial.print("Relay1 state: ");
  Serial.println(relay1.readState());
  Serial.print("Relay2 state: ");
  Serial.println(relay2.readState());
  delay(1000);
  relay1.relayOff();
  relay2.relayOff();
  Serial.print("Relay1 state: ");
  Serial.println(relay1.readState());
  Serial.print("Relay2 state: ");
  Serial.println(relay2.readState());
  delay(1000);
}
