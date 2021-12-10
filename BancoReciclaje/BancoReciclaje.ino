#include "UbidotsEsp32Mqtt.h"

const char *UBIDOTS_TOKEN = "BBFF-ie3MYz2KJe4QXIygX8RC162mWqpFKA";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "redmi";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "8702gabo";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "balanza";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "peso"; // Put here your Variable label to which data  will be published
const char *VARIABLE_LABEL2 = "led";
const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

unsigned long timer;
uint8_t analogPin = 34; // Pin used to read data from GPIO34 ADC_CH6.

Ubidots ubidots(UBIDOTS_TOKEN);

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  timer = millis();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
  int timeChange= ((millis()) - timer);
  if (timeChange > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    float value=random(0,100);//analogRead(analogPin);
    int   value2=random(0,2);
    Serial.println((String)VARIABLE_LABEL+" "+value);
    Serial.println((String)VARIABLE_LABEL2+" "+value2);
    ubidots.add(VARIABLE_LABEL,value); // Insert your variable Labels and the value to be sent
    ubidots.add(VARIABLE_LABEL2,value2);
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  ubidots.loop();
}

////*****************TOMAR VARIABLES DESDE UBIDOTS
//#include "UbidotsEsp32Mqtt.h"
//
//const char *UBIDOTS_TOKEN = "";  // Put here your Ubidots TOKEN
//const char *WIFI_SSID = "";      // Put here your Wi-Fi SSID
//const char *WIFI_PASS = "";      // Put here your Wi-Fi password
//const char *DEVICE_LABEL = "";   // Replace with the device label to subscribe to
//const char *VARIABLE_LABEL = ""; // Replace with your variable label to subscribe to
//
//Ubidots ubidots(UBIDOTS_TOKEN);
//
//
//void callback(char *topic, byte *payload, unsigned int length)
//{
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
//  for (int i = 0; i < length; i++)
//  {
//    Serial.print((char)payload[i]);
//  }
//  Serial.println();
//}
//
//void setup()
//{
//  // put your setup code here, to run once:
//  Serial.begin(115200);
//  ubidots.setDebug(true);  // uncomment this to make debug messages available
//  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
//  ubidots.setCallback(callback);
//  ubidots.setup();
//  ubidots.reconnect();
//  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL); // Insert the dataSource and Variable's Labels
//}
//
//void loop()
//{
//  // put your main code here, to run repeatedly:
//  if (!ubidots.connected())
//  {
//    ubidots.reconnect();
//    ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL); // Insert the dataSource and Variable's Labels
//  }
//  ubidots.loop();
//}
