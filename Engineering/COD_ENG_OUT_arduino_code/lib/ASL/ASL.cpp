#include <ASL.hpp>

void draw(RGBmatrixPanel *matrix) {
  matrix->drawPixel(2, 6, matrix->Color333(7, 0, 0));
  matrix->drawPixel(6, 2, matrix->Color333(7, 0, 0));
  matrix->drawPixel(8, 6, matrix->Color333(7, 0, 0));
  matrix->drawPixel(12, 6, matrix->Color333(7, 0, 0));
  matrix->drawPixel(8, 8, matrix->Color333(7, 0, 0));
  matrix->drawPixel(8, 12, matrix->Color333(7, 0, 0));
}

ASL::cla_board::cla_board(uint8_t _u8_matrix_a, uint8_t _u8_matrix_b,
                          uint8_t _u8_matrix_c, uint8_t _u8_matrix_clk,
                          uint8_t _u8_matrix_lat, uint8_t _u8_matrix_oe) {
  RGBmatrixPanel obj_matrix(_u8_matrix_a, _u8_matrix_b, _u8_matrix_c,
                            _u8_matrix_clk, _u8_matrix_lat, _u8_matrix_oe,
                            false);
  obj_matrix.begin();
  this->obj_matrix = &obj_matrix;
}

void ASL::cla_board::Begin() {
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

void ASL::cla_board::Set_Colors(uint8_t _u8_player_nr,
                                uint16_t _u16_bright_color,
                                uint16_t _u16_dark_color) {
  u16_player_color[_u8_player_nr][0] = _u16_bright_color;
  u16_player_color[_u8_player_nr][1] = _u16_dark_color;
}