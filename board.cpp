#include "board.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

Board::Board() {

    for(int i = 0; i < 10; i++) 
    {
        for(int j = 0; j < 10; j++) 
        {
            grid[i][j] = '~';  // Water
        }
    }

    numShips = 0;
}

Board::~Board()
{

}

void Board::displayBoard(Board targetBoard) 
{
    cout << "Twoja plansza"   << "          Plansza przeciwnika: "  << endl;
    cout << "  1 2 3 4 5 6 7 8 9 10        1 2 3 4 5 6 7 8 9 10" << endl;  // Column headings

    for(int i = 0; i < 10; i++) 
    {
        cout << char('A' + i) << " ";  // Row headings (letters A-J)

        // Displaying the player board
        for(int j = 0; j < 10; j++)
        {
            cout << grid[i][j] << " ";  // View board status
        }
        
        cout << "        ";  // Spacing between boards

        // Displaying the opponent's board
        for(int j = 0; j < 10; j++) 
        {
            if(targetBoard.grid[i][j] == 'S') 
            {
                cout << "~ ";  // Hide ships
            } 
            else 
            {
                cout << targetBoard.grid[i][j] << " ";  // View board status
            }
        }
        cout << endl;  // A new line after each line
    }
    }

bool Board::canPlaceShip(int y, int x, int size, bool isHorizontal) 
{
    // Check for horizontal ship (changes column `x`)
    if(isHorizontal) 
    {
        // Check that the ship fits horizontally on the board
        if (x + size > 10) 
        {
            cout << "Statek wychodzi poza plansze" << endl;
            return false;
        }
        // Iterate through each square where the ship is to be placed
        for(int i = 0; i < size; i++) 
        {
            int currentCol = x + i;    // The column changes in subsequent steps
            int currentRow = y;        // The government remains the same
            // Check if the main field is free
            if(grid[currentRow][currentCol] == 'S') 
            {
                cout << "Statek nachodzi na inny statek" << endl;
                return false;
            }

            // Checking all eight adjacent squares
            int directions[8][2] = {
                {-1, -1}, {-1, 0}, {-1, 1}, // Top: left-top, center, right-top
                {0, -1},          {0, 1},   // Sides: left, right
                {1, -1}, {1, 0}, {1, 1}     // Bottom: left-bottom, center, right-bottom
            };

            for(auto &dir : directions) 
            {
                int neighborRow = currentRow + dir[0];
                int neighborCol = currentCol + dir[1];
                
                // Check if the neighbor is within the boundaries of the board and if he is occupied
                if(neighborRow >= 0 && neighborRow < 10 && neighborCol >= 0 && neighborCol < 10)
                {
                    if(grid[neighborRow][neighborCol] == 'S') 
                    {
                        cout << "Statek styka sie z innym statkiem" << endl;
                        return false;
                    }

                }
            }   
        } 
    }
    // Check for vertical ship (changes row `y`)
    else 
    {
        // Check if the ship fits vertically on the board
        if(y + size > 10) 
        {
            cout << "Statek wychodzi poza plansze" << endl;
            return false;
        }

        // Iterate through each square where the ship is to be placed
        for(int i = 0; i < size; i++) 
        {
            int currentRow = y + i;    // The government changes in successive steps
            int currentCol = x;        // The column remains the same

            // Check if the main field is free
            if(grid[currentRow][currentCol] == 'S') 
            {
                cout << "Statek nachodzi na inny statek" << endl;
                return false;
            }
            // Checking all eight adjacent squares
            int directions[8][2] = {
                {-1, -1}, {-1, 0}, {-1, 1}, // Top: left-top, center, right-top
                {0, -1},          {0, 1},   // Sides: left, right
                {1, -1}, {1, 0}, {1, 1}     // Bottom: left-bottom, center, right-bottom
            };

            for(auto &dir : directions)
            {
                int neighborRow = currentRow + dir[0];
                int neighborCol = currentCol + dir[1];
                
                // Check if the neighbor is within the boundaries of the board and if he is occupied
                if(neighborRow >= 0 && neighborRow < 10 && neighborCol >= 0 && neighborCol < 10) 
                {
                    if(grid[neighborRow][neighborCol] == 'S') 
                    {
                        cout << "Statek styka sie z innym statkiem" << endl;
                        return false;
                    }
                }
            }
        }

    }
    return true; // If no adjacent space is occupied, a ship may be placed
    
}

void Board::placeShip(Ship& ship, int x, int y, bool isHorizontal)
{
    ship.place(x, y, isHorizontal);
    ships[numShips++] = &ship;

    if(isHorizontal)
    {
        for(int i = 0; i < ship.getSize(); i++)
        {
            grid[x][y + i] = 'S';  // Placing the ship horizontally
        }
    }
    else
    {
        for(int i = 0; i < ship.getSize(); i++)
        {
            grid[x + i][y] = 'S';  // Placing the ship vertically
        }
    }
}

bool Board::checkHit(int x, int y) {

        if(x < 0 || x >= 10 || y < 0 || y >= 10) 
        {
            return false; // Off the board
        }

        return grid[x][y] == 'S'; // Check if the field contains a ship

}

void Board::hitOrMiss(int x, int y, bool isHit) 
{

        if(isHit) 
        {

            grid[x][y] = 'X'; // 'X' means hit

        } 
        else 
        {

            grid[x][y] = 'O'; // 'O' stands for box

        }

}

bool Board::checkIfShipSunk(int x, int y) 
{
    // Initializing the array of checked fields
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++) 
        {
            checked[i][j] = false;
        }
    }
    bool isDestroyed = checkIfShipSunkRecursive(x, y, checked);
    if(isDestroyed)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::checkIfShipSunkRecursive(int x, int y, bool checked[10][10]) 
{
    // Checking whether the field has already been checked
    if(checked[x][y]) 
    {
        return true;
    }

    // Mark the field as checked
    checked[x][y] = true;

    // Four directions: up, down, left, right
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool allNeighborsSunk = true;

    for(auto& dir : directions) 
    {
        int neighborRow = x + dir[0];
        int neighborCol = y + dir[1];

        // Checking if the neighbor is within the boundaries of the board
        if(neighborRow >= 0 && neighborRow < 10 && neighborCol >= 0 && neighborCol < 10) 
        {
            char neighborCell = grid[neighborRow][neighborCol];

            if(neighborCell == 'S') 
            {
                // If a missing piece of the ship is found, we stop checking
                allNeighborsSunk = false;
            } 
            else if(neighborCell == 'X' && !checked[neighborRow][neighborCol]) 
            {
                // If there is a hit that has not been checked yet, call recursively for that field
                allNeighborsSunk = allNeighborsSunk && checkIfShipSunkRecursive(neighborRow, neighborCol, checked);
            } 
            else if(neighborCell == '~' || neighborCell == 'O')
            {
                // If an empty square or box is encountered, continue to the next direction
                continue;
            }
        }
    }

    // If the function has passed through all its neighbors and found no missing fragment, the ship is sunk
    return allNeighborsSunk;
}

void Board::markSurroundingAsMisses(int x, int y) 
{
    // We define eight possible directions around the flooded field
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},  // Top: left-top, center, right-top
        {0, -1},          {0, 1},    // Left and right
        {1, -1}, {1, 0}, {1, 1}      // Bottom: left-bottom, center, right-bottom
    };

    // We iterate through each direction
    for(auto& dir : directions) 
    {
        int neighborCol = x + dir[0];
        int neighborRow = y + dir[1];

        // We check whether the neighbor is within the borders of the board
        if(neighborRow >= 0 && neighborRow < 10 && neighborCol >= 0 && neighborCol < 10) 
        {
            // If the box is water (~), we mark it as a box
            if(grid[neighborCol][neighborRow] == '~') 
            {
                grid[neighborCol][neighborRow] = 'O'; // Box
            }
        }
    }
}

bool Board::allShipsSunk()
{
    if(numShips == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::validateShipPositionInput(char colInput, int rowInput, int orientation) {
    // Checking if the first character (line) is a letter from 'A' to 'J'
    if (cin.fail() || colInput < 'A' || colInput > 'J') 
    {
        cout << "Błędne dane, podaj jeszcze raz" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    // Checking if a column (number) is in the range 1 to 10
    if (cin.fail() || rowInput < 1 || rowInput > 10) 
    {
        cout << "Błędne dane, podaj jeszcze raz" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    // Checking if the orientation is correct (0 for portrait, 1 for landscape)
    if (cin.fail() || orientation != 0 && orientation != 1) 
    {
        cout << "Błędne dane, podaj jeszcze raz" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    // If everything is correct
    return true;
}

bool Board::validateShotInput(char colInput, int rowInput) 
{
    // Checking if the first character (line) is a letter from 'A' to 'J'
    if (cin.fail() || colInput < 'A' || colInput > 'J') 
    {
        cout << "Błędne dane, podaj jeszcze raz" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    // Check if the column (number) is in the range 1 to 10
    if (cin.fail() || rowInput < 1 || rowInput > 10) 
    {
        cout << "Błędne dane, podaj jeszcze raz" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    // If everything is correct
    return true;
}
bool Board::isShotAgain(int x, int y)
{
    if(grid[x][y] == 'X' || grid[x][y] == 'O')
    {
        cout << "Już strzelałeś w to miejsce, wybierz inne" << endl;
        return false;
    }
    else
    {
        return true;
    }
}

void Board::decreaseNumOfShips()
{
    numShips--;
}

bool Board::isCellInCheckedAndGrid(int i, int j)
{
    if(checked[i][j] && grid[i][j] == 'X')
    {
        return true;
    }
    else
    {
        return false;
    }
}
