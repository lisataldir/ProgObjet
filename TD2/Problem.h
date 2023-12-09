#ifndef PROBLEM_H_
#define PROBLEM_H_

#include "Equation.h"
#include "Timer.h"
#include <thread>
#include <execution>

class Problem{
public:
    Equation equation{};
    IMesh* imesh{};

    void solve_with_print();
    void solve_without_print();
    void solve_parallel();
};

#endif