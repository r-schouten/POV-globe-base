#include <Arduino.h>
#include <Servo.h>
class MotorController
{
    private:
    Servo myservo;
    int port;
    public:
    MotorController(int _port) {
      port=_port;
      Serial.println("servo controller started");
    }
    void detach()
    {
      myservo.detach(); //detach servo
      Serial.println("servo detached");
    }
    void attach()
    {
      myservo.attach(port); 
      myservo.writeMicroseconds(1000);
      delay(500);
      Serial.println("servo attached");
    }
    void setSpeed(int speed)
    {
      if(speed<1100)
      {
        speed=1000;
      }
      Serial.print("writing Microseconds: ");
      Serial.println(speed);
      myservo.writeMicroseconds(speed);
    }
    
};

