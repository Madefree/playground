#include "Daisy22.h"
#include "Wire.h"
 
Daisy22 expander(0x27); // Put Address I2C
 
void setup() {
  Serial.begin(9600);
  Serial.println("Daisy22 begin..");
  expander.begin();
  Serial.println("Looping Pin P0");
}
 
void loop() { // Looping..
  expander.digitalWrite(P0,HIGH);  // High pin P0
  expander.digitalWrite(P0,LOW);   // Low pin P0
}
