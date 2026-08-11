#include <sqlite3.h>
#include <gtest/gtest.h>
#include "Database.h"
using namespace std;

class DatabaseTest : public ::testing::Test {
protected:
    const string filename = "test.db";

    void SetUp() override {
        remove(filename.c_str());
    }
    void TearDown() override {
        remove(filename.c_str());
    }
};

TEST_F(DatabaseTest, DatabaseFileIsCreated) {
    Database db(filename);
    sqlite3* connection = nullptr;
    EXPECT_EQ(sqlite3_open(filename.c_str(), &connection), SQLITE_OK);
    sqlite3_close(connection);
}

TEST_F(DatabaseTest, TableIsCreated) {
    Database db(filename);
    db.createTable();

    sqlite3* connection = nullptr;
    ASSERT_EQ(sqlite3_open(filename.c_str(), &connection), SQLITE_OK);

    sqlite3_stmt* stmt = nullptr;

    const char* sql =
        "SELECT name FROM sqlite_master "
        "WHERE type='table' AND name='expenses';";

    ASSERT_EQ(sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr), SQLITE_OK);
    EXPECT_EQ(sqlite3_step(stmt), SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(connection);
}

TEST_F(DatabaseTest, ExpenseCanBeInserted) {
    Database db(filename);

    db.createTable();
    db.addExpense("Food", 100);

    sqlite3* connection = nullptr;
    ASSERT_EQ(sqlite3_open(filename.c_str(), &connection), SQLITE_OK);

    sqlite3_stmt* stmt = nullptr;
    const char* sql =
        "SELECT COUNT(*) FROM expenses; ";

    ASSERT_EQ(sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr), SQLITE_OK);
    ASSERT_EQ(sqlite3_step(stmt), SQLITE_ROW);
    EXPECT_EQ(sqlite3_column_int(stmt, 0), 1);

    sqlite3_finalize(stmt);
    sqlite3_close(connection);
}

TEST_F(DatabaseTest, CorrectCategoryIsStored) {
    Database db(filename);

    db.createTable();
    db.addExpense("Transport", 50);

    sqlite3* connection = nullptr;
    ASSERT_EQ(sqlite3_open(filename.c_str(), &connection), SQLITE_OK);

    sqlite3_stmt* stmt = nullptr;
    const char* sql =
        "SELECT category FROM expenses LIMIT 1; ";

    ASSERT_EQ(sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr), SQLITE_OK);
    ASSERT_EQ(sqlite3_step(stmt), SQLITE_ROW);

    string category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

    EXPECT_EQ(category, "Transport");

    sqlite3_finalize(stmt);
    sqlite3_close(connection);
}

TEST_F(DatabaseTest, CorrectAmountIsStored)
{
    Database db(filename);

    db.createTable();
    db.addExpense("Food", 99.99);

    sqlite3* connection = nullptr;
    ASSERT_EQ(sqlite3_open(filename.c_str(), &connection), SQLITE_OK);

    sqlite3_stmt* stmt = nullptr;

    const char* sql =
        "SELECT amount FROM expenses LIMIT 1;";

    ASSERT_EQ(
        sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr),
        SQLITE_OK
    );

    ASSERT_EQ(sqlite3_step(stmt), SQLITE_ROW);

    EXPECT_NEAR(
        sqlite3_column_double(stmt, 0),
        99.99,
        0.001
    );

    sqlite3_finalize(stmt);
    sqlite3_close(connection);
}

TEST_F(DatabaseTest, MultipleExpenseCanBeInserted) {
    Database db(filename);

    db.createTable();
    db.addExpense("Food", 20);
    db.addExpense("Gas", 40);
    db.addExpense("Pets", 60);

    sqlite3* connection = nullptr;
    ASSERT_EQ(sqlite3_open(filename.c_str(), &connection), SQLITE_OK);

    sqlite3_stmt* stmt = nullptr;
    const char* sql =
        "SELECT COUNT(*) FROM expenses; ";

    ASSERT_EQ(sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr), SQLITE_OK);
    ASSERT_EQ(sqlite3_step(stmt), SQLITE_ROW);
    EXPECT_EQ(sqlite3_column_int(stmt, 0), 3);

    sqlite3_finalize(stmt);
    sqlite3_close(connection);
}