#ifndef DATABASE_H
#define DATABASE_H
#include <sqlite3.h>
#include <string>

class Database {
private:
    sqlite3* db;

public:
    Database(const std::string& filename);
    ~Database();

    void createTable();
    void addExpense(const std::string& category, double amount);
    void addIncome(const std::string& category, double amount);
};

#endif