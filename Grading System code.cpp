#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct Student {
    string name;
    float math, science, english, average;
    string remark;
};

float inputFloat(string prompt) {
    float val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= 0 && val <= 100) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Enter number from 0 to 100.\n";
    }
}

int inputInt(string prompt, int min, int max) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= min && val <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Enter number from " << min << " to " << max << ".\n";
    }
}

char inputYN(string prompt) {
    char c;
    while (true) {
        cout << prompt;
        cin >> c; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        c = toupper(c);
        if (c == 'Y' || c == 'N') return c;
        cout << "Enter Y or N.\n";
    }
}

int main() {
    do {
        int count = inputInt("How many students? (1-30): ", 1, 30);
        vector<Student> students;

        for (int i = 0; i < count; ++i) {
            Student s;
            cout << "\n[Student " << i + 1 << "]\nEnter name: ";
            getline(cin, s.name);
            s.math = inputFloat("Math: ");
            s.science = inputFloat("Science: ");
            s.english = inputFloat("English: ");
            s.average = (s.math + s.science + s.english) / 3;
            s.remark = s.average >= 90 ? "Excellent" : s.average >= 75 ? "Passed" : "Failed";
            students.push_back(s);

            if (inputYN("Summarized Grades? (Y/N): ") == 'Y') break;
        }

        sort(students.begin(), students.end(), [](auto &a, auto &b) {
            return a.average > b.average;
        });

        cout << "\n----- STUDENT GRADE SUMMARY -----\n";
        cout << left << setw(15) << "Name"
             << setw(10) << "Math" << setw(10) << "Science"
             << setw(10) << "English" << setw(10) << "Average"
             << setw(10) << "Remarks\n";

        for (auto &s : students) {
            cout << left << setw(15) << s.name
                 << setw(10) << s.math << setw(10) << s.science
                 << setw(10) << s.english << setw(10) << fixed << setprecision(1) << s.average
                 << setw(10) << s.remark << "\n";
        }
    } while (inputYN("\nRepeat program? (Y/N): ") == 'Y');

    cout << "\nThank you!\n";
    return 0;
}