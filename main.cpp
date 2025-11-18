#include "instructions.h"
using namespace std;

void menu()
{
    int choice;
    do
    {
        cout << "=================================" << endl;
        cout << "    " << "WELCOME TO BATTLESHIP GAME" << endl;
        cout << "=================================" << endl;
        cout << "\n"<< setw(20) << "MAIN MENU" << endl;
        cout << "----------------------------------" << endl;
        cout << "1. Start New Game" << endl;
        cout << "2. View Instructions" << endl;
        cout << "3. View LeaderBoard" << endl;
        cout << "4. Exit" << endl;
        cout << "----------------------------------" << endl;
        cout << "\n\nEnter Your Choice (1-4)" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            // StartGame();
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

int main()
{
    menu();
    return 0;
}