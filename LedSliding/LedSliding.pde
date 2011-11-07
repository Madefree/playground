#include <Daisy11.h>

Daisy11 led(W4);

void setup() {
  led.begin();
}

void loop() {
  // Sliding Led
  for(int i=; i<8; i++) { // Sliding On
    led.ledOn(i);
    delay(50);
  }
  for(int i=7; i>=0; i--) { // sliding Off
    led.ledOff(i);
    delay(50);
  }
  
}
