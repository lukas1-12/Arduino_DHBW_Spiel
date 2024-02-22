/**
 * @file 001-TestCase_Requirements.cpp
 * @brief This file contains the test cases for the requirements of the game
 * logic.
 *
 * This file contains multiple game situations and checks if the game logic
 * behaves as expected and as defined in the requirements.
 */

#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iostream>
#include <logic.hpp>

// Requirement 44: "Landet ein Benutzer mit seiner Spielfigur auf einem bereits
// von einem anderen Benutzer besetzten Feld, so schmeißt er diesen automatisch"

TEST_CASE("Test Move_Token_Kick", "[cla_player]") {
  LOGIC::cla_session game(4, 0, LOGIC::Student);
  game.array_players[0]->Set_Token_Position(2, 29);
  game.array_players[1]->Set_Token_Position(1, 25);
  game.array_players[0]->Move_Token(2, 1);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 30);
  game.array_players[1]->Move_Token(1, 5);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 3);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 30);
}

// Requirement 46: "Zu Beginn befinden sich alle Figuren in den Häusern"
TEST_CASE("Test Home_Position", "[cla_player]") {
  LOGIC::cla_session game(4, 0, LOGIC::Student);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 1);
  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 2);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 3);
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 4);

  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 1);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 2);
  REQUIRE(game.array_players[1]->Get_Token_Position(2) == 3);
  REQUIRE(game.array_players[1]->Get_Token_Position(3) == 4);

  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 1);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 2);
  REQUIRE(game.array_players[2]->Get_Token_Position(2) == 3);
  REQUIRE(game.array_players[2]->Get_Token_Position(3) == 4);

  REQUIRE(game.array_players[3]->Get_Token_Position(0) == 1);
  REQUIRE(game.array_players[3]->Get_Token_Position(1) == 2);
  REQUIRE(game.array_players[3]->Get_Token_Position(2) == 3);
  REQUIRE(game.array_players[3]->Get_Token_Position(3) == 4);
}

// Test Get_Player_Status
TEST_CASE("Test Get_Player_Status", "[cla_player]") {
  LOGIC::cla_session game(4, 2, LOGIC::Student);
  game.array_players[0]->Set_Token_Position(0, 45);
  game.array_players[0]->Set_Token_Position(1, 48);
  game.array_players[0]->Set_Token_Position(2, 46);
  game.array_players[0]->Set_Token_Position(3, 47);
  REQUIRE(game.array_players[0]->Get_Player_Status() == LOGIC::Finished);

  game.array_players[1]->Set_Token_Position(0, 1);
  game.array_players[1]->Set_Token_Position(1, 2);
  game.array_players[1]->Set_Token_Position(2, 3);
  game.array_players[1]->Set_Token_Position(3, 4);
  REQUIRE(game.array_players[1]->Get_Player_Status() == LOGIC::Start);

  game.array_players[2]->Set_Token_Position(0, 45);
  game.array_players[2]->Set_Token_Position(1, 24);
  game.array_players[2]->Set_Token_Position(2, 46);
  game.array_players[2]->Set_Token_Position(3, 47);
  REQUIRE(game.array_players[2]->Get_Player_Status() == LOGIC::Track_Finished);

  game.array_players[3]->Set_Token_Position(0, 35);
  game.array_players[3]->Set_Token_Position(1, 36);
  game.array_players[3]->Set_Token_Position(2, 37);
  game.array_players[3]->Set_Token_Position(3, 38);
  REQUIRE(game.array_players[3]->Get_Player_Status() == LOGIC::Track);
  REQUIRE(game.array_players[3]->Get_Player_Status() != LOGIC::Start_Track);
  REQUIRE(game.array_players[3]->Get_Player_Status() != LOGIC::Start_Finished);
  REQUIRE(game.array_players[3]->Get_Player_Status() !=
          LOGIC::Start_Track_Finished);
}

// Test occuppied flag in Auto Move
TEST_CASE("Test occupied flag in Auto_Move", "[cla_player]") {
  bool bool_occupied = false;
  uint8_t u8_old_position = 0;
  LOGIC::cla_session game(2, 1, LOGIC::Student);
  game.array_players[0]->Move_Token(0, 6);
  game.array_players[0]->Move_Token(0, 6);
  game.array_players[0]->Move_Token(0, 5);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 16);
  game.array_players[1]->Auto_Move(6, bool_occupied, u8_old_position);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 15);
  REQUIRE(bool_occupied == false);
  game.array_players[1]->Auto_Move(1, bool_occupied, u8_old_position);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 16);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 1);
  REQUIRE(bool_occupied == true);
}

// Test occuppied flag in Auto Move with start position
TEST_CASE("Test occupied flag in Auto_Move with start position",
          "[cla_player]") {
  bool bool_occupied = false;
  uint8_t u8_old_position = 0;
  LOGIC::cla_session game(2, 1, LOGIC::Student);
  game.array_players[0]->Move_Token(0, 6);
  game.array_players[0]->Move_Token(0, 6);
  game.array_players[0]->Move_Token(0, 4);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 15);
  game.array_players[1]->Auto_Move(6, bool_occupied, u8_old_position);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 15);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 1);
  REQUIRE(bool_occupied == true);
  game.array_players[1]->Auto_Move(1, bool_occupied, u8_old_position);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 16);
  REQUIRE(bool_occupied == false);
}

// Requirement  52: "Erreicht eine Spielfigur das Endfeld, so begibt sie sich
// mit den übrigen, gewürfelten Felder ins Ziel"
TEST_CASE("Test Move into Finish", "[cla_player]") {
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
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 45);
  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 46);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 47);
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 48);

  // Player 1
  game.array_players[1]->Set_Token_Position(0, 10);
  game.array_players[1]->Set_Token_Position(1, 11);
  game.array_players[1]->Set_Token_Position(2, 12);
  game.array_players[1]->Set_Token_Position(3, 13);
  game.array_players[1]->Move_Token(0, 6);
  game.array_players[1]->Move_Token(1, 6);
  game.array_players[1]->Move_Token(2, 3);
  game.array_players[1]->Move_Token(3, 5);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 46);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 47);
  REQUIRE(game.array_players[1]->Get_Token_Position(2) == 45);
  REQUIRE(game.array_players[1]->Get_Token_Position(3) == 48);

  // Player 2
  game.array_players[2]->Set_Token_Position(0, 24);
  game.array_players[2]->Set_Token_Position(1, 21);
  game.array_players[2]->Set_Token_Position(2, 22);
  game.array_players[2]->Set_Token_Position(3, 23);
  game.array_players[2]->Move_Token(0, 4);
  game.array_players[2]->Move_Token(1, 6);
  game.array_players[2]->Move_Token(2, 4);
  game.array_players[2]->Move_Token(3, 2);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 48);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 47);
  REQUIRE(game.array_players[2]->Get_Token_Position(2) == 46);
  REQUIRE(game.array_players[2]->Get_Token_Position(3) == 45);

  // Player 3
  game.array_players[3]->Set_Token_Position(0, 33);
  game.array_players[3]->Set_Token_Position(1, 31);
  game.array_players[3]->Set_Token_Position(2, 32);
  game.array_players[3]->Set_Token_Position(3, 34);
  game.array_players[3]->Move_Token(0, 2);
  game.array_players[3]->Move_Token(1, 6);
  game.array_players[3]->Move_Token(2, 6);
  game.array_players[3]->Move_Token(3, 2);
  REQUIRE(game.array_players[3]->Get_Token_Position(0) == 45);
  REQUIRE(game.array_players[3]->Get_Token_Position(1) == 47);
  REQUIRE(game.array_players[3]->Get_Token_Position(2) == 48);
  REQUIRE(game.array_players[3]->Get_Token_Position(3) == 46);
}

// Requirement 59: "Befindet sich eine fremde Figur auf dem eigenen Startfeld,
// so wird diese geschmissen falls man eine eigene Figur aus dem Haus bringt"

TEST_CASE("Test Kick_Token_From_Start_Position", "[cla_player]") {
  LOGIC::cla_session game(4, 0, LOGIC::Student);
  game.array_players[0]->Set_Token_Position(1, 15);
  game.array_players[1]->Set_Token_Position(1, 25);
  game.array_players[2]->Set_Token_Position(1, 35);
  game.array_players[3]->Set_Token_Position(1, 5);
  game.array_players[0]->Move_Token(0, 6);
  game.array_players[1]->Move_Token(0, 6);
  game.array_players[2]->Move_Token(0, 6);
  game.array_players[3]->Move_Token(0, 6);
  REQUIRE(game.array_players[0]->Get_Token_Position(0) == 5);
  REQUIRE(game.array_players[1]->Get_Token_Position(0) == 15);
  REQUIRE(game.array_players[2]->Get_Token_Position(0) == 25);
  REQUIRE(game.array_players[3]->Get_Token_Position(0) == 35);

  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 2);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 2);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 2);
  REQUIRE(game.array_players[3]->Get_Token_Position(1) == 2);
}

// Requirement 55: "Spielfiguren werden übersprungen, außer sie befinden sich
// auf dem letzten Feld des Spielzugs"
TEST_CASE("Test Skip_And_Kick_Tokens", "[cla_player]") {
  LOGIC::cla_session game(4, 0, LOGIC::Student);
  game.array_players[0]->Set_Token_Position(1, 15);
  game.array_players[0]->Set_Token_Position(2, 16);
  game.array_players[1]->Set_Token_Position(1, 19);
  game.array_players[2]->Set_Token_Position(1, 17);
  game.array_players[3]->Set_Token_Position(1, 18);
  game.array_players[0]->Move_Token(1, 4);

  REQUIRE(game.array_players[0]->Get_Token_Position(1) == 19);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 16);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 2);
  REQUIRE(game.array_players[2]->Get_Token_Position(1) == 17);
  REQUIRE(game.array_players[3]->Get_Token_Position(1) == 18);
}

// Requirement 54: "Ein Spielzug bei dem ein Spieler mit seiner Spiellfigur auf
// einem von sich selbst besetztem Feld landet, kann nicht ausgeführt werden"

// Test if player throws himself out of the game after start and on the field
TEST_CASE("Test if player throws himself (Requirement 54)", "[cla_player]") {
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
TEST_CASE("Test if player throws himself in and before finish (Requirement 54)",
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