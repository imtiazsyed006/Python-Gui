#include <Wire.h>
#define address 0x1E

float x,y,z,arg,angle_x,angle_y,angle_z,eighty,sixty;
//double angle_1,angle_2,angle_3;
//int finalangle_1,finalangle_2,finalangle_3;
float offset_x,offset_y,offset_z;
float scale_x,scale_y,scale_z;
float xnew,ynew,znew;
int temp_x,temp_y,temp_z;

void setup(){
  Serial.begin(9600);
  Wire.begin();

  magSetting(0x00,B01101000);
  magSetting(0x01,B01100000);
}

void loop(){
  getReadings();
  x_angle();
  y_angle();
  z_angle();
  printReadings();

}

void getReadings(){
    magSetting(0x02,0x01);
    Wire.requestFrom(address,6);
  if(Wire.available()>5){
    x = readValue();
    y = readValue();
    z = readValue();
    scale_x = 0.9939;
    scale_y = 1.0933;
    scale_z = 1.0012;

    offset_x = -182;
    offset_y = -71;
    offset_z = -139;
    xnew = (x-offset_x)*scale_x;
    ynew = (y-offset_y)*scale_y;
    znew = (z-offset_z)*scale_z;
  }
  else {
    Serial.println("0,0,0");
  }
}
 

int readValue(){
  int val = Wire.read()<<8;
      val|=Wire.read();
      return val;
      
}
void magSetting(byte regloc, byte setting){
  Wire.beginTransmission(address);
  Wire.write(regloc);
  Wire.write(setting);
  Wire.endTransmission();
  delay(10);
}

void printReadings(){
  String dat;
  //dat = String(finalangle_1)+" s "+String(finalangle_2)+'s'+String(finalangle_3);
  dat = String(temp_x)+","+String(temp_y)+","+String(temp_z);
  Serial.println(dat);
  delay(100);
  
}
void x_angle(){
      if (ynew > 0 & xnew > 0){
      arg = ynew/xnew;
      angle_x = atan(ynew/xnew);
      temp_x = abs(angle_x)*180/3.14;
    }
    else if(ynew > 0 & xnew < 0){
      arg = ynew/xnew;
      angle_x = atan(arg);
      temp_x = 180 - abs(angle_x)*180/3.14;
    }
    else if(ynew < 0 & xnew < 0){
      arg = ynew/xnew;
      angle_x = atan(arg);
      temp_x = 180 + abs(angle_x)*180/3.14;
    }
    else if(ynew < 0 & xnew > 0){
      arg = ynew/xnew;
      angle_x = atan(arg);
      temp_x = 360 - abs(angle_x)*180/3.14;
    }
    else if(ynew > 0 & xnew == 0){
      angle_x = 90;
    }
    else if(ynew < 0 & xnew == 0){
      angle_x = 270;
    }
    else if(ynew == 0 & xnew > 0){
      angle_x = 0;
    }
    else if(ynew == 0 & xnew < 0){
      angle_x = 180;
    }
}

void y_angle(){
      if (xnew > 0 & znew > 0){
      arg = znew/xnew;
      angle_y = atan(znew/xnew);
      temp_y = abs(angle_y)*180/3.14;
    }
    else if(xnew > 0 & znew < 0){
      arg = znew/xnew;
      angle_y = atan(arg);
      temp_y = 360 - abs(angle_y)*180/3.14;
    }
    else if(xnew < 0 & znew < 0){
      arg = znew/xnew;
      angle_y = atan(arg);
      temp_y = 180 + abs(angle_y)*180/3.14;
    }
    else if(xnew < 0 & znew > 0){
      arg = znew/xnew;
      angle_y = atan(arg);
      temp_y = 180 - abs(angle_y)*180/3.14;
    }
    else if(xnew > 0 & znew == 0){
      angle_y = 0;
    }
    else if(xnew < 0 & znew == 0){
      angle_y = 180;
    }
    else if(xnew == 0 & znew > 0){
      angle_y = 90;
    }
    else if(xnew == 0 & znew < 0){
      angle_y = 270;
    }
}

void z_angle(){
      if (ynew > 0 & znew > 0){
      arg = ynew/znew;
      angle_z = atan(ynew/znew);
      temp_z = abs(angle_z)*180/3.14;
    }
    else if(ynew > 0 & znew < 0){
      arg = ynew/znew;
      angle_z = atan(arg);
      temp_z = 180 - abs(angle_z)*180/3.14;
    }
    else if(ynew < 0 & znew < 0){
      arg = ynew/znew;
      angle_z = atan(arg);
      temp_z = 180 + abs(angle_z)*180/3.14;
    }
    else if(ynew < 0 & znew > 0){
      arg = ynew/znew;
      angle_z = atan(arg);
      temp_z = 360 - abs(angle_z)*180/3.14;
    }
    else if(ynew > 0 & znew == 0){
      angle_z = 90;
    }
    else if(ynew < 0 & znew == 0){
      angle_z = 270;
    }
    else if(ynew == 0 & znew > 0){
      angle_z = 0;
    }
    else if(ynew == 0 & znew < 0){
      angle_z = 180;
    }
}
