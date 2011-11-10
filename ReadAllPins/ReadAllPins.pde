#include "Daisy22.h"
#include "Wire.h"
 
Daisy22 expander(0x27); // Put Address I2C
 
void setup() {
  Serial.begin(9600);
  Serial.println("Daisy22 begin..");
  expander.begin();
  Serial.println("Read P0-P1 pin..");
  expander.digitalWrite(0x55); // Write 01010101
  int value = expander.digitalRead();
  for(int i=0; i<8; i++) {
    Serial.print("P");
    Serial.print(i);
    if(value & 1<<i)
      Serial.print(" HIGH\n");
    else
      Serial.print(" LOW\n");
  }
}
 
void loop() {
}
