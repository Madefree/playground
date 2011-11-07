#include "Daisy2.h"
 
// Plugged two Daisy2 to W3 with A+B configuration A+B
Daisy2 stepperX(W3,A);
Daisy2 stepperY(W3,B);
 
void setup() {
  stepperX.begin();
  stepperY.begin();
}
 
void loop() {
 
  stepperX.setSpeed(100);
  stepperY.setSpeed(100);
  stepperX.step(3000);
  stepperY.step(3000);
  stepperX.invertDirection();
  stepperY.invertDirection();
  stepperX.step(3000);
  stepperY.step(3000);
}
