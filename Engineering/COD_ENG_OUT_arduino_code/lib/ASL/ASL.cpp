#include <ASL.hpp>
#include <Arduino.h>

ASL::cla_display::cla_display(uint8_t _u8_matrix_a, uint8_t _u8_matrix_b,
                              uint8_t _u8_matrix_c, uint8_t _u8_matrix_clk,
                              uint8_t _u8_matrix_lat, uint8_t _u8_matrix_oe) {
  u8_matrix_a = _u8_matrix_a;
  u8_matrix_b = _u8_matrix_b;
  u8_matrix_c = _u8_matrix_c;
  u8_matrix_clk = _u8_matrix_clk;
  u8_matrix_lat = _u8_matrix_lat;
  u8_matrix_oe = _u8_matrix_oe;
}

void ASL::cla_display::Set_Colors(uint8_t _u8_player_nr,
                                  uint16_t _u16_bright_color,
                                  uint16_t _u16_dark_color) {
  u16_player_color[_u8_player_nr][0] = _u16_bright_color;
  u16_player_color[_u8_player_nr][1] = _u16_dark_color;
}

void ASL::cla_display::Begin() {
  RGBmatrixPanel obj_matrix_no_pointer(u8_matrix_a, u8_matrix_b, u8_matrix_c,
                                       u8_matrix_clk, u8_matrix_lat,
                                       u8_matrix_oe, false);
  obj_matrix_no_pointer.begin();
  this->obj_matrix = &obj_matrix_no_pointer;
  // Set up starting board:
  for (uint8_t i = 0; i < 40; i++) {
    obj_matrix->drawPixel(u8_track_positions[i][1], u8_track_positions[i][2],
                          u16_track_color);
    obj_matrix->updateDisplay();
  }
}

void ASL::cla_display::Display_Players(uint8_t _u8_player_quantity) {
  // Home Positions:
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      if (_u8_player_quantity > i) {
        obj_matrix->drawPixel(u8_home_positions[i][j][0],
                              u8_home_positions[i][j][1],
                              u16_player_color[i][0]);
      } else {
        obj_matrix->drawPixel(u8_home_positions[i][j][0],
                              u8_home_positions[i][j][1], 0x00);
      }
    }
  }
  // Finish Positions:
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      if (_u8_player_quantity > i) {
        obj_matrix->drawPixel(u8_finish_positions[i][j][0],
                              u8_finish_positions[i][j][1],
                              u16_player_color[i][1]);
      } else {
        obj_matrix->drawPixel(u8_finish_positions[i][j][0],
                              u8_finish_positions[i][j][1], 0x00);
      }
    }
  }
}

void ASL::cla_display::Display_Current_Player(uint8_t _u8_current_player) {
  obj_matrix->drawLine(14, 2, 14, 12, u16_player_color[_u8_current_player][0]);
}

void ASL::cla_display::Blink_Start(en_blink_mode _en_blink_mode,
                                   int8_t _u8_blink_cycles,
                                   uint8_t _u8_blink_player_number,
                                   uint8_t _u8_old_position,
                                   uint8_t _u8_new_position) {
  // write transfer parameters to class variables:
  u8_blink_old_position = _u8_old_position;
  u8_blink_new_position = _u8_new_position;
  u8_blink_player_number = _u8_blink_player_number;
  u8_blink_counter = _u8_blink_cycles;
  u8_blink_state = 0;
  en_current_blink_mode = _en_blink_mode;

  // Setup Timer 4 to CTC Mode with a prescaler of 256:
  TCCR4A = 0;
  TCCR4B = 0;
  // WGM 42:40 = 010 -> CTC Mode
  TCCR4B |= (1 << WGM42);
  // CS 42:40 = 100 -> Prescaler 256
  TCCR4B |= (1 << CS42);
  // Set Output Compare:
  if (en_current_blink_mode == fast) {
    // Fast Blink
    OCR4A = FAST_BLINK;
  } else if (en_current_blink_mode == slow) {
    // Slow Blink
    OCR4A = SLOW_BLINK;
  }
  // Enable Interupt for Output Compare A:
  TIMSK4 |= 1 << OCIE4A;
}

void ASL::cla_display::Blink_Update() {
  // Blinking is done in the interupt routine.
  if (u8_blink_state == 0) {
    Modify_Position(u8_blink_old_position, u8_blink_player_number, false);
    Modify_Position(u8_blink_new_position, u8_blink_player_number, true);
    u8_blink_state = 1;
  } else {
    Modify_Position(u8_blink_old_position, u8_blink_player_number, true);
    Modify_Position(u8_blink_new_position, u8_blink_player_number, false);
    u8_blink_state = 0;
  }
}

void ASL::cla_display::Blink_Stop() {
  // make sure its actually blinking
  if (en_current_blink_mode != off) {
    // Disable Interupt for Output Compare A:
    TIMSK4 &= 0b11111110;
    // Reset Timer 4:
    TCCR4A = 0;
    TCCR4B = 0;
    OCR4A = 0;
    // Reset display:
    Modify_Position(u8_blink_old_position, u8_blink_player_number, true);
    Modify_Position(u8_blink_new_position, u8_blink_player_number, false);
  }
  en_current_blink_mode = off;
}

void ASL::cla_display::Modify_Position(uint8_t _u8_position,
                                       uint8_t _u8_player_number,
                                       bool bool_turn_on) {
  uint16_t u16_new_color = 0x00;
  // Determine the new color of the pixel:
  if (!bool_turn_on) {
    if ((_u8_position < 5) | (_u8_position >= 45)) {
      u16_new_color = u16_player_color[_u8_player_number][1];
    } else {
      u16_new_color = u16_track_color;
    }
  } else {
    u16_new_color = u16_player_color[_u8_player_number][0];
  }
  // Draw the new pixel:
  if (_u8_position < 5) {
    // Starting Square
    _u8_position--;
    obj_matrix->drawPixel(u8_home_positions[_u8_player_number][_u8_position][0],
                          u8_home_positions[_u8_player_number][_u8_position][1],
                          u16_new_color);
  } else if ((_u8_position >= 5) && (_u8_position < 45)) {
    // Track
    _u8_position -= 5;
    obj_matrix->drawPixel(u8_track_positions[_u8_position][1],
                          u8_track_positions[_u8_position][2], u16_new_color);
  } else {
    // Finish Square
    _u8_position -= 45;
    obj_matrix->drawPixel(
        u8_finish_positions[_u8_player_number][_u8_position][0],
        u8_finish_positions[_u8_player_number][_u8_position][1], u16_new_color);
  }
}

void ASL::cla_display::Move_Token(uint8_t _u8_player_nr, uint8_t _u8_token_nr,
                                  uint8_t _u8_old_position,
                                  uint8_t _u8_new_position) {
  Modify_Position(_u8_old_position, _u8_player_nr, false);
  Modify_Position(_u8_new_position, _u8_player_nr, true);
}

void ASL::cla_display::Display_Dice(uint8_t _u8_dice_value,
                                    uint8_t _u8_dice_roll_counter,
                                    uint8_t _u8_current_player_number) {
  obj_matrix->drawRect(16, 2, 5, 5,
                       u16_player_color[_u8_current_player_number][0]);
  switch (_u8_dice_roll_counter) {
  case 0:
    obj_matrix->drawPixel(17, 2, 0x00);
    obj_matrix->drawPixel(18, 2, 0x00);
    obj_matrix->drawPixel(19, 2, 0x00);
    break;
  case 1:
    obj_matrix->drawPixel(17, 2,
                          u16_player_color[_u8_current_player_number][0]);
    obj_matrix->drawPixel(18, 2, 0x00);
    obj_matrix->drawPixel(19, 2, 0x00);
    break;
  case 2:
    obj_matrix->drawPixel(17, 2,
                          u16_player_color[_u8_current_player_number][0]);
    obj_matrix->drawPixel(18, 2,
                          u16_player_color[_u8_current_player_number][0]);
    obj_matrix->drawPixel(19, 2, 0x00);
    break;
  case 3:
    obj_matrix->drawPixel(17, 2,
                          u16_player_color[_u8_current_player_number][0]);
    obj_matrix->drawPixel(18, 2,
                          u16_player_color[_u8_current_player_number][0]);
    obj_matrix->drawPixel(19, 2,
                          u16_player_color[_u8_current_player_number][0]);
    break;
  }

  obj_matrix->drawPixel(18, 4, 0x00);
  obj_matrix->drawPixel(17, 3, 0x00);
  obj_matrix->drawPixel(17, 4, 0x00);
  obj_matrix->drawPixel(17, 5, 0x00);
  obj_matrix->drawPixel(19, 3, 0x00);
  obj_matrix->drawPixel(19, 4, 0x00);
  obj_matrix->drawPixel(19, 5, 0x00);
  switch (_u8_dice_value) {
  case 0:
    // Just leave it turned off.
    break;
  case 1:
    obj_matrix->drawPixel(18, 4, u16_track_color);
    break;
  case 2:
    obj_matrix->drawPixel(17, 3, u16_track_color);
    obj_matrix->drawPixel(19, 5, u16_track_color);
    break;
  case 3:
    obj_matrix->drawPixel(18, 4, u16_track_color);
    obj_matrix->drawPixel(17, 3, u16_track_color);
    obj_matrix->drawPixel(19, 5, u16_track_color);
    break;
  case 4:
    obj_matrix->drawPixel(17, 3, u16_track_color);
    obj_matrix->drawPixel(19, 5, u16_track_color);
    obj_matrix->drawPixel(17, 5, u16_track_color);
    obj_matrix->drawPixel(19, 3, u16_track_color);
    break;
  case 5:
    obj_matrix->drawPixel(17, 3, u16_track_color);
    obj_matrix->drawPixel(19, 5, u16_track_color);
    obj_matrix->drawPixel(17, 5, u16_track_color);
    obj_matrix->drawPixel(19, 3, u16_track_color);
    obj_matrix->drawPixel(18, 4, u16_track_color);
    break;
  case 6:
    obj_matrix->drawPixel(17, 3, u16_track_color);
    obj_matrix->drawPixel(17, 4, u16_track_color);
    obj_matrix->drawPixel(17, 5, u16_track_color);
    obj_matrix->drawPixel(19, 3, u16_track_color);
    obj_matrix->drawPixel(19, 4, u16_track_color);
    obj_matrix->drawPixel(19, 5, u16_track_color);
    break;
  }
}

void ASL::Setup_Buttons() {
  // Set PIN 2 and 3 to Input with external pull-up. PIN 2 and 3 correspond to
  // DDE4 and DDE5.
  // Set DDRE pin 4 and 5 to input
  DDRE &= 0b11001111;
  // Set PORTE pin 4 and 5 to non-pull-up.
  PORTE &= 0b11001111;
  PORTE |= 0b00110000;
  //  We want the interupt to occur on falling edge, so ISCn1 = 1 and ISCn0 =
  //  0 last 4 bits for INT5 and INT4.
  EICRB &= 0b11110000;
  EICRB |= 0b00001010;
  // Enable INT4 and INT5:
  EIMSK |= 0b00110000;
  // enable Global interupt
  SREG |= 0b10000000;
  // we will use a timer to disable interupts fo a short period of time after
  // the first button press.
  // set prescaler to 1024 -> frequency is now 15.625kHz
  // -> T of 1 count cycle : 0,000064s
  // -> T of 0x1000 count cycles: 4096 * 0,000064s = 0,262144s
  TCCR3A = 0;
  TCCR3B = 0;
  // Set Prescaler to 1024
  TCCR3B |= (1 << CS32) | (1 << CS30);
  // Set Output Compare to 0,262144s:
  OCR3A = 0x1000;
  // Enable Interupt:
  TIMSK3 |= 1 << OCIE3A;
}

void ASL::Setup_Dice() {
#if RANDOM_DICE
  // The Dice will use Counter 0 (8 Bit Counter).
  // Set WGM1 to 1 and WGM0 to 0 (last 2 bits): CTC mode
  TCCR0A = 1 << WGM01;
  // TCCR0A = 0b00000010;
  // Set WGM2 to 0 (xxxx 0xxx)
  // Set clock source to no prescaler (xxxx x001)
  TCCR0B = 1 << CS00;
  // TCCR0B = 0b00000001;
  // set reset value to 5 (6 values: 0:5 -> need to add 1 later to get dice
  // value 1:6)
  OCR0A = 0x05;
#else
  // Setup dice to read from Port L
  // Set Port L to Input
  DDRL = 0x00;
  // Set Port L to Pull-Up
  PORTL = 0xff;
#endif
}

uint8_t ASL::Roll_Dice() {
  //
#if RANDOM_DICE
  uint8_t i = TCNT0 + 1;
#else
  uint8_t i = ~PINL;
#endif
  return i;
}