#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iostream>
#include <logic.hpp>

// Test hard compter player
TEST_CASE("Test en_mode = Professor", "[cla_computer_player]") {
  LOGIC::cla_session game(2, 1, LOGIC::Professor);
  bool bool_is_occupied;

  game.array_players[1]->Set_Token_Position(0, 25);
  game.array_players[1]->Set_Token_Position(1, 35);
  game.array_players[1]->Set_Token_Position(2, 16);
  game.array_players[1]->Set_Token_Position(3, 15);
  game.array_players[0]->Set_Token_Position(2, 36);
  game.array_players[0]->Set_Token_Position(3, 37);
  game.array_players[1]->Auto_Move(1, bool_is_occupied);
  game.array_players[1]->Auto_Move(1, bool_is_occupied);
  game.array_players[1]->Auto_Move(6, bool_is_occupied);
  game.array_players[1]->Auto_Move(6, bool_is_occupied);
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 4);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 3);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 31);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 43);
}

// Test hard compter player in more complex situation
TEST_CASE("Test Professor V2", "[cla_computer_player]") {
  LOGIC::cla_session game(4, 2, LOGIC::Professor);
  bool bool_is_occupied;
  game.array_players[0]->Set_Token_Position(3, 27);
  game.array_players[0]->Set_Token_Position(0, 25);
  game.array_players[2]->Set_Token_Position(3, 45);
  REQUIRE(game.array_players[2]->Auto_Move(6, bool_is_occupied) == 0);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 25);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 1);
  REQUIRE(game.array_players[2]->Auto_Move(6, bool_is_occupied) == 0);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 31);
  game.array_players[1]->Set_Token_Position(2, 37);
  REQUIRE(game.array_players[2]->Auto_Move(6, bool_is_occupied) == 1);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 31);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 25);
  game.array_players[1]->Set_Token_Position(2, 33);
  REQUIRE(game.array_players[2]->Auto_Move(2, bool_is_occupied) == 1);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 31);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 27);
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 4);
}

// Test Auto_Move into finish
TEST_CASE("Test Auto_Move", "[cla_player]") {
  LOGIC::cla_session game(2, 1, LOGIC::Student);
  bool bool_is_occupied;
  game.array_players[0]->Set_Token_Position(0, 10);
  game.array_players[1]->Auto_Move(6, bool_is_occupied);
  game.array_players[1]->Auto_Move(6, bool_is_occupied);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 21);

  game.array_players[1]->Set_Token_Position(0, 11);
  game.array_players[1]->Set_Token_Position(1, 12);
  game.array_players[1]->Set_Token_Position(2, 13);
  game.array_players[1]->Set_Token_Position(3, 14);
  REQUIRE(game.array_players[1]->Auto_Move(4, bool_is_occupied) == 0);
  game.array_players[0]->Set_Token_Position(0, 47);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 45);
  game.array_players[1]->Auto_Move(3, bool_is_occupied);
  game.array_players[1]->Auto_Move(5, bool_is_occupied);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 47);
  game.array_players[1]->Auto_Move(1, bool_is_occupied);

  std::cout << "Position of Token 0 of Player 1: "
            << (int)game.array_players[1]->Get_Token_Position(0) << std::endl;
  std::cout << "Position of Token 1 of Player 1: "
            << (int)game.array_players[1]->Get_Token_Position(1) << std::endl;
  std::cout << "Position of Token 2 of Player 1: "
            << (int)game.array_players[1]->Get_Token_Position(2) << std::endl;
  std::cout << "Position of Token 3 of Player 1: "
            << (int)game.array_players[1]->Get_Token_Position(3) << std::endl;

  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 48);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 47);
  REQUIRE(game.array_players[1]->Get_Token_Position(2) == 13);
  REQUIRE(game.array_players[1]->Get_Token_Position(3) == 45);
}