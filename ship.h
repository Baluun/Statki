#ifndef SHIP_H
#define SHIP_H

class Ship {

private:
    int size;
    bool isHorizontal;
    int x;  // Ship's starting position
    char col; // Ship's starting position
public:
    int& getSize() {return this->size;}
    bool& getIsHorizontal() {return this->isHorizontal;}
    int& getX() {return this->x;}
    char& getCol() {return this->col;}



    Ship(int size);
    ~Ship();
    
    void place(int x, char col, bool isHorizontal);
    
    bool isHit(int hitX, char hitCol);
};

#endif
