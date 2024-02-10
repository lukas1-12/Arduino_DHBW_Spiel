#include <RGBmatrixPanel.h> // Hardware-specific library#
#include <inttypes.h>

// See Calculation Excel for more information on the timing.
#define FAST_BLINK 15625
#define SLOW_BLINK 31250

namespace ASL {

/**
 * \brief the states of the finite state machine.
 *
 * Defines the states of the finite state machine. Starting state is 1.
 */
typedef enum {
  setup_real_players = 0,
  modify_real_player_number,     // 1  0001 x
  setup_computer_players,        // 2  0010
  modify_computer_player_number, // 3  0011 x
  init_game_logic,               // 4  0100 x
  wait_for_dice_roll,            // 5  0101
  roll_the_dice,                 // 6  0110 x
  wait_for_player_input,         // 7  0111
  display_token,                 // 8  1000 x
  move_token,                    // 9  1001 x
  game_finished                  // 10 1010
} en_state;

typedef enum { fast = 0, slow } en_blink_mode;

/**
 * \brief display handler
 *
 * This class handles all the functions and parameters needed to display the
 * game.
 */
class cla_display {
  uint8_t u8_matrix_a;   /**< matrix pin a   */
  uint8_t u8_matrix_b;   /**< matrix pin b   */
  uint8_t u8_matrix_c;   /**< matrix pin c   */
  uint8_t u8_matrix_clk; /**< matrix pin clk */
  uint8_t u8_matrix_lat; /**< matrix pin lat */
  uint8_t u8_matrix_oe;  /**< matrix pin oe  */

  /**
   * \brief Pointer to the matrix object.
   */
  RGBmatrixPanel *obj_matrix;

  /**
   * \brief Stores the track positions.
   * Order: track_position, x, y
   */
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

  /**
   * \brief Stores the players individual home Positions.
   * Order: player_nr, token_nr, x/y
   */
  uint8_t u8_home_positions[4][4][2] = {
      {{2, 2}, {2, 3}, {3, 2}, {3, 3}},
      {{11, 2}, {11, 3}, {12, 2}, {12, 3}},
      {{11, 11}, {11, 12}, {12, 11}, {12, 12}},
      {{2, 11}, {2, 12}, {3, 11}, {3, 12}},
  };

  /**
   * \brief Stores the Players Colors.
   * Order: player_nr, bright/dark
   */
  uint16_t u16_player_color[4][2] = {
      {0xf800, 0x1000},
      {0x07e0, 0x00a0},
      {0xffe0, 0x10a0},
      {0x001f, 0x0002},
  };

  /**
   * \brief Stores the Track Color.
   */
  uint16_t u16_track_color = 0xffff;

  uint8_t u8_blink_old_position = 0;
  uint8_t u8_blink_new_position = 0;
  uint8_t u8_blink_counter = 0;
  uint8_t u8_blink_state = 0;

public:
  /**
   * \brief Constructor of the class.
   */
  cla_display(uint8_t _u8_matrix_a, uint8_t u8_matrix_b, uint8_t u8_matrix_c,
              uint8_t u8_matrix_clk, uint8_t u8_lat, uint8_t u8_matrix_oe);

  /**
   * \brief Set the Colors of the player
   *
   * \param _u8_player_nr Number of the Player (0:3)
   * \param _u16_bright_color Bright Color for the Player
   * \param _u16_dark_color Dark Color for the Player
   */
  void Set_Colors(uint8_t _u8_player_nr, uint16_t _u16_bright_color,
                  uint16_t _u16_dark_color);

  /**
   * \brief Initial Setup
   *
   * This function must be called ONCE at the beginning of the Code
   */
  void Begin();

  /**
   * \brief Display the Players.
   *
   * This method is supposed to be called when setting the Game up. It displays
   * the number of players that are currently chosen.
   *
   * \param _u8_player_quantity The number of Players to be displayed.
   */
  void Display_Players(uint8_t _u8_player_quantity);

  /**
   * \brief Display the Current Player
   *
   * This method can display the current player on the matrix.
   *
   * \param _u8_current_player_number The number of the current player.
   */
  void Display_Current_Player(uint8_t _u8_current_player_number);

  /**
   * \brief Display a Token
   *
   * This method can display a token on the matrix.
   *
   * \param _u8_player_number chosen player
   * \param _u8_token_number chosen token
   * \param _u8_new_position new position of the token
   */
  void Display_Token_Start(uint8_t _u8_player_number, uint8_t _u8_new_position);

  /**
   * \brief Blink a Token
   *
   * This method can blink a token.
   *
   * \param _u8_blink_mode The mode of the blinking
   * \param _u8_blink_cycles The number of cycles to blink
   * \param _u8_old_position old position of the token
   * \param _u8_new_position new position of the token
   */
  void Blink_Start(en_blink_mode _u8_blink_mode, uint8_t _u8_blink_cycles,
                   uint8_t _u8_old_position, uint8_t _u8_new_position);

  void Blink_Update();

  void Blink_Stop();

  void Modify_Position(uint8_t _u8_position, uint8_t _u8_player_number,
                       bool bool_remove);

  /**
   * \brief Move a Token
   *
   * This method can move a token.
   *
   * \param _u8_player_number chosen player
   * \param _u8_token_number chosen token
   * \param _u8_old_position old position of the token
   * \param _u8_new_position new position of the token
   */
  void Move_Token(uint8_t _u8_player_nr, uint8_t u8_token_nr,
                  uint8_t _u8_remove_position, uint8_t _u8_add_position);

  /**
   * \brief Display the dice
   *
   * Display the Dice on the matrix.
   * \param _u8_dice_value The value to be displayed.
   */
  void Display_Dice(uint8_t _u8_dice_value, uint8_t _u8_dice_roll_counter,
                    uint8_t _u8_current_player_number);
};

/**
 * \brief setup function for the Buttons
 *
 * Sets Buttons on Pin 2 and 3 to input and enables interupt for them. This
 * function must be called ONCE at the beginning of the program in Order for the
 * Buttons to work.
 */
void Setup_Buttons();

/**
 * \brief setup function for the Dice
 *
 * Sets Timer 0 to count to 5 using CTC mode, so the value read from the TCNT
 * register can be used as a dice value after adding 1. This function must be
 * called ONCE at the beginning of the program in Order for the Dice to work.
 */
void Setup_Dice();

/**
 * \brief roll the Dice.
 *
 * This function reads the TCNT register value, adds one and returns it. In
 * Order to receive a Value between 1 and 6, the Setup_Dice() function must be
 * called beforehand (ONCE).
 */
uint8_t Roll_Dice();

} // namespace ASL
