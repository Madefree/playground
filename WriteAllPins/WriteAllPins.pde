#include "Daisy22.h"
#include "Wire.h"
 
Daisy22 expander(0x27); // Put Address I2C
 
void setup() {
  Serial.begin(9600);
  Serial.println("Daisy22 begin..");
  expander.begin();
  Serial.println("Looping Pin P0-P7");
}
 
void loop() { // Looping..
  expander.digitalWrite(0xFF);  // High pin P0-P7
  expander.digitalWrite(0x00);   // Low pin P0-P7
}
