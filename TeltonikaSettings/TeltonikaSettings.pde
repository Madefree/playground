/* 
  Settings up Daisy13 Teltonika module to work with BeeBoard on W4 port
    * Hold reset button
    * Plug Daisy13 to W1
    * Release reset button
    * When the Tx LED stops flashing, you can disconnect Daisy-13 to W1
    * Now the Teltonika modem is ready to work with the Bee to W4 port.
*/

void setup() {

 Serial.begin(115200);
 Serial.println("AT&K0");  // Disable DTE Flow Control
 delay(600);
 Serial.println("AT+IPR=9600"); // Set speed 9600 baud
 delay(1000);
 Serial.begin(9600);
 delay(600);
 Serial.println("AT+ICF=3,1"); // Set 8 bit data 1 stop
 delay(600);
 Serial.println("AT&W0"); // Store current configuration to profile 0
 delay(600);
 Serial.println("AT&Y0"); // Used profile 0 after hardware reset
 delay(600);
 Serial.println("AT+CPWROFF"); // Power off
 // finish

}

void loop() {}
