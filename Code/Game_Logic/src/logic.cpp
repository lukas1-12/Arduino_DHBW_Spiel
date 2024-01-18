#include "logic.hpp"
#include <cstdint>

typedef enum {
  Start=0,
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

uint8_t cla_session::Is_Occupied(uint8_t _u8_affected_track_position){
  for(int i = 0; i < u8_player_quantity; i++){
    
  }
};

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

status cla_player::Get_Status(uint8_t _u8_token_number){
  this->cla_player::Get_Token_Position();
};

uint8_t cla_player::Get_Player_Progress(){
  uint8_t _u8_overall_progress = 0;
  for(uint8_t u8_token_number = 0; u8_token_number < 4; u8_token_number++){
    _u8_overall_progress += this->cla_player::Get_Token_Progress(u8_token_number);
  }
  return _u8_overall_progress;
};

bool Is_Computer(){
  return false;
};

uint8_t cla_computer_player::Auto_Move(uint8_t _u8_token_number){
  
};

uint8_t cla_manual_player::Manual_Move(uint8_t _u8_token_number){
  
};