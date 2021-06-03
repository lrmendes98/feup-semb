#include "schedule.h"
#include "hardware.h"
#include "network.h"



/**************** Arduino framework ********************/

// the setup function runs once when you press reset or power the board
// used to configure hardware resources and software structures

void setup() {
  delay(1000);

  Serial.begin(115200);
  setupHardware();
  post();
  setupLogic();
  if (setupNetwork() == 0) {
    blink_leds();
  }

  // run the kernel initialization routine
  Sched_Init();

  // add all periodic tasks  (code, offset, period) in ticks
  // for the moment, ticks in 10ms -- see below timer frequency
  Sched_AddT(receivePacket, 1, 10);   // task id=0 --> highest priority

#ifdef LUIS_ARDUINO
  Sched_AddT(read_light_sensor, 1, 200);
#endif

  Sched_AddT(updateLeds, 1, 200);
  Sched_AddT(readSwitch_1, 1, 500);
  Sched_AddT(readSwitch_2, 1, 500);
  Sched_AddT(readSwitch_3, 1, 500);
  Sched_AddT(readSwitch_4, 1, 500);

  // though T4 wakes up every 100 ms it will not preempt T1 the executes betwee 200 and 500 ms!
  // observe that the "4" written by T4 never appears between the S and F of T1
  // S and F from T1 always appear together --> T1 executes without preemption

  noInterrupts(); // disable all interrupts

  timer1_isr_init();
  timer1_attachInterrupt(Sched_Schedule);
  timer1_enable(TIM_DIV256, TIM_EDGE, TIM_LOOP);
  timer1_write(1000);
  interrupts(); // enable all interrupts
}


// the loop function runs over and over again forever
void loop() {
  // invokes the dispatcher to execute the highest priority ready task
  Sched_Dispatch();
}
