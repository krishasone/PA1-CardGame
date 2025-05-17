#include "card_list.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

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
    cout << "insert passed"<<endl;
}

void testRemove() {
    cout << "testing remove" << endl;
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
    cout << "remove passed"<<endl;
}

void testContains() {
    cout << "testing contains" << endl;
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

    cout << "All contains() tests passed";
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

    cout << "success/predec pass";
}

void testPrintDeck() {
    cout << "test print deck" << endl;
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

    cout << "print deck passed"<<endl;
}

//Iterator
void testIterator() {
    cout << "test iterator" << endl;
    CardBST bst;

    assert(bst.begin() == bst.end());
    assert(bst.rbegin() == bst.rend());


    bst.insert(Card("h 3"));
    auto it = bst.begin();
    assert(it->card == Card("h 3"));
    assert(++it == bst.end());


    bst.insert(Card("s 10"));
    bst.insert(Card("c a"));
    vector<Card> expected = {Card("c a"), Card("s 10"), Card("h 3"), };
    size_t i = 0;
    bst.printDeck();
    for (auto it = bst.begin(); it != bst.end(); ++it) {
        assert(it->card == expected.at(i));
        i++;
    }

    auto rit = bst.rbegin();
    assert(rit->card == Card("h 3"));
    assert((--rit)->card == Card("s 10"));
    assert((--rit)->card == Card("c a"));
    assert(--rit == bst.rend());

    auto it1 = bst.begin();
    auto it2 = bst.begin();
    assert(it1 == it2);
    ++it1;
    assert(it1 != it2);

    cout << "iterator passed"<<endl;
}


void testPlayGameCommonCards() {
    cout << "test common card" << endl;
    CardBST alice, bob;

    // Setup decks
    alice.insert(Card("h 3"));
    alice.insert(Card("s 10"));
    alice.insert(Card("c a"));
    bob.insert(Card("h 3"));
    bob.insert(Card("d j"));

    
    playGame(alice, bob);
    
    assert(!alice.contains(Card("h 3")));
    assert(!bob.contains(Card("h 3")));
    assert(alice.count() == 2);
    assert(bob.count() == 1);

    cout << "common card test passed"<<endl;
}

void testPlayGameEmptyHand() {
    cout << "playgame w empty hand" << endl;
    CardBST alice, bob;
    alice.insert(Card("h 3"));
    
    playGame(alice, bob);
    
    assert(alice.count() == 1);
    assert(bob.count() == 0);

    cout << "empty hand test"<<endl;
}

void testPlayGameNoCommon() {
    cout << "no common cards test" << endl;
    CardBST alice, bob;
    alice.insert(Card("h 3"));
    bob.insert(Card("d j"));
    
    
    playGame(alice, bob);
    
    assert(alice.count() == 1);
    assert(bob.count() == 1);

    cout << "no common cards test passed!"<<endl;
}

int main() {
    testInsert();
    testRemove();
    testContains();
    testSuccessorPredecessor();
    testPrintDeck();
    
    testIterator();
    
    testPlayGameCommonCards();
    testPlayGameEmptyHand();
    testPlayGameNoCommon();

    cout << "all tests passed" << endl;
    return 0;
}