#include <iostream>
#include <sqlite3.h>
#include "Database.h"

Database::Database(const std::string& filename) {
    if (sqlite3_open(filename.c_str(), &db) == SQLITE_OK) {
        std::cout << "Database connected!" << std::endl;
    } else {
        std::cout << "Database connection failed: "
                  << sqlite3_errmsg(db) << std::endl;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

void Database::createTable() {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE
        );
        CREATE TABLE IF NOT EXISTS expenses (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            category TEXT NOT NULL,
            amount REAL NOT NULL,
            date TEXT DEFAULT CURRENT_DATE
        );
        CREATE TABLE IF NOT EXISTS incomes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            category TEXT NOT NULL,
            amount REAL NOT NULL,
            date TEXT DEFAULT CURRENT_DATE
        );
    )";
    char* errorMessage = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cout << "SQL error: "
                  << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    else {
        std::cout << "Tables created successfully!" << std::endl;
    }
}

void Database::addExpense(const std::string& category, double amount) {
    const char* sql = R"(
        INSERT INTO expenses(category, amount)
        VALUES (?, ?);
    )";
    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK) {
        std::cout << "Prepare failed: "
                  << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(
        statement,
        1,
        category.c_str(),
        -1,
        SQLITE_TRANSIENT
    );
    sqlite3_bind_double(statement, 2, amount);

    if (sqlite3_step(statement) == SQLITE_DONE) {
        std::cout << "Expense added!" << std::endl;
    }
    else {
        std::cout << "Insert failed: "
                  << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(statement);
}

void Database::addIncome(const std::string& category, double amount)
{
    const char* sql =
        "INSERT INTO incomes (category, amount) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: "
                  << sqlite3_errmsg(db) << std::endl;
        return;
    }
    sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 2, amount);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Insert failed: "
                  << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Income added!" << std::endl;
    }
    sqlite3_finalize(stmt);
}

void Database::printReport() {
    const char* expenseSql = R"(
        SELECT category, amount, date
        FROM expenses
        WHERE strftime('%Y-%m', date) = strftime('%Y-%m', 'now');
    )";

    const char* incomeSql = R"(
        SELECT category, amount, date
        FROM incomes
        WHERE strftime('%Y-%m', date) = strftime('%Y-%m', 'now');
    )";

    sqlite3_stmt* stmt;

    double totalExpenses = 0.0;
    double totalIncomes = 0.0;

    if (sqlite3_prepare_v2(db, expenseSql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Prepare failed: "
                  << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "\n===== Expenses this month =====\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* category =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        double amount = sqlite3_column_double(stmt, 1);
        const char* date =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        std::cout << category
                  << " | " << amount
                  << " | " << date
                  << std::endl;
        totalExpenses += amount;
    }

    sqlite3_finalize(stmt);

    if (sqlite3_prepare_v2(db, incomeSql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Prepare failed: "
                  << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "\n===== Income this month =====\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* category =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        double amount = sqlite3_column_double(stmt, 1);

        const char* date =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        std::cout << category
                  << " | " << amount
                  << " | " << date
                  << std::endl;

        totalIncomes += amount;
    }

    sqlite3_finalize(stmt);

    std::cout << "\n===== Summary =====\n";

    std::cout << "Total income:   " << totalIncomes << std::endl;
    std::cout << "Total expenses: " << totalExpenses << std::endl;
    std::cout << "Balance:        "
              << totalIncomes - totalExpenses
              << std::endl;
}
