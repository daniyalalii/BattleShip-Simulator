#include "instructions.h"
#include "game.h"
#include "colors.h"

void startGame();
int getShipPlacementChoice(string playerName);

void menu()
{
    int choice;
    do
    {
        setColor(BLUE_TEXT);
        cout << "=================================" << endl;
        cout << "    " << "WELCOME TO BATTLESHIP GAME" << endl;
        cout << "=================================" << endl;
        resetColor();
        
        setColor(YELLOW_TEXT);
        cout << "\n"<< setw(20) << "MAIN MENU" << endl;
        resetColor();
        
        setColor(CYAN_TEXT);
        cout << "----------------------------------" << endl;
        cout << "1. Start New Game" << endl;
        cout << "2. View Instructions" << endl;
        cout << "3. View LeaderBoard" << endl;
        cout << "4. Exit" << endl;
        cout << "----------------------------------" << endl;
        resetColor();
        
        cout << "\n\nEnter Your Choice (1-4)" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            startGame();
            break;
        }
        case 2:
        {
            viewInstructions();
            break;
        }
        case 3:
        {
            // viewLeaderboard();
            break;
        }
        case 4:
        {
            cout << "-----------------------------------------" << endl;
            cout << "Thank You for using BattleShip Simulator" << endl;
            cout << "-----------------------------------------" << endl;
            break;
        }
        default:{
            cout<<"Enter Correct Input!"<<endl;
        }
        }
    } while (choice != 4);
}

void startGame()
{
    setColor(GREEN_TEXT);
    cout << "=== BATTLESHIP SIMULATOR ===" << endl;
    resetColor();
    cout << "Welcome to the ultimate naval battle!" << endl;

    
    int gameMode;
    do {
        cout << "\nSelect Game Mode:" << endl;
        cout << "1. Player vs Computer" << endl;
        cout << "2. Player vs Player" << endl;
        cout << "Enter your choice (1 or 2): ";
        cin >> gameMode;
    } while (gameMode != 1 && gameMode != 2);
    
    if (gameMode == 1) {
        // Player vs Computer mode
        char playerBoard[10][10];
        char computerBoard[10][10];
        string playerName;

        do {
            cout << "Enter your name: ";
            cin.ignore(); 
            getline(cin, playerName);
            if (playerName.empty()) {
                cout << "Please enter a valid name!" << endl;
            }
        } while (playerName.empty());

        initializeBoard(computerBoard);
        initializeBoard(playerBoard);
        
        cout << "\nComputer is placing ships..." << endl;
        setRandomShips(computerBoard);
        
        int placementChoice = getShipPlacementChoice(playerName);

        if (placementChoice == 1) {
            cout << "\nNow it's your turn to place ships manually!" << endl;
            setShipAt(playerBoard);
        } else {
            cout << "\nPlacing your ships randomly..." << endl;
            setRandomShipsQuiet(playerBoard);
            cout << "Your ships have been placed!" << endl;
            cout << "\nYour board:" << endl;
            printBoard(playerBoard, false);
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
        
        clearScreen();
        vsComputer(playerBoard, computerBoard);
    }
    else {
        // Player vs Player mode
        char player1Board[10][10];
        char player2Board[10][10];
        string player1Name;
        string player2Name;
        
        do {
            cout << "Enter Player 1's name: ";
            cin.ignore(); 
            getline(cin, player1Name);
            if (player1Name.empty()) {
                cout << "Please enter a valid name!" << endl;
            }
        } while (player1Name.empty());
        
        do {
            cout << "Enter Player 2's name: ";
            getline(cin, player2Name);
            if (player2Name.empty()) {
                cout << "Please enter a valid name!" << endl;
            }
        } while (player2Name.empty());
        
        initializeBoard(player1Board);
        initializeBoard(player2Board);
        
        // Player 1 ship placement
        int player1Choice = getShipPlacementChoice(player1Name);
        if (player1Choice == 1) {
            cout << "\n" << player1Name << ", place your ships manually!" << endl;
            setShipAt(player1Board);
        } else {
            cout << "\n" << player1Name << ", placing your ships randomly..." << endl;
            setRandomShipsQuiet(player1Board);
            cout << player1Name << "'s ships have been placed!" << endl;
            cout << "\n" << player1Name << "'s board:" << endl;
            printBoard(player1Board, false);
            cout << "Press Enter to continue to Player 2...";
            cin.ignore();
            cin.get();
        }
        
        clearScreen();

        // Player 2 ship placement
        int player2Choice = getShipPlacementChoice(player2Name);
        if (player2Choice == 1) {
            cout << "\n" << player2Name << ", place your ships manually!" << endl;
            setShipAt(player2Board);
        } else {
            cout << "\n" << player2Name << ", placing your ships randomly..." << endl;
            setRandomShipsQuiet(player2Board);
            cout << player2Name << "'s ships have been placed!" << endl;
            cout << "\n" << player2Name << "'s board:" << endl;
            printBoard(player2Board, false);
            cout << "Press Enter to start the battle...";
            cin.ignore();
            cin.get();
        }
        
        clearScreen();
        vsPlayer(player1Board, player2Board, player1Name, player2Name);
    }
    
    cout << "\nThank you for playing Battleship!" << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

int getShipPlacementChoice(string playerName) {
    int choice;
    do {
        cout << "\n" << playerName << ", how would you like to place your ships?" << endl;
        cout << "1. Place ships manually" << endl;
        cout << "2. Place ships randomly (automatic)" << endl;
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "Invalid choice! Please enter 1 or 2." << endl;
        }
    } while (choice != 1 && choice != 2);
    return choice;
}

int main()
{
    // Initialize console colors
    initConsoleColors();
    
    menu();
    return 0;
}