#include "debounce.h"
#include "arduino.h"

static unsigned long lastPressTime = -10000;

bool debounceButton(int pin, unsigned long delay_ms) {
    unsigned long now = millis();
    if (digitalRead(pin) == LOW) { // button pressed
        if (now - lastPressTime >= delay_ms) {
            lastPressTime = now;
            return true;
        }
        return false;
    }
    return false;
}

void debounceReset(void) {
    lastPressTime = -10000; // reset state for tests
}
