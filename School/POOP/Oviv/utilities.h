#pragma once 

#include "std_lib_facilities.h"

int incrementByValueNumTimes (int startValue, int increment, int numTimes);

void incrementByValueNumTimesRef (int &startValue, int increment, int numTimes);

int swapNumbersByVal(int x1, int x2);

int swapNumbersByRef(int &x1, int &x2);

int swapNumbersByConstRef(const int& x1, const int& x2);

struct Student{string name; string studyProgram; int age;}; 

void printStudent(Student& student);

bool isInProgram(const Student& student,const string& program);

string randomizeString(char bottomLimit, char upperLimit, int length);

string readInputToString(char bottomLimit, char upperLimit, int length);

int countChar(string& str, char car);

void playMastermind();

int checkCharactersAndPosition(string& code, string& guess);

void checkCharacters(string& code, string& guess);

string convertToUpper(string str);
