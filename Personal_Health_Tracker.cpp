#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

struct User {
    string name;
    int age;
    float height;
    float weight;
};

float calculateBMI(float weight, float height) {
    return weight / (height * height);
}

string getBMICategory(float bmi) {
    if (bmi < 18.5)
        return "Underweight";
    else if (bmi < 25)
        return "Normal weight";
    else if (bmi < 30)
        return "Overweight";
    else
        return "Obese";
}

string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[11];
    sprintf(date, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return string(date);
}

void saveToFile(string date, string entry) {
    ofstream file("health_log.txt", ios::app);
    if (file.is_open()) {
        file << "[" << date << "] " << entry << "\n";
        file.close();
    } else {
        cout << " Error opening file to save data.\n";
    }
}

int main() {
    User user;
    int choice;
    float bmi;
    int totalCalories = 0;
    int totalSteps = 0;
    string date = getCurrentDate();

    cout << " Enter your name: ";
    getline(cin, user.name);
    cout << " Enter your age: ";
    cin >> user.age;
    cout << " Enter height (in meters): ";
    cin >> user.height;
    cout << " Enter weight (in kg): ";
    cin >> user.weight;

    bmi = calculateBMI(user.weight, user.height);
    string category = getBMICategory(bmi);

    saveToFile(date, "User: " + user.name + ", Age: " + to_string(user.age) +
                ", BMI: " + to_string(bmi) + " (" + category + ")");

    while (true) {
        cout << "\n====== Personal Health Tracker ======\n";
        cout << "1. Log Meal (Calories)\n";
        cout << "2. Log Exercise (Steps)\n";
        cout << "3. Show Daily Summary\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            int calories;
            cout << " Enter calories consumed: ";
            cin >> calories;
            totalCalories += calories;
            saveToFile(date, "Meal logged: " + to_string(calories) + " kcal");
        } else if (choice == 2) {
            int steps;
            cout << " Enter number of steps: ";
            cin >> steps;
            totalSteps += steps;
            saveToFile(date, "Exercise logged: " + to_string(steps) + " steps");
        } else if (choice == 3) {
            cout << "\n Summary for " << date << ":\n";
            cout << " Name: " << user.name << "\n";
            cout << "BMI: " << bmi << " (" << category << ")\n";
            cout << " Calories consumed: " << totalCalories << " kcal\n";
            cout << " Steps taken: " << totalSteps << "\n";
        } else if (choice == 4) {
            cout << " All data saved to health_log.txt. Goodbye!\n";
            break;
        } else {
            cout << " Invalid option. Please try again.\n";
        }
    }

    return 0;
}
