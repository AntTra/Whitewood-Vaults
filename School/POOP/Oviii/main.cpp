//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//
// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "cannonball.h"
#include "cannonball_viz.h"
#include "utilities.h"

//------------------------------------------------------------------------------'

void testDeviation(double compareOperand, double toOperand,
double maxError, string name);


int main() {

    testDeviation(velX(50.0,2.5), 50.0, 0.0001, "velX(50.0,2.5)");
    testDeviation(velX(50.0,5.0), 50.0, 0.0001, "velX(50.0,5.0)");

    testDeviation(velY(25.0,2.5), 0.475, 0.0001, "velY(25.0,2.5)");
    testDeviation(velY(25.0,5.0), -24.05, 0.0001, "velY(25.0,5.0)");

    testDeviation(posX(0.0,50.0,2.5), 125.0, 0.0001, "posX(0.0,50.0,2.5)");
    testDeviation(posX(0.0,50.0,5.0), 250.0, 0.0001, "posX(0.0,50.0,5.0)");

    testDeviation(posY(0.0,25.0,2.5), 31.84, 0.0001, "posY(0.0,25.0,2.5)");
    testDeviation(posY(0.0,25.0,5.0), 2.375, 0.0001, "posY(0.0,25.0,5.0)");

    //vectorArray();

    cannonBallViz(600, 9000, 500, 100, 20);


    cout << "Distance traveled " << getDistanceTraveled(13.8728, 7.22175) << endl;

    cout << "Error: " << targetPractice(20.4253, 13.8728, 7.22175) << endl;

    cout << endl;

    //bool checkIfDistanceToTargetIsCorrect() {               //function definition is not allowed here.      
    //    double error = targetPractice(100,0,0);             //errorkoden er det samme med ulike parametre men hey. Dersom erroren ikke er 0 så returnerer den ikke feilmelding
    //    if(error == 0) return true;                
    //}

    playTargetPractice();

    return 0;
}

void testDeviation(double compareOperand, double toOperand, double maxError, string name) {
    if (abs(compareOperand - toOperand) <= maxError) {
        cout << name << " is valid" << endl;
    }
    else {
        cout << name << " is not valid, expected " << toOperand << ", got " << compareOperand << endl;
    }
}

//------------------------------------------------------------------------------
