/**
 * \file marked_dice.hpp
 * \brief This file contains the dice values for the test cases.
 *
 * This file contains multiple arrays for different test cases. The array to be
 * used can be selected using the TEST_CASE macro.
 */

#ifndef MARKED_DICE_HPP
#define MARKED_DICE_HPP
#include "Arduino.h"

#define TEST_CASE 2

#if TEST_CASE == 0
// Test the Dice roll counter (you can roll the dice 3 times when all tokens in
// starting square, if the dice value is 6, you get a second turn.)
// 1 Real Player, 1 Computer Player
const uint8_t u8_dice_value_array[] = {6, 6, 5, 1, 1, 6, 2,
                                       1, 1, 1, 1, 1, 6, 3};
#elif TEST_CASE == 1
// Test token blinking
// 1 Real Player, 1 Computer Player
const uint8_t u8_dice_value_array[] = {6, 5, 6, 1, 6, 4, 1, 4, 1, 4, 1, 1, 1};
#elif TEST_CASE == 2
// Test winner animation (Get Player 1 in finishing square as fast as possible)
// 1 Real Player
const uint8_t u8_dice_value_array[] = {6, 40, 6, 41, 6, 42, 6, 43,
                                       1, 1,  1, 1,  1, 1,  1};
#elif TEST_CASE == 3
// Test walking (test if tokens walk over each other)
// 2 Real Players
const uint8_t u8_dice_value_array[] = {6, 5, 6, 1, 5, 1, 3, 3,
                                       4, 4, 5, 4, 2, 5, 4};
#elif TEST_CASE == 4
// Test walking (test if tokens can get accross 44/5 line without problems)
// 4 Real Players
const uint8_t u8_dice_value_array[] = {6, 5, 1, 1, 1, 1, 1, 1, 6, 5,
                                       6, 1, 1, 1, 1, 1, 1, 1, 7};
#elif TEST_CASE == 5
// Test walking: New player dissapears
// Expected behavior: Player 1 should dissapear from the track, because he is
// thrown by player 2 2 Real Players
const uint8_t u8_dice_value_array[] = {6, 15, 6, 5, 0, 0, 0, 0};
#elif TEST_CASE == 6
// Test walking: New player dissapears
// Expected behavior: Player 1 should dissapear from the track, because he is
// thrown by player 2
// 2 Real Players
const uint8_t u8_dice_value_array[] = {6, 5, 1, 1, 1, 5, 1, 1,
                                       1, 3, 6, 1, 1, 3, 0, 0};
#elif TEST_CASE == 7
// Test walking: Player on position 44
// Expected behavior: Green player should be on position 44.
// 4 real players
const uint8_t u8_dice_value_array[] = {6, 1, 6, 1, 6, 1, 6, 9, 1, 1, 1, 1};
#elif TEST_CASE == 8
// Test walking: finish line
// Expected behavior: Players should finish
// 4 real players
const uint8_t u8_dice_value_array[] = {6, 39, 6, 39, 6, 39, 6, 39, 1, 1,
                                       1, 1,  6, 41, 6, 42, 6, 43, 6, 41};
#elif TEST_CASE == 9
// Test walking: finish line
// Expected behavior: Player1 should finish
// 1 real player
const uint8_t u8_dice_value_array[] = {6, 39, 1, 6, 38, 3, 6, 42, 6, 43};
// BUG-SPECIFIC TEST CASES
#elif TEST_CASE == 10
// Test Bug: Player 1 throw player 3
// Expected behavior: Player 3 should be thrown and immediatly appear in his
// starting square 3 real players
const uint8_t u8_dice_value_array[] = {6, 21, 6, 1, 6, 3, 2};
#elif TEST_CASE == 11
// Test Bug: Player 1 blink in finish position [seems like bug appears if finish
// position is occupied by other player]
// Expected behavior: Player 1 should
// blink in his finish position 2 real player
const uint8_t u8_dice_value_array[] = {6, 40, 6, 41, 6, 1, 0, 1};
#endif

#endif