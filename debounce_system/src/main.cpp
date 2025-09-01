#include <Arduino.h>

#define LED_PIN 14

char c = '\0'; // Initialize with a null character

void read()
{
  if (Serial.available() > 0) 
  {
    c = Serial.read();
    Serial.println(c);
  }
}

void quick_blink()
{
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
}

void long_blink()
{
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  
}

void loop() {
  read();

  if (c == 'Q')
  {
    quick_blink();
    c = '\0'; // Reset the command character
  }

  if (c == 'L')
  {
    long_blink();
    c = '\0'; // Reset the command character
  } 
}