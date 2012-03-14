#include "Wire.h"
#include "Daisy7.h"
#include "gps.h"
#include "TeltonikaTM1Q.h"
#include "SoftwareSerial.h"
#include "TimerOne.h"

#define WATCHDOG

#ifdef WATCHDOG
#include <avr/io.h>
#include <avr/wdt.h>
#define resetBee() while(1) {}
#endif

volatile boolean gps_ready = false;  // GPS decode status

void setup() {
  
#ifdef WATCHDOG
  wdt_enable(WDTO_4S);
#endif
   gsm.debug(false);      // Disable gsm Serial Hardware Debug
   Serial.begin(115200);  // GPS Baud-rate : default 115200
   gps_setup();           // init GPS
   if(!gsm.begin()) {     // Init GSM
#ifdef WATCHDOG
    resetBee();
#endif
     return;
   }

   // Timer GPS Event configuration 
   Timer1.initialize(3000);           // 1000 us
   Timer1.attachInterrupt(gpsEvent);  // GPS Event Interrupt
}

void loop() {

 char number[20];
 boolean auth;
 char smsbuff[100];
 char buff[20];

  if(gsm.readCallAuthPhoneBook(number,20,auth)) {
    if(auth) {
      if(gps_ready) { // if GPS data are valid
        // Append Latitude
        strcpy(smsbuff,"Lat: "); 
        dtostrf(gps_lat, 6, 6, buff);
        strcat(smsbuff,buff);
        // Append Longitude
        strcat(smsbuff,"\nLon: ");
        dtostrf(gps_lon, 6, 6, buff);
        strcat(smsbuff,buff);
        // Append Speed
        strcat(smsbuff,"\nSpeed : ");
        dtostrf(gps_speed, 4, 4, buff);
        strcat(smsbuff,buff);
        // Append Altitude
        strcat(smsbuff,"\nAltitude: ");
        dtostrf(gps_altitude, 4, 4, buff);
        strcat(smsbuff,buff);
        // Append GoogleMaps link for traking
        strcat(smsbuff,"\nhttp://maps.google.com/maps?q=");
        dtostrf(gps_lat, 4, 4, buff);
        strcat(smsbuff,buff);
        strcat(smsbuff,",");
        dtostrf(gps_lon, 4, 4, buff);
        strcat(smsbuff,buff);
        delay(2000); // Delay Modem GSM
        // Send SMS
        gsm.sendSMS(number,smsbuff);
        gps_ready=false;
      }
    }
  }

}

/*********  GPS Event Interrupt   *********/
void gpsEvent() {
 int val;
 while (Serial.available()) { // Empties the buffer of the Serial
   val = Serial.read();
   if (gps_decode(val)) // decode NMEA GPS data
     gps_ready = true;
 }
}
