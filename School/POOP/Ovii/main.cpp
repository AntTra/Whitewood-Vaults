#include "std_lib_facilities.h"
#include "AnimationWindow.h"

//------------------------------------------------------------------------------'

void inputIntegerAndPrint() {
     int x = 0;

     cout << "Skriv inn et heltall: ";
     cin >> x;
     cout << "Du skrev: " << x << endl;

}

int inputInteger() {
     int tall;
     cout << "Skriv inn et heltall: ";
     cin >> tall;
     return tall;
}

void inputIntegersAndPrintSum() {
     int y = inputInteger();
     int z = inputInteger();
     cout << "Summen av tallene: " << y + z << endl;
}

int isOdd(int odd) {
        if (odd % 2 != 0) {
            return true;
        }
        else {
            return false;
        }
}


void printHumanReadableTime(int s) {
     int s1 = s % 60;
     int m1 = s / 60;
     int m = m1 % 60;
     int t = m1 / 60;
     
     cout << s1 << "seconds " << m << "minutes " << t << "hours" << endl;
}

void sum() {
    int a1, l1, k1;
    cout << "Skriv antall tall som skal summeres: ";
    cin >> a1;
    for (int i = 0; i < a1; ++i) {                                                                        // for er best når det er kjent mengde med tilfeller
        cout << "Skriv et tall som skal summeres: ";
        cin >> l1;
        k1 += l1;
        }
    cout << "Sum: " << k1 << "\n" << endl;
    cout << "Avslutter programmet" << endl;
}

void sum0() {
    int l, k;
    cout << "Skriv tall som skal summeres: ";
    cin >> k;
    while (1) {                                                                                            // while er best når det er ukjent mengde med tilfeller
        cout << "Skriv et annet tall som skal summeres (avbryt program ved å skrive 0): ";
        cin >> l;
        k += l;
        cout << "Sum: " << k << "\n" << endl;
        if (l == 0) {
            break;
        }
     } 
    cout << "Avslutter programmet" << endl;
}

void inputDouble() {
    double q;
    cout << "Skriv inn et desimaltall: "<< endl;
    cin >> q;
    cout << "Du skrev " << q << endl; 
}

void nokToEuro() {                                                                                       // vil ikke omskrive funksjonene tidligere for at det skal passe inn i neste oppgave
    double NOK;
    cout << "Skriv NOK som skal konverteres til EURO: ";
    cin >> NOK;
    cout.precision(2);
    cout << NOK << " NOK blir til " << fixed << NOK / 9.75 << " EURO" << endl;                           // ville brukt inputDouble fordi den ville returnert en double verdi fremfor en integer. Nyttig når man deler med en double/float
}

void multiplicationTable() {
    int u, h, w, res;
    cout << "Skriv høyden: ";
    cin >> h;
    cout << "Skriv bredden: ";
    cin >> w;

    for (int t = 1; t <= h; ++t) {
        for (u = 1; u <= w; ++u) {
            res = t * u;
            cout << res << "   ";
        }
        cout << "\n";
        cout << "\n";
    }
    cout << "\n";
}

int discriminant(double a, double b, double c) {
    return pow(b, 2) - 4 * a * c;
}

int printRealRoots(double a, double b, double c) {
    double x1, x2;
    if (discriminant(a, b, c) > 0) {
        x1 = (-b + sqrt(discriminant(a, b, c))) / (2 * a); 
        x2 = (-b - sqrt(discriminant(a, b, c))) / (2 * a);
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
    else if (discriminant(a, b, c) == 0) {
        x1 = -b / (2 * a);
        cout << "x1 = x2 = " << x1 << endl;
    }
    else if (discriminant(a, b, c) < 0) {
        cout << "Yu trippin on sum imaginary shit rn" << endl;
    }
    return 0;
}

int solveQuadraticEquation() {
    double a, b, c;
    int res;
    cout << "Skriv inn 3 desimaltall: ";
    cin >> a >> b >> c;
    res = printRealRoots(a, b, c);
    return res;
}

int calculateBalance(int innskudd, int rente, int aar) {
    vector<int> saldo(0);
    saldo.push_back(innskudd * pow((1 + rente/static_cast<double>(100)), aar));
    return saldo.at(0);
}

void printBalance() {
    int innskudd1, rente1, aar1;
    cout << "Hei bruker! Skriv inn din innskudd, rente og år osv. bank account number pls ";
    cin >> innskudd1 >> rente1 >> aar1;
    for (int poop = 0; poop < aar1; poop++) {
        cout << "År" << "    " << "Saldo" << endl;
        int bingbong = calculateBalance(innskudd1, rente1, poop);
        cout << poop << "      " << bingbong << endl; 
    }
}

void menu() {
    while(1) {
        cout << "Velg en funksjon: \n"
        << "0) Avslutt\n"
        << "1) InputIntegerAndPrint\n"
        << "2) InputInteger\n"
        << "3) InputIntegersAndPrintSum\n"
        << "4) Teori\n"
        << "5) isOdd\n"
        << "6) printHumanReadableTime\n"
        << "7) sum for\n"
        << "8) sum while\n"
        << "9) inputDouble\n"
        << "10) nokToEuro\n"
        << "11) multiplicationTable\n"
        << "12) solveQuadraticEquation\n"
        << "13) win.draw_triangle\n"
        << "14) calculateBalance\n"
        << "15) printBalance"
        << "Angi valg (0-15): ";

        int choice;
        cin >> choice;

        switch(choice) {
            case 0: {
                // 0) avslutt'
                return;
            }
                break;
            case 1: {
                // 1) inputIntegerAndPrint
                inputIntegerAndPrint();
                cout << "" << endl;
            }
                break;
            case 2: {
                // 2) inputInteger
                int number = inputInteger();
                cout << "Du skrev: " << number << endl;
                cout << "" << endl;
            }
                break;
            case 3: {
                // 3) inputIntegersAndPrintSum
                inputIntegersAndPrintSum();
                cout << "" << endl;
            }
                break;
            case 4: {
                cout << "Tror ikke det vil funkte å bruke inputIntegerAndPrint i inputIntegersAndPrintSum mest fordi jeg burde hatt cout << text i main slik at det ikke blir outputta to ganger. Aner ikke hvorfor man ville brukt de to funksjonene fremfor andre. Fordi det er enklest?\n" << endl;
            }
                break;
            case 5: {
                cout << (isOdd(5) ? "true\n" : "false\n") << endl;
            }
                break;
            case 6: {
                printHumanReadableTime(36000);
                cout << "" << endl;
            }
                break;
            case 7: {
                sum();
                cout << "" << endl;
            }
                break;
            case 8: {
                sum0();
                cout << "" << endl;
            }
                break;
            case 9: {
                inputDouble();
                cout << "" << endl;
            }
                break;
            case 10: {
                nokToEuro();
                cout << "" << endl;
            }
                break;
            case 11: {
                multiplicationTable();
                cout << endl;
            }
            break;
            case 12: {
                solveQuadraticEquation();
                cout << endl;
            }
            break;
            case 13: {
                AnimationWindow window{100, 100, 1500, 1200, "Pythagoras"};
                Point point1{450, 450}, point2{300, 450}, point3{300, 250};
                window.draw_triangle(point1, point2, point3, Color::black);
                window.draw_quad(point1, point2, Point{300, 600}, Point{450, 600}, Color::red);
                window.draw_quad(point3, point2, Point{100, 450}, Point{100, 250}, Color::green);
                window.draw_quad(point3, point1, Point{650, 300}, Point{500, 100});
                window.wait_for_close();
            }
            break;
            case 14: {
                calculateBalance(5000, 3, 2);
                cout << endl;
            }
            break;
            case 15: {
                printBalance();
                cout << endl;
            }
            break;
            default: {
                cout << "Vennligst angi et heltall mellom 0 og 6\n" << endl;
            }
                break;
        }
    }
}

int main() {
     while(1) {
         menu();
         break;
     }
return 0;
}

//------------------------------------------------------------------------------