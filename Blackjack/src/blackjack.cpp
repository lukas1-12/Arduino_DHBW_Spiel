#include "blackjack.hpp"
#include <iostream>
#include <stdint.h>
#include <array>
#include <vector>
#include <utility>
#include <random>


cla_session::cla_session(uint8_t _u8_player_quantity) {
    u8_player_quantity = u8_player_quantity;
}

cla_deck::cla_deck() {
    uint8_t u8_index = 0;
    for (uint8_t u8_suit = 0; u8_suit < 4; u8_suit++) {
        for (uint8_t u8_rank = 1; u8_rank < 14; u8_rank++) {
            deck.push_back({ static_cast<Suit>(u8_suit), static_cast<Rank>(u8_rank) });
            u8_index++;
        }
    }
}

uint8_t cla_player::u8_convert_rank_to_value(Rank _rank) {
    switch (_rank) {
        case Rank::ACE:
            return 1;
        case Rank::TWO:
            return 2;
        case Rank::THREE:
            return 3;
        case Rank::FOUR:
            return 4;
        case Rank::FIVE:
            return 5;
        case Rank::SIX:
            return 6;
        case Rank::SEVEN:
            return 7;
        case Rank::EIGHT:
            return 8;
        case Rank::NINE:
            return 9;
        case Rank::TEN:
            return 10;
        case Rank::JACK:
            return 10;
        case Rank::QUEEN:
            return 10;
        case Rank::KING:
            return 10;
        default:
            return 0;
    }
}



uint8_t cla_player::u8_get_hand_value(std::vector<std::pair<Suit, Rank>> _hand) {
    uint8_t u8_hand_value = 0;
    uint8_t u8_ace_count = 0;
    for (auto card : _hand) {
        uint8_t u8_card_value = u8_convert_rank_to_value(card.second);
        if (u8_card_value == 1) {
            u8_ace_count++;
        }
        u8_hand_value += u8_card_value;
    }
    while (u8_hand_value <= 11 && u8_ace_count > 0) {
        u8_hand_value += 10;
        u8_ace_count--;
    }
    return u8_hand_value;
}



void cla_deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

std::pair<Suit, Rank> cla_deck::deal() {
    if (!deck.empty()) {
        std::pair<Suit, Rank> card = deck.back();
        deck.pop_back();
        return card;
    } else {
        std::cout << "Das Deck ist leer!" << std::endl;
        return { Suit::HEARTS, Rank::ACE }; // Dummy-Karte zurückgeben
    }
}