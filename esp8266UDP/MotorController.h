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
      Serial.println("servo attached");
    }
    void setSpeed(int n)
    {
      Serial.print("writing Microseconds: ");
      Serial.println(n);
      myservo.writeMicroseconds(n);
    }
    
};

