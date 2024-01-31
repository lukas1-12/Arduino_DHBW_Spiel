#include "logic.hpp"
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

cla_session::cla_session(uint8_t _u8_player_quantity,
                         uint8_t _u8_computer_quantity) {
  u8_player_quantity = _u8_player_quantity;
  u8_computer_quantity = _u8_computer_quantity;
  array_players[u8_player_quantity];

  for (int i = 0; i < _u8_player_quantity; i++) {
    array_players[i] = new cla_player(
        i, 5 + i * 10, _u8_computer_quantity,this); // ID = i, Startposition = 5 + i * 10
  }
};

cla_player::cla_player(uint8_t _u8_player_id, uint8_t _u8_start_position, uint8_t _u8_computer_quantity,
                       cla_session *_obj_my_session) {
  obj_my_session = _obj_my_session;
  u8_player_id = _u8_player_id;
  u8_start_position = _u8_start_position;
  for (int p = 0; p < 4; p++) {
    u8_token_position[p] =
        p + 1; // So each token has a unique position in the home field
  }
  bool is_computer = false;
  for (int q = 0; q < _u8_computer_quantity; q++) {
    is_computer = true;
    new cla_computer_player(this, 0);
  }
};

cla_computer_player::cla_computer_player(cla_player *_obj_my_player, uint8_t _u8_en_mode){
    obj_my_player = _obj_my_player;
    u8_en_mode = _u8_en_mode;
};

std::array<uint8_t, 2>
cla_session::Is_Occupied(uint8_t _u8_affected_track_position) {
  for (uint8_t i = 0; i < u8_player_quantity; i++) {
    for (uint8_t a = 0; a < 4; a++) {
      if (array_players[i]->Get_Token_Position(a) ==
          _u8_affected_track_position) {
        return {i, a}; // i stands for the player ID, a for the token number
      }
    }
  }
  return {10, 0}; // 10 stands for no player at the given track position
}

bool cla_session::Return_Home(uint8_t _u8_affected_track_position) {
  if (Is_Occupied(_u8_affected_track_position).at(0) != 10) {
    array_players[Is_Occupied(_u8_affected_track_position).at(0)]
        ->Set_Token_Position(Is_Occupied(_u8_affected_track_position).at(1),
                             Is_Occupied(_u8_affected_track_position).at(1) +
                                 1); // Set_Token_Position sets the token
                                     // position to the home field (1,2,3,4)
    return true;
  } else {
    return false;
  }
};

uint8_t cla_player::Calculate_Possible_Position(uint8_t _u8_token_number,
                                                uint8_t _u8_dice_value) {
  if (u8_token_position[_u8_token_number] <= 4 &&
      _u8_dice_value ==
          6) { // token is in the home field and would move onto the track
    return u8_start_position;
  } else if (u8_token_position[_u8_token_number] <= 4 &&
             _u8_dice_value != 6) { // token is in the home field and would not
                                    // move onto the track
    return u8_token_position[_u8_token_number];
  } else if (this->Get_Token_Progress(_u8_token_number) + _u8_dice_value > 39 &&
             this->Get_Token_Progress(_u8_token_number) + _u8_dice_value <
                 44) { // token is on the track and would move into the finish
    return Get_Token_Progress(_u8_token_number) + _u8_dice_value + 5;
  } else if (this->Get_Token_Progress(_u8_token_number) + _u8_dice_value > 39 &&
             this->Get_Token_Progress(_u8_token_number) + _u8_dice_value >
                 43) { // token is on the track and would move out of the finish
    return u8_token_position[_u8_token_number];
  } else if (u8_token_position[_u8_token_number] > 44 &&
             u8_token_position[_u8_token_number] + _u8_dice_value < 49) {
    // token is in the finish and would not move out of the finish
    return u8_token_position[_u8_token_number] + _u8_dice_value;
  } else if (u8_token_position[_u8_token_number] > 44 &&
             u8_token_position[_u8_token_number] + _u8_dice_value > 49) {
    // token is in the finish and would move out of the finish
    return u8_token_position[_u8_token_number];
  } else {
    uint8_t u8_possible_position =
        u8_token_position[_u8_token_number] + _u8_dice_value;
    if (u8_possible_position >
        44) { // token is on track and would move out of the track
      u8_possible_position = u8_possible_position - 40;
    }
    return u8_possible_position;
  }
};

uint8_t cla_player::Move_Token(uint8_t _u8_token_number,
                               uint8_t _u8_dice_value) {
  uint8_t u8_possible_position =
      Calculate_Possible_Position(_u8_token_number, _u8_dice_value);
  if (u8_possible_position ==
      Get_Token_Position(
          _u8_token_number)) { // token stays on the same position (e.g would
                               // move out of the finish)
    return Get_Token_Position(_u8_token_number);
  } else if (obj_my_session->Is_Occupied(u8_possible_position).at(0) ==
             10) { // possible position is not occupied
    u8_token_position[_u8_token_number] = u8_possible_position;
    return u8_possible_position;
  } else if (obj_my_session->Is_Occupied(u8_possible_position).at(0) !=
                 u8_player_id &&
             obj_my_session->Is_Occupied(u8_possible_position).at(0) != 10) {
    // possible position is occupied by another player -> other player gets sent
    // home
    obj_my_session->Return_Home(u8_possible_position);
    u8_token_position[_u8_token_number] = u8_possible_position;
    return u8_possible_position;
  } else if (obj_my_session->Is_Occupied(u8_possible_position).at(0) ==
                 u8_player_id &&
             u8_possible_position <
                 45) { // token is on track, position is occupied by other token
                       // of same player and would not move into the finish
                       // -> other token of the same player gets moved one field
                       // further
    Move_Token(_u8_token_number, _u8_dice_value + 1);
    return 0; // error if Move_Token(.... _u8_dice_value+1) is not called
  } else if (obj_my_session->Is_Occupied(u8_possible_position).at(0) ==
                 u8_player_id &&
             u8_possible_position >
                 44) { // token is on track and would move into the finish
    return u8_token_position
        [_u8_token_number]; // token stays on the same position because other
                            // token of the same player is in the way
  } else {
    return 0; // Error
  }
};

uint8_t cla_player::Get_Token_Position(uint8_t _u8_token_number) {
  return u8_token_position[_u8_token_number];
};

uint8_t cla_player::Set_Token_Position(uint8_t _u8_token_number,
                                       uint8_t _u8_new_position) {
  u8_token_position[_u8_token_number] = _u8_new_position;
  return u8_token_position[_u8_token_number];
};

uint8_t cla_player::Get_Token_Progress(uint8_t _u8_token_number) {
  if (u8_token_position[_u8_token_number] >= 5) { // token is on the track
    int8_t i8_token_progress =
        u8_token_position[_u8_token_number] - u8_start_position;
    if (i8_token_progress < 0) { // to compensate the offset for each player
      i8_token_progress =
          u8_token_position[_u8_token_number] + 40 - u8_start_position;
    }
    if (u8_token_position[_u8_token_number] >= 44) {
      i8_token_progress =
          u8_token_position[_u8_token_number] -
          5; // to compensate the offset on the field
    }
    return i8_token_progress;
  } else {
    return 0;
  }
};

status cla_player::Get_Status() {
  uint8_t u8_status = 0; // Position < 5 -> start, 5<=Position<=44 -> Track,
                         // Position > 44 -> Finished
  for (int i = 0; i < 4; i++) {
    if (u8_token_position[i] <= 4) {
      u8_status += 0;
    } else if (u8_token_position[i] <= 44) {
      u8_status += 1;
    } else if (u8_token_position[i] > 44) {
      u8_status += 10;
    }
  };
  if (u8_status == 0) {
    return Start; // all tokens are in start
  } else if (u8_status > 0 &&
             u8_status <
                 10) { // at least one token is on the track, rest is in start
    return Start_Track;
  } else if (u8_status == 10 or u8_status == 20 or
             u8_status == 30) { // max 3 token are finished, rest in start
    return Start_Finished;
  } else if (u8_status > 10 && u8_status <= 12 or
             u8_status > 20 &&
                 u8_status <= 21) { // at least one is in start, one is
                                    // finished, rest on track
    return Start_Track_Finished;
  } else if (u8_status == 4) { // all tokens are on the track
    return Track;
  } else if (u8_status == 40) { // all tokens are finished
    return Finished;
  } else if (u8_status == 13 or u8_status == 22 or
             u8_status ==
                 31) { // at least one token is on track, rest is finished
    return Track_Finished;
  } else {
    return Error;
  }
};

uint8_t cla_player::Get_Player_Progress() {
  uint8_t u8_overall_progress = 0;
  for (uint8_t u8_token_number = 0; u8_token_number < 4; u8_token_number++) {
    u8_overall_progress +=
        this->cla_player::Get_Token_Progress(u8_token_number);
  }
  return u8_overall_progress;
};

bool Is_Computer() { return false; };

uint8_t cla_computer_player::Auto_Move(uint8_t _u8_dice_value) { 
  for(int ii = 0; ii < 4; ii++) {
    if(obj_my_player->Calculate_Possible_Position(ii, _u8_dice_value)> 4) {
      obj_my_player->Move_Token(ii, _u8_dice_value);
      return obj_my_player->Get_Token_Position(ii);
    }
  }
  return 0; // No toke could be moved
};

uint8_t cla_manual_player::Manual_Move(uint8_t _u8_token_number) { return 0; };

uint8_t cla_session::Get_Player_Quantity() { return u8_player_quantity; };

uint8_t cla_player::Get_Start_Position() { return u8_start_position; };

uint8_t cla_player::Get_Player_ID() { return u8_player_id; };