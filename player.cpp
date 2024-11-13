#include "Player.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Player::Player(string name)
{
    cout << "Podaj nazwe gracza: " << name << endl;
    cin >> getName();
}

Player::~Player() 
{
    
}
void Player::placeShips() 
{
    int sizes[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    for(int i = 0; i < 10; i++) 
    {
        Ship ship(sizes[i]);
        int x, y;
        int isHorizontal;
        char col;
        do
        {
            do
            {
                cout << name << " ustaw statek o rozmiarze: " << sizes[i] << endl;
                cout << "Podaj współrzędne (kolumna A-J spacja, wiersz 1-10 spacja,) i orientację (1 - poziomo, 0 - pionowo): ";
                cin >> col >> y >> isHorizontal;
            }
            while(!getOwnBoard().validateShipPositionInput(col, y, isHorizontal));
            
            x = col - 'A';  // Converting a letter to an index
            y--;  // Adapting to an array index
        } 
        while(!getOwnBoard().canPlaceShip(x, y, sizes[i], isHorizontal));
        getOwnBoard().placeShip(ship, x, y, isHorizontal);
        getOwnBoard().displayBoard(getTargetBoard());
    }
}

bool Player::takeTurn(Player& opponent) 
{
    int x, y;
    char col;
    do
    {
        do
        {
            cout << name << " podaj współrzędne strzału (kolumna A-J, wiersz 1-10): ";
            cin >> col >> y;
        }
        while(getTargetBoard().validateShotInput(col, y) == false);
        
        x = col - 'A';
        y--;
    }
    while(getTargetBoard().isShotAgain(x, y) == false);
    if(opponent.getOwnBoard().checkHit(x, y)) 
    {
        cout << "Trafiony!" << endl;
        getTargetBoard().hitOrMiss(x, y, true);
        opponent.getOwnBoard().hitOrMiss(x, y, true);
        if(opponent.getOwnBoard().checkIfShipSunk(x,y))
        {
            
            cout << "Statek został zniszcony" << endl;
            opponent.getOwnBoard().decreaseNumOfShips();
            for(int i = 0; i < 10; i++) 
            {
                for(int j = 0; j < 10; j++) 
                {
                    if(opponent.getOwnBoard().isCellInCheckedAndGrid(i, j))
                    {
                        getTargetBoard().markSurroundingAsMisses(i, j);  // Mark adjacent squares around the hit
                    }
                    
                }
            }
        }
        else
        {
            cout << "Statek nie został zniszcony" << endl;
        }
        return true;
    } 
    else 
    {
        cout << "Pudło!" << endl;
        getTargetBoard().hitOrMiss(x, y, false);
        return false;
    }
}

