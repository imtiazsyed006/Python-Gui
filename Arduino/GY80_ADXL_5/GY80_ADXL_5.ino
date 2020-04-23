#include <Wire.h>
//--- Accelerometer Register Addresses
#define Power_Register 0x2D
#define X_Axis_Register_DATAX0 0x32 // Hexadecima address for the DATAX0 internal register.
#define X_Axis_Register_DATAX1 0x33 // Hexadecima address for the DATAX1 internal register.
#define Y_Axis_Register_DATAY0 0x34 
#define Y_Axis_Register_DATAY1 0x35
#define Z_Axis_Register_DATAZ0 0x36
#define Z_Axis_Register_DATAZ1 0x37
int ADXAddress = 0x53;  //Device address in which is also included the 8th bit for selecting the mode, read in this case.
int X0,X1,X_out;
int Y0,Y1,Y_out;
int Z1,Z0,Z_out;
float Xa,Ya,Za;
float x, y, z;
void setup() {
   Wire.begin(); // Initiate the Wire library    
  Serial.begin(9600);    
  delay(100);

  // Start I2C Transmission
  Wire.beginTransmission(ADXAddress);
  // Select bandwidth rate register
  Wire.write(0x2C);
  // Normal mode, Output data rate = 100 Hz
  Wire.write(0x0A);
  // Stop I2C transmission
  Wire.endTransmission();

  delay(10);
   Wire.beginTransmission(0x53);
  // Select data format register
  Wire.write(0x31);
  // Self test disabled, 4-wire interface, Full resolution, Range = +/-2g
  Wire.write(0x08);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
  
  Wire.beginTransmission(ADXAddress);
  Wire.write(Power_Register); // Power_CTL Register
  // Enable measurement
  Wire.write(8); // Bit D3 High for measuring enable (0000 1000)
  Wire.endTransmission();
  delay(10);
}
void loop() {
  // X-axis
  Wire.beginTransmission(ADXAddress); // Begin transmission to the Sensor 
  //Ask the particular registers for data
  Wire.write(X_Axis_Register_DATAX0);
  Wire.write(X_Axis_Register_DATAX1);  
  Wire.endTransmission(); // Ends the transmission and transmits the data from the two registers
  Wire.requestFrom(ADXAddress,2); // Request the transmitted two bytes from the two registers
  if(Wire.available()<=2) {  // 
    int val = Wire.read()<<8;
        val |= Wire.read();
         x = val;

//        val = Wire.read()<<8;
//        val |= Wire.read();
//         y = val;
//
//        val = Wire.read()<<8;
//        val |= Wire.read();
//         z = val;
  }
//  }
//  // Y-Axis
//  Wire.beginTransmission(ADXAddress); 
//  Wire.write(Y_Axis_Register_DATAY0);
//  Wire.write(Y_Axis_Register_DATAY1);  
//  Wire.endTransmission(); 
//  Wire.requestFrom(ADXAddress,2);
//  if(Wire.available()<=2) { 
//   int Y = Wire.read()<<8;
//       Y |=Wire.read();
//  }
//  // Z-Axis
//  Wire.beginTransmission(ADXAddress); 
//  Wire.write(Z_Axis_Register_DATAZ0);
//  Wire.write(Z_Axis_Register_DATAZ1);  
//  Wire.endTransmission(); 
//  Wire.requestFrom(ADXAddress,2);
//  if(Wire.available()<=2) { 
//     int Z = Wire.read()<<8;
//         Z |=Wire.read();
//  }
  // Prints the data on the Serial Monitor
  Serial.print("Xa= ");
  Serial.println(x);
//  Serial.print("   Ya= ");
//  Serial.print(y);
//  Serial.print("   Za= ");
//  Serial.println(z);
  delay(100);
}
