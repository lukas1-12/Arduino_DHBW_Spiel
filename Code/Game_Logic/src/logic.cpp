#include  <cstdint>
#include "logic.hpp"

cla_session::cla_session(uint8_t _u8_player_quantity,
                         uint8_t _u8_computer_quantity) {
  u8_player_quantity = _u8_player_quantity;
  u8_computer_quantity = _u8_computer_quantity;
};

uint8_t cla_session::Is_Occupied(uint8_t _u8_affected_track_position) {
    
};