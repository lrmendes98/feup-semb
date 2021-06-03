#ifndef _NETWORK_H
#define _NETWORK_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "user_interface.h"
#include "config.h"

#define BUFFER_LENGTH 256
char incomingPacket[BUFFER_LENGTH];

// local network settings
const char* ssid = SSID;
const char* password = PASSWORD;

// multicast settings
IPAddress multicastAddress(239, 0, 0, 1);
unsigned int multicastPort = 4444;
WiFiUDP Udp;

int setupNetwork() {
  WiFi.mode(WIFI_STA); //station
  wifi_set_sleep_type(NONE_SLEEP_T); //LIGHT_SLEEP_T and MODE_SLEEP_T
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println("\nConnection established!");
  Udp.beginMulticast(WiFi.localIP(), multicastAddress, multicastPort);

  return 0;
}

void receivePacket() {
  int packetLength = Udp.parsePacket();
  if (packetLength) {
    int len = Udp.read(incomingPacket, BUFFER_LENGTH);
    if (len > 0) {
      incomingPacket[len] = 0;
      Serial.print("Received: ");
      Serial.printf("%s ", incomingPacket);
      Serial.print("with length ");
      Serial.println(len);
      int id;
      if (len == 1 || len == 2) {
        if (len == 1)
          id = (int)incomingPacket[0] - 48;
        else if (len == 2)
          id = ((int)incomingPacket[0] - 48) * 10 + ((int)incomingPacket[1] - 48);
        switches[id] = !switches[id];
      }

    }
  }
}

char * toArray(int number, int valueSize) {
  int i;
  char *numberArray = (char*) calloc(valueSize + 1, sizeof(char));
  for (i = valueSize - 1; i >= 0; --i, number /= 10) {
    numberArray[i] = (number % 10) + 48;
  }
  numberArray[valueSize] = '\0';
  return numberArray;
}

void send_light_packet(int value) {
  int valueSize = floor(log10(value)) + 1;
 

  char* msg = (char*) calloc(valueSize+3, sizeof(char));
  char* valueArray = toArray(value, valueSize);
  msg[0] = (char) (0 + 48);
  msg[1] = 32;
  memcpy(msg + 2, valueArray, (valueSize+1) * sizeof(char));

  Serial.print("Sent Light: ");
  Serial.println(msg);
  Udp.beginPacketMulticast(multicastAddress, multicastPort, WiFi.localIP());
  Udp.write(msg);
  Udp.endPacket();

  free(valueArray);
  free(msg);
}

void sendPacket(int id) {
  char msg[3];
  if (id > 9) {
    msg[0] = (char) (id / 10 + 48);
    msg[1] = (char) (id % 10 + 48);
    msg[2] = 0;
  } else {
    msg[0] = (char) (id + 48);
    msg[1] = 0;
    msg[2] = 0;
  }
  Serial.print("Sent: ");
  Serial.println(msg);
  Udp.beginPacketMulticast(multicastAddress, multicastPort, WiFi.localIP());
  Udp.write(msg);
  Udp.endPacket();
}

void sendPacket(int id, int state) {
  char msg[5];
  if (id > 9) {
    msg[0] = (char) (id / 10 + 48);
    msg[1] = (char) (id % 10 + 48);
    msg[2] = 32;
    msg[3] = (char) (state + 48);
    msg[4] = 0;
  } else {
    msg[0] = (char) (id + 48);
    msg[1] = 32;
    msg[2] = (char) (state + 48);
    msg[3] = 0;
    msg[4] = 0;
  }

  Serial.print("Sent: ");
  Serial.println(msg);
  Udp.beginPacketMulticast(multicastAddress, multicastPort, WiFi.localIP());
  Udp.write(msg);
  Udp.endPacket();
}

#endif
