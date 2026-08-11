cmake_minimum_required(VERSION 3.20)

project(FinanceTracker)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)
find_package(GTest REQUIRED)

enable_testing()

# Main application
add_executable(FinanceTracker
src/main.cpp
src/Database.cpp
)

target_include_directories(FinanceTracker PRIVATE
include
)

target_link_libraries(FinanceTracker PRIVATE
SQLite3::SQLite3
)

# Tests
add_executable(DatabaseTest
tests/DatabaseTest.cpp
src/Database.cpp
)

target_include_directories(DatabaseTest PRIVATE
include
)

target_link_libraries(DatabaseTest
PRIVATE
SQLite3::SQLite3
GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(DatabaseTest)
