#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <stdbool.h>

bool debounceButton(int pin, unsigned long delay_ms);
void debounceReset(void);

#endif
