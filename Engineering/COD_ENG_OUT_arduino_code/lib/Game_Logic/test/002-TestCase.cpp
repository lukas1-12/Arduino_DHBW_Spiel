#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iostream>
#include <logic.hpp>

// Test hard compter player
TEST_CASE("Test en_mode = Professor", "[cla_computer_player]") {
  LOGIC::cla_session game(2, 1, LOGIC::Professor);
  bool bool_is_occupied;
  uint8_t u8_old_position;

  game.array_players[1]->Set_Token_Position(0, 25);
  game.array_players[1]->Set_Token_Position(1, 35);
  game.array_players[1]->Set_Token_Position(2, 16);
  game.array_players[1]->Set_Token_Position(3, 15);
  game.array_players[0]->Set_Token_Position(2, 36);
  game.array_players[0]->Set_Token_Position(3, 37);
  game.array_players[1]->Auto_Move(1, bool_is_occupied, u8_old_position);
  game.array_players[1]->Auto_Move(1, bool_is_occupied, u8_old_position);
  game.array_players[1]->Auto_Move(6, bool_is_occupied, u8_old_position);
  game.array_players[1]->Auto_Move(6, bool_is_occupied, u8_old_position);
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 4);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 3);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 31);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 43);
}

// Test hard compter player in more complex situation
TEST_CASE("Test Professor V2", "[cla_computer_player]") {
  LOGIC::cla_session game(4, 2, LOGIC::Professor);
  bool bool_is_occupied;
  uint8_t u8_old_position;

  game.array_players[0]->Set_Token_Position(3, 27);
  game.array_players[0]->Set_Token_Position(0, 25);
  game.array_players[2]->Set_Token_Position(3, 45);
  REQUIRE(game.array_players[2]->Auto_Move(6, bool_is_occupied, u8_old_position) == 0);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 25);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 1);
  REQUIRE(game.array_players[2]->Auto_Move(6, bool_is_occupied, u8_old_position) == 0);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 31);
  game.array_players[1]->Set_Token_Position(2, 37);
  REQUIRE(game.array_players[2]->Auto_Move(6, bool_is_occupied, u8_old_position) == 1);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 31);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 25);
  game.array_players[1]->Set_Token_Position(2, 33);
  REQUIRE(game.array_players[2]->Auto_Move(2, bool_is_occupied, u8_old_position) == 1);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 31);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 27);
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 4);
}

// Test Auto_Move into finish
TEST_CASE("Test Auto_Move", "[cla_player]") {
  LOGIC::cla_session game(2, 1, LOGIC::Student);
  bool bool_is_occupied;
    uint8_t u8_old_position;

  game.array_players[0]->Set_Token_Position(0, 10);
  game.array_players[1]->Auto_Move(6, bool_is_occupied, u8_old_position);
  game.array_players[1]->Auto_Move(6, bool_is_occupied, u8_old_position);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 21);

  game.array_players[1]->Set_Token_Position(0, 11);
  game.array_players[1]->Set_Token_Position(1, 12);
  game.array_players[1]->Set_Token_Position(2, 13);
  game.array_players[1]->Set_Token_Position(3, 14);
  REQUIRE(game.array_players[1]->Auto_Move(4, bool_is_occupied, u8_old_position) == 0);
  game.array_players[0]->Set_Token_Position(0, 48);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 45);
  game.array_players[1]->Auto_Move(3, bool_is_occupied, u8_old_position);
  game.array_players[1]->Auto_Move(5, bool_is_occupied, u8_old_position);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 47);
  game.array_players[1]->Auto_Move(1, bool_is_occupied, u8_old_position);

  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 48);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 47);
  REQUIRE(game.array_players[1]->Get_Token_Position(2) == 13);
  REQUIRE(game.array_players[1]->Get_Token_Position(3) == 45);
}

// One manual player is with 3 tokens in Finish, computer moves 4 token to
// finish
TEST_CASE("Test Auto_Move into Finish while manual player is in finish",
          "[cla_player]") {
  LOGIC::cla_session game(2, 1, LOGIC::Student);
  bool bool_is_occupied;
  uint8_t u8_old_position;

  game.array_players[0]->Set_Token_Position(0, 48);
  game.array_players[0]->Set_Token_Position(1, 47);
  game.array_players[0]->Set_Token_Position(2, 46);
  game.array_players[0]->Set_Token_Position(3, 43);
  game.array_players[1]->Set_Token_Position(0, 10);
  game.array_players[1]->Set_Token_Position(1, 11);
  game.array_players[1]->Set_Token_Position(2, 12);
  game.array_players[1]->Set_Token_Position(3, 13);
  game.array_players[1]->Auto_Move(5, bool_is_occupied, u8_old_position);
  game.array_players[1]->Auto_Move(5, bool_is_occupied, u8_old_position);
  game.array_players[1]->Auto_Move(5, bool_is_occupied, u8_old_position);
  game.array_players[1]->Auto_Move(5, bool_is_occupied, u8_old_position);

  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 45);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 46);
  REQUIRE(game.array_players[1]->Get_Token_Position(2) == 47);
  REQUIRE(game.array_players[1]->Get_Token_Position(3) == 48);

  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 48);
  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 47);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 46);
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 43);
}

// Test if player throws himself out of the game after start and on the field
TEST_CASE("Test if player throws himself", "[cla_player]") {
  LOGIC::cla_session game(2, 1, LOGIC::Student);
  bool bool_is_occupied;
  uint8_t u8_old_position;

  game.array_players[0]->Move_Token(0, 6);
  game.array_players[0]->Move_Token(1, 6);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 5);
  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 2);
  game.array_players[0]->Move_Token(0, 4);
  game.array_players[0]->Move_Token(1, 6);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 9);
  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 5);
  game.array_players[0]->Move_Token(1, 4);
  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 5);

  game.array_players[1]->Auto_Move(6, bool_is_occupied, u8_old_position);
  game.array_players[1]->Auto_Move(6, bool_is_occupied, u8_old_position);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 21);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 2);
  game.array_players[1]->Auto_Move(6, bool_is_occupied, u8_old_position);
  game.array_players[1]->Auto_Move(6, bool_is_occupied, u8_old_position);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 21);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 15);
  game.array_players[1]->Auto_Move(4, bool_is_occupied, u8_old_position);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 19);
}

// Test if player throws himself out of the game in and before finish
TEST_CASE("Test if player throws himself in and before finish",
          "[cla_player]") {
  LOGIC::cla_session game(2, 1, LOGIC::Student);
  bool bool_is_occupied;
  uint8_t u8_old_position;

  game.array_players[0]->Set_Token_Position(0, 46);
  game.array_players[0]->Set_Token_Position(1, 44);
  game.array_players[0]->Set_Token_Position(2, 43);
  game.array_players[0]->Set_Token_Position(3, 45);
  game.array_players[0]->Move_Token(2, 4);
  game.array_players[0]->Move_Token(1, 3);
  game.array_players[0]->Move_Token(0, 2);
  game.array_players[0]->Move_Token(3, 3);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 48);
  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 44);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 47);
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 45);

  game.array_players[1]->Set_Token_Position(0, 46);
  game.array_players[1]->Set_Token_Position(1, 14);
  game.array_players[1]->Set_Token_Position(2, 13);
  game.array_players[1]->Set_Token_Position(3, 45);

  game.array_players[1]->Auto_Move(3, bool_is_occupied, u8_old_position);

  game.array_players[1]->Auto_Move(6, bool_is_occupied, u8_old_position);

  game.array_players[1]->Auto_Move(4, bool_is_occupied, u8_old_position);

  game.array_players[1]->Auto_Move(2, bool_is_occupied, u8_old_position);

  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 48);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 47);
  REQUIRE(game.array_players[1]->Get_Token_Position(2) == 13);
  REQUIRE(game.array_players[1]->Get_Token_Position(3) == 45);
}

//Test professor mode V2
TEST_CASE("Big test for professor mode", "[cla_computer_player]") {
  LOGIC::cla_session game(4, 2, LOGIC::Professor);
  bool bool_is_occupied;
  uint8_t u8_old_position;

  game.array_players[0]->Set_Token_Position(3, 29);
  game.array_players[0]->Set_Token_Position(0, 28);
  game.array_players[2]->Auto_Move(6, bool_is_occupied, u8_old_position);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 25);
  game.array_players[2]->Auto_Move(2, bool_is_occupied, u8_old_position);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 27);
  game.array_players[2]->Auto_Move(6, bool_is_occupied, u8_old_position);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 25);
  game.array_players[2]->Auto_Move(3, bool_is_occupied, u8_old_position);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 28);
  std::cout << (int)game.array_players[2]->Auto_Move(5, bool_is_occupied, u8_old_position) << std::endl;
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 32);
}