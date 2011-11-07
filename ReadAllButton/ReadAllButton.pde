#include <Daisy5.h>

Daisy5 button(W4);

void setup() {
  Serial.begin(9600);
  Serial.println("Daisy5 begin..");
  button.begin();
}

void loop() {
  for (int i=1; i<8; i++) {
    if (button.readButton(i) == HIGH) {
        Serial.print("Pressed Button P");
        Serial.println(i-1);
        delay(200);
    }    
  }
}
