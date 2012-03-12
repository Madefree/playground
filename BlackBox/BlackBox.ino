#include "Wire.h"
#include "Daisy7.h"
#include "gps.h"
#include "SD.h"
#include "TimerOne.h"

#define DUMP_INTERVAL 200 // Store interval [ms]
#define SD_CHIPSEL 10
#define FILE "DUMP.CSV"

Daisy7 imu; // Daisy7 object

volatile boolean gps_ready = false; // GPS decode status

void setup()
{
  Serial.begin(115200);
  gps_setup();

  // Daisy7 IMU begin
  imu.begin();

  imu.MagnSetScale(1.3); // Set the scale of the imu.
  imu.MagnSetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous

  // SD card begin
  if (SD.begin(SD_CHIPSEL))
  {     
    // Open File
    File dataFile;
    
    // CSV Header
    if (!SD.exists(FILE))
    {
      dataFile = SD.open(FILE, FILE_WRITE);
      dataFile.println(F("GPS-Time,GPS-Latitude,GPS-Longitude,GPS-Course,GPS-Speed,GPS-Altitude,Magn-X,Magn-Y,Magn-Z,Acc-X,Acc-Y,Acc-Z,Gyro-X,Gyro-Y,Gyro-Z,Temperature,Pressure,Altitude"));
      dataFile.close();
    }
  }
  
  // TimerOne init
  Timer1.initialize(1000); // 1000 us
  Timer1.attachInterrupt(gpsEvent);
}


void loop()
{
  String data = "";
  char buff[20];
 
  // Open File
  File dataFile = SD.open(FILE, FILE_WRITE);
   
  if (dataFile)
  {
    if (gps_ready)
    {
      // GPS Time
      String time = String(gps_time);
      data += time;
      data += ",";
      
      // GPS Latitude
      dtostrf(gps_lat, 4, 4, buff);
      data += buff;
      data += ",";
      
      // GPS Longitude
      dtostrf(gps_lon, 4, 4, buff);
      data += buff;
      data += ",";
      
      // GPS Course
      dtostrf(gps_course, 4, 4, buff);
      data += buff;
      data += ",";
      
      // GPS Speed
      dtostrf(gps_speed, 4, 4, buff);
      data += buff;
      data += ",";
      
      // GPS Altitude
      dtostrf(gps_altitude, 4, 4, buff);
      data += buff;
      data += ",";
      
      // Store GPS data
      dataFile.print(data);
      data = "";
      
      gps_ready = false;
    }
    else
      dataFile.print(",,,,,,");
   
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
    
    // Store Magnetometer data
    dataFile.print(data);
    data = "";

    // Retrieve the Raw Values from the Accelerometer.
    AccelerometerRaw acc;
    acc = imu.Accelerometer();
    
    // Accelerometer Raw X
    dtostrf(acc.XAxis, 4, 4, buff);
    data += buff;
    data += ",";
    
    // Accelerometer Raw Y
    dtostrf(acc.YAxis, 4, 4, buff);
    data += buff;
    data += ",";
    
    // Accelerometer Raw Z
    dtostrf(acc.ZAxis, 4, 4, buff);
    data += buff;
    data += ",";
 
    // Store Accelerometer data
    dataFile.print(data);
    data = "";

    // Retrieve the Raw Values from the Gyroscope.
    GyroRaw gyro;
    gyro = imu.GyroRead();
    
    // Gyroscope Raw X
    dtostrf(gyro.XAxis, 4, 4, buff);
    data += buff;
    data += ",";
    
    // Gyroscope Raw Y
    dtostrf(gyro.YAxis, 4, 4, buff);
    data += buff;
    data += ",";
    
    // Gyroscope Raw Z
    dtostrf(gyro.ZAxis, 4, 4, buff);
    data += buff;
    data += ",";
    
    // Store Gyroscope data
    dataFile.print(data);
    data = "";

    // Retrieve the Values from the Barometer.
    float temp = imu.BaroGetTemperature(imu.bmp085ReadUT());
    float pressure = imu.BaroGetPressure(imu.bmp085ReadUP());
    float altitude = imu.calcAltitude(pressure);
    
    // Barometer Temperature
    dtostrf(temp, 4, 4, buff);
    data += buff;
    data += ",";
    
    // Barometer Pressure
    dtostrf(pressure/100, 4, 4, buff);
    data += buff;
    data += ",";
    
    // Barometer Altitude
    dtostrf(altitude, 4, 4, buff);
    data += buff;
    
    // Store Barometer data
    dataFile.println(data);
  }
  
  // Close File
  dataFile.close();
  
  delay(DUMP_INTERVAL);
}


void gpsEvent() {
  int val;
  while (Serial.available()) {
    val = Serial.read();
    if (gps_decode(val))
      gps_ready = true;
  }
}
