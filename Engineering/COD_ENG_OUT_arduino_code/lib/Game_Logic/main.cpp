#ifndef __AVR__

#include "logic.hpp"
#include <cstdint>
#include <iostream>
#include <random>

bool bool_is_occupied;
uint8_t u8_old_position;

int main() {
  LOGIC::cla_session game(3, 3, LOGIC::Professor);
  /*
  std::cout << "\033[31m" << (int)game.Get_Player_Quantity()
            << " Players \033[0m" << std::endl;
  std::cout << "\033[31m" << (int)game.Get_Computer_Quantity()
            << " Computer Players \033[0m" << std::endl;
  std::cout << "###############################################" << std::endl;
  std::cout << "Start Position of Player 0 is: "
            << (int)game.array_players[0]->Get_Start_Position() << std::endl;
  std::cout << "Start Position of Player 1 is: "
            << (int)game.array_players[1]->Get_Start_Position() << std::endl;
  std::cout << "Start Position of Player 2 is: "
            << (int)game.array_players[2]->Get_Start_Position() << std::endl;
  std::cout << "player 0 is a computer player: "
            << game.array_players[0]->Is_Computer() << std::endl;
  std::cout << "player 1 is a computer player: "
            << game.array_players[1]->Is_Computer() << std::endl;
  std::cout << "player 2 is a computer player: "
            << game.array_players[2]->Is_Computer() << std::endl;
  // std::cout << "player 3 is a computer player: " <<
  // game.array_players[3]->Is_Computer() << std::endl;
  std::cout << "###############################################" << std::endl;

  game.array_players[0]->Set_Token_Position(0, 25);
  game.array_players[0]->Set_Token_Position(1, 26);
  game.array_players[1]->Set_Token_Position(2, 30);
  std::cout << "Token 0 of player 0 could be at: "
            << (int)game.array_players[0]->Calculate_Possible_Position(0, 4)
            << std::endl;
  std::cout << "Token 1 of player 0 could be at: "
            << (int)game.array_players[0]->Calculate_Possible_Position(1, 4)
            << std::endl;
  game.array_players[0]->Auto_Move(4, bool_is_occupied);
  game.array_players[0]->Auto_Move(4, bool_is_occupied);
  std::cout << "Token 0 of player 0 is at: "
            << (int)game.array_players[0]->Get_Token_Position(0) << std::endl;
  std::cout << "Token 1 of player 0 is at: "
            << (int)game.array_players[0]->Get_Token_Position(1) << std::endl;
  std::cout << "Token 2 of player 1 is at: "
            << (int)game.array_players[1]->Get_Token_Position(2) << std::endl;


  game.array_players[0]->Set_Token_Position(0, 20);
  game.array_players[0]->Set_Token_Position(1, 21);
  game.array_players[0]->Set_Token_Position(2, 22);
  game.array_players[0]->Set_Token_Position(3, 23);
  std::cout << "Player Progress: " << (int)game.array_players[0]->Get_Player_Progress() << std::endl;

  game.array_players[0]->Set_Token_Position(0, 40);
  game.array_players[0]->Set_Token_Position(1, 41);
  game.array_players[0]->Set_Token_Position(2, 42);
  game.array_players[0]->Set_Token_Position(3, 43);

  std::cout << "Possible Position of Token 0: " << (int)game.array_players[0]->Calculate_Possible_Position(0, 5) << std::endl;
  std::cout << "Possible Position of Token 1: " << (int)game.array_players[0]->Calculate_Possible_Position(1, 5) << std::endl;
  std::cout << "Possible Position of Token 2: " << (int)game.array_players[0]->Calculate_Possible_Position(2, 5) << std::endl;
  std::cout << "Possible Position of Token 3: " << (int)game.array_players[0]->Calculate_Possible_Position(3, 5) << std::endl;
  */

 
  // Let 3 computers play against each other
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> distribution(1, 6);

  std::cout << "###############################################" << std::endl;
  std::cout << "\033[31m" << (int)game.Get_Player_Quantity() << " Players \033[0m" << std::endl;
  int8_t i8_game = 1;
  int8_t i8_player = 0;
  int counter = 0;
  while(i8_game) {
    std::cout << "\033[31m" << "Player " << (int)i8_player << " is on turn \033[0m" << std::endl;
    for(int w = 0; w < 4; w++) {
      std::cout << "Token " << w << " is on position " << (int)game.array_players[i8_player]->Get_Token_Position(w) << std::endl;
    }
    int dice_value = 0;
    std::cout << "Please roll the dice:" << std::endl;
    dice_value = distribution(gen);
    std::cout << "Dice value: " << (int)dice_value << std::endl;

    if(dice_value > 6) {
      i8_game = 0;
      break;
    }
    game.array_players[i8_player]->Auto_Move(dice_value, bool_is_occupied, u8_old_position);

    for(int w = 0; w < 4; w++) {
      std::cout << "Token " << w << " is on position " << (int)game.array_players[i8_player]->Get_Token_Position(w) << std::endl;
    }

    counter = counter + 1;
    
    if(game.array_players[i8_player]->Get_Player_Progress() == 28){
      std::cout << "Player " << (int)i8_player << " won the game" << std::endl;
      i8_game = 0;
    };
    if(i8_player == 2){
    i8_player = 0;
    } else {
      i8_player = i8_player + 1;
    }
    std::cout << "-----------------------------------------------" << std::endl;
  }
    std::cout << "###############################################" << std::endl;
    std::cout << "Game finished with " << counter << " player moves" << std::endl;

  return 0;
}

#endif