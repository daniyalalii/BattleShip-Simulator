#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include "colors.h"

using namespace std;

const int ships = 5;
const int shipSizes[ships] = {5, 4, 3, 3, 2};
const string shipNames[ships] = {
    "Aircraft Carrier",
    "Battleship",
    "Destroyer",
    "Submarine",
    "Patrol Boat"};

void vsPlayer(char board1[10][10], char board2[10][10], string player1Name, string player2Name);
void updateScore(int &score, bool isHit);
void displayResult(int player1Score, int player2Score);
void clearBoard(char board[10][10]);

void initializeBoard(char board[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            board[i][j] = '~';
        }
    }
}
void printBoard(char board[10][10], bool hideShips)
{
    // // Print top border
    // cout << "   ";
    // for (int j = 0; j < 10; j++)
    // {
    //     if(j==0) continue
    //     cout << "+---";
    // }
    // // cout << "+" << endl;
    // cout<<endl;
    
    for (int i = 0; i < 10; i++)
    {
        if (i == 0)
        {
            cout << "   ";
            for (int j = 0; j < 10; j++)
            {
                cout << " ";
                setColor(CYAN_TEXT);
                cout << j;
                resetColor();
                cout << "  ";
            }
            cout << " " << endl;
            
            cout << "   ";
            for (int j = 0; j < 10; j++)
            {
                cout << "+---";
            }
            cout << "+" << endl;
        }
        
        setColor(CYAN_TEXT);
        cout << i << " ";
        resetColor();
        
        for (int j = 0; j < 10; j++)
        {
            cout << " ";
            if (hideShips && board[i][j] == 'S')
            {
                printColoredChar('~'); 
            }
            else
            {
                printColoredChar(board[i][j]); 
            }
        }
        cout << " " << endl;
        
        cout << "   ";
        for (int j = 0; j < 10; j++)
        {
            cout << "+---";
        }
        cout << "+" << endl;
    }
}

bool canPlaceShipRandom(char board[10][10], int row, int col, int size, bool horizontal)
{
    if (horizontal)
    {
        if (col + size > 10)
            return false;
    }
    else
    {
        if (row + size > 10)
            return false;
    }

    if (horizontal)
    {
        for (int i = -1; i <= size; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int checkRow = row + j;
                int checkCol = col + i;

                if (checkRow < 0 || checkRow >= 10 || checkCol < 0 || checkCol >= 10)
                    continue;

                if (board[checkRow][checkCol] == 'S')
                    return false;
            }
        }
    }
    else
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= size; j++)
            {
                int checkRow = row + j;
                int checkCol = col + i;

                if (checkRow < 0 || checkRow >= 10 || checkCol < 0 || checkCol >= 10)
                    continue;

                if (board[checkRow][checkCol] == 'S')
                    return false;
            }
        }
    }

    return true;
}

void setRandomShips(char board[10][10])
{
    srand(time(0));

    for (int shipIndex = 0; shipIndex < ships; shipIndex++)
    {
        int currentShipSize = shipSizes[shipIndex];
        bool shipPlaced = false;
        int attempts = 0;
        const int maxAttempts = 1000;

        while (!shipPlaced && attempts < maxAttempts)
        {
            int row = rand() % 10;
            int col = rand() % 10;
            bool horizontal = rand() % 2; 

            if (canPlaceShipRandom(board, row, col, currentShipSize, horizontal))
            {
                if (horizontal)
                {
                    for (int j = 0; j < currentShipSize; j++)
                    {
                        board[row][col + j] = 'S';
                    }
                }
                else
                {
                    for (int j = 0; j < currentShipSize; j++)
                    {
                        board[row + j][col] = 'S';
                    }
                }

                shipPlaced = true;
                // cout << "Computer placed " << shipNames[shipIndex]
                //      << " (" << currentShipSize << " blocks) at (" << row << "," << col
                //      << ") " << (horizontal ? "horizontally" : "vertically") << endl;
            }

            attempts++;
        }

        if (!shipPlaced)
        {
            bool found = false;
            for (int r = 0; r < 10 && !found; r++)
            {
                for (int c = 0; c < 10 && !found; c++)
                {
                    if (canPlaceShipRandom(board, r, c, currentShipSize, true))
                    {
                        for (int j = 0; j < currentShipSize; j++)
                        {
                            board[r][c + j] = 'S';
                        }
                        found = true;
                        shipPlaced = true;
                    }
                    else if (canPlaceShipRandom(board, r, c, currentShipSize, false))
                    {
                        for (int j = 0; j < currentShipSize; j++)
                        {
                            board[r + j][c] = 'S';
                        }
                        found = true;
                        shipPlaced = true;
                    }
                }
            }
        }

        if (!shipPlaced)
        {
            cout << "Error: Could not place " << shipNames[shipIndex]<<endl;
        }
    }

    cout << "Computer ship placement complete!" << endl;
}

bool canPlaceShip(char board[10][10], int row, int col, int size, bool horizontal)
{
    if (horizontal)
    {
        if (col + size > 10)
        {
            cout << "Error: Ship goes out of bounds horizontally!" << endl;
            return false;
        }
    }
    else
    {
        if (row + size > 10)
        {
            cout << "Error: Ship goes out of bounds vertically!" << endl;
            return false;
        }
    }

    if (horizontal)
    {
        for (int i = 0; i < size; i++)
        {
            if (board[row][col + i] == 'S')
            {
                cout << "Error: Another ship is already placed at position (" << row << ", " << (col + i) << ")!" << endl;
                return false;
            }
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            if (board[row + i][col] == 'S')
            {
                cout << "Error: Another ship is already placed at position (" << (row + i) << ", " << col << ")!" << endl;
                return false;
            }
        }
    }

    return true;
}

void setShipAt(char board[10][10])
{
    for (int i = 0; i < ships; i++)
    {
        bool shipPlaced = false;
        while (!shipPlaced)
        {
            int horizontal;
            do
            {
                cout << "\n--- Placing ship " << (i + 1) << " of " << ships << " ---" << endl;
                cout << "Current board:" << endl;
                printBoard(board, false);
                cout << "Next ship to place: " << shipNames[i] << " (" << shipSizes[i] << " blocks)" << endl;
                cout << "How do you want to place this ship?" << endl;
                cout << "Horizontal--> 1" << endl;
                cout << "Vertical--> 2" << endl;
                cin >> horizontal;
            } while (horizontal != 1 && horizontal != 2);

            int rowNumber, colNumber;
            cout << "Enter starting rowNumber (0-9): ";
            cin >> rowNumber;
            cout << "Enter starting colNumber (0-9): ";
            cin >> colNumber;

            if (rowNumber < 0 || rowNumber >= 10 || colNumber < 0 || colNumber >= 10)
            {
                cout << "Error: Starting position must be within board bounds (0-9)!" << endl;
                continue;
            }

            int currentShipSize = shipSizes[i];
            if (!canPlaceShip(board, rowNumber, colNumber, currentShipSize, horizontal == 1))
            {
                continue;
            }

            if (horizontal == 1)
            {
                for (int j = 0; j < currentShipSize; j++)
                {
                    board[rowNumber][colNumber + j] = 'S';
                }
            }
            else
            {
                for (int j = 0; j < currentShipSize; j++)
                {
                    board[rowNumber + j][colNumber] = 'S';
                }
            }

            cout << shipNames[i] << " placed successfully!" << endl;
            shipPlaced = true;
        }

        cout << "\nUpdated board:" << endl;
        printBoard(board, false);
        if (i < ships - 1)
        {
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
}

void clearScreen()
{
    system("cls");
}

bool allShipsSunk(char board[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board[i][j] == 'S')
            {
                return false; 
            }
        }
    }
    return true; 
}

void computerShoot(char playerBoard[10][10], int &computerHits, int &computerShots)
{
    int row, col;
    bool validShot = false;

    while (!validShot)
    {
        row = rand() % 10;
        col = rand() % 10;

        if (playerBoard[row][col] != 'X' && playerBoard[row][col] != 'O')
        {
            validShot = true;
        }
    }

    computerShots++;
    cout << "Computer shoots at (" << row << ", " << col << ")" << endl;

    if (playerBoard[row][col] == 'S')
    {
        playerBoard[row][col] = 'X';
        computerHits++;
        cout << "Computer HIT your ship!" << endl;
    }
    else
    {
        playerBoard[row][col] = 'O';
        cout << "Computer MISSED!" << endl;
    }
}

bool playerShoot(char computerBoard[10][10], int &playerHits, int &playerShots)
{
    int row, col;

    cout << "\nYour turn to shoot!" << endl;
    cout << "Enter target row (0-9): ";
    cin >> row;
    cout << "Enter target column (0-9): ";
    cin >> col;

    if (row < 0 || row >= 10 || col < 0 || col >= 10)
    {
        cout << "Invalid coordinates! Please enter values between 0-9." << endl;
        return false;
    }

    if (computerBoard[row][col] == 'X' || computerBoard[row][col] == 'O')
    {
        cout << "You already shot at this position! Try again." << endl;
        return false;
    }

    playerShots++;

    if (computerBoard[row][col] == 'S')
    {
        computerBoard[row][col] = 'X';
        playerHits++;
        cout << "HIT! You hit a computer ship!" << endl;
    }
    else
    {
        computerBoard[row][col] = 'O';
        cout << "MISS! No ship at that location." << endl;
    }

    return true;
}

// Player vs Computer mode
void vsComputer(char playerBoard[10][10], char computerBoard[10][10])
{
    cout << "\n=== BATTLE BEGINS! ===" << endl;
    cout << "Legend: 'S' = Ship, 'X' = Hit, 'O' = Miss, '~' = Water" << endl;

    int playerHits = 0, playerShots = 0;
    int computerHits = 0, computerShots = 0;
    int round = 1;

    while (true)
    {
        cout << "\n"<< string(50, '=') << endl;
        cout << "\t\tROUND " << round << endl;
        cout << string(50, '=') << endl;

        cout << "\nComputer's Board (Your targets):" << endl;
        printBoard(computerBoard, true);

        cout << "\nYour Board:" << endl;
        printBoard(playerBoard, false); 

        cout << "\nScore - You: " << playerHits << " hits/" << playerShots << " shots";
        cout << " | Computer: " << computerHits << " hits/" << computerShots << " shots" << endl;

        bool validShot = false;
        while (!validShot)
        {
            validShot = playerShoot(computerBoard, playerHits, playerShots);
        }

        if (allShipsSunk(computerBoard))
        {
            cout << "\n"<< string(50, '*') << endl;
            cout << "\t\tCONGRATULATIONS! YOU WIN!" << endl;
            cout << "You sunk all computer ships!" << endl;
            cout << "Final Score: " << playerHits << " hits in " << playerShots << " shots";
            double accuracy = (double)playerHits / playerShots * 100;
            cout << " (Accuracy: " << fixed << setprecision(1) << accuracy << "%)" << endl;
            cout << string(50, '*') << endl;
            break;
        }

        cout << "\nPress Enter for computer's turn...";
        cin.ignore();
        cin.get();

        computerShoot(playerBoard, computerHits, computerShots);

        if (allShipsSunk(playerBoard))
        {
            cout << "\n"<< string(50, '-') << endl;
            cout << "\t\tGAME OVER! Computer wins!" << endl;
            cout << "Computer sunk all your ships!" << endl;
            cout << "Computer Score: " << computerHits << " hits in " << computerShots << " shots";
            double compAccuracy = (double)computerHits / computerShots * 100;
            cout << " (Accuracy: " << fixed << setprecision(1) << compAccuracy << "%)" << endl;
            cout << string(50, '-') << endl;
            break;
        }

        cout << "\nPress Enter to continue to next round...";
        cin.ignore();
        cin.get();

        round++;
    }

    cout << "\nFinal Boards:" << endl;
    cout << "\nComputer's Board:" << endl;
    printBoard(computerBoard, false);

    cout << "\nYour Board:" << endl;
    printBoard(playerBoard, false);
}

void clearBoard(char board[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            board[i][j] = '~';
        }
    }
}

void updateScore(int &score, bool isHit)
{
    if (isHit)
    {
        score += 10;
    }
    else
    {
        score -= 1;
    }
}

void displayResult(int player1Score, int player2Score)
{
    cout << "\n"
         << string(60, '=') << endl;
    cout << "FINAL RESULTS" << endl;
    cout << string(60, '=') << endl;
    cout << "Player 1 Final Score: " << player1Score << " points" << endl;
    cout << "Player 2 Final Score: " << player2Score << " points" << endl;
    cout << string(60, '-') << endl;

    if (player1Score > player2Score)
    {
        cout << "PLAYER 1 WINS! " << endl;
        cout << "Victory margin: " << (player1Score - player2Score) << " points" << endl;
    }
    else if (player2Score > player1Score)
    {
        cout << " PLAYER 2 WINS!" << endl;
        cout << "Victory margin: " << (player2Score - player1Score) << " points" << endl;
    }
    else
    {
        cout << "IT'S A DRAW!" << endl;
        cout << "Both players scored equally!" << endl;
    }
    cout << string(60, '=') << endl;
}

bool playerShootPvP(char opponentBoard[10][10], int playerNum, int &playerHits, int &playerShots, int &playerScore)
{
    int row, col;

    cout << "\nPlayer " << playerNum << "'s turn to shoot!" << endl;
    cout << "Enter target row (0-9): ";
    cin >> row;
    cout << "Enter target column (0-9): ";
    cin >> col;

    if (row < 0 || row >= 10 || col < 0 || col >= 10)
    {
        cout << "Invalid coordinates! Please enter values between 0-9." << endl;
        return false;
    }

    if (opponentBoard[row][col] == 'X' || opponentBoard[row][col] == 'O')
    {
        cout << "You already shot at this position! Try again." << endl;
        return false;
    }

    playerShots++;

    if (opponentBoard[row][col] == 'S')
    {
        // Hit!
        opponentBoard[row][col] = 'X';
        playerHits++;
        updateScore(playerScore, true);
        cout << "HIT! You hit Player " << (3 - playerNum) << "'s ship! (+10 points)" << endl;
    }
    else
    {
        opponentBoard[row][col] = 'O';
        updateScore(playerScore, false);
        cout << " MISS! No ship at that location. (-1 point)" << endl;
    }

    cout << "Current Score: " << playerScore << " points" << endl;
    return true;
}

// Player vs Player mode
void vsPlayer(char board1[10][10], char board2[10][10], string player1Name, string player2Name)
{
    cout << "\n=== " << player1Name << " VS " << player2Name << " BATTLE! ===" << endl;
    cout << "Legend: 'S' = Ship, 'X' = Hit , 'O' = Miss , '~' = Water" << endl;
    cout << "Scoring: Hit = +10 points, Miss = -1 point" << endl;

    int player1Hits = 0, player1Shots = 0, player1Score = 0;
    int player2Hits = 0, player2Shots = 0, player2Score = 0;
    int round = 1;

    while (true)
    {
        cout << "\n"
             << string(60, '=') << endl;
        cout << "ROUND " << round << endl;
        cout << string(60, '=') << endl;

        // Show current scores
        cout << "Scores - " << player1Name << ": " << player1Score << " points | " << player2Name << ": " << player2Score << " points" << endl;

        // Player 1's turn
        cout << "\n--- " << player1Name.substr(0, min((int)player1Name.length(), 15)) << "'S TURN ---" << endl;
        cout << player2Name << "'s Board (your targets):" << endl;
        printBoard(board2, true);

        bool validShot = false;
        while (!validShot)
        {
            validShot = playerShootPvP(board2, 1, player1Hits, player1Shots, player1Score);
        }

        // Check if Player 1 wins
        if (allShipsSunk(board2))
        {
            cout << "\n"
                 << string(50, '*') << endl;
            cout << player1Name.substr(0, min((int)player1Name.length(), 20)) << " WINS BY SINKING ALL SHIPS!" << endl;
            cout << string(50, '*') << endl;
            displayResult(player1Score, player2Score);
            break;
        }

        cout << "\nPress Enter for " << player2Name << "'s turn...";
        cin.ignore();
        cin.get();

        // Player 2's turn
        cout << "\n--- " << player2Name.substr(0, min((int)player2Name.length(), 15)) << "'S TURN ---" << endl;
        cout << player1Name << "'s Board (your targets):" << endl;
        printBoard(board1, true);

        validShot = false;
        while (!validShot)
        {
            validShot = playerShootPvP(board1, 2, player2Hits, player2Shots, player2Score);
        }

        // Check if Player 2 wins
        if (allShipsSunk(board1))
        {
            cout << "\n"
                 << string(50, '*') << endl;
            cout << "🎉 " << player2Name.substr(0, min((int)player2Name.length(), 20)) << " WINS BY SINKING ALL SHIPS! 🎉" << endl;
            cout << string(50, '*') << endl;
            displayResult(player1Score, player2Score);
            break;
        }

        cout << "\nPress Enter to continue to next round...";
        cin.ignore();
        cin.get();

        round++;
    }

    cout << "\nFinal Boards:" << endl;
    cout << "\n" << player1Name << "'s Board:" << endl;
    printBoard(board1, false);
    cout << "\n" << player2Name << "'s Board:" << endl;
    printBoard(board2, false);
}

void setRandomShipsQuiet(char board[10][10])
{
    srand(time(0));

    for (int shipIndex = 0; shipIndex < ships; shipIndex++)
    {
        int currentShipSize = shipSizes[shipIndex];
        bool shipPlaced = false;
        int attempts = 0;
        const int maxAttempts = 1000;

        while (!shipPlaced && attempts < maxAttempts)
        {
            int row = rand() % 10;
            int col = rand() % 10;
            bool horizontal = rand() % 2;
            if (canPlaceShipRandom(board, row, col, currentShipSize, horizontal))
            {
                if (horizontal)
                {
                    for (int j = 0; j < currentShipSize; j++)
                    {
                        board[row][col + j] = 'S';
                    }
                }
                else
                {
                    for (int j = 0; j < currentShipSize; j++)
                    {
                        board[row + j][col] = 'S';
                    }
                }

                shipPlaced = true;
            }

            attempts++;
        }

        if (!shipPlaced)
        {
            bool found = false;
            for (int r = 0; r < 10 && !found; r++)
            {
                for (int c = 0; c < 10 && !found; c++)
                {
                    if (canPlaceShipRandom(board, r, c, currentShipSize, true))
                    {
                        for (int j = 0; j < currentShipSize; j++)
                        {
                            board[r][c + j] = 'S';
                        }
                        found = true;
                        shipPlaced = true;
                    }
                    else if (canPlaceShipRandom(board, r, c, currentShipSize, false))
                    {
                        for (int j = 0; j < currentShipSize; j++)
                        {
                            board[r + j][c] = 'S';
                        }
                        found = true;
                        shipPlaced = true;
                    }
                }
            }
        }

        if (!shipPlaced)
        {
            cout << "Error: Could not place " << shipNames[shipIndex]
                 << ". Board may be too crowded." << endl;
        }
    }
}

#endif