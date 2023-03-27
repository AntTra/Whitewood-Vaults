#include "test.h"
#include "utilities.h"
#include "std_lib_facilities.h"

void testCallByValue() {
    int v0 = 5;
    int increment = 2;
    int iterations = 10;
    int result = incrementByValueNumTimes(v0, increment, iterations);
    cout << "v0: " << v0
    << " increment: " << increment
    << " iterations: " << iterations
    << " result: " << result << endl;
}

void testCallByReference() {
    int v0 = 5;
    int increment = 2;
    int iterations = 10;
    incrementByValueNumTimesRef(v0, increment, iterations);
    cout << "v0: " << &v0
    << " increment: " << increment
    << " iterations: " << iterations
    << " result: ";
    cout << v0 << endl;
}

void testString() {
    string grades = randomizeString('A', 'F', 8);
    cout << grades << ", " << endl;
    vector<int> gradeCount(6);
    char A = 'A';
    int num = 5;
    double sum = 0;
    for (int i = 0; i < gradeCount.size(); i++) {
        gradeCount.at(i) = countChar(grades, A + i);
        sum += gradeCount.at(i)*(num - i);
        //cout << sum << endl;
        cout << A + i << ": " << gradeCount.at(i) << endl;
    }
    cout << "Gjennomsnittskarakteren er: " << sum / 8 << endl;
}

