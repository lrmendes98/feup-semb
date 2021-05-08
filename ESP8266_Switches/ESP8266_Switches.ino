const int LED_1_PIN = 14;
const int LED_2_PIN = 12;
const int LED_3_PIN = 13;
const int LED_4_PIN = 15;
const int SWITCH_1_PIN = 4;
const int SWITCH_2_PIN = 5;
const int SWITCH_3_PIN = 2;
const int SWITCH_4_PIN = 0;
int switch_1 = 0;
int switch_2 = 0;
int switch_3 = 0;
int switch_4 = 0;

void setup() {

// initialize GPIO 5 as an output

  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
  pinMode(SWITCH_1_PIN, INPUT_PULLUP);
  pinMode(SWITCH_2_PIN, INPUT_PULLUP);
  pinMode(SWITCH_3_PIN, INPUT_PULLUP);
  pinMode(SWITCH_4_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

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

void loop() {
  readSwitch_1();
  readSwitch_2();
  readSwitch_3();
  readSwitch_4();

}
