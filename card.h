// card.h
// Author: Krisha Soneji
// All class declarations related to defining a single card go here
#ifndef CARD_H
#define CARD_H
#include <string>
#include<iostream>
using namespace std;
class Card {
    public:
        Card(string c);
        string getSuit() const;
        string getValue() const;
        bool operator<(const Card& other) const;
        bool operator>(const Card& other) const;
        bool operator==(const Card& other) const;
    private:
        string suit;
        string value;
};
#endif
