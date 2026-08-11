cmake_minimum_required(VERSION 3.20)
project(FinanceTracker)
set(CMAKE_CXX_STANDARD 17)
find_package(SQLite3 REQUIRED)
add_executable(FinanceTracker
    main.cpp
    Database.cpp
)
target_link_libraries(FinanceTracker PRIVATE SQLite3::SQLite3)

find_package(GTest REQUIRED)

enable_testing()

add_executable(DatabaseTest
        tests/DatabaseTest.cpp
        Database.cpp
)

target_link_libraries(DatabaseTest
        PRIVATE
        SQLite3::SQLite3
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(DatabaseTest)