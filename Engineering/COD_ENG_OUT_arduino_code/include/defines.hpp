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

// See Calculation Excel for more information on the timing.
#define FAST_BLINK 7813
#define SLOW_BLINK 15625

// Define the Debug Flag
#define DEBUG true
#define RANDOM_DICE false