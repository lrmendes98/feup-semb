#ifndef _HARDWARE_H
#define _HARDWARE_H

#include "network.h"
#include "config.h"

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

void post() {
  Serial.print("\nStarting POST");
  const size_t led_array_size = 4;
  int led_array[led_array_size] = {LED_1_PIN, LED_2_PIN, LED_3_PIN, LED_4_PIN};
  int switch_array[led_array_size] = {SWITCH_1_PIN, SWITCH_2_PIN, SWITCH_3_PIN, SWITCH_4_PIN};

  int small_delay = 60;

  for (int i = 0; i < led_array_size; i++) {
    digitalWrite(led_array[i], 1);
  }
  delay(1000);
  for (int i = 0; i < led_array_size; i++) {
    digitalWrite(led_array[i], 0);
  }

  // fancy flash
  for (int i = 0; i < led_array_size; i++) {
    digitalWrite(led_array[i], 1);
    delay(small_delay);
    digitalWrite(led_array[i], 0);
  }

  // invert fancy flash
  for (int i = led_array_size - 1; i >= 0; i--) {
    digitalWrite(led_array[i], 1);
    delay(small_delay);
    digitalWrite(led_array[i], 0);
  }

  delay(500);

  // Flash switches ON state
  for (int i = 0; i < led_array_size; i++) {
    digitalWrite(led_array[i], !digitalRead(switch_array[i]));
  }

  delay(700);

  // Flash switches OFF state
  for (int i = 0; i < led_array_size; i++) {
    digitalWrite(led_array[i], digitalRead(switch_array[i]));
  }

  delay(700);

  // Leds OFF
  for (int i = 0; i < led_array_size; i++) {
    digitalWrite(led_array[i], 0);
  }

  Serial.print("\nDone\n");

}



void updateLeds() {
  int led1State = ( switches[1] + switches[17] + switches[18] + switches[20] + switches[22] ) % 2;
  int led2State = ( switches[5] + switches[17] + switches[19] + switches[20] + switches[23] ) % 2;
  int led3State = ( switches[9] + switches[17] + switches[18] + switches[21] + switches[23] ) % 2;
  int led4State = ( switches[13] + switches[17] + switches[19] + switches[21] + switches[22] ) % 2;

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
