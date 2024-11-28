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
        cout << "Naciśnij enter, aby kontynuować i przejść do rozmieszczania statków gracza " << player2.getName() << "." << endl;
        cin.ignore();
        cin.get();  // Pauza na wprowadzenie dowolnego klawisza
        cout << "\033[2J\033[1;1H";  // Czyszczenie ekranu

        cout << player2.getName() << " rozmieszcza statki" << endl;
        player2.getOwnBoard().displayBoard(player1.getTargetBoard());
        player2.placeShips();
        cout << "\033[2J\033[1;1H";
        cout << "Naciśnij enter, aby kontynuować i przejść tury gracza " << player1.getName() << "." << endl;
        cin.ignore();
        cin.get();  // Pauza na wprowadzenie dowolnego klawisza
        cout << "\033[2J\033[1;1H";  // Czyszczenie ekranu

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
                    player1.getOwnBoard().displayBoard(player1.getTargetBoard());
                    player1Turn = false;
                    cout << "Naciśnij enter aby, wyczyścic konsole" << endl;
                    cin.ignore();
                    cin.get();
                    cout << "\033[2J\033[1;1H";
                    cout << "Naciśnij enter, aby kontynuować i przejść do tury gracza " << player2.getName() << "." << endl;
                    cin.get();  // Pauza na wprowadzenie dowolnego klawisza
                    cout << "\033[2J\033[1;1H";  // Czyszczenie ekranu
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
                    player2.getOwnBoard().displayBoard(player2.getTargetBoard());
                    player1Turn = true;
                    cout << "Naciśnij enter aby, wyczyścić konsole" << endl;
                    cin.ignore();
                    cin.get();
                    cout << "\033[2J\033[1;1H";
                    cout << "Naciśnij enter, aby kontynuować i przejść do tury gracza " << player1.getName() << "." << endl;
                    cin.get();  // Pauza na wprowadzenie dowolnego klawisza
                    cout << "\033[2J\033[1;1H";  // Czyszczenie ekranu
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
        cout << player2.getName() << ": " << player2Wins << " wygranych" << endl;

        string choice;
        cout << "Czy chcesz zagrać ponownie? (yes/no): ";
        cin >> choice;
        if(choice == "no") 
        {
           playAgain = false;
        }
        player1.getOwnBoard().resetBoard();
        player1.getTargetBoard().resetBoard();
        player2.getOwnBoard().resetBoard();
        player2.getTargetBoard().resetBoard(); 
        player1.getOwnBoard().setNumberOfShipsZero();
        player1.getTargetBoard().setNumberOfShipsZero();
        player2.getOwnBoard().setNumberOfShipsZero();
        player2.getTargetBoard().setNumberOfShipsZero();

    }

    return 0;
}
