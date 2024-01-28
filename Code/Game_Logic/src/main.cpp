#include "logic.hpp"
#include <cstdint>
#include <iostream>


int main() {
  cla_session game(4, 0);
  std::cout <<"Test"<< std::endl;
  std::cout << (int)game.Get_Player_Quantity() << std::endl;
  std::cout << (int)game.array_players[1]->Get_Token_Position(3) << std::endl;
  std::cout << (int)game.array_players[1]->Get_Start_Position() << std::endl;
  std::cout << (int)game.array_players[0]->Get_Player_ID() << std::endl;
  std::cout << (int)game.array_players[2]->Get_Start_Position() << std::endl;
  std::cout << "Hello World!" << std::endl;
  game.array_players[1]->Set_Token_Position(3, 10);
  std::cout << (int)game.Is_Occupied(10).at(0) << std::endl;
  std::cout << (int)game.Is_Occupied(10).at(1) << std::endl;
  return 0;
}