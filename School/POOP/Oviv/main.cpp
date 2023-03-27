#include "std_lib_facilities.h"
#include "test.h"
#include "utilities.h"
//------------------------------------------------------------------------------'



int main() {
    Student student;
    student.name = "Bitch Bitchington";
    student.studyProgram = "MTBitchTek";
    student.age = 69;

    int num;
    cout << "1) Oppgave 1a) \n"
    << "2) Oppgave 1c - testCallByValue)\n" 
    << "3) Oppgave 1d - incrementByValueNumTimesRef\n"
    << "4) Oppgave 1e - swapNumbers()\n"
    << "5) Oppgave 2b - printStudent()\n"
    << "6) Oppgave 2c - isInProgram()\n"
    << "7) Oppgave 3b - testString()\n"
    << "8) Oppgave 3d - readInputToString(bottomLimit, upperLimit, length)\n"
    << "9) Oppgave 3e - countChar(a, b)\n"
    << "Yo write deloppgave pls: ";
    cin >> num;
    switch (num)
    {
    case 1: {
        cout << "Oppgave 1 a)   v0 vil bli addert med 2x10 ganger. v0 vil dermed returnere 25" << endl;
    }
        break;
    case 2: {
        testCallByValue();
        cout << endl;
    }
        break;
    case 3: {
        testCallByReference();
        cout << endl;
    }
        break;
    case 4: {
        int a = 1;
        int b = 2;
        swapNumbersByRef(a, b);
        swapNumbersByVal(2, 4);
    //    swapNumbersByConstRef(a, b);
        cout << endl;
    }
        break;
    case 5: {
        printStudent(student);
        cout << endl;
    }
        break;
    case 6: {                               // erroren forklarer at vi i tests.h filen har inkludert struct filen flere ganger over h filer. Kan bruke pragma once for å unngå dette
        if (isInProgram(student, "MTBitchTek")) {
            cout << "True";
        }
        else {
            cout << "False";
        }
        cout << endl;
    }
        break;
    case 7: {
        testString();
        cout << endl;
    }
        break;
    case 8: {
        char bottomLimit = 'a';
        char upperLimit = 'f';
        int length = 8;
        readInputToString(bottomLimit, upperLimit, length);
        cout << endl;
    }
        break;
    case 9: {
        string a = "iiiisi";
        char b = 'i';
        cout << countChar(a, b);
        cout << endl;
    }
        break;
    case 10: {          // h) og i) spør om enten en while løkke eller en for løkke
        playMastermind();
        cout << endl;
    }
        break;
    case 11: {
        string code = "secret";
        string guess = "skcfgt";
        checkCharacters(code, guess);
    }
        break;
    default:
        break;
    }
    
    return 0;
}

//------------------------------------------------------------------------------
