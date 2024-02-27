#include <Arduino.h>

const int i_pin = 2; 
volatile uint32_t u32_start_time_high = 0;
volatile uint32_t u32_duration_high = 0; 
volatile uint32_t u32_start_time_low = 0; 
volatile uint32_t u32_duration_low = 0; 
float fl_high_frequency = 0.0; 
float fl_low_frequency = 0.0; 

void Pin_Change();

void setup() {
  pinMode(i_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(i_pin), Pin_Change, CHANGE);
  Serial.begin(9600);
}

void loop() {
  if (u32_duration_high > 0) {
    fl_high_frequency = 1000000.0 / u32_duration_high; // Calculate frequency for the high state in Hertz
    Serial.print("Duration of Pin High: ");
    Serial.print(u32_duration_high);
    Serial.print(" microseconds, Frequency: ");
    Serial.print(fl_high_frequency, 3); // Display frequency with 3 decimal places
    Serial.println(" Hz");
    u32_duration_high = 0; // Reset duration for the next measurement
  }

  if (u32_duration_low > 0) {
    fl_low_frequency = 1000000.0 / u32_duration_low; // Calculate frequency for the low state in Hertz
    Serial.print("Duration of Pin Low: ");
    Serial.print(u32_duration_low);
    Serial.print(" microseconds, Frequency: ");
    Serial.print(fl_low_frequency, 3); // Display frequency with 3 decimal places
    Serial.println(" Hz");
    u32_duration_low = 0; // Reset duration for the next measurement
  }
}

/**
 * \ @brief This function is responsible for handling pin state changes.
 *
 * This function reads the state of a digital pin and records the timing
 * information for transitions between HIGH and LOW states. It calculates
 * the duration of the HIGH and LOW states and updates the corresponding
 * variables accordingly.
*/
void Pin_Change() {
  int state = digitalRead(i_pin);
  unsigned long currentTime = micros();

  if (state == HIGH) {
    u32_start_time_high = currentTime; // Save current time for the beginning of the high state
    if (u32_duration_low == 0) {
      u32_duration_low = currentTime - u32_start_time_low; // Calculate elapsed time for low state
    }
  } else {
    u32_start_time_low = currentTime; // Save current time for the beginning of the low state
    if (u32_duration_high == 0) {
      u32_duration_high = currentTime - u32_start_time_high; // Calculate elapsed time for high state
    }
  }
}


