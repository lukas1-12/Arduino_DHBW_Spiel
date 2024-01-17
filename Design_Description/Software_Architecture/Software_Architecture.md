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
        Roll_Dice()
        Button_01_Interrupt_Handler()
        Button_02_Interrupt_Handler()
        ...()
    }
    Arduino_Sketch *-- ASL
    ASL *-- HAL
    RGBmatrixPanel *-- HAL
    class HAL{
        Hardware Abstraction Layer*
    }
```

## Finite State Machine

```mermaid
    stateDiagram-v2
        [*] --> s1
        s1 : Intitialise
        s1 --> s2 : Start of Game session.
        s2 : move
        state if1 <<choice>>
        s2 --> if1 : Player finished move.
        if1 --> s2 : not all tokens in finishing square, next player.
        if1 --> s3 : all tokens in finishing square.
        s3 : Game finished
        s3 --> s1 : Button pressed.
```

## Class Diagram Game Logic Library

### Class Diagram
---
```c++
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
        + cla_player obj_player[u8_player_quantity]

        + cla_session(uint8_t _u8_player_quantity, uint8_t _u8_computer_quantity)
        + Is_Occupied(uint8_t _u8_affected_track_position) uint8_t
        + Return_Home(uint8_t _u8_affected_track_position) bool
    }

    cla_session "1" *-- "1..4" cla_player
    class cla_player {
        # uint8_t u8_token_position[4]
        # uint8_t u8_start_position
        # cla_session* obj_my_session

        + cla_player(cla_session* _obj_my_session)
        + Calculate_Possible_Position(uint8_t _u8_token_number, uint8_t _u8_dice_value) uint8_t
        + Move_Token(uint8_t _u8_token_number, uint8_t _u8_dice_value) uint8_t
        + Get_Token_Position(uint8_t _u8_token_number) uint8_t
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
        - mode en_mode
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
---
```c++
uint8_t u8_token_track_position
```
The absolute position of the token. The track squares are numbered the same for all players, so the starting square for each player differs.
```c++
uint8_t u8_token_progress
```
The relative Position of the token. The track squares are numbered individually for each player, so the starting square for each player has the same number.

### Functional Description of Methods
---
#### cla_session
---
```c++
cla_session(uint8_t _u8_player_quantity, uint8_t _u8_computer_quantity)
```
Constructor.

---
```c++
Is_Occupied(uint8_t _u8_affected_track_position) : uint8_t
```
checks if there is a token at a given track position

---
```c++
Return_Home(uint8_t _u8_affected_track_position) : bool
```
checks if there is a token at a given track position and puts it back into the starting square. If a token was returned, the return value is ```True```. If the track position was not occupied, the return value is ```False```

---
#### cla_player
---
```c++
cla_player(cla_session* _obj_my_session)
```
Constructor. A pointer to the corresponding session class is needed for calling cla_session methods calling inside cla_player methods.

---
```c++
uint8_t Calculate_Possible_Position(uint8_t _u8_token_number, uint8_t _u8_dice_value) 
```
Return the position that can be reached with the dice value. (absolute/track position)

---
```c++
uint8_t Move_Token(uint8_t _u8_token_number, uint8_t _u8_dice_value)
```
Moves the Token and returns the reached position. (absolute/track position)

---
```c++
uint8_t Get_Token_Position(uint8_t _u8_token_number)
```
Returns the absolute Position of the Token (track position)

---
```c++
uint8_t Get_Token_Progress(uint8_t _u8_token_number)
```
Returns the relative Position of the Token (progress)

---
```c++ 
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

---
```c++
uint8_t Get_Player_Progress()
```
Adds the u8_token_progress of all tokens together and returns that value.

---
```c++
virtual bool Is_Computer()
```
Returns ```True``` or ```False```. Method implemented individually in child classes. If possible, an alternative would be to actually return the type. the method name would then be something like ```Get_Player_Type()```

---
#### cla_computer_player
---
```c++
uint8_t Auto_Move(uint8_t _u8_dice_value)
```
Calculates a move automatically depending on en_mode.

### Example code snippets
---
```c++
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
```c++
    #include <utility>
    return std::make_pair(intValue, doubleValue);
```













