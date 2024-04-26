/**
 * \file defines.hpp
 *
 * \brief This file contains all the defines for the project.
 *
 * Use this file to define all the ports, colors, animation speeds, initial
 * values and debug modes.
 */

#ifndef DEFINES_HPP
#define DEFINES_HPP

// Define all the Ports here:
#define CLK 11 // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE 12
#define A A0
#define B A1
#define C A2

// define all the colors
#define RED_BRIGHT 0xf800
#define RED_DARK 0x1000
#define GREEN_BRIGHT 0x7e0
#define GREEN_DARK 0xa0
#define YELLOW_BRIGHT 0xffe0
#define YELLOW_DARK 0x10a0
#define BLUE_BRIGHT 0x001f
#define BLUE_DARK 0x0002
#define WHITE_BRIGHT 0xffff

// Define Debounce time
// -> T of 0x1000 count cycles: 4096 * 0,000064s = 0,262144s
#define DEBOUNCE_TIME 0x1000

// See Calculation Excel for more information on the timing.
#define FAST_BLINK 7813
#define SLOW_BLINK 15625

// Define Animation Speed
#define ANIMATION_SPEED_COMPUTER 15625 // 15625 -> 250ms
#define ANIMATION_SPEED_DICE 3125      // 6250 -> 100ms, repeated 20 times -> 2s
#define ANIMATION_SPEED_MOVE 6250      // 6250 -> 100ms

// Define cylce count
#define BLINK_CYCLES_TOKEN -1
#define BLINK_CYCLES_OCCUPIED_TOKEN 3
#define BLINK_CYCLES_WINNER_ANIMATION -1

// Define initial values
#define INITIAL_DICE_VALUE 0
#define INITIAL_DICE_ROLL_COUNTER DICE_ROLLS_AT_START
#define INITIAL_COMPUTER_MODE LOGIC::Student
#define INITIAL_PLAYER_QUANTITY 2
#define INITIAL_COMPUTER_QUANTITY 0
#define INITIAL_CURRENT_PLAYER_NUMBER 0
#define INITIAL_CURRENT_TOKEN_NUMBER 0
#define INITIAL_BOOL_BLINK_FLAG false

// Other defines
#define DICE_ROLLS_AT_START 3
#define DICE_ROLLS_NORMAL 1
#define DICE_ROLLS_AT_SIX 1

// Define the Debug Flag
#define DEBUG false
#define TIMING_DEBUG false
// 0 for off
// 1 for ISR(INT4_vect)
// 2 for ISR(INT5_vect)
// 3 for ISR(TIMER3_COMPA_vect)
// 4 for ISR(TIMER4_COMPA_vect)
// 5 for ISR(TIMER5_COMPA_vect)
// 6 for ISR in matrix library (Adafruit_GFX)
// number 6 must be added individually to the library, as the library is
// automatically loaded when compiling platformio project for the first time.
#define TIMING_DEBUG_INTERN 0
// number of interupts to measure before crash.
#define TIMING_DEBUG_COUNT_TO 100
// DICE_MODE 0: Normal, Random Dice
//           1: Dice input via PORT L
//           2: marked Dice using Array
#define DICE_MODE 0
#if DICE_MODE == 2
#include "../test/marked_dice.hpp"
#endif
#endif