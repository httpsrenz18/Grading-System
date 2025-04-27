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

// Limits for grades input, Enter Grades: 
float gradeLimits(string prompt) {
    float value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0 && value <= 100) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Enter number from 0 to 100.\n";
    }
}

// How many students you want to add, How many students? (1-30)
int inputStudent(string prompt, int minimum, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minimum && value <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Enter number from " << minimum << " to " << max << ".\n";
    }
}


//If you prompt wrong to the question Y(yes) N(no) it will repeat
char inputYN(string prompt) {
    char command;
    while (true) {
        cout << prompt;
        cin >> command; cin.ignore(numeric_limits<streamsize>::max(), '\n'); //only accept first letter of your input/answer
        command = toupper(command); //converting the command in uppercase. y - Y and n - N
        if (command == 'Y' || command == 'N') return command;
        cout << "Enter Y or N.\n";
    }
}

int main() {
    do {
        // uses vector to stored list of students
        int count = inputStudent("How many students? (1-30): ", 1, 30);
        vector<Student> students;
        
        
        for (int i = 0; i < count; ++i) {
            Student s;
            cout << "\n[Student " << i + 1 << "]\nEnter name: ";
            getline(cin, s.name); //getline use to allows spaces
            s.math = gradeLimits("Math: ");
            s.science = gradeLimits("Science: ");
            s.english = gradeLimits("English: ");
            s.average = (s.math + s.science + s.english) / 3;
            s.remark = s.average >= 90 ? "Excellent" : s.average >= 75 ? "Passed" : "Failed"; //? asking if the statement is true ':' if not
            students.push_back(s); // pushback is vertors command, it will repeat the process untile vector is true
            
            
            // asking if you want to summarized the grades early
            if (inputYN("Summarized Grades? (Y/N): ") == 'Y') break;
        }
        
        //sorting the grades from highest to lowest
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
    } while (inputYN("\nRepeat program? (Y/N): ") == 'Y'); //asking if you wnat to repeat the program

    cout << "\nThank you!\n"; //End of the Program
    return 0;
}