#ifndef _LOGIC_H
#define _LOGIC_H

#include "hardware.h"
#include "config.h"
#include <dht11.h>
#define DHT11PIN 16
dht11 DHT11;

int localSwitches[4];

void setupLogic() {
  for (int i = 0; i < SWITCH_N; i++) {
    switches[i] = 0;
  }
}

void read_light_sensor() {
  Serial.println();

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (C): ");
  Serial.println((float)DHT11.temperature, 2);

  int value = analogRead(A0);
  send_light_packet(value);
}

void readSwitch_1() {
  int newSwitch = !digitalRead(SWITCH_1_PIN);
  if (newSwitch != localSwitches[0]) {
    switches[SWITCH1_ID] = !switches[SWITCH1_ID];
    localSwitches[0] = !localSwitches[0];
    sendPacket(SWITCH1_ID);
  }
}

void readSwitch_2() {
  int newSwitch = !digitalRead(SWITCH_2_PIN);
  if (newSwitch != localSwitches[1]) {
    switches[SWITCH2_ID] = !switches[SWITCH2_ID];
    localSwitches[1] = !localSwitches[1];
    sendPacket(SWITCH2_ID);
  }
}

void readSwitch_3() {
  int newSwitch = !digitalRead(SWITCH_3_PIN);
  if (newSwitch != localSwitches[2]) {
    switches[SWITCH3_ID] = !switches[SWITCH3_ID];
    localSwitches[2] = !localSwitches[2];
    sendPacket(SWITCH3_ID);
  }
}

void readSwitch_4() {
  int newSwitch = !digitalRead(SWITCH_4_PIN);
  if (newSwitch != localSwitches[3]) {
    switches[SWITCH4_ID] = !switches[SWITCH4_ID];
    localSwitches[3] = !localSwitches[3];
    sendPacket(SWITCH4_ID);
  }
}

//void loop() {
//receivePacket(switches);
//readSwitch_1();
//readSwitch_2();
//readSwitch_3();
//readSwitch_4();
//updateLeds();
//delay(200);
//}

#endif
