#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "user_interface.h"

#define BUFFER_LENGTH 256
#define SWITCH_N 32

const char* ssid = "HUAWEI P10";
const char* password = "2072cac61e06";

WiFiUDP Udp;
IPAddress multicastAddress(239,0,0,1);
unsigned int multicastPort = 4444;

char incomingPacket[BUFFER_LENGTH];

const int LED_1_PIN = 14;
const int LED_2_PIN = 12;
const int LED_3_PIN = 13;
const int LED_4_PIN = 15;
const int SWITCH_1_PIN = 4;
const int SWITCH_2_PIN = 5;
const int SWITCH_3_PIN = 2;
const int SWITCH_4_PIN = 0;
int switches[SWITCH_N];

void setup(){

  for (int i = 0; i < SWITCH_N; i++) {
    switches[i] = 0;
  }
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
  pinMode(SWITCH_1_PIN, INPUT_PULLUP);
  pinMode(SWITCH_2_PIN, INPUT_PULLUP);
  pinMode(SWITCH_3_PIN, INPUT_PULLUP);
  pinMode(SWITCH_4_PIN, INPUT_PULLUP);
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

void receivePacket() {
  int packetLength = Udp.parsePacket(); 
  if(packetLength){
    int len = Udp.read(incomingPacket, BUFFER_LENGTH);
    if (len > 0){
      incomingPacket[len] = 0;
      Serial.print("Received: ");
      Serial.printf("%s\n", incomingPacket);
      if (len < 3)
        return;
      int id = (int)incomingPacket[0] - 48;
      Serial.println(id);
      int state = (int)incomingPacket[2] - 48;
      switches[id] = state;  
    }
  }
}

void updateLeds() {
  switches[1] ? digitalWrite(LED_1_PIN, HIGH) : digitalWrite(LED_1_PIN, LOW);
  switches[2] ? digitalWrite(LED_2_PIN, HIGH) : digitalWrite(LED_2_PIN, LOW);
  switches[3] ? digitalWrite(LED_3_PIN, HIGH) : digitalWrite(LED_3_PIN, LOW);
  switches[4] ? digitalWrite(LED_4_PIN, HIGH) : digitalWrite(LED_4_PIN, LOW);
}
/*
void readSwitch_1() {
  int newSwitch_1 = !digitalRead(SWITCH_1_PIN);
  if (switch_1 != newSwitch_1) {
    switch_1 = newSwitch_1;
    if (switch_1) {
      Serial.println("Switch 1 ON");
      digitalWrite(LED_1_PIN, HIGH);
    } else {
      Serial.println("Switch 1 OFF");
      digitalWrite(LED_1_PIN, LOW);
    }
  }
}

void readSwitch_2() {
  int newSwitch_2 = !digitalRead(SWITCH_2_PIN);
  if (switch_2 != newSwitch_2) {
    switch_2 = newSwitch_2;
    if (switch_2) {
      Serial.println("Switch 2 ON");
      digitalWrite(LED_2_PIN, HIGH);
    } else {
      Serial.println("Switch 2 OFF");
      digitalWrite(LED_2_PIN, LOW);
    }
  }
}

void readSwitch_3() {
  int newSwitch_3 = !digitalRead(SWITCH_3_PIN);
  if (switch_3 != newSwitch_3) {
    switch_3 = newSwitch_3;
    if (switch_3) {
      Serial.println("Switch 3 ON");
      digitalWrite(LED_3_PIN, HIGH);
    } else {
      Serial.println("Switch 3 OFF");
      digitalWrite(LED_3_PIN, LOW);
    }
  }
}

void readSwitch_4() {
  int newSwitch_4 = !digitalRead(SWITCH_4_PIN);
  if (switch_4 != newSwitch_4) {
    switch_4 = newSwitch_4;
    if (switch_4) {
      Serial.println("Switch 4 ON");
      digitalWrite(LED_4_PIN, HIGH);
    } else {
      Serial.println("Switch 4 OFF");
      digitalWrite(LED_4_PIN, LOW);
    }
  }
}
*/

void loop() {
  receivePacket();
  updateLeds();
  //readSwitch_1();
  //readSwitch_2();
  //readSwitch_3();
  //readSwitch_4();
}
