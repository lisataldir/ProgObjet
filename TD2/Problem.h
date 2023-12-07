#ifndef PROBLEM_H_
#define PROBLEM_H_

#include "Equation.h"
#include "Timer.h"
#include <thread>

class Problem{
public:
    Equation equation{};
    IMesh* imesh{};

    void solve();
    void solve_parallel();
};

#endif