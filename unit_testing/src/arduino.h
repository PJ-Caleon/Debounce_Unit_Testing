#ifndef FAKE_ARDUINO_H
#define FAKE_ARDUINO_H

#include <stdint.h>

#define HIGH 1
#define LOW  0

extern unsigned long fake_millis;
extern int fake_digital_state;

static inline unsigned long millis(void) {
    return fake_millis;
}

static inline int digitalRead(int pin) {
    (void)pin;
    return fake_digital_state;
}

#endif
