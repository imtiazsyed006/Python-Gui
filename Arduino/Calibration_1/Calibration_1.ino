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
  myservo.attach(9);
  myservo.write(0);
  writeRegister(L3G4200D_Address,CTRL_REG1,0b00001111);
  writeRegister(L3G4200D_Address, CTRL_REG4,0b0011000);
  delay(1500);
  Serial.println('a');
  char a = 'b';
  while (a!='a')
  {
    a = Serial.read();
  }
}
void loop()
{
  if (Serial.available() > 0)
  {
    int mode = Serial.read();
    switch (mode)
    {
      case 'G':
        getGyroValues();
        Serial.println(x);
        Serial.println(y);
        Serial.println(y);
        break;
      case 'C':
        myservo.write(180);
        for (int i = 1; i<=50;i++)
        {
          getGyroValues();
          Serial.println(x);
          Serial.println(y);
          Serial.println(z);
        }
        myservo.write(0);
        delay(200);
        break;
    }
  }
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

  
        
