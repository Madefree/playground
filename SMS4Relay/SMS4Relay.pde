#include <Daisy4.h>
#include "TeltonikaTM1Q.h"
#include <NewSoftSerial.h>


Daisy4 relay1(W3,DIP1);
Daisy4 relay2(W3,DIP2);
Daisy4 relay3(W3,DIP3);
Daisy4 relay4(W3,DIP4);

void setup()
{
 //Serial connection.
 Serial.begin(9600);
 relay1.begin();
 relay2.begin();
 relay3.begin();
 relay4.begin();
 Serial.println("BEE SMS Remote Control");
 //Start configuration.
 if (gsm.begin())
   Serial.println("\nstatus=READY");
 else Serial.println("\nstatus=IDLE");
 gsm.debug(false);  //Disable gsm Serial Debug
}

void loop()
{
  
   char smsbuffer[100];
   char number[15];
   boolean auth;
   
   if(gsm.readSMSAuthPhoneBook(smsbuffer,100,number,15,auth)) {
     
     if (auth) { // Number is Authorized
       // Relay State command
       if(smsbuffer[0]=='S' && smsbuffer[1]=='T' && smsbuffer[2]=='A' && smsbuffer[3]=='T' && smsbuffer[4]=='E') {
         strcpy(smsbuffer,"Relay State\n");
         if(relay1.readState() == HIGH )
           strcat(smsbuffer,"relay1: ON\n");
         else
           strcat(smsbuffer,"relay1: OFF\n");
         if(relay2.readState() == HIGH )
           strcat(smsbuffer,"relay2: ON\n");
         else
           strcat(smsbuffer,"relay2: OFF\n");
         if(relay3.readState() == HIGH )
           strcat(smsbuffer,"relay3: ON\n");
         else
           strcat(smsbuffer,"relay3: OFF\n");
         if(relay4.readState() == HIGH )
           strcat(smsbuffer,"relay4: ON\n");
         else
           strcat(smsbuffer,"relay4: OFF\n");
          
           gsm.sendSMS(number,smsbuffer);  // Replay SMS with Relay STATE info
       
       } else if(smsbuffer[0]=='S' && smsbuffer[1]=='E' && smsbuffer[2]=='T' && smsbuffer[3]==':' ) {
         if(smsbuffer[4]=='0') {
           relay1.relayOff();
         } else if(smsbuffer[4]=='1') {
           relay1.relayOn();
         }
         if(smsbuffer[5]=='0') {
           relay2.relayOff();
         } else if(smsbuffer[5]=='1') {
           relay2.relayOn();
         }
         if(smsbuffer[6]=='0') {
           relay3.relayOff();
         } else if(smsbuffer[6]=='1') {
           relay3.relayOn();
         }
         if(smsbuffer[7]=='0') {
           relay4.relayOff();
         } else if(smsbuffer[7]=='1') {
           relay4.relayOn();
         }
       }else
         Serial.println("SMS Syntax ERROR");
         
       
     }
     else {
       Serial.print("Number ");
       Serial.print(number);
       Serial.println(" is not authorized!");
     }
     
   }
}
     

