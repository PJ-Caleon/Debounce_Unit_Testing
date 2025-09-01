#include "debounce.h"
#include "arduino.h"

static unsigned long lastPressTime = 0;

bool debounceButton(int pin, unsigned long delay_ms) {
    unsigned long now = millis();
    if (digitalRead(pin) == LOW) {
        if (now - lastPressTime > delay_ms) {
            lastPressTime = now;
            return false;
        }
    }
    return true;
}
