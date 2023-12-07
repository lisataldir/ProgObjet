cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(Simulation)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(Main.exe Main.cpp IMesh.cpp Variable.cpp Equation.cpp Timer.cpp Problem.cpp)
add_executable(Test.exe Test.cpp IMesh.cpp Variable.cpp Equation.cpp Timer.cpp Problem.cpp)

find_package(Threads)
target_link_libraries(Main.exe Threads::Threads)

enable_testing()
find_package(GTest REQUIRED)
add_test(Test Main.exe)
target_link_libraries(Test.exe PUBLIC GTest::GTest GTest::Main)
gtest_discover_tests(Test.exe)