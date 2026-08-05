#include <iostream>
using namespace std;

void printMenu() {
    cout << "==== Finance Tracker ====" << endl;
    cout << "1. Add expenses" << endl;
    cout << "2. Add income" << endl;
    cout << "3. Report" << endl;
    cout << "4. Quit" << endl;
    cout << "Enter action: ";
}

void addExpenses() {
    double expense = 0.0;
    int category = 0;
    cout << "==== Categories ====" << endl;
    vector<string> categories = {
        "Transport",
        "Shopping",
        "Education",
        "Pets",
        "Beauty",
        "Gas",
        "Food",
        "Electronics",
        "Health",
        "Kids",
        "Travel",
        "Internet"
    };

    for (int i = 0; i < categories.size(); i++) {
        cout << i + 1 << ". " << categories[i] << '\n';
    }
    cout << "Enter the category: ";
    cin >> category;
    cout << "Enter the expense: ";
    cin >> expense;
    //TODO: database
}

int handleChoice() {
    int started_choice = 0;
    do {
        printMenu();
        cin >> started_choice;

        switch (started_choice) {
            case 1: addExpenses(); break;
            case 2: cout << "Add income" << endl; break;
            case 3: cout << "Report" << endl; break;
            case 4: cout << "Have a nice day!" << endl; break;
            default: cout << "Invalid choice.\n";
        }
    } while (started_choice != 4);
    return 0;
}

int main() {
    handleChoice();

    return 0;
}