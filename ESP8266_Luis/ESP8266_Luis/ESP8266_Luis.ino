#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "user_interface.h"

#define BUFFER_LENGTH 256


// Configuracao dependente do ESP
const int LED_1_PIN = 16;
const int LED_2_PIN = 12;
const int LED_3_PIN = 13;
const int LED_4_PIN = 15;
const int SWITCH_1_PIN = 2;
const int SWITCH_2_PIN = 0;
const int SWITCH_3_PIN = 4;
const int SWITCH_4_PIN = 5;

// Configuracoes de networking
const char* ssid     = "Redmi Note 9S";     // The SSID (name) of the AP
const char* password = "1c64aee4ca58";      // The password of the AP
uint16_t port = 5000;
char * host = "192.168.43.49";

// Estado inicial dos interruptores
int switch_1 = 0;
int switch_2 = 0;
int switch_3 = 0;
int switch_4 = 0;

// Configuracao do cliente multicast
WiFiUDP Udp;
IPAddress multicastAddress(239, 0, 0, 1);
unsigned int multicastPort = 4444;
char incomingPacket[BUFFER_LENGTH];


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


////////////////////////////////////////////
/*              SETUP & LOOP              */
////////////////////////////////////////////

void setup() {
  // baudrate of the monitor
  Serial.begin(115200);

  // Setup Pins
  pinMode(LED_1_PIN, OUTPUT);
  //  pinMode(LED_2_PIN, OUTPUT);
  //  pinMode(LED_3_PIN, OUTPUT);
  //  pinMode(LED_4_PIN, OUTPUT);
  pinMode(SWITCH_1_PIN, INPUT_PULLUP);
  pinMode(SWITCH_2_PIN, INPUT_PULLUP);
  pinMode(SWITCH_3_PIN, INPUT_PULLUP);
  pinMode(SWITCH_4_PIN, INPUT_PULLUP);

  // Setup networking side
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
  Serial.println(WiFi.localIP());         // Print the local IP asigned to the esp

  Udp.beginMulticast(WiFi.localIP(), multicastAddress, multicastPort);


}

void loop() {
  int packetLength = Udp.parsePacket();
  if (packetLength) {
    int len = Udp.read(incomingPacket, BUFFER_LENGTH);
    if (len > 0) {
      incomingPacket[len] = 0;
      Serial.print("Recieved: ");
      Serial.printf("%s\n", incomingPacket);
      if (strcmp(incomingPacket, "1") == 0) {
        switch_1 ? switch_1 = 0 : switch_1 = 1;
        Serial.println(switch_1);
        if (switch_1) {
          Serial.println("Switch 1 ON");
          digitalWrite(LED_1_PIN, HIGH);
        } else {
          Serial.println("Switch 1 OFF");
          digitalWrite(LED_1_PIN, LOW);
        }
      }

      if (strcmp(incomingPacket, "2") == 0) {
        switch_2 ? switch_2 = 0 : switch_2 = 1;
        Serial.println(switch_2);
        if (switch_2) {
          Serial.println("Switch 2 ON");
          digitalWrite(LED_2_PIN, HIGH);
        } else {
          Serial.println("Switch 2 OFF");
          digitalWrite(LED_2_PIN, LOW);
        }
      }

      if (strcmp(incomingPacket, "3") == 0) {
        switch_3 ? switch_3 = 0 : switch_3 = 1;
        Serial.println(switch_3);
        if (switch_3) {
          Serial.println("Switch 3 ON");
          digitalWrite(LED_3_PIN, HIGH);
        } else {
          Serial.println("Switch 3 OFF");
          digitalWrite(LED_3_PIN, LOW);
        }
      }

      if (strcmp(incomingPacket, "4") == 0) {
        switch_4 ? switch_4 = 0 : switch_4 = 1;
        Serial.println(switch_4);
        if (switch_4) {
          Serial.println("Switch 4 ON");
          digitalWrite(LED_4_PIN, HIGH);
        } else {
          Serial.println("Switch 4 OFF");
          digitalWrite(LED_4_PIN, LOW);
        }
      }

    }
  }
//
//  readSwitch_1();
//  readSwitch_2();
//  readSwitch_3();
//  readSwitch_4();
}
