#include "utilities.h"
#include "test.h"
#include "std_lib_facilities.h"

int incrementByValueNumTimes(int startValue, int increment, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        startValue += increment;
    }
    return startValue;
}

void incrementByValueNumTimesRef (int &startValue, int increment, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        startValue += increment;
    }
}
int swapNumbersByVal(int x1, int x2) {
    int temp = x1;
    x1 = x2;
    x2 = temp;
    cout << endl << "Pass-By-Value\n" << "x1 = " << x1 << ", x2 = " << x2 << endl;
    return 0;
}
int swapNumbersByRef(int &x1, int &x2) {
    int temp = x1;
    x1 = x2;
    x2 = temp;
    cout << "Pass-By-Reference:\n" << "x1 = " << x1 << ", x2 = " << x2 << endl;
    return 0;
}

// Forskjellen på pass by value og pass by ref er at den sistnevnte leser fra memory av
// variabelen, noe som skal være mer effektivt for å endre argumentet i call funksjonen.
// pass by value er bedre dersom det skal sendes argumenter fra en funksjon til en annen


//DET GÅR JO FAEN IKKE Å ENDRE PÅ CONST ARGUMENTER. E R G O  FOR FFS. SWAP ER UMULIG!!!
//int swapNumbersByConstRef(const int& a, const int& b) {
//    int temp = a;
//    a = b;
//    b = temp;
//    printf("Pass-By-Reference:\n x1 = %d, x2 = %d", a, b);
//    return 0;
//}


void printStudent(Student& student) {
    cout << "-------------------------" << endl;
    cout << "--- " << student.name << " ---" << endl;
    cout << "------- " << student.studyProgram << " ------" << endl;
    cout << "-------- " << "Age: " << student.age << " --------" << endl;
    cout << "-------------------------" << endl;
}

bool isInProgram(const Student& student, const string& program) {
    return student.studyProgram == program;
}

string randomizeString(char bottomLimit, char upperLimit, int length) {
    string str;
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<char> distribution(bottomLimit, upperLimit);

    for (int i = 0; i < length; i++) {
        str += static_cast<char>(distribution(generator));
    }
    return str;
}

string readInputToString(char bottomLimit, char upperLimit, int length) {
    string str;
    char x;
    int i = 0; 
    cout << "Input 4 letters: ";
    while (i < length) {
        cin >> x;
        x = toupper(x);
        if (bottomLimit <= x&&x <= upperLimit) {
            str += x;
            i += 1;
        }
        else {
            cout << "Skriv no innenfor grensa\n";
        }
        
    }
    str = convertToUpper(str);
    return str;
}

int countChar(string& str, char car) {
    int ant = 0; 
    for (char s : str) {
        if (s == car) {
            ant++;
        }
    }   
    return ant;
}

string convertToUpper(string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

void playMastermind() { //constexpr gjør variabelen til const bare når programmet kjører. Bruker heller const når ting ikke funker eller når man ikke vet verdien ved compile som ved cin
    constexpr int size = 4;
    constexpr int letters = 6;
    string code = randomizeString('A', 'A' + (letters - 1), size);
    string guess;
    cout << "Fasit: " << code << endl;
    int i = 0;
    int forsok = 5;
    while (i < forsok) {                // kan bruke en do/while funksjon for å hindre at kode etter break kjører
        if (checkCharactersAndPosition(code, guess) == code.length()) {
            break;
        }    
        guess = readInputToString('A', 'A' + (letters - 1), size);
        guess = convertToUpper(guess);
        cout << "Correct guess in position:" << checkCharactersAndPosition(code, guess) << endl;
        i++;
        cout << forsok - i << " forsøk igjen" << endl;
        
    }
    if (checkCharactersAndPosition(code, guess) < code.length()) {
        cout << "BuhUU taper" << endl;
    }
    else {
        cout << "Grattis" << endl;
    }
}

int checkCharactersAndPosition(string& code, string& guess) {
    int correct = 0;
    for (int i = 0; i < code.size(); i++) {
        if (code[i] == guess[i]) {
            correct++;
        }
    }
    return correct;
}

void checkCharacters(string& code, string& guess) {
    int correct = 0;
    for (int i = 0; i < code.size(); i++) {
            correct += countChar(code, guess[i]);
    }  
    cout << "Correct letters: " << correct << endl;
    while (checkCharactersAndPosition(code, guess) < code.size()) {
        cout << "Try again. Write new code: ";
        cin >> guess;
        checkCharactersAndPosition(code, guess);
    }
}







