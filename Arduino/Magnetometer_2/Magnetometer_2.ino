#include <Wire.h>

int x, y, z, val;
String data;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  //send 0x3C 0x00 0x70 (8-average, 15 Hz default, normal measurement)
  Wire.begin();
  Wire.beginTransmission(0x1E);
  Wire.write(0x00);
  Wire.write(0x70);
  Wire.endTransmission();
  delay(10);
  //send 0x3C 0x01 0xA0 (Gain=5, or any other desired gain)
  Wire.beginTransmission(0x1E);
  Wire.write(0x01);
  Wire.write(0xA0);
  Wire.endTransmission();
  delay(10);
  //send 0x3C 0x02 0x00 (Continuous-measurement mode)
  Wire.beginTransmission(0x1E);
  Wire.write(0x02);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(10);

}

void loop() 
{
  
  
  Wire.requestFrom(0x1E,6);
  if (Wire.available() > 5)
  {
    x = readValue();
    y = readValue();
    z = readValue();
  }
  else 
  {
    Serial.println("No data found");
  }
  data = String(x) + "   ,   " + String(y) + "   ,   " + String(z);
  //Send 0x3C 0x03 (point to first data register 03)
  Serial.println(data);
  Wire.beginTransmission(0x1E);
  Wire.write(0x03);
  Wire.endTransmission();
  delay(100);
}

int readValue()
{
  int val = Wire.read()<<8 | Wire.read(); 
      //val |= Wire.read();

  return val;
}
  
