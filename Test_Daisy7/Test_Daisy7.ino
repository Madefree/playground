#include "Wire.h"
#include "Daisy7.h"

Daisy7 imu;

// Record any errors that may occur in the imu.
int error = 0;

void setup()
{
  // Initialize the serial port.
  Serial.begin(9600);
  // Start the I2C interface.
  Wire.begin();
    
  Serial.println("Setting scale to +/- 1.3 Ga");
  error = imu.MagnSetScale(1.3); // Set the scale of the imu.
  if(error != 0) // If there is an error, print it out.
    Serial.println(imu.MagnGetErrorText(error));
  
  Serial.println("Setting measurement mode to continous.");
  error = imu.MagnSetMeasurementMode(Measurement_Continuous); // Set the measurement mode to Continuous
  if(error != 0) // If there is an error, print it out.
    Serial.println(imu.MagnGetErrorText(error));
    
       imu.AccConfig();
       
  imu.GyroEnableDefault();
}

// Our main program loop.
void loop()
{
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

  // Output the data via the serial port.
  Output(raw, scaled, heading, headingDegrees);

  imu.BaroCalibration();
  float temp=imu.BaroGetTemperature(imu.bmp085ReadUT());
  float pressure = imu.BaroGetPressure(imu.bmp085ReadUP());
  float atm = pressure / 101325;
  float altitude = imu.calcAltitude(pressure);
  Serial.print("Temp: ");
  Serial.println(temp);
  Serial.print("Pressure: ");
  Serial.println(pressure);
  Serial.print("Altitude: ");
  Serial.print(altitude);

  AccelerometerRaw val;
  val=imu.Accelerometer();
  
  Serial.print("ACC X:");
  Serial.print(val.XAxis);
  Serial.print(" Y:");
  Serial.print(val.YAxis);
  Serial.print(" Z:");
  Serial.println(val.ZAxis);
   
  imu.GyroRead();

  Serial.print("GYRO X:");
  Serial.print((int)imu.g.x);
  Serial.print(" Y:");
  Serial.print((int)imu.g.y);
  Serial.print(" Z:");
  Serial.println((int)imu.g.z);
   
  Serial.println();
   
  delay(1000);

}

// Output the data down the serial port.
void Output(MagnetometerRaw raw, MagnetometerScaled scaled, float heading, float headingDegrees)
{
   Serial.print("Raw:\t");
   Serial.print(raw.XAxis);
   Serial.print("   ");   
   Serial.print(raw.YAxis);
   Serial.print("   ");   
   Serial.print(raw.ZAxis);
   Serial.print("   \tScaled:\t");
   
   Serial.print(scaled.XAxis);
   Serial.print("   ");   
   Serial.print(scaled.YAxis);
   Serial.print("   ");   
   Serial.print(scaled.ZAxis);

   Serial.print("   \tHeading:\t");
   Serial.print(heading);
   Serial.print(" Radians   \t");
   Serial.print(headingDegrees);
   Serial.println(" Degrees   \t");
}
