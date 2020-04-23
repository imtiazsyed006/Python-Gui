#include <Wire.h>
#define address 0x1E

int x,y,z,xm,ym,zm,angle_d_1,angle_d_2,angle_d_3,angle,arg;
//double angle_1,angle_2,angle_3;
//int finalangle_1,finalangle_2,finalangle_3;
float offset_x,offset_y,offset_z;
float scale_x,scale_y,scale_z;
int xnew,ynew,znew;

void setup(){
  Serial.begin(9600);
  Wire.begin();

  magSetting(0x00,B01101000);
  magSetting(0x01,B01100000);
}

void loop(){
  getReadings();
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
    if (ynew > 0 & xnew > 0){
      arg = ynew/xnew;
      angle = atan(ynew/xnew);
      //angle = atan2(ynew,xnew);//*180/3.14;
    }
    else if(ynew > 0 & xnew < 0){
      xnew = -1*xnew;
      arg = ynew/xnew;
      angle = atan(arg);
      //angle = 90+atan2(ynew,xnew);//*180/3.14;
    }
    else if(ynew < 0 & xnew < 0){
      xnew = -1*xnew;
      ynew = -1*ynew;
      arg = ynew/xnew;
      angle = atan(arg);
      //angle = 180+atan2(ynew,xnew);//*180/3.14;
    }
    else if(ynew < 0 & xnew > 0){
      ynew = -1*ynew;
      arg = ynew/xnew;
      angle = atan(arg);
      //angle = 270+atan2(ynew,xnew);//*180/3.14;
    }
    else if(ynew > 0 & xnew == 0){
      angle = 90;
    }
    else if(ynew < 0 & xnew == 0){
      angle = 270;
    }
    else if(ynew == 0 & xnew > 0){
      angle = 0;
    }
    else if(ynew == 0 & xnew < 0){
      angle = 180;
    }

    
    //xm = x*0.92;
    //ym = y*0.92;
    //zm = z*0.92;
    //angle_1 = atan2(ym,xm);
    //angle_2 = atan2(zm,xm);
    //angle_3 = atan2(ym,zm);
    //if(angle_1<0){
      //angle_1 += 2*3.14;
    //}
    //if(angle_2<0){
      //angle_2 += 2*3.14;
    //}
    //if(angle_3<0){
      //angle_3 += 2*3.14;
    //}
    //angle_d_1 = angle_1*180/3.14;
    //angle_d_2 = angle_2*180/3.14;
    //angle_d_3 = angle_3*180/3.14;
    //finalangle_1 = angle_d_1;
    //finalangle_2 = angle_d_2;
    //finalangle_3 = angle_d_3;
    
  //}
  else {
    Serial.println("0,0,0");
  }
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
  dat = String(xnew)+","+String(ynew)+","+String(znew);
  
  //Serial.print(" x: ");
  //Serial.print(x);
  //Serial.print(" offset_x ");
  //Serial.print(offset_x);
  //Serial.print(" Scale_x ");
  //Serial.println(scale_x);
  //Serial.print(xnew);
  //Serial.print(",");
  //Serial.print(y);
  //Serial.print(",");
  //Serial.println(z);
  //Serial.print(" dat ");
  Serial.println(dat);
  Serial.println(angle);
  Serial.print(arg);
  //Serial.print("X: ");
  //Serial.print(finalangle_1);
  //Serial.print(" , ");
  //Serial.print("Y: ");
  //Serial.print(finalangle_2);
  //Serial.print(" , ");
  //Serial.print("Z: ");
  //Serial.print(finalangle_3);
  //Serial.print("\n");
  //Serial.println(angle);
  delay(1000);
  
}
