#include "MotorController.h"
#include "SpeedMeasure.h"
#include "UDPConnection.h"
int *rpm;
int *desiredSpeed;
boolean *motorRunning;
int oldSpeed;
boolean oldMotorRunning=false;
MotorController motorController(5);
SpeedMeasure speedMeasure(4,rpm);
UDPConnection udp;
void setup()
{
  Serial.begin(115200);
  Serial.println("started");
  motorController.attach();  
  udp.setup(rpm,desiredSpeed,motorRunning);
}
void loop()
{
  speedMeasure.loop();
  udp.loop();
  if(oldSpeed!=*desiredSpeed)
  {
    if(*motorRunning==1)
    {
      motorController.setSpeed(map(*desiredSpeed,0,100,900,1300));
      oldSpeed=*desiredSpeed;
    }
  }
  if(oldMotorRunning!=*motorRunning)
  {
    if(*motorRunning==1)
    {
      motorController.attach();
      motorController.setSpeed(map(*desiredSpeed,0,100,1100,1800));
      oldSpeed=*desiredSpeed;
    }
    else
    {
      motorController.detach();
    }
    oldMotorRunning=*motorRunning;
  }
 
  /*String readString;
  while (Serial.available()) {
    char c = Serial.read();  //gets one byte from serial buffer
    readString += c; //makes the string readString
    delay(1);  //slow looping to allow buffer to fill with next character
  }
  if (readString.length() > 0) {
    int n = readString.toInt();  //convert readString into a number
    Serial.print("writing Microseconds: ");
    Serial.println(n);
    
  }*/
}















