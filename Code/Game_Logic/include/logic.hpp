#include <cstdint>

class cla_session {
    public:
        cla_session(uint8_t _u8_player_quantity, uint8_t _u8_computer_quantity);
        uint8_t Is_Occupied(uint8_t _u8_affected_track_position);
        bool Return_Home(uint8_t _u8_affected_track_position);
    
    private:   
        uint8_t u8_player_quantity;
        uint8_t u8_computer_quantity;
};

class cla_player {
    public:
    cla_player(cla_session* _obj_my_session);
    uint8_t Calculate_Possible_Position(uint8_t _u8_token_number,uint8_t _u8_dice_value);
    uint8_t Move_Token(uint8_t _u8_token_number, uint8_t _u8_dice_value);
    uint8_t Get_Token_Position(uint8_t _u8_token_number);
    uint8_t Get_Token_Progress(uint8_t _u8_token_number);
    void Get_Status(uint8_t _u8_token_number); // wie war das gemeint?
    uint8_t Get_Player_Progress();
    bool Is_Computer();

    
    protected:
         uint8_t u8_start_position;
         uint8_t u8_token_position[4];
         cla_session* obj_my_session;
    
};

class cla_computer_player {
    public:
        uint8_t Auto_Move(uint8_t _u8_dice_value);

    private:
        //mode
};

class cla_manual_player {
    public:
        uint8_t Manual_Move(uint8_t _u8_dice_value);
};