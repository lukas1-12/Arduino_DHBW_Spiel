#include <ASL.hpp>
#include <Arduino.h>

extern volatile ASL::en_state en_current_state;

/**
 * \brief interupt routine for the Choose (green) Button.
 */
ISR(INT4_vect) {
  switch (en_current_state) {
  case ASL::setup_real_players:
    en_current_state = ASL::modify_real_player_number;
    break;
  case ASL::modify_real_player_number:
    // NOP
    break;
  case ASL::setup_computer_players:
    en_current_state = ASL::modify_computer_player_number;
    break;
  case ASL::modify_computer_player_number:
    break;
  case ASL::wait_for_dice_roll:
    en_current_state = ASL::roll_the_dice;
    break;
  case ASL::roll_the_dice:
    // NOP
    break;
  case ASL::wait_for_player_input:
    en_current_state = ASL::display_token;
    break;
  case ASL::display_token:
    // NOP
    break;
  case ASL::move_token:
    // NOP
    break;
  case ASL::game_finished:
    en_current_state = ASL::setup_real_players;
    break;
  default:
    // An error occured, go back to setup.
    en_current_state = ASL::setup_real_players;
    break;
  }
}

/**
 * \brief interupt routine for the Submit (red) Button.
 */
ISR(INT5_vect) {
  switch (en_current_state) {
  case ASL::setup_real_players:
    en_current_state = ASL::setup_computer_players;
    break;
  case ASL::modify_real_player_number:
    // NOP
    break;
  case ASL::setup_computer_players:
    en_current_state = ASL::wait_for_dice_roll;
    break;
  case ASL::modify_computer_player_number:
    break;
  case ASL::wait_for_dice_roll:
    // NOP
    break;
  case ASL::roll_the_dice:
    // NOP
    break;
  case ASL::wait_for_player_input:
    en_current_state = ASL::move_token;
    break;
  case ASL::display_token:
    // NOP
    break;
  case ASL::move_token:
    // NOP
    break;
  case ASL::game_finished:
    en_current_state = ASL::setup_real_players;
    break;
  default:
    // An error occured, go back to setup.
    en_current_state = ASL::setup_real_players;
    break;
  }
}