#include <ASL.hpp>
#include <Arduino.h>

// Define all the Ports here:
#define CLK 11 // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE 12
#define A A0
#define B A1
#define C A2

// define all the colors
#define RED_BRIGHT 0xf800
#define RED_DARK 0x1000
#define GREEN_BRIGHT 0x7e0
#define GREEN_DARK 0xa0
#define YELLOW_BRIGHT 0xffe0
#define YELLOW_DARK 0x10a0
#define BLUE_BRIGHT 0x001f
#define BLUE_DARK 0x0002
#define WHITE_BRIGHT 0xffff

typedef enum {
  initialise = 0,
  move,
  game_finished,
} en_state;

volatile en_state en_current_state = initialise;

void setup() {
  ASL::cla_display obj_display(A, B, C, CLK, LAT, OE);
  obj_display.Set_Colors(0, RED_BRIGHT, RED_DARK);
  obj_display.Set_Colors(1, BLUE_BRIGHT, BLUE_DARK);
  obj_display.Set_Colors(2, YELLOW_BRIGHT, YELLOW_DARK);
  obj_display.Set_Colors(3, GREEN_BRIGHT, GREEN_DARK);
  obj_display.Begin();
  ASL::Setup_Buttons();
}
uint8_t u8_test_incrementer = 0;

void loop() {
  switch (en_current_state) {
  case initialise:

    break;
  case move:

    break;
  case game_finished:

    break;
  default:
    break;
  }
}
