/**
 * @file color_calculator.cpp
 * @brief This file contains the implementation of the color calculator.
 *
 * The color calculator is used to calculate the 16 bit color value from RGB
 * values. The 16 Bit intgeger can then be used for the Matrix library directly.
 * This reduces the startuptime of the arduino compared to setting the RGB
 * values in the Setup routine.
 *
 * The color calculator expects the Values in RGB order. Values can reach from 0
 * to 255. Be careful as You will NOT be told when input is invalid.
 *
 * compile with: ```gcc color_calculator.cpp -o color_calculator```
 *
 * Run with: ```./color_calculator```
 */

#include <inttypes.h>
#include <stdio.h>

/**
 * @brief This function calculates the 16 bit color value from the given RGB
 * values.
 *
 * @param r The red value of the color.
 * @param g The green value of the color.
 * @param b The blue value of the color.
 * @return The 16 bit color value to be used for the LED matrix.
 */
uint16_t getColor(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
}

int main() {
  int inputr = 0;
  int inputg = 0;
  int inputb = 0;
  scanf("%i", &inputr);
  scanf("%i", &inputg);
  scanf("%i", &inputb);
  uint16_t i = getColor(inputr, inputg, inputb);
  printf("0x%02x\n", i);
  return 0;
}