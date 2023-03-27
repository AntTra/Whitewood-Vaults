#include "imp.h"



void userInputToFile() {
    filesystem::path fileName{"myFile.txt"};
    ofstream outputStream{fileName};
    ifstream inputStream{fileName};
    string nextword;
    string str;
    cout << "Write 'quit' to quit writing. ";
    while (1) {
        cout << "Write words to file: ";
        cin >> str;
        if (str == "quit") {
            break;
        }
        outputStream << str << endl;
    }

    cout << "\n\nWords written line by line" << endl;

    while (inputStream >> nextword) {
        cout << nextword << endl;
    }
    readFromFile();
}

void readFromFile() {
    string nextword;
    string nxtline;
    int i = 1;
    ifstream inputStream{"myFile.txt"};
    
    if (!inputStream) {                              //check the error
        cout << "Error: Can't open from input file " << '"' << "myFile.txt" << '"' << endl;
        }
    else {
        cout << "Please enter output file name: ";   //user input name
        string oname; 
        cin >> oname;
        ofstream oStream(oname.c_str());
        ifstream ist(oname.c_str());
        while (inputStream >> nextword) {   
            oStream << i << ". " << nextword << endl;
            i++;
            }   
        cout << "\n\nWords written to file, line by line with enumerate: " << endl;
        while (getline(ist, nxtline)) {   
            cout << nxtline << endl;
            }   
        cout << "\n\n";
    }
}

void countChar() {
    vector<int>characterCount(26, 0);
    filesystem::path file{"grunnlov.txt"};
    ifstream inputStream{file};
    char a = 'a';   
    char nextChar;

    if (!inputStream) {     //  check error
        cerr << "Error: Can't open from input file\n";
    }

    else {
    while (inputStream >> nextChar) {
        nextChar = tolower(nextChar);
        for (int i = 0; i < 26; i++) {
        if (nextChar == a + i) {
                ++characterCount[i];
            }
        }
    }

    for (a = 'a'; a <= 'z'; a++) {
        std::cout << a << ": " << characterCount[a-'a'] << endl;
        }

    }
}

class CourseCatalog
{
private:
    map<string, string> courses;
public:
    void addCourse(const string& code, const string& name) {
        courses[code] = name;
    }

    void removeCourse(const string& code) {
        courses.erase(code);
    }

    string getCourse(const string& code) {
        return courses[code];
    }

    friend ostream& operator<<(ostream& os, const CourseCatalog& c) {
        for (const auto& course : c.courses) {
            os << course.first << " - " << course.second << endl;
        }
        return os;
    }
    
    void loadFromFile(string filename) {
        ifstream infile(filename);
        if (!infile) {
            cerr << "Could not open file: " << filename << endl;
            return;
        }

        string code, name;
        while (getline(infile, code, ',') && getline(infile, name)) {
            courses[code] = name;
        }

        infile.close();
    }

    void saveToFile(string filename) {
        ofstream outfile(filename);
        if (!outfile) {
            cerr << "Could not open file: " << filename << endl;
            return; 
        }

        for (const auto& course : courses) {
            outfile << course.first << "," << course.second << endl;
        }

        outfile.close();
    }
};

void test() {
    CourseCatalog catalog;
    catalog.addCourse("TDT4110", "Informasjonsteknologi grunnkurs");
    catalog.addCourse("TDT4102", "Prosedyre- og objektorientert programmering");
    catalog.addCourse("TMA4100", "Matematikk 1");

    cout << catalog << endl;

    catalog.addCourse("TDT4102", "C++");
    cout << catalog << endl;

    catalog.saveToFile("courses.txt");

    CourseCatalog catalog2;
    catalog2.loadFromFile("courses.txt");
    cout << catalog2 << endl;
}



istream& operator>>(istream& is, Temps& t) {
    is >> t.max >> t.min;
    return is;
}

vector<Temps> readTemps(const string& filename) {
    vector<Temps> temps;
    ifstream file(filename);
    if (file) {
        Temps t;
        while (file >> t) {
            temps.push_back(t);
        }
    } else {
        std::cerr << "Failed to open file " << filename << endl;
    }
    return temps;
}

void tempStats(const vector<Temps>& temps) {
    if (temps.empty()) {
        cout << "No temperatures to analyze" << endl;
        return;
    }
    int max_idx = 0;
    int min_idx = 0;
    for (int i = 1; i < temps.size(); i++) {
        if (temps[i].max > temps[max_idx].max) {
            max_idx = i;
        }
        if (temps[i].min < temps[min_idx].min) {
            min_idx = i;
        }
    }
    cout << "Day with highest temperature: " << max_idx << ", max temp: " << temps[max_idx].max << endl;
    cout << "Day with lowest temperature: " << min_idx << ", min temp: " << temps[min_idx].min << endl;
}



