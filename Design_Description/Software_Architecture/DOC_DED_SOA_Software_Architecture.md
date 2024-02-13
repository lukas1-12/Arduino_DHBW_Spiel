## Software Architecture

```mermaid
    classDiagram
    class Arduino_Sketch {
        the Sketch from Arduino IDE
    }
    Arduino_Sketch *--  Game_Logic
    class Game_Logic{
        Library with all 
        classes and methods 
        for the Game Logic
    }
    ASL *-- RGBmatrixPanel
    class RGBmatrixPanel{
        Hardware Abstraction Layer:*
        Library provided by 
        the matrix manufacturer
    }
    class ASL{
        Application service Layer*
        Library with all classes
        and methods for the 
        Hardware handling.
    }
    Arduino_Sketch *-- ASL
    ASL *-- HAL
    RGBmatrixPanel *-- HAL
    class HAL{
        Hardware Abstraction Layer*
    }
```

## Finite State Machine (with external memory)

```mermaid
    stateDiagram-v2
        [*] --> s1
    s1 : Setup real Players
        s1 --> s2 : Green Button
        s2 --> s1: Calculation Complete
    s2 : Modify real Player Number
        s1 --> s3: Red Button
    s3 : Setup Computer Players
        s3 --> s4 : Green Button
    s4 : Modify Computer Player Number
        s4 --> s3: Calculation Complete
        s3 --> s3a : Red Button
    s3a: Setup Computer Player Mode
        s3a --> s3b: Green Button
        s3a --> s4a: Red Button
    s3b: Modify Computer Player Mode
        s3b --> s3a: Calculation Complete
    s4a: Init Game Logic
        s4a --> s5: Init Complete
    s5 : Wait for Dice Roll
        s5 -->s6 : Green Button
    s6 : Roll the Dice 
        state if2 <<choice>>
        s6 --> if2 : Dice was rolled.
        if2 --> s5 : not a 6 and all players in starting square\n and not completed 3 turns to roll the dice.
        if2 --> s9a: not a 6, all players in starting square\n and completed 3 turns to roll the dice.
        if2 --> s8a: none of the other.
        # Players ------------------
    s7 : Wait for Player Input
        s7 --> s8a : Green Button (next token)
    s8 : Display token
        s8 --> s7 : Calculation Complete
        s7 --> s9 : Red Button
    s8a: Validate token
        s8a --> s8 : Valid Token found.
        s8a --> s9a: No Valid Token found.
    s9 : move token
        state if1 <<choice>>
        s9 --> if1 : Player finished move.
        if1 --> s5 : Player gets one more turn\n (Dice value was 6.)
        if1 --> s9a : not all tokens in finishing square,\n next player.
        if1 --> s10 : all tokens in finishing square.
    s9a: Next Player
        s9a --> s5: calculation complete
    s10: Game finished
        s10 --> s1 : Button pressed.
```

## Class Diagram Game Logic Library

### Class Diagram

```cpp
note:   - : private
        # : protected
        + : public
```
```mermaid
  classDiagram
    %%{init:{'flowchart':{'nodeSpacing': 50, 'rankSpacing': 100}}}%%
    
    class cla_session {
        - uint8_t u8_player_quantity
        - uint8_t u8_computer_quantity
        + cla_player *array_players[4]
        + uint8_t u8_is_occupied_id
        + uint8_t u8_is_occupied_token_number

        + cla_session(uint8_t _u8_player_quantity, uint8_t _u8_computer_quantity)
        + Is_Occupied(uint8_t &u8_is_occupied_player_id, uint8_t &u8_is_occupied_token_number, uint8_t _u8_affected_track_position) bool
        + Return_Home(uint8_t _u8_affected_track_position) bool
        + Get_Variables...()  uint8_t

    }

    cla_session "1" *-- "1..4" cla_player
    class cla_player {
        # uint8_t u8_token_position[4]
        # uint8_t u8_start_position
        # cla_session* obj_my_session
        + cla_computer_player* array_computer_players[3]

        + cla_player(uint8_t _u8_start_position, uint8_t _u8_computer_quantity, cla_session* _obj_my_session)
        + Calculate_Possible_Position(uint8_t _u8_token_number, uint8_t _u8_dice_value) uint8_t
        + Move_Token(uint8_t _u8_token_number, uint8_t _u8_dice_value) uint8_t
        + Get_Token_Position(uint8_t _u8_token_number) uint8_t
        + Set_Token_Position(uint8_t _u8_token_number, uint8_t _u8_new_position) uint8_t
        + Get_Token_Progress(uint8_t _u8_token_number) uint8_t
        + Get_Player_Status() status
        + Get_Player_Progress() uint8_t
        + virtual Is_Computer() bool

    }

    cla_player <|-- cla_manual_player
    class cla_manual_player {

    }
    cla_player <|-- cla_computer_player
    class cla_computer_player{
        - uint8_t u8_en_mode
        + cla_player *obj_player

        + cla_computer_player(cla_player *_obj_player, uint8_t _u8_mode)
        + Auto_Move(uint8_t _u8_dice_value) uint8_t
    }

    mode "1" --* "1" cla_computer_player
    class mode{
        <<typedef enum>>
        hard
        easy
    }
```

### token_track_position and token_progress

```cpp
uint8_t u8_token_track_position
```
The absolute position of the token. The track squares are numbered the same for all players, so the starting square for each player differs.
```cpp
uint8_t u8_token_progress
```
The relative Position of the token. The track squares are numbered individually for each player, so the starting square for each player has the same number.

### Functional Description of Methods

#### cla_session

```cpp
cla_session(uint8_t _u8_player_quantity, uint8_t _u8_computer_quantity)
```
Constructor.


```cpp
Is_Occupied(uint8_t _u8_affected_track_position) : uint8_t
```
checks if there is a token at a given track position


```cpp
Return_Home(uint8_t _u8_affected_track_position) : bool
```
checks if there is a token at a given track position and puts it back into the starting square. If a token was returned, the return value is ```True```. If the track position was not occupied, the return value is ```False```


#### cla_player

```cpp
cla_player(uint8_t _u8_start_position, uint8_t _u8_computer_quantity,cla_session* _obj_my_session)
```
Constructor. A pointer to the corresponding session class is needed for calling cla_session methods calling inside cla_player methods.

```cpp
uint8_t Calculate_Possible_Position(uint8_t _u8_token_number, uint8_t _u8_dice_value) 
```
Return the position that can be reached with the dice value. (absolut position (absolute Positions are 5-44))

```cpp
uint8_t Move_Token(uint8_t _u8_token_number, uint8_t _u8_dice_value)
```
Moves the Token and returns the reached position. (absolute position)

```cpp
uint8_t Get_Token_Position(uint8_t _u8_token_number)
```
Returns the absolute Position of the Token (track position)

```cpp
uint8_t Get_Token_Progress(uint8_t _u8_token_number)
```
Returns the relative Position (1-39) of the Token (progress)

```cpp 
status Get_Player_Status() 
```
Returns the Players status. Status is defined via typedef enum and can have the following values:
en_status           |Token(s) in Starting Square| Token(s) on Game Track| Token(s) in Finishing Square
--------------------|---------------------------|-----------------------|---------------------------
Start               | YES                       | NO                    | NO
Start_Track         | YES                       | YES                   | NO
Start_Finished      | YES                       | NO                    | YES
Start_Track_Finished| YES                       | YES                   | YES
Error               | NO                        | NO                    | NO
Track               | NO                        | YES                   | NO
Finished            | NO                        | NO                    | YES
Track_Finished      | NO                        | YES                   | YES

```cpp
uint8_t Get_Player_Progress()
```
Adds the u8_token_progress of all tokens together and returns that value (Finished == 166).

```cpp
virtual bool Is_Computer()
```
Returns ```True``` or ```False```. Method implemented individually in child classes. If possible, an alternative would be to actually return the type. the method name would then be something like ```Get_Player_Type()```

#### cla_computer_player

```cpp
uint8_t Auto_Move(uint8_t _u8_dice_value)
```
Calculates a move automatically depending on en_mode.

### Example code snippets

```cpp
cla_session::cla_session(uint8_t _u8_player_quantity, uint8_t _u8_computer_quantity){
    uint8_t i = 0;
    while(i < (_u8_player_quantity - _u8_computer_quantity)){
        obj_player[i] = new cla_manual_player();
        i++;
    }
    while(i < _u8_player_quantity){
        obj_player[i] = new cla_computer_player();
        i++;
    }
}
//  u8_player_quantity 
//      = cu8_computer_quantity + quantity of manual players.
```
With this setup, computers are always the last at play. Maybe a different approach is better for the Game experience.

AutoMove() might need two return parameters. This could be done like this:
```cpp
    #include <utility>
    return std::make_pair(intValue, doubleValue);
```

## Class Diagram ASL

```mermaid
  classDiagram
  class cla_display {
        - uint8_t u8_matrix_a
        - uint8_t u8_matrix_b
        - uint8_t u8_matrix_c
        - uint8_t u8_matrix_clk
        - uint8_t u8_matrix_lat
        - uint8_t u8_matrix_oe
        - RGBmatrixPanel *obj_matrix
        - uint8_t u8_track_positions[40][3]
        - uint8_t u8_home_positions[4][4][2]
        - uint8_t u8_finished_positions[4][4][2]
        - int16_t u16_player_color[4][2]
        - uint16_t u16_track_color
        - en_blink_mode en_current_blink_mode
        - u8_blink_player
        - u8_blink_track_position

        + cla_display(uint8_t _u8_matrix_a, uint8_t _u8_matrix_b, uint8_t _u8_matrix_c, uint8_t _u8_matrix_clk, uint8_t _u8_matrix_lat, uint8_t _u8_matrix_oe)
        + Set_Colors(uint8_t _u8_player_nr, uint16_t _u16_bright_color, uint16_t _u16_dark_color) void
        + Begin() void
        + Display_Players() void
        + Display_Token(uint8_t _u8_player_number, uint8_t _u8_new_position)
        + Move_Token(uint8_t _u8_player_number, uint8_t _u8_remove_position, uint8_t _u8_add_position) void
        + Display_Dice() void
        + Winner_Animation(uint8_t _u8_player_number) void
        - Blink(en_blink_mode _en_current_blink_mode, int8_t _u8_switching_cycles, uint8_t _u8_player_number, uint8_t _u8_track_position)
    }
    class cla_buttons{
        + cla_buttons()
    }
    class cla_dice{
        + cla_dice()
        + Roll_Dice() int
    }
    class en_blink_mode{
        <<enumeration>>
        Slow
        Fast
        Off
    }
```

#### Timers

- Timer 0: ( 8Bit) Runs from 0 to 5 to create a "random" Dice value
- Timer 1: (16Bit) Used for the LED matrix
- Timer 2: ( 8Bit) Not in Use
- Timer 3: (16Bit) Used for Button Debounce
- Timer 4: (16Bit) Used for Led Blinking
- TImer 5: (16Bit) Not in Use