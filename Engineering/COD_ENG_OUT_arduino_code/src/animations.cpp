#ifndef ANIMATIONS
#define ANIMATIONS
#include <ASL.hpp>
#include <Arduino.h>
#include <defines.hpp>
#include <logic.hpp>

void Move_Token(int8_t _i8_current_player_number, uint8_t _u8_remove_position,
                uint8_t _u8_add_position, ASL::cla_display *_obj_display,
                LOGIC::cla_session *_obj_session, uint8_t _u8_player_quantity) {
  bool bool_jump = false;
  for (uint8_t i = 1; i <= (_u8_add_position - _u8_remove_position); i++) {
    // take care about the old position
    if (bool_jump) {
      _obj_display->Modify_Position((_u8_remove_position + i - 2),
                                    _i8_current_player_number, false);
      bool_jump = false;
    } else {
      _obj_display->Modify_Position((_u8_remove_position + i - 1),
                                    _i8_current_player_number, false);
    }
    // check if the current position is occupied
    if ((_u8_remove_position + i) != _u8_add_position) {
      for (uint8_t u8_player_i = 0; u8_player_i < _u8_player_quantity;
           u8_player_i++) {
        for (uint8_t u8_token_i = 0; u8_token_i < 4; u8_token_i++) {
          if (_obj_session->array_players[u8_player_i]->Get_Token_Position(
                  u8_token_i) == (_u8_remove_position + i)) {
            // skip that position
            bool_jump = true;
          }
        }
      }
    }
    // Set the new position
    if (!bool_jump) {
      _obj_display->Modify_Position(_u8_remove_position + i,
                                    _i8_current_player_number, true);
      ASL::Delay_256(ANIMATION_SPEED_MOVE);
    }
  }
}

#endif