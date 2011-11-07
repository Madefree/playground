#include <Daisy2.h>
 
Daisy2 stepper(W3,A);
 
void setup() {
  stepper.begin();
}
 
void loop() {
 
  stepper.setSpeed(100);
  stepper.step(3000);
  stepper.invertDirection();
  stepper.step(3000);
 
}
