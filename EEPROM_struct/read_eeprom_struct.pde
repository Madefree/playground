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
   
   // Read stored configuration
    eeprom_read_block((void*)&settings, (void*)0, sizeof(settings));
   
   Serial.println("Read configuration:");
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
