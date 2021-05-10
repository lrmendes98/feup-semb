#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "user_interface.h"

#define BUFFER_LENGTH 256

const char* ssid = "HUAWEI P10";
const char* password = "2072cac61e06";

WiFiUDP Udp;
IPAddress multicastAddress(239,0,0,1);
unsigned int multicastPort = 4444;

char incomingPacket[BUFFER_LENGTH]; 

void setup(){
    Serial.begin(115200);
    
    WiFi.mode(WIFI_STA); //station
    wifi_set_sleep_type(NONE_SLEEP_T); //LIGHT_SLEEP_T and MODE_SLEEP_T
    
    Serial.print("Connecting to ");
    Serial.print(ssid);
    
    WiFi.begin(ssid, password);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(++i); Serial.print(' ');
    }
    
    Serial.println("Connection established!");
    
    Udp.beginMulticast(WiFi.localIP(), multicastAddress, multicastPort);
}

void loop(){
    int packetLength = Udp.parsePacket(); 
    if(packetLength){
        int len = Udp.read(incomingPacket, BUFFER_LENGTH);
        if (len > 0){
            incomingPacket[len] = 0;
            Serial.printf("%s\n", incomingPacket);
        }
    }
}
