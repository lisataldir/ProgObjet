#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include "IMesh.h"


class Variable{
private:
    IMesh* imesh{};
    char const * m_name;
public:
    std::vector<double> u;
    Variable(IMesh* mesh, char const* name);
    double& operator[](int i);
    void print(int iter);
};

struct Upwind{
    static Variable update(Variable& u_n, Variable& u_np1, double t, IMesh* imesh){
        try {
            if (!imesh) throw std::invalid_argument("In Upwind : IMesh cannot be nullptr.");

            int n = imesh->x_size();
            u_np1[0] = u_n[0];

            for (int i = 1; i < n; ++i){
                u_np1[i] = u_n[i] - 0.5*(u_n[i] - u_n[i-1]);
            } 
            return u_np1;
        } catch (const std::exception& e){
            std::cout << "Invalid argument : " << e.what() << std::endl;
            return u_np1;
        }
        
    }
};

struct LaxWendroff{
    static Variable update(Variable& u_n, Variable& u_np1, double t, IMesh* imesh){
        try {
            if (!imesh) throw std::invalid_argument("In LaxWendroff : IMesh cannot be nullptr.");

            int n = imesh->x_size();
            u_np1[0] = u_n[0];

            double dt = imesh->getStepTime();
            double dx = imesh->getStepSpace();
            double a = 0.5*dx/dt;

            for (int i = 1; i < n - 1; ++i){
                u_np1[i] = u_n[i] - a*dt/(2*dx) *( u_n[i+1] - u_n[i-1]) + a*a*dt*dt/(2*dx*dx) * (u_n[i+1] - 2*u_n[i] + u_n[i-1]);
            } 
            u_np1[n-1]= u_n[n-1];
            return u_np1;

        } catch (const std::exception& e) {
            std::cout << "Invalid argument : " << e.what() << std::endl;
            return u_np1;
        }
        
    }
};

#endif