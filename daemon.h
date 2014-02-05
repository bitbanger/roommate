#ifndef DAEMON_H
#define DAEMON_H

const int GPIO_SERVO = 0;
const int SERVO_RANGE = 200;
const int SERVO_LOCKED = 21; // "angle"
const int SERVO_UNLOCKED = 10; // "angle"

const int GPIO_RED = 4;
const int GPIO_GREEN = 5;
const int GPIO_BLUE = 6;
const int LED_DOWNSHIFT = 2; // number of powers of two shorter than an octet

#endif
