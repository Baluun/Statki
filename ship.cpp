#include "Ship.h"
#include <iostream>

using namespace std;

Ship::Ship(int size) : size(size), y(-1), x(-1), isHorizontal(true) 
{

}

Ship::~Ship() 
{
}

void Ship::place(int y, char x, bool isHorizontal) 
{
    getY() = y;
    getX() = x;
    getIsHorizontal() = isHorizontal;
}

bool Ship::isHit(int hitY, char hitX) 
{
    if (isHorizontal) 
    {
        return hitY == y && hitX >= x && hitX < x + size;
    } 
    else 
    {
        return hitX == x && hitY >= y && hitY < y + size;
    }
}

