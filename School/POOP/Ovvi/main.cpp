//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor

#include <iostream>
#include <filesystem>
#include <fstream>
#include <ostream>
#include "imp.h"
using namespace std;
//------------------------------------------------------------------------------'

int main() {
    int choice;
    char subchoice;
    cout << "Enter 0 to exit. Choose task (1 - 4): ";
    cin >> choice;
    while(1) {
        switch (choice)
        {
        case 0:
            break;
        case 1:
            {
                cout << "Choose subtask (a - b): ";
                cin >> subchoice;
                switch (subchoice)
                {
                case 'a':
                    {
                        userInputToFile();
                    }
                    break;
                case 'b':
                    {
                        readFromFile();
                    }
                    break;
                default:
                    printf("Valid input pls. You inputted %f", subchoice);
                    cout << endl;
                    break;
                }
            }
            break;
        case 2:
            {
                cout << "Choose subtask (a - b): ";
                cin >> subchoice;
                switch (subchoice)
                {
                case 'a':
                    {
                        countChar();
                    }
                    break;
                case 'b':
                    {
                        string nextLine;
                        ifstream inputStream{"test.txt"};
                        while (getline(inputStream, nextLine)) {
                            cout << nextLine << endl;
                        }
                    }
                    break;
                default:
                    break;
                }
            }
            break;
        case 3:
            {  
            test();
        }
            break;
        case 4:
            {
            vector<Temps> temps = readTemps("temperatures.txt");
            tempStats(temps);
        }
        break;
    }


    return 0;
}
}

//------------------------------------------------------------------------------
