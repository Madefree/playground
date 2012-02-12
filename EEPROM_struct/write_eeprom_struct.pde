#include <avr/eeprom.h>

struct settings_t
{
  long time;
  int analogVal;
  float temp;
  char name[50];
  
} settings;

void setup()
{
   Serial.begin(115200);
   
   // Set Struct variable 
   settings.time=100000;
   settings.analogVal=analogRead(0);
   settings.temp=23.15;
   strcpy(settings.name,"Test EEPROM");
   
   // Write configuration in EEPROM
   eeprom_write_block((const void*)&settings, (void*)0, sizeof(settings));
   
   Serial.println("EEPROM written with this configuration:");
   Serial.print("name: ");
   Serial.println(settings.name);
   Serial.print("time: ");
   Serial.println(settings.time);
   Serial.print("analogVal: ");
   Serial.println(settings.analogVal);
   Serial.print("temp: ");
   Serial.println(settings.temp);

}
void loop()
{
}
