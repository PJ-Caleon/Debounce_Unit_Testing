#include "unity.h"
#include "debounce.h"
#include "arduino.h"

void setUp(void) {
  fake_millis = 0;
  fake_digital_state = HIGH; 
  debounceReset();
}

void tearDown(void) {}

void test_first_press_should_trigger(void) {
    fake_digital_state = LOW;
    TEST_ASSERT_TRUE(debounceButton(14, 50));
}

void test_immediate_second_press_should_fail(void) {
    fake_digital_state = LOW; 
    TEST_ASSERT_TRUE(debounceButton(14, 50)); 

    // simulate still holding button down
    TEST_ASSERT_FALSE(debounceButton(14, 50)); 

    // release button
    fake_digital_state = HIGH;
}

void test_press_after_delay_should_work(void) {
    fake_digital_state = LOW;
    TEST_ASSERT_TRUE(debounceButton(14, 50));

    // release button
    fake_digital_state = HIGH;

    // wait
    fake_millis = 50;

    // press again
    fake_digital_state = LOW;
    TEST_ASSERT_TRUE(debounceButton(14, 50));
}
