#include <SoftPWM.h>


void setup()
{
  SoftPWMBegin();
  SoftPWMSet(8, 0); // Wing W4 pin 2 - LED-BLUE
  SoftPWMSet(7, 0); // Wing W4 pin 3 - LED-GREEN
  SoftPWMSet(2, 0); // Wing W4 pin 4 - LED-RED
}

void rgb(int r,int g,int b) {
    SoftPWMSet(2, r); 
    SoftPWMSet(7, g);
    SoftPWMSet(8, b);
}

void loop()
{
  
  // FADE RED Color
  for ( int j=0; j<2; j++) {

      for(int i=0; i<=255; i++) {
        rgb(i,0,0);
        delay(2);
      }
  
      for(int i=255; i>=0; i--) {
        rgb(i,0,0);
        delay(2);
      }  
  }
  
  // FADE GREEN Color
  for ( int j=0; j<2; j++) {

      for(int i=0; i<=255; i++) {
        rgb(0,i,0);
        delay(2);
      }
  
      for(int i=255; i>=0; i--) {
        rgb(0,i,0);
        delay(2);
      }  
  }
  
  // FADE BLUE Color
  for ( int j=0; j<2; j++) {

      for(int i=0; i<=255; i++) {
        rgb(0,0,i);
        delay(2);
      }
  
      for(int i=255; i>=0; i--) {
        rgb(0,0,i);
        delay(2);
      }  
  }
  
  // FADE YELLLOW Color
  for ( int j=0; j<2; j++) {

      for(int i=0; i<=255; i++) {
        rgb(i,i,0);
        delay(2);
      }
  
      for(int i=255; i>=0; i--) {
        rgb(i,i,0);
        delay(2);
      }  
  }  
  
  // FADE VIOLET Color
  for ( int j=0; j<2; j++) {

      for(int i=0; i<=255; i++) {
        rgb(i/2,0,i);
        delay(2);
      }
  
      for(int i=255; i>=0; i--) {
        rgb(i/2,0,i);
        delay(2);
      }  
  } 
}

