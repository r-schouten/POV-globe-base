#include "MotorController.h"
#include "SpeedMeasure.h"
#include "UDPConnection.h"
int *rpm;
int *desiredSpeed;
boolean *motorRunning;
int oldSpeed;
boolean oldMotorRunning = false;
MotorController motorController(12);
SpeedMeasure speedMeasure(16, rpm);
UDPConnection udp;
void setup()
{
  Serial.begin(115200);
  Serial.println("started");
  motorController.attach();
  udp.setup(rpm, desiredSpeed, motorRunning);
}
void loop()
{
  speedMeasure.loop();
  udp.loop();
  motorController.setSpeed(map(*desiredSpeed, 0, 100, 1000, 1500));
  Serial.println(*desiredSpeed);
  delay(10);

}















