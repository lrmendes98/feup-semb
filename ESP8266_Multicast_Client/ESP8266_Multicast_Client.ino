#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "user_interface.h"

#define BUFFER_LENGTH 256
#define SWITCH_N 32

const char* ssid = "HUAWEI P10";
const char* password = "2072cac61e06";

WiFiUDP Udp;
IPAddress multicastAddress(239, 0, 0, 1);
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

void setup() {

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
  if (packetLength) {
    int len = Udp.read(incomingPacket, BUFFER_LENGTH);
    if (len > 0) {
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

void sendPacket(int id, int state) {
  char msg[4];
  msg[0] = (char) id + 48;
  msg[1] = 32;
  msg[2] = (char) state + 48;
  msg[3] = 0;
  Serial.println(msg);
  Udp.beginPacketMulticast(multicastAddress, multicastPort, WiFi.localIP());
  Udp.write(msg);
  Udp.endPacket();
}

void updateLeds() {
  switches[1] ? digitalWrite(LED_1_PIN, HIGH) : digitalWrite(LED_1_PIN, LOW);
  switches[2] ? digitalWrite(LED_2_PIN, HIGH) : digitalWrite(LED_2_PIN, LOW);
  switches[3] ? digitalWrite(LED_3_PIN, HIGH) : digitalWrite(LED_3_PIN, LOW);
  switches[4] ? digitalWrite(LED_4_PIN, HIGH) : digitalWrite(LED_4_PIN, LOW);
}

void readSwitch_1() {
  int newSwitch = !digitalRead(SWITCH_1_PIN);
  if (newSwitch != switches[1]) {
    switches[1] = newSwitch;
    sendPacket(1, newSwitch);
  }
}

void readSwitch_2() {
  int newSwitch = !digitalRead(SWITCH_2_PIN);
  if (newSwitch != switches[2]) {
    switches[2] = newSwitch;
    sendPacket(2, newSwitch);
  }
}

void readSwitch_3() {
  int newSwitch = !digitalRead(SWITCH_3_PIN);
  if (newSwitch != switches[3]) {
    switches[3] = newSwitch;
    sendPacket(3, newSwitch);
  }
}

void readSwitch_4() {
  int newSwitch = !digitalRead(SWITCH_4_PIN);
  if (newSwitch != switches[4]) {
    switches[4] = newSwitch;
    sendPacket(4, newSwitch);
  }
}

void loop() {
  receivePacket();
  readSwitch_1();
  readSwitch_2();
  //readSwitch_3();
  //readSwitch_4();
  updateLeds();
}
