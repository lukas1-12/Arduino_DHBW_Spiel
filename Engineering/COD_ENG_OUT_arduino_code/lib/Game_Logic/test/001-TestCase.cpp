#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <logic.hpp>


TEST_CASE("Test game constructer", "[cla_session]") {
  LOGIC::cla_session game(4, 1);
  REQUIRE(game.Get_Player_Quantity() == 4);
  REQUIRE(game.Get_Computer_Quantity() == 1);
}

TEST_CASE("Test Set_Token", "[cla_player]") {
  LOGIC::cla_session game(4, 2);
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
  LOGIC::cla_session game(4, 0);
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
  REQUIRE(game.array_players[0]->Get_Token_Position(3) == 32);
}

//Requirement 44: "Landet ein Benutzer mit seiner Spielfigur auf einem bereits von einem anderen Benutzer besetzten Feld, so schmeißt er diesen automatisch"

TEST_CASE("Test Move_Token_Kick", "[cla_player]") {
  LOGIC::cla_session game(4, 0);
  game.array_players[0]->Set_Token_Position(2, 29);
  game.array_players[1]->Set_Token_Position(1, 25);
  game.array_players[0]->Move_Token(2, 1);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 30);
  game.array_players[1]->Move_Token(1, 5);
  REQUIRE(game.array_players[0]->Get_Token_Position(2) == 3);
  REQUIRE(game.array_players[1]->Get_Token_Position(1) == 30);
}

//Requirement 46: "Zu Beginn befinden sich alle Figuren in den Häusern"
TEST_CASE("Test Home_Position", "[cla_player]") {
  LOGIC::cla_session game(4, 0);
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

//Requirement  52: "Erreicht eine Spielfigur das Endfeld, so begibt sie sich mit den übrigen, gewürfelten Felder ins Ziel"
TEST_CASE("Test Move into Finish", "[cla_player]") {
  LOGIC::cla_session game(4, 0);
  
  //Player 0
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

  //Player 1
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

  //Player 2
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

  //Player 3
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