#include "Equation.h"

Variable Equation::compute(IMesh* imesh, Variable u_n, Variable u_np1){
    if (imesh == nullptr) return u_n;

    int n = imesh->x_size();
    u_np1.u.resize(n);
    u_np1[0] = u_n[0];

    for (int i = 1; i < n; ++i){
        u_np1[i] = u_n[i] - 0.5*(u_n[i] - u_n[i-1]);
    } 
    return u_np1;
}
