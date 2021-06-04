#ifndef _NETWORK_H
#define _NETWORK_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string.h>
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
      if ((int)incomingPacket[0] - 48 == 0) {
        char* msg = (char*) calloc(len, sizeof(char));
        memcpy(msg, incomingPacket, len * sizeof(char));
        char* token;
        token = strtok(msg, " ");
        for (int i = 0; i < 3; i++) {
          token = strtok(NULL, " ");
          climateValues[i] = atoi(token);
        }
        free(msg);
      }
      else if (len == 1 || len == 2) {
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

void send_light_packet(int brightnessValue, int temperatureValue, int humidityValue) {
  int brightnessValueSize = floor(log10(brightnessValue)) + 1;
  int temperatureValueSize = floor(log10(temperatureValue)) + 1;
  int humidityValueSize = floor(log10(humidityValue)) + 1;

  // Allocate the adequate array size + 1 per array, + id + 3 spaces
  char* msg = (char*) calloc(brightnessValueSize + 1 + temperatureValueSize + 1 + humidityValueSize + 1 + 4, sizeof(char));
  char* brightnessValueArray = toArray(brightnessValue, brightnessValueSize);
  char* temperatureValueArray = toArray(temperatureValue, temperatureValueSize);
  char* humidityValueArray = toArray(humidityValue, humidityValueSize);

  // id = 0
  msg[0] = (char) (0 + 48);

  // Append space
  msg[1] = 32;

  // Append brightness array value
  memcpy(msg + 2, brightnessValueArray, (brightnessValueSize + 1) * sizeof(char));

  // Append space
  // current size = 2 + brightnessValueSize + 1, using size - 1 because index
  msg[(2 + brightnessValueSize + 1) - 1] = 32;

  // Append temperature value
  memcpy(msg + 2 + brightnessValueSize + 1, temperatureValueArray, (temperatureValueSize + 1) * sizeof(char));

  // Append space, current size = 2 + brightnessValueSize + 1 + temperatureValueSize + 1
  msg[2 + brightnessValueSize + temperatureValueSize + 1] = 32;

  // Append humidity value
  memcpy(msg + 2 + brightnessValueSize + 1 + temperatureValueSize + 1, humidityValueArray, (humidityValueSize + 1) * sizeof(char));

  Serial.print("Sent Data: ");
  Serial.println(msg);
  Udp.beginPacketMulticast(multicastAddress, multicastPort, WiFi.localIP());
  Udp.write(msg);
  Udp.endPacket();

  free(brightnessValueArray);
  free(temperatureValueArray);
  free(humidityValueArray);
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
