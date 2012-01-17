#include "TeltonikaTM1Q.h"
#include <NewSoftSerial.h>

#define QUALIFIED_NUMBER "+391234567890"

void setup() 
{
  //Serial connection.
  Serial.begin(9600);
  Serial.println("BeeGSM testing.");
  //Start configuration.
  gsm.debug(false);
  if (gsm.begin())
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");

};

char number[20];
char message[100];

void loop() 

{
  
  if(gsm.readCall(number, 20))
  {
      if(strcmp(QUALIFIED_NUMBER,number)==0) {
        Serial.println("Received call!");
        Serial.print("Number: ");
        Serial.println(number);
        /* Create Buffer for SMS*/
        strcpy(message,"Bee ADC Value\n");
        char val[10];
        strcat(message,"chan0: ");
        itoa(analogRead(0),val,10);
        strcat(message,val);
        strcat(message,"\n");
        strcat(message,"chan1: ");
        itoa(analogRead(1),val,10);
        strcat(message,val);
        strcat(message,"\n");
        strcat(message,"chan2: ");
        itoa(analogRead(2),val,10);
        strcat(message,val);
        strcat(message,"\n");
        strcat(message,"chan3: ");
        itoa(analogRead(3),val,10);
        strcat(message,val);
        strcat(message,"\n");
        delay(200);
        /* send SMS */
        gsm.sendSMS(number,message);
      }
    else
      Serial.println("Number is not authorized!");
   
  }
};

