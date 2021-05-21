#ifndef _HARDWARE_H
#define _HARDWARE_H

#include "network.h"

const int LED_1_PIN = 14;
const int LED_2_PIN = 12;
const int LED_3_PIN = 13;
const int LED_4_PIN = 15;
const int SWITCH_1_PIN = 0;
const int SWITCH_2_PIN = 2;
const int SWITCH_3_PIN = 5;
const int SWITCH_4_PIN = 4;

void updateLeds() {
  int led1State = ( switches[1] + switches[17] + switches[18] + switches[20] + switches[22] )%2;
  int led2State = ( switches[5] + switches[17] + switches[19] + switches[20] + switches[23] )%2;
  int led3State = ( switches[9] + switches[17] + switches[18] + switches[21] + switches[23] )%2;
  int led4State = ( switches[13] + switches[17] + switches[19] + switches[21] + switches[22] )%2;

  digitalWrite(LED_1_PIN, led1State);
  sendPacket(LED1_ID, led1State);
  digitalWrite(LED_2_PIN, led2State);
  sendPacket(LED2_ID, led2State);
  digitalWrite(LED_3_PIN, led3State);
  sendPacket(LED3_ID, led3State);
  digitalWrite(LED_4_PIN, led4State);
  sendPacket(LED4_ID, led4State);
}

#endif
