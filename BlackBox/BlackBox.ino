#include "Wire.h"
#include "Daisy7.h"
#include <SD.h>

#define WATCHDOG // Comment this line to disable watchdog

#ifdef WATCHDOG
#include <avr/io.h>
#include <avr/wdt.h>
#endif

#define DUMP_INTERVAL 200 // Stored value interval [ms]
#define SD_CHIPSEL 10
#define MAGN_FILE "MAG_DUMP.CSV"
#define ACC_FILE "ACC_DUMP.CSV"
#define GYRO_FILE "GYR_DUMP.CSV"
#define BARO_FILE "BAR_DUMP.CSV"

#define PIN_RESET_FILE  9//Remove old CSV file at boot

Daisy7 imu;


void setup()
{

#ifdef WATCHDOG
  wdt_enable(WDTO_4S); //Watchdog 4 secondi
#endif

#ifdef PIN_RESET_FILE
  pinMode(PIN_RESET_FILE,INPUT);
  if(digitalRead(PIN_RESET_FILE)==HIGH) {
    SD.remove(MAGN_FILE);
    SD.remove(ACC_FILE);
    SD.remove(GYRO_FILE);
    SD.remove(BARO_FILE);
  }
#endif

  Serial.begin(9600);
  // IMU begin
  imu.begin();
  
  imu.MagnSetScale(1.3); // Set the scale of the imu.
  imu.MagnSetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  
  // SD begin
  if(SD.begin(SD_CHIPSEL)) {
     String data="";
     File dataFile;
     if (!SD.exists(MAGN_FILE)) {
       dataFile = SD.open(MAGN_FILE, FILE_WRITE);
       data += "Magnetometer Dump File\n";
       data += "Raw-X,Raw-Y,Raw-Z,Scaled-X,Scaled-Y,Scaled-Z,Heading-Rad,Heading-Deg";
       dataFile.println(data);
       dataFile.close();
     } 
    
     if (!SD.exists(ACC_FILE)) {
       dataFile = SD.open(ACC_FILE, FILE_WRITE);
       data = "";
       data += "Accelerometer Dump File\n";
       data += "Raw-X,Raw-Y,Raw-Z";
       dataFile.println(data);
       dataFile.close();
     }
     if (!SD.exists(GYRO_FILE)) {
       dataFile = SD.open(GYRO_FILE, FILE_WRITE);
       data = "";
       data += "Gyroscope Dump File\n";
       data += "Raw-X,Raw-Y,Raw-Z";
       dataFile.println(data);
       dataFile.close();
     }
      if (!SD.exists(BARO_FILE)) {
       dataFile = SD.open(BARO_FILE, FILE_WRITE);
       data = "";
       data += "Barometer Dump File\n";
       data += "Temperature[C],Pressure[mb],Altitude[m]";
       dataFile.println(data);
       dataFile.close();
     }
  }
  
#ifdef WATCHDOG
  wdt_reset();
#endif
}

void loop()
{
  
#ifdef WATCHDOG
  wdt_reset();
#endif
  String data = "";
  char buff[20];
  
  File dataFile = SD.open(MAGN_FILE, FILE_WRITE);
  if(dataFile) {
     // Retrive the raw values from the imu (not scaled).
    MagnetometerRaw raw = imu.MagnReadRawAxis();
    // Retrived the scaled values from the imu (scaled to the configured scale).
    MagnetometerScaled scaled = imu.MagnReadScaledAxis();
  
    // Values are accessed like so:
    int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)

    // Calculate heading when the magnetometer is level, then correct for signs of axis.
    float heading = atan2(scaled.YAxis, scaled.XAxis);
  
    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of
    // the magnetic field in your location. Find yours here: http://www.magnetic-declination.com/

    // If you cannot find your Declination, comment out these two lines, your imu will be slightly off.
    float declinationAngle = 0.0457;
    heading += declinationAngle;
  
    // Correct for when signs are reversed.
    if(heading < 0)
      heading += 2*PI;
    
    // Check for wrap due to addition of declination.
    if(heading > 2*PI)
      heading -= 2*PI;
   
    // Convert radians to degrees for readability.
    float headingDegrees = heading * 180/M_PI; 
    dtostrf(raw.XAxis, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(raw.YAxis, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(raw.ZAxis, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(scaled.XAxis, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(scaled.YAxis, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(scaled.ZAxis, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(heading, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(headingDegrees, 4, 4, buff);
    data += buff;
    dataFile.println(data); 
  }
#ifdef WATCHDOG
   else resetBee();
#endif
  dataFile.close();
  
  data="";
  dataFile = SD.open(ACC_FILE, FILE_WRITE);
  if(dataFile) {
    AccelerometerRaw val;
    val=imu.Accelerometer();
    dtostrf(val.XAxis, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(val.YAxis, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(val.ZAxis, 4, 4, buff);
    data += buff;
    dataFile.println(data);
  }
#ifdef WATCHDOG
   else resetBee();
#endif
  dataFile.close();
  
  data=""; 
  dataFile = SD.open(GYRO_FILE, FILE_WRITE);
  if(dataFile) {
    GyroRaw g;
    g = imu.GyroRead();
    dtostrf(g.XAxis, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(g.YAxis, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(g.ZAxis, 4, 4, buff);
    data += buff;
    dataFile.println(data);
  }
#ifdef WATCHDOG
   else resetBee();
#endif
  dataFile.close();
  
  data="";
  dataFile = SD.open(BARO_FILE, FILE_WRITE);
  if(dataFile) {
    float temp=imu.BaroGetTemperature(imu.bmp085ReadUT());
    float pressure = imu.BaroGetPressure(imu.bmp085ReadUP());
    float altitude = imu.calcAltitude(pressure);
    dtostrf(temp, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(pressure/100, 4, 4, buff);
    data += buff;
    data += ",";
    dtostrf(altitude, 4, 4, buff);
    data += buff;
    dataFile.println(data);
  }
#ifdef WATCHDOG
   else resetBee();
#endif
  dataFile.close();

  delay(DUMP_INTERVAL); // Interval DUMP
}

#ifdef WATCHDOG
void resetBee() {
  while(1) {}
}
#endif

