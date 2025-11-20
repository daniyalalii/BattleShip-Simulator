#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include<iostream>
#include<iomanip>
using namespace std;

void viewInstructions(){
    cout<<"-------------------------------------"<<endl;
    cout<<setw(25)<<"Instructions"<<endl;
    cout<<"-------------------------------------"<<endl;
    cout<<"1. Place Your Ships on the board"<<endl;
    cout<<"2. You and Computer take turn firing shots"<<endl;
    cout<<"3. \'O\' means MISS, \'X means HIT\'"<<endl;
    cout<<"4. Sink all enemy ships to win"<<endl;
    cout<<"5. Your score is based on accuracy and speed"<<endl;
    cout<<"-------------------------------------"<<endl;
}

#endif