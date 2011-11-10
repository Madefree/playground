#include "Daisy22.h"
#include "Wire.h"
 
Daisy22 expander(0x27); // Put Address I2C
 
void setup() {
  Serial.begin(9600);
  Serial.println("Daisy22 begin..");
  expander.begin();
  Serial.println("Read P0 pin..");
  int value = expander.digitalRead(P0);
  if(value==HIGH)
    Serial.println("P0 HIGH");
  else
    Serial.println("P0 LOW"); 
}
 
void loop() {
}
