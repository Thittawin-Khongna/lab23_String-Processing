#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

struct Student {
    string name;
    int score;
    char grade;
};

vector<Student> students;

string toLowercase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void importDataFromFile() {
    ifstream file("name_score.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open file 'name_score.txt'." << endl;
        return;
    }

    string line; 
    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;

        string name = line.substr(0, colonPos);
        string scoresStr = line.substr(colonPos + 1);

        int score1, score2, score3;
        if (sscanf(scoresStr.c_str(), "%d %d %d", &score1, &score2, &score3) != 3) continue;

        int totalScore = score1 + score2 + score3;
        char grade;
        if (totalScore >= 80) grade = 'A';
        else if (totalScore >= 70) grade = 'B';
        else if (totalScore >= 60) grade = 'C';
        else if (totalScore >= 50) grade = 'D';
        else grade = 'F';

        students.push_back({name, totalScore, grade});
    }
    file.close();
}

void searchName(const string& name) {
    bool found = false;
    string lowerName = toLowercase(name);

    for (const auto& student : students) {
        if (toLowercase(student.name) == lowerName) {
            cout << "---------------------------------" << endl;
            cout << student.name << "'s score = " << student.score << endl;
            cout << student.name << "'s grade = " << student.grade << endl;
            cout << "---------------------------------" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "---------------------------------" << endl;
        cout << "Cannot found." << endl;
        cout << "---------------------------------" << endl;
    }
}

void searchGrade(char grade) {
    bool found = false;
    grade = toupper(grade);

    cout << "---------------------------------" << endl;
    for (const auto& student : students) {
        if (student.grade == grade) {
            cout << student.name << " (" << student.score << ")" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Cannot found." << endl;
    }
    cout << "---------------------------------" << endl;
}

void getCommand() {
    string command;
    while (true) {
        cout << "Please input your command:" << endl;
        getline(cin, command);

        string lowerCommand = toLowercase(command);

        if (lowerCommand.substr(0, 4) == "name") {
            string name = command.substr(5);
            name.erase(0, name.find_first_not_of(' '));
            name.erase(name.find_last_not_of(' ') + 1);
            searchName(name);
        } else if (lowerCommand.substr(0, 5) == "grade") {
            char grade = command[6];
            searchGrade(grade);
        } else if (lowerCommand == "exit") {
            break;
        } else {
            cout << "---------------------------------" << endl;
            cout << "Invalid command." << endl;
            cout << "---------------------------------" << endl;
        }
    }
}

int main() {
    importDataFromFile();
    getCommand();
    return 0;
}