#include <Daisy4.h>
#include "TeltonikaTM1Q.h"
#include <NewSoftSerial.h>

char n[15];

Daisy4 relay(W3,DIP2);

void setup() 
{
  //Serial connection.
  Serial.begin(9600);
  relay.begin();
  Serial.println("BEE Toll free remote control via GSM");
  //Start configuration.
  if (gsm.begin())
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
  gsm.debug(false);  //Disable gsm Serial Debug
}

void loop() 
{
  
  if(gsm.readCall(n,20))
  {
    Serial.println(n);
    if( qualified_sim_number(n)) {  //  Important: the number stored in SIM CARD must be saved with the International prefix
                                    //  Exaple : +391231456789                                       
      relay.relayOn();
      delay(1000);
      relay.relayOff();
    }
    else
      Serial.println("Number is not authorized!");
  }
}

boolean qualified_sim_number(char *number) {
  char number_en[15];
  char info[100];
  for(int i=1; i<100; i++) {
    gsm.readPhoneBook(i,number_en,info);
    if(strcmp(number_en,number)==0) 
      return true;
  }
  return false;
}
