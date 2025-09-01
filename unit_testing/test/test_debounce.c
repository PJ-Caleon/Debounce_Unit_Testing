#include "unity.h"
#include "debounce.h"
#include "arduino.h"

void setUp(void) {
  fake_millis = 0;
  fake_digital_state = HIGH;
}

void tearDown(void) {}

void test_button_press_triggers_once(void) {
  // press button
  fake_digital_state = HIGH;
  TEST_ASSERT_TRUE(debounceButton(2, 50));

  // immediately press again (should fail)
  TEST_ASSERT_FALSE(debounceButton(2, 50));

  // wait > debounce delay
  fake_millis = 60;
  TEST_ASSERT_TRUE(debounceButton(2, 50));
}
