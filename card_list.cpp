// card_list.cpp
// Author: Your name
// Implementation of the classes defined in card_list.h
#include "card_list.h"
#include "card.h"
#include <iostream>
using std::cout;

CardBST::CardBST(){
    root = nullptr;
}

CardBST::~CardBST(){
    clear(root);
}

void CardBST::clear(Node*n){
    if (n==nullptr){
        return;
    }
    clear(n->left);
    clear(n->right);
    delete n;
}


CardBST::Node* CardBST::getNodeFor(Card c, Node* n) const {
    if (n == nullptr) {
        return nullptr;
    }
    if (c == n->card) {
        return n;
    }
    if (c < n->card) {
        if (n->left != nullptr){
            return getNodeFor(c, n->left);
        }
        else {
            return nullptr;
        }
    }
    else {
        if (n->right != nullptr){
            return getNodeFor(c, n->right);
        }
        else {
            return nullptr;
        }
    }
}
CardBST::Node* CardBST::getNodeFor(Card c) const{
    return getNodeFor(c, root);
}

bool CardBST::insert(Card c, Node *n) {
    if (c == n->card) {
        return false;
    }
    if (c < n->card) {
        if (n->left == nullptr){
            n->left = new Node(c);
            n->left->parent = n;
            return true;
        }
        else {
            return insert(c, n->left);
        }
    }
    else {
        if (n->right == nullptr) {
            n->right = new Node(c);
            n->right->parent = n;
            return true;
        }
        else {
            return insert(c, n->right);
        }
    }
    return false;
}

bool CardBST::insert(Card c) {
    if (root == nullptr) {
        root = new Node(c);
        return true;
    }
    return insert(c, root);  
}

int CardBST::count (Node* n){
    if (n == nullptr){
        return 0;
    }
    return 1 + count(n->left) + count(n->right);
}

int CardBST::count() {
    return count(root);
}


CardBST::Node* CardBST::getSuccessorNode(Card c) const{
    Node* curr = getNodeFor(c, root);
    if (curr == nullptr) {
        return nullptr;
    }
    if (curr->right != nullptr){
        curr = curr->right;
        while (curr->left!=nullptr){
            curr = curr->left;
        }
        return curr;
    }
    else {
        Node* successor = nullptr;
        Node* ancestor = root;
        while (ancestor != curr) {
            if (curr->card < ancestor->card) {
                successor = ancestor; // So far this is the deepest node for which current is in left
                ancestor = ancestor->left;
            } else {
                ancestor = ancestor->right;
            }
        }
        return successor;
        }
        return nullptr;
}

Card CardBST:: getSuccessor(Card c){
    if (CardBST::getSuccessorNode(c) == nullptr){
        return Card("0");
    }
    else {
        return CardBST::getSuccessorNode(c)->card;
    }
}

CardBST::Node* CardBST::getPredecessorNode(Card c) const {
    Node* curr = getNodeFor(c, root);
    if (curr == nullptr) {
        return nullptr;
    }
    if (curr->left != nullptr){
        curr = curr->left;
        while (curr->right!=nullptr){
            curr = curr->right;
        }
        return curr;
    }
    else {
        Node* parent = curr->parent;
        while (parent != nullptr && curr == parent->left) {
            curr = parent;
            parent = parent->parent;
        }
        return parent;
    }
}
bool CardBST::contains(Card c) const {
    if (getNodeFor(c, root)!=nullptr) {
        return true;
    }
    return false;
}


bool CardBST::remove(Card c){
    if (CardBST::contains(c) == false) {
        return false;
    }
    Node* n = getNodeFor(c, root);

    if (n->right == nullptr && n->left == nullptr) {
        if (n->parent == nullptr) {
            root = nullptr;
            delete n;
            return true;
        }
        if (n->parent->right == n) {
            n->parent->right = nullptr;
            delete n;
            return true;
        }
        if (n->parent->left == n) {
            n->parent->left = nullptr;
            delete n;
            return true;
        }
    }
    if (n->right == nullptr) {
        if (n->parent == nullptr) {
            root = n->left;
            root->parent=nullptr;
            delete n;
            return true;
        }
        if (n->parent->right == n) {
            n->parent->right = n->left;
            n->left->parent = n->parent;
            delete n;
            return true;
        }
        if (n->parent->left == n) {
            n->parent->left = n->left;
            n->left->parent = n->parent;
            delete n;
            return true;
        }
        //predecessor of deletd node=swap value,one node tree, leaf node, one child, two children
    }
    if (n->left == nullptr) {
        if (n->parent == nullptr) {
            root = n->right;
            root->parent=nullptr;
            delete n;
            return true;
        }
        if (n->parent->left == n) {
            n->parent->left = n->right;
            n->right->parent = n->parent;
            delete n;
            return true;
        }
        if (n->parent->right == n) {
            n->parent->right = n->right;
            n->right->parent = n->parent;
            delete n;
            return true;
        }
    }

    if (n->left != nullptr && n->right != nullptr) {
        Card successor_val = getSuccessor(c);
        Node* successor_node = getSuccessorNode(c);

        Card temp = n->card;
        n->card = successor_val;
        successor_node->card = temp;

        if (successor_node->parent->left == successor_node) {
            successor_node->parent->left = successor_node->right; 
            if (successor_node->right != nullptr) {
                successor_node->right->parent = successor_node->parent;
            }
        } else {
            successor_node->parent->right = successor_node->right;
            if (successor_node->right != nullptr) {
                successor_node->right->parent = successor_node->parent;
            }
        }

        delete successor_node;
        return true;
    }
    return false;
    
}

ostream& operator<< (ostream& s, Card c){
    s<<c.getSuit()<<" "<<c.getValue();
    return s;
}

void CardBST::printDeck(Node* n){
    if (n == nullptr) {
        return;
    }
    printDeck(n->left);
    cout<<n->card<<" "<<endl;
    printDeck(n->right);
}

void CardBST::printDeck(){
    printDeck(root);
}

CardBST::Node* CardBST::findMin (Node* n){
    if (n==nullptr){
        return nullptr;
    }
    if (n->left == nullptr) {
        return n;
    }
    return findMin(n->left);
    
}

CardBST::Node* CardBST::findMax (Node* n){
    if (n==nullptr){
        return nullptr;
    }
    if (n->right == nullptr) {
        return n;
    }
    return findMax(n->right);
    
}

CardBST::Node* CardBST::findMin (){
   return findMin(root);
}

CardBST::Node* CardBST::findMax (){
   return findMax(root);
}

CardBST::iterator CardBST:: begin(){
    return iterator(findMin(),this);
}

CardBST::iterator CardBST:: end(){
    return iterator(findMax(),this);
}

CardBST::iterator CardBST:: rend(){
    return iterator(findMin(),this);
}

CardBST::iterator CardBST:: rbegin(){
    return iterator(findMax(),this);
}
void playGame(CardBST& alice, CardBST& bob){
    bool matchFound = true;
    
    while (matchFound) {
        matchFound = false;

        for (auto it = alice.begin(); it != alice.end();++it) {
            Card valueToRemove = it->card;
            if (bob.contains(it->card)) {
                cout << "Alice picked matching card " << it->card << endl;
          

                bob.remove(valueToRemove);
                alice.remove(valueToRemove);
                
                matchFound = true;
                break;
            }
        }
        
        if (!matchFound) break;
        matchFound = false;
    
        for (auto rit = bob.rbegin(); rit != bob.rend();++rit) {
            Card valueToRemove = rit->card;
            if (valueToRemove == bob.rbegin()->card) {
                bob.rbegin() = ++rit;
            }
            if (alice.contains(rit->card)) {
                cout << "Bob picked matching card " << rit->card << endl;
            
                
                alice.remove(valueToRemove);
                bob.remove(valueToRemove);
                
                matchFound = true;
                break;
            }
        }
    }
}