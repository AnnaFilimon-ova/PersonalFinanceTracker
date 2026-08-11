#include <iostream>
#include "Database.h"
using namespace std;

//Prints the action menu.
void printMenu() {
    cout << "==== Finance Tracker ====" << endl;
    cout << "1. Add expenses" << endl;
    cout << "2. Add income" << endl;
    cout << "3. Report" << endl;
    cout << "4. Quit" << endl;
    cout << "Enter action: ";
}

//adds expenses to the db.
void addExpenses(Database& database) {
    double expense = 0.0;
    int category = 0;
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

    cout << "==== Categories ====" << endl;
    for (int i = 0; i < categories.size(); i++) {
        cout << i + 1 << ". " << categories[i] << '\n';
    }
    cout << "Enter the category: ";
    cin >> category;
    cout << "Enter the expense: ";
    cin >> expense;

    database.addExpense(categories[category - 1], expense);
}

//adds expenses to the db.
void addIncomes(Database& database) {
    double income = 0.0;
    int income_category = 0;
    vector<string> income_categories = {
        "Salary",
        "Freelancing",
        "Business",
        "Investments",
        "Transfers",
        "Scholarship",
        "Refund",
        "Other"
    };
    cout << "==== Categories ====" << endl;
    for (int i = 0; i < income_categories.size(); i++) {
        cout << i + 1 << ". " << income_categories[i] << '\n';
    }
    cout << "Enter the category: ";
    cin >> income_category;
    cout << "Enter the income: ";
    cin >> income;

    database.addIncomes(income_categories[income_category - 1], income);
}

//controls future action.
int handleChoice(Database& database) {
    int started_choice = 0;
    do {
        printMenu();
        cin >> started_choice;

        switch (started_choice) {
            case 1: addExpenses(database); break;
            case 2: addIncomes(database); break;
            case 3: cout << "Report" << endl; break;
            case 4: cout << "Have a nice day!" << endl; break;
            default: cout << "Invalid choice.\n";
        }
    } while (started_choice != 4);
    return 0;
}

int main() {
    Database database("finance.db");
    database.createTable();
    cout << "Tracker started!" << endl;
    handleChoice(database);
    return 0;
}