#include <iostream>
#include "Player.cpp"
#include "Board.cpp"
#include "Ship.cpp"
using namespace std;

int main()
{
    Player player1("Gracz 1");
    Player player2("Gracz 2");

    int player1Wins = 0;
    int player2Wins = 0;
    bool playAgain = true;

    while(playAgain) 
    {
        cout << player1.getName() << " rozmieszcza statki" << endl;
        player1.getOwnBoard().displayBoard(player1.getTargetBoard());
        player1.placeShips();
        cout << "\033[2J\033[1;1H";

        cout << player2.getName() << " rozmieszcza statki" << endl;
        player2.getOwnBoard().displayBoard(player1.getTargetBoard());
        player2.placeShips();
        cout << "\033[2J\033[1;1H";

        bool player1Turn = true;
        bool gameOn = true;

        while(gameOn)
        {
            if(player1Turn) 
            {
                cout << "Strzela " << player1.getName() << ": " << endl;
                player1.getOwnBoard().displayBoard(player1.getTargetBoard());
                if(!player1.takeTurn(player2)) 
                {
                    player1Turn = false;
                    cout << "\033[2J\033[1;1H";
                }
                if(player2.getOwnBoard().allShipsSunk())     
                {
                    cout << player1.getName() << " wygrywa!" << endl;
                    player1Wins++;
                    gameOn = false;
                }
            } 
            else 
            {
                cout << " Strzela " << player2.getName() << ": " << endl;
                player2.getOwnBoard().displayBoard(player2.getTargetBoard());
                if(!player2.takeTurn(player1)) 
                {
                    player1Turn = true;
                    cout << "\033[2J\033[1;1H";
                }
                if(player1.getOwnBoard().allShipsSunk()) 
                {
                    cout << player2.getName() << " wygrywa!" << endl;
                    player2Wins++;
                    gameOn = false;
                }
            }
        }

        cout << player1.getName() << ": " << player1Wins << " wygranych" << endl;
        cout << player1.getName() << ": " << player2Wins << " wygranych" << endl;

        string choice;
        cout << "Czy chcesz zagrać ponownie? (yes/no): ";
        cin >> choice;
        if(choice == "no") 
        {
           playAgain = false;
        }        
    }

    return 0;
}
