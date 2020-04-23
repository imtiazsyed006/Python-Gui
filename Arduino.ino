#include "max6675.h"
#include <TimerOne.h>

#define stepPin 15
#define dirPin 14

int ktcSO = 12;
int ktcCS1 = 5;
int ktcCLK = 13;
int ktcCS2 = 6;
int ktcCS3 = 7;
int ktcCS4 = 8;
int ktcCS5 = 9;
int ktcCS6 = 10;

MAX6675 ktc1(ktcCLK, ktcCS1, ktcSO);
MAX6675 ktc2(ktcCLK, ktcCS2, ktcSO);
MAX6675 ktc3(ktcCLK, ktcCS3, ktcSO);
MAX6675 ktc4(ktcCLK, ktcCS4, ktcSO);
MAX6675 ktc5(ktcCLK, ktcCS5, ktcSO);
MAX6675 ktc6(ktcCLK, ktcCS6, ktcSO);

volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
int flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
void flow () // Interrupt function
{
   flow_frequency++;
}

void setup() 
{
  pinMode(3,OUTPUT);
  
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(flowsensor, INPUT);
  digitalWrite(2, HIGH); // Optional Internal Pull-Up
  attachInterrupt(0, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
  currentTime = micros();
  cloopTime = currentTime;

  Serial.begin(9600);
}

int flowrate ()
{
   currentTime = micros();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000000))
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
      //Serial.print("DATA,TIME,");
     // 1_hour=1_hour*10+5;
      return(l_hour); // Print litres/hour
      //Serial.println("1");
   }
    
}

char input[20];
long spd,dist,offset,count=0;
long delaytime,steps,offset_steps;
boolean c=LOW;
void timer_setup ()
{

    Timer1.initialize(delaytime);
    Timer1.attachInterrupt(run);

}

void run ()
{
    if (count<steps)
    {
      digitalWrite(stepPin,c);
      c=!c;
      count++;
      if (count==offset_steps)
      {digitalWrite(3,HIGH);}
    }
    else
    {
      Timer1.stop();
      Timer1.detachInterrupt();
      digitalWrite(3,LOW);
      Serial.println('s');   
    }  
}


void loop() 
{
   byte size = Serial.readBytes(input,20);
   if (size>0)
   {
      spd=0;dist=0;offset=0;
      String spd_s="";
      String dist_s="";
      String offset_s="";
      String r_s="";
      int z=1,r;
      for (int i=0;i<size;)
      {
        if (z==1)
        {
          if (input[i]==';'){spd=spd_s.toInt();z++;}
          else{spd_s=spd_s+String(input[i]);}
          i=i+1;
        }
        if (z==2)
        {
          if (input[i]==';'){dist=dist_s.toInt();z++;}
          else{dist_s=dist_s+String(input[i]);}
          i=i+1;
        }
        if (z==3)
        {
          if (input[i]==';'){offset=offset_s.toInt();z++;}
          else{offset_s=offset_s+String(input[i]);}
          i=i+1;
        }
        if (z==4)
        {
          if (input[i]==';'){r=r_s.toInt();z++;break;}
          else{r_s=r_s+String(input[i]);}
          i=i+1;
        }
      }
      if (r==1)
      {
        count=0;
        delaytime=750000/spd;
        steps=(dist+offset)*80;
        offset_steps=offset*80;
        digitalWrite(dirPin,HIGH);
        timer_setup();
      }
      if (r==2)
      {
        count=0;
        delaytime=750000/spd;
        steps=(dist+offset)*80;
        offset_steps=offset*80;
        digitalWrite(dirPin,LOW);
        timer_setup();  
      }
   }
   String values;
   values=String(millis()/1000)+','+String(flowrate())+','+String(ktc1.readCelsius())+','+String(ktc2.readCelsius())
   +','+String(ktc3.readCelsius())+','+String(ktc4.readCelsius())+','+String(ktc5.readCelsius())+','+String(ktc6.readCelsius());
   Serial.println(values);
}
