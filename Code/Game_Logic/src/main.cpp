#include "logic.hpp"
#include <cstdint>
#include <iostream>


int main() {
  cla_session game(2, 0);
  game.array_players[1]->Set_Token_Position(0, 44); 
  game.array_players[1]->Set_Token_Position(1, 43);
  //std::cout << "Start Position Player 1: " << (int)game.array_players[1]->Get_Start_Position() << std::endl;
  std::cout << "Token 0 progress: " << (int)game.array_players[1]->Get_Token_Progress(0) << std::endl;
  std::cout << "Token 0 could be at Position: " << (int)game.array_players[1]->Calculate_Possible_Position(0, 3) << std::endl;
  game.array_players[1]->Move_Token(0,3);
  std::cout << "Token 0 at Position: " << (int)game.array_players[1]->Get_Token_Position(0) << std::endl;
  game.array_players[1]->Move_Token(1,5);
  std::cout << "Token 1 at Position: " << (int)game.array_players[1]->Get_Token_Position(1) << std::endl;



  /*
  std::cout << (int)game.array_players[0]->Get_Start_Position() << std::endl;
  std::cout << (int)game.array_players[1]->Get_Start_Position() << std::endl;
  std::cout << "###############################################" << std::endl;
  std::cout << (int)game.Get_Player_Quantity() << " Players" << std::endl;
  int8_t i8_game = 1;
  int8_t i8_player = 0;
  while(i8_game) {
    std::cout << "Player " << (int)i8_player << " is on turn" << std::endl;
    for(int w = 0; w < 4; w++) {
      std::cout << "Token " << w << " is on position " << (int)game.array_players[i8_player]->Get_Token_Position(w) << std::endl;
    }
    int dice_value = 0;
    std::cout << "Please roll the dice:" << std::endl;
    std::cin >> dice_value;
    if(dice_value > 6) {
      i8_game = 0;
      break;
    }
    for(int w = 0; w < 4; w++) {
      std::cout << "Token " << w << " could be on position " << (int)game.array_players[i8_player]->Calculate_Possible_Position(w, dice_value) << std::endl;
    }
    int token_number = 0;
    std::cin >> token_number;
    game.array_players[i8_player]->Move_Token(token_number, dice_value);
    std::cout << "Token " << (int)token_number << " is now on position " << (int)game.array_players[i8_player]->Get_Token_Position(token_number) << std::endl;
    if(game.array_players[i8_player]->Get_Player_Progress() == 166){
      i8_game = 0;
    };
    if(i8_player == 0){
    i8_player = 1;
    } else {
      i8_player = 0;
    }
    std::cout << "-----------------------------------------------" << std::endl;
  }
    std::cout << "###############################################" << std::endl;
    std::cout << "Game finished" << std::endl;
  */
}