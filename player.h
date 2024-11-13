#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include <iostream>
using namespace std;

class Player {
private:
    Board ownBoard;
    Board targetBoard;
    string name;
public:
   
    Board& getOwnBoard() {return this->ownBoard;}
    Board& getTargetBoard() {return this->targetBoard;}
    string& getName() {return this->name;}

    Player(string name);
    ~Player();
    
    void placeShips();
    
    bool takeTurn(Player& opponent);
};

#endif