#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <stdbool.h>
#include <stdint.h>

bool debounceButton(int pin, unsigned long delay_ms);

#endif
