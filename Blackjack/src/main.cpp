#include "blackjack.hpp"
#include <iostream>

auto main() -> int
{
    std::string suitNames[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
    std::string rankNames[] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

    cla_deck deck;
    /*
    std::cout << "Deck created" << std::endl;    
    int suitIndex = static_cast<int>(deck.deal().first);
    int rankIndex = static_cast<int>(deck.deal().second);
    std::cout << "Suit: " << suitNames[suitIndex] << " Rank: " << rankNames[rankIndex] << std::endl;
    deck.shuffle();
    std::cout << "Deck shuffled" << std::endl;
    suitIndex = static_cast<int>(deck.deal().first);
    rankIndex = static_cast<int>(deck.deal().second);
    std::cout << "Suit: " << suitNames[suitIndex] << " Rank: " << rankNames[rankIndex] << std::endl;
        deck.shuffle();
    std::cout << "Deck shuffled" << std::endl;
    suitIndex = static_cast<int>(deck.deal().first);
    rankIndex = static_cast<int>(deck.deal().second);
    std::cout << "Suit: " << suitNames[suitIndex] << " Rank: " << rankNames[rankIndex] << std::endl;
    */
   deck.shuffle();
   cla
}