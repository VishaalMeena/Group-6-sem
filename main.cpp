#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Predefined data for students, teachers, and admin users
map<string, string> studentData = {{"student1", "pass123"}, {"student2", "pass456"}};
map<string, string> teacherData = {{"teacher1", "teach123"}};
map<string, string> adminData = {{"admin", "admin123"}};

// Questions for the exam with their correct answers
vector<pair<string, string>> questions = {
    {"What is the capital of France?", "Paris"},
    {"What is 2 + 2?", "4"},
    {"Who wrote 'Hamlet'?", "Shakespeare"},
    {"What is the largest planet in our solar system?", "Jupiter"}
};

// Results of the students after taking the exam
map<string, int> results; 

/**
 * Authenticate user based on role, username, and password.
 * 
 * @param role The role of the user (student/teacher/admin).
 * @param username The username entered by the user.
 * @param password The password entered by the user.
 * @return True if the credentials are valid, false otherwise.
 */
bool authenticate(string role, string username, string password) {
    if (role == "student" && studentData.find(username) != studentData.end() && studentData[username] == password)
        return true;
    if (role == "teacher" && teacherData.find(username) != teacherData.end() && teacherData[username] == password)
        return true;
    if (role == "admin" && adminData.find(username) != adminData.end() && adminData[username] == password)
        return true;
    return false;
}

/**
 * Add a new question to the exam question set.
 * 
 * Asks for the question and its correct answer and adds it to the global list of questions.
 */
void addQuestion() {
    string question, answer;
    cout << "Enter the question: ";
    cin.ignore();
    getline(cin, question);
    cout << "Enter the correct answer: ";
    getline(cin, answer);
    questions.push_back(make_pair(question, answer));
    cout << "Question added successfully!\n";
}

/**
 * Allows a student to take the exam.
 * 
 * The student answers the questions one by one, and the system compares the answers with the correct ones.
 * The student's score is saved and displayed at the end.
 * 
 * @param student The username of the student taking the exam.
 */
void takeExam(string student) {
    if (questions.empty()) {
        cout << "No questions available yet!\n";
        return;
    }

    int score = 0;
    string studentAnswer;
    cout << "Starting the exam...\n";

    for (int i = 0; i < questions.size(); ++i) {
        cout << "Q" << i + 1 << ": " << questions[i].first << endl;
        cout << "Your answer: ";
        getline(cin, studentAnswer);

        if (studentAnswer == questions[i].second) {
            score++;
        }
    }

    results[student] = score;
    cout << "Exam completed! Your score is: " << score << "/" << questions.size() << endl;
}

/**
 * Displays the exam results of a student.
 * 
 * If the student has taken the exam, their score is displayed. Otherwise, a message is shown indicating that they haven't taken the exam yet.
 * 
 * @param student The username of the student whose results are to be displayed.
 */
void displayResults(string student) {
    if (results.find(student) != results.end()) {
        cout << "Your score: " << results[student] << "/" << questions.size() << endl;
    } else {
        cout << "No results found. Please complete the exam.\n";
    }
}

/**
 * Menu for admin users, allowing them to add questions and view registered students.
 */
void adminMenu() {
    int choice;
    do {
        cout << "\nAdmin Menu\n1. Add Question\n2. View All Students\n3. Logout\nChoice: ";
        cin >> choice;
        cin.ignore();  

        switch (choice) {
            case 1:
                addQuestion();
                break;
            case 2:
                cout << "Students Registered:\n";
                for (auto &s : studentData) {
                    cout << " - " << s.first << endl;
                }
                break;
            case 3:
                cout << "Logging out...\n";
                return;
        }
    } while (choice != 3);
}

/**
 * Menu for teacher users, allowing them to add questions.
 */
void teacherMenu() {
    int choice;
    do {
        cout << "\nTeacher Menu\n1. Add Question\n2. Logout\nChoice: ";
        cin >> choice;
        cin.ignore();  

        switch (choice) {
            case 1:
                addQuestion();
                break;
            case 2:
                cout << "Logging out...\n";
                return;
        }
    } while (choice != 2);
}

/**
 * Menu for student users, allowing them to take the exam and view their results.
 * 
 * @param student The username of the student.
 */
void studentMenu(string student) {
    int choice;
    do {
        cout << "\nStudent Menu\n1. Take Exam\n2. View Results\n3. Logout\nChoice: ";
        cin >> choice;
        cin.ignore();  

        switch (choice) {
            case 1:
                takeExam(student);
                break;
            case 2:
                displayResults(student);
                break;
            case 3:
                cout << "Logging out...\n";
                return;
        }
    } while (choice != 3);
}

/**
 * Main function that starts the Online Examination System.
 * 
 * Handles user login, verifies credentials, and directs the user to the appropriate menu based on their role.
 */
int main() {
    string role, username, password;

    cout << "Welcome to the Online Examination System\n";
    cout << "Select your role (student/teacher/admin): ";
    cin >> role;
    
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Authenticate user
    if (!authenticate(role, username, password)) {
        cout << "Invalid login credentials!\n";
        return 0;
    }

    cout << "Login successful!\n";

    // Direct to role-specific menus
    if (role == "admin") {
        adminMenu();
    } else if (role == "teacher") {
        teacherMenu();
    } else if (role == "student") {
        studentMenu(username);
    }

    return 0;
}
