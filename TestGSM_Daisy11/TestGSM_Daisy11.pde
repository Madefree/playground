#include <Daisy11.h>
#include "TeltonikaTM1Q.h"
#include <NewSoftSerial.h>

//Change this for yours
#define QUALIFIED_NUMBER "+391234567890"

char msg[160];
int numdata;

Daisy11 led(W3);

void setup() 
{
  //Serial connection.
  Serial.begin(9600);
  led.begin();
  Serial.println("GSM + Daisy11 test started");
  //Start configuration.
  gsm.debug(false);
  if (gsm.begin())
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
  
  //if (gsm.sendSMS(QUALIFIED_NUMBER, "Hi friend!"))
    //Serial.println("\nSMS sent OK");
}

void loop() 
{
  char smsbuffer[160];
  char n[20];
  char led_state[10];
  
  //Check if SMS arrived
  if(gsm.readSMS(smsbuffer, 160, n, 20))
  {
    Serial.print("Sender: ");
    Serial.println(n);
    Serial.print("Message: ");
    Serial.println(smsbuffer);
    //Parsing SMS with syntax "LED:1011100"
    if(strcmp(QUALIFIED_NUMBER,n)==0)
    {
      if(smsbuffer[0]=='L' && smsbuffer[1]=='E' && smsbuffer[2]=='D' && smsbuffer[3]==':') //LED command
      {
        for(int i=1; i<8; i++) {
          if(smsbuffer[3+i]=='0')
            led.ledOff(i);
          else if(smsbuffer[3+1]=='1')
            led.ledOn(i);
        }
      }
    }
    else
      Serial.println("Number is not authorized!");
  }
  
  //Check if Voice Call arrived
  if(gsm.readCall(n,20))
  {
    Serial.println(n);
    //Compare sender number with qualified number
    if(strcmp(QUALIFIED_NUMBER,n)==0)
    {
      for(int i=1; i<8; i++) 
        led.ledOn(i);
      delay(500);
      for(int i=1; i<8; i++) 
        led.ledOff(i);
      delay(500);
      for(int i=1; i<8; i++) 
        led.ledOn(i);
      delay(500);
      for(int i=1; i<8; i++) 
        led.ledOff(i);
      delay(500);
    }
    else
      Serial.println("Number is not authorized!");
  }
}

