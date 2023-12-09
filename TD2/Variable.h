#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "IMesh.h"


struct Variable{
    char const * m_name;
    IMesh* imesh{};
    std::vector<double> u;

    double& operator[](int i);
    void print(int iter);
};

struct Upwind{
    static Variable update(Variable u_n, Variable u_np1, double t, IMesh* imesh){
        if (imesh == nullptr) return u_n;

        int n = imesh->x_size();
        u_np1.u.resize(n);
        u_np1[0] = u_n[0];

        for (int i = 1; i < n; ++i){
            u_np1[i] = u_n[i] - 0.5*(u_n[i] - u_n[i-1]);
        } 
        return u_np1;
    }
};

struct LaxWendroff{
    static Variable update(Variable u_n, Variable u_np1, double t, IMesh* imesh){
        if (imesh == nullptr) return u_n;

        int n = imesh->x_size();
        u_np1.u.resize(n);
        u_np1[0] = u_n[0];

        double a = imesh->getA();
        double dt = imesh->getStepTime();
        double dx = imesh->getStepSpace();

        for (int i = 1; i < n - 1; ++i){
            u_np1[i] = u_n[i] - a*dt/(2*dx) *( u_n[i+1] - u_n[i-1]) + a*a*dt*dt/(2*dx*dx) * (u_n[i+1] - 2*u_n[i] + u_n[i-1]);
        } 

        u_np1[n-1]= u_n[n-1];

        return u_np1;
    }
};

#endif