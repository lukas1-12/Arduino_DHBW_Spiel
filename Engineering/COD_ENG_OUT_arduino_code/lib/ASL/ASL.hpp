#include <RGBmatrixPanel.h> // Hardware-specific library#
#include <inttypes.h>

namespace ASL {

typedef enum {
  setup_real_players = 1,
  modify_real_player_number,
  setup_computer_players,
  modify_computer_player_number,
  wait_for_dice_roll,
  roll_the_dice,
  wait_for_player_input,
  display_token,
  move_token,
  game_finished
} en_state;

class cla_display {
  uint8_t u8_matrix_a;
  uint8_t u8_matrix_b;
  uint8_t u8_matrix_c;
  uint8_t u8_matrix_clk;
  uint8_t u8_matrix_lat;
  uint8_t u8_matrix_oe;
  RGBmatrixPanel *obj_matrix;
  // track_position, x, y
  uint8_t u8_track_positions[40][3] = {
      {5, 2, 6},   {6, 3, 6},   {7, 4, 6},   {8, 5, 6},   {9, 6, 6},
      {10, 6, 5},  {11, 6, 4},  {12, 6, 3},  {13, 6, 2},  {14, 7, 2},
      {15, 8, 2},  {16, 8, 3},  {17, 8, 4},  {18, 8, 5},  {19, 8, 6},
      {20, 9, 6},  {21, 10, 6}, {22, 11, 6}, {23, 12, 6}, {24, 12, 7},
      {25, 12, 8}, {26, 11, 8}, {27, 10, 8}, {28, 9, 8},  {29, 8, 8},
      {30, 8, 9},  {31, 8, 10}, {32, 8, 11}, {33, 8, 12}, {34, 7, 12},
      {35, 6, 12}, {36, 6, 11}, {37, 6, 10}, {38, 6, 9},  {39, 6, 8},
      {40, 5, 8},  {41, 4, 8},  {42, 3, 8},  {43, 2, 8},  {44, 2, 7},
  };
  // player_nr, token_nr, x/y
  uint8_t u8_home_positions[4][4][2] = {
      {{2, 2}, {2, 3}, {3, 2}, {3, 3}},
      {{11, 2}, {11, 3}, {12, 2}, {12, 3}},
      {{11, 11}, {11, 12}, {12, 11}, {12, 12}},
      {{2, 11}, {2, 12}, {3, 11}, {3, 12}},
  };
  // player_nr, bright/dark
  uint16_t u16_player_color[4][2] = {
      {0xf800, 0x1000},
      {0x07e0, 0x00a0},
      {0xffe0, 0x10a0},
      {0x001f, 0x0002},
  };
  uint16_t u16_track_color = 0xffff;

public:
  void Begin();
  cla_display(uint8_t _u8_matrix_a, uint8_t u8_matrix_b, uint8_t u8_matrix_c,
              uint8_t u8_matrix_clk, uint8_t u8_lat, uint8_t u8_matrix_oe);
  void Set_Colors(uint8_t _u8_player_nr, uint16_t _u16_bright_color,
                  uint16_t _u16_dark_color);
  void Display_Dice(uint8_t _u8_dice_value);
};

void Setup_Buttons();

} // namespace ASL
