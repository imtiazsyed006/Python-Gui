#include <Wire.h>
#include <GY80.h>

GY80 sensor = GY80(); //create GY80 instance

void setup()
{
    // initialize serial communication at 115200 bits per second:
    Serial.begin(9600);
    sensor.begin();       //initialize sensors
}


void loop()
{
    GY80_scaled val = sensor.read_scaled();       //get values from all sensors
    // print out values

    Serial.print("Mag:");                         //magnetometer values
    Serial.print(val.m_x,2);
    Serial.print(',');
    Serial.print(val.m_y,2);
    Serial.print(',');
    Serial.print(val.m_z,2);
    Serial.print("\n");
  
    delay(1000);        // delay in between reads for stability
}
