/*
#include <WiFi.h>
 
char* ssid = "HUAWEI P10";
char* password =  "2072cac61e06";
 
uint16_t port = 5000;
char * host = "192.168.43.49";
 
void setup()
{
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
 
}
 
void loop()
{
    WiFiClient client;
 
    if (!client.connect(host, port)) {
 
        Serial.println("Connection to host failed");
 
        delay(1000);
        return;
    }
 
    Serial.println("Connected to server successful!");
 
    client.print("Hello from ESP32!");
 
    Serial.println("Disconnecting...");
    client.stop();
 
    delay(10000);
}

*/

#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char* ssid     = "HUAWEI P10";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "2072cac61e06";     // The password of the Wi-Fi network

uint16_t port = 5000;
char * host = "192.168.43.49";

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
  
}

void loop() {
  WiFiClient client;
 
    if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(1000);
        return;
    }
    Serial.println("Connected to server successful!");
    client.print("Hello from ESP32!");
    Serial.println("Disconnecting...");
    client.stop();
 
    delay(10000);
}
