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

volatile ASL::en_state en_current_state = ASL::setup_real_players;
uint8_t u8_player_quantity = 1;
uint8_t u8_computer_quantity = 0;
uint8_t u8_current_token_number = 0;
ASL::cla_display obj_display(A, B, C, CLK, LAT, OE);

void setup() {
  obj_display.Set_Colors(0, RED_BRIGHT, RED_DARK);
  obj_display.Set_Colors(1, BLUE_BRIGHT, BLUE_DARK);
  obj_display.Set_Colors(2, YELLOW_BRIGHT, YELLOW_DARK);
  obj_display.Set_Colors(3, GREEN_BRIGHT, GREEN_DARK);
  obj_display.Begin();
  ASL::Setup_Buttons();
  ASL::Setup_Dice();
}
uint8_t u8_test_incrementer = 0;

void loop() {
  switch (en_current_state) {
  case ASL::setup_real_players:
    obj_display.Display_Players(u8_player_quantity);
    break;
  case ASL::modify_real_player_number:
    if (u8_player_quantity < 4) {
      u8_player_quantity++;
    } else {
      u8_player_quantity = 1;
    }
    en_current_state = ASL::setup_real_players;
    break;
  case ASL::setup_computer_players:
    obj_display.Display_Players(u8_player_quantity);
    break;
  case ASL::modify_computer_player_number:
    if (u8_player_quantity < 4) {
      u8_player_quantity++;
      u8_computer_quantity++;
    } else {
      u8_player_quantity = u8_player_quantity - u8_computer_quantity;
      u8_computer_quantity = 0;
    }
    en_current_state = ASL::setup_computer_players;
    break;
  case ASL::wait_for_dice_roll:
    // NOP
    break;
  case ASL::roll_the_dice:
    obj_display.Display_Dice(ASL::Roll_Dice());
    en_current_state = ASL::display_token;
    break;
  case ASL::wait_for_player_input:

    break;
  case ASL::display_token:

    en_current_state = ASL::wait_for_player_input;
    break;
  case ASL::move_token:

    en_current_state = ASL::wait_for_dice_roll;
    break;
  case ASL::game_finished:

    break;
  default:
    // An error occured, go back to setup.
    en_current_state = ASL::setup_real_players;
    break;
  }
}
