#include <ASL.hpp>
#include <Arduino.h>
#include <defines.hpp>
#include <logic.hpp>

volatile ASL::en_state en_current_state = ASL::setup_real_players;
uint8_t u8_player_quantity = 1;
uint8_t u8_computer_quantity = 0;

// Use int here, as invalid values are -1
volatile int8_t i8_current_player_number = 0;
volatile int8_t i8_current_token_number = 0;
uint8_t u8_dice_value = 0;
uint8_t u8_dice_roll_counter = 3;
LOGIC::mode en_computer_mode = LOGIC::Student;

// classes
LOGIC::cla_session *obj_session;
ASL::cla_display obj_display(A, B, C, CLK, LAT, OE);

// Variables used to check if the new position is occupied
uint8_t u8_occupying_player;
uint8_t u8_occupying_token;
bool bool_occupied_flag = false;

// Function Prototypes
extern void Move_Token(int8_t _i8_current_player_number,
                       uint8_t _u8_remove_position, uint8_t _u8_add_position,
                       ASL::cla_display *_obj_display,
                       LOGIC::cla_session *_obj_session,
                       uint8_t _u8_player_quantity, uint8_t _u8_dice_value);

void setup() {
  obj_display.Set_Colors(0, RED_BRIGHT, RED_DARK);
  obj_display.Set_Colors(1, BLUE_BRIGHT, BLUE_DARK);
  obj_display.Set_Colors(2, YELLOW_BRIGHT, YELLOW_DARK);
  obj_display.Set_Colors(3, GREEN_BRIGHT, GREEN_DARK);
  obj_display.Begin();
  ASL::Setup_Buttons();
  ASL::Setup_Dice();
#if DEBUG
  // Set Port K to Output
  DDRK = 0xff;
#endif
}

void loop() {
  static uint8_t u8_old_position;
  switch (en_current_state) {
  // -----------------------------------------------------------------------------
  case ASL::setup_real_players:
    if (obj_display.Blink_Is_On()) {
      obj_display.Blink_Stop();
    }
    obj_display.Display_Players(u8_player_quantity);
    break;
  // -----------------------------------------------------------------------------
  case ASL::modify_real_player_number:
    if (u8_player_quantity < 4) {
      u8_player_quantity++;
    } else {
      u8_player_quantity = 0;
    }
#if DEBUG
    // First 4 Bits are for the current state, two for the player quantity and
    // two for computer quantity
    PORTK = en_current_state | ((u8_player_quantity - 1) << 4) |
            (u8_computer_quantity << 6);
#endif
    en_current_state = ASL::setup_real_players;
    break;
  // -----------------------------------------------------------------------------
  case ASL::setup_computer_players:
    obj_display.Display_Players(u8_player_quantity);
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
#if DEBUG
    // First 4 Bits are for the current state, two for the player quantity and
    // two for computer quantity
    PORTK = en_current_state | ((u8_player_quantity - 1) << 4) |
            (u8_computer_quantity << 6);
#endif
    en_current_state = ASL::setup_computer_players;
    break;
  // -----------------------------------------------------------------------------
  case ASL::setup_computer_player_mode:
    // display mode.
    break;
  // -----------------------------------------------------------------------------
  case ASL::modify_computer_player_mode:
    // modify the computer player mode
    switch (en_computer_mode) {
    case LOGIC::Student:
      en_computer_mode = LOGIC::Professor;
      break;
    case LOGIC::Professor:
      en_computer_mode = LOGIC::Student;
      break;
    }
    // Go back to setup state
    en_current_state = ASL::setup_computer_player_mode;
    break;
  // -----------------------------------------------------------------------------
  case ASL::init_game_logic:
    obj_session = new LOGIC::cla_session(
        u8_player_quantity, u8_computer_quantity, en_computer_mode);
#if DEBUG
    // First 4 Bits are for the current state, two for the player quantity and
    // two for computer quantity
    PORTK = en_current_state | ((u8_player_quantity - 1) << 4) |
            (u8_computer_quantity << 6);
#endif
    obj_display.Display_Current_Player(i8_current_player_number);
    en_current_state = ASL::wait_for_dice_roll;
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
    // temporary variables to store the old and new position of the token
    uint8_t u8_old_position;
    uint8_t u8_new_position;
    // Get the old and new position of the token.
    u8_old_position = obj_session->array_players[i8_current_player_number]
                          ->Get_Token_Position(i8_current_token_number);
    u8_new_position = obj_session->array_players[i8_current_player_number]
                          ->Calculate_Possible_Position(i8_current_token_number,
                                                        u8_dice_value);
    // Start blinking the token
    obj_display.Blink_Start(ASL::slow, -1, ASL::token, i8_current_player_number,
                            u8_occupying_player, u8_new_position,
                            bool_occupied_flag, u8_old_position);

#if DEBUG
    PORTK = en_current_state | (i8_current_player_number << 4) |
            (i8_current_token_number << 6);
#endif
    en_current_state = ASL::wait_for_player_input;
  } break;
  // -----------------------------------------------------------------------------
  case ASL::validate_token: {
#if DEBUG
    PORTK = en_current_state | (i8_current_player_number << 4) |
            (i8_current_token_number << 6);
#endif
    en_current_state = ASL::wait_for_player_input;
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
  } break;
  // -----------------------------------------------------------------------------
  case ASL::move_token: {
    // temporary variables to store the old and new position of the token
    uint8_t u8_old_position;
    uint8_t u8_new_position;
    obj_display.Blink_Stop();
    u8_old_position = obj_session->array_players[i8_current_player_number]
                          ->Get_Token_Position(i8_current_token_number);
    u8_new_position = obj_session->array_players[i8_current_player_number]
                          ->Calculate_Possible_Position(i8_current_token_number,
                                                        u8_dice_value);
    if (bool_occupied_flag) {
      obj_display.Move_Token(
          u8_occupying_player, u8_new_position,
          obj_session->array_players[u8_occupying_player]->Get_Token_Position(
              u8_occupying_token));
      obj_display.Blink_Start(ASL::fast, 3, ASL::token_thrown,
                              i8_current_player_number, u8_occupying_player,
                              u8_new_position);
      bool_occupied_flag = false;
    }
    // move the token on the display
    if (u8_old_position >= 5) {
      Move_Token(i8_current_player_number, u8_old_position, u8_new_position,
                 &obj_display, obj_session, u8_player_quantity, u8_dice_value);
    } else {
      obj_display.Move_Token(i8_current_player_number, u8_old_position,
                             u8_new_position);
    }
    // move the token in the logic
    obj_session->array_players[i8_current_player_number]->Move_Token(
        i8_current_token_number, u8_dice_value);
    // determine the next state
    if (u8_dice_roll_counter >= 1) {
      en_current_state = ASL::wait_for_dice_roll;
    } else if (obj_session->array_players[i8_current_player_number]
                   ->Get_Player_Status() == LOGIC::Finished) {
      en_current_state = ASL::game_finished;
    } else {
      en_current_state = ASL::next_player;
    }
  } break;
  // -----------------------------------------------------------------------------
  case ASL::next_player: {
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
      u8_dice_roll_counter = 3;
    } else {
      // roll the dice 1 time (unless you get a 6)
      u8_dice_roll_counter = 1;
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
        uint8_t u8_new_position = 0;
        u8_dice_value = ASL::Roll_Dice();
        if (u8_dice_value == 6) {
          u8_dice_roll_counter = 1;
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
        if (bool_occupied_flag) {
          u8_occupying_player = obj_session->u8_is_occupied_player_id;
          u8_occupying_token = obj_session->u8_is_occupied_token_number;
          obj_display.Move_Token(u8_occupying_player, u8_new_position,
                                 obj_session->array_players[u8_occupying_player]
                                     ->Get_Token_Position(u8_occupying_token));
          obj_display.Blink_Start(ASL::fast, 3, ASL::token_thrown,
                                  i8_current_player_number, u8_occupying_player,
                                  u8_new_position);
          bool_occupied_flag = false;
        }
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
    // Reset the token number for the next player
    i8_current_token_number = 0;
  } break;
  // -----------------------------------------------------------------------------
  case ASL::game_finished:
    // delete obj_session;
    static bool bool_do_once = true;
    if (bool_do_once) {
      obj_display.Blink_Start(ASL::slow, -1, ASL::winner_animation,
                              i8_current_player_number, -1);
      obj_display.Display_Restore();
      bool_do_once = false;
    }
    asm volatile("nop"); // Do nothing
    break;
  default:
    // An error occured, go back to setup.
    en_current_state = ASL::setup_real_players;
    break;
  }
}
