#include "hardware.h"

#define SWITCH_N 32
int switches[SWITCH_N];
int localSwitches[4];

void setupHardware() {
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
  pinMode(SWITCH_1_PIN, INPUT_PULLUP);
  pinMode(SWITCH_2_PIN, INPUT_PULLUP);
  pinMode(SWITCH_3_PIN, INPUT_PULLUP);
  pinMode(SWITCH_4_PIN, INPUT_PULLUP);
}

void setup() {
  for (int i = 0; i < SWITCH_N; i++) {
    switches[i] = 0;
  }
  Serial.begin(115200);
  setupHardware();
  setupNetwork();
}

void updateLeds() {
  switches[1] ? digitalWrite(LED_1_PIN, HIGH) : digitalWrite(LED_1_PIN, LOW);
  switches[2] ? digitalWrite(LED_2_PIN, HIGH) : digitalWrite(LED_2_PIN, LOW);
  switches[3] ? digitalWrite(LED_3_PIN, HIGH) : digitalWrite(LED_3_PIN, LOW);
  switches[4] ? digitalWrite(LED_4_PIN, HIGH) : digitalWrite(LED_4_PIN, LOW);
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

void loop() {
  receivePacket(switches);
  readSwitch_1();
  readSwitch_2();
  readSwitch_3();
  readSwitch_4();
  updateLeds(switches);
  delay(200);
}
