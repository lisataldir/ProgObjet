#ifndef PROBLEM_H_
#define PROBLEM_H_

#include "Equation.h"
#include <exception>
#include <stdexcept>
#include <memory>

class Problem{
public:
    Problem(Equation eq,  IMesh* mesh);
    ~Problem() {delete imesh;}
    void solve();

    void solve_without_print();
    void solve_parallel();
    void solve_with_task();
    
private:
    Equation equation{};
    IMesh* imesh;
};

#endif