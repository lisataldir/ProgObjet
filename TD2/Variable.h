#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include "IMesh.h"


struct Variable{
    char const * m_name;
    IMesh* imesh{};
    std::vector<double> u;

    double& operator[](int i);
    void print(int iter);
};

struct Upwind{
    Variable update(Variable&& u_n, Variable&& u_np1, double t, IMesh* imesh);
};

struct LaxWendroff{
    Variable update(Variable&& u_n, Variable&& u_np1, double t, IMesh* imesh);
};

#endif