#ifndef _LOGIC_H
#define _LOGIC_H

#include "hardware.h"
#include "config.h"

#ifdef LUIS_ARDUINO
#include <dht11.h>
#define DHT11PIN 16
dht11 DHT11;
#endif

int localSwitches[4];

void setupLogic(void) {
  for (int i = 0; i < SWITCH_N; i++) {
    switches[i] = 0;
  }
  climateValues[0] = 1000;
}

#ifdef LUIS_ARDUINO
void read_sensors_data(void) {
  int chk = DHT11.read(DHT11PIN);

  int humidity = (int)DHT11.humidity;
  int temperature = (int)DHT11.temperature;
  int brightness = analogRead(A0);

  climateValues[0] = brightness;
  climateValues[1] = temperature;
  climateValues[2] = humidity;

  send_light_packet(brightness, temperature, humidity);
}
#endif


void readSwitch_1(void) {
  int newSwitch = !digitalRead(SWITCH_1_PIN);
  if (newSwitch != localSwitches[0]) {
    switches[SWITCH1_ID] = !switches[SWITCH1_ID];
    localSwitches[0] = !localSwitches[0];
    sendSwitchPacket(SWITCH1_ID);
  }
}

void readSwitch_2(void) {
  int newSwitch = !digitalRead(SWITCH_2_PIN);
  if (newSwitch != localSwitches[1]) {
    switches[SWITCH2_ID] = !switches[SWITCH2_ID];
    localSwitches[1] = !localSwitches[1];
    sendSwitchPacket(SWITCH2_ID);
  }
}

void readSwitch_3(void) {
  int newSwitch = !digitalRead(SWITCH_3_PIN);
  if (newSwitch != localSwitches[2]) {
    switches[SWITCH3_ID] = !switches[SWITCH3_ID];
    localSwitches[2] = !localSwitches[2];
    sendSwitchPacket(SWITCH3_ID);
  }
}

void readSwitch_4(void) {
  int newSwitch = !digitalRead(SWITCH_4_PIN);
  if (newSwitch != localSwitches[3]) {
    switches[SWITCH4_ID] = !switches[SWITCH4_ID];
    localSwitches[3] = !localSwitches[3];
    sendSwitchPacket(SWITCH4_ID);
  }
}

#endif
