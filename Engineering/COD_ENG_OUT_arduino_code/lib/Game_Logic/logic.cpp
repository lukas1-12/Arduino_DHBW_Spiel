#include "logic.hpp"
#include <cstdint>

#ifndef __AVR__
#include <iostream>
#endif

namespace LOGIC {
cla_session::cla_session(uint8_t _u8_player_quantity,
                         uint8_t _u8_computer_quantity, mode _en_mode) {
  u8_player_quantity = _u8_player_quantity;
  u8_computer_quantity = _u8_computer_quantity;
  array_players[u8_player_quantity];
  u8_is_occupied_player_id = 10;
  u8_is_occupied_token_number = 10;

  for (int i = 0; i < _u8_player_quantity; i++) {
    if (_u8_player_quantity - _u8_computer_quantity > i)
      array_players[i] =
          new cla_manual_player(i, 5 + i * 10, _u8_computer_quantity,
                                this); // ID = i, Startposition = 5 + i * 10
    else {
      array_players[i] = new cla_computer_player(
          i, 5 + i * 10, _u8_computer_quantity, this,
          _en_mode); // ID = i, Startposition = 5 + i * 10
    }
  }
};

cla_player::cla_player(uint8_t _u8_player_id, uint8_t _u8_start_position,
                       uint8_t _u8_computer_quantity,
                       cla_session *_obj_my_session) {
  obj_my_session = _obj_my_session;
  u8_player_id = _u8_player_id;
  u8_start_position = _u8_start_position;
  for (int p = 0; p < 4; p++) {
    u8_token_position[p] =
        p + 1; // So each token has a unique position in the home field
  }
};

cla_computer_player::cla_computer_player(uint8_t _u8_player_id,
                                         uint8_t _u8_start_position,
                                         uint8_t _u8_computer_quantity,
                                         cla_session *_obj_my_session,
                                         mode _en_mode)
    : cla_player(_u8_player_id, _u8_start_position, _u8_computer_quantity,
                 _obj_my_session) {
  this->en_mode = _en_mode;
}

cla_manual_player::cla_manual_player(uint8_t _u8_player_id,
                                     uint8_t _u8_start_position,
                                     uint8_t _u8_computer_quantity,
                                     cla_session *_obj_my_session)
    : cla_player(_u8_player_id, _u8_start_position, _u8_computer_quantity,
                 _obj_my_session) {}

bool cla_session::Is_Occupied(uint8_t &u8_is_occupied_player_id,
                              uint8_t &u8_is_occupied_token_number,
                              uint8_t _u8_affected_track_position) {
  for (uint8_t i = 0; i < u8_player_quantity; i++) {
    for (uint8_t a = 0; a < 4; a++) {
      if (array_players[i]->Get_Token_Position(a) ==
          _u8_affected_track_position) {
        u8_is_occupied_player_id = i;
        u8_is_occupied_token_number = a;
        return true; // i stands for the player ID, a for the token number
      }
    }
  }
  u8_is_occupied_player_id = 10;
  u8_is_occupied_token_number = 10;
  return false; // 10 stands for no player/token at the given track position
}

bool cla_session::Return_Home(uint8_t _u8_affected_track_position) {
  if (Is_Occupied(u8_is_occupied_player_id, u8_is_occupied_token_number,
                  _u8_affected_track_position)) {
    array_players[u8_is_occupied_player_id]->Set_Token_Position(
        u8_is_occupied_token_number,
        u8_is_occupied_token_number +
            1); // Set_Token_Position sets the token
                // position to the home field (1,2,3,4)
    return true;
  } else {
    return false;
  }
};

uint8_t cla_player::Calculate_Possible_Position(uint8_t _u8_token_number,
                                                uint8_t _u8_dice_value) {
  if ((u8_token_position[_u8_token_number] <= 4) &&
      (_u8_dice_value ==
       6)) { // token is in the home field and would move onto the track
    return u8_start_position;
  } else if (obj_my_session->Is_Occupied(
                 obj_my_session->u8_is_occupied_player_id,
                 obj_my_session->u8_is_occupied_token_number,
                 u8_token_position[_u8_token_number] + _u8_dice_value) ==
                 true &&
             obj_my_session->u8_is_occupied_player_id == u8_player_id) {
    return u8_token_position[_u8_token_number];
  } else if (u8_token_position[_u8_token_number] <= 4 &&
             _u8_dice_value != 6) { // token is in the home field and would
                                    // not move onto the track
    return u8_token_position[_u8_token_number];
  } else if (this->Get_Token_Progress(_u8_token_number) + _u8_dice_value > 39 &&
             this->Get_Token_Progress(_u8_token_number) + _u8_dice_value <
                 44) { // token is on the track and would move into the finish
    return Get_Token_Progress(_u8_token_number) + _u8_dice_value + 5;
  } else if (this->Get_Token_Progress(_u8_token_number) + _u8_dice_value > 39 &&
             this->Get_Token_Progress(_u8_token_number) + _u8_dice_value >
                 43) { // token is on the track and would move out of the
                       // finish
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
  } else if (obj_my_session->Is_Occupied(
                 obj_my_session->u8_is_occupied_player_id,
                 obj_my_session->u8_is_occupied_token_number,
                 u8_possible_position) == false) {
    // possible position is not occupied
    u8_token_position[_u8_token_number] = u8_possible_position;
    return u8_possible_position;
  } else if (obj_my_session->Is_Occupied(
                 obj_my_session->u8_is_occupied_player_id,
                 obj_my_session->u8_is_occupied_token_number,
                 u8_possible_position) == true &&
             obj_my_session->u8_is_occupied_player_id != u8_player_id) {
    // possible position is occupied by another player -> other player gets
    // sent home
    obj_my_session->Return_Home(u8_possible_position);
    u8_token_position[_u8_token_number] = u8_possible_position;
    return u8_possible_position;
  } else {
    return 0; // Error
  }
};

int8_t cla_player::Is_Start_Field_Occupied_By_Own_Token() {
  uint8_t u8_counter = 0;
  for (uint8_t token = 0; token < 4; token++) {
    if (Get_Token_Position(token) <= 4) {
      u8_counter = u8_counter + 1;
    } else {
      u8_counter = u8_counter;
    }
  };
  if (obj_my_session->Is_Occupied(obj_my_session->u8_is_occupied_player_id,
                                  obj_my_session->u8_is_occupied_token_number,
                                  u8_start_position) &&
      u8_player_id == obj_my_session->u8_is_occupied_player_id &&
      u8_counter > 0) {
    return obj_my_session->u8_is_occupied_token_number;
  } else {
    return -1; // no own token at the start position
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
      i8_token_progress = u8_token_position[_u8_token_number] -
                          5; // to compensate the offset on the field
    }
    return i8_token_progress;
  } else {
    return 0;
  }
};

status cla_player::Get_Player_Status() {
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

int8_t cla_computer_player::Auto_Move(uint8_t _u8_dice_value,
                                      bool &_bool_occupied_flag) {
  bool token_moved = false;
  // std::cout << "Computer Level: " << en_mode << std::endl;
  switch (en_mode) {
  case Student:
    // std::cout << "Student" << std::endl;
    for (int n = 0; n < 4; n++) {
      if (Calculate_Possible_Position(n, _u8_dice_value) > 4 &&
          Calculate_Possible_Position(n, _u8_dice_value) !=
              Get_Token_Position(n)) {
        if (obj_my_session->Is_Occupied(
                obj_my_session->u8_is_occupied_player_id,
                obj_my_session->u8_is_occupied_token_number,
                Calculate_Possible_Position(n, _u8_dice_value)) == true) {
          _bool_occupied_flag = true;
          // std::cout << "Student thrown someone" << std::endl;
        }
        Move_Token(n, _u8_dice_value);
        // std::cout << "End of Student move" << std::endl;
        return n; // Token number that was moved
      }
    }
    return -1; // No token could be moved

  case Professor:
    for (int n = 0; n < 4; n++) {
      if (obj_my_session->Is_Occupied(
              obj_my_session->u8_is_occupied_player_id,
              obj_my_session->u8_is_occupied_token_number,
              Calculate_Possible_Position(n, _u8_dice_value)) == true &&
          obj_my_session->u8_is_occupied_player_id != u8_player_id) {
        Move_Token(n, _u8_dice_value);
        token_moved = true;
        _bool_occupied_flag = true;
        // std::cout << "Professor thrown someone" << std::endl;
        return n;
      }
    }

    if (!token_moved) { // If no token could be moved -> student move
      for (int m = 0; m < 4; m++) {
        if (Calculate_Possible_Position(m, _u8_dice_value) > 4 &&
            Calculate_Possible_Position(m, _u8_dice_value) !=
                Get_Token_Position(m)) {
          if (obj_my_session->Is_Occupied(
                  obj_my_session->u8_is_occupied_player_id,
                  obj_my_session->u8_is_occupied_token_number,
                  Calculate_Possible_Position(m, _u8_dice_value)) == true) {
            _bool_occupied_flag = true;
            // std::cout << "Student thrown someone" << std::endl;
          }
          Move_Token(m, _u8_dice_value);
          // std::cout << "Professor did a Student move was done" << std::endl;
          return m;
        }
      }
    }
    return -1; // No token could be moved

  default:
    return -1; // Error
  }
}

uint8_t cla_manual_player::Manual_Move(uint8_t _u8_token_number) { return 0; };

uint8_t cla_session::Get_Player_Quantity() { return u8_player_quantity; };

uint8_t cla_session::Get_Computer_Quantity() { return u8_computer_quantity; };

uint8_t cla_player::Get_Start_Position() { return u8_start_position; };

uint8_t cla_player::Get_Player_ID() { return u8_player_id; };

uint8_t cla_session::Get_Is_Occupied_Player_ID() {
  return u8_is_occupied_player_id;
};

uint8_t cla_session::Get_Is_Occupied_Token_Number() {
  return u8_is_occupied_token_number;
};

int8_t cla_player::Auto_Move(uint8_t _u8_dice_value,
                             bool &_bool_occupied_flag) {
  return 10;
};

mode cla_computer_player::Get_En_Mode() { return en_mode; };

} // namespace LOGIC