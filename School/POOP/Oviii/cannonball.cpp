#include "cannonball.h"
#include "utilities.h"
#include "std_lib_facilities.h"

double acclY() {
    return -9.81;
}

double velX(double initVelocity, double time) {
    time = 0;
    return initVelocity;
}
double velY(double initVelocityY, double time) {
    return initVelocityY + acclY() * time;
}

double posX(double initPosition, double initVelocity, double time) {
    return initPosition + initVelocity * time;
}

double posY(double initPosition, double initVelocity, double time) {
    return initPosition + initVelocity * time + 0.5 * acclY() * pow(time, 2);
}

void printTime(double time) {
    int seconds = (int)time % 60;
    int minutes = (int)(time / 60) % 60;
    int hours = (int)minutes / 60;
    cout << fixed << setprecision(2) << seconds << "seconds " << fixed << setprecision(2) << minutes << "minutes " << fixed << setprecision(2) << hours << "hours\n";
}

double flightTime(double initVelocityY) {
    return -2 * initVelocityY / acclY();
}

// Ber brukeren om en vinkel
double getUserInputTheta() {
    double Theta;
    cout << "Write angle in degrees: ";
    cin >> Theta;
    return Theta;
}
//Ber brukeren om en absoluttfart
double getUserInputAbsVelocity() {
    double AbsVelocity;
    cout << "Write absolute velocity: ";
    cin >> AbsVelocity;
    return AbsVelocity;
}
// Konverterer fra grader til radianer
double degToRad(double deg) {
    double rad;
    rad = deg * M_PI/180;
    return rad;
}
// Returnerer henholdsvis farten i x-, og y-retning, gitt en vinkel
// theta og en absoluttfart absVelocity.
double getVelocityX(double theta, double absVelocity) {
    return absVelocity * cos(degToRad(theta));
}

double getVelocityY(double theta, double absVelocity) {
    return absVelocity * sin(degToRad(theta));
}
// Dekomponerer farten gitt av absVelocity, i x- og y-komponentene
// gitt vinkelen theta. Det første elementet i vectoren skal være
//x-komponenten, og det andre elementet skal være y-komponenten.
// "Vector" i funksjonsnavnet er vektor-begrepet i geometri
vector<double> getVelocityVector(double theta, double absVelocity) {
    vector<double> velocityVector;
    velocityVector.push_back(getVelocityX(theta, absVelocity));
    velocityVector.push_back(getVelocityY(theta, absVelocity));
    return velocityVector;
}

void vectorArray() {
    double theta = getUserInputTheta(), absvelocity = getUserInputAbsVelocity();
    vector<double> velocityVector = getVelocityVector(theta, absvelocity);
    
    cout << "Velocity vector = {";
        for (int i = 0; i < velocityVector.size(); i++) {
            cout << velocityVector[i];
            if (i != velocityVector.size() - 1) {
                cout << ", ";
        }
    }
    cout << "}" << endl;
}

double getDistanceTraveled(double velocityX, double velocityY) {
    return velocityX * flightTime(velocityY);
}

double targetPractice(double distanceToTarget,
double velocityX,
double velocityY) {
    return distanceToTarget - getDistanceTraveled(velocityX, velocityY);
}

void playTargetPractice() {

    double horisontal, vertical;
    double target = randomWithLimits(100, 1000);

    cout << "Hallah. Uhhh" << endl 
    << "Her har du spillet osv." << endl 
    << "Target er på " << target << endl
    << "Lykke til" << endl << "\n" 
    << "The range is 100 to 1000. Make your guess by writing the angle velocity you want to throw" 
    << ". You have ten tries, tourist. \n";
    
    double angle = getUserInputTheta();
    double velocity = getUserInputAbsVelocity();

    horisontal = getVelocityX(angle, velocity);
    vertical = getVelocityY(angle, velocity);

    for (int j = 0; j < 10; j++) {
        
        if (fabs(targetPractice(target, horisontal, vertical)) <= 5) {
            cout << "Får jeg godkjent nå?\n";
            break;
        }
        else if (targetPractice(target, horisontal, vertical) > 0) {
            cout << "Aim higher or smth! You were " << targetPractice(target, horisontal, vertical) << " off. \n";
        }
        else {
            cout << "Aim lower or smth! You were " << -targetPractice(target, horisontal, vertical) << " off. \n";
        }

        cout << "Flighttime was "; 
        printTime(flightTime(vertical));

        cout << "_______________________________________" << endl;
        cout << 9 - j << " forsøk igjen" << endl;
        double angle = getUserInputTheta();
        double velocity = getUserInputAbsVelocity();

        horisontal = getVelocityX(angle, velocity);
        vertical = getVelocityY(angle, velocity);
    }
    cout << "You lose. No trøsting for you";
}

