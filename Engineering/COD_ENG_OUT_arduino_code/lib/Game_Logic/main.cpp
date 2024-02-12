#include "logic.hpp"
#include <cstdint>
#include <iostream>
#include <random>
#include <array>


int main() {
  LOGIC::cla_session game(4, 1, LOGIC::Student);
  std::cout << "\033[31m" << (int)game.Get_Player_Quantity() << " Players \033[0m" << std::endl;
  std::cout << "\033[31m" << (int)game.Get_Computer_Quantity() << " Computer Players \033[0m" << std::endl;
  std::cout << "###############################################" << std::endl;
  std::cout << "Start Position of Player 0 is: " << (int)game.array_players[0]->Get_Start_Position() << std::endl;
  std::cout << "Start Position of Player 1 is: " << (int)game.array_players[1]->Get_Start_Position() << std::endl;
  std::cout << "Start Position of Player 2 is: " << (int)game.array_players[2]->Get_Start_Position() << std::endl;
  std::cout << "player 0 is a computer player: " << game.array_players[0]->Is_Computer() << std::endl;
  std::cout << "player 1 is a computer player: " << game.array_players[1]->Is_Computer() << std::endl;
  std::cout << "player 2 is a computer player: " << game.array_players[2]->Is_Computer() << std::endl;
  std::cout << "player 3 is a computer player: " << game.array_players[3]->Is_Computer() << std::endl;
  std::cout << "###############################################" << std::endl;
  //std::cout << "Start Position of Player 3 is: " << (int)game.array_players[3]->Get_Start_Position() << std::endl;
  /*
  std::cout << "###############################################" << std::endl;
  std::cout << "\033[31m" << (int)game.Get_Player_Quantity() << " Players \033[0m" << std::endl;
  game.array_players[0]->Set_Token_Position(0, 45);
  game.array_players[0]->Set_Token_Position(1, 25);
  game.array_players[1]->Set_Token_Position(2, 29);
  std::cout << "Token 0 of player 0 is at: " << (int)game.array_players[0]->Get_Token_Position(0) << std::endl;
  std::cout << "Token 1 of player 0 is at: " << (int)game.array_players[0]->Get_Token_Position(1) << std::endl;
  std::cout << "Token 2 of player 1 is at: " << (int)game.array_players[1]->Get_Token_Position(2) << std::endl;

  std::cout << "Possible position of token 1 is: " << (int)game.array_players[0]->Calculate_Possible_Position(1, 4) << std::endl;
  game.array_players[0]->Move_Token(1, 4);

  std::cout << "###############################################" << std::endl;
  std::cout << "Token 0 of player 0 is at: " << (int)game.array_players[0]->Get_Token_Position(0) << std::endl;
  std::cout << "Token 1 of player 0 is at: " << (int)game.array_players[0]->Get_Token_Position(1) << std::endl;
  std::cout << "Token 2 of player 1 is at: " << (int)game.array_players[1]->Get_Token_Position(2) << std::endl;

  std::cout << "###############################################" << std::endl;
  game.array_players[0]->Set_Token_Position(2, 44);
  std::cout << "Token 2 of player 0 is at: " << (int)game.array_players[0]->Get_Token_Position(2) << std::endl;
  game.array_players[0]->Move_Token(2, 1);
  std::cout << "Token 0 of player 0 is at: " << (int)game.array_players[0]->Get_Token_Position(0) << std::endl;
  std::cout << "Token 2 of player 0 is at: " << (int)game.array_players[0]->Get_Token_Position(2) << std::endl;
  */


  /*
  game.array_players[0]->Set_Token_Position(0, 47);
  std::cout << "Token 0 progress: " << (int)game.array_players[0]->Get_Token_Progress(0) << std::endl;
  game.array_players[0]->Set_Token_Position(1, 45); 
  std::cout << "Token 1 progress: " << (int)game.array_players[0]->Get_Token_Progress(1) << std::endl;
  game.array_players[0]->Set_Token_Position(2, 44);
  std::cout << "Token 2 progress: " << (int)game.array_players[0]->Get_Token_Progress(2) << std::endl;
  game.array_players[0]->Set_Token_Position(3, 42);
  std::cout << "Token 3 progress: " << (int)game.array_players[0]->Get_Token_Progress(3) << std::endl;
  std::cout << game.array_players[0]->Get_Status() << std::endl;
  */

  /*
  for(int w = 0; w < 4; w++) {
    std::cout << "Token " << w << " could be on position " << (int)game.array_players[0]->Calculate_Possible_Position(w, 3) << std::endl;
  }
  game.array_players[0]->Move_Token(0,3);
  std::cout << "Token 0 at Position: " << (int)game.array_players[0]->Get_Token_Position(0) << std::endl;
  game.array_players[0]->Move_Token(1,3);
  std::cout << "Token 1 at Position: " << (int)game.array_players[0]->Get_Token_Position(1) << std::endl;
  game.array_players[0]->Move_Token(2,3);
  std::cout << "Token 2 at Position: " << (int)game.array_players[0]->Get_Token_Position(2) << std::endl;
  game.array_players[0]->Move_Token(3,3);
  std::cout << "Token 3 at Position: " << (int)game.array_players[0]->Get_Token_Position(3) << std::endl;
  */

  /*
  game.array_players[1]->Set_Token_Position(0, 44); 
  game.array_players[1]->Set_Token_Position(1, 43);
  //std::cout << "Start Position Player 1: " << (int)game.array_players[1]->Get_Start_Position() << std::endl;
  std::cout << "Token 0 progress: " << (int)game.array_players[1]->Get_Token_Progress(0) << std::endl;
  std::cout << "Token 0 could be at Position: " << (int)game.array_players[1]->Calculate_Possible_Position(0, 3) << std::endl;
  game.array_players[1]->Move_Token(0,3);
  std::cout << "Token 0 at Position: " << (int)game.array_players[1]->Get_Token_Position(0) << std::endl;
  game.array_players[1]->Move_Token(1,5);
  std::cout << "Token 1 at Position: " << (int)game.array_players[1]->Get_Token_Position(1) << std::endl;
  */

  /*
  game.array_players[1]->Set_Token_Position(0, 14);
  std::cout << "Token 0 progress: " << (int)game.array_players[1]->Get_Token_Progress(0) << std::endl;
  game.array_players[1]->Set_Token_Position(1, 13); 
  std::cout << "Token 1 progress: " << (int)game.array_players[1]->Get_Token_Progress(1) << std::endl;
  game.array_players[1]->Set_Token_Position(2, 12);
  std::cout << "Token 2 progress: " << (int)game.array_players[1]->Get_Token_Progress(2) << std::endl;
  game.array_players[1]->Set_Token_Position(3, 11);
  std::cout << "Token 3 progress: " << (int)game.array_players[1]->Get_Token_Progress(3) << std::endl;
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

  /*
  // Let 2 computers play against each other
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
    game.array_players[i8_player]->array_computer_players[i8_game]->Auto_Move(dice_value);

    for(int w = 0; w < 4; w++) {
      std::cout << "Token " << w << " is on position " << (int)game.array_players[i8_player]->Get_Token_Position(w) << std::endl;
    }

    counter = counter + 1;
    
    if(game.array_players[i8_player]->Get_Player_Progress() == 166){
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
    


/*
  game.array_players[0]->Set_Token_Position(0, 45);
  game.array_players[0]->Set_Token_Position(1, 25);
    std::cout << "Possible position of token 1 is: " << (int)game.array_players[0]->Calculate_Possible_Position(1, 4) << std::endl;
  game.array_players[0]->array_computer_players[0]->Auto_Move(4);
  std::cout << "Token 0 is on position " << (int)game.array_players[0]->Get_Token_Position(0) << std::endl;
  std::cout << "Token 1 is on position " << (int)game.array_players[0]->Get_Token_Position(1) << std::endl;
  std::cout << "Token 2 is on position " << (int)game.array_players[0]->Get_Token_Position(2) << std::endl;
  std::cout << "Token 3 is on position " << (int)game.array_players[0]->Get_Token_Position(3) << std::endl;
  */


}