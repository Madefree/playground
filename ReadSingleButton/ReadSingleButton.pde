#include <Daisy5.h>

Daisy5 button(W3);

void setup() {
  Serial.begin(9600);
  Serial.println("Daisy5 begin..");
  button.begin();
}

void loop() {
  if (button.readButton(P1) == HIGH)
    Serial.println("Button P1 pressed!");
    delay(200);
}
