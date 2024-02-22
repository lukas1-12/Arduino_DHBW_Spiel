/**
 * @file 003-TestCase_Session_and_Player.cpp
 * @brief Test cases for various situations during a game
 *
 * This file contains multiple game situations for testing the behavior of the
 * game logic. It covers various situations in which the players have to make
 * decisions and move tokens with different start conditions.
 */

#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iostream>
#include <logic.hpp>

TEST_CASE("Test game constructer", "[cla_session]") {
  LOGIC::cla_session game(4, 1, LOGIC::Student);
  REQUIRE(game.Get_Player_Quantity() == 4);
  REQUIRE(game.Get_Computer_Quantity() == 1);
}

TEST_CASE("Test Set_Token", "[cla_player]") {
  LOGIC::cla_session game(4, 2, LOGIC::Student);
  game.array_players[0]->Set_Token_Position(0, 45);
  game.array_players[1]->Set_Token_Position(1, 25);
  game.array_players[2]->Set_Token_Position(2, 29);
  game.array_players[3]->Set_Token_Position(3, 30);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 45);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 25);
  REQUIRE(game.array_players[2]->Get_Token_Position(2) == 29);
  REQUIRE(game.array_players[3]->Get_Token_Position(3) == 30);
}

TEST_CASE("Test Move_Token", "[cla_player]") {
  LOGIC::cla_session game(4, 0, LOGIC::Student);
  game.array_players[0]->Set_Token_Position(0, 45);
  game.array_players[0]->Set_Token_Position(1, 25);
  game.array_players[0]->Set_Token_Position(2, 29);
  game.array_players[0]->Set_Token_Position(3, 30);
  game.array_players[0]->Move_Token(0, 4);
  game.array_players[0]->Move_Token(1, 3);
  game.array_players[0]->Move_Token(2, 2);
  game.array_players[0]->Move_Token(3, 1);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 45);
  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 28);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 31);
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 30);
}

TEST_CASE("Test Is_Startfield_occupied...", "[cla_player]") {
  LOGIC::cla_session game(4, 0, LOGIC::Student);
  game.array_players[0]->Set_Token_Position(0, 5);
  game.array_players[1]->Set_Token_Position(1, 15);
  game.array_players[2]->Set_Token_Position(2, 25);
  game.array_players[3]->Set_Token_Position(3, 35);
  REQUIRE(game.array_players[0]->Is_Start_Field_Occupied_By_Own_Token() == 0);
  REQUIRE(game.array_players[1]->Is_Start_Field_Occupied_By_Own_Token() == 1);
  REQUIRE(game.array_players[2]->Is_Start_Field_Occupied_By_Own_Token() == 2);
  REQUIRE(game.array_players[3]->Is_Start_Field_Occupied_By_Own_Token() == 3);
  game.array_players[0]->Set_Token_Position(3, 8);
  game.array_players[0]->Set_Token_Position(1, 6);
  game.array_players[0]->Set_Token_Position(2, 7);
  REQUIRE(game.array_players[0]->Is_Start_Field_Occupied_By_Own_Token() == -1);
}

// Test all players move into finish:
TEST_CASE("Test parallel Move into Finish", "[cla_player]") {
  LOGIC::cla_session game(4, 0, LOGIC::Student);

  // Player 0
  game.array_players[0]->Set_Token_Position(0, 40);
  game.array_players[0]->Set_Token_Position(1, 41);
  game.array_players[0]->Set_Token_Position(2, 42);
  game.array_players[0]->Set_Token_Position(3, 43);
  game.array_players[0]->Move_Token(0, 5);
  game.array_players[0]->Move_Token(1, 5);
  game.array_players[0]->Move_Token(2, 5);
  game.array_players[0]->Move_Token(3, 5);

  // Player 1
  game.array_players[1]->Set_Token_Position(0, 10);
  game.array_players[1]->Set_Token_Position(1, 11);
  game.array_players[1]->Set_Token_Position(2, 12);
  game.array_players[1]->Set_Token_Position(3, 13);
  game.array_players[1]->Move_Token(0, 6);
  game.array_players[1]->Move_Token(1, 6);
  game.array_players[1]->Move_Token(2, 3);
  game.array_players[1]->Move_Token(3, 5);

  // Player 2
  game.array_players[2]->Set_Token_Position(0, 24);
  game.array_players[2]->Set_Token_Position(1, 21);
  game.array_players[2]->Set_Token_Position(2, 22);
  game.array_players[2]->Set_Token_Position(3, 23);
  game.array_players[2]->Move_Token(0, 4);
  game.array_players[2]->Move_Token(1, 6);
  game.array_players[2]->Move_Token(2, 4);
  game.array_players[2]->Move_Token(3, 2);

  // Player 3
  game.array_players[3]->Set_Token_Position(0, 33);
  game.array_players[3]->Set_Token_Position(1, 31);
  game.array_players[3]->Set_Token_Position(2, 32);
  game.array_players[3]->Set_Token_Position(3, 34);
  game.array_players[3]->Move_Token(0, 2);
  game.array_players[3]->Move_Token(1, 6);
  game.array_players[3]->Move_Token(2, 6);
  game.array_players[3]->Move_Token(3, 2);

  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 45);
  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 46);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 47);
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 48);

  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 46);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 47);
  REQUIRE(game.array_players[1]->Get_Token_Position(2) == 45);
  REQUIRE(game.array_players[1]->Get_Token_Position(3) == 48);

  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 48);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 47);
  REQUIRE(game.array_players[2]->Get_Token_Position(2) == 46);
  REQUIRE(game.array_players[2]->Get_Token_Position(3) == 45);

  REQUIRE(game.array_players[3]->Get_Token_Position(0) == 45);
  REQUIRE(game.array_players[3]->Get_Token_Position(1) == 47);
  REQUIRE(game.array_players[3]->Get_Token_Position(2) == 48);
  REQUIRE(game.array_players[3]->Get_Token_Position(3) == 46);
}

// Test Get_Player_Progress
TEST_CASE("Test Get_Player_Progress V1", "[cla_player]") {
  LOGIC::cla_session game(4, 4, LOGIC::Student);
  game.array_players[0]->Set_Token_Position(0, 45);
  game.array_players[0]->Set_Token_Position(1, 43);
  game.array_players[0]->Set_Token_Position(2, 46);
  game.array_players[0]->Set_Token_Position(3, 47);
  REQUIRE(game.array_players[0]->Get_Player_Progress() == 27);

  game.array_players[1]->Set_Token_Position(0, 1);
  game.array_players[1]->Set_Token_Position(1, 2);
  game.array_players[1]->Set_Token_Position(2, 3);
  game.array_players[1]->Set_Token_Position(3, 4);
  REQUIRE(game.array_players[1]->Get_Player_Progress() == 1);

  game.array_players[2]->Set_Token_Position(0, 45);
  game.array_players[2]->Set_Token_Position(1, 24);
  game.array_players[2]->Set_Token_Position(2, 46);
  game.array_players[2]->Set_Token_Position(3, 47);
  REQUIRE(game.array_players[2]->Get_Player_Progress() == 27);

  game.array_players[3]->Set_Token_Position(0, 1);
  game.array_players[3]->Set_Token_Position(1, 2);
  game.array_players[3]->Set_Token_Position(2, 3);
  game.array_players[3]->Set_Token_Position(3, 4);
  REQUIRE(game.array_players[3]->Get_Player_Progress() == 1);

  game.array_players[0]->Set_Token_Position(0, 20);
  game.array_players[0]->Set_Token_Position(1, 21);
  game.array_players[0]->Set_Token_Position(2, 22);
  game.array_players[0]->Set_Token_Position(3, 23);
  REQUIRE(game.array_players[0]->Get_Player_Progress() == 12);

  game.array_players[0]->Set_Token_Position(0, 45);
  game.array_players[0]->Set_Token_Position(1, 46);
  game.array_players[0]->Set_Token_Position(2, 47);
  game.array_players[0]->Set_Token_Position(3, 48);
  REQUIRE(game.array_players[0]->Get_Player_Progress() == 28);
}