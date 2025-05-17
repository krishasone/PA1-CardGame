#include "card_list.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Helper functions

// ==================== BST Public Methods Tests ====================
void testInsert() {
    cout << "Testing insert()" << endl;
    CardBST bst;

    assert(bst.insert(Card("h 3")) == true);
    assert(bst.count() == 1);


    assert(bst.insert(Card("h 3")) == false);
    assert(bst.count() == 1);

    assert(bst.insert(Card("s 10")) == true);
    assert(bst.insert(Card("c a")) == true);
    assert(bst.count() == 3);

    assert(bst.insert(Card("c 2")) == true);

    assert(bst.insert(Card("s k")) == true);
    bst.printDeck();
    cout << "All insert() tests passed!\n";
}

void testRemove() {
    cout << "=== Testing remove() ===" << endl;
    CardBST bst;

    assert(bst.remove(Card("h 3")) == false);

    bst.insert(Card("h 3"));
    assert(bst.remove(Card("h 3")) == true);
    assert(bst.count() == 0);

    bst.insert(Card("h 3"));
    bst.insert(Card("s 10"));
    assert(bst.remove(Card("s 10")) == true);
    assert(bst.count() == 1);

    bst.insert(Card("c a"));
    bst.insert(Card("c 2"));
    bst.insert(Card("s k"));
    assert(bst.remove(Card("h 3")) == true);
    assert(bst.count() == 3);

    // 5. Non-existent card
    assert(bst.remove(Card("d j")) == false);
    bst.printDeck();
    cout << "All remove() tests passed!\n";
}

void testContains() {
    cout << "=== Testing contains() ===" << endl;
    CardBST bst;

    assert(bst.contains(Card("h 3")) == false);

    bst.insert(Card("h 3"));
    assert(bst.contains(Card("h 3")) == true);

    bst.insert(Card("s 10"));
    bst.insert(Card("c a"));
    assert(bst.contains(Card("s 10")) == true);

    bst.remove(Card("h 3"));
    assert(bst.contains(Card("h 3")) == false);

    assert(bst.contains(Card("d j")) == false);

    cout << "All contains() tests passed!\n";
}

void testSuccessorPredecessor() {
    cout << "Testing successor/predecessor" << endl;
    CardBST bst;
    
    // 1. Successor of leftmost
    assert(bst.getSuccessorNode(Card("c 2"))==nullptr);

    bst.insert(Card("h 3"));
    bst.insert(Card("s 10"));
    bst.insert(Card("c a"));
    bst.insert(Card("c 2"));

    assert(bst.getPredecessorNode(Card("h 3")) == bst.getNodeFor(Card("s 10")));

    assert(bst.getPredecessorNode(Card("s 10")) == bst.getNodeFor(Card("c 2")));

    assert(bst.getPredecessorNode(Card("d j")) == nullptr);

    assert(bst.getSuccessorNode(Card("c 2")) == bst.getNodeFor(Card("s 10")));

    assert(bst.getSuccessorNode(Card("h 3")) == nullptr);

    assert(bst.getSuccessorNode(Card("s 10")) == bst.getNodeFor(Card("h 3")));

    assert(bst.getSuccessorNode(Card("d j")) == nullptr);

    cout << "All successor/predecessor tests passed!\n";
}

void testPrintDeck() {
    cout << "=== Testing printDeck() ===" << endl;
    CardBST bst;
    
    bst.printDeck();

    bst.insert(Card("h 3"));
    bst.printDeck();

    bst.insert(Card("s 10"));
    bst.insert(Card("c a"));
    bst.printDeck();

    bst.remove(Card("h 3"));
    bst.printDeck();

    bst.insert(Card("d j"));
    bst.insert(Card("h k"));
    bst.printDeck();

    cout << "All printDeck() tests passed!\n";
}

//Iterator
void testIterator() {
    cout << "=== Testing Iterator ===" << endl;
    CardBST bst;

    assert(bst.begin() == bst.end());
    assert(bst.rbegin() == bst.rend());


    bst.insert(Card("h 3"));
    auto it = bst.begin();
    assert(it->card == Card("h 3"));
    assert(++it == nullptr);


    bst.insert(Card("s 10"));
    bst.insert(Card("c a"));
    vector<Card> expected = {Card("c a"), Card("h 3"), Card("s 10")};
    size_t i = 0;
    for (auto it = bst.begin(); it != bst.end(); ++it) {
        assert(it->card == expected[i++]);
    }

    auto rit = bst.rbegin();
    assert(rit->card == Card("s 10"));
    assert((++rit)->card == Card("h 3"));
    assert((++rit)->card == Card("c a"));
    assert(++rit == bst.rend());

    // 5. Iterator comparison
    auto it1 = bst.begin();
    auto it2 = bst.begin();
    assert(it1 == it2);
    ++it1;
    assert(it1 != it2);

    cout << "All iterator tests passed!\n";
}

// ==================== playGame Tests ====================
void testPlayGameCommonCards() {
    cout << "=== Testing playGame() with common cards ===" << endl;
    CardBST alice, bob;
    
    // Setup decks
    alice.insert(Card("h 3"));
    alice.insert(Card("s 10"));
    alice.insert(Card("c a"));
    bob.insert(Card("h 3"));
    bob.insert(Card("d j"));

    // Redirect cout
    stringstream output;
    auto old_buf = cout.rdbuf(output.rdbuf());
    
    playGame(alice, bob);
    
    cout.rdbuf(old_buf);
    
    // Verify output
    assert(output.str().find("Alice picked matching card h 3") != string::npos);
    assert(!alice.contains(Card("h 3")));
    assert(!bob.contains(Card("h 3")));
    assert(alice.count() == 2);
    assert(bob.count() == 1);

    cout << "Common cards test passed!\n";
}

void testPlayGameEmptyHand() {
    cout << "=== Testing playGame() with empty hand ===" << endl;
    CardBST alice, bob;
    alice.insert(Card("h 3"));
    
    stringstream output;
    auto old_buf = cout.rdbuf(output.rdbuf());
    
    playGame(alice, bob);
    
    cout.rdbuf(old_buf);
    
    assert(output.str().empty());
    assert(alice.count() == 1);
    assert(bob.count() == 0);

    cout << "Empty hand test passed!\n";
}

void testPlayGameNoCommon() {
    cout << "=== Testing playGame() with no common cards ===" << endl;
    CardBST alice, bob;
    alice.insert(Card("h 3"));
    bob.insert(Card("d j"));
    
    stringstream output;
    auto old_buf = cout.rdbuf(output.rdbuf());
    
    playGame(alice, bob);
    
    cout.rdbuf(old_buf);
    
    assert(output.str().empty());
    assert(alice.count() == 1);
    assert(bob.count() == 1);

    cout << "No common cards test passed!\n";
}

// ==================== Main ====================
int main() {
    // BST Methods
    testInsert();
    testRemove();
    testContains();
    testSuccessorPredecessor();
    testPrintDeck();
    
    // Iterator
    testIterator();
    
    // playGame
    testPlayGameCommonCards();
    testPlayGameEmptyHand();
    testPlayGameNoCommon();

    cout << "=== All tests passed! ===" << endl;
    return 0;
}