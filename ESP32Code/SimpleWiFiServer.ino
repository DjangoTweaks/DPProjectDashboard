#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DPIN 4        //Pin to connect DHT sensor (GPIO number)
#define DTYPE DHT11   // Define DHT 11 or DHT22 sensor type


// const int mq2_analog_pin = A0; // Analog pin of MQ2 sensor connected to ESP8266


const char* ssid     = "ORBI87";
const char* password = "royalmesa924";

DHT dht(DPIN,DTYPE);


WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    dht.begin();

 

    server.begin();

   

}

void loop()
{

   SensorDataPost();
 
    
  
}


void SensorDataPost()
{

  HTTPClient http; 
  delay(3000);
  
  float tc_DHT = dht.readTemperature(false);  //Read temperature in C
  float hu_DHT = dht.readHumidity();          //Read Humidity

  // int sensorValue = analogRead(mq2_analog_pin);
  // float voltage = sensorValue * (3.3 / 1023.0); // Convert analog value to voltage


  // String payload = "{\"temperature\":" + String(tc_DHT) + ",\"humidity\":" + String(hu_DHT) + "}";

  String payload = "{\"temperature\":" + String(tc_DHT) + ",\"humidity\":" + String(hu_DHT) + ",\"distance\":" + String(distance_value) + ",\"concentration\":" + String(concentration_value) + "}";


  http.begin("http://10.0.0.14:3000/send-data-ESP32");
  http.addHeader("Content-Type","application/json");

  int httpResponseCode = http.POST(payload);

  if(httpResponseCode)
  {
    String resp = http.getString();
    Serial.println(httpResponseCode);  
    Serial.println(resp); 
  }
  else
  {
    Serial.println("Error Occured");
    Serial.println(httpResponseCode);  
  }

  http.end(); 

}




