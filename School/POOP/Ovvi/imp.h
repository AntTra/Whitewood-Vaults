#include <iostream>
#include <filesystem>
#include <fstream>
#include <ostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

void userInputToFile();
void readFromFile();
void countChar();
void test();
struct Temps {
    double max;
    double min;
};
vector<Temps> readTemps(const string& filename);
void tempStats(const vector<Temps>& temps);