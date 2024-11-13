#include "Ship.h"
#include <iostream>

using namespace std;

Ship::Ship(int size) : size(size), x(-1), col(-1), isHorizontal(true) 
{

}

Ship::~Ship() 
{
}

void Ship::place(int x, char col, bool isHorizontal) 
{
    getX() = x;
    getCol() = col;
    getIsHorizontal() = isHorizontal;
}

bool Ship::isHit(int hitX, char hitCol) 
{
    if (isHorizontal) 
    {
        return hitX == x && hitCol >= col && hitCol < col + size;
    } 
    else 
    {
        return hitCol == col && hitX >= x && hitX < x + size;
    }
}

