#ifndef MARKED_DICE_HPP
#define MARKED_DICE_HPP
#include "Arduino.h"

#define TEST_CASE 0

#if TEST_CASE == 0
// 1 Real Player, 1 Computer Player
const uint8_t u8_dice_value_array[] = {6, 6, 5, 1, 1, 6, 1};
#elif TEST_CASE == 1
const uint8_t u8_dice_value_array[] = {1, 2, 3};
#endif

#endif