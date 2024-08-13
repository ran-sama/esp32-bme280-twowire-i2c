#include <WiFi.h>
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

WiFiServer server(7890);

void setup() {
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  I2Cone.begin(SDA_1, SCL_1, 100000);
  I2Ctwo.begin(SDA_2, SCL_2, 100000);
  
  bool status1 = bme1.begin(0x76, &I2Cone);
  bool status2 = bme2.begin(0x76, &I2Ctwo);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if(client){
    if (client.connected()){
      if (client.available()){
        String replyPacket1 = String(bme1.readTemperature()) + "$" + String(bme1.readHumidity()) + "$" + String(bme1.readPressure()/100.0F);
        String replyPacket2 = String(bme2.readTemperature()) + "$" + String(bme2.readHumidity()) + "$" + String(bme2.readPressure()/100.0F);
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type: text/plain");
        client.println("Content-Length: " + String(replyPacket1.length() + 1 + replyPacket2.length()));
        client.println();
        client.println(replyPacket1 + "$" + replyPacket2);
      }
    }
  }
  delay(1000);
  client.stop();
  delay(1000);
}
