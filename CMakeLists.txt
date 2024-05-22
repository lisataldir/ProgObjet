cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(SimulationEquationDeTransport)

add_executable(Main.exe Main.cpp Timer.cpp Variable.cpp IMesh.cpp Equation.cpp Problem.cpp)
add_executable(Test.exe Test.cpp Timer.cpp Variable.cpp IMesh.cpp Equation.cpp Problem.cpp)

find_package(Threads)
find_package(TBB)
target_link_libraries(Main.exe PRIVATE Threads::Threads TBB::tbb)

enable_testing()
add_test(Test Test.exe)
find_package(GTest REQUIRED)

target_sources(Test.exe PRIVATE Test.cpp Variable.cpp IMesh.cpp Equation.cpp Problem.cpp)
target_link_libraries(Test.exe PUBLIC GTest::GTest GTest::Main)
target_link_libraries(Test.exe PRIVATE Threads::Threads TBB::tbb)

gtest_discover_tests(Test.exe)