// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"
#include <iterator>

using namespace std;

void game(set<Card>& a, set<Card>& b){
  set<Card>::iterator it;
  set<Card>::iterator rit;
  bool matchFound = false;
  bool run = true;
  while (run) {
    for (it = a.begin(); it!=a.end();) {
      if (b.find(*it)!=b.end()){
        cout<<"Alice picked matching card "<<it->getSuit()<<" "<<it->getValue()<<endl;
        b.erase(*it);
        
        it = a.erase(it);
        matchFound = true;
        break;
      }
      else{
        ++it;
      }   
    }
    if (matchFound) {
      matchFound=false;
    }
    else {
      run=false;
    }
    for (auto rit = b.rbegin(); rit!=b.rend(); ) {
      if (a.find(*rit)!=a.end()){
        cout<<"Bob picked matching card "<<rit->getSuit()<<" "<<rit->getValue()<<endl;
        a.erase(*rit);
        auto erased = --(rit.base());
        b.erase(erased);
        matchFound = true;
        break;
      }
      else{
        ++rit;
      }   
    }
  }
  if (matchFound) {
    matchFound=false;
  }
  else {
    run=false;
  }
}

void printCards(set<Card>c){
  for (auto x: c) {
    cout<<x.getSuit()<<" "<<x.getValue()<<endl;
  }
}

int main(int argv, char** argc){
  set<Card> a; //alices cards
  set<Card> b; //bobs cards
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    a.insert(Card(line));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    b.insert(Card(line));
  }
  cardFile2.close();

  game(a,b);
  cout<<endl;
  cout<<"Alice's cards:"<<endl;
  printCards(a);
  cout<<endl;
  cout<<"Bob's cards:"<<endl;
  printCards(b);

  
  return 0;
}

