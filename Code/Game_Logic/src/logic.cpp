#include "logic.hpp"
#include <cstdint>

typedef enum {
  Start = 0,
  Start_Track,
  Start_Finished,
  Start_Track_Finished,
  Error,
  Track,
  Finished,
  Track_Finished,
} status;

cla_session::cla_session(uint8_t _u8_player_quantity,
                         uint8_t _u8_computer_quantity) {
  u8_player_quantity = _u8_player_quantity;
  u8_computer_quantity = _u8_computer_quantity;
};

uint8_t cla_session::Is_Occupied(uint8_t _u8_affected_track_position) {
  for (int i = 0; i < u8_player_quantity; i++) {
    for (int a = 0; a < 4; a++) {
      for (const auto &player : vec_players) {
        if (player->Get_Token_Position(a) == _u8_affected_track_position) {
          return true;
        }
      }
    }
  }
  return false;
}

bool cla_session::Return_Home(uint8_t _u8_affected_track_position) {
  if (Is_Occupied(_u8_affected_track_position)) {
    return true;
  } else {
    return false;
  }
};

cla_player::cla_player(cla_session *_obj_my_session) {
  obj_my_session = _obj_my_session;
};

uint8_t cla_player::Calculate_Possible_Position(uint8_t _u8_token_number,
                                                uint8_t _u8_dice_value) {
  return u8_token_position[_u8_token_number] + _u8_dice_value;
};

uint8_t cla_player::Move_Token(uint8_t _u8_token_number,
                               uint8_t _u8_dice_value){

};

uint8_t cla_player::Get_Token_Position(uint8_t _u8_token_number) {
  return u8_token_position[_u8_token_number];
};

uint8_t cla_player::Get_Token_Progress(uint8_t _u8_token_number) {
  return u8_token_position[_u8_token_number] - u8_start_position;
};

status cla_player::Get_Status(uint8_t _u8_token_number) {
  uint8_t _8_status = 0; // Position < 1 -> start, 0<=Position<=40 -> Track,
                         // Position > 40 -> Finished
  for (int i = 0; i < 4; i++) {
    if (u8_token_position[i] < 0) {
      _8_status += 0;
    } else if (u8_token_position[i] <= 40) {
      _8_status += 1;
    } else if (u8_token_position[i] > 40) {
      _8_status += 10;
    }
  };
  if (_8_status == 0) {
    return Start; // all tokens are in start
  } else if (_8_status > 0 &&
             _8_status <
                 10) { // at least one token is on the track, rest is in start
    return Start_Track;
  } else if (_8_status == 10 or _8_status == 20 or
             _8_status == 30) { // max 3 token are finished, rest in start
    return Start_Finished;
  } else if (_8_status > 10 && _8_status <= 12 or
             _8_status > 20 &&
                 _8_status <= 21) { // at least one is in start, one is
                                    // finished, rest on track
    return Start_Track_Finished;
  } else if (_8_status == 4) { // all tokens are on the track
    return Track;
  } else if (_8_status == 40) { // all tokens are finished
    return Finished;
  } else if (_8_status == 13 or _8_status == 22 or
             _8_status ==
                 31) { // at least one token is on track, rest is finished
    return Track_Finished;
  } else {
    return Error;
  }
};

uint8_t cla_player::Get_Player_Progress() {
  uint8_t _u8_overall_progress = 0;
  for (uint8_t u8_token_number = 0; u8_token_number < 4; u8_token_number++) {
    _u8_overall_progress +=
        this->cla_player::Get_Token_Progress(u8_token_number);
  }
  return _u8_overall_progress;
};

bool Is_Computer() { return false; };

uint8_t cla_computer_player::Auto_Move(uint8_t _u8_token_number){

};

uint8_t cla_manual_player::Manual_Move(uint8_t _u8_token_number){

};