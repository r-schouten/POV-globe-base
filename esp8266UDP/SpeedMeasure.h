#include <Arduino.h>

class SpeedMeasure
{
  private:
    int val, original;
    double count;
    int rpm;
    unsigned long oldTime;
    int port;
    long mcount[10];
    double tcount;
    long roundReceiveTime;
  public:
    SpeedMeasure(int port, int*& _rpm)
      : port(port)
    {
      _rpm = &rpm;
      pinMode(port, INPUT);
    }
    void loop()
    {
      val = digitalRead(port);
      if (val != original) {
        original = val;
        if (val == 1) {

          long roundLengthTime = millis() - roundReceiveTime;
          roundReceiveTime = millis();
          if (roundLengthTime < 10) {
            return;//mismeting
          }
          Serial.println(roundLengthTime);
          for (int i = 0; i < 10; i++) {
            if (i < 9) {
              mcount[i] = mcount[i + 1];
            } else {
              mcount[i] = roundLengthTime;
            }
          }
          for (int j = 0; j < 10; j++) {
            Serial.print(mcount[j]);
            Serial.print(" ");
            tcount += mcount[j];
          }
          Serial.println();
          tcount = 1000.0/(tcount/10.0);
          rpm = tcount*30;
          tcount = 0;
          count = 0;

          Serial.print("rpm = ");
          Serial.println(rpm);
        }
      }
      if(millis()-roundReceiveTime>500)
      {
        rpm=0;
      }

    }

};

