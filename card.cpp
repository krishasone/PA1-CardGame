// card.cpp
// Author: Krisha Soneji
// Implementation of the classes defined in card.h
#include "card.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;
Card::Card(string c) {
    if (c.length()==3){
        suit = c.substr(0,1);
        value = c.substr(2,1);
    }
    else {
        suit = c.substr(0,1);
        value = c.substr(2,4);
    }
}
string Card::getSuit() const{
    return suit;
}
string Card::getValue() const{
    return value;
}
bool Card::operator<(const Card& other) const{
    string suitOrder = "cdsh";
    string valueOrder = "a1234567891jqk";

    int thisSuit = suitOrder.find(suit);
    int otherSuit = suitOrder.find(other.suit);
    
    if (thisSuit != otherSuit) {
        return thisSuit < otherSuit;
    }

    if (value == "10" && other.value == "10") return false;
    if (value == "10") return false;
    if (other.value == "10") return true;
    
    int thisVal = valueOrder.find(value);
    int otherVal = valueOrder.find(other.value);
    
    return thisVal < otherVal;
}
bool Card::operator== (const Card& other) const{
    return suit == other.suit && value == other.value;
}

bool Card::operator>(const Card& other) const{
    return other < *this;
}