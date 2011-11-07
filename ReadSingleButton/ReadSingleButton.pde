#include <Daisy5.h>
#include <Daisy11.h>
 
Daisy5 button(W3);
Daisy11 led(W4);
 
void setup() {
  Serial.begin(9600);
  Serial.println("Daisy5 & Daisy11 begin..");
  button.begin();
  led.begin();
}
 
void loop() {
  for (int i=1; i<8; i++) {
    if (button.readButton(i) == HIGH) {
      led.ledChange(i);
      delay(200);
    }    
  }
}
