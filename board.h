#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include "Player.h"
#include <iostream>

class Board
{
private:
    char grid[10][10];
    bool checked[10][10];
    Ship* ships[10];  // Maximum 10 ships
    int numShips;

public:
    
    char (*getGrid())[10] {return this->grid;}
    int& getNumShips() {return this->numShips;}
    
    
    Board();
    ~Board();
    
    void displayBoard(Board targetBoard);

    bool canPlaceShip(int y, int x, int size, bool isHorizontal);

    void placeShip(Ship& ship, int x, int y, bool isHorizontal);

    bool checkHit(int x, int y);

    void hitOrMiss(int x, int y, bool isHit);

    bool checkIfShipSunk(int x, int y);

    bool checkIfShipSunkRecursive(int x, int y, bool checked[10][10]);

    bool allShipsSunk();

    bool validateShipPositionInput(char colInput, int rowInput , int orientation);

    bool validateShotInput(char colInput, int rowInput);

    bool isShotAgain(int x, int y);

    void markSurroundingAsMisses(int x, int y);

    void decreaseNumOfShips();

    bool isCellInCheckedAndGrid(int i, int j);

};

#endif