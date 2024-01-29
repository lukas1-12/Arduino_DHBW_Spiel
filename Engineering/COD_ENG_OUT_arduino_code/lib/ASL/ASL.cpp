#include <ASL.hpp>
#include <Arduino.h>

ASL::cla_display::cla_display(uint8_t _u8_matrix_a, uint8_t _u8_matrix_b,
                              uint8_t _u8_matrix_c, uint8_t _u8_matrix_clk,
                              uint8_t _u8_matrix_lat, uint8_t _u8_matrix_oe) {
  RGBmatrixPanel obj_matrix(_u8_matrix_a, _u8_matrix_b, _u8_matrix_c,
                            _u8_matrix_clk, _u8_matrix_lat, _u8_matrix_oe,
                            false);
  obj_matrix.begin();
  this->obj_matrix = &obj_matrix;
}

void ASL::cla_display::Begin() {
  for (uint8_t i = 0; i < 40; i++) {
    obj_matrix->drawPixel(u8_track_positions[i][1], u8_track_positions[i][2],
                          u16_track_color);
  }
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      obj_matrix->drawPixel(u8_home_positions[i][j][0],
                            u8_home_positions[i][j][1], u16_player_color[i][0]);
    }
  }
}

void ASL::cla_display::Set_Colors(uint8_t _u8_player_nr,
                                  uint16_t _u16_bright_color,
                                  uint16_t _u16_dark_color) {
  u16_player_color[_u8_player_nr][0] = _u16_bright_color;
  u16_player_color[_u8_player_nr][1] = _u16_dark_color;
}

void ASL::cla_display::Display_Dice(uint8_t _u8_dice_value) {
  obj_matrix->drawPixel(17, 3, 0x00);
  obj_matrix->drawPixel(16, 2, 0x00);
  obj_matrix->drawPixel(16, 3, 0x00);
  obj_matrix->drawPixel(16, 4, 0x00);
  obj_matrix->drawPixel(18, 2, 0x00);
  obj_matrix->drawPixel(18, 3, 0x00);
  obj_matrix->drawPixel(18, 4, 0x00);
  switch (_u8_dice_value) {
  case 0:
    // Just leave it turned off.
    break;
  case 1:
    obj_matrix->drawPixel(17, 3, u16_track_color);
    break;
  case 2:
    obj_matrix->drawPixel(16, 2, u16_track_color);
    obj_matrix->drawPixel(18, 4, u16_track_color);
    break;
  case 3:
    obj_matrix->drawPixel(17, 3, u16_track_color);
    obj_matrix->drawPixel(16, 2, u16_track_color);
    obj_matrix->drawPixel(18, 4, u16_track_color);
    break;
  case 4:
    obj_matrix->drawPixel(16, 2, u16_track_color);
    obj_matrix->drawPixel(18, 4, u16_track_color);
    obj_matrix->drawPixel(16, 4, u16_track_color);
    obj_matrix->drawPixel(18, 2, u16_track_color);
    break;
  case 5:
    obj_matrix->drawPixel(16, 2, u16_track_color);
    obj_matrix->drawPixel(18, 4, u16_track_color);
    obj_matrix->drawPixel(16, 4, u16_track_color);
    obj_matrix->drawPixel(18, 2, u16_track_color);
    obj_matrix->drawPixel(17, 3, u16_track_color);
    break;
  case 6:
    obj_matrix->drawPixel(16, 2, u16_track_color);
    obj_matrix->drawPixel(16, 3, u16_track_color);
    obj_matrix->drawPixel(16, 4, u16_track_color);
    obj_matrix->drawPixel(18, 2, u16_track_color);
    obj_matrix->drawPixel(18, 3, u16_track_color);
    obj_matrix->drawPixel(18, 4, u16_track_color);
    break;
  default:
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
}
