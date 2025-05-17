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
    string valueOrder = "a234567891jqk";

    int thisSuit = suitOrder.find(suit);
    int otherSuit = suitOrder.find(other.suit);
    
    if (thisSuit != otherSuit) {
        return thisSuit < otherSuit;
    }

    string thisVal = (value == "10") ? "1" : value;
    string otherVal = (other.value == "10") ? "1" : other.value;
    
    return valueOrder.find(thisVal) < valueOrder.find(otherVal);
}
bool Card::operator== (const Card& other) const{
    return suit == other.suit && value == other.value;
}

bool Card::operator>(const Card& other) const{
    return other < *this;
}