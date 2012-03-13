#include "Wire.h"
#include "Daisy7.h"
#include "gps.h"
#include "SD.h"
#include "TimerOne.h"

#define DUMP_INTERVAL 200 // Store interval [ms]
#define SD_CHIPSEL 10     // SD card chip select
#define FILE "DUMP.CSV"   // Dump file name
#define STATE_LED 9       // Led dump indicator
#define BUTTON 6          // pin button Start-Stop dump 

Daisy7 imu; // Daisy7 object

volatile boolean gps_ready = false;  // GPS decode status
boolean dump_active = false;         // Start-Stop Dump to SD

void setup()
{
  pinMode(STATE_LED, INPUT);
  pinMode(BUTTON, INPUT);
  
  Serial.begin(115200);  // GPS Baud-rate : default 115200
  gps_setup();           // init gps

  imu.begin();           // Daisy7 IMU begin

  imu.MagnSetScale(1.3); // Set the scale of the magnetometer.
  imu.MagnSetMeasurementMode(Measurement_Continuous); // Set MAgnetometer measurement mode to Continuous

  if (SD.begin(SD_CHIPSEL))   // SD card begin
  {
    if (digitalRead(BUTTON) == LOW)  // Reset dump file when Button is pressed at boot
    {
      SD.remove(FILE);
      pinMode(STATE_LED, OUTPUT);
      delay(500);
      pinMode(STATE_LED, INPUT);
      delay(500);
      pinMode(STATE_LED, OUTPUT);
      delay(500);
      pinMode(STATE_LED, INPUT);
      delay(1000);
    }
    
    // Open File
    File dataFile;
    
    if (!SD.exists(FILE))  // Create CSV Header
    {
      dataFile = SD.open(FILE, FILE_WRITE);
      dataFile.println(F("BEE Board BlackBox Dump CSV"));
      dataFile.print(F("Dump Interval: "));
      dataFile.print(String(DUMP_INTERVAL));
      dataFile.println(" ms");
      dataFile.println(F("GPS-Time,GPS-Latitude,GPS-Longitude,GPS-Course,GPS-Speed,GPS-Altitude,Magn-X,Magn-Y,Magn-Z,Acc-X,Acc-Y,Acc-Z,Gyro-X,Gyro-Y,Gyro-Z,Temperature,Pressure,Altitude"));
      dataFile.close();
    }
  }
  
  // Timer GPS Event configuration 
  Timer1.initialize(1000);           // 1000 us
  Timer1.attachInterrupt(gpsEvent);  // GPS Event Interrupt
}


void loop()
{
  if (digitalRead(BUTTON) == LOW) // Start-Stop Dump
  {
    dump_active = !dump_active;
    delay(1000);
  }
  
  if (dump_active)
  {
    String data = "";
    char buff[20];
   
    // Open File
    File dataFile = SD.open(FILE, FILE_WRITE);
     
    if (dataFile)
    {
      /*************  GPS Data   **************/
      if (gps_ready) // if GPS data are valid
      {
        // Append GPS Time
        String time = String(gps_time);
        data += time;
        data += ",";
        
        // Append GPS Latitude
        dtostrf(gps_lat, 4, 4, buff);
        data += buff;
        data += ",";
        
        // Append GPS Longitude
        dtostrf(gps_lon, 4, 4, buff);
        data += buff;
        data += ",";
        
        // Append GPS Course
        dtostrf(gps_course, 4, 4, buff);
        data += buff;
        data += ",";
        
        // Append GPS Speed
        dtostrf(gps_speed, 4, 4, buff);
        data += buff;
        data += ",";
        
        // Append GPS Altitude
        dtostrf(gps_altitude, 4, 4, buff);
        data += buff;
        data += ",";
        
        // Store GPS data to CSV
        dataFile.print(data);
        data = "";
        
        gps_ready = false;
      }
      else 
        dataFile.print(",,,,,,");
     
     /*************  Magnetometer Data   **************/
     
      // Retrieve the Raw Values from the Magnetometer.
      MagnetometerRaw magn = imu.MagnReadRawAxis();
      
      // Magnetometer Raw X
      dtostrf(magn.XAxis, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Magnetometer Raw Y
      dtostrf(magn.YAxis, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Magnetometer Raw Z
      dtostrf(magn.ZAxis, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Store Magnetometer data to CSV
      dataFile.print(data);
      data = "";
  
      /*************  Accelerometer Data   **************/
      
      // Retrieve the Raw Values from the Accelerometer.
      AccelerometerRaw acc;
      acc = imu.Accelerometer();
      
      // Append Accelerometer Raw X
      dtostrf(acc.XAxis, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Append Accelerometer Raw Y
      dtostrf(acc.YAxis, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Append Accelerometer Raw Z
      dtostrf(acc.ZAxis, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Store Accelerometer data to CSV
      dataFile.print(data);
      data = "";
   
      /*************  Gyroscope Data   **************/
        
      // Retrieve the Raw Values from the Gyroscope.
      GyroRaw gyro;
      gyro = imu.GyroRead();
      
      // Append Gyroscope Raw X
      dtostrf(gyro.XAxis, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Append Gyroscope Raw Y
      dtostrf(gyro.YAxis, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Append Gyroscope Raw Z
      dtostrf(gyro.ZAxis, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Store Gyroscope data to CSV
      dataFile.print(data);
      data = "";
      
      /*************  Barometer Data   **************/
  
      // Retrieve the Values from the Barometer.
      float temp = imu.BaroGetTemperature(imu.bmp085ReadUT());
      float pressure = imu.BaroGetPressure(imu.bmp085ReadUP());
      float altitude = imu.calcAltitude(pressure);
      
      // Append Barometer Temperature
      dtostrf(temp, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Append Barometer Pressure
      dtostrf(pressure/100, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Append Barometer Altitude
      dtostrf(altitude, 4, 4, buff);
      data += buff;
      
      // Store Barometer data to CSV
      dataFile.println(data);
      
      // Flash led to each write
      pinMode(STATE_LED, OUTPUT);
    }
    
    // Close File
    dataFile.close();
  }
  // Dump Interval
  delay(DUMP_INTERVAL);
  // Led Off
  pinMode(STATE_LED, INPUT);
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
