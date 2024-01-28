#include "logic.hpp"
#include <cstdint>
#include <iostream>


int main() {
  cla_session game(4, 0);
  std::cout << "###############################################" << std::endl;
  game.array_players[1]->Set_Token_Position(3, 10);
  //std::cout << game.Return_Home(10) << std::endl;
  game.array_players[1]->Move_Token(3, 5);
  std::cout << (int)game.array_players[1]->Get_Token_Position(3) << std::endl;
  game.array_players[0]->Set_Token_Position(0, 10);
  std::cout << (int)game.Is_Occupied(10).at(0) << std::endl;
  std::cout << (int)game.Is_Occupied(10).at(1) << std::endl;
  std::cout << "###############################################" << std::endl;
  game.array_players[3]->Set_Token_Position(1, 30);
  std::cout << (int)game.array_players[3]->Get_Token_Position(1) << std::endl;
  std::cout << (int)game.array_players[1]->Get_Token_Position(3) << std::endl;
  std::cout << "###############################################" << std::endl;
  std::cout << (int)game.array_players[3]->Get_Token_Progress(1) << std::endl;
  std::cout << (int)game.array_players[3]->Calculate_Possible_Position(1, 5) << std::endl;

  return 0;
}