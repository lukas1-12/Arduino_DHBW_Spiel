/**
 * \file interupt.cpp
 *
 * \brief This file contains all interupt routines.
 */

#include <ASL.hpp>
#include <Arduino.h>
#include <logic.hpp>

extern volatile ASL::en_state en_current_state;
extern uint8_t u8_player_quantity;
extern uint8_t u8_computer_quantity;
extern volatile int8_t i8_current_token_number;
extern ASL::cla_display obj_display;
extern volatile bool bool_blink_flag;

/**
 * \brief interupt routine for the Choose (green) Button.
 *
 * This interupt is used for state manipulation.
 */
ISR(INT4_vect) {
  // Disable INT4:
  EIMSK &= 0b11101111;

#if TIMING_DEBUG
  PORTK |= 0b00000001;
#endif

  switch (en_current_state) {
  case ASL::display_setup_real_players:
    // NOP
    break;
  case ASL::setup_real_players:
    en_current_state = ASL::modify_real_player_number;
    break;
  case ASL::modify_real_player_number:
    // NOP
    break;
  case ASL::display_setup_computer_players:
    // NOP
    break;
  case ASL::setup_computer_players:
    en_current_state = ASL::modify_computer_player_number;
    break;
  case ASL::modify_computer_player_number:
    // NOP
    break;
  case ASL::display_setup_computer_player_mode:
    // NOP
    break;
  case ASL::setup_computer_player_mode:
    en_current_state = ASL::modify_computer_player_mode;
    break;
  case ASL::modify_computer_player_mode:
    // NOP
    break;
  case ASL::init_game_logic:
    // NOP
    break;
  case ASL::wait_for_dice_roll:
    en_current_state = ASL::roll_the_dice;
    break;
  case ASL::roll_the_dice:
    // NOP
    break;
  case ASL::wait_for_player_input:
    en_current_state = ASL::validate_token;
    break;
  case ASL::display_token:
    // NOP
    break;
  case ASL::validate_token:
    // NOP
    break;
  case ASL::move_token:
    // NOP
    break;
  case ASL::next_player:
    // NOP
    break;
  case ASL::game_finished:
    en_current_state = ASL::display_setup_real_players;
    break;
  default:
    // An error occured, go back to setup.
    en_current_state = ASL::display_setup_real_players;
    break;
  }

  // Reset the timer. Interupts must be disabled during this task, because it is
  // a 16 BIT Timer.
  cli();
  TCNT3 = 0x0000;
  sei();
  // clear Interupt Flag Register for Output compare A
  TIFR3 = 1 << OCF3A;

#if TIMING_DEBUG
  PORTK &= 0b11111110;
#endif

  // Enable Timer interupt
  TIMSK3 |= 1 << OCIE3A;
}

/**
 * \brief interupt routine for the Submit (red) Button.
 *
 * This interupt is used for state manipulation.
 */
ISR(INT5_vect) {
  // Disable INT5:
  EIMSK &= 0b11011111;

#if TIMING_DEBUG
  PORTK |= 0b00000010;
#endif

  switch (en_current_state) {
  case ASL::display_setup_real_players:
    // NOP
    break;
  case ASL::setup_real_players:
    if (u8_player_quantity != 4) {
      en_current_state = ASL::display_setup_computer_players;
    } else {
      en_current_state = ASL::init_game_logic;
    }
    break;
  case ASL::modify_real_player_number:
    // NOP
    break;
  case ASL::display_setup_computer_players:
    // NOP
    break;
  case ASL::setup_computer_players:
    if (u8_computer_quantity != 0) {
      en_current_state = ASL::display_setup_computer_player_mode;
    } else {
      en_current_state = ASL::init_game_logic;
    }
    break;
  case ASL::modify_computer_player_number:
    // NOP
    break;
  case ASL::display_setup_computer_player_mode:
    // NOP
    break;
  case ASL::setup_computer_player_mode:
    en_current_state = ASL::init_game_logic;
    break;
  case ASL::modify_computer_player_mode:
    // NOP
    break;
  case ASL::init_game_logic:
    // NOP
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
  case ASL::validate_token:
    // NOP
    break;
  case ASL::move_token:
    // NOP
    break;
  case ASL::next_player:
    // NOP
    break;
  case ASL::game_finished:
    en_current_state = ASL::display_setup_real_players;
    break;
  default:
    // An error occured, go back to setup.
    en_current_state = ASL::display_setup_real_players;
    break;
  }

  // Reset the timer. Interupts must be disabled during this task, because it is
  // a 16 BIT Timer.
  cli();
  TCNT3 = 0x0000;
  sei();
  // clear Interupt Flag Register for Output compare A
  TIFR3 = 1 << OCF3A;

#if TIMING_DEBUG
  PORTK &= 0b11111101;
#endif

  // Enable Timer interupt
  TIMSK3 |= 1 << OCIE3A;
}

/**
 * \brief interupt routine for the Timer 3.
 *
 * This interupt is used for button debounce. it will be triggered shortly after
 * button interupts to reenable the buttons.
 */
ISR(TIMER3_COMPA_vect) {
#if TIMING_DEBUG
  PORTK |= 0b00000100;
#endif

  // Disable Timer Interupt:
  TIMSK3 &= ~(1 << OCIE3A);
  // Enable INT4 and INT5:
  EIMSK |= 0b00110000;
  // Reset Interupt Flags:
  EIFR |= 0b00110000;

#if TIMING_DEBUG
  PORTK &= 0b11111011;
#endif
}

/**
 * \brief interupt routine for the Timer 4.
 *
 * This interupt is used for the display update when using the Blink method. It
 * might just set the bool_blink_flag, if updating the display would take too
 * long for the ISR.
 */
ISR(TIMER4_COMPA_vect) {
#if TIMING_DEBUG
  PORTK |= 0b00001000;
#endif

  bool_blink_flag = obj_display.Blink_Update(true);

#if TIMING_DEBUG
  PORTK &= 0b11110111;
#endif
}

/**
 * \brief interupt routine for the Timer 5.
 *
 * This interupt does nothing except disabling itself. The Delay_256 function
 * will pause and return when this interrupt occurs.
 */
ISR(TIMER5_COMPA_vect) {
#if TIMING_DEBUG
  PORTK |= 0b00010000;
#endif

  // Disable Timer Interupt:
  TIMSK5 &= ~(1 << OCIE5A);

#if TIMING_DEBUG
  PORTK &= 0b11101111;
#endif
}