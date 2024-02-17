#include <../../include/defines.hpp>
#include <RGBmatrixPanel.h> // Hardware-specific library#
#include <inttypes.h>
namespace ASL {

/**
 * \brief the states of the finite state machine.
 *
 * Defines the states of the finite state machine. Starting state is 1.
 */
typedef enum {
  display_setup_real_players = 0,
  setup_real_players,                 // 1   0001
  modify_real_player_number,          // 2   0010
  display_setup_computer_players,     // 3   0011
  setup_computer_players,             // 4   0100
  modify_computer_player_number,      // 5   0101
  display_setup_computer_player_mode, // 6   0110
  setup_computer_player_mode,         // 7   0111
  modify_computer_player_mode,        // 8   1000
  init_game_logic,                    // 9   1001
  wait_for_dice_roll,                 // 10  1010
  roll_the_dice,                      // 11  1011
  wait_for_player_input,              // 12  1100
  display_token,                      // 13  1101
  validate_token,                     // 14  1110
  move_token,                         // 15  1111
  next_player,                        // 16 10000
  game_finished                       // 17 10001
} en_state;

typedef enum { off = 0, fast, slow } en_blink_mode;

typedef enum {
  token = 0,
  token_thrown,
  starting_square,
  winner_animation
} en_blink_type;

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
   * \brief Stores the players individual finish Positions.
   * Order: player_nr, token_nr, x/y
   */
  uint8_t u8_finish_positions[4][4][2] = {
      {{3, 7}, {4, 7}, {5, 7}, {6, 7}},
      {{7, 3}, {7, 4}, {7, 5}, {7, 6}},
      {{11, 7}, {10, 7}, {9, 7}, {8, 7}},
      {{7, 11}, {7, 10}, {7, 9}, {7, 8}},
  };

  /**
   * \brief Stores the smiley for the winner animation.
   */
  uint8_t u8_smiley_postitions[26][2] = {
      {0, 2}, {0, 3}, {0, 4}, {0, 5}, {1, 1}, {1, 6}, {2, 0}, {2, 2}, {2, 4},
      {2, 7}, {3, 0}, {3, 5}, {3, 7}, {4, 0}, {4, 5}, {4, 7}, {5, 0}, {5, 2},
      {5, 4}, {5, 7}, {6, 1}, {6, 6}, {7, 2}, {7, 3}, {7, 4}, {7, 5}};

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

  // --- variables for the blink function ---
  /** current blink mode */
  en_blink_mode en_current_blink_mode = off;
  /**
   * current blink counter. Will count down to determine how many blink_clycles
   * are left.
   */
  int8_t i8_blink_counter = 0;
  /** current blink type, determines what is blinking */
  en_blink_type en_current_blink_type = token;
  /** he number of the player to blink. */
  uint8_t u8_blink_player_number = 0;
  /** The number of the second player to blink. Used in token, if occupied flag
   * is set and in display for the second color. */
  int8_t i8_blink_second_player = -1;
  /** old position to blink in token mode */
  uint8_t u8_blink_old_position = 0;
  /** new position to blink in token mode */
  uint8_t u8_blink_new_position = 0;
  /** stores if we are currently in the on or off phase */
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
   * \brief Display the Track
   */
  void Display_Track();

  /**
   * \brief Display the Players all in home.
   *
   * This method is supposed to be called when setting the Game up. It displays
   * the number of players that are currently chosen.
   *
   * \param _u8_player_quantity The number of Players to be displayed.
   */
  void Display_Players(uint8_t _u8_player_quantity,
                       bool _bool_tokens_at_home = true);

  /**
   * \brief Restore Display to track only
   */
  void Display_Restore();

  /**
   * \brief Display the Current Player
   *
   * This method can display the current player on the matrix.
   *
   * \param _i8_current_player_number The number of the current player.
   * \param _u8_tokens_at_home Tokens at home, signaled by the bit position
   * (1 << tokennr -> token is home). default: -1 (don't animate)
   */
  void Display_Current_Player(int8_t _i8_current_player_number,
                              int8_t _i8_tokens_at_home = -1);

  /**
   * \brief Display the Progress
   * This method can display the progress of the Player.
   *
   * \param _i8_current_player_number The number of the current player.
   * \param _u8_progress The progress of the player. (0:28)
   */
  void Display_Progress(int8_t _i8_current_player_number, uint8_t _u8_progress);

  /**
   * \brief Display the Word
   *
   * \param _ch_first_letter The first letter of the word to display. default: '
   * ' \param _ch_second_letter The second letter of the word to display.
   * default: ' '
   */
  void Display_Char(char _ch_first_letter = ' ', char _ch_second_letter = ' ',
                    char _ch_third_letter = ' ');

  /**
   * \brief clears the right half of the display.
   */
  void Display_Clear_Right();

  /**
   * \brief Blink method
   *
   * This method can blink
   * - a token to display possible Progress (token)
   * - two tokens alternating in the color of two players (token_thrown)
   *
   * \param _en_blink_mode The mode of the blinking (fast/slow/off)
   * \param _i8_blink_cycles The number of cycles to blink (-1: infinite)
   * \param _en_blink_type The type of the blinking
   * (token/token_thrown/starting_square/winner_animation)
   * \param _u8_blink_player_number The number of the player to blink.
   * \param _i8_blink_second_player The number of the second player to blink.
   * \param _u8_new_position new position of the token. default: 0. Different
   * use in case of blink_type starting_square: Tokens at home, signaled by the
   * bit position (1 << tokennr -> token is home). \param _bool_occupied_flag
   * flag used in token mode to determine the color to alternate the new
   * position to. default: true \param _u8_old_position old position of the
   * token. default: 0
   */
  void Blink_Start(en_blink_mode _en_blink_mode, int8_t _i8_blink_cycles,
                   en_blink_type _en_blink_type,
                   uint8_t _u8_blink_player_number,
                   int8_t _i8_blink_second_player, uint8_t _u8_new_position = 0,
                   bool _bool_occupied_flag = true,
                   uint8_t _u8_old_position = 0);
  /**
   * \brief Update the Blink state
   *
   * \param _bool_isr_active flag to determine if the function is called from an
   * interupt service routine.
   * \return true if the Blinking wasn't executed due to it possibly taking too
   * long.
   */
  bool Blink_Update(bool _bool_isr_active);

  /**
   * \brief Stop blinking
   */
  void Blink_Stop();

  /**
   * \brief Is Blinking On?
   *
   * \return true if blinking is on, false otherwise
   */
  bool Blink_Is_On();

  void Modify_Position(uint8_t _u8_position, uint8_t _u8_player_number,
                       bool bool_remove);

  /**
   * \brief Move a Token
   *
   * This method can move a token.
   *
   * \param _u8_player_number chosen player
   * \param _u8_old_position old position of the token
   * \param _u8_new_position new position of the token
   */
  void Move_Token(uint8_t _u8_player_nr, uint8_t _u8_remove_position,
                  uint8_t _u8_add_position);

  /**
   * \brief Display the dice
   *
   * Display the Dice on the matrix. when Set to animate, it will play a small
   * animation. The animation uses a simple delay instead of interupts, since
   * the program is not supposed to keep running while the animation is played.
   *
   * \param _u8_dice_value The value to be displayed.
   * \param _u8_dice_roll_counter The number of the current roll.
   * \param _i8_current_player_number The number of the current player.
   * \param _bool_animate flag to determine if the dice should be animated.
   * should be handled with care as it uses Delay. default: true
   */
  void Display_Dice(uint8_t _u8_dice_value, uint8_t _u8_dice_roll_counter,
                    int8_t _i8_current_player_number,
                    bool _bool_animate = true);
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

/**
 * \brief Delay
 *
 * This function is a simple delay function. It uses Timer 5 with /256 clk
 * divider to count to the value in the transfer parameter. when reached, the
 * function returns.
 *
 * \param _u16_delay The number of timer cycles to delay.
 */
void Delay_256(uint16_t _u16_delay);

} // namespace ASL
