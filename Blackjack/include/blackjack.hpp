#include <stdint.h>
#include <array>
#include <vector>
#include <algorithm>


enum class Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
enum class Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };

class cla_session {
    public:
    cla_session(uint8_t _u8_player_quantity);
    uint8_t u8_get_player_quantity();

    private:
    uint8_t u8_player_quantity;
    
};


class cla_player {
    public:
    bool b_want_to_play();
    bool b_stop_playing();
    uint8_t u8_get_money();
    uint8_t u8_set_money(uint8_t _u8_money);
    uint8_t u8_set_bet();
    bool b_get_is_dealer();
    uint8_t u8_convert_rank_to_value(Rank _rank);
    uint8_t u8_get_hand_value(std::vector<std::pair<Suit, Rank>> _hand);


    private:
    uint8_t u8_money;
    uint8_t u8_bet;
    std::vector<std::pair<Suit, Rank>> hand;
    bool b_is_dealer;
};

class cla_deck {
    public:
    cla_deck();
    void shuffle();
    std::pair<Suit, Rank> deal();


    private:
    std::vector<std::pair<Suit, Rank>> deck;
};