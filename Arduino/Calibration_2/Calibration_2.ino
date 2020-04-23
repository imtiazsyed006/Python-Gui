#include <Wire.h>
#include <Servo.h>

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

int L3G4200D_Address = 105;

int x;
int y;
int z;

Servo myservo;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  myservo.attach(12);
  myservo.write(0);
  writeRegister(L3G4200D_Address,CTRL_REG1,0b00001111);
  writeRegister(L3G4200D_Address, CTRL_REG4,0b0011000);
  delay(1500);

}
void loop()
{
        getGyroValues();
        Serial.print(x);
        Serial.print(',');
        Serial.print(y);
        Serial.print(',');
        Serial.println(z);
        
}

void getGyroValues()
{
  byte xMSB = readRegister(L3G4200D_Address,0x29);
  byte xLSB = readRegister(L3G4200D_Address,0x28);
  x = ((xMSB<<8)|xLSB);
  
  byte yMSB = readRegister(L3G4200D_Address,0x2B);
  byte yLSB = readRegister(L3G4200D_Address,0x2A);
  y = ((yMSB<<8)|yLSB);
  
  byte zMSB = readRegister(L3G4200D_Address,0x2D);
  byte zLSB = readRegister(L3G4200D_Address,0x2C);
  z = ((zMSB<<8)|zLSB);
}

void writeRegister(int deviceAddress, byte address, byte val)
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(address);
  Wire.write(val);
  Wire.endTransmission();
}

int readRegister(int deviceAddress, byte address)
{
  Wire.beginTransmission(deviceAddress);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(deviceAddress,1);
  while (!Wire.available())
  {
    // waiting
  }
  return Wire.read();
}

  
        
