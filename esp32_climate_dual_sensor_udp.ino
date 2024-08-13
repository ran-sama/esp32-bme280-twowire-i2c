#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SDA_1 21
#define SCL_1 22
#define SDA_2 33
#define SCL_2 32

WiFiUDP udp;
TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

Adafruit_BME280 bme1;
Adafruit_BME280 bme2;

char ssid[] = "name";
char pass[] = "password";
unsigned int localPort = 2390;

void setup() {
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  
  udp.begin(localPort);
  
  I2Cone.begin(SDA_1, SCL_1, 100000); 
  I2Ctwo.begin(SDA_2, SCL_2, 100000);
  bool status1 = bme1.begin(0x76, &I2Cone);  
  bool status2 = bme2.begin(0x76, &I2Ctwo);  
}

void loop() { 
  String replyPacket1 = String(bme1.readTemperature()) + "$" + String(bme1.readHumidity()) + "$" + String(bme1.readPressure()/100.0F);
  udp.beginPacket("10.0.0.10", 7890);
  //udp.write(replyPacket1.c_str());
  udp.print(replyPacket1);
  udp.endPacket();
  
  String replyPacket2 = String(bme2.readTemperature()) + "$" + String(bme2.readHumidity()) + "$" + String(bme2.readPressure()/100.0F);
  udp.beginPacket("10.0.0.10", 7892);
  //udp.write(replyPacket2.c_str());
  udp.print(replyPacket2);
  udp.endPacket();
  
  delay(60000);
}
