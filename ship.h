#ifndef SHIP_H
#define SHIP_H

class Ship {

private:
    int size;
    bool isHorizontal;
    int y;  // Ship's starting position
    char x; // Ship's starting position
public:
    int& getSize() {return this->size;}
    bool& getIsHorizontal() {return this->isHorizontal;}
    int& getY() {return this->y;}
    char& getX() {return this->x;}



    Ship(int size);
    ~Ship();
    
    void place(int y, char x, bool isHorizontal);
    
    bool isHit(int hitY, char hitX);
};

#endif