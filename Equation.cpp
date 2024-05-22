#include "Equation.h"
#include <iostream>
#include <exception>

Variable Equation::compute(IMesh* imesh, Variable& u_n, Variable& u_np1){
    try {
        if (!imesh) {
            throw std::invalid_argument("In Equation::compute : IMesh cannot be nullptr.");
        }

        int n = imesh->x_size();
        u_np1[0] = u_n[0];

        for (int i = 1; i < n; ++i){
            u_np1[i] = u_n[i] - 0.5*(u_n[i] - u_n[i-1]);
        } 
        return u_np1;
    } catch (const std::exception& e) {
        std::cout << "Invalid argument : " << e.what() << std::endl;
        return u_n;
    }
    
}