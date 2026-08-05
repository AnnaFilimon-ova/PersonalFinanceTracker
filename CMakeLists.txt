cmake_minimum_required(VERSION 3.20)
project(FinanceTracker)
set(CMAKE_CXX_STANDARD 17)
find_package(SQLite3 REQUIRED)
add_executable(FinanceTracker
    main.cpp
        Database.cpp
)
target_link_libraries(FinanceTracker PRIVATE SQLite3::SQLite3)