#include "Daisy2.h"
 
Daisy2 stepperX(W3,A);
Daisy2 stepperY(W3,B);
Daisy2 stepperZ(W4,A);
 
void setup() {

  stepperX.begin();
  stepperY.begin();
  stepperZ.begin();
  for(int i=0; i<10; i++) {
    stepperX.setSpeed(500);
    stepperY.setSpeed(500);
    stepperZ.setSpeed(500);
    stepperX.step(3000);
    stepperY.step(200);
    stepperZ.step(200);
    stepperX.invertDirection();
    stepperY.invertDirection();
    stepperZ.invertDirection();
    stepperX.step(3000);
    stepperY.step(200);
    stepperZ.step(200);
    }
}
 
void loop() {}
