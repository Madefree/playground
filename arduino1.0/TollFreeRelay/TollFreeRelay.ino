#include "TeltonikaTM1Q.h"
#include <SoftwareSerial.h>
#include <Daisy4.h>

Daisy4 relay(W3,DIP2);

void setup() 
{
  //Serial connection.
  Serial.begin(9600);
  relay.begin();
  Serial.println("Bee Board Toll free remote control");
  //Start configuration.
  gsm.debug(false);
  if (gsm.begin())
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
};

void loop() 
{
  char number[20];
  boolean auth;

  if(gsm.readCallAuthPhoneBook(number,20,auth)) {  // Important: the number stored in SIM CARD must be saved with the International prefix
                                         // Example : +391231456789  
                                         
      if(auth) {
          Serial.print("Number ");
          Serial.print(number);
          Serial.println(" authorized !");
          Serial.println("Relay ON");
          relay.relayOn();
          delay(1000);
          relay.relayOff();
          Serial.println("Relay OFF");
        
      } else {
          Serial.print("Number ");
          Serial.print(number);
          Serial.println(" is not authorized!");
      }
  }
};

