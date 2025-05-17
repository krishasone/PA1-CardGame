// card_list.h
// Author: Krisha Soneji
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H
#include <iostream>
#include "card.h"

using namespace std;

class CardBST {
 private:

    struct Node {
	Card card;
	Node *left, *right, * parent;
	// useful constructor:
    Node(const Card& card) : card(card), left(nullptr), right(nullptr), parent(nullptr) { }
    };

    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
     // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(Card c, Node *n); // note overloading names for simplicity
    int count (Node* n);
    
    void printDeck(Node* n);
    Node* findMin(Node* n);
    Node* findMax(Node* n);
    ostream& operator<< (Card c);
    Node* getNodeFor(Card c, Node* n) const;

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
       

 public:
    CardBST();               
    ~CardBST();                
    bool insert(Card c);    
    bool remove(Card c);   
    int count();
    void printDeck();
    Card getSuccessor(Card c);
    Node* findMin();
    Node* findMax();
    bool contains (Card c) const;
    Node* getNodeFor(Card c) const;
    
    Node* getSuccessorNode(Card c) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(Card c) const; // returns the Node containing the predecessor of the given value 
    
    class iterator;
    iterator begin();
    iterator end();
    iterator rbegin();
    iterator rend();
    friend void playGame(CardBST& alice, CardBST& bob);
};

class CardBST::iterator {
    private:
        CardBST::Node* curr;
        CardBST* tree;
    public:
        iterator(CardBST::Node* p = nullptr, CardBST* ptree= nullptr): curr(p), tree(ptree){
    }

        Card& operator*() const { return curr->card; }
        Node* operator->() const { return curr; }

        iterator& operator++() {
            if (curr) {
            curr = tree->getSuccessorNode(curr->card);
            }
            return *this;

        }
        iterator& operator--(){
            curr = tree->getPredecessorNode(curr->card);
            return *this;
        }

        bool operator==(const iterator& other) const { 
            return curr == other.curr; 
        }
        bool operator!=(const iterator& other) const { 
            return !(*this == other); 
        }

    };
void playGame(CardBST& alice, CardBST& bob);
#endif

