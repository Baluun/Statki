#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
using namespace std;
Player::Player(string name)
{
    cout << "Podaj nazwe gracza: " << name << endl;
    getline(cin, this->name);
    cout << endl;
}

Player::~Player()
{

}
void Player::placeShips()
{
    cout << name << ", czy chcesz rozmieszczać statki ręcznie (1) czy automatycznie (2)? ";
    int choice;
    cin >> choice;
    cout << endl;

    int sizes[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}; // Rozmiary statków

    if(choice == 2)
    {
        srand(time(0)); // Inicjalizacja generatora liczb pseudolosowych

        for(int i = 0; i < 10; i++)
        {
            Ship ship(sizes[i]);
            bool placed = false;

            while(!placed)
            {
                int x = rand() % 10; // Losowa kolumna
                int y = rand() % 10; // Losowy wiersz
                bool isHorizontal = rand() % 2; // Losowa orientacja (0 = pionowo, 1 = poziomo)

                if(getOwnBoard().canPlaceShip(y, x, sizes[i], isHorizontal, false))
                {
                    getOwnBoard().placeShip(ship, y, x, isHorizontal);
                    placed = true;
                }
            }
        }
        getOwnBoard().displayBoard(getTargetBoard());
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            Ship ship(sizes[i]);
            int y;
            int isHorizontal = 1;
            char x;
            do
            {
                do
                {
                    cout << name << " ustaw statek o rozmiarze: " << sizes[i] << endl;
                    if (sizes[i] == 1)
                    {
                        cout << "Podaj współrzędne (kolumna A-J spacja, wiersz 1-10): ";
                        cin >> x >> y;
                        x = toupper(x);
                        isHorizontal = 1; // Domyślna orientacja dla jednomasztowców
                    }
                    else
                    {
                        cout << "Podaj współrzędne (kolumna A-J spacja, wiersz 1-10 spacja) i orientację (1-poziomo, 0-pionowo): ";
                        cin >> x >> y >> isHorizontal;
                        x = toupper(x);
                    }
                }
                while (!getOwnBoard().validateShipPositionInput(x, y, isHorizontal));

                x = x - 'A';  // Konwersja litery na indeks
                y--;          // Adaptacja do indeksów tablicy
            }
            while (!getOwnBoard().canPlaceShip(x, y, sizes[i], isHorizontal, true));

            getOwnBoard().placeShip(ship, x, y, isHorizontal);
            getOwnBoard().displayBoard(getTargetBoard());
        }
    }
}

bool Player::takeTurn(Player& opponent)
{
    int y;
    char x ;
    do
    {
        do
        {
            cout << name << " podaj współrzędne strzału (kolumna A-J, wiersz 1-10): ";
            cin >> x >> y;
            x = toupper(x);
        }
        while(getTargetBoard().validateShotInput(x, y) == false);

        x = x - 'A';
        y--;
    }
    while(getTargetBoard().isShotAgain(x, y) == false);
    if(opponent.getOwnBoard().checkHit(x, y))
    {
        cout << "========================================" << endl;
        cout << "Trafiony!" << endl;
        cout << "========================================" << endl;
        ::Beep(1000,500);
        getTargetBoard().hitOrMiss(x, y, true);
        opponent.getOwnBoard().hitOrMiss(x, y, true);
        if(opponent.getOwnBoard().checkIfShipSunk(x,y))
        {

            cout << "========================================" << endl;
            cout << "Statek został zniszcony" << endl;
            cout << "========================================" << endl;
            ::Beep(600,700);
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
            cout << "========================================" << endl;
            cout << "Statek nie został zniszcony" << endl;
            cout << "========================================" << endl;
        }
        return true;
    }
    else
    {
        cout << "========================================" << endl;
        cout << "Pudło!" << endl;
        cout << "========================================" << endl;
        ::Beep(400,300);
        getTargetBoard().hitOrMiss(x, y, false);
        return false;
    }
}


