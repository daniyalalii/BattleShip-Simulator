#ifndef COLORS_H
#define COLORS_H

// Fix for Windows.h and C++17 std::byte conflict
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif

// Include iostream first to establish std::byte
#include <iostream>

// Temporarily undefine byte if defined by C++
#ifdef byte
#undef byte
#endif

#include <windows.h>

// Restore std namespace
using namespace std;

// Global variables for console colors
HANDLE hConsole;
WORD defaultAttr;

void initConsoleColors() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    defaultAttr = csbi.wAttributes;
}

void setColor(WORD attr) { 
    SetConsoleTextAttribute(hConsole, attr); 
}

void resetColor() { 
    SetConsoleTextAttribute(hConsole, defaultAttr); 
}

// Color constants for easy use
const WORD RED_TEXT = FOREGROUND_RED | FOREGROUND_INTENSITY;
const WORD BLUE_TEXT = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const WORD GREEN_TEXT = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const WORD YELLOW_TEXT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const WORD WHITE_TEXT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const WORD GRAY_TEXT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD CYAN_TEXT = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

// Background color constants for filled cells
const WORD BLUE_BACKGROUND = BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD RED_BACKGROUND = BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD GREEN_BACKGROUND = BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD GRAY_BACKGROUND = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

void printColoredChar(char ch) {
    if (ch == 'X') {
        setColor(RED_BACKGROUND); // Red background for hits
        cout << " " << ch << " ";
        resetColor();
    } else if (ch == 'O') {
        setColor(GRAY_BACKGROUND); // Gray background for misses
        cout << " " << ch << " ";
        resetColor();
    } else if (ch == 'S') {
        setColor(GREEN_BACKGROUND); // Green background for ships
        cout << " " << ch << " ";
        resetColor();
    } else if (ch == '~') {
        setColor(BLUE_BACKGROUND); // Blue background for water
        cout << " " << ch << " ";
        resetColor();
    } else {
        cout << " " << ch << " "; // Default color for other characters
    }
}

#endif