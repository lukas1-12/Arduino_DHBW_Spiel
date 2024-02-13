#include "logic.hpp"
#include <cstdint>
#include <iostream>

bool bool_is_occupied;

int main() {
  LOGIC::cla_session game(3, 3, LOGIC::Professor);
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

  game.array_players[0]->Set_Token_Position(0, 47);
  std::cout << "Token 0 progress: "
            << (int)game.array_players[0]->Get_Token_Progress(0) << std::endl;
  game.array_players[0]->Set_Token_Position(1, 45);
  std::cout << "Token 1 progress: "
            << (int)game.array_players[0]->Get_Token_Progress(1) << std::endl;
  game.array_players[0]->Set_Token_Position(2, 44);
  std::cout << "Token 2 progress: "
            << (int)game.array_players[0]->Get_Token_Progress(2) << std::endl;
  game.array_players[0]->Set_Token_Position(3, 42);
  std::cout << "Token 3 progress: "
            << (int)game.array_players[0]->Get_Token_Progress(3) << std::endl;
  std::cout << game.array_players[0]->Get_Player_Status() << std::endl;
  std::cout << "Hello World!" << std::endl;
  return 0;
}