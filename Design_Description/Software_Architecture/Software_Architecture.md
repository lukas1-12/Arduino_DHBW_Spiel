## Zustandsautomat

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

## Klassendiagramm Spiellogik

#### Klassendiagramm
```mermaid
  classDiagram
    %%{init:{'flowchart':{'nodeSpacing': 50, 'rankSpacing': 100}}}%%
    class cla_session {
        - uint8_t u8_player_quantity
        - uint8_t u8_computer_quantity
        - cla_player obj_player[u8_player_quantity]

        + cla_session(uint8_t _u8_player_quantity, uint8_t _u8_computer_quantity)
    }
    cla_session "1" *-- "1..4" cla_player
    class cla_player {
        - uint8_t u8_token_position[4]
        
        + Calculate_Possible_Position(uint8_t _u8_token_number, uint8_t _u8_dice_value) uint8_t
        + Move_Man(uint8_t _u8_token_number, uint8_t _u8_dice_value) uint8_t
        + Get_Position(uint8_t _u8_man_number) uint8_t

    }
    cla_player <|-- cla_manual_player
    class cla_manual_player {

    }
    cla_player <|-- cla_computer_player
    class cla_computer_player{
        enum en_mode
        Auto_Move() uint8_t
    }
    note for cla_computer_player "Auto_Move() will return player number."
    en_mode "1" --* "1" cla_computer_player
    class en_mode{
        <<enumeration>>
        hard
        easy
    }
```
#### Beispiel
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
Eventuell könnte hierbei eine Abfrage, ob der Spieler manuell oder Computer ist, zum Problem werden.
Computer wären bei dieser Anordnung immer als letztes am Zug.














