#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
class UDPConnection
{
  private:
    const char* ssid = "povGlobe";
    const char* password = "povGlobe";
    WiFiUDP Udp;
    unsigned int localUdpPort = 42069;  // local port to listen on
    char incomingPacket[255];  // buffer for incoming packets
    int *rpm;
    int desiredSpeed = 0;
    boolean motorRunning = false;
    long packetReceivedTime;

  public:
    void setup(int *&_rpm, int *&_desiredSpeed, boolean *&_motorRunning)
    {
      rpm = _rpm;
      _desiredSpeed = &desiredSpeed;
      _motorRunning = &motorRunning;
      
      Serial.printf("Connecting to %s ", ssid);
      WiFi.begin(ssid, password);
      
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print(".");
      }
      Serial.println(" connected");
      IPAddress ip(192, 168, 137, 101);
      IPAddress gateway(192, 168, 137, 1);
      IPAddress subnet(255, 255, 255, 0);
      if (!WiFi.config(ip, gateway, subnet)) {
        Serial.println("STA Failed to configure");
      }
      Udp.begin(localUdpPort);
      Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
    }
    void loop()
    {
      int packetSize = Udp.parsePacket();
      if (packetSize)
      {
        // receive incoming UDP packets
        packetReceivedTime = millis();
        Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
        int len = Udp.read(incomingPacket, 255);
        if (incomingPacket[0] == '0') //stop
        {
          Serial.println("stop");
          //motorRunning = false;
          desiredSpeed = 0;
        }
        /*else if (incomingPacket[0] == '1') //start
          {
          Serial.println("start");
          motorRunning = true;
          }*/
        else if (incomingPacket[0] == '2') //speed update
        {
          String str(incomingPacket);
          str = str.substring(1, len);
          desiredSpeed = str.toInt();
          Serial.println(str);
          Serial.println(desiredSpeed);
        }
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        String response = "";
        response += *rpm;
        char charBuf[20];
        response.toCharArray(charBuf, 20);
        Udp.write(charBuf);
        Udp.endPacket();
      }
      if (millis() - packetReceivedTime > 3000)
      {
        //motorRunning = false;
        desiredSpeed = 0;
      }
    }
};
