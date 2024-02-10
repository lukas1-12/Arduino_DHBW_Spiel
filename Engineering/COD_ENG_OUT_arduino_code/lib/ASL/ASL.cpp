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
}

void ASL::cla_display::Display_Current_Player(uint8_t _u8_current_player) {
  obj_matrix->drawLine(14, 2, 14, 12, u16_player_color[_u8_current_player][0]);
}

void ASL::cla_display::Display_Token(uint8_t _u8_player_nr,
                                     uint8_t _u8_new_position) {
  if (_u8_new_position < 5) {
  } else if (_u8_new_position >= 5 && _u8_new_position <= 40) {
    _u8_new_position -= 5;
    obj_matrix->drawPixel(u8_track_positions[_u8_new_position][1],
                          u8_track_positions[_u8_new_position][2],
                          u16_player_color[_u8_player_nr][1]);
  } else {
  }
}

void ASL::cla_display::Move_Token(uint8_t _u8_player_nr, uint8_t _u8_token_nr,
                                  uint8_t _u8_old_position,
                                  uint8_t _u8_new_position) {
  // remove old position from display
  if (_u8_old_position < 5) {
    // remove from starting square
    obj_matrix->drawPixel(u8_home_positions[_u8_player_nr][_u8_token_nr][0],
                          u8_home_positions[_u8_player_nr][_u8_token_nr][1],
                          0x00);
  } else if (_u8_old_position >= 5 && _u8_old_position <= 40) {
    _u8_old_position -= 5;
    obj_matrix->drawPixel(u8_track_positions[_u8_old_position][1],
                          u8_track_positions[_u8_old_position][2], 0x00);
  } else {
    // remove from finish square
  }
  // add new position to display
  if (_u8_new_position < 5) {
    // add to starting square
    obj_matrix->drawPixel(u8_home_positions[_u8_player_nr][_u8_token_nr][0],
                          u8_home_positions[_u8_player_nr][_u8_token_nr][1],
                          u16_player_color[_u8_player_nr][0]);
  } else if (_u8_new_position >= 5 && _u8_new_position <= 40) {
    _u8_new_position -= 5;
    obj_matrix->drawPixel(u8_track_positions[_u8_new_position][1],
                          u8_track_positions[_u8_new_position][2],
                          u16_player_color[_u8_player_nr][0]);
  } else {
    // add to finish square
  }
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
  //  We want the interupt to occur on falling edge, so ISCn1 = 1 and ISCn0 = 0
  //  last 4 bits for INT5 and INT4.
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
}

uint8_t ASL::Roll_Dice() {
  //
  uint8_t i = TCNT0 + 1;
  return i;
}