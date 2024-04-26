/**
 * \file main.cpp
 * \brief This file contains the main loop and setup of the game.
 *
 * In this file, the setup and loop functions are implemented.
 */

#include <ASL.hpp>
#include <Arduino.h>
#include <defines.hpp>
#include <logic.hpp>

// Global Variables, because they are used in the interupt routine or setup
// function.
volatile ASL::en_state en_current_state = ASL::display_setup_real_players;
// used in ISR (but not changed):
uint8_t u8_player_quantity;
uint8_t u8_computer_quantity;

// Use int here, as invalid values are -1
volatile int8_t i8_current_player_number;
volatile int8_t i8_current_token_number;

// classes
LOGIC::cla_session *obj_session;
ASL::cla_display obj_display(A, B, C, CLK, LAT, OE);

// Used for blinking
volatile bool bool_blink_flag = false;

// Function Prototypes
extern void Move_Token(int8_t _i8_current_player_number,
                       uint8_t _u8_remove_position, uint8_t _u8_add_position,
                       ASL::cla_display *_obj_display,
                       LOGIC::cla_session *_obj_session,
                       uint8_t _u8_player_quantity, uint8_t _u8_dice_value);

#if TIMING_DEBUG_INTERN != 0
volatile uint8_t u8_timing_debug_array[101];
volatile uint8_t u8_timing_debug_counter = 0;
#endif

void setup() {
  obj_display.Set_Colors(0, RED_BRIGHT, RED_DARK);
  obj_display.Set_Colors(1, BLUE_BRIGHT, BLUE_DARK);
  obj_display.Set_Colors(2, YELLOW_BRIGHT, YELLOW_DARK);
  obj_display.Set_Colors(3, GREEN_BRIGHT, GREEN_DARK);
  obj_display.Begin();
  ASL::Setup_Buttons();
  ASL::Setup_Dice();
#if DEBUG || TIMING_DEBUG
  // Set Port K to Output
  DDRK = 0xff;
#endif
#if TIMING_DEBUG_INTERN != 0
  // Set Timer 2 to prescaler 0
  TCCR2A = 0x00;
  TCCR2B = 0x00;
  TCCR2B |= (1 << CS20);
  Serial.begin(9600);
#endif
}

void loop() {
  // Variables used to check if the new position is occupied
  static uint8_t u8_occupying_player;
  static uint8_t u8_occupying_token;
  static bool bool_occupied_flag;

  // dice variables
  static uint8_t u8_dice_value;
  static uint8_t u8_dice_roll_counter;

  // player setup variables
  static LOGIC::mode en_computer_mode;

  static uint8_t u8_old_position;
  static uint8_t u8_new_position;
  switch (en_current_state) {
  // -----------------------------------------------------------------------------
  case ASL::display_setup_real_players:
    // ...........................................................................
    // .............................INITIALIZATION................................
    // ...........................................................................
    // This is the first state, so we will set some initial values here.
    u8_dice_value = INITIAL_DICE_VALUE;
    u8_dice_roll_counter = INITIAL_DICE_ROLL_COUNTER;
    en_computer_mode = INITIAL_COMPUTER_MODE;
    u8_player_quantity = INITIAL_PLAYER_QUANTITY;
    u8_computer_quantity = INITIAL_COMPUTER_QUANTITY;
    i8_current_player_number = INITIAL_CURRENT_PLAYER_NUMBER;
    i8_current_token_number = INITIAL_CURRENT_TOKEN_NUMBER;
    bool_blink_flag = INITIAL_BOOL_BLINK_FLAG;
    // ...........................................................................
    if (obj_display.Blink_Is_On()) {
      obj_display.Blink_Stop();
    }
    obj_display.Display_Restore();
    obj_display.Display_Players(u8_player_quantity);
    obj_display.Display_Char('R', 'E', 'A');
    en_current_state = ASL::setup_real_players;
    break;
  // -----------------------------------------------------------------------------
  case ASL::setup_real_players:
    // NOP
    break;
  // -----------------------------------------------------------------------------
  case ASL::modify_real_player_number:
    if (u8_player_quantity < 4) {
      u8_player_quantity++;
    } else {
      u8_player_quantity = 0;
    }
    obj_display.Display_Players(u8_player_quantity);
#if DEBUG
    // First 4 Bits are for the current state, two for the player quantity and
    // two for computer quantity
    PORTK = en_current_state | ((u8_player_quantity - 1) << 4) |
            (u8_computer_quantity << 6);
#endif
    en_current_state = ASL::setup_real_players;
    break;
  // -----------------------------------------------------------------------------
  case ASL::display_setup_computer_players:
    obj_display.Display_Players(u8_player_quantity);
    obj_display.Display_Char('C', 'O', 'M');
    en_current_state = ASL::setup_computer_players;
    break;
  // -----------------------------------------------------------------------------
  case ASL::setup_computer_players:
    // NOP
    break;
  // -----------------------------------------------------------------------------
  case ASL::modify_computer_player_number:
    if (u8_player_quantity < 4) {
      u8_player_quantity++;
      u8_computer_quantity++;
    } else {
      u8_player_quantity = u8_player_quantity - u8_computer_quantity;
      u8_computer_quantity = 0;
    }
    obj_display.Display_Players(u8_player_quantity);
#if DEBUG
    // First 4 Bits are for the current state, two for the player quantity and
    // two for computer quantity
    PORTK = en_current_state | ((u8_player_quantity - 1) << 4) |
            (u8_computer_quantity << 6);
#endif
    en_current_state = ASL::setup_computer_players;
    break;
  // -----------------------------------------------------------------------------
  case ASL::display_setup_computer_player_mode:
    obj_display.Display_Char('S', 'T', 'U');
    en_current_state = ASL::setup_computer_player_mode;
    break;
  case ASL::setup_computer_player_mode:
    // display mode.
    break;
  // -----------------------------------------------------------------------------
  case ASL::modify_computer_player_mode:
    // modify the computer player mode
    switch (en_computer_mode) {
    case LOGIC::Student:
      en_computer_mode = LOGIC::Professor;
      obj_display.Display_Char('P', 'R', 'O');
      break;
    case LOGIC::Professor:
      en_computer_mode = LOGIC::Student;
      obj_display.Display_Char('S', 'T', 'U');
      break;
    }
    // Go back to setup state
    en_current_state = ASL::setup_computer_player_mode;
    break;
  // -----------------------------------------------------------------------------
  case ASL::init_game_logic:
    // remove txt from display
    obj_display.Display_Char();
    obj_session = new LOGIC::cla_session(
        u8_player_quantity, u8_computer_quantity, en_computer_mode);
#if DEBUG
    // First 4 Bits are for the current state, two for the player quantity and
    // two for computer quantity
    PORTK = en_current_state | ((u8_player_quantity - 1) << 4) |
            (u8_computer_quantity << 6);
#endif
    obj_display.Display_Current_Player(i8_current_player_number);
    if (u8_player_quantity != u8_computer_quantity) {
      // Only wait for dice roll, if there are real players
      en_current_state = ASL::wait_for_dice_roll;
    } else {
      // Set the player number to minus one: In next_player state, the next
      // player is chosen by adding one to the current player number, and we
      // want to start at player 0.
      i8_current_player_number = -1;
      en_current_state = ASL::next_player;
    }
    break;
  // -----------------------------------------------------------------------------
  case ASL::wait_for_dice_roll:
    // NOP
    break;
  // -----------------------------------------------------------------------------
  case ASL::roll_the_dice:
    u8_dice_value = ASL::Roll_Dice();
    u8_dice_roll_counter--;
    obj_display.Display_Dice(u8_dice_value, u8_dice_roll_counter,
                             i8_current_player_number);
    // You can roll the dice up to 3 times, when all your tokens are still in
    // the Starting Square and you did not get a 6.
    if ((obj_session->array_players[i8_current_player_number]
             ->Get_Player_Status() == LOGIC::Start) &&
        (u8_dice_roll_counter >= 1) && (u8_dice_value != 6)) {
      // one more chance for the same player
      en_current_state = ASL::wait_for_dice_roll;
    } else if ((obj_session->array_players[i8_current_player_number]
                    ->Get_Player_Status() == LOGIC::Start) &&
               u8_dice_roll_counter <= 0 && u8_dice_value != 6) {
      // If you did not get a 6 and dice roll counter is 0,
      // wait for next player to roll dice
      en_current_state = ASL::next_player;
    } else if (u8_dice_value == 6) {
      // If you got a 6, your token is moved out of the Starting Square
      en_current_state = ASL::validate_token;
      u8_dice_roll_counter = 1;
    } else {
      // If you got a number between 1 and 5, you can move a token
      en_current_state = ASL::validate_token;
    }
#if DEBUG
    PORTK = en_current_state | (i8_current_player_number << 4) |
            (i8_current_token_number << 6);
    ;
#endif
    break;
  // -----------------------------------------------------------------------------
  case ASL::wait_for_player_input:
    // NOP
    break;
  // -----------------------------------------------------------------------------
  case ASL::display_token: {
    // First, stop previous blinking, if it was blinking.
    obj_display.Blink_Stop();
    // Start blinking the token
    obj_display.Blink_Start(ASL::slow, BLINK_CYCLES_TOKEN, ASL::token,
                            i8_current_player_number, u8_occupying_player,
                            u8_new_position, bool_occupied_flag,
                            u8_old_position);

#if DEBUG
    PORTK = en_current_state | (i8_current_player_number << 4) |
            (i8_current_token_number << 6);
#endif
    en_current_state = ASL::wait_for_player_input;
  } break;
  // -----------------------------------------------------------------------------
  case ASL::validate_token: {
    if (i8_current_token_number < 3) {
      i8_current_token_number++;
    } else {
      i8_current_token_number = 0;
    }
#if DEBUG
    PORTK = en_current_state | (i8_current_player_number << 4) |
            (i8_current_token_number << 6);
#endif
    // Lets get the current player state, so we don't have to do it several
    // times in the else if statement.
    LOGIC::status en_player_state =
        obj_session->array_players[i8_current_player_number]
            ->Get_Player_Status();
    // check if a token must be moved from starting square
    if (obj_session->array_players[i8_current_player_number]
            ->Is_Start_Field_Occupied_By_Own_Token() != -1) {
      i8_current_token_number =
          obj_session->array_players[i8_current_player_number]
              ->Is_Start_Field_Occupied_By_Own_Token();
      en_current_state = ASL::move_token;
    } else if ((u8_dice_value == 6) &&
               ((en_player_state == LOGIC::Start) ||
                (en_player_state == LOGIC::Start_Track) ||
                (en_player_state == LOGIC::Start_Finished) ||
                (en_player_state == LOGIC::Start_Track_Finished))) {
      // if a 6 was rolled and there are still token in the starting square, the
      // player cannot choose a token to move, so lets look for a token in the
      // starting square
      i8_current_token_number = 0;
      while (obj_session->array_players[i8_current_player_number]
                 ->Get_Token_Position(i8_current_token_number) >= 5) {
        // increase token number as long as the token is not in the starting
        // square
        i8_current_token_number++;
      }
      en_current_state = ASL::move_token;
    }
    // if no specific token must be moved, check if any token can be moved
    else {
      // variable used to determine how many token can be moved
      uint8_t u8_token_counter = 0;
      // variable used to determine the next movable Token
      int8_t u8_next_movable_token = -1;
      // check how many tokens can be moved:
      for (uint8_t i = 0; i < 4; i++) {
        if (obj_session->array_players[i8_current_player_number]
                ->Calculate_Possible_Position(i, u8_dice_value) !=
            obj_session->array_players[i8_current_player_number]
                ->Get_Token_Position(i)) {
          u8_token_counter++;
          // determine the next movable token
          if (u8_next_movable_token == -1) {
            // if it is -1, no token was found yet, so use the current token
            u8_next_movable_token = i;
          } else if ((u8_next_movable_token < i8_current_token_number) &&
                     (i >= i8_current_token_number)) {
            // we want the smallest token number that is larger than the current
            // token number, if there is one.
            u8_next_movable_token = i;
          }
        }
      }
      // set current token number to the next movable token
      i8_current_token_number = u8_next_movable_token;
      // handle cases of tokens that can be moved.
      if (u8_token_counter == 0) {
        // If no token can be moved, next player is chosen
        en_current_state = ASL::next_player;
      } else if (u8_token_counter == 1) {
        // If only one token can be moved, it is chosen and moved.
        en_current_state = ASL::move_token;
      } else {
        // If more than one token can be moved, display it, so the Player can
        // Choose.
        en_current_state = ASL::display_token;
      }
    }
    // check if the new position is occupied and set the occupied flag
    // accordingly.
    bool_occupied_flag = obj_session->Is_Occupied(
        u8_occupying_player, u8_occupying_token,
        obj_session->array_players[i8_current_player_number]
            ->Calculate_Possible_Position(i8_current_token_number,
                                          u8_dice_value));
    // Get the old and new position of the token.
    u8_old_position = obj_session->array_players[i8_current_player_number]
                          ->Get_Token_Position(i8_current_token_number);
    u8_new_position = obj_session->array_players[i8_current_player_number]
                          ->Calculate_Possible_Position(i8_current_token_number,
                                                        u8_dice_value);
  } break;
  // -----------------------------------------------------------------------------
  case ASL::move_token: {
    obj_display.Blink_Stop();
    // move the token on the display
    if (u8_old_position >= 5) {
      Move_Token(i8_current_player_number, u8_old_position, u8_new_position,
                 &obj_display, obj_session, u8_player_quantity, u8_dice_value);
    } else {
      obj_display.Move_Token(i8_current_player_number, u8_old_position,
                             u8_new_position);
    }
    // move the token in the logic (must be done before setting the occupied
    // token, because the new position is set here.)
    obj_session->array_players[i8_current_player_number]->Move_Token(
        i8_current_token_number, u8_dice_value);
    // Move the occupying token on the display, if needed.
    if (bool_occupied_flag) {
      obj_display.Move_Token(
          u8_occupying_player, u8_new_position,
          obj_session->array_players[u8_occupying_player]->Get_Token_Position(
              u8_occupying_token));
      obj_display.Blink_Start(ASL::fast, BLINK_CYCLES_OCCUPIED_TOKEN,
                              ASL::token_thrown, i8_current_player_number,
                              u8_occupying_player, u8_new_position);
      bool_occupied_flag = false;
    }
    // determine the next state
    if (u8_dice_roll_counter >= 1) {
      en_current_state = ASL::wait_for_dice_roll;
    } else {
      en_current_state = ASL::next_player;
    }
  } break;
  // -----------------------------------------------------------------------------
  case ASL::next_player: {
    if (obj_session->array_players[i8_current_player_number]
            ->Get_Player_Status() == LOGIC::Finished) {
      // clear the right half of the display
      obj_display.Display_Clear_Right();
      // Start winner animation
      obj_display.Display_Progress(i8_current_player_number, 28);
      obj_display.Blink_Start(ASL::slow, BLINK_CYCLES_WINNER_ANIMATION,
                              ASL::winner_animation, i8_current_player_number,
                              BLINK_CYCLES_WINNER_ANIMATION);
      delete obj_session;
      en_current_state = ASL::game_finished;
      break;
    } else {
      if (i8_current_player_number < (u8_player_quantity - 1)) {
        i8_current_player_number++;
      } else {
        i8_current_player_number = 0;
      }
      // Calculate transfer parameter for display current player
      int8_t i8_tokens_at_home = 0;
      for (uint8_t i = 0; i < 4; i++) {
        if (obj_session->array_players[i8_current_player_number]
                ->Get_Token_Position(i) < 5) {
          i8_tokens_at_home |= (1 << i);
        }
      }
      // before the current player can be displayed, blinking animation (throw)
      // must be finished. Otherwise the wrong token might be displayed on the
      // position somebody was thrown from, because the blinking is restarted in
      // another mode (starting_square) and the Blink_Stop() method was never
      // called. This could lead to the wrong token being displayed, since the
      // position is alternating in the two colors. If the blinking gets
      // disrupted while the thrown token is displayed, the wrong token stays
      // displayed.
      while (obj_display.Blink_Is_On()) {
        // Wait for blinking animation to finish, so the thrown animation isn't
        // getting messed up by the next player's starting square blinking.
        // If no token was thrown, Blink_Is_On will immediatly return false and
        // the loop will never be executed.
        asm volatile("nop"); // Do nothing
      }
      obj_display.Display_Current_Player(i8_current_player_number,
                                         i8_tokens_at_home);
      // Display the progress bar:
      obj_display.Display_Progress(
          i8_current_player_number,
          obj_session->array_players[i8_current_player_number]
              ->Get_Player_Progress());
      //  Set the dice roll counter for the next player:
      if (obj_session->array_players[i8_current_player_number]
              ->Get_Player_Status() == LOGIC::Start) {
        // roll the dice 3 times
        u8_dice_roll_counter = DICE_ROLLS_AT_START;
      } else {
        // roll the dice 1 time (unless you get a 6)
        u8_dice_roll_counter = DICE_ROLLS_NORMAL;
      }
      en_current_state = ASL::wait_for_dice_roll;
      while (obj_display.Blink_Is_On()) {
        // Wait for blinking animation to finish, so the starting square isn't
        // getting messed up by the player leaving the starting square.
        asm volatile("nop"); // Do nothing
      }
      // ------ Auto-move if we have a computer player ---------
      if (obj_session->array_players[i8_current_player_number]->Is_Computer()) {
        while (u8_dice_roll_counter > 0) {
          // Computer code here
          u8_dice_value = ASL::Roll_Dice();
          if (u8_dice_value == 6) {
            u8_dice_roll_counter = DICE_ROLLS_AT_SIX;
          } else {
            u8_dice_roll_counter--;
          }
          obj_display.Display_Dice(u8_dice_value, u8_dice_roll_counter,
                                   i8_current_player_number);
          ASL::Delay_256(ANIMATION_SPEED_COMPUTER);
          i8_current_token_number =
              obj_session->array_players[i8_current_player_number]->Auto_Move(
                  u8_dice_value, bool_occupied_flag, u8_old_position);
          u8_new_position = obj_session->array_players[i8_current_player_number]
                                ->Get_Token_Position(i8_current_token_number);
          if (i8_current_token_number != -1) {
            // move the token on the display
            if (u8_old_position >= 5) {
              Move_Token(i8_current_player_number, u8_old_position,
                         u8_new_position, &obj_display, obj_session,
                         u8_player_quantity, u8_dice_value);
            } else {
              obj_display.Move_Token(i8_current_player_number, u8_old_position,
                                     u8_new_position);
            }
          }
          if (bool_occupied_flag) {
            u8_occupying_player = obj_session->u8_is_occupied_player_id;
            u8_occupying_token = obj_session->u8_is_occupied_token_number;
            obj_display.Move_Token(
                u8_occupying_player, u8_new_position,
                obj_session->array_players[u8_occupying_player]
                    ->Get_Token_Position(u8_occupying_token));
            obj_display.Blink_Start(ASL::fast, BLINK_CYCLES_OCCUPIED_TOKEN,
                                    ASL::token_thrown, i8_current_player_number,
                                    u8_occupying_player, u8_new_position);
            bool_occupied_flag = false;
          }
          if (u8_dice_roll_counter > 0) {
            ASL::Delay_256(ANIMATION_SPEED_COMPUTER);
          }
#if DEBUG
          PORTK = en_current_state | ((i8_current_player_number << 4) && 0x0f) |
                  ((i8_current_token_number << 6) && 0x0f);
#endif
          en_current_state = ASL::next_player;
        }
      }
    }
    // Reset the token number for the next player
    i8_current_token_number = 0;
  } break;
  // -----------------------------------------------------------------------------
  case ASL::game_finished:
    asm volatile("nop"); // Do nothing
    break;
  default:
    // An error occured, go back to setup.
    en_current_state = ASL::display_setup_real_players;
    break;
  }
  // ------------------------------Blinking--------------------------------------
  if (bool_blink_flag) {
    obj_display.Blink_Update(false);
    bool_blink_flag = false;
  }
#if TIMING_DEBUG_INTERN != 0
  if (u8_timing_debug_counter > TIMING_DEBUG_COUNT_TO) {
    obj_display.obj_matrix->dumpMatrix();
    Serial.println("--------------------");
    for (uint8_t i = 0; i < TIMING_DEBUG_COUNT_TO; i++) {
      Serial.print(u8_timing_debug_array[i]);
      Serial.print(" ");
    }
  }
#endif
}
