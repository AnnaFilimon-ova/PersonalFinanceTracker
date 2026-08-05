#include <iostream>
#include <sqlite3.h>
#include "Database.h"
using namespace std;

Database::Database() {
    connect();
}

void Database::connect() {
    sqlite3 *db;
    if (sqlite3_open("finance.db", &db) == SQLITE_OK) {
        cout << "Database opened successfully!" << endl;
    } else {
        cout << "Database failed to open!" << endl;
    }
    sqlite3_close(db);
}

Database::~Database() {}