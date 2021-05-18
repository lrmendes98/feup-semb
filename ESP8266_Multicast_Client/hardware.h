#ifndef _HARDWARE_H
#define _HARDWARE_H

const int LED_1_PIN = 14;
const int LED_2_PIN = 12;
const int LED_3_PIN = 13;
const int LED_4_PIN = 15;
const int SWITCH_1_PIN = 0;
const int SWITCH_2_PIN = 2;
const int SWITCH_3_PIN = 5;
const int SWITCH_4_PIN = 4;

void updateLeds(int switches[]) {
  digitalWrite(LED_1_PIN, ( switches[1] + switches[17] + switches[18] + switches[20] + switches[22] )%2 );
  digitalWrite(LED_2_PIN, ( switches[5] + switches[17] + switches[19] + switches[20] + switches[23] )%2 );
  digitalWrite(LED_3_PIN, ( switches[9] + switches[17] + switches[18] + switches[21] + switches[23] )%2 );
  digitalWrite(LED_4_PIN, ( switches[13] + switches[17] + switches[19] + switches[21] + switches[22] )%2 );
}

#endif
