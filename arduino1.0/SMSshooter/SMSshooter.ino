#include "TeltonikaTM1Q.h"
#include <SoftwareSerial.h>
#include <Daisy5.h>

Daisy5 button(W3);

#define NUMBER_PRESET_1 "+390123456789"
#define SMS_PRESET_1  "SMS Preset 1"
#define NUMBER_PRESET_2 "+390123456789"
#define SMS_PRESET_2  "SMS Preset 2"
#define NUMBER_PRESET_3 "+390123456789"
#define SMS_PRESET_3  "SMS Preset 3"
#define NUMBER_PRESET_4 "+390123456789"
#define SMS_PRESET_4  "SMS Preset 4"
#define NUMBER_PRESET_5 "+390123456789"
#define SMS_PRESET_5  "SMS Preset 5"
#define NUMBER_PRESET_6 "+390123456789"
#define SMS_PRESET_6  "SMS Preset 6"
#define NUMBER_PRESET_7 "+390123456789"
#define SMS_PRESET_7  "SMS Preset 7"


void setup() 
{
  //Serial connection.
  Serial.begin(9600);
  button.begin();
  Serial.println("Bee Board SMS Relay remote control");
  //Start configuration.
  gsm.debug(false);
  if (gsm.begin())
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
};

void loop() 
{
   if(button.readButton(P1) == HIGH ) {   //  Button P1 : send SMS preset 1
     gsm.sendSMS(NUMBER_PRESET_1,SMS_PRESET_1);
     Serial.println("Send SMS Preset 1");
     delay(50);
   }
   if(button.readButton(P2) == HIGH ) {   //  Button P2 : send SMS preset 2
     gsm.sendSMS(NUMBER_PRESET_2,SMS_PRESET_2);
     Serial.println("Send SMS Preset 2");
     delay(50);
   }
   if(button.readButton(P3) == HIGH ) {   //  Button P3 : send SMS preset 3
     gsm.sendSMS(NUMBER_PRESET_3,SMS_PRESET_3);
     Serial.println("Send SMS Preset 3");
     delay(50);
   }
   if(button.readButton(P4) == HIGH ) {   //  Button P4 : send SMS preset 4
     gsm.sendSMS(NUMBER_PRESET_1,SMS_PRESET_4);
     Serial.println("Send SMS Preset 4");
     delay(50);
   }
   if(button.readButton(P5) == HIGH ) {   //  Button P5 : send SMS preset 5
     gsm.sendSMS(NUMBER_PRESET_5,SMS_PRESET_5);
     Serial.println("Send SMS Preset 5");
     delay(50);
   }
   if(button.readButton(P6) == HIGH ) {   //  Button P6 : send SMS preset 6
     gsm.sendSMS(NUMBER_PRESET_6,SMS_PRESET_6);
     Serial.println("Send SMS Preset 6");
     delay(50);
   }
   if(button.readButton(P7) == HIGH ) {   //  Button P7 : send SMS preset 7
     gsm.sendSMS(NUMBER_PRESET_7,SMS_PRESET_7);
     Serial.println("Send SMS Preset 7");
     delay(50);
   }
};

