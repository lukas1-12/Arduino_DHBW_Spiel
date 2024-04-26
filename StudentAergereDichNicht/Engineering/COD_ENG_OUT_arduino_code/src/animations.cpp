/**
 * @file animations.cpp
 * \brief This file contains the animations for the game.
 *
 * In this file, all functions that display animations are defined.
 */

#ifndef ANIMATIONS
#define ANIMATIONS
#include <ASL.hpp>
#include <Arduino.h>
#include <defines.hpp>
#include <logic.hpp>

/**
 * \brief This function animates the token movement.
 *
 * This function animates the movement of a token from one position to another.
 *
 * \param _i8_current_player_number The number of the current player.
 * \param _u8_remove_position The start position for the token to start walking.
 * \param _u8_add_position The end position for the token to stop walking.
 * \param _obj_display Pointer to the display object.
 * \param _obj_session Pointer to the session object.
 * \param _u8_player_quantity The number of players.
 * \param _u8_dice_value The distance the token will walk.
 */
void Move_Token(int8_t _i8_current_player_number, uint8_t _u8_remove_position,
                uint8_t _u8_add_position, ASL::cla_display *_obj_display,
                LOGIC::cla_session *_obj_session, uint8_t _u8_player_quantity,
                uint8_t _u8_dice_value) {
  bool bool_jump = false;
  uint8_t i = _u8_remove_position;
  if (_u8_remove_position != _u8_add_position) {
    // only move if the position is not the same
    do {
      i++;
      // take care of the old position
      if (bool_jump) {
        bool_jump = false;
      } else {
        uint8_t u8_modify_position = i - 1;
        if (i == 5) {
          u8_modify_position = 44;
        }
        _obj_display->Modify_Position((u8_modify_position),
                                      _i8_current_player_number, false);
      }
      // handle case that the end of the track is reached
      if (((i) == 45) && (_i8_current_player_number != 0)) {
        i = 5;
      }
      // handle case of end position
      switch (_i8_current_player_number) {
      case 0:
        if (i == 45) {
          i = 45;
        }
        break;
      case 1:
        if (i == 15) {
          i = 45;
        }
        break;
      case 2:
        if (i == 25) {
          i = 45;
        }
        break;
      case 3:
        if (i == 35) {
          i = 45;
        }
        break;
      }
      // check if the current position is occupied, only if its not the end
      // position
      if (i != _u8_add_position) {
        for (uint8_t u8_player_i = 0; u8_player_i < _u8_player_quantity;
             u8_player_i++) {
          for (uint8_t u8_token_i = 0; u8_token_i < 4; u8_token_i++) {
            if (_obj_session->array_players[u8_player_i]->Get_Token_Position(
                    u8_token_i) == (i)) {
              // skip that position
              bool_jump = true;
            }
          }
        }
      }
      // Set the new position
      if (!bool_jump) {
        _obj_display->Modify_Position(i, _i8_current_player_number, true);
        ASL::Delay_256(ANIMATION_SPEED_MOVE);
      }
    } while (i != _u8_add_position);
  }
}

#endif